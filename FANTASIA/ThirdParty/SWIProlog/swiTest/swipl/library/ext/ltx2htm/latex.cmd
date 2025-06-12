% Standard LaTeX stuff

\documentstyle[-]{-}
\documentclass[-]{-}
\usepackage[-]{-}[-]=prolog
\makeindex
\title{+}
\booktitle
\author{+}
\maketitle
\psdirectories{-}
\thispagestyle{-}
\pagenumbering{-}
\bibliographystyle{-}
\bibliography{-}
{document}
{letter}

% Include
\include{-}
\input{-}
\InputIfFileExists{-}{+}{+}
\IfFileExists{-}{+}{+}

% Environments

{tabular}{-}
{tabulary}{-}{-}
{array}{-}
{tabbing}
{minipage}{-}
{center}
{abstract}
{quote}
{verbatim}=verbatim
{alltt}=verbatim
{code}=verbatim
{titlepage}
{minipage}{-}
{comment}

% Placing control

\clearpage
\cleardoublepage
\nopagebreak
\pagebreak
\linebreak
\newpage
\hyphenpenalty{-}
\centerline{+}
\rightline{+}

% floats

{table}[-]=float
{figure}[-]=float

% Lists

{itemize}=list
{description}=list
{enumerate}=list
{shortlist}=list
\item[+]=item		1 0

% Normal commands

\part{+}		2 2
\chapter*{+}		2 2
\section*{+}		2 2
\subsection*{+}		2 2
\subsubsection*{+}	2 2
\paragraph{+}		2 1
\subparagraph{+}	2 1
\footnote{+}		% 0
\footnotetext[-]{+}	1 1
\newlength{-}
\setlength{-}{-}
\ifthenelse{+}{+}{+}
\equal{+}{+}
\itemsep{-}
\settowidth{-}{-}
\newcommand{-}[-]{-}=prolog	1 1
\renewcommand{-}[-]{-}=prolog	1 1
\newenvironment{-}{-}{-} 1 1
\addcontentsline{-}{-}{+}
\parskip{d}
\parindent{d}
\def{-}{-}		1 1
\setcounter{-}{-}
\label{-}
\caption{+}		1 1
\ref{-}
\pageref{-}
\cite{-}
\nocite{-}
\yearcite{-}
\opencite{-}
\index{-}
\idx{-}
\tableofcontents
\printindex
\appendix
\string{-}
\mbox{+}
\makebox[-][-]{+}
\raisebox{-}{+}
\parbox[-]{d}{+}
\begin=begin		2 1
\end{-}=end		1 2
\\[d]			0 1
\ 
\-
\verb=verb
\newline

% table stuff

\hline
\multicolumn{-}{-}{+}
\cline{-}
\>

% Font switch/style commands

\ul
\bf
\em
\sc
\sl
\sf
\it
\rm
\tt
\Huge
\Large
\LARGE
\large
\small
\tiny
\normalsize
\footnotesize
\scriptsize
\cal

% Modern LaTeX font commands

\mathit{+}
\emph{+}
\texttt{+}
\textbf{+}
\textit{+}
\textsf{+}
\textsc{+}

% BibTeX support

{thebibliography}{-}=list
\bibitem[+]{-}=item
\newblock
\,
\protect
\citename{+}

% Dimensions

\textwidth
\linewidth
\vfil
\vfill
\hfill
\vskip{d}
\vspace{d}
\hspace{d}
\headheight{d}
\footheight{d}
\setlength{-}{d}
\vbox{-}
\noindent
\sloppy
\and
\leavevmode
\/
\rule{d}{d}

% Special characters

\{
\}
\[
\]
\&
\$
\%
\'{-}
\"{-}
\#
\copyright
\circ
\year
\LaTeX
\TeX

% Arithmetic (math mode)

\rhd
\times
\equiv
\pi
\le
\ge
\leq
\geq
\neq
\pm
\mid
\mu
\sin{+}
\cos{+}
\tan{+}
\sinh{+}
\cosh{+}
\tanh{+}
\arcsin{+}
\arccos{+}
\arctan{+}
\ln{+}
\lg{+}
\log{+}
\not{-}
\frac{+}{+}
\pow{+}{+}
\sqrt{+}
\mod{+}{+}
\rem{+}{+}
\div
\longrightarrow
\Longrightarrow
\rightarrow
\Rightarrow
\longleftrightarrow
\Longleftrightarrow
\leftrightarrow
\Leftrightarrow
\longleftarrow
\Longleftarrow
\leftarrow
\Leftarrow
\alpha
\beta
\exists
\emptyset
\subset
\langle
\rangle
\wedge
\sum


% fancy styles support

\fancyplain{-}
\pagestyle{-}
\rightmark
\leftmark
\lhead[-]{-}
\chead[-]{-}
\rhead[-]{-}
\lfoot[-]{-}
\cfoot[-]{-}
\rfoot[-]{-}
\footrulewidth{d}

% graphics support

\psfig{-}
\includegraphics[-]{-}

% Changebar support

\chgbarbegin
\chgbarend
\cbstart
\cbend

% Text producing commands

\ldots

% References

\chapref{-}
\Chapref{-}
\figref{-}
\Figref{-}
\secref{-}
\Secref{-}
\tabref{-}
\Tabref{-}

% Stuff from package{html}

\tick{+}=item
{htmlonly}
{dlist}=list
{itemlist}=list
\excludecomment{-}
\obeylines
\raggedright
\email{-}
\file{-}

% Output control commands

\onefile
\bodycolor{-}
\linkimage{-}{-}
\htmlmainfile{-}
\htmloutput{-}
\htmlfiledepth{-}
