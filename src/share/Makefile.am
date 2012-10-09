#NOTE NEXT IS ONLY FOR INSTALLED LIBRARIES
#lib_LIBRARIES = libshare.a

# Define HASH_FUNCTION for uthash.h; all functions seem better than the default JEN
AM_CPPFLAGS = -DHASH_FUNCTION=HASH_SFH

noinst_LIBRARIES = libshare.a
libshare_a_SOURCES = \
  fqreader.c fqreader.h \
  linereader.c linereader.h \
  mkdirp.c mkdirp.h \
  strutils.c strutils.h \
  tokenset.c tokenset.h \
  uthash.h \
  utils.c utils.h \
  varstr.c varstr.h

clean-generic:
	rm -f core core.* a.out *.BAK *.bak *~

