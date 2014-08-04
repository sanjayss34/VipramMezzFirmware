#!/bin/bash

rm logfile100MHz2.log
echo "Starting test:"

rowaddr=0
while [ $rowaddr -lt 128 ];
do
timestamp=$(date +%T)
echo $timestamp
echo $timestamp >> logfile100MHz2.log
echo "----Testing Row $rowaddr"
python loadAllRandom.py $rowaddr --go | grep 'match\|Testing Row\|shift\|Loaded\|number of hits'| tee -a logfile100MHz2.log
rowaddr=$[$rowaddr+4]
sleep 1s 
done
