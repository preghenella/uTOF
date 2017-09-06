#! /bin/bash

# get directory list
dirList=$(ls /alistorage/tofcalib/trainoutputs/chunk*/*/ -d | grep -v lists)

# clean-up all directories
for dir in $dirList; do
    rm -f $dir/processDirectory.log $dir/chain.list $dir/chain.root $dir/chainer.log $dir/uTOFtree.root $dir/uTOFwriter.log
done
