/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        jan@swi-prolog.org
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2020-2024, SWI-Prolog Solutions b.v.
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

:- module(http_redis_plugin, []).
:- use_module(library(http/http_session)).
:- autoload(library(error), [must_be/2]).
:- autoload(library(lists), [member/2]).
:- autoload(library(redis), [redis/3, redis/2, redis_get_list/4, redis_zscan/4]).
:- autoload(library(broadcast), [broadcast/1]).
:- use_module(library(debug), [debug/3]).
:- autoload(library(socket), [ip_name/2]).

/** <module> Hook session management to use Redis

This module acts as  a   plugin  for library(http/http_session), storing
session information on a Redis server. This has several consequences:

  - The Prolog server may be restarted without loosing session data.
    This is notably useful when long session timeouts are used.
  - Multiple Prolog servers can act as a cluster while session
    management is used.
  - Associating Prolog data with sessions is relatively slow.  The
    assert/retract is replaced by managing a Redis list.  Data in
    this list is matched sequentially, where each term needs to be
    parsed before it can be matched.
  - Associated data is currently limited to __ground terms__.

The   library   is   activated   by   loading    it   in   addition   to
library(http/http_session)  and  using    http_set_session_options/1  to
configure the Redis database as below. The redis_server/2 predicate from
library(redis) can be used  to  specify   the  parameters  for the redis
server  such as host, port or authentication.

```
:- http_set_session_options(
       [ redis_db(default),
         redis_prefix('swipl:http:session')
       ]).
```

## Redis key usage

All  Redis  keys  reside  under  a    prefix  specified  by  the  option
redis_prefix(Prefix), which defaults to  `'swipl:http:session'`. Here we
find:

  - An ordered set at <prefix>:expire that contains the session ids,
    ordered by the time the session expires.  Session enumeration and
    garbage collection is based on this set.
  - A hash at <prefix>:session:<id> which contains the _peer_ address,
    the _last used_ time and optionally session specific settings.
  - If there is session _data_, a list at <prefix>:data:<id> of Prolog
    terms, represented as strings that contain the session data.
*/

:- multifile
    http_session:hooked/0,
    http_session:hook/1,
    http_session:session_setting/1,
    http_session:session_option/2.

http_session:session_option(redis_db, atom).
http_session:session_option(redis_ro, atom).
http_session:session_option(redis_prefix, atom).

http_session:hooked :-
    http_session:session_setting(redis_db(_)).

%http_session:hook(assert_session(SessionID, Peer)).
%http_session:hook(set_session_option(SessionId, Setting)).
%http_session:hook(get_session_option(SessionId, Setting)).
%http_session:hook(active_session(SessionID, Peer, LastUsed)).
%http_session:hook(set_last_used(SessionID, Now, TimeOut)).
%http_session:hook(asserta(session_data(SessionId, Data))).
%http_session:hook(assertz(session_data(SessionId, Data))).
%http_session:hook(retract(session_data(SessionId, Data))).
%http_session:hook(retractall(session_data(SessionId, Data))).
%http_session:hook(session_data(SessionId, Data)).
%http_session:hook(current_session(SessionID, Data)).
%http_session:hook(close_session(?SessionID)).
%http_session:hook(gc_sessions).

:- dynamic
    peer/2,                             % SessionID, Peer
    last_used/2.                        % SessionID, Time


http_session:hook(assert_session(SessionID, Peer)) :-
    session_db(rw, SessionID, DB, Key),
    http_session:session_setting(timeout(Timeout)),
    asserta(peer(SessionID, Peer)),
    ip_name(Peer, PeerS),
    get_time(Now),
    redis(DB, hset(Key,
                   peer, PeerS,
                   last_used, Now)),
    expire(SessionID, Timeout).
http_session:hook(set_session_option(SessionID, Setting)) :-
    session_db(rw, SessionID, DB, Key),
    Setting =.. [Name,Value],
    redis(DB, hset(Key, Name, Value as prolog)),
    (   Setting = timeout(Timeout)
    ->  expire(SessionID, Timeout)
    ;   true
    ).
http_session:hook(get_session_option(SessionID, Setting)) :-
    session_db(ro, SessionID, DB, Key),
    Setting =.. [Name,Value],
    redis(DB, hget(Key, Name), Value).
http_session:hook(active_session(SessionID, Peer, LastUsed)) :-
    (   last_used(SessionID, LastUsed0),
        peer(SessionID, Peer0)
    ->  LastUsed = LastUsed0,
        Peer = Peer0
    ;   session_db(ro, SessionID, DB, Key),
        redis(DB, hget(Key, peer), PeerS),
        ip_name(Peer, PeerS),
        redis(DB, hget(Key, last_used), LastUsed as number),
        update_session(SessionID, LastUsed, _, Peer)
    ).
http_session:hook(set_last_used(SessionID, Now, Timeout)) :-
    http_session:session_setting(granularity(TimeGranularity)),
    LastUsed is floor(Now/TimeGranularity)*TimeGranularity,
    update_session(SessionID, LastUsed, Updated, _Peer),
    (   Updated == true
    ->  session_db(rw, SessionID, DB, Key),
        redis(DB, hset(Key, last_used, Now)),
        expire(SessionID, Timeout)
    ;   true
    ).
http_session:hook(asserta(session_data(SessionID, Data))) :-
    must_be(ground, Data),
    session_data_db(rw, SessionID, DB, Key),
    redis(DB, lpush(Key, Data as prolog)).
http_session:hook(assertz(session_data(SessionID, Data))) :-
    must_be(ground, Data),
    session_data_db(rw, SessionID, DB, Key),
    redis(DB, rpush(Key, Data as prolog)).
http_session:hook(retract(session_data(SessionID, Data))) :-
    session_data_db(rw, SessionID, DB, Key),
    redis_get_list(DB, Key, 10, List),
    member(Data, List),
    redis(DB, lrem(Key, 1, Data as prolog)).
http_session:hook(retractall(session_data(SessionID, Data))) :-
    forall(http_session:hook(retract(session_data(SessionID, Data))),
           true).
http_session:hook(session_data(SessionID, Data)) :-
    session_data_db(rw, SessionID, DB, Key),
    redis_get_list(DB, Key, 10, List),
    member(Data, List).
http_session:hook(current_session(SessionID, Data)) :-
    session_db(ro, SessionID, DB, Key),
    redis(DB, hget(Key, last_used), Time as number),
    number(Time),
    get_time(Now),
    Idle is Now - Time,
    (   nonvar(Data)
    ->  (   Data = peer(Peer)
        ->  redis(DB, hget(Key, peer), PeerS),
            ip_name(Peer, PeerS)
        ;   Data = idle(Idle0)
        ->  Idle0 = Idle
        ;   http_session:hook(session_data(SessionID, Data))
        )
    ;   (   Data = peer(Peer),
            redis(DB, hget(Key, peer), PeerS),
            ip_name(Peer, PeerS)
        ;   Data = idle(Idle)
        ;   non_reserved_property(Data),
            http_session:hook(session_data(SessionID, Data))
        )
    ).
http_session:hook(close_session(SessionID)) :-
    gc_session(SessionID).
http_session:hook(gc_sessions) :-
    gc_sessions.

non_reserved_property(P) :-
    var(P),
    !.
non_reserved_property(peer(_)) :- !, fail.
non_reserved_property(idle(_)) :- !, fail.
non_reserved_property(_).


%!  update_session(+SessionID, ?LastUsed, -Updated, ?Peer) is det.
%
%   Update cached last_used and peer notions.

update_session(SessionID, LastUsed, Updated, Peer) :-
    transaction(update_session_(SessionID, LastUsed, Updated, Peer)).

update_session_(SessionID, LastUsed, Updated, Peer) :-
    update_last_used(SessionID, Updated, LastUsed),
    update_peer(SessionID, Peer).

update_last_used(SessionID, Updated, LastUsed), nonvar(LastUsed) =>
    (   last_used(SessionID, LastUsed)
    ->  true
    ;   retractall(last_used(SessionID, _)),
        asserta(last_used(SessionID, LastUsed)),
        Updated = true
    ).
update_last_used(_, _, _) =>
    true.

update_peer(SessionID, Peer), nonvar(Peer) =>
    (   peer(SessionID, Peer)
    ->  true
    ;   retractall(peer(SessionID, _)),
        asserta(peer(SessionID, Peer))
    ).
update_peer(_, _) =>
    true.


		 /*******************************
		 *      SCHEDULE TIMEOUT	*
		 *******************************/

expire(SessionID, Timeout) :-
    get_time(Now),
    Time is integer(Now+Timeout),
    session_expire_db(rw, DB, Key),
    redis(DB, zadd(Key, Time, SessionID)).

gc_sessions :-
    session_expire_db(ro, DB, Key),
    session_expire_db(rw, DB, TMOKey),
    get_time(Now),
    End is integer(Now),
    redis(DB, zrangebyscore(Key, "-inf", End), TimedOut as atom),
    (   member(SessionID, TimedOut),
        redis(DB, zrem(TMOKey, SessionID), 1), % 0 if someone else deleted this
        gc_session(SessionID),
        fail
    ;   true
    ).

%!  gc_session(+SessionID) is semidet.

gc_session(_) :-
    prolog_current_frame(Frame),
    prolog_frame_attribute(Frame, parent, PFrame),
    prolog_frame_attribute(PFrame, parent_goal, gc_session(_)),
    !.
gc_session(SessionID) :-
    debug(http_session(gc), 'GC session ~p', [SessionID]),
    session_db(ro, SessionID, DB, SessionKey),
    redis(DB, hget(SessionKey, peer), PeerS),
    ip_name(Peer, PeerS),
    broadcast(http_session(end(SessionID, Peer))),
    session_db(rw, SessionID, DBw, SessionKey),
    redis(DBw, del(SessionKey)),
    session_data_db(rw, SessionID, DBw, DataKey),
    redis(DBw, del(DataKey)),
    retractall(peer(SessionID, _)),
    retractall(last_used(SessionID, _)).


		 /*******************************
		 *             UTIL		*
		 *******************************/

%!  session_db(+RW, ?SessionID, -DB, -Key) is det.

session_db(RW, SessionID, DB, Key) :-
    nonvar(SessionID),
    !,
    redis_db(RW, DB),
    key_prefix(Prefix),
    atomics_to_string([Prefix,session,SessionID], :, Key).
session_db(RW, SessionID, DB, Key) :-
    session_expire_db(RW, DB, TMOKey),
    redis_zscan(DB, TMOKey, Pairs, []),
    member(SessionIDS-_Timeout, Pairs),
    atom_string(SessionID, SessionIDS),
    key_prefix(Prefix),
    atomics_to_string([Prefix,session,SessionID], :, Key).

session_expire_db(RW, DB, Key) :-
    redis_db(RW, DB),
    key_prefix(Prefix),
    atomics_to_string([Prefix,expire], :, Key).

session_data_db(RW, SessionID, DB, Key) :-
    redis_db(RW, DB),
    key_prefix(Prefix),
    atomics_to_string([Prefix,data,SessionID], :, Key).

key_prefix(Prefix) :-
    http_session:session_setting(redis_prefix(Prefix)),
    !.
key_prefix('swipl:http:sessions').

redis_db(ro, DB) :-
    http_session:session_setting(redis_ro(DB0)),
    !,
    DB = DB0.
redis_db(_, DB) :-
    http_session:session_setting(redis_db(DB)).
