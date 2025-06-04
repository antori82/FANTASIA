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

:- module(man_summary_browser, []).

:- use_module(library(pce)).
:- use_module(util).
:- require([ forall/2
           , send_list/3
           ]).


:- pce_begin_class(man_summary_browser(displayed_attribute, size), browser).

class_variable(header_font,     font,   bold).
class_variable(list_font,       font,   normal).

variable(displayed_attribute, name, get,
         "Get method for getting string").

                /********************************
                *            CREATE             *
                ********************************/

:- pce_autoload(drag_and_drop_dict_item_gesture, library(dragdict)).
:- pce_global(@man_drag_and_drop_objects,
              make_man_drag_and_drop_objects).

make_man_drag_and_drop_objects(G) :-
    new(G, drag_and_drop_dict_item_gesture),
    send(G, get_source, @arg1?object).


initialise(S, Att:name, Size:size) :->
    "Create from displayed attribute and size"::
    DI = @arg1,
    new(Tool, S?frame),
    new(Manual, Tool?manual),
    new(Selection, Manual?selection),
    new(Obj, DI?object),

    get(S, list_font, ListFont),
    get(S, header_font, HeaderFont),

    send(S, send_super, initialise, @default, Size),
    send(S, slot, displayed_attribute, Att),
    send(S, font, ListFont),
    send(S, tab_stops, vector(20, 300)),
    send_list(S, [hor_stretch, hor_shrink], 100),
    send_list(S, [ver_stretch, ver_shrink], 1000),
    send(S, style, header, style(font := HeaderFont)),

    send(S, select_message,
         message(S, request_selection, Obj, @off)),
    send(S, open_message,
         message(S, request_selection, Obj, @on)),
    send(S?list_browser, recogniser, @man_drag_and_drop_objects),

    send(S, popup, new(P, popup(view, @nil))),
    send_list(P, append,
              [ menu_item(select,
                          message(S, request_selection, Obj, @on))
              , menu_item(class_browser,
                          message(Tool, request_tool_focus, Obj, @on),
                          @default, @on,
                          DI?style \== header)
              , menu_item(source,
                          message(Tool, request_source, Obj),
                          @default, @off,
                          and(message(Obj, has_send_method, has_source),
                              message(Obj, has_source)))
              , menu_item(spy,
                          message(Obj, break, full, @on),
                          @default, @off,
                          and(message(Obj, has_send_method, break),
                              Obj?break == @off))
              , menu_item(nospy,
                          message(Obj, break, full, @off),
                          @default, @off,
                          and(message(Obj, has_send_method, break),
                              Obj?break == @on))
              , menu_item(trace,
                          message(Obj, trace, full, @on),
                          @default, @off,
                          and(message(Obj, has_send_method, trace),
                              Obj?trace == @off))
              , menu_item(notrace,
                          message(Obj, trace, full, @off),
                          @default, @on,
                          and(message(Obj, has_send_method, trace),
                              Obj?trace == @on))
              ]),
    ifmaintainer((send_list(P, append,
              [ new(CM, menu_item(class,
                                  end_group := @on)),
                menu_item(relate,
                          message(Tool, request_relate, Obj),
                          @default, @off,
                          and(Manual?edit_mode == @on,
                              Selection \== @nil,
                              Selection \== Obj,
                              not(message(Selection, man_related,
                                          see_also, Obj))))
              , menu_item(unrelate,
                          message(Tool, request_unrelate, Obj),
                          @default, @off,
                          and(Manual?edit_mode == @on,
                              Selection \== @nil,
                              or(message(Obj, man_related,
                                         see_also, Selection),
                                 message(Selection, man_related,
                                         see_also, Obj))))
              , menu_item(inherit,
                          message(Tool, request_inherit, Obj),
                          @default, @off,
                          and(Manual?edit_mode == @on,
                              Selection \== @nil,
                              Selection \== Obj,
                              not(message(Selection, man_related,
                                          inherit, Obj))))
              , menu_item(uninherit,
                          message(Tool, request_uninherit, Obj),
                          @default, @off,
                          and(Manual?edit_mode == @on,
                              Selection \== @nil,
                              message(Obj, man_related,
                                      inherit, Selection)))
              ]),

        ClassifyTab = @man_classification,

        send(CM, popup, new(CP, popup(class))),
        send(CP, show_current, @on),
        send(CP, update_message,
         message(CP, selection,
                 ?(ClassifyTab, member, Obj?man_id))),
        forall(man_classification(T, L),
           send(CP, append,
                menu_item(T,
                          and(message(ClassifyTab, append, Obj?man_id, T),
                              message(ClassifyTab, modified, @on)),
                          L))))).


                /********************************
                *         COMMUNICATION         *
                ********************************/

selected(S, Obj:object*) :->
    "Set selection to requested object"::
    (   Obj == @nil
    ->  send(S, selection, @nil)
    ;   get(S?dict, find, @arg1?object == Obj, Di)
    ->  send(S, selection, Di),
        send(S, normalise, Di)
    ;   send(S, selection, @nil)
    ).


release_selection(S) :->
    "Unselect all objects"::
    send(S, selection, @nil).


                /********************************
                *        FILL THE BROWSER       *
                ********************************/

append_card(S, What:object) :->
    "Append a single card"::
    send(S, append,
         dict_item(What?(S?displayed_attribute), @default, What)).


append_group(S, Index:int, Group:name, Members:chain) :->
    "Append group of cards"::
    (   get(@manual, module, groups, @on, Module),
        get(Module?id_table, member, Group, GroupCard),
        get(GroupCard, summary, Summary),
        Summary \== @nil
    ->  new(Label, string('%d\t%s\t%s', Index, Group, Summary))
    ;   new(Label, string('%d\t%s', Index, Group))
    ),
    send(S, append,
         dict_item(Group, Label, style := header, object := Members)),
    send(Members, for_all,
         message(S, append_card, @arg1)).


members(S, Matches:chain) :->
    "Display chain of cards"::
    send(S, clear),
    (   send(Matches, empty)
    ->  send(S, report, warning, 'No match')
    ;   send(S, report, progress, 'Grouping ...'),
        group_objects(Matches, Groups),
        send(S, report, done),
        new(Index, number(1)),
        send(Groups, for_all,
             and(message(S, append_group, Index, @arg1?name, @arg1?value),
                 message(Index, plus, 1))),
        (   get(S?frame, manual, Manual),
            Manual \== @nil
        ->  send(S, selected, Manual?selection)
        ;   true
        )
    ).


update(S, What:object) :->
    "Update selection for object"::
    get(S, displayed_attribute, Att),
    get(S?members, find_all, @arg1?object == What, DictItems),
    send(DictItems, for_all, message(@arg1, key, @arg1?object?Att)).


                /********************************
                *            CHANGES            *
                ********************************/

update_card(S, Obj:object) :->
    "Update the value for specified card"::
    (   get(S?dict, find, @arg1?object == Obj, Di)
    ->  send(Di, key, Obj?(S?displayed_attribute))
    ;   true
    ).


:- pce_end_class.
