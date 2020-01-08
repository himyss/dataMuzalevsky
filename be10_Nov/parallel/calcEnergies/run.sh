#!/bin/bash
rm textout/*.txt

root -l -q calcEnergies1.C >> textout/out1.txt 2> textout/err1.txt &
root -l -q calcEnergies.C >> textout/out2.txt 2> textout/err2.txt 