# Enabling Coverage Support with Jenkins
To enable coverage support you will need to install the utility [Gcovr][]. Gcovr will analize the output from GNU Gcov and create a [Cobertura][] compatible XML file to be consumed by the Jenkins Cobertura plugin.

To install `gcovr` type the following command:

```
$ sudo easy_install gcovr
```

To enable [GNU Gcov][] support in your programs, you need to enable coverage support by adding the following CFLAGS to our build:

* In GCC

```
CFLAGS += -O0 --coverage
LDFLAGS += -lgcov
```

* In LLVM Clang

```
CFLAGS += -O0 -fprofile-arcs -ftest-coverage
```

Once you have built your programs using the new flags, running the program will enable GNU Gcov to generate two files, one ending with `*.gcda` and another ending in `*.gcno`.  These files will be analyzed by `gcovr` to create the Corbertura XML files using the following command:

```
$ gcovr -r . --xml -o coverage.xml
```

Gcovr has many more options.  Please visit their page at [gcovr.com][]

[Cobertura]: http://cobertura.sourceforge.net
[Gcovr]: http://gcovr.com 
[gcovr.com]: http://gcovr.com
[GNU Gcov]: http://gcc.gnu.org/onlinedocs/gcc/Gcov.html

