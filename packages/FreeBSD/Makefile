# Created by: Harshavardhana
# $FreeBSD$
#

PORTNAME=         cmockery2
PORTVERSION=      1.3.8
CATEGORIES=       sysutils
MASTER_SITES=     https://codeload.github.com/lpabon/cmockery2/tar.gz/
DISTNAME=         v1.3.8
EXTRACT_SUFX=

MAINTAINER=       harsha@harshavardhana.net
COMMENT=          Cmockery2 revival of Cmockery unit test framework from Google

LICENSE=          AL2

WRKSRC=           ${WRKDIR}/cmockery2-${PORTVERSION}

PLIST_SUB+=       RESETPREFIX=${PREFIX}

GNU_CONFIGURE=    yes

INSTALL_TARGET=   install-strip
# Disable gcov on FreeBSD
#CONFIGURE_ARGS=   --enable-gcov
PREFIX= /usr

pre-configure:
	@${ECHO_MSG} "Running autogen.sh..."
	cd ${WRKSRC} && ./autogen.sh

post-install:
	@${ECHO_MSG} ""
	@${ECHO_MSG} "===================================================="
	@${ECHO_MSG} "Remember to visit for reading up documentation"
	@${ECHO_MSG} "https://github.com/lpabon/cmockery2/blob/master/doc/usage.md"
	@${ECHO_MSG} ""
	@${ECHO_MSG} "===================================================="

.include <bsd.port.mk>
