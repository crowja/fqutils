#!/bin/sh

# run ./mkdist.sh RELEASE for a formal release.

if test z$1 = z; then
  PREDIST=1 LDFLAGS=-L/usr/local/lib ./autogen.sh && LDFLAGS=-L/usr/local/lib make distcheck
else
  LDFLAGS=-L/usr/local/lib ./autogen.sh && LDFLAGS=-L/usr/local/lib make distcheck
fi

