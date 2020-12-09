#!/bin/bash
rm textout/*.txt

root -l -q 'reco_ect.C(5)' >> textout/outect5.txt 2> textout/errect5.txt &
root -l -q 'reco_ect.C(6)' >> textout/outect6.txt 2> textout/errect6.txt &