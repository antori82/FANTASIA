/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        jan@swi-prolog.org
    WWW:           http://www.swi-prolog.org
    Copyright (c)  2024, SWI-Prolog Solutions b.v.
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

:- module(htmx,
          [ reply_htmx/1,               % +HTML
            reply_htmx/2,               % +HTML, +Request
            htmx_oob//2                 % ++Id, :HTML
          ]).
:- use_module(library(http/html_write)).

/** <module> Support htmx.org

Quoted from htmx.org:

> [htmx](https://htmx.org) gives you access to AJAX, CSS Transitions,
> WebSockets and Server Sent Events directly in HTML, using attributes,
> so you can build modern user interfaces with the simplicity and power
> of hypertext

The idea behind htmx is to allow   adding attributes to any HTML element
that cause an HTTP request. The  HTTP   response  is typically a (short)
HTML fragment that extends or replaces  an   element  on  the page. This
allows us to program a most functionality interactive seen in modern web
applications using the powerful  SWI-Prolog   HTML  generation framework
rather than having to write a  JSON backend and accompagnying JavaScript
frontend that runs in the browser.

Below is a minimal, yet fully functional application

```
:- use_module(library(http/http_server)).
:- use_module(library(http/htmx)).
:- use_module(library(main)).

:- initialization(main, main).

main(_Argv) :-
    http_server([port(8080)]),
    thread_get_message(quit).

http:location(htmx, root(htmx), []).

:- http_handler(root(.), home, []).

home(_Request) :-
    reply_html_page(
        [ title('HTMX demo'),
          script(src('https://unpkg.com/htmx.org'), [])
        ],
        [ button([ 'hx-post'('/htmx/clicked'),
                   'hx-swap'('outerHTML')
                 ],
                 'Click me')
        ]).

:- http_handler(htmx(clicked), reply_htmx(\clicked), []).

clicked -->
    html('Thanks for clicking me!').
```

HTMX requires no  dedicated  support  from   the  server.  This  library
provides reply_htmx/1,2 to reply with a  single HTML element rather than
an entire page.  Future  versions  of   this  library  may  provide some
additional utility predicates.
*/

:- html_meta
    reply_htmx(html),
    reply_htmx(html, +),
    htmx_oob(+, html, ?, ?).

%!  reply_htmx(+HTML) is det.
%!  reply_htmx(+HTML, +Request) is det.
%
%   Reply a plain HTML element as  opposed   to  a complete HTML page as
%   created using reply_html_page/2,3. While reply_htmx/1  is to be used
%   in a normal HTTP handler  (route),   reply_htmx/2  may be registered
%   directly in the http_handler/3 declaration to deal with simple cases
%   where we do not need the `Request` data.

reply_htmx(HTML) :-
    phrase(html(HTML), Tokens),
    format('Content-type: text/html~n~n', []),
    print_html(Tokens).

reply_htmx(HTML, _Request) :-
    reply_htmx(HTML).

%!  htmx_oob(++Target, :HTML)// is det.
%
%   Emit an htmx out-of-band element.  HTML is used to swap the
%   content of the DOM element with id Target.

htmx_oob(Target, HTML) -->
    html(div([id(Target), 'hx-swap-oob'(true)],
             HTML)).
