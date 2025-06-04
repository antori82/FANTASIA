/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org/packages/xpce/
    Copyright (c)  1985-2011, University of Amsterdam
                              VU University Amsterdam
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

:- module(pce_require,
          [ pce_require/1               % file
          , pce_require/3               % file x directive x message
          ]).
:- use_module(library(pce)).
:- require([ absolute_file_name/3
           , append/3
           , forall/2
           , ignore/1
           , is_list/1
           , member/2
           , pce_error/1
           , sformat/3
           ]).

/** <module> XPCE sanity check and cross-referencer

This module is part of infrastructure to port XPCE between SWI, SICStus
and Quintus.

@tbd    This should be (re-)based on library(prolog_xref).
*/

target_prolog(common).                  % Common between QP 3.2 and SICStus 3

:- dynamic
    called/1,                       % called head
    defined/1,                      % defined head
    output_to/2,                    % output is emacs buffer
    current_require_declaration/1.  % Current declaration

                 /*******************************
                 *           BUILT-INS          *
                 *******************************/

:- use_module(library('xref/common')).  % Common built-in's

system_predicate(require(_)).
system_predicate(discontiguous(_)).
system_predicate(Head) :-
    built_in(Head).


                /********************************
                *            TOPLEVEL           *
                ********************************/

%!  pce_require(+File) is det.
%
%   Compute the require/1 directive for  File   and  print it to the
%   current output.

pce_require(File) :-
    clean,
    collect(File),
    report.

%!  pce_require(+File, -Directive, -Message) is det.
%
%   Compute the :- require/1 directive by cross-referencing File.

pce_require(File, Directive, Message) :-
    new(D, string),
    new(M, string),
    asserta(output_to(D, M), Clause),
    pce_require(File),
    erase(Clause),
    get(D, value, Directive),
    get(M, value, Message).


clean :-
    retractall(called(_)),
    retractall(defined(_)),
    retractall(current_require_declaration(_)).


collect(File) :-
    find_source_file(File, Source),
    seeing(Old), see(Source),
    repeat,
        catch(read(Term), E,
              (   print_message(error, E),
                  fail
              )),
        req_expand(Term, T),
        (   T == end_of_file
        ->  !, seen, see(Old)
        ;   process(T),
            fail
        ).


                 /*******************************
                 *           EXPANSION          *
                 *******************************/

%!  req_expand(+Term, -Expanded)
%
%   Do the term-expansion.  We have to pass require as we need it
%   for validation.  Otherwise we do term-expansion, handling all
%   of the XPCE class compiler as normal Prolog afterwards.

req_expand((:- require(X)), (:- require(X))) :- !.
req_expand(Term, _) :-
    requires_library(Term, Lib),
    ensure_loaded(user:Lib),
    fail.
req_expand(Term, T) :-
    expand_term(Term, Expanded),
    (   is_list(Expanded)
    ->  member(T, Expanded)
    ;   T = Expanded
    ).


%!  requires_library(+Term, -Library)
%
%   known expansion hooks.  Should be more dynamic!

requires_library((:- emacs_begin_mode(_,_,_,_,_)), library(emacs_extend)).
requires_library((:- draw_begin_shape(_,_,_,_)), library(pcedraw)).


                 /*******************************
                 *           PROCESS            *
                 *******************************/

process((:- Directive)) :-
    !,
    process_directive(Directive),
    !.
process((Head :- Body)) :-
    !,
    assert_defined(Head),
    process_body(Body).
process('$source_location'(_File, _Line):Clause) :-
    !,
    process(Clause).
process(Head) :-
    assert_defined(Head).

                /********************************
                 *           DIRECTIVES         *
                 ********************************/

process_directive(List) :-
    is_list(List),
    !,
    process_directive(consult(List)).
process_directive(use_module(_Module, Import)) :-
    assert_import(Import).
process_directive(require(Import)) :-            % Include if report only
    assert_current_require_declaration(Import).
process_directive(use_module(Modules)) :-
    process_use_module(Modules).
process_directive(consult(Modules)) :-
    process_use_module(Modules).
process_directive(ensure_loaded(Modules)) :-
    process_use_module(Modules).
process_directive(dynamic(Dynamic)) :-
    assert_dynamic(Dynamic).

process_directive(op(P, A, N)) :-
    op(P, A, N).                    % should be local ...
process_directive(pce_expansion:push_compile_operators) :-
    pce_expansion:push_compile_operators.
process_directive(pce_expansion:pop_compile_operators) :-
    pce_expansion:pop_compile_operators.
process_directive(Goal) :-
    process_body(Goal).


              /********************************
              *             BODY                *
              ********************************/

meta_goal((A, B),               [A, B]).
meta_goal((A; B),               [A, B]).
meta_goal((A| B),               [A, B]).
meta_goal((A -> B),             [A, B]).
meta_goal(findall(_V, G, _L),   [G]).
meta_goal(setof(_V, G, _L),     [G]).
meta_goal(bagof(_V, G, _L),     [G]).
meta_goal(forall(A, B),         [A, B]).
meta_goal(maplist(G, _),        [G+1]).
meta_goal(maplist(G, _, _),     [G+2]).
meta_goal(maplist(G, _, _, _),  [G+3]).
meta_goal(checklist(G, _L),     [G+1]).
meta_goal(call(G),              [G]).
meta_goal(call(G, _A1),         [G+1]).
meta_goal(call(G, _A1, _A2),    [G+2]).
meta_goal(not(G),               [G]).
meta_goal(\+(G),                [G]).
meta_goal(ignore(G),            [G]).
meta_goal(once(G),              [G]).
meta_goal(initialization(G),    [G]).

meta_goal(ifmaintainer(G),      [G]).   % used in manual

process_body(Goal) :-
    meta_goal(Goal, Metas),
    !,
    assert_called(Goal),
    process_called_list(Metas).
process_body(Goal) :-
    assert_called(Goal),
    ignore(check_goal(Goal)).

process_called_list([]).
process_called_list([H|T]) :-
    process_meta(H),
    process_called_list(T).

process_meta(A+N) :-
    !,
    nonvar(A),
    \+ A = _:_,
    A =.. List,
    length(Rest, N),
    append(List, Rest, NList),
    Term =.. NList,
    process_body(Term).
process_meta(G) :-
    process_body(G).


                /********************************
                *           CHECKING            *
                ********************************/

check_goal(Goal) :-
    send_list_goal(Goal),
    output_compatibility('Send/[2,3] used with list argument').

send_list_goal(Goal) :-
    (   Goal = send(A, B)
    ;   Goal = send(A, B, C)
    ),
    member(X, [A,B,C]),
    nonvar(X),
    X = [_|_],
    !.


                /********************************
                *       INCLUDED MODULES        *
                ********************************/

process_use_module(_Module:_Files) :- !. % loaded in another module
process_use_module([]) :- !.
process_use_module([H|T]) :-
    !,
    process_use_module(H),
    process_use_module(T).
process_use_module(library(pce)) :-    % bit special
    !,
    file_public_list(library(pce), Public),
    forall(member(Name/Arity, Public),
           (   functor(Term, Name, Arity),
               \+ system_predicate(Term),
               \+ Term = pce_error(_) % hack!?
           ->  assert_defined(Term)
           ;   true
           )).
process_use_module(File) :-
    (   file_public_list(File, Public)
    ->  assert_import(Public)
    ;   true
    ).

file_public_list(File, Public) :-
    find_source_file(File, Source),
    seeing(Old), see(Source),
    read(ModuleDecl),
    seen, see(Old),
    ModuleDecl = (:- module(_, Public)).


                /********************************
                *       PHASE 1 ASSERTIONS      *
                ********************************/

assert_called(Var) :-
    var(Var),
    !.
assert_called(Goal) :-
    called(Goal),
    !.
assert_called(Goal) :-
    functor(Goal, Name, Arity),
    functor(Term, Name, Arity),
    asserta(called(Term)).

assert_defined(_Module:_Head) :- !.     % defining in another module.  Bah!
assert_defined(Goal) :-
    defined(Goal),
    !.
assert_defined(Goal) :-
    functor(Goal, Name, Arity),
    functor(Term, Name, Arity),
    check_system_predicate(Term),
    asserta(defined(Term)).

assert_import([]) :- !.
assert_import([H|T]) :-
    assert_import(H),
    assert_import(T).
assert_import(Name/Arity) :-
    functor(Term, Name, Arity),
    assert_defined(Term).

assert_dynamic((A, B)) :-
    !,
    assert_dynamic(A),
    assert_dynamic(B).
assert_dynamic(Name/Arity) :-
    functor(Term, Name, Arity),
    assert_defined(Term).


assert_current_require_declaration([]).
assert_current_require_declaration([Name/Arity|Rest]) :-
    functor(Head, Name, Arity),
    assert(current_require_declaration(Head)),
    assert_current_require_declaration(Rest).

check_system_predicate(Head) :-
    system_predicate(Head),
    !,
    functor(Head, Name, Arity),
    target_prolog(Prolog),
    source_warning('Redefined ~w system predicate: ~w/~d',
                   [Prolog, Name, Arity]).
pce_ifhostproperty(prolog(swi),
(check_system_predicate(Head) :-
        predicate_property(system:Head, system_predicate), !,
        functor(Head, Name, Arity),
        Prolog = 'SWI-Prolog',
        source_warning('Redefined ~w system predicate: ~w/~d',
                       [Prolog, Name, Arity]))).
check_system_predicate(_).

                /********************************
                *             REPORT            *
                ********************************/

undefined(Head) :-
    defined(Head), !, fail.
undefined(Head) :-
    system_predicate(Head), !, fail.
undefined(_).

report :-
    findall(Head, (called(Head), undefined(Head)), U0),
    sort(U0, Undefined),            % remove duplicates
    (   forall(member(U, Undefined), current_require_declaration(U)),
        forall(current_require_declaration(U), member(U, Undefined))
    ->  message(':- require/1: up-to-date')
    ;   output(':- require([ '),
        report_undefined(Undefined),
        output(']).~n')
    ).


report_undefined([]).
report_undefined([L]) :-
    !,
    functor(L, Name, Arity),
    report_name_arity(Name, Arity),
    output('~n\t   ', []).
report_undefined([H|T]) :-
    functor(H, Name, Arity),
    report_name_arity(Name, Arity),
    output(',~n\t     ', []),
    report_undefined(T).

report_name_arity(Name, Arity) :-
    current_op(P, _, Name),
    P >= 1000,
    !,
    output('(~q)/~d', [Name, Arity]).
report_name_arity(Name, Arity) :-
    output('~q', [Name/Arity]).


                /********************************
                *            UTILITIES          *
                ********************************/

%!  find_source_file(+Spec, -File)
%
%   Find named source file.

find_source_file(Spec, File) :-
    do_find_source_file(Spec, File),
    !.
find_source_file(Spec, _) :-
    source_warning('Cannot file from ~w', [Spec]),
    fail.

do_find_source_file(Spec, File) :-
    absolute_file_name(Spec, File,
                       [ file_type(prolog),
                         access(read),
                         file_errors(fail)
                       ]),
    !.


                /********************************
                *            OUTPUT             *
                ********************************/

to_string(Prolog, string(Prolog)) :-
    is_list(Prolog),
    !.
to_string(Atomic, Atomic).

output(Fmt) :-
    output(Fmt, []).
output(Fmt, Args) :-
    output_to(D, _), D \== @nil,
    !,
    sformat(Buf, Fmt, Args),
    to_string(Buf, String),
    send(D, append, String).
output(Fmt, Args) :-
    format(Fmt, Args).


message(Fmt) :-
    message(Fmt, []).
message(Fmt, Args) :-
    output_to(_, Msg), Msg \== @nil,
    !,
    sformat(Buf, Fmt, Args),
    to_string(Buf, String),
    send(Msg, append, String).
message(Fmt, Args) :-
    format(user_error, Fmt, Args),
    format(user_error, '~n', []).


output_compatibility(Fmt) :-
    output_compatibility(Fmt, []).
output_compatibility(Fmt, Args) :-
    source_warning(Fmt, Args).

source_warning(Fmt, Args) :-
    pce_error(preformatted(Fmt, Args)).
