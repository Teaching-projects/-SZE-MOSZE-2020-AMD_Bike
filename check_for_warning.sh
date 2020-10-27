#!/bin/bash
if grep --quiet "warning" "./cppcheck_output.txt"
then exit 1
fi