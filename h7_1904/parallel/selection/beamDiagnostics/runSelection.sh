#!/bin/bash
rm textout/*.txt

root -l -q 'selection.C(0,557841)' >> textout/out1.txt 2> textout/err1.txt &
root -l -q 'selection.C(1,1115486)' >> textout/out2.txt 2> textout/err2.txt &
root -l -q 'selection.C(2,530522)' >> textout/out3.txt 2> textout/err3.txt &
root -l -q 'selection.C(3,543126)' >> textout/out4.txt 2> textout/err4.txt & 
root -l -q 'selection.C(4,498886)' >> textout/out5.txt 2> textout/err5.txt &
root -l -q 'selection.C(5,26445)' >> textout/out6.txt 2> textout/err6.txt &
root -l -q 'selection.C(6,161880)' >> textout/out7.txt 2> textout/err7.txt 