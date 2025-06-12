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

:- module(drag_and_drop, []).
:- use_module(library(pce)).
:- require([ default/3
           , ignore/1
           ]).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Define a gesture that allows to  `drag-and-drop' objects.  The target on
which to drop should understand the method  ->drop, which will be called
with the dropped graphical  as  an   argument.   If  may  also implement
->preview_drop, which will be called to   provide visual feedback of the
drop that will take place when the button is released here.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- pce_begin_class(drag_and_drop_gesture, gesture,
                   "Drag and drop command-gesture").

variable(target,        graphical*,     get,  "Drop target").
variable(warp,          bool,           both, "Pointer in center?").
variable(offset,        point,          get,  "Offset X-y <->caret pointer").
variable(get_source,    function*,      both, "Function to map the source").
variable(source,        any,            get,  "Current source").
variable(active_cursor, cursor*,        get,  "@nil: activated").

resource(warp,   bool,        '@on',
         "Pointer in center?").
resource(button, button_name, left,
         "Button on which gesture operates").
resource(cursor, cursor*,     cross_reverse,
         "Cursor to display.  @nil: use graphical").

active_distance(_G, D) :-
    D > 5.

initialise(G, But:button=[button_name],
           M:modifier=[modifier], W:warp=[bool],
           S:get_source=[function]*) :->
    "Create from button, modifiers and warp"::
    send(G, send_super, initialise, But, M),
    default(W, resource(G, warp), Warp),
    default(S, @nil, GS),
    send(G, warp, Warp),
    send(G, get_source, GS),
    send(G, slot, offset, new(point)).


verify(_G, Ev:event) :->
    "Only accept as single-click"::
    get(Ev, multiclick, single).


initiate(G, Ev:event) :->
    "Change the cursor"::
    get(Ev, receiver, Gr),
    get(Ev, position, Gr, Offset),
    send(G?offset, copy, Offset),
    send(G, set_source, Ev),
    get(G, cursor, Gr, Cursor),
    send(G, slot, active_cursor, Cursor).


set_source(G, Ev:event) :->
    "Find source from event"::
    get(Ev, receiver, Gr),
    get(G, get_source, Function),
    (   Function == @nil
    ->  send(G, slot, source, Gr)
    ;   get(Function, '_forward', Gr, Source),
        send(G, slot, source, Source)
    ).


cursor(G, Gr, Cursor:cursor) :<-
    "Create cursor from the graphical"::
    (   get(G, slot, cursor, C0),
        (   C0 == @default
        ->  get(G, resource_value, cursor, Cursor)
        ;   Cursor = C0
        ),
        Cursor \== @nil
    ->  true
    ;   get(Gr?area, size, size(W, H)),
        (   get(G, warp, @on)
        ->  new(HotSpot, point(W/2, H/2)),
            send(Gr, pointer, HotSpot),
            send(G?offset, copy, HotSpot)
        ;   get(G, offset, HotSpot)
        ),
        new(BM, image(@nil, W, H)),
        send(BM, draw_in, Gr, point(0,0)),
        send(BM, or, image('cross.bm'), point(HotSpot?x-8, HotSpot?y-8)),
        new(Cursor, cursor(@nil, BM, @default, HotSpot))
    ).


drag(G, Ev:event) :->
    "Find possible ->drop target"::
    (   get(G, active_cursor, Cursor),
        Cursor \== @nil
    ->  (   get(Ev, click_displacement, D),
            active_distance(G, D)
        ->  send(Ev?window, focus_cursor, Cursor),
            send(G, slot, active_cursor, @nil),
            send(G, drag, Ev)
        ;   true
        )
    ;   get(G, source, Source),
        (   get(Ev, inside_sub_window, Frame),
            get(Ev, inside_sub_window, Frame, Window),
            get(Window, find, Ev,
                and(@arg1 \== Source,
                    or(and(G?target == @arg1,
                           message(G, move_target, Ev)),
                       message(G, target, Source, Ev, @arg1))),
                _Gr)
        ->  true
        ;   send(G, target, Source, @nil, @nil)
        )
    ).


:- pce_global(@dd_dummy_point, new(point)).

move_target(G, Ev:event) :->
    "The user is dragging the object over a drop-zone"::
    get(G, target, Target),
    get(G, source, Source),
    (   get(Target, send_method, preview_drop, tuple(_, Method)),
        get(Method, argument_type, 1, Type),
        get(Type, check, Source, Src),
        get(Method, argument_type, 2, PosType),
        send(PosType, validate, @dd_dummy_point)
    ->  get(Ev, position, Target, Pos),
        get(Pos, copy, P2),
        send(P2, minus, G?offset),
        send(Target, preview_drop, Src, P2)
    ;   true
    ).


target(G, Source:any, Ev:event*, Gr:graphical*) :->
    "Make the given object the target"::
    (   Gr == @nil
    ;   get(Gr, is_displayed, @on),
        send(Gr, has_send_method, drop)
    ),
    ignore((get(G, target, Old),
            send(Old, has_send_method, preview_drop),
            send(Old, preview_drop, @nil))),
    (   get(Gr, send_method, preview_drop, tuple(_, Method)),
        get(Method, argument_type, 1, Type),
        get(Type, check, Source, Src)
    ->  (   get(Method, argument_type, 2, PosType),
            send(PosType, validate, @dd_dummy_point)
        ->  get(Ev, position, Gr, Pos),
            get(Pos, copy, P2),
            send(P2, minus, G?offset),
            send(Gr, preview_drop, Src, P2)
        ;   send(Gr, preview_drop, Src)
        )
    ;   true
    ),
    send(G, slot, target, Gr).


terminate(G, Ev:event) :->
    "->drop to <-target"::
    (   get(G, active_cursor, Cursor),
        Cursor \== @nil
    ->  send(G, slot, active_cursor, @nil),
        send(G, cancel)
    ;   get(G, slot, target, Target),
        send(Ev?window, focus_cursor, @nil),
        get(G, source, Source),
        send(G, slot, source, @nil),
        (   Target == @nil
        ->  true
        ;   send(G, target, Source, @nil, @nil),
            get(Target, send_method, drop, tuple(_, Method)),
            get(Method, argument_type, 1, T1),
            get(T1, check, Source, Src),
            get(Target, display, Display),
            (   get(Method, argument_type, 2, Type),
                send(Type, validate, @dd_dummy_point)
            ->  get(Ev, position, Target, Pos),
                get(Pos, copy, P2),
                send(P2, minus, G?offset),
                send(Display, busy_cursor),
                ignore(send(Target, drop, Src, P2)),
                send(Display, busy_cursor, @nil)
            ;   send(Display, busy_cursor, @default),
                ignore(send(Target, drop, Src)),
                send(Display, busy_cursor, @nil)
            )
        )
    ).

:- pce_end_class.
