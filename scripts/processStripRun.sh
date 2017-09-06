#! /bin/bash 

# loop over strips
for strip in {0000..1638}; do

    while [ $(ps -ef | grep uTOFstripWriter | grep -v grep | wc -l) -ge 5 ]; do sleep 60s; done

    if [[ $strip == "0000" ]]; then ./processStrip.sh $strip true
    else ./processStrip.sh $strip false
    fi

    sleep 60s

done