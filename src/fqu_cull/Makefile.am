bin_PROGRAMS = fqu_cull
#AM_CPPFLAGS = -I../share -I../.. 
AM_CPPFLAGS = -I$(top_srcdir)/src/share
LDADD = ../share/libshare.a

fqu_cull_SOURCES = main.c main.h options.c options.h
dist_man1_MANS = fqu_cull.man

indent:
	if test -s main.c; then indent main.c; fi
	if test -s main.h; then indent main.h; fi
	if test -s options.c; then indent options.c; fi
	if test -s options.h; then indent options.h; fi

clean-generic:
	rm -f core core.* a.out *.BAK *.bak *~

