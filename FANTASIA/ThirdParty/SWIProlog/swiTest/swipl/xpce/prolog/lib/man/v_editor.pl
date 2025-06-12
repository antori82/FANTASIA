/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1985-2002, University of Amsterdam
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

:- module(man_editor, []).

:- use_module(library(pce)).
:- use_module(util).
:- require([ forall/2
           , ignore/1
           , member/2
           , send_list/2
           , send_list/3
           , show_key_bindings/1
           ]).

                 /*******************************
                 *        BUTTON (JUMP)         *
                 *******************************/

:- pce_begin_class(man_button_fragment(object), fragment,
                   "Active fragment in a card editor").

variable(object,        object,         get, "Related object").

initialise(F, TB:text_buffer, Re:regex, R:'0..9', Target:object) :->
    "Create fragment for target"::
    get(Re, register_start, R, S),
    get(Re, register_size, R, L),
    send(F, send_super, initialise, TB, S, L, jump),
    send(F, slot, object, Target).

:- pce_end_class.

                 /*******************************
                 *          FRAGMENT            *
                 *******************************/

:- pce_begin_class(man_fragment, fragment).

variable(object, object*, both, "Related object").

:- pce_end_class.



                 /*******************************
                 *           THE VIEW           *
                 *******************************/

:- pce_begin_class(man_editor, view).

class_variable(man_font,     font,   normal, "Font for running text").
class_variable(out_font,     font,   italic, "Font outside frags").
class_variable(title_font,   font,   bold,   "Font for titles").
class_variable(section_font, font,   huge,   "Font for sections").
class_variable(tag_font,     font,   italic, "Font for tags").
class_variable(code_font,    font,   fixed,  "Font for code att").
class_variable(jump_style,   style,  when(@colour_display,
                                          style(colour := dark_green,
                                                underline := @on),
                                          style(font := bold)),
               "Style for `jump' fragment").
class_variable(search_style, style,  when(@colour_display,
                                          style(background := green),
                                          style(highlight := @on))).
class_variable(size,         size,   size(80,15), "Size in chars").

initialise(E) :->
    get(E, out_font, OutFont),
    get(E, man_font, ManFont),
    get(E, title_font, TitleFont),
    get(E, section_font, SectionFont),
    get(E, code_font, CodeFont),
    get(E, tag_font, TagFont),
    get(E, jump_style, JumpStyle),
    get(E, search_style, SearchStyle),

    send(E, send_super, initialise),
    send(E, font, OutFont),
    send(E?image, tab_distance, 4 * CodeFont?ex),
    send(E, editable, @off),

    send(E, style, title, style(@nil, TitleFont)),
    send(E, style, title_tag, style(font := TagFont)),
    send(E, style, section, style(font := SectionFont)),
    send(E, style, code, style(@nil, CodeFont)),
    send(E, style, description, style(font := ManFont)),
    send(E, style, diagnostics, style(font := ManFont)),
    send(E, style, bugs, style(@nil, ManFont)),
    send(E, style, user_interface, style(font := ManFont)),
    send(E, style, last_modified, style(font := ManFont)),
    send(E, style, defaults, style(font := ManFont)),
    send(E, style, jump, JumpStyle),
    send(E, style, example_code, style(font := CodeFont)),
    send(E, style, mark, style(underline := @on)),
    send(E, style, search_hit, SearchStyle),

    send(E, key_binding, '\\C-x\\C-s', save_if_modified),
    send(E, key_binding, '\\C-c\\C-f', jump_on_caret),
    send(E, key_binding, '\\eM', toggle_fill_mode),
    send(E, key_binding, '\\ep', jump_previous),
    send(E, key_binding, '\\er', relate_from_caret),
    send(E?image, recogniser, @man_editor_recogniser),

    send(E, fill_mode, @on).


                /********************************
                *             MODES             *
                ********************************/

edit_mode(E, Val:bool) :->
    "Switch edit mode"::
    send(E, editable, Val).


                /********************************
                *             POPUP             *
                ********************************/


:- pce_global(@man_editor_recogniser, make_editor_recogniser).

make_editor_recogniser(G) :-
    new(G, handler_group),

    new(I, @event?receiver),                  % text_image
    new(E, I?window),                         % editor (view)
    new(C, ?(I, index, @event)),              % character index
    new(F, ?(E, find_fragment,
             message(@arg1, overlap, C))),    % Fragment
    new(J, ?(E, find_fragment,
             and(message(@arg1, overlap, C),
                 @arg1?style == jump))),      % Jump Fragment

    send(G, append, popup_gesture(new(P, popup))),

    send(P, attribute, attribute_fragment),
    send(P, attribute, jump_fragment),
    send(P, update_message,
         and(message(P, attribute_fragment, @nil),
             message(P, jump_fragment, @nil),
             message(P, attribute_fragment, F),
             message(P, jump_fragment, J))),

    new(JF, P?jump_fragment),
    new(AF, P?attribute_fragment),
    new(Tool, E?frame),
    new(Manual, Tool?manual),
    new(Selection, Manual?selection),
    new(Obj, AF?object),
    new(Class, when(message(Obj, has_get_method, context),
                    Obj?context, Obj)),
    new(HasClass, and(AF \== @nil,
                      message(Class, instance_of, class))),

    send_list(P, append,
              [ menu_item(jump,
                          message(E, jump_on_fragment, JF),
                          @default, @off,
                          JF \== @nil)
              , menu_item(back,
                          message(E, jump_previous),
                          @default, @on,
                          Manual?selection_history?size > 1)
              , menu_item(class_browser,
                          message(Manual, request_tool_focus, Class),
                          @default, @on,
                          HasClass)
              , menu_item(source,
                          message(Manual, request_source, Obj),
                          @default, @on,
                          and(AF \== @nil,
                              message(Obj, has_send_method, has_source),
                              message(Obj, has_source)))
              , menu_item(consult,
                          message(E, consult, AF),
                          @default, @on,
                          and(AF \== @nil, or(AF?style == code,
                                              AF?style == example_code)))
              , menu_item(show_key_bindings,
                          message(E, show_key_bindings),
                          @default, @on)
              ]),
    ifmaintainer(send_list(P, append,
              [ menu_item(describe,
                          message(E, describe, AF),
                          @default, @off,
                          and(I?frame?manual?edit_mode == @on,
                              AF \== @nil))
              , menu_item(relate,
                          message(Tool, request_relate, Obj),
                          condition :=
                             (and(Manual?edit_mode == @on,
                              Selection \== @nil, AF \== @nil,
                              Selection \== Obj,
                              not(message(Selection, man_related,
                                          see_also, Obj)))))

              ])),

    send(G, append, click_gesture(left, '', double,
                                  message(E, jump_on_caret))).


show_key_bindings(E, _Arg:[int]) :->
    "Popup a view with the key bindings"::
    ensure_loaded(library(keybinding)),
    show_key_bindings(E).


:- pce_global(@man_demo_file, new(file)).

consult(E, F:fragment) :->
    "Consult fragment of editor"::
    File = @man_demo_file,
    send(File, open, write),
    send(File, append, F?string),
    send(File, newline),
    send(File, close),
    get(File, name, FileName),
    consult(user:FileName),
    send(E, report, status, 'Fragment consulted'),
    send(File, remove).


describe(_E, TF:fragment) :->
    "Make the description of this object"::
    get(TF, object, Target),
    get(TF, next, @arg1?style == description, DFrag),
    send(DFrag, object, Target),
    (   get(TF, next, and(@arg1?style == mark,
                          @arg1?start < DFrag?start), Mark)
    ;   get(TF, previous, @arg1?style == mark, Mark)
    ),
    send(Mark, start, TF?start),
    send(Mark, object, Target).


toggle_fill_mode(E) :->
    "Toggle auto fill mode"::
    send(E, fill_mode, E?fill_mode?negate),
    send(E, report, status, 'Fill mode is now %N', E?fill_mode).


                 /*******************************
                 *             DISPLAY          *
                 *******************************/

selection(E, Objects:'chain|object') :->
    "Display manual for chain of objects"::
    send(E, clear),
    (   send(Objects, instance_of, chain)
    ->  group_objects(Objects, Sheet),
        send(Sheet, for_all,
             message(E, display_group, @arg1?name, @arg1?value))
    ;   send(E, display_cluster, chain(Objects))
    ),
    send(E, mark_jumpable),
    send(E, mark_search),
    send(E, keyboard_focus, E?editor).


display_group(E, Group:name, Members:chain) :->
    "Display group of objects of the same group"::
    send(E, display_group_title, Group),
    combine_behaviour(Members, Combined),
    send(Combined, for_all,
         message(E, display_cluster, @arg1)).


%       Display a cluster of objects with the same description.  First
%       The cluster is expanded with the source of the description.  If
%       the cluster contains variables that have class-variables, these are
%       appended too.

display_cluster(E, Members:chain) :->
    "Display a cluster of methods/classes"::
    get(Members, head, Leader),
    get(Leader, man_description, _), % force cache entry
    get(Leader, man_description_source, Source),
    send(Members, add, Source),
    send(Members, for_all,
         if(and(message(@arg1, instance_of, variable),
                message(Members, add,
                        ?(@arg1?context, class_variable, @arg1?name))))),
    send(Members, sort, ?(@prolog, compare_cluster_elements,
                          @arg1?class_name, @arg2?class_name)),
    send(Members, for_all,
         message(E, display_object_title, @arg1, Source)),
    send(E, display_object_description, Source),
    forall(member(Att, [user_interface, code]),
           ignore(send(E, display_object_attribute, Source, Att))).


:- pce_global(@man_cluster_order,
              new(chain(class,
                        delegate_variable,
                        variable,
                        class_variable,
                        get_method,
                        send_method))).


compare_cluster_elements(X, X, equal).
compare_cluster_elements(X, Y, R) :-
    send(@man_cluster_order, member, X),
    send(@man_cluster_order, member, Y),
    !,
    (   send(@man_cluster_order, before, X, Y)
    ->  R = smaller
    ;   R = larger
    ).
compare_cluster_elements(X, _, smaller) :-
    send(@man_cluster_order, member, X),
    !.
compare_cluster_elements(_, Y, larger) :-
    send(@man_cluster_order, member, Y),
    !.
compare_cluster_elements(X, Y, R) :-
    get(X, compare, Y, R).


%       displaying fields and titles

display_group_title(E, Group:name) :->
    "Display the title of a group"::
    send(E, append_fragment, @nil, section,
         string('%s\n\n', Group?capitalise)).

display_object_title(E, Obj:object, Source:[object]) :->
    "Display the header-line of an object"::
    get(Obj, man_header, Name),
    (   Source == Obj
    ->  get(E, text_buffer, TB),
        get(TB, size, Start),
        send(E, append_fragment, Obj, title, string('%s\n', Name)),
        new(F, man_fragment(TB, Start, 1, mark)),
        send(F, object, Obj)
    ;   send(E, append_fragment, Obj, title, string('%s\n', Name))
    ).


display_object_description(E, Obj:object) :->
    "Display the description of Obj"::
    get(Obj, man_description, Descr),
    new(S, string('%s', Descr)),
    send(S, append, '\n\n'),
    send(E, append_fragment, Obj, description, S).


attribute(user_interface).
attribute(code).

display_object_attribute(E, Obj:object, Att:name) :->
    "Display any other attribute of the object"::
    get(Obj, man_attribute, Att, Value),
    send(E, append_fragment, Obj, title, string('\t%s\n', Att?label_name)),
    indent(Value, V),
    send(E, append_fragment, Obj, Att, string('\n%s\n', V)).


combine_behaviour(Chain, Combined) :-
    new(Combined, chain),
    send(Chain, for_all,
         and(assign(new(B, var), @arg1),
             or(and(assign(new(Ch, var),
                           ?(Combined, find,
                             message(@arg1?head?man_description, equal,
                                     B?man_description))),
                    message(Ch, append, B)),
                message(Combined, append,
                        ?(@pce, instance, chain, B))))).


append_fragment(E, Obj:object*, Kind:name, Text:char_array) :->
    "Append text as named fragment"::
    get(E, text_buffer, TB),
    get(TB, size, Start),
    get(Text, size, Length),
    send(TB, append, Text),
    new(F, man_fragment(TB, Start, Length, Kind)),
    send(F, object, Obj).


                 /*******************************
                 *         SEARCH MARKS         *
                 *******************************/

mark_search(E) :->
    "Mark hits for the search patterns"::
    get(E, frame, Frame),
    get(Frame, manual, Manual),
    get(Manual, search_patterns, Patterns),
    (   Patterns == @nil
    ->  true
    ;   send(Patterns, for_all, message(E, mark_search_pattern, @arg1))
    ).


mark_search_pattern(E, Pattern:regex) :->
    get(E, text_buffer, TB),
    send(Pattern, for_all, TB,
         message(E, mark_search_hit, Pattern)).


mark_search_hit(E, Pattern:regex) :->
    get(E, text_buffer, TB),
    get(Pattern, register_start, Start),
    get(Pattern, register_end, End),
    Len is End - Start,
    new(_, man_fragment(TB, Start, Len, search_hit)).


                /********************************
                *            JUMPING            *
                ********************************/

jump_pattern('\\W(<?->?\\w+)').

:- pce_global(@man_object_regex,
              new(regex('@(\\w+)'))).
:- pce_global(@man_global_method_regex,
              new(regex('`@?((\\w+)\\s*(<?->?)(\\w+)):?[^\']*\''))).
:- pce_global(@man_local_method_regex,
              new(regex('\\W((<?->?)(\\w+))'))).
:- pce_global(@man_classclass_regex,
              new(regex('\\y[Cc]lass\\s+(\\w+|[-+*/?\\=])'))).
:- pce_global(@man_objectclass_regex,
              new(regex('(\\w+|[-+*/?\\=])[ \\t\\n]object'))).
:- pce_global(@man_classvar_regex,
              new(regex('(\\w+)\\.(\\w+)'))).
:- pce_global(@man_example_code_regex,
              new(regex('\n\\s*((\n\t\t+[^\t#*0-9][^\n]*|\n\\s*)+)\n'))).
:- pce_global(@man_example_regex,
              new(regex('[Ee]xample\\s+`([^\']+)\''))).
:- pce_global(@man_predicate_regex,
              new(regex('(\\w+)/(\\d+|\\[[0-9,-]+\\])'))).

mark_jumpable(E) :->
    "Mark possible active fragments"::
    get(E, text_buffer, TB),
    get(TB, find_all_fragments, @arg1?style == jump, JumpFrags),
    send(JumpFrags, for_all, message(@arg1, free)),
    send(JumpFrags, free),
    send(@man_object_regex, for_all, TB,
         if(message(E, mark_object, @arg1))),
    send(@man_global_method_regex, for_all, TB,
         if(message(E, mark_global_method, @arg1))),
    send(@man_classclass_regex, for_all, TB,
         if(message(E, mark_class, @arg1))),
    send(@man_objectclass_regex, for_all, TB,
         if(message(E, mark_class, @arg1))),
    send(@man_classvar_regex, for_all, TB,
         if(message(E, mark_classvar, @arg1))),
    send(@man_local_method_regex, for_all, TB,
         if(message(E, mark_local_method, @arg1))),
    send(@man_example_code_regex, for_all, TB,
         if(message(E, mark_example_code, @arg1))),
    send(@man_example_regex, for_all, TB,
         if(message(E, mark_example, @arg1))),
    send(@man_predicate_regex, for_all, TB,
         if(message(E, mark_predicate, @arg1))).


mark_example_code(E, Re:regex) :->
    get(Re, register_start, 1, Start),
    get(Re, register_size,  1, Size),
    get(E, text_buffer, TB),
    new(_, fragment(TB, Start, Size, example_code)).


mark_predicate(E, Re:regex) :->
    get(Re, register_value, E, 1, PredName),
    get(string('$predicates$%s', PredName), value, Id),
    new(_, man_button_fragment(E, Re, 0, Id)).


mark_example(E, Re:regex) :->
    get(Re, register_value, E, 1, Example),
    send(Example, translate, ' ', '_'),
    send(Example, downcase),
    get(string('$examples$%s', Example), value, Id),
    new(_, man_button_fragment(E, Re, 0, Id)).


mark_object(E, Re:regex) :->
    get(Re, register_value, E, 1, name, Ref),
    get(@pce, object_from_reference, Ref, _Target),
    new(Global, man_global(Ref)),
    new(_, man_button_fragment(E, Re, 0, Global)).


mark_classvar(E, Re:regex) :->
    get(Re, register_value, E, 1, name, ClassName),
    get(Re, register_value, E, 2, name, ClassVarName),
    get(@pce, convert, ClassName, class, Class),
    get(Class, class_variable, ClassVarName, ClassVar),
    new(_, man_button_fragment(E, Re, 0, ClassVar)).


mark_global_method(E, Re:regex) :->
    get(Re, register_value, E, 2, Class),
    get(Re, register_value, E, 3, Access),
    get(Re, register_value, E, 4, Selector),
    jump_method(Class, Access, Selector, Method),
    new(_, man_button_fragment(E, Re, 1, Method)).


mark_local_method(E, Re:regex) :->
    get(Re, register_value, E, 2, Access),
    get(Re, register_value, E, 3, Selector),
    get(Re, register_start, Start),
    get(E, find_fragment,
        and(message(@arg1, overlap, Start),
            @arg1?style == description),
        Fragment),
    get(Fragment, object, Obj),
    class_of(Obj, ClassName),
    get(@pce, convert, ClassName, class, Class),
    jump_method(Class, Access, Selector, Method),
    new(_, man_button_fragment(E, Re, 1, Method)).


jump_method(C0, A0, M0, Obj) :-
    (    send(C0, instance_of, class)
    ->   Class = C0
    ;    send(C0, downcase),
         send(C0, strip),
         get(@pce, convert, C0, class, Class)
    ),
    send_list([A0, M0], [downcase, strip]),
    get(A0, value, A1),
    get(M0, value, M1),
    preferred_send_get(A1, SG),
    get(Class, SG, M1, Obj),
    get(Obj, name, M1).                       % avoid catch_all

preferred_send_get('<-', get_method).
preferred_send_get('-', instance_variable).
preferred_send_get(_, send_method).
preferred_send_get(_, get_method).

mark_class(E, Re:regex) :->
    get(Re, register_value, E, 1, ClassString),
    send(ClassString, downcase),
    get(@pce, convert, ClassString, class, Class),
    new(_, man_button_fragment(E, Re, 1, Class)).


jump_on_caret(E, _Arg:[int]) :->
    "Jump to fragment around caret"::
    get(E, jump_fragment_from_caret, Frag),
    send(E, jump_on_fragment, Frag).


jump_on_fragment(E, Frag:fragment) :->
    "Select argument fragment"::
    get(Frag, object, Obj),
    (   atom(Obj)
    ->  (   get(Obj, scan, '$%[^$]$%s', vector(ModuleName, LocalId)),
            get(E?frame?manual, space, Space),
            get(Space, module, ModuleName, @on, Module),
            get(Module, card, LocalId, Target)
        ;   send(E, report, warning, 'Cannot find card from id %s', Obj),
            fail
        )
    ;   Target = Obj
    ),
    send(E?frame, request_selection, Target, @on).


jump_fragment_from_caret(E, Frag:fragment) :<-
    "Jumpable fragment at caret"::
    get(E, caret, C),
    (   get(E, find_fragment, and(message(@arg1, overlap, C),
                              @arg1?style == jump), Frag)
    ->  true
    ;   send(E, report, warning, 'Not in a jump fragment'),
        fail
    ).


jump_previous(E, _Arg:[int]) :->
    "Jump back to previous card"::
    get(E, frame, Frame),
    get(Frame, manual, Manual),
    get(Manual, selection_history, Chain),
    (   get(Chain, nth1, 2, Previous)
    ->  send(Frame, request_selection, Previous, @on)
    ;   send(E, report, warning, 'No previous card')
    ).

                /********************************
                *             RELATE            *
                ********************************/

relate_from_caret(E, _Arg:[int]) :->
    "Relate (see_also) with pointed-to object"::
    get(E, frame, Frame),
    get(Frame, manual, Manual),
    (   get(Manual, edit_mode, @on)
    ->  get(E, jump_fragment_from_caret, F),
        get(F, object, There),
        get(E, object, Here),
        (   Here == There
        ->  send(E, report, warning, 'Can''t relate to myself')
        ;   send(Here, man_related, see_also, There)
        ->  send(E, report, warning, 'Already related')
        ;   send(Manual, create_relation, relate, Here, see_also, There),
            send(Manual, create_relation, relate, There, see_also, Here)
        )
    ;   send(E, report, warning, 'Text is read-only')
    ).


                /********************************
                *             SAVING            *
                ********************************/

save_if_modified(E, _Arg:[int]) :->
    "Save value of the attribute has modified"::
    (   get(E, modified, @on),
        save_fragments(E, Changes),
        Changes > 0
    ->  send(E, mark_jumpable),
        send(@man_description_cache, clear),
        send(@man_source_cache, clear),
        send(E, report, status, string('Saved %d changes', Changes))
    ;   send(E, report, status, 'No changes need saving')
    ),
    send(E, modified, @off).


save_fragments(E, Changes) :-
    get(E, first_fragment, F),
    save_fragments(F, 0, Changes).


:- pce_global(@man_blank_line_regex,
              new(regex('(\\s*\n)*'))).
:- pce_global(@man_empty_regex,
              new(regex('\\s*(\\(not documented)?\\s*'))).
:- pce_global(@man_undent_regex,
              new(regex(@man_indent))).

attribute_fragment(description).
attribute_fragment(code).
attribute_fragment(user_interface).

save_fragments(@nil, S, S) :- !.
save_fragments(F, S0, S) :-
    get(F, style, Att),
    attribute_fragment(Att),
    get(F, object, Object),
    get(F, string, NewString),
    send(NewString, strip, trailing),
    (   send(@man_blank_line_regex, search, NewString),
        get(@man_blank_line_regex, register_start, 0)
    ->  get(@man_blank_line_regex, register_end, End),
        send(NewString, delete, 0, End)
    ;   true
    ),
    (   get(@man_empty_regex, match, NewString, NewStringSize),
        get(NewString, size, NewStringSize)
    ->  NewValue = @nil
    ;   NewValue = NewString
    ),
    (   Att == description,
        get(Object, man_description, OldValue) % HACK
    ->  true
    ;   get(Object, man_attribute, Att, OldValue)
    ->  true
    ;   OldValue = @nil
    ),
    \+ equal(NewValue, OldValue),
    !,
    (   NewValue \== @nil
    ->  send(NewValue, prepend, '\n'), % undent the lines (HACK)
        send(@man_undent_regex, for_all, NewValue,
             message(@arg1, replace, @arg2, @man_nl)),
        send(NewValue, delete, 0, 1)
    ;   true
    ),
    send(Object, man_attribute, Att, NewValue),
    (   NewValue == @nil
    ->  send(@pce, format, 'Cleared %s of %N\n', Att, Object)
    ;   get(NewValue, size, Size),
        send(@pce, format, 'Modified %s of %N (%d chars)\n',
             Att, Object, Size)
    ),
    S1 is S0 + 1,
    (   get(F, next, F1)
    ->  save_fragments(F1, S1, S)
    ;   S = S1
    ).
save_fragments(F, S0, S) :-
    (   get(F, next, F1)
    ->  save_fragments(F1, S0, S)
    ;   S = S0
    ).


equal(@nil, @nil) :- !.
equal(_, @nil) :- !, fail.
equal(@nil, _) :- !, fail.
equal(S1, S2) :- send(S1, equal, S2).

:- pce_end_class.
