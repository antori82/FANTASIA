/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2000-2023, University of Amsterdam
                              VU University Amsterdam
                              CWI, Amsterdam
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

:- module(socket,
          [ socket_create/2,		% -Socket, +Options
	    tcp_socket/1,               % -Socket
            tcp_close_socket/1,         % +Socket
            tcp_open_socket/3,          % +Socket, -Read, -Write
            tcp_connect/2,              % +Socket, +Address
            tcp_connect/3,              % +Address, -StreamPair, +Options
            tcp_connect/4,              % +Socket, +Address, -Read, -Write)
            tcp_bind/2,                 % +Socket, +Address
            tcp_accept/3,               % +Master, -Slave, -PeerName
            tcp_listen/2,               % +Socket, +BackLog
            tcp_fcntl/3,                % +Socket, +Command, ?Arg
            tcp_setopt/2,               % +Socket, +Option
            tcp_getopt/2,               % +Socket, ?Option
            host_address/3,		% ?HostName, ?Address, +Options
            tcp_host_to_address/2,      % ?HostName, ?Ip-nr
            tcp_select/3,               % +Inputs, -Ready, +Timeout
            gethostname/1,              % -HostName

            ip_name/2,			% ?Ip, ?Name

            tcp_open_socket/2,          % +Socket, -StreamPair

            udp_socket/1,               % -Socket
            udp_receive/4,              % +Socket, -Data, -Sender, +Options
            udp_send/4,                 % +Socket, +Data, +Sender, +Options

            negotiate_socks_connection/2% +DesiredEndpoint, +StreamPair
          ]).
:- use_module(library(debug), [assertion/1, debug/3]).
:- autoload(library(lists), [last/2, member/2, append/3, append/2]).
:- autoload(library(apply), [maplist/3, maplist/2]).
:- autoload(library(error),
            [instantiation_error/1, syntax_error/1, must_be/2, domain_error/2]).
:- autoload(library(option), [option/2, option/3]).

:- multifile
    rewrite_host/3.                     % +HostIn, -Host, +Socket

/** <module> Network socket (TCP and UDP) library

The library(socket) provides  TCP  and   UDP  inet-domain  sockets  from
SWI-Prolog, both client and server-side  communication. The interface of
this library is very close to the  Unix socket interface, also supported
by the MS-Windows _winsock_ API. SWI-Prolog   applications  that wish to
communicate with multiple sources have two options:

  - Use I/O multiplexing based on wait_for_input/3.  On Windows
    systems this can only be used for sockets, not for general
    (device-) file handles.
  - Use multiple threads, handling either a single blocking socket
    or a pool using I/O multiplexing as above.

## Client applications  {#socket-server}

Using this library to establish  a  TCP   connection  to  a server is as
simple as opening a file.  See also http_open/3.

==
dump_swi_homepage :-
    setup_call_cleanup(
        tcp_connect('www.swi-prolog.org':http, Stream, []),
        ( format(Stream,
                 'GET / HTTP/1.1~n\c
                  Host: www.swi-prolog.org~n\c
                  Connection: close~n~n', []),
          flush_output(Stream),
          copy_stream_data(Stream, current_output)
        ),
        close(Stream)).
==

To   deal   with   timeouts   and     multiple   connections,   threads,
wait_for_input/3 and/or non-blocking streams (see   tcp_fcntl/3)  can be
used.

## Server applications  {#socket-client}

The typical sequence for generating a server application is given below.
To close the server, use close/1 on the `StreamPair`.

  ==
  create_server(Port) :-
        tcp_socket(Socket),
        tcp_bind(Socket, Port),
        tcp_listen(Socket, 5),
        tcp_open_socket(Socket, StreamPair),
        stream_pair(StreamPair, AcceptFd, _),
        <dispatch>
  ==

There are various options for <dispatch>.  The most commonly used option
is to start a Prolog  thread   to  handle the connection. Alternatively,
input from multiple clients  can  be  handled   in  a  single  thread by
listening to these clients  using   wait_for_input/3.  Finally,  on Unix
systems, we can use fork/1 to handle   the  connection in a new process.
Note that fork/1 and threads do not  cooperate well. Combinations can be
realised  but  require  good   understanding    of   POSIX   thread  and
fork-semantics.

Below  is  the  typical  example  using  a   thread.  Note  the  use  of
setup_call_cleanup/3 to guarantee that all resources are reclaimed, also
in case of failure or exceptions.

  ==
  dispatch(AcceptFd) :-
          tcp_accept(AcceptFd, Socket, Peer),
          thread_create(process_client(Socket, Peer), _,
                        [ detached(true)
                        ]),
          dispatch(AcceptFd).

  process_client(Socket, Peer) :-
          setup_call_cleanup(
              tcp_open_socket(Socket, StreamPair),
              handle_service(StreamPair),
              close(StreamPair)).

  handle_service(StreamPair) :-
          ...
  ==

## Socket exceptions			{#socket-exceptions}

Errors that are trapped by  the  low-level   library  are  mapped  to an
exception of the shape below. In this term,  `Code` is a lower case atom
that corresponds to the C macro name,   e.g., `epipe` for a broken pipe.
`Message` is the human readable string for   the  error code returned by
the OS or  the  same  as  `Code`  if   the  OS  does  not  provide  this
functionality. Note that `Code` is derived from   a static set of macros
that may or may not be defines for the   target OS. If the macro name is
not known, `Code` is =|ERROR_nnn|=, where _nnn_ is an integer.

    error(socket_error(Code, Message), _)

Note that on Windows `Code` is a ``wsa*``   code  which makes it hard to
write portable code that handles specific   socket errors. Even on POSIX
systems the exact set of errors  produced   by  the network stack is not
defined.

## Socket addresses (families)		{#socket-domains}

The library supports both IP4 and IP6 addresses. On Unix systems it also
supports _Unix domain sockets_ (``AF_UNIX``).  The   address  of  a Unix
domain sockets is a file name.  Unix   domain  sockets are created using
socket_create/2 or unix_domain_socket/1.

IP4 or IP6 sockets can be created using socket_create/2 or tcp_connect/3
with the `inet` (default, IP3) or  `inet6`   domain  option. Some of the
predicates produce or consume IP addresses as  a Prolog term. The format
of this term is one of:

  - ip(A,B,C,D)
    Represents an IP4 address.  Each field is an integer in the range
    0..255 (8 bit).
  - ip(A,B,C,D,E,F,G,H)
    Represents an IP6 address.  Each field is an integer in the range
    0..65535 (16 bit).

The  predicate  ip_name/2  translates  between   the  canonical  textual
representation and the above defined address terms.

## Socket predicate reference           {#socket-predicates}
*/

:- multifile
    tcp_connect_hook/3,             % +Socket, +Addr, -In, -Out
    tcp_connect_hook/4,             % +Socket, +Addr, -Stream
    proxy_for_url/3,                % +URL, +Host, -ProxyList
    try_proxy/4.                    % +Proxy, +Addr, -Socket, -Stream

:- predicate_options(tcp_connect/3, 3,
                     [ bypass_proxy(boolean),
                       nodelay(boolean),
                       domain(oneof([inet,inet6]))
                     ]).

:- use_foreign_library(foreign(socket)).
:- public tcp_debug/1.                  % set debugging.

:- if(current_predicate(unix_domain_socket/1)).
:- export(unix_domain_socket/1).  % -Socket
:- endif.

%!  socket_create(-SocketId, +Options) is det.
%
%   Create a socket according to Options.   Supported Options are:
%
%     - domain(+Domain)
%       One of `inet` (default), `inet6`, `unix` or `local` (same
%       as `unix`)
%     - type(+Type)
%       One of `stream` (default) to create a TCP connection or
%       `dgram` to create a UDP socket.
%
%   This   predicate    subsumes   tcp_socket/1,    udp_socket/1   and
%   unix_domain_socket/1.

%!  tcp_socket(-SocketId) is det.
%
%   Equivalent   to   socket_create(SocketId,    [])   or,   explicit,
%   socket_create(SocketId, [domain(inet), type(stream)]).

%!  unix_domain_socket(-SocketId) is det.
%
%   Equivalent   to    socket_create(SocketId,   [domain(unix)])   or,
%   explicit, socket_create(SocketId, [domain(unix), type(stream)])
%
%   Unix  domain   socket  affect  tcp_connect/2  (for   clients)  and
%   tcp_bind/2 and tcp_accept/3 (for servers).  The address is an atom
%   or string  that is  handled as  a file name.  On most  systems the
%   length of this  file name is limited to 128  bytes (including null
%   terminator), but  according to the Linux  documentation (unix(7)),
%   portable applications must  keep the address below  92 bytes. Note
%   that  these lengths  are  in bytes.  Non-ascii  characters may  be
%   represented as multiple  bytes. If the length limit  is exceeded a
%   representation_error(af_unix_name) exception is raised.

%!  tcp_close_socket(+SocketId) is det.
%
%   Closes the indicated socket, making  SocketId invalid. Normally,
%   sockets are closed by closing both   stream  handles returned by
%   open_socket/3. There are two cases   where tcp_close_socket/1 is
%   used because there are no stream-handles:
%
%     - If, after tcp_accept/3, the server uses fork/1 to handle the
%       client in a sub-process. In this case the accepted socket is
%       not longer needed from the main server and must be discarded
%       using tcp_close_socket/1.
%     - If, after discovering the connecting client with
%       tcp_accept/3, the server does not want to accept the
%       connection, it should discard the accepted socket
%       immediately using tcp_close_socket/1.

%!  tcp_open_socket(+SocketId, -StreamPair) is det.
%
%   Create streams to communicate to  SocketId.   If  SocketId  is a
%   master socket (see tcp_bind/2), StreamPair   should  be used for
%   tcp_accept/3. If SocketId is a  connected (see tcp_connect/2) or
%   accepted socket (see tcp_accept/3), StreamPair   is unified to a
%   stream pair (see stream_pair/3) that can be used for reading and
%   writing. The stream or pair must   be closed with close/1, which
%   also closes SocketId.

tcp_open_socket(Socket, Stream) :-
    tcp_open_socket(Socket, In, Out),
    (   var(Out)
    ->  Stream = In
    ;   stream_pair(Stream, In, Out)
    ).

%!  tcp_open_socket(+SocketId, -InStream, -OutStream) is det.
%
%   Similar to tcp_open_socket/2, but creates   two separate sockets
%   where tcp_open_socket/2 would have created a stream pair.
%
%   @deprecated New code should use tcp_open_socket/2 because
%   closing a stream pair is much easier to perform safely.

%!  tcp_bind(SocketId, ?Address) is det.
%
%   Bind  the  socket  to  Address  on  the  current  machine.  This
%   operation, together with tcp_listen/2 and tcp_accept/3 implement
%   the _server-side_ of the socket interface.  Address is either an
%   plain `Port` or a term HostPort. The first form binds the socket
%   to the given port on all interfaces, while the second only binds
%   to the matching interface. A typical   example is below, causing
%   the socket to listen only on port   8080  on the local machine's
%   network.
%
%     ==
%       tcp_bind(Socket, localhost:8080)
%     ==
%
%   If `Port` is unbound, the system   picks  an arbitrary free port
%   and unifies `Port` with the  selected   port  number.  `Port` is
%   either an integer or the name of  a registered service. See also
%   tcp_connect/4.

%!  tcp_listen(+SocketId, +BackLog) is det.
%
%   Tells, after tcp_bind/2,  the  socket   to  listen  for incoming
%   requests for connections. Backlog  indicates   how  many pending
%   connection requests are allowed. Pending   requests are requests
%   that  are  not  yet  acknowledged  using  tcp_accept/3.  If  the
%   indicated number is exceeded,  the   requesting  client  will be
%   signalled  that  the  service  is  currently  not  available.  A
%   commonly used default value for Backlog is 5.

%!  tcp_accept(+Socket, -Slave, -Peer) is det.
%
%   This predicate waits on a server socket  for a connection request by
%   a client. On success, it creates  a   new  socket for the client and
%   binds the identifier to Slave. Peer is   bound  to the IP-address of
%   the client or the atom `af_unix` if Socket is an AF_UNIX socket (see
%   unix_domain_socket/1).

%!  tcp_connect(+SocketId, +Address) is det.
%
%   Connect SocketId. After successful completion, tcp_open_socket/3
%   can be used to create  I/O-Streams   to  the remote socket. This
%   predicate is part of the low level client API. A connection to a
%   particular host and port is realised using these steps:
%
%     ==
%         tcp_socket(Socket),
%         tcp_connect(Socket, Host:Port),
%         tcp_open_socket(Socket, StreamPair)
%     ==
%
%   Typical client applications should use  the high level interface
%   provided by tcp_connect/3 which  avoids   resource  leaking if a
%   step in the process fails, and can  be hooked to support proxies.
%   For example:
%
%     ==
%         setup_call_cleanup(
%             tcp_connect(Host:Port, StreamPair, []),
%             talk(StreamPair),
%             close(StreamPair))
%     ==
%
%   If SocketId is an AF_UNIX socket (see unix_domain_socket/1), Address
%   is an atom or string denoting a file name.

tcp_connect(Socket, Host0:Port) =>
    (   rewrite_host(Host0, Host, Socket)
    ->  true
    ;   Host = Host0
    ),
    tcp_connect_(Socket, Host:Port).
tcp_connect(Socket, Address) =>
    tcp_connect_(Socket, Address).

%!  rewrite_host(+HostIn, -HostOut, +Socket) is nondet.
%
%   Allow rewriting the host for tcp_connect/2   and therefore all other
%   predicates to connect a socket.
%
%   This hook is currently defined  in   Windows  to  map `localhost` to
%   ip(127,0,0,1) as resolving `localhost`  on   Windows  is  often very
%   slow. Note that we do not want to do that in general as a system may
%   prefer to map `localhost` to `::1`, i.e., the IPv6 loopback address.

:- if(current_prolog_flag(windows, true)).
rewrite_host(localhost, ip(127,0,0,1), _).
:- endif.


                 /*******************************
                 *      HOOKABLE CONNECT        *
                 *******************************/

%!  tcp_connect(+Socket, +Address, -Read, -Write) is det.
%
%   Connect a (client) socket to Address and return a bi-directional
%   connection through the  stream-handles  Read   and  Write.  This
%   predicate may be hooked   by  defining socket:tcp_connect_hook/4
%   with the same signature. Hooking can be  used to deal with proxy
%   connections. E.g.,
%
%       ==
%       :- multifile socket:tcp_connect_hook/4.
%
%       socket:tcp_connect_hook(Socket, Address, Read, Write) :-
%           proxy(ProxyAdress),
%           tcp_connect(Socket, ProxyAdress),
%           tcp_open_socket(Socket, Read, Write),
%           proxy_connect(Address, Read, Write).
%       ==
%
%   @deprecated New code should use tcp_connect/3 called as
%   tcp_connect(+Address, -StreamPair, +Options).

tcp_connect(Socket, Address, Read, Write) :-
    tcp_connect_hook(Socket, Address, Read, Write),
    !.
tcp_connect(Socket, Address, Read, Write) :-
    tcp_connect(Socket, Address),
    tcp_open_socket(Socket, Read, Write).



%!  tcp_connect(+Address, -StreamPair, +Options) is det.
%!  tcp_connect(+Socket, +Address, -StreamPair) is det.
%
%   Establish a TCP communication as a  client.   The  +,-,+ mode is the
%   preferred way for a client to establish a connection. This predicate
%   can be hooked to support network proxies.   To use a proxy, the hook
%   proxy_for_url/3 must be defined. Permitted options are:
%
%      * bypass_proxy(+Boolean)
%        Defaults to =false=. If =true=, do not attempt to use any
%        proxies to obtain the connection
%
%      * nodelay(+Boolean)
%        Defaults to =false=. If =true=, set nodelay on the
%        resulting socket using tcp_setopt(Socket, nodelay)
%
%      * domain(+Domain)
%        One of `inet' or `inet6`.  When omitted we use host_address/2
%        with type(stream) and try the returned addresses in order.
%
%   The +,+,- mode is  deprecated  and   does  not  support  proxies. It
%   behaves  like  tcp_connect/4,  but  creates    a  stream  pair  (see
%   stream_pair/3).
%
%   @arg Address is either a Host:Port  term   or  a  file name (atom or
%   string). The latter connects  to  an   AF_UNIX  socket  and requires
%   unix_domain_socket/1.
%
%   @error proxy_error(tried(ResultList)) is raised by   mode (+,-,+) if
%   proxies are defines by proxy_for_url/3 but no proxy can establsh the
%   connection. `ResultList` contains one or  more   terms  of  the form
%   false(Proxy)  for  a  hook  that    simply  failed  or  error(Proxy,
%   ErrorTerm) for a hook that raised an exception.
%
%   @see library(http/http_proxy) defines a hook  that allows to connect
%   through HTTP proxies that support the =CONNECT= method.

% Main mode: +,-,+
tcp_connect(Address, StreamPair, Options) :-
    var(StreamPair),
    !,
    (   memberchk(bypass_proxy(true), Options)
    ->  tcp_connect_direct(Address, Socket, StreamPair, Options)
    ;   findall(Result,
                try_a_proxy(Address, Result),
                ResultList),
        last(ResultList, Status)
    ->  (   Status = true(_Proxy, Socket, StreamPair)
        ->  true
        ;   throw(error(proxy_error(tried(ResultList)), _))
        )
    ;   tcp_connect_direct(Address, Socket, StreamPair, Options)
    ),
    (   memberchk(nodelay(true), Options)
    ->  tcp_setopt(Socket, nodelay)
    ;   true
    ).
% backward compatibility mode +,+,-
tcp_connect(Socket, Address, StreamPair) :-
    tcp_connect_hook(Socket, Address, StreamPair0),
    !,
    StreamPair = StreamPair0.
tcp_connect(Socket, Address, StreamPair) :-
    connect_stream_pair(Socket, Address, StreamPair).

:- public tcp_connect_direct/3.   % used by HTTP proxy code.
tcp_connect_direct(Address, Socket, StreamPair) :-
    tcp_connect_direct(Address, Socket, StreamPair, []).

%!  tcp_connect_direct(+Address, +Socket, -StreamPair, +Options) is det.
%
%   Make a direct connection to a TCP address, i.e., do not take proxy
%   rules into  account.  If  no explicit  domain (`inet`,  `inet6` is
%   given,  perform  a  getaddrinfo()  call  to  obtain  the  relevant
%   addresses.

tcp_connect_direct(Host0:Port, Socket, StreamPair, Options) :-
    must_be(ground, Host0),
    \+ option(domain(_), Options),
    !,
    (   rewrite_host(Host0, Host, Socket)
    ->  true
    ;   Host = Host0
    ),
    State = error(_),
    (   (   is_ip(Host, Domain)
        ->  IP = Host
        ;   host_address(Host, Address, [type(stream)]),
            Domain = Address.domain,
            IP = Address.address
        ),
	socket_create(Socket, [domain(Domain)]),
	E = error(_,_),
	catch(connect_or_discard_socket(Socket, IP:Port, StreamPair),
	      E, store_error_and_fail(State, E)),
	debug(socket, '~p: connected to ~p', [Host, IP])
    ->  true
    ;   arg(1, State, Error),
	assertion(nonvar(Error)),
	throw(Error)
    ).
tcp_connect_direct(Address, Socket, StreamPair, Options) :-
    make_socket(Address, Socket, Options),
    connect_or_discard_socket(Socket, Address, StreamPair).

is_ip(ip(_,_,_,_), inet).
is_ip(ip(_,_,_,_, _,_,_,_), inet6).

connect_or_discard_socket(Socket, Address, StreamPair) :-
    setup_call_catcher_cleanup(
	true,
	connect_stream_pair(Socket, Address, StreamPair),
	Catcher, cleanup(Catcher, Socket)).

cleanup(exit, _) :- !.
cleanup(_, Socket) :-
    tcp_close_socket(Socket).

connect_stream_pair(Socket, Address, StreamPair) :-
    tcp_connect(Socket, Address, Read, Write),
    stream_pair(StreamPair, Read, Write).

store_error_and_fail(State, E) :-
    arg(1, State, E0),
    var(E0),
    nb_setarg(1, State, E),
    fail.

:- if(current_predicate(unix_domain_socket/1)).
make_socket(Address, Socket, _Options) :-
    (   atom(Address)
    ;   string(Address)
    ),
    !,
    unix_domain_socket(Socket).
:- endif.
make_socket(_Address, Socket, Options) :-
    option(domain(Domain), Options, inet),
    socket_create(Socket, [domain(Domain)]).


%!  tcp_select(+ListOfStreams, -ReadyList, +TimeOut)
%
%   Same as the built-in wait_for_input/3. Used  to allow for interrupts
%   and timeouts on Windows. A redesign  of the Windows socket interface
%   makes  it  impossible  to  do  better  than  Windows  select()  call
%   underlying wait_for_input/3. As input multiplexing typically happens
%   in a background thread anyway we  accept   the  loss of timeouts and
%   interrupts.
%
%   @deprecated Use wait_for_input/3

tcp_select(ListOfStreams, ReadyList, TimeOut) :-
    wait_for_input(ListOfStreams, ReadyList, TimeOut).


                 /*******************************
                 *        PROXY SUPPORT         *
                 *******************************/

try_a_proxy(Address, Result) :-
    format(atom(URL), 'socket://~w', [Address]),
    (   Address = Host:_
    ->  true
    ;   Host = Address
    ),
    proxy_for_url(URL, Host, Proxy),
    debug(socket(proxy), 'Socket connecting via ~w~n', [Proxy]),
    (   catch(try_proxy(Proxy, Address, Socket, Stream), E, true)
    ->  (   var(E)
        ->  !, Result = true(Proxy, Socket, Stream)
        ;   Result = error(Proxy, E)
        )
    ;   Result = false(Proxy)
    ),
    debug(socket(proxy), 'Socket: ~w: ~p', [Proxy, Result]).

%!  try_proxy(+Proxy, +TargetAddress, -Socket, -StreamPair) is semidet.
%
%   Attempt  a  socket-level  connection  via  the  given  proxy  to
%   TargetAddress. The Proxy argument must match the output argument
%   of proxy_for_url/3. The predicate tcp_connect/3 (and http_open/3
%   from the library(http/http_open)) collect the  results of failed
%   proxies and raise an exception no  proxy is capable of realizing
%   the connection.
%
%   The default implementation  recognises  the   values  for  Proxy
%   described    below.    The      library(http/http_proxy)    adds
%   proxy(Host,Port)  which  allows  for  HTTP   proxies  using  the
%   =CONNECT= method.
%
%     - direct
%     Do not use any proxy
%     - socks(Host, Port)
%     Use a SOCKS5 proxy

:- multifile
    try_proxy/4.

try_proxy(direct, Address, Socket, StreamPair) :-
    !,
    tcp_connect_direct(Address, Socket, StreamPair).
try_proxy(socks(Host, Port), Address, Socket, StreamPair) :-
    !,
    tcp_connect_direct(Host:Port, Socket, StreamPair),
    catch(negotiate_socks_connection(Address, StreamPair),
          Error,
          ( close(StreamPair, [force(true)]),
            throw(Error)
          )).

%!  proxy_for_url(+URL, +Hostname, -Proxy) is nondet.
%
%   This hook can be implemented  to  return   a  proxy  to try when
%   connecting to URL. Returned proxies are   tried  in the order in
%   which they are  returned  by   the  multifile  hook try_proxy/4.
%   Pre-defined proxy methods are:
%
%      * direct
%        connect directly to the resource
%      * proxy(Host, Port)
%        Connect to the resource using an HTTP proxy. If the
%        resource is not an HTTP URL, then try to connect using the
%        CONNECT verb, otherwise, use the GET verb.
%      * socks(Host, Port)
%        Connect to the resource via a SOCKS5 proxy
%
%   These correspond to the proxy  methods   defined  by  PAC [Proxy
%   auto-config](http://en.wikipedia.org/wiki/Proxy_auto-config).
%   Additional methods can  be  returned   if  suitable  clauses for
%   http:http_connection_over_proxy/6 or try_proxy/4 are defined.

:- multifile
    proxy_for_url/3.

%!  udp_socket(-SocketId) is det.
%
%   Equivalent to socket_create(SocketId, [type(dgram)]) or, explicit,
%   socket_create(SocketId, [domain(inet), type(dgram)]).

%!  udp_receive(+Socket, -Data, -From, +Options) is det.
%
%   Wait for and  return the next datagram. The Data  is returned as a
%   Prolog term  depending on Options.  From  is a term of  the format
%   Ip:Port indicating the sender of the message. Here, `Ip` is either
%   an  ip4  or  ip6  structure.   Socket  can  be  waited  for  using
%   wait_for_input/3. Defined Options:
%
%     - as(+Type)
%     Defines the type for Data.  Possible values are `atom`, `codes`,
%     `string` (default) or `term` (parse as Prolog term).
%     - encoding(+Encoding)
%     Specify the encoding used to interpret the message. It is one of
%     `octet`. `iso_latin_1`, `text` or `utf8`.
%     - max_message_size(+Size)
%     Specify  the  maximum  number  of  bytes  to  read  from  a  UDP
%     datagram. Size must be within the range 0-65535. If unspecified,
%     a maximum of 4096 bytes will be read.
%
%   For example:
%
%   ```
%   receive(Port) :-
%       udp_socket(Socket),
%       tcp_bind(Socket, Port),
%       repeat,
%           udp_receive(Socket, Data, From, [as(atom)]),
%           format('Got ~q from ~q~n', [Data, From]),
%           fail.
%   ```


%!  udp_send(+Socket, +Data, +To, +Options) is det.
%
%   Send a UDP message. Data is  a string, atom or code-list providing
%   the data.  To is an  address of the  form Host:Port where  Host is
%   either the hostname or an IP address. Defined Options are:
%
%     - encoding(+Encoding)
%       Specifies   the  encoding   to   use  for   the  string.   See
%       udp_receive/4 for details
%     - as(+Type)
%       This uses the  same values for Type as the  as(Type) option of
%       udp_receive/4. The are interpreted differently though. No Type
%       corresponds   to  CVT_ALL   of  PL_get_chars().    Using  atom
%       corresponds to CVT_ATOM  and any of string or  codes is mapped
%       to  CVT_STRING|CVT_LIST,  allowing  for  a  SWI-Prolog  string
%       object,  list  of  character  codes  or  list  of  characters.
%       Finally, `term` maps to CVT_WRITE_CANONICAL. This implies that
%       arbitrary Prolog terms  can be sent reliably  using the option
%       list `[as(term),encoding(utf8)])`, using  the same option list
%       for udp_receive/4.
%
%   For example
%
%   ```
%   send(Host, Port, Message) :-
%       udp_socket(S),
%       udp_send(S, Message, Host:Port, []),
%       tcp_close_socket(S).
%   ```
%
%   A  broadcast is  achieved by  using tcp_setopt(Socket,  broadcast)
%   prior  to  sending  the  datagram  and  using  the  local  network
%   broadcast address as a ip/4 term.


                 /*******************************
                 *            OPTIONS           *
                 *******************************/

%!  tcp_setopt(+SocketId, +Option) is det.
%
%   Set options on the socket.  Defined options are:
%
%     - reuseaddr
%     Allow servers to reuse a port without the system being
%     completely sure the port is no longer in use.
%
%     - bindtodevice(+Device)
%     Bind the socket to Device (an atom). For example, the code
%     below binds the socket to the _loopback_ device that is
%     typically used to realise the _localhost_. See the manual
%     pages for setsockopt() and the socket interface (e.g.,
%     socket(7) on Linux) for details.
%
%       ==
%       tcp_socket(Socket),
%       tcp_setopt(Socket, bindtodevice(lo))
%       ==
%
%     - nodelay
%     - nodelay(true)
%     If =true=, disable the Nagle optimization on this socket,
%     which is enabled by default on almost all modern TCP/IP
%     stacks. The Nagle optimization joins small packages, which is
%     generally desirable, but sometimes not. Please note that the
%     underlying TCP_NODELAY setting to setsockopt() is not
%     available on all platforms and systems may require additional
%     privileges to change this option. If the option is not
%     supported, tcp_setopt/2 raises a domain_error exception. See
%     [Wikipedia](http://en.wikipedia.org/wiki/Nagle's_algorithm)
%     for details.
%
%     - broadcast
%     UDP sockets only: broadcast the package to all addresses
%     matching the address. The address is normally the address of
%     the local subnet (i.e. 192.168.1.255).  See udp_send/4.
%
%     - ip_add_membership(+MultiCastGroup)
%     - ip_add_membership(+MultiCastGroup, +LocalInterface)
%     - ip_add_membership(+MultiCastGroup, +LocalInterface, +InterfaceIndex)
%     - ip_drop_membership(+MultiCastGroup)
%     - ip_drop_membership(+MultiCastGroup, +LocalInterface)
%     - ip_drop_membership(+MultiCastGroup, +LocalInterface, +InterfaceIndex)
%     Join/leave a multicast group.  Calls setsockopt() with the
%     corresponding arguments.
%
%     - dispatch(+Boolean)
%     In GUI environments (using XPCE or the Windows =swipl-win.exe=
%     executable) this flags defines whether or not any events are
%     dispatched on behalf of the user interface. Default is
%     =true=. Only very specific situations require setting
%     this to =false=.
%
%     - sndbuf(+Integer)
%     Sets the send buffer size to Integer (bytes). On Windows this defaults
%     (now) to 64kb. Higher latency links may benefit from increasing this
%     further since the maximum theoretical throughput on a link is given by
%     buffer-size / latency.
%     See https://support.microsoft.com/en-gb/help/823764/slow-performance-occurs-when-you-copy-data-to-a-tcp-server-by-using-a
%     for Microsoft's discussion

%!  tcp_fcntl(+Stream, +Action, ?Argument) is det.
%
%   Interface to the fcntl() call. Currently   only suitable to deal
%   switch stream to non-blocking mode using:
%
%     ==
%       tcp_fcntl(Stream, setfl, nonblock),
%     ==
%
%   An attempt to read from a non-blocking  stream while there is no
%   data available returns -1  (or   =end_of_file=  for read/1), but
%   at_end_of_stream/1    fails.    On      actual     end-of-input,
%   at_end_of_stream/1 succeeds.

tcp_fcntl(Socket, setfl, nonblock) :-
    !,
    tcp_setopt(Socket, nonblock).

%!  tcp_getopt(+Socket, ?Option) is semidet.
%
%   Get  information  about  Socket.  Defined    properties  are  below.
%   Requesting an unknown option results in a `domain_error` exception.
%
%     - file_no(-File)
%     Get the OS file handle as an integer.  This may be used for
%     debugging and integration.

%!  host_address(+HostName, -Address, +Options) is nondet.
%!  host_address(-HostName, +Address, +Options) is det.
%
%   Translate  between a  machines  host-name  and it's  (IP-)address.
%   Supported options:
%
%     - domain(+Domain)
%       One of `inet` or `inet6` to limit the results to the given
%       family.
%     - type(+Type)
%       One of `stream` or `dgram`.
%     - canonname(+Boolean)
%       If `true` (default `false`), return the canonical host name
%       in the frist answer
%
%   In mode (+,-,+) Address is unified to a dict with the following keys:
%
%     - address
%       A Prolog terms describing the ip address.
%     - domain
%       One of `inet` or `inet6`.  The underlying getaddrinfo() calls
%       this `family`.  We use `domain` for consistency with
%       socket_create/2.
%     - type
%       Currently one of `stream` or `dgram`.
%     - host
%       Available if canonname(true) is specified on the first
%       returned address.  Holds the official canonical host name.

host_address(HostName, Address, Options), ground(HostName) =>
    '$host_address'(HostName, Addresses, Options),
    member(Address, Addresses).
host_address(HostName, Address, Options), is_dict(Address) =>
    '$host_address'(HostName, Address.address, Options).
host_address(HostName, Address, Options), ground(Address) =>
    '$host_address'(HostName, Address, Options).

%!  tcp_host_to_address(?HostName, ?Address) is det.
%
%   Translate between a machines  host-name   and  it's (IP-)address. If
%   HostName is an atom, it  is   resolved  using  getaddrinfo() and the
%   IP-number  is  unified  to  Address  using  a  term  of  the  format
%   ip(Byte1,Byte2,Byte3,Byte4). Otherwise, if Address is   bound  to an
%   ip(Byte1,Byte2,Byte3,Byte4) term, it is  resolved by gethostbyaddr()
%   and the canonical hostname is unified with HostName.
%
%   @deprecated New code should  use   host_address/3.  This  version is
%   bootstrapped from host_address/3 and only searches for IP4 addresses
%   that support TCP connections.

tcp_host_to_address(Host, Address), ground(Address) =>
    host_address(Host, Address, []).
tcp_host_to_address(Host, Address), ground(Host) =>
    host_address(Host, [Dict|_], [domain(inet), type(stream)]),
    Address = Dict.address.


%!  gethostname(-Hostname) is det.
%
%   Return the canonical fully qualified name  of this host. This is
%   achieved by calling gethostname() and  return the canonical name
%   returned by getaddrinfo().


%!  ip_name(?IP, ?Name) is det.
%
%   Translate between the textual representation  of an IP address and
%   the  Prolog data  structure.  Prolog  represents ip4  addresses as
%   ip(A,B,C,D) and ip6 addresses as ip(A,B,C,D,E,F,H).  For example:
%
%       ?- ip_name(ip(1,2,3,4), Name)
%       Name = '1.2.3.4'.
%       ?- ip_name(IP, '::').
%       IP = ip(0,0,0,0,0,0,0,0).
%       ?- ip_name(IP, '1:2::3').
%       IP = ip(1,2,0,0,0,0,0,3).

ip_name(Ip, Atom), ground(Atom) =>
    name_to_ip(Atom, Ip).
ip_name(Ip, Atom), ground(Ip) =>
    ip_to_name(Ip, Atom).
ip_name(Ip, _) =>
    instantiation_error(Ip).

name_to_ip(Atom, Ip4) :-
    split_string(Atom, '.', '', Parts),
    length(Parts, 4),
    maplist(string_byte, Parts, Bytes),
    !,
    Ip4 =.. [ip|Bytes].
name_to_ip(Atom, Ip6) :-
    split_string(Atom, ':', '', Parts0),
    clean_ends(Parts0, Parts1),
    length(Parts1, Len),
    (   Len < 8
    ->  append(Pre, [""|Post], Parts1),
	Zeros is 8-(Len-1),
	length(ZList, Zeros),
	maplist(=("0"), ZList),
	append([Pre, ZList, Post], Parts)
    ;   Len == 8
    ->  Parts = Parts1
    ),
    !,
    maplist(string_short, Parts, Shorts),
    Ip6 =.. [ip|Shorts].
name_to_ip(Atom, _) :-
    syntax_error(ip_address(Atom)).

clean_ends([""|T0], T) :-
    !,
    (   append(T1, [""], T0)
    ->  T = T1
    ;   T = T0
    ).
clean_ends(T0, T) :-
    append(T1, [""], T0),
    !,
    T = T1.
clean_ends(T, T).

string_byte(String, Byte) :-
    number_string(Byte, String),
    must_be(between(0, 255), Byte).

string_short(String, Short) :-
    string_concat('0x', String, String1),
    number_string(Short, String1),
    must_be(between(0, 65535), Short).

ip_to_name(ip(A,B,C,D), Atom) :-
    !,
    atomic_list_concat([A,B,C,D], '.', Atom).
ip_to_name(IP, Atom) :-
    compound(IP),
    compound_name_arity(IP, ip, 8),
    !,
    IP =.. [ip|Parts],
    (   zero_seq(Parts, Pre, Post, Len),
        Len > 1,
        \+ ( zero_seq(Post, _, _, Len2),
	     Len2 > Len
	   )
    ->  append([Pre, [''], Post], Parts1),
	(   Pre == []
	->  Parts2 = [''|Parts1]
	;   Parts2 = Parts1
	),
	(   Post == []
	->  append(Parts2, [''], Parts3)
	;   Parts3 = Parts2
	)
    ;   Parts3 = Parts
    ),
    maplist(to_hex, Parts3, Parts4),
    atomic_list_concat(Parts4, ':', Atom).
ip_to_name(IP, _) :-
    domain_error(ip_address, IP).

zero_seq(List, Pre, Post, Count) :-
    append(Pre, [0|Post0], List),
    leading_zeros(Post0, Post, 1, Count).

leading_zeros([0|T0], T, C0, C) =>
    C1 is C0+1,
    leading_zeros(T0, T, C1, C).
leading_zeros(L0, L, C0, C) =>
    L = L0,
    C = C0.

to_hex('', '') :-
    !.
to_hex(Num, Hex) :-
    format(string(Hex), '~16r', [Num]).



                 /*******************************
                 *            SOCKS             *
                 *******************************/

%!  negotiate_socks_connection(+DesiredEndpoint, +StreamPair) is det.
%
%   Negotiate  a  connection  to  DesiredEndpoint  over  StreamPair.
%   DesiredEndpoint should be in the form of either:
%
%      * hostname : port
%      * ip(A,B,C,D) : port
%
%   @error socks_error(Details) if the SOCKS negotiation failed.

negotiate_socks_connection(Host:Port, StreamPair):-
    format(StreamPair, '~s', [[0x5,    % Version 5
                               0x1,    % 1 auth method supported
                               0x0]]), % which is 'no auth'
    flush_output(StreamPair),
    get_byte(StreamPair, ServerVersion),
    get_byte(StreamPair, AuthenticationMethod),
    (   ServerVersion =\= 0x05
    ->  throw(error(socks_error(invalid_version(5, ServerVersion)), _))
    ;   AuthenticationMethod =:= 0xff
    ->  throw(error(socks_error(invalid_authentication_method(
                                    0xff,
                                    AuthenticationMethod)), _))
    ;   true
    ),
    (   Host = ip(A,B,C,D)
    ->  AddressType = 0x1,                  % IPv4 Address
        format(atom(Address), '~s', [[A, B, C, D]])
    ;   AddressType = 0x3,                  % Domain
        atom_length(Host, Length),
        format(atom(Address), '~s~w', [[Length], Host])
    ),
    P1 is Port /\ 0xff,
    P2 is Port >> 8,
    format(StreamPair, '~s~w~s', [[0x5,   % Version 5
                                   0x1,   % Please establish a connection
                                   0x0,   % reserved
                                   AddressType],
                                  Address,
                                  [P2, P1]]),
    flush_output(StreamPair),
    get_byte(StreamPair, _EchoedServerVersion),
    get_byte(StreamPair, Status),
    (   Status =:= 0                        % Established!
    ->  get_byte(StreamPair, _Reserved),
        get_byte(StreamPair, EchoedAddressType),
        (   EchoedAddressType =:= 0x1
        ->  get_byte(StreamPair, _),        % read IP4
            get_byte(StreamPair, _),
            get_byte(StreamPair, _),
            get_byte(StreamPair, _)
        ;   get_byte(StreamPair, Length),   % read host name
            forall(between(1, Length, _),
                   get_byte(StreamPair, _))
        ),
        get_byte(StreamPair, _),            % read port
        get_byte(StreamPair, _)
    ;   throw(error(socks_error(negotiation_rejected(Status)), _))
    ).


                 /*******************************
                 *             MESSAGES         *
                 *******************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
The C-layer generates exceptions of the  following format, where Message
is extracted from the operating system.

        error(socket_error(Code, Message), _)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- multifile
    prolog:error_message//1.

prolog:error_message(socket_error(_Code, Message)) -->
    [ 'Socket error: ~w'-[Message] ].
prolog:error_message(socks_error(Error)) -->
    socks_error(Error).
prolog:error_message(proxy_error(tried(Tried))) -->
    [ 'Failed to connect using a proxy.  Tried:'-[], nl],
    proxy_tried(Tried).

socks_error(invalid_version(Supported, Got)) -->
    [ 'SOCKS: unsupported version: ~p (supported: ~p)'-
      [ Got, Supported ] ].
socks_error(invalid_authentication_method(Supported, Got)) -->
    [ 'SOCKS: unsupported authentication method: ~p (supported: ~p)'-
      [ Got, Supported ] ].
socks_error(negotiation_rejected(Status)) -->
    [ 'SOCKS: connection failed: ~p'-[Status] ].

proxy_tried([]) --> [].
proxy_tried([H|T]) -->
    proxy_tried(H),
    proxy_tried(T).
proxy_tried(error(Proxy, Error)) -->
    [ '~w: '-[Proxy] ],
    '$messages':translate_message(Error).
proxy_tried(false(Proxy)) -->
    [ '~w: failed with unspecified error'-[Proxy] ].
