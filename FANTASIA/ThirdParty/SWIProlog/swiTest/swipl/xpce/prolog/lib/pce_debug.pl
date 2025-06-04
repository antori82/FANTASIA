/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi-prolog.org
    WWW:           https://www.swi-prolog.org
    Copyright (c)  1985-2021, University of Amsterdam
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

:- module(pce_debug,
        [ debugpce/0
        , debugpce/1
        , nodebugpce/0
        , nodebugpce/1
        , tracepce/1                    % Trace a pce method
        , notracepce/1                  % UnTrace a pce method
        , spypce/1                      % Trace a pce method
        , nospypce/1                    % UnTrace a pce method
        , checkpce/0                    % Check all global pce objects
        , show_slots/1                  % Show all pce slot-values
        , pcerefer/1                    % Print objects refering to me
        , pcerefer/2                    % Print objects refering to me
        , pce_global_objects/1          % -globals
        ]).
:- use_module(library(pce)).
:- require([ forall/2
           , pce_to_method/2
           , append/3
           , between/3
           , genarg/3
           ]).
:- set_prolog_flag(generate_debug_info, false).
:- meta_predicate test(0,-).

% leave this to the user
% :- op(100, xfx, user:(<-)).

%   debugpce/0
%   nodebugpce/0

debugpce :-
    send(@pce, debugging, @on).
nodebugpce :-
    send(@pce, debugging, @off).


%%   debugpce(+Subject) is det.
%%   nodebugpce(+Subject) is det.
%
%   Start/stop printing debugging messages on `Subject'. System maintenance
%   usage only.

debugpce(Subject) :-
    send(@pce, debug_subject, Subject).

nodebugpce(Subject) :-
    send(@pce, nodebug_subject, Subject).



%       (no)tracepce(+ClassName ->|<- +Selector)
%
%       Send a ->trace message to the refered method.  This will cause
%       PCE to  print the enters,  exits or failures  of  this method.
%       Prints  the class  and selector   on  which  the tracepoint is
%       actually set (which might be an inherited method).

tracepce(Spec) :-
    method(Spec, Method),
    send(Method, trace, full),
    trace_feedback('Tracing', Method).

notracepce(Spec) :-
    !,
    method(Spec, Method),
    send(Method, trace, full, @off),
    trace_feedback('Stopped tracing', Method).

%       (no)spypce(+ClassName ->|<- +Selector)
%
%       Put a spy-point on the Prolog implementation or XPCE method object

spypce(Spec) :-
    method(Spec, Method),
    send(Method, break, full),
    (   prolog_method(Method)
    ->  debug
    ;   true
    ),
    trace_feedback('Spying', Method).

nospypce(Spec) :-
    method(Spec, Method),
    send(Method, break, full, @off),
    trace_feedback('Stopped spying', Method).

method(Spec, Method) :-
    pce_to_method(Spec, Method),
    send(Method, instance_of, behaviour).


%       succeed if the method is implemented in Prolog (dubious test).

prolog_method(Implementation) :-
    send(Implementation, instance_of, method),
    get(Implementation, message, Msg),
    send(Msg, instance_of, c_pointer).

trace_feedback(Action, Obj) :-
    (   prolog_method(Obj)
    ->  Type = 'Prolog implementation of'
    ;   get(Obj?class_name, label_name, Type)
    ),
    get(Obj?context, name, ClassName),
    get(Obj, name, Selector),
    get(Obj, access_arrow, Arrow),
    format('~w ~w: ~w ~w~w~n', [Action, Type, ClassName, Arrow, Selector]).


                /********************************
                *       CHECK PCE DATABASE      *
                ********************************/

%!  pce_global_objects(-ChainOfGlobalObjects)
%   Return a chain with all globally known objects.

pce_global_objects(Chain) :-
    new(Chain, chain),
    send(@pce, for_name_reference,
         message(@prolog, '_append_reference', Chain, @arg1)).

'_append_reference'(_, Name) :-
    non_object_reference(Name),
    !.
'_append_reference'(Chain, Name) :-
    send(Chain, '_append', @Name).

non_object_reference('_object_to_itf_table').
non_object_reference('_name_to_itf_table').
non_object_reference('_handle_to_itf_table').

%       checkpce/0
%
%       Runs a recursive  '_check' on all  reachable objects.  See the
%       reference documentation of `Object ->_check' for details.

checkpce :-
    get(@pce, is_runtime_system, @on),
    !,
    send(checkpce, error, runtime_version).
checkpce :-
    test(check_pce_database, Status),
    test(check_pce_types, Status),
    test(check_classes, Status),
    test(check_redefined_methods, Status),
    Status = yes.

check_classes :-
    (   pce_expansion:compiling(_, _)
    ->  forall(pce_expansion:compiling(Class, Path),
               ( file_base_name(Path, File),
                 send(@pce, format,
                      '[PCE: WARNING: definition of class \c
                          %s in ~s not closed]\n',
                      Class, File))),
        fail
    ;   true
    ).

check_redefined_methods :-
    findall(S, redefined_send_method(S), SL),
    maplist(report_redefined_method, SL),
    findall(G, redefined_get_method(G), GL),
    maplist(report_redefined_method, GL),
    SL == [],
    GL == [].

redefined_send_method(method(Class, Sel, B0, B1)) :-
    pce_principal:pce_lazy_send_method(Sel, Class, B1),
    (   pce_principal:pce_lazy_send_method(Sel, Class, B0)
    ->  B0 \== B1
    ;   fail
    ).
redefined_get_method(method(Class, Sel, B0, B1)) :-
    pce_principal:pce_lazy_get_method(Sel, Class, B1),
    (   pce_principal:pce_lazy_get_method(Sel, Class, B0)
    ->  B0 \== B1
    ;   fail
    ).

report_redefined_method(method(_, _, B0, B1)) :-
    arg(1, B0, Id0),                % deliberate redefinition
    arg(1, B1, Id1),
    Id0 \== Id1,
    !.
report_redefined_method(method(Class, Sel, B0, B1)) :-
    describe_location(B1, Loc1),
    (   Loc1 = File:Line
    ->  Loc = file(File, Line)
    ;   true
    ),
    print_message(error,
                  error(pce(redefined_method(Class, Sel, B0, B1)),
                        Loc)).

describe_location(Binder, File:Line) :-
    genarg(_, Binder, source_location(File, Line)),
    !.
describe_location(_, '<no source>').


check_pce_database :-
    pce_global_objects(All),
    send(All, '_check'),
    send(All, done).

check_pce_types :-
    get(@pce, unresolved_types, Types),
    get(Types, find_all,
        message(@prolog, no_autoload_class, @arg1?context?print_name),
        Unresolved),
    (   send(Unresolved, empty)
    ->  true
    ;   send(@pce, format,
             '[PCE: WARNING: The following type(s) have no associated class:\n'),
        send(Unresolved, for_all,
             message(@pce, format, '\t%N\n', @arg1)),
        send(@pce, format, ']\n')
    ).


no_autoload_class(ClassName) :-
    pce_prolog_class(ClassName), !, fail.
no_autoload_class(ClassName) :-
    pce_autoload:autoload_decl(ClassName, _), !, fail.
no_autoload_class(_).


%!  show_slots(+Reference)
%
%   Show  all   slots of the   named object.  Actually,  this is a
%   terminal version  of   the inspector  tool  provided  with the
%   manual.  Notably used by me if PCE is in such  a bad shape the
%   inspector won't run anymore

show_slots(X) :-
    get(X, '_class', Class),
    get(Class, slots, Slots),
    Max is Slots - 1,
    X = @Ref,
    get(X, '_class_name', ClassName),
    format('@~w/~w~n', [Ref, ClassName]),
    between(0, Max, Slot),
        get(X, '_slot', Slot, Value),
        get(Class, instance_variable, Slot, Var),
        get(Var, name, Name),
        format('~t~8|~w~t~30|~p~n', [Name, Value]),
    fail ; true.


                /********************************
                *             REFER             *
                ********************************/

pcerefer(Obj) :-
    get(Obj, '_references', Refs),
    format('~p has ~d references~n', [Obj, Refs]),
    (   Refs > 0
    ->  pce_global_objects(All),
        new(Found, number(0)),
        send(All, for_slot_reference,
             if(message(Obj, '_same_reference', @arg4),
                message(@prolog, call,
                        pcerefer, Obj, @arg1, @arg2, @arg3, All, Found))),
        send(All, done),
        get(Found, value, FoundRefs),
        (   Refs == FoundRefs
        ->  format('Found all references~n', [])
        ;   format('Found ~d of ~d references~n', [FoundRefs, Refs])
        ),
        free(Found)
    ;   true
    ).


pcerefer(From, Obj) :-
    get(Obj, references, Refs),
    format('~p has ~d references~n', [Obj, Refs]),
    (   Refs > 0
    ->  new(Found, number(0)),
        send(From, for_slot_reference,
             if(Obj == @arg4,
                message(@prolog, call,
                        pcerefer, Obj, @arg1, @arg2, @arg3, @nil, Found))),
        free(Found)
    ;   true
    ).

:- public pcerefer/6.

pcerefer(Obj, From, Type, Where, All, Found) :-
    Obj \== All,
    From \== All,
    !,
    get(From, '_class_name', ClassName),
    format('~t~8|~w ~w of ~w/~w --> ~p~n',
           [Type, Where, From, ClassName, Obj]),
    send(Found, plus, 1).
pcerefer(_, _, _, _, _, _).


                /********************************
                *           UTILITIES           *
                ********************************/

test(Goal, _) :-
    Goal,
    !.
test(_, no).

                 /*******************************
                 *            MESSAGES          *
                 *******************************/


:- multifile
    prolog:message/3.

prolog:message(error(pce(redefined_method(Class, Sel, B0, B1)), _)) -->
    { describe_location(B0, Loc0),
      describe_location(B1, Loc1),
      (   functor(B0, bind_send, _)
      ->  Arrow = (->)
      ;   Arrow = (<-)
      )
    },
    [ '~w: ~w~w~w redefined'-[Loc1, Class, Arrow, Sel], nl,
      '\tFirst definition at ~w'-[Loc0]
    ].
