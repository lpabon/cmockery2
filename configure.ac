## To make it useful, replace <<TEXT>> with actual text for your project.
## Also, look at comments with "## double hashes" to see if any are worth
## uncommenting or modifying.

## Process this file with autoconf to produce configure.
## In general, the safest way to proceed is to run ./autogen.sh

# make sure we're interpreted by some minimal autoconf
AC_PREREQ(2.57)

AC_INIT(cmockery2, 1.3.4, lpabon@redhat.com)
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
AM_CONDITIONAL(GCC, test "$GCC" = yes)   # let the Makefile know if we're gcc

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

## Check out ../autoconf/ for other macros you can call to do useful stuff

# Write generated configuration file
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
