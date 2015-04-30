[![Build Status](https://travis-ci.org/lpabon/cmockery2.svg?branch=master)](https://travis-ci.org/lpabon/cmockery2)
[![Join the chat at https://gitter.im/lpabon/cmockery2](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/lpabon/cmockery2?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Cmockery tests are compiled into a stand-alone executable and linked
with the cmockery library, the standard C library and module being
tested. Any symbols external to the module being tested should be
mocked - replaced with functions that return values determined by
the test - within the test application. Even though significant
differences may exist between the target execution environment of a
code module and the environment used to test the code the unit
testing is still valid since its goal is to test the logic of a
code modules at a functional level and not necessarily all of its
interactions with the target execution environment.

Other features:
* Lightweight C Unit test with mocking support
* JUnit XML report output which can be used with Jenkins
* Provides design-by-contract support

This project is a successor of http://code.google.com/p/cmockery-staging/
which is a successor of Google's http://code.google.com/p/cmockery/.


# Documentation

* [Usage Guide](doc/usage.md)
* [Coverage Support with Jenkins](doc/coverage.md)

# Presentations
* [Devconf 2015](http://slides-lpabon.rhcloud.com/02052015_devconf_cmockery2.html)
