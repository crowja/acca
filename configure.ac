dnl M4 seems to need the trailing comma below for the continuation
dnl to be treated correctly. Removing it (without doing anything
dnl else) will cause the generated configure to barf on finding
dnl a working C compiler.
AC_INIT(
  [Assessment of categorical causal assertions],
  [0.1],
  [crowja@gmail.com],
  [acca],
  [],
)

dnl Unique file in the source directory
AC_CONFIG_SRCDIR([src/main.c])

AC_PREREQ([2.69])
AC_COPYRIGHT([John A. Crow])
AC_CONFIG_MACRO_DIR([m4])

AC_LANG(C)
AC_PROG_CC

dnl AC_OPENMP sets the variable OPENMP_CFLAGS to the compiler
dnl flags needed for supporting OpenMP. Set to empty if (a) the 
dnl compiler already supports OpenMP, (b) if it has no way to
dnl activate OpenMP support, or if the user overrides it via
dnl "./configure --disable-openmp".
AC_OPENMP
dnl m4_include([m4/ax_lib_sqlite3.m4])
dnl AX_LIB_SQLITE3

dnl Process Makefile.in to create Makefile
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
