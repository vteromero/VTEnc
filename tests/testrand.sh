#!/bin/bash

FILES=`ls data/rand.*.bin`

for file in $FILES; do
  ./testbinseq $file

  if [ "$?" -eq "0" ]; then
    echo "$file - OK"
  else
    echo "$file - KO"
    exit 1
  fi
done
