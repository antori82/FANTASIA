/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org/packages/xpce/
    Copyright (c)  2001-2018, University of Amsterdam
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

:- module(prolog_ide_stack,
          [ display_stack/3             % +Window, +Call, +Choice
          ]).
:- use_module(library(pce)).
:- autoload(clause,[predicate_classification/2]).
:- autoload(gui,[in_debug_thread/2,prolog_frame_attribute/4]).
:- autoload(util,[thread_self_id/1]).
:- use_module(library(debug),[assertion/1,debug/3]).
:- autoload(library(lists),[member/2,nth1/3]).
:- autoload(library(pce_util),[default/3]).
:- autoload(library(prolog_clause),[predicate_name/2]).
:- autoload(library(sort),[predsort/3]).
:- autoload(library(system),[system_module/0]).

:- system_module.

%!  display_stack(+StackWindow, +CallList, +ChoiceList) is det.
%
%   Display parent environments and choicepoints.

running_in_pce_thread :-
    pce_thread(Pce),
    thread_self_id(Pce).

display_stack(Window, Call, Choice) :-
    assertion(running_in_pce_thread),
    get(@pce, convert, normal, font, Font),
    get(Font, height, FH),
    merge_choices(Choice, Call, AllFrames),
    in_debug_thread(Window, level_tag_frames(AllFrames, Tagged)),
    keysort(Tagged, SortedByLevel),
    assign_y(SortedByLevel, 0, FH+4, Rows),
    display_levels(Rows, Choice, Window),
    link_parents(Call, Window),
    Call = [Current|_],
    (   Choice = [FirstChoice|_],
        same_frame(Current, FirstChoice)
    ->  link_choices(Choice, Window)
    ;   link_choices([Current|Choice], Window)
    ),
    send(Window, compute),
    send(Window, scroll_vertical, goto, file, 1000).

same_frame(frame(F, _), frame(F, _)).

merge_choices([], Call, Call).
merge_choices([C0|CT], Call, T) :-
    member(C, Call),
    same_frame(C0, C),
    !,
    merge_choices(CT, Call, T).
merge_choices([C0|CT], Call, [C0|T]) :-
    merge_choices(CT, Call, T).

%!  level_tag_frames(+Frames, -TaggedFrames) is det.
%
%   Tag each frame with its recursion level.  Must run in the context
%   of the debugged thread.

level_tag_frames([], []).
level_tag_frames([H|T], [Level-H|LT]) :-
    frame_level(H, Level),
    level_tag_frames(T, LT).

frame_level(frame(F, _), L) :-
    prolog_frame_attribute(F, level, L).

%!  assign_y(+TaggedFrames, +Y0, +FrameHeight, -Rows) is det.
%
%   Combine all frames (tagged with level) of the same level.
%
%   @param Rows     List of Y-ListOfFrames

assign_y([], _, _, []).
assign_y([L0-F0|Frames], Y, FH, [Y-[F0|T0]|T]) :-
    same_level(L0, Frames, T0, RFrames),
    NY is Y + FH,
    assign_y(RFrames, NY, FH, T).

same_level(L, [L-F0|T], [F0|FT], R) :-
    !,
    same_level(L, T, FT, R).
same_level(_, T, [], T).

display_levels([], _, _).
display_levels([Y-Frames|T], Choice, Window) :-
    predsort(cmpframes(Choice), Frames, SortedFrames),
    debug(gtrace(stack), 'Sorted frames: ~p', [SortedFrames]),
    SortedFrames = [frame(Frame, PC)|_],
    prolog_frame_attribute(Window, Frame, level, Level),
    send(Window, display, new(Txt,text(Level, left, normal)), point(5, Y)),
    get(Txt?font, ex, Ex),
    (   PC = choice(_)
    ->  X0 is 4*Ex + 20*Ex
    ;   X0 is 4*Ex
    ),
    display_frames(SortedFrames, Window, X0, Y),
    display_levels(T, Choice, Window).


cmpframes(Choice, Result, frame(Fr1, choice(_)), frame(Fr2, choice(_))) :-
    !,
    nth1(I1, Choice, frame(Fr1, choice(_))),
    nth1(I2, Choice, frame(Fr2, choice(_))),
    compare(Result, I1, I2).
cmpframes(_, <, _, frame(_, choice(_))) :- !.
cmpframes(_, >, frame(_, choice(_)), _) :- !.
cmpframes(_, Result, F1, F2) :-
    compare(Result, F1, F2).

display_frames([], _, _, _).
display_frames([F|T], Window, X, Y) :-
    v_stack_frame(Window, F, V),
    send(V, set, X, Y),
    send(Window, append, V),
    get(@pce, convert, normal, font, Font),
    get(Font, ex, Ex),
    X2 is X + 20*Ex,
    display_frames(T, Window, X2, Y).


v_stack_frame(Window, frame(Frame, choice(CH)), V) :-
    !,
    frame_label(Window, Frame, Label),
    new(V, prolog_stack_frame(Window, Frame, Label, choice(CH), choicepoint)).
v_stack_frame(Window, frame(Frame, PC), V) :-
    frame_label(Window, Frame, Label),
    frame_style(Window, Frame, PC, Style),
    new(V, prolog_stack_frame(Window, Frame, Label, PC, Style)).

frame_label(Window, Frame, Label) :-
    prolog_frame_attribute(Window, Frame, goal,  Goal),
    predicate_name(user:Goal, Label).

frame_style(Window, Frame, PC, Style) :-
    integer(PC),
    !,
    prolog_frame_attribute(Window, Frame, has_alternatives, A),
    det_style(A, Style).
frame_style(Window, Frame, _, Style) :-
    in_debug_thread(Window, frame_predicate_class(Frame, Style)).

%!  frame_predicate_class(+Frame, -Style) is det.
%
%   Use Style for displaying  Frame.  Computed   as  a  whole in the
%   debugged thread to avoid exchanging the goal between threads.

frame_predicate_class(Frame, Style) :-
    prolog_frame_attribute(Frame, goal, Goal),
    predicate_classification(Goal, Style).

det_style(false, deterministic).
det_style(true,  choicepoint).

link_parents([H1,H2|T], W) :-
    !,
    H1 = frame(F1, PC1),
    H2 = frame(F2, PC2),
    get(W, member, F1, PC1, V1),
    get(W, member, F2, PC2, V2),
    new(_, hyper(V1, V2, parent, child)),
    link_parents([H2|T], W).
link_parents(_, _).

link_choices([H1,H2|T], W) :-
    !,
    H1 = frame(F1, _),
    H2 = frame(F2, _),
    get(W, member, F1, V1),
    get(W, member, F2, V2),
    get(V1, pc, PC1),
    get(V2, pc, PC2),
    (   (   PC1 == choice
        ;   PC2 == choice
        )
    ->  Handle = @default
    ;   Handle = east
    ),
    new(_, connection(V1, V2, @prolog_choice_link, Handle)),
    link_choices([H2|T], W).
link_choices(_, _).

clean(P) :-
    send(P?graphicals, for_all,
         if(message(@arg1, instance_of, text),
            message(@prolog, clean_level, @arg1))).

clean_level(Text) :-
    get(@pce, convert, Text?string, int, Level),
    (   get(Text?device?graphicals, find,
            and(message(@arg1, instance_of, prolog_stack_frame),
                @arg1?level == Level),
            _)
    ->  true
    ;   free(Text)
    ).

                 /*******************************
                 *       STACK-VIEW WINDOW      *
                 *******************************/

:- pce_begin_class(prolog_stack_view, picture,
                   "Overview of the parent stack-frames").

variable(members,       hash_table,  get, "Frame --> Visualiser table").

class_variable(background, colour, white).
class_variable(colour,     colour, black).

initialise(B) :->
    assertion(running_in_pce_thread),
    get(@pce, convert, normal, font, Font),
    get(Font, ex, Ex),
    send_super(B, initialise, size := size(20 * Ex, 100)),
    send(B, label, 'Stack'),
    send(B, hor_stretch, 100),
    send(B, hor_shrink, 100),
    send(B, slot, members, new(chain_table)).

clean(B) :->
    clean(B).

clear(B) :->
    send(B?graphicals, for_all, message(@arg1, destroy)).


member(B, F:int, Location:[prolog], V:prolog_stack_frame) :<-
    "Find visualiser from frame"::
    get(B, members, Table),
    get(Table, member, F, Chain),
    (   Location == @default
    ->  get(Chain, head, V)
    ;   Location = choice(CHP)
    ->  get(Chain, find, @arg1?choice == CHP, V)
    ;   get(Chain, find, @arg1?pc == Location, V)
    ).


append(B, V:prolog_stack_frame) :->
    send(B, display, V),
    get(V, frame_reference, Frame),
    send(B?members, append, Frame, V).


up(B, Times:[int]) :->
    "Select (Nth) parent"::
    default(Times, 1, N),
    get(B, selection, Fr),
    get(B, member, Fr, V),
    (   N < 0
    ->  D is -N,
        step(D, B, child,  V, V2)
    ;   step(N, B, parent, V, V2)
    ),
    send(V2, select, @on).


step(0, _, _, V, V) :- !.
step(N, B, child, V, V2) :-
    get(V, hypered, child, Ch),
    !,
    (   get(Ch, frame_reference, Frame),
        prolog_frame_attribute(B, Frame, goal, Goal),
        predicate_property(user:Goal, foreign),
        get(Ch, hypered, child, Ch2)
    ->  NN is N - 1,
        step(NN, B, child, Ch2, V2)
    ;   NN is N - 1,
        step(NN, B, child, Ch, V2)
    ).
step(N, B, parent, V, V2) :-
    get(V, frame_reference, Frame),
    in_debug_thread(B, prolog_parent(Frame, Parent, PC)),
    (   debug(gtrace(stack), 'Looking for parent ~d, PC=~d', [Parent, PC]),
        get(B, member, Parent, PC, V1)
    ->  true
    ;   v_stack_frame(B, frame(Parent, PC), V1),
        send(V1, compute),
        send(V1, do_set, V?x, V?y - V1?height),
        new(_, hyper(V, V1, parent, child)),
        send(V?device, append, V1)
    ),
    !,
    NN is N - 1,
    step(NN, B, parent, V1, V2).
step(_, B, parent, V, V) :-
    !,
    send(B, report, warning, 'Top frame').
step(_, B, child, V, V) :-
    !,
    send(B, report, warning, 'Deepest frame').

%!  prolog_parent(+Frame, -Parent, -PC)
%
%   Find parent executing Prolog. If our  direct parent is a foreign
%   frame, keep walking up. Same  if  the   parent  appears  to be a
%   hidden frame, we keep walking up for   a user-frame. Must run in
%   debugged thread.

prolog_parent(Frame, Parent, PC) :-
    prolog_frame_attribute(Frame, pc, PC0),
    !,
    prolog_frame_attribute(Frame, parent, MyParent),
    (   prolog_frame_attribute(MyParent, hidden, false)
    ->  Parent = MyParent,
        PC = PC0
    ;   prolog_parent(MyParent, Parent, PC)
    ).
prolog_parent(Frame, Parent, PC) :-
    prolog_frame_attribute(Frame, parent, Super),
    prolog_parent(Super, Parent, PC).

down(B, Times:[int]) :->
    "Select (Nth) child"::
    default(Times, 1, N),
    NN is -N,
    send(B, up, NN).

selection(B, What:'int|prolog_stack_frame', PC:location=[prolog]) :->
    "Select the given frame"::
    (   integer(What)
    ->  (   get(B, member, What, PC, V)
        ->  send_super(B, selection, V)
        ;   send_super(B, selection, @nil)
        )
    ;   send_super(B, selection, What)
    ).

selection(B, Fr:int) :<-
    "Return selected frame visualiser"::
    get_super(B, selection, Chain),
    get(Chain, size, 1),
    get(Chain, head, Gr),
    get(Gr, frame_reference, Fr).

frame_finished(B, Fr:int) :->
    get(B, members, Table),
    get(Table, member, Fr, Frames),
    (   send(Frames, empty)
    ->  true
    ;   send(Frames, for_all, message(@arg1, destroy)),
        clean(B)
    ).

:- pce_end_class.


                 /*******************************
                 *       FRAME VISUALISER       *
                 *******************************/

:- pce_begin_class(prolog_stack_link, line).

class_variable(colour, colour, black).

:- pce_end_class.

:- pce_global(@prolog_choice_link,
              new(link(link, link, prolog_stack_link(arrows := second)))).

:- pce_begin_class(prolog_stack_frame, figure,
                   "Frame of the stack-view").

handle(-5,  h/2, link, east).
handle(w+5, h/2, link, west).

resource(Name, image, image(File)) :-
    style_image(_, File),
    file_name_extension(Name, xpm, File).

style_image(deterministic,      'det.xpm').
style_image(choicepoint,        'ndet.xpm').
style_image(built_in,           'builtin.xpm').
style_image(foreign,            'foreign.xpm').
style_image(dynamic,            'dynamic.xpm').
style_image(undefined,          'undefined.xpm').
style_image(transparent,        'meta.xpm').
style_image(user,               'user.xpm').

variable(frame_reference,  int,         get, "Reference of Prolog frame").
variable(pc,               'int|name',  get, "Location in the frame").
variable(choice,           int*,        get, "Id of choice-point").
variable(frame_level,      int,         get, "Nesting of the frame").

class_variable(background, colour, white).
class_variable(colour,     colour, black).

:- pce_global(@prolog_stack_frame_recogniser,
              new(click_gesture(left, '', single,
                                message(@receiver, select)))).

initialise(D, Window:window, Frame:int, Label:char_array,
           Location:prolog, Style:name) :->
    send_super(D, initialise),
    send(D, background, ?(D, class_variable_value, background)),
    send(D, colour, ?(D, class_variable_value, colour)),
    send(D, border, 3),
    send(D, shadow, 1),
    send(D, pen, 1),
    style_image(Style, Image),
    file_name_extension(Resource, _, Image),
    send(D, display, new(B, bitmap(resource(Resource)))),
    send(D, display, text(Label, left, normal), point(B?right_side, 0)),
    send(D, slot, frame_reference, Frame),
    (   Location = choice(CH)
    ->  send(D, slot, pc, choice),
        send(D, slot, choice, CH)
    ;   send(D, slot, pc, Location)
    ),
    prolog_frame_attribute(Window, Frame, level, Level),
    send(D, slot, frame_level, Level).

unlink(D) :->
    (   get(D, device, Dev),
        Dev \== @nil,
        get(Dev, members, Table),
        send(Table, delete, D?frame_reference)
    ->  true
    ;   true
    ),
    send_super(D, unlink).


event(D, Ev:event) :->
    (   send_super(D, event, Ev)
    ;   send(@prolog_stack_frame_recogniser, event, Ev)
    ).


select(D, Show:[bool]) :->
    "Make this frame the selected one"::
    send(D?device, selection, D),
    (   Show \== @off
    ->  get(D, frame_reference, Frame),
        get(D, pc, PC),
        debug(gtrace(stack), '~p: select ~p at PC=~w', [D, Frame, PC]),
        (   PC == choice
        ->  get(D, choice, CH),
            Location = choice(CH)
        ;   Location = PC
        ),
        send(D?frame, show_frame, Frame, Location)
    ;   true
    ).

help_message(D, _What:{tag,summary}, _Ev:[event], Msg:string) :<-
    "Fetch associated help message"::
    get(D, frame_reference, FR),
    get(D, pc, PC),
    new(Msg, string('Frame #%d at PC = %s', FR, PC)).

:- pce_end_class.
