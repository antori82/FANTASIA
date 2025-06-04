/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org/packages/xpce/
    Copyright (c)  2003-2023, University of Amsterdam
                              VU University Amsterdam
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

:- module(pce_prolog_xref, []).
:- use_module(library(pce)).

/** <module> XPCE plugin for library(prolog_xref)

This library facilitates using  PceEmacs  editors   as  sources  for the
Prolog cross referencer.
*/

:- multifile
    prolog:xref_source_identifier/2,        % +Source, -Id
    prolog:xref_source_directory/2,         % +Source, -Dir
    prolog:xref_open_source/2.              % +SourceId, -Stream

%!  prolog:xref_source_identifier(+Object, -Ref)
%
%   The  cross-referencer  runs  faster  if   the  reference  is  an
%   indexable term. Therefore we strip the XPCE @ from the object.

prolog:xref_source_identifier(Object, Ref) :-
    object(Object),
    !,
    Object = @Ref.
prolog:xref_source_identifier(Ref, Ref) :-
    integer(Ref),
    !.

%!  prolog:xref_source_directory(+Source, -Dir)
%
%   Find the directory of a PceEmacs buffer to resolve relative paths.

prolog:xref_source_directory(SourceId, Dir) :-
    integer(SourceId),
    Obj = @SourceId,
    object(Obj),
    catch(get(Obj?file, absolute_path, Path), _, fail),
    file_directory_name(Path, Dir).

%!  prolog:xref_open_source(+Source, -Stream)
%
%   Open the PceEmacs as a Prolog stream.

prolog:xref_open_source(SourceId, Stream) :-
    integer(SourceId),
    Obj = @SourceId,
    object(Obj),
    pce_open(Obj, read, Stream),
    (   catch(get(Obj?file, absolute_path, Path), _, fail)
    ->  set_stream(Stream, file_name(Path))
    ;   true
    ).
