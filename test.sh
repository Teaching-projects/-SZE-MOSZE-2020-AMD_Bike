#!/bin/bash

IFS=$'\n'

rm output.txt

./main test/scenarios/scenario1.json >> output.txt

cat output.txt
DIFF=$(diff output.txt scenario1_output.txt) 

if [ "$DIFF" != "" ] 
then
	echo "Not matching"
	exit 1
else
	echo "Matching"
fi