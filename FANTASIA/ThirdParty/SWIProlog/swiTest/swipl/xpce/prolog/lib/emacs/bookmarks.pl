/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        wielemak@science.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1999-2020, University of Amsterdam
                              CWI, Amsterdam
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

:- module(emacs_bookmarks, []).
:- use_module(library(pce)).
:- use_module(library(toolbar)).
:- use_module(library(pce_toc)).
:- use_module(library(pce_report)).
:- use_module(library(persistent_frame)).
:- require([ '$my_file'/1,
	     call_cleanup/2,
	     file_directory_name/2,
	     term_to_atom/2,
	     absolute_file_name/3,
	     default/3,
	     get_chain/3,
	     send_list/3
	   ]).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This module provides the first  definition   of  an advanced bookmarking
system   for   PceEmacs.   Bookmarks    are     kept    in    the   file
<config>/emacs_bookmarks as Prolog data. Bookmarks  can be annotated and
are time-stampted.

The bookmark mechanism is available through the Browse menu of PceEmacs.

Some issues to consider:

        * Save `collapsed' status of nodes?
        * Selective expansion
        * Search
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- pce_global(@emacs_mark_list, new(emacs_bookmark_editor)).

resource(save, image, image('16x16/save.xpm')).
resource(cut,  image, image('16x16/cut.xpm')).
resource(open, image, image('16x16/book2.xpm')).

:- pce_begin_class(emacs_bookmark_editor, persistent_frame,
                   "PceEmacs bookmark administration and viewing").

variable(file,         file, get, "File for holding the bookmarks").
variable(exit_message, code, get, "Registered exit message").

initialise(BM) :->
    send_super(BM, initialise, 'PceEmacs bookmarks'),
    send(BM, done_message, message(BM, status, hidden)),
    send(BM, append, new(D, dialog)),
    send(BM, fill_dialog),
    send(new(emacs_bookmark_window), below, D),
    send(new(V, view(size := size(40,8))), below, D),
    send(V, font, normal),
    send(V, ver_stretch, 0),
    send(@pce, exit_message, new(Msg, message(BM, save))),
    send(BM, slot, exit_message, Msg),
    ignore(send(BM, load)).

fill_dialog(BM) :->
    get(BM, member, dialog, D),
    send(D, pen, 0),
    send(D, gap, size(0, 5)),
    send(D, append, new(TB, tool_bar(BM))),
    send_list(TB, append,
              [ tool_button(save, resource(save), 'Save bookmarks'),
                gap,
                tool_button(goto, resource(open), 'Open editor'),
                tool_button(cut,  resource(cut),  'Delete selection')
              ]),
    send(D, append, graphical(0,0,10,1), right), % make a gap
    send(D, append, new(reporter), right),
    send(D, resize_message, message(D, layout, @arg2)).

unlink(BM) :->
    get(BM, exit_message, Msg),
    get(@pce, exit_messages, Chain),
    send(Chain, delete_all, Msg),
    send(BM, save),
    send_super(BM, unlink).


tree(BM, Tree:toc_tree) :<-
    get(BM, member, emacs_bookmark_window, W),
    get(W, tree, Tree).

view(BM, V:view) :<-
    "View for annotations"::
    get(BM, member, view, V).

selection(BM, Sel:'name|emacs_bookmark') :<-
    get(BM, member, emacs_bookmark_window, W),
    get(W, selection, Sel0),
    get(Sel0, map, @arg1?identifier, Sel1),
    get(Sel1, head, Sel).

:- pce_group(edit).

goto(BM) :->
    "Edit current selection"::
    get(BM, member, emacs_bookmark_window, W),
    (   get(BM, selection, Sel),
        send(Sel, instance_of, emacs_bookmark)
    ->  send(W, open_node, Sel)
    ;   send(BM, report, warning, 'No selection')
    ).

cut(BM) :->
    "Delete selected nodes"::
    get(BM, member, emacs_bookmark_window, W),
    (   get(W, selection, Nodes),
        \+ send(Nodes, empty)
    ->  send(Nodes, for_all, message(@arg1, delete_tree))
    ;   send(BM, report, warning, 'No selection')
    ).

:- pce_group(interface).

bookmark(F, BM:emacs_bookmark, Sort:[bool]) :->
    "Append a bookmark"::
    get(F, tree, Tree),
    send(Tree?root, append, BM, Sort).

append_hit(F, Buffer:emacs_buffer, SOL:int) :->
    "Add bookmark for indicated line"::
    get(Buffer, scan, SOL, line, 0, end, EOL),
    get(Buffer, contents, SOL, EOL-SOL, Title),
    send(Title, translate, '\t', ' '),
    get(Buffer, line_number, SOL, Line),
    (   get(Buffer, file, File),
        File \== @nil,
        get(File, absolute_path, FileName)
    ->  true
    ;   send(Buffer, report, warning, 'No associated file'),
        fail
    ),
    send(F, bookmark, new(BM, emacs_bookmark(FileName, Line, Title))),
    send(BM, link, Buffer),
    send(F, open).

loaded_buffer(F, TB:emacs_buffer) :->
    "PceEmacs has loaded a file"::
    get(F, tree, Tree),
    send(Tree?root, loaded_buffer, TB).

saved_buffer(_F, TB:emacs_buffer) :->
    "PceEmacs has saved this buffer"::
    send(TB, for_all_fragments,
         if(message(@arg1, send_hyper, bookmark, update))).


current(F, BM:emacs_bookmark*, UpdateSelection:[bool]) :->
    "Make this bookmark the current one"::
    (   UpdateSelection \== @off,
        get(F, member, emacs_bookmark_window, BW)
    ->  send(BW, selection, BM)
    ;   true
    ),
    get(F, view, View),
    (   get(View, modified, @on),
        get(View, hypered, bookmark, BM2)
    ->  send(BM2, note, View?contents)
    ;   true
    ),
    send(View, delete_hypers, bookmark),
    (   BM == @nil
    ->  send(View, clear),
        send(View, editable, @off),
        send(View, background, grey80)
    ;   new(_, hyper(View, BM, bookmark, editor)),
        (   get(BM, note, Note),
            Note \== @nil
        ->  send(View, contents, Note),
            send(View, modified, @off)
        ;   true
        ),
        send(View, editable, @on),
        send(View, background, white)
    ).

:- pce_group(file).

save(BM) :->
    "Save bookmarks to file"::
    send(BM, current, @nil),
    get(BM, bookmarks_file, write, File),
    get(BM, tree, Tree),
    get(Tree, root, Root),
    ignore(pce_catch_error(_, send(file(File), backup))),
    (   catch(setup_call_cleanup(
                  open(File, write, Fd),
                  ( format(Fd, '/* PceEmacs Bookmarks */~n~n', []),
                    send(Root, save, Fd)
                  ),
                  close(Fd)),
              _, fail)
    ->  send(BM, report, status, 'Saved bookmarks to %s', File)
    ;   send(BM, report, status, 'Failed to save bookmarks to %s', File)
    ).

load(BM) :->
    "Load bookmarks from file"::
    get(BM, bookmarks_file, File),
    catch(open(File, read, Fd), _, fail),
    call_cleanup(( read(Fd, Term0),
                   load_bookmarks(Term0, Fd, BM)
                 ),
                 close(Fd)).


load_bookmarks(end_of_file, _, _) :- !.
load_bookmarks(Term, Fd, BM) :-
    !,
    load_bookmark(Term, BM),
    read(Fd, Term2),
    load_bookmarks(Term2, Fd, BM).

load_bookmark(bookmark(File0, Line, Title, Stamp, Note), BM) :-
    !,
    (   absolute_file_name(File0,
                           [ access(read),
                             file_errors(fail)
                           ],
                           File)
    ->  new(Created, date),
        FStamp is float(Stamp),             % avoid overflow
        send(Created, posix_value, FStamp),
        send(BM, bookmark,
             new(M, emacs_bookmark(File, Line, Title, Created, Note)),
             @off),                 % do not sort
        (   get(@emacs, file_buffer, File, Buffer)
        ->  send(M, link, Buffer)
        ;   true
        )
    ;   true
    ).
load_bookmark(Term, BM) :-
    term_to_atom(Term, Atom),
    send(BM, report, warning, 'Unknown term in bookmarks file: %s', Atom).

bookmarks_file(BM, Access:[{read,write}], File:name) :<-
    (   get(BM, file, F),
        F \== @nil,
        send(F, access, Access)
    ->  get(F, absolute_path, File)
    ;   get(@pce, application_data, DataDir),
        (   Access == write
        ->  get(DataDir, path, Path),
            '$my_file'(Path)                % process owns path
        ;   true
        ),
        get(DataDir, file, emacs_bookmarks, F),
        get(F, absolute_path, File),
        send(BM, slot, file, File)          % use the absolute path
    ).

:- pce_end_class(emacs_bookmark_editor).

:- pce_begin_class(emacs_bookmark_window, toc_window).

initialise(BW) :->
    send_super(BW, initialise),
    send(BW, root, emacs_toc_bookmark_folder(/)).

open_node(BW, Id:any) :->
    "Open bookmark on double-click"::
    (   send(Id, instance_of, emacs_bookmark)
    ->  (   send(Id, exists)
        ->  ignore(send(Id, update)),
            send(@emacs, goto_source_location, Id, tab)
        ;   (   get(Id, file_name, File),
                send(@display, confirm,
                     'Marked file "%s" does not exist.\nDelete bookmark?',
                     File)
            ->  get(BW, node, Id, Node),
                send(Node, delete_tree)
            ;   true
            )
        )
    ).

select_node(BW, Id:any) :->
    "User selected a node"::
    (   send(Id, instance_of, emacs_bookmark)
    ->  send(BW?frame, current, Id)
    ;   true
    ).

selection(BW, Sel:any*) :->
    (   Sel == @nil
    ->  send(BW?frame, current, @nil, @off)
    ;   true
    ),
    send_super(BW, selection, Sel).

:- pce_end_class.

:- pce_begin_class(emacs_toc_bookmark_folder, toc_folder,
                   "Represent directory in bookmarks").

initialise(F, Path:name) :->
    (   Path == /
    ->  (   has_drives
        ->  RootName = 'My Computer'
        ;   RootName = '/'
        ),
        send_super(F, initialise, RootName, @nil)
    ;   get(file(Path), base_name, BaseName),
        send_super(F, initialise, BaseName, Path)
    ).

collapsed(F, Val:bool*) :->
    "Disable toc_window expansion mechanism"::
    send_class(F, node, collapsed(Val)).

append(F, BM:emacs_bookmark, Sort:[bool]) :->
    get(BM, file_name, FileName),
    get(F, identifier, Path),
    (   Path == @nil                % this is the root
    ->  true
    ;   send(FileName, prefix, Path)
    ),
    get(F, sons, Sons),
    (   get(Sons, find, message(@arg1, append, BM), _)
    ->  true
    ;   sub_directory(Path, FileName, SubPath),
        SubPath \== FileName,
        send(F, collapsed, @off),
        send(F, son, new(S, emacs_toc_bookmark_folder(SubPath))),
        send(S, append, BM),
        (   Sort \== @off
        ->  send(F, sort)
        ;   true
        )
    ;   send_class(F, node, collapsed(@off)),
        send(F, son, new(emacs_toc_bookmark(BM))),
        (   Sort \== @off
        ->  send(F, sort)
        ;   true
        )
    ).

sort(F) :->
    "Sort the nodes"::
    send(F, sort_sons, ?(@arg1, compare, @arg2)).

compare(F, N:toc_node, Diff:{smaller,equal,larger}) :<-
    "Put folders before files, otherwise alphabetical"::
    (   send(N, instance_of, toc_folder)
    ->  get(F, member, text, T0),
        get(N, member, text, T1),
        get(T0?string, compare, T1?string, Diff)
    ;   Diff = smaller
    ).

sub_directory(@nil, File, SubPath) :-
    !,
    (   has_drives
    ->  new(Re, regex('[a-zA-Z]:'))
    ;   new(Re, regex('/[^/]*'))
    ),
    send(Re, match, File),
    get(Re, register_value, File, 0, name, SubPath).
sub_directory(Path, File, SubPath) :-
    send(File, prefix, Path),
    file_directory_name(File, FileDir),
    (   FileDir == Path
    ->  SubPath = File
    ;   sub_directory(Path, FileDir, SubPath)
    ).


save(F, Fd:prolog) :->
    "Save bookmarks to file"::
    get_chain(F, sons, Sons),
    save_sons(Sons, Fd).

save_sons([], _).
save_sons([H|T], Fd) :-
    send(H, save, Fd),
    save_sons(T, Fd).

loaded_buffer(F, TB:emacs_buffer) :->
    "PceEmacs has loaded this buffer"::
    (   get(TB, file, File),
        File \== @nil,
        get(File, absolute_path, Path),
        get(F, identifier, Id),
        (   Id == @nil
        ->  true
        ;   send(Path, prefix, Id)
        )
    ->  send(F?sons, for_all,
             message(@arg1, loaded_buffer, TB))
    ;   true
    ).

:- pce_end_class(emacs_toc_bookmark_folder).

:- pce_begin_class(emacs_toc_bookmark, toc_file,
                   "Represent a bookmark").

initialise(F, BM:emacs_bookmark) :->
    get(BM, title, Title),
    get(BM, file_name, Path),
    get(file(Path), base_name, File),
    get(BM, line_no, Line),
    send_super(F, initialise,
               string('%s:%d %s', File, Line, Title), BM),
    send(BM, slot, node, F).

unlink(F) :->
    get(F, identifier, BM),
    send(BM, slot, node, @nil),
    send_super(F, unlink).

update(F) :->
    "Update label after changed bookmark"::
    get(F, identifier, BM),
    get(BM, title, Title),
    get(BM, file_name, Path),
    get(file(Path), base_name, File),
    get(BM, line_no, Line),
    send(F, label, string('%s:%d %s', File, Line, Title)).

append(_F, _BM:emacs_bookmark) :->
    "Can't append to a file"::
    fail.

save(F, Fd:prolog) :->
    "Save bookmarks to file"::
    get(F, identifier, BM),
    get(BM, term, bookmark(File, Line, Title, Stamp, NoteText)),
    format(Fd, 'bookmark(~q, ~q, ~q, ~0f, ~q).~n',
           [File, Line, Title, Stamp, NoteText]).

loaded_buffer(F, TB:emacs_buffer) :->
    "PceEmacs has loaded this buffer"::
    get(F, identifier, BM),
    get(BM, file_name, FileName),
    (   get(TB, file, File),
        File \== @nil,
        get(File, absolute_path, Path),
        Path == FileName
    ->  send(BM, link, TB)
    ;   true
    ).

compare(F, N2:toc_node, Diff:{smaller,equal,larger}) :<-
    (   send(N2, instance_of, emacs_toc_bookmark_folder)
    ->  Diff = larger
    ;   get(F, identifier, BM0),
        get(N2, identifier, BM1),
        (   get(BM0, file_name, F1),
            get(BM1, file_name, F2),
            get(file(F1), base_name, B1),
            get(file(F2), base_name, B2),
            get(B1, compare, B2, Diff),
            Diff \== equal
        ->  true
        ;   get(BM0, line_no, L0),
            get(BM1, line_no, L1),
            get(number(L0), compare, L1, Diff)
        )
    ).

:- pce_end_class(emacs_toc_bookmark).

:- pce_begin_class(emacs_bookmark, source_location,
                   "Bookmark in PceEmacs").

variable(title,   string,              get,  "Represented title").
variable(created, date,                get,  "Date of creation").
variable(note,    string*,             both, "Annotation").
variable(node,    emacs_toc_bookmark*, get,  "Visualiser").

initialise(BM, File:name, Line:int, Title:string,
           Created:[date], Note:[string]*) :->
    send_super(BM, initialise, File, Line),
    send(BM, slot, title, Title),
    (   Created == @default
    ->  send(BM, slot, created, new(date))
    ;   send(BM, slot, created, Created)
    ),
    default(Note, @nil, TheNote),
    send(BM, slot, note, TheNote).

term(BM, Term:prolog) :<-
    "Describe bookmark as a Prolog term"::
    ignore(send(BM, update)),
    get(BM, file_name, File),
    get(BM, line_no, Line),
    get(BM?title, value, Title),
    get(BM?created, posix_value, Stamp),
    (   get(BM, note, Note),
        Note \== @nil
    ->  get(Note, value, NoteText)
    ;   NoteText = ''
    ),
    Term = bookmark(File, Line, Title, Stamp, NoteText).

exists(BM) :->
    "Test whether associated file exists"::
    get(BM, file_name, File),
    send(file(File), exists).

:- pce_group(buffer).

link(BM, To:text_buffer) :->
    "Link the bookmark using a fragment"::
    get(BM, line_no, Line),
    get(To, scan, 0,   line, Line-1, start, SOL),
    get(To, scan, SOL, line, 0,      end,   EOL),
    new(_, emacs_bookmark_hyper(BM, fragment(To, SOL, EOL-SOL, bookmark))).
%       format('Linked ~p to ~p~n', [BM, To]).

update(BM) :->
    "If bookmark is linked, update <-line_no"::
    get(BM, hypered, fragment, Fragment),
    (   get(Fragment, text_buffer, TB),
        TB \== @nil
    ->  get(Fragment, start, Start),
        get(TB, line_number, Start, Line),
        (   get(BM, line_no, Line)
        ->  true
        ;   send(BM, line_no, Line),
            Modified = true
        ),
        get(Fragment, string, Title),
        send(Title, translate, '\t', ' '),
        (   send(BM?title, equal, Title)
        ->  true
        ;   send(BM, slot, title, Title),
            Modified = true
        ),
        (   Modified == true
        ->  send(BM, modified)
        ;   true
        )
    ;   true                        % destroy?
    ).

modified(BM) :->
    "Bookmark parameters have been modified"::
    get(BM, node, Node),
    send(Node, update).

:- pce_end_class(emacs_bookmark).


:- pce_begin_class(emacs_bookmark_hyper, hyper,
                   "Hyper from bookmark to fragment").

initialise(H, BM:emacs_bookmark, To:fragment) :->
    send_super(H, initialise, BM, To, fragment, bookmark).

unlink_from(H) :->
    "Bookmark is deleted"::
    get(H, to, Fragment),
    free(Fragment),
    free(H).

unlink_to(H) :->
    "Fragment is deleted, update line"::
    get(H, from, BM),
    send(BM, update),
    free(H).

:- pce_end_class.

                 /*******************************
                 *             MISC             *
                 *******************************/

:- dynamic
    has_drives/1.

%       See whether there is only one logical root in the filesystem or
%       there are multiple.

has_drives :-
    has_drives(True),
    !,
    True = true.
has_drives :-
    (   get(directory(.), roots, Roots),
        get(Roots, size, 1)
    ->  assert(has_drives(false)),
        fail
    ;   assert(has_drives(true))
    ).
