/*
    Author:        Eshel Yaron
    E-mail:        eshel@swi-prolog.org
    Copyright (c)  2022-2024, SWI-Prolog Solutions b.v.
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

:- module(sweep_link,
	  [ write_sweep_module_location/0
	  ]).

/** <module> Information for dynamically linking to GNU Emacs
*/

sweep_link_version(1).

write_sweep_module_location :-
    sweep_module(Path),
    sweep_link_version(V),
    format('V ~w~n', [V]),
    (   current_prolog_flag(executable_format, elf)
    ->  current_prolog_flag(libswipl, Libpath),
	format('L ~w~n', [Libpath])
    ;   true
    ),
    format('M ~w~n', [Path]).

sweep_module(Path) :-
    current_prolog_flag(windows, true),
    current_prolog_flag(executable, Exe),
    prolog_to_os_filename(PlExe, Exe),
    file_directory_name(PlExe, BinDir),
    atomic_concat(BinDir, '/sweep-module.dll', Path),
    exists_file(Path),
    !.
sweep_module(Path) :-
    absolute_file_name(foreign('sweep-module'),
		       Path,
		       [file_type(executable), access(read)]).
