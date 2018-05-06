#include <TSystem.h>
#include <iostream>

using namespace std;

void findPeaks()
{
	gSystem->Load("/home/muzalevsky/AculUti/libAculData.so");
	gSystem->Load("/home/muzalevsky/AculUti/libTELoss.so");

	AculCalibration cal;
	cal.SetWorkDirectory("/home/muzalevsky/work/dataMuzalevsky/exp201803/data/");
	cal.SetParFileName("/home/muzalevsky/work/dataMuzalevsky/exp201803/calib/parforcal.par");	
	cal.SetInputRootFile("/media/analysis_nas/exp201803/rootfiles/csi_l_0002.root");
	cal.Init();	//takes parameters from .par
	cal.PrintInputParameters();

 	cal.FindPedestals(0, 50);
	cal.FindEnergyPedestals();
	cal.Mycalc(130, 350);
	//cal.FindEnergyPedestals();
	cal.ShowFullCalibratedSpectra(0, 4095);

}


