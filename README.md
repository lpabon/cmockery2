[![Build Status](https://travis-ci.org/lpabon/cmockery2.svg?branch=master)](https://travis-ci.org/lpabon/cmockery2)

# Overview

Cmockery tests are compiled into stand-alone executables and linked with the Cmockery library, the standard C library and module being tested. Any symbols external to the module being tested should be mocked - replaced with functions that return values determined by the test - within the test application. Even though significant differences may exist between the target execution environment of a code module and the environment used to test the code the unit testing is still valid since its goal is to test the logic of a code modules at a functional level and not necessarily all of its interactions with the target execution environment.

cmockery2 project also adds xUnit xml reporting support to integrate with Jenkins.

This repo is a fork from http://code.google.com/p/cmockery-staging/ which
is a fork from http://code.google.com/p/cmockery/.

# Features
* Lightweight C Unit test with mocking support
* JUnit XML report output which can be used with Jenkins
* Provides design-by-contract support

# Documentation
* [Usage Guide](doc/usage.md)
* [Coverage Support with Jenkins](doc/coverage.md)

# Presentations
* [Test Methodologies in C](http://slides-lpabon.rhcloud.com/feb24_glusterfs_unittest.html)
