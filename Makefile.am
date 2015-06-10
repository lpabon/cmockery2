## This is a boilerplate file for Google opensource projects.
## To make it useful, replace <<TEXT>> with actual text for your project.
## Also, look at comments with "## double hashes" to see if any are worth
## uncommenting or modifying.

## Process this file with automake to produce Makefile.in

# Make sure that when we re-make ./configure, we get the macros we need
ACLOCAL_AMFLAGS = -I m4

# This is so we can #include <cmockery/foo>
AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/src/cmockery

cmockeryincludedir = $(includedir)/cmockery
## The .h files you want to install (that is, .h files that people
## who install this package can include in their own applications.)
cmockeryinclude_HEADERS = src/cmockery/cmockery_override.h\
						  src/cmockery/cmockery.h\
						  src/cmockery/pbc.h

docdir = $(prefix)/share/doc/$(PACKAGE)-$(VERSION)
## This is for HTML and other documentation you want to install.
## Add your documentation files (in doc/) in addition to these
## top-level boilerplate files.  Also add a TODO file if you have one.
nodist_doc_DATA = AUTHORS COPYING ChangeLog doc/index.html doc/usage.md \
    doc/coverage.md

if HAVE_PKG_CONFIG
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE_NAME@.pc
endif

## The libraries (.so's) you want to install
lib_LTLIBRARIES =

## unittests you want to run when people type 'make check'.
## TESTS is for binary unittests, check_SCRIPTS for script-based unittests.
## TESTS_ENVIRONMENT sets environment variables for when you run unittest,
## but it only seems to take effect for *binary* unittests (argh!)
TESTS =
check_SCRIPTS =
noinst_SCRIPTS =


## vvvv RULES TO MAKE THE LIBRARIES, BINARIES, AND UNITTESTS

lib_LTLIBRARIES += libcmockery.la
libcmockery_la_SOURCES = src/cmockery/config.h\
						 src/cmockery.c\
						 src/cmockery/cmockery_override.h\
						 src/cmockery/cmockery.h\
						 src/cmockery/pbc.h
libcmockery_la_CFLAGS = -I$(top_srcdir)/src/cmockery -DHAVE_CONFIG_H -Wall \
                        -Werror

noinst_PROGRAMS = calculator
nodist_calculator_SOURCES = src/example/calculator.c src/cmockery/config.h
calculator_CFLAGS =

unit_test_CFLAGS = -I$(top_srcdir)/src/cmockery \
                   -I$(top_srcdir)/src/example -DUNIT_TESTING=1 \
                   -Wall -Werror -DHAVE_CONFIG_H

noinst_PROGRAMS += calculator_test
TESTS += calculator_test
nodist_calculator_test_SOURCES = src/example/calculator_test.c \
                          $(nodist_calculator_SOURCES)
calculator_test_CFLAGS = $(unit_test_CFLAGS)
calculator_test_LDADD = libcmockery.la

noinst_PROGRAMS += allocate_module_test
# Don't add this one, it returns a fail exit status,
# which is expected. TESTS += allocate_module_test
nodist_allocate_module_test_SOURCES = src/example/allocate_module_test.c \
                               src/example/allocate_module.c
allocate_module_test_CFLAGS = $(unit_test_CFLAGS)
allocate_module_test_LDADD = libcmockery.la

noinst_PROGRAMS += assert_macro_test
TESTS += assert_macro_test
nodist_assert_macro_test_SOURCES = src/example/assert_macro_test.c \
                            src/example/assert_macro.c
assert_macro_test_CFLAGS = $(unit_test_CFLAGS)
assert_macro_test_LDADD = libcmockery.la

noinst_PROGRAMS += customer_database_test
TESTS += customer_database_test
nodist_customer_database_test_SOURCES = src/example/customer_database_test.c \
                                 src/example/customer_database.c \
                                 src/example/database.h
customer_database_test_CFLAGS = $(unit_test_CFLAGS)
customer_database_test_LDADD = libcmockery.la

noinst_PROGRAMS += key_value_test
TESTS += key_value_test
nodist_key_value_test_SOURCES = src/example/key_value_test.c \
			 src/example/key_value.h \
                         src/example/key_value.c
key_value_test_CFLAGS = $(unit_test_CFLAGS)
key_value_test_LDADD = libcmockery.la

noinst_PROGRAMS += product_database_test
TESTS += product_database_test
product_database_testdir = src/example
nodist_product_database_test_SOURCES = src/example/product_database_test.c \
                                src/example/product_database.c \
                                src/example/database.h
product_database_test_CFLAGS = $(unit_test_CFLAGS)
product_database_test_LDADD = libcmockery.la

noinst_PROGRAMS += game_test
TESTS += game_test
nodist_game_test_SOURCES = src/example/game_test.c src/example/game.c
game_test_CFLAGS = $(unit_test_CFLAGS)
game_test_LDADD = libcmockery.la

noinst_PROGRAMS += run_tests
TESTS += run_tests
nodist_run_tests_SOURCES = src/example/run_tests.c
run_tests_CFLAGS = $(unit_test_CFLAGS)
run_tests_LDADD = libcmockery.la

noinst_PROGRAMS += realloc_test
TESTS += realloc_test
nodist_realloc_test_SOURCES = src/example/realloc_test.c
realloc_test_CFLAGS = $(unit_test_CFLAGS)
realloc_test_LDADD = libcmockery.la

noinst_PROGRAMS += mem_test
TESTS += mem_test
nodist_mem_test_SOURCES = src/example/mem_test.c
mem_test_CFLAGS = $(unit_test_CFLAGS)
mem_test_LDADD = libcmockery.la

## ^^^^ END OF RULES TO MAKE THE LIBRARIES, BINARIES, AND UNITTESTS


## This should always include $(TESTS), but may also include other
## binaries that you compile but don't want automatically installed.
noinst_PROGRAMS += $(TESTS)

rpm: dist-gzip packages/rpm.sh packages/rpm/rpm.spec
	@cd packages && ./rpm.sh ${PACKAGE} ${VERSION}

deb: dist-gzip packages/deb.sh packages/deb/*
	@cd packages && ./deb.sh ${PACKAGE} ${VERSION}

## If you're using libtool, add 'libtool' here.  Also add this rule:
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
EXTRA_DIST = autogen.sh README.md $(SCRIPTS)

CLEANFILES = *.gcda *.gcno *_xunit.xml

dist-hook:
	cp $(top_srcdir)/Makefile.am.dist $(top_distdir)/Makefile.am
