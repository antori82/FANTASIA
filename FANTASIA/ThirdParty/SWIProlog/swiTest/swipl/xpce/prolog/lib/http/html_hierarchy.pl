/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  2000-2014, University of Amsterdam
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

:- module(html_hierarchy,
          [ html_hierarchy/6,           % +Root, :GenChild, :GenLabel
            html_hierarchy_image/2,     % +Path, -Image
            pageYOffset/2               % +Cookie, -Y
          ]).
:- use_module(library(pce)).
:- use_module(library(http/html_write)).

:- meta_predicate
    html_hierarchy(+, :, :, +, -, +).

html_hierarchy(Root, GenChild, GenLabel, Cookie) -->
    { strip_module(GenChild, M1, T1),
      strip_module(GenLabel, M2, T2)
    },
    script,
    hierarchy(Root, M1:T1, M2:T2, Cookie, 0, []).

hierarchy(Root, GenChild, GenLabel, Cookie, 0, _) -->
    !,
    { findall(Child, gen_child(GenChild, Root, Child), Subs)
    },
    html([ \gen_label(GenLabel, Root),
           br([])
         | \subclasses(Subs, GenChild, GenLabel, Cookie, 1, [])
         ]).
hierarchy(Root, GenChild, GenLabel, Cookie, Level, Lines) -->
    { findall(Child, gen_child(GenChild, Root, Child), Subs),
      (   Subs == []
      ->  Pre = n
      ;   (   expanded(Root, Cookie)
          ->  Pre = m,
              java_collapse(Root, ExpCol)
          ;   Pre = p,
              java_expand(Root, ExpCol)
          )
      ),
      atomic_list_concat([Pre, Level|Lines], :, Place),
      atomic_list_concat(['/images/hierarchy/', Place], ImgSrc),
      SubLevel is Level + 1
    },
    (   {Pre==n}
    ->  html([ img([ src(ImgSrc), alt(''), align(top) ], []),
               \gen_label(GenLabel, Root),
               br([])
             ])
    ;   {Pre==m}
    ->  html([ a([href(ExpCol)],
                 img([ src(ImgSrc),
                       alt(''),
                       align(top),
                       border(0)
                     ])),
               \gen_label(GenLabel, Root),
               br([])
             | \subclasses(Subs, GenChild, GenLabel, Cookie, SubLevel, Lines)
             ])
    ;   html([ a([href(ExpCol)],
                 img([ src(ImgSrc),
                       alt(''),
                       align(top),
                       border(0)
                     ])),
               \gen_label(GenLabel, Root),
               br([])
             ])
    ).


script -->                              % tagged window.location.pathname
    html(script(
'function pageY()
{ if ( navigator.appName == "Microsoft Internet Explorer" )
    return document.body.scrollTop;
  else
    return window.pageYOffset;
}

function getCookie(name)
{ var cookie = " " + document.cookie;
  var search = " " + name + "=";
  var setStr = null;
  var offset = 0;
  var end = 0;
  if (cookie.length > 0)
  { offset = cookie.indexOf(search);
    if (offset != -1)
    { offset += search.length;
      end = cookie.indexOf(";", offset)
      if (end == -1)
      { end = cookie.length;
      }
      setStr = cookie.substring(offset, end);
    }
  }
  return(setStr);
}

function setCookie(name, value)
{ document.cookie = name + "=" + value;
}

function expand(name)
{ var e = getCookie("expand");

  if ( e )
  { e += name + "&";
  } else
  { e = "&" + name + "&";
  }

  setCookie("expand", e);
  setCookie("y", pageY());
  window.location.reload();
}

function collapse(name)
{ var e = getCookie("expand");

  if ( e )
  { var a = e.split("&");
    var r = new String("&");

    for(var i=0; i < a.length; i++)
    { if ( a[i] != name && a[i] != "" )
      { r += a[i] + "&";
      }
    }

    setCookie("expand", r);
  }

  setCookie("y", pageY());
  window.location.reload();
}

function expandall()
{ setCookie("expand", "all");
  setCookie("y", pageY());
  window.location.reload();
}
')).


%!  pageYOffset(+Cookie, -Y)
%
%   Return the current page Y-offset from the cookie.  This value may
%   be used in the onLoad handler of the page-body.

pageYOffset(Cookie, Y) :-
    new(Re, regex('y=([0-9]+)')),
    send(Re, search, Cookie),
    get(Re, register_value, Cookie, 1, int, Y).
pageYOffset(_, 0).


:- dynamic
    ccode/2.

class_code(Class, Code) :-
    ccode(Class, Code),
    !.
class_code(Class, Code) :-
    flag(ccode, Code, Code+1),
    assert(ccode(Class, Code)).


expanded(_, Cookie) :-
    send(regex('expand=all'), search, Cookie),
    !.
expanded(Class, Cookie) :-
    class_code(Class, Code),
    atomic_list_concat([&, Code, &], Pattern),
    sub_atom(Cookie, _, _, _, Pattern),
    !.

java_expand(Class, Code) :-
    class_code(Class, CCode),
    sformat(Code, 'javascript:expand(\'~w\')', CCode).
java_collapse(Class, Code) :-
    class_code(Class, CCode),
    sformat(Code, 'javascript:collapse(\'~w\')', CCode).


subclasses([], _, _, _, _, _) -->
    [].
subclasses([H], GenChild, GenLabel, Cookie, Level, Lines) -->
    !,
    hierarchy(H, GenChild, GenLabel, Cookie, Level, Lines).
subclasses([H|T], GenChild, GenLabel, Cookie, Level, Lines) -->
    hierarchy(H, GenChild, GenLabel, Cookie, Level, [Level|Lines]),
    subclasses(T, GenChild, GenLabel, Cookie, Level, Lines).


                 /*******************************
                 *          GENERATORS          *
                 *******************************/

gen_child(GenChildren, Root, Child) :-
    call(GenChildren, Root, Child).

gen_label(G, Class, A, B) :-
    call(G, Class, A, B).


                 /*******************************
                 *            IMAGES            *
                 *******************************/

html_hierarchy_image(Path, Img) :-
    atom_concat('/images/hierarchy/', IName, Path),
    !,
    term_to_atom(Type:X, IName),
    (   X = N:VLines
    ->  true
    ;   N = X,
        VLines = []
    ),
    Left is (N-1)*20 + 10,
    H = 18,
    H2 is H//2,
    new(P, path(points := chain(point(Left, 0),
                                point(Left, H2),
                                point(N*20, H2)))),
    new(Img, pixmap(@nil, width := N*20, height := H)),
    vlines(VLines, Img, H),
    send(Img, draw_in, P),
    (   Type == m
    ->  get(class(tree), class_variable, expanded_image, CV),
        get(CV, value, ExpImg),
        send(Img, draw_in, bitmap(ExpImg), point(Left-4, 5))
    ;   Type == p
    ->  get(class(tree), class_variable, collapsed_image, CV),
        get(CV, value, ExpImg),
        send(Img, draw_in, bitmap(ExpImg), point(Left-4, 5))
    ;   true
    ).

vlines([], _, _) :- !.
vlines(N:T, Img, H) :-
    !,
    X is (N-1)*20+10,
    send(Img, draw_in, line(X, 0, X, H)),
    vlines(T, Img, H).
vlines(N, Img, H) :-
    X is (N-1)*20+10,
    send(Img, draw_in, line(X, 0, X, H)).

level(A0-B, Level, [B|A]) :-
    !,
    level(A0, Level, A).
level(B, B, []).






