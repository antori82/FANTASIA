/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@cs.vu.nl
    WWW:           http://www.swi-prolog.org/packages/xpce/
    Copyright (c)  1985-2017, University of Amsterdam,
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

:- module(emacs_frame, []).
:- use_module(library(pce)).
:- use_module(library(tabbed_window)).
:- use_module(prompt).
:- require([ between/3,
             atomic_list_concat/2,
             default/3,
             send_list/2,
             send_list/3
           ]).

resource(mode_x_icon,   image, image('32x32/doc_x.xpm')).


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
@current_emacs_mode is a variable  pointing   to  the current emacs-mode
object.  Pushed by `emacs_key_binding  ->fill_arguments_and_execute' and
various others.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- pce_global(@current_emacs_mode, new(var)).

:- pce_begin_class(emacs_tabbed_window, tabbed_window,
                   "Emacs editor tabs").

:- pce_global(@emacs_tab_popup, make_emacs_tab_popup).

make_emacs_tab_popup(P) :-
    new(P, popup),
    Tab = @arg1,
    Cond = (Tab?device?graphicals?size \== 1),
    send_list(P, append,
              [ menu_item(close_tab,
                          message(Tab, destroy),
                          condition := Cond),
                menu_item(close_other_tabs,
                          message(Tab, close_other_tabs),
                          condition := Cond),
                menu_item(move_to_new_window,
                          message(Tab, untab),
                          condition := Cond)
              ]).

current(TW, Window:window) :->
    "Make the given window the current one"::
    send_super(TW, current, Window),
    get(Window, text_buffer, TB),
    (   get(TW, frame, Frame),
        send(TB, check_modified_file, Frame),
        send(Frame, has_send_method, setup_mode)
    ->  send(TW?frame, setup_mode, Window)
    ;   send(TB, check_modified_file)
    ).

frame_window(_TW, Window:window, _Name:name, _Rank:'1..', Frame:frame) :<-
    "After un-tabbing, give the window a new frame"::
    new(Frame, emacs_frame(Window)).

empty(TW) :->
    "Last window-tab disappeared"::
    send(TW?frame, destroy).

:- pce_end_class.


:- pce_begin_class(emacs_frame, frame, "Frame for the PceEmacs editor").

class_variable(size,         size, size(80,32), "Size of text-field").
class_variable(prompt_style, {mini_window,dialog}, dialog, "How to prompt").

initialise(F, For:'emacs_buffer|emacs_view') :->
    "Create window for buffer"::
    send(F, send_super, initialise, 'PceEmacs', application := @emacs),
    send(F, icon, image(resource(mode_x_icon))),
    send(F, done_message, message(F, quit)),
    send(F, append, new(MBD, emacs_mode_dialog)),

    send(new(TW, emacs_tabbed_window), below, MBD),
    send(TW, label_popup, @emacs_tab_popup),
    send(new(emacs_mini_window), below, TW),

    (   send(For, instance_of, emacs_view)
    ->  V = For,
        get(For, text_buffer, B)
    ;   B = For,
        get(F, class_variable_value, size, Size),
        new(V, emacs_view(B, Size?width, Size?height))
    ),

    send(TW, append, V),
    send(B, update_label),
    get(V, editor, E),
    send(F, keyboard_focus, V),
    send(F, setup_mode, V),

    send(F, open),

    get(E, mode, Mode),
    ignore(send(Mode, new_buffer)).

quit(F) :->
    "User-initiated quit"::
    get(F, member, emacs_tabbed_window, TW),
    get(TW?members, size, Count),
    (   Count == 1
    ->  send(F, destroy)
    ;   send(F, confirm, 'Close %d tabs?', Count)
    ->  send(F, destroy)
    ;   true
    ).

confirm(F, Format:char_array, Args:any...) :->
    "Confirm centered"::
    new(D, dialog('Confirm action')),
    String =.. [string, Format | Args ],
    send(D, append, label(message, String)),
    send(D, append, button(ok, message(D, return, ok))),
    send(D, append, button(cancel, message(D, return, cancel))),
    send(D, transient_for, F),
    send(D, modal, transient),
    get(D, confirm_centered, F?area?center, Rval),
    send(D, destroy),
    Rval == ok.

editor_event(F, Ev:event) :->
    "Delegate to the mini-window"::
    get(F, member, mini_window, MW),
    send(MW, editor_event, Ev).

input_focus(F, Val:bool) :->
    "Activate the window"::
    send(F, send_super, input_focus, Val),
    (   send(F, unlinking)
    ->  true
    ;   send(F, active, Val)
    ).

on_current_desktop(F) :->
    "True if F for more than half on the current desktop"::
    get(F, area, FArea),
    (   object(FArea, area(-32000, -32000, _, _))
    ->  true                    % MS-Windows iconized
    ;   get(F?display, size, size(DW,DH)),
        get(FArea, intersection, area(0,0,DW,DH), Intersection),
        get(FArea, measure, MA),
        get(Intersection, measure, IA),
        IA > MA/2
    ).

tab(F, B:buffer=emacs_buffer, Expose:expose=[bool]) :->
    "Add new tab holding buffer"::
    get(F, member, emacs_tabbed_window, TW),
    (   get(TW, members, Windows),
        get(Windows, find, @arg1?text_buffer == B, Window)
    ->  (   Expose == @on
        ->  send(TW, on_top, Window)
        ;   true
        )
    ;   send(TW, append, new(V, emacs_view(B)), B?name, Expose),
        send(B, update_label),
        send(F, setup_mode, V)
    ).


buffer(F, B:emacs_buffer) :->
    "Switch to the given emacs buffer"::
    get(F, editor, E),
    send(E, text_buffer, B).


view(F, View:emacs_view) :<-
    "Currently active view"::
    get(F, member, emacs_tabbed_window, TW),
    get(TW, current, View).


editor(F, Editor:emacs_editor) :<-
    "Editor component of the frame"::
    get(F, view, V),
    get(V, editor, Editor).


menu_bar(F, MB:emacs_menu_bar) :<-
    "The menu_bar object at the top"::
    get(F, member, emacs_mode_dialog, D),
    get(D, member, emacs_menu_bar, MB).


mode(F, Mode:emacs_mode) :<-
    "Current mode object of the editor"::
    get(F, editor, E),
    get(E, mode, Mode).


setup_mode(F, V:emacs_view) :->
    "Setup the mode for indicated view"::
    get(V, mode, Mode),
    (   get(Mode, icon, Icon)
    ->  send(F, icon, Icon)
    ;   true
    ),
    get(F, menu_bar, MB),
    ignore(send(V, fill_menu_bar, MB)),
    (   get(V, label, Label)
    ->  send(F, label, Label)
    ;   true
    ).


active(F, Val:bool) :->
    "Indicate active status"::
    get(F, view, View),
    (   Val == @on
    ->  send(@emacs, first, F),
        send(@emacs, selection, View?text_buffer)
    ;   send(@emacs, selection, @nil)
    ).


fit(F) :->
    "Request to fit the contents"::
    (   get(F, attribute, fitted, @on)
    ->  send(F, resize)
    ;   send(F, send_super, fit),
        send(F, attribute, fitted, @on)
    ).


keyboard_focus(F, W:window) :->
    (   send(W, instance_of, view),
        get(F, member, mini_window, MW),
        get(MW, prompter, Prompter), Prompter \== @nil
    ->  send(F, send_super, keyboard_focus, MW)
    ;   send(F, send_super, keyboard_focus, W)
    ).

                 /*******************************
                 *          PROMPTING           *
                 *******************************/

:- pce_global(@prompt_recogniser, make_prompt_binding).

make_prompt_binding(G) :-
    new(G, key_binding(emacs_mini_window_prompter, text_item)),
    send(G, function, 'TAB',  complete),
    send(G, function, 'SPC',  insert_self),
    send(G, function, 'RET',  if(message(@receiver, apply, @on))),
    send(G, function, '\\C-g', and(message(@receiver, keyboard_quit),
                                  message(@receiver?frame, return,
                                          canceled))).

prompt_using(F, Item:dialog_item, Rval:unchecked) :<-
    "Prompt for value in dialog using Item"::
    get(F, view, View),
    get(F, member, mini_window, W),
    get(F, menu_bar, MB),
    send(MB, active, @off),

    send(W, client, View),
    send(W, prompter, Item),
    send(Item, message, message(F, return, ok)),
    (   send(Item, instance_of, text_item)
    ->  send(Item, recogniser, @prompt_recogniser),
        send(Item, value_font, fixed)
    ;   true
    ),
    send(F, keyboard_focus, W),
    get(F, confirm, Return),
    object(F),                      % may be freed!

    (   Return == ok
    ->  get(Item, selection, Rval)
    ;   true
    ),

    send(Item, message, @nil),
    send(Item, lock_object, @on),   % Tricky, but we should leave the
    send(W, prompter, @nil),        % lifetime to the caller
    get(Item, unlock, Item),
    get(F, view, View),
    send(F, keyboard_focus, View),
    send(MB, active, @on),
    Return == ok.

reset(F) :->
    "Remove prompter"::
    send(F, send_super, reset),
    get(F, member, mini_window, W),
    send(W, prompter, @nil),
    get(F, menu_bar, MB),
    send(MB, active, @on).

show_line_number(F, Line:'int|{too_expensive}*') :->
    "Show current line in mini-window"::
    get(F, member, mini_window, W),
    send(W, show_line_number, Line).

:- pce_end_class(emacs_frame).


:- pce_begin_class(emacs_mode_dialog, dialog,
                   "Show menu-bar for mode options").

initialise(D) :->
    send_super(D, initialise),
    send(D, gap, size(0,0)),
    send(D, pen, 0),
    send(D, append, new(emacs_menu_bar)),
    send(D, append, new(TB, tool_bar), right),
    send(TB, reference, point(0,15)),
    send(TB, alignment, right),
    get(@emacs, history, History),
    get(History, button, forward, Forward),
    get(History, button, backward, Backward),
    send_list(TB, append, [Backward,Forward]),
    send_list([Backward,Forward], activate).

resize(D) :->
    send(D, layout, D?area?size).

assign_accelerators(_) :->
    "Accelerators are defined by the window"::
    true.

:- pce_end_class(emacs_mode_dialog).


:- pce_begin_class(emacs_menu_bar, menu_bar,
                   "Top menu bar of the editor").

assign_accelerators(_) :->
    "Accelerators are defined by the window"::
    true.

mode(MB, Mode:emacs_mode) :->
    "Prepare for given mode"::
    get(Mode, mode_menu, ModeMenu),
    send(MB, clear),
    send(ModeMenu, for_all,
         message(MB, append_items, Mode, @arg1?name, @arg1?value)).

append_items(MB, Mode:emacs_mode, Name:name, Entries:chain) :->
    (   get(MB, member, Name, Popup)
    ->  true
    ;   new(Popup, emacs_popup(Name,
                               message(@emacs_mode, noarg_call, @arg1))),
        (   Name == help
        ->  send(MB, append, Popup, right)
        ;   send(MB, append, Popup)
        )
    ),
    send(Entries, for_some, message(Popup, append_item, Mode, @arg1)).

:- pce_end_class(emacs_menu_bar).


:- pce_begin_class(emacs_popup, popup,
                   "Popup for the mode-menu").

class_variable(accelerator_font, font, small).

assign_accelerators(_) :->
    "Accelerators are defined by the window"::
    true.

append_item(P, Mode:emacs_mode, Item:any) :->
    "Append single menu item"::
    (   Item == -
    ->  send(P, append, gap)
    ;   atom(Item)
    ->  send(P, append, new(MI, menu_item(Item))),
        (   accelerator(Item, Mode, Accell)
        ->  send(MI, accelerator, Accell)
        ;   true
        ),
        (   get(Mode, send_method, Item, tuple(_, Impl))
        ->  (   forall((between(1, 10, ArgN),
                    get(Impl, argument_type, ArgN, ArgType)),
                send(ArgType, includes, default))
            ->  true
            ;   send(MI, label, string('%s ...', Item?label_name))
            )
        ;   send(MI, active, @off)
        )
    ;   send(P, append, Item?clone)
    ).

%       accelerator(+Command, +Mode, -Accelerator)
%
%       Copy/cut are hacked due to the tricky combination of CUA and
%       native Emacs mode.

accelerator(copy, _, 'Control-c') :- !.
accelerator(cut,  _, 'Control-x') :- !.
accelerator(Cmd,  Mode, Accell) :-
    get(Mode, bindings, KeyBindings),
    get(KeyBindings, binding, Cmd, Key),
    human_accelerator(Key, Accell).

%       human_accelerator(+Key, -Human)
%
%       Translate XPCE key-sequences in conventional notation.  Should be
%       part of the XPCE kernel someday.

:- dynamic
    accel_cache/2.

human_accelerator(Key, Text) :-
    accel_cache(Key, Text),
    !.
human_accelerator(Key, Text) :-
    new(S, string('%s', Key)),
    send(regex('\\\\C-(.)'), for_all, S,
         message(@arg1, replace, @arg2, 'Control-\\1 ')),
    send(regex('\\\\e'), for_all, S,
         message(@arg1, replace, @arg2, 'Alt-')),
    get(S, value, Text),
    assert(accel_cache(Key, Text)).

:- pce_end_class(emacs_popup).


:- pce_begin_class(emacs_mini_window, dialog, "Prompt and feedback window").

variable(prompter,       dialog_item*,  get,    "Current prompter").
variable(report_count,   number,        get,    "Count to erase report").
variable(report_type,    name*,         both,   "Last type of report").

initialise(D) :->
    send(D, send_super, initialise),
    send(D, slot, report_count, number(0)),
    send(D, gap, size(10, 2)),
    send(D, pen, 0),
    send(D, display, new(R, label(reporter)), point(0, 2)),
    send(R, wrap, clip),
    send(D, display, new(T, text('', right, normal)), point(100, 2)),
    send(T, name, line),
    get(text_item(''), height, MH),
    send(D, height, MH),
    send(D, name, mini_window).

resize(D) :->
    get(D, member, line, Text),
    get(D?area, width, W),
    get(Text, width, TW),
    send(Text, x, W-TW-16).

'_compute_desired_size'(_) :->
    "We have fixed size"::
    true.

client(D, Client:emacs_view) :->
    "Register emacs_view as client"::
    send(D, delete_hypers, client),
    new(_, hyper(D, Client, client, mini_window)).
client(D, Client:emacs_view) :<-
    "Get client emacs_view"::
    get(D, hypered, client, Client).


show_line_number(D, Line:'int|{too_expensive}*') :->
    "Show number of current line"::
    get(D, member, line, Text),
    (   Line == @nil
    ->  send(Text, string, '')
    ;   Line == too_expensive
    ->  send(Text, string, 'Line: ?')
    ;   send(Text, string, string('Line: %d', Line))
    ).


report(D, Type:name, Fmt:[char_array], Args:any ...) :->
    "Report"::
    (   get(D, report_type, ReportType),
        ok_to_overrule(Type, ReportType)
    ->  send(D, report_type, Type),
        get(D, member, reporter, Label),
        get(D, report_count, RC),
        (   Fmt == '', Type == status       % clear
        ->  send(Label, clear),
            send(RC, value, 0)
        ;   (   get(D, prompter, Prompter), Prompter \== @nil
            ->  send(Label, x, Prompter?width + 10)
            ;   send(Label, x, 0)
            ),
            send(Label, displayed, @on),
            Msg =.. [report, Type, Fmt|Args],
            send(Label, Msg),
            send(RC, value, 10)
        )
    ;   true
    ).

ok_to_overrule(_, @nil).
ok_to_overrule(_, status).
ok_to_overrule(_, progress).
ok_to_overrule(_, done).
ok_to_overrule(warning, warning).
ok_to_overrule(inform, _).
ok_to_overrule(error, _).

:- pce_global(@emacs_mini_window_bindings, make_emacs_mini_window_bindings).

make_emacs_mini_window_bindings(B) :-
    new(B, key_binding(emacs_mini_window)),
    send(B, function, '\\en', m_x_next),
    send(B, function, '\\ep', m_x_previous).

editor_event(D, Ev:event) :->
    "Process event typed in the editor"::
    (   get(D, prompter, Prompter),
        Prompter \== @nil
    ->  (   send(@emacs_mini_window_bindings, event, Ev)
        ->  true
        ;   get(D, member, reporter, Reporter),
            send(Reporter, displayed, @off),
            ignore(send(Ev, post, Prompter))
        )
    ;   send(D, report_type, @nil),
        get(D, report_count, RC),
        send(RC, minus, 1),
        (   send(RC, equal, 0)
        ->  send(D, report, status, '')
        ),
        fail
    ).


event(D, Ev:event) :->
    "Process direct event"::
    (   get(D, prompter, Prompter),
        Prompter \== @nil
    ->  send(D, editor_event, Ev)
    ;   send_super(D, event, Ev)
    ).


m_x_next(D) :->
    "Handle M-n to get next value"::
    (   get(D?client?mode, m_x_next, NewDefault)
    ->  send(D?prompter, displayed_value, NewDefault?print_name)
    ;   send(D?prompter, restore)
    ).


m_x_previous(D) :->
    "Handle M-p to get previous value"::
    get(D?client?mode, m_x_previous, NewDefault),
    send(D?prompter, displayed_value, NewDefault?print_name).


geometry(D, X:[int], Y:[int], W:[int], H:[int]) :->
    "Change size, center contents vertically"::
    send(D, send_super, geometry, X, Y, W, H),
    get(D, height, DH),
    DH2 is DH//2,
    send(D?graphicals, for_all,
         message(@arg1, center_y, DH2)).


prompter(D, Prompter:dialog_item*) :->
    "Display the prompter"::
    get(D, member, reporter, Reporter),
    (   get(D, prompter, OldPrompter), OldPrompter \== @nil
    ->  send(D, erase, OldPrompter)
    ;   true
    ),
    (   Prompter == @nil
    ->  send(Reporter, clear),
        send(Reporter, displayed, @on)
    ;   send(Reporter, displayed, @off),
        get(Prompter, height, H),
        get(D, height, DH),
        PY is (DH-H)//2,
        send(D, display, Prompter, point(25, PY)),
        get(Prompter, height, H),
        MinH is H,
        (   DH < MinH
        ->  send(D, height, MinH)
        ;   true
        )
    ),
    send(D, slot, prompter, Prompter).

:- pce_end_class.


:- pce_begin_class(emacs_view, view,
                   "View running an emacs_editor").

:- pce_global(@emacs_image_recogniser,
              new(handler(button,
                          message(@receiver?device?(mode), event, @event)))).

class_variable(size,         size, size(80,32), "Size of text-field").

initialise(V, B:buffer=[emacs_buffer], W:width=[int], H:height=[int]) :->
    "Create for buffer"::
    get(V, class_variable_value, size, size(DW, DH)),
    default(W, DW, Width),
    default(H, DH, Height),
    (   B == @default
    ->  new(Buffer, emacs_buffer(@nil, '*scratch*'))
    ;   Buffer = B
    ),
    send_super(V, initialise, @default, @default, @default,
               new(E, emacs_editor(Buffer, Width, Height))),
    send(E?image, recogniser, @emacs_image_recogniser),
    send(E, recogniser,
         handler(keyboard,
                 if(message(E?frame, has_send_method, editor_event),
                    message(E?frame, editor_event, @arg1),
                    new(or)))),

    get(Buffer, mode, ModeName),
    send(E, mode, ModeName),
    get(E, mode, Mode),             % the mode object
    ignore(send(Mode, new_buffer)).

label(V, Label:name) :->
    "Set label of frame/tab"::
    get(V, device, Dev),
    (   send(Dev, has_send_method, label)
    ->  send(Dev, label, Label),
        (   get(Dev, container, emacs_tabbed_window, TW),
            get(TW, current, V),
            get(V, frame, Frame),
            Frame \== @nil
        ->  send(Frame, label, Label) % HACK: should subclass window_tab
        ;   true
        )
    ;   get(V, frame, Frame),
        Frame \== @nil
    ->  send(Frame, label, Label)
    ;   true
    ).
label(V, Label:name) :<-
    "Fetch the current label"::
    get(V, device, Dev),
    send(Dev, has_get_method, label),
    get(Dev, label, Label).

drop_files(V, Files:chain, _At:point) :->
    "Accept files dropped on me"::
    send(V?editor, drop_files, Files).


:- pce_group(mode).

setup_mode(V) :->
    "Editor has changed mode; ask <-frame to do its part"::
    (   get(V, frame, Frame),
        send(Frame, has_send_method, setup_mode)
    ->  send(Frame, setup_mode, V)
    ;   true
    ).

fill_menu_bar(V, MB:menu_bar) :->
    "Setup menu-bar for current mode"::
    send(V?editor, fill_menu_bar, MB).

:- pce_group(prompt).

prompt_using(V, Item:dialog_item, Rval:unchecked) :<-
    "Prompt for one value using a dialog-item"::
    (   get(V, frame, Frame),
        send(Frame, has_get_method, prompt_using)
    ->  get(Frame, prompt_using, Item, Rval)
    ;   new(D, dialog),             % very incomplete!
        send(D, transient_for, V),
        send(D, modal, transient),
        send(D, append, Item),
        get(D, confirm_centered, Rval)
    ).

prompt(V, Label:char_array, Default:[any], Type:[type], History:[chain],
       Rval:any) :<-
    "Prompt for a value"::
    get(V, mode, Mode),
    make_item(Mode, Label, Default, Type, History, Item),
    (   send(Item, instance_of, text_item)
    ->  send(Item, length, 60),
        send(Item, pen, 0)
    ),

    get(V, prompt_using, Item, RawRval),

    fix_rval(Type, RawRval, Rval),
    (   object(Rval),
        get(Rval, lock_object, @off)
    ->  send(Rval, lock_object, @on),       % protect during deletion!
        free(Item),
        get(Rval, unlock, Rval)
    ;   free(Item)
    ).


%       If the user entered a directory while requested for a file,
%       start the finder in the specified directory to provide the file.

fix_rval(Type, RawRval, RVal) :-
    send(Type, instance_of, type),
    send(Type, includes, file),
    \+ send(Type, includes, directory),
    atom(RawRval),
    send(directory(RawRval), exists),
    !,
    get(@finder, file, @on, directory := RawRval, RVal).
fix_rval(_, Rval, Rval).


:- pce_global(@emacs_prompt_for,
              new(constant(prompt, 'Prompt for value'))).

interactive_arguments(V, Impl:any, Times:[int], Argv:vector) :<-
    "Prompt for arguments for the given implementation"::
    get(V, mode, Mode),
    make_arg_vector(Impl, Times, Argv),
    (   get(Argv, index, @emacs_prompt_for, _)
    ->  (   get(V, frame, Frame),
            send(Frame, has_get_method, prompt_style),
            get(Frame, prompt_style, mini_window)
        ->  fill_arg_vector(Mode, Impl, Argv)
        ;   new(D, emacs_prompt_dialog(Mode, Impl, Argv)),
            send(D, prompt, V, Argv),
            send(D, destroy)
        )
    ;   true
    ).

fill_arg_vector(Mode, Impl, Argv) :-
    fill_arg_vector(1, Mode, Impl, Argv).

fill_arg_vector(ArgN, Mode, Impl, Argv) :-
    get(Impl, argument_type, ArgN, ArgType),
    get(Argv, element, ArgN, @emacs_prompt_for),
    !,
    get(Mode, interactive_argument, Impl, ArgN, Arg),
    get(ArgType, check, Arg, CheckedArg),
    send(Argv, element, ArgN, CheckedArg),
    Next is ArgN + 1,
    fill_arg_vector(Next, Mode, Impl, Argv).
fill_arg_vector(ArgN, Mode, Impl, Argv) :-
    get(Impl, argument_type, ArgN, _),
    !,
    Next is ArgN + 1,
    fill_arg_vector(Next, Mode, Impl, Argv).
fill_arg_vector(_, _, _, _).


make_arg_vector(Impl, Times, Argv) :-
    new(Argv, code_vector),
    make_arg_vector(1, Impl, Times, Argv).

make_arg_vector(ArgN, Impl, Times, Argv) :-
    get(Impl, argument_type, ArgN, ArgType),
    !,
    (   integer(Times),
        send(ArgType, includes, int)
    ->  send(Argv, element, ArgN, Times),
        NextTimes = @default
    ;   NextTimes = Times,
        (   send(ArgType, includes, default)
        ->  send(Argv, element, ArgN, @default)
        ;   send(Argv, element, ArgN, @emacs_prompt_for)
        )
    ),
    Next is ArgN + 1,
    make_arg_vector(Next, Impl, NextTimes, Argv).
make_arg_vector(_, _, _, _).


:- pce_end_class(emacs_view).


:- pce_begin_class(emacs_editor, editor, "Generic PceEmacs editor").

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
We use a pool of  modes  recorded  in   <-modes  to  avoid  the need for
destruction of mode objects during the livetime  of the editor.  This is
dangerous as the mode might still be `running' some command.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

variable(mode,            emacs_mode*,  get, "Mode of operation").
variable(modes,           chain,        get, "Modes part of this editor").

initialise(E, TB:[text_buffer], W:[int], H:[int]) :->
    send(E, send_super, initialise, TB, W, H),
    send(E, slot, modes, new(chain)).


unlink(E) :->
    "Unlink from mode object"::
    get(E, modes, Modes),
    send(Modes, for_all, message(@arg1, free)),
    send(E, send_super, unlink).

:- pce_global(@emacs_idle_timer, make_idle_timer).

make_idle_timer(T) :-
    new(T, timer(2)),
    send(T, message,
         new(Msg, message(T, send_hyper, editor, editor_idle_event))),
    send(Msg, debug_class, service).        % non-traceable


editor_idle_event(E) :->
    "Editor is idle"::
    get(E, mode, Mode),
    Mode \== @nil,
    send(Mode, has_send_method, idle),
    get(E, window, Window),
    get(Window, focus, @nil),       % only send event if no recognisers
    send(Mode, idle).               % are active


start_idle_timer(E, Interval:[real]) :->
    "Reset the idle timer to timeout after the specified time"::
    default(Interval, 2, Time),
    send(@emacs_idle_timer, interval, Time),
    send(@emacs_idle_timer, status, once),
    send(@emacs_idle_timer, delete_hypers),
    new(_, hyper(@emacs_idle_timer, E, editor, idle_timer)).


typed(E, Id:'event|event_id') :->
    "Handle typing via mode"::
    send(E, start_idle_timer),
    get(E, mode, Mode),
    (   send(Mode, typed, Id, E),
        object(Mode)                % may disappear
    ->  send(Mode, highlight_matching_bracket)
    ;   true
    ).


caret(E, Caret:[int]) :->
    "Deal with idle-timing and ->new_caret_position"::
    get(E, caret, Old),
    send_super(E, caret, Caret),
    send(E, start_idle_timer),
    get(E, mode, Mode),
    (                               % Mode can be @nil
        send(Mode, has_send_method, new_caret_position)
    ->  (   Caret == @default
        ->  get(E, caret, NewCaret)
        ;   NewCaret = Caret
        ),
        (   Old \== NewCaret
        ->  send(Mode, new_caret_position, NewCaret)
        ;   true
        )
    ;   true
    ).


event(E, Ev:event) :->
    (   send(Ev, is_a, area_enter)
    ->  get(E, frame, Frame),
        (   get(Frame, transients, Transients),
            Transients \== @nil,
            get(Transients, find, @arg1?modal == transient, _)
        ->  format('We have a transient~n')
        ;   send(Frame, keyboard_focus, E?window)
        )
    ;   send_super(E, event, Ev)
    ).


paste(E, Which:[{primary,clipboard}]) :->
    send(E, start_idle_timer),
    send_super(E, paste, Which),
    send(E, highlight_matching_bracket).


highlight_matching_bracket(E) :->
    get(E, mode, Mode),
    (   send(Mode, highlight_matching_bracket)
    ->  true
    ;   true                        % avoid delegation
    ).


mode(E, ModeName:mode_name) :->
    "Associate argument mode"::
    get(E, mode, OldMode),
    (   get(OldMode, name, ModeName)
    ->  send(E, syntax, OldMode?syntax)
    ;   (   get(E?modes, find, @arg1?name == ModeName, Mode)
        ->  send(E, slot, mode, Mode)
        ;   send(E, slot, mode, ModeName),  % Converted to object
            get(E, mode, Mode),             % The object
            send(Mode, editor, E),
            send(E?modes, append, Mode)
        ),
        send(E?text_buffer, mode, ModeName),
        send(E, syntax, Mode?syntax),
        send(E, bindings, Mode?bindings),
        send(E, setup_mode),
        send(E?device, setup_mode),
        send(E, report, status, 'Switched to ``%s'''' mode', ModeName)
    ).


preview_drop(E, Obj:object*) :->
    "Delegate to mode"::
    get(E, mode, Mode),
    get(Mode?class, send_method, preview_drop, _), % avoid delegation
    send(Mode, preview_drop, Obj).


drop(E, Obj:object) :->
    "Delegate to mode"::
    get(E, mode, Mode),
    get(Mode?class, send_method, drop, _),         % avoid delegation
    send(Mode, drop, Obj).


auto_fill(E, Caret:[int], Regex:[regex]) :->
    "Delegate to mode"::
    (   get(E, mode, Mode),
        get(Mode?class, send_method, auto_fill, _)
    ->  send(Mode, auto_fill, Caret, Regex)
    ;   send_super(E, auto_fill, Caret, Regex)
    ).


import_selection(E) :->
    "Import the (primary) selection or the cut_buffer"::
    get(E, display, Display),
    get(Display, selected_text, String),
    (   get(E, frame, Frame),
        get(Frame, member, mini_window, MiniWindow),
        get(MiniWindow, prompter, TI),
        send(TI, instance_of, text_item)
    ->  send(TI, insert, @default, String)
    ;   send(E, insert, String)
    ).


catch_all(E, Selector:name, Args:unchecked ...) :->
    "Delegate to mode"::
    get(E, mode, Mode),
    get(Mode?class, send_method, Selector, _),
    send(@pce, last_error, @nil),
    Msg =.. [Selector|Args],
    send(Mode, Msg).


text_buffer(E, B:emacs_buffer) :->
    "Switch to indicated buffer"::
    get(E, text_buffer, Last),
    (   B == Last
    ->  true
    ;   send_super(E, text_buffer, B),
        get(B, mode, ModeName),
        send(E, mode, ModeName),
        send(B, update_label),
        send(E, report, status, ''),
        get(E, mode, Mode),
        send(Mode, new_buffer),
        (   send(Last, instance_of, emacs_buffer)
        ->  send(E, delete_hypers, last_buffer),
            new(_, hyper(E, Last, last_buffer, last_editor))
        ;   true
        )
    ).


last_buffer(E, TB:text_buffer) :<-
    "Text-buffer we came from (for default)"::
    get(E, hypered, last_buffer, TB).


                 /*******************************
                 *          UTILITIES           *
                 *******************************/

label(E, Label:name) :->
    "Delegate to view"::
    get(E, device, View),
    send(View, label, Label).

size(E, Size:size) :->
    "Set size, resizing the frame"::
    get(E, frame, Frame),
    get(Frame, size, size(FW,FH)),
    get(E?area, size, size(W0,H0)),
    send_super(E, size, Size),
    get(E?area, size, size(W1,H1)),
    FW1 is FW+W1-W0,
    FH1 is FH+H1-H0,
    send(Frame, size, size(FW1, FH1)).

font(E, Font:font) :->
    "Set font, resizing the frame"::
    get(E, frame, Frame),
    get(Frame, size, size(FW,FH)),
    get(E?area, size, size(W0,H0)),
    send_super(E, font, Font),
    get(E?area, size, size(W1,H1)),
    FW1 is FW+W1-W0,
    FH1 is FH+H1-H0,
    send(Frame, size, size(FW1, FH1)).

looking_at(E, Re:regex, Where:[int], End:[int]) :->
    "Test if regex macthes from the caret"::
    (   Where == @default
    ->  get(E, caret, C)
    ;   C = Where
    ),
    get(E, text_buffer, TB),
    send(Re, match, TB, C, End).

looking_at(E, Re:regex, Where:[int], End:[int], Len:int) :<-
    "Test if regex macthes from the caret"::
    (   Where == @default
    ->  get(E, caret, C)
    ;   C = Where
    ),
    get(E, text_buffer, TB),
    get(Re, match, TB, C, End, Len).


		 /*******************************
		 *            DABBREV		*
		 *******************************/

dabbrev_candidates(E, CMode:name, Target:char_array, Completions:chain) :<-
    get(E, mode, Mode),
    Mode \== @nil,
    send(Mode, has_get_method, dabbrev_candidates),
    get(Mode, dabbrev_candidates, CMode, Target, Completions).

:- pce_end_class.


                 /*******************************
                 *          EMACS MODES         *
                 *******************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PceEmacs  modes  are  tricky  stuff.   We    like  to  have  comfortable
programming, which implies we should  represent   a  PceEmacs  mode as a
class.   This  provides  us  with  a   good  programming  interface  and
inheritance as well as all the other goodies of OO programming.

We also would like to be able to   switch PceEmacs windows from one mode
to another.  This conflicts, as instances  cannot be migrated from class
to class.  Therefore, PceEmacs modes are objects  that are attached to a
emacs_editor.  An emacs_mode delegates to the   editor  in this mode and
editors delegate to their mode (with an explicit method to avoid endless
loops  if  the   method   is   defined    on   neither).    The   method
`pce_editor->mode' attaches a mode to an editor.

Next, we would like users to be able  to extend these classes to provide
custom methods and possibly redefine methods.  This has been implemented
using tricky meta-programming: class emacs_mode_class   is a subclass of
class `class' (representing classes).   This   class  defines the method
->load_user_extensions, which is called when an instance of the class is
created.   The  classes  defining  emacs_modes  are  instances  of  this
emacs_mode_class class.  To understand this, try:

        ?- new(X, class(myclass, class)),
           new(Y, myclass(myobject, object)),
           new(Z, myobject).

and verify how the objects and classes are related.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


:- pce_begin_class(emacs_mode_class, class,
                   "Class for emacs modes").

variable(user_extensions_loaded, bool := @off, get,
         "Test if extensions are loaded").

load_user_extensions(C) :->
    "Load mode extensions from ~/lib/xpce/emacs/"::
    (   get(C, user_extensions_loaded, @on)
    ->  true
    ;   get(C, name, Name),
        (   atom_concat(emacs_, Base, Name)
        ->  true
        ;   Base = Name
        ),
        send(@emacs, load_user_extension, Base),
        send(C, slot, user_extensions_loaded, @on),
        get(C, super_class, Super),
        (   send(Super, has_send_method, load_user_extensions)
        ->  send(Super, load_user_extensions)
        ;   true
        )
    ).

:- pce_end_class(emacs_mode_class).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Finally, we have to tell pce_begin_class/3 the  meta-class we want to be
using.  If pce_begin_class/3 makes a subclass, it will make the subclass
of the same  meta-class  as  its   super-class.   Thus,  a  subclass  of
emacs_mode will be an instance   of  class(emacs_mode_class), instead of
class(class).
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- pce_begin_class(emacs_mode_class:emacs_mode(name), object,
                   "Generic PceEmacs mode class").

variable(name,            name,         get,  "Name of the mode").
variable(syntax,          syntax_table, get,  "Syntax for this mode").
variable(bindings,        key_binding,  get,  "Key-binding table").
variable(editor,          editor*,      both, "Associated editor").
variable(m_x_history,     chain*,       both, "Current M-x command history").
variable(m_x_index,       int*,         both, "M-p/M-n current index").
variable(m_x_argn,        int*,         both, "M-p/M-n current argument").
variable(keep_selection,  bool := @off, both, "Keep selection for this method").

delegate_to(editor).

                /********************************
                *         CREATE/REUSE          *
                ********************************/

initialise(M) :->
    "Create"::
    get(M, class_name, ClassName),
    mode_name(ClassName, Name),
    send(@mode_name_type?context, add, Name), % make sure
    send(M, send_super, initialise),
    send(M, slot, name, Name),
    send(M, slot, syntax, Name),              % converts to object
    send(M, bindings).


icon(_, I:image) :<-
    "Return icon for mode"::
    new(I, image(resource(mode_x_icon))).


mode_name(emacs_mode, default) :- !.
mode_name(Mode, Name) :-
    (   atom_concat(emacs_, M1, Mode)
    ;   M1 = Mode
    ),
    !,
    (   atom_concat(Name, '_mode', M1)
    ;   Name = M1
    ),
    !.


table_name(ClassName, TableName) :-
    atom_concat(TableName, '_mode', ClassName).


new_buffer(M) :->
    "Called if a new buffer is attached to this mode"::
    (   get(M, frame, Frame),
        send(Frame, has_send_method, show_line_number)
    ->  send(Frame, show_line_number, @nil)
    ;   true
    ),
    send(M, new_caret_position, M?caret).


new_caret_position(M, Caret:int) :->
    "Called after any caret movement"::
    get(M, text_buffer, TB),
    get(TB, find_all_fragments,
        message(@arg1, overlap, Caret),
        Fragments),
    (   send(Fragments, empty)
    ->  send(M, report, status, '')
    ;   send(Fragments, for_some,
             message(M, in_fragment, @arg1))
    ).


highlight_matching_bracket(_M, _At:[int]) :->
    "Virtual.  Statically highlight bracket matching caret"::
    true.


in_fragment(M, Fragment:fragment) :->
    "Called after a caret movement brings the caret in fragment"::
    (   send(Fragment, has_send_method, identify)
    ->  send(Fragment, identify)
    ;   (   get(Fragment, attribute, message, Message)
        ->  get(Fragment, style, StyleName),
            send(M, report, status, '%s: %s', StyleName, Message)
        ;   true
        )
    ).


bindings(M) :->
    "Associate key_binding table"::
    get(M, class_name, ClassName),
    binding_name(ClassName, Name),
    get(@key_bindings, member, Name, Table),
    !,
    send(M, slot, bindings, Table).


syntax(M) :->
    "Associate syntax table"::
    get(M, class_name, ClassName),
    binding_name(ClassName, Name),
    get(@syntax_tables, member, Name, Table),
    !,
    send(M, slot, syntax, Table).


binding_name(ClassName, Name) :-
    table_name(ClassName, Name).
binding_name(ClassName, Name) :-
    mode_name(ClassName, ModeName),
    key_binding_name(ModeName, Name).
binding_name(ClassName, Name) :-
    get(@pce, convert, ClassName, class, Class),
    get(Class, super_class, Super),
    send(Super, is_a, emacs_mode),
    get(Super, name, SuperName),
    binding_name(SuperName, Name).


convert(_, Name:name, Mode:emacs_mode) :<-
    "Convert name into a mode object"::
    atomic_list_concat([emacs_, Name, '_mode'], ModeClassName),
    get(@pce, convert, ModeClassName, class, _), % fail silently
    new(Mode, ModeClassName).


                 /*******************************
                 *         THE MODE MENU        *
                 *******************************/

:- pce_global(@emacs_mode, new(@event?window?(mode))).

mode_menu(M, MM:emacs_mode_menu) :<-
    "Return the mode-menu structure for this mode"::
    get(M, class_name, ClassName),
    mode_menu_name(ClassName, Name),
    get(@emacs_mode_menus, member, Name, MM),
    !.


mode_menu_name(ClassName, Name) :-
    mode_name(ClassName, Name).
mode_menu_name(ClassName, Name) :-
    get(@pce, convert, ClassName, class, Class),
    get(Class, super_class, Super),
    send(Super, is_a, emacs_mode),
    get(Super, name, SuperName),
    mode_menu_name(SuperName, Name).

fill_menu_bar(M, MB:menu_bar) :->
    "Fill the menu_bar"::
    send(MB, mode, M).


                 /*******************************
                 *            HISTORY           *
                 *******************************/

%:- pce_global(@c_method, new(var)).    % debugging

open_history(M, Impl:behaviour, Force:[bool]) :->
    "(Initialise) history for behaviour"::
    (   (Force == @on ; get(M, m_x_history, @nil))
    ->  (   get(Impl, attribute, emacs_history, History)
        ->  true
        ;   send(Impl, attribute, emacs_history, new(History, chain))
        ),
%       send(@c_method, assign, Impl, global),
        send(M, m_x_history, History),
        send(M, m_x_index, @nil)
    ;   true
    ).


close_history(M, Argv:[vector]) :->
    "Close open history adding Argv"::
    get(M, m_x_history, History),
    (   Argv \== @default,
        History \== @nil
    ->  get(Argv, copy, Save),
        clean_argv(Save),
        (   get(History, find,
                message(@prolog, same_argv, Save, @arg1),
                Old)
        ->  send(History, move_after, Old)
        ;   send(History, prepend, Argv)
        )
    ;   true
    ),
    send(M, m_x_history, @nil),
    send(M, m_x_index, @nil).


same_argv(V1, V2) :-
    get(V1, size, S1),
    get(V2, size, S1),
    forall(between(1, S1, N),
           (   get(V1, element, N, E1), get(E1, print_name, P1),
               get(V2, element, N, E2), get(E2, print_name, P2),
               send(P1, equal, P2)
           )).


%       clean_argv(+Vector)
%       Replace vector elements with their written version to avoid the
%       risk of illegal-object references.

clean_argv(Vector) :-
    get(Vector, low_index, Low),
    get(Vector, high_index, High),
    (   between(Low, High, Index),
        get(Vector, element, Index, E),
        object(E),
        get(E, protect, @off),
        send(Vector, element, Index, E),
        fail
    ;   true
    ).


noarg_call(M, Selector:name, Times:[int]) :->
    "Invoke method without arguments (prompt)"::
    (   get(M, send_method, Selector, tuple(_, Impl))
    ->  send(@current_emacs_mode, assign, M),
        send(M, open_history, Impl, @on),
        get(M, interactive_arguments, Impl, Times, Argv),
        send(M, report, status, ''),
        send(M, close_history, Argv),
        (   send(M, send_vector, Selector, Argv)
        ->  (   object(M)
            ->  send(M, mark_undo)
            ;   true
            )
        ;   (   object(M)
            ->  send(M, report, status, '%s command failed', Selector)
            ;   true
            )
        )
    ;   send(M, report, error, 'No implementation for ``%s''''', Selector)
    ).


arg_call(M, Selector:name, Arg:any) :->
    "Invoke method from pullright menu"::
    send(M, Selector, Arg).


                 /*******************************
                 *           SETUP              *
                 *******************************/

setup_mode(M) :->
    "Initialise mode (->load_user_extensions)"::
    send(M, load_user_extensions).


load_user_extensions(M) :->
    "Load mode extensions from ~/lib/xpce/emacs/"::
    send(M?class, load_user_extensions).


                /********************************
                *           TYPING              *
                ********************************/

typed(M, Id:'event|event_id', Editor:editor) :->
    "Handle typed character for editor"::
    get(M, text_buffer, TB),
    send(TB, check_auto_save),

                                    % send to mode rather than editor
    (   get(M, focus_function, F), F \== @nil
    ->  (   send(M, F, Id)
        ->  true
        ;   send(M, focus_function, @nil),
            send(M, typed, Id, Editor)        % failed: unfocus and resent
        )
    ;   get(M, bindings, Binding),
        send(Binding, typed, Id, M)
    ).


                 /*******************************
                 *           SELECTION          *
                 *******************************/

default(_E, _Type:type, _Default:unchecked) :<-
    "[virtual] Provide default for prompting"::
    fail.


                 /*******************************
                 *           EVENTS             *
                 *******************************/

event(M, Ev:event) :->
    "Allow for gestures to be appended to modes"::
    (   get(M, all_recognisers, Chain),
            get(Chain, find,
                message(@arg1, event, Ev), _)
    ;   send(Ev, is_a, ms_right_down), % show fragment popup (if any)
        get(M?image, index, Caret),
        get(M?text_buffer, find_all_fragments,
            message(@arg1, overlap, Caret),
            Fragments),
        send(Fragments, sort, ?(@arg1?length, compare, @arg2?length)),
        get(Fragments, find, message(@arg1, has_get_method, popup), F),
        get(F, popup, P), P \== @nil,
        new(G, popup_gesture(P)),
        send(G, context, F),        % make fragment available as @arg1
        send(G, event, Ev)
    ).


                 /*******************************
                 *        FIX DELEGATION        *
                 *******************************/

file(M, File:file*) :<-
    "Return associated file"::
    get(M?text_buffer, file, File).


                 /*******************************
                 *      PROMPTING ARGUMENTS     *
                 *******************************/

prompt(M, Label:char_array, Default:[any], Type:[type], Rval:any) :<-
    "Prompt for a value in the mini-window"::
    get(M?window, prompt, Label, Default, Type, Rval).


prompt_using(M, Item:graphical, Rval:any) :<-
    "Prompt using dialog item in the mini-window"::
    get(M?window, prompt_using, Item, Rval).


interactive_arguments(M, Implementation:any, Times:[int], Argv:vector) :<-
    "Prompt for arguments for the given implementation"::
    get(M, window, View),
    get(View, interactive_arguments, Implementation, Times, Argv).


interactive_argument(M, Implementation:any, Which:int, Value:any) :<-
    "Prompt for interactive argument of specified type"::
    send(M, open_history, Implementation),
    get(M, window, EmacsWindow),
    get(Implementation, argument_type, Which, Type),
    send(M, m_x_argn, Which),
    get(M, m_x_history, History),
    (   get(M, m_x_index, Idx), Idx \== @nil % use M-x History!
    ->  get(History, nth1, Idx, HistArgv),
        get(HistArgv, element, Which, DefaultValue)
    ->  true
    ;   get(Implementation, name, ImplName),
        \+ send(ImplName, suffix, selection), % not on *_selection
        get(M, selected, Selection),
        get(Type, check, Selection, DefaultValue)
    ->  true
    ;   DefaultValue = @default
    ),
    (   get(Type, argument_name, Label), Label \== @nil
    ->  true
    ;   get(Type, name, Label)
    ),
    (   (   History == @nil
        ;   send(History, empty)
        )
    ->  ValueSet = @default
    ;   get(History, map, ?(@arg1, element, Which), ValueSet)
    ),
    get(EmacsWindow, prompt, Label, DefaultValue, Type, ValueSet, Value).


m_x_previous(M, Value:any) :<-
    "Read next value from the M-x history"::
    get(M, m_x_index, Idx),
    (   Idx == @nil
    ->  Nidx = 1
    ;   Nidx is Idx + 1
    ),
    (   get(M, m_x_history, H), H \== @nil,
        get(H, nth1, Nidx, ArgVector)
    ->  get(ArgVector, element, M?m_x_argn, Value),
        send(M, m_x_index, Nidx)
    ;   send(M, report, warning, 'No (more) history'),
        fail
    ).


m_x_next(M, Value:any) :<-
    "Read previous value from the M-x history"::
    get(M, m_x_index, Idx),
    (   (Idx == @nil ; Idx =< 1)
    ->  send(M, report, warning, 'Back at start'),
        fail
    ;   Nidx is Idx - 1
    ),
    get(M?m_x_history, nth1, Nidx, ArgVector),
    get(ArgVector, element, M?m_x_argn, Value),
    send(M, m_x_index, Nidx).


                 /*******************************
                 *       LOCATION HISTORY       *
                 *******************************/

location_history(M, Start:start=[int], Len:length=[int],
                 Always:always=[bool], Title:title=[char_array]) :->
    "Add location to the editor history"::
    (   Start == @default
    ->  get(M, caret, Caret),
        get(M, scan, Caret, line, 0, start, SOF)
    ;   SOF = Start
    ),
    (   Always \== @on,
        send(M, history_not_interesting, SOF)
    ->  true
    ;   get(M, text_buffer, TB),
        new(_, emacs_history_fragment(TB, SOF, Len, Title))
    ).

history_not_interesting(M, Start:int) :->
    "True if Start is close to the recent history mark"::
    (   Start == 0
    ;   send(M, history_close_to_last, Start)
    ),
    !.

history_close_to_last(M, Start:int, MaxDist:[int]) :->
    "True if Start is within MaxDist lines from last"::
    default(MaxDist, 10, MD),
    get(M, text_buffer, TB),
    get(@emacs?history, current, Current),
    get(Current, get_hyper, fragment, text_buffer, TB),
    get(Current, get_hyper, fragment, start, StartOfCurrent),
    (   Start < StartOfCurrent
    ->  get(TB, count_lines, Start, StartOfCurrent, Lines)
    ;   Start > StartOfCurrent
    ->  get(TB, count_lines, StartOfCurrent, Start, Lines)
    ;   Lines = 0
    ),
    Lines < MD.


                 /*******************************
                 *            REPORT            *
                 *******************************/

report_to(M, E:editor) :<-
    "Send reports to the <-editor"::
    get(M, editor, E).

:- pce_end_class.


:- pce_begin_class(emacs_mode_menu(name), sheet).

:- pce_global(@emacs_mode_menus, new(hash_table)). % name ---> mode_menu object

variable(name,          name,           get,    "Name of the menu").

initialise(MM, Name:name, Super:[emacs_mode_menu]) :->
    "Create from name and super (default) menu"::
    send(MM, send_super, initialise),
    send(MM, slot, name, Name),
    send(@emacs_mode_menus, append, Name, MM),
    send(MM, protect),
    (   Super \== @default
    ->  send(Super, for_all,
             message(MM, value, @arg1?name, @arg1?value?copy))
    ;   true
    ).


lookup(_, Name:name, _Super:[emacs_mode_menu], MM) :<-
    "Reuse existing mode menu"::
    get(@emacs_mode_menus, member, Name, MM).


convert(_, Name:name, MM:emacs_mode_menu) :<-
    "Convert name to mode-menu object"::
    (   get(@emacs_mode_menus, member, Name, MM)
    ->  true
    ;   get(@pce, convert, string('emacs_%s_mode', Name), class, Class),
        get(Class, name, ClassName),
        mode_menu_name(ClassName, MenuName),
        get(@emacs_mode_menus, member, MenuName, MM)
    ).


action_name(Name, Name) :-
    atomic(Name),
    !.
action_name(MenuItem, Name) :-
    get(MenuItem?value?print_name, value, Name).

locate_action(Chain, Action, Cell) :-
    action_name(Action, Name),
    get(Chain, find, message(@prolog, action_name, @arg1, Name), Cell).

append(MM, Name:name, Action:'name|menu_item', Before:[name]) :->
    "Append item for specified menu"::
    (   get(MM, value, Name, Chain)
    ->  true
    ;   send(MM, value, Name, new(Chain, chain))
    ),
    (   Action == -
    ->  send(Chain, append, Action)
    ;   locate_action(Chain, Action, Old)
    ->  send(Chain, replace, Old, Action)
    ;   send(Chain, append, Action),
        (   Before \== @default,
            locate_action(Chain, Before, CellValue),
            send(Chain, move_before, Action, CellValue)
        ->  true
        ;   true
        )
    ).

delete(MM, Menu:name, Action:name) :->
    "Delete item from inherited menu"::
    (   get(MM, value, Menu, Chain),
        send(Chain, delete, Action)
    ->  true
    ;   true
    ).

:- pce_end_class.


                 /*******************************
                 *         KEY-BINDINGS         *
                 *******************************/

:- pce_begin_class(emacs_key_binding, key_binding,
                   "Specialised key_binding for history").

key_binding_name(@default, @default) :- !.
key_binding_name(@nil, @nil) :- !.
key_binding_name(KB, Name) :-
    object(KB),
    get(KB, name, KBName),
    !,
    key_binding_name(KBName, Name).
key_binding_name(editor, editor) :- !.
key_binding_name(X, Internal) :-
    atom_concat('emacs$', X, Internal).


initialise(KB, Name:[name]*, Super:[key_binding]) :->
    default(Super, editor, S),
    key_binding_name(Name, IName),
    key_binding_name(S, IS),
    send(KB, send_super, initialise, IName, IS).

convert(_, IName:name, KB:emacs_key_binding) :<-
    "Handle mapped names"::
    key_binding_name(Name, IName),
    get(type(key_binding), convert, Name, KB).

lookup(_, Name:name, _Super:[key_binding], KB:emacs_key_binding) :<-
    "Find existing mappings"::
    key_binding_name(Name, IName),
    get(@key_bindings, member, IName, KB).

:- pce_group(execute).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
These methods define  argument-filling  and   execution  from  arbitrary
methods from a keyboard command.  As  we   want  to  do  fairly advanced
prompting we need to do redefine some things from class key_binding.

First we check whether there is  need   for  prompting.  If so, we check
whether we use the miniwindow or  not.   The  miniwindow prompts for one
argument  at  a  time.  The  system  ->fill_arguments_and_execute  calls
<-interactive_argument on Receiver for each missing argument.

If we are in prompt mode we simply   use  ->noarg_call on the mode, just
like commands comming from the menus.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

fill_arguments_and_execute(KB, EvId:event_id, Receiver:emacs_mode,
                           Selector:name, Argv:any ...) :->
    "Open/close the argument processing"::
     Message =.. [ fill_arguments_and_execute,
                   EvId, Receiver, Selector | Argv],

    (   get(Receiver, send_method, Selector, tuple(_, Impl))
    ->  (   length(Argv, Before),
            First is Before + 1,
            args_available(First, Impl, KB, EvId)
        ->  send_super(KB, Message)                 % no need to prompt
        ;   get(Receiver, frame, Frame),
            send(Frame, has_get_method, prompt_style),
            get(Frame, prompt_style, mini_window)
        ->  send(@current_emacs_mode, assign, Receiver),
            send(Receiver, open_history, Impl, @on),
            send_super(KB, Message)                 % miniwindow
        ;   send(Receiver, noarg_call, Selector)    % prompting
        )
    ;   send_super(KB, Message)                     % generate error
    ).

%       args_available(+I, +Implementation, +KeyBinding, +EventId)
%
%       See whether all arguments are around that allow us to execute
%       the command without prompting.  See the implementation of
%       `key_binding->fill_arguments_and_execute' for reference.

args_available(N, Impl, KB, EvId) :-
    get(Impl, argument_type, N, ArgType),
    !,
    (   send(ArgType, includes, event_id)
    ;   send(ArgType, includes, char),
        integer(EvId)
    ;   send(ArgType, includes, int),
        get(KB, argument, Arg),
        integer(Arg)
    ;   send(ArgType, includes, default)
    ),
    !,
    NN is N + 1,
    args_available(NN, Impl, KB, EvId).
args_available(_, _, _, _).

execute(KB, Receiver:emacs_mode, Selector:name, Argv:any ...) :->
    "Push history if available"::
    (   get(Receiver, m_x_history, @nil)
    ->  true
    ;   VectorTerm =.. [code_vector|Argv], % do not create references!
        send(Receiver, close_history, new(VectorTerm))
    ),
    Message =.. [execute, Receiver, Selector | Argv],
    send_super(KB, Message).

:- pce_end_class.


                 /*******************************
                 *         ARGUMENT ITEM        *
                 *******************************/

:- pce_begin_class(emacs_argument_item, menu_item,
                   "Item with pullright for args").

initialise(I, Name:name, ValueSet:'chain|function') :->
    send(I, send_super, initialise, Name),
    send(I, popup,
         new(P, emacs_argument_popup(Name,
                                     message(@emacs_mode, arg_call,
                                             Name, @arg1)))),
    (   send(ValueSet, '_instance_of', chain)
    ->  send(P, members, ValueSet)
    ;   send(P, update_message,
             message(@receiver, members, ValueSet))
    ).

:- pce_end_class.


:- pce_begin_class(emacs_argument_popup, popup,
                   "Emacs mode menu pullright popup").

members(I, Members:chain) :->
    "->clear and attach new members (do not capitalise)"::
    get(Members, map,
        create(menu_item, @arg1, @default, @arg1?print_name),
        Items),
    send(I, send_super, members, Items).

:- pce_end_class.
