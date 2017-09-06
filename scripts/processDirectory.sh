#! /bin/bash 

# get absolute path
directory=$(readlink -e $1)

# clean up
rm -f $directory/processDirectory.log $directory/chain.root $directory/chainer.log $directory/uTOFwriter.root $directory/uTOFwriter.log
date > $directory/processDirectory.log

# find files and write list 
find $directory -name "TOFcalibTree.root" > $directory/chain.list

# create chain
chainer=/alistorage/tofcalib/tools/chainer.C
root -b -q $chainer"(\"$directory/chain.list\", \"aodTree\", \"$directory/chain.root\")" &> $directory/chainer.log
writer=/alistorage/tofcalib/uTOF/bin/uTOFwriter
$writer -i $directory/chain.root -o $directory/uTOFtree.root &> $directory/uTOFwriter.log &
