#!/bin/sh

# run ./mkdist.sh RELEASE for a formal release.

if test z$1 = z; then
  PREDIST=1 ./autogen.sh && make distcheck
else
  ./autogen.sh && make distcheck
fi

