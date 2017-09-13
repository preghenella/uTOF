#! /bin/bash

dirOut=/alistorage/tofcalib/uTOF/data/uTOFstrip
dirLog=/alistorage/tofcalib/uTOF/log/uTOFstrip

for strip in {0000..1637}; do

    writeLog=$dirLog/uTOFstripWriter.$strip.log
    writeOut=$dirOut/uTOFstrip.$strip.root
    nHits=`grep -s "Final fill" $writeLog | awk {'print $7'}`
    if [[ $nHits == "" ]]; then
	nHits=0
	echo [INCOMPLETE] $writeLog
	while [ $(ps -ef | grep uTOFstripWriter | grep -v grep | wc -l) -ge 3 ]; do sleep 60s; done
	./processStrip.sh $strip
    fi
done

