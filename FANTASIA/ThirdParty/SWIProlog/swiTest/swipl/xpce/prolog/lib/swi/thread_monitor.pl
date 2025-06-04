/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2002-2013, University of Amsterdam
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

:- module(pce_thread_monitor,
          [
          ]).
:- use_module(library(pce)).
:- use_module(library(toolbar)).
:- use_module(library(pce_report)).
:- use_module(library(persistent_frame)).

:- pce_autoload(plotter,      library('plot/plotter')).
:- pce_autoload(partof_hyper, library(hyper)).
:- pce_autoload(float_item,   library(pce_float_item)).
:- pce_autoload(tick_box,     library(pce_tick_box)).

/** <module> XPCE-base SWI-Prolog thread monitor

This library defines  the  class   prolog_thread_monitor,  a  frame that
displays the status of threads.
*/

resource(running,   image, library('trace/icons/mini-run.xpm')).
resource(true,      image, image('16x16/ok.xpm')).
resource(false,     image, image('16x16/false.xpm')).
resource(exception, image, image('16x16/error.xpm')).
resource(exited,    image, image('16x16/done.xpm')).
resource(profiling, image, image('16x16/profiler.xpm')).


:- pce_begin_class(thread_statistics, object,
                   "Record historic status of a thread").

variable(local,  int := 0, get, "Local-stack usage").
variable(global, int := 0, get, "Global-stack usage").
variable(trail,  int := 0, get, "Trail-stack usage").
variable(cpu,    int := 0, get, "%CPU (0..100)").

initialise(TS, Thread:any, CPU:int) :->
    "Create for victim"::
    send_super(TS, initialise),
    (   catch(thread_stack_sizes(Thread, Local, Global, Trail), _, fail)
    ->  send(TS, slot, local,  Local),
        send(TS, slot, global, Global),
        send(TS, slot, trail,  Trail)
    ;   true
    ),
    send(TS, slot, cpu, CPU).

thread_stack_sizes(Thread, Local, Global, Trail) :-
    thread_statistics(Thread, localused, Local),
    thread_statistics(Thread, globalused, Global),
    thread_statistics(Thread, trailused, Trail).

:- pce_end_class(thread_statistics).


:- pce_begin_class(thread_status, dict_item,
                   "Status of a thread").

variable(status,   prolog,       get,  "Current status (thread_property(Id, status(Status)))").
variable(state,    name := running, get,  "Core status (functor of <-status)").
variable(seen,     bool := @off, both, "Seen this one").
variable(recall,   int,          get,  "Recall last #samples").
variable(lastcpu,  real*,        get,  "CPU at last call").
variable(lastwall, real*,        get,  "Wall at last call").
variable(leftcpu,  int := 0,     none, "Pass-through").
variable(profiling,bool := @off, get,  "Am I being profiled?").

initialise(TS, Id:'int|name', Recall:int, Status:prolog, CpuH:[int]) :->
    send_super(TS, initialise, Id, Id, new(chain), running),
    send(TS, slot, recall, Recall),
    send(TS, update, Status, CpuH).

update(TS, Status:prolog, CpuH:[int]) :->
    default(CpuH, 20, CPUH),
    get(TS, key, TID),
    send(TS, seen, @on),
    (   get(TS, state, running)
    ->  send(TS, slot, status, Status),
        functor(Status, State, _),
        get(TS, object, History),
        (   State == running
        ->  get(TS, cpu_percentage, CPU),
            CPULine is round(CPU*CPUH/100),
            atom_concat(running_, CPULine, RunningStyle),
            send(TS, state, running, RunningStyle),
            send(History, append, new(Stat, thread_statistics(TID, CPU))),
            (   get(TS, recall, Recall),
                get(History, size, Len),
                Len > Recall
            ->  send(History, delete_head),
                ignore(send(TS, send_hyper, diagram, shift_stat))
            ;   true
            ),
            ignore(send(TS, send_hyper, diagram, show_stat, Stat))
        ;   send(TS, state, State)
        )
    ;   true
    ).

cpu_percentage(TS, CPU:'0..100') :<-
    get(TS, key, TID),
    (   catch(thread_statistics(TID, cputime, Now), _, fail)
    ->  true
    ;   get(TS, lastcpu, Now), Now \== @nil
    ->  true
    ;   Now = 0.0
    ),
    get_time(WallNow),
    (   get(TS, lastcpu, Last), Last \== @nil,
        get(TS, lastwall, LastWall),
        get(TS, slot, leftcpu, Left),
        catch(CPU0 is round(100 * (Now-Last)/(WallNow-LastWall)) + Left,
              _, fail)
    ->  CPU is min(CPU0, 100),
        NewLeft is max(0, CPU0-CPU),
        send(TS, slot, leftcpu, NewLeft)
    ;   CPU = 0
    ),
    send(TS, slot, lastcpu, Now),
    send(TS, slot, lastwall, WallNow).

state(TS, State:name, Style:[name]) :->
    "Set state and update icon"::
    send(TS, slot, state, State),
    (   get(TS, profiling, @on)
    ->  send(TS, style, profiling)
    ;   default(Style, State, TheStyle),
        send(TS, style, TheStyle)
    ).

recall(TS, Recall:'1..') :->
    send(TS, slot, recall, Recall),
    get(TS, object, History),
    truncate_chain(History, Recall).

truncate_chain(Chain, Len) :-
    get(Chain, size, Size),
    Size =< Len,
    !.
truncate_chain(Chain, Len) :-
    send(Chain, delete_head),
    truncate_chain(Chain, Len).


join(TS) :->
    "Join this thread"::
    get(TS, key, TID),
    catch(thread_join(TID, _), _, fail),
    send(TS, free).

is_running(TS) :->
    "True if thread is running"::
    get(TS, style, Style),
    sub_atom(Style, 0, _, _, running).

start_profile(TS, How:[{cpu,wall}]) :->
    "Start profiling this thread"::
    (   get(TS, profiling, @on)
    ->  send(TS, report, warning, 'Already profiling')
    ;   get(TS, key, TID),
        profile_arg(How, TS, Arg),
        thread_signal(TID,
                      (       reset_profiler,
                              profiler(_, Arg)
                      )),
        send(TS, slot, profiling, @on),
        send(TS, style, profiling)
    ).


:- if(current_predicate('$profile'/2)).
profile_arg(cpu,  _, cputime).
profile_arg(wall, _, walltime).
:- else.
profile_arg(cpu,  _, true).
profile_arg(wall, TS, true) :-
    send(TS, report, warning,
         'Wall time profiling requires a more recent Prolog version').
:- endif.

end_profile(TS) :->
    "End profiling"::
    (   get(TS, profiling, @off)
    ->  send(TS, report, error, 'Not profiling')
    ;   get(TS, key, TID),
        thread_signal(TID,
                      ( profiler(_, false),
                        show_profile
                      )),
        send(TS, slot, profiling, @off),
        send(TS, style, TS?state)
    ).

:- if(current_predicate(show_profile/2)).
show_profile :-                                 % backward compatibility
    show_profile(plain, 25).
:- else.
show_profile :-
    show_profile([]).
:- endif.

abort(TS) :->
    "Send abort to the thread"::
    get(TS, key, TID),
    catch(thread_signal(TID, abort), _, fail).

trace(TS) :->
    "Prepare tread for debugging"::
    get(TS, key, TID),
    catch(thread_signal(TID, (attach_console, trace)), _, fail).

signal(TS, Signal:prolog) :->
    "Send a signal to the thread"::
    get(TS, key, TID),
    catch(thread_signal(TID, Signal), _, fail).

gtrace(TS) :->
    "Prepare tread for graphical debugging"::
    get(TS, key, TID),
    catch(thread_signal(TID, gtrace), _, fail).

:- pce_end_class(thread_status).


:- pce_begin_class(thread_browser, browser,
                   "Show active threads").

variable(recall,     int := 360, get, "#samples recalled").
variable(cpu_height, int := 20,  get, "Height of CPU image").
class_variable(size, size, size(10, 10)).

initialise(TB) :->
    send_super(TB, initialise),
    send(TB, style, running, style(icon := resource(running))),
    send(TB, style, true, style(icon := resource(true))),
    send(TB, style, false, style(icon := resource(false))),
    send(TB, style, exception, style(icon := resource(exception))),
    send(TB, style, exited, style(icon := resource(exited))),
    send(TB, style, profiling, style(icon := resource(profiling))),
    send(TB, select_message, message(TB, details, @arg1)),
    send(TB, running_styles),
    send(TB?image, recogniser,
         handler(ms_right_down,
                 and(message(TB, selection, ?(TB, dict_item, @event)),
                     new(or)))),
    send(TB, popup, new(P, popup)),
    new(IsRunning, message(@arg1, is_running)),
    send_list(P, append,
              [ menu_item(join,
                          message(@arg1, join),
                          condition := not(IsRunning)),
                gap,
                menu_item(graphical_debugger,
                          message(@arg1, gtrace),
                          condition := IsRunning),
                menu_item(debug_mode,
                          message(@arg1, signal, debug),
                          condition := IsRunning),
                menu_item(nodebug_mode,
                          message(@arg1, signal, nodebug),
                          condition := IsRunning),
                gap,
                menu_item(trace,
                          message(@arg1, trace),
                          condition := IsRunning),
                menu_item(attach_console,
                          message(@arg1, signal, attach_console),
                          condition := IsRunning),
                gap,
                menu_item(profile_cpu,
                          message(@arg1, start_profile, cpu),
                          condition := and(IsRunning,
                                           not(TB?profiling))),
                menu_item(profile_wall_time,
                          message(@arg1, start_profile, wall),
                          condition := and(IsRunning,
                                           not(TB?profiling))),
                menu_item(show_profile,
                          message(@arg1, end_profile),
                          condition := @arg1?profiling == @on),
                gap,
                menu_item(abort,
                          message(@arg1, abort),
                          condition := IsRunning)
              ]).

running_styles(TB) :->
    "Define styles running_0..running_<H>"::
    get(TB, font, Font),
    get(Font, ascent, Ascent),
    get(Font, descent, Descent),
    H is Ascent+Descent,
    send(TB, slot, cpu_height, H),
    new(Running, image(resource(running))),
    get(Running, size, size(W,_IH)),
    (   between(0, H, N),
        new(Img, image(@nil, W, H, pixmap)),
        send(Img, hot_spot, point(0, Ascent)),
        send(Img, background, grey80),
        send(Img, foreground, green),
        forall(between(0,N,I),
               (   Y is H-I,
                   send(Img, draw_in, line(0,Y,W,Y)))),
        send(Img, draw_in, bitmap(Running)),
        atom_concat(running_, N, Style),
        send(TB, style, Style, style(icon := Img)),
        fail
    ;   true
    ).

update(TB) :->
    "Update with thread-status"::
    get(TB, dict, Dict),
    send(Dict, for_all, message(@arg1, seen, @off)),
    forall(thread_id_status(Id, Status),
           send(TB, update_thread, Id, Status)),
    send(Dict, for_all,
         if(@arg1?seen == @off,
            message(@arg1, free))),
    (   get(TB, selection, TS),
        TS \== @nil
    ->  send(TB, report_status, TS)
    ;   true
    ).

:- if(catch(thread_property(main, id(_)),_,fail)).
thread_id_status(Id, Status) :-
    thread_property(Handle, status(Status)),
    (   atom(Handle)
    ->  Id = Handle
    ;   thread_property(Handle, id(Id))
    ).
:- else.
thread_id_status(Id, Status) :-
    thread_property(Id, status(Status)).
:- endif.


recall(TB, Recall:'1..') :->
    "Recall this many samples"::
    send(TB, slot, recall, Recall),
    get(TB, dict, Dict),
    send(Dict, for_all, message(@arg1, recall, Recall)).


update_thread(TB, Id:'int|name', Status:prolog) :->
    get(TB, cpu_height, CpuH),
    (   get(TB, member, Id, TS)
    ->  send(TS, update, Status, CpuH)
    ;   get(TB, recall, Recall),
        send(TB, append, thread_status(Id, Recall, Status, CpuH))
    ).

profiling(TB, TID:any) :<-
    "Thread we are profiling (or fail)"::
    get(TB, dict, Dict),
    get(Dict, find, @arg1?profiling == @on, DI),
    get(DI, key, TID).

join_all(TB) :->
    "Join all completed threads"::
    get(TB, dict, Dict),
    send(Dict, for_all,
         if(@arg1?state \== running,
            message(@arg1, join))).

details(TB, TS:thread_status) :->
    "Show detailed usage of thread"::
    get(TB?frame, member, thread_window, P),
    send(P, thread_diagram, TS),
    send(TB, report_status, TS).

report_status(TB, TS:thread_status) :->
    "Report status of a thread"::
    get(TS, status, Status),
    get(TS, key, TID),
    get(TS, lastcpu, Time),
    (   number(Time)
    ->  RTime = Time
    ;   RTime = 0
    ),
    (   Status = exception(Except),
        special_exception(Except)
    ->  message_to_string(Except, Message),
        send(TB, report, status,
             'Thread %s ERROR: %s (%.3f sec CPU)', TID, Message, RTime)
    ;   atomic(Status)
    ->  send(TB, report, status,
             'Thread %s status: %s (%.3f sec CPU)', TID, Status, RTime)
    ;   new(S, text_buffer),
        pce_open(S, write, Out),
        write_term(Out, Status, [ max_depth(5),
                                  quoted(true),
                                  portray(true)
                                ]),
        close(Out),
        send(TB, report, status,
             'Thread %s status: %s (%.3f sec CPU)', TID, S?contents, RTime)
    ).

special_exception(error(_,_)).
special_exception('$aborted').
special_exception(unwind(abort)).

:- pce_end_class(thread_browser).


:- pce_begin_class(thread_diagram, plotter,
                   "Show resource usage of thread").

variable(graphs, chain, get, "Graphs shown").

initialise(TD, TS:thread_status, Graphs:chain, H:int, V:int) :->
    "Create from thread-status report"::
    send_super(TD, initialise),
    default_size_limit(Limit),
    send(TD, slot, graphs, Graphs),
    send(TD, axis,
         new(X, thread_axis(y, 100, Limit, 10,  V, point(50,200)))),
    send(X, scale, log),
    send(TD, axis,
         plot_axis(x, 0, H, 100, H, point(50, 200))),
    new(_, partof_hyper(TS, TD, diagram, status)),
    send(TS, recall, H),
    send(TD, update).

default_size_limit(Limit) :-
    (   current_prolog_flag(address_bits, 32)
    ->  Limit is 100*1000*1000
    ;   Limit is 10*1000*1000*1000
    ).

attach(TD, TS:thread_status) :->
    "Switch to another thread"::
    send(TD, delete_hypers, status),
    new(_, partof_hyper(TS, TD, diagram, status)),
    send(TD, update).


axis_length(TD, H:[int], V:[int]) :->
    "Set length of the axis"::
    (   H == @default
    ->  true
    ;   get(TD, axis, x, XAxis),
        send(XAxis, length, H),
        send(XAxis, high, H),
        ignore(send(TD, send_hyper, status, recall, H))
    ),
    (   V == @default
    ->  true
    ;   get(TD, axis, y, YAxis),
        send(YAxis, length, V)
    ),
    send(TD, clear),
    send(TD, update).


update(TD) :->
    send(TD, clear),
    get(TD, hypered, status, TS),
    get(TS, object, History),
    send(TD?graphs, for_all,
         message(TD, show, History, @arg1)).


clear(TD) :->
    "Delete the paths"::
    send(TD?graphicals, for_all,
         if(message(@arg1, instance_of, path),
            message(@arg1, free))).


graphs(TD, Graphs:chain) :->
    send(TD, clear),
    send(TD, slot, graphs, Graphs),
    send(TD, update).


show(TD, History:chain, Selector:name) :->
    "Show all points of the given graph"::
    get(TD, axis, x, XAxis),
    get(TD, axis, y, YAxis),
    send(TD, display, new(G, path)),
    colour(Selector, Colour),
    send(G, colour, Colour),
    send(G, name, Selector),
    new(N, number(0)),
    send(History, for_all,
         and(message(G, append,
                     create(point,
                            ?(XAxis, location, N),
                            ?(YAxis, location, Selector, @arg1?Selector))),
             message(N, plus, 1))).

colour(local,  blue).
colour(global, orange).
colour(trail,  dark_green).
colour(cpu,    purple).

shift_stat(TD) :->
    "Delete leftmost point"::
    send(TD?graphs, for_all,
         message(TD, shift_graph, @arg1)).

shift_graph(TD, Which:name) :->
    (   get(TD, member, Which, G)
    ->  get(G, points, Points),
        get(Points, head, Head),
        get(Head, x, X0),
        send(G, delete, Head),
        get(Points?head, x, X1),
        Shift = X0 - X1,
        send(G, relative_move, point(Shift, 0), points)
    ;   true
    ).


show_stat(TD, Stat:thread_statistics) :->
    "Add a single sample"::
    send(TD?graphs, for_all,
         message(TD, extend_graph, Stat, @arg1)).


extend_graph(TD, Stat:thread_statistics, Sel:name) :->
    get(TD, member, Sel, G),
    get(TD, axis, y, YAxis),
    get(Stat, Sel, Value),
    get(YAxis, location, Sel, Value, Y),
    get(G?points, tail, PP),
    get(PP, x, LX),
    X is LX + 1,
    send(G, append, point(X, Y)).

:- pce_end_class(thread_diagram).


:- pce_begin_class(thread_axis, plot_axis,
                   "(Y-)Axis for thread-resources").

label_for_value(A, Val:'int|real', Gr:graphical) :<-
    "Generate readable labels"::
    (   Val < 1000
    ->  S = Val
    ;   Val < 1000*1000
    ->  K is Val / 1000,
        new(S, string('%dK', K))
    ;   Val < 1000*1000*1000
    ->  M is Val / (1000*1000),
        new(S, string('%dM', M))
    ;   M is Val / (1000*1000*1000),
        new(S, string('%dG', M))
    ),
    get(A, tag_font, Font),
    new(Gr, text(S, right, Font)).

location(A, Sel:name, Val:'int|real', Loc:int) :<-
    "Ignore values < low"::
    (   percent_scale(Sel)
    ->  get(A, percent_location, Val, Loc)
    ;   get(A, low, Low),
        V is max(Val, Low),
        get_super(A, location, V, Loc)
    ).

percent_scale(cpu).

percent_location(A, Val:'int|real', Loc:int) :<-
    "Simple percent scale location"::
    get(A, origin, point(_, Y0)),
    get(A, length, Len),
    Loc is Y0 - round(Len*Val/100).

:- pce_end_class(thread_axis).


:- pce_begin_class(thread_window, picture,
                   "Show details of a thread").

thread_diagram(Win, TS:thread_status) :->
    "Show thread-diagram for status"::
    (   get(Win, member, thread_diagram, TD)
    ->  send(TD, attach, TS)
    ;   send(Win, clear, destroy),
        get(Win, axis_length, size(H, V)),
        get(Win?frame, graphs, Graphs),
        send(Win, display, thread_diagram(TS, Graphs, H, V)),
        send(Win, recenter)
    ).

axis_length(Win, Size:size) :<-
    "Axis length for diagram"::
    get(Win, size, size(W, H)),
    get(@pce, convert, normal, font, Font),
    get(Font, ex, Ex),
    get(Font, height, FH),
    DW is W-10*Ex,
    DH is H-2*FH-10,
    new(Size, size(DW, DH)).

resize(Win) :->
    "Window is resized; update display"::
    get(Win, axis_length, size(W,H)),
    send(Win?frame, recall, W),
    (   get(Win, member, thread_diagram, TD)
    ->  send(TD, axis_length, W, H),
        send(Win, recenter)
    ;   true
    ).

recenter(Win) :->
    "Center what is displayed on me"::
    (   get(Win?graphicals, head, Head)
    ->  send(Head, center, Win?visible?center)
    ;   true
    ).

graphs(Win, Graphs:chain) :->
    "Determine the graphs displayed"::
    (   get(Win, member, thread_diagram, TD)
    ->  send(TD, graphs, Graphs)
    ;   true
    ).

:- pce_end_class(thread_window).


:- pce_begin_class(prolog_thread_monitor, persistent_frame,
                   "Monitor thread-activity").

variable(timer,           timer*,     get, "Update timer").
variable(graphs,          chain,      get, "Which graphs are shown").
variable(update_interval, 'int|real*', get, "Update interval").

class_variable(update_interval, 'int|real*', 0.2).
class_variable(graphs,          chain,      chain(local,global,trail,cpu)).

initialise(TM) :->
    send_super(TM, initialise, 'SWI-Prolog thread monitor'),
    send(TM, append, new(TD, tool_dialog)),
    send(new(thread_window), right, new(TB, thread_browser)),
    send(TB, below, TD),
    send(new(report_dialog), below, TB),
    send(TM, fill_tool_dialog, TD),
    send(TM, update),
    get(TM, update_interval, Time),
    send(TM, update_interval, Time),
    send(TM, selection, main).

unlink(TM) :->
    send(TM, update_interval, @nil),
    send_super(TM, unlink).

fill_tool_dialog(TM, TD:tool_dialog) :->
    "Fill menu-bar"::
    get(TM, member, thread_browser, TB),
    send_list(TD, append,
              [ new(File, popup(file)),
                new(Threads, popup(threads))
              ]),
    send_list(File, append,
              [ menu_item(settings, message(TM, settings)),
                gap,
                menu_item(exit, message(TM, destroy))
              ]),
    send_list(Threads, append,
              [ menu_item(new,
                          message(@prolog, interactor)),
                gap,
                menu_item(join_all,
                          message(TB, join_all))
              ]).


update_interval(TM, Interval:'int|real*') :->
    "Set the timer update interval"::
    (   get(TM, timer, Old), Old \== @nil
    ->  free(Old),
        send(TM, slot, timer, @nil)
    ;   true
    ),
    (   Interval == @nil
    ->  true
    ;   send(TM, slot, timer,
             new(T, timer(Interval, message(TM, update)))),
        send(T, service, @on),      % hide from debugger
        send(T, start)
    ).


graphs(TM, Graphs:chain) :->
    send(TM, slot, graphs, Graphs),
    get(TM, member, thread_window, TW),
    send(TW, graphs, Graphs).


update(TM) :->
    "Update status"::
    get(TM, member, thread_browser, TB),
    send(TB, update).

selection(TM, Thread:'name|int') :->
    "Select the given thread"::
    get(TM, member, thread_browser, TB),
    get(TB, member, Thread, DI),
    send(TB, selection, DI),
    send(TB, details, DI).

recall(TM, Recall:'1..') :->
    "#samples recalled"::
    get(TM, member, thread_browser, TB),
    send(TB, recall, Recall).


settings(TM) :->
    "Edit settings"::
    send(new(thread_settings_dialog(TM)), open_centered, TM?area?center).

:- pce_end_class(prolog_thread_monitor).


:- pce_begin_class(thread_settings_dialog, dialog,
                   "Settings for the thread-monitor").

initialise(D, TM:prolog_thread_monitor) :->
    send_super(D, initialise, 'Thread Monitor Settings'),
    send(D, append,
         new(FI, float_item(update_interval,
                            TM?update_interval,
                            message(TM, update_interval, @arg1),
                            0.05))),
    send(FI, step, 0.05),
    send(D, append, new(Graphs, menu(graphs, toggle,
                                     message(TM, graphs, @arg1)))),
    add_field(Graphs, local),
    add_field(Graphs, global),
    add_field(Graphs, trail),
    add_field(Graphs, cpu),
    get(TM, graphs, GraphsSetting),
    send(Graphs, selection, GraphsSetting),
    send(D, append,
         new(Apply, button(apply,
                           and(message(D, apply),
                               message(@receiver, active, @off))))),
    send(D, append, button(done, message(D, destroy))),
    send(D, default_button, apply),
    send(Apply, active, @off),
    new(_, partof_hyper(TM, D, settings, monitor)),
    send(D, transient_for, TM).

add_field(Menu, Name) :-
    colour(Name, Colour),
    send(Menu, append, new(MI, menu_item(Name))),
    send(MI, colour, Colour).

:- pce_end_class.
