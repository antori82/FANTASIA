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

:- module(pce_http_man,
          [ pce_http_man/1              % ?Port
          ]).
:- use_module(library(pce)).
:- use_module(library('http/html_write')).
:- use_module(httpd).
:- use_module(html_hierarchy).
:- use_module(html_refman).

:- use_module(library('man/v_search')).
:- pce_autoload(man_inheritance_tree, library('man/v_inherit')).

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Demo for the XPCE HTTP Deamon. This demo provides a extensive tranlation
of the XPCE class hierarchy and class documentation to HTML.

To test it, do:

        ?- [http_man].
        ?- pce_http_man(8080).          % or some other port

Then run your browser and start at the url http://localhost:8080/
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

url(pcehome, 'http://www.swi-prolog.org/packages/xpce/').
url(pceusg,  'http://www.swi.psy.uva.nl/projects/xpce/UserGuide').

pce_http_man(Port) :-                   % start on anonymous port
    var(Port),
    !,
    new(HTTPD, manpce_httpd),
    get(HTTPD, address, Port).
pce_http_man(Port) :-
    new(_, manpce_httpd(Port)).

:- pce_begin_class(manpce_httpd, httpd,
                   "Demo HTTPD for XPCE manual").

accepted(HTTPD) :->
    "Log connections"::
    send_super(HTTPD, accepted),
    get(HTTPD, peer_name, Peer),
    log(connect(Peer)).


request(HTTPD, Request:sheet) :->
    get(Request, path, Path),
    get(Request, form, Form),
    log(request(Request)),
    flag(requests, N, N+1),
    reply(Path, Form, HTTPD).

:- pce_end_class.

                 /*******************************
                 *              LOG             *
                 *******************************/

log(connect(Peer)) :-
    !,
    (   send(Peer, instance_of, tuple)
    ->  send(@pce, format, 'New connection from %s:%s\n',
             Peer?first, Peer?second)
    ;   send(@pce, format, 'New connection from %s\n', Peer)
    ).
log(request(Request)) :-
    !,
    get(Request, path, Path),
    send(@pce, format, '\t%s\n', Path),
    (   get(Request, form, Form),
        Form \== @nil
    ->  send(Form, for_all,
             message(@pce, format, '\t\t%s=%s\n', @arg1?name, @arg1?value))
    ;   true
    ).
log(_).


                 /*******************************
                 *            REPLIES           *
                 *******************************/

:- discontiguous
    reply/3.

%       /
%

reply(/, @nil, HTTPD) :-
    send(HTTPD, reply_html, pce_http_man:frames).

frames -->
    html(html([ head(title('XPCE web-manual')),
                frameset([cols('25%,75%')],
                         [ frame([ src('/classhierarchy'),
                                   name(hierarchy)
                                 ]),
                           frameset([ rows('60,*')
                                    ],
                                    [ frame([ src('/top'),
                                              name(top)
                                            ]),
                                      frame([ src('/search'),
                                              name(description)
                                            ])
                                    ])
                         ])
              ])).

%       /class/
%
%       Provide a table with all classes

reply('/class/', @nil, HTTPD) :-
    new(Classes, chain),
    send(@classes, for_all, message(Classes, append, @arg1)),
    send(Classes, sort),
    chain_list(Classes, Sorted),
    send(HTTPD, reply_html, pce_http_man:classindex(Sorted)).

classindex(Classes) -->
    page(title('XPCE Class Index'),
         [ h1([align(center)], 'XPCE Class Index'),
           table([ border(2),
                   align(center)
                 ],
                 [ tr([ th('Name'),
                        th('Summary')
                      ])
                 | \classrows(Classes)
                 ])
         ]).

classrows([]) -->
    [].
classrows([H|T]) -->
    classrow(H),
    classrows(T).

classrow(Name) -->
    { get(@pce, convert, Name, class, Class),
      get(Class, summary, Summary)
    },
    html(tr([ td(\class_name(Name)),
              td(Summary)
            ])).

class_name(Class) -->
    { object(Class),
      !,
      get(Class, name, Name)
    },
    class_name(Name).
class_name(Name) -->
    { www_form_encode(Name, Encoded),
      atom_concat('/class?name=', Encoded, URL)
    },
    html(a([href(URL), target(description)], Name)).

classlist([], _) -->
    [].
classlist([H], _) -->
    class_name(H).
classlist([H|T], S) -->
    html([\class_name(H), S]),
    classlist(T, S).

%       /class?name=classname
%
%       Provide documentation on the class.

reply('/class', Form, HTTPD) :-
    get(Form, name, Class),
    !,
    get(@pce, convert, Class, class, ClassObj),
    send(HTTPD, reply_html, pce_http_man:classpage(ClassObj)).

classpage(Class) -->
    { get(Class, name, Name)
    },
    page([ title(['XPCE class ', Name])
         ],
         \classdoc(Class)
        ).

classdoc(Class) -->
    { get(Class, name, Name),
      make_diagram([Name], Diagram)
    },
    html([ h1([align(center)], ['XPCE class ', em(Name)]),
           hr([]),
           center(Diagram),
           p([]),
           \classtable(Class),
           h2('Description'),
           \description(Class),
           p([]),
           \classbehaviour(Class)
         ]).

description(Obj) -->
    { html_description(Obj, String),
      get(String, value, HTML)
    },
    [HTML].


classtable(Class) -->
    html_begin(table(border(2),
                     align(center),
                     width('100%'))),
    summary_row(Class),
    meta_class_row(Class),
    super_class_row(Class),
    subclasses_row(Class),
    instance_variables(Class),
    html_end(table).

summary_row(Class) -->
    { get(Class, summary, Summary),
      Summary \== @nil
    },
    !,
    head_row('Summary', Summary).
summary_row(_) -->
    [].

meta_class_row(Class) -->
    { get(Class, class, MetaClass),
      \+ get(MetaClass, name, class)
    },
    !,
    head_row('Meta Class', \class_name(MetaClass)).
meta_class_row(_) -->
    [].

super_class_row(Class) -->
    { get(Class, super_class, Super),
      Super \== @nil
    },
    !,
    head_row('Super Class', \class_name(Super)).
super_class_row(_) -->
    [].

subclasses_row(Class) -->
    { get(Class, sub_classes, Subs),
      Subs \== @nil,
      chain_list(Subs, List)
    },
    !,
    head_row('Sub Classes', \classlist(List, ', ')).
subclasses_row(_) -->
    [].

head_row(Name, Value) -->
    html(tr([ th([align(right), colspan(2)], Name),
              td(Value)
            ])).


instance_variables(Class) -->
    { get(Class, instance_variables, Vector),
      object(Vector, Term),
      Term =.. [_|Vars]
    },
    html([ tr([ th([ colspan(3),
                     bgcolor(yellow)
                   ],
                   'Instance variables')
              ]),
           tr([ th('Name'),
                th('Type'),
                th('Summary')
              ])
         | \variables(Vars)
         ]).

variables([]) -->
    [].
variables([H|T]) -->
    { get(H, name, Name),
      get(H, type, Type),
      get(H, summary, Summary)
    },
    html([ tr([td(Name), td(\type(Type)), td(Summary)])
         ]),
    variables(T).


                 /*******************************
                 *          BEHAVIOUR           *
                 *******************************/

classbehaviour(Class) -->
    { collect_behaviour(Class, Chain),
      group_objects(Chain, Groups), % Groups is a sheet name->chain
      get_chain(Groups, attribute_names, List)
    },
    html(h2('Behaviour')),
    groups(List, Groups).

groups([], _) -->
    [].
groups([H|T], Groups) -->
    { get(Groups, value, H, Chain),
      chain_list(Chain, Members)
    },
    group(H, Members),
    groups(T, Groups).

group(Group, Members) -->
    { cluster_behaviour(Members, Clusters),
      chain_list(Clusters, List)
    },
    html([ \group_header(Group),
           dl(\behaviour_clusters(List))
         ]).


group_header(Group) -->
    { group_summary(Group, Summary),
      !,
      get(Group, capitalise, GroupName)
    },
    html(h4([hr([]), GroupName, ' -- ', em(Summary)])).
group_header(Group) -->
    { get(Group, capitalise, GroupName)
    },
    html(h4(GroupName)).


behaviour_clusters([]) -->
    [].
behaviour_clusters([H|T]) -->
    { chain_list(H, L),
      L = [First|_]
    },
    html([ dt(\headlines(L)),
           dd(\description(First))
         ]),
    behaviour_clusters(T).

headlines([]) -->
    [].
headlines([H]) -->
    !,
    headline(H).
headlines([H|T]) -->
    !,
    headline(H),
    html(br([])),
    headlines(T).

                 /*******************************
                 *          INHERITANCE         *
                 *******************************/

%       /inherit?class=Class
%
%       Show inheritance/delegation picture

reply('/inherit', Form, HTTPD) :-
    Form \== @nil,
    get(Form, value, class, Class),
    make_diagram([Class], Dia),
    send(HTTPD, reply, Dia).


:- dynamic
    saved_diagram/2.

make_diagram(Classes, I) :-
    saved_diagram(Classes, I),
    !.
make_diagram(Classes, I) :-
    new(I, man_inheritance_tree),
    send(I, level_gap, 15),
    forall(member(C, Classes), send(I, show, C, @off)),
    send(I, for_all,
         message(@prolog, add_href, @arg1?image)),
    send(I, lock_object, @on),
    assert(saved_diagram(Classes, I)).

add_href(Text) :-
    get(Text?string, value, ClassName),
    www_form_encode(ClassName, Encoded),
    atom_concat('/class?name=', Encoded, HREF),
    send(Text, attribute, href, HREF).


                 /*******************************
                 *        CLASS HIERARCHY       *
                 *******************************/

%       /classhierarchy
%       /classhierarchy?root=name
%
%       Emit the class hierarchy

reply('/classhierarchy', Form, HTTPD) :-
    (   Form \== @nil,
        get(Form, value, root, Root)
    ->  true
    ;   Root = object
    ),
    get(HTTPD, request, Request),
    (   get(Request, value, cookie, Cookie)
    ;   Cookie = []
    ),
    send(HTTPD, reply_html, pce_http_man:classhierarchy(Root, Cookie)).
reply(Path, @nil, HTTPD) :-
    html_hierarchy_image(Path, Image),
    !,
    send(HTTPD, reply, Image).

classhierarchy(Root, Cookie) -->
    {   pageYOffset(Cookie, Y), Y \== 0
    ->  sformat(JS, 'window.scrollTo(0, ~w)', [Y]),
        OnLoad = [onLoad(JS)]
    ;   OnLoad = []
    },
    page([ head(title('XPCE Class Hierarchy')),
           body([ bgcolor(white)
                | OnLoad
                ],
                [ h3('Class Hierarchy')
                | \html_hierarchy(Root,
                                  gen_subclass, hierarchy_class_name,
                                  Cookie)
                ])
         ]).

hierarchy_class_name(Name) -->
    { www_form_encode(Name, Encoded),
      atom_concat('/class?name=', Encoded, URL)
    },
    html(a([name(Encoded), href(URL), target(description)], Name)).

gen_subclass(Super, Sub) :-
    get(@pce, convert, Super, class, Class),
    get(Class, sub_classes, Chain),
    chain_list(Chain, List),
    member(SubClass, List),
    get(SubClass, name, Sub).

%       /man?for=Spec
%
%       As manpce/1: handle @ref, class, class->method, class<-method, etc.

reply('/man', Form, HTTPD) :-
    (   get(Form, value, for, String)
    ->  atom_to_method(String, Object)
    ;   get(Form, value, id, Id),
        man_search:object_from_id(Id, Object)
    ),
    send(HTTPD, reply_html, pce_http_man:objpage(Object)).

objpage(Object) -->
    page([title('XPCE Manual')],
         [\objdoc(Object)
         ]).

objdoc(Object) -->
    { send(Object, instance_of, class)
    },
    !,
    classdoc(Object).
objdoc(SendMethod) -->
    { send(SendMethod, instance_of, behaviour)
    },
    !,
    html(dl(\behaviour(SendMethod))).
objdoc(Object) -->
    html(dl(\object(Object))).


behaviour(M) -->
    html([ dt(\headline(M)),
           dd(\description(M))
         ]).

object(@Ref) -->
    html([ dt(b([@, Ref])),
           dd(\description(@Ref))
         ]).

headline(SM) -->
    { send(SM, instance_of, send_method)
    },
    !,
    html([ \contextclass(SM),
           '->',
           b(\name(SM)),
           '(',
           \argv(SM),
           ')'
         ]).
headline(GM) -->
    { send(GM, instance_of, get_method),
      get(GM, return_type, Return)
    },
    !,
    html([ \contextclass(GM),
           '<-',
           b(\name(GM)),
           '(',
           \argv(GM),
           ') --> ',
           \type(Return)
         ]).
headline(V) -->
    { send(V, instance_of, variable),
      get(V, access_arrow, Arrow),
      get(V, type, Type)
    },
    !,
    html([ \contextclass(V),
           Arrow,
           b(\name(V)),
           ': ',
           \type(Type)
         ]).
headline(V) -->
    { send(V, instance_of, class)
    },
    !,
    html([ 'Class ', b(\name(V))
         ]).
headline(V) -->
    objref(V).

contextclass(SM) -->
    { get(SM, context, Class),
      send(Class, instance_of, class)
    },
    class_name(Class).

name(Obj) -->
    { send(Obj, has_get_method, name),
      !,
      get(Obj, name, Name)
    },
    html(Name).
name(Obj) -->
    html(Obj).

objref(@Obj) -->
    { get(@Obj, class_name, Name)
    },
    html([@, Obj, /, Name]).

argv(Method) -->
    { get(Method, types, Argv),
      get(Argv, size, Size)
    },
    argv(1, Size, Argv).

argv(I, AC, V) -->
    { I =< AC,
      !,
      get(V, element, I, Type)
    },
    (   { get(Type, argument_name, ArgName),
          ArgName \== @nil
        }
    ->  html([ var(ArgName),
               =,
               \type(Type)
             ])
    ;   type(Type)
    ),
    (   { I < AC
        }
    ->  [ ', ' ]
    ;   []
    ),
    { NI is I + 1
    },
    argv(NI, AC, V).
argv(_, _, _) -->
    [].


                 /*******************************
                 *            SEARCH            *
                 *******************************/

%       /search?for=pattern
%
%       Execute a search

reply('/search', @nil, HTTPD) :-
    !,
    send(HTTPD, reply_html, pce_http_man:searchpage).

searchpage -->
    page([ title('Search XPCE manual')
         ],
         [ \searchhead,
           \searchform('', 25)
         ]).

searchhead -->
    html([ h1('Search the XPCE reference manual'),
           p([ 'Please use the form below to search through the XPCE ',
               'reference material. ',
               'Advanced syntax: '
             ]),
           dl([dt(b('<...>')),
               dd('Word-match rather then substring match'),
               dt(b('not ...')),
               dd('Not containing ...'),
               dt(b('... and ...')),
               dd('Containing both expressions (default)'),
               dt(b('... or ...')),
               dd('Containing either expression'),
               dt(b('(...)')),
               dd('Use braces to specify nesting')
              ]),
           p([])
         ]).

searchform(For, Max) -->
    html(form([ action('/search'),
                method('GET')
              ],
              table(align(center),
                    [ tr([ td(align(right), b('Search for')),
                           td(colspan(2),
                              input([name(for), value(For), size(40)]))
                         ]),
                      tr([ td(align(right), b('Max results')),
                           td(align(left),
                              select(name(max_results),
                                     [ \option(10, Max),
                                       \option(25, Max),
                                       \option(100, Max)
                                     ])),
                           td(align(right),
                              input(type(submit)))
                         ])
                    ]))).

option(Value, Value) -->
    !,
    html(option(selected, Value)).
option(Value, _) -->
    html(option([], Value)).

reply('/search', Form, HTTPD) :-
    get(Form, value, for, For),
    (   get(Form, value, max_results, M0),
        get(@pce, convert, M0, int, Max)
    ->  true
    ;   Max = 25
    ),
    (   get(Form, value, from, From0),
        get(@pce, convert, From0, int, From)
    ->  true
    ;   From = 0
    ),
    send(HTTPD, reply_html, pce_http_man:search(For, Max, From)).

search(For, Max, From) -->
    { search_index(@man_index),
      man_search:parse_search_spec(For, Term),
      man_search:execute_search(Term, @man_index, CardsIds),
      get(CardsIds, size, Matches),
      (   From == 0
      ->  (   Matches > Max
          ->  get(CardsIds, sub, 0, Max, Ch2),
              chain_list(Ch2, List),
              Found = p([ 'Showing first ~w matches of ~w. '-
                            [Max, Matches],
                          \next(For, Max, From)
                        ])
          ;   chain_list(CardsIds, List),
              Found = p('Found ~w matches'-[Matches])
          )
      ;   To is From+Max,
          get(CardsIds, sub, From, To, Ch2),
          chain_list(Ch2, List),
          (   Matches > To
          ->  Next = [\next(For, Max, From)
                     ]
          ;   Next = []
          ),
          get(List, size, Size),
          TheTo is From + Size,
          Found = p([ 'Showing matches from ~w to ~w from ~w. '-
                        [From, TheTo, Matches]
                    | Next
                    ])
      )
    },
    page([title(['XPCE Search results for ', For])],
         [ h2(['Search results for ', em(For)]),
           Found,
           p([]),
           table([ width('100%')
                 ],
                 [ col(width('30%')),
                   col(width('70%'))
                 | \search_results(List)
                 ]),
           p([]),
           hr([]),
           \searchform(For, Max)
         ]).

next(For, Max, From) -->
    { NewFrom is From+Max,
      www_form_encode(For, F1),
      www_form_encode(Max, F2),
      www_form_encode(NewFrom, F3),
      atomic_list_concat(['/search?for=', F1,
                   '&max_results=', F2,
                   '&from=', F3],
                  URL)
    },
    html(a(href(URL), next)).


search_results([]) -->
    [].
search_results([H|T]) -->
    search_result(H),
    search_results(T).

search_result(Id) -->
    { man_search:object_from_id(Id, Object),
      www_form_encode(Id, Encoded),
      atom_concat('/man?id=', Encoded, HREF),
      (   get(Object, summary, Summary),
          Summary \== @nil
      ;   Summary = ''
      )
    },
    html([ tr([ td(a(href(HREF), Object)),
                td(Summary)
              ])
         ]).


search_index(Index) :-
    object(Index),
    !.
search_index(@Ref) :-
    absolute_file_name(pce('/man/reference/index'),
                       [ extensions([obj]),
                         access(read),
                         file_errors(fail)
                       ],
                       IndexFile),
    get(file(IndexFile), object, Obj),
    send(Obj, name_reference, Ref).

%       /about
%
%       Temporary stuff

reply('/about', @nil, HTTPD) :-
    send(HTTPD, reply_html, pce_http_man:about).

about -->
    page([ title('About the XPCE Web manual')
         ],
         [ h3('About the XPCE Web manual'),

           p(\['The XPCE Web-manual is based on the built-in XPCE online ',
               'manual started using the <b>manpce/0</b> predicate.']),
           p(\['This manual can be read from the main XPCE site or installed ',
               'locally.  Please refer to the directory ',
               '<b><tt>.../xpce/prolog/lib/http</tt></b> for details.'])
         ]).

reply('/top', @nil, HTTPD) :-
    send(HTTPD, reply_html, pce_http_man:top).

top -->
    { url(pcehome, Home),
      url(pceusg, USG)
    },
    page([ title('XPCE reference manual index'),
           meta(['http-equiv'('Refresh'), content(60)])
         ],
         [ p(align(center),
             [ \link(Home, 'XPCE Home'), ' ',
               \link(USG,  'User Guide'), ' ',
               \link('/search', 'Search'), ' ',
               \link('/about',  'About'),
               br([]),
               font(size(-1), em(\info))
             ])
         ]).


link(URL, Name) -->
    html([ '[', a([ href(URL), target(description) ], Name), ']' ]).


info -->
    { get(@pce, version, Version),
      flag(requests, Requests, Requests),
      statistics(cputime, CPU),
      sformat(C2, '~2f', [CPU])
    },
    html([ 'XPCE ', Version,
           '; Up ', \uptime,
           '; Processed ', Requests, ' requests in ', C2, ' seconds'
          ]).

:- pce_global(@started, new(date)).
:- get(@started, class, _).             % just create it

uptime -->
    { get(new(date), difference, @started, minute, UpMinutes),
      UpDays  is UpMinutes // (24*60),
      UpHours is UpMinutes // 60 - UpDays*24,
      UpMin   is UpMinutes mod 60
    },
    html([ UpDays, ' days ', UpHours, h, UpMin, m ]).





%       /blank
%
%       Just emit a blank page

reply('/blank', @nil, HTTPD) :-
    send(HTTPD, reply_html, pce_http_man:blankpage).

blankpage -->
    page([title(blank)], []).

%       Catch all.  Do not add clauses for reply below this line

reply(Path, @nil, HTTPD) :-
    send(HTTPD, not_found, Path).



                 /*******************************
                 *             TYPES            *
                 *******************************/

type(T) -->
    { get(T, kind, alias),
      get(T, argument_name, ArgName),
      ArgName \== @nil,
      !,
      get(T, context, Type)
    },
    type(Type).
type(T) -->
    { get(T, kind, class),
      !,
      get(T, context, C),
      (   atom(C)
      ->  Name = C
      ;   get(C, name, Name)
      )
    },
    type_default(T, '['),
    class_name(Name),
    type_supers(T),
    type_default(T, ']'),
    type_nil(T),
    type_vector(T).
type(T) -->
    { get(T, name, Name),
      atom_length(Name, L)
    },
    (   { L > 20,
          make_breakable(Name, Full)
        }
    ->  html(Full)
    ;   html(Name)
    ).

make_breakable(Atom, Breakable) :-
    new(Breakable, string('%s', Atom)),
    send(regex('([,|])'), for_all, Breakable,
               message(@arg1, replace, @arg2, '\\1 ')).

type_default(T, C) -->
    { get(T, supers, Supers), Supers \== @nil,
      send(Supers, member, type(default))
    },
    !,
    [ C ].
type_default(_, _) -->
    [].

type_nil(T) -->
    { get(T, supers, Supers), Supers \== @nil,
      send(Supers, member, type(nil))
    },
    !,
    [ '*' ].
type_nil(_) -->
    [].

type_vector(T) -->
    { get(T, vector, @on)
    },
    !,
    [ '...' ].
type_vector(_) -->
    [].

type_supers(T) -->
    { get(T, supers, Supers), Supers \== @nil,
      chain_list(Supers, L)
    },
    !,
    t_supers(L).
type_supers(_) -->
    [].

t_supers([]) -->
    [].
t_supers([H|T]) -->
    (   { get(H, name, nil)
        ; get(H, name, default)
        }
    ->  []
    ;   ['|'],
        type(H)
    ),
    t_supers(T).
