#!/bin/bash
rm textout/*.txt

root -l -q 'calcEnergies_frame6Li.C(0)' >> textout/out16Li.txt 2> textout/err16Li.txt &
root -l -q 'calcEnergies_frame6Li.C(1)' >> textout/out26Li.txt 2> textout/err26Li.txt &
root -l -q 'calcEnergies_frame6Li.C(2)' >> textout/out36Li.txt 2> textout/err36Li.txt &
root -l -q 'calcEnergies_frame6Li.C(3)' >> textout/out46Li.txt 2> textout/err46Li.txt & 
root -l -q 'calcEnergies_frame6Li.C(4)' >> textout/out56Li.txt 2> textout/err56Li.txt &
root -l -q 'calcEnergies_frame6Li.C(5)' >> textout/out66Li.txt 2> textout/err66Li.txt &
root -l -q 'calcEnergies_frame6Li.C(6)' >> textout/out76Li.txt 2> textout/err76Li.txt 