#!/bin/bash

ROOTDIR="$(dirname $0)"
FILES=`ls $ROOTDIR/data/rand.*.bin`
MIN_CLUSTER_LENGTHS="1 2 4 8 16 32 64 128 256"

for file in $FILES; do
  echo -n "$file -m"

  for m in $MIN_CLUSTER_LENGTHS; do
    echo -n " $m"

    $ROOTDIR/testbinseq -m $m $file

    if [ "$?" -ne "0" ]; then
      echo " - KO"
      exit 1
    fi
  done

  echo " - OK"
done
