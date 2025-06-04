/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@cs.vu.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1985-2010, University of Amsterdam, VU University Amsterdam
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

:- module(emacs_fundamental_mode, []).
:- use_module(library(pce)).
:- use_module(library(print_text)).
:- require([ append/3
           , auto_call/1
           , between/3
           , chain_list/2
           , default/3
           , ignore/1
           ]).

:- emacs_begin_mode(fundamental, [],    % []: root of the mode hierarchy
                    "Generic PceEmacs editing mode",
        [ prefix                   = key('\\C-h'),
          insert_file              = key('\\C-xi'),
          write_file               = key('\\C-x\\C-w'),
          save_and_kill            = key('\\C-x#'),
          what_cursor_position     = key('\\C-x='),
          count_lines_region       = key('\\e='),
          replace                  = key('\\e%'),
          grab_region              = key('\\ew'),
          justify_paragraph        = key('\\eQ'),
          bookmark_line            = key('\\e@'),
          execute_extended_command = key('\\ex'),
          write_region             = key('\\e\\C-w'),
          compile                  = key('\\C-x\\C-m'),

          prefix                   = key('\\eg'),

          font_magnify             = key('\\C-+'),
          font_reduce              = key('\\C--'),
          font_default             = key('\\C-='),

                                        % FILE menu
          show_buffer_menu         = key('\\C-x\\C-b') + button(file),
          switch_to_buffer         = key('\\C-xb') +
                                     button(file, @emacs_mode?buffers),
          -                        = button(file),
          open                     = key('\\C-x\\C-f') + button(file),
          new                      = button(file),
          save_buffer              = key('\\C-x\\C-s') + button(file),
          save_as                  = button(file),
          print                    = button(file),
          print_selection          = button(file),
          -                        = button(file),
          revert                   = button(file),
          kill_buffer              = key('\\C-xk') + button(file),
          -                        = button(file),
          ispell                   = button(file),
          shell                    = button(file),
          (mode)                   = key('\\em') +
                                     button(file, @emacs_mode?modes),
          properties               = button(file),
          -                        = button(file),
          quit                     = key('\\C-x\\C-c') + button(file),

                                        % EDIT menu
          undo                     = button(edit),
          -                        = button(edit),
          copy                     = button(edit),
          cut                      = button(edit),
          paste                    = button(edit),
          -                        = button(edit),
          goto_line                = button(edit) +
                                     key('\\eg\\eg') + key('\\egg'),
          find                     = key(key_top_4) + button(edit),
          replace                  = button(edit),
          -                        = button(edit),
          editor_preferences       = button(edit),
          prolog_preferences       = button(edit),

                                        % BROWSER menu
          prefix                   = key('\\C-x5'),

          split_window             = key('\\C-x2') + key('\\C-x52') + button(browse),
          only_window              = key('\\C-x1') + button(browse),
          -                        = button(browse),
          bookmark_line            = button(browse),
          show_bookmarks           = button(browse),
          -                        = button(browse),
          grep                     = button(browse),
          git_grep                 = button(browse),

                                        % COMPILE menu
          compile                  = button(compile),

                                        % HELP menu
          help                     = button(help),
          help_on_mode             = button(help),
          customise                = button(help),
          -                        = button(help),
          show_key_bindings        = key(key_top_1)
                                        + key('\\C-hb')
                                        + button(help),
          describe_key             = key('\\C-hk') + button(help),
          describe_function        = key('\\C-hf') + button(help),
          -                        = button(help),
          manual_entry             = button(help),
          xpce_manual              = button(help)
        ],
        [
        ]).

class_variable(grep_command, string,
               [ 'X'('grep -n %s /dev/null'),
                 windows('grep -n %s NUL')
               ],
               "Command of M-x grep").
class_variable(git_grep_command, string,
               'git --no-pager grep --no-color -n %s',
               "Command of M-x git-grep").
class_variable(shell_command, chain*,
               when(@pce?window_system == windows,
                    @nil,
                    chain('/bin/sh', '-c')),
               "Command for running grep, make, etc.").
class_variable(auto_colourise_size_limit, int, 50000,
               "Auto-colourise if buffer is smaller then this").
class_variable(print_command, string,
               [ 'X'('lpr %s'),
                 windows('NOTEPAD.EXE /P %s')
               ],
               "Command to print a file").
class_variable(tab_width, int,
               8,
               "Distance between tab-stops").

variable(print_command, name, both,
         "Command to print a file").
variable(auto_colourise_size_limit,
         int,
         both,
         "Auto-colourise if buffer is smaller then this").

                 /*******************************
                 *      COLOURISE BUFFERS       *
                 *******************************/

idle(M) :->
    "Idle event was received, colour the current element"::
    send(M, auto_colourise_buffer).


new_buffer(M) :->
    "A new buffer is attached"::
    send_super(M, new_buffer),
    send(M, auto_colourise_buffer).


auto_colourise_buffer(M) :->
    "Colourise if shorter then <-auto_colourise_size_limit"::
    get(M, text_buffer, TB),
    get(TB, generation, Generation),
    get(TB, coloured_generation, Coloured),
    (   Coloured \== Generation,
        get(TB, size, Size),
        get(M, auto_colourise_size_limit, Limit),
        Size < Limit,
        get(M, focus_function, @nil)        % don't colour in special modes
    ->  (   send(M, colourise_buffer)
        ->  send(TB, coloured_generation, Generation)
        ;   true
        )
    ;   true
    ).


colourisation_up_to_date(M) :->
    "True if the colourisation is up-to-date"::
    get(M, text_buffer, TB),
    get(TB, generation, Generation),
    get(TB, coloured_generation, Coloured),
    Generation == Coloured.


colourise_buffer(M) :->
    "Colour buffer using syntax-rules"::
    send(M, remove_syntax_fragments),
    get(M, text_buffer, TB),
    get(TB, generation, Generation),
    send(TB, coloured_generation, Generation).


remove_syntax_fragments(M,
                        From:from=[int], To:to=[int],
                        Style:style=[name]) :->
    "Remove all syntax-colouring fragments"::
    remove_condition(From, To, Style, Condition),
    send(M, for_all_fragments,
         if(Condition, message(@arg1, free))).


:- pce_global(@is_emacs_colour_fragment,
              new(message(@arg1, instance_of, emacs_colour_fragment))).

remove_condition(@default, @default, @default,
                 @is_emacs_colour_fragment).
remove_condition(From, To, @default,
                 and(message(@arg1, overlap, point(From, To)),
                     @is_emacs_colour_fragment)).
remove_condition(@default, @default, Style,
                 and(@arg1?style == Style,
                     @is_emacs_colour_fragment)).
remove_condition(From, To, Style,
                 and(@arg1?style == Style,
                     message(@arg1, overlap, point(From, To)),
                     @is_emacs_colour_fragment)).


                 /*******************************
                 *      GLOBAL UTILITIES        *
                 *******************************/

quit(M) :->
    "Destroy the editor"::
    ignore(send(M?text_buffer, save_if_modified)),
    send(M, destroy).

editor_preferences(_M) :->
    "Edit XPCE preferences"::
    prolog_edit_preferences(xpce).

prolog_preferences(_M) :->
    "Edit Prolog customization file"::
    prolog_edit_preferences(prolog).


                 /*******************************
                 *              REGION          *
                 *******************************/

region(M, Tuple:tuple) :<-
    "Get region start and end (sorted)"::
    get(M, mark, Mark),
    get(M, caret, Caret),
    (   Caret > Mark
    ->  new(Tuple, tuple(Mark, Caret))
    ;   Mark > Caret
    ->  new(Tuple, tuple(Caret, Mark))
    ).

line_region(M, F0:[int], T0:[int], Tuple:tuple) :<-
    "Start and end-of region for line-oriented commands"::
    (   F0 == @default,
        T0 == @default
    ->  get(M, region, tuple(From, To))
    ;   From = F0,
        To = T0
    ),
    get(M, text_buffer, TB),
    get(TB, scan, From, line, 0, start, S),
    get(TB, scan, To,   line, 0, start, E),
    new(Tuple, tuple(S, E)).

for_lines_in_region(M, From:[int], To:[int], Code:code) :->
    "Run code with @arg1, @arg2 at the start/end of each line"::
    get(M, line_region, From, To, tuple(S, E)),
    for_lines_in_region(M, S, E, Code).

for_lines_in_region(_M, S, E, _Code) :-
    S >= E,
    !.
for_lines_in_region(M, S, E, Code) :-
    get(M, scan, S, line, 0, EOL),
    send(Code, forward, S, EOL),
    SOL is EOL + 1,
    for_lines_in_region(M, SOL, E, Code).

warn_big_region(M, Action:name, N:int) :->
    "Warn if region exceeds size"::
    get(M, region, tuple(Start, End)),
    (   End - Start > N
    ->  send(@display, confirm,
             'Region is > %d characters; %s?', N, Action)
    ;   true
    ).

warn_big_paragraph(M, Action:name, N:int) :->
    "Warn if paragraph exceeds size"::
    get(M, caret, Caret),
    get(M, text_buffer, TB),
    get(TB, scan, Caret+1, paragraph, 0, start, SP),
    get(TB, scan, Caret-1, paragraph, 0, end, EP),
    (   EP - SP > N
    ->  send(@display, confirm,
             'Paragraph is > %d characters; %s?', N, Action)
    ;   true
    ).


                 /*******************************
                 *      DANGEROUS ACTIONS       *
                 *******************************/

upcase_region(M) :->
    "Upcase region, but warn if dangerous"::
    send(M, warn_big_region, upcase, 100),
    send_super(M, upcase_region).

downcase_region(M) :->
    "Downcase region, but warn if dangerous"::
    send(M, warn_big_region, downcase, 100),
    send_super(M, downcase_region).

fill_region(M) :->
    "Fill region, but warn if dangerous"::
    send(M, warn_big_region, fill, 1000),
    send_super(M, fill_region).

justify_paragraph(M) :->
    "Justify paragraph, but warn if dangerous"::
    send(M, warn_big_paragraph, justify, 1000),
    send_super(M, justify_paragraph).

fill_paragraph(M, Arg:[int]) :->
    "Fill paragraph, but warn if dangerous"::
    send(M, warn_big_paragraph, justify, 1000),
    send_super(M, fill_paragraph, Arg).


                 /*******************************
                 *              EDIT            *
                 *******************************/

grab_region(M) :->
    "Copy the current region into the cut-buffer"::
    send(M, kill_or_grab_region, 1).


sort_lines_in_region(M) :->
    "Sort lines in mark ... caret alphabetically"::
    get(M, region, tuple(Start, End)),
    send(M, sort, Start, End).


delete_matching_lines(M, Re:regex) :->
    "Delete lines in (point,end) matching regex"::
    get(M, caret, Caret),
    get(M, text_buffer, TB),
    get(TB, scan, Caret, line, 0, start, SOL),
    send(Re, compile, @on),
    new(Here, number(SOL)),
    repeat,
        (   get(TB, size, Size),
            get(Here, value, PlHere),
            PlHere >= Size
        ->  !
        ;   get(TB, scan, Here, line, 0, end, EOL),
            (   send(Re, search, TB, Here, EOL)
            ->  send(TB, delete, Here, EOL+1-Here)
            ;   send(Here, value, EOL+1)
            ),
            fail
        ).


/*
delete_rectangle(M) :->
        "Delete rectangular area (mark,caret)"::
        get(M, mark, Mark),
        get(M, column, Mark, MarkColumn),
        get(M, caret, Caret),
        get(M, column, Caret, CaretColumn),
        min(MarkColumn, CaretColumn, FromColumn),
        max(MarkColumn, CaretColumn, ToColumn),

*/

dabbrev_candidates(_M, _Mode:name, _Target:char_array, _Completions:chain) :<-
    fail.

                 /*******************************
                 *            LOAD/SAVE         *
                 *******************************/

buffers(_M, Buffers:chain) :<-
    "Chain with existing buffers"::
    get(@emacs, buffers, Buffers).

modes(_M, Modes:chain) :<-
    "Chain with defined modes"::
    get(@emacs, modes, Modes).


save_text(M) :->
    "Save buffer as ASCII if it is modified"::
    get(M, text_buffer, TB),
    (   get(TB, modified, @on)
    ->  send(M?text_buffer, save),
        send(M, report, status,
             'Buffer saved in file `%s''', TB?file?base_name)
    ;   send(M, report, status, 'No changes need saving')
    ).


save_buffer(M) :->
    "Save buffer if it is modified"::
    send(M, save_text).


save_as(M, File:save_file) :->
    "Equivalent to write_file"::
    send(M, write_file, File).


save_some_buffers(_M, Arg:[int]) :->
    "Save modified buffers. Arg: donot confirm"::
    (   Arg == @default
    ->  send(@emacs, save_some_buffers)
    ;   send(@emacs, save_some_buffers, @on)
    ).


find_file(_M, File:file) :->
    "Find existing file or create new one"::
    new(Buffer, emacs_buffer(File)),
    send(Buffer, open, tab).

new(M, File:save_file) :->
    "Create a new file"::
    send(M, find_file(File)).

open(M, File:file) :->
    "Open existing file (use File/New ... to create a new file)"::
    send(M, find_file(File)).


insert_file(M, File:file) :->
    "Insert file at point"::
    send(M?text_buffer, insert_file, M?caret, File).


write_file(M, File:save_file) :->
    "Write buffer to named file"::
    send(M?text_buffer, save, File).


write_region(M, File:save_file) :->
    "Write current region to file"::
    get(M, region, tuple(Start, End)),
    Length is End - Start,
    send(M?text_buffer, write_region, File, Start, Length).


show_buffer_menu(_M) :->
    "Expose the buffer-menu window"::
    send(@emacs, show_buffer_menu).


switch_to_buffer(_, Buffer:emacs_buffer) :->
    "Switch this window to named buffer"::
    send(Buffer, open, tab).
%       send(M, text_buffer, Buffer).           % Always in same window


kill_buffer(M) :->
    "Kill the current buffer"::
    get(M, text_buffer, Buffer),
    send(Buffer, kill).


                 /*******************************
                 *           SETTINGS           *
                 *******************************/

comment_column(M, Col:[int]) :->
    "Set comment column to current column"::
    (   Col == @default
    ->  get(M, column, Column)
    ;   Column = Col
    ),
    send(M?editor, comment_column, Column).

encoding(M,
         Enc:encoding={ascii,iso_latin_1,text,utf8,unicode_be,unicode_le},
         BOM:'BOM'=bool) :->
    "Set the character encoding for the file"::
    (   get(M, file, File),
        File \== @nil
    ->  send(File, encoding, Enc),
        send(File, bom, BOM)
    ;   send(M, report, warning, "No file")
    ).

newline_mode(M, Mode:mode={posix,dos}) :->
    "Set save-mode for newlines"::
    get(M, text_buffer, TB),
    get(TB, file, File),
    send(File, newline_mode, Mode).

tab_width(M, Width:width='2..') :->
    "Set distance between tab-stops"::
    get(M, text_buffer, TB),
    get(M, editor, E),
    send(TB, tab_width, Width),
    send(E, tab_distance, Width).


                 /*******************************
                 *             PRINT            *
                 *******************************/

print(M, From:[int], To:[int]) :->
    "Print contents of the buffer"::
    get(M, text_buffer, TB),
    get(M, editor, E),
    (   get(M, file, File),
        File \== @nil
    ->  get(File, absolute_path, Path),
        prolog_to_os_filename(Path, FileName),
        (   From \== @default, To \== @default
        ->  get(M, line_number, From, FL),
            get(M, line_number, To-1, TL),
            format(string(Job), '~w (lines ~w..~w)', [FileName, FL, TL])
        ;   Job = FileName
        )
    ;   Job = @default
    ),
    send(TB, print, From, To,
         editor := E,
         job := Job).


print_region(M) :->
    "Print current region"::
    get(M, line_region, tuple(From, To)),
    send(M, print, From, To).


print_selection(M) :->
    "Print the current selection (=region)"::
    send(M, print_region).


                 /*******************************
                 *          FIND/REPLACE        *
                 *******************************/

:- pce_autoload(editor_find_dialog, library('emacs/find')).

find(M) :->
    "Find in text"::
    get(M, editor, E),
    send(editor_find_dialog(E), open).


replace(M, From:'replace=regex', To:'into=string') :->
    "Query replace regular expression"::
    send(M, query_replace_regex, From, To).


query_replace_regex(M,
                    From:'replace=regex',
                    To:'into=string') :->
    "Query replace regular expression"::
    send(M, internal_mark),
    send(M, attribute, attribute(replace_search_pattern, From)),
    send(M, attribute, attribute(replace_replace_pattern, To)),
    send(M, attribute, attribute(replace_count, number(0))),
    replace_find_and_mark(M),
    send(M, focus_function, '_query_replace_regex').


replace_find_and_mark(M) :-
    get(M, replace_search_pattern, Regex),
    (   send(Regex, search, M?text_buffer, M?caret)
    ->  get(Regex, register_start, Start),
        get(Regex, register_end, End),
        send(M, caret, End),
        send(M, selection, Start, End, highlight),
        send(M, report, status,
             'Commands: "y" = replace-and-next; "." = replace; \c
             "n" = next; "!" = non-interactive; "ESC" = stop')
    ;   send(M, report, status, 'Done.'),
        send(M, replace_end),
        fail
    ).


replace_match(M) :-
    get(M, replace_search_pattern, Regex),
    get(M, replace_replace_pattern, Replace),
    get(Regex, register_end, End0),
    get(Regex, register_start, Start0),
    send(Regex, replace, M?text_buffer, Replace),
    send(M?replace_count, plus, 1),
    get(Regex, register_end, End),
    (   End0 == Start0                % 0-length search string!
    ->  send(M, caret, End+1)
    ;   send(M, caret, End)
    ).


replace_end(M) :->
    send(M, focus_function, @nil),
    get(M, internal_mark, Mark),
    send(M, selection, Mark, @default, inactive),
    get(M?replace_count, value, Replaced),
    send(M, report, status, 'Replaced %s matches', Replaced).


'_query_replace_regex'(M, Id:event_id) :->
    "Focus function for query_replace_regex"::
    (   Id == 0'y                           % replace-and-continue
    ->  replace_match(M),
        ignore(replace_find_and_mark(M))
    ;   Id == 0'.                           % replace and done
    ->  replace_match(M),
        send(M, replace_end)
    ;   Id == 0'n                           % donot replace and continue
    ->  (   replace_find_and_mark(M)
        ->  true
        ;   get(M, focus_function, @nil)
        )
    ;   Id == 27                            % exit
    ->  send(M, replace_end)
    ;   Id == 0'!                           % replace no-query
    ->  repeat,
            send(M, '_query_replace_regex', 0'y),
            get(M, focus_function, @nil),
        !
    ;   send(M, replace_end),               % anything else: cancel
        fail
    ).


bookmark_line(M) :->
    "Create a mark in the mark-list"::
    get(M, caret, Caret),
    get(M, scan, Caret, line, 0, start, SOL),
    send(@emacs_mark_list, append_hit, M?text_buffer, SOL).


show_bookmarks(_) :->
    "Show PceEmacs bookmarks"::
    send(@emacs, show_bookmarks).


                 /*******************************
                 *         PROCESS STUFF        *
                 *******************************/

has_processes(M) :->
    "Test if this XPCE version supports processes"::
    (   send(@pce, has_feature, process)
    ->  true
    ;   send(M, report, error, 'No inferior processes in this OS'),
        fail
    ).

                 /*******************************
                 *             INFO             *
                 *******************************/

properties(M) :->
    "Display information-window on buffer"::
    get(M, properties, _).

properties(M, V:view) :<-
    "Display information-window on buffer"::
    get(M, text_buffer, Buffer),
    get(Buffer, name, Name),
    get(Buffer, modified, Modified),
    get(Buffer, size, Size),
    get(Buffer, line_number, Lines),
    get(Buffer, mode, Mode),
    new(V, view(string('Buffer %s', Name), size(60, 8))),
    send(V, confirm_done, @off),
    send(V, tab_stops, vector(200)),
    send(V, appendf, 'Buffer Name:\t%s\n', Name),
    send(V, appendf, 'Mode:\t%s\n', Mode),
    send(V, appendf, 'Modified:\t%s\n', Modified?name),
    send(V, appendf, 'Size:\t%d characters; %d lines\n', Size, Lines-1),
    get(Buffer, file, File),
    (   Modified == @on,
        File \== @nil
    ->  get(File, size, FileSize),
        send(V, appendf, 'File Size:\t%d characters\n', FileSize)
    ;   true
    ),
    (   File \== @nil
    ->  get(File, absolute_path, Path),
        send(V, appendf, 'Path:\t%s\n', Path),
        send(V, appendf, 'Encoding:\t%s (BOM=%s, NL=%s)\n',
             File?encoding, File?bom, File?newline_mode)
    ;   send(V, appendf, 'Path:\t<No file>\n')
    ),
    send(V, caret, 0),
    send(new(D, dialog), below, V),
    send(D, append, button(quit, message(V, destroy))),
    send(V, open_centered, M?frame?area?center).


                 /*******************************
                 *           SPELLING           *
                 *******************************/

:- pce_autoload(ispell, demo(ispell)).

ispell(M) :->
    "Start ispell on this text_buffer"::
    send(M, has_processes),
    new(Ispell, ispell),
    get(M, text_buffer, TB),
    send(Ispell, buffer, TB),
    send(Ispell, label, string('Ispell Emacs buffer %s', TB?name)),
    send(Ispell, open),
    send(Ispell, spell).

		 /*******************************
		 *       EDIT WITH EMACS	*
		 *******************************/

chrome_server(_) :->
    "Start HTTP server on 9292 for Edit With Emacs"::
    send(@emacs, chrome_server).


                 /*******************************
                 *        M-x PROCESSING        *
                 *******************************/

command_names(M, Names:chain) :<-
    "Find all send_methods on this mode"::
    get(M, find_all_send_methods, Chain),
    get(Chain, map, @arg1?name, Names).


:- initialization
   (   object(@emacs_mode_command)
   ->  true
   ;   new(@emacs_mode_command,
           type(emacs_mode_command, value_set,
            quote_function(@current_emacs_mode?command_names),
            @nil))
   ).

execute_extended_command(M,
                         CmdName:command=emacs_mode_command,
                         Times:[int]) :->
    "Prompt for interactive command"::
    send(M, noarg_call, CmdName, Times).


                 /*******************************
                 *           COMPILE            *
                 *******************************/

split_command_string(String, List) :-
    new(Ch, chain),
    new(Re, regex('[^ ]+')),
    send(Re, for_all, String,
         message(Ch, append, ?(@arg1, register_value, @arg2, 0, name))),
    chain_list(Ch, List).

compile(M, Command:shell_command=string, Label:[name]) :->
    "Run Unix (compilation) process in buffer"::
    send(M, save_some_buffers),
    send(M, has_processes),
    default(Label, Command, Lbl),
    get(M, directory, Dir),
    new(B, emacs_process_buffer(@default, string('*%s*', Lbl))),
    (   get(B, process, OldP), OldP \== @nil,
        get(OldP, status, running)
    ->  new(D, dialog('Running Process')),
        send(D, append, label(reporter,
                              'Kill running process and start new one?')),
        send(D, append, button(kill,
                               and(message(B, process, @nil),
                                   message(D, return, ok)))),
        send(D, append, button(cancel,
                               message(D, return, cancel))),
        get(D, confirm_centered, Status),
        send(D, destroy),
        Status == ok
    ;   true
    ),
    get(M, shell_command, ShellCommandChain),
    (   ShellCommandChain \== @nil
    ->  chain_list(ShellCommandChain, List),
        append(List, [Command], ArgList),
        Process =.. [process|ArgList]
    ;   split_command_string(Command, Args),
        Process =.. [process|Args]
    ),
    new(P, Process),
    send(P, directory, Dir),
    send(B, clear),
    send(B, format, 'cd %s\n%s\n', Dir?path, Command),
    send(B, directory, Dir),
    send(B, process, P),
    send(B, start_process),
    send(B, open, tab),
    send(B?editors, for_some,
         and(message(@arg1, report, status, 'Running ...'),
             message(@arg1, scroll_to, 0),
             message(@arg1, caret, @default))).


grep(M, GrepArgs:grep_arguments=string) :->
    "Run the OS grep command in compilation buffer"::
    get(M, grep_command, GrepCommad),
    send(M, compile,
         string(GrepCommad, GrepArgs),
         string('grep %s', GrepArgs)).


git_grep(M, GrepArgs:grep_arguments=string) :->
    "Run the git grep in compilation buffer"::
    get(M, git_grep_command, GrepCommad),
    send(M, compile,
         string(GrepCommad, GrepArgs),
         string('git-grep %s', GrepArgs)).


shell(M) :->
    "Start interactive shell"::
    send(M, has_processes),
    (   get(@emacs, buffer, '*shell*', Buffer)
    ->  send(Buffer, open)
    ;   (   get(@pce, environment_variable, 'SHELL', Shell)
        ->  better_shell(Shell, Shell2),
            Process = process(Shell2, '-i')
        ;   get(@pce, operating_system, winnt) % TBD: Windows 95-ME
        ->  Process = process('cmd.exe')
        ;   Process = process('sh', '-i')
        ),
        new(P, Process),
        get(M, directory, Dir),
        send(P, directory, Dir),
        new(B, emacs_process_buffer(P, '*shell*')),
        send(B, directory, Dir),
        send(B, start_process),
        send(B, open, tab)
    ).

better_shell('/bin/tcsh', '/bin/csh') :- !.
better_shell(Shell, Shell).

manual_entry(M, Spec:unix_manual_entry_for=name) :->
    "Lookup Unix manual entry"::
    send(M, has_processes),
    new(B, emacs_buffer(@nil, Spec)),
    send(B, (mode), man),
    send(B, open),
    send(B?editors?head, man, Spec).

gdb(M, Cmd:file) :->
    "Run Unix GDB on command"::
    send(M, has_processes),
    new(X, emacs_gdb_buffer(Cmd)),
    get(X, process, Process),
    (   Process \== @nil,
        get(Process, status, inactive)
    ->  get(M, directory, Dir),
        send(Process, directory, Dir),
        send(X, directory, Dir)
    ;   true
    ),
    send(X, start_process),
    send(X, open).

                 /*******************************
                 *       WYSIWYG (ANNOTATE)     *
                 *******************************/

annotate(M) :->
    "Start annotation buffer from current buffer"::
    get(M, text_buffer, OB),
    get(OB, file, OFile),
    (   OFile == @nil
    ->  NFile = @nil,
        get(OB?name, append, '.ann', BufName)
    ;   get(OFile?absolute_path, append, '.ann', NewName),
        new(NFile, file(NewName)),
        BufName = @default
    ),
    (   send(NFile, exists)
    ->  new(B, emacs_annotate_buffer(NFile, BufName))
    ;   pce_catch_error(open_file,
                        new(B, emacs_annotate_buffer(NFile, BufName))),
        send(B, contents, OB?contents)
    ),
    send(B, (mode), annotate),
    send(B, open).


                 /*******************************
                 *        MISCELLENEOUS         *
                 *******************************/

split_window(M) :->
    "Create another window for this buffer"::
    get(M, text_buffer, Buffer),
    get(Buffer, open, window, Frame),
    get(Frame, editor, NewEditor),
    get(M, caret, Here),
    send(NewEditor, caret, Here).

only_window(M) :->
    "Quit other windows on this buffer"::
    get(M, text_buffer, Buffer),
    get(M, editor, Editor),
    send(Buffer?editors, for_all,
         if(@arg1 \== Editor,
            message(@arg1, quit))).


save_and_kill(M) :->
    "Save, kill window and buffer (return server)"::
    get(M, editor, Editor),
    get(M, text_buffer, TB),
    send(TB, save),
    (   get(Editor, hypered, server, _Server)
    ->  send(TB, kill)
    ;   send(M, quit)
    ).


insert_date(M) :->
    "Insert current date"::
    new(Date, date),
    get(Date, year, Y),
    get(Date, month_name, @on, Mon),
    get(Date, day, D),
    send(M, insert, string('%s %s, %s', Mon, D, Y)).


insert_character_by_code(M, Code:code='0..') :->
    "Insert character by entering numeric value"::
    send(M, insert_self, @default, Code).


what_cursor_position(M) :->
    "Inform user on current position"::
    get(M, caret, Caret),
    get(M, length, Size),
    Proc is (100 * Caret) / Size,
    get(M, column, Caret, Col),
    send(M, report, inform, 'point=%d of %d(%d%%); column=%d',
         Caret, Size, Proc, Col).


what_line(M) :->
    "Inform user on current line"::
    get(M, line_number, M?caret, CaretLine),
    send(M, report, inform, 'line %d', CaretLine).


goto_line(M, LineNo:int, Title:title=[char_array]*) :->
    "Goto given line-number"::
    (   (   Title == @nil
        ;   get(M, line_number, M?caret, CaretLine),
            abs(LineNo-CaretLine) < 10
        )
    ->  send(M, point_to_top_of_file, LineNo)
    ;   send(@emacs, location_history),
        send(M, point_to_top_of_file, LineNo),
        send(@emacs, location_history, Title)
    ).


count_lines_region(M) :->
    "Inform user on # lines in region"::
    get(M, region, tuple(Start, End)),
    get(M, line_number, Start, CaretLine),
    get(M, line_number, End, MarkLine),
    Lines is MarkLine - CaretLine,
    send(M, report, inform, 'Region has %d lines', Lines).


count_chars_region(M) :->
    "Inform user on # characters in region"::
    get(M, region, tuple(Start, End)),
    Chars is End - Start,
    send(M, report, inform, 'Region contains %d characters', Chars).

resize_font(M, Factor:int) :->
    "Resize font to percentage, keep size in chars"::
    get(M, font, Font),
    get(Font, family, Family),
    get(Font, style, Style),
    get(Font, points, Points0),
    Points is round(Points0*Factor/100),
    send(M, font, font(Family, Style, Points)),
    get(@pce, convert, fixed, font, Default),
    get(Default, points, DefPoints),
    Perc is round(Points*100/DefPoints),
    send(M, report, status, 'Resized to %d percent', Perc).

font_magnify(M) :->
    "Increase font 20%"::
    send(M, resize_font, 110).

font_reduce(M) :->
    "Decrease font 20%"::
    A is round(100*100/110),
    send(M, resize_font, A).

font_default(M) :->
    "Use default font (size)"::
    send(M, font, fixed),
    send(M, report, status, 'Resized to 100 percent').


                 /*******************************
                 *             HELP             *
                 *******************************/

:- pce_group(help).

help(_) :->
    "Display general help"::
    send(@emacs, help).


customise(_) :->
    "Display customisation help"::
    send(@emacs, customise).


%       ->help_on_mode
%
%       See whether there is a file named <Source>.html, where <Source>
%       is the name of the source-file loaded to define the given mode.
%       If so, open it using the users' browser using www_open_url/1.

help_on_mode(M) :->
    "Provide mode-specific help"::
    (   get(M, class, Class),
        get(Class, source, source_location(File, _)),
        file_name_extension(FileBase, _, File),
        absolute_file_name(FileBase,
                           [ extensions([html]),
                             access(read),
                             file_errors(fail)
                           ],
                           HTML)
    ->  atom_concat('file:', HTML, URI),
        www_open_url(URI)
    ;   send(M, report, warning, 'No help on mode %s', M?name)
    ).


show_key_bindings(M) :->
    "Display window with key-bindings"::
    auto_call(show_key_bindings(M)).


describe_function(M, CmdName:command=emacs_mode_command) :->
    "Give help on command"::
    get(M, send_method, CmdName, tuple(_, Impl)),
    auto_call(help(Impl)).

describe_key(M) :->
    "Read key and write its action"::
    send(M, report, status, 'Describe key: '),
    send(M, focus_function, '_describe_key').

'_describe_key'(M, Ev:event) :->
    "Handle \\C-hk keys"::
    (   get(M, attribute, key_prefix, Prefix)
    ->  get(Ev, key, KeyName0),
        atom_concat(Prefix, KeyName0, KeyName),
        send(M, delete_attribute, key_prefix)
    ;   get(Ev, key, KeyName)
    ),
    get(M, bindings, Bindings),
    get(Bindings, function, KeyName, MethodName),
    (   prefix_method(MethodName)
    ->  send(M, attribute, key_prefix, KeyName),
        send(M, report, status, 'Describe key: %s', KeyName)
    ;   send(M, focus_function, @nil),
        (   get(M, send_method, MethodName, tuple(_, Impl))
        ->  get(Impl, summary, Summary),
            send(M, report, inform, 'Key %s executes %s: "%s"',
                 KeyName, MethodName, Summary)
        ;   send(M, report, inform, 'Key %s is not bound', KeyName)
        )
    ).

prefix_method(prefix).
prefix_method(prefix_or_cut).
prefix_method(prefix_or_copy).

key_binding_style(M, Style:key_binding_style) :->
    "Switch keyboard accelerator style"::
    send(@pce, key_binding_style, Style),
    send(M, report, status, 'Switched to %s style keys', Style).


                 /*******************************
                 *             PCE              *
                 *******************************/

xpce_manual(_M) :->
    "Start XPCE manual"::
    auto_call(manpce).

manpce(_M, Class:'behaviour|class*') :->
    "Start XPCE manual on behaviour or class"::
    (   Class == @nil
    ->  auto_call(manpce)
    ;   auto_call(manpce(Class))
    ).


editpce(M, Class:'behaviour|class*') :->
    "Edit XPCE class or class <->method"::
    (   Class == @nil
    ->  send(M, report, warning,
             'Enter "class" or "class->|<-|-selector"')
    ;   auto_call(editpce(Class))
    ).


tracepce(M, Method:behaviour*) :->
    "Put trace-point on XPCE class <->method"::
    (   Method == @nil
    ->  send(M, report, warning,
             'Enter "class->|<-|-selector"')
    ;   auto_call(tracepce(Method))
    ).


spypce(M, Method:behaviour*) :->
    "Put spy-point on XPCE class <->method"::
    (   Method == @nil
    ->  send(M, report, warning,
             'Enter "class->|<-|-selector"')
    ;   auto_call(spypce(Method))
    ).


                 /*******************************
                 *             DROP             *
                 *******************************/

preview_drop(M, Obj:object*) :->
    "Preview the upcomming drop action"::
    (   Obj == @nil
    ->  send(M, report, status, '')
    ;   send(Obj, instance_of, file)
    ->  send(M, report, status,
             'Please drop to switch to %s', Obj?absolute_path)
    ).


drop_files(M, Files:chain) :->
    "Drop chain of files"::
    send(Files, for_all, message(M, drop, create(file, @arg1))).


drop(M, Obj:object) :->
    "Import source-code from object"::
    (   send(Obj, instance_of, file)
    ->  send(M, find_file, Obj)
    ;   send(Obj, instance_of, chain)
    ->  send(Obj, for_all,
             if(message(@arg1, instance_of, object),
                message(M, drop, @arg1)))
    ).

:- emacs_end_mode.


                 /*******************************
                 *            FRAGMENT          *
                 *******************************/

:- pce_begin_class(emacs_colour_fragment, fragment,
                   "Provide colourised region").

variable(severity, {status,warning,error} := status, both, "Message severity").
variable(message,  string*,          both, "Message displayed").
variable(popup,    popup*,           both, "Associated popup menu").
variable(context,  any*,             both, "Popup context argument").

identify(F) :->
    (   get(F, message, Msg),
        Msg \== @nil
    ->  get(F, severity, Severity),
        (   Severity == status
        ->  send(F?text_buffer, report, status, Msg)
        ;   send(F?text_buffer, report, inform,
                 string('%s: %s', F?severity, Msg))
        )
    ;   true
    ).

:- pce_end_class.
