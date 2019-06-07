#if !defined(__CLING__)


#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLine.h"
#include "TCutG.h"
#include "TROOT.h"
//#include "TMarker.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"


#include <iostream>

using std::cout;
using std::endl;

#endif

//#include "cutsCsI.cxx"
#include "cutsCsIcal.cxx"
//#include "cutsTritium.cxx"
#include "cutsTritiumCal.cxx"
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

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0);
void MakeConditionBeamID();
TString MakeGeneralTritiumCut();

void DrawMultCT();
void DrawCTaux();
void DrawIDplotCraw(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0);
void DrawTestOfCsImaxAmp(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, Bool_t showDrawTest = 0);
void DrawTauAmp(const Bool_t xstrips = 1, const Bool_t ystrips = 1,
		const Bool_t crystals = 1, const Bool_t makeCsICuts = 0);
void DrawCleanTritons(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0);
void DrawCleanTritonsWithHe(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0);

//global conditions:
TString timeConditonCX;
TString timeConditonCY;
TString targetCondition;
TString MWPCtimeCondition;
TString beamIdCondition;

const Double_t m3He = 2808.391;
const Double_t cut3HeEnergy = 30.;
TString timeCondCsI;

TString genCon;

void showCT(const Bool_t allStat = 1) {

	genCon =
			MakeGeneralTritiumCut() + " && "
			//			MakeGeneralDeuteriumCut() + " && "
			+ Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);

	const Bool_t showViewer = 0;

	InitTrees(allStat);
//	InitTrees(allStat,1);
	MakeConditionBeamID();

	if (showViewer) tr->StartViewer();

//	DrawMultCT();					//ok
//	DrawCTaux();					//ok
//	DrawIDplotCraw();				//ok
//	DrawIDplotCraw(4,10);
//	DrawTestOfCsImaxAmp();			//ok
//	DrawTestOfCsImaxAmp(16, 0, 1);	//todo: test is very interesting function - should be tested for blockNb
//	DrawTestOfCsImaxAmp(4,10);
//	DrawTauAmp(1, 0, 0);
//	DrawTauAmp(1, 1, 0);			//ok
//	DrawTauAmp(0, 0, 1, 1);
	DrawTauAmp(0, 0, 1);			//seems to be ok
//	DrawCleanTritons(4, 12);
//	DrawCleanTritons(1);
//	DrawCleanTritons();				//ok
//	DrawCleanTritons(16, 0, 0);				//ok
//	DrawCleanTritonsWithHe(4, 12);
//	DrawCleanTritonsWithHe();		//todo: need to be checked again

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
//	tr->SetMarkerSize(0.2);

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

void DrawMultCT() {

	const Long64_t lowStatEntries = 100000;

	TCanvas *c1 = new TCanvas("c1", "c1: Auxiliary information on trigger and CT multiplicity", 1500, 1000);
	c1->Divide(3,2);

	c1->cd(1);
	tr->Draw("trigger", "", "", lowStatEntries);
	c1->Update();

	c1->cd(2);
	var.Form("Length$(%s)", CTX.Data());
	con.Form("Length$(%s)>0", CTX.Data());
	tr->Draw(var, con + "&& trigger==2", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult CTX, trigger==2");
	c1->Update();

	c1->cd(5);
	var.Form("Length$(%s)", CTX.Data());
	con.Form("Length$(%s)>0", CTX.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult CTX, trigger==3");
	c1->Update();

	c1->cd(3);
	var.Form("Length$(%s)", CTY.Data());
	con.Form("Length$(%s)>0", CTY.Data());
	tr->Draw(var, con + "&& trigger==2", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult CTY, trigger==2");
	c1->Update();

	c1->cd(6);
	var.Form("Length$(%s)", CTY.Data());
	con.Form("Length$(%s)>0", CTY.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult CTY, trigger==3");
	c1->Update();

	TCanvas *c1_1 = new TCanvas("c1_1", "c1_1: Auxiliary information on trigger and CT multiplicity", 1000, 500);
	c1_1->Divide(2,1);

	c1_1->cd(1);
	var.Form("Length$(%s)", CTCsI.Data());
	con.Form("Length$(%s)>0", CTCsI.Data());
	tr->Draw(var, con + "&& trigger==2", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult CTCsI, trigger==2");
	c1_1->Update();

	c1_1->cd(2);
	var.Form("Length$(%s)", CTCsI.Data());
	con.Form("Length$(%s)>0", CTCsI.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult CTCsI, trigger==3");
	c1_1->Update();


}

void DrawCTaux() {

	const Long64_t lowStatEntries = 100000;

	TCanvas *c2 = new TCanvas("c2", "c2: Auxiliary information on CT", 1500, 1000);
	c2->Divide(3,2);

	c2->cd(1);
	var.Form("%s.fStripNb", CTX.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired X strip C 1mm, trigger==3");
	c2->Update();

	c2->cd(2);
	var.Form("%s.fStripNb", CTY.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired Y strip C 1mm, trigger==3");
	c2->Update();

	c2->cd(3);
	var.Form("%s.fBlockNb", CTCsI.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired CsI block, trigger==3");
	c2->Update();

	c2->cd(5);
	var.Form("%s.fStripNb", CTY.Data());
	con.Form("%s.fStripNb!=12", CTY.Data());
	tr->Draw(var, con + "&& trigger==3", "", lowStatEntries);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired Y strip C, trigger==3, strip 12 excluded");
	c2->Update();

	c2->cd(4);
	tr->Draw("BeamDetToFDigi2.fTime", "Length$(BeamDetToFDigi2)==1", "", lowStatEntries);
	c2->Update();
}

void DrawIDplotCraw(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0) {

	const Long64_t lowStatEntries = 10000000;

	TCanvas *c3 = new TCanvas("c3", "c3: dE-E: 1mm vs. CsI, mults==1, trigger==3", 1000, 1000);
	Int_t noPads = DivideCanvas(c3, firstStrip, showNoStrips);
//	c3->Divide(4,4);

	for (Int_t i = 0; i < noPads; i++) {
		c3->cd(i+1);
		if (i+firstStrip==9) continue;
		var.Form("%s.fEdep*1000:%s.fEdep", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && Length$(%s)==1",
				CTCsI.Data(), i+firstStrip, CTX.Data(), CTCsI.Data());
		//		cout << var << endl;
		tr->Draw(var, con + "&& trigger==3", "col", lowStatEntries);
		TString hTitle;
		hTitle.Form("dE-E: CsI==%d", i+firstStrip);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats();
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("ch");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
		c3->Update();
	}
}

void DrawTestOfCsImaxAmp(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, Bool_t showDrawTest = 0) {

	if (showDrawTest) {

		Info("DrawTestOfCsImaxAmp", "Test of methodic used in TTree::Draw");

		TCanvas *c4 = new TCanvas("c4", "c4: dE-E: 1mm vs. veto(1mm), mults==1, target selected", 1000, 1000);
		//	c4->Divide(4,4);
		c4->Divide(2,2);


		//	con.Form("%s.fStripNb == %d && Length$(%s)==1 && Length$(%s)==1",
		//			RTY.Data(), i, RTY.Data(), RT3rd.Data());
		con.Form("%s.fEdep > 0",
				CTCsI.Data());

		c4->cd(1);
		var.Form("Max$(%s.fEdep)", CTCsI.Data());
		tr->Draw(var, con, "", 100000);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Max. amp in CsI");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("ch");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");

		c4->cd(3);
		var.Form("Min$(%s.fEdep)", CTCsI.Data());
		tr->Draw(var, con, "", 100000);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Min. amp in CsI");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("ch");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");

		c4->cd(2);
		var.Form("Max$(%s.fEdep)", CTCsI.Data());
		con.Form("%s.fEdep > 0 && Length$(%s)==1",
				CTCsI.Data(), CTCsI.Data());
		tr->Draw(var, con, "", 100000);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Max. amp in CsI, mult==1");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("ch");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");

		c4->cd(4);
		var.Form("Min$(%s.fEdep)", CTCsI.Data());
		con.Form("%s.fEdep > 0 && Length$(%s)==1",
				CTCsI.Data(), CTCsI.Data());
		tr->Draw(var, con, "", 100000);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Min. amp in CsI, mult==1");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("ch");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
		c4->Update();
	}

	const Long64_t lowStatEntries = 10000000;

	TCanvas *c4_1 = new TCanvas("c4_1", "c4_1: dE-E: Si vs. max. energy in CsI, mult(Si)==1", 1000, 1000);
	Int_t noPads = DivideCanvas(c4_1, firstStrip, showNoStrips);

	for (Int_t i = 0; i < noPads; i++) {
		c4_1->cd(i+1);
		if (i+firstStrip==9) continue;
		var.Form("%s.fEdep*1000:Max$(%s.fEdep)*1000", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1",
				CTCsI.Data(), i+firstStrip, CTX.Data());
		//		cout << var << endl;
//		tr->Draw(var, con + "&& trigger==3 && ( (fYt-2.)^2 + fXt^2 ) < 8.^2", "", 100000);
		tr->Draw(var, con + "&& trigger==3", "col", lowStatEntries);
		TString hTitle;
		hTitle.Form("dE-E: CsI==%d", i+firstStrip);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH1F*)gPad->GetPrimitive("htemp"))->SetStats();
		((TH1F*)gPad->GetPrimitive("htemp"))->SetXTitle("ch");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
		c4_1->Update();
	}
}

void DrawTauAmp(const Bool_t xstrips = 1, const Bool_t ystrips = 1,
		const Bool_t crystals = 1, const Bool_t makeCsICuts = 0) {

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	if (xstrips) {
		TCanvas *c5_1 = new TCanvas("c5_1", "c5_1: central X Si dE-tau, trigger==3", 1000, 1000);
		c5_1->Divide(4,4);

		for (Int_t i = 0; i < 16; i++) {
			c5_1->cd(i+1);

			tr->SetMarkerSize(0.1);

			tr->SetMarkerColor(kBlack);
			var.Form("%s.fEdep*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", CTX.Data(), CTX.Data());
			con.Form("%s.fStripNb == %d"
					"&& %s.fTime-BeamDetToFDigi2.fTime/2.>0. && %s.fTime-BeamDetToFDigi2.fTime/2.<400.",
					CTX.Data(), i,
					CTX.Data(), CTX.Data());
			//		cout << var << endl;
			tr->Draw(var, con + "&& trigger==3", "", 1000000);
			TString hTitle;
			hTitle.Form("dE-tau: stripX==%d", i);
			((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
			((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("ns");
			((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
			c5_1->Update();

			tr->SetMarkerColor(kRed);
			con.Form("%s.fStripNb == %d && %s",
					CTX.Data(), i, timeConditonCX.Data());
			tr->Draw(var, con + "&& trigger==3", "same", 1000000);
			c5_1->Update();

			tr->SetMarkerColor(kGreen);
			tr->SetMarkerSize(1.4);
			con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
					+ genCon
					+ "&&" + targetCondition
					+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
					+ "&&" + Form("%s.fStripNb == %d", CTX.Data(), i)
					;
			tr->Draw(var, con, "same");
			c5_1->Update();
		}

		TCanvas *c5_2 = new TCanvas("c5_2", "c5_2: central X Si dE-tau, trigger==3", 1000, 1000);
		c5_2->Divide(4,4);

		for (Int_t i = 0; i < 16; i++) {
			c5_2->cd(i+1);

			tr->SetMarkerSize(0.1);

			tr->SetMarkerColor(kBlack);
			var.Form("%s.fEdep*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", CTX.Data(), CTX.Data());
			//		var.Form("%s.fEdep*1000:%s.fTime", CTX.Data(), CTX.Data());
			con.Form("%s.fStripNb == %d"
					"&& %s.fTime-BeamDetToFDigi2.fTime/2.>0. && %s.fTime-BeamDetToFDigi2.fTime/2.<400.",
					CTX.Data(), i+16,
					CTX.Data(), CTX.Data());
			//		cout << var << endl;
			tr->Draw(var, con + "&& trigger==3", "", 1000000);
			TString hTitle;
			hTitle.Form("dE-tau: stripX==%d", i+16);
			((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
			((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("ns");
			((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
			c5_2->Update();

			tr->SetMarkerColor(kRed);
			con.Form("%s.fStripNb == %d && %s",
					CTX.Data(), i+16, timeConditonCX.Data());
			tr->Draw(var, con + "&& trigger==3", "same", 1000000);
			c5_2->Update();

			tr->SetMarkerColor(kGreen);
			tr->SetMarkerSize(1.4);
			con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
					+ genCon
					+ "&&" + targetCondition
					+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
					+ "&&" + Form("%s.fStripNb == %d", CTX.Data(), i+16)
					;
			tr->Draw(var, con, "same");
			c5_2->Update();
		}

	}//if X strips

	if (ystrips) {
		TCanvas *c5_3 = new TCanvas("c5_3", "c5_3: central Y Si dE-tau, trigger==3", 1000, 1000);
		c5_3->Divide(4,4);

		for (Int_t i = 0; i < 16; i++) {
			c5_3->cd(i+1);

			tr->SetMarkerSize(0.1);

			tr->SetMarkerColor(kBlack);
			var.Form("%s.fEdep*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", CTY.Data(), CTY.Data());
			//		var.Form("%s.fEdep*1000:%s.fTime", CTX.Data(), CTX.Data());
			con.Form("%s.fStripNb == %d"
					"&& %s.fTime-BeamDetToFDigi2.fTime/2.>0. && %s.fTime-BeamDetToFDigi2.fTime/2.<400.",
					CTY.Data(), i,
					CTY.Data(), CTY.Data());
			//		cout << var << endl;
			tr->Draw(var, con + "&& trigger==3", "", 1000000);
			TString hTitle;
			hTitle.Form("dE-tau: stripY==%d", i);
			((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
			((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("ns");
			((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
			c5_3->Update();

			tr->SetMarkerColor(kRed);
			con.Form("%s.fStripNb == %d && %s",
					CTY.Data(), i, timeConditonCY.Data());
			tr->Draw(var, con + "&& trigger==3", "same", 1000000);
			c5_3->Update();

			tr->SetMarkerColor(kGreen);
			tr->SetMarkerSize(1.4);
			con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
					+ genCon
					+ "&&" + targetCondition
					+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
					+ "&&" + Form("%s.fStripNb == %d", CTY.Data(), i)
					;
			tr->Draw(var, con, "same");
			c5_3->Update();
		}

		TCanvas *c5_4 = new TCanvas("c5_4", "c5_4: central Y Si dE-tau, trigger==3", 1000, 1000);
		c5_4->Divide(4,4);

		for (Int_t i = 0; i < 16; i++) {
			c5_4->cd(i+1);

			tr->SetMarkerSize(0.1);

			tr->SetMarkerColor(kBlack);
			var.Form("%s.fEdep*1000:%s.fTime - BeamDetToFDigi2.fTime/2.", CTY.Data(), CTY.Data());
			//		var.Form("%s.fEdep*1000:%s.fTime", CTX.Data(), CTX.Data());
			con.Form("%s.fStripNb == %d"
					"&& %s.fTime-BeamDetToFDigi2.fTime/2.>0. && %s.fTime-BeamDetToFDigi2.fTime/2.<400.",
					CTY.Data(), i+16,
					CTY.Data(), CTY.Data());
			//		cout << var << endl;
			tr->Draw(var, con + "&& trigger==3", "", 1000000);
			TString hTitle;
			hTitle.Form("dE-tau: stripY==%d", i+16);
			((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
			((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("ns");
			((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
			c5_4->Update();

			tr->SetMarkerColor(kRed);
			con.Form("%s.fStripNb == %d && %s",
					CTY.Data(), i+16, timeConditonCY.Data());
			tr->Draw(var, con + "&& trigger==3", "same", 1000000);
			c5_4->Update();

			tr->SetMarkerColor(kGreen);
			tr->SetMarkerSize(1.4);
			con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
					+ genCon
					+ "&&" + targetCondition
					+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
					+ "&&" + Form("%s.fStripNb == %d", CTY.Data(), i+16)
					;
			tr->Draw(var, con, "same");
			c5_4->Update();
		}
	}// if Y strips

	if (crystals) {

		TCanvas *c5_5 = new TCanvas("c5_5", "c5_5: central CsI max(dE)-tau, trigger==3", 1000, 1000);
		c5_5->Divide(4,4);

		TCanvas *cEtauCuts[16];
		Long64_t drawEvents = 1000000;
//		Long64_t drawEvents = 10000000;

//		if (!makeCsICuts) {
//			cutsCsI();
//		}

		for (Int_t i = 0; i < 16; i++) {

			//make particular canvases to draw graphical cuts
			if (makeCsICuts) {
				cEtauCuts[i] = new TCanvas();
				cEtauCuts[i]->ToggleToolBar();
				cEtauCuts[i]->ToggleEditor();
				cEtauCuts[i]->ToggleEventStatus();
				drawEvents = 5000000;
			}
			//use one divided canvas to show results
			else c5_5->cd(i+1);
			//crystal No.9 is omitted in analysis
			if (i==9) continue;

			tr->SetMarkerColor(kBlack);
//			var.Form("%s.fEdep:%s.fTime - BeamDetToFDigi2.fTime/2.", CTCsI.Data(), CTCsI.Data());
			var.Form("Max$(%s.fEdep):%s.fTime - BeamDetToFDigi2.fTime/2.", CTCsI.Data(), CTCsI.Data());
			con.Form("%s.fBlockNb == %d"
					"&& Length$(%s)==1"
					"&& %s.fTime-BeamDetToFDigi2.fTime/2.>-400. && %s.fTime-BeamDetToFDigi2.fTime/2.<200.",
					CTCsI.Data(), i,
					CTCsI.Data(),
					CTCsI.Data(), CTCsI.Data()
					);

//			tr->Draw(var, con + "&& trigger==3", "", 10*drawEvents);
			tr->Draw(var, con + "&& trigger==3", "col", drawEvents);
			TString hTitle;
			hTitle.Form("crystal==%d", i);
			((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
			gPad->Update();

//
//			cCsI[i]->Draw("same");

//
			tr->SetMarkerColor(kRed);
			tr->SetMarkerSize(.3);
//			tr->Draw(var, con + "&& trigger==3 && ( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2", "same", 10*drawEvents);

			cCsI[i]->SetLineColor(kBlue);
			cCsI[i]->SetLineWidth(3);
//			cCsI[i]->Draw("same");

			//following operations may be performed
			//only if not creating graphical cuts
			if (!makeCsICuts) {
				TString hTitle;
				hTitle.Form("dE-tau: crystal==%d", i);
				((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
				((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("ns");
				((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
				gPad->Update();


				cCsI[i]->Draw();


				tr->SetMarkerColor(kRed);
				//condition of non-zero time in F5 is important
				//and should be used bellow
				con.Form("%s.fBlockNb == %d && %s"
						"&& BeamDetToFDigi2.fTime/2.>0.",
						CTCsI.Data(), i, cCsI[i]->GetName()
				);
				tr->Draw(var, con + " && trigger==3", "same", drawEvents);

				tr->SetMarkerColor(kGreen);
				tr->SetMarkerSize(1.4);
				con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
						+ genCon
						+ "&&" + targetCondition
						+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
						+ "&&" + Form("%s.fBlockNb == %d", CTCsI.Data(), i)
						;
				tr->Draw(var, con, "same");
				c5_5->Update();
			}
			gPad->Update();
		}
	}

}

void DrawCleanTritons(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0) {

	TCanvas *c6 = new TCanvas("c6", "c6: dE-E: Si vs. max(CsI), mult(Si)==1, CsI time cuts", 1000, 1000);
//	c6->Divide(4,4);
	Int_t noPads = DivideCanvas(c6, firstStrip, showNoStrips);

	TCanvas *cTritonCuts[16];

	Long64_t tCount = 0;

	Info("DrawCleanTritons", "Green points - all statistics");

	for (Int_t i = 0; i < noPads; i++) {
		//make particular canvases to draw graphical cuts
		if (makeCuts) {
			cTritonCuts[i] = new TCanvas();
			cTritonCuts[i]->ToggleToolBar();
			cTritonCuts[i]->ToggleEditor();
			cTritonCuts[i]->ToggleEventStatus();
		}
		//use one divided canvas to show results
		else c6->cd(i+1);
		//crystal No.9 is omitted in analysis
		if (i+firstStrip==9) continue;

		cTritium[i+firstStrip]->Draw();
		cTritium[i+firstStrip]->SetLineColor(kBlue);
		cTritium[i+firstStrip]->SetLineWidth(3);
		gPad->Update();

		tr->SetMarkerSize(0.5);

		tr->SetMarkerColor(kBlack);
		var.Form("%s.fEdep*1000:Max$(%s.fEdep)", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016 "
//				"&& Max$(%s.fEdep)<2000",
				"&& Max$(%s.fEdep)<200",
				CTCsI.Data(), i+firstStrip, CTX.Data(), CTX.Data(), CTCsI.Data());
		tr->Draw(var, con + "&& trigger==3", "", 1000000);
		TString hTitle;
		hTitle.Form("dE-E: CsI==%d", i+firstStrip);
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("MeV");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
		gPad->Update();

		cTritium[i+firstStrip]->Draw();
		gPad->Update();

		tr->SetMarkerColor(kRed);
		//condition of non-zero time in F5 is important
		//and should be used bellow
		con.Form("%s.fBlockNb == %d"
				"&& Length$(%s)==1 && %s"
				"&& %s && BeamDetToFDigi2.fTime/2.>0."
				"&& %s",
				CTCsI.Data(), i+firstStrip,
				CTX.Data(), timeConditonCX.Data(),
				cCsI[i+firstStrip]->GetName(),
				targetCondition.Data()
		);
		tr->Draw(var, con + " && trigger==3", "same");
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		//condition of non-zero time in F5 is important
		//and should be used bellow
		con.Form("%s.fBlockNb == %d"
				"&& Length$(%s)==1 && %s"
				"&& %s && BeamDetToFDigi2.fTime/2.>0."
				"&& %s"
				"&& %s",
				CTCsI.Data(), i+firstStrip,
				CTX.Data(), timeConditonCX.Data(),
				cCsI[i+firstStrip]->GetName(),
				targetCondition.Data(),
				cTritium[i+firstStrip]->GetName()
		);
		Long64_t currTritiumCount = tr->Draw(var, con + " && trigger==3", "same");
		tCount += currTritiumCount;
		cout << currTritiumCount << endl;
		gPad->Update();


	}//for crystals

	Info("DrawCleanTritons", "%lld tritons found in whole data.", tCount);

}

void DrawCleanTritonsWithHe(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0) {

	TCanvas *c6 = new TCanvas("c6", "c6: dE-E: Si vs. max(CsI), mult(Si)==1, CsI time cuts", 1000, 1000);
//	c6->Divide(4,4);
	Int_t noPads = DivideCanvas(c6, firstStrip, showNoStrips);

	TCanvas *cTritonCuts[16];

	Long64_t tCount = 0;

	Info("DrawCleanTritons", "Green points - all statistics");

	for (Int_t i = 0; i < noPads; i++) {
		//make particular canvases to draw graphical cuts
		if (makeCuts) {
			cTritonCuts[i] = new TCanvas();
			cTritonCuts[i]->ToggleToolBar();
			cTritonCuts[i]->ToggleEditor();
			cTritonCuts[i]->ToggleEventStatus();
		}
		//use one divided canvas to show results
		else c6->cd(i+1);
		//crystal No.9 is omitted in analysis
		if (i+firstStrip==9) continue;

		cTritium[i+firstStrip]->Draw();
		cTritium[i+firstStrip]->SetLineColor(kBlue);
		cTritium[i+firstStrip]->SetLineWidth(3);
		gPad->Update();

		tr->SetMarkerColor(kBlack);
		tr->SetMarkerSize(0.2);
		var.Form("%s.fEdep*1000:Max$(%s.fEdep)", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016 && Max$(%s.fEdep)<200",
				CTCsI.Data(), i+firstStrip, CTX.Data(), CTX.Data(), CTCsI.Data());
		tr->Draw(var, con + "&& trigger==3", "", 1000000);
		TString hTitle;
		hTitle.Form("dE-E: CsI==%d", i+firstStrip);
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("MeV");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
		gPad->Update();

		cTritium[i+firstStrip]->Draw();
		gPad->Update();

		tr->SetMarkerColor(kRed);
		//condition of non-zero time in F5 is important
		//and should be used bellow
		con.Form("%s.fBlockNb == %d"
				"&& Length$(%s)==1 && %s"
				"&& %s && BeamDetToFDigi2.fTime/2.>0."
				"&& %s",
				CTCsI.Data(), i+firstStrip,
				CTX.Data(), timeConditonCX.Data(),
				cCsI[i+firstStrip]->GetName(),
				targetCondition.Data()
		);
		tr->Draw(var, con + " && trigger==3", "same");
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		tr->SetMarkerSize(0.9);
		//condition of non-zero time in F5 is important
		//and should be used bellow
		con.Form("%s.fBlockNb == %d"
				"&& Length$(%s)==1 && %s"
				"&& %s && BeamDetToFDigi2.fTime/2.>0."
				"&& %s"
				"&& %s",
				CTCsI.Data(), i+firstStrip,
				CTX.Data(), timeConditonCX.Data(),
				cCsI[i+firstStrip]->GetName(),
				targetCondition.Data(),
				cTritium[i+firstStrip]->GetName()
		);
		con.Append(" && " + (TString)cHelium3[i+firstStrip]->GetName());
		con.Append(" && fRTEdepCorr > 0. && fRTEdepCorr < 0.002");
		con.Append(" && " + MWPCtimeCondition);
		con.Append(" && " + beamIdCondition);
		Long64_t currTritiumCount = tr->Draw(var, con + " && trigger==3", "same");
		tCount += currTritiumCount;
		cout << currTritiumCount << endl;
		gPad->Update();


	}//for crystals

	Info("DrawCleanTritons", "%lld tritons found in whole data.", tCount);

}
