#!/bin/bash
rm textout/*.txt

root -l -q 'selection6Li.C(0)' >> textout/out1.txt 2> textout/err1.txt &
root -l -q 'selection6Li.C(1)' >> textout/out2.txt 2> textout/err2.txt &
root -l -q 'selection6Li.C(2)' >> textout/out3.txt 2> textout/err3.txt &
root -l -q 'selection6Li.C(3)' >> textout/out4.txt 2> textout/err4.txt & 
root -l -q 'selection6Li.C(4)' >> textout/out5.txt 2> textout/err5.txt &
root -l -q 'selection6Li.C(5)' >> textout/out6.txt 2> textout/err6.txt &
root -l -q 'selection6Li.C(6)' >> textout/out7.txt 2> textout/err7.txt 