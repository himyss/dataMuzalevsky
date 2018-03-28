#include "TLine.h"
#include "TPad.h"
#include "TCutG.h"

void showT1Sim()
{

	TFile *fc = new TFile("cut.root", "READ");
	TCutG *cHe = (TCutG*)fc->Get("cut3He");

	TFile *fcPos = new TFile("cutsPos.root", "READ");
	TCutG *c3He = (TCutG*)fcPos->Get("c3HePos");
	TCutG *c6He = (TCutG*)fcPos->Get("c6HePos");

	TFile *fr = new TFile("sim_digi.root", "READ");
	TTree *tr = (TTree*)fr->Get("er");
	tr->AddFriend("out", "output.root");



	TCanvas *c3 = new TCanvas("c3", "Telescope info", 1200, 800);
	c3->Divide(3,2);

	c3->cd(1);
//	tr->Draw("(MCTrack.fEnergy - MCTrack.fMass)*1000", "MCTrack.fPdgCode == 1000020060");
	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000",
			"ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000<6 && ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000<70","");
	cHe->Draw("same");

	c3->cd(2);
//	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000",
//			"ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000<6 && ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000<70","");
//	cHe->Draw("same");
	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeY:ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeX", "cut3He", "col");

	c3->cd(3);
	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeY:ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeX", "", "col");
	c3He->SetLineWidth(3);
	c3He->SetLineColor(kRed);
	c3He->Draw("same");
	c6He->Draw("same");
	c6He->SetLineWidth(3);
	c6He->SetLineColor(kGreen);


	c3->cd(4);
	tr->Draw("(MCTrack.fEnergy - MCTrack.fMass)*1000", "MCTrack.fPdgCode == 1000010010");
	tr->Draw("(MCTrack.fEnergy - MCTrack.fMass)*1000", "MCTrack.fPdgCode == 2212");
	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000",
			"ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000<6 && ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000<70","");
	cHe->Draw("same");
	tr->SetMarkerColor(kRed);
	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000",
			"ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000<6 "
			"&& ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000<70 "
			"&& cut3He","same");


	c3->cd(5);
	tr->Draw("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X.fEdep*1000:ERQTelescopeSiDigi_DoubleSi_SD2_XY_1_X.fEdep*1000","","col");


	c3->cd(6);
	tr->Draw("ERQTelescopeSiPoint_DoubleSi_SD2_XY_1_X.fY:ERQTelescopeSiPoint_DoubleSi_SD2_XY_1_X.fX", "", "col");

//	return;

	TCanvas *c1 = new TCanvas("c1", "Telescope info", 1200, 800);
	c1->Divide(3,2);

	c1->cd(1);
	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeY:ERQTelescopeTrack_DoubleSi_SD2_XY_1.fTelescopeX", "", "col");
	c3He->Draw("same");

	c1->cd(2);
//	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fVectorOnTarget.fY:ERQTelescopeTrack_DoubleSi_SD2_XY_1.fVectorOnTarget.fX", "", "col");
	tr->Draw("energy", "energy>0");


	c1->cd(3);
	//	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fVectorOnTarget.fY:ERQTelescopeTrack_DoubleSi_SD2_XY_1.fVectorOnTarget.fX", "", "col");
	tr->Draw("energy*1000", "energy>0 && cut3He");

	c1->cd(4);
	tr->Draw("particle.Theta()*TMath::RadToDeg()", "");
	tr->Draw("particle.Phi()*TMath::RadToDeg()", "");
	tr->Draw("particle.Theta()*TMath::RadToDeg():particle.Phi()*TMath::RadToDeg()", "");
	tr->Draw("particle.fP.fY:particle.fP.fX", "");
	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fSumEdep*1000", "cut3He", "");
//	tr->Draw("ERQTelescopeTrack_DoubleSi_SD2_XY_1.fSumEdep*1000", "cut3He && ERQTelescopeTrack_DoubleSi_SD2_XY_1.GetEntriesFast()", "");


	c1->cd(6);
//	tr->Draw("MCTrack.fEnergy*0.001", "MCTrack.fPdgCode == 1000020030");
	tr->Draw("MCTrack.fEnergy*1000-2809", "MCTrack.fPdgCode == 1000020030");
	tr->Draw("MCTrack.fEnergy*1000-2809", "MCTrack.fPdgCode == 1000020030 && ERQTelescopeTrack_DoubleSi_SD2_XY_1.fSumEdep");
//	tr->Draw("MCTrack.fEnergy*1000-2809", "MCTrack.fPdgCode == 1000020030 && ");


	c1->cd(5);
	tr->Draw("MCTrack.fEnergy*1000-2809 - energy*1000", "energy>0 && cut3He");
	tr->Draw("MCTrack.fEnergy*1000-2809", "MCTrack.fPdgCode == 1000020030");
	tr->Draw("MCTrack.fEnergy*1000-2809 - ERQTelescopeTrack_DoubleSi_SD2_XY_1.fSumEdep*1000", "cut3He && MCTrack.fPdgCode == 1000020030");
//	tr->Draw("MCTrack.fEnergy*1000-2809 - ERQTelescopeTrack_DoubleSi_SD2_XY_1.fSumEdep*1000", "cut3He ");
//	tr->Draw("energy*1000 - ERQTelescopeTrack_DoubleSi_SD2_XY_1.fSumEdep*1000", "cut3He");


}
