#!/bin/bash
rm textout/*.txt

root -l -q reco1.C >> textout/out1.txt 2> textout/err1.txt &
root -l -q reco2.C >> textout/out2.txt 2> textout/err2.txt &
root -l -q reco.C >> textout/out.txt 2> textout/err.txt 