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

:- module(man_module_browser, []).

:- use_module(library(pce)).
:- use_module(util).
:- require([ forall/2
           , member/2
           , send_list/3
           ]).

:- pce_begin_class(man_module_browser(module_name), man_frame).

variable(module,        man_module*,    get,    "Currently viewed module").
variable(create_class,  name*,          both,   "Classname to be created").


initialise(MB, Manual:man_manual, ModuleName:name, CreateClass:[name]*,
               Label:[name]) :->
    "Create from Manual"::
    send(MB, send_super, initialise, Manual, Label),

    new(Browser, man_summary_browser(man_summary, size(90, 15))),
    dialog(Dialog),

    new(Obj, @arg1?object),
    new(EditModeOn, MB?manual?edit_mode == @on),
    ifmaintainer(send_list(Browser?popup, append,
              [ menu_item(rename,
                          message(MB, rename,
                                  Obj, Dialog?name_member?selection),
                          @default, @off,
                          and(EditModeOn,
                              Dialog?name_member?selection \== ''))
              , menu_item(summary,
                          message(MB, summary,
                                  Obj, Dialog?summary_member?selection),
                          @default, @on,
                          and(EditModeOn,
                              Dialog?summary_member?selection \== ''))
              , menu_item(delete,
                          block(message(@display, confirm,
                                        'Delete card %s', Obj?man_name),
                                message(MB, delete, @arg1)),
                          @default, @on,
                          EditModeOn)
              ])),

    send(MB, append, Browser),
    send(Dialog, below, Browser),
    send(MB, edit_mode, Manual?edit_mode),
    send(MB, view, ModuleName, CreateClass).


module_name(MB, Name:name) :<-
    get(MB, module, Module),
    (   Module \== @nil
    ->  get(Module, name, Name)
    ;   Name = '(nil)'
    ).


browser(MB, Browser) :<-
    "Get the browser"::
    get(MB, member, man_summary_browser, Browser).



                /********************************
                *            DIALOG             *
                ********************************/

dialog(D) :-
    new(D, dialog),
    new(MB, D?frame),

    ifmaintainer((
        send(D, append, new(TN, text_item(name,    '', @nil))),
        send(D, append, new(TS, text_item(summary, '',
                                          if(TN?selection \== '',
                                             message(D?create_member,
                                                     execute))))),
        send(TN, length, 15),
        send(TS, length, 40),
        send(D, append, button(create, block(message(MB, create_card,
                                                     TN?selection,
                                                     TS?selection),
                                             message(TN, clear),
                                             message(TS, clear),
                                             message(TN, caret)))))),

    send(D, append, button(help,   message(MB, help))),
    send(D, append, button(quit,   message(MB, quit))).



                /********************************
                *          COMMUNICATION        *
                ********************************/

toggle_edit_mode(MB) :->
    "Toggle between edit and browse mode"::
    (   get(MB?manual, edit_mode, @on)
    ->  send(MB?manual, edit_mode, @off)
    ;   send(MB?manual, edit_mode, @on)
    ).


edit_mode(MB, Val:bool) :->
    "Switch edit mode on/off"::
    get(MB, dialog_member, Dialog),
    forall(member(Name, [create, name, summary]),
           (   get(Dialog, member, Name, Item)
           ->  send(Item, active, Val)
           ;   true
           )).


selected(MB, Obj:object*) :->
    "Set the selection"::
    send(MB?browser, selected, Obj).


release_selection(MB) :->
    send(MB?browser, selected, @nil).


                /********************************
                *            FILLING            *
                ********************************/

view(MB, ModuleName:name, ClassName:name*) :->
    "Connect to a specified module"::
    get(MB?manual, module, ModuleName, @on, Module),
    send(MB, slot, module, Module),
    (   ClassName == @default
    ->  send(MB, slot, create_class, @nil)
    ;   send(MB, slot, create_class, ClassName)
    ),
    get(MB, browser, Browser),
    send(Module?id_table, for_some,
         message(Browser, append_card, @arg2)),
    send(Browser, sort).


                /********************************
                *            EDITING            *
                ********************************/

create_card(MB, Name:string, Summary:string) :->
    "Add a card to the module"::
    send(Name, strip),
    (   get(Name, size, 0)
    ->  send(@display, inform, 'Please enter a card name first')
    ;   get(MB, create_class, ClassName),
        (   ClassName \== @nil
        ->  Term =.. [ClassName, MB?module, Name],
            new(Card, Term),
            send(Card, store, summary, Summary),
            send(MB?browser, append_card, Card)
        ;   send(@display, inform, 'What class?')
        )
    ).


rename(MB, Card:man_card, Name:string) :->
    "Change name to value in dialog"::
    send(Name, strip),
    (   get(Name, size, 0)
    ->  send(@display, inform, 'Please enter a card name first')
    ;   send(Card, store, name, Name),
        send(MB?browser, update_card, Card)
    ).


summary(MB, Card:man_card, Summary:string) :->
    "Change summary to value in dialog"::
    send(Summary, strip),
    (   get(Summary, size, 0)
    ->  send(@display, inform, 'Please enter a card name first')
    ;   send(Card, store, summary, Summary),
        send(MB?browser, update_card, Card)
    ).


delete(_MB, DI:dict_item) :->
    "Delete from module"::
    get(DI, object, Card),
    send(DI, free),
    send(Card, free).

:- pce_end_class.
