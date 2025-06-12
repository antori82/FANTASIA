/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1996-2011, University of Amsterdam
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

:- module(xref_common,
          [ built_in/1
          ]).

built_in(!).
built_in([]).
built_in(abort).
built_in(char_code(_,_)).
built_in(ignore(_)).
built_in(is_list(_)).
built_in(atom_concat(_,_,_)).
built_in(catch(_,_,_)).
built_in(throw(_)).
built_in(sub_atom(_,_,_,_,_)).
built_in(at_end_of_line).
built_in(atom_codes(_,_)).
built_in(number_codes(_,_)).
built_in(current_prolog_flag(_,_)).
built_in(set_prolog_flag(_,_)).
built_in(current_predicate(_)).
built_in(break).
built_in(debug).
built_in(debugging).
built_in(fail).
built_in(false).
built_in(fileerrors).
built_in(forall(_,_)).
built_in(garbage_collect).
built_in(gc).
built_in(halt).
built_in(help).
built_in(listing).
built_in(nl).
built_in(nodebug).
built_in(nofileerrors).
built_in(nogc).
built_in(nospyall).
built_in(notrace).
built_in(otherwise).
built_in(repeat).
built_in(seen).
built_in(skip_line).
built_in(statistics).
built_in(told).
built_in(trace).
built_in(true).
built_in(ttyflush).
built_in(ttynl).
built_in(version).
built_in(term_variables(_,_)).
built_in(copy_term(_,_)).
built_in(','(_, _)).
built_in(-->(_, _)).
built_in(->(_, _)).
built_in([_|_]).
built_in(:(_, _)).
built_in(:-(_)).
built_in(:-(_, _)).
built_in(;(_, _)).
built_in(<(_, _)).
built_in(=(_, _)).
built_in(=..(_, _)).
built_in(=:=(_, _)).
built_in(=<(_, _)).
built_in(==(_, _)).
built_in(=\=(_, _)).
built_in(>(_, _)).
built_in(>=(_, _)).
built_in(?-(_)).
built_in(@<(_, _)).
built_in(@=<(_, _)).
built_in(@>(_, _)).
built_in(@>=(_, _)).
built_in('C'(_, _, _)).
built_in(\+(_)).
built_in(\==(_, _)).
built_in(^(_, _)).
built_in(abolish(_)).
built_in(abolish(_, _)).
built_in(absolute_file_name(_, _)).
built_in(arg(_, _, _)).
built_in(assert(_)).
built_in(assert(_, _)).
built_in(asserta(_)).
built_in(asserta(_, _)).
built_in(assertz(_)).
built_in(assertz(_, _)).
built_in(at_end_of_line(_)).
built_in(atom(_)).
built_in(atom_chars(_, _)).
built_in(atomic(_)).
built_in(bagof(_, _, _)).
built_in(call(_)).
built_in(callable(_)).
built_in(character_count(_, _)).
built_in(clause(_, _)).
built_in(clause(_, _, _)).
built_in(close(_)).
built_in(compare(_, _, _)).
built_in(compile(_)).
built_in(compound(_)).
built_in(consult(_)).
built_in(copy_term(_, _)).
built_in(current_atom(_)).
built_in(current_input(_)).
built_in(current_key(_, _)).
built_in(current_module(_)).
built_in(current_module(_, _)).
built_in(current_op(_, _, _)).
built_in(current_output(_)).
built_in(current_predicate(_, _)).
built_in(current_stream(_, _, _)).
built_in(display(_)).
built_in(dynamic(_)).
built_in(ensure_loaded(_)).
built_in(erase(_)).
built_in(expand_term(_, _)).
built_in(findall(_, _, _)).
built_in(float(_)).
built_in(flush_output(_)).
built_in(format(_, _)).
built_in(format(_, _, _)).
built_in(functor(_, _, _)).
built_in(get(_)).
built_in(get(_, _)).
built_in(get0(_)).
built_in(get0(_, _)).
built_in(ground(_)).
built_in(halt(_)).
built_in(initialization(_)).
built_in(instance(_, _)).
built_in(integer(_)).
built_in(is(_, _)).
built_in(keysort(_, _)).
built_in(leash(_)).
built_in(length(_, _)).
built_in(line_count(_, _)).
built_in(line_position(_, _)).
built_in(listing(_)).
built_in(load_foreign_files(_, _)).
built_in(meta_predicate(_)).
built_in(mode(_)).
built_in(module(_)).
built_in(module(_, _)).
built_in(multifile(_)).
built_in(name(_, _)).
built_in(nl(_)).
built_in(nonvar(_)).
built_in(nospy(_)).
built_in(number(_)).
built_in(number_chars(_, _)).
built_in(numbervars(_, _, _)).
built_in(on_exception(_, _, _)).
built_in(op(_, _, _)).
built_in(open(_, _, _)).
built_in(open_null_stream(_)).
built_in(peek_char(_)).
built_in(peek_char(_, _)).
built_in(phrase(_, _)).
built_in(phrase(_, _, _)).
built_in(portray_clause(_)).
built_in(predicate_property(_, _)).
built_in(print(_)).
built_in(print(_, _)).
built_in(print_message(_, _)).
built_in(prolog_flag(_, _)).
built_in(prolog_flag(_, _, _)).
built_in(prolog_load_context(_, _)).
built_in(prompt(_, _)).
built_in(public(_)).
built_in(put(_)).
built_in(put(_, _)).
built_in(raise_exception(_)).
built_in(read(_)).
built_in(read(_, _)).
built_in(read_term(_, _)).
built_in(read_term(_, _, _)).
built_in(reconsult(_)).
built_in(recorda(_, _, _)).
built_in(recorded(_, _, _)).
built_in(recordz(_, _, _)).
built_in(restore(_)).
built_in(retract(_)).
built_in(retractall(_)).
built_in(save_program(_)).
built_in(see(_)).
built_in(seeing(_)).
built_in(seek(_, _, _, _)).
built_in(set_input(_)).
built_in(set_output(_)).
built_in(setof(_, _, _)).
built_in(simple(_)).
built_in(skip(_)).
built_in(skip(_, _)).
built_in(skip_line(_)).
built_in(sort(_, _)).
built_in(source_file(_)).
built_in(source_file(_, _)).
built_in(spy(_)).
built_in(statistics(_, _)).
built_in(stream_code(_, _)).
built_in(stream_position(_, _)).
built_in(tab(_)).
built_in(tab(_, _)).
built_in(tell(_)).
built_in(telling(_)).
built_in(ttyget(_)).
built_in(ttyget0(_)).
built_in(ttyput(_)).
built_in(ttyskip(_)).
built_in(ttytab(_)).
built_in(unknown(_, _)).
built_in(use_module(_)).
built_in(use_module(_, _)).
built_in(use_module(_, _, _)).
built_in(var(_)).
built_in(version(_)).
built_in(write(_)).
built_in(write(_, _)).
built_in(write_canonical(_)).
built_in(write_canonical(_, _)).
built_in(write_term(_, _)).
built_in(write_term(_, _, _)).
built_in(writeq(_)).
built_in(writeq(_, _)).
