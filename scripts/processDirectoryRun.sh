#! /bin/bash

# get directory list
dirList=$(ls /alistorage/tofcalib/trainoutputs/chunk*/*/ -d | grep -v lists)
dirDone=$(./countProcessed.sh | grep uTOFtree.root)

# process all directories
for dir in $dirList; do
    
    # check if already done
    if echo $dirDone | grep $dir &> /dev/null ; then
	continue;
    fi
    
    # sleep for a while if queue is full
    while [ $(ps -ef | grep uTOFwriter | grep -v grep | wc -l) -ge 1 ]; do
        sleep 600s;
    done

    # start process
    ./processDirectory.sh $dir
    sleep 600s;

done