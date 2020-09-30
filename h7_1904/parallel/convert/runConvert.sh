#!/bin/bash

rm textout/*


root -l -q 'convert.C(0)' >> textout/out0.txt 2> textout/err0.txt &
root -l -q 'convert.C(1)' >> textout/out1.txt 2> textout/err1.txt &
root -l -q 'convert.C(2)' >> textout/out2.txt 2> textout/err2.txt &
root -l -q 'convert.C(3)' >> textout/out3.txt 2> textout/err3.txt &
root -l -q 'convert.C(4)' >> textout/out4.txt 2> textout/err4.txt &
root -l -q 'convert.C(5)' >> textout/out5.txt 2> textout/err5.txt &
root -l -q 'convert.C(6)' >> textout/out6.txt 2> textout/err6.txt &
