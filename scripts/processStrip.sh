#! /bin/bash 

# check arguments
if [[ $1 == "" ]]; then
    echo usage: $0 [strip] [makeChain=true/false]
    exit 1
fi
strip=$1

if [[ $2 == "" ]]; then
    makeChain=true
elif [[ $2 == "false" ]]; then
    makeChain=false
elif [[ $2 == "true" ]]; then
    makeChain=false
else
    echo usage: $0 [strip] [makeChain]
    exit 1
fi

# prepare output dirs
dirOut=/alistorage/tofcalib/uTOF/data/uTOFstrip
dirLog=/alistorage/tofcalib/uTOF/log/uTOFstrip
mkdir -p $dirOut
mkdir -p $dirLog

# create chain
chainLis=$dirOut/uTOFtree.chain.list
chainExe="root -b -q /alistorage/tofcalib/tools/chainer.C"
chainOut=$dirOut/uTOFtree.chain.root
chainLog=$dirLog/uTOFtree.chainer.log
if [[ $makeChain == "true" ]]; then
    rm -f $chainLis
    for I in `./processDirectoryDone.sh | grep uTOFtree.root`; do 
	echo $I >> $chainLis 
    done
    $chainExe"(\"$chainLis\", \"uTOFtree\", \"$chainOut\")" &> $chainLog
fi

# process strip
writeExe=/alistorage/tofcalib/uTOF/bin/uTOFstripWriter
writeIn=$chainOut
writeOut=$dirOut/uTOFstrip.$strip.root
writeLog=$dirLog/uTOFstripWriter.$strip.log
$writeExe -s $strip -i $writeIn -o $writeOut &> $writeLog &
