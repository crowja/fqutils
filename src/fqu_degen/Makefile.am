bin_PROGRAMS = fqu_degen
###AM_CPPFLAGS = -I../share -I../.. -I$(top_srcdir)/src/share
AM_CPPFLAGS = -I$(top_srcdir)/src/share
LDADD = ../share/libshare.a
.PHONY: indent strict

fqu_degen_SOURCES = main.c main.h options.c options.h
dist_man1_MANS = fqu_degen.man

indent:
	if test -s main.c; then indent main.c; fi
	if test -s main.h; then indent main.h; fi
	if test -s options.c; then indent options.c; fi
	if test -s options.h; then indent options.h; fi

clean-generic:
	rm -f core core.* a.out *.BAK *.bak *~

strict:
	make clean; make CFLAGS="-pedantic -ansi -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations $(CFLAGS)"



