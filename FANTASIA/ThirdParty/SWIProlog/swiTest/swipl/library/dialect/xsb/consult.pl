/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2019, VU University Amsterdam
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

:- module(consult,
          [ consult/1,                  % :File
            ensure_dync_loaded/1,       % +File
            add_lib_dir/1,              % +Directories
            add_lib_dir/2               % +Root, +Directories
          ]).
:- use_module(library(error)).
:- use_module(library(filesex)).

:- meta_predicate
    ensure_dync_loaded(:).

ensure_dync_loaded(File) :-
    load_files(File, [if(not_loaded), dialect(xsb)]).

%!  add_lib_dir(+Directories) is det.
%!  add_lib_dir(+Root, +Directories) is det.
%
%   Add    members    of    the    comma      list     Directories    to
%   user:library_directory/1.  If  Root  is  given,    all   members  of
%   Directories are interpreted relative to Root.

add_lib_dir(Directories) :-
    add_lib_dir('.', Directories).

add_lib_dir(_, Var) :-
    var(Var),
    !,
    instantiation_error(Var).
add_lib_dir(Root, (A,B)) :-
    !,
    add_lib_dir(Root, A),
    add_lib_dir(Root, B).
add_lib_dir(Root, a(Dir)) :-
    !,
    add_to_library_directory(Root, Dir, asserta).
add_lib_dir(Root, Dir) :-
    add_to_library_directory(Root, Dir, assertz).

add_to_library_directory(Root, Dir, How) :-
    (   expand_file_name(Dir, [Dir1])
    ->  true
    ;   Dir1 = Dir
    ),
    relative_file_name(TheDir, Root, Dir1),
    exists_directory(TheDir),
    !,
    (   user:library_directory(TheDir)
    ->  true
    ;   call(How, user:library_directory(TheDir))
    ).
add_to_library_directory(_, _, _).
