#!/bin/bash
rm textout/*.txt

root -l -q 'reco6Li.C(0)' >> textout/out6Li1.txt 2> textout/err6Li1.txt &
root -l -q 'reco6Li.C(1)' >> textout/out6Li2.txt 2> textout/err6Li2.txt &
root -l -q 'reco6Li.C(2)' >> textout/out6Li3.txt 2> textout/err6Li3.txt &
root -l -q 'reco6Li.C(3)' >> textout/out6Li4.txt 2> textout/err6Li4.txt & 
root -l -q 'reco6Li.C(4)' >> textout/out6Li5.txt 2> textout/err6Li5.txt &
root -l -q 'reco6Li.C(5)' >> textout/out6Li6.txt 2> textout/err6Li6.txt &
root -l -q 'reco6Li.C(6)' >> textout/out6Li7.txt 2> textout/err6Li7.txt 