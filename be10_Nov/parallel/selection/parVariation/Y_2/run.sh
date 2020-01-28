#!/bin/bash
rm textout/*.txt

root -l -q selection1.C >> textout/out1.txt 2> textout/err1.txt &
root -l -q selection2.C >> textout/out2.txt 2> textout/err2.txt &
root -l -q selection.C >> textout/out.txt 2> textout/err.txt 