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

:- module(pce_font_item, []).
:- use_module(library(pce)).
:- require([ send_list/2
           , default/3
           ]).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This file defines class font_item.   Class   font_item  is a dialog-item
specialised in entering font-values.  It consists   of three cycle menus
for the family, style and point-size of the font.  The interface is very
similar to the interface of  the   built-in  dialog-items  such as class
text_item and friends.  Summary:

        <->selection:   Access to current font
        <->default:     Default value, which may be function (->restore)
        ->apply:        Execute the item

Though a bit complicated due to all  interaction between the items, this
class may be used as an   example/template  for defining compound dialog
items.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- pce_begin_class(font_item, label_box, "Dialog item for defining a font").

variable(value_set,     chain,          get,    "List of fonts").

initialise(FI, Name:[name],
           Default:'[font|function]', Message:[code]*,
           ValueSet:[chain]) :->
    "Create font-selector"::
    default(Name, font, Nm),
    default(Default, normal, Def),
    send(FI, send_super, initialise, Nm, Message),
    send(FI, gap, size(5,0)),
    send(FI, alignment, column),
    send(FI, append,
         new(Fam, menu(family, cycle, message(FI, family, @arg1)))),
    send(FI, append,
         new(Wgt, menu(weight, cycle, message(FI, weight, @arg1))), right),
    send(FI, append,
         new(Pts, menu(points, cycle, message(FI, points, @arg1))), right),
    send(Fam, show_label, @off),
    send(Wgt, show_label, @off),
    send(Pts, show_label, @off),
    send(FI, value_set, ValueSet),
    send(FI, default, Def).

clear(_) :->
    true.

active(FI, Val:bool) :->
    send(FI?graphicals, for_all, message(@arg1, active, Val)).


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Assign the item a value set (set of   fonts  to choose from).  This will
make entries in the three menus.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

value_set(FI, ValueSet:[chain]) :->
    "Define set of available fonts"::
    (   ValueSet == @default
    ->  new(Set, chain),
        send(@fonts, for_all, message(Set, append, @arg2))
    ;   Set = ValueSet
    ),
    send(FI, slot, value_set, Set),
    get(FI, member, family, Fam),
    get(FI, member, weight, Wgt),
    get(FI, member, points, Pts),
    send_list([Fam, Wgt, Pts], clear),
    send(Set, for_all,
         and(if(not(?(Fam, member, @arg1?family)),
                message(Fam, append, @arg1?family)),
             if(not(?(Wgt, member, @arg1?style)),
                message(Wgt, append, @arg1?style)),
             if(not(?(Pts, member, @arg1?points)),
                message(Pts, append, @arg1?points)))),
    send(Fam, sort),
    send(Wgt, sort),
    send(Pts, sort, ?(@arg1?value, compare, @arg2?value)).


                 /*******************************
                 *            CHANGES           *
                 *******************************/

modified_item(_FI, _Gr:graphical, _Modified:bool) :->
    fail.

forward(FI) :->
    send(FI, modified, @on),
    (   send(FI?device, modified_item, FI, @on)
    ->  true
    ;   send(FI, apply)
    ).


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
pick_active(+Menu)  changes  the  selection  of  a  menu  to  an  active
menu-item close to the current one of the current one is not active.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

pick_active(M) :-
    get(M, active_item, M?selection, @on),
    !.
pick_active(M) :-
    get(M, selection, S),
    get(M, member, S, MI),
    get(M, members, Chain),
    (   get(Chain, find, @arg1?active == @on, _)
    ->  get(Chain, index, MI, I),
        pick_active(Chain, I, 0, MIA),
        (   MIA == MI
        ->  true
        ;   send(M, selection, MIA)
        )
    ;   true
    ).


pick_active(Chain, I, Offset, MI) :-
    (   Offset mod 2 =:= 1
    ->  Idx is I + Offset//2
    ;   Idx is I - Offset//2
    ),
    get(Chain, nth1, Idx, MI),
    get(MI, active, @on),
    !.
pick_active(Chain, I, Offset, MI) :-
    NewOffset is Offset+1,
    pick_active(Chain, I, NewOffset, MI).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
After some menu has changed, this  method activates all styles available
to the current family  and  all   point-sizes  available  to the current
family/style combination.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

activate(FI) :->
    get(FI, member, family, Fam),
    get(FI, member, weight, Wgt),
    get(FI, member, points, Pts),
    get(FI, value_set, ValueSet),
    get(Fam, selection, CFam),
    new(Wgts, chain),
    new(Ptss, chain),
    send(ValueSet, for_all,
         if(@arg1?family == CFam, message(Wgts, append, @arg1?style))),
    send(Wgt?members, for_all,
         message(@arg1, active,
                 when(message(Wgts, member, @arg1?value), @on, @off))),
    pick_active(Wgt),
    get(Wgt, selection, CWgt),
    send(ValueSet, for_all,
         if(and(@arg1?family == CFam,
                @arg1?style == CWgt),
            message(Ptss, append, @arg1?points))),
    send(Pts?members, for_all,
         message(@arg1, active,
                 when(message(Ptss, member, @arg1?value), @on, @off))),
    pick_active(Pts).


family(FI, _Fam:name) :->
    "User changed family cycle"::
    send(FI, activate),
    send(FI, forward).

weight(FI, _Wgt:name) :->
    send(FI, activate),
    send(FI, forward).

points(FI, _Pts:int) :->
    send(FI, forward).


                 /*******************************
                 *  GENERIC DIALOG OPERATIONS   *
                 *******************************/

selection(FI, Font:font) :->
    "Set the selection"::
    get(FI, member, family, Fam),
    get(FI, member, weight, Wgt),
    get(FI, member, points, Pts),
    send(Fam, selection, Font?family),
    send(Wgt, selection, Font?style),
    send(Pts, selection, Font?points),
    send(FI, activate).

selection(FI, Font:font) :<-
    "Get the current font"::
    get(FI, member, family, Fam),
    get(FI, member, weight, Wgt),
    get(FI, member, points, Pts),
    get(Fam, selection, Family),
    get(Wgt, selection, Style),
    get(Pts, selection, Points),
    new(Font, font(Family, Style, Points)).

:- pce_end_class.
