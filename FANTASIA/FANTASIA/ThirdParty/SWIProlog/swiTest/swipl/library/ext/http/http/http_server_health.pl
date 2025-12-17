/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        jan@swi-prolog.org
    WWW:           http://www.swi-prolog.org
    Copyright (C): 2024 SWI-Prolog Solutions b.v.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    As a special exception, if you link this library with other files,
    compiled with a Free Software compiler, to produce an executable, this
    library does not by itself cause the resulting executable to be covered
    by the GNU General Public License. This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
*/

:- module(http_server_health,
          [ server_health/1             % +Request
          ]).
:- autoload(library(lists), [member/2]).
:- autoload(library(aggregate), [aggregate_all/3, aggregate_all/4]).
:- autoload(library(apply), [maplist/3]).
:- autoload(library(option), [option/2]).
:- autoload(library(http/http_dispatch), [http_handler/3]).
:- autoload(library(http/http_json), [reply_json/1]).
:- autoload(library(http/http_parameters), [http_parameters/2]).
:- autoload(library(http/thread_httpd), [http_server_property/2, http_workers/2]).
:- autoload(library(http/http_stream), [cgi_statistics/1]).
:- use_module(library(http/http_cors), [cors_enable/2, cors_enable/0]).

:- http_handler(root(health), server_health, [id(server_health), priority(-10)]).

/** <module> HTTP Server health statistics

This module defines an HTTP handler for ``/health``. The handler returns
a JSON document  with  elementary  health   statistics  on  the  running
instance. The location can be changed  using http_handler/3. Keys may be
added using additional clauses for health/2 or hidden using hide/1.

This  library  defines  an  HTTP  handler   and  defines  two  multifile
predicates (health/2 and hide/1) to control the information presented.
*/

%!  server_health(+Request)
%
%   HTTP handler that replies with  the   overall  health of the server.
%   Returns a JSON object from all solutions of health/2.
%
%   Processes an optional parameter `fields` to  specify the fields that
%   should be returned.  The  fields  content   is  ","  or  white space
%   delimited.

server_health(Request) :-
    option(method(options), Request), !,
    cors_enable(Request,
                [ methods([get])
                ]),
    format('~n').
server_health(Request) :-
    http_parameters(Request,
                    [ fields(FieldSpec, [ optional(true) ])
                    ]),
    cors_enable,
    (   var(FieldSpec)
    ->  true
    ;   split_string(FieldSpec, ", \t\r\n", " \t\r\n", Strings),
        maplist(atom_string, Fields, Strings)
    ),
    get_server_health(Health, Fields),
    reply_json(Health).

get_server_health(Health, Fields) :-
    var(Fields),
    !,
    findall(Key-Value, health(Key, Value), Pairs),
    dict_pairs(Health, health, Pairs).
get_server_health(Health, Fields) :-
    findall(Key-Value, (member(Key,Fields),health(Key, Value)), Pairs),
    dict_pairs(Health, health, Pairs).

%!  health(-Key, -Value) is nondet.
%
%   Multifile extensible. True when  Key/Value  can   be  reported  as a
%   health statistics. Keys may  be  added   by  adding  clauses to this
%   multifile predicate. Keys may be   filtered using hide/1. Predefined
%   Key values are:
%
%     - up
%       Defined to be `true`.
%     - epoch
%       Starting time of the server in seconds after Jan 1, 1970 UTC.
%     - cpu_time
%       Total process CPU usage in seconds.
%     - threads
%       Number of active threads
%     - workers
%       Number of HTTP _worker_ threads.
%     - requests
%       Number of HTTP requests processed.
%     - bytes_sent
%       Number of bytes send in reply to HTTP requests.
%     - open_files
%       Number of open file streams.  This includes physical files as
%       well as sockets (except for Windows).  On Linux we count the
%       file handles in ``/proc/self/fd``.  Otherwise we use
%       stream_property/2 with the file_no(Fd) property.
%     - loadavg
%       An array holding the load average over the last [1,5,15]
%       minutes.  This key is only supported on Linux machines.  It
%       is based on ``/proc/loadavg``
%     - heap
%       When compiled with TCMalloc, this provides two properties:
%       - inuse: Bytes
%         Total amount of in-use memory in bytes
%       - size: Bytes
%         Same as `inuse`, but including the TCMalloc overhead and
%         (thus) memory that has been freed and is not (yet) reused.
%
%   @arg Key is the name of the JSON key.  Must be an atom
%   @arg Value is the Prolog representation for a JSON (dict) value.

:- multifile health/2.

term_expansion((health(Key,Value) :- Body),
               (health(Key,Value) :- \+ hide(Key), Body)).

health(up, true) :-
    true.
health(epoch, Epoch) :-
    http_server_property(_, start_time(Epoch)).
health(cpu_time, Time) :-
    statistics(process_cputime, Time).
health(threads, Count) :-
    statistics(threads, Count).
health(workers, Count) :-
    aggregate_all(sum(N), http_workers(_,N), Count).
health(requests, RequestCount) :-
    cgi_statistics(requests(RequestCount)).
health(bytes_sent, BytesSent) :-
    cgi_statistics(bytes_sent(BytesSent)).
:- if(exists_directory('/proc/self/fd')).
health(open_files, Streams) :-
    directory_files('/proc/self/fd', FDs),
    length(FDs, Files),
    Streams is Files - 2.               % Ignore . and ..
:- else.
health(open_files, Streams) :-
    findall(N, stream_property(_, file_no(N)), FDs),
    sort(FDs, Unique),
    length(Unique, Streams).
:- endif.
health(loadavg, LoadAVG) :-
    access_file('/proc/loadavg', exist),
    catch(setup_call_cleanup(
              open('/proc/loadavg', read, In),
              read_string(In, _, String),
              close(In)),
	      _, fail),
    split_string(String, " ", " ", [One,Five,Fifteen|_]),
    maplist(number_string, LoadAVG, [One,Five,Fifteen]).
:- if(current_predicate(malloc_property/1)).
health(heap, json{inuse:InUse, size:Size}) :-
    malloc_property('generic.current_allocated_bytes'(InUse)),
    malloc_property('generic.heap_size'(Size)).
:- endif.

%!  hide(?Key) is nondet.
%
%   Multifile hook. If true for  a   specific  Key, hide this statistics
%   from the output. This may be used to hide keys that are considered a
%   security risk.

:- multifile hide/1.
