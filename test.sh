#!/bin/bash

IFS=$'\n'

rm output.txt

./main test/units/Vader.json test/units/Luke.json >> output.txt
./main test/units/Vader.json test/units/Yoda.json >> output.txt
./main test/units/Yoda.json test/units/Luke.json >> output.txt
./main test/units/Yoda.json test/units/Vader.json >> output.txt
./main test/units/Luke.json test/units/Yoda.json >> output.txt
./main test/units/Luke.json test/units/Vader.json >> output.txt

cat output.txt
DIFF=$(diff output.txt correct_output.txt) 

if [ "$DIFF" != "" ] 
then
	echo "Not matching"
	exit 1
else
	echo "Matching"
fi