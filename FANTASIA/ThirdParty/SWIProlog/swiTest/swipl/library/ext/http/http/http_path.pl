/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2008-2022, University of Amsterdam
                              VU University Amsterdam
                              SWI-Prolog Solutions b.v.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in
       the documentation and/or other materials provided with the
       distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

:- module(http_path,
          [ http_absolute_location/3,   % +Spec, -Path, +Options
            http_clean_location_cache/0
          ]).
:- use_module(library(debug),[debug/3]).
:- if(exists_source(library(http/http_host))).
:- autoload(library(http/http_host),[http_public_host/4]).
:- export(http_absolute_uri/2).         % +Spec, -URI
:- endif.
:- autoload(library(apply),[exclude/3]).
:- autoload(library(broadcast),[listen/2]).
:- autoload(library(error),
	    [must_be/2,existence_error/2,instantiation_error/1]).
:- autoload(library(lists),[reverse/2,append/3]).
:- autoload(library(option),[option/3]).
:- autoload(library(pairs),[pairs_values/2]).
:- autoload(library(uri),
	    [ uri_authority_data/3, uri_authority_components/2,
	      uri_data/3, uri_components/2, uri_normalized/3
	    ]).
:- use_module(library(settings),[setting/4,setting/2]).

:- predicate_options(http_absolute_location/3, 3, [relative_to(atom)]).

/** <module> Abstract specification of HTTP server locations

This module provides an abstract specification  of HTTP server locations
that is inspired on absolute_file_name/3. The   specification is done by
adding rules to the  dynamic   multifile  predicate http:location/3. The
speficiation is very similar to   user:file_search_path/2,  but takes an
additional argument with options. Currently only one option is defined:

    * priority(+Integer)
    If two rules match, take the one with highest priority.  Using
    priorities is needed because we want to be able to overrule
    paths, but we do not want to become dependent on clause ordering.

    The default priority is 0. Note however that notably libraries may
    decide to provide a fall-back using a negative priority.  We suggest
    -100 for such cases.

This library predefines a single location at priority -100:

    * root
    The root of the server.  Default is /, but this may be overruled
    using the setting (see setting/2) =|http:prefix|=

To serve additional resource files such as CSS, JavaScript and icons,
see `library(http/http_server_files)`.

Here is an example that binds =|/login|=  to login/1. The user can reuse
this application while moving all locations  using   a  new rule for the
admin location with the option =|[priority(10)]|=.

  ==
  :- multifile http:location/3.
  :- dynamic   http:location/3.

  http:location(admin, /, []).

  :- http_handler(admin(login), login, []).

  login(Request) :-
          ...
  ==
*/

:- setting(http:prefix, atom, '',
           'Prefix for all locations of this server').

%!  http:location(+Alias, -Expansion, -Options) is nondet.
%
%   Multifile hook used to specify new  HTTP locations. Alias is the
%   name  of  the  abstract  path.  Expansion    is  either  a  term
%   Alias2(Relative), telling http_absolute_location/3  to translate
%   Alias by first translating Alias2 and then applying the relative
%   path Relative or, Expansion is an   absolute location, i.e., one
%   that starts with a =|/|=. Options   currently  only supports the
%   priority  of  the  path.  If  http:location/3  returns  multiple
%   solutions the one with the  highest   priority  is selected. The
%   default priority is 0.
%
%   This library provides  a  default   for  the  abstract  location
%   =root=. This defaults to the setting   http:prefix  or, when not
%   available to the  path  =|/|=.  It   is  adviced  to  define all
%   locations (ultimately) relative to  =root=.   For  example,  use
%   root('home.html') rather than =|'/home.html'|=.

:- multifile
    http:location/3.                % Alias, Expansion, Options
:- dynamic
    http:location/3.                % Alias, Expansion, Options

http:location(root, Root, [priority(-100)]) :-
    (   setting(http:prefix, Prefix),
        Prefix \== ''
    ->  Root = Prefix
    ;   Root = (/)
    ).

:- if(current_predicate(http_public_host/4)).
%!  http_absolute_uri(+Spec, -URI) is det.
%
%   URI is the absolute (i.e., starting   with  =|http://|=) URI for
%   the abstract specification Spec. Use http_absolute_location/3 to
%   create references to locations on the same server.

http_absolute_uri(Spec, URI) :-
    http_public_host(_Request, Host, Port,
                     [ global(true)
                     ]),
    (   setting(http:public_scheme, Scheme)
    ->  true
    ;   default_port(Scheme, Port)
    ->  true
    ;   Scheme = http
    ),
    http_absolute_location(Spec, Path, []),
    uri_authority_data(host, AuthC, Host),
    (   default_port(Scheme, Port)
    ->  true
    ;   uri_authority_data(port, AuthC, Port)
    ),
    uri_authority_components(Authority, AuthC),
    uri_data(path, Components, Path),
    uri_data(scheme, Components, Scheme),
    uri_data(authority, Components, Authority),
    uri_components(URI, Components).

default_port(http,  80).
default_port(https, 443).

:- endif.


%!  http_absolute_location(+Spec, -Path, +Options) is det.
%
%   Path is the HTTP location for the abstract specification Spec.
%   Options:
%
%       * relative_to(Base)
%       Path is made relative to Base.  Default is to generate
%       absolute URLs.
%
%   @see     http_absolute_uri/2 to create a reference that can be
%            used on another server.

:- dynamic
    location_cache/3.

http_absolute_location(Spec, Path, Options) :-
    must_be(ground, Spec),
    option(relative_to(Base), Options, /),
    absolute_location(Spec, Base, Path, Options),
    debug(http_path, '~q (~q) --> ~q', [Spec, Base, Path]).

absolute_location(Spec, Base, Path, _Options) :-
    location_cache(Spec, Base, Cache),
    !,
    Path = Cache.
absolute_location(Spec, Base, Path, Options) :-
    expand_location(Spec, Base, L, Options),
    assert(location_cache(Spec, Base, L)),
    Path = L.

expand_location(Spec, Base, Path, _Options) :-
    atomic(Spec),
    !,
    (   uri_components(Spec, Components),
        uri_data(scheme, Components, Scheme),
        atom(Scheme)
    ->  Path = Spec
    ;   relative_to(Base, Spec, Path)
    ).
expand_location(Spec, _Base, Path, Options) :-
    Spec =.. [Alias, Sub],
    http_location_path(Alias, Parent),
    absolute_location(Parent, /, ParentLocation, Options),
    phrase(path_list(Sub), List),
    atomic_list_concat(List, /, SubAtom),
    (   ParentLocation == ''
    ->  Path = SubAtom
    ;   sub_atom(ParentLocation, _, _, 0, /)
    ->  atom_concat(ParentLocation, SubAtom, Path)
    ;   atomic_list_concat([ParentLocation, SubAtom], /, Path)
    ).


%!  http_location_path(+Alias, -Expansion) is det.
%
%   Expansion is the expanded HTTP location for Alias. As we have no
%   condition search, we demand a single  expansion for an alias. An
%   ambiguous alias results in a printed   warning.  A lacking alias
%   results in an exception.
%
%   @error  existence_error(http_alias, Alias)

http_location_path(Alias, Path) :-
    findall(P-L, http_location_path(Alias, L, P), Pairs),
    sort(Pairs, Sorted0),
    reverse(Sorted0, Result),
    (   Result = [_-One]
    ->  Path = One
    ;   Result == []
    ->  existence_error(http_alias, Alias)
    ;   Result = [P-Best,P2-_|_],
        P \== P2
    ->  Path = Best
    ;   Result = [_-First|_],
        pairs_values(Result, Paths),
        print_message(warning, http(ambiguous_location(Alias, Paths))),
        Path = First
    ).


%!  http_location_path(+Alias, -Path, -Priority) is nondet.
%
%   @tbd    prefix(Path) is discouraged; use root(Path)

http_location_path(Alias, Path, Priority) :-
    http:location(Alias, Path, Options),
    option(priority(Priority), Options, 0).
http_location_path(prefix, Path, 0) :-
    (   catch(setting(http:prefix, Prefix), _, fail),
        Prefix \== ''
    ->  (   sub_atom(Prefix, 0, _, _, /)
        ->  Path = Prefix
        ;   atom_concat(/, Prefix, Path)
        )
    ;   Path = /
    ).


%!  relative_to(+Base, +Path, -AbsPath) is det.
%
%   AbsPath is an absolute URL location created from Base and Path.
%   The result is cleaned

relative_to(/, Path, Path) :- !.
relative_to(_Base, Path, Path) :-
    sub_atom(Path, 0, _, _, /),
    !.
relative_to(Base, Local, Path) :-
    sub_atom(Base, 0, _, _, /),    % file version
    !,
    path_segments(Base, BaseSegments),
    append(BaseDir, [_], BaseSegments) ->
    path_segments(Local, LocalSegments),
    append(BaseDir, LocalSegments, Segments0),
    clean_segments(Segments0, Segments),
    path_segments(Path, Segments).
relative_to(Base, Local, Global) :-
    uri_normalized(Local, Base, Global).

path_segments(Path, Segments) :-
    atomic_list_concat(Segments, /, Path).

%!  clean_segments(+SegmentsIn, -SegmentsOut) is det.
%
%   Clean a path represented  as  a   segment  list,  removing empty
%   segments and resolving .. based on syntax.

clean_segments([''|T0], [''|T]) :-
    !,
    exclude(empty_segment, T0, T1),
    clean_parent_segments(T1, T).
clean_segments(T0, T) :-
    exclude(empty_segment, T0, T1),
    clean_parent_segments(T1, T).

clean_parent_segments([], []).
clean_parent_segments([..|T0], T) :-
    !,
    clean_parent_segments(T0, T).
clean_parent_segments([_,..|T0], T) :-
    !,
    clean_parent_segments(T0, T).
clean_parent_segments([H|T0], [H|T]) :-
    clean_parent_segments(T0, T).

empty_segment('').
empty_segment('.').


%!  path_list(+Spec, -List) is det.
%
%   Translate seg1/seg2/... into [seg1,seg2,...].
%
%   @error  instantiation_error
%   @error  type_error(atomic, X)

path_list(Var) -->
    { var(Var),
      !,
      instantiation_error(Var)
    }.
path_list(A/B) -->
    !,
    path_list(A),
    path_list(B).
path_list(.) -->
    !,
    [].
path_list(A) -->
    { must_be(atomic, A) },
    [A].


                 /*******************************
                 *            MESSAGES          *
                 *******************************/

:- multifile
    prolog:message/3.

prolog:message(http(ambiguous_location(Spec, Paths))) -->
    [ 'http_absolute_location/2: ambiguous specification: ~q: ~p'-
      [Spec, Paths]
    ].


                 /*******************************
                 *        CACHE CLEANUP         *
                 *******************************/

%!  http_clean_location_cache
%
%   HTTP locations resolved  through   http_absolute_location/3  are
%   cached.  This  predicate  wipes   the    cache.   The  cache  is
%   automatically wiped by make/0 and if  the setting http:prefix is
%   changed.

http_clean_location_cache :-
    retractall(location_cache(_,_,_)).

:- listen(settings(changed(http:prefix, _, _)),
          http_clean_location_cache).

:- multifile
    user:message_hook/3.
:- dynamic
    user:message_hook/3.

user:message_hook(make(done(Reload)), _Level, _Lines) :-
    Reload \== [],
    http_clean_location_cache,
    fail.
