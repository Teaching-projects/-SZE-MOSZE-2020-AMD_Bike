#!/bin/bash

IFS=$'\n'

./a.out units/Vader.json units/Luke.json >> output.txt
./a.out units/Vader.json units/Yoda.json >> output.txt
./a.out units/Yoda.json units/Luke.json >> output.txt
./a.out units/Yoda.json units/Vader.json >> output.txt
./a.out units/Luke.json units/Yoda.json >> output.txt
./a.out units/Luke.json units/Vader.json >> output.txt

cat output.txt

diff output.txt correct_output.txt

if [ $? -eq 0 ]
then
echo "Matching"
else
echo "Not matching"
fi