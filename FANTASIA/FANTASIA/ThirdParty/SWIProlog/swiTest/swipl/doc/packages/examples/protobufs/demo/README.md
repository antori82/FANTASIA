# Examples for handling Google's Protocol Buffers

## Makefile

The Makefile contains a grab-bag of simple rules, to make running some
of the examples easier. The default goal is `check`. Other convenience
goals exist - see the `.PHONY` rule to see what they are

## Installing protobuf (on Ubuntu)

You can use the Ubuntu package `protobuf-compiler` (this has been
tested with package 3.21.12-3, dated 8 Apr 2023) or you can clone from
https://github.com/protocolbuffers/protobuf - see `../bootstrap/README.md`
for more on this.

To install the Python support: `sudo apt install python3-protobuf`
version 3.21.12-3 or later). Alternatively: `python3 -m pip install
protobuf` (you might wish to add `--user`, or do this in a virtual
env).

## vector_demo.pl

Contains code snippets that correspond to the documentation
in `../protobufs_overview.md`. There are also some basic tests
in here.

TODO: separate out the tests into a proper test suite.
