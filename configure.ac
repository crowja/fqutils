AC_PREREQ([2.59])

AC_INIT( [fqutils], m4_esyscmd_s([ver='0.4.0'; if test z$PREDIST = z; then echo $ver; else date +$ver-%s; fi]), [jac@ncgr.org] )

AM_INIT_AUTOMAKE([1.10 -Wall foreign no-define dist-bzip2 no-installinfo no-texinfo.tex])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([ \
Makefile \
src/Makefile \
src/share/Makefile \
src/fqu_are_paired/Makefile \
src/fqu_cat/Makefile \
src/fqu_cull/Makefile \
src/fqu_degen/Makefile \
src/fqu_rselect/Makefile \
src/fqu_splitq/Makefile \
src/fqu_summary/Makefile \
src/fqu_tidy/Makefile \
src/fqu_wc/Makefile \
tests/Makefile
])

AC_CANONICAL_HOST
### AX_PATH_LIB_PCRE
### AX_OPENMP
### CFLAGS="$CFLAGS $OPENMP_CFLAGS"

###AC_ARG_WITH([zlib-prefix],
### AS_HELP_STRING([--with-zlib-prefix=<path>], [Look for zlib includes in <path>/include and libraries in <path>/lib]),
### [zlib_lib=["-L${with_zlib_prefix}/lib"]],
### [LDFLAGS=["-L${with_zlib_prefix}/lib ${LDFLAGS}]" CPPFLAGS=["-I${with_zlib_prefix}/include ${CPPFLAGS}"]]
###)

### FIXME --- add handling for --with-static, --with-static=yes, --with-static=no
AC_ARG_ENABLE([static],
AS_HELP_STRING([--enable-static], [Try to build static binaries.]), [LDFLAGS=["-static ${LDFLAGS}"]], [])

AC_PROG_INSTALL
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])  # workaround autotools inconsistency
AC_PROG_RANLIB
AC_PROG_CC
AC_HEADER_STDC
AC_PROG_CC_STDC
AC_TYPE_SIZE_T

AC_CHECK_LIB([z], [gzbuffer], [], [echo "@<:@1;31m*** FAILED ***@<:@0m Could not locate an appropriate libz; requires at least Zlib 1.2.4. Perhaps you need to specify LDFLAGS?" 2>&1; exit 1])

AC_OUTPUT

printf "\tCPPFLAGS\t%s\n" ${CPPFLAGS}
printf "\tLDFLAGS \t%s\n" ${LDFLAGS}

