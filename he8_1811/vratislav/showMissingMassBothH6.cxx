#if !defined(__CLING__)


//#include "../install/include/conversion/ConvertRepackedToCalibrated.h"
//#include "../install/include/data/DetEventCommon.h"
#include "TFile.h"
//#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TLatex.h"
//#include "TLine.h"
#include "TMarker.h"
//#include "TLegend.h"
//#include "TLegendEntry.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"


#include <iostream>

using std::cout;
using std::endl;

#endif

#include "cutsRTY.cxx"
#include "cutsRT20X.cxx"
#include "cutsHelium3.cxx"
#include "cutsLTHelium3.cxx"
//todo: to be deleted:
//#include "cutsHelium4.cxx"
#include "cutsTritiumCal.cxx"
#include "cutsDeuteriumCal.cxx"
#include "cutsCsIcal.cxx"

//RT first layer
const TString RT20X = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0";
//RT second layer
const TString RTY = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0";
//RT third layer
const TString RT3rd = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0";

//left telescope
TString LT20X = "ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0";
TString LTY = "ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_Y";
TString LTX = "ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X";
TString LT3rd = "ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD_L_X_0";

//CsI layer
const TString CTCsI = "ERQTelescopeCsIDigi_Central_telescope_CsI_0";

TChain *tr;
TChain *trIn;

//TMarker *mP[3][4];  //[energies][particles], energies: 10, 20, 30 MeV, particles: 3,4,6,8He
//TMarker *mPcorrected[16][3][4]; //the same but for different strips

//auxiliary variables
TString var;
TString con;

//global conditions:
TString targetCondition;
//TString timeCondY;
TString timeCondCsI;
//TString MWPCtimeCondition;
//TString beamIdCondition;

const Double_t m8He = 7482.5396;
const Double_t m3He = 2808.391;
const Double_t m2H = 1875.6128;
const Double_t m3H = 2808.9207;
const Double_t mn = 939.5653;
const Double_t m4He = 3727.379;		//mass of 4He in MeV

const Double_t cut4HeEnergy = 20.;
const Int_t kMMbins = 25;
const Double_t massOfProducts = m3H+3*mn;		//4-body decay with tritium
const Double_t massOfProducts5bDecay = m2H+4*mn;		//5-body decay with deuterium

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0);
void InitExternalCuts();
TString MakeGeneralTritiumCut();
TString MakeGeneralDeuteriumCut();

void DrawTargetPosition(TString beamProjCondition = "");

void DrawMMspectrumRT6H();
void DrawMMspectrumLT6H();

void DrawMMspectrumBoth6HwithT();
void DrawMMspectrumBoth6HwithD();
//void DrawMMspectrumTritiumSelection();
void DrawMMspectrumCM6HwithT();
void DrawMMspectrumCM6HwithD();

void DrawAnglesFor6HwithT();
void DrawAnglesFor6HwithD();

void DrawCMreaction6HwithT();

void DrawMMspectrumPureTrianglesT();
void DrawMMspectrumPureTrianglesD();

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void DrawMMspectrumAngles();
void DrawMMspectrumAnalysis();
void DrawCorrelationsEnergies();
void DrawCorrelationsAngles();
void DrawAngularAnalysis();
void DrawMMsplitted3HeLABAngle();

TString genCon;
TString genConDeuterium;

void showMissingMassBothH6(const Bool_t allStat = 1) {

	InitTrees(allStat);
//	InitTrees(allStat, 1);

	InitExternalCuts();

	genCon =
			MakeGeneralTritiumCut() + " && "
//			MakeGeneralDeuteriumCut() + " && "
			+ Form("f4HeMeasuredCorrected.E()-%f<%f", m4He, cut4HeEnergy);

	genConDeuterium =
//			MakeGeneralTritiumCut() + " && "
			MakeGeneralDeuteriumCut() + " && "
			+ Form("f4HeMeasuredCorrected.E()-%f<%f", m4He, cut4HeEnergy);

//	DrawTargetPosition();

//	DrawMMspectrumRT6H();
//	DrawMMspectrumLT6H();
	DrawMMspectrumBoth6HwithT();
	DrawMMspectrumBoth6HwithD();

	DrawMMspectrumCM6HwithT();
	DrawMMspectrumCM6HwithD();

//	DrawAnglesFor6HwithT();
//	DrawAnglesFor6HwithD();

	//there is no need to investigate coincidences with deuterium
//	DrawCMreaction6HwithT();

	DrawMMspectrumPureTrianglesT();
	DrawMMspectrumPureTrianglesD();

	////////////////////////////////////////
	////////////////////////////////////////

//	DrawAngularAnalysis();
//
//	DrawCorrelationsEnergies();
//	DrawCorrelationsAngles();

//	DrawMMspectrumAngles();
//	DrawAngularAnalysis();

//	DrawMMsplitted3HeLABAngle();

//	DrawMMspectrumAngles();

//	DrawMMspectrumAnalysis();


//	tr->StartViewer();

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
//	tr->SetMarkerSize(0.1);
	tr->SetMarkerSize(0.7);

}

void InitExternalCuts() {
	const Bool_t useFirstLayerCuts = 1;
	const Bool_t useSecondLayerCuts = 1;
	const Bool_t useHeliumCuts = 1;
	const Bool_t useTritiumCuts = 1;
	const Bool_t useDeuteriumCuts = 1;
	const Bool_t useCsICuts = 1;

	//todo: to be deleted
	if (useSecondLayerCuts) {
		cutsRT20X();
	}

	//todo: to be deleted
	if (useSecondLayerCuts) {
		cutsRTY();
	}

	//todo: to be deleted
	if (useHeliumCuts) {
		cutsHelium3();
	}

	if (useTritiumCuts) {
		cutsTritium();
	}

	if (useDeuteriumCuts) {
		cutsDeuterium();
	}

	if (useCsICuts) {
		cutsCsI();
	}

	//time condition for Y strips from cutsRTY()
//	timeCondY.Form("(cutRTY_0 || cutRTY_1 || cutRTY_2 || cutRTY_3"
//			" || cutRTY_4 || cutRTY_5 || cutRTY_6 || cutRTY_7"
//			" || cutRTY_8 || cutRTY_9 || cutRTY_10 || cutRTY_11"
//			" || cutRTY_12 || cutRTY_13 || cutRTY_14 || cutRTY_15)");

	timeCondCsI.Form("(cutCsI_0 || cutCsI_1 || cutCsI_2 || cutCsI_3"
			" || cutCsI_4 || cutCsI_5 || cutCsI_6 || cutCsI_7"
			" || cutCsI_8 || cutCsI_10 || cutCsI_11"
			" || cutCsI_12 || cutCsI_13 || cutCsI_14 || cutCsI_15)");

	//condition on position in the center of the target
//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 6^2";
	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	//time in MWPC's
//	TString MWPCX1 = "BeamDetMWPCDigiX1";
//	TString MWPCY1 = "BeamDetMWPCDigiY1";
//	TString MWPCX2 = "BeamDetMWPCDigiX2";
//	TString MWPCY2 = "BeamDetMWPCDigiY2";

//	MWPCtimeCondition.Form("(%s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95. "
//			"&& %s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95. "
//			"&& %s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95. "
//			"&& %s.fTime/2.-BeamDetToFDigi2.fTime/2. > 65. && %s.fTime/2.-BeamDetToFDigi2.fTime/2. < 95.)",
//			MWPCX1.Data(), MWPCX1.Data(),
//			MWPCY1.Data(), MWPCY1.Data(),
//			MWPCX2.Data(), MWPCX2.Data(),
//			MWPCY2.Data(), MWPCY2.Data()
//	);
//
//	//8He cut
//	beamIdCondition = "BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >200."
//				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 240."
//				" && BeamDetToFDigi2.fEdep>2600."
//				" && BeamDetToFDigi2.fEdep<4300.";
}

TString MakeGeneralTritiumCut() {

	TString cut;

	//for 16 crystals except No.9
	cut.Form(" (%s", cTritium[0]->GetName());
	for (Int_t i = 1; i < 16; i++) {
		if (i==9) continue;
		cut.Append(" || " + (TString)cTritium[i]->GetName());
	}
	cut.Append(")");

//	timeCondCsI.Form("(cutCsI_0 || cutCsI_1 || cutCsI_2 || cutCsI_3"
//			" || cutCsI_4 || cutCsI_5 || cutCsI_6 || cutCsI_7"
//			" || cutCsI_8 || cutCsI_10 || cutCsI_11"
//			" || cutCsI_12 || cutCsI_13 || cutCsI_14 || cutCsI_15)");

	cut.Append(" && " + timeCondCsI + " && fTFlag");

//	cout << cut << endl;

	return cut;
}

TString MakeGeneralDeuteriumCut() {

	TString cut;

	//for 16 crystals except No.9
	cut.Form(" (%s", cDeuterium[0]->GetName());
	for (Int_t i = 1; i < 16; i++) {
		if (i==9) continue;
		cut.Append(" || " + (TString)cDeuterium[i]->GetName());
	}
	cut.Append(")");

//	timeCondCsI.Form("(cutCsI_0 || cutCsI_1 || cutCsI_2 || cutCsI_3"
//			" || cutCsI_4 || cutCsI_5 || cutCsI_6 || cutCsI_7"
//			" || cutCsI_8 || cutCsI_10 || cutCsI_11"
//			" || cutCsI_12 || cutCsI_13 || cutCsI_14 || cutCsI_15)");

	cut.Append(" && " + timeCondCsI + " && fTFlag");

//	cout << cut << endl;

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

	if (noPads<=1) c->Divide(1,1);
	if (noPads<=4 && noPads>1) c->Divide(2,2);
	if (noPads>4 && noPads<=6) c->Divide(3,2);
	if (noPads>6 && noPads<=8) c->Divide(4,2);
	if (noPads==9) c->Divide(3,3);
	if (noPads>9 && noPads<=12) c->Divide(4,3);
	if (noPads>12) c->Divide(4,4);

	return noPads;
}

void DrawTargetPosition(TString beamProjCondition = "") {

//	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
//	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, used %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cTargetPosMM", "cTargetPosMM: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1000, 1000);

	tr->SetMarkerSize(0.2);
	tr->SetMarkerColor(kBlack);
	tr->Draw("fYt:fXt", "fYt>-40. && fXt>-40.", "col");
	gPad->Update();
	tr->SetMarkerSize(0.9);
	tr->SetMarkerColor(kBlue);

	if (beamProjCondition == "") {
		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9^2";
	} else {
		targetCondition = beamProjCondition;
	}

	tr->Draw("fYt:fXt", "fHeFlagRT==1 || fHeFlagLT==1", "same");
	gPad->Update();
	tr->SetMarkerColor(kGreen);
	cout << tr->Draw("fYt:fXt",
			"(fHeFlagRT==1 || fHeFlagLT==1) && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition, "same") << endl;
	gPad->Update();

}

void DrawMMspectrumRT6H() {

	Info("DrawMMspectrumRT6H",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMRight",
			"cHeMMRight: 6H missing mass from right telescope",
			1500, 600);
	c->Divide(3,1);

	con = "(f4HeFlagRT==1) && " + genCon;
//			+ MakeGeneralTritiumCut() + " && "
//			+ MakeGeneralDeuteriumCut() + " && "
//			+ Form("f4HeMeasuredCorrected.E()-%f<%f", m4He, cut4HeEnergy);

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565>>hMMmeas(14, -5., 21.)",
	tr->Draw(Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas(%d, -5., 21.)", massOfProducts, kMMbins),
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->SetTitle("measured E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565>>hMMmeas8(14, -5., 21.)",
	tr->Draw(Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas8(%d, -5., 21.)", massOfProducts, kMMbins),
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565>>hMMmeas7(14, -5., 21.)",
	tr->Draw(Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas7(%d, -5., 21.)", massOfProducts, kMMbins),
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->SetTitle("measured E(^{3}He), r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

}

void DrawMMspectrumLT6H() {

	Info("DrawMMspectrumLT",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMLeft",
			"cHeMMLeft: 6H missing mass from left telescope",
			1500, 600);
	c->Divide(3,1);

	con = "(f4HeFlagLT==1) && " + genCon;
//			+ MakeGeneralTritiumCut() + " && "
//			+ MakeGeneralDeuteriumCut() + " && "
//			+ Form("f4HeMeasuredCorrected.E()-%f<%f", m4He, cut4HeEnergy);



	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565>>hMMmeasLT(14, -5., 21.)",
	tr->Draw(Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeasLT(%d, -5., 21.)", massOfProducts, kMMbins),
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeasLT"))->SetTitle("measured E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeasLT"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasLT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565>>hMMmeas8LT(14, -5., 21.)",
	tr->Draw(Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas8LT(%d, -5., 21.)", massOfProducts, kMMbins),
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas8LT"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8LT"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8LT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565>>hMMmeas7LT(14, -5., 21.)",
	tr->Draw(Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas7LT(%d, -5., 21.)", massOfProducts, kMMbins),
//	tr->Draw("fHydrogen6MeasuredCorrected.Mag()-2808.92-3*939.565",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas7LT"))->SetTitle("measured E(^{3}He), r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7LT"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7LT"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

}

void DrawMMspectrumBoth6HwithT() {

	Info("DrawMMspectrumBoth6HwithT",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMBothT",
			"cHeMMBothT: 6H missing mass from both telescopes, 4-body decay",
			1500, 600);
	c->Divide(3,1);

	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genCon;

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeasBothT(%d, -5., 21.)", massOfProducts, kMMbins);
	tr->Draw(var, con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeasBothT"))->SetTitle("MM from E(^{4}He), r_{beam} = 9 mm, 4-body");
	((TH1F*)gPad->GetPrimitive("hMMmeasBothT"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasBothT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas8BothT(%d, -5., 21.)", massOfProducts, kMMbins);
	tr->Draw(var, con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothT"))->SetTitle("MM from E(^{4}He), r_{beam} = 8 mm, 4-body");
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothT"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas7BothT(%d, -5., 21.)", massOfProducts, kMMbins);
	tr->Draw(var, con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothT"))->SetTitle("MM from E(^{4}He), r_{beam} = 7 mm, 4-body");
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothT"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

}

void DrawMMspectrumBoth6HwithD() {

	Info("DrawMMspectrumBoth6HwithD",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMBothD",
			"cHeMMBothD: 6H missing mass from both telescopes, 5-body decay",
			1500, 600);
	c->Divide(3,1);

	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genConDeuterium;

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeasBothD(%d, -5., 21.)",
			massOfProducts5bDecay, kMMbins);
	tr->Draw(var, con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeasBothD"))->SetTitle("MM from E(^{4}He), r_{beam} = 9 mm, 5-body");
	((TH1F*)gPad->GetPrimitive("hMMmeasBothD"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasBothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas8BothD(%d, -5., 21.)",
			massOfProducts5bDecay, kMMbins);
	tr->Draw(var, con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothD"))->SetTitle("MM from E(^{4}He), r_{beam} = 8 mm, 5-body");
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothD"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f>>hMMmeas7BothD(%d, -5., 21.)",
			massOfProducts5bDecay, kMMbins);
	tr->Draw(var, con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothD"))->SetTitle("MM from E(^{4}He), r_{beam} = 7 mm, 5-body");
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothD"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

}

void DrawMMspectrumCM6HwithT() {

	Info("DrawMMspectrumCM6H", "Missing mass of 6H from 4He; 4-body decay");
	Info("DrawMMspectrumCM6H",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM",
			"cHeMM_CM: Both detectors, 6H, 4-body decay",
			1400, 1200);
	c->Divide(3,3);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	//////////////////////////////
	//Golovkov triangle
	//////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "1*x/2", 0, 16);
//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
	TString conTriangle = Form(" && fTMeasuredCorrectedCM6H.E()-%f <= -1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-%f)",
			m3H, massOfProducts);

	////////////////////////////
	//6H MM measured right
	////////////////////////////

	///*
	con = "(f4HeFlagRT==1) && " + genCon;

	c->cd(1);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f", m3H);
	tr->Draw(var+">>hTcmMeasRight(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hTcmMeasRight"))->SetTitle("Right, E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hTcmMeasRight"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hTcmMeasRight"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(2);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f", m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Right, corr MM(^{6}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetMarkerColor(kBlack);

	c->cd(3);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas8CMrightT(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightT"))->SetTitle("Right, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightT"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();
	//*/

	////////////////////////////
	//6H MM measured left
	////////////////////////////

	///*
	con = "(f4HeFlagLT==1) && " + genCon;

	c->cd(4);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f", m3H);
	tr->Draw(var+">>hTcmMeasLeft(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hTcmMeasLeft"))->SetTitle("Left, E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hTcmMeasLeft"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hTcmMeasLeft"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f", m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Left, corr MM(^{6}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetMarkerColor(kBlack);

	c->cd(6);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas8CMleftT(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftT"))->SetTitle("Left, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftT"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();
	//*/


	////////////////////////////
	//6H MM measured both
	////////////////////////////

	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genCon;

	c->cd(7);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f", m3H);
	tr->Draw(var+">>hTcmMeasBoth(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hTcmMeasBoth"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hTcmMeasBoth"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hTcmMeasBoth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(8);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f", m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{6}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetMarkerColor(kBlack);

	c->cd(9);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas8CMbothT(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothT"))->SetTitle("Both, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothT"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

}

void DrawMMspectrumCM6HwithD() {

	Info("DrawMMspectrumCM6HwithD", "Missing mass of 6H from 4He; 5-body decay");
	Info("DrawMMspectrumCM6HwithD",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CMwithD",
			"cHeMM_CMwithD: Both detectors, 6H, 5-body decay",
			1400, 1200);
	c->Divide(3,3);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	//////////////////////////////
	//Golovkov triangle
	//////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "1*x/2", 0, 16);
//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";

	//form of approximated triangle is identical for 4- and 5-body decay
	TString conTriangle =
			Form(" && fDMeasuredCorrectedCM6H.E()-%f <= 1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-%f)",
			m2H, massOfProducts5bDecay);

	////////////////////////////
	//6H MM measured right
	////////////////////////////

	con = "(f4HeFlagRT==1) && " + genConDeuterium;

	c->cd(1);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f", m2H);
	tr->Draw(var+">>hDcmMeasRight(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hDcmMeasRight"))->SetTitle("Right, E(^{2}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hDcmMeasRight"))->GetXaxis()->SetTitle("E_{CM}(^{2}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hDcmMeasRight"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(2);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f",
			m2H, massOfProducts5bDecay);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Right, corr MM(^{6}H) with E(^{2}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{2}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetMarkerColor(kBlack);

	c->cd(3);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f",
			massOfProducts5bDecay);
	tr->Draw(var+Form(">>hMMmeas8CMrightD(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightD"))->SetTitle("Right, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightD"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	////////////////////////////
	//6H MM measured left
	////////////////////////////

	con = "(f4HeFlagLT==1) && " + genConDeuterium;

	c->cd(4);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f", m2H);
	tr->Draw(var+">>hDcmMeasLeft(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hDcmMeasLeft"))->SetTitle("Left, E(^{2}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hDcmMeasLeft"))->GetXaxis()->SetTitle("E_{CM}(^{2}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hDcmMeasLeft"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f", m2H, massOfProducts5bDecay);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Left, corr MM(^{6}H) with E(^{2}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{2}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetMarkerColor(kBlack);

	c->cd(6);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts5bDecay);
	tr->Draw(var+Form(">>hMMmeas8CMleftD(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftD"))->SetTitle("Left, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftD"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();


	////////////////////////////
	//6H MM measured both
	////////////////////////////

	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genConDeuterium;

	c->cd(7);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f", m2H);
	tr->Draw(var+">>hDcmMeasBoth(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hDcmMeasBoth"))->SetTitle("measured, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hDcmMeasBoth"))->GetXaxis()->SetTitle("E_{CM}(^{2}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hDcmMeasBoth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(8);
	//	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f", m2H, massOfProducts5bDecay);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{6}H) with E(^{2}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{2}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetMarkerColor(kBlack);

	c->cd(9);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts5bDecay);
	tr->Draw(var+Form(">>hMMmeas8CMbothD(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothD"))->SetTitle("Both, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothD"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

}

void DrawAnglesFor6HwithT() {

	Info("DrawAnglesFor6HwithT",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeAnglesFor6HwithT",
			"cHeAnglesFor6HwithT: some meaningful text",
			1500, 1000);
	c->Divide(3,2);

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	////////////////////
	// right
	////////////////////

//	con = "(f4HeFlagRT==1) && " + genCon;
	con = "fTrigger==3 && fAngleLAB4HeBeamMeasuredCorrected && " + MakeGeneralTritiumCut();

	c->cd(1);
	tr->Draw(Form("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>>hAngleLAB4HeRight(50, 5., 30.)"),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeRight"))->SetTitle("Right, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeRight"))->GetXaxis()->SetTitle("angle(^{4}He vs. beam) (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeRight"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()",
			con + " && " + targetCondition
			+ " && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23",
			"same");
	tr->SetLineColor(kBlue+2);


	c->cd(4);
	con = "(f4HeFlagRT==1)"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23 && "
			+ genCon
			+ " && " + targetCondition;

	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas4HeAngleCutLeft(%d, -5., 21.)", kMMbins),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutLeft"))->SetTitle("Right, MM (^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutLeft"))->GetXaxis()->SetTitle("angle(^{4}He vs. beam) (deg.)");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutLeft"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// left
	////////////////////

//	con = "(f4HeFlagLT==1) && " + genCon;
	con = "fTrigger==2 && fAngleLAB4HeBeamMeasuredCorrected && " + MakeGeneralTritiumCut();

	c->cd(2);
	tr->Draw(Form("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>>hAngleLAB4HeLeft(50, 5., 30.)"),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeLeft"))->SetTitle("Left, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeLeft"))->GetXaxis()->SetTitle("angle(^{4}He vs. beam) (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeLeft"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()",
			con + " && " + targetCondition
			+ " && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23",
			"same");
	tr->SetLineColor(kBlue+2);

	c->cd(5);
	con = "(f4HeFlagLT==1)"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23 && "
			+ genCon
			+ " && " + targetCondition;

	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas4HeAngleCutRight(%d, -5., 21.)", kMMbins),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutRight"))->SetTitle("Left, MM (^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutRight"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutRight"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// both
	////////////////////

//	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genCon;
	con = "(fTrigger==2 || fTrigger==3) && fAngleLAB4HeBeamMeasuredCorrected && " + MakeGeneralTritiumCut();

	c->cd(3);
	tr->Draw(Form("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>>hAngleLAB4HeBoth(50, 5., 30.)"),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeBoth"))->SetTitle("Both, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeBoth"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeBoth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()",
			con + " && " + targetCondition
			+ " && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23",
			"same");
	tr->SetLineColor(kBlue+2);

	c->cd(6);
	con = "(f4HeFlagLT==1 || f4HeFlagRT==1)"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23 && "
			+ genCon
			+ " && " + targetCondition;

	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas4HeAngleCutBoth(%d, -5., 21.)", kMMbins),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutBoth"))->SetTitle("Both, MM (^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutBoth"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutBoth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

}

void DrawAnglesFor6HwithD() {

	Info("DrawAnglesFor6HwithD",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeAnglesFor6HwithD",
			"cHeAnglesFor6HwithD: some meaningful text",
			1500, 1000);
	c->Divide(3,2);

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	////////////////////
	// right
	////////////////////

//	con = "(f4HeFlagRT==1) && " + genCon;
	con = "fTrigger==3 && fAngleLAB4HeBeamMeasuredCorrected && " + MakeGeneralDeuteriumCut();

	c->cd(1);
	tr->Draw(Form("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>>hAngleLAB4HeRightD(50, 5., 30.)"),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeRightD"))->SetTitle("Right, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeRightD"))->GetXaxis()->SetTitle("angle(^{4}He vs. beam) (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeRightD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()",
			con + " && " + targetCondition
			+ " && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23",
			"same");
	tr->SetLineColor(kBlue+2);

	c->cd(4);
	con = "(f4HeFlagRT==1)"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23 && "
			+ genConDeuterium
			+ " && " + targetCondition;

	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f", massOfProducts5bDecay);
	tr->Draw(var+Form(">>hMMmeas4HeAngleCutLeftD(%d, -5., 21.)", kMMbins),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutLeftD"))->SetTitle("Right, MM (^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutLeftD"))->GetXaxis()->SetTitle("angle(^{4}He vs. beam) (deg.)");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutLeftD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// left
	////////////////////

//	con = "(f4HeFlagLT==1) && " + genCon;
	con = "fTrigger==2 && fAngleLAB4HeBeamMeasuredCorrected && " + MakeGeneralDeuteriumCut();

	c->cd(2);
	tr->Draw(Form("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>>hAngleLAB4HeLeftD(50, 5., 30.)"),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeLeftD"))->SetTitle("Left, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeLeftD"))->GetXaxis()->SetTitle("angle(^{4}He vs. beam) (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeLeftD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()",
			con + " && " + targetCondition
			+ " && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23",
			"same");
	tr->SetLineColor(kBlue+2);

	c->cd(5);
	con = "(f4HeFlagLT==1)"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23 && "
			+ genConDeuterium
			+ " && " + targetCondition;

	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f", massOfProducts5bDecay);
	tr->Draw(var+Form(">>hMMmeas4HeAngleCutRightD(%d, -5., 21.)", kMMbins),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutRightD"))->SetTitle("Left, MM (^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutRightD"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutRightD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// both
	////////////////////

//	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genCon;
	con = "(fTrigger==2 || fTrigger==3) && fAngleLAB4HeBeamMeasuredCorrected && "
			+ MakeGeneralDeuteriumCut();

	c->cd(3);
	tr->Draw(Form("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>>hAngleLAB4HeBothD(50, 5., 30.)"),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeBothD"))->SetTitle("Both, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeBothD"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hAngleLAB4HeBothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()",
			con + " && " + targetCondition
			+ " && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23",
			"same");
	tr->SetLineColor(kBlue+2);

	c->cd(6);
	con = "(f4HeFlagLT==1 || f4HeFlagRT==1)"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()>12"
			" && fAngleLAB4HeBeamMeasuredCorrected*TMath::RadToDeg()<23 && "
			+ genConDeuterium
			+ " && " + targetCondition;

	var = Form("fHydrogen6MeasuredCorrected.Mag()-%f", massOfProducts5bDecay);
	tr->Draw(var+Form(">>hMMmeas4HeAngleCutBothD(%d, -5., 21.)", kMMbins),
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutBothD"))->SetTitle("Both, MM (^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutBothD"))->GetXaxis()->SetTitle("MM ^{6}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas4HeAngleCutBothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

}

void DrawCMreaction6HwithT() {

	Info("DrawCMreaction6H", "Function used for check and correction of 3He cuts");
	Info("DrawCMreaction6H",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cCMreaction6HT",
			"cCMreaction6HT: both detectors",
			1400, 1000);
	c->Divide(3,2);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	//////////////////////////////
	//Golovkov triangle
	//////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "1*x/2", 0, 16);
	//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
	//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
	TString conTriangle = Form(" && fTMeasuredCorrectedCM6H.E()-%f <= -1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-%f)",
			m3H, massOfProducts);


	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genCon + "&&" + targetCondition + conTriangle;

	c->cd(1);
	tr->Draw("fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>>h7HangleCMreaction(25,0.,35.)",
			con);
	((TH1F*)gPad->GetPrimitive("h7HangleCMreaction"))->SetTitle("Both, angle(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("h7HangleCMreaction"))->GetXaxis()->SetTitle("angle(^{6}H) in reaction CM (deg.)");
	((TH1F*)gPad->GetPrimitive("h7HangleCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(2);
	tr->Draw(Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f>>hMMboth(20, -5., 21.)", massOfProducts), con);
	((TH1F*)gPad->GetPrimitive("hMMboth"))->SetTitle("Both, MM(^{6}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMboth"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMboth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(3);
	var = Form("fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()"
			":fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, angular correlation, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle(^{6}H) in reaction CM (deg.)");
	gPad->Update();

	/////////////////////////////////////
	// cuts for reaction angle
	/////////////////////////////////////

	c->cd(4);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f>>hMMbothSmallAnglesCMreaction(20, -5., 21.)",
			massOfProducts);
	tr->Draw(var, con + " && fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()<16.");
	((TH1F*)gPad->GetPrimitive("hMMbothSmallAnglesCMreaction"))->SetTitle("Both, angle_{CM}(^{6}H)<16 deg.");
	((TH1F*)gPad->GetPrimitive("hMMbothSmallAnglesCMreaction"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMbothSmallAnglesCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	var = Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f>>hMMbothLargeAnglesCMreaction(20, -5., 21.)", massOfProducts);
	tr->Draw(var, con+" && fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>16.");
	((TH1F*)gPad->GetPrimitive("hMMbothLargeAnglesCMreaction"))->SetTitle("Both, angle_{CM}(^{6}H)>16 deg.");
	((TH1F*)gPad->GetPrimitive("hMMbothLargeAnglesCMreaction"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMbothLargeAnglesCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
//	tr->SetLineColor(kGreen);
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(6);
	tr->Draw(Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f>>hMMbothMeanAnglesCMreaction(20, -5., 21.)", massOfProducts),
			con
			+ " && fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>12."
			+ " && fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()<22."
	);
	((TH1F*)gPad->GetPrimitive("hMMbothMeanAnglesCMreaction"))->SetTitle("Both, angle_{CM}(^{6}H) in (12,22) deg.");
	((TH1F*)gPad->GetPrimitive("hMMbothMeanAnglesCMreaction"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMbothMeanAnglesCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kGreen);
//	tr->Draw(Form("fHydrogen6MeasuredCorrectedCM.Mag()-%f", massOfProducts),
//			con + conTriangle
//			+ " && fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>12."
//			+ " && fHydrogen6MeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()<22.",
//			"same"
//	);
	tr->SetLineColor(kBlue+2);
	gPad->Update();
}

void DrawMMspectrumPureTrianglesT() {

	Info("DrawMMspectrumPureTrianglesT", "Function used for ...");
	const Long64_t drawEntries = 100000000;
	Info("DrawMMspectrumPureTrianglesT",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM_pureTriangleT",
			"cHeMM_CM_pureTriangleT: meaningful text",
			1000, 500);
	c->Divide(2,1);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	////////////////////////////
	//6H MM measured
	////////////////////////////

	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genCon;

	c->cd(1);
	tr->SetMarkerSize(0.9);
	var = Form("fTMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f",
			m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{6}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();


	c->cd(2);
	gPad->Update();
	tr->Draw(var+">>hPureTriangleT(15,-3.,21.,15,0.,18.)", con, "col text");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->SetTitle("Both, corr MM(^{6}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();


}

void DrawMMspectrumPureTrianglesD() {

	Info("DrawMMspectrumPureTrianglesD", "Function used for ...");
	const Long64_t drawEntries = 100000000;
	Info("DrawMMspectrumPureTrianglesD",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM_pureTriangleD",
			"cHeMM_CM_pureTriangleD: meaningful text",
			1000, 500);
	c->Divide(2,1);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	////////////////////////////
	//6H MM measured
	////////////////////////////

	con = "(f4HeFlagRT==1 || f4HeFlagLT==1) && " + genConDeuterium;

	c->cd(1);
	tr->SetMarkerSize(0.9);
	var = Form("fDMeasuredCorrectedCM6H.E()-%f:fHydrogen6MeasuredCorrectedCM.Mag()-%f",
			m2H, massOfProducts5bDecay);

	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{6}H) with E(^{2}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{2}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();


	c->cd(2);
	gPad->Update();
	tr->Draw(var+">>hPureTriangleD(15,-10.,15.,15,0.,8.)", con, "col text");
	((TH1F*)gPad->GetPrimitive("hPureTriangleD"))->SetTitle("Both, corr MM(^{6}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hPureTriangleD"))->GetXaxis()->SetTitle("MM (^{6}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hPureTriangleD"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hPureTriangleD"))->GetYaxis()->SetTitle("E(^{2}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("hPureTriangleD"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();


}

void DrawMMspectrumAngles() {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMangles", "cHeMMangles: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1500, 1000);
	c->Divide(3,2);

//	const Int_t kRebin = 10;
	const Int_t kRebin = 5;

	tr->SetMarkerSize(0.9);
	tr->SetMarkerColor(kBlue+2);

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";
//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 10.5^2";

	con = "fHeFlag==1  && "
				+ MakeGeneralTritiumCut() + " && "
				+ targetCondition + " && "
				"Length$(" + RTY + ") && "
				+ RTY + ".fEdep*1000<30."
				+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	////////////////////
	// 3H vs. 7H angle
	////////////////////

	c->cd(1);
	var = "fAngleLABhtMeasuredCorrected*TMath::RadToDeg()";
	cout << tr->Draw(var+">>hAngleMeas(11, 0., 10.)", con) << endl;
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->SetTitle("measured angle (^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetXaxis()->SetTitle("angle (^{7}H vs. ^{3}H) meas (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	tr->SetLineColor(kGreen+2);
	cout << tr->Draw(var,
			con+" && (fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565)<10.", "same") << endl;
	gPad->Update();

	tr->SetLineColor(kRed+2);
	cout << tr->Draw(var,
			con+" && (fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565)<5.", "same") << endl;
	gPad->Update();

	c->cd(4);
	tr->SetLineColor(kBlue+2);
	var = "fAngleLABhtCalculated*TMath::RadToDeg()";
	cout << tr->Draw(var+">>hAngleCalc(11, 0., 10.)", con) << endl;
	((TH1F*)gPad->GetPrimitive("hAngleCalc"))->SetTitle("calculated angle (^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleCalc"))->GetXaxis()->SetTitle("angle (^{7}H vs. ^{3}H) calc (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleCalc"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hAngleCalc"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hAngleCalc"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	tr->SetLineColor(kGreen+2);
	cout << tr->Draw(var,
			con+" && (fHydrogenCalculated.Mag()-2808.92-4*939.565)<10.", "same") << endl;
	gPad->Update();

	tr->SetLineColor(kRed+2);
	cout << tr->Draw(var,
			con+" && (fHydrogenCalculated.Mag()-2808.92-4*939.565)<5.", "same") << endl;
	gPad->Update();


	tr->SetLineColor(kBlue+2);
//	return;
	/////////////////////////////////////////////
	// 3H vs. 7H angle, correlation with MM
	/////////////////////////////////////////////

	TString angularCut = " && (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2>5."
			"&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<35.";
//	TString angularCut = " && (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())<10.";

	c->cd(2);
	tr->SetMarkerColor(kBlue+2);
	var = "(fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2:fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr angle^{2} (^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle^{2} (^{3}H vs. ^{7}H) meas (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	tr->SetMarkerColor(kGreen);
	cout << tr->Draw(var, con + angularCut, "same") << endl;
	gPad->Update();

	c->cd(5);
	tr->SetMarkerColor(kBlue+2);
	var = "(fAngleLABhtCalculated*TMath::RadToDeg())^2:fHydrogenCalculated.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr angle^{2} (^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle^{2} (^{3}H vs. ^{7}H) calc (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	tr->SetMarkerColor(kGreen);
	cout << tr->Draw(var, con + angularCut, "same") << endl;
	gPad->Update();

	/////////////////////////////////////////////
	// resulting MM, cut for 3H vs. 7H angle
	/////////////////////////////////////////////
	c->cd(3);
	tr->SetLineColor(kBlue+2);
	var = "fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var + ">>hMMmeasCutted(14, -5., 21.)", con) << endl;
	((TH1F*)gPad->GetPrimitive("hMMmeasCutted"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeasCutted"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasCutted"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hMMmeasCutted"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hMMmeasCutted"))->GetYaxis()->SetTitleSize(0.05);

	gPad->Update();
	tr->SetLineColor(kGreen);
	cout << tr->Draw(var, con + angularCut, "same") << endl;
	gPad->Update();

	c->cd(6);
	tr->SetLineColor(kBlue+2);
	var = "fHydrogenCalculated.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var+">>hMMcalcCutted(14, -5., 21.)", con) << endl;
	((TH1F*)gPad->GetPrimitive("hMMcalcCutted"))->SetTitle("calculated E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalcCutted"))->GetXaxis()->SetTitle("MM calc (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalcCutted"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hMMcalcCutted"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hMMcalcCutted"))->GetYaxis()->SetTitleSize(0.05);

	gPad->Update();
	tr->SetLineColor(kGreen);
	cout << tr->Draw(var, con + angularCut, "same") << endl;
	gPad->Update();

	tr->SetLineColor(kBlue+2);

}

void DrawMMspectrumAnalysis() {

	Info("DrawMMspectrumAnalysis", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMManalysis", "cHeMManalysis: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1500, 1000);
	c->Divide(4,2);

//	const Int_t kRebin = 10;
	const Int_t kRebin = 5;

	Double_t kTritiumMass = 2808.92;	//mass of 3H in MeV
	Double_t kNeutronMass = 939.565;	//mass of 3H in MeV

//	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 8.^2";
	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 10.5^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition;

	tr->SetMarkerSize(0.9);
	tr->SetMarkerColor(kBlue+2);

	//////////
	// MM
	//////////

	c->cd(1);
//	tr->Draw("fHydrogenMeasured.Mag()-2808.92-4*939.565", MakeHeCut());
//	cout << tr->Draw("fHydrogenMeasured.Mag()-2808.92-4*939.565", "fHeFlag==1  && " + MakeGeneralTritiumCut()) << endl;
	cout << tr->Draw("fHydrogenMeasured.Mag()-2808.92-4*939.565", con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->Rebin(kRebin);
	gPad->Update();

	c->cd(5);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565", MakeHeCut());
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->Rebin(kRebin);
	gPad->Update();

//	c->cd(3);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565", MakeHeCut());
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565", con);
//	((TH1F*)gPad->GetPrimitive("htemp"))->Rebin(kRebin);
//	gPad->Update();

	//////////////////////////////////
	// MM cuted for Pavel's triangle
	//////////////////////////////////


//	TString angularCut = " && (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<10.";
	TString angularCut = " && (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2>5."
			"&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<30.";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<25.";

//	con = "fHeFlag==1  && "
//			+ MakeGeneralTritiumCut() + " && "
//			+ targetCondition + " && "
//			"Length$(" + RTY + ") && "
//			+ RTY + ".fEdep*1000<30." + angularCut;



	c->cd(2);
//	con.Form("fHeFlag==1  && "
//			"%s && Length$(%s) "
//			"&& %s.fEdep*1000<25.",
//			MakeGeneralTritiumCut().Data(), RTY.Data(),
//			RTY.Data());
	tr->Draw("fHydrogenMeasured.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->Rebin(kRebin);
	gPad->Update();

	c->cd(6);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->Rebin(kRebin);
	gPad->Update();

	/////////////////////////////////////
	// check of Pavel's triangle
	//////////////////////////////////////

	c->cd(3);
	tr->SetMarkerColor(kBlue+2);
		var = "(fAngleLABhtMeasured*TMath::RadToDeg())^2:fHydrogenMeasured.Mag()-2808.92-4*939.565";
		cout << tr->Draw(var, con) << endl;
		gPad->Update();
		tr->SetMarkerColor(kGreen);
		cout << tr->Draw(var, con + angularCut, "same") << endl;
		gPad->Update();




	c->cd(7);
	tr->SetMarkerColor(kBlue+2);
		var = "(fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2:fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
		cout << tr->Draw(var, con) << endl;
		gPad->Update();
		tr->SetMarkerColor(kGreen);
		cout << tr->Draw(var, con + angularCut, "same") << endl;
		gPad->Update();

	gPad->Update();

	////////////////////////////////////////
	// new correlations
	////////////////////////////////////////////

	c->cd(4);
		tr->SetMarkerColor(kBlue+2);
//			var = "fAngleLAB7hBeamMeasured*TMath::RadToDeg():fHydrogenMeasured.Mag()-2808.92-4*939.565";
			var = "fHeMeasured.Theta()*TMath::RadToDeg():fHydrogenMeasured.Mag()-2808.92-4*939.565";
			cout << tr->Draw(var, con) << endl;
			gPad->Update();
			tr->SetMarkerColor(kGreen);
//			cout << tr->Draw(var, con + angularCut, "same") << endl;
			gPad->Update();




		c->cd(8);
		tr->SetMarkerColor(kBlue+2);
			var = "fAngleLAB7hBeamMeasuredCorrected*TMath::RadToDeg():fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
			var = "fHeMeasuredCorrected.Theta()*TMath::RadToDeg():fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
			cout << tr->Draw(var, con) << endl;
			gPad->Update();
			tr->SetMarkerColor(kGreen);
//			cout << tr->Draw(var, con + angularCut, "same") << endl;
			gPad->Update();

		gPad->Update();

}

void DrawCorrelationsEnergies()
{
	Info("DrawCorrelationsEnergies", "MM vs. energy correlations");
	const Long64_t drawEntries = 100000000;
	Info("DrawCorrelationsEnergies",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cCorrEnergies", "cCorrEnergies: some meaningful text", 1500, 1000);
	c->Divide(2,2);

	tr->SetMarkerSize(0.9);
	tr->SetMarkerColor(kBlue+2);

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 8.^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<30.";

	/////////////////////////////////////////
	// correlation with 3He energy
	/////////////////////////////////////////

	c->cd(1);
	tr->SetMarkerColor(kBlue+2);
	var = "fHeMeasuredCorrected.E()-2808.391:fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr E(^{3}He) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}He) meas (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	c->cd(3);
	tr->SetMarkerColor(kBlue+2);
	var = "fHeCalculated.E()-2808.391:fHydrogenCalculated.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("calculated, corr E(^{3}He) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}He) calc (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	/////////////////////////////////////////
	// correlation with beam energy
	/////////////////////////////////////////

	c->cd(2);
	tr->SetMarkerColor(kBlue+2);
	var = "fBeamTarget.E()-7482.538:fHydrogenMeasured.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr E(beam) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{8}He) meas (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	c->cd(4);
	tr->SetMarkerColor(kBlue+2);
	var = "fBeamTarget.E()-7482.538:fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("calculated, corr E(beam) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{8}He) calc (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

}

void DrawCorrelationsAngles()
{
	Info("DrawCorrelationsAngles", "MM vs. angle correlations");
	const Long64_t drawEntries = 100000000;
	Info("DrawCorrelationsAngles",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cCorrAngles", "cCorrAngles: some meaningful text", 1500, 1000);
	c->Divide(3,2);

	tr->SetMarkerSize(0.9);
	tr->SetMarkerColor(kBlue+2);

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 8.^2";
//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 10.5^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<30."
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	////////////////////////////////////////////////////
	// correlation with angle between 3He and 8He
	////////////////////////////////////////////////////

	c->cd(1);
	tr->SetMarkerColor(kBlue+2);
	var = "fAngleLAB3HeBeamMeasuredCorrected*TMath::RadToDeg():fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr angle(^{3}He) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle (^{3}He vs. ^{8}He) meas (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	c->cd(4);
	tr->SetMarkerColor(kBlue+2);
	var = "fAngleLAB3HeBeamCalculated*TMath::RadToDeg():fHydrogenCalculated.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("calculated, corr angle(^{3}He) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle (^{3}He vs. ^{8}He) calc (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	////////////////////////////////////////////////////////
	// correlation with squared angle between 7H and 3H
	////////////////////////////////////////////////////////

	c->cd(2);
	tr->SetMarkerColor(kBlue+2);
//	var = "(fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2:fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	var = "(fAngleLABhtMeasuredCorrected*TMath::RadToDeg()):fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
//	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr angle^{2} (^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr angle (^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle^{2} (^{3}H vs. ^{7}H) meas (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	c->cd(5);
	tr->SetMarkerColor(kBlue+2);
//	var = "(fAngleLABhtCalculated*TMath::RadToDeg())^2:fHydrogenCalculated.Mag()-2808.92-4*939.565";
	var = "(fAngleLABhtCalculated*TMath::RadToDeg()):fHydrogenCalculated.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
//	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("calculated, corr angle^{2} (^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("calculated, corr angle (^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle^{2} (^{3}H vs. ^{7}H) calc (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	////////////////////////////////////////////////////
	// correlation with angle between 3H and 8He
	////////////////////////////////////////////////////

	c->cd(3);
	tr->SetMarkerColor(kBlue+2);
	var = "fAngleLAB3HBeam*TMath::RadToDeg():fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr angle(^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle (^{3}H vs. ^{8}He) meas (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	c->cd(6);
	tr->SetMarkerColor(kBlue+2);
	var = "fAngleLAB3HBeam*TMath::RadToDeg():fHydrogenCalculated.Mag()-2808.92-4*939.565";
	cout << tr->Draw(var, con) << endl;
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("calculated, corr angle(^{3}H) with MM, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle (^{3}H vs. ^{8}He) calc (deg.)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

}

void DrawAngularAnalysis() {

	const Long64_t lowStat = 100000;
	Info("DrawAngularAnalysis",
				"Used number of entries; lowStat -  %lld; all - %lld",
				lowStat, tr->GetEntries());

	TCanvas *c = new TCanvas("cAngularAnalysis", "cAngularAnalysis: some meaningful text", 1500, 1000);
	c->Divide(3,2);

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	const Double_t a3HeMin = 8.;
	const Double_t a3HeMax = 25.;
	const Double_t a3HMax = 8.;

	//cut for angles - kinematics
	const TString con3HeAngleKin =
			Form("v3He.Theta()*TMath::RadToDeg()<%f && v3He.Theta()*TMath::RadToDeg()>%f", a3HeMax, a3HeMin);
	const TString con3HAngleKin =
			Form("TMath::Abs(v3H.Theta()*TMath::RadToDeg())<%f", a3HMax);

	//cut for angles - exp. data
	const TString con3HeAngleExp =
			Form("fAngleBeam3He.Theta()*TMath::RadToDeg()<%f && fAngleBeam3He.Theta()*TMath::RadToDeg()>%f", a3HeMax, a3HeMin);
	const TString con3HAngleExp =
			Form("TMath::Abs(fAngleLAB3HBeam*TMath::RadToDeg())<%f", a3HMax);

	cout << con3HAngleExp << endl;

	////////////////////////////////////////////////////
	// experimental data
	////////////////////////////////////////////////////


	con = "fHeFlagRT==1 && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && Length$(" + RTY + ")"
			+ "&&" + RTY + ".fEdep*1000<30. "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	TString conTriangleMeas = " && fTMeasuredCorrectedCM.E()-2808.92 <= 4/7*(fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565)";
	conTriangleMeas.Append(" && fTritiumKinMeasuredCorrected>65.");

	c->cd(1);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565>>hMMmeas8CMdem(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMdem"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMdem"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMdem"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + conTriangleMeas,
			"same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(2);
	tr->Draw("fAngleLAB3HBeam*TMath::RadToDeg()",
			"fAngleLAB3HBeam<3.14 && " + MakeGeneralTritiumCut(), "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetName("hExpTritiumAll");
	((TH1F*)gPad->GetPrimitive("hExpTritiumAll"))->SetTitle("");
	((TH1F*)gPad->GetPrimitive("hExpTritiumAll"))->GetXaxis()->SetTitle("angle (^{3}H vs. beam)");
	((TH1F*)gPad->GetPrimitive("hExpTritiumAll"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->Draw("fAngleLAB3HBeam*TMath::RadToDeg()",
			"fAngleLAB3HBeam<3.14 && " + MakeGeneralTritiumCut() + "&&" + con3HAngleExp, "same");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetFillColor(kGray);
	gPad->Update();

	c->cd(3);
	tr->Draw("fAngleBeam3He.Theta()*TMath::RadToDeg()>>hAngle3HeBeamLab(25, 5., 30.)",
			"fHeFlag", "");
	((TH1F*)gPad->GetPrimitive("hAngle3HeBeamLab"))->SetName("hExpHeliumAll");
	((TH1F*)gPad->GetPrimitive("hExpHeliumAll"))->SetTitle("");
	((TH1F*)gPad->GetPrimitive("hExpHeliumAll"))->GetXaxis()->SetTitle("angle (^{3}He vs. beam)");
	((TH1F*)gPad->GetPrimitive("hExpHeliumAll"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->Draw("fAngleBeam3He.Theta()*TMath::RadToDeg()",
			"fHeFlag &&" + con3HeAngleExp, "same");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetFillColor(kGray);
	gPad->Update();

	////////////////////////////////////////////////////
	// kinematics
	////////////////////////////////////////////////////

	TFile *fr = new TFile("7H-gen/outputAngles.root", "READ");
	TTree* trKin = (TTree*)fr->Get("kin");
	trKin->SetLineWidth(3);

	const Double_t m8He = 7482.5396;
	const Double_t m3He = 2808.391;
	const Double_t m2H = 1875.6128;
	const Double_t m3H = 2808.9207;
	const Double_t mn = 939.5653;

	c->cd(4);
	trKin->Draw(Form("v7Hcm7H.E()-%f>>hMMkin(50,-0.5,9.5)", m3H+4*mn),
			Form("v7Hcm7H.E()-%f<3. ", m3H+4*mn));
	((TH1F*)gPad->GetPrimitive("hMMkin"))->SetTitle("input: excitation energy of ^{7}H");
	((TH1F*)gPad->GetPrimitive("hMMkin"))->GetXaxis()->SetTitle("E_{T} (^{7}H) MeV");
	((TH1F*)gPad->GetPrimitive("hMMkin"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hMMkin"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hMMkin"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	trKin->SetLineColor(kRed);
	trKin->Draw(Form("v7Hcm7H.E()-%f", m3H+4*mn),
			Form("v7Hcm7H.E()-%f>3. ", m3H+4*mn),
			"same");
	trKin->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	trKin->SetLineColor(kRed);
	trKin->Draw("fAngle7H3Hlab*TMath::RadToDeg()>>hAngleKin(200, 0., 16.)",
			Form("v7Hcm7H.E()-%f>3. && ", m3H+4*mn) + con3HeAngleKin + "&&" + con3HAngleKin,
			"");
	TH1F *hAngleKinFit5 = new TH1F(*((TH1F*)gPad->GetPrimitive("hAngleKin")));
	trKin->SetLineColor(kBlue+2);
	trKin->Draw("fAngle7H3Hlab*TMath::RadToDeg()",
			Form("v7Hcm7H.E()-%f<3. && ", m3H+4*mn) + con3HeAngleKin + "&&" + con3HAngleKin,
			"same");
	TH1F *hAngleKinFit1 = new TH1F(*((TH1F*)gPad->GetPrimitive("htemp")));

	((TH1F*)gPad->GetPrimitive("hAngleKin"))->SetTitle("simulated angle (^{3}H)");
	((TH1F*)gPad->GetPrimitive("hAngleKin"))->GetXaxis()->SetTitle("angle (^{7}H vs. ^{3}H) kin (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleKin"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hAngleKin"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hAngleKin"))->GetYaxis()->SetTitleSize(0.05);

	hAngleKinFit1->SetName("hAngleKinFit1");
	hAngleKinFit5->SetName("hAngleKinFit5");
	gPad->Update();

	////////////////////////////////////////////////////
	// comparison of epx with kinematics
	////////////////////////////////////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<30."
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(6);
	var = "fAngleLABhtMeasuredCorrected*TMath::RadToDeg()";
	cout << tr->Draw(var+">>hAngleMeas(16, 0., 16.)",
			con + conTriangleMeas + " && fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565 < 10.")
					<< endl;
	hAngleKinFit1->Scale(4./6600.);
	hAngleKinFit1->Draw("same s");

	hAngleKinFit5->Scale(4./6700.);
	hAngleKinFit5->Draw("same");

	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->SetTitle("measured angle (^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetXaxis()->SetTitle("angle (^{7}H vs. ^{3}H) meas (deg.)");
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetYaxis()->SetTitle("counts");
	((TH1F*)gPad->GetPrimitive("hAngleMeas"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

}

void DrawMMsplitted3HeLABAngle() {

	const Long64_t lowStat = 100000;
	Info("DrawAngularAnalysis",
				"Used number of entries; lowStat -  %lld; all - %lld",
				lowStat, tr->GetEntries());

	TCanvas *c = new TCanvas("cSplit3HeLab", "cSplit3HeLab: some meaningful text", 1500, 1000);
	c->Divide(3,2);

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

//	const Double_t a3HeMin = 8.;
//	const Double_t a3HeMax = 25.;
//	const Double_t a3HMax = 8.;

	//cut for angles - kinematics
//	const TString con3HeAngleKin =
//			Form("v3He.Theta()*TMath::RadToDeg()<%f && v3He.Theta()*TMath::RadToDeg()>%f", a3HeMax, a3HeMin);
//	const TString con3HAngleKin =
//			Form("TMath::Abs(v3H.Theta()*TMath::RadToDeg())<%f", a3HMax);

	//cut for angles - exp. data
//	const TString con3HeAngleExp =
//			Form("fAngleBeam3He.Theta()*TMath::RadToDeg()<%f && fAngleBeam3He.Theta()*TMath::RadToDeg()>%f", a3HeMax, a3HeMin);
//	const TString con3HAngleExp =
//			Form("TMath::Abs(fAngleLAB3HBeam*TMath::RadToDeg())<%f", a3HMax);

//	cout << con3HAngleExp << endl;

	////////////////////////////////////////////////////
	// missing mass
	////////////////////////////////////////////////////


	con = "fHeFlag==1 && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && Length$(" + RTY + ")"
			+ "&&" + RTY + ".fEdep*1000<30. "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	TString conTriangleMeas = " && fTMeasuredCorrectedCM.E()-2808.92 <= 4/7*(fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565)";
//	conTriangleMeas.Append(" && fTritiumKinMeasuredCorrected>65.");

//	TString conAnglesUp = "&& fAngleBeam3He.Theta()*TMath::RadToDeg()<15";
//	TString conAnglesLow = "&& fAngleBeam3He.Theta()*TMath::RadToDeg()>15";
	TString conAnglesUp = "&& fAngleBeam3He.Theta()*TMath::RadToDeg()>10"
			"&& fAngleBeam3He.Theta()*TMath::RadToDeg()<20";
	TString conAnglesLow = "&& fAngleBeam3He.Theta()*TMath::RadToDeg()>20"
			"&& fAngleBeam3He.Theta()*TMath::RadToDeg()<26";

	c->cd(1);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565>>hMMmeas8CMdem(14, -5., 21.)", con);
	TH1F* hMMmeas8CMdem = ((TH1F*)gPad->GetPrimitive("hMMmeas8CMdem"));
	hMMmeas8CMdem->SetTitle("");
	hMMmeas8CMdem->GetXaxis()->SetTitle("MM (MeV)");
	hMMmeas8CMdem->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(4);
	tr->Draw("fAngleBeam3He.Theta()*TMath::RadToDeg()>>hExpHeliumAll(25, 5., 30.)",
			"fHeFlag", "");
	((TH1F*)gPad->GetPrimitive("hExpHeliumAll"))->SetTitle("");
	((TH1F*)gPad->GetPrimitive("hExpHeliumAll"))->GetXaxis()->SetTitle("angle (^{3}He vs. beam)");
	((TH1F*)gPad->GetPrimitive("hExpHeliumAll"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	tr->SetLineColor(kRed);
	tr->Draw("fAngleBeam3He.Theta()*TMath::RadToDeg()",
			"fHeFlag" + conAnglesUp, "same");
	gPad->Update();

	tr->SetLineColor(kGreen);
	tr->Draw("fAngleBeam3He.Theta()*TMath::RadToDeg()",
			"fHeFlag" + conAnglesLow, "same");
	gPad->Update();
	tr->SetLineColor(kBlue+2);

	c->cd(2);
	hMMmeas8CMdem->Draw();
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + /*conTriangleMeas +*/ + conAnglesUp,
			"same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	hMMmeas8CMdem->Draw();
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + /*conTriangleMeas +*/ + conAnglesLow,
			"same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	////////////////////////////////////////////////////
	// triangle
	////////////////////////////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "4*x/7", 0, 16);


	c->cd(3);
	tr->SetMarkerSize(0.9);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("kin. triangle, angle(^{3}He)<15 deg.");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + /*conTriangleMeas +*/ + conAnglesUp,
			"same");
	tr->SetMarkerColor(kBlack);


	c->cd(6);
	tr->SetMarkerSize(0.9);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("kin. triangle, angle(^{3}He)>15 deg.");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kGreen);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + /*conTriangleMeas +*/ + conAnglesLow,
			"same");
	tr->SetMarkerColor(kBlack);
}
