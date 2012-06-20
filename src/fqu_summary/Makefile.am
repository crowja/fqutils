bin_PROGRAMS = fqu_summary
AM_CPPFLAGS = -I../share -I../..
LDADD = ../share/libshare.a -lz

fqu_summary_SOURCES = main.c main.h options.c options.h
dist_man1_MANS = fqu_summary.man

indent:
	if test -s main.c; then indent main.c; fi
	if test -s main.h; then indent main.h; fi
	if test -s options.c; then indent options.c; fi
	if test -s options.h; then indent options.h; fi

clean-generic:
	rm -f core core.* a.out *.BAK *.bak *~

