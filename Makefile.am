AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

SUBDIRS = src tests
dist_noinst_SCRIPTS = autogen.sh

maintainer-scrub:
	-@rm -f *~ core *.tgz *.tar.gz *.tar.bz2
	-@make maintainer-clean

clean-generic:
	rm -f core core.* a.out *.BAK *.bak *~

predist:
	t=`date +%s`; $(MAKE) VERSION="$(VERSION)-$$t" dist

###t=`date +%s`; $(MAKE) VERSION="$(VERSION)" CPPFLAGS="-DVERSION_QUALIFIER=\"$$t\" $(CPPFLAGS)" dist
