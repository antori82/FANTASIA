/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  2000-2011, University of Amsterdam
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

:- module(html_util,
          [ column_width/2,             % +Spec, -Width
            table_width/2,              % +Spec, -Width

            option/2,                   % ?Option, +OptionList
            option/3,                   % ?Option, +OptionList, +Default

            apply_options/3,            % +Options, +Type, +Object
            content_to_atom/2,          % +Content, -Atom

            debug/3,                    % +Subject, +Format, +Args
            debug/2,                    % +Subject, :Goal

            debug/1,                    % +/-Subject
            debugging/1                 % ?Subject
          ]).


hres(118).                              % 118 pixels/per inch
em(10).                                 % width of default font

%       column_width(+Spec, -Result)
%
%       Parses an HTML column-width specification into either an integer
%       (representing pixel width) or a term *(Width) representing relative
%       width.

column_width(Spec, Width) :-
    atom_codes(Spec, Chars),
    phrase(cwidth(Width), Chars).

cwidth(Width) -->
    number(N),
    wunit(Unit),
    (   "*"
    ->  { Width = *(N)
        }
    ;   { unit_factor(Unit, F),
          Width is integer(F*N)
        }
    ).


%       table_width(+Spec, -Result)
%
%       Parses an HTML table-width specification into either an integer
%       (representing pixel width) or a term percent(Width) representing
%       relative width.

table_width(Spec, Width) :-
    atom_codes(Spec, Chars),
    phrase(twidth(Width), Chars).

twidth(Width) -->
    number(N),
    wunit(Unit),
    (   "%"
    ->  { Width = percent(N)
        }
    ;   { unit_factor(Unit, F),
          Width is integer(F*N)
        }
    ).


wunit(pt) --> "pt".
wunit(pi) --> "pi".
wunit(in) --> "in".
wunit(cm) --> "cm".
wunit(mm) --> "mm".
wunit(em) --> "em".
wunit(px) --> "px".
wunit(px) --> "".

unit_factor(in, F) :- hres(F).
unit_factor(pt, F) :- hres(R), F is R/72.
unit_factor(pi, F) :- hres(R), F is R/6.
unit_factor(cm, F) :- hres(R), F is R/2.54.
unit_factor(mm, F) :- hres(R), F is R/25.4.
unit_factor(em, F) :- em(F).
unit_factor(px, 1).


                 /*******************************
                 *           DCG BASICS         *
                 *******************************/

number(N) -->
    digits1(I),
    (   "."
    ->  digits1(F),
        { append(I, [0'.|F], A),
          number_chars(N, A)
        }
    ;   { number_chars(N, I)
        }
    ).

integer(I) -->
    digits1(D),
    { number_chars(I, D)
    }.

digits1([D0|D]) -->                     % 1 or more digits
    digit(D0),
    digits(D).

digits([D0|D]) -->                      % 0 or 1 digit
    digit(D0),
    !,
    digits(D).
digits([]) -->
    [].

digit(D, [D|T], T) :-                   % a digit
    code_type(D, digit).


                 /*******************************
                 *             OPTIONS          *
                 *******************************/

%       option(Option(?Value), OptionList, Default)

option(Opt, Options) :-
    memberchk(Opt, Options),
    !.
option(Opt, Options) :-                 % xml2pl compatible handling
    functor(Opt, OptName, 1),
    arg(1, Opt, OptVal),
    memberchk(OptName=OptVal, Options),
    !.

option(Opt, Options, _) :-
    option(Opt, Options),
    !.
option(Opt, _, Default) :-
    arg(1, Opt, Default).


%       apply_options(Options, :Direct, Object).

:- meta_predicate
    apply_options(+, :, +),
    apply_option(+, :, +).

apply_options([], _, _) :- !.
apply_options([H|T], Direct, Object) :-
    apply_option(H, Direct, Object),
    apply_options(T, Direct, Object).

apply_option(N=V, Direct, Object) :-
    !,
    Term =.. [N,V],
    apply_option(Term, Direct, Object).
apply_option(Term, Direct, Object) :-
    Direct \== [],
    call(Direct, Term, Object),
    !.
apply_option(Term, _, Object) :-
    catch(send(Object, Term), _, fail),
    !.
apply_option(Term, _, Object) :-
    format('Warning: failed to apply option ~p to ~p~n', [Term, Object]).


                 /*******************************
                 *       TEXT CONVERSION        *
                 *******************************/

%       content_to_atom(+Content, -Atom)
%
%       Translate content into an atom.   Used for <title> and other elements
%       for which we only allow CDATA.

content_to_atom([Atom], Atom).


                 /*******************************
                 *             DEBUG            *
                 *******************************/

:- dynamic
    subject/1.
:- meta_predicate
    debug(+, :).

debugging(X) :-
    subject(X).

debug(Subject, Format, Args) :-
    subject(Subject),
    !,
    format(user_output, Format, Args).
debug(_, _, _).

debug(Subject, Goal) :-
    debugging(Subject),
    !,
    Goal.
debug(_, _).

debug(+Subject) :-
    asserta(subject(Subject)).
debug(-Subject) :-
    retractall(subject(Subject)).

