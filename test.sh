#!/bin/bash

IFS=$'\n'

rm output.txt

./a.out units/Vader.json units/Luke.json >> output.txt
./a.out units/Vader.json units/Yoda.json >> output.txt
./a.out units/Yoda.json units/Luke.json >> output.txt
./a.out units/Yoda.json units/Vader.json >> output.txt
./a.out units/Luke.json units/Yoda.json >> output.txt
./a.out units/Luke.json units/Vader.json >> output.txt

cat output.txt
DIFF=$(diff output.txt correct_output.txt) 

if [ "$DIFF" != "" ] 
then
echo "Not matching"
else
echo "Matching"
fi