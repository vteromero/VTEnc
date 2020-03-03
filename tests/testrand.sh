#!/bin/bash

ROOTDIR="$(dirname $0)"
FILES=`ls $ROOTDIR/data/rand.*.bin`

for file in $FILES; do
  $ROOTDIR/testbinseq $file

  if [ "$?" -eq "0" ]; then
    echo "$file - OK"
  else
    echo "$file - KO"
    exit 1
  fi
done
