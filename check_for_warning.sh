#!/bin/bash
if grep --quiet "warning" "./test/outputs/cppcheck_output.txt"
then exit 1
fi