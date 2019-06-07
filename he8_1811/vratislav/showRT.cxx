#if !defined(__CLING__)


//#include "../install/include/conversion/ConvertRepackedToCalibrated.h"
//#include "../install/include/data/DetEventCommon.h"
#include "TFile.h"
//#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLine.h"
#include "TMarker.h"
#include "TLegend.h"
#include "TLegendEntry.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"


#include <iostream>

using std::cout;
using std::endl;

#endif

#include "cutsRTY.cxx"
#include "cutsRT20X.cxx"
#include "cutsHelium3.cxx"
//#include "cutsHelium3false.cxx"
//#include "cutsHelium4.cxx"
//#include "cutsTritium.cxx"
#include "cutsTritiumCal.cxx"
#include "cutsCsIcal.cxx"

//first layer
TString RT20X = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0";
//second layer
TString RTY = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0";
//third layer
TString RT3rd = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0";

TString TOF2 = "BeamDetToFDigi2.fTime";

	//trigger==2: Left telescope
	//trigger==3: Right telescope


TChain *tr;
TChain *trIn;

TMarker *mP[3][4];  //[energies][particles], energies: 10, 20, 30 MeV, particles: 3,4,6,8He
TMarker *mPcorrected[16][3][4]; //the same but for different strips

//const Int_t showNoStrips = 12;

//auxiliary variables
TString var;
TString con;

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0);
void InitMarkers();
void InitCorrectedMarkers();
void InitExternalCuts();
TString MakeGeneralTritiumCut();

void DrawThinRMults(const Long64_t lowStatEntries = 100000);
void DrawThickRMults(const Long64_t lowStatEntries = 100000);
void DrawIDplotVeto();
void DrawIDplotVetoTargetSelection();
void DrawTauAmpR(const Bool_t firstLayer = 1,
		const Bool_t seconLayer = 1, const Bool_t makeCuts = 0);
void DrawIDplotThinR();
void DrawIDplotThinRtargetSelection(const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawIDplotTargetSelCorrected (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawCheckCorrection (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0);
void DrawCheckIDplotInPixels (const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0);
void DrawIDplotCorrectedForHeCuts (const Int_t showNoStrips = 16,
		Int_t firstStrip = 0, const Bool_t logZ = 0, Bool_t makeCuts = 0);
void DrawC11(const Bool_t logZ = 0);
void DrawIDplotCorrectedTimeCuts (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawIDplotCorrectedTimeCuts2 (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawIDplotCorrectedTimeCuts3 (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawIDplotCorrectedWithCuts (const Int_t showNoStrips = 16,
		Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawIDplotCorrectedWithCuts2 (const Int_t showNoStrips = 16,
		Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawIDplotCorrectedWithCutsFinal (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, const Bool_t logZ = 0);
void DrawHeEnergyLABWithCutsFinal(const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, const Bool_t logZ = 0);


//global conditions:
TString targetCondition;
TString timeCondY;
TString MWPCtimeCondition;
TString beamIdCondition;

TString genCon;
const Double_t m3He = 2808.391;
const Double_t cut3HeEnergy = 30.;

void showRT(const Bool_t allStat = 1) {

	genCon =
			MakeGeneralTritiumCut() + " && "
			//			MakeGeneralDeuteriumCut() + " && "
			+ Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);

	const Bool_t showViewer = 0;

//	InitTrees(allStat);
	InitTrees(allStat, 1);

	InitMarkers();


	InitExternalCuts();

	InitCorrectedMarkers();

	if (showViewer) tr->StartViewer();

//	DrawThinRMults();
//	DrawThickRMults();					//todo: try to find criterion for multiplicity
//	DrawIDplotVeto();
//	DrawIDplotVetoTargetSelection();
//	DrawTauAmpR(1,0);					//ok
	DrawTauAmpR(0,1);					//ok
//	DrawTauAmpR(1,0,1);
//	DrawIDplotThinR();					//ok
//	DrawIDplotThinRtargetSelection(12,0);
//	DrawIDplotTargetSelCorrected();
//	DrawIDplotTargetSelCorrected(4,5);
	//	DrawCheckCorrection();
//	DrawCheckIDplotInPixels();
//	DrawIDplotCorrectedForHeCuts(16, 0, 0, 1);		//ok
//	DrawIDplotCorrectedForHeCuts(4, 0, 0);
//	DrawIDplotCorrectedForHeCuts(12, 0, 0);
//	DrawC11();										//probably not needed
//	DrawIDplotCorrectedTimeCuts(4,2);
//	DrawIDplotCorrectedTimeCuts2(4,2);
//	DrawIDplotCorrectedTimeCuts3(4,2);
//	DrawIDplotCorrectedWithCuts(12);
//	DrawIDplotCorrectedWithCuts2(4,0);
//	DrawIDplotCorrectedWithCutsFinal(4,12);
//	DrawIDplotCorrectedWithCutsFinal(16,0);
//	DrawHeEnergyLABWithCutsFinal(16);

	return;
}

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0) {
	TString inFile;
	const Int_t run = 7;
	const Int_t noFiles = 22;
//	const Int_t noFiles = 7;

//	TString	inPath = "~/data/exp1811/calibrated_filtered/reco/";
//	TString	inPath = "~/data/exp1811/calibrated_filtered_CsI/reco/";
//	TString	inPath = "~/data/exp1811/calibrated_filtered_CsI/reco_6H/";
	TString	inPath = "~/data/exp1811/calibrated_filtered_CsI_both/reco/";

	tr = new TChain("reco");
	if (!background) {
		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.reco.root", inPath.Data(), run, i);
			tr->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_%02d_*", inPath.Data(), 8);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 9);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 10);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 11);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 12);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 13);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 14);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 15);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 16);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 17);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 18);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 19);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 20);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 21);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 22);
			tr->Add(inFile.Data());
		}

//		inPath = "~/data/exp1811/calibrated_filtered/";
//		inPath = "~/data/exp1811/calibrated_filtered_CsI/";
		inPath = "~/data/exp1811/calibrated_filtered_CsI_both/";
		trIn = new TChain("er");
		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.Digi.root", inPath.Data(), run, i);
			trIn->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_%02d_*", inPath.Data(), 8);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 9);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 10);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 11);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 12);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 13);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 14);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 15);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 16);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 17);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 18);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 19);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 20);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 21);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 22);
			trIn->Add(inFile.Data());
		}
	}//if target filled

	if (background) {

//		inPath = "~/data/exp1811/calibrated_filtered/background_filtered/reco/";
//		inPath = "~/data/exp1811/calibrated_filtered_CsI/background/reco/";
		inPath = "~/data/exp1811/calibrated_filtered_CsI_both/background_reco/";

		for (Int_t i = 1; i <= 18; i++) {
			inFile.Form("%she8_empty_target_%02d_%04d.reco.root", inPath.Data(), 29, i);
			tr->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 24);
			cout << inFile << endl;
			tr->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 25);
			tr->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 26);
			tr->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 27);
			tr->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 28);
			tr->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 30);
			tr->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 31);
			tr->Add(inFile.Data());
		}

		trIn = new TChain("er");
//		inPath = "~/data/exp1811/calibrated_filtered/background_filtered/";
//		inPath = "~/data/exp1811/calibrated_filtered_CsI/background/";
		inPath = "~/data/exp1811/calibrated_filtered_CsI_both/background/";


		for (Int_t i = 1; i <= 18; i++) {
			inFile.Form("%she8_empty_target_%02d_%04d.Digi.root", inPath.Data(), 29, i);
			trIn->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 24);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 25);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 26);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 27);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 28);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 30);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_empty_target_%02d_*", inPath.Data(), 31);
			trIn->Add(inFile.Data());
		}
	}//if background measurement

	tr->AddFriend(trIn);
	tr->SetMarkerStyle(20);
	tr->SetMarkerSize(0.1);
//	tr->SetMarkerSize(0.7);

}

void InitMarkers() {

	//markers calculated using LISE++
	//Y: energy deposit in 20 microns of Si
	//X: energy deposit in thick Si

	//todo: real normalization is set for 23 microns
	//it means that we have only 20 microns of sensitive
	//layer from 23 mcm and the rest is probably the sum
	//of dead layers (their location was not analysed yet)

	mP[0][0] = new TMarker(8.3988, 1.6012, 20);
	mP[0][1] = new TMarker(8.0198, 1.9802, 20);
	mP[0][2] = new TMarker(7.3376, 2.6624, 20);
	mP[0][3] = new TMarker(6.7503, 3.2497, 20);

	mP[1][0] = new TMarker(19.08, 0.91957, 20);
	mP[1][1] = new TMarker(18.861, 1.1387, 20);
	mP[1][2] = new TMarker(18.445, 1.5546, 20);
	mP[1][3] = new TMarker(18.089, 1.9113, 20);

	mP[2][0] = new TMarker(29.329, 0.67113, 20);
	mP[2][1] = new TMarker(29.168, 0.83237, 20);
	mP[2][2] = new TMarker(28.869, 1.1315, 20);
	mP[2][3] = new TMarker(28.586, 1.4136, 20);

	for (Int_t e = 0; e < 3; e++) {
		for (Int_t p = 0; p < 4; p++) {
			mP[e][p]->SetMarkerSize(0.8);
			mP[e][p]->SetMarkerColor(kRed);
		}
	}


}

void InitCorrectedMarkers() {

	Double_t correction[16] = {1.125, 1.112, 1., 0.947,
								1., 1.08, 1.048, 1.07,
								1.15, 0.77, 1.10, 0.98,
								0.92, 1., 1.25, 1.15};

	for (Int_t s = 0; s < 16; s++) {
		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
//				mPcorrected[s][e][p]->Copy(*mPin[e][p]);
//				mPin[e][p]->Copy(*mPcorrected[s][e][p]);
				mPcorrected[s][e][p] = new TMarker(*mP[e][p]);
				mPcorrected[s][e][p]->SetMarkerSize(0.8);
				mPcorrected[s][e][p]->SetMarkerColor(kBlue);
//				mPcorrected[s][e][p]->SetMarkerColor(kMagenta);

				mPcorrected[s][e][p]->SetY(correction[s]*mP[e][p]->GetY());

			}//for particle
		}//for energy
	}//for strip


}

void InitExternalCuts() {
	const Bool_t useFirstLayerCuts = 1;
	const Bool_t useSecondLayerCuts = 1;
	const Bool_t useHeliumCuts = 1;
	const Bool_t useTritiumCuts = 1;
	const Bool_t useCsIcuts = 1;

	if (useSecondLayerCuts) {
		cutsRT20X();
	}

	if (useSecondLayerCuts) {
		cutsRTY();
	}

	if (useHeliumCuts) {
		cutsHelium3();
	}

	if (useTritiumCuts) {
		cutsTritium();
	}

	if (useCsIcuts) {
		cutsCsI();
	}

	//time condition for Y strips from cutsRTY()
	timeCondY.Form("(cutRTY_0 || cutRTY_1 || cutRTY_2 || cutRTY_3"
			" || cutRTY_4 || cutRTY_5 || cutRTY_6 || cutRTY_7"
			" || cutRTY_8 || cutRTY_9 || cutRTY_10 || cutRTY_11"
			" || cutRTY_12 || cutRTY_13 || cutRTY_14 || cutRTY_15)");

	//condition on position in the center of the target
	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";

	//time in MWPC's
	TString MWPCX1 = "BeamDetMWPCDigiX1";
	TString MWPCY1 = "BeamDetMWPCDigiY1";
	TString MWPCX2 = "BeamDetMWPCDigiX2";
	TString MWPCY2 = "BeamDetMWPCDigiY2";

	MWPCtimeCondition.Form("(%s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95. "
			"&& %s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95. "
			"&& %s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95. "
			"&& %s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95.)",
			MWPCX1.Data(), MWPCX1.Data(),
			MWPCY1.Data(), MWPCY1.Data(),
			MWPCX2.Data(), MWPCX2.Data(),
			MWPCY2.Data(), MWPCY2.Data()
	);

	//8He cut
	beamIdCondition = "BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >200."
				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 240."
				" && BeamDetToFDigi2.fEdep>2600."
				" && BeamDetToFDigi2.fEdep<4300.";
}

TString MakeGeneralTritiumCut() {

	TString cut;

	cutsTritium();

	//for 16 crystals except No.9
	cut.Form(" (%s", cTritium[0]->GetName());
	for (Int_t i = 1; i < 16; i++) {
		if (i==9) continue;
		cut.Append(" || " + (TString)cTritium[i]->GetName());
	}
	cut.Append(")");

	TString timeCondCsI;
	timeCondCsI.Form("(cutCsI_0 || cutCsI_1 || cutCsI_2 || cutCsI_3"
			" || cutCsI_4 || cutCsI_5 || cutCsI_6 || cutCsI_7"
			" || cutCsI_8 || cutCsI_10 || cutCsI_11"
			" || cutCsI_12 || cutCsI_13 || cutCsI_14 || cutCsI_15)");

	cut.Append(" && " + timeCondCsI + " && fTFlag");

	return cut;
}

Int_t DivideCanvas(TCanvas *c, Int_t firstStrip, Int_t showNoStrips) {

	Int_t noPads = 0;
	if ( ( (16 - firstStrip) - showNoStrips ) < 0 ) noPads = 16-firstStrip;
	else noPads = showNoStrips;

	if (!c) {
		Error("DivideCanvas", "Canvas was not catched.");
		return noPads;
	}

	if (noPads<=4) c->Divide(2,2);
	if (noPads>4 && noPads<=6) c->Divide(3,2);
	if (noPads>6 && noPads<=8) c->Divide(4,2);
	if (noPads==9) c->Divide(3,3);
	if (noPads>9 && noPads<=12) c->Divide(4,3);
	if (noPads>12) c->Divide(4,4);

	return noPads;
}

void DrawThinRMults(const Long64_t lowStatEntries = 100000) {

	TCanvas *c1 = new TCanvas("c1", "c1: Auxiliary information on trigger", 1500, 1000);
	c1->Divide(2,2);

	c1->cd(1);
	tr->Draw("trigger", "", "", lowStatEntries);
	c1->Update();

	c1->cd(3);
	var.Form("Length$(%s)", RT20X.Data());
	con.Form("Length$(%s)>0", RT20X.Data());
	tr->Draw(var, con + "&& trigger==2", "", lowStatEntries);
	if ((TH1F*)gPad->GetPrimitive("htemp")) {
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult R20, trigger==2");
	}
	c1->Update();

	c1->cd(4);
	var.Form("Length$(%s)", RT20X.Data());
	con.Form("Length$(%s)>0", RT20X.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult R20, trigger==3");
	c1->Update();



}

void DrawThickRMults(const Long64_t lowStatEntries = 100000) {

	TCanvas *c2 = new TCanvas("c2", "c2: Auxiliary information on 1 mm detectors", 1500, 1000);
	c2->Divide(3,2);

	c2->cd(1);
	var.Form("Length$(%s)", RTY.Data());
	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, con + "&& trigger==2", "", lowStatEntries);
	if ((TH1F*)gPad->GetPrimitive("htemp")) {
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult R1mm, trigger==2");
	}
	c2->Update();

	c2->cd(2);
	var.Form("Length$(%s)", RTY.Data());
	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult R1mm, trigger==3");
	c2->Update();

	c2->cd(5);
	var.Form("%s.fStripNb", RTY.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired strip R1mm, trigger==3");
	c2->Update();

	c2->cd(3);
	var.Form("Length$(%s)", RT3rd.Data());
	con.Form("Length$(%s)>0", RT3rd.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult Rveto, trigger==3");
	c2->Update();

	c2->cd(6);
	var.Form("%s.fStripNb", RTY.Data());
	con.Form("%s.fStripNb!=7", RTY.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired strip R1mm, trigger==3, strip 7 excluded");
	c2->Update();

	c2->cd(4);
	tr->Draw("BeamDetToFDigi2.fTime", "Length$(BeamDetToFDigi2)==1", "", lowStatEntries);
	c2->Update();


}

void DrawIDplotVeto() {
	TCanvas *c3 = new TCanvas("c3", "c3: dE-E: 1mm vs. veto(1mm), mults==1", 1000, 1000);
	c3->Divide(4,4);

	for (Int_t i = 0; i < 16; i++) {
		c3->cd(i+1);
		var.Form("%s.fEdep:%s.fEdep", RTY.Data(), RT3rd.Data());
		con.Form("%s.fStripNb == %d && Length$(%s)==1 && Length$(%s)==1",
				RTY.Data(), i, RTY.Data(), RT3rd.Data());
		//		cout << var << endl;
		tr->Draw(var, con + "&& trigger==3", "", 1000000);
		TString hTitle;
		hTitle.Form("dE-E: Y strip(1mm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		c3->Update();
	}
}

void DrawIDplotVetoTargetSelection() {

	const Long64_t drawEntries = 10000000;
	Info("DrawIDplotVetoTargetSelection", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c4 = new TCanvas("c4", "c4: dE-E: 1mm vs. veto(1mm), mults==1, target selected", 1000, 1000);
	c4->Divide(4,4);

	for (Int_t i = 0; i < 16; i++) {
		c4->cd(i+1);
		var.Form("%s.fEdep:%s.fEdep", RTY.Data(), RT3rd.Data());
		con.Form("%s.fStripNb == %d && Length$(%s)==1 && Length$(%s)==1"
				"&& %s",
				RTY.Data(), i, RTY.Data(), RT3rd.Data(),
				targetCondition.Data());
		//		cout << var << endl;
		tr->Draw(var, con + "&& trigger==3 && ( (fYt-2.)^2 + fXt^2 ) < 8.^2", "", drawEntries);
		TString hTitle;
		hTitle.Form("dE-E: Y strip(1mm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		c4->Update();
	}
}

void DrawTauAmpR(const Bool_t firstLayer = 1,
		const Bool_t secondLayer = 1, const Bool_t makeCuts = 0) {

	Long64_t drawEntries = 2000000;
//	Long64_t drawEntries = 100000000;

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	if (firstLayer) {
		TCanvas *c5_1 = new TCanvas("c5", "c5: 20 mcm dE-tau, trigger==3", 1000, 1000);
		c5_1->Divide(4,4);

		TCanvas *cEtauCuts1[16];

		for (Int_t i = 0; i < 16; i++) {
			if (makeCuts) {
				cEtauCuts1[i] = new TCanvas();
				cEtauCuts1[i]->ToggleToolBar();
				cEtauCuts1[i]->ToggleEditor();
				cEtauCuts1[i]->ToggleEventStatus();
				drawEntries = 5000000;
			}
			else c5_1->cd(i+1);

			tr->SetMarkerColor(kBlack);
			var.Form("%s.fEdep*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", RT20X.Data(), RT20X.Data());
			con.Form("%s.fStripNb == %d"
					"&& %s.fEdep*1000<15"
					"&& %s.fTime - BeamDetToFDigi2.fTime/2. > -70."
					"&& %s.fTime - BeamDetToFDigi2.fTime/2. < 150.",
					RT20X.Data(), i,
					RT20X.Data(),
					RT20X.Data(),
					RT20X.Data());
			//		cout << var << endl;


			//todo: working variables
//			var.Form("fRTEdepCorr*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", RT20X.Data());
//			con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
//					"&& fRTEdepCorr > 0."
//					"&& %s.fEdep*1000<15"
//					"&& %s.fTime - BeamDetToFDigi2.fTime/2. > -70."
//					"&& %s.fTime - BeamDetToFDigi2.fTime/2. < 150.",
//					i, RTY.Data(), RT3rd.Data(),
//					RT20X.Data(),
//					RT20X.Data(),
//					RT20X.Data());

			tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
			TString hTitle;
			hTitle.Form("dE-tau: strip(20mcm)==%d", i);
			((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
			gPad->Update();

			if (!makeCuts) {
				tr->SetMarkerColor(kRed);
				cRT20X[i]->Draw();
				cRT20X[i]->SetLineWidth(3);
				con.Form("%s.fStripNb == %d"
						"&& %s.fEdep*1000<15"
						"&& %s.fTime - BeamDetToFDigi2.fTime/2. < 50",
						RT20X.Data(), i,
						RT20X.Data(),
						RT20X.Data());
				//			tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
				c5_1->Update();

				tr->SetMarkerColor(kGreen);
				tr->SetMarkerSize(1.4);
				con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
						+ genCon
						+ "&&" + targetCondition
						+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
						+ "&&" + Form("%s.fStripNb == %d", RT20X.Data(), i)
						;
				cout << tr->Draw(var, con, "same") << endl;
				c5_1->Update();

			}
			gPad->Update();

		}//for strips
	}//if first layer (20 mcm)

	if (secondLayer) {
		TCanvas *c5_2 = new TCanvas("c5_2", "c5: 1 mm dE-tau, trigger==3", 1000, 1000);
		c5_2->Divide(4,4);

		TCanvas *cEtauCuts2[16];

		for (Int_t i = 0; i < 16; i++) {
			if (makeCuts) {
				cEtauCuts2[i] = new TCanvas();
				cEtauCuts2[i]->ToggleToolBar();
				cEtauCuts2[i]->ToggleEditor();
				cEtauCuts2[i]->ToggleEventStatus();
				drawEntries = 5000000;
			}
			else c5_2->cd(i+1);

			tr->SetMarkerColor(kBlack);
			var.Form("%s.fEdep*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", RTY.Data(), RTY.Data());
			con.Form("%s.fStripNb == %d"
									"&& %s.fEdep*1000<30"
					"&& %s.fTime - BeamDetToFDigi2.fTime/2. > -70."
					"&& %s.fTime - BeamDetToFDigi2.fTime/2. < 400.",
					RTY.Data(), i,
					RTY.Data(),
					RTY.Data(),
					RTY.Data()
			);
			//todo: delete following condition
//			con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
//					"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
//					//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
//					"",
//					i, RTY.Data(), RT3rd.Data(),
//					RTY.Data()
//					//				RTY.Data(), RTY.Data()
//			);
			//		cout << var << endl;
			tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
			TString hTitle;
			hTitle.Form("dE-tau: Y strip==%d", i);
			((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());

			gPad->SetLogz();

			gPad->Update();

			if (!makeCuts) {
				tr->SetMarkerColor(kRed);
				cRTY[i]->Draw();
				cRTY[i]->SetLineWidth(3);
			//		tr->SetMarkerColor(kRed);
			//		con.Form("%s.fStripNb == %d"
			//				"&& %s.fEdep*1000<15"
			//				"&& %s.fTime - BeamDetToFDigi2.fTime/2. < 50",
			//				RT20X.Data(), i,
			//				RT20X.Data(),
			//				RT20X.Data());
				TString timeCondition;
				timeCondition.Form("cutRTY_%d", i);
				con.Append(" && " + timeCondition);
//				tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
				gPad->Update();

				tr->SetMarkerColor(kGreen);
				tr->SetMarkerSize(1.4);
				con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
						+ genCon
						+ "&&" + targetCondition
						+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
						+ "&&" + Form("%s.fStripNb == %d", RTY.Data(), i)
						;
				cout << tr->Draw(var, con, "same") << endl;
				c5_2->Update();
			}
		}
	}// if second layer (1mm Y)

}

void DrawIDplotThinR() {

	const Long64_t drawEntries = 10000000;
	Info("DrawIDplotThinR", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c6 = new TCanvas("c6", "c6: dE-E: 20mcm vs. 1mm, mults==1", 1000, 1000);
	c6->Divide(4,4);

	for (Int_t i = 0; i < 16; i++) {
		c6->cd(i+1);
		var.Form("%s.fEdep*1000:%s.fEdep*1000", RT20X.Data(), RTY.Data());
		con.Form("Length$(%s) == 1 && Length$(%s) == 1 "
				"&& %s.fEdep < 0.007 && %s.fEdep < 0.07 "
				"&& %s.fStripNb == %d",
				RT20X.Data(), RTY.Data(),
				RT20X.Data(), RTY.Data(),
				RT20X.Data(), i
		);
		//		cout << var << endl;
		tr->Draw(var, con + "&& trigger==3 ", "col", drawEntries);

		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("dE (MeV)");

		c6->Update();
	}

}

void DrawIDplotThinRtargetSelection(const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0, const Bool_t logZ = 0) {

	const Long64_t drawEntries = 10000000;
//	const Long64_t drawEntries = 1000000;
	Info("DrawIDplotThinRtargetSelection", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c7 = new TCanvas("c7", "c7: dE-E: 20mcm vs. 1mm, mults==1, target selected, veto on", 1300, 1000);

	Int_t noPads = DivideCanvas(c7, firstStrip, showNoStrips);

	for (Int_t i = 0; i < noPads; i++) {
		c7->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.1);

		var.Form("%s.fEdep*1000:%s.fEdep*1000", RT20X.Data(), RTY.Data());
		con.Form("Length$(%s) == 1 && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& %s.fEdep < 0.007 && %s.fEdep < 0.07 "
				"&& %s.fStripNb == %d"
				"&& %s.fEdep > -0.0017/0.02*%s.fEdep + 0.0017",
				RT20X.Data(), RTY.Data(), RT3rd.Data(),
				RT20X.Data(), RTY.Data(),
				RT20X.Data(), i+firstStrip,
				RT20X.Data(), RTY.Data()
		);
		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i+firstStrip);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		gPad->Update();


		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);
		con.Form("Length$(%s) == 1 && Length$(%s) == 1 && Length$(%s) == 0 "
					"&& %s.fEdep < 0.007 && %s.fEdep < 0.07 "
					"&& %s.fStripNb == %d"
					"&& %s.fEdep > -0.0017/0.02*%s.fEdep + 0.0017"
					"&& %s",
					RT20X.Data(), RTY.Data(), RT3rd.Data(),
					RT20X.Data(), RTY.Data(),
					RT20X.Data(), i+firstStrip,
					RT20X.Data(), RTY.Data(),
					targetCondition.Data()
			);

		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();
	}

}

void DrawIDplotTargetSelCorrected (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t logZ = 0) {

	const Long64_t drawEntries = 10000000;
	Info("DrawIDplotTargerSelCorrected",
			"High statistics needed, slow drawing; used %lld entries from %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c8 = new TCanvas("c8", "c8: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c8, firstStrip, showNoStrips);


	for (Int_t i = 0; i < noPads; i++) {
		c8->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
				"&& fTrigger==3",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
//				RTY.Data(), RTY.Data()
		);
//		con.Form("");

//		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		cout << tr->Draw(var, con /*+ "&& trigger==3"*/, "", drawEntries) << endl;
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i+firstStrip);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("dE corrected (MeV)");
		gPad->Update();

		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);

		con.Append("&&" + targetCondition);

		tr->Draw(var, con , "same", drawEntries);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
				mP[e][p]->SetMarkerColor(kYellow);
				mP[e][p]->SetMarkerSize(1.2);
				mP[e][p]->Draw("same");
			}
		}
		gPad->Update();
	}

}

void DrawCheckCorrection (const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0) {

	const Long64_t drawEntries = 1000000;
	Info("DrawCheckCorrection", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c9 = new TCanvas("c9", "c9: check of E correction for thickness", 1300, 1000);
	Int_t noPads = DivideCanvas(c9, firstStrip, showNoStrips);


	for (Int_t i = 0; i < noPads; i++) {
		c9->cd(i+1);

		var.Form("fRTEdepCorr*1000 - measuredEdep*1000");
		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && measuredEdep > 0.",
				i+firstStrip, RT20X.Data() );

		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		TString hTitle;
		hTitle.Form("E(corr) - E(meas): strip(20mcm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());

		gPad->Update();
	}

}

void DrawCheckIDplotInPixels (const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0) {

	const Long64_t drawEntries = 10000000;
//	const Long64_t drawEntries = 10000;
	Info("Draw10", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c10 = new TCanvas("c10", "c8: dE-E: 20mcm vs. 1mm, mults==1, Y strip==7, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c10, firstStrip, showNoStrips);


	for (Int_t i = 0; i < noPads; i++) {
		c10->cd(i+1);


		var.Form("%s.fEdep*1000:%s.fEdep*1000", RT20X.Data(), RTY.Data());
		con.Form("Length$(%s) == 1 && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& %s.fEdep < 0.007 && %s.fEdep < 0.07 "
				"&& %s.fStripNb == %d"
				"&& %s.fEdep > -0.0017/0.02*%s.fEdep + 0.0017"
				"&& %s.fStripNb > 6 && %s.fStripNb < 8",
				RT20X.Data(), RTY.Data(), RT3rd.Data(),
				RT20X.Data(), RTY.Data(),
				RT20X.Data(), i+firstStrip,
				RT20X.Data(), RTY.Data(),
				RTY.Data(), RTY.Data()
		);


		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d, Ystrip==7", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("dE (MeV)");
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
				mP[e][p]->Draw("same");
			}
		}
		gPad->Update();
	}

}

void DrawIDplotCorrectedForHeCuts (const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0, const Bool_t logZ = 0, Bool_t makeCuts = 0) {

	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedForHeCuts",
			"High statistics needed, slow drawing; used %lld entries from %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c8_1;
	Int_t noPads = 0;
//	if (!makeCuts) {
		c8_1 = new TCanvas("c8_1", "c8_1: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
		noPads = DivideCanvas(c8_1, firstStrip, showNoStrips);
//	}

	TCanvas *canvasHeliumCuts[16];
	if (makeCuts) {
//		Warning("DrawIDplotTargerSelCorrected", "First two arguments (showNoStrips and firstStrip) ignored.");

		Int_t noPads = 0;
		if ( ( (16 - firstStrip) - showNoStrips ) < 0 ) noPads = 16-firstStrip;
		else noPads = showNoStrips;

//		firstStrip = 0;
//		noPads = 16;
	}

	for (Int_t i = 0; i < noPads; i++) {
		if (makeCuts) {
			canvasHeliumCuts[i] = new TCanvas();
			canvasHeliumCuts[i]->ToggleToolBar();
			canvasHeliumCuts[i]->ToggleEditor();
			canvasHeliumCuts[i]->ToggleEventStatus();
//			drawEntries = 5000000;
		}
		else c8_1->cd(i+1);
//		c8_1->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
//				RTY.Data(), RTY.Data()
		);

//		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);

		TString hTitle;
		if(makeCuts) {
			TString tritium = MakeGeneralTritiumCut();
			tr->SetMarkerSize(.7);
			con.Append(" && " + tritium);
			cout << tr->Draw(var, con + "&& trigger==3", "", drawEntries) << endl;
			hTitle.Form("dE_corr-E: strip(20mcm)==%d, He in RT", i+firstStrip);
		}
		else {
			cout << tr->Draw(var, con + "&& trigger==3", "col", drawEntries) << endl;
			hTitle.Form("dE-E: strip(20mcm)==%d, all", i+firstStrip);
		}



//		hTitle.Form("dE-E: strip(20mcm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("dE_corr (MeV)");
		gPad->Update();

		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);

//		con.Append("&&" + targetCondition);

		if (cHelium3[i+firstStrip]) cHelium3[i+firstStrip]->Draw();

		if (!makeCuts) {
//			cHelium3[i]->Draw();

//			TString heliumCut = cHeliu

			con.Append("&&" + (TString)cHelium3[i+firstStrip]->GetName());

//			TString tritium = MakeGeneralTritiumCut();


//			con.Append(" && !" + tritium);

			tr->Draw(var, con + "&& trigger==3", "same", drawEntries);

		}

//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
//				mP[e][p]->Draw("same");
				mP[e][p]->SetMarkerColor(kMagenta);
				mP[e][p]->SetMarkerSize(0.9);
				mP[e][p]->Draw("same");
//				mPcorrected[i+firstStrip][e][p]->SetMarkerColor(kMagenta);
//				mPcorrected[i+firstStrip][e][p]->SetMarkerSize(0.9);
//				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();
	}

}

void DrawC11(const Bool_t logZ = 0) {


	const Long64_t drawEntries = 100000000;


	TCanvas *c11 = new TCanvas("c11", "c9: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on, selected Y-strips", 1100, 1100);
	c11->Divide(2,2);

	const Int_t firstStrip = 2;

	TLine *lE = new TLine(0.02, 0.0005, 0.02, 0.007);
	TLine *lDE = new TLine(0., 0.0023, 0.04, 0.0023);
	TLine *lDE2 = new TLine(0.0002, 0.0012, 0.07, 0.0012);

	lE->SetLineColor(kGreen);
	lDE->SetLineColor(kMagenta);
	lDE2->SetLineColor(kGreen);

	for (Int_t i = 0; i < 4; i++) {
		c11->cd(i+1);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.007 && %s.fEdep < 0.07 "
				"&& %s.fStripNb > 6 && %s.fStripNb < 8",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data(),
				RTY.Data(), RTY.Data()
		);

		//			con.Form("%s.fStripNb == %d && Length$(%s) == 1 && Length$(%s) == 0 "
		//					"&& fRTEdepCorr < 0.007 && %s.fEdep < 0.07 ",
		//					RT20X.Data(), i, RTY.Data(), RT3rd.Data(),
		//					RTY.Data()
		//			);

		//		cout << var << endl;
		//			tr->Draw(var, con + "&& trigger==3", "", 100*lowStatEntries);

		//			var.Form("measuredEdep - %s.fEdep", RT20X.Data());
		//			var.Form("fRTEdepCorr - %s.fEdep", RT20X.Data());
		//			var.Form("fRTEdepCorr - measuredEdep");
		//			con.Form("Length$(%s) == 1 && measuredEdep > 0.", RT20X.Data() );

		//			tr->Draw(var, con + "&& trigger==3", "", 100*lowStatEntries);
		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i+firstStrip);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());

		gPad->Update();
		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.4);
		tr->Draw(var, con + "&& trigger==3 &&  ( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2", "same", drawEntries);
		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.1);
		gPad->Update();

		lE->Draw();
		lDE->Draw();
		lDE2->Draw();
		if (logZ) gPad->SetLogz();
		gPad->Update();
	}

}

void DrawIDplotCorrectedTimeCuts (const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0, const Bool_t logZ = 0) {

	const Long64_t drawEntries = 10000000;
//	const Long64_t drawEntries = 10000;
	Info("DrawIDplotTargerSelCorrected", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c12 = new TCanvas("c12", "c12: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c12, firstStrip, showNoStrips);


	for (Int_t i = 0; i < noPads; i++) {
		c12->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
//				RTY.Data(), RTY.Data()
		);

//		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		cout << tr->Draw(var, con + "&& trigger==3", "", drawEntries) << endl;
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("dE (MeV)");
		gPad->Update();

		//add target condition
		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.7);
		con.Append("&&" + targetCondition);
		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		//add condition for time cuts in 20 mcm
		tr->SetMarkerColor(kGreen);
		tr->SetMarkerSize(0.7);
		TString timeCut;
		timeCut.Form("%s", cRT20X[i+firstStrip]->GetName());
		con.Append(" && " + timeCut);

		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
//				mP[e][p]->Draw("same");
				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();

		//build of legend
		TLegend *legend = new TLegend();
		legend->AddEntry("entry1", "target con");
		legend->AddEntry("entry2", "target con + time con");
		( (TLegendEntry*)legend->GetListOfPrimitives()->At(0) )->SetMarkerColor(kRed);
		( (TLegendEntry*)legend->GetListOfPrimitives()->At(1) )->SetMarkerColor(kGreen);
		legend->Draw();
		gPad->Update();
	}

}

void DrawIDplotCorrectedTimeCuts2 (const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0, const Bool_t logZ = 0) {

	Warning("DrawIDplotCorrectedTimeCuts", "We cannot work with E-tau cuts for Y strips!!!!!");

	const Long64_t drawEntries = 10000000;
	Info("DrawIDplotTargerSelCorrected", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c13 = new TCanvas("c13", "c13: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c13, firstStrip, showNoStrips);


	for (Int_t i = 0; i < noPads; i++) {
		c13->cd(i+1);

		tr->SetMarkerColor(kRed);
//		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.7);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
//				RTY.Data(), RTY.Data()
		);

		con.Append("&&" + targetCondition);

//		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		cout << tr->Draw(var, con + "&& trigger==3", "", drawEntries) << endl;
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("dE (MeV)");
		gPad->Update();

		//time condition in Y strips added
//		tr->SetMarkerColor(kRed);
		tr->SetMarkerColor(kGreen);
//		tr->SetMarkerSize(0.2);
//		con.Append("&&" + targetCondition);

//		TString timeCondY;
////		timeCond.Form("%s.fTime - BeamDetToFDigi2.fTime/2. < 50", RT20X.Data());
//		timeCondY.Form("(cutRTY_0 || cutRTY_1 || cutRTY_2 || cutRTY_3"
//				" || cutRTY_4 || cutRTY_5 || cutRTY_6 || cutRTY_7"
//				" || cutRTY_8 || cutRTY_9 || cutRTY_10 || cutRTY_11"
//				" || cutRTY_12 || cutRTY_13 || cutRTY_14 || cutRTY_15)");

//		timeCond.Form("(cutRTY_0 && cutRTY_1 && cutRTY_2 && cutRTY_3"
//				" && cutRTY_4 && cutRTY_5 && cutRTY_6 && cutRTY_7"
//				" && cutRTY_8 && cutRTY_9 && cutRTY_10 && cutRTY_11"
//				" && cutRTY_12 && cutRTY_13 && cutRTY_14 && cutRTY_15)");
//		timeCond.Form("(cutRTY_1 && cutRTY_2)"
//				"");
		TString newCon = con;
		newCon.Append(" && " + timeCondY);
		cout << "\t" << tr->Draw(var, newCon + "&& trigger==3", "same", drawEntries) << endl;
		gPad->Update();

//		timeCond.Form("!(cutRTY_0 || cutRTY_1 || cutRTY_2 || cutRTY_3"
//				" || cutRTY_4 || cutRTY_5 || cutRTY_6 || cutRTY_7"
//				" || cutRTY_8 || cutRTY_9 || cutRTY_10 || cutRTY_11"
//				" || cutRTY_12 || cutRTY_13 || cutRTY_14 || cutRTY_15)");

		//time condition in Y strips excluded
		newCon = con;
		newCon.Append(" && !" + timeCondY);
		tr->SetMarkerColor(kGreen);
//		cout << "\t" << tr->Draw(var, newCon + "&& trigger==3", "same", drawEntries) << endl;
//		tr->SetMarkerColor(kBlack);
//		tr->SetMarkerSize(0.1);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
//				mP[e][p]->Draw("same");
				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();

		//build of legend
		TLegend *legend = new TLegend();
		legend->AddEntry("entry1", "target con");
		legend->AddEntry("entry2", "target con + time con");
		( (TLegendEntry*)legend->GetListOfPrimitives()->At(0) )->SetMarkerColor(kRed);
		( (TLegendEntry*)legend->GetListOfPrimitives()->At(1) )->SetMarkerColor(kGreen);
		legend->Draw();
		gPad->Update();
	}

}

void DrawIDplotCorrectedTimeCuts3 (const Int_t showNoStrips = 12,
		const Int_t firstStrip = 0, const Bool_t logZ = 0) {

	Warning("DrawIDplotCorrectedTimeCuts", "We cannot work with E-tau cuts for Y strips!!!!!");

	const Long64_t drawEntries = 10000000;
	Info("DrawIDplotTargerSelCorrected", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c13 = new TCanvas("c13", "c13: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c13, firstStrip, showNoStrips);


	for (Int_t i = 0; i < noPads; i++) {
		c13->cd(i+1);

		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.7);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
		);

		con.Append("&&" + targetCondition);

		cout << tr->Draw(var, con + "&& trigger==3", "", drawEntries) << endl;
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("dE (MeV)");
		gPad->Update();

		//time condition in Y strips added
		tr->SetMarkerColor(kGreen);

		TString timeCutX;
		timeCutX.Form("%s", cRT20X[i+firstStrip]->GetName());
		con.Append(" && " + timeCutX);

//		TString newCon = con;
		con.Append(" && " + timeCondY );
		cout << "\t" << tr->Draw(var, con + "&& trigger==3", "same", drawEntries) << endl;
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();

		//build of legend
		TLegend *legend = new TLegend();
		legend->AddEntry("entry1", "target con");
		legend->AddEntry("entry2", "target con + time con");
		( (TLegendEntry*)legend->GetListOfPrimitives()->At(0) )->SetMarkerColor(kRed);
		( (TLegendEntry*)legend->GetListOfPrimitives()->At(1) )->SetMarkerColor(kGreen);
		legend->Draw();
		gPad->Update();
	}

}

void DrawIDplotCorrectedWithCuts (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, const Bool_t logZ = 0) {

	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCuts", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c14 = new TCanvas("c14", "c14: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c14, firstStrip, showNoStrips);

	for (Int_t i = 0; i < noPads; i++) {
		c14->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
				//				RTY.Data(), RTY.Data()
		);

		//		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
		cout << tr->Draw(var, con + "&& trigger==3", "col", drawEntries) << endl;
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i+firstStrip);
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("dE (MeV)");
		gPad->Update();



		cHelium3[i+firstStrip]->SetLineWidth(3);
		cHelium3[i+firstStrip]->Draw();
		gPad->Update();

		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);
		con.Append("&&" + targetCondition);
		cout << "\t" << tr->Draw(var, con + "&& trigger==3", "same", drawEntries) << endl;
		gPad->Update();

		//			TString heliumCut = cHeliu

//		con.Append("&&" + (TString)cHelium3[i]->GetName());

		tr->SetMarkerColor(kGreen);
		tr->SetMarkerSize(0.9);
		TString tritium = MakeGeneralTritiumCut();
//		con.Append(" && " + tritium);
		con.Append(" && " + tritium + " && " + (TString)cHelium3[i+firstStrip]->GetName());
		cout << "\t" << tr->Draw(var, con + "&& trigger==3", "same", drawEntries) << endl;
		gPad->Update();


//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);

//		}

		//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
				mP[e][p]->Draw("same");
			}
		}
		gPad->Update();
	}

}

void DrawIDplotCorrectedWithCuts2 (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, const Bool_t logZ = 0) {

	Info("DrawIDplotCorrectedWithCuts2", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCuts", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c14 = new TCanvas("c14", "c14: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c14, firstStrip, showNoStrips);

	for (Int_t i = 0; i < noPads; i++) {
		c14->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				//					"&& %s.fStripNb > 6 && %s.fStripNb < 8"
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()
				//				RTY.Data(), RTY.Data()
		);

		//		tr->Draw(var, con + "&& trigger==3", "col", drawEntries);
//		cout << tr->Draw(var, con + "&& trigger==3", "col", drawEntries) << endl;
		TString hTitle;
		hTitle.Form("dE-E: strip(20mcm)==%d", i+firstStrip);
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats(1);
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("E (MeV)");
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("dE (MeV)");
		gPad->Update();



		cHelium3[i+firstStrip]->SetLineWidth(3);
		cHelium3[i+firstStrip]->Draw();
		gPad->Update();

		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);
		con.Append("&&" + targetCondition);
		cout << "\t" << tr->Draw(var, con + "&& trigger==3", "same", drawEntries) << endl;
		gPad->Update();

		//			TString heliumCut = cHeliu

//		con.Append("&&" + (TString)cHelium3[i]->GetName());

		tr->SetMarkerColor(kBlue);
		tr->SetMarkerSize(0.9);
		TString tritium = MakeGeneralTritiumCut();
		con.Append(" && " + tritium);
		cout << "\t" << tr->Draw(var, con + "&& trigger==3", "same", drawEntries) << endl;
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		con.Append(" && " + (TString)cHelium3[i+firstStrip]->GetName());
		cout << "\t" << tr->Draw(var, con + "&& trigger==3", "same", drawEntries) << endl;

//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);

//		}

		//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
//				mP[e][p]->Draw("same");
				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();

		cout << endl;
	}

}

void DrawIDplotCorrectedWithCutsFinal (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, const Bool_t logZ = 0) {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c15 = new TCanvas("c15", "c14: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c15, firstStrip, showNoStrips);

	Long64_t tCount = 0;

	for (Int_t i = 0; i < noPads; i++) {
		c15->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()

		);

		gPad->Update();

		cHelium3[i+firstStrip]->SetLineWidth(3);
		cHelium3[i+firstStrip]->Draw();
		gPad->Update();

		//draw with target condition
		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);
		con.Append("&&" + targetCondition);
		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		//draw with tritium coincidences
		tr->SetMarkerColor(kBlue);
		tr->SetMarkerSize(0.9);
		TString tritium = MakeGeneralTritiumCut();
		con.Append(" && " + tritium);
		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

//		continue;

		//draw with all conditions
		tr->SetMarkerColor(kGreen);

		//add 3He ID cut
		con.Append(" && " + (TString)cHelium3[i+firstStrip]->GetName());

		//add RT time cuts
		TString timeCutX;
		timeCutX.Form("%s", cRT20X[i+firstStrip]->GetName());
		con.Append(" && " + timeCutX);
		con.Append(" && " + timeCondY );

		//add MWPC time condition
		con.Append(" && " + MWPCtimeCondition);

		//add beam condition
		con.Append(" && " + beamIdCondition);

		Long64_t currTritiumCount = tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		tCount += currTritiumCount;
		cout << currTritiumCount << endl;

		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
				mPcorrected[i+firstStrip][e][p]->SetMarkerColor(kMagenta);
				mPcorrected[i+firstStrip][e][p]->SetMarkerSize(1.);
//				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();

	}

	Info("DrawCleanTritons", "%lld 3He-3H coincidences found in whole data.", tCount);

}

void DrawHeEnergyLABWithCutsFinal (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, const Bool_t logZ = 0) {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	TCanvas *c15 = new TCanvas("c15", "c14: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c15, firstStrip, showNoStrips);

	Long64_t tCount = 0;

	for (Int_t i = 0; i < noPads; i++) {
		c15->cd(i+1);

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

		con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
				"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
				"",
				i+firstStrip, RTY.Data(), RT3rd.Data(),
				RTY.Data()

		);

		gPad->Update();

		cHelium3[i+firstStrip]->SetLineWidth(3);
//		cHelium3[i+firstStrip]->Draw();
		gPad->Update();

		//draw with target condition
		tr->SetMarkerColor(kRed);
		tr->SetMarkerSize(0.2);
		con.Append("&&" + targetCondition);
//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

		//draw with tritium coincidences
		tr->SetMarkerColor(kBlue);
		tr->SetMarkerSize(0.9);
		TString tritium = MakeGeneralTritiumCut();
		con.Append(" && " + tritium);
//		tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		gPad->Update();

//		continue;

		//draw with all conditions
		tr->SetMarkerColor(kGreen);

		//add 3He ID cut
		con.Append(" && " + (TString)cHelium3[i+firstStrip]->GetName());

		//add RT time cuts
		TString timeCutX;
		timeCutX.Form("%s", cRT20X[i+firstStrip]->GetName());
		con.Append(" && " + timeCutX);
		con.Append(" && " + timeCondY );

		//add MWPC time condition
		con.Append(" && " + MWPCtimeCondition);

		//add beam condition
		con.Append(" && " + beamIdCondition);

		var.Form("%s.fEdep*1000", RTY.Data());
//		Long64_t currTritiumCount = tr->Draw(var, con + "&& trigger==3", "same", drawEntries);
		Long64_t currTritiumCount = tr->Draw(var, con + "&& trigger==3", "", drawEntries);
		tCount += currTritiumCount;
		cout << currTritiumCount << endl;

		gPad->Update();

		if (logZ) gPad->SetLogz();
		gPad->Update();

		for (Int_t e = 0; e < 3; e++) {
			for (Int_t p = 0; p < 4; p++) {
				mPcorrected[i+firstStrip][e][p]->SetMarkerColor(kMagenta);
				mPcorrected[i+firstStrip][e][p]->SetMarkerSize(1.);
//				mPcorrected[i+firstStrip][e][p]->Draw("same");
			}
		}
		gPad->Update();

	}

	Info("DrawHeEnergyLABWithCutsFinal", "%lld our 3He found in whole data.", tCount);

}
