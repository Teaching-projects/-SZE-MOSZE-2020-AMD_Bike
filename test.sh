#!/bin/bash
IFS=$'\n'
rm output.txt
cat test/scenarios/preparedgame2.txt | ./main >> output.txt
cat output.txt
DIFF=$(diff output.txt test/outputs/preparedgame2_output.txt) 

if [ "$DIFF" != "" ] 
then
	echo "Not matching"
	exit 1
else
	echo "Matching"
fi