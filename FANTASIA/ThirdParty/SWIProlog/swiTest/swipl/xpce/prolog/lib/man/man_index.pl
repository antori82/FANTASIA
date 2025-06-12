/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1996-2018, University of Amsterdam
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

:- module(man_word_index,
          [ pce_make_manual_index/0,
            pce_make_manual_index/1,    % +File
            pce_make_manual_index/2     % +File, -Reference
          ]).
:- use_module(user:library(pce)).       % HACK: needed for build process
:- use_module(library(pce)).
:- use_module(library(pce_manual)).
:- require([ atomic_list_concat/2
           ]).

:- dynamic
    use_gui/0,
    quiet/0.

quiet.

:- pce_begin_class(man_index_manager, object,
                   "Dummy object to exploit XPCE autoloader").

make_index(_IM, IndexFile:name, Index:chain_table) :<-
    asserta(use_gui),
    pce_make_manual_index(IndexFile, Index).

:- pce_end_class.


%       make_manual_index([+File, [-Reference]])
%
%       Creates a word index for the manual system.  This index is a
%       chain_table mapping all words that appear in the manual onto
%       a chain of card identifiers.
%
%       At the moment only all class-related cards (classes, variables,
%       methods and class-variables are processed.


pce_ifhostproperty(prolog(quintus),
(   access_file(File, Mode) :-
        can_open_file(File, Mode))).

pce_make_manual_index :-
    absolute_file_name(pce('man/reference/index.obj'), File),
    pce_make_manual_index(File).
pce_make_manual_index(File, @man_tmp_index) :-
    pce_make_manual_index(File).
pce_make_manual_index(File) :-
    prepare_manual,
    access_file(File, write),      % just make sure!
    !,
    new(Ch, chain),                 % gather all built-in classes
    send(@man_tmp_view, format, 'Collecting built-in classes ... '),
    send(@man_tmp_view, synchronise),
    send(@classes, for_all,
         if(@arg2?creator == built_in,
            message(Ch, append, @arg2))),
    send(Ch, sort, ?(@arg1?name, compare, @arg2?name)),
    send(@man_tmp_view, format, '%d classes.\n', Ch?size),
    send(@man_tmp_view, synchronise),
    send(Ch, for_all, message(@prolog, make_class_index, @arg1)),
    make_module_index,
    send(@man_tmp_view, format, '\n\nCleaning index table'),
    send(@man_tmp_view, synchronise),
    clean_index(@man_tmp_index),
    send(@man_tmp_view, format, 'Cleaning done\n\n'),
    send(@man_tmp_view, format, 'Saving index table to %s ... ', File),
    send(@man_tmp_view, synchronise),
    send(@man_tmp_index, save_in_file, File),
    send(@man_tmp_view, format, '%d bytes. Finished.\n', file(File)?size),
    send(@man_tmp_view, synchronise),
    (   get(@man_tmp_view?frame, member, dialog, D),
        get(D, member, quit, Quit),
        get(D, member, abort, Abort)
    ->  send(Quit, active, @on),
        send(Abort, active, @off)
    ;   true
    ).
pce_make_manual_index(File) :-
    send(file(File), report, error, 'Cannot write %s', File),
    fail.

make_class_index(Class) :-
    get(Class, name, Name),
    (   get(@man_tmp_view, column, C),
        C > 64
    ->  send(@man_tmp_view, newline)
    ;   true
    ),
    send(@man_tmp_view, format, '(%s', Name),
    send(@man_tmp_view, synchronise),
    new(Objs, chain),
    send(Objs, merge, Class?send_methods),
    send(Objs, merge, Class?get_methods),
    send(Objs, for_all,
         if(message(@arg1?message, instance_of, c_pointer),
            message(Objs, delete, @arg1))),
    send(Class?instance_variables, for_all,
         message(Objs, append, @arg1)),
    send(Objs, merge, Class?class_variables),
    send(Objs, append, Class),
    send(Objs, for_all,
         message(@prolog, make_card_index, @arg1)),
    send(Objs, done),
    send(@man_tmp_view, format, ') ', Name),
    send(@man_tmp_view, synchronise).

make_card_index(Card) :-
    get(Card, man_id, Id),
    (   get(Card, man_summary, Summary)
    ->  word_index(Summary, Id)
    ;   true
    ),
    (   get(Card, man_description, Description)
    ->  word_index(Description, Id)
    ;   true
    ).


:- pce_global(@man_tmp_view, make_man_tmp_view).
:- pce_global(@man_tmp_index, new(chain_table)).
:- pce_global(@man_tmp_index_regex, make_index_regex).

make_index_regex(R) :-
    new(R, regex('@?[a-zA-Z]\\w+')),
    send(R, compile, @on).

make_man_tmp_view(V) :-
    use_gui,
    !,
    new(V, view('Build PCE manual index')),
    send(new(D, dialog), below, V),
    send(D, append, new(Quit, button(quit, message(D, destroy)))),
    send(Quit, active, @off),
    send(D, append,
         button(abort,
                and(message(@display, confirm,
                            'Abort generation of search index?'),
                    message(@prolog, halt)))),
    send(D, append, label(reporter), right),
    send(V, open),
    send(V, wait),
    send(V, format, 'Building PCE manual index.\n'),
    send(V, format, 'This process will take several minutes.\n\n').
make_man_tmp_view(V) :-
    new(V, man_index_output).

word_index(Text, Id) :-
    send(@man_tmp_index_regex, for_all, Text,
         message(@man_tmp_index, append,
                 ?(@arg1, register_value, @arg2, 0, name)?downcase, Id)).

:- pce_begin_class(man_index_output, object,
                   "Dummy drain to catch feedback in non-gui mode").

synchronise(_) :->
    true.

column(_, C) :<-
    C = 0.

format(_, Fmt:char_array, Args:any ...) :->
    (   quiet
    ->  true
    ;   Msg =.. [format, Fmt | Args],
        send(@pce, Msg),
        flush
    ).

frame(_, _) :<-
    fail.

:- pce_end_class.


                 /*******************************
                 *             MANUAL           *
                 *******************************/

prepare_manual :-
    use_gui,
    !,
    manpce.
prepare_manual :-
    new(Directory, directory('$PCEHOME/man/reference')),
    new(@man_space, man_space(reference, Directory)),
    send(@pce, send_method,         % make it silent
         send_method(report, vector('any ...'), new(and))).


                 /*******************************
                 *        NON-CLASS CARDS       *
                 *******************************/

non_class_module(predicates).
non_class_module(objects).
non_class_module(tools).

make_module_index :-
    send(@man_tmp_view, format, '\n\n'),
    non_class_module(Module),
    send(@man_tmp_view, format, '%s index ... ', Module),
    send(@man_tmp_view, synchronise),
    make_module_index(Module),
    send(@man_tmp_view, format, 'done.\n'),
    send(@man_tmp_view, synchronise),
    fail.
make_module_index.

make_module_index(ModuleName) :-
    (   object(@manual)
    ->  get(@manual, space, ManSpace)
    ;   ManSpace = @man_space       % non-gui building
    ),
    get(ManSpace, module, ModuleName, @on, Module),
    send(Module?id_table, for_all,
         message(@prolog, index_card, ModuleName, @arg1, @arg2)).


index_card(Module, CardId, Card) :-
    send(@man_tmp_view, synchronise),
    atomic_list_concat([$, Module, $, CardId], Id),
    (   get(Card, man_summary, Summary)
    ->  word_index(Summary, Id)
    ;   true
    ),
    (   get(Card, man_description, Description)
    ->  word_index(Description, Id)
    ;   true
    ).


                 /*******************************
                 *             CLEAN            *
                 *******************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
These words appear in more then 500 cards and probably have little value
in specifying search  options.   Deleting   them  significantly  reduces
memory and saves time with loading and processing the index.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

noindex(and).
noindex(will).
noindex(was).
noindex(using).
noindex(is).
noindex(or).
noindex(not).
noindex(the).
noindex(a).
noindex(an).
noindex(class).
noindex(object).
noindex(method).
noindex(that).
noindex(also).
noindex(see).
noindex(it).
noindex(to).
noindex(used).
noindex(when).
noindex(by).
noindex(of).
noindex(with).
noindex(from).
noindex(if).
noindex(in).
noindex(are).
noindex(be).
noindex(this).

clean_index(Table) :-
    noindex(Word),
    get(Table, member, Word, Chain),
    get(Chain, size, Size),
    send(@man_tmp_view, format, 'Deleted "%s", %d entries\n', Word, Size),
    send(@man_tmp_view, synchronise),
    send(Table, delete, Word),
    fail.
clean_index(Table) :-
    send(Table, for_all, message(@arg2, unique)).


