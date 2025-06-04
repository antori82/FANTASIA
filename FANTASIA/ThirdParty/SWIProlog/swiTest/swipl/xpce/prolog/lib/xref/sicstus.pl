/*  Part of XPCE --- The SWI-Prolog GUI toolkit

    Author:        Jan Wielemaker and Anjo Anjewierden
    E-mail:        jan@swi.psy.uva.nl
    WWW:           http://www.swi.psy.uva.nl/projects/xpce/
    Copyright (c)  1995-2011, University of Amsterdam
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
This file contains a list of   Quintus  Prolog built-in predicates, used
for the XPCE/Prolog cross-referencer to compute require/1 directives
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

!.
','(_,_).
'.'(_,_).
'C'(_,_,_).
-->(_,_).
->(_,_).
:(_,_).
:-(_).
:-(_,_).
;(_,_).
<(_,_).
=(_,_).
=..(_,_).
=:=(_,_).
=<(_,_).
==(_,_).
=\=(_,_).
>(_,_).
>=(_,_).
?-(_).
?=(_,_).
@<(_,_).
@=<(_,_).
@>(_,_).
@>=(_,_).
[].
\+(_).
\==(_,_).
^(_,_).
abolish(_).
abolish(_,_).
abort.
absolute_file_name(_,_).
arg(_,_,_).
assert(_).
assert(_,_).
asserta(_).
asserta(_,_).
assertz(_).
assertz(_,_).
at_end_of_line(_).
at_end_of_line.
at_end_of_stream(_).
at_end_of_stream.
atom(_).
atom_chars(_,_).
atomic(_).
bagof(_,_,_).
bb_delete(_,_).
bb_get(_,_).
bb_put(_,_).
bb_update(_,_,_).
block(_).
break.
call(_).
call_residue(_,_).
callable(_).
character_count(_,_).
clause(_,_).
clause(_,_,_).
close(_).
compare(_,_,_).
compile(_).
compound(_).
consult(_).
copy_term(_,_).
create_mutable(_,_).
current_atom(_).
current_input(_).
current_key(_,_).
current_module(_).
current_module(_,_).
current_op(_,_,_).
current_output(_).
current_predicate(_,_).
current_stream(_,_,_).
debug.
debugging.
dif(_,_).
display(_).
dynamic(_).
ensure_loaded(_).
erase(_).
expand_term(_,_).
fail.
false.
fcompile(_).
fileerrors.
findall(_,_,_).
findall(_,_,_,_).
float(_).
flush_output(_).
flush_output.
format(_,_).
format(_,_,_).
freeze(_,_).
frozen(_,_).
functor(_,_,_).
garbage_collect.
gc.
get(_).
get(_,_).
get0(_).
get0(_,_).
get_mutable(_,_).
ground(_).
halt(_).
halt.
help.
if(_,_,_).
incore(_).
initialization(_).
initialization.
instance(_,_).
integer(_).
is(_,_).
keysort(_,_).
leash(_).
length(_,_).
line_count(_,_).
line_position(_,_).
listing(_).
listing.
load(_).
load_foreign_files(_,_).
meta_predicate(_).
mode(_).
module(_).
module(_,_).
multifile(_).
muse_flag(_,_).
muse_flag(_,_,_).
muse_flags.
muse_sync.
muse_trace(_).
muse_trace(_,_).
name(_,_).
nl(_).
nl.
nodebug.
nofileerrors.
nogc.
nonvar(_).
nospy(_).
nospyall.
notrace.
number(_).
number_chars(_,_).
numbervars(_,_,_).
on_exception(_,_,_).
op(_,_,_).
open(_,_,_).
open_null_stream(_).
otherwise.
parallel(_).
parallel.
peek_char(_).
peek_char(_,_).
phrase(_,_).
phrase(_,_,_).
portray_clause(_).
portray_clause(_,_).
predicate_property(_,_).
prepare_foreign_files(_).
print(_).
print(_,_).
print_message(_,_).
profile_data(_,_,_,_).
profile_reset(_).
prolog_flag(_,_).
prolog_flag(_,_,_).
prolog_load_context(_,_).
prompt(_,_).
public(_).
put(_).
put(_,_).
raise_exception(_).
read(_).
read(_,_).
read_term(_,_).
read_term(_,_,_).
reconsult(_).
recorda(_,_,_).
recorded(_,_,_).
recordz(_,_,_).
reinitialise.
repeat.
require(_).
restore(_).
retract(_).
retractall(_).
save(_).
save(_,_).
save_program(_).
see(_).
seeing(_).
seek(_,_,_,_).
seen.
sequential(_).
sequential.
set_input(_).
set_output(_).
set_stream_position(_,_).
setof(_,_,_).
simple(_).
skip(_).
skip(_,_).
skip_line(_).
skip_line.
sort(_,_).
source_file(_).
source_file(_,_).
spy(_).
spypoint_condition(_,_,_).
statistics(_,_).
statistics.
stream_code(_,_).
stream_interrupt(_,_,_).
stream_position(_,_).
stream_select(_,_,_).
tab(_).
tab(_,_).
tell(_).
telling(_).
told.
trace.
true.
ttyflush.
ttyget(_).
ttyget0(_).
ttynl.
ttyput(_).
ttyskip(_).
ttytab(_).
undo(_).
unknown(_,_).
update_mutable(_,_).
use_module(_).
use_module(_,_).
use_module(_,_,_).
var(_).
version(_).
version.
when(_,_).
write(_).
write(_,_).
write_canonical(_).
write_canonical(_,_).
write_term(_,_).
write_term(_,_,_).
writeq(_).
writeq(_,_).
