#!/bin/bash

rm err*.txt
rm out*.txt

root -l -q 'convert.C(5)' >> out1.txt 2> err1.txt &
root -l -q 'convert.C(6)' >> out2.txt 2> err2.txt 