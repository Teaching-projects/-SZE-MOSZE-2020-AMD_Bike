#!/bin/bash
IFS=$'\n'
rm aktoutput.txt
cat test/scenarios/scenario1game.txt | ./main >> aktoutput.txt
DIFF=$(diff aktoutput.txt scenario1game_output.txt) 

if [ "$DIFF" != "" ] 
then
	echo "Not matching"
	exit 1
else
	echo "Matching"
fi