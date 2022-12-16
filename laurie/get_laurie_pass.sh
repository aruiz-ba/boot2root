#!/bin/sh

number=1
while [ $number -lt 7 ]
do
getme=$(grep "getme$number(" *.pcap | grep -v BJPCP.pcap | awk -F ':' '{ print $1 }')
getme_num=$(cat $getme | grep // | awk -F '//file' '{ print $2 }')
cat $(grep "//file$((getme_num + 1))$" *pcap | awk -F ':' '{ print $1 }') | grep return | awk -F "'" '{ print $2 }' | tr '\n' ' ' | tr -d "[:space:]"
number=$((number + 1))
done

grep -v "useless" *.pcap | grep -v "Got you" | grep return | grep BJPCP.pcap | awk -F "'" '{ print $2 }' | tr '\n' ' ' | tr -d "[:space:]"
