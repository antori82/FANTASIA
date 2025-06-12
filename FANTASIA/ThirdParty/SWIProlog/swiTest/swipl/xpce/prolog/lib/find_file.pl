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

:- module(pce_finder, []).
:- use_module(library(pce)).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This file defines the driver for prompting   files. Upto XPCE 6.0.5 this
module defined class finder as a subclass  of class dialog prompting for
files. If the display implemented  <-win_file_name (Windows), the <-file
method of finder called this method.

Now,  @finder  is  a  simple   autoload    object   that   either  loads
find_file_dialog or used `display<-win_file_name'.   This approach makes
the code more readable and reduces resources on the Windows version. Any
version of the system can use class find_file_dialog to realise portable
embedable file-prompters.

Typical usage:

        :- pce_autoload(finder, library(find_file)).
        :- pce_global(@finder, new(finder)).

                ...,
                get(@finder, file, ...Options..., FileName),
                ....

Examples:

        get(@finder, file, save, pl, SaveFile)
        get(@finder, file, open, tuple('Source', chain(c,h)), SourceFile)

See <-file below for all optios.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


                 /*******************************
                 *     DEFAULT GLOBAL OBJECT    *
                 *******************************/

:- pce_global(@finder, new(finder)).

%       register_file_dialog
%
%       If the display doesn't implement <-win_file_name we register the
%       autoload class find_file_dialog to do the job ourselves.

register_file_dialog :-
    (   send(@display, has_get_method, win_file_name)
    ->  true
    ;   pce_autoload(find_file_dialog, find_file_dialog)
    ).

:- register_file_dialog.


                 /*******************************
                 *           CLASS FINDER       *
                 *******************************/

:- pce_begin_class(finder, object,
                   "Find files on behalf of applications").

variable(directory,     directory,      both, "Current directory").
variable(label,         [char_array],   both, "Used label").

initialise(F) :->
    send_super(F, initialise),
    send(F, slot, directory, directory('.')).


file(F, Exists:exists=[bool|{open,save}], Ext0:extension='[name|chain|tuple]',
     Dir:directory=[directory], Default:default=[name], File:name) :<-
    "Get [existing] file with [extension]"::
    get_file(F, Exists, Ext0, Dir, Default, File).

get_file(F, Exists, Ext, Dir, Default, File) :-
    send(@display, has_get_method, win_file_name),
    !,
    mode(Exists, Mode),
    win_filter(Ext, Filters),
    (   Dir == @default
    ->  get(F, directory, DefDir)
    ;   DefDir = Dir
    ),
    get(F, label, Label),
    get(@display, win_file_name, Mode, Filters,
        Label, Default, DefDir, @default, chain(overwriteprompt), File),
    file_directory_name(File, NewDir),
    send(F, slot, directory, NewDir).
get_file(F, Exists, Ext, Dir, Default, File) :-
    mode(Exists, Mode),
    get(F, label, Label),
    new(D, find_file_dialog(Mode, Label)),
    send(D, filter, Ext),
    (   Default \== @default
    ->  send(D, default_file, Default)
    ;   true
    ),
    (   Dir == @default
    ->  send(D, directory, F?directory)
    ;   send(D, directory, Dir)
    ),
    send(D, make_transient),
    send(D, message, message(D, return, @arg1)),
    get(D, confirm, File),
    send(F, slot, directory, D?directory),
    send(D, destroy).

%!  mode(+Exists, -Mode)
%
%   Map old boolean mode to new named mode.

mode(@on,      open).
mode(@off,     save).
mode(@default, open).
mode(save,     save).
mode(open,     open).

%!  win_filter(+Spec, -Filter)
%
%   Map abstract filter to a filter for `display<-win_file_name'.
%   See find_file_dialog for details.

win_filter(@default, @default) :- !.
win_filter(Atom, chain(Tuple)) :-
    atom(Atom),
    !,
    file_filter(Atom, Tuple).
win_filter(Tuple, chain(Filter)) :-
    send(Tuple, instance_of, tuple),
    !,
    file_filter(Tuple, Filter).
win_filter(Chain, Filter) :-
    get(Chain, map, ?(@prolog, file_filter, @arg1), Filter).

file_filter(Tuple, tuple(Label, Pattern)) :-
    send(Tuple, instance_of, tuple),
    !,
    get(Tuple, first, Label),
    get(Tuple, second, ExtList),
    to_pattern(ExtList, Pattern).
file_filter(*, tuple(all_files, *)) :- !.
file_filter(Ext0, Filter) :-
    atom_concat('.', Ext, Ext0),
    !,
    file_filter(Ext, Filter).
file_filter(Ext, tuple(Name, Pattern)) :-
    file_type(Ext, Name),
    !,
    atom_concat('*.', Ext, Pattern).
file_filter(Ext, Pattern) :-
    atom_concat('*.', Ext, Pattern).

to_pattern(*, '*.*') :- !.
to_pattern(Ext, Pattern) :-
    atom(Ext),
    !,
    (   sub_atom(Ext, 0, _, _, '.')
    ->  atom_concat('*', Ext, Pattern)
    ;   atom_concat('*.', Ext, Pattern)
    ).
to_pattern(Chain, Pattern) :-
    chain_list(Chain, List),
    maplist(to_pattern, List, Patterns),
    atomic_list_concat(Patterns, ';', Pattern).

%!  file_type(?Extension, ?Type) is nondet.
%
%   Allow the user to add rules to this predicate, showing proper
%   names to the user rather than patterns.  The collection here
%   is rather arbitrary ...  Maybe we should read the registery
%   for defined filetypes ...
%
%   @tbd    Merge with MIME-type library

:- multifile
    file_type/2.

file_type(pl,   'Prolog files').
file_type(c,    'C source files').
file_type(cc,   'C++ source files').
file_type(cpp,  'C++ source files').
file_type(cxx,  'C++ source files').
file_type(h,    'C header files').
file_type(pd,   'PceDraw files').
file_type(ps,   'PostScript files').
file_type(eps,  'Encapsulated PostScript files').
file_type(pdf,  'Portable Document Format files').
file_type(txt,  'Text files').
file_type(jpeg, 'JPEG images').
file_type(jpg,  'JPEG images').
file_type(gif,  'GIF images').
file_type(xpm,  'XPM images').
file_type(ico,  'Icon files').
file_type(cur,  'Cursor files').
file_type(html, 'HTML documents').
file_type(htm,  'HTML documents').
file_type(xml,  'XML documents').
file_type(sgml, 'SGML documents').
file_type(rdf,  'RDF files').
file_type(rdfs, 'RDF schema files').
file_type(tex,  'TeX or LaTeX files').
file_type(*,    'All files').

:- pce_end_class(finder).
