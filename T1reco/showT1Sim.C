#include "TLine.h"
#include "TPad.h"

void showT1Sim()
{
//	TFile *fr = new TFile("output.root", "READ");
//	TTree *tr = (TTree*)fr->Get("out");
//	tr->AddFriend("er", "full.root");

//	TFile *fr = new TFile("full.root", "READ");
	TFile *fr = new TFile("sim_digi.root", "READ");
	TTree *tr = (TTree*)fr->Get("er");

	TCanvas *c3 = new TCanvas("c3", "Telescope info", 1200, 800);
	c3->Divide(3,2);

	c3->cd(1);
	tr->Draw("(MCTrack.fEnergy - MCTrack.fMass)*1000", "MCTrack.fPdgCode == 1000020060");

	c3->cd(2);
	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000",
			"ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000<6 && ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000<70","");

	c3->cd(3);
	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeY:ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeX", "", "col");

	c3->cd(4);
	tr->Draw("(MCTrack.fEnergy - MCTrack.fMass)*1000", "MCTrack.fPdgCode == 1000010010");
	tr->Draw("(MCTrack.fEnergy - MCTrack.fMass)*1000", "MCTrack.fPdgCode == 2212");


	c3->cd(5);
	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000","","col");


	c3->cd(6);
	tr->Draw("ERQTelescopeSiPoint_DoubleSi_SD2_XY_1_X.fY:ERQTelescopeSiPoint_DoubleSi_SD2_XY_1_X.fX", "", "col");

}
