/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        jan@swi-prolog.org
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2023, SWI-Prolog Solutions b.v.
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

:- module(pldoc_markdown,
          [ print_markdown/2            % +String, +Options
          ]).
:- use_module(library(pldoc)).
:- autoload(library(pldoc/doc_html)).
:- autoload(library(pldoc/doc_wiki), [wiki_codes_to_dom/3]).
:- autoload(library(sgml), [load_html/3]).
:- autoload(library(http/html_write), [html/3, print_html/1]).
:- use_module(library(lynx/pldoc_style), []).
:- autoload(library(lynx/html_text), [html_text/2]).

:- predicate_options(print_markdown/2, 2,
                     [ pass_to(wiki_codes_to_dom/3, 2),
                       pass_to(load_html/3, 3),
                       pass_to(html_text/2, 2)
                     ]).

/** <module> Markdown utilities

This module provides high level PlDoc markdown utilities.

@tbd	The current implementation creates the markdown DOM, translates
        this to HTML, then parses it and feeds it into the HTML
        rendering.  Creating an parsing the HTML string representation
        could be skipped.
*/

%!  print_markdown(+Input, +Options) is det.
%
%   Print a PlDoc  markdown  formatted   String  to  `current_output` as
%   formatted text.
%
%   @arg Input is either a term `Format-Args`, a atom, string, or a list
%   of codes.
%   @see html_text/2 for the most useful options.

print_markdown(String, Options) :-
    to_codes(String, Codes),
    wiki_codes_to_dom(Codes, Options, DOM1),
    phrase(html(DOM1), Tokens),
    with_output_to(string(HTML), print_html(Tokens)),
    setup_call_cleanup(
        open_string(HTML, In),
        load_html(In, DOM, Options),
        close(In)),
    html_text(DOM, Options).

to_codes(Fmt-Args, Codes) =>
    format(codes(Codes), Fmt, Args).
to_codes(String, Codes), atomic(String) =>
    string_codes(String, Codes).
to_codes(List, Codes), is_of_type(List, Codes) =>
    Codes = List.

