/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2009-2023, VU University Amsterdam
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

:- module(uri,
          [ uri_components/2,           % ?URI, ?Components
            uri_data/3,                 % ?Field, +Components, ?Data
            uri_data/4,                 % +Field, +Components, -Data, -New
	    uri_edit/3,			% +Actions,+URI0,-URI

            uri_normalized/2,           % +URI, -NormalizedURI
            iri_normalized/2,           % +IRI, -NormalizedIRI
            uri_normalized_iri/2,       % +URI, -NormalizedIRI
            uri_normalized/3,           % +URI, +Base, -NormalizedURI
            iri_normalized/3,           % +IRI, +Base, -NormalizedIRI
            uri_normalized_iri/3,       % +URI, +Base, -NormalizedIRI
            uri_resolve/3,              % +URI, +Base, -AbsURI
            uri_is_global/1,            % +URI
            uri_query_components/2,     % ?QueryString, ?NameValueList
            uri_authority_components/2, % ?Authority, ?Components
            uri_authority_data/3,       % ?Field, ?Components, ?Data
					% Encoding
            uri_encoded/3,              % +Component, ?Value, ?Encoded
            uri_file_name/2,            % ?URI, ?Path
            uri_iri/2                   % ?URI, ?IRI
	  ]).
:- autoload(library(error), [domain_error/2]).
:- use_foreign_library(foreign(uri)).

/** <module> Process URIs

This  library  provides   high-performance    C-based   primitives   for
manipulating URIs. We decided for a  C-based implementation for the much
better performance on raw character  manipulation. Notably, URI handling
primitives are used in  time-critical  parts   of  RDF  processing. This
implementation is based on RFC-3986:

        http://labs.apache.org/webarch/uri/rfc/rfc3986.html

The URI processing in this library is  rather liberal. That is, we break
URIs according to the rules, but we  do not validate that the components
are valid. Also, percent-decoding for IRIs   is  liberal. It first tries
UTF-8; then ISO-Latin-1 and finally accepts %-characters verbatim.

Earlier experience has shown that strict   enforcement of the URI syntax
results in many errors that  are   accepted  by  many other web-document
processing tools.
*/

%!  uri_components(+URI, -Components) is det.
%!  uri_components(-URI, +Components) is det.
%
%   Break a URI  into  its  5   basic  components  according  to the
%   RFC-3986 regular expression:
%
%       ==
%       ^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?
%        12            3  4          5       6  7        8 9
%       ==
%
%   @param Components is a   term  uri_components(Scheme, Authority,
%   Path, Search, Fragment). If a URI  is *parsed*, i.e., using mode
%   (+,-), components that are not   found are left _uninstantiated_
%   (variable). See uri_data/3 for accessing this structure.

%!  uri_data(?Field, +Components, ?Data) is semidet.
%
%   Provide access the uri_component structure.  Defined field-names
%   are: =scheme=, =authority=, =path=, =search= and =fragment=

uri_data(scheme,    uri_components(S, _, _, _, _), S).
uri_data(authority, uri_components(_, A, _, _, _), A).
uri_data(path,      uri_components(_, _, P, _, _), P).
uri_data(search,    uri_components(_, _, _, S, _), S).
uri_data(fragment,  uri_components(_, _, _, _, F), F).

%!  uri_data(+Field, +Components, +Data, -NewComponents) is semidet.
%
%   NewComponents is the same as Components with Field set to Data.

uri_data(scheme,    uri_components(_, A, P, Q, F), S,
                    uri_components(S, A, P, Q, F)).
uri_data(authority, uri_components(S, _, P, Q, F), A,
                    uri_components(S, A, P, Q, F)).
uri_data(path,      uri_components(S, A, _, Q, F), P,
                    uri_components(S, A, P, Q, F)).
uri_data(search,    uri_components(S, A, P, _, F), Q,
                    uri_components(S, A, P, Q, F)).
uri_data(fragment,  uri_components(S, A, P, Q, _), F,
                    uri_components(S, A, P, Q, F)).

%!  uri_normalized(+URI, -NormalizedURI) is det.
%
%   NormalizedURI is the normalized form   of  URI. Normalization is
%   syntactic and involves the following steps:
%
%       * 6.2.2.1. Case Normalization
%       * 6.2.2.2. Percent-Encoding Normalization
%       * 6.2.2.3. Path Segment Normalization

%!  iri_normalized(+IRI, -NormalizedIRI) is det.
%
%   NormalizedIRI is the normalized form   of  IRI. Normalization is
%   syntactic and involves the following steps:
%
%       * 6.2.2.1. Case Normalization
%       * 6.2.2.3. Path Segment Normalization
%
%   @see    This is similar to uri_normalized/2, but does not do
%           normalization of %-escapes.

%!  uri_normalized_iri(+URI, -NormalizedIRI) is det.
%
%   As uri_normalized/2, but percent-encoding is translated into IRI
%   Unicode characters. The translation  is   liberal:  valid  UTF-8
%   sequences  of  %-encoded  bytes  are    mapped  to  the  Unicode
%   character. Other %XX-sequences are mapped   to the corresponding
%   ISO-Latin-1 character and sole % characters are left untouched.
%
%   @see uri_iri/2.


%!  uri_is_global(+URI) is semidet.
%
%   True if URI has a scheme. The  semantics   is  the  same as the code
%   below, but the implementation is more efficient  as it does not need
%   to parse the other components, nor  needs   to  bind the scheme. The
%   condition to demand a scheme of more  than one character is added to
%   avoid confusion with DOS path names.
%
%   ==
%   uri_is_global(URI) :-
%           uri_components(URI, Components),
%           uri_data(scheme, Components, Scheme),
%           nonvar(Scheme),
%           atom_length(Scheme, Len),
%           Len > 1.
%   ==

%!  uri_resolve(+URI, +Base, -GlobalURI) is det.
%
%   Resolve a possibly local URI relative   to Base. This implements
%   http://labs.apache.org/webarch/uri/rfc/rfc3986.html#relative-transform

%!  uri_normalized(+URI, +Base, -NormalizedGlobalURI) is det.
%
%   NormalizedGlobalURI is the normalized global version of URI.
%   Behaves as if defined by:
%
%   ==
%   uri_normalized(URI, Base, NormalizedGlobalURI) :-
%           uri_resolve(URI, Base, GlobalURI),
%           uri_normalized(GlobalURI, NormalizedGlobalURI).
%   ==

%!  iri_normalized(+IRI, +Base, -NormalizedGlobalIRI) is det.
%
%   NormalizedGlobalIRI is the normalized  global   version  of IRI.
%   This is similar to uri_normalized/3, but   does  not do %-escape
%   normalization.

%!  uri_normalized_iri(+URI, +Base, -NormalizedGlobalIRI) is det.
%
%   NormalizedGlobalIRI is the normalized global IRI of URI. Behaves
%   as if defined by:
%
%   ==
%   uri_normalized(URI, Base, NormalizedGlobalIRI) :-
%           uri_resolve(URI, Base, GlobalURI),
%           uri_normalized_iri(GlobalURI, NormalizedGlobalIRI).
%   ==

%!  uri_query_components(+String, -Query) is det.
%!  uri_query_components(-String, +Query) is det.
%
%   Perform encoding and decoding of an URI query string. Query is a
%   list of fully decoded (Unicode) Name=Value pairs. In mode (-,+),
%   query elements of the forms Name(Value)  and Name-Value are also
%   accepted to enhance interoperability with   the option and pairs
%   libraries.  E.g.
%
%   ==
%   ?- uri_query_components(QS, [a=b, c('d+w'), n-'VU Amsterdam']).
%   QS = 'a=b&c=d%2Bw&n=VU%20Amsterdam'.
%
%   ?- uri_query_components('a=b&c=d%2Bw&n=VU%20Amsterdam', Q).
%   Q = [a=b, c='d+w', n='VU Amsterdam'].
%   ==


%!  uri_authority_components(+Authority, -Components) is det.
%!  uri_authority_components(-Authority, +Components) is det.
%
%   Break-down the  authority component of  a URI.  The fields  of the
%   structure Components  can be accessed  using uri_authority_data/3.
%   This  predicate deals  with  IPv6 addresses  written as  ``[ip]``,
%   returning the  _ip_ as `host`,  without the enclosing  `[]`.  When
%   constructing an  authority string and  the host contains  `:`, the
%   host is  embraced in  `[]`.  If  `[]` is  not used  correctly, the
%   behavior  should be  considered poorly  defined.  If  there is  no
%   balancing  `]` or  the  host part  does not  end  with `]`,  these
%   characters  are  considered  normal  characters and  part  of  the
%   (invalid) host name.


%!  uri_authority_data(+Field, ?Components, ?Data) is semidet.
%
%   Provide access the uri_authority  structure. Defined field-names
%   are: =user=, =password=, =host= and =port=

uri_authority_data(user,     uri_authority(U, _, _, _), U).
uri_authority_data(password, uri_authority(_, P, _, _), P).
uri_authority_data(host,     uri_authority(_, _, H, _), H).
uri_authority_data(port,     uri_authority(_, _, _, P), P).


%!  uri_encoded(+Component, +Value, -Encoded) is det.
%!  uri_encoded(+Component, -Value, +Encoded) is det.
%
%   Encoded   is   the   URI   encoding   for   Value.   When   encoding
%   (Value->Encoded), Component specifies the URI   component  where the
%   value is used. It is  one   of  =query_value=, =fragment=, =path= or
%   =segment=.  Besides  alphanumerical   characters,    the   following
%   characters are passed verbatim (the set   is split in logical groups
%   according to RFC3986).
%
%       $ query_value, fragment :
%       "-._~" | "!$'()*,;" | "@" | "/?"
%       $ path :
%       "-._~" | "!$&'()*,;=" | "@" | "/"
%       $ segment :
%       "-._~" | "!$&'()*,;=" | "@"

%!  uri_iri(+URI, -IRI) is det.
%!  uri_iri(-URI, +IRI) is det.
%
%   Convert between a URI, encoded in US-ASCII and an IRI. An IRI is
%   a fully expanded  Unicode  string.   Unicode  strings  are first
%   encoded into UTF-8, after which %-encoding takes place.
%
%   @error syntax_error(Culprit) in mode (+,-) if URI is not a
%   legally percent-encoded UTF-8 string.


%!  uri_file_name(+URI, -FileName) is semidet.
%!  uri_file_name(-URI, +FileName) is det.
%
%   Convert between a URI and a   local  file_name. This protocol is
%   covered by RFC 1738. Please note   that file-URIs use _absolute_
%   paths. The mode (-, +) translates  a possible relative path into
%   an absolute one.

uri_file_name(URI, FileName) :-
    nonvar(URI),
    !,
    uri_components(URI, Components),
    uri_data(scheme, Components, File), File == file,
    (   uri_data(authority, Components, '')
    ->  true
    ;   uri_data(authority, Components, localhost)
    ),
    uri_data(path, Components, FileNameEnc),
    uri_encoded(path, FileName0, FileNameEnc),
    delete_leading_slash(FileName0, FileName).
uri_file_name(URI, FileName) :-
    nonvar(FileName),
    !,
    absolute_file_name(FileName, Path0),
    ensure_leading_slash(Path0, Path),
    uri_encoded(path, Path, PathEnc),
    uri_data(scheme, Components, file),
    uri_data(authority, Components, ''),
    uri_data(path, Components, PathEnc),
    uri_components(URI, Components).

%!  ensure_leading_slash(+WinPath, -Path).
%!  delete_leading_slash(+Path, -WinPath).
%
%   Deal with the fact that absolute paths   in Windows start with a
%   drive letter rather than a  /.  For   URIs  we  need a path that
%   starts with a /.

ensure_leading_slash(Path, SlashPath) :-
    (   sub_atom(Path, 0, _, _, /)
    ->  SlashPath = Path
    ;   atom_concat(/, Path, SlashPath)
    ).

:- if(current_prolog_flag(windows, true)).
delete_leading_slash(Path, WinPath) :-
    atom_concat(/, WinPath, Path),
    is_absolute_file_name(WinPath),
    !.
:- endif.
delete_leading_slash(Path, Path).


		 /*******************************
		 *          MODIFYING           *
		 *******************************/

%!  uri_edit(+Actions, +URI0, -URI) is det.
%
%   Modify a  URI according  to Actions.  Actions  is either  a single
%   action or a  (nested) list of actions.   Defined primitive actions
%   are:
%
%     - scheme(+Scheme)
%       Set the Scheme of the URI (typically `http`, `https`, etc.)
%     - user(+User)
%       Add/set the user of the authority component.
%     - password(+Password)
%       Add/set the password of the authority component.
%     - host(+Host)
%       Add/set the host (or ip address) of the authority component.
%     - port(+Port)
%       Add/set the port of the authority component.
%     - path(+Path)
%       Set/extend the `path` component.  If Path is not absolute it
%       is taken relative to the path of URI0.
%     - search(+KeyValues)
%       Extend the `Key=Value` pairs of the current search (query)
%       component.   New values replace existing values.  If KeyValues
%       is written as =(KeyValues) the current search component is
%       ignored.  KeyValues is a list, whose elements are one of
%       `Key=Value`, `Key-Value` or `Key(Value)`.
%     - fragment(+Fragment)
%       Set the Fragment of the uri.
%
%   Components can be  _removed_ by using a variable  as value, except
%   from `path` which  can be reset using path(/) and  query which can
%   be dropped using query(=([])).
%
%   @arg URI0 is either a valid uri or a variable to start fresh.

uri_edit(Actions, URI0, URI) :-
    (   var(URI0)
    ->  URI1 = '/'
    ;   URI1 = URI0
    ),
    uri_components(URI1, Comp0),
    edit_components(Actions, Comp0, Comp),
    uri_components(URI, Comp).

edit_components([], Comp0, Comp) =>
    Comp = Comp0.
edit_components([H|T], Comp0, Comp) =>
    edit_components(H, Comp0, Comp1),
    edit_components(T, Comp1, Comp).
edit_components(scheme(Scheme), Comp0, Comp) =>
    uri_data(scheme, Comp0, Scheme, Comp).
edit_components(path(Path), Comp0, Comp) =>
    uri_data(path, Comp0, Path0),
    (   (   var(Path0)
        ;   Path0 == ''
        )
    ->  Path1 = '/'
    ;   Path1 = Path0
    ),
    uri_normalized(Path, Path1, Path2),
    uri_data(path, Comp0, Path2, Comp).
edit_components(fragment(Fragment), Comp0, Comp) =>
    uri_data(fragment, Comp0, Fragment, Comp).
edit_components(Authority, Comp0, Comp),
  authority_field(Authority) =>
    uri_data(authority, Comp0, Auth0),
    (   var(Auth0)
    ->  true
    ;   uri_authority_components(Auth0, AComp0)
    ),
    edit_auth_components(Authority, AComp0, AComp),
    uri_authority_components(Auth, AComp),
    uri_data(authority, Comp0, Auth, Comp).
edit_components(query(Search), Comp0, Comp) =>
    edit_components(search(Search), Comp0, Comp).
edit_components(search(=(Search)), Comp0, Comp) =>
    uri_query_components(String, Search),
    uri_data(search, Comp0, String, Comp).
edit_components(search(Search), Comp0, Comp) =>
    uri_data(search, Comp0, SS0),
    (   var(SS0)
    ->  Search0 = []
    ;   uri_query_components(SS0, Search0)
    ),
    join_search(Search0, Search, Search1),
    uri_query_components(SS1, Search1),
    uri_data(search, Comp0, SS1, Comp).
edit_components(Other, _, _) =>
    domain_error(uri_edit, Other).

authority_field(user(_)).
authority_field(password(_)).
authority_field(host(_)).
authority_field(port(_)).

edit_auth_components(user(User),
		     uri_authority(_, Passwd, Host, Port),
		     uri_authority(User, Passwd, Host, Port)).
edit_auth_components(password(Passwd),
		     uri_authority(User, _, Host, Port),
		     uri_authority(User, Passwd, Host, Port)).
edit_auth_components(host(Host),
		     uri_authority(User, Passwd, _, Port),
		     uri_authority(User, Passwd, Host, Port)).
edit_auth_components(port(Port),
		     uri_authority(User, Passwd, Host, _),
		     uri_authority(User, Passwd, Host, Port)).

join_search([], Search, Search).
join_search([N=_|ST], New, Search) :-
    (   memberchk(N=_, New)
    ->  true
    ;   functor(T, N, 1),
	memberchk(T, New)
    ->  true
    ;   memberchk(N-_, New)
    ),
    !,
    join_search(ST, New, Search).
join_search([H|ST], New, [H|Search]) :-
    join_search(ST, New, Search).


                 /*******************************
                 *            SANDBOX           *
                 *******************************/

:- multifile sandbox:safe_primitive/1.

sandbox:safe_primitive(uri:uri_components(_,_)).
sandbox:safe_primitive(uri:uri_normalized(_,_)).
sandbox:safe_primitive(uri:iri_normalized(_,_)).
sandbox:safe_primitive(uri:uri_normalized_iri(_,_)).
sandbox:safe_primitive(uri:uri_normalized(_,_,_)).
sandbox:safe_primitive(uri:iri_normalized(_,_,_)).
sandbox:safe_primitive(uri:uri_normalized_iri(_,_,_)).
sandbox:safe_primitive(uri:uri_resolve(_,_,_)).
sandbox:safe_primitive(uri:uri_is_global(_)).
sandbox:safe_primitive(uri:uri_query_components(_,_)).
sandbox:safe_primitive(uri:uri_authority_components(_,_)).
sandbox:safe_primitive(uri:uri_encoded(_,_,_)).
sandbox:safe_primitive(uri:uri_iri(_,_)).
