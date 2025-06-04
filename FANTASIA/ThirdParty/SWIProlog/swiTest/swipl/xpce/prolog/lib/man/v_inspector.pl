/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1985-2002, University of Amsterdam
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

:- module(pce_inspector, []).

:- use_module(library(pce)).
:- use_module(library(toolbar)).
:- use_module(library(pce_report)).
:- require([ between/3
           , nth1/3
           , portray_object/2
           , random/3
           , send_list/3
           , term_to_atom/2
           ]).

:- pce_autoload(select_graphical, v_select).

:- dynamic
    inspector_window/1.

resource(clear, image, image('16x16/trashcan.xpm')).
resource(help,  image, image('16x16/help.xpm')).
resource(grab,  image, image('16x16/handpoint.xpm')).


                /********************************
                *        SELECTABLE TEXT        *
                ********************************/

:- pce_begin_class(isp_selectable_text, text).

initialise(T, String:string, Adjust:[name], Font:[font]) :->
    send(T, send_super, initialise, String, Adjust, Font).


:- pce_global(@isp_selectable_text_handler,
        new(click_gesture(left, '', single,
                          message(@receiver, select)))).

event(_T, Event:event) :->
    send(@isp_selectable_text_handler, event, Event).

select(T) :->
    send(T?window, selection, T),
    get(T, display, Display),
    (    get(T, object, Object)
    ->   flash(Object),
         Object = @Reference,
         new(S, string('@%s', Reference))
    ;    get(T, string, S)
    ),
    send(Display, copy, S).


reference(_T, _) :<-
    fail.

object(T, Obj:'object|function') :<-
    get(T, reference, Ref),
    object(@Ref),
    Obj = @Ref.

flash(Object) :-
    object(Object),
    send(Object, has_send_method, flash),
    !,
    send(Object, flash).
flash(_).

:- pce_end_class.

                /********************************
                *          VALUE_TEXT           *
                ********************************/

:- pce_begin_class(isp_value_text, isp_selectable_text).

variable(reference,     'name|int*',    get).

handle(w-6, h/2, link).

initialise(T, Value:unchecked) :->
    send(T, send_super, initialise, '', left, font(helvetica, roman, 12)),
    send(T, display_value, Value).


display_value(T, Value:unchecked) :->
    value_text(Value, Text),
    send(T, string, Text),
    send(T, object, Value),
    send(T, relink).


label(T, Label:name) :->
    send(T, name, Label).


value_text(Value, String) :-
    object(Value),
    !,
    Value = @Reference,
    get(Value, '_class_name', ClassName),
    new(String, string('@%s/%s', Reference, ClassName)).
value_text(@Reference, String) :-
    !,
    new(String, string('@%s', Reference)).
value_text(Atomic, Atomic) :-
    atomic(Atomic),
    !.
value_text(Term, Atomic) :-
    term_to_atom(Term, Atomic).     % long terms!?


object(T, Object:unchecked) :->
    (   object(Object)
    ->  Object = @Ref,
        send(T, slot, reference, Ref)
    ;   send(T, slot, reference, @nil)
    ).


object(T, Object) :<-
    get(T, reference, Ref),
    Ref \== @nil,
    Object = @Ref.


%               EVENTS

:- pce_global(@isp_value_text_popup, make_isp_value_text_popup).

make_isp_value_text_popup(P) :-
    new(P, popup),
    VT = @arg1,
    new(Obj, VT?object),
    send_list(P, append,
              [ menu_item(flash_visual,
                          message(Obj, flash),
                          condition := message(Obj, has_send_method,
                                               flash)),
                menu_item(show_card,
                          message(VT, expand),
                          condition := Obj,
                          end_group := @on),
                menu_item(class_details,
                          message(VT, class_details),
                          condition := Obj),
                menu_item(class_source,
                          message(VT, class_source),
                          condition := and(Obj,
                                           Obj?'_class'?creator \== built_in))
              ]).


:- pce_global(@isp_value_text_handler,
        new(handler_group(
                click_gesture(left, '', single,
                              and(message(@receiver, select),
                                  message(@receiver, pretty_print))),
                click_gesture(left, '', double,
                              message(@receiver, expand)),
                handler(ms_right_down, and(message(@receiver, select),
                                           new(or))),
                popup_gesture(@isp_value_text_popup)))).


event(_T, Event:event) :->
    send(@isp_value_text_handler, event, Event).


expand(T) :->
    get(T, object, Object),
    get(T, window, Window),
    get(T, absolute_position, Window, P),
    get(T, width, W),
    send(P, plus, point(W+30,0)),
    send(Window, inspect, Object, P).

class_details(T) :->
    "Show the class browser"::
    get(T, object, Object),
    get(Object, '_class', Class),
    send(T?frame, request_tool_focus, Class).

class_source(T) :->
    "Edit source of related class"::
    get(T, object, Object),
    get(Object, '_class', Class),
    send(T?frame, request_source, Class).

pretty_print(T) :->
    get(T, object, Object),
    flash(Object),
    portray_object(Object, Term),
    term_to_atom(Term, Atom),
    send(T, report, inform, '%s', Atom).

%               LINKS

%       ValueText ->link_to: Reference
%       Called after an inspector for Object has been created.  It will connect
%       to that inspector if it displays the object for which the inspector has
%       been created.

link_to(T, Ref:'name|int') :->
    (   get(T, reference, Ref),
        get(T, window, MonPict),
        get(MonPict, inspector, @Ref, Monitor),
        \+ send(T, connected, Monitor)
    ->  send(T, link, Monitor)
    ;   true
    ).


%       ValueText ->relink
%       Called after the displayed value has been changed.  Destroyes old
%       connections and recreates a new one if necessary.

relink(T) :->
    send(T, disconnect),
    (   get(T, object, Object),
        get(T, window, MonPict),
        get(MonPict, inspector, Object, Monitor)
    ->  send(T, link, Monitor)
    ;   true
    ).


:- pce_global(@isp_value_text_link,
              new(link(link, link, line(0,0,0,0,second)))).

link(T, Gr:graphical) :->
    send(T, connect, Gr, @isp_value_text_link).


:- pce_end_class.

                /********************************
                *        ATTRIBUTE SHEET        *
                ********************************/


:- pce_begin_class(isp_title_text, isp_selectable_text).

initialise(T, String:string) :->
    send(T, send_super,
         initialise, String, left, font(helvetica, bold, 14)).

object(T, Object) :<-
    get(T, device, Dev),
    get(Dev, object, Object).

reference(T, Ref) :<-
    get(T, device, Dev),
    get(Dev, object, @Ref).

:- pce_end_class.


:- pce_begin_class(isp_label_text, isp_selectable_text).

initialise(T, Label:name) :->
    send(T, send_super,
         initialise, Label, left, font(helvetica, roman, 12)).

label(T, Label:name) :->
    send(T, string, Label),
    send(T, name,   Label).

:- pce_end_class.

:- pce_begin_class(isp_attribute_value_sheet, figure).

handle(0, 10, link).

:- pce_global(@isp_attribute_value_sheet_format,
              make_isp_attribute_value_sheet_format).

make_isp_attribute_value_sheet_format(F) :-
    new(F, format(horizontal, 2, @on)),
    send(F, row_sep, 0).

initialise(AV, Title:name, TitleValue:[name]) :->
    new(TT, isp_title_text(Title)),
    new(TV, isp_label_text('')),

    send(TT, name, title),
    send(TV, name, title_value),

    (   TitleValue \== @default
    ->  send(TV, string, TitleValue)
    ;   true
    ),

    send(AV, send_super, initialise),
    send(AV, border, 5),
    send(AV, background, colour(white)),
    send(AV, pen, 1),
    send(AV, shadow, 2),
    send(AV, format, @isp_attribute_value_sheet_format),

    send(AV, display, TT),
    send(AV, display, TV).


unlink(AV) :->
    send(AV, for_some, @default, message(@arg1, disconnect)),
    send(AV, send_super, unlink).


title_value(AV, Text:string) :->
    get(AV, member, title_value, TextObj),
    send(TextObj, string, Text).


display_value(AV, Name:name, Value:unchecked) :->
    new(NT, isp_label_text(Name)),
    new(VT, isp_value_text(Value)),

    send(NT, name, Name),
    send(VT, name, Name),

    send(AV, display, NT),
    send(AV, display, VT).


value(AV, Name:name, Value:unchecked) :->
    send(AV, for_some, Name,
         if(message(@arg1, instance_of, isp_value_text),
            message(@arg1, display_value, Value))).


relink(AV) :->
    send(AV, for_all, @default,
         if(message(@arg1, has_send_method, relink),
            message(@arg1, relink))).


link_to(AV, Dest:'name|int') :->
    send(AV, for_all, @default,
         if(message(@arg1, has_send_method, link_to),
            message(@arg1, link_to, Dest))).


:- pce_global(@isp_attribute_value_sheet_handler,
              make_isp_attribute_value_sheet_handler).

make_isp_attribute_value_sheet_handler(H) :-
    new(H, handler_group(popup_gesture(new(P, popup)),
                         click_gesture(left, '', single,
                                       message(@receiver, expose)),
                         new(move_outline_gesture))),
    new(IsObjectSheet, message(@arg1, instance_of, isp_object_sheet)),
    new(Obj, @arg1?object),
    send_list(P, append,
              [ menu_item(send_to_foreground,
                          message(@arg1, expose)),
                menu_item(send_to_background,
                          message(@arg1, hide)),
                menu_item(quit,
                          message(@arg1, quit), end_group := @on),
                menu_item(class_details,
                          message(@arg1, class_details),
                          condition := IsObjectSheet),
                menu_item(class_source,
                          message(@arg1, class_source),
                          end_group := @on,
                          condition := and(IsObjectSheet,
                                           Obj?'_class'?creator \== built_in)),
                menu_item(find_referees,
                          message(@arg1, referees),
                          condition := and(Obj,
                                           Obj?'_references' > 0))
              ]).


event(AV, Event:event) :->
    (   send(AV, send_super, event, Event)
    ->  true
    ;   send(@isp_attribute_value_sheet_handler, event, Event)
    ).


quit(AV) :->
    (   get(AV, object, Object)
    ->  send(Object, '_inspect', @off),
        get(AV, device, Dev),
        send(Dev, uninspect, Object)
    ;   true
    ).

:- pce_end_class.


                /********************************
                *         OBJECT_SHEET          *
                ********************************/

:- pce_begin_class(isp_object_sheet, isp_attribute_value_sheet).

variable(object, any, none).

initialise(OS, Object:'object|function') :->
    value_text(Object, Title),
    send(OS, object, Object),
    send(OS, send_super, initialise, Title),
    send(OS, update_flags),
    send(OS, display_slots).

object(OS, Object:'object|function') :->
    Object = @Reference,
    send(OS, slot, object, Reference).

object(OS, Object) :<-
    get(OS, slot, object, Reference),
    Object = @Reference.

update_flags(OS) :->
    get(OS, object, Object),
    get(Object, '_flags', Flags),
    get(Object, '_references', Refs),
    send(OS, title_value, string('%s (%s)', Flags, Refs)).

display_slots(OS) :->
    get(OS, object, Object),
    display_extensions(OS, Object),
    display_slots(OS, Object).

display_extensions(OS, Object) :-
    display_extension(OS, Object, all_attributes),
    display_extension(OS, Object, all_constraints),
    display_extension(OS, Object, all_get_methods),
    display_extension(OS, Object, all_hypers),
    display_extension(OS, Object, all_recognisers),
    display_extension(OS, Object, all_send_methods).

display_extension(OS, Object, Ext) :-
    \+ send(Object, '_instance_of', function),
    send(Object, has_get_method, Ext),
    get(Object, Ext, Value),
    !,
    send(OS, display_value, Ext, Value).
display_extension(_, _, _).


%       for chains and vectors we first display the extra slots and
%       then the elements

display_slots(OS, Chain) :-
    send(Chain, '_instance_of', chain),
    !,
    class_slot_names(chain, ChainSlots),
    slot_names(Chain, Names),
    subtract(Names, ChainSlots, ExtraSlots),
    display_slots(OS, Chain, ExtraSlots),
    display_slots_v(OS, Chain, []).
display_slots(OS, Vector) :-
    send(Vector, '_instance_of', vector),
    !,
    class_slot_names(vector, VectorSlots),
    slot_names(Vector, Names),
    subtract(Names, VectorSlots, ExtraSlots),
    display_slots(OS, Vector, ExtraSlots),
    display_slots_v(OS, Vector, []).
display_slots(OS, PrimCode) :-
    send(PrimCode, '_instance_of', message),
    !,
    display_slots_v(OS, PrimCode, [receiver, selector]).
display_slots(OS, PrimCode) :-
    send(PrimCode, '_instance_of', ?),
    !,
    display_slots_v(OS, PrimCode, [receiver, selector]).
display_slots(OS, String) :-
    send(String, '_instance_of', char_array),
    !,
    get(String, value, Text),
    send(OS, display_value, value, Text),
    class_slot_names(char_array, StringSlots),
    slot_names(String, Names),
    subtract(Names, StringSlots, ExtraSlots),
    display_slots(OS, String, ExtraSlots).
display_slots(OS, Object) :-
    slot_names(Object, Names),
    display_slots(OS, Object, Names).

slot_names(Object, Names) :-
    get(Object, '_class', Class),
    class_slot_names(Class, Names).

class_slot_names(Class, Names) :-
    atom(Class),
    !,
    get(@pce, convert, Class, class, Object),
    class_slot_names(Object, Names).
class_slot_names(Class, Names) :-
    get(Class, slots, N),
    slot_names(Class, 0, N, Raw),
    sort(Raw, Names).

slot_names(_, N, N, []) :- !.
slot_names(Class, Slot, Max, [Name|Rest]) :-
    get(Class, instance_variable, Slot, Var),
    get(Var, name, Name),
    Next is Slot + 1,
    slot_names(Class, Next, Max, Rest).

display_slots(_, _, []) :- !.
display_slots(OS, Obj, [Name|Rest]) :-
    get(Obj, '_slot', Name, Value),
    send(OS, display_value, Name, Value),
    display_slots(OS, Obj, Rest).

display_slots_v(OS, Obj, First) :-
    get(Obj, '_arity', Arity),
    Max is Arity + 1,
    length(First, NF),
    display_slots_v(OS, Obj, First, NF, 1, Max).

display_slots_v(_, _, _, _, N, N) :- !.
display_slots_v(OS, Obj, First, NF, Arg, N) :-
    get(Obj, '_arg', Arg, ArgValue),
    (   Arg > NF
    ->  ArgName is Arg - NF
    ;   nth1(Arg, First, ArgName)
    ),
    send(OS, display_value, ArgName, ArgValue),
    Next is Arg + 1,
    display_slots_v(OS, Obj, First, NF, Next, N).


%       Enumerated slots

change_no(OS, Index:int, Value:any) :->
    send(OS, value, Index, Value).


clear_no(OS) :->
    between(1, 10000, N),
        (   get(OS, member, N, _)
        ->  send(OS, for_all, N, message(@arg1, free)),
            fail
        ;   !
        ).

delete_no(OS, Index:int) :->
    send(OS, for_all, Index, message(@arg1, free)),
    between(Index, 10000, N),
        Next is N + 1,
        (   get(OS, member, Next, _)
        ->  send(OS, for_all, Next, message(@arg1, label, N)),
            fail
        ;   !
        ).

insert_no(OS, Index:int, Value:any) :->
    get(OS, graphicals, Grs),
    (   get(Grs, tail, LastValueText),
        get(LastValueText, name, LastName),
        get(@pce, convert, LastName, int, End)
    ->  Start is Index - 1,
        rename_att_values(End, Start, OS)
    ;   true
    ),
    send(OS, display_value, Index, Value),
    get(Grs, tail, ValueText),
    send(ValueText, relink),
    (   Next is Index + 1,
        get(OS, member, Next, NextGr)
    ->  send(ValueText, hide, NextGr),
        send(Grs?tail, hide, ValueText)
    ;   true
    ).

rename_att_values(Start, Start, _) :- !.
rename_att_values(Index, Start, OS) :-
    Next is Index + 1,
    send(OS, for_all, Index, message(@arg1, label, Next)),
    Prev is Index - 1,
    rename_att_values(Prev, Start, OS).

class_details(OS) :->
    "Show the class browser"::
    get(OS, object, Object),
    get(Object, '_class', Class),
    send(OS?frame, request_tool_focus, Class).

class_source(OS) :->
    "Edit source of related class"::
    get(OS, object, Object),
    get(Object, '_class', Class),
    send(OS?frame, request_source, Class).

referees(OS) :->
    "Add objects refering to me"::
    get(OS, object, Object),
    pce_global_objects(Globals),
    send(Globals, for_slot_reference,
         if(message(Object, '_same_reference', @arg4),
            message(OS, add_referee, @arg1, Globals))),
    send(Globals, done).

add_referee(OS, From:unchecked, Globals:chain) :->
    (   From \== Globals
    ->  get(OS, window, Inspector),
        send(Inspector, inspect, From)
    ;   true
    ).

:- pce_end_class.

                /********************************
                *        INSPECTOR_WINDOW       *
                ********************************/

:- pce_begin_class(isp_inspector_window, picture).

variable(inspected,             hash_table,     get).

initialise(MP) :->
    send(MP, send_super, initialise, 'PCE Inspector', size(512, 512)),
    send(MP, slot, inspected, new(hash_table)),
    send(MP, done_message, message(MP, quit)).


selection(MP, Gr:graphical) :<-
    get(MP, hypered, selection, Gr).

selection(MP, Gr:graphical*) :->
    "Set (sole) selected object"::
    (   get(MP, selection, Old)
    ->  send(Old, selected, @off)
    ;   true
    ),
    send(MP, delete_hypers, selection),
    new(_, hyper(MP, Gr, selection, window)),
    (   Gr \== @nil
    ->  send(Gr, selected, @on)
    ;   true
    ).


inspect_object(MP, Object:object) :->
    send(MP, inspect, Object).


inspect(MP, Object:'object|function', Pos:[point]) :->
    object(Object),
    check_not_self(MP, Object),
    (   get(MP, inspector, Object, Monitor)
    ->  send(Monitor, expose),
        send(Monitor, flash)
    ;   new(OS, isp_object_sheet(Object)),
        (   Pos == @default
        ->  get(MP, visible, area(X, Y, W, H)),
            get(OS, size, size(OW, OH)),
            random_pos(X, W, OW, OX),
            random_pos(Y, H, OH, OY),
            ThePos = point(OX, OY)
        ;   ThePos = Pos
        ),
        send(MP, display, OS, ThePos),
        Object = @Reference,
        get(MP, inspected, Table),
        send(Table, append, Reference, OS),
        send(OS, relink),
        send(MP, for_some, @default,
             if(message(@arg1, instance_of, isp_object_sheet),
                message(@arg1, link_to, Reference))),
        prepare_class(Object)
    ).


%       Place object with with OW at random location in window at X
%       with visual width W.

random_pos(X, W, OW, OX) :-
    WRI is W - OW - 20,
    (   WRI > 0
    ->  random(0, WRI, WRAND),
        OX is X + WRAND + 10
    ;   OX is X + 10
    ).


check_not_self(MP, Display) :-
    send(Display, '_instance_of', display),
    !,
    send(MP, report, error, 'Can''t inspect the display'),
    fail.
check_not_self(Pict, Obj) :-
    send(Obj, '_instance_of', graphical),
    get(Obj, frame, Frame),
    get(Pict, frame, Frame),
    !,
    send(Pict, report, error, 'Can''t inspect myself'),
    fail.
check_not_self(_, _).


inspector(MP, Object:'object|function', Monitor) :<-
    object(Object),
    Object = @Reference,
    get(MP, inspected, Table),
    get(Table, member, Reference, Monitor).


uninspect(MP, Object:'object|function') :->
    get(MP, inspector, Object, Monitor),
    Object = @Reference,
    get(MP, inspected, Table),
    send(Table, delete, Reference),
    send(Object, '_inspect', @off),
    send(Monitor, free).


unregister(MP) :->
    "Delete all registrations"::
    get(MP, inspected, Table),
    send(Table, for_all,
         message(@arg1, '_inspect', @off)).


clear(MP) :->
    "Send ->quit to all object-sheets"::
    send(MP, for_some, isp_object_sheet, message(@arg1, quit)).


inspect_atom(MP, What:string) :->
    "Create a card, target is a string"::
    send(What, strip),
    (   (   get(What, scan, '@%d', vector(Ref))
        ;   get(What, scan, '@%s', vector(string(Ref)))
        )
    ->  (   object(@Ref)
        ->  send(MP, inspect, @Ref)
        ;   send(MP, report, error, 'No such object: %s', What)
        )
    ;   send(MP, report, error, 'Bad object reference syntax: %s', What)
    ).

                /********************************
                *          TRAP CHANGES         *
                ********************************/

%       prepare_class(+Object)
%       Install changes forwarding messages for the class `Object' belongs
%       to.

prepare_class(Object) :-
    send(Object, '_inspect', @on),
    get(Object, '_class', Class),
    send(Class, changed_message, @changed_slot),
    send(Class, freed_message, @freed_object).

:- pce_global(@freed_object, make_freed_object).
:- pce_global(@changed_slot, make_changed_slot).

make_changed_slot(Msg) :-
    new(Msg, message(@prolog, call,
                     changed_slot, @arg1, @arg2, @arg3)),
    send(Msg, debug_class, service).
make_freed_object(Msg) :-
    new(Msg, message(@prolog, call, freed_object, @arg2)),
    send(Msg, debug_class, service).

changed_slot(Instance, add_reference, _From) :-
    !,
    inspector_window(Mon),
    get(Mon, inspector, Instance, Monitor),
    send(Monitor, update_flags),
    fail ; true.
changed_slot(Instance, del_reference, _From) :-
    !,
    inspector_window(Mon),
    get(Mon, inspector, Instance, Monitor),
    send(Monitor, update_flags),
    fail ; true.
changed_slot(Instance, A1, A2) :-
    inspector_window(Mon),
    get(Mon, inspector, Instance, Monitor),
    get(Instance, '_class_name', ClassName),
    changed_slot(ClassName, Instance, Monitor, A1, A2),
    fail ; true.

changed_slot(chain, _, Monitor, clear,  _) :-
    !,
    send(Monitor, clear_no).
changed_slot(chain, Chain, Monitor, insert, Index) :-
    !,
    get(Chain, nth1, Index, Value),
    send(Monitor, insert_no, Index, Value).
changed_slot(chain, Chain, Monitor, cell,   Index) :-
    !,
    get(Chain, nth1, Index, Value),
    send(Monitor, change_no, Index, Value).
changed_slot(chain, _, Monitor, delete, Index) :-
    !,
    send(Monitor, delete_no, Index).
changed_slot(_, Instance, Monitor, SlotName, _) :-
    get(Instance, slot, SlotName, Value),
    send(Monitor, value, SlotName, Value).


freed_object(Instance) :-
    inspector_window(Mon),
    send(Mon, uninspect, Instance),
    fail ; true.

:- pce_end_class.


                /********************************
                *             MAIN              *
                ********************************/

:- pce_begin_class(isp_frame, man_frame).

initialise(F, Manual:man_manual) :->
    send(F, send_super, initialise, Manual, 'PCE Inspector'),
    send(F, append, new(TD, tool_dialog)),
    send_list(TD, append,
              [ tool_button(clear,
                            resource(clear),
                            'Clear window'),
                tool_button(help,
                            resource(help),
                            'Help on the inspector'),
                tool_button(grab,
                            resource(grab),
                            'Select object from screen')
              ]),
    send(new(Inspector, isp_inspector_window), below, TD),
    asserta(inspector_window(Inspector)),
    send(new(report_dialog), below, Inspector),

    send(TD, append, graphical(0,0,20,0), right),
    send(TD, append,
         new(TI, text_item(inspect, '',
                           and(message(Inspector, inspect_atom, @arg1),
                               message(@receiver, clear)))),
         right),
    send(TI, reference, point(0, TI?height)).


unlink(F) :->
    get(F, member, isp_inspector_window, Inspector),
    retractall(inspector_window(Inspector)),
    send(Inspector, unregister),
    send(F, send_super, unlink).


inspect(F, Object:object) :->
    "Inspect object"::
    get(F, member, isp_inspector_window, Window),
    send(Window, inspect, Object).

clear(F) :->
    get(F, member, isp_inspector_window, Window),
    send(Window, clear).

grab(F) :->
    "Add a new object from the screen"::
    new(D, select_graphical('Select object to inspect')),
    send(D, attribute, report_to, F),
    get(D, select,
        @arg1?frame \== F,
        F?area?center, Obj),
    send(D, destroy),
    Obj \== @nil,
    send(F, inspect, Obj).


:- pce_end_class(isp_frame).
