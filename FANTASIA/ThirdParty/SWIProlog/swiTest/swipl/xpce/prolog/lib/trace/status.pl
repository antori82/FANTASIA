/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  2001-2020, University of Amsterdam
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

:- module(prolog_debug_status, []).
:- use_module(library(pce)).
:- use_module(library(persistent_frame)).
:- use_module(library(pce_report)).
:- use_module(library(toolbar)).
:- use_module(library('trace/clause')).
:- use_module(library(prolog_predicate_item)).
:- use_module(library(prolog_breakpoints)).
:- if(exists_source(library(prolog_trace))).
:- use_module(library(prolog_trace)).
:- endif.
:- if(exists_source(library(threadutil))).
:- use_module(library(threadutil)).
:- endif.

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This  module  defines  the  class   prolog_debug_status,  a  status  dialog
representing the current debugger-status (cf.  debugging/0) with entries
to alter the state of the  debugger   by  changing  the mode and editing
trace, spy and break-points.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

resource(delete, image, image('16x16/cut.xpm')).
resource(stop,   image, image('16x16/stop.xpm')).
resource(trace,  image, image('16x16/eye.xpm')).
resource(edit,   image, image('16x16/edit.xpm')).
resource(spy,    image, library('trace/icons/spy.xpm')).
resource(icon,   image, image('32x32/dbgsettings.xpm')).

:- dynamic
    debug_status_window/1.


:- pce_begin_class(prolog_debug_status, persistent_frame,
                   "Show status of Prolog debugger").

initialise(F, App:[application]*) :->
    send_super(F, initialise('Prolog debugging')),
    send(F, icon, resource(icon)),
    send(F, append, new(prolog_debug_status_dialog)),
    (   App \== @default, App \== @nil
    ->  send(F, application, App)
    ;   true
    ).

:- pce_end_class(prolog_debug_status).


:- pce_begin_class(prolog_debug_status_dialog, dialog,
                   "View/change debug_status information").

initialise(D) :->
    send_super(D, initialise),
    send(D, append, new(TB, tool_bar(D))),
    send_list(TB, append,
              [ tool_button(cut,
                            resource(delete),
                            delete)
              ]),
    send(D, append,
         new(Ch, menu(mode, choice, message(D, mode, @arg1))),
         right),
    send_list(Ch, append, [ normal, debug ]),
    send(Ch, layout, horizontal),
    send(Ch, alignment, right),
    send(Ch, reference, point(0, Ch?height)),
    send(D, append, new(LB, list_browser)),
    send(LB, select_message, message(D, identify, @arg1)),
    send(LB, open_message, message(D, edit, @arg1)),
    send(LB, style, spy, style(icon := resource(spy))),
    send(LB, style, break, style(icon := resource(stop))),
    send(LB, style, trace, style(icon := resource(trace))),
    send(LB, attribute, hor_stretch, 100),
    send(LB, attribute, ver_stretch, 100),
    send(D, append, new(PI, prolog_predicate_item(predicate))),
    send(PI, length, 30),
    send(PI, reference, point(0, PI?height)),
    send(D, append, new(TB2, tool_bar(D)), right),
    send(TB2, name, tb2),
    send(TB2, alignment, right),
    send_list(TB2, append,
              [ tool_button(spy,
                            resource(spy),
                            'Break on (spy) predicate'),
                tool_button(trace,
                            resource(trace),
                            'Log calls to predicate'),
                tool_button(edit,
                            resource(edit),
                            'Edit predicate/show listing')
              ]),
    send(D, append, new(reporter)),
    send(D, resize_message, message(D, layout, @arg2)),
    send(D, update),
    assert(debug_status_window(D)).

unlink(D) :->
    retractall(debug_status_window(D)),
    send_super(D, unlink).

layout(D, Size:[size]) :->
    "Fix layout"::
    send_super(D, layout, Size),
    get(D, member, tb2, TB2),
    get(D, member, predicate, PI),
    send(PI, right_side, TB2?left_side - D?gap?width).

:- pce_group(update).

clear(D) :->
    "Clear the browser"::
    get(D, member, list_browser, LB),
    send(LB, clear).

update(D) :->
    "Update for current settings"::
    send(D, clear),
    (   debugging(How, Where),
        send(D, append_debug, How, Where),
        fail
    ;   true
    ),
    get(D, member, mode, Mode),
    (   current_prolog_flag(debug, true)
    ->  send(Mode, selection, debug)
    ;   send(Mode, selection, normal)
    ).

append_debug(D, What:{spy,trace,break}, Where:prolog) :->
    get(D, member, list_browser, LB),
    name_of(Where, Label),
    send(LB, append, dict_item(Label,
                               @default,
                               prolog(Where),
                               What)).


debugging(How, Where) :-
    Where = _:_,
    current_predicate(_, Where),
    \+ predicate_property(Where, imported_from(_)),
    debugging_(Where, How).
debugging(break, breakpoint(Id)) :-
    breakpoint_property(Id, clause(_)).

debugging_(Where, spy) :-
    '$get_predicate_attribute'(Where, spy, 1).
:- if(exists_source(library(prolog_trace))).
debugging_(M:Head, trace) :-
    functor(Head, Name, Arity),
    tracing(M:Name/Arity, _).
:- else.
debugging_(Where, trace) :-
    '$get_predicate_attribute'(Where, trace_any, 1).
:- endif.

name_of(breakpoint(Id), Label) :-
    !,
    breakpoint_property(Id, clause(Ref)),
    clause_name(Ref, Label).
name_of(Where, Label) :-
    predicate_name(user:Where, Label).

item(D, What:{spy,trace,break}, Where:prolog, Item:dict_item) :<-
    "Find item representing this debug"::
    get(D, member, list_browser, LB),
    get(LB?members, find_all, @arg1?style == What, Candidates),
    chain_list(Candidates, List),
    member(Item, List),
    get(Item, object, Where).

:- pce_group(action).

selection(D, DI:dict_item) :<-
    "Get selected item"::
    get(D, member, list_browser, LB),
    get(LB, selection, DI).

spy(D) :->
    "Set spy point on predicate"::
    get(D, member, predicate, PI),
    (   get(PI, selection, What)
    ->  user:tspy(What)
    ;   send(D, report, warning, 'No predicate')
    ).

trace(D) :->
    "Set spy point on predicate"::
    get(D, member, predicate, PI),
    (   get(PI, selection, What)
    ->  user:trace(What)
    ;   send(D, report, warning, 'No predicate')
    ).

identify(D, DI:dict_item) :->
    "Report verbosely the meaning of current item"::
    get(DI, label, Label),
    get(DI, style, Style),
    style_name(Style, Name),
    send(D, report, status, '%s %s', Name, Label).

style_name(spy,   'Spy point on').
style_name(break, 'Break-point in').
style_name(trace, 'Trace-point on').

edit(D, DI:[dict_item]) :->
    "Edit source"::
    (   DI \== @default
    ->  get(DI, object, What)
    ;   get(D, member, predicate, PI),
        get(PI, selection, What)
    ->  true
    ;   get(D, selection, DI)
    ->  get(DI, object, What)
    ),
    edit_or_list(What).

edit_or_list(0) :- !, fail.             % catch variables
edit_or_list(Name/Arity) :-
    edit_or_list(_Module:Name/Arity).
edit_or_list(Module:Name/Arity) :-
    atom(Name),
    integer(Arity),
    functor(Head, Name, Arity),
    predicate_property(Module:Head, dynamic),
    predicate_property(Module:Head, number_of_clauses(N)),
    send(@display, confirm,
         '%s:%s/%d is a dynamic predicate with %d clauses.  Show listing?',
         Module, Name, Arity, N),
    !,
    start_emacs,
    new(Tmp, emacs_buffer(@nil, string('*Listing for %s:%s/%d*',
                                       Module, Name, Arity))),
    pce_open(Tmp, write, Out),
    telling(Old), set_output(Out),
    ignore(listing(Module:Name/Arity)),
    tell(Old),
    close(Out),
    send(Tmp, modified, @off),
    send(Tmp, open).
edit_or_list(Spec) :-
    edit(Spec).

cut(D) :->
    "Delete associated object"::
    (   get(D, selection, DI)
    ->  get(DI, object, Where),
        get(DI, style, Style),
        delete(Style, Where)
    ;   send(D, report, warning, 'No selection')
    ).

delete(spy, Head) :-
    !,
    '$nospy'(Head).
delete(trace, Head) :-
    !,
    trace(Head, -all).
delete(break, breakpoint(Id)) :-
    delete_breakpoint(Id).

mode(_D, Mode:{normal,debug,trace}) :->
    "Set the run mode for all threads"::
    (   Mode == normal
    ->  tnodebug
    ;   Mode == debug
    ->  tdebug
    ).

:- pce_end_class.


                 /*******************************
                 *         MESSAGE HOOKS        *
                 *******************************/

:- multifile
    user:message_hook/3.

                                        % ADDING ITEMS
%user:message_hook(Term, Level, _Lines) :-
%       format('~p ~p~n', [Level, Term]),
%       fail.
user:message_hook(spy(Head), _Level, _Lines) :-
    debug_status_window(D),
    send(D, append_debug, spy, Head),
    fail.
user:message_hook(breakpoint(set, Id), _Level, _Lines) :-
    debug_status_window(D),
    send(D, append_debug, break, breakpoint(Id)),
    fail.
user:message_hook(trace(Head, Ports), _Level, _Lines) :-
    Ports \== [],
    debug_status_window(D),
    \+ get(D, item, trace, Head, _),
    send(D, append_debug, trace, Head),
    fail.
                                        % DELETING ITEMS
user:message_hook(nospy(Head), _Level, _Lines) :-
    debug_status_window(D),
    get(D, item, spy, Head, DI),
    free(DI),
    fail.
user:message_hook(breakpoint(delete, Id), _Level, _Lines) :-
    debug_status_window(D),
    get(D, item, break, breakpoint(Id), DI),
    free(DI),
    fail.
user:message_hook(trace(Head, []), _Level, _Lines) :-
    debug_status_window(D),
    get(D, item, trace, Head, DI),
    free(DI),
    fail.
user:message_hook(debug_mode(OnOff), _Level, _Lines) :-
    debug_status_window(D),
    get(D, member, mode, Mode),
    (   OnOff == off
    ->  send(Mode, selection, normal)
    ;   send(Mode, selection, debug)
    ).
user:message_hook(trace_mode(_OnOff), _Level, _Lines) :-
    debug_status_window(D),
    get(D, member, mode, Mode),
    (   current_prolog_flag(debug, true)
    ->  send(Mode, selection, debug)
    ;   send(Mode, selection, normal)
    ).
