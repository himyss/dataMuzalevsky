#!/bin/bash

rm err*.txt
rm out*.txt

root -l -q convert1.C >> out1.txt 2> err1.txt &
root -l -q convert2.C >> out2.txt 2> err2.txt &
root -l -q convert3.C >> out3.txt 2> err3.txt 