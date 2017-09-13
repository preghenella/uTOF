#! /bin/bash

dirOut=/alistorage/tofcalib/uTOF/data/uTOFstrip
dirLog=/alistorage/tofcalib/uTOF/log/uTOFstrip

totalHits=0
tobeProcessed=0
finishedProcessed=0
for strip in {0000..1637}; do
    ((tobeProcessed++))
    writeLog=$dirLog/uTOFstripWriter.$strip.log
    writeOut=$dirOut/uTOFstrip.$strip.root
    nHits=`grep -s "Final fill" $writeLog | awk {'print $7'}`
    if [[ $nHits == "" ]]; then
	nHits=0
	echo [INCOMPLETE] $writeLog
	./processStrip.sh $strip
	wait
    else
	((finishedProcessed++))
    fi
    totalHits=$((totalHits + nHits))
done

echo "Current status: $finishedProcessed out of $tobeProcessed processes have completed ($((100 * finishedProcessed / tobeProcessed))%)"
echo "Total hits available so far: $totalHits" 