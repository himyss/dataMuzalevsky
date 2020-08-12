
  #!/bin/bash

# =============================================================================

# Please specify the path to a directory which contains _ONLY_ the files you want to analyse
# You should not put the trailing slash sign (but actually if you will, it should not affect the result...)
# You need to have write access to this directory
INPUTLMDDIR=/mnt/analysis_nas/exp201904/raw/h7

if [ ! -d "${INPUTLMDDIR}" ]; then
  echo -e "Directory ${INPUTLMDDIR} does not exist. Aborting."
  exit;
fi

# Please specify the path to the output directory where the resulting root files will be written
OUTPUTROOTDIR=/mnt/analysis_nas/exp201904/beamDiagnostics

# TODO check that ${OUTPUTROOTDIR} exists ???

# Please specify the input XML configuration file
SETUPFILE=/mnt/analysis_nas/exp201904/setupEXP1904.xml

# TODO check that ${SETUPFILE} exists

# Please specify how many threads do you want to occupy
NTHREADS=16

# Please specify the prefix for the generated lml files
# In principle, there are no constraints, but you may want to keep it the same as the directory name

PREFIX=h7_ct

# FILES=${INPUTLMDDIR}/${PREFIX}*.lmd
# =============================================================================

rm ${OUTPUTROOTDIR}/*.txt

for (( i=0; i <=66; i++ ))
do

echo "run $i" 
echo 
#i=1
  if [ $i -lt 10 ]; then
    FILES=${INPUTLMDDIR}/${PREFIX}_0$i*.root
    RUN=${PREFIX}_0$i
  fi

  if [ $i -gt 9 ]; then
    FILES=${INPUTLMDDIR}/${PREFIX}_$i*.root
    RUN=${PREFIX}_$i
  fi  

  #FILES=${INPUTLMDDIR}/${PREFIX}*.lmd
  #echo $FILES

  # Count input data files
  NFILES=`ls -1q ${FILES} | wc -l`
  echo $NFILES  
  echo $NTHREADS   

  # Continue, of there are no files for certain run
  if [ $NFILES -eq 0 ] 
  then
  continue
  fi

  let iFile=1 #number of the file in the cirtain run
  let iThread=1 #number of the thread
  for FILE in ${FILES}
  do

    TEXTOUTFILE=${OUTPUTROOTDIR}/${RUN}_${iFile}_out.txt
    TEXTERRFILE=${OUTPUTROOTDIR}/${RUN}_${iFile}_err.txt  # Default: textoutput/err.txt
    OUTFILENAME=${OUTPUTROOTDIR}/${RUN}_${iFile}_digi.root


    echo $FILE $iFile $iThread

    if [ $iFile -eq $NFILES ]; then
      echo "	Processing run $i, file $iFile Last file, finish"
      

      echo $OUTFILENAME   
      echo $FILE

      root -l -q "digibuilder.C(\"${FILE}\",\"${OUTFILENAME}\")" >> ${TEXTOUTFILE} 2> ${TEXTERRFILE} &

      echo -e "\e[1m\e[32mWaiting for all threads to finish\e[0m"
      wait

      break
      #root -l -q "parallelDigi.C($run, $j, 0)" >> out.txt 2> err.txt 
    fi

    if [ $iThread -eq $NTHREADS ]; then
      echo "	Processing run $i, file $iFile Busy, pause"

      echo $OUTFILENAME   
      echo $FILE

      root -l -q "digibuilder.C(\"${FILE}\",\"${OUTFILENAME}\")" >> ${TEXTOUTFILE} 2> ${TEXTERRFILE} &

      echo -e "\e[1m\e[32mWaiting for all threads to finish\e[0m"
      wait
      
      let iThread=1
      let iFile++
      continue
    fi

    if [[ $iThread -lt $NTHREADS && $iFile -lt $NFILES ]]; then
      echo "	Processing run $i, file $iFile"

      echo $OUTFILENAME   
      echo $FILE

      root -l -q "digibuilder.C(\"${FILE}\",\"${OUTFILENAME}\")" >> ${TEXTOUTFILE} 2> ${TEXTERRFILE} &

      let iThread++
      let iFile++
      continue
    fi
	  
  done

done

# ELAPSED_TIME=$(($SECONDS - $START_TIME))
# echo "Elapsed time: $ELELAPSED_TIME" 
# echo "$(($ELAPSED_TIME/60)) min $(($ELAPSED_TIME%60)) sec"

exit
