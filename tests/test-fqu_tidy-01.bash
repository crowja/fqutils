#! /bin/bash

tmpfile_fq=`mktemp`
cat in00.fq | ../src/fqu_tidy/fqu_tidy > $tmpfile_fq
d=`diff expected-fqu_tidy-01 $tmpfile_fq`
rm $tmpfile_fq

if test z"$z" != z; then
  exit 1
else
  exit 0
fi
