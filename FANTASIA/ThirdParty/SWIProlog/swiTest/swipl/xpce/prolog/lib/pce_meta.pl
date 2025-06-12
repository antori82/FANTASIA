/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org/packages/xpce/
    Copyright (c)  1999-2011, University of Amsterdam
                              VU University Amsterdam
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

:- module(pce_meta,
          [ pce_to_method/2,            % +Spec, -BehaviourObject
            isa_class/2,                % ?SubClassName, ?SuperClassName
            current_class/2,            % ?ClassName, ?ClassObject
            to_class_name/2,            % +NameOrClass, -ClassName
            pce_library_class/4,        % ?Name, ?Super, ?Comment, ?File
            implements/2,               % ?Class, ?SendOrGet(?Name)
            implements/3,               % idem, -Method
            pce_to_pl_type/2,           % +PceType, -PrologType
            type_accepts_function/1,    % +Type
            classify_class/2            % +Class, -Classification
          ]).
:- use_module(library(pce)).
:- require([ pce_error/1
           , chain_list/2
           , get_chain/3
           , maplist/3
           ]).

/** <module> Reflection support for XPCE

This module defines utilities to  simplify   reflexion  support of XPCE,
notably implementing non-deterministic logical relations   on top of the
deterministic XPCE methods.
*/


                 /*******************************
                 *      INTERACTION SUPPORT     *
                 *******************************/

%!  pce_to_method(+Spec, -Object) is semidet.
%
%   Object is the XPCE object described by Spec.  Spec is one of
%
%           * send(Receiver, Selector)
%           * ->(Receiver, Selector)
%           Find a send-method on Receiver
%           * get(Receiver, Selector)
%           * <-(Receiver, Selector)
%           Find a get-method on Receiver
%           * Receiver-Selector
%           Find an instance variable (slot) on Receiver
%           * ClassName
%           Find a class from its name

pce_to_method(->(Receiver, Selector), Method) :-
    !,
    (   atom(Receiver)
    ->  get(@pce, convert, Receiver, class, Class),
        get(Class, send_method, Selector, Method)
    ;   object(Receiver)
    ->  get(Receiver, send_method, Selector, tuple(_, Method))
    ).
pce_to_method(<-(Receiver, Selector), Method) :-
    !,
    (   atom(Receiver)
    ->  get(@pce, convert, Receiver, class, Class),
        get(Class, get_method, Selector, Method)
    ;   object(Receiver)
    ->  get(Receiver, get_method, Selector, tuple(_, Method))
    ).
pce_to_method((Receiver-Selector), Method) :-
    !,
    (   atom(Receiver)
    ->  get(@pce, convert, Receiver, class, Class),
        get(Class, instance_variable, Selector, Method)
    ;   object(Receiver),
        get(Receiver, attribute, Method)
    ->  true
    ;   object(Receiver),
        get(Receiver, class, Class),
        get(Class, instance_variable, Selector, Method)
    ).
pce_to_method(ClassName, Class) :-
    atom(ClassName),
    get(@pce, convert, ClassName, class, Class),
    !.
pce_to_method(Method, Method) :-
    object(Method),
    !.
pce_to_method(get(Receiver, Selector), Method) :-
    !,
    pce_to_method(<-(Receiver, Selector), Method).
pce_to_method(send(Receiver, Selector), Method) :-
    !,
    pce_to_method(->(Receiver, Selector), Method).


                 /*******************************
                 *           CLASSES            *
                 *******************************/

%!  isa_class(?Sub, ?Super)
%
%   Succeeds if Sub is Super or below Super.  Can be used with any
%   instantiation.  If class is instantiated the super-chain is
%   followed.

isa_class(Class, Super) :-
    ground(Class),
    !,
    gen_super(Class, Super).
isa_class(Class, Super) :-
    current_class(Class, ClassObject),
    current_class(Super, SuperObject),
    send(ClassObject, is_a, SuperObject).

gen_super(Class, Class).
gen_super(Class, Super) :-
    current_class(Class, ClassObject),
    get(ClassObject, super_class, SuperObject),
    current_class(Super0, SuperObject),
    gen_super(Super0, Super).


%!  current_class(?Name, ?Class)
%
%   Convert between name and class object.  Insufficient instantation
%   enumerates the classes.

:- dynamic
    current_class_cache/2.


make_current_class :-
    retractall(current_class_cache(_,_)),
    send(@classes, for_all,
         message(@prolog, assert_class, @arg1, @arg2)),
    send(class(class), created_message,
         message(@prolog, assert_class, @arg2?name, @arg2)).

assert_class(Name, Object) :-
    assert(current_class_cache(Name, Object)).

:- initialization
    make_current_class.

current_class(Class, ClassObject) :-
    current_class_cache(Class, ClassObject).
current_class(Class, ClassObject) :-
    pce_prolog_class(Class),
    \+ current_class_cache(Class, _),
    get(@pce, convert, Class, class, ClassObject).


%!  to_class_name(+AtomOrClass, -ClassName)
%
%   Convert a name or class-object into a class name

to_class_name(Name0, Name) :-
    atom(Name0),
    !,
    (   current_class(Name0, _)
    ->  Name = Name0
    ;   pce_error(no_class(Name0))
    ).
to_class_name(ClassObj, Name) :-
    object(ClassObj),
    send(ClassObj, instance_of, class),
    !,
    get(ClassObj, name, Name).


                 /*******************************
                 *            LIBRARY           *
                 *******************************/

:- dynamic
    library_index/4,
    index_files/1.

%!  pce_library_class(?Name, ?Super, ?Comment, ?File)
%
%   Examine the library index for defined classes.

pce_library_class(Name, Super, Comment, library(File)) :-
    atom(Name),
    !,
    (   library_index(Name, Super, Comment, File)
    *-> true
    ;   update_library_index,
        library_index(Name, Super, Comment, File)
    ).

update_library_index :-
    setof(File, index_file(File), Files),
    (   index_files(Files)
    ->  true
    ;   retractall(index_files(_)),
        retractall(library_index(_,_,_,_)),
        load_index_files(Files),
        assert(index_files(Files))
    ).


index_file(File) :-
    absolute_file_name(library('CLASSINDEX.pl'), File,
                       [ access(read),
                         solutions(all),
                         file_errors(fail)
                       ]).

load_index_files([]).
load_index_files([H|T]) :-
    load_index_file(H),
    load_index_files(T).

load_index_file(File) :-
    open(File, read, In),
    read(In, Term),
    call_cleanup(read_index(Term, In), close(In)).

read_index(end_of_file, _) :- !.
read_index(class(Name, Super, Comment, File), In) :-
    assert(library_index(Name, Super, Comment, File)),
    read(In, Term),
    read_index(Term, In).


                 /*******************************
                 *            METHODS           *
                 *******************************/

%!  implements(?Class:atom, ?Method:atom) is nondet.
%!  implements(?Class:atom, ?Method:atom, -MethodObj:object) is nondet.
%
%   True if Class implements the method.  If class is a variable,
%   backtracking yields all classes
%
%   `What'  may  be  wrapped  in  self(What)  or  root(What).  Using
%   self(What) returns only those classes  that have a non-inherited
%   implementation of the method,  while   using  root(What) returns
%   only  those  classes  for   which    there   is  no  super-class
%   implementing the requested method.
%
%   @param Class    Name of XPCE class
%   @param Method   One of send(Name) or get(Name)
%   @param MethodObj XPCE Object representing the method

implements(Class, What) :-
    implements(Class, What, _).

implements(Class, self(What), Method) :-
    implements(Class, What, Method),
    get(Method, context, ClassObject),
    get(ClassObject, name, Class).
implements(Class, root(What), Method) :-
    implements(Class, self(What), Method),
    (   send(Method, has_get_method, inherited_from)
    ->  \+ get(Method, inherited_from, _)
    ;   true
    ).
implements(Class, send(Name), Method) :-
    current_class(Class, ClassObject),
    (   atom(Name)
    ->  get(ClassObject, send_method, Name, Method)
    ;   isa_class(Class, Super),
        current_class(Super, SuperObject),
        (   get_chain(SuperObject, send_methods, Methods)
        ;   get_chain(SuperObject, instance_variables, Methods)
        ),
        member(Method, Methods),
        get(Method, name, Name),
        get(ClassObject, send_method, Name, Method)         % not overruled
    ).
implements(Class, get(Name), Method) :-
    current_class(Class, ClassObject),
    (   atom(Name)
    ->  get(ClassObject, get_method, Name, Method)
    ;   isa_class(Class, Super),
        current_class(Super, SuperObject),
        (   get_chain(SuperObject, get_methods, Methods)
        ;   get_chain(SuperObject, instance_variables, Methods)
        ),
        member(Method, Methods),
        get(Method, name, Name),
        get(ClassObject, get_method, Name, Method)
    ).


                 /*******************************
                 *             TYPES            *
                 *******************************/

%!  pce_to_pl_type(+PceType, -PrologType)
%   Convert an XPCE Type object to our type-checkers type-logic.
%

pce_to_pl_type(Type, Pl) :-
    get(Type, kind, Kind),
    pce_to_pl_type(Kind, Type, Pl0),
    type_supers(Pl0, Type, Pl).

type_supers(Pl0, Type, Pl) :-
    get(Type, supers, Supers),
    Supers \== @nil,
    !,
    chain_list(Supers, SuperList),
    maplist(pce_to_pl_type, SuperList, PlSupers),
    list_to_or([Pl0|PlSupers], Pl).
type_supers(Pl, _, Pl).

pce_to_pl_type(class, Type, Pl) :-
    get(Type, context, Context),
    (   atom(Context)
    ->  Class = Context
    ;   get(Context, name, Class)
    ),
    class_type(Class, Pl).
pce_to_pl_type(class_object, _, and(sub(object), not(sub(function)))).
pce_to_pl_type(unchecked,    _, or(sub(object), integer)).
pce_to_pl_type(any,          _, and(or(sub(object), integer),
                                    not(sub(function)))).
pce_to_pl_type(int,          _, integer).
pce_to_pl_type(char,         _, integer(0,255)).
pce_to_pl_type(int_range,    T, integer(Low, High)) :-
    get(T, context, tuple(Low0, High0)),
    to_range_boundary(Low0, Low),
    to_range_boundary(High0, High).
pce_to_pl_type(real_range,   T, float(Low, High)) :-
    get(T, context, tuple(Low0, High0)),
    to_range_boundary(Low0, Low),
    to_range_boundary(High0, High).
pce_to_pl_type(event_id,     _, or(integer, atom)).
pce_to_pl_type(value,        T, value(V)) :-
    get(T, context, V).
pce_to_pl_type(name_of,      T, Pl) :-
    get_chain(T, context, Atoms),
    list_to_value_or(Atoms, Pl).
pce_to_pl_type(member,       T, PlType) :-
    get(T, context, T2),
    pce_to_pl_type(T2, PlType).
pce_to_pl_type(value_set,    T, Pl) :-
    get_chain(T, context, Elements),
    list_to_value_or(Elements, Pl).
pce_to_pl_type(compound,     T, PlType) :-
    get_chain(T, context, Supers),
    maplist(pce_to_pl_type, Supers, PlSupers),
    list_to_or(PlSupers, PlType).
pce_to_pl_type(alias,        T, PlType) :-
    get(T, context, T2),
    pce_to_pl_type(T2, PlType).
pce_to_pl_type(alien,        _, integer).

class_type(name,   atom) :- !.
class_type(number, integer) :- !.
class_type(real,   float) :- !.
class_type(Class,  sub(Class)).

to_range_boundary(N, unbound) :-
    unbound(N),
    !.
to_range_boundary(N, N).

unbound(@nil).
unbound(1073741823).
unbound(-1073741824).


list_to_or([X], X) :- !.
list_to_or([A|B], or(A, C)) :-
    list_to_or(B, C).

list_to_value_or([X], value(X)) :- !.
list_to_value_or([A|B], or(value(A), T)) :-
    list_to_value_or(B, T).

%!  type_accepts_function(+Type)
%
%   Succeeds if Type accepts function arguments

type_accepts_function(Type) :-
    send(type(function), specialised, Type).

%!  classify_class(+ClassName, -Classification) is det.
%
%   Classify an XPCE class.  Defined classes are:
%
%     * built_in
%     * file(File)
%     * library(File)
%     * user(File)
%     * user
%     * undefined

classify_class(Name, built_in) :-
    get(@classes, member, Name, Class),
    get(Class, creator, built_in),
    !.
classify_class(Name, library(File)) :-
    pce_library_class(Name, _, _, FileSpec),
    FileSpec = library(File),
    (   get(@classes, member, Name, Class),
        get(Class, source, source_location(File, _Line))
    ->  absolute_file_name(FileSpec, File,
                           [ access(read)
                           ])

    ;   true
    ),
    !.
classify_class(Name, user(File)) :-
    get(@classes, member, Name, Class),
    get(Class, source, source_location(File, _Line)).
classify_class(Name, user(File)) :-
    pce_prolog_class(Name),
    pce_principal:pce_class(Name, _Meta, _Super, _Vars, _Res, Attributes),
    memberchk(send(@class, source, source_location(File, _Line)),
              Attributes),
    !.
classify_class(Name, user) :-
    get(@classes, member, Name, _),
    !.
classify_class(_, undefined).
