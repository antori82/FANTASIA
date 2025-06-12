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

:- module(xml_browse, []).
:- use_module(library(pce)).
:- use_module(library('doc/load')).
:- use_module(library('doc/xml_hierarchy')).
:- use_module(library(pprint)).
:- use_module(library(toolbar)).
:- use_module(library(pce_report)).
:- use_module(library(find_file)).

:- pce_global(@finder, new(finder)).

:- multifile
    doc:caption/2.

:- pce_begin_class(xml_browser, frame,
                   "Browse XML document").

initialise(B, XML:[prolog]) :->
    send_super(B, initialise, 'XML structure browser'),
    send(B, append, new(D, tool_dialog(B))),
    send(B, fill_dialog(D)),
    new(H, xml_browse_hierarchy(XML)),
    send(new(doc_window), right, H),
    send(H, below, D),
    send(new(report_dialog), below, H).

fill_dialog(B, D:tool_dialog) :->
    send_list(D, append,
              [ new(F, popup(file)),
                new(V, popup(view)),
                new(S, popup(search)),
                new(H, popup(help))
              ]),
    send_list(F, append,
              [ menu_item(open_file,
                          message(B, open_file)),
                gap,
                menu_item(exit,
                          message(B, destroy))
              ]),
    send_list(V, append,
              [ menu_item(dom,
                          message(B, view_dom),
                          'DOM')
              ]),
    send_list(S, append,
              [ menu_item(find_elements,
                          message(B, search))
              ]),
    send_list(H, append,
              [ menu_item(about,
                          message(B, about))
              ]).


xml(B, XML:prolog) :->
    get(B, member, doc_window, DW),
    send(DW, clear),
    get(B, member, xml_browse_hierarchy, H),
    send(H, xml, XML).

show_xml(B, Tokens:prolog) :->
    "Show parsed XML in browser"::
    get(B, member, doc_window, DW),
    send(DW, show, Tokens).

:- pce_group(action).

open_file(B) :->
    "Open SGML/XML/HTML file"::
    get(@finder, file, open,
        chain(tuple('HTML files', chain(html,htm)),
              tuple('XML files', xml),
              tuple('SGML files', chain(sgml,sgm)),
              tuple('All files', '*')),
        FileName),
    file_name_extension(_, Ext, FileName),
    dialect(Ext, Dialect),
    (   Dialect == html
    ->  load_html_file(FileName, DOM)
    ;   load_structure(FileName, DOM,
                       [ dialect(Dialect)
                       ])
    ),
    send(B, xml, DOM).

dialect(html, html).
dialect(htm,  html).
dialect(xml,  xml).
dialect(sgml, sgml).
dialect(sgm,  sgml).

about(_B) :->
    send(@display, inform,
         'Visualise HTML/XML/SGML DOM structure\n\c
              as produced by library(sgml)\n\n\c
              By Jan Wielemaker\n\c
              jan@swi.psy.uva.nl').

view_dom(B) :->
    get(B, member, xml_browse_hierarchy, H),
    get_chain(H, selection, Selection),
    (   Selection == []
    ->  send(B, report, warning, 'No selection')
    ;   new(V, view),
        pce_open(V, write, Fd),
        forall(member(Node, Selection),
               (   get(Node, xml, DOM),
                   print_term(DOM,
                              [ output(Fd),
                                right_margin(78)
                              ])
               )),
        close(Fd),
        send(V, caret, 0),
        send(V, open)
    ).

search(B) :->
    "Search the hierarchy"::
    new(D, dialog('Search DOM')),
    send(D, append, new(T, text_item(text))),
    send(D, append, new(E, text_item(element))),
    send(D, append, new(A, text_item(attribute))),
    send(D, append, new(V, text_item(value))),
    send(D, append, button(search, message(B, search_for,
                                           T?selection,
                                           E?selection,
                                           A?selection,
                                           V?selection))),
    send(D, append, button(done, message(D, destroy))),
    send(D, default_button(search)),
    send(D, transient_for, B),
    send(D, open_centered, B?area?center).

search_for(B,
           Text0:name,
           Element0:name,
           Attribute0:name,
           Value0:name) :->
    "Execute search"::
    mkvar(Text0, Text),
    mkvar(Element0, Element),
    mkvar(Attribute0, Attribute),
    mkvar(Value0, Value),
    (   var(Attribute),
        var(Value)
    ->  true
    ;   A = (Attribute = Value)
    ),
    get(B, member, xml_browse_hierarchy, H),
    get(H, root, Root),
    send(Root, collapsed, @on),
    send(H, selection, @nil),
    get(H, xml, DOM),
    findall(Node, find_node(B, DOM, Element, A, Text, Node), Nodes),
    (   Nodes == []
    ->  send(B, report, warning, 'No match')
    ;   length(Nodes, Len),
        send(B, report, status, 'Found %d matching elements', Len),
        send(H, normalise, Nodes)
    ).

mkvar('', _) :- !.
mkvar(X, X).

find_node(B, DOM, E, A, T, Node) :-
    find(DOM, E, A, T, Path),
    get(B, member, xml_browse_hierarchy, H),
    get(H, node_from_path, Path, Node),
    send(Node, selected, @on).

find(element(E, AL, Content), E, A, Text, []) :-
    (   var(A)
    ->  true
    ;   memberchk(A, AL)
    ),
    (   var(Text)
    ->  true
    ;   member(Atom, Content),
        atom(Atom),
        sub_atom(Atom, _, _, _, Text)
    ->  true
    ).
find(element(_, _, Content), E, A, Text, [N|T]) :-
    nth_element(N, Content, Sub),
    find(Sub, E, A, Text, T).

%       nth_element(-N, +List, -Element)
%
%       As nth1/3, but only counts the element(_,_,_) terms in the
%       list.

nth_element(N, Content, E) :-
    nth_element(Content, E, 1, N).

nth_element([Elem|_], Elem, Base, Base) :-
    Elem = element(_,_,_).
nth_element([H|Tail], Elem, N, Base) :-
    (   H = element(_,_,_)
    ->  succ(N, M)
    ;   M = N
    ),
    nth_element(Tail, Elem, M, Base).

:- pce_end_class(xml_browser).

                 /*******************************
                 *            HIERARCHY         *
                 *******************************/

:- pce_begin_class(xml_browse_hierarchy, xml_hierarchy,
                   "Browse an XML hierarchy").

select_node(H, Node:xml_node) :->
    "Show content of selected node"::
    get(Node, xml, Tokens),
    send(H?frame, show_xml, Tokens).

caption(H, XML:prolog, Caption:name) :<-
    "Provide caption"::
    (   doc:caption(XML, Caption)
    ->  true
    ;   get_super(H, caption, XML, Caption)
    ->  true
    ;   XML=[_|_]
    ->  Caption = '<Elements>'
    ;   Caption = '??'
    ).

:- pce_end_class.

