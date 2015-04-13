## To make it useful, replace <<TEXT>> with actual text for your project.
## Also, look at comments with "## double hashes" to see if any are worth
## uncommenting or modifying.

## Process this file with autoconf to produce configure.
## In general, the safest way to proceed is to run ./autogen.sh

# make sure we're interpreted by some minimal autoconf
AC_PREREQ(2.57)

AC_INIT(cmockery2, 1.3.9, lpabon@redhat.com)
AC_CONFIG_AUX_DIR([.])

# The argument here is just something that should be in the current directory
# (for sanity checking)
AC_CONFIG_SRCDIR(README.md)
AM_INIT_AUTOMAKE
AC_GNU_SOURCE
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_CONFIG_HEADERS(src/cmockery/config.h)

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX

# Check if CC is linked to CLANG
AC_MSG_CHECKING([if compiling with clang])
AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([], [[
#ifndef __clang__
       not clang
#endif
]])],
[CLANG=yes], [CLANG=no])
AC_MSG_RESULT([$CLANG])
AM_CONDITIONAL(CLANG, test "$CLANG" = yes)

AM_CONDITIONAL(GCC, test "$GCC" = yes)   # let the Makefile know if we're gcc

OLD_CFLAGS=$CFLAGS
CFLAGS=

# Enable gcov suport.
AC_ARG_ENABLE([gcov],
AC_HELP_STRING([--enable-gcov],
[build binaries with gcov support]), [use_gcov=yes], [use_gcov=no])
if test "x$use_gcov" = xyes; then
  if test "x$CLANG" = xyes; then
    CFLAGS="$CFLAGS -fprofile-arcs -ftest-coverage"
  else
    CFLAGS="$CFLAGS --coverage"
  fi
fi
AM_CONDITIONAL(GCOV, test "$use_gcov" = yes)

if test "x$use_gcov" = xyes; then
  CFLAGS="$CFLAGS -O0 -g -Wall"
else
  CFLAGS="$CFLAGS $OLD_CFLAGS"
fi

# Uncomment this if you'll be exporting libraries (.so's)
# Use AC_PROG_LIBTOOL instead of LT_INIT because
# we need it to support EL5
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

# Check whether some low-level functions/files are available
AC_HEADER_STDC

# For older versions of automake
AM_PROG_CC_C_O

# Here are some examples of how to check for the existence of a fn or file
##AC_CHECK_FUNCS(memmove)
##AC_CHECK_HEADERS(sys/resource.h)
AC_CHECK_FUNCS(setjmp)
AC_CHECK_FUNCS(longjmp)
AC_CHECK_FUNCS(strcmp)
AC_CHECK_FUNCS(strcpy)
AC_CHECK_FUNCS(memcpy)
AC_CHECK_FUNCS(memset)
AC_CHECK_FUNCS(malloc)
AC_CHECK_FUNCS(calloc)
AC_CHECK_FUNCS(free)
AC_CHECK_FUNCS(exit)
AC_CHECK_FUNCS(signal)
AC_CHECK_FUNCS(printf)
AC_CHECK_FUNCS(fprintf)
AC_CHECK_FUNCS(snprintf)
AC_CHECK_FUNCS(vsnprintf)
AC_CHECK_FUNCS(gettimeofday)
AC_CHECK_FUNCS(strsignal)
AC_CHECK_HEADERS(assert.h)
AC_CHECK_HEADERS(malloc.h)
AC_CHECK_HEADERS(setjmp.h)
AC_CHECK_HEADERS(stdarg.h)
AC_CHECK_HEADERS(stddef.h)
AC_CHECK_HEADERS(stdio.h)
AC_CHECK_HEADERS(stdlib.h)
AC_CHECK_HEADERS(string.h)
AC_CHECK_HEADERS(signal.h)
AC_CHECK_HEADERS(inttypes.h)
AC_CHECK_HEADERS(stdint.h)
AC_CHECK_HEADERS(sys/time.h)
AC_CHECK_TYPES([unsigned long long, uintmax_t, uintptr_t])

AC_PREFIX_DEFAULT(/usr)

# If pkg-config
AC_CHECK_PROG(PKG_CONFIG, pkg-config, yes)
AM_CONDITIONAL([HAVE_PKG_CONFIG], [test "x$PKG_CONFIG" != "x"])
AS_IF([test "x$PKG_CONFIG" != "x"], [
    AC_CONFIG_FILES([cmockery2.pc])
])

## Check out ../autoconf/ for other macros you can call to do useful stuff

# Write generated configuration file
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
