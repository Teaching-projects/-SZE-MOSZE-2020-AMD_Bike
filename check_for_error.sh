#!/bin/bash
if grep --quiet "error" "./test/outputs/cppcheck_output.txt"
then exit 1
fi