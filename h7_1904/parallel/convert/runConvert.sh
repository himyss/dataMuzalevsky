#!/bin/bash

rm err*.txt
rm out*.txt

root -l -q convert1.C >> out1.txt 2> err1.txt &
root -l -q convert2.C >> out2.txt 2> err2.txt &
root -l -q convert3.C >> out3.txt 2> err3.txt &
root -l -q convert4.C >> out4.txt 2> err4.txt & 
root -l -q convert5.C >> out5.txt 2> err5.txt &
root -l -q convert6.C >> out6.txt 2> err6.txt &
root -l -q convert7.C >> out7.txt 2> err7.txt  