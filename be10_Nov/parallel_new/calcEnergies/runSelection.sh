#!/bin/bash

if [ -z ${ROOTSYS+x} ]; then
  echo "ROOTSYS is unset. Aborting.";
  exit;
else
  echo "ROOTSYS is set to '$ROOTSYS'";
fi

# =============================================================================

# Please specify the path to a directory which contains _ONLY_ the files you want to analyse
# You should not put the trailing slash sign (but actually if you will, it should not affect the result...)
# You need to have write access to this directory
INPUTLMDDIR=/media/ivan/data/exp1906/analysed/selected

if [ ! -d "${INPUTLMDDIR}" ]; then
  echo -e "Directory ${INPUTLMDDIR} does not exist. Aborting."
  exit;
fi

# Please specify the path to the output directory where the resulting root files will be written
OUTPUTROOTDIR=/media/ivan/data/exp1906/analysed/calcEnergies

# TODO check that ${SETUPFILE} exists

# Please specify how many threads do you want to occupy
NTHREADS=4

# Please specify the prefix for the generated lml files
# In principle, there are no constraints, but you may want to keep it the same as the directory name

PREFIX=be10_ect

FILES=${INPUTLMDDIR}/${PREFIX}*.root

# Remove textual output if it already exists from previous analysis runs
if [ -d ${OUTPUTROOTDIR}/textoutput/ ]; then
  rm -fv ${OUTPUTROOTDIR}/textoutput/*.txt
else
  mkdir ${OUTPUTROOTDIR}/textoutput
fi

# =============================================================================

#NAMES=${FILES}-${INPUTLMDDIR}

echo "before read"

# Count input data files
NFILES=`ls -1q ${FILES} | wc -l`

echo "nFiles=${NFILES}"
echo "nThreads=${NTHREADS}"

echo "files read"

  #let IBATCH=1
let iFile=0

for INPUTFILENAME in ${FILES}
do
  NAME=$(basename "$INPUTFILENAME")
  OUTPUTFILENAME=${NAME//.digi.root/.cal.root}
  OUTPUTFILENAME=${OUTPUTROOTDIR}/${OUTPUTFILENAME}

  TEXTERRFILE=${OUTPUTROOTDIR}/textoutput/${NAME}_err.txt  # Default: textoutput/err.txt
  TEXTOUTFILE=${OUTPUTROOTDIR}/textoutput/${NAME}_out.txt  # Default: textoutput/out.txt # No reason to suppres

  # Remove output file if it already exists from previous analysis runs
  # if [ -f $OUTPUTFILENAME ]; then
  #   rm ${OUTPUTFILENAME}
  # fi

  if [ $iFile -eq $NTHREADS ]; then
    echo -e "\e[1;32;1mWaiting for all threads to finish\e[0m"
    wait
    let iFile=0
  fi
  
  if [ $iFile -lt $NTHREADS ]; then

    ANARUNINFO="========================== ANALYSIS RUN INFO ===================================
    Current date and time                      ${DATETIME}
    Processing input file                      ${INPUTFILENAME}
    into output file                           ${OUTPUTFILENAME}
    Text output file:                          ${TEXTOUTFILE}
    Text error file:                           ${TEXTERRFILE}
    ============================================================================================"

# Starting outoutfile with ANARUNINFO 
cat > ${TEXTOUTFILE} << EOF
${ANARUNINFO}
EOF

    echo -e "\e[1m\e[34m${ANARUNINFO}\e[0m"

    echo -e "\e[1m\e[32m"`date` "Analysis started.\e[0m"

    root -l -q 'calcEnergies_ect.C('\"$INPUTFILENAME\"','\"$OUTPUTFILENAME\"')' >> ${TEXTOUTFILE} 2> ${TEXTERRFILE} &

    let iFile++
  fi
done

echo -e "\e[1m\e[32m"`date` "Analysis finished.\e[0m"
