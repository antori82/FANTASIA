/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  2001-2024, University of Amsterdam
                              VU University Amsterdam
                              CWI, Amsterdam
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

:- module(prolog_navigator, []).
:- use_module(library(pce)).
:- use_module(library(persistent_frame)).
:- use_module(library(toc_filesystem)).
:- use_module(library(pce_report)).
:- use_module(library(toolbar)).
% used in load hook: cannot be autoloaded.
:- use_module(library(trace/util),[canonical_source_file/2]).

:- autoload(browse_xref,
	    [ x_browse_info/2,
	      x_browse_analyse/1,
	      system_predicate/1,
	      global_predicate/1
	    ]).
:- use_module(library(debug),[debug/3]).
:- autoload(library(prolog_code), [head_name_arity/3]).
:- autoload(library(prolog_debug), [nospy/1, spy/1]).
:- autoload(library(edit),[edit/1]).
:- autoload(library(help),[help/1]).
:- autoload(library(lists),[member/2]).
:- autoload(library(pce_debug),
	    [nospypce/1,spypce/1,notracepce/1,tracepce/1]).
:- autoload(library(pce_image),[pce_image_directory/1]).
:- autoload(library(pce_manual),[manpce/1,manpce/0]).
:- autoload(library(pce_util),[send_list/3,default/3,get_chain/3]).
:- autoload(library(prolog_source),
	    [ prolog_open_source/2,
	      prolog_read_source_term/4,
	      prolog_close_source/1
	    ]).
:- autoload(library(prolog_trace),[trace/2,trace/1]).
:- autoload(library(swi_ide),[prolog_ide/1]).
:- if(exists_source(library(pldoc/man_index))).
:- autoload(library(pldoc/man_index),[man_object_property/2]).
:- endif.

:- pce_image_directory(library('trace/icons')).

:- dynamic
    prolog_overview_window/1.

resource(edit,        image, image('16x16/edit.xpm')).
resource(up,          image, image('16x16/up.xpm')).
resource(refresh,     image, image('16x16/refresh.xpm')).
resource(butterfly,   image, image('butterfly.xpm')).
resource(dbgsettings, image, image('16x16/dbgsettings.xpm')).

:- pce_begin_class(prolog_navigator, persistent_frame,
                   "Prolog source navigator").

initialise(SB, Root:directory) :->
    send_super(SB, initialise, 'Prolog Navigator'),
    send(SB, icon, resource(butterfly)),
    send(SB, append, new(D, dialog)),
    send(new(W, prolog_source_structure(Root)), below, D),
    send(D, append, new(tool_bar(W))),
    send(D, gap, size(0, 2)),
    send(D, pen, 0),
    send(SB, fill_tool_bar),
    send(new(report_dialog), below, W).

tool_bar(SB, TB:tool_bar) :<-
    "Get the toolbar"::
    get(SB, member, dialog, D),
    get(D, member, tool_bar, TB).

fill_tool_bar(SB) :->
    "Fill the toolbar"::
    get(SB, tool_bar, TB),
    send_list(TB, append,
              [ tool_button(up,
                            resource(up),
                            'Up one level'),
                tool_button(refresh,
                            resource(refresh),
                            'Update view'),
                gap,
                tool_button(debug_settings,
                            resource(dbgsettings),
                            'Edit breakpoints'),
                tool_button(edit,
                            resource(edit),
                            'Open file in editor')
              ]).

goto(SB, File:file, Line:int) :->
    "Expand and highlight tree for given location"::
    get(SB, member, prolog_source_structure, FB),
    send(FB, goto, File, Line).

directory(SB, Dir:directory) :->
    "Make directory visible"::
    get(SB, member, prolog_source_structure, FB),
    get(FB, dir_node, Dir, @on, _Node).

:- pce_end_class(prolog_navigator).


:- pce_begin_class(prolog_source_structure, toc_filesystem,
                   "Browser for (prolog) source-files").

class_variable(background,   colour, white).
class_variable(colour,       colour, black).
class_variable(auto_refresh, int*, @nil).
class_variable(size,    size,   size(200, 500),
               "Intial window size").

variable(file_pattern,  regex, get, "Pattern of showed files").

initialise(FB, Root:directory) :->
    source_pattern(Regex),
    send(FB, slot, file_pattern, Regex),
    send_super(FB, initialise, Root),
    send(FB?frame, label, 'SWI-Prolog Navigator'),
    asserta(prolog_overview_window(FB)).

source_pattern(Pat) :-
    findall(E, (user:prolog_file_type(E, prolog),
                \+ user:prolog_file_type(E, qlf)), Exts),
    (   Exts = [Ext]
    ->  format(atom(Pat), '.*\\.~w$', [Ext])
    ;   atomic_list_concat(Exts, '|', P1),
        format(atom(Pat), '.*\\.(~w)$', [P1])
    ).

unlink(FB) :->
    retractall(prolog_overview_window(FB)),
    send_super(FB, unlink).

make_file_node(_FB, File:file, Node:sb_prolog_file) :<-
    "Return a Prolog source-file node"::
    new(Node, sb_prolog_file(File)).

:- pce_group(navigate).

file_node(FB, File:name, Create:[bool], Node:toc_node) :<-
    "Get node for file, possibly add it to the tree"::
    canonical_source_file(File, Path),
    (   get(FB, node, Path, Node)
    ->  true
    ;   Create == @on
    ->  file_directory_name(Path, Dir),
        get(FB, dir_node, Dir, @on, DirNode),
        send(DirNode, collapsed, @off),
        get(FB, node, Path, Node)
    ).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
->goto: File, Line opens  the  tree   such  that  the indicated position
becomes visible and selects the entity   holding the specified location.
First it looks for the file, then it  assumes the sons are in file-order
and looks for the first son after the requested line. After finding this
it iterates on this.

This method is intended to synchronise with an editor.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

goto(FB, File:'file|node', Line:int) :->
    "Show indicated position"::
    (   send(File, instance_of, file)
    ->  get(FB, file_node, File?name, @on, Node)
    ;   Node = File
    ),
    (   (   get(Node, collapsed, @nil)
        ;   send(Node, instance_of, sb_predicate)
        )
    ->  send(FB?tree, selection, Node),
        send(FB, normalise, Node)
    ;   send(Node, collapsed, @off),
        new(N, var(value := @nil)),
        (   get(Node?sons, find,
                and(message(@arg1, has_get_method, line),
                    if(and(@arg1?line \== @nil,
                           @arg1?line > Line),
                       new(and),
                       and(assign(N, @arg1, global),
                           new(or)))),
                _)
        ->  get(N, '_value', N2),
            (   N2 == @nil
            ->  send(FB?tree, selection, Node),
                send(FB, normalise, Node)
            ;   send(FB, goto, N2, Line)
            )
        ;   get(Node?sons, tail, Last)
        ->  send(FB, goto, Last, Line)
        ;   send(FB?tree, selection, Node),
            send(FB, normalise, Node)
        )
    ).

:- pce_group(popup).

popup(FB, Id:any, Popup:popup) :<-
    "Return popup from current node"::
    get(FB, node, Id, Node),
    (   send(Node, has_get_method, popup),
        get(Node, popup, Popup)
    ->  true
    ;   send(Node, instance_of, toc_directory)
    ->  new(Popup, popup(options)),
        send(Popup, append,
             menu_item(expand_all,
                       message(Node, expand_all)))
    ).


:- pce_group(edit).

edit(FB) :->
    "Edit selected file"::
    (   get(FB, selection, Sel),
        get(Sel, head, FileNode),
        send(FileNode, instance_of, sb_prolog_file),
        get(FileNode, identifier, File),
        edit(file(File))
    ;   send(FB, report, warning, 'No selected file'),
        fail
    ).

debug_settings(_FB) :->
    "Open debug-status editor"::
    prolog_ide(open_debug_status).

:- pce_group(event).

event(FB, Ev:event) :->
    "Deal with identifying nodes"::
    (   send_super(FB, event, Ev)
    ->  true
    ;   send(Ev, is_a, loc_move)
    ->  (   get(FB, hypered, current, Node)
        ->  (   send(Ev, inside, Node)
            ->  true
            ;   send(FB, delete_hypers, current),
                send(FB, report, status, '')
            )
        ;   get(FB, find, Ev, @arg1?node, Img),
            new(_, hyper(FB, Img, current, toc)),
            get(Img, node, Node),
            (   send(Node, has_send_method, identify)
            ->  send(Node, identify)
            ;   true
            )
        )
    ).

:- pce_end_class(prolog_source_structure).


:- pce_begin_class(sb_prolog_file, toc_folder,
                   "Display a Prolog file").

initialise(TF, File:file) :->
    get(File, name, FileName),
    canonical_source_file(FileName, Path),
    file_image(Path, Img),
    file_base_name(FileName, Base),
    send_super(TF, initialise, Base, Path, Img),
    send(TF, name, Base).

update_image(_TF) :->
    true.

loaded(TF) :->
    get(TF, identifier, Path),
    source_file(Path).

included(TF) :->
    get(TF, identifier, Path),
    included_file(Path).

file_image(Path, 'plloadedfile.xpm') :-
    source_file(Path),
    !.
file_image(Path, 'plincludedfile.xpm') :-
    included_file(Path),
    !.
file_image(_, 'plfile.xpm').

included_file(Path) :-
    source_file_property(Path, included_in(_,_)).


module(TF, Module:name) :<-
    "Return module defined in this file"::
    get(TF, identifier, Path),
    (   x_browse_info(Path, entity(module(Module), _Line))
    ->  true
    ;   catch(module_of_path(Path, Module), _, fail)
    ).

module_of_path(Path, Module) :-
    catch(setup_call_cleanup(
              prolog_open_source(Path, Stream),
              prolog_read_source_term(Stream, Term, _, []),
              prolog_close_source(Stream)), _,
          fail),
    Term = (:- module(Module, _Public)).

hidden_entity(module(_)).

file_expansion_entity(Path, entity(module(Module), Line)) :-
    once(x_browse_info(Path, entity(module(Module), Line))).
file_expansion_entity(Path, entity(dynamic, -)) :-
    once(file_expansion_entity(Path, entity(dynamic(_), _))).
file_expansion_entity(Path, Entity) :-
    x_browse_info(Path, Entity),
    arg(1, Entity, Term),
    \+ hidden_entity(Term).

expand(TF) :->
    get(TF, identifier, Path),
    get(TF, window, TocWindow),
    x_browse_analyse(Path),
    (   file_expansion_entity(Path, entity(Info, Line)),
        make_file_toc_entry(Info, Path, Entry),
        send(TocWindow, son, TF, Entry),
        send(Entry, file_id, Path),
        integer(Line),
        send(Entry, line, Line),
        fail
    ;   true
    ).

expand_all(_TF) :->
    true.

split_head(M:Head, Name, Arity, M) :-
    !,
    callable(Head),
    head_name_arity(Head, Name, Arity).
split_head(Head, Name, Arity, @nil) :-
    callable(Head),
    head_name_arity(Head, Name, Arity).

make_file_toc_entry(predicate(Head), Key, TE) :-
    split_head(Head, Name, Arity, Module),
    new(TE, sb_predicate(Key, Name, Arity, Module)).
make_file_toc_entry(grammar_rule(Head), Key, TE) :-
    split_head(Head, Name, Arity, Module),
    new(TE, sb_predicate(Key, Name, Arity, Module)).
make_file_toc_entry(Term, _Key, TE) :-
    make_file_toc_entry(Term, TE).

make_file_toc_entry(xpce_class(Class, _Super, Doc), TE) :-
    to_summary(Doc, PceDoc),
    new(TE, toc_xpce_class(Class, PceDoc)).
make_file_toc_entry(xpce_class_extension(Class), TE) :-
    new(TE, toc_xpce_class(Class, @default, 'classext.xpm')).
make_file_toc_entry(module(Module), TE) :-
    new(TE, toc_module(Module, @default, 'module.xpm')).
make_file_toc_entry(dynamic, TE) :-
    new(TE, sb_predicate_list(dynamic, @default, 'mini-run.xpm')).

to_summary(Doc, String) :-
    catch(string_codes(String, Doc), _, fail),
    !.
to_summary(_, @default).

local_predicate_name(M:Head, Label) :-
    !,
    callable(Head),
    head_name_arity(Head, Name, Arity),
    atomic_list_concat([M, :, Name, /, Arity], Label).
local_predicate_name(Head, Label) :-
    head_name_arity(Head, Name, Arity),
    atomic_list_concat([Name, /, Arity], Label).

identify(TF) :->
    "Identify myself"::
    get(TF, identifier, Path),
    (   send(TF, loaded)
    ->  send(TF, report, status, 'Loaded file %s', Path)
    ;   send(TF, included)
    ->  send(TF, report, status, 'Included file %s', Path)
    ;   send(TF, report, status, 'File %s', Path)
    ).

:- pce_group(popup).

:- free(@sb_file_popup).
:- pce_global(@sb_file_popup, make_sb_file_popup).

make_sb_file_popup(P) :-
    new(P, popup(source_options)),

    send_list(P, append,
              [ menu_item(edit,
                          message(@arg1, edit)),
                menu_item(consult,
                          message(@arg1, consult))
              ]).

popup(_, Popup:popup) :<-
    Popup = @sb_file_popup.

edit(TF) :->
    get(TF, identifier, Path),
    edit(file(Path)).

consult(TF) :->
    "Load into Prolog"::
    get(TF, identifier, Path),
    ensure_loaded(user:Path).

:- pce_end_class(sb_prolog_file).

:- pce_begin_class(toc_source_folder, toc_folder,
                   "Representation of a source entity").

variable(file_id,       name,   both, "File it was loaded from").
variable(line,          int*,   both, "Line it is associated with").

update_image(_) :->
    true.

open(TE) :->
    "Synonym for ->edit"::
    send(TE, edit).

edit(TE) :->
    "Open definition in editor"::
    get(TE, file_id, File),
    get(TE, line, Line),
    (   integer(Line)
    ->  edit(file(File, line(Line)))
    ;   send(TE, report, error, 'No source')
    ).

has_source(TE) :->
    "Has associated source"::
    get(TE, line, Line),
    integer(Line).

status(TE, Status:{open,close}) :<-
    get(TE, collapsed, Val),
    (   Val == @on
    ->  Status = close
    ;   Status = open
    ).

:- pce_group(popup).

:- free(@source_popup).
:- pce_global(@source_popup, make_source_popup).

make_source_popup(P) :-
    new(P, popup(source_options)),

    send_list(P, append,
              [ menu_item(edit,
                          message(@arg1, edit),
                          condition := message(@arg1, has_source))
              ]).

popup(_, Popup:popup) :<-
    Popup = @source_popup.

:- pce_end_class.

:- pce_begin_class(toc_xpce_entity, toc_file,
                   "Representation of an XPCE source entity").

variable(file_id,       name,   both, "File it was loaded from").
variable(line,          int*,   both, "Line it is associated with").


open(TE) :->
    send(TE, edit).

edit(TE) :->
    "Edit the source"::
    get(TE, file_id, File),
    get(TE, line, Line),
    (   integer(Line)
    ->  edit(file(File, line(Line)))
    ;   send(TE, report, error, 'No source')
    ).

has_source(TE) :->
    "Has associated source"::
    get(TE, line, Line),
    integer(Line).

loaded(TE) :->
    "Test if class is loaded"::
    get(TE, identifier, Id),
    atomic_list_concat([_Type, _Name, Class], $, Id),
    pce_prolog_class(Class).

behaviour(TE, Behaviour:behaviour) :<-
    "Get behaviour (if loaded)"::
    get(TE, identifier, Id),
    atomic_list_concat([Type, Name, Class], $, Id),
    get(@pce, convert, Class, class, ClassObj),
    (   Type == send
    ->  get(ClassObj, send_method, Name, Behaviour)
    ;   Type == get
    ->  get(ClassObj, get_method, Name, Behaviour)
    ;   Type == var
    ->  get(ClassObj, instance_variable, Name, Behaviour)
    ;   Type == cvar
    ->  get(ClassObj, class_variable, Name, Behaviour)
    ).

spy(TE, Val:[bool]) :->
    "Set spy-point"::
    get(TE, behaviour, Behaviour),
    (   Val == @off
    ->  nospypce(Behaviour)
    ;   spypce(Behaviour)
    ).

trace(TE, Val:[bool]) :->
    "Set trace-point"::
    get(TE, behaviour, Behaviour),
    (   Val == @off
    ->  notracepce(Behaviour)
    ;   tracepce(Behaviour)
    ).

identify(TE) :->
    "Identify myself"::
    get(TE, identifier, Id),
    atomic_list_concat([Type, Name, Class], $, Id),
    identify_behaviour(Type, Name, Class, TE).

identify_behaviour(send, Name, Class, TE) :-
    send(TE, report, status, 'XPCE send method %s->%s', Class, Name).
identify_behaviour(get, Name, Class, TE) :-
    send(TE, report, status, 'XPCE get method %s<-%s', Class, Name).
identify_behaviour(var, Name, Class, TE) :-
    send(TE, report, status, 'XPCE instance variable %s-%s', Class, Name).
identify_behaviour(cvar, Name, Class, TE) :-
    send(TE, report, status, 'XPCE class variable %s.%s', Class, Name).

:- pce_group(popup).

:- free(@sb_xpce_behaviour_popup).
:- pce_global(@sb_xpce_behaviour_popup,
              make_sb_xpce_behaviour_popup).

make_sb_xpce_behaviour_popup(P) :-
    new(P, popup(predicate_options)),

    send_list(P, append,
              [ menu_item(edit,
                          message(@arg1, open),
                          condition := message(@arg1, has_source)),
                menu_item(spy,
                          message(@arg1, spy),
                          condition := message(@arg1, loaded)),
                menu_item(trace,
                          message(@arg1, trace),
                          condition := message(@arg1, loaded))
              ]).

popup(_, Popup:popup) :<-
    Popup = @sb_xpce_behaviour_popup.

:- pce_end_class(toc_xpce_entity).

:- pce_begin_class(toc_xpce_class, toc_source_folder,
                   "Representation of a class (or extension)").

variable(class_id,      name,    get, "Class it represents").
variable(summary,       string*, get, "Summary documentation").

initialise(CF, Class:name, Summary:[string], Image:[image]) :->
    "Create from ClassName, Summary and Image"::
    default(Summary, @nil, Sum),
    default(Image, 'class.xpm', Img),
    send_super(CF, initialise, Class, @default, Img),
    send(CF, slot, class_id, Class),
    send(CF, slot, summary, Sum).


expand(CF) :->
    get(CF, identifier, NodeId),
    get(CF, file_id, BrowseId),
    get(CF, class_id, Class),
    get(CF, window, TocWindow),
    (   file_expansion_entity(BrowseId, entity(Info, Line)),
        make_class_toc_enter(Info, Class, BrowseId, Entry),
        send(TocWindow, son, NodeId, Entry),
        send(Entry, file_id, BrowseId),
        integer(Line),
        send(Entry, line, Line),
        fail
    ;   true
    ).

make_class_toc_enter(xpce_class_local_predicate(Class,Head), Class, Key, TE) :-
    make_file_toc_entry(predicate(Head), Key, TE),
    !.
make_class_toc_enter(Term, Class, _Key, TE) :-
    make_class_toc_enter(Term, Class, TE).

make_class_toc_enter(xpce_method(send(Class, Name, _Doc)), Class, TE) :-
    atomic_list_concat([send, Name, Class], $, Id),
    new(TE, toc_xpce_entity(Name, Id, 'send.xpm')).
make_class_toc_enter(xpce_method(get(Class, Name, _Doc)), Class, TE) :-
    atomic_list_concat([get, Name, Class], $, Id),
    new(TE, toc_xpce_entity(Name, Id, 'get.xpm')).
make_class_toc_enter(xpce_variable(Class, Name, _Doc), Class, TE) :-
    atomic_list_concat([var, Name, Class], $, Id),
    new(TE, toc_xpce_entity(Name, Id, 'ivar.xpm')).
make_class_toc_enter(xpce_class_variable(Class, Name, _Doc), Class, TE) :-
    atomic_list_concat([cvar, Name, Class], $, Id),
    new(TE, toc_xpce_entity(Name, Id, 'classvar.xpm')).

identify(CF) :->
    "Report who I am"::
    get(CF, class_id, Class),
    (   get(CF, summary, Summary),
        Summary \== @nil
    ->  send(CF, report, status, 'XPCE class %s (%s)', Class, Summary)
    ;   send(CF, report, status, 'XPCE class %s', Class)
    ).

:- pce_group(popup).

:- free(@sb_xpce_class_popup).
:- pce_global(@sb_xpce_class_popup, make_sb_xpce_class_popup).

make_sb_xpce_class_popup(P) :-
    new(P, popup(source_options)),

    send_list(P, append,
              [ menu_item(edit,
                          message(@arg1, edit),
                          condition := message(@arg1, has_source),
                          end_group := @on),
                menu_item(class_details,
                          message(@arg1, class_details),
                          condition := message(@arg1, loaded)),
                menu_item(class_hierarchy,
                          message(@arg1, class_hierarchy),
                          condition := message(@arg1, loaded))
              ]).

popup(_, Popup:popup) :<-
    Popup = @sb_xpce_class_popup.

loaded(CF) :->
    "Test if class is loaded"::
    get(CF, class_id, Class),
    pce_prolog_class(Class).

class_details(CF) :->
    "Open ClassBrowser"::
    get(CF, class_id, Class),
    manpce(Class).

class_hierarchy(CF) :->
    "Open and direct ClassHierarchy"::
    get(CF, class_id, Class),
    manpce,
    get(@manual, start_tool, class_hierarchy, Tool),
    send(Tool, focus, Class).

:- pce_end_class(toc_xpce_class).

:- pce_begin_class(toc_module, toc_source_folder,
                   "Representation of the module").

expand(MF) :->
    get(MF, identifier, NodeId),
    get(MF, file_id, BrowseId),
    get(MF, window, TocWindow),
    (   x_browse_info(BrowseId, export(Head)),
        (   x_browse_info(BrowseId, entity(predicate(Head), Line))
        ->  make_file_toc_entry(predicate(Head), BrowseId, Entry),
            send(Entry, file_id, BrowseId),
            send(Entry, line, Line)
        ;   local_predicate_name(Head, Label),
            atom_concat('$export$', Label, Id),
            new(Entry, toc_file(Label, Id, 'pred.bm'))
        ),
        send(TocWindow, son, NodeId, Entry),
        fail
    ;   true
    ).

update_image(MF) :->
    get(MF, status, Status),
    image(module, Status, Image),
    send(MF, image, Image).

:- pce_end_class.

:- pce_begin_class(sb_predicate_list, toc_source_folder,
                   "Representation of predicate set").

variable(set,   name,   get, "Name of the represented set").

initialise(PL, Name:name, Id:any, Img:[image]) :->
    send(PL, send_super, initialise, Name, Id, Img),
    send(PL, slot, set, Name).

expand(MF) :->
    get(MF, identifier, NodeId),
    get(MF, set, Set),
    get(MF, file_id, BrowseId),
    get(MF, window, TocWindow),
    Term =.. [Set, Head],
    (   file_expansion_entity(BrowseId, entity(Term, Line)),
        make_file_toc_entry(predicate(Head), BrowseId, Entry),
        send(Entry, file_id, BrowseId),
        send(Entry, line, Line),
        send(TocWindow, son, NodeId, Entry),
        fail
    ;   true
    ).

update_image(MF) :->
    get(MF, set, Set),
    get(MF, status, Status),
    image(Set, Status, Image),
    send(MF, image, Image).

:- pce_end_class.

:- pce_begin_class(sb_predicate, toc_source_folder,
                   "Represents a predicate").

variable(name,           name,  get, "Name of the represented predicate").
variable(arity,          int,   get, "Arity of it").
variable(module,         name*, get, "Module (or local)").
variable(classification, name,  get, "Class of the predicate").

initialise(P, BrowseId:name, Name:name, Arity:int, Module:[name]*) :->
    default(Module, @nil, M),
    head_name_arity(Head0, Name, Arity),
    (   M == @nil
    ->  Head = Head0
    ;   Head = M:Head0
    ),
    local_predicate_name(Head, Label),
    classify_predicate(Head, BrowseId, Classification),
    send(P, slot, classification, Classification),
    image(predicate, Classification, Img),
    send(P, send_super, initialise, Label, @default, Img),
    send(P, slot, name, Name),
    send(P, slot, arity, Arity),
    send(P, slot, module, M),
    (   expandable(Head, Classification)
    ->  true
    ;   send(P, collapsed, @nil)
    ).

file_node(P, Node:sb_prolog_file) :<-
    "Find associated file-node"::
    file_node(P, Node).

file_node(Node, Node) :-
    send(Node, instance_of, sb_prolog_file),
    !.
file_node(Node, FileNode) :-
    get_chain(Node, parents, Parents),
    member(Parent, Parents),
    file_node(Parent, FileNode),
    !.

head(P, Qualify:[bool], Head:prolog) :<-
    "Get the head"::
    get(P, module, M),
    get(P, name, Name),
    get(P, arity, Arity),
    head_name_arity(Head0, Name, Arity),
    (   M == @nil
    ->  (   Qualify == @on
        ->  (   get(P, file_node, SbPrologFile),
                get(SbPrologFile, module, Module)
            ->  Head = Module:Head0
            ;   Head = user:Head0
            )
        ;   Head = Head0
        )
    ;   Head = M:Head0
    ).

expandable(Head, _) :-
    prolog_xbrowse:called(_, Head).

classify_predicate(Head, Key, dcg) :-
    x_browse_info(Key, entity(grammar_rule(Head), _)),
    !.
classify_predicate(Head, Key, dynamic) :-
    x_browse_info(Key, entity(dynamic(Head), _)),
    !.
classify_predicate(Head, _, imported) :-
    prolog_xbrowse:imported(Head),
    !.
classify_predicate(Head, Key, exported) :-
    x_browse_info(Key, export(Head)).
classify_predicate(Head, _, built_in) :-
    system_predicate(Head),
    !.
classify_predicate(Head, _, global) :-
    global_predicate(Head),
    !.
classify_predicate(Head, Key, incomplete) :-
    x_browse_info(Key, entity(unreferenced_call(Head, _), _)),
    !.
classify_predicate(Head, Key, unreferenced) :-
    x_browse_info(Key, entity(unreferenced_predicate(Head), _)),
    !.
classify_predicate(Head, Key, undefined) :-
    x_browse_info(Key, entity(unreferenced_call(_, To), _)),
    memberchk(Head, To),
    !.
classify_predicate(Head, _Key, fact) :-
    \+ prolog_xbrowse:called(_, Head),
    !.
classify_predicate(_, _, local).

expand(P) :->
    get(P, file_id, Key),
    get(P, head, Head),
    get(P, window, TocWindow),
    (   prolog_xbrowse:called(Called, Head),
        make_file_toc_entry(predicate(Called), Key, TE),
        send(TocWindow, son, P, TE),
        send(TE, slot, file_id, Key),
        predicate_location(Key, Called, Line),
        send(TE, slot, line, Line),
        fail
    ;   true
    ).

predicate_location(K, Called, Line) :-
    x_browse_info(K, entity(predicate(Called), Line)),
    !.
predicate_location(K, Called, Line) :-
    x_browse_info(K, entity(dynamic(Called), Line)),
    !.
predicate_location(K, Called, Line) :-
    x_browse_info(K, entity(grammar_rule(Called), Line)),
    !.
predicate_location(K, Called, Line) :-
    x_browse_info(K, entity(xpce_class_local_predicate(_, Called), Line)),
    !.

identify(P) :->
    "Identify myself as status"::
    get(P, classification, Class),
    get(P, name, Name),
    get(P, arity, Arity),
    identify_predicate(Class, Name/Arity, P).

identify_predicate(fact, Name/Arity, P) :-
    send(P, report, status,
         'Unit-clause predicate %s/%d', Name, Arity).
identify_predicate(Class, Name/Arity, P) :-
    send(P, report, status,
         '%s predicate %s/%d', Class?label_name, Name, Arity).

open(P) :->
    "Edit, manual or expand"::
    (   send(P, has_source)
    ->  send(P, edit)
    ;   send(P, has_manual)
    ->  send(P, manual)
    ;   send_super(P, open)
    ).

manual(P) :->
    get(P, name, Name),
    get(P, arity, Arity),
    (   help(Name/Arity)
    ->  true
    ;   send(P, report, warning, 'No help for %s/%d', Name, Arity)
    ).

has_manual(P) :->
    "Succeed if there is a manual-page"::
    get(P, name, Name),
    get(P, arity, Arity),
    man_predicate_summary(Name/Arity, _).

:- if(current_predicate(man_object_property/2)).
man_predicate_summary(PI, Summary) :-
    man_object_property(PI, Summary).
:- endif.
man_predicate_summary(_, _) :-
    fail.

built_in(P) :->
    "True is represented predicate is builtin"::
    get(P, head, Head),
    system_predicate(Head).

loaded(P) :->
    "Test if represented predicate is loaded"::
    get(P, file_node, Node),
    send(Node, loaded).

spy(P, Val:[bool]) :->
    "Switch spying on/off"::
    get(P, head, @on, Head),
    (   Val == @off
    ->  nospy(Head)
    ;   spy(Head)
    ).

trace(P, Val:[bool]) :->
    "Switch tracing on/off"::
    get(P, head, @on, Head),
    (   Val == @off
    ->  trace(Head, -all)
    ;   trace(Head)
    ).

:- free(@prolog_predicate_popup).
:- pce_global(@prolog_predicate_popup,
              make_prolog_predicate_popup).

make_prolog_predicate_popup(P) :-
    new(P, popup(predicate_options)),

    send_list(P, append,
              [ menu_item(edit,
                          message(@arg1, open),
                          condition := message(@arg1, has_source)),
                menu_item(spy,
                          message(@arg1, spy),
                          condition := message(@arg1, loaded)),
                menu_item(trace,
                          message(@arg1, trace),
                          condition := message(@arg1, loaded)),
                menu_item(manual,
                          message(@arg1, manual),
                          condition := message(@arg1, has_manual))
              ]).

popup(_, Popup:popup) :<-
    Popup = @prolog_predicate_popup.

:- pce_end_class(sb_predicate).


image(module,           open,           'openmodule.xpm').
image(module,           closed,         'module.xpm').

image(dynamic,          open,           'mini-run.xpm').
image(dynamic,          closed,         'mini-run.xpm').

image(predicate,        built_in,       'builtin.xpm').
image(predicate,        global,         'mini-globe.xpm').
image(predicate,        dynamic,        'mini-run.xpm').
image(predicate,        imported,       'import.xpm').
image(predicate,        exported,       'export.xpm').
image(predicate,        incomplete,     'warnpred.xpm').
image(predicate,        unreferenced,   'unrefpred.xpm').
image(predicate,        undefined,      'undefpred.xpm').
image(predicate,        fact,           'fact.bm').
image(predicate,        local,          'pred.bm').
image(predicate,        dcg,            'grammar.bm').



                 /*******************************
                 *             HOOK             *
                 *******************************/

:- multifile
    user:message_hook/3.

image_of_load_state(start, _,       'loading.xpm').
image_of_load_state(true,  load,    'plloadedfile.xpm').
image_of_load_state(true,  include, 'plincludedfile.xpm').
image_of_load_state(false, _,       'loadfailed.xpm').

user:message_hook(load_file(What), _Kind, _Lines) :-
    loading(What, load).
user:message_hook(include_file(What), _Kind, _Lines) :-
    loading(What, include).

loading(What, How) :-
    load_info(What, File, Stage),
    prolog_overview_window(Win),
    (   file_name_extension(_, qlf, File)
    ->  debug(gtrace(qlf), 'Looking for ~q', [File]),
        '$qlf_sources'(File, Sources),
        debug(gtrace(qlf), 'Contains ~q', [Sources]),
        member(TheFile, Sources)
    ;   TheFile = File
    ),
    get(Win, file_node, TheFile, Node),
    image_of_load_state(Stage, How, Img),
    in_pce_thread(update_image(Node, Img)),
    fail.

update_image(Node, Img) :-
    send(Node, image, Img),
    send(Node, flush).

load_info(start(_Level, file(_, Path)),
          Path, start).
load_info(failed(Spec),
          Path, false) :-
    absolute_file_name(Spec,
                       [ file_type(prolog),
                         access(read)
                       ],
                       Path).
load_info(done(_Level, file(_, Path), _, _, _, _),
          Path, true).
load_info(done(_Level, file(_, Path)),
          Path, true).

