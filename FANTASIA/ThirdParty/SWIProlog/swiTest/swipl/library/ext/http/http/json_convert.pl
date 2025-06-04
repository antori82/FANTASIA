/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2007-2014, University of Amsterdam
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

:- module(json_convert,
          [ prolog_to_json/2,           % :Term, -JSON object
            json_to_prolog/2,           % +JSON, :Term
            (json_object)/1,            % +Definition
            op(1150, fx, (json_object))
          ]).
:- use_module(library(error)).
:- use_module(library(pairs)).
:- use_module(library(apply)).
:- use_module(json).

:- meta_predicate
    prolog_to_json(:, -),
    json_to_prolog(+, :).

:- public
    clear_cache/0,
    prolog_list_to_json/3,          % +ListIn, -ListOut, +Module
    prolog_to_json/3,               % +In, -Out, +Module
    prolog_bool_to_json/2.          % +In, -Boolean

/** <module> Convert between JSON terms and Prolog application terms

The idea behind this module is to  provide a flexible high-level mapping
between Prolog terms as you would like   to see them in your application
and the standard representation of a JSON   object as a Prolog term. For
example,  an  X-Y  point  may  be  represented  in  JSON  as  =|{"x":25,
"y":50}|=. Represented in Prolog  this   becomes  json([x=25,y=50]), but
this is a pretty non-natural  representation   from  the Prolog point of
view.

This module allows for defining records (just like library(record)) that
provide   transparent   two-way   transformation     between   the   two
representations.

  ==
  :- json_object
          point(x:integer, y:integer).
  ==

This declaration causes prolog_to_json/2 to translate the native Prolog
representation into a JSON Term:

  ==
  ?- prolog_to_json(point(25,50), X).

  X = json([x=25, y=50])
  ==

A json_object/1 declaration can define multiple   objects separated by a
comma (,), similar to the dynamic/1 directive. Optionally, a declaration
can  be  qualified   using   a    module.   The   conversion  predicates
prolog_to_json/2 and json_to_prolog/2 first try  a conversion associated
with the calling  module.  If  not   successful,  they  try  conversions
associated with the module =user=.

JSON objects have no _type_. This can be solved by adding an extra field
to the JSON object, e.g. =|{"type":"point", "x":25, "y":50}|=. As Prolog
records are typed by their functor we need some notation to handle this
gracefully. This is achieved by adding +Fields to the declaration. I.e.

  ==
  :- json_object
          point(x:integer, y:integer) + [type=point].
  ==

Using this declaration, the conversion becomes:

  ==
  ?- prolog_to_json(point(25,50), X).

  X = json([x=25, y=50, type=point])
  ==

The predicate json_to_prolog/2 is often  used after http_read_json/2 and
prolog_to_json/2 before reply_json/1. For now  we consider them separate
predicates because the transformation may be   too  general, too slow or
not needed for dedicated  applications.  Using   a  separate  step  also
simplifies debugging this rather complicated process.

@tbd    Ignore extra fields.  Using a partial list of _extra_?
@tbd    Consider a sensible default for handling JSON =null=.  Conversion
        to Prolog could translate @null into a variable if the desired type
        is not =any=.  Conversion to JSON could map variables to =null=,
        though this may be unsafe.  If the Prolog term is known to be
        non-ground and JSON @null is a sensible mapping, we can also use
        this simple snipit to deal with that fact.

        ==
                term_variables(Term, Vars),
                maplist(=(@null), Vars).
        ==
*/

%!  current_json_object(Term, Module, Fields)
%
%   Multifile   predicate   computed   from     the    json_object/1
%   declarations. Term is the most  general Prolog term representing
%   the object. Module is the module in  which the object is defined
%   and Fields is a list of f(Name,  Type, Default, Var), ordered by
%   Name. Var is the corresponding variable in Term.

:- multifile
    json_object_to_pairs/3,         % Term, Module, Pairs
    current_json_object/3.          % Term, Module, Fields

%!  json_object(+Declaration)
%
%   Declare a JSON object.  The declaration takes the same format as
%   using in record/1 from library(record).  E.g.
%
%     ==
%     ?- json_object
%           point(x:int, y:int, z:int=0).
%     ==
%
%   The type arguments are either types as know to library(error) or
%   functor  names  of  other  JSON   objects.  The  constant  =any=
%   indicates an untyped argument.  If  this   is  a  JSON  term, it
%   becomes  subject  to  json_to_prolog/2.  I.e.,  using  the  type
%   list(any) causes the conversion to be   executed on each element
%   of the list.
%
%   If a field has a default, the default   is  used if the field is
%   not specified in the JSON  object.   Extending  the  record type
%   definition, types can be of  the   form  (Type1|Type2). The type
%   =null= means that the field may _not_ be present.
%
%   Conversion of JSON  to  Prolog   applies  if  all  non-defaulted
%   arguments can be found in  the   JSON  object. If multiple rules
%   match, the term with the highest arity gets preference.

json_object(Declaration) :-
    throw(error(context_error(nodirective, json_object(Declaration)), _)).


%!  compile_json_objects(+Spec, -Clauses) is det.
%
%   Compiles a :- json_object directive into Clauses. Clauses are of
%   the form:
%
%   ==
%   json_object_to_pairs(Term, Module, Pairs) :-
%           <type-checks on Term>,
%           <make Pairs from Term>.
%   ==

compile_json_objects(Spec, Clauses) :-
    phrase(compile_objects(Spec), Clauses).

compile_objects(A) -->
    { var(A),
      !,
      instantiation_error(A)
    }.
compile_objects((A,B)) -->
    !,
    compile_objects(A),
    compile_objects(B).
compile_objects(Term) -->
    compile_object(Term).

compile_object(ObjectDef) -->
    { prolog_load_context(module, CM),
      strip_module(CM:ObjectDef, M, Def),
      extra_defs(Def, Term, ExtraFields),
      Term =.. [Constructor|Args],
      defaults(Args, Defs, TypedArgs),
      types(TypedArgs, Names, Types)
    },
    record_to_json_clause(Constructor, M, Types, Names, ExtraFields),
    current_clause(Constructor, M, Types, Defs, Names, ExtraFields),
    [ (:- json_convert:clear_cache) ].

extra_defs(Term+Extra0, Term, Extra) :-
    !,
    must_be(list, Extra0),
    maplist(canonical_pair, Extra0, Extra).
extra_defs(Term,       Term, []).


canonical_pair(Var, _) :-
    var(Var),
    !,
    instantiation_error(Var).
canonical_pair(Name=Value, Name=Value) :-
    !,
    must_be(atom, Name).
canonical_pair(Name-Value, Name=Value) :-
    !,
    must_be(atom, Name).
canonical_pair(NameValue, Name=Value) :-
    NameValue =.. [Name,Value],
    !.
canonical_pair(Pair, _) :-
    type_error(pair, Pair).


%!  record_to_json_clause(+Constructor, +Module, +Type, +Names)
%
%   Create a clause translating the record   definition into a pairs
%   representation.

record_to_json_clause(Constructor, Module, Types, Names, Extra) -->
    { type_checks(Types, VarsHead, VarsBody, Body0, Module),
      clean_body(Body0, Body),
      Term =.. [Constructor|VarsHead],
      make_pairs(Names, VarsBody, Pairs, Extra),
      Head =.. [json_object_to_pairs,Term,Module,json(Pairs)]
    },
    [ (json_convert:(Head :- Body)) ].


%!  type_checks(+Types, -VarsIn, -VarsOut, -Goal, +Module) is det.
%
%   Goal is a body-term  that  validates   Vars  satisfy  Types.  In
%   addition to the types accepted by   must_be/2,  it accepts =any=
%   and Name/Arity. The latter demands  a   json_object  term of the
%   given Name and Arity.
%
%   @tbd    Compile list(Type) specification.  Currently Type is
%           handled like =any=

type_checks([], [], [], true, _).
type_checks([Type|T], [IV|IVars], [OV|OVars], (Goal, Body), M) :-
    !,
    type_check(Type, IV, OV, M, Goal),
    type_checks(T, IVars, OVars, Body, M).

type_check(any, IV, OV, M, prolog_to_json(IV, OV, M)) :- !.
type_check(Name/Arity, IV, OV, M, prolog_to_json(IV, OV, M)) :-
    !,
    functor(IV, Name, Arity).
type_check(boolean, IV, OV, _, prolog_bool_to_json(IV, OV)) :- !.
type_check(list, IV, OV, M, prolog_list_to_json(IV, OV, M)) :- !.
type_check(list(any), IV, OV, M, prolog_list_to_json(IV, OV, M)) :- !.
type_check(list(_Type), IV, OV, M, prolog_list_to_json(IV, OV, M)) :- !.
type_check(Type, V, V, _, Goal) :-
    type_goal(Type, V, Goal).


%!  prolog_bool_to_json(+Prolog, -JSON) is semidet.
%
%   JSON is the JSON boolean for Prolog. It is a flexible the Prolog
%   notation for thruth-value, accepting one of  =true=, =on= or =1=
%   for @true and one of =false=, =fail=, =off= or =0= for @false.
%
%   @error  instantiation_error if Prolog is unbound.

prolog_bool_to_json(Var, _) :-
    var(Var),
    instantiation_error(Var).
prolog_bool_to_json(true, @(true)).
prolog_bool_to_json(false, @(false)).
prolog_bool_to_json(fail, @(false)).
prolog_bool_to_json(0, @(false)).
prolog_bool_to_json(on, @(true)).
prolog_bool_to_json(off, @(false)).
prolog_bool_to_json(1, @(false)).
prolog_bool_to_json(@(True), True) :-
    prolog_bool_to_json(True, True).


%!  type_goal(+Type, +Var, -BodyTerm) is det.
%
%   Inline type checking calls.

type_goal(Type, Var, Body) :-
    current_type(Type, Var, Body0),
    primitive(Body0, Body),
    !.
type_goal(Type, Var, is_of_type(Type, Var)).

primitive((A0,B0), (A,B)) :-
    !,
    primitive(A0, A),
    primitive(B0, B).
primitive((A0;B0), (A,B)) :-
    !,
    primitive(A0, A),
    primitive(B0, B).
primitive((A0->B0), (A,B)) :-
    !,
    primitive(A0, A),
    primitive(B0, B).
primitive(_:G, G) :-
    !,
    predicate_property(system:G, built_in).
primitive(G, G) :-
    predicate_property(system:G, built_in).

non_json_type(Type) :-
    current_type(Type, _, _),
    !.


%!  clean_body(+BodyIn, -BodyOut) is det.
%
%   Cleanup a body goal. Eliminate   redundant =true= statements and
%   perform partial evaluation on some  commonly constructs that are
%   generated from the has_type/2 clauses in library(error).

clean_body(Var, Var) :-
    var(Var),
    !.
clean_body((A0,B0), G) :-
    !,
    clean_body(A0, A),
    clean_body(B0, B),
    conj(A, B, G).
clean_body(ground(X), true) :-          % Generated from checking extra fields.
    ground(X),
    !.
clean_body(memberchk(V, Values), true) :- % generated from oneof(List)
    ground(V), ground(Values),
    memberchk(V, Values),
    !.
clean_body((integer(Low) -> If ; Then), Goal) :- % generated from between(Low,High)
    number(Low),
    !,
    (   integer(Low)
    ->  Goal = If
    ;   Goal = Then
    ).
clean_body((A->true;fail), A) :- !.     % nullable fields.
clean_body((fail->_;A), A) :- !.
clean_body(A, A).

conj(T, A, A) :- T == true, !.
conj(A, T, A) :- T == true, !.
conj(A, B, (A,B)).

make_pairs([], [], L, L).
make_pairs([N|TN], [V|TV], [N=V|T], Tail) :-
    make_pairs(TN, TV, T, Tail).

%!  current_clause(+Constructor, +Module, +Types, +Defs, +Names, +Extra)
%
%   Create the clause current_json_object/3.

current_clause(Constructor, Module, Types, Defs, Names, Extra) -->
    { length(Types, Arity),
      functor(Term, Constructor, Arity),
      extra_fields(Extra, EF),
      Term =.. [_|Vars],
      mk_fields(Names, Types, Defs, Vars, Fields0, EF),
      sort(Fields0, Fields),
      Head =.. [current_json_object, Term, Module, Fields]
    },
    [ json_convert:Head ].

extra_fields([], []).
extra_fields([Name=Value|T0], [f(Name, oneof([Value]), _, Value)|T]) :-
    extra_fields(T0, T).

mk_fields([], [], [], [], Fields, Fields).
mk_fields([Name|TN], [Type|TT], [Def|DT], [Var|VT],
          [f(Name, Type, Def, Var)|T], Tail) :-
    mk_fields(TN, TT, DT, VT, T, Tail).


/* The code below is copied from library(record) */

%!  defaults(+ArgsSpecs, -Defaults, -Args)
%
%   Strip the default specification from the argument specification.

defaults([], [], []).
defaults([Arg=Default|T0], [Default|TD], [Arg|TA]) :-
    !,
    defaults(T0, TD, TA).
defaults([Arg|T0], [NoDefault|TD], [Arg|TA]) :-
    no_default(NoDefault),
    defaults(T0, TD, TA).

no_default('$no-default$').

%!  types(+ArgsSpecs, -Defaults, -Args)
%
%   Strip the default specification from the argument specification.

types([], [], []).
types([Name:Type|T0], [Name|TN], [Type|TT]) :-
    !,
    must_be(atom, Name),
    types(T0, TN, TT).
types([Name|T0], [Name|TN], [any|TT]) :-
    must_be(atom, Name),
    types(T0, TN, TT).


                 /*******************************
                 *       PROLOG --> JSON        *
                 *******************************/

%!  prolog_to_json(:Term, -JSONObject) is det.
%
%   Translate a Prolog application Term  into   a  JSON object term.
%   This transformation is based on   :- json_object/1 declarations.
%   If  a  json_object/1  declaration  declares   a  field  of  type
%   =boolean=, commonly used thruth-values in   Prolog are converted
%   to JSON booleans. Boolean  translation   accepts  one of =true=,
%   =on=, =1=, @true, =false=, =fail=, =off= or =0=, @false.
%
%   @error  type_error(json_term, X)
%   @error  instantiation_error

prolog_to_json(Module:Term, JSON) :-
    prolog_to_json(Term, JSON, Module).

prolog_to_json(Var, _, _) :-
    var(Var),
    !,
    instantiation_error(Var).
prolog_to_json(Atomic, Atomic, _) :-
    atomic(Atomic),
    !.
prolog_to_json(List, JSON, Module) :-
    is_list(List),
    !,
    prolog_list_to_json(List, JSON, Module).
prolog_to_json(Record, JSON, Module) :-
    record_to_pairs(Record, JSON, Module),
    !.
prolog_to_json(Term, Term, _) :-
    is_json_term(Term),
    !.
prolog_to_json(Term, _, _) :-
    type_error(json_term, Term).

record_to_pairs(T, _, _) :-
    var(T),
    !,
    instantiation_error(T).
record_to_pairs(T, JSON, M) :-
    object_module(M, Module),
    json_object_to_pairs(T, Module, JSON),
    !.

object_module(user, user) :- !.
object_module(M, M).
object_module(_, user).

prolog_list_to_json([], [], _).
prolog_list_to_json([H0|T0], [H|T], M) :-
    prolog_to_json(H0, H, M),
    prolog_list_to_json(T0, T, M).


                 /*******************************
                 *       JSON --> PROLOG        *
                 *******************************/

:- dynamic
    json_to_prolog_rule/3,          % Module, Pairs, Term
    created_rules_for_pairs/2.      % Module, Pairs

clear_cache :-
    retractall(json_to_prolog_rule(_,_,_)),
    retractall(created_rules_for_pairs(_,_)).

:- clear_cache.

%!  json_to_prolog(+JSON, -Term) is det.
%
%   Translate  a  JSON  term   into    an   application  term.  This
%   transformation is based on  :-   json_object/1  declarations. An
%   efficient transformation is non-trivial,  but   we  rely  on the
%   assumption that, although the order of   fields in JSON terms is
%   irrelevant and can therefore vary  a lot, practical applications
%   will normally generate the JSON objects in a consistent order.
%
%   If a field in a json_object is declared of type =boolean=, @true
%   and @false are  translated  to  =true=   or  =false=,  the  most
%   commonly used Prolog representation for truth-values.

json_to_prolog(JSON, Module:Term) :-
    json_to_prolog(JSON, Term, Module).

json_to_prolog(json(Pairs), Term, Module) :-
    !,
    (   pairs_to_term(Pairs, Term, Module)
    ->  true
    ;   json_pairs_to_prolog(Pairs, Prolog, Module),
        Term = json(Prolog)
    ).
json_to_prolog(List, Prolog, Module) :-
    is_list(List),
    !,
    json_list_to_prolog(List, Prolog, Module).
json_to_prolog(@(Special), @(Special), _) :- !.
json_to_prolog(Atomic, Atomic, _).

json_pairs_to_prolog([], [], _).
json_pairs_to_prolog([Name=JSONValue|T0], [Name=PrologValue|T], Module) :-
    json_to_prolog(JSONValue, PrologValue, Module),
    json_pairs_to_prolog(T0, T, Module).

json_list_to_prolog([], [], _).
json_list_to_prolog([JSONValue|T0], [PrologValue|T], Module) :-
    json_to_prolog(JSONValue, PrologValue, Module),
    json_list_to_prolog(T0, T, Module).


%!  pairs_to_term(+Pairs, ?Term, +Module) is semidet.
%
%   Convert a Name=Value set into a Prolog application term based on
%   json_object/1 declarations. If multiple rules   can  be created,
%   make the one with the highest arity the preferred one.
%
%   @tbd    Ignore extra pairs if term is partially given?

pairs_to_term(Pairs, Term, Module) :-
    object_module(Module, M),
    (   json_to_prolog_rule(M, Pairs, Term)
    ->  !
    ;   created_rules_for_pairs(M, Pairs)
    ->  !, fail
    ;   pairs_args(Pairs, PairArgs),
        sort(PairArgs, SortedPairArgs),
        findall(Q-Rule,
                ( create_rule(SortedPairArgs, Module, M, Term0, Body, Q),
                  Rule = (json_to_prolog_rule(M, PairArgs, Term0) :- Body)
                ),
                RulePairs),
        keysort(RulePairs, ByQuality),
        pairs_values(ByQuality, Rules),
        maplist(asserta, Rules),
        asserta(created_rules_for_pairs(M, PairArgs)),
        json_to_prolog_rule(M, Pairs, Term), !
    ).

pairs_args([], []).
pairs_args([Name=_Value|T0], [Name=_|T]) :-
    pairs_args(T0, T).

%!  create_rule(+PairArgs, +Module, -ObjectM, -Term, -Body,
%!              -Quality) is det.
%
%   Create a new rule for dealing with Pairs, a Name=Value list of a
%   particular order.  Here is an example rule:
%
%     ==
%     json_to_prolog_rule([x=X, y=Y], point(X,Y)) :-
%           integer(X),
%           integer(Y).
%     ==
%
%   @arg PairArgs is an ordered list of Name=Variable pairs
%   @arg Module is the module requesting the conversion
%   @arg ObjectM is the module where the object is defined
%   @arg Term is the converted term (with variable arguments)
%   @arg Body is a Prolog goal that validates the types and
%        converts arguments.
%   @arg Quality is a number that indicates the matching quality.
%        Larger values are better.  Max is 0.  There is a penalty
%        of 1 for applying a default value and a penalty of 2 for
%        ignoring a value in the JSON term.

create_rule(PairArgs, Module, M, Term, Body, Quality) :-
    current_json_object(Term, M, Fields),
    match_fields(PairArgs, Fields, Body0, Module, 0, Quality),
    clean_body(Body0, Body).

match_fields(Ignored, [], true, _, Q0, Q) :-
    !,
    length(Ignored, Len),
    Q is Q0-2*Len.
match_fields([Name=JSON|TP], [f(Name, Type, _, Prolog)|TF], (Goal,Body),
             M, Q0, Q) :-
    !,
    match_field(Type, JSON, Prolog, M, Goal),
    match_fields(TP, TF, Body, M, Q0, Q).
match_fields([Name=JSON|TP], [f(OptName, Type, Def, Prolog)|TF], Body,
             M, Q0, Q) :-
    OptName @< Name,
    !,
    (   nullable(Type)
    ->  true
    ;   no_default(NoDef),
        Def \== NoDef
    ->  Prolog = Def
    ),
    Q1 is Q0-1,
    match_fields([Name=JSON|TP], TF, Body, M, Q1, Q).
match_fields([], [f(_OptName, Type, Def, Prolog)|TF], Body,
             M, Q0, Q) :-
    !,
    (   nullable(Type)
    ->  true
    ;   no_default(NoDef),
        Def \== NoDef
    ->  Prolog = Def
    ),
    Q1 is Q0-1,
    match_fields([], TF, Body, M, Q1, Q).
match_fields([Name=_|TP], [F|TF], Body, M, Q0, Q) :-
    arg(1, F, Next),
    Name @< Next,
    Q1 is Q0-2,
    match_fields(TP, [F|TF], Body, M, Q1, Q).

nullable(null).
nullable((A|B)) :- ( nullable(A) -> true ; nullable(B) ).

match_field((A|B), JSON, Prolog, M, (BodyA->true;BodyB)) :-
    !,
    match_field(A, JSON, Prolog, M, BodyA),
    match_field(B, JSON, Prolog, M, BodyB).
match_field(null, _, _, _, fail) :- !.
match_field(any, JSON, Prolog, M, json_to_prolog(JSON,Prolog,M)) :- !.
match_field(F/A, JSON, Prolog, M, json_to_prolog(JSON,Prolog,M)) :-
    !,
    functor(Prolog, F, A).
match_field(boolean, JSON, Prolog, _, json_bool_to_prolog(JSON, Prolog)) :- !.
match_field(list(Type), JSON, Prolog, M, json_list_to_prolog(JSON, Prolog, M)) :-
    !,
    (   Type = _Funcor/_Arity
    ->  true
    ;   non_json_type(Type)
    ->  true
    ;   current_json_object(Term, M, _Fields),
        functor(Term, Type, _)
    ).
match_field(list, JSON, Prolog, M, Goal) :-
    !,
    match_field(list(any), JSON, Prolog, M, Goal).
match_field(Type, Var, Var, _, Goal) :-
    type_goal(Type, Var, Goal).

:- public json_bool_to_prolog/2.

json_bool_to_prolog(@(True), True).


                 /*******************************
                 *            EXPANSION         *
                 *******************************/

:- multifile
    system:term_expansion/2.
:- dynamic
    system:term_expansion/2.

system:term_expansion((:- json_object(Spec)), Clauses) :-
    compile_json_objects(Spec, Clauses).
