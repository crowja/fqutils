AC_PREREQ([2.59])

AC_INIT([MY_PACKAGE_NAME], [0.0.0], [jac@ncgr.org])
AM_INIT_AUTOMAKE([1.10 -Wall foreign no-define dist-bzip2 no-installinfo no-texinfo.tex])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([ \
Makefile \
src/Makefile \
src/share/Makefile \
src/fqu_cat/Makefile \
src/fqu_cull/Makefile \
src/fqu_is_paired/Makefile \
src/fqu_summary/Makefile \
src/fqu_tidy/Makefile \
tests/Makefile
])

AC_CANONICAL_HOST

AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_CC

AC_CHECK_LIB([z], [gzbuffer], [], [echo "@<:@1;31m*** FAILED ***@<:@0m Could not locate an appropriate zlib." 2>&1; exit 1])

AC_OUTPUT

