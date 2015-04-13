#!/bin/bash

# Simple script to create RPMs


cleanup()
{
    rm -rf ${RPMBUILDDIR} > /dev/null 2>&1
    rm -f ${PKGCONFIG} > /dev/null 2>&1
}

fail()
{
    exit 0
    cleanup
    echo $1
    exit $2
}

create_dir()
{
    if [ ! -d "$1" ] ; then
        mkdir -p "$1"
        if [ $? -ne 0 ] ; then
            fail "Unable to create dir $1" $?
        fi
    fi
}

gittotar()
{
    # Only archives committed changes
    # Export the current commited git changes to a directory
    git archive --format=tar --prefix=${SRCTAR_DIR}/ HEAD | gzip -c > ${SRCTAR}
    if [ $? -ne 0 -o \! -s ${SRCTAR} ] ; then
        fail "Unable to create git archive" $?
    fi
}

prep()
{
    rm -rf ${RPMBUILDDIR} > /dev/null 2>&1
    create_dir ${RPMBUILDDIR}
    create_dir ${RPMBUILDDIR}/SOURCES

    # Create a tar file out of the current committed changes
    gittotar

}

create_rpm()
{
    cp -f ${SRCTAR} ${RPMBUILDDIR}/SOURCES
    # Create the rpm
    # _topdir Notifies rpmbuild the location of the root directory
    #         containing the RPM information
    rpmbuild --define "_topdir ${RPMBUILDDIR}" \
        -ta ${SRCTAR}
    if [ $? -ne 0 ] ; then
        fail "Unable to create rpm" $?
    fi

    # Move the rpms to the root directory
}

create_src()
{
    git archive --format=tar --prefix=${SRCTAR_DIR}/ HEAD | gzip -c > ${SRCTAR}
    if [ $? -ne 0 ] ; then
        fail "Unable to create source archive"
    fi
}

################## MAIN #####################


## RPM NAME
RPMNAME=cmockery2
PKG_NAME=$RPMNAME
PKG_VERSION=1.3.9

BUILDDIR=$PWD/build
RPMBUILDDIR=${BUILDDIR}/rpmbuild
RPMBUILDDIR_RPMS=${RPMBUILDDIR}/RPMS
RPMBUILDDIR_SRPMS=${RPMBUILDDIR}/SRPMS
SRCNAME=${RPMNAME}-${PKG_VERSION}
SRCTAR_DIR=${PKG_NAME}-${PKG_VERSION}
SRCTAR=${RPMBUILDDIR}/${SRCNAME}.tar.gz

prep
create_src
create_rpm
