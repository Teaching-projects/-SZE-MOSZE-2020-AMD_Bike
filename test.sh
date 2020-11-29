#!/bin/bash
IFS=$'\n'
rm output.txt
cat test/scenarios/scenario1game.txt | ./main >> output.txt

DIFF=$(diff output.txt scenario1game_output.txt) 

if [ "$DIFF" != "" ] 
then
	echo "Not matching"
	exit 1
else
	echo "Matching"
fi