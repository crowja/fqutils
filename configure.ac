AC_PREREQ([2.59])

##AC_INIT([fqutils], [0.0.4], [jac@ncgr.org])
AC_INIT([fqutils], m4_esyscmd_s([ver='0.1.0'; if test z$PREDIST = z; then echo $ver; else date +$ver-%s; fi]), [jac@ncgr.org])
AM_INIT_AUTOMAKE([1.10 -Wall foreign no-define dist-bzip2 no-installinfo no-texinfo.tex])


AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([ \
Makefile \
src/Makefile \
src/share/Makefile \
src/fqu_cat/Makefile \
src/fqu_cull/Makefile \
src/fqu_is_paired/Makefile \
src/fqu_splitq/Makefile \
src/fqu_summary/Makefile \
src/fqu_tidy/Makefile \
tests/Makefile
])

AC_CANONICAL_HOST

###AC_ARG_WITH([zlib-prefix],
### AS_HELP_STRING([--with-zlib-prefix=<path>], [Look for zlib includes in <path>/include and libraries in <path>/lib]),
### [zlib_lib=["-L${with_zlib_prefix}/lib"]],
### [LDFLAGS=["-L${with_zlib_prefix}/lib ${LDFLAGS}]" CPPFLAGS=["-I${with_zlib_prefix}/include ${CPPFLAGS}"]]
###)

AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_CC

AC_CHECK_LIB([z], [gzbuffer], [], [echo "@<:@1;31m*** FAILED ***@<:@0m Could not locate an appropriate libz; requires at least Zlib 1.2.4. Perhaps you need to specify LDFLAGS?" 2>&1; exit 1])

AC_OUTPUT

echo "\tCPPFLAGS\t${CPPFLAGS}"
echo "\tLDFLAGS \t${LDFLAGS}"

