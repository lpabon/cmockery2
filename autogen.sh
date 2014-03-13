#!/bin/sh

# Before using, you should figure out all the .m4 macros that your
# configure.m4 script needs and make sure they exist in the autoconf/
# directory.
#
# These are the files that this script might edit:
#    aclocal.m4 configure Makefile.in src/config.h.in \
#    depcomp config.guess config.sub install-sh missing mkinstalldirs \
#    ltmain.sh
#
# Here's a command you can run to see what files aclocal will import:
#  aclocal -I ../autoconf --output=- | sed -n 's/^m4_include..\([^]]*\).*/\1/p'

rm -rf autom4te.cache > /dev/null 2>&1
rm -f m4/libtool.m4 m4/lt*.m4 > /dev/null 2>&1
if [ ! -d m4 ] ; then
    mkdir m4
fi

trap 'rm -f aclocal.m4.tmp' EXIT

# Use version 1.9 of aclocal and automake if available.
ACLOCAL=aclocal-1.9
if ! env "$ACLOCAL" --version > /dev/null 2>&1 ; then
  ACLOCAL=aclocal
fi

AUTOMAKE=automake-1.9
if ! env "$AUTOMAKE" --version > /dev/null 2>&1 ; then
  AUTOMAKE=automake
fi

# glibtoolize is used for Mac OS X
LIBTOOLIZE=libtoolize
if ! env "$LIBTOOLIZE" --version > /dev/null 2>&1 ; then
  LIBTOOLIZE=glibtoolize
fi

# aclocal tries to overwrite aclocal.m4 even if the contents haven't
# changed, which is annoying when the file is not open for edit (in
# p4).  We work around this by writing to a temp file and just
# updating the timestamp if the file hasn't change.
echo "Running $ACLOCAL ..."
"$ACLOCAL" --force -I m4 --output=aclocal.m4.tmp
if cmp aclocal.m4.tmp aclocal.m4 > /dev/null 2>&1 ; then
  touch aclocal.m4               # pretend that we regenerated the file
  rm -f aclocal.m4.tmp
else
  mv aclocal.m4.tmp aclocal.m4   # we did set -e above, so we die if this fails
fi

echo "Running autoheader ..."
autoheader -f -W all
echo "Running $LIBTOOLIZE ..."
"$LIBTOOLIZE" --automake -c -f
echo "Running autoconf ..."
autoconf -f -W all,no-obsolete
echo "Running automake ..."
"$AUTOMAKE" -a -c -f --foreign -W all

rm -rf autom4te.cache
exit 0
