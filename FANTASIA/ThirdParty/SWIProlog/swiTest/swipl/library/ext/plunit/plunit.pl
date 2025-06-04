/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2006-2024, University of Amsterdam
			      VU University Amsterdam
			      CWI, Amsterdam
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

:- module(plunit,
	  [ set_test_options/1,         % +Options
	    begin_tests/1,              % +Name
	    begin_tests/2,              % +Name, +Options
	    end_tests/1,                % +Name
	    run_tests/0,                % Run all tests
	    run_tests/1,                % +Tests
	    run_tests/2,                % +Tests, +Options
	    load_test_files/1,          % +Options
	    running_tests/0,            % Prints currently running test
	    current_test/5,             % ?Unit,?Test,?Line,?Body,?Options
	    current_test_unit/2,        % ?Unit,?Options
	    test_report/1               % +What
	  ]).

/** <module> Unit Testing

Unit testing environment for SWI-Prolog and   SICStus Prolog. For usage,
please visit https://www.swi-prolog.org/pldoc/package/plunit.
*/

:- autoload(library(statistics), [call_time/2]).
:- autoload(library(apply),
            [maplist/3, include/3, maplist/2, foldl/4, partition/4]).
:- autoload(library(lists), [member/2, append/2, flatten/2, append/3]).
:- autoload(library(option), [ option/3, option/2, select_option/3 ]).
:- autoload(library(ordsets), [ord_intersection/3]).
:- autoload(library(error), [must_be/2, domain_error/2]).
:- autoload(library(aggregate), [aggregate_all/3]).
:- autoload(library(streams), [with_output_to/3]).
:- autoload(library(ansi_term), [ansi_format/3]).
:- if(exists_source(library(time))).
:- autoload(library(time), [call_with_time_limit/2]).
:- endif.

:- public
    unit_module/2.

:- meta_predicate
    valid_options(1, +),
    count(0, -).

		 /*******************************
		 *    CONDITIONAL COMPILATION   *
		 *******************************/

swi     :- catch(current_prolog_flag(dialect, swi),     _, fail).
sicstus :- catch(current_prolog_flag(dialect, sicstus), _, fail).

throw_error(Error_term,Impldef) :-
    throw(error(Error_term,context(Impldef,_))).

:- set_prolog_flag(generate_debug_info, false).
current_test_flag(optimise, Value) =>
    current_prolog_flag(optimise, Value).
current_test_flag(occurs_check, Value) =>
    (   current_prolog_flag(plunit_occurs_check, Value0)
    ->  Value = Value0
    ;   current_prolog_flag(occurs_check, Value)
    ).
current_test_flag(Name, Value), atom(Name) =>
    atom_concat(plunit_, Name, Flag),
    current_prolog_flag(Flag, Value).
current_test_flag(Name, Value), var(Name) =>
    global_test_option(Opt, _, _Type, _Default),
    functor(Opt, Name, 1),
    current_test_flag(Name, Value).

set_test_flag(Name, Value) :-
    Opt =.. [Name, Value],
    global_test_option(Opt),
    !,
    atom_concat(plunit_, Name, Flag),
    set_prolog_flag(Flag, Value).
set_test_flag(Name, _) :-
    domain_error(test_flag, Name).

current_test_flags(Flags) :-
    findall(Flag, current_test_flag(Flag), Flags).

current_test_flag(Opt) :-
    current_test_flag(Name, Value),
    Opt =.. [Name, Value].

% ensure expansion to avoid tracing
goal_expansion(forall(C,A),
	       \+ (C, \+ A)).
goal_expansion(current_module(Module,File),
	       module_property(Module, file(File))).


		 /*******************************
		 *            IMPORTS           *
		 *******************************/

:- initialization init_flags.

init_flags :-
    (   global_test_option(Option, _Value, Type, Default),
	Default \== (-),
	Option =.. [Name,_],
	atom_concat(plunit_, Name, Flag),
        flag_type(Type, FlagType),
	create_prolog_flag(Flag, Default, [type(FlagType), keep(true)]),
	fail
    ;   true
    ).

flag_type(boolean, FlagType) => FlagType = boolean.
flag_type(Type, FlagType), Type = oneof(Atoms), maplist(atom, Atoms) =>
    FlagType = Type.
flag_type(oneof(_), FlagType) => FlagType = term.
flag_type(positive_integer, FlagType) => FlagType = integer.
flag_type(number, FlagType) => FlagType = float.



%!  set_test_options(+Options)
%
%   Specifies how to deal with test suites.  Defined options are:
%
%    - load(+Load)
%      Whether or not the tests must be loaded.  Values are
%      `never`, `always`, `normal` (only if not optimised)
%
%    - run(+When)
%      When the tests are run.  Values are `manual`, `make`
%      or make(all).
%
%    - format(+Mode)
%      Currently one of `tty` or `log`.   `tty` uses terminal
%      control to overwrite successful tests, allowing the
%      user to see the currently running tests and output
%      from failed tests.  This is the default of the output
%      is a tty.  `log` prints a full log of the executed
%      tests and their result and is intended for non-interactive
%      usage.
%
%    - output(+When)
%      If `always`, emit all output as it is produced, if `never`,
%      suppress all output and if `on_failure`, emit the output
%      if the test fails.
%
%    - show_blocked(+Bool)
%      Show individual blocked tests during the report.
%
%    - occurs_check(+Mode)
%      Defines the default for the `occurs_check` flag during
%      testing.
%
%    - cleanup(+Bool)
%      If `true` (default =false), cleanup report at the end
%      of run_tests/1.  Used to improve cooperation with
%      memory debuggers such as dmalloc.
%
%    - jobs(Num)
%      Number of jobs to use for concurrent testing.  Default
%      is one, implying sequential testing.
%
%    - timeout(+Seconds)
%      Set timeout for each individual test.  This acts as a
%      default that may be overuled at the level of units or
%      individual tests.   A timeout of 0 or negative is handled
%      as _inifinite_.

set_test_options(Options) :-
    flatten([Options], List),
    maplist(set_test_option, List).

set_test_option(sto(true)) =>
    print_message(warning, plunit(sto(true))).
set_test_option(jobs(Jobs)) =>
    must_be(positive_integer, Jobs),
    set_test_option_flag(jobs(Jobs)).
set_test_option(Option),
  compound(Option), global_test_option(Option) =>
    set_test_option_flag(Option).
set_test_option(Option) =>
    domain_error(option, Option).

global_test_option(Opt) :-
    global_test_option(Opt, Value, Type, _Default),
    must_be(Type, Value).

global_test_option(load(Load), Load, oneof([never,always,normal]), normal).
global_test_option(output(Cond), Cond, oneof([always,on_failure]), on_failure).
global_test_option(format(Feedback), Feedback, oneof([tty,log]), tty).
global_test_option(silent(Silent), Silent, boolean, false).
global_test_option(show_blocked(Blocked), Blocked, boolean, false).
global_test_option(run(When), When, oneof([manual,make,make(all)]), make).
global_test_option(occurs_check(Mode), Mode, oneof([false,true,error]), -).
global_test_option(cleanup(Bool), Bool, boolean, true).
global_test_option(jobs(Count), Count, positive_integer, 1).
global_test_option(timeout(Number), Number, number, 3600).

set_test_option_flag(Option) :-
    Option =.. [Name, Value],
    set_test_flag(Name, Value).

%!  loading_tests
%
%   True if tests must be loaded.

loading_tests :-
    current_test_flag(load, Load),
    (   Load == always
    ->  true
    ;   Load == normal,
	\+ current_test_flag(optimise, true)
    ).

		 /*******************************
		 *            MODULE            *
		 *******************************/

:- dynamic
    loading_unit/4,                 % Unit, Module, File, OldSource
    current_unit/4,                 % Unit, Module, Context, Options
    test_file_for/2.                % ?TestFile, ?PrologFile

%!  begin_tests(+UnitName:atom) is det.
%!  begin_tests(+UnitName:atom, Options) is det.
%
%   Start a test-unit. UnitName is the  name   of  the test set. the
%   unit is ended by :- end_tests(UnitName).

begin_tests(Unit) :-
    begin_tests(Unit, []).

begin_tests(Unit, Options) :-
    must_be(atom, Unit),
    map_sto_option(Options, Options1),
    valid_options(test_set_option, Options1),
    make_unit_module(Unit, Name),
    source_location(File, Line),
    begin_tests(Unit, Name, File:Line, Options1).

map_sto_option(Options0, Options) :-
    select_option(sto(Mode), Options0, Options1),
    !,
    map_sto(Mode, Flag),
    Options = [occurs_check(Flag)|Options1].
map_sto_option(Options, Options).

map_sto(rational_trees, Flag) => Flag = false.
map_sto(finite_trees, Flag)   => Flag = true.
map_sto(Mode, _) => domain_error(sto, Mode).


:- if(swi).
begin_tests(Unit, Name, File:Line, Options) :-
    loading_tests,
    !,
    '$set_source_module'(Context, Context),
    (   current_unit(Unit, Name, Context, Options)
    ->  true
    ;   retractall(current_unit(Unit, Name, _, _)),
	assert(current_unit(Unit, Name, Context, Options))
    ),
    '$set_source_module'(Old, Name),
    '$declare_module'(Name, test, Context, File, Line, false),
    discontiguous(Name:'unit test'/4),
    '$set_predicate_attribute'(Name:'unit test'/4, trace, false),
    discontiguous(Name:'unit body'/2),
    asserta(loading_unit(Unit, Name, File, Old)).
begin_tests(Unit, Name, File:_Line, _Options) :-
    '$set_source_module'(Old, Old),
    asserta(loading_unit(Unit, Name, File, Old)).

:- else.

% we cannot use discontiguous as a goal in SICStus Prolog.

user:term_expansion((:- begin_tests(Set)),
		    [ (:- begin_tests(Set)),
		      (:- discontiguous(test/2)),
		      (:- discontiguous('unit body'/2)),
		      (:- discontiguous('unit test'/4))
		    ]).

begin_tests(Unit, Name, File:_Line, Options) :-
    loading_tests,
    !,
    (   current_unit(Unit, Name, _, Options)
    ->  true
    ;   retractall(current_unit(Unit, Name, _, _)),
	assert(current_unit(Unit, Name, -, Options))
    ),
    asserta(loading_unit(Unit, Name, File, -)).
begin_tests(Unit, Name, File:_Line, _Options) :-
    asserta(loading_unit(Unit, Name, File, -)).

:- endif.

%!  end_tests(+Name) is det.
%
%   Close a unit-test module.
%
%   @tbd    Run tests/clean module?
%   @tbd    End of file?

end_tests(Unit) :-
    loading_unit(StartUnit, _, _, _),
    !,
    (   Unit == StartUnit
    ->  once(retract(loading_unit(StartUnit, _, _, Old))),
	'$set_source_module'(_, Old)
    ;   throw_error(context_error(plunit_close(Unit, StartUnit)), _)
    ).
end_tests(Unit) :-
    throw_error(context_error(plunit_close(Unit, -)), _).

%!  make_unit_module(+Name, -ModuleName) is det.
%!  unit_module(+Name, -ModuleName) is det.

:- if(swi).

unit_module(Unit, Module) :-
    atom_concat('plunit_', Unit, Module).

make_unit_module(Unit, Module) :-
    unit_module(Unit, Module),
    (   current_module(Module),
	\+ current_unit(_, Module, _, _),
	predicate_property(Module:H, _P),
	\+ predicate_property(Module:H, imported_from(_M))
    ->  throw_error(permission_error(create, plunit, Unit),
		    'Existing module')
    ;  true
    ).

:- else.

:- dynamic
    unit_module_store/2.

unit_module(Unit, Module) :-
    unit_module_store(Unit, Module),
    !.

make_unit_module(Unit, Module) :-
    prolog_load_context(module, Module),
    assert(unit_module_store(Unit, Module)).

:- endif.

		 /*******************************
		 *           EXPANSION          *
		 *******************************/

%!  expand_test(+Name, +Options, +Body, -Clause) is det.
%
%   Expand test(Name, Options) :-  Body  into   a  clause  for
%   'unit test'/4 and 'unit body'/2.

expand_test(Name, Options0, Body,
	    [ 'unit test'(Name, Line, Options, Module:'unit body'(Id, Vars)),
	      ('unit body'(Id, Vars) :- !, Body)
	    ]) :-
    source_location(_File, Line),
    prolog_load_context(module, Module),
    (   prolog_load_context(variable_names, Bindings)
    ->  true
    ;   Bindings = []
    ),
    atomic_list_concat([Name, '@line ', Line], Id),
    term_variables(Options0, OptionVars0), sort(OptionVars0, OptionVars),
    term_variables(Body, BodyVars0), sort(BodyVars0, BodyVars),
    ord_intersection(OptionVars, BodyVars, VarList),
    Vars =.. [vars|VarList],
    (   is_list(Options0)           % allow for single option without list
    ->  Options1 = Options0
    ;   Options1 = [Options0]
    ),
    maplist(expand_option(Bindings), Options1, Options2),
    join_true_options(Options2, Options3),
    map_sto_option(Options3, Options4),
    valid_options(test_option, Options4),
    valid_test_mode(Options4, Options).

expand_option(_, Var, _) :-
    var(Var),
    !,
    throw_error(instantiation_error,_).
expand_option(Bindings, Cmp, true(Cond)) :-
    cmp(Cmp),
    !,
    var_cmp(Bindings, Cmp, Cond).
expand_option(_, error(X), throws(error(X, _))) :- !.
expand_option(_, exception(X), throws(X)) :- !. % SICStus 4 compatibility
expand_option(_, error(F,C), throws(error(F,C))) :- !. % SICStus 4 compatibility
expand_option(_, true, true(true)) :- !.
expand_option(_, O, O).

cmp(_ == _).
cmp(_ = _).
cmp(_ =@= _).
cmp(_ =:= _).

var_cmp(Bindings, Expr, cmp(Name, Expr)) :-
    arg(_, Expr, Var),
    var(Var),
    member(Name=V, Bindings),
    V == Var,
    !.
var_cmp(_, Expr, Expr).

join_true_options(Options0, Options) :-
    partition(true_option, Options0, True, Rest),
    True \== [],
    !,
    maplist(arg(1), True, Conds0),
    flatten(Conds0, Conds),
    Options = [true(Conds)|Rest].
join_true_options(Options, Options).

true_option(true(_)).

valid_test_mode(Options0, Options) :-
    include(test_mode, Options0, Tests),
    (   Tests == []
    ->  Options = [true([true])|Options0]
    ;   Tests = [_]
    ->  Options = Options0
    ;   throw_error(plunit(incompatible_options, Tests), _)
    ).

test_mode(true(_)).
test_mode(all(_)).
test_mode(set(_)).
test_mode(fail).
test_mode(throws(_)).


%!  expand(+Term, -Clauses) is semidet.

expand(end_of_file, _) :-
    loading_unit(Unit, _, _, _),
    !,
    end_tests(Unit),                % warn?
    fail.
expand((:-end_tests(_)), _) :-
    !,
    fail.
expand(_Term, []) :-
    \+ loading_tests.
expand((test(Name) :- Body), Clauses) :-
    !,
    expand_test(Name, [], Body, Clauses).
expand((test(Name, Options) :- Body), Clauses) :-
    !,
    expand_test(Name, Options, Body, Clauses).
expand(test(Name), _) :-
    !,
    throw_error(existence_error(body, test(Name)), _).
expand(test(Name, _Options), _) :-
    !,
    throw_error(existence_error(body, test(Name)), _).

:- multifile
    system:term_expansion/2.

system:term_expansion(Term, Expanded) :-
    (   loading_unit(_, _, File, _)
    ->  source_location(ThisFile, _),
	(   File == ThisFile
	->  true
	;   source_file_property(ThisFile, included_in(File, _))
	),
	expand(Term, Expanded)
    ).


		 /*******************************
		 *             OPTIONS          *
		 *******************************/

%!  valid_options(:Pred, +Options) is det.
%
%   Verify Options to be a list of valid options according to
%   Pred.
%
%   @error `type_error` or `instantiation_error`.

valid_options(Pred, Options) :-
    must_be(list, Options),
    verify_options(Options, Pred).

verify_options([], _).
verify_options([H|T], Pred) :-
    (   call(Pred, H)
    ->  verify_options(T, Pred)
    ;   throw_error(domain_error(Pred, H), _)
    ).

valid_options(Pred, Options0, Options, Rest) :-
    must_be(list, Options0),
    partition(Pred, Options0, Options, Rest).

%!  test_option(+Option) is semidet.
%
%   True if Option is a valid option for test(Name, Options).

test_option(Option) :-
    test_set_option(Option),
    !.
test_option(true(_)).
test_option(fail).
test_option(throws(_)).
test_option(all(_)).
test_option(set(_)).
test_option(nondet).
test_option(fixme(_)).
test_option(forall(X)) :-
    must_be(callable, X).
test_option(timeout(Seconds)) :-
    must_be(number, Seconds).

%!  test_option(+Option) is semidet.
%
%   True if Option is a valid option for :- begin_tests(Name,
%   Options).

test_set_option(blocked(X)) :-
    must_be(ground, X).
test_set_option(condition(X)) :-
    must_be(callable, X).
test_set_option(setup(X)) :-
    must_be(callable, X).
test_set_option(cleanup(X)) :-
    must_be(callable, X).
test_set_option(occurs_check(V)) :-
    must_be(oneof([false,true,error]), V).
test_set_option(concurrent(V)) :-
    must_be(boolean, V),
    print_message(informational, plunit(concurrent)).
test_set_option(timeout(Seconds)) :-
    must_be(number, Seconds).

		 /*******************************
		 *             UTIL		*
		 *******************************/

:- meta_predicate
       reify_tmo(0, -, +),
       reify(0, -),
       capture_output(0,-),
       capture_output(0,-,+),
       got_messages(0,-).

%!  reify_tmo(:Goal, -Result, +Options) is det.

:- if(current_predicate(call_with_time_limit/2)).
reify_tmo(Goal, Result, Options) :-
    option(timeout(Time), Options),
    Time > 0,
    !,
    reify(call_with_time_limit(Time, Goal), Result0),
    (   Result0 = throw(time_limit_exceeded)
    ->  Result = throw(time_limit_exceeded(Time))
    ;   Result = Result0
    ).
:- endif.
reify_tmo(Goal, Result, _Options) :-
    reify(Goal, Result).

%!  reify(:Goal, -Result) is det.
%
%   Call  Goal  and  unify  Result  with   one  of  `true`,  `false`  or
%   `throw(E)`.

reify(Goal, Result) :-
    (   catch(Goal, E, true)
    ->  (   var(E)
	->  Result = true
	;   Result = throw(E)
	)
    ;   Result = false
    ).

%!  capture_output(:Goal, -Output) is semidet.
%!  capture_output(:Goal, -Output, +Options) is semidet.
%
%   @arg Output is a pair `Msgs-String`, where  `Msgs` is a boolean that
%   is true if there were messages that   require a non-zero exit status
%   and Output contains the output as a string.

capture_output(Goal, Output) :-
    current_test_flag(output, OutputMode),
    capture_output(Goal, Output, [output(OutputMode)]).

capture_output(Goal, Msgs-Output, Options) :-
    option(output(How), Options, always),
    (   How == always
    ->  call(Goal),
        Msgs = false                % irrelavant
    ;   with_output_to(string(Output), got_messages(Goal, Msgs),
                       [ capture([user_output, user_error]),
                         color(true)
                       ])
    ).

%!  got_messages(:Goal, -Result)

got_messages(Goal, Result) :-
    (   current_prolog_flag(on_warning, status)
    ;   current_prolog_flag(on_error, status)
    ), !,
    nb_delete(plunit_got_message),
    setup_call_cleanup(
        asserta(( user:thread_message_hook(_Term, Kind, _Lines) :-
                      got_message(Kind), fail), Ref),
        Goal,
        erase(Ref)),
    (   nb_current(plunit_got_message, true)
    ->  Result = true
    ;   Result = false
    ).
got_messages(Goal, false) :-
    call(Goal).

:- public got_message/1.
got_message(warning) :-
    current_prolog_flag(on_warning, status), !,
    nb_setval(plunit_got_message, true).
got_message(error) :-
    current_prolog_flag(on_error, status), !,
    nb_setval(plunit_got_message, true).


		 /*******************************
		 *        RUNNING TOPLEVEL      *
		 *******************************/

:- dynamic
    output_streams/2,               % Output, Error
    test_count/1,                   % Count
    passed/5,                       % Unit, Test, Line, Det, Time
    failed/5,                       % Unit, Test, Line, Reason, Time
    timeout/5,                      % Unit, Test, Line, Limit, Time
    failed_assertion/7,             % Unit, Test, Line, ALoc, STO, Reason, Goal
    blocked/4,                      % Unit, Test, Line, Reason
    fixme/5,                        % Unit, Test, Line, Reason, Status
    running/5,                      % Unit, Test, Line, STO, Thread
    forall_failures/2.              % Nth, Failures

%!  run_tests is semidet.
%!  run_tests(+TestSet) is semidet.
%!  run_tests(+TestSet, +Options) is semidet.
%
%   Run tests and report about the   results.  The predicate run_tests/0
%   runs all known tests that are not blocked. The predicate run_tests/1
%   takes a specification of tests  to  run.
%
%   The predicate run_tests/2 is  synchronized. Concurrent testing may
%   be     achieved    using     the     relevant    options.      See
%   set_test_options/1. Options are  passed to set_test_options/1.  In
%   addition the following options are processed:
%
%     - summary(-Summary)
%       Unify Summary do a dict holding the keys below.  The value of
%       these keys is an integer describing the number of tests.  If
%       this option is given, run_tests/2 does not fail if some tests
%       failed.
%
%       - total
%       - passed
%       - failed
%       - timeout
%       - blocked
%
%   @arg  TestSet  is either  a  single  specification  or a  list  of
%   specifications. Each single specification is  either the name of a
%   test-unit  or a  term <test-unit>:<test>,  denoting a  single test
%   within a unit.  If TestSet is `all`, all known tests are executed.

run_tests :-
    run_tests(all).

run_tests(Set) :-
    run_tests(Set, []).

run_tests(all, Options) :-
    !,
    findall(Unit, current_test_unit(Unit,_), Units),
    run_tests(Units, Options).
run_tests(Set, Options) :-
    valid_options(global_test_option, Options, Global, Rest),
    current_test_flags(Old),
    setup_call_cleanup(
	set_test_options(Global),
	( flatten([Set], List),
	  maplist(runnable_tests, List, Units),
	  with_mutex(plunit, run_tests_sync(Units, Rest))
	),
	set_test_options(Old)).

run_tests_sync(Units0, Options) :-
    cleanup,
    count_tests(Units0, Units, Count),
    asserta(test_count(Count)),
    save_output_state,
    setup_call_cleanup(
        setup_trap_assertions(Ref),
        call_time(setup_jobs_and_run_units(Count, Units, Summary, Options),
                  Time),
        report_and_cleanup(Ref, Time, Options)),
    (   option(summary(Summary), Options)
    ->  true
    ;   test_summary_passed(Summary) % fail if some test failed
    ).

setup_jobs_and_run_units(Count, Units, Summary, Options) :-
    setup_call_cleanup(
        setup_jobs(Count),
        ( run_units(Units, Options),
          test_summary(_All, Summary)
        ),
        cleanup_jobs).

%!  report_and_cleanup(+Ref, +Time, +Options)
%
%   Undo changes to the environment   (trapping  assertions), report the
%   results and cleanup.

report_and_cleanup(Ref, Time, Options) :-
    cleanup_trap_assertions(Ref),
    report(Time, Options),
    cleanup_after_test.


%!  run_units_and_check_errors(+Units, +Options) is semidet.
%
%   Run all test units and succeed if all tests passed.

run_units(Units, _Options) :-
    maplist(schedule_unit, Units),
    job_wait(_).

%!  runnable_tests(+Spec, -Plan) is det.
%
%   Change a Unit+Test spec  into  a   plain  `Unit:Tests`  lists, where
%   blocked tests or tests whose condition   fails  are already removed.
%   Each test in `Tests` is a  term   `@(Test,Line)`,  which serves as a
%   unique identifier of the test.

:- det(runnable_tests/2).
runnable_tests(Spec, Unit:RunnableTests) :-
    unit_from_spec(Spec, Unit, Tests, Module, UnitOptions),
    (   option(blocked(Reason), UnitOptions)
    ->  info(plunit(blocked(unit(Unit, Reason)))),
        RunnableTests = []
    ;   \+ condition(Module, unit(Unit), UnitOptions)
    ->  RunnableTests = []
    ;   var(Tests)
    ->  findall(TestID,
                runnable_test(Unit, _Test, Module, TestID),
                RunnableTests)
    ;   flatten([Tests], TestList),
        findall(TestID,
                ( member(Test, TestList),
                  runnable_test(Unit,Test,Module, TestID)
                ),
                RunnableTests)
    ).

runnable_test(Unit, Name, Module, @(Test,Line)) :-
    current_test(Unit, Name, Line, _Body, TestOptions),
    (   option(blocked(Reason), TestOptions)
    ->  Test = blocked(Name, Reason)
    ;   condition(Module, test(Unit,Name,Line), TestOptions),
        Test = Name
    ).

unit_from_spec(Unit0:Tests0, Unit, Tests, Module, Options), atom(Unit0) =>
    Unit = Unit0,
    Tests = Tests0,
    (   current_unit(Unit, Module, _Supers, Options)
    ->  true
    ;   throw_error(existence_error(unit_test, Unit), _)
    ).
unit_from_spec(Unit0, Unit, _, Module, Options), atom(Unit0) =>
    Unit = Unit0,
    (   current_unit(Unit, Module, _Supers, Options)
    ->  true
    ;   throw_error(existence_error(unit_test, Unit), _)
    ).

%!  count_tests(+Units0, -Units, -Count) is det.
%
%   Count the number of tests to   run. A forall(Generator, Test) counts
%   as a single test. During the execution,   the  concrete tests of the
%   _forall_ are considered "sub tests".

count_tests(Units0, Units, Count) :-
    count_tests(Units0, Units, 0, Count).

count_tests([], T, C0, C) =>
    T = [],
    C = C0.
count_tests([_:[]|T0], T, C0, C) =>
    count_tests(T0, T, C0, C).
count_tests([Unit:Tests|T0], T, C0, C) =>
    partition(is_blocked, Tests, Blocked, Use),
    maplist(assert_blocked(Unit), Blocked),
    (   Use == []
    ->  count_tests(T0, T, C0, C)
    ;   length(Use, N),
        C1 is C0+N,
        T = [Unit:Use|T1],
        count_tests(T0, T1, C1, C)
    ).

is_blocked(@(blocked(_,_),_)) => true.
is_blocked(_) => fail.

assert_blocked(Unit, @(blocked(Test, Reason), Line)) =>
    assert(blocked(Unit, Test, Line, Reason)).

%!  run_unit(+Unit) is det.
%
%   Run a single test unit. Unit is a  term Unit:Tests, where Tests is a
%   list of tests to run.

run_unit(_Unit:[]) =>
    true.
run_unit(Unit:Tests) =>
    unit_module(Unit, Module),
    unit_options(Unit, UnitOptions),
    (   setup(Module, unit(Unit), UnitOptions)
    ->  begin_unit(Unit),
        call_time(run_unit_2(Unit, Tests), Time),
        test_summary(Unit, Summary),
	end_unit(Unit, Summary.put(time, Time)),
        cleanup(Module, UnitOptions)
    ;   job_info(end(unit(Unit, _{error:setup_failed})))
    ).

begin_unit(Unit) :-
    job_info(begin(unit(Unit))),
    job_feedback(informational, begin(Unit)).

end_unit(Unit, Summary) :-
    job_info(end(unit(Unit, Summary))),
    job_feedback(informational, end(Unit, Summary)).

run_unit_2(Unit, Tests) :-
    forall(member(Test, Tests),
	   run_test(Unit, Test)).


unit_options(Unit, Options) :-
    current_unit(Unit, _Module, _Supers, Options).


cleanup :-
    set_flag(plunit_test, 1),
    retractall(output_streams(_,_)),
    retractall(test_count(_)),
    retractall(passed(_, _, _, _, _)),
    retractall(failed(_, _, _, _, _)),
    retractall(timeout(_, _, _, _, _)),
    retractall(failed_assertion(_, _, _, _, _, _, _)),
    retractall(blocked(_, _, _, _)),
    retractall(fixme(_, _, _, _, _)),
    retractall(running(_,_,_,_,_)),
    retractall(forall_failures(_,_)).

cleanup_after_test :-
    (   current_test_flag(cleanup, true)
    ->  cleanup
    ;   true
    ).


%!  run_tests_in_files(+Files:list) is det.
%
%   Run all test-units that appear in the given Files.

run_tests_in_files(Files) :-
    findall(Unit, unit_in_files(Files, Unit), Units),
    (   Units == []
    ->  true
    ;   run_tests(Units)
    ).

unit_in_files(Files, Unit) :-
    is_list(Files),
    !,
    member(F, Files),
    absolute_file_name(F, Source,
		       [ file_type(prolog),
			 access(read),
			 file_errors(fail)
		       ]),
    unit_file(Unit, Source).


		 /*******************************
		 *         HOOKING MAKE/0       *
		 *******************************/

%!  make_run_tests(+Files)
%
%   Called indirectly from make/0 after Files have been reloaded.

make_run_tests(Files) :-
    current_test_flag(run, When),
    (   When == make
    ->  run_tests_in_files(Files)
    ;   When == make(all)
    ->  run_tests
    ;   true
    ).

		 /*******************************
		 *      ASSERTION HANDLING      *
		 *******************************/

:- if(swi).

:- dynamic prolog:assertion_failed/2.

setup_trap_assertions(Ref) :-
    asserta((prolog:assertion_failed(Reason, Goal) :-
		    test_assertion_failed(Reason, Goal)),
	    Ref).

cleanup_trap_assertions(Ref) :-
    erase(Ref).

test_assertion_failed(Reason, Goal) :-
    thread_self(Me),
    running(Unit, Test, Line, Progress, Me),
    (   catch(get_prolog_backtrace(10, Stack), _, fail),
	assertion_location(Stack, AssertLoc)
    ->  true
    ;   AssertLoc = unknown
    ),
    report_failed_assertion(Unit:Test, Line, AssertLoc,
			    Progress, Reason, Goal),
    assert_cyclic(failed_assertion(Unit, Test, Line, AssertLoc,
				   Progress, Reason, Goal)).

assertion_location(Stack, File:Line) :-
    append(_, [AssertFrame,CallerFrame|_], Stack),
    prolog_stack_frame_property(AssertFrame,
				predicate(prolog_debug:assertion/1)),
    !,
    prolog_stack_frame_property(CallerFrame, location(File:Line)).

report_failed_assertion(UnitTest, Line, AssertLoc,
			Progress, Reason, Goal) :-
    print_message(
	error,
	plunit(failed_assertion(UnitTest, Line, AssertLoc,
				Progress, Reason, Goal))).

:- else.

setup_trap_assertions(_).
cleanup_trap_assertions(_).

:- endif.


		 /*******************************
		 *         RUNNING A TEST       *
		 *******************************/

%!  run_test(+Unit, +Test) is det.
%
%   Run a single test.

run_test(Unit, @(Test,Line)) :-
    unit_module(Unit, Module),
    Module:'unit test'(Test, Line, TestOptions, Body),
    unit_options(Unit, UnitOptions),
    run_test(Unit, Test, Line, UnitOptions, TestOptions, Body).

%!  run_test(+Unit, +Name, +Line, +UnitOptions, +Options, +Body)
%
%   Deals with forall(Generator, Test)

run_test(Unit, Name, Line, UnitOptions, Options, Body) :-
    option(forall(Generator), Options),
    !,
    unit_module(Unit, Module),
    start_test(Unit, @(Name,Line), Nth),
    State = state(0),
    call_time(forall(Module:Generator,            % may become concurrent
                     (   incr_forall(State, I),
                         run_test_once6(Unit, Name,
                                        forall(Generator, Nth-I), Line,
                                        UnitOptions, Options, Body)
                     )),
                     Time),
    arg(1, State, Generated),
    progress(Unit:Name, Nth, forall(end, Nth, Generated), Time).
run_test(Unit, Name, Line, UnitOptions, Options, Body) :-
    start_test(Unit, @(Name,Line), Nth),
    run_test_once6(Unit, Name, Nth, Line, UnitOptions, Options, Body).

start_test(_Unit, _TestID, Nth) :-
    flag(plunit_test, Nth, Nth+1).

incr_forall(State, I) :-
    arg(1, State, I0),
    I is I0+1,
    nb_setarg(1, State, I).

%!  run_test_once6(+Unit, +Name, +Progress, +Line, +UnitOptions,
%!                 +Options, +Body)
%
%   Inherit the `timeout` and `occurs_check` option (Global -> Unit -> Test).

run_test_once6(Unit, Name, Progress, Line, UnitOptions, Options, Body) :-
    current_test_flag(timeout, DefTimeOut),
    current_test_flag(occurs_check, DefOccurs),
    inherit_option(timeout,      Options,  [UnitOptions], DefTimeOut, Options1),
    inherit_option(occurs_check, Options1, [UnitOptions], DefOccurs, Options2),
    run_test_once(Unit, Name, Progress, Line, Options2, Body).

inherit_option(Name, Options0, Chain, Default, Options) :-
    Term =.. [Name,_Value],
    (   option(Term, Options0)
    ->  Options = Options0
    ;   member(Opts, Chain),
        option(Term, Opts)
    ->  Options = [Term|Options0]
    ;   Default == (-)
    ->  Options = Options0
    ;   Opt =.. [Name,Default],
	Options = [Opt|Options0]
    ).

%!  run_test_once(+Unit, +Name, +Progress, +Line, +Options, +Body)
%
%   Deal with occurs_check, i.e., running the  test multiple times with different
%   unification settings wrt. the occurs check.

run_test_once(Unit, Name, Progress, Line, Options, Body) :-
    option(occurs_check(Occurs), Options),
    !,
    begin_test(Unit, Name, Line, Progress),
    current_prolog_flag(occurs_check, Old),
    setup_call_cleanup(
	set_prolog_flag(occurs_check, Occurs),
	capture_output(run_test_6(Unit, Name, Line, Options, Body, Result),
		       Output),
	set_prolog_flag(occurs_check, Old)),
    end_test(Unit, Name, Line, Progress),
    report_result(Result, Progress, Output, Options).
run_test_once(Unit, Name, Progress, Line, Options, Body) :-
    begin_test(Unit, Name, Line, Progress),
    capture_output(run_test_6(Unit, Name, Line, Options, Body, Result),
		   Output),
    end_test(Unit, Name, Line, Progress),
    report_result(Result, Progress, Output, Options).

%!  report_result(+Result, +Progress, +Output, +Options) is det.

:- det(report_result/4).
report_result(failure(Unit, Name, Line, How, Time),
	      Progress, Output, Options) =>
    failure(Unit, Name, Progress, Line, How, Time, Output, Options).
report_result(success(Unit, Name, Line, Determinism, Time),
	      Progress, Output, Options) =>
    success(Unit, Name, Progress, Line, Determinism, Time, Output, Options).
report_result(setup_failed(Unit, Name, Line, Time, Output, Result),
	      Progress, _Output, Options) =>
    failure(Unit, Name, Progress, Line,
            setup_failed(Result), Time, Output, Options).

%!  run_test_6(+Unit, +Name, +Line, +Options, :Body, -Result) is det.
%
%   6th step  of the  tests.  Deals  with tests  that must  be ignored
%   (blocked, conditions fails), setup and cleanup at the test level.
%   Result is one of:
%
%     - failure(Unit, Name, Line, How, Time)
%       How is one of:
%       - succeeded
%       - Exception
%       - time_limit_exceeded(Limit)
%       - cmp_error(Cmp, E)
%       - wrong_answer(Cmp)
%       - failed
%       - no_exception
%       - wrong_error(Expect, E)
%       - wrong_answer(Expected, Bindings)
%     - success(Unit, Name, Line, Determinism, Time)
%     - setup_failed(Unit, Name, Line)

run_test_6(Unit, Name, Line, Options, Body, Result) :-
    option(setup(Setup), Options),
    !,
    unit_module(Unit, Module),
    capture_output(call_time(reify(call_ex(Module, Setup), SetupResult),
                             Time),
                   Output),
    (   SetupResult == true
    ->  run_test_7(Unit, Name, Line, Options, Body, Result),
        cleanup(Module, Options)
    ;   Result = setup_failed(Unit, Name, Line, Time, Output, SetupResult)
    ).
run_test_6(Unit, Name, Line, Options, Body, Result) :-
    unit_module(Unit, Module),
    run_test_7(Unit, Name, Line, Options, Body, Result),
    cleanup(Module, Options).

%!  run_test_7(+Unit, +Name, +Line, +Options, :Body, -Result) is det.
%
%   This step  deals with the expected  outcome of the test.   It runs
%   the  actual test  and then  compares  the result  to the  outcome.
%   There are  two main categories:  dealing with a single  result and
%   all results.

run_test_7(Unit, Name, Line, Options, Body, Result) :-
    option(true(Cmp), Options),			   % expected success
    !,
    unit_module(Unit, Module),
    call_time(reify_tmo(call_det(Module:Body, Det), Result0, Options), Time),
    (   Result0 == true
    ->  cmp_true(Cmp, Module, CmpResult),
	(   CmpResult == []
	->  Result = success(Unit, Name, Line, Det, Time)
	;   Result = failure(Unit, Name, Line, CmpResult, Time)
	)
    ;   Result0 == false
    ->  Result = failure(Unit, Name, Line, failed, Time)
    ;   Result0 = throw(E2)
    ->  Result = failure(Unit, Name, Line, throw(E2), Time)
    ).
run_test_7(Unit, Name, Line, Options, Body, Result) :-
    option(fail, Options),                         % expected failure
    !,
    unit_module(Unit, Module),
    call_time(reify_tmo(Module:Body, Result0, Options), Time),
    (   Result0 == true
    ->  Result = failure(Unit, Name, Line, succeeded, Time)
    ;   Result0 == false
    ->  Result = success(Unit, Name, Line, true, Time)
    ;   Result0 = throw(E)
    ->  Result = failure(Unit, Name, Line, throw(E), Time)
    ).
run_test_7(Unit, Name, Line, Options, Body, Result) :-
    option(throws(Expect), Options),		   % Expected error
    !,
    unit_module(Unit, Module),
    call_time(reify_tmo(Module:Body, Result0, Options), Time),
    (   Result0 == true
    ->  Result = failure(Unit, Name, Line, no_exception, Time)
    ;   Result0 == false
    ->  Result = failure(Unit, Name, Line, failed, Time)
    ;   Result0 = throw(E)
    ->  (   match_error(Expect, E)
        ->  Result = success(Unit, Name, Line, true, Time)
        ;   Result = failure(Unit, Name, Line, wrong_error(Expect, E), Time)
        )
    ).
run_test_7(Unit, Name, Line, Options, Body, Result) :-
    option(all(Answer), Options),                  % all(Bindings)
    !,
    nondet_test(all(Answer), Unit, Name, Line, Options, Body, Result).
run_test_7(Unit, Name, Line, Options, Body, Result) :-
    option(set(Answer), Options),                  % set(Bindings)
    !,
    nondet_test(set(Answer), Unit, Name, Line, Options, Body, Result).

%!  non_det_test(+Expected, +Unit, +Name, +Line, +Options, +Body, -Result)
%
%   Run tests on non-deterministic predicates.

nondet_test(Expected, Unit, Name, Line, Options, Body, Result) :-
    unit_module(Unit, Module),
    result_vars(Expected, Vars),
    (   call_time(reify_tmo(findall(Vars, Module:Body, Bindings),
                            Result0, Options), Time)
    ->  (   Result0 == true
        ->  (   nondet_compare(Expected, Bindings, Unit, Name, Line)
            ->  Result = success(Unit, Name, Line, true, Time)
            ;   Result = failure(Unit, Name, Line,
				 [wrong_answer(Expected, Bindings)], Time)
            )
        ;   Result0 = throw(E)
        ->  Result = failure(Unit, Name, Line, throw(E), Time)
        )
    ).

cmp_true([], _, L) =>
    L = [].
cmp_true([Cmp|T], Module, L) =>
    E = error(Formal,_),
    cmp_goal(Cmp, Goal),
    (   catch(Module:Goal, E, true)
    ->  (   var(Formal)
	->  cmp_true(T, Module, L)
	;   L = [cmp_error(Cmp,E)|L1],
	    cmp_true(T, Module, L1)
	)
    ;   L = [wrong_answer(Cmp)|L1],
	cmp_true(T, Module, L1)
    ).

cmp_goal(cmp(_Var, Expr), Goal) => Goal = Expr.
cmp_goal(Expr, Goal) => Goal = Expr.


%!  result_vars(+Expected, -Vars) is det.
%
%   Create a term v(V1, ...) containing all variables at the left
%   side of the comparison operator on Expected.

result_vars(Expected, Vars) :-
    arg(1, Expected, CmpOp),
    arg(1, CmpOp, Vars).

%!  nondet_compare(+Expected, +Bindings, +Unit, +Name, +Line) is semidet.
%
%   Compare list/set results for non-deterministic predicates.
%
%   @tbd    Properly report errors
%   @bug    Sort should deal with equivalence on the comparison
%           operator.

nondet_compare(all(Cmp), Bindings, _Unit, _Name, _Line) :-
    cmp(Cmp, _Vars, Op, Values),
    cmp_list(Values, Bindings, Op).
nondet_compare(set(Cmp), Bindings0, _Unit, _Name, _Line) :-
    cmp(Cmp, _Vars, Op, Values0),
    sort(Bindings0, Bindings),
    sort(Values0, Values),
    cmp_list(Values, Bindings, Op).

cmp_list([], [], _Op).
cmp_list([E0|ET], [V0|VT], Op) :-
    call(Op, E0, V0),
    cmp_list(ET, VT, Op).

%!  cmp(+CmpTerm, -Left, -Op, -Right) is det.

cmp(Var  == Value, Var,  ==, Value).
cmp(Var =:= Value, Var, =:=, Value).
cmp(Var  =  Value, Var,  =,  Value).
:- if(swi).
cmp(Var =@= Value, Var, =@=, Value).
:- else.
:- if(sicstus).
cmp(Var =@= Value, Var, variant, Value). % variant/2 is the same =@=
:- endif.
:- endif.


%!  call_det(:Goal, -Det) is nondet.
%
%   True if Goal succeeded.  Det is unified to =true= if Goal left
%   no choicepoints and =false= otherwise.

:- if((swi;sicstus)).
call_det(Goal, Det) :-
    call_cleanup(Goal,Det0=true),
    ( var(Det0) -> Det = false ; Det = true ).
:- else.
call_det(Goal, true) :-
    call(Goal).
:- endif.

%!  match_error(+Expected, +Received) is semidet.
%
%   True if the Received errors matches the expected error. Matching
%   is based on subsumes_term/2.

match_error(Expect, Rec) :-
    subsumes_term(Expect, Rec).

%!  setup(+Module, +Context, +Options) is semidet.
%
%   Call the setup handler and  fail  if   it  cannot  run  for some
%   reason. The condition handler is  similar,   but  failing is not
%   considered an error.  Context is one of
%
%    - unit(Unit)
%      If it is the setup handler for a unit
%    - test(Unit,Name,Line)
%      If it is the setup handler for a test

setup(Module, Context, Options) :-
    option(setup(Setup), Options),
    !,
    capture_output(reify(call_ex(Module, Setup), Result), Output),
    (   Result == true
    ->  true
    ;   print_message(error,
		      plunit(error(setup, Context, Output, Result))),
	fail
    ).
setup(_,_,_).

%!  condition(+Module, +Context, +Options) is semidet.
%
%   Evaluate the test or test unit condition.

condition(Module, Context, Options) :-
    option(condition(Cond), Options),
    !,
    capture_output(reify(call_ex(Module, Cond), Result), Output),
    (   Result == true
    ->  true
    ;   Result == false
    ->  fail
    ;   print_message(error,
		      plunit(error(condition, Context, Output, Result))),
	fail
    ).
condition(_, _, _).


%!  call_ex(+Module, +Goal)
%
%   Call Goal in Module after applying goal expansion.

call_ex(Module, Goal) :-
    Module:(expand_goal(Goal, GoalEx),
	    GoalEx).

%!  cleanup(+Module, +Options) is det.
%
%   Call the cleanup handler and succeed.   Failure  or error of the
%   cleanup handler is reported, but tests continue normally.

cleanup(Module, Options) :-
    option(cleanup(Cleanup), Options, true),
    (   catch(call_ex(Module, Cleanup), E, true)
    ->  (   var(E)
	->  true
	;   print_message(warning, E)
	)
    ;   print_message(warning, goal_failed(Cleanup, '(cleanup handler)'))
    ).

success(Unit, Name, Progress, Line, Det, Time, _Output, Options) :-
    memberchk(fixme(Reason), Options),
    !,
    (   (   Det == true
	;   memberchk(nondet, Options)
	)
    ->  progress(Unit:Name, Progress, fixme(passed), Time),
	Ok = passed
    ;   progress(Unit:Name, Progress, fixme(nondet), Time),
	Ok = nondet
    ),
    flush_output(user_error),
    assert(fixme(Unit, Name, Line, Reason, Ok)).
success(Unit, Name, Progress, Line, _, Time, Output, Options) :-
    failed_assertion(Unit, Name, Line, _,Progress,_,_),
    !,
    failure(Unit, Name, Progress, Line, assertion, Time, Output, Options).
success(Unit, Name, Progress, Line, _, Time, Output, Options) :-
    Output = true-_,
    !,
    failure(Unit, Name, Progress, Line, message, Time, Output, Options).
success(Unit, Name, Progress, Line, Det, Time, _Output, Options) :-
    assert(passed(Unit, Name, Line, Det, Time)),
    (   (   Det == true
	;   memberchk(nondet, Options)
	)
    ->  progress(Unit:Name, Progress, passed, Time)
    ;   unit_file(Unit, File),
	print_message(warning, plunit(nondet(File:Line, Unit:Name, Progress)))
    ).

%!  failure(+Unit, +Name, +Progress, +Line,
%!          +How, +Time, +Output, +Options) is det.
%
%   Test failed.  Report the error.

failure(Unit, Name, Progress, Line, _, Time, _Output, Options),
  memberchk(fixme(Reason), Options) =>
    assert(fixme(Unit, Name, Line, Reason, failed)),
    progress(Unit:Name, Progress, fixme(failed), Time).
failure(Unit, Name, Progress, Line, time_limit_exceeded(Limit), Time,
	Output, Options) =>
    assert_cyclic(timeout(Unit, Name, Line, Limit, Time)),
    progress(Unit:Name, Progress, timeout(Limit), Time),
    report_failure(Unit, Name, Progress, Line, timeout(Limit), Time, Output, Options).
failure(Unit, Name, Progress, Line, E, Time, Output, Options) =>
    assert_cyclic(failed(Unit, Name, Line, E, Time)),
    progress(Unit:Name, Progress, failed, Time),
    report_failure(Unit, Name, Progress, Line, E, Time, Output, Options).

%!  assert_cyclic(+Term) is det.
%
%   Assert  a  possibly  cyclic  unit   clause.  Current  SWI-Prolog
%   assert/1 does not handle cyclic terms,  so we emulate this using
%   the recorded database.
%
%   @tbd    Implement cycle-safe assert and remove this.

:- if(swi).
assert_cyclic(Term) :-
    acyclic_term(Term),
    !,
    assert(Term).
assert_cyclic(Term) :-
    Term =.. [Functor|Args],
    recorda(cyclic, Args, Id),
    functor(Term, _, Arity),
    length(NewArgs, Arity),
    Head =.. [Functor|NewArgs],
    assert((Head :- recorded(_, Var, Id), Var = NewArgs)).
:- else.
:- if(sicstus).
:- endif.
assert_cyclic(Term) :-
    assert(Term).
:- endif.


		 /*******************************
		 *             JOBS             *
		 *******************************/

:- if(current_prolog_flag(threads, true)).

:- dynamic
       job_data/2,		% Queue, Threads
       scheduled_unit/1.

schedule_unit(_:[]) :-
    !.
schedule_unit(UnitAndTests) :-
    UnitAndTests = Unit:_Tests,
    job_data(Queue, _),
    !,
    assertz(scheduled_unit(Unit)),
    thread_send_message(Queue, unit(UnitAndTests)).
schedule_unit(Unit) :-
    run_unit(Unit).

%!  setup_jobs(+Count) is det.
%
%   Setup threads for concurrent testing.

setup_jobs(Count) :-
    (   current_test_flag(jobs, Jobs0),
	integer(Jobs0)
    ->  true
    ;   current_prolog_flag(cpu_count, Jobs0)
    ),
    Jobs is min(Count, Jobs0),
    Jobs > 1,
    !,
    message_queue_create(Q, [alias(plunit_jobs)]),
    length(TIDs, Jobs),
    foldl(create_plunit_job(Q), TIDs, 1, _),
    asserta(job_data(Q, TIDs)),
    job_feedback(informational, jobs(Jobs)).
setup_jobs(_) :-
    job_feedback(informational, jobs(1)).

create_plunit_job(Q, TID, N, N1) :-
    N1 is N + 1,
    atom_concat(plunit_job_, N, Alias),
    thread_create(plunit_job(Q), TID, [alias(Alias)]).

plunit_job(Queue) :-
    repeat,
    (   catch(thread_get_message(Queue, Job,
				 [ timeout(10)
				 ]),
	      error(_,_), fail)
    ->  job(Job),
	fail
    ;   !
    ).

job(unit(Unit:Tests)) =>
    run_unit(Unit:Tests).
job(test(Unit, Test)) =>
    run_test(Unit, Test).

cleanup_jobs :-
    retract(job_data(Queue, TIDSs)),
    !,
    message_queue_destroy(Queue),
    maplist(thread_join, TIDSs).
cleanup_jobs.

%!  job_wait(?Unit) is det.
%
%   Wait for all test jobs to finish.

job_wait(Unit) :-
    thread_wait(\+ scheduled_unit(Unit),
		[ wait_preds([scheduled_unit/1]),
		  timeout(1)
		]),
    !.
job_wait(Unit) :-
    job_data(_Queue, TIDs),
    member(TID, TIDs),
    thread_property(TID, status(running)),
    !,
    job_wait(Unit).
job_wait(_).


job_info(begin(unit(Unit))) =>
    print_message(silent, plunit(begin(Unit))).
job_info(end(unit(Unit, Summary))) =>
    retractall(scheduled_unit(Unit)),
    print_message(silent, plunit(end(Unit, Summary))).

:- else.			% No jobs

schedule_unit(Unit) :-
    run_unit(Unit).

setup_jobs(_) :-
    print_message(silent, plunit(jobs(1))).
cleanup_jobs.
job_wait(_).
job_info(_).

:- endif.



		 /*******************************
		 *            REPORTING         *
		 *******************************/

%!  begin_test(+Unit, +Test, +Line, +Progress) is det.
%!  end_test(+Unit, +Test, +Line, +Progress) is det.
%
%   Maintain running/5 and report a test has started/is ended using
%   a =silent= message:
%
%       * plunit(begin(Unit:Test, File:Line, Progress))
%       * plunit(end(Unit:Test, File:Line, Progress))
%
%   @see message_hook/3 for intercepting these messages

begin_test(Unit, Test, Line, Progress) :-
    thread_self(Me),
    assert(running(Unit, Test, Line, Progress, Me)),
    unit_file(Unit, File),
    test_count(Total),
    job_feedback(information, begin(Unit:Test, File:Line, Progress/Total)).

end_test(Unit, Test, Line, Progress) :-
    thread_self(Me),
    retractall(running(_,_,_,_,Me)),
    unit_file(Unit, File),
    test_count(Total),
    job_feedback(information, end(Unit:Test, File:Line, Progress/Total)).

%!  running_tests is det.
%
%   Print the currently running test.

running_tests :-
    running_tests(Running),
    print_message(informational, plunit(running(Running))).

running_tests(Running) :-
    test_count(Total),
    findall(running(Unit:Test, File:Line, Progress/Total, Thread),
	    (   running(Unit, Test, Line, Progress, Thread),
		unit_file(Unit, File)
	    ), Running).


%!  current_test(?Unit, ?Test, ?Line, ?Body, ?Options) is nondet.
%
%   True when a test with the specified properties is loaded.

current_test(Unit, Test, Line, Body, Options) :-
    current_unit(Unit, Module, _Supers, _UnitOptions),
    Module:'unit test'(Test, Line, Options, Body).

%!  current_test_unit(?Unit, ?Options) is nondet.
%
%   True when a Unit is a current unit test declared with Options.

current_test_unit(Unit, UnitOptions) :-
    current_unit(Unit, _Module, _Supers, UnitOptions).


count(Goal, Count) :-
    aggregate_all(count, Goal, Count).

%!  test_summary(?Unit, -Summary) is det.
%
%   True when Summary is a dict that reports the main statistics
%   about the executed tests.

test_summary(Unit, Summary) :-
    count(failed(Unit, _0Test, _0Line, _Reason, _0Time), Failed),
    count(timeout(Unit, _0Test, _0Line, _Limit, _0Time), Timeout),
    count(passed(Unit, _0Test, _0Line, _Det, _0Time), Passed),
    count(blocked(Unit, _0Test, _0Line, _0Reason), Blocked),
    count(fixme(Unit, _0Test, _0Line, _0Reason, _0How), Fixme),
    test_count(Total),
    Summary = plunit{total:Total,
		     passed:Passed,
		     failed:Failed,
		     timeout:Timeout,
		     blocked:Blocked,
		     fixme:Fixme}.

test_summary_passed(Summary) :-
    _{failed: 0} :< Summary.

%!  report(+Time, +Options) is det.
%
%   Print a summary of the tests that ran.

report(Time, _Options) :-
    test_summary(_, Summary),
    print_message(silent, plunit(Summary)),
    _{ passed:Passed,
       failed:Failed,
       timeout:Timeout,
       blocked:Blocked,
       fixme:Fixme
     } :< Summary,
    (   Passed+Failed+Timeout+Blocked+Fixme =:= 0
    ->  info(plunit(no_tests))
    ;   Failed+Timeout =:= 0
    ->  report_blocked(Blocked),
	report_fixme,
        test_count(Total),
	info(plunit(all_passed(Total, Passed, Time)))
    ;   report_blocked(Blocked),
	report_fixme,
	report_failed(Failed),
	report_timeout(Timeout),
	info(plunit(passed(Passed))),
        info(plunit(total_time(Time)))
    ).

report_blocked(0) =>
    true.
report_blocked(Blocked) =>
    findall(blocked(Unit:Name, File:Line, Reason),
	    ( blocked(Unit, Name, Line, Reason),
	      unit_file(Unit, File)
	    ),
	    BlockedTests),
    info(plunit(blocked(Blocked, BlockedTests))).

report_failed(Failed) :-
    print_message(error, plunit(failed(Failed))).

report_timeout(Count) :-
    print_message(warning, plunit(timeout(Count))).

report_fixme :-
    report_fixme(_,_,_).

report_fixme(TuplesF, TuplesP, TuplesN) :-
    fixme(failed, TuplesF, Failed),
    fixme(passed, TuplesP, Passed),
    fixme(nondet, TuplesN, Nondet),
    print_message(informational, plunit(fixme(Failed, Passed, Nondet))).


fixme(How, Tuples, Count) :-
    findall(fixme(Unit, Name, Line, Reason, How),
	    fixme(Unit, Name, Line, Reason, How), Tuples),
    length(Tuples, Count).

report_failure(Unit, Name, Progress, Line, Error,
	       Time, Output, _Options) =>
    test_count(Total),
    job_feedback(error, failed(Unit:Name, Progress/Total, Line,
			       Error, Time, Output)).


%!  test_report(+What) is det.
%
%   Produce reports on test  results  after   the  run.  Currently  only
%   supports `fixme` for What.

test_report(fixme) :-
    !,
    report_fixme(TuplesF, TuplesP, TuplesN),
    append([TuplesF, TuplesP, TuplesN], Tuples),
    print_message(informational, plunit(fixme(Tuples))).
test_report(What) :-
    throw_error(domain_error(report_class, What), _).


		 /*******************************
		 *             INFO             *
		 *******************************/

%!  unit_file(+Unit, -File) is det.
%!  unit_file(?Unit, ?File) is nondet.
%
%   True when the test unit Unit is defined in File.

unit_file(Unit, File), nonvar(Unit) =>
    unit_file_(Unit, File),
    !.
unit_file(Unit, File) =>
    unit_file_(Unit, File).

unit_file_(Unit, File) :-
    current_unit(Unit, Module, _Context, _Options),
    module_property(Module, file(File)).
unit_file_(Unit, PlFile) :-
    test_file_for(TestFile, PlFile),
    module_property(Module, file(TestFile)),
    current_unit(Unit, Module, _Context, _Options).


		 /*******************************
		 *             FILES            *
		 *******************************/

%!  load_test_files(+Options) is det.
%
%   Load .plt test-files related  to   loaded  source-files.  Options is
%   currently ignored.

load_test_files(_Options) :-
    State = state(0,0),
    (   source_file(File),
	file_name_extension(Base, Old, File),
	Old \== plt,
	file_name_extension(Base, plt, TestFile),
	exists_file(TestFile),
        inc_arg(1, State),
	(   test_file_for(TestFile, File)
	->  true
	;   load_files(TestFile,
		       [ if(changed),
			 imports([])
		       ]),
            inc_arg(2, State),
	    asserta(test_file_for(TestFile, File))
	),
        fail
    ;   State = state(Total, Loaded),
        print_message(informational, plunit(test_files(Total, Loaded)))
    ).

inc_arg(Arg, State) :-
    arg(Arg, State, N0),
    N is N0+1,
    nb_setarg(Arg, State, N).


		 /*******************************
		 *           MESSAGES           *
		 *******************************/

%!  info(+Term)
%
%   Runs print_message(Level, Term), where Level is   one of `silent` or
%   `informational` (default).

info(Term) :-
    message_level(Level),
    print_message(Level, Term).

%!  progress(+UnitTest, +Progress, +Result, +Time) is det.
%
%   Test Unit:Name completed in Time. Result is the result and is one of
%
%     - passed
%     - failed
%     - assertion
%     - nondet
%     - fixme(passed)
%     - fixme(nondet)
%     - fixme(failed)
%     - forall(end, Nth, FTotal)
%       Pseudo result for completion of a forall(Gen,Test) set.  Mapped
%       to forall(FTotal, FFailed)

progress(UnitTest, _Progress, forall(end, Nth, FTotal), Time) =>
    (   retract(forall_failures(Nth, FFailed))
    ->  true
    ;   FFailed = 0
    ),
    test_count(Total),
    job_feedback(information, progress(UnitTest, forall(FTotal,FFailed), Nth/Total, Time)).
progress(UnitTest, Progress, Result, Time), Progress = forall(_Gen, Nth-_I) =>
    with_mutex(plunit_forall_counter,
               update_forall_failures(Nth, Result)),
    test_count(Total),
    job_feedback(information, progress(UnitTest, Result, Progress/Total, Time)).
progress(UnitTest, Progress, Result, Time) =>
    test_count(Total),
    job_feedback(information, progress(UnitTest, Result, Progress/Total, Time)).

update_forall_failures(_Nth, passed) =>
    true.
update_forall_failures(Nth, _) =>
    (   retract(forall_failures(Nth, Failed0))
    ->  true
    ;   Failed0 = 0
    ),
    Failed is Failed0+1,
    asserta(forall_failures(Nth, Failed)).

message_level(Level) :-
    (   current_test_flag(silent, true)
    ->  Level = silent
    ;   Level = informational
    ).

locationprefix(File:Line) -->
    !,
    [ url(File:Line), ':'-[], nl, '    ' ].
locationprefix(test(Unit,_Test,Line)) -->
    !,
    { unit_file(Unit, File) },
    locationprefix(File:Line).
locationprefix(unit(Unit)) -->
    !,
    [ 'PL-Unit: unit ~w: '-[Unit] ].
locationprefix(FileLine) -->
    { throw_error(type_error(locationprefix,FileLine), _) }.

:- discontiguous
    message//1.
:- '$hide'(message//1).

message(error(context_error(plunit_close(Name, -)), _)) -->
    [ 'PL-Unit: cannot close unit ~w: no open unit'-[Name] ].
message(error(context_error(plunit_close(Name, Start)), _)) -->
    [ 'PL-Unit: cannot close unit ~w: current unit is ~w'-[Name, Start] ].
message(plunit(nondet(Pos, Test, Progress))) -->
    locationprefix(Pos),
    test_name(Test, Progress),
    [ ': Test succeeded with choicepoint'-[] ].
message(error(plunit(incompatible_options, Tests), _)) -->
    [ 'PL-Unit: incompatible test-options: ~p'-[Tests] ].
message(plunit(sto(true))) -->
    [ 'Option sto(true) is ignored.  See `occurs_check` option.'-[] ].
message(plunit(test_files(Total, Loaded))) -->
    [ 'Found ~D .plt test files, loaded ~D'-[Total, Loaded] ].

					% Unit start/end
message(plunit(jobs(1))) -->
    !.
message(plunit(jobs(N))) -->
    [ 'Testing with ~D parallel jobs'-[N] ].
message(plunit(begin(_Unit))) -->
    { tty_feedback },
    !.
message(plunit(begin(Unit))) -->
    [ 'Start unit: ~w~n'-[Unit], flush ].
message(plunit(end(_Unit, _Summary))) -->
    { tty_feedback },
    !.
message(plunit(end(Unit, Summary))) -->
    (   {test_summary_passed(Summary)}
    ->  [ 'End unit ~w: passed (~3f sec CPU)'-[Unit, Summary.time.cpu] ]
    ;   [ ansi(error, 'End unit ~w: **FAILED (~3f sec CPU)', [Unit, Summary.time.cpu]) ]
    ).
message(plunit(blocked(unit(Unit, Reason)))) -->
    [ 'PL-Unit: ~w blocked: ~w'-[Unit, Reason] ].
message(plunit(running([]))) -->
    !,
    [ 'PL-Unit: no tests running' ].
message(plunit(running([One]))) -->
    !,
    [ 'PL-Unit: running ' ],
    running(One).
message(plunit(running(More))) -->
    !,
    [ 'PL-Unit: running tests:', nl ],
    running(More).
message(plunit(fixme([]))) --> !.
message(plunit(fixme(Tuples))) -->
    !,
    fixme_message(Tuples).
message(plunit(total_time(Time))) -->
    [ 'Test run completed'-[] ],
    test_time(Time).

					% Blocked tests
message(plunit(blocked(1, Tests))) -->
    !,
    [ 'one test is blocked'-[] ],
    blocked_tests(Tests).
message(plunit(blocked(N, Tests))) -->
    [ '~D tests are blocked'-[N] ],
    blocked_tests(Tests).

blocked_tests(Tests) -->
    { current_test_flag(show_blocked, true) },
    !,
    [':'-[]],
    list_blocked(Tests).
blocked_tests(_) -->
    [ ' (use run_tests/2 with ', ansi(code, 'show_blocked(true)', []),
      ' for details)'-[]
    ].

list_blocked([]) --> !.
list_blocked([blocked(Unit:Test, Pos, Reason)|T]) -->
    [nl],
    locationprefix(Pos),
    test_name(Unit:Test, -),
    [ ': ~w'-[Reason] ],
    list_blocked(T).

					% fail/success
message(plunit(no_tests)) -->
    !,
    [ 'No tests to run' ].
message(plunit(all_passed(1, 1, Time))) -->
    !,
    [ 'test passed' ],
    test_time(Time).
message(plunit(all_passed(Total, Total, Time))) -->
    !,
    [ 'All ~D tests passed'-[Total] ],
    test_time(Time).
message(plunit(all_passed(Total, Count, Time))) -->
    !,
    { SubTests is Count-Total },
    [ 'All ~D (+~D sub-tests) tests passed'- [Total, SubTests] ],
    test_time(Time).

test_time(Time) -->
    { var(Time) }, !.
test_time(Time) -->
    [ ' in ~3f seconds (~3f cpu)'-[Time.wall, Time.cpu] ].

message(plunit(passed(Count))) -->
    !,
    [ '~D tests passed'-[Count] ].
message(plunit(failed(0))) -->
    !,
    [].
message(plunit(failed(1))) -->
    !,
    [ '1 test failed'-[] ].
message(plunit(failed(N))) -->
    [ '~D tests failed'-[N] ].
message(plunit(timeout(0))) -->
    !,
    [].
message(plunit(timeout(N))) -->
    [ '~D tests timed out'-[N] ].
message(plunit(fixme(0,0,0))) -->
    [].
message(plunit(fixme(Failed,0,0))) -->
    !,
    [ 'all ~D tests flagged FIXME failed'-[Failed] ].
message(plunit(fixme(Failed,Passed,0))) -->
    [ 'FIXME: ~D failed; ~D passed'-[Failed, Passed] ].
message(plunit(fixme(Failed,Passed,Nondet))) -->
    { TotalPassed is Passed+Nondet },
    [ 'FIXME: ~D failed; ~D passed; (~D nondet)'-
      [Failed, TotalPassed, Nondet] ].

message(plunit(begin(Unit:Test, _Location, Progress))) -->
    { tty_columns(SummaryWidth, _Margin),
      test_name_summary(Unit:Test, SummaryWidth, NameS),
      progress_string(Progress, ProgressS)
    },
    (   { tty_feedback,
	  tty_clear_to_eol(CE)
	}
    ->  [ at_same_line, '\r[~w] ~w ..~w'-[ProgressS, NameS,
					     CE], flush ]
    ;   { jobs(_) }
    ->  [ '[~w] ~w ..'-[ProgressS, NameS] ]
    ;   [ '[~w] ~w ..'-[ProgressS, NameS], flush ]
    ).
message(plunit(end(_UnitTest, _Location, _Progress))) -->
    [].
message(plunit(progress(_UnitTest, Status, _Progress, _Time))) -->
    { Status = forall(_Gen,_NthI)
    ; Status == assertion
    },
    !.
message(plunit(progress(Unit:Test, Status, Progress, Time))) -->
    { jobs(_),
      !,
      tty_columns(SummaryWidth, Margin),
      test_name_summary(Unit:Test, SummaryWidth, NameS),
      progress_string(Progress, ProgressS),
      progress_tag(Status, Tag, _Keep, Style)
    },
    [ ansi(Style, '[~w] ~w ~`.t ~w (~3f sec)~*|',
	   [ProgressS, NameS, Tag, Time.wall, Margin]) ].
message(plunit(progress(_UnitTest, Status, _Progress, Time))) -->
    { tty_columns(_SummaryWidth, Margin),
      progress_tag(Status, Tag, _Keep, Style)
    },
    [ at_same_line, ansi(Style, '~`.t ~w (~3f sec)~*|',
			 [Tag, Time.wall, Margin]) ],
    (   { tty_feedback }
    ->  [flush]
    ;   []
    ).
message(plunit(failed(Unit:Test, Progress, Line, Failure, _Time, Output))) -->
    { unit_file(Unit, File) },
    locationprefix(File:Line),
    test_name(Unit:Test, Progress),
    [': '-[] ],
    failure(Failure),
    test_output(Output).
message(plunit(timeout(Unit:Test, Progress, Line, Limit, Output))) -->
    { unit_file(Unit, File) },
    locationprefix(File:Line),
    test_name(Unit:Test, Progress),
    [': '-[] ],
    timeout(Limit),
    test_output(Output).
:- if(swi).
message(plunit(failed_assertion(Unit:Test, Line, AssertLoc,
				Progress, Reason, Goal))) -->
    { unit_file(Unit, File) },
    locationprefix(File:Line),
    test_name(Unit:Test, Progress),
    [ ': assertion'-[] ],
    assertion_location(AssertLoc, File),
    assertion_reason(Reason), ['\n\t'],
    assertion_goal(Unit, Goal).

assertion_location(File:Line, File) -->
    [ ' at line ~w'-[Line] ].
assertion_location(File:Line, _) -->
    [ ' at ', url(File:Line) ].
assertion_location(unknown, _) -->
    [].

assertion_reason(fail) -->
    !,
    [ ' failed'-[] ].
assertion_reason(Error) -->
    { message_to_string(Error, String) },
    [ ' raised "~w"'-[String] ].

assertion_goal(Unit, Goal) -->
    { unit_module(Unit, Module),
      unqualify(Goal, Module, Plain)
    },
    [ 'Assertion: ~p'-[Plain] ].

unqualify(Var, _, Var) :-
    var(Var),
    !.
unqualify(M:Goal, Unit, Goal) :-
    nonvar(M),
    unit_module(Unit, M),
    !.
unqualify(M:Goal, _, Goal) :-
    callable(Goal),
    predicate_property(M:Goal, imported_from(system)),
    !.
unqualify(Goal, _, Goal).

test_output(Msgs-String) -->
    { nonvar(Msgs) },
    !,
    test_output(String).
test_output("") --> [].
test_output(Output) -->
    [ ansi(code, '~N~s', [Output]) ].

:- endif.
					% Setup/condition errors
message(plunit(error(Where, Context, _Output, throw(Exception)))) -->
    locationprefix(Context),
    { message_to_string(Exception, String) },
    [ 'error in ~w: ~w'-[Where, String] ].
message(plunit(error(Where, Context, _Output, false))) -->
    locationprefix(Context),
    [ 'setup failed in ~w'-[Where] ].

                                        % delayed output
message(plunit(test_output(_, Output))) -->
    [ '~s'-[Output] ].
					% Interrupts (SWI)
:- if(swi).
message(interrupt(begin)) -->
    { thread_self(Me),
      running(Unit, Test, Line, Progress, Me),
      !,
      unit_file(Unit, File),
      restore_output_state
    },
    [ 'Interrupted test '-[] ],
    running(running(Unit:Test, File:Line, Progress, Me)),
    [nl],
    '$messages':prolog_message(interrupt(begin)).
message(interrupt(begin)) -->
    '$messages':prolog_message(interrupt(begin)).
:- endif.

message(concurrent) -->
    [ 'concurrent(true) at the level of units is currently ignored.', nl,
      'See set_test_options/1 with jobs(Count) for concurrent testing.'
    ].

test_name(Name, forall(Generator, _Nth-I)/_Total) -->
    !,
    test_name(Name, -),
    [ ' (~d-th forall generator = '-[I],
      ansi(code, '~p', [Generator]), ')'-[]
    ].
test_name(Name, _) -->
    !,
    [ 'test ', ansi(code, '~q', [Name]) ].

running(running(Unit:Test, File:Line, _Progress, Thread)) -->
    thread(Thread),
    [ '~q:~q at '-[Unit, Test], url(File:Line) ].
running([H|T]) -->
    ['\t'], running(H),
    (   {T == []}
    ->  []
    ;   [nl], running(T)
    ).

thread(main) --> !.
thread(Other) -->
    [' [~w] '-[Other] ].

:- if(swi).
write_term(T, OPS) -->
    ['~W'-[T,OPS] ].
:- else.
write_term(T, _OPS) -->
    ['~q'-[T]].
:- endif.

expected_got_ops_(Ex, E, OPS, Goals) -->
    ['    Expected: '-[]], write_term(Ex, OPS), [nl],
    ['    Got:      '-[]], write_term(E,  OPS), [],
    ( { Goals = [] } -> []
    ; [nl, '       with: '-[]], write_term(Goals, OPS), []
    ).


failure(List) -->
    { is_list(List) },
    !,
    [ nl ],
    failures(List).
failure(Var) -->
    { var(Var) },
    !,
    [ 'Unknown failure?' ].
failure(succeeded(Time)) -->
    !,
    [ 'must fail but succeeded in ~2f seconds~n'-[Time] ].
failure(wrong_error(Expected, Error)) -->
    !,
    { copy_term(Expected-Error, Ex-E, Goals),
      numbervars(Ex-E-Goals, 0, _),
      write_options(OPS)
    },
    [ 'wrong error'-[], nl ],
    expected_got_ops_(Ex, E, OPS, Goals).
failure(wrong_answer(cmp(Var, Cmp))) -->
    { Cmp =.. [Op,Answer,Expected],
      !,
      copy_term(Expected-Answer, Ex-A, Goals),
      numbervars(Ex-A-Goals, 0, _),
      write_options(OPS)
    },
    [ 'wrong answer for ', ansi(code, '~w', [Var]),
      ' (compared using ~w)'-[Op], nl ],
    expected_got_ops_(Ex, A, OPS, Goals).
failure(wrong_answer(Cmp)) -->
    { Cmp =.. [Op,Answer,Expected],
      !,
      copy_term(Expected-Answer, Ex-A, Goals),
      numbervars(Ex-A-Goals, 0, _),
      write_options(OPS)
    },
    [ 'wrong answer (compared using ~w)'-[Op], nl ],
    expected_got_ops_(Ex, A, OPS, Goals).
failure(wrong_answer(CmpExpected, Bindings)) -->
    { (   CmpExpected = all(Cmp)
      ->  Cmp =.. [_Op1,_,Expected],
	  Got = Bindings,
	  Type = all
      ;   CmpExpected = set(Cmp),
	  Cmp =.. [_Op2,_,Expected0],
	  sort(Expected0, Expected),
	  sort(Bindings, Got),
	  Type = set
      )
    },
    [ 'wrong "~w" answer:'-[Type] ],
    [ nl, '    Expected: ~q'-[Expected] ],
    [ nl, '       Found: ~q'-[Got] ].
:- if(swi).
failure(cmp_error(_Cmp, Error)) -->
    { message_to_string(Error, Message) },
    [ 'Comparison error: ~w'-[Message] ].
failure(throw(Error)) -->
    { Error = error(_,_),
      !,
      message_to_string(Error, Message)
    },
    [ 'received error: ~w'-[Message] ].
:- endif.
failure(message) -->
    !,
    [ 'Generated unexpected warning or error'-[] ].
failure(setup_failed(throw(Error))) -->
    { Error = error(_,_),
      !,
      message_to_string(Error, Message)
    },
    [ 'test setup goal raised error: ~w'-[Message] ].
failure(setup_failed(_)) -->
    !,
    [ 'test setup goal failed' ].
failure(Why) -->
    [ '~p'-[Why] ].

failures([]) -->
    !.
failures([H|T]) -->
    !,
    failure(H), [nl],
    failures(T).

timeout(Limit) -->
    [ 'Timeout exceeeded (~2f sec)'-[Limit] ].

fixme_message([]) --> [].
fixme_message([fixme(Unit, _Name, Line, Reason, How)|T]) -->
    { unit_file(Unit, File) },
    fixme_message(File:Line, Reason, How),
    (   {T == []}
    ->  []
    ;   [nl],
	fixme_message(T)
    ).

fixme_message(Location, Reason, failed) -->
    [ 'FIXME: ~w: ~w'-[Location, Reason] ].
fixme_message(Location, Reason, passed) -->
    [ 'FIXME: ~w: passed ~w'-[Location, Reason] ].
fixme_message(Location, Reason, nondet) -->
    [ 'FIXME: ~w: passed (nondet) ~w'-[Location, Reason] ].


write_options([ numbervars(true),
		quoted(true),
		portray(true),
		max_depth(100),
		attributes(portray)
	      ]).

%!  test_name_summary(+Term, +MaxLen, -Summary) is det.
%
%   Given the test id, generate  string that summarizes this in MaxLen
%   characters.

test_name_summary(Term, MaxLen, Summary) :-
    summary_string(Term, Text),
    atom_length(Text, Len),
    (   Len =< MaxLen
    ->  Summary = Text
    ;   End is MaxLen//2,
        Pre is MaxLen - End - 2,
        sub_string(Text, 0, Pre, _, PreText),
        sub_string(Text, _, End, 0, PostText),
        format(string(Summary), '~w..~w', [PreText,PostText])
    ).

summary_string(Unit:Test, String) =>
    summary_string(Test, String1),
    atomics_to_string([Unit, String1], :, String).
summary_string(@(Name,Vars), String) =>
    format(string(String), '~W (using ~W)',
           [ Name, [numbervars(true), quoted(false)],
             Vars, [numbervars(true), portray(true), quoted(true)]
           ]).
summary_string(Name, String) =>
    term_string(Name, String, [numbervars(true), quoted(false)]).

%!  progress_string(+Progress, -S) is det.
%
%   True when S is a string representation for the test progress.

progress_string(forall(_Vars, N-I)/Total, S) =>
    format(string(S), '~w-~w/~w', [N,I,Total]).
progress_string(Progress, S) =>
    term_string(Progress, S).

%!  progress_tag(+Status, -Tag, -Keep, -Style) is det.
%
%   Given a progress status, determine the status tag, whether we must
%   preserve the  line and the Style  we must use to  print the status
%   line.

progress_tag(passed,        Tag, Keep, Style) =>
    Tag = passed, Keep = false, Style = comment.
progress_tag(fixme(passed), Tag, Keep, Style) =>
    Tag = passed, Keep = false, Style = comment.
progress_tag(fixme(_),      Tag, Keep, Style) =>
    Tag = fixme, Keep = true, Style = warning.
progress_tag(nondet,        Tag, Keep, Style) =>
    Tag = '**NONDET', Keep = true, Style = warning.
progress_tag(timeout(_Limit), Tag, Keep, Style) =>
    Tag = '**TIMEOUT', Keep = true, Style = warning.
progress_tag(assertion,     Tag, Keep, Style) =>
    Tag = '**FAILED', Keep = true, Style = error.
progress_tag(failed,        Tag, Keep, Style) =>
    Tag = '**FAILED', Keep = true, Style = error.
progress_tag(forall(_,0),   Tag, Keep, Style) =>
    Tag = passed, Keep = false, Style = comment.
progress_tag(forall(_,_),   Tag, Keep, Style) =>
    Tag = '**FAILED', Keep = true, Style = error.


		 /*******************************
		 *           OUTPUT		*
		 *******************************/

save_output_state :-
    stream_property(Output, alias(user_output)),
    stream_property(Error, alias(user_error)),
    asserta(output_streams(Output, Error)).

restore_output_state :-
    output_streams(Output, Error),
    !,
    set_stream(Output, alias(user_output)),
    set_stream(Error, alias(user_error)).
restore_output_state.



		 /*******************************
		 *      CONCURRENT STATUS       *
		 *******************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This part deals with interactive feedback   when we are running multiple
threads. The terminal window cannot work on   top  of the Prolog message
infrastructure and (thus) we have to use more low-level means.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

:- dynamic
       jobs/1,			% Count
       job_window/1,		% Count
       job_status_line/3.	% Job, Format, Args

job_feedback(_, jobs(Jobs)) :-
    retractall(jobs(_)),
    Jobs > 1,
    asserta(jobs(Jobs)),
    tty_feedback,
    !,
    retractall(job_window(_)),
    asserta(job_window(Jobs)),
    retractall(job_status_line(_,_,_)),
    jobs_redraw.
job_feedback(_, jobs(Jobs)) :-
    !,
    retractall(job_window(_)),
    info(plunit(jobs(Jobs))).
job_feedback(_, Msg) :-
    job_window(_),
    !,
    with_mutex(plunit_feedback, job_feedback(Msg)).
job_feedback(Level, Msg) :-
    print_message(Level, plunit(Msg)).

job_feedback(begin(Unit:Test, _Location, Progress)) =>
    tty_columns(SummaryWidth, _Margin),
    test_name_summary(Unit:Test, SummaryWidth, NameS),
    progress_string(Progress, ProgressS),
    tty_clear_to_eol(CE),
    job_format(comment, '\r[~w] ~w ..~w',
	       [ProgressS, NameS, CE]),
    flush_output.
job_feedback(end(_UnitTest, _Location, _Progress)) =>
    true.
job_feedback(progress(_UnitTest, Status, _Progress, Time)) =>
    (   hide_progress(Status)
    ->  true
    ;   tty_columns(_SummaryWidth, Margin),
	progress_tag(Status, Tag, _Keep, Style),
	job_finish(Style, '~`.t ~w (~3f sec)~*|',
		   [Tag, Time.wall, Margin])
    ).
job_feedback(failed(UnitTest, Progress, Line, Error, Time, Output)) =>
    tty_columns(_SummaryWidth, Margin),
    progress_tag(failed, Tag, _Keep, Style),
    job_finish(Style, '~`.t ~w (~3f sec)~*|',
	       [Tag, Time.wall, Margin]),
    print_test_output(Error, Output),
    (   (   Error = timeout(_)	% Status line suffices
	;   Error == assertion	% We will get an failed test later
	)
    ->  true
    ;   print_message(Style, plunit(failed(UnitTest, Progress, Line,
					   Error, Time, "")))
    ),
    jobs_redraw.
job_feedback(begin(_Unit)) => true.
job_feedback(end(_Unit, _Summary)) => true.

hide_progress(assertion).
hide_progress(forall(_,_)).
hide_progress(failed).
hide_progress(timeout(_)).

print_test_output(Error, _Msgs-Output) =>
    print_test_output(Error, Output).
print_test_output(_, "") => true.
print_test_output(assertion, Output) =>
    print_message(debug, plunit(test_output(error, Output))).
print_test_output(message, Output) =>
    print_message(debug, plunit(test_output(error, Output))).
print_test_output(_, Output) =>
    print_message(debug, plunit(test_output(informational, Output))).

%!  jobs_redraw is det.
%
%   Redraw the job window.

jobs_redraw :-
    job_window(N),
    !,
    tty_columns(_, Width),
    tty_header_line(Width),
    forall(between(1,N,Line), job_redraw_worker(Line)),
    tty_header_line(Width).
jobs_redraw.

job_redraw_worker(Line) :-
    (   job_status_line(Line, Fmt, Args)
    ->  ansi_format(comment, Fmt, Args)
    ;   true
    ),
    nl.

%!  job_format(+Style, +Fmt, +Args) is det.
%!  job_format(+Job, +Style, +Fmt, +Args, +Save) is det.
%
%   Point should be  below the status window.  Format  Fmt+Args in the
%   line Job using Style and return to the position below the window.

job_format(Style, Fmt, Args) :-
    job_self(Job),
    job_format(Job, Style, Fmt, Args, true).

%!  job_finish(+Style, +Fmt, +Args) is det.
%!  job_finish(+Job, +Style, +Fmt, +Args) is det.
%
%   Complete  the status  line  for Job.   This  redraws the  original
%   status line when we are using a job window.

job_finish(Style, Fmt, Args) :-
    job_self(Job),
    job_finish(Job, Style, Fmt, Args).

:- det(job_finish/4).
job_finish(Job, Style, Fmt, Args) :-
    retract(job_status_line(Job, Fmt0, Args0)),
    !,
    string_concat(Fmt0, Fmt, Fmt1),
    append(Args0, Args, Args1),
    job_format(Job, Style, Fmt1, Args1, false).

:- det(job_format/5).
job_format(Job, Style, Fmt, Args, Save) :-
    job_window(Jobs),
    Up is Jobs+2-Job,
    flush_output(user_output),
    tty_up_and_clear(Up),
    ansi_format(Style, Fmt, Args),
    (   Save == true
    ->  retractall(job_status_line(Job, _, _)),
	asserta(job_status_line(Job, Fmt, Args))
    ;   true
    ),
    tty_down_and_home(Up),
    flush_output(user_output).

:- det(job_self/1).
job_self(Job) :-
    job_window(N),
    N > 1,
    thread_self(Me),
    split_string(Me, '_', '', [_,_,S]),
    number_string(Job, S).

%!  feedback is semidet.
%
%   provide feedback using the `tty`  format, which reuses the current
%   output line if the test is successful.

tty_feedback :-
    has_tty,
    current_test_flag(format, tty).

has_tty :-
    stream_property(user_output, tty(true)).

tty_columns(SummaryWidth, Margin) :-
    tty_width(W),
    Margin is W-8,
    SummaryWidth is max(20,Margin-34).

tty_width(W) :-
    current_predicate(tty_size/2),
    catch(tty_size(_Rows, Cols), error(_,_), fail),
    Cols > 25,
    !,
    W = Cols.
tty_width(80).

tty_header_line(Width) :-
    ansi_format(comment, '~N~`\u2015t~*|~n', [Width]).

:- if(current_predicate(tty_get_capability/3)).
tty_clear_to_eol(S) :-
    getenv('TERM', _),
    catch(tty_get_capability(ce, string, S),
          error(_,_),
          fail),
    !.
:- endif.
tty_clear_to_eol('\e[K').

tty_up_and_clear(Lines) :-
    format(user_output, '\e[~dA\r\e[K', [Lines]).

tty_down_and_home(Lines) :-
    format(user_output, '\e[~dB\r', [Lines]).

:- if(swi).

:- multifile
    prolog:message/3,
    user:message_hook/3.

prolog:message(Term) -->
    message(Term).

%       user:message_hook(+Term, +Kind, +Lines)

user:message_hook(make(done(Files)), _, _) :-
    make_run_tests(Files),
    fail.                           % give other hooks a chance

:- endif.

:- if(sicstus).

user:generate_message_hook(Message) -->
    message(Message),
    [nl].                           % SICStus requires nl at the end

%!  user:message_hook(+Severity, +Message, +Lines) is semidet.
%
%   Redefine printing some messages. It appears   SICStus has no way
%   to get multiple messages at the same   line, so we roll our own.
%   As there is a lot pre-wired and   checked in the SICStus message
%   handling we cannot reuse the lines. Unless I miss something ...

user:message_hook(informational, plunit(begin(Unit)), _Lines) :-
    format(user_error, '% PL-Unit: ~w ', [Unit]),
    flush_output(user_error).
user:message_hook(informational, plunit(end(_Unit)), _Lines) :-
    format(user, ' done~n', []).

:- endif.
