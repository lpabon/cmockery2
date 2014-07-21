# $FreeBSD$

PORTNAME=         cmockery2
PORTVERSION=      1.3.8
CATEGORIES=       sysutils
MASTER_SITES=     https://codeload.github.com/lpabon/cmockery2/tar.gz/
DISTNAME=         v1.3.8
EXTRACT_SUFX=

MAINTAINER=       harsha@harshavardhana.net
COMMENT=          Cmockery2 revival of Cmockery unit test framework from Google

WRKSRC=           ${WRKDIR}/cmockery2-${PORTVERSION}

PLIST_SUB+=       RESETPREFIX=${PREFIX}

GNU_CONFIGURE=    yes

INSTALL_TARGET=   install-strip
# Disable gcov on FreeBSD
#CONFIGURE_ARGS=   --enable-gcov
pre-patch:
	cd ${WRKSRC}; ./autogen.sh

.include <bsd.port.mk>
