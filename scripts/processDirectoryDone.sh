#! /bin/bash

totalHits=0
tobeProcessed=0
finishedProcessed=0
for I in `ls /alistorage/tofcalib/trainoutputs/chunk*/*/ -d | grep -v lists`; do
    ((tobeProcessed++))
    nHits=`grep -s "Final fill" $I/uTOFwriter.log | awk {'print $7'}`
    if [[ $nHits == "" ]]; then
	nHits=0
    else
	((finishedProcessed++))
	echo $I/uTOFtree.root
    fi
    totalHits=$((totalHits + nHits))
done

echo "Current status: $finishedProcessed out of $tobeProcessed processes have completed ($((100 * finishedProcessed / tobeProcessed))%)"
echo "Total hits available so far: $totalHits" 