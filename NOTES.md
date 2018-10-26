# Dev notes on acca

To get started run autoconf to generate the configure script, then run it
to generate the Makefile from Makefile.in. This will help you understand
what to change in configure.ac and Makefile.in.

Clean up configure.ac. It includes, for example, using

    m4_include([m4/ax_lib_sqlite3.m4])
    AX_LIB_SQLITE3

in order to show how to incorporate local Autoconf macros.

Makefile.in also needs substantial cleaning. It contains many examples of
variables set by Autoconf templating.

The Makefile in src is simply a convenience for the dev; it's not called by
the top-level Makefile.
