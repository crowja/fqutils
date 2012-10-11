#! /bin/bash

tmpfile_fq=`mktemp`
cat in00.fq | ../src/fqu_cat/fqu_cat --squash > $tmpfile_fq
d=`diff expected-fqu_cat-02 $tmpfile_fq`
rm $tmpfile_fq

if test z"$d" != z; then
  exit 1
else
  exit 0
fi
