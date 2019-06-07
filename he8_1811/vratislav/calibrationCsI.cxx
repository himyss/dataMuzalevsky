#if !defined(__CLING__)


#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLine.h"
#include "TCutG.h"
#include "TROOT.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"

#include <iostream>

using std::cout;
using std::endl;

#endif

#include "cutsCsI.cxx"
#include "cutsTritium.cxx"
#include "cutsHelium3.cxx"


//Si X layer
TString CTX = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X";
//Si Y layer
TString CTY = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_Y";
//CsI layer
TString CTCsI = "ERQTelescopeCsIDigi_Central_telescope_CsI_0";

TString TOF2 = "BeamDetToFDigi2.fTime";

//right telescope: todo: to be deleted
//first layer
TString RT20X = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0";
//second layer
TString RTY = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0";
//third layer
TString RT3rd = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0";

//trigger==2: Left telescope
//trigger==3: Right telescope

TChain *tr;
TChain *trIn;

const Int_t showNoStrips = 12;

//auxiliary variables
TString var;
TString con;

void InitTrees(const Bool_t allStat = 0);
void MakeConditionBeamID();
void DrawCleanTritons(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0);
//global conditions:
TString timeConditonCX;
TString timeConditonCY;
TString targetCondition;
TString MWPCtimeCondition;
TString beamIdCondition;


void calibrationCsI(const Bool_t allStat = 1) {

//TProof::Open("");
	const Bool_t showViewer = 0;

	InitTrees(allStat);
	MakeConditionBeamID();

	if (showViewer) tr->StartViewer();

	DrawCleanTritons(1, 0);

}

void InitTrees(const Bool_t allStat = 0) {
	TString inFile;
	const Int_t run = 10;
	//	const Int_t noFiles = 23;
	const Int_t noFiles = 7;
	TString	inPath;

//	TString	inPath = "~/data/exp1811/calibrated_filtered/reco/";
	/*TString	inPath = "~/data/exp1811/calibrated_filtered_CsI/reco/";

	tr = new TChain("reco");

		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.reco.root", inPath.Data(), run, i);
			tr->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_%02d_*", inPath.Data(), 7);
			//			cout << inFile << endl;
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 8);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 9);
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
		}*/

//		inPath = "~/data/exp1811/calibrated_filtered/";
		inPath = "~/data/exp1811/calibrated_filtered_CsI/";
		tr = new TChain("er");
		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.Digi.root", inPath.Data(), run, i);
			tr->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_%02d_*", inPath.Data(), 7);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 8);
			tr->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 9);
			tr->Add(inFile.Data());
			/*inFile.Form("%she8_%02d_*", inPath.Data(), 11);
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
			tr->Add(inFile.Data());*/
		}
//	}//if target filled

//	tr->AddFriend(trIn);
	tr->SetMarkerStyle(20);
	tr->SetMarkerSize(0.1);

}

void MakeConditionBeamID() {
	const Bool_t useCsIcuts = 1;
	const Bool_t useTritiumCuts = 1;
	const Bool_t useHeliumCuts = 1;


	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";

//	targetCondition.Append(" && " + MWPCtimeCondition);
	cout << targetCondition << endl;

	if (useCsIcuts) {
		cutsCsI();
	}

	if (useTritiumCuts) {
		cutsTritium();
	}

	if (useHeliumCuts) {
		cutsHelium3();
	}

	//global time conditions
	timeConditonCX.Form("%s.fTime-BeamDetToFDigi2.fTime/2.>100. && %s.fTime-BeamDetToFDigi2.fTime/2.<135.",
			CTX.Data(), CTX.Data());
	timeConditonCY.Form("%s.fTime-BeamDetToFDigi2.fTime/2.>100. && %s.fTime-BeamDetToFDigi2.fTime/2.<135.",
			CTY.Data(), CTY.Data());


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

void DrawCleanTritons(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0) {
//--------------------------------------------------------------------------------------------------------------------------
/*
	const Int_t nCrystal = 16;
	TH2F *h[nCrystal];
	THStack *hs = new THStack("hs","");
	for (Int_t i = 0; i < nCrystal; i++) {
		h[i] = 0;
	}
	TString	hName, hTitle;
	for(Int_t i=0; i<nCrystal; i++) {
		hName.Form("dE-E[%d]",i);
		hTitle.Form("dE-E[%d]",i);
		h[i] = new TH2F (hName.Data(), hTitle.Data(),400, 0., 200., 100, 0., 16.);
		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(.3);
		var.Form("%s.fEdep*1000:Max$(%s.fEdep)>>dE-E[%d]", CTX.Data(), CTCsI.Data(), i);
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016 && Max$(%s.fEdep)<200",
		CTCsI.Data(), i, CTX.Data(), CTX.Data(), CTCsI.Data());
		tr->Draw(var, con + "&& trigger==3", "");
		hs->Add(h[i]);
	}	
	hs->Draw("colz");
*/
//----------------------------------------------------------------------------------------------------------------
	/*TCanvas *c100 = new TCanvas("c100","c100: dE-E: Calibrated", 1000, 1000);
	c100->Divide(4,4);
	for (Int_t i = 0; i < 16; i++) {
		c100->cd(i+1);
		tr->SetMarkerColor(kBlue); //normal 1
		var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
				CTCsI.Data(), i, CTX.Data(), CTX.Data());
		tr->Draw(var, con + "&& trigger==3", "");

		tr->SetMarkerColor(kRed);
		var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016 && %s.fEdep<2000",
					CTCsI.Data(), 3, CTX.Data(), CTX.Data(), CTCsI.Data());
		tr->Draw(var, con + "&& trigger==3", "same");
		c100->Update();
	}*/
//-------------------------------------------------------------------------------------------------------------------------------------------	
	/*TCanvas *c98 = new TCanvas("c98","c98: each of crystal for dE-E: Calibrated", 1000, 1000);
	c98->Divide(4,4);
	for (Int_t i=0; i<16; i++){
	c98->cd(i+1);
	tr->SetMarkerColor(kBlack);
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), i, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& trigger==3", "");
	gPad->Update();
	}
*/
//-------------------------------------------------------------------------------------------------------------------------------------------
	TCanvas *c99 = new TCanvas("c99","c99: SUM all of crystals dE-E: Calibrated", 1000, 1000);
	c99->Divide(1,1);
	c99->cd(1);

	tr->SetMarkerSize(0.5);
 	tr->SetMarkerStyle(20);

 	tr->SetMarkerColor(kBlack);
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
//	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
//		CTCsI.Data(), 0, CTX.Data(), CTX.Data());
	con.Form("%s.fBlockNb != %d && Length$(%s)==1 && %s.fEdep<0.016",
			CTCsI.Data(), 9, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "");
	c99->Update();

	return;

	tr->SetMarkerColor(kGreen); //kGreen
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 1, CTX.Data(), CTX.Data());
//	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

//	return;

	tr->SetMarkerColor(kYellow); //kYellow
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 2, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "");
//	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

//	return;

	tr->SetMarkerColor(kMagenta); //kMagenta
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 3, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();
	
//	return;

	tr->SetMarkerColor(kOrange); //kOrange
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 4, CTX.Data(), CTX.Data());
//	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

	/*tr->SetMarkerSize(0.2);
 	tr->SetMarkerStyle(20);
	tr->SetMarkerColor(kSpring); //kSpring
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 5, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& trigger==3", "same");
	c99->Update();*/

//	return;

	tr->SetMarkerColor(kViolet); //kViolet
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 6, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

//	return;

	tr->SetMarkerColor(kPink); //kPink
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 7, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

//	return;

	tr->SetMarkerColor(kAzure); //kAzure
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 8, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

//	return;

	tr->SetMarkerColor(kTeal); //kTeal
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 10, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();
	
	return;

	tr->SetMarkerColor(kCyan); //kCyan
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 11, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

	tr->SetMarkerColor(kArmy); //kArmy
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 12, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

	tr->SetMarkerColor(kRed); //kRed
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 13, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

	tr->SetMarkerColor(kBlue); //kBlue
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 14, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();

	tr->SetMarkerColor(kBlack); //normal 1
	var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
	con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016",
		CTCsI.Data(), 15, CTX.Data(), CTX.Data());
	tr->Draw(var, con + "&& fTrigger==3", "same");
	c99->Update();
}
