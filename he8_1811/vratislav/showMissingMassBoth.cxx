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
#include "TH2F.h"

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
#include "cutsHelium4.cxx"
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
//Si X layer
TString CTX = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X";

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

const Double_t cut3HeEnergy = 30.;
const Int_t kMMbins = 14;
const Double_t massOfProducts = m3H+4*mn;		//5-body decay with tritium
const Double_t massOfProducts6bDecay = m2H+5*mn;		//5-body decay with deuterium

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0);
void InitExternalCuts();

TString MakeGeneralTritiumCut();
TString MakeGeneralDeuteriumCut();

void DrawTargetPosition(TString beamProjCondition = "");

void DrawMMspectrumRT();
void DrawMMspectrumLT();
void DrawMMspectrumBoth();
void DrawMMspectrumBothWithD();
//void DrawMMspectrumTritiumSelection();

void DrawMMspectrumCM();
void DrawMMspectrumCMwithD(Bool_t allFigures = 0);

void DrawCMreaction();

void DrawMMspectrumPureTriangles();

void DrawGScandidate(TString option = "");

void DrawIDplotCorrectedWithCutsFinal(const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, TString telescope = "", const Bool_t logZ = 0);
void DrawCleanTritons(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0);

/////////////////////////////////////////////

void DrawMMspectrumAngles();
void DrawMMspectrumAnalysis();
void DrawCorrelationsEnergies();
void DrawCorrelationsAngles();
void DrawAngularAnalysis();
void DrawMMsplitted3HeLABAngle();

TString genCon;
TString genConDeuterium;

TString timeConditonCX;

void showMissingMassBoth(const Bool_t allStat = 1) {

	InitTrees(allStat);
//	InitTrees(allStat, 1);

	InitExternalCuts();

	genCon =
			MakeGeneralTritiumCut() + " && "
			//			MakeGeneralDeuteriumCut() + " && "
			+ Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);

	genConDeuterium =
	//			MakeGeneralTritiumCut() + " && "
				MakeGeneralDeuteriumCut() + " && "
				+ Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);

	//cuts for test of GS hypothesis
	TString conTriangle = Form(" && fTMeasuredCorrectedCM.E()-%f <= 1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
					m3H, massOfProducts);
	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	TString conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
					+ genCon + "&&" + targetCondition
					+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts)
					+ conTriangle;
	TString conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
			+ genCon + "&&" + targetCondition
			+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts)
			+ conTriangle;

//	genCon = conGScandidateLarge;

//	DrawTargetPosition();

//	DrawMMspectrumRT();
//	DrawMMspectrumLT();
//	DrawMMspectrumBoth();
//	DrawMMspectrumBothWithD();

//	DrawMMspectrumCM();
//	DrawMMspectrumCMwithD(0);

//	DrawCMreaction();

//	DrawMMspectrumPureTriangles();

//	DrawGScandidate("showSpectra");
//	DrawGScandidate("showOffsets");
//	DrawGScandidate("showAngles");
	DrawGScandidate("showTritiumEnergy");

//	DrawIDplotCorrectedWithCutsFinal(16, 0, "R");
//	DrawIDplotCorrectedWithCutsFinal(16, 0, "L");

//	DrawIDplotCorrectedWithCutsFinal(4, 0, "R");
//	DrawIDplotCorrectedWithCutsFinal(4, 4, "R");
//	DrawIDplotCorrectedWithCutsFinal(4, 8, "R");
//	DrawIDplotCorrectedWithCutsFinal(4, 12, "R");

//	DrawIDplotCorrectedWithCutsFinal(4, 0, "L");
//	DrawIDplotCorrectedWithCutsFinal(4, 4, "L");
//	DrawIDplotCorrectedWithCutsFinal(4, 8, "L");
//	DrawIDplotCorrectedWithCutsFinal(4, 12, "L");

//	DrawCleanTritons(16, 0);


	//small GS
//	DrawIDplotCorrectedWithCutsFinal(1, 8, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 10, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 12, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 0, "L");
//	DrawIDplotCorrectedWithCutsFinal(1, 6, "L");

//	DrawCleanTritons(1, 0);
//	DrawCleanTritons(1, 3);
//	DrawCleanTritons(1, 5);
//	DrawCleanTritons(1, 13);
//	DrawCleanTritons(1, 15);

	//large GS
//	DrawIDplotCorrectedWithCutsFinal(1, 0, "L");
//	DrawIDplotCorrectedWithCutsFinal(1, 6, "L");
//	DrawIDplotCorrectedWithCutsFinal(1, 7, "L");
//	DrawIDplotCorrectedWithCutsFinal(1, 1, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 5, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 7, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 8, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 10, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 12, "R");
//	DrawIDplotCorrectedWithCutsFinal(1, 13, "R");

	//	DrawCleanTritons(1, 0);
	//	DrawCleanTritons(1, 3);
	//	DrawCleanTritons(1, 5);
	//	DrawCleanTritons(1, 13);
	//	DrawCleanTritons(1, 15);

	/////////////////////////////////////////////
	/////////////////////////////////////////////


//	DrawMMspectrumTritiumSelection();
//	DrawMMspectrumCM();
//	DrawMMspectrumPureTriangle();
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

	if (useHeliumCuts) {
		cutsHelium3();
		cutsLTHelium3();
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

	timeConditonCX.Form("%s.fTime-BeamDetToFDigi2.fTime/2.>100. && %s.fTime-BeamDetToFDigi2.fTime/2.<135.",
				CTX.Data(), CTX.Data());

	timeCondCsI.Form("(cutCsI_0 || cutCsI_1 || cutCsI_2 || cutCsI_3"
			" || cutCsI_4 || cutCsI_5 || cutCsI_6 || cutCsI_7"
			" || cutCsI_8 || cutCsI_10 || cutCsI_11"
			" || cutCsI_12 || cutCsI_13 || cutCsI_14 || cutCsI_15)");

	//condition on position in the center of the target
//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 6^2";
	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	//time in MWPC's
	TString MWPCX1 = "BeamDetMWPCDigiX1";
	TString MWPCY1 = "BeamDetMWPCDigiY1";
	TString MWPCX2 = "BeamDetMWPCDigiX2";
	TString MWPCY2 = "BeamDetMWPCDigiY2";

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

void DrawMMspectrumRT() {

	Info("DrawMMspectrumRT",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMRight",
			"cHeMMRight: 7H missing mass from right telescope",
			1500, 600);
	c->Divide(3,1);

	con = "(fHeFlagRT==1) && "
			+ MakeGeneralTritiumCut() + " && "
			+ Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(14, -5., 21.)",
			con + " && " + targetCondition);

//	tr->Draw(Form("fHeMeasuredCorrected.E()-%f", m3He),
//			con + " && " + targetCondition
////			+ Form("fHeMeasuredCorrected.E()-%f<1", m3He, cut3HeEnergy)
//			);

//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->SetTitle("Right, MM ^{7}H, r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(14, -5., 21.)",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->SetTitle("Right, MM ^{7}H, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(14, -5., 21.)",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->SetTitle("Right, MM ^{7}H, r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

}

void DrawMMspectrumLT() {

	Info("DrawMMspectrumLT",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMLeft",
			"cHeMMLeft: 7H missing mass from left telescope",
			1500, 600);
	c->Divide(3,1);

	con = "(fHeFlagLT==1) && "
			+ MakeGeneralTritiumCut() + " && "
			+ Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeasLT(14, -5., 21.)",
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeasLT"))->SetTitle("Left, MM ^{7}H, r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeasLT"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasLT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8LT(14, -5., 21.)",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8LT"))->SetTitle("Left, MM ^{7}H, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8LT"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8LT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7LT(14, -5., 21.)",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas7LT"))->SetTitle("Left, MM ^{7}H, r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7LT"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7LT"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

}

void DrawMMspectrumBoth() {

	Info("DrawMMspectrumBoth",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMBoth",
			"cHeMMBoth: 7H missing mass from both telescopes",
			1500, 600);
	c->Divide(3,1);

	con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
			+ MakeGeneralTritiumCut()
			+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);
//			+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, 25.);
			;

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
	var = Form("fHydrogenMeasuredCorrected.Mag()-%f", massOfProducts);
	tr->Draw(var+">>hMMmeasBoth(14, -5., 21.)",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeasBoth"))->SetTitle("Both, MM ^{7}H, r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeasBoth"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasBoth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
	var = Form("fHydrogenMeasuredCorrected.Mag()-%f", massOfProducts);
	tr->Draw(var+">>hMMmeas8Both(14, -5., 21.)",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas8Both"))->SetTitle("Both, MM ^{7}H, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8Both"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8Both"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
	var = Form("fHydrogenMeasuredCorrected.Mag()-%f", massOfProducts);
	tr->Draw(var+">>hMMmeas7Both(14, -5., 21.)",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas7Both"))->SetTitle("Both, MM ^{7}H, r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7Both"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7Both"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

}

void DrawMMspectrumBothWithD() {

	Info("DrawMMspectrumBothwithD",
			"High statistics needed, slow drawing; available %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMBothD",
			"cHeMMBothD: 7H missing mass from both telescopes",
			1500, 600);
	c->Divide(3,1);

	con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
			+ MakeGeneralDeuteriumCut()
			+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy);
			;


	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	c->cd(1);
	var = Form("fHydrogenMeasuredCorrected.Mag()-%f", massOfProducts6bDecay);
	tr->Draw(var+">>hMMmeasBothD(14, -5., 21.)",
			con + " && " + targetCondition);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeasBothD"))->SetTitle("Both, MM ^{7}H, r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeasBothD"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasBothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	c->cd(2);
	var = Form("fHydrogenMeasuredCorrected.Mag()-%f", massOfProducts6bDecay);
	tr->Draw(var+">>hMMmeas8BothD(14, -5., 21.)",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothD"))->SetTitle("Both, MM ^{7}H, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothD"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8BothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	c->cd(3);
	var = Form("fHydrogenMeasuredCorrected.Mag()-%f", massOfProducts6bDecay);
	tr->Draw(var+">>hMMmeas7BothD(14, -5., 21.)",
			con + " && " + targetCondition);
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothD"))->SetTitle("Both, MM ^{7}H, r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothD"))->GetXaxis()->SetTitle("MM ^{7}H (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7BothD"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

}

void DrawMMspectrumCM() {

	Info("DrawMMspectrumCM6H", "Function used for check and correction of 3He cuts");
	Info("DrawMMspectrumCM6H",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM",
			"cHeMM_CM: both detectors",
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
	TString conTriangle = Form(" && fTMeasuredCorrectedCM.E()-%f <= 1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
			m3H, massOfProducts);

	////////////////////////////
	//6H MM measured right
	////////////////////////////

	con = "(fHeFlagRT==1) && " + genCon;

	c->cd(1);
	var = Form("fTMeasuredCorrectedCM.E()-%f", m3H);
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
	var = Form("fTMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
			m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Right, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
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
	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas8CMright(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMright"))->SetTitle("Right, MM(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMright"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMright"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	////////////////////////////
	//6H MM measured left
	////////////////////////////

	con = "(fHeFlagLT==1) && " + genCon;

	c->cd(4);
	var = Form("fTMeasuredCorrectedCM.E()-%f", m3H);
	tr->Draw(var+">>hTcmMeasLeft(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hTcmMeasLeft"))->SetTitle("Left, E(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hTcmMeasLeft"))->GetXaxis()->SetTitle("E_{CM}(^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hTcmMeasLeft"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	var = Form("fTMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
			m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Left, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
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
	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas8CMleft(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleft"))->SetTitle("Left, MM(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleft"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMleft"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();


	////////////////////////////
	//6H MM measured both
	////////////////////////////

	con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon;

	c->cd(7);
	var = Form("fTMeasuredCorrectedCM.E()-%f", m3H);
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
	var = Form("fTMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
			m3H, massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
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
	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+Form(">>hMMmeas8CMboth(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMboth"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMboth"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMboth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

}

void DrawMMspectrumCMwithD(Bool_t allFigures = 0) {

	Info("DrawMMspectrumCMwithD", "Some meaningful text");
	Info("DrawMMspectrumCMwithD",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM_D",
			"cHeMM_CM_D: both detectors",
			1400, 1200);
	c->Divide(3,3);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	//////////////////////////////
	//Golovkov triangle
	//////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "4*x/7", 0, 16);
//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
//	TString conTriangle = " && fTMeasuredCorrectedCM6H.E()-2808.92 <= 1.0+1/2*(fHydrogen6MeasuredCorrectedCM.Mag()-2808.92-3*939.565)";
	TString conTriangle = Form(" && fDMeasuredCorrectedCM.E()-%f <= 1.0+5/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
			m2H, massOfProducts6bDecay);

	////////////////////////////
	//6H MM measured right
	////////////////////////////

	if (allFigures) {

		con = "(fHeFlagRT==1) && " + genConDeuterium;

		c->cd(1);
		var = Form("fDMeasuredCorrectedCM.E()-%f", m2H);
		tr->Draw(var+">>hTcmMeasRightD(90, 0., 18.)", con);
		((TH1F*)gPad->GetPrimitive("hTcmMeasRightD"))->SetTitle("Right, E(^{3}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hTcmMeasRightD"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hTcmMeasRightD"))->GetYaxis()->SetTitle("counts");
		gPad->Update();
		tr->SetLineColor(kRed);
		tr->Draw(var, con + conTriangle, "same");
		tr->SetLineColor(kBlue+2);
		gPad->Update();

		c->cd(2);
		var = Form("fDMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
				m2H, massOfProducts6bDecay);
		tr->Draw(var, con);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Right, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
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
		var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts6bDecay);
		tr->Draw(var+Form(">>hMMmeas8CMrightD(%d, -5., 21.)", kMMbins), con);
		((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightD"))->SetTitle("Right, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightD"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMmeas8CMrightD"))->GetYaxis()->SetTitle("counts");
		gPad->Update();
		tr->SetLineColor(kGreen);
		tr->Draw(var, con + conTriangle, "same");
		tr->SetLineColor(kBlue+2);
		gPad->Update();

	}

	////////////////////////////
	//6H MM measured left
	////////////////////////////

	if (allFigures) {

		con = "(fHeFlagLT==1) && " + genConDeuterium;

		c->cd(4);
		var = Form("fDMeasuredCorrectedCM.E()-%f", m2H);
		tr->Draw(var+">>hTcmMeasLeftD(90, 0., 18.)", con);
		((TH1F*)gPad->GetPrimitive("hTcmMeasLeftD"))->SetTitle("Left, E(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hTcmMeasLeftD"))->GetXaxis()->SetTitle("E_{CM}(^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hTcmMeasLeftD"))->GetYaxis()->SetTitle("counts");
		gPad->Update();
		tr->SetLineColor(kRed);
		tr->Draw(var, con + conTriangle, "same");
		tr->SetLineColor(kBlue+2);
		gPad->Update();

		c->cd(5);
		var = Form("fDMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
				m2H, massOfProducts6bDecay);
		tr->Draw(var, con);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Left, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
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
		var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts6bDecay);
		tr->Draw(var+Form(">>hMMmeas8CMleftD(%d, -5., 21.)", kMMbins), con);
		((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftD"))->SetTitle("Left, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftD"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMmeas8CMleftD"))->GetYaxis()->SetTitle("counts");
		gPad->Update();
		tr->SetLineColor(kGreen);
		tr->Draw(var, con + conTriangle, "same");
		tr->SetLineColor(kBlue+2);
		gPad->Update();

	}

	////////////////////////////
	//6H MM measured both
	////////////////////////////

	con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genConDeuterium;

	c->cd(7);
	var = Form("fDMeasuredCorrectedCM.E()-%f", m2H);
	tr->Draw(var+">>hTcmMeasBothD(90, 0., 18.)", con);
	((TH1F*)gPad->GetPrimitive("hTcmMeasBothD"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hTcmMeasBothD"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hTcmMeasBothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(8);
	var = Form("fDMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
			m2H, massOfProducts6bDecay);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
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
	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts6bDecay);
	tr->Draw(var+Form(">>hMMmeas8CMbothD(%d, -5., 21.)", kMMbins), con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothD"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothD"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CMbothD"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw(var, con + conTriangle, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

}

void DrawCMreaction() {

	Info("DrawCMreaction", "Function used for check and correction of 3He cuts");
	Info("DrawCMreaction",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cCMreaction",
			"cCMreaction: both detectors",
			1400, 1000);
	c->Divide(3,2);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition;

	c->cd(1);
	tr->Draw("fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>>h7HangleCMreaction(25,5.,50.)",
			con);
	((TH1F*)gPad->GetPrimitive("h7HangleCMreaction"))->SetTitle("Both, angle(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("h7HangleCMreaction"))->GetXaxis()->SetTitle("angle(^{7}H) in reaction CM (deg.)");
	((TH1F*)gPad->GetPrimitive("h7HangleCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(2);
	tr->Draw(Form("fHydrogenMeasuredCorrectedCM.Mag()-%f>>hMMboth(20, -5., 20.)", massOfProducts), con);
	((TH1F*)gPad->GetPrimitive("hMMboth"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMboth"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMboth"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(3);
	var = Form("fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()"
			":fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, angular correlation, r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle(^{7}H) in reaction CM (deg.)");
	gPad->Update();

	c->cd(4);
	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+">>hMMbothSmallAnglesCMreaction(20, -5., 20.)",
			con + " && fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()<25."
	);
	((TH1F*)gPad->GetPrimitive("hMMbothSmallAnglesCMreaction"))->SetTitle("Both, angle_{CM}(^{7}H)<25 deg.");
	((TH1F*)gPad->GetPrimitive("hMMbothSmallAnglesCMreaction"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMbothSmallAnglesCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(5);
//	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var+">>hMMbothLargeAnglesCMreaction(20, -5., 20.)",
			con
			+ " && fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>25."
	);
	((TH1F*)gPad->GetPrimitive("hMMbothLargeAnglesCMreaction"))->SetTitle("Both, angle_{CM}(^{7}H)>25 deg.");
	((TH1F*)gPad->GetPrimitive("hMMbothLargeAnglesCMreaction"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMbothLargeAnglesCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();


	c->cd(6);
//	var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
	tr->Draw(var + ">>hMMbothMeanAnglesCMreaction(20, -5., 20.)",
			con
			+ " && fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()>20."
			+ " && fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg()<35."
	);
	((TH1F*)gPad->GetPrimitive("hMMbothMeanAnglesCMreaction"))->SetTitle("Both, angle_{CM}(^{7}H) in (20,35) deg.");
	((TH1F*)gPad->GetPrimitive("hMMbothMeanAnglesCMreaction"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMbothMeanAnglesCMreaction"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
}


void DrawMMspectrumPureTriangles() {

	Info("DrawMMspectrumPureTriangles", "Function used for ...");
	const Long64_t drawEntries = 100000000;
	Info("DrawMMspectrumPureTriangles",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM_pureTriangle",
			"cHeMMts: meaningful text",
			1000, 500);
	c->Divide(2,1);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon
//			+ "&&" + "fRTEStripCorr != 5"
			+ "&&" + "ERQTelescopeCsIDigi_Central_telescope_CsI_0.fBlockNb != 5"
			+ "&&" + targetCondition;


	tr->SetMarkerSize(0.9);

	var = Form("fTMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
			m3H, massOfProducts);
//	var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());
//	var.Form("fLT20EdepCorrected*1000:%s.fEdep*1000", LTY.Data());

	c->cd(1);

	tr->Draw(var, con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();

	c->cd(2);
	tr->Draw(var+">>hPureTriangleT(15,-5.,19.,15,0.,13.)", con, "col text");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->SetTitle("Both, corr MM(^{7}H) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("hPureTriangleT"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
}

void DrawGScandidate(TString option = "") {

	Info("DrawGScandidate", "Meaningful text");
	Info("DrawGScandidate",
			"High statistics needed, slow drawing; available - %lld",
			tr->GetEntries());

	TString conGScandidate;
	TString conGScandidateLarge;

	if (option.Contains("showSpectra")) {

		TCanvas *c = new TCanvas("cGScandidate",
				"cGScandidate: both detectors",
				1400, 1000);
		c->Divide(3,2);

		////////////////////
		// conditions
		////////////////////

		//target
		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

		//triangle
		TString conTriangle = Form(" && fTMeasuredCorrectedCM.E()-%f <= 1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
				m3H, massOfProducts);

		//without triangle
//		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition;
//		conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
//				+ genCon + "&&" + targetCondition
//				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts);
//		conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
//				+ genCon + "&&" + targetCondition
//				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts);

		//with triangle
		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition
				+ conTriangle;
		conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts)
				+ conTriangle;
		conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts)
				+ conTriangle;

		//experimental condition
//		conGScandidate.Append(" && fRTEStripCorr != 12");
//		conGScandidate.Append(" && fLT20StripNbCorrected != 0");
//
//		conGScandidateLarge.Append(" && fRTEStripCorr != 12");
//		conGScandidateLarge.Append(" && fLT20StripNbCorrected != 0");

		var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);

		c->cd(1);
		tr->Draw(var+">>hMMboth(20, -5., 20.)", con);
		((TH1F*)gPad->GetPrimitive("hMMboth"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMboth"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMboth"))->GetYaxis()->SetTitle("counts/1.25 MeV");
		gPad->Update();
//		return;

		c->cd(4);
		tr->Draw(var+">>hMMbothHR(83, -5., 20.)", con);
		((TH1F*)gPad->GetPrimitive("hMMbothHR"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMbothHR"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMbothHR"))->GetYaxis()->SetTitle("counts/0.3 MeV");
		gPad->Update();

		c->cd(2);
		tr->Draw(var+">>hMMbothZoom(9, -1.25., 10.)", con);
		((TH1F*)gPad->GetPrimitive("hMMbothZoom"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMbothZoom"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMbothZoom"))->GetYaxis()->SetTitle("counts/1.25 MeV");
		gPad->Update();

		tr->SetLineColor(kGreen);
		cout << tr->Draw(var, conGScandidate, "same") << endl;
		tr->SetLineColor(kBlue+2);
		gPad->Update();

		c->cd(5);
		//	tr->Draw(var+">>hMMbothHRzoom(36, -1.25, 10.)", con);
		tr->Draw(var+">>hMMbothHRzoom(36, -0.8, 10.)", con);
		((TH1F*)gPad->GetPrimitive("hMMbothHRzoom"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMbothHRzoom"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMbothHRzoom"))->GetYaxis()->SetTitle("counts/0.3 MeV");
		gPad->Update();

		tr->SetLineColor(kGreen);
		cout << tr->Draw(var, conGScandidate, "same") << endl;
		tr->SetLineColor(kBlue+2);
		gPad->Update();

		c->cd(3);
		tr->Draw(var+">>hMMbothZoom2(9, -1.25., 10.)", con);
		((TH1F*)gPad->GetPrimitive("hMMbothZoom2"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMbothZoom2"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMbothZoom2"))->GetYaxis()->SetTitle("counts/1.25 MeV");
		gPad->Update();

		tr->SetLineColor(kRed);
		cout << tr->Draw(var, conGScandidateLarge, "same") << endl;
		tr->SetLineColor(kBlue+2);
		gPad->Update();

		c->cd(6);
		//	tr->Draw(var+">>hMMbothHRzoom(36, -1.25, 10.)", con);
		tr->Draw(var+">>hMMbothHRzoom2(36, -0.8, 10.)", con);
		((TH1F*)gPad->GetPrimitive("hMMbothHRzoom2"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hMMbothHRzoom2"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hMMbothHRzoom2"))->GetYaxis()->SetTitle("counts/0.3 MeV");
		gPad->Update();

		tr->SetLineColor(kRed);
		cout << tr->Draw(var, conGScandidateLarge, "same") << endl;
		tr->SetLineColor(kBlue+2);
		gPad->Update();

	}//showSpectra

	if (option.Contains("showOffsets")) {
		TCanvas *c = new TCanvas("cGScandidateOffsets",
				"cGScandidateOffsets: both detectors",
				1400, 1000);
		c->Divide(3,2);

		//conditions
		TString conTriangle = Form(" && fTMeasuredCorrectedCM.E()-%f <= 1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
					m3H, massOfProducts);

//		TString conTriangleModest = Form(" && fTMeasuredCorrectedCM.E()-%f <= -1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
//							m3H, massOfProducts);

		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";
		con = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+conTriangle;

		//drawing
		for (Int_t i = 0; i < 6; i++) {
			c->cd(i+1);

			const Int_t noBins = 36;
			const Float_t localMin = -.8;
			const Float_t localMax = 10.;
			const Float_t localBinSize = (localMax-localMin)/noBins;

			TString histName = Form("hMMbothHRzoom%d", i);
			var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f>>%s(%d, %f, %f)",
					massOfProducts,
					histName.Data(),
					noBins, localMin+i*localBinSize/6., localMax+i*localBinSize/6.);
			cout << var << endl;

			tr->Draw(var, con);
			((TH1F*)gPad->GetPrimitive(histName))
					->SetTitle(Form("Both, MM(^{7}H), offset=%f", i*localBinSize/6.));
			((TH1F*)gPad->GetPrimitive(histName))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
			((TH1F*)gPad->GetPrimitive(histName))->GetYaxis()->SetTitle("counts/0.3 MeV");
			gPad->Update();

//			var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);
//			tr->SetLineColor(kGreen);
//			tr->Draw(var, con+conTriangle, "same");
//			gPad->Update();

//			tr->SetLineColor(kBlue+2);
			gPad->Update();
		}

	}//showOffsets


	if (option.Contains("showAngles")) {

		TCanvas *c = new TCanvas("cGScandidateAngles",
				"cGScandidateAngles: both detectors",
				1800, 600);
		c->Divide(3,1);

		////////////////////
		// conditions
		////////////////////

		//target
		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

		//triangle
		TString conTriangle = Form(" && fTMeasuredCorrectedCM.E()-%f <= 1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
				m3H, massOfProducts);

		//without triangle
		//		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition;
		//		conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
		//				+ genCon + "&&" + targetCondition
		//				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts);
		//		conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
		//				+ genCon + "&&" + targetCondition
		//				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts);

		//with triangle
		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition
				+ conTriangle;
		conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts)
				+ conTriangle;
		conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts)
				+ conTriangle;

		//experimental condition
				conGScandidate.Append(" && fRTEStripCorr != 12");
				conGScandidate.Append(" && fLT20StripNbCorrected != 0");
		//
		//		conGScandidateLarge.Append(" && fRTEStripCorr != 12");
		//		conGScandidateLarge.Append(" && fLT20StripNbCorrected != 0");

		var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);

		tr->SetMarkerSize(1.7);

		c->cd(1);
		tr->Draw("fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg():"+var, con);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, angular correlation, CM of reaction");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle(^{7}H) in reaction CM (deg.)");
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		tr->Draw("fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg():"+var, conGScandidate, "same");
		tr->SetMarkerColor(kBlack);
		gPad->Update();

		c->cd(2);
		tr->Draw("fAngleLABhtMeasuredCorrected*TMath::RadToDeg():"+var, con);
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, angular correlation, LAB");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle(^{3}H vs. ^{7}H) in LAB (deg.)");
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		tr->Draw("fAngleLABhtMeasuredCorrected*TMath::RadToDeg():"+var, conGScandidate, "same");
		tr->SetMarkerColor(kBlack);
		gPad->Update();

		c->cd(3);
		tr->Draw("fAngleCMof7HhtMeasuredCorrected*TMath::RadToDeg():"+var, con);
//		((TH1F*)gPad->GetPrimitive("hMMboth"))->SetTitle("Both, MM(^{7}H), r_{beam} = 8 mm");
//		((TH1F*)gPad->GetPrimitive("hMMboth"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
//		((TH1F*)gPad->GetPrimitive("hMMboth"))->GetYaxis()->SetTitle("counts/1.25 MeV");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, angular correlation, CM of ^{7}H");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("angle(^{3}H vs. ^{7}H) in CM of ^{7}H (deg.)");
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		tr->Draw("fAngleCMof7HhtMeasuredCorrected*TMath::RadToDeg():"+var, conGScandidate, "same");
		tr->SetMarkerColor(kBlack);
		gPad->Update();

		tr->SetMarkerSize(0.7);

	}

	if (option.Contains("showTritiumEnergy")) {

		TCanvas *c = new TCanvas("cGScandidateTritium",
				"cGScandidateTritium: both detectors",
				1200, 600);
		c->Divide(2,1);

		////////////////////
		// conditions
		////////////////////

		//target
		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

		//triangle
		TString conTriangle = Form(" && fTMeasuredCorrectedCM.E()-%f <= 1.0+4/7*(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
				m3H, massOfProducts);

		//without triangle
		//		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition;
		//		conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
		//				+ genCon + "&&" + targetCondition
		//				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts);
		//		conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
		//				+ genCon + "&&" + targetCondition
		//				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts);

		//with triangle
		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon + "&&" + targetCondition
				+ conTriangle;
		conGScandidate = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<3.", massOfProducts)
				+ conTriangle;
		conGScandidateLarge = "(fHeFlagRT==1 || fHeFlagLT==1) && "
				+ genCon + "&&" + targetCondition
				+ "&&" + Form("fHydrogenMeasuredCorrectedCM.Mag()-%f<5.", massOfProducts)
				+ conTriangle;

		//experimental condition
//		conGScandidate.Append(" && fRTEStripCorr != 12");
//		conGScandidate.Append(" && fLT20StripNbCorrected != 0");
		//
		//		conGScandidateLarge.Append(" && fRTEStripCorr != 12");
		//		conGScandidateLarge.Append(" && fLT20StripNbCorrected != 0");

//		var = Form("fHydrogenMeasuredCorrectedCM.Mag()-%f", massOfProducts);

		tr->SetMarkerSize(1.7);

		c->cd(1);
		var = Form("fTMeasuredCorrectedCM.E()-%f:fHydrogenMeasuredCorrectedCM.Mag()-%f",
					m3H, massOfProducts);
//		tr->Draw("fHydrogenMeasuredCorrectedCMreaction.Theta()*TMath::RadToDeg():"+var, con);
		tr->Draw(var, conGScandidate);
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, corr MM(^{7}H) with E(^{3}H), CM of reaction");
		((TH2F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM (^{7}H) (MeV)");
		((TH2F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
//			((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
//			((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		tr->Draw(var, conGScandidate
				+Form(" && (fTMeasuredCorrectedCM.E()-%f)/(fHydrogenMeasuredCorrectedCM.Mag()-%f)>0.8",
						m3H, massOfProducts), "same");
		tr->SetMarkerColor(kBlack);
		gPad->Update();


		c->cd(2);
		var = Form("(fTMeasuredCorrectedCM.E()-%f)/(fHydrogenMeasuredCorrectedCM.Mag()-%f)",
							m3H, massOfProducts);
		tr->Draw(var, conGScandidate);
//		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, angular correlation, LAB");
		((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Both, tritium correlation, CM of reaction");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("\\varepsilon (^{3}H)");
		((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("counts");
		gPad->Update();

		tr->SetLineColor(kGreen);
		tr->Draw(var, conGScandidate
				+Form(" && (fTMeasuredCorrectedCM.E()-%f)/(fHydrogenMeasuredCorrectedCM.Mag()-%f)>0.8",
						m3H, massOfProducts), "same");
		tr->SetLineColor(kBlue+2);
		gPad->Update();

	}
	return;
}


void DrawIDplotCorrectedWithCutsFinal(const Int_t showNoStrips = 12,
		Int_t firstStrip = 0, TString telescope = "", const Bool_t logZ = 0) {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal", "High statistics needed, slow drawing; used %lld entries", drawEntries);

	if (telescope.EqualTo("")) Error("DrawIDplotCorrectedWithCutsFinal", "No telescope was set");

	if (telescope.Contains("R")) {
		TString canvasName = Form("cdEEidPlotRight_%d_%d", showNoStrips, firstStrip);
		TCanvas *cR = new TCanvas(canvasName, "cdEEidPlotRight: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
		Int_t noPads = DivideCanvas(cR, firstStrip, showNoStrips);

		Long64_t tCount = 0;

		for (Int_t i = 0; i < noPads; i++) {
			cR->cd(i+1);

			tr->SetMarkerColor(kBlack);
			tr->SetMarkerSize(0.2);
			var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());

			con.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
					"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.0045 && %s.fEdep < 0.045 "
					"",
					i+firstStrip, RTY.Data(), RT3rd.Data(),
					RTY.Data()

			);

			//draw all
			tr->SetMarkerSize(0.2);
			tr->Draw(var, con + "&& fTrigger==3", "", drawEntries);
			((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(Form("RT, strip No. %d", i+firstStrip));
			gPad->Update();

			cHelium3[i+firstStrip]->SetLineWidth(3);
			cHelium3[i+firstStrip]->Draw("same");
			gPad->Update();

			//draw selection
			targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";
			con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon
					+ "&&" + targetCondition
					+ "&&" + Form("fRTEStripCorr == %d", i+firstStrip);

			tr->SetMarkerColor(kGreen);
			tr->SetMarkerSize(1.4);
			tr->Draw(var, con + "&& fTrigger==3", "same", drawEntries);
			gPad->Update();

		}

		Info("DrawIDplotCorrectedWithCutsFinal", "%lld 3He-3H coincidences found in whole data.", tCount);

	}

	if (telescope.Contains("L")) {
		TString canvasName = Form("cdEEidPlotLeft_%d_%d", showNoStrips, firstStrip);
		TCanvas *cL = new TCanvas(canvasName, "cdEEidPlotLeft: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
		Int_t noPads = DivideCanvas(cL, firstStrip, showNoStrips);

		Long64_t tCount = 0;

		for (Int_t i = 0; i < noPads; i++) {
			cL->cd(i+1);

			tr->SetMarkerColor(kBlack);
			tr->SetMarkerSize(0.2);
//			var.Form("fRTEdepCorr*1000:%s.fEdep*1000", RTY.Data());
			var.Form("fLT20EdepCorrected*1000:%s.fEdep*1000", LTY.Data());

			con.Form("fLT20StripNbCorrected == %d && Length$(%s) == 1 && Length$(%s) == 0 "
					"&& fLT20EdepCorrected > 0. && fLT20EdepCorrected < 0.005 && %s.fEdep < 0.05 "
					"",
					i+firstStrip, LTY.Data(), LT3rd.Data(),
					LTY.Data()

			);

			//draw all
			tr->SetMarkerSize(0.2);
			tr->Draw(var, con + "&& fTrigger==2", "", drawEntries);
			((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle(Form("LT, strip No. %d", i+firstStrip));
			gPad->Update();

			cLTHelium3[i+firstStrip]->SetLineWidth(3);
			cLTHelium3[i+firstStrip]->Draw("same");
			gPad->Update();

//			return;

			//draw selection
			targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";
			con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon
					+ "&&" + targetCondition
					+ "&&" + Form("fLT20StripNbCorrected == %d", i+firstStrip);

			tr->SetMarkerColor(kGreen);
			tr->SetMarkerSize(1.4);
			tr->Draw(var, con + "&& fTrigger==2", "same", drawEntries);
			gPad->Update();

		}

		Info("DrawIDplotCorrectedWithCutsFinal", "%lld 3He-3H coincidences found in whole data.", tCount);
	}
}

void DrawCleanTritons(const Int_t showNoStrips = 16,
		const Int_t firstStrip = 0, const Bool_t makeCuts = 0) {

	TString canvasName = Form("cdEEidPlotCentral_%d_%d", showNoStrips, firstStrip);
	TCanvas *c6 = new TCanvas(canvasName, "cdEEidPlotCentral: dE-E: Si vs. max(CsI), mult(Si)==1, CsI time cuts", 1000, 1000);
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

//		cTritium[i+firstStrip]->Draw();
//		cTritium[i+firstStrip]->SetLineColor(kRed);
//		cTritium[i+firstStrip]->SetLineWidth(3);
//		gPad->Update();

		tr->SetMarkerSize(0.5);

		tr->SetMarkerColor(kBlack);
		var.Form("%s.fEdep*1000:Max$(%s.fEdep)", CTX.Data(), CTCsI.Data());
		con.Form("%s.fBlockNb == %d && Length$(%s)==1 && %s.fEdep<0.016 "
//				"&& Max$(%s.fEdep)<2000",
				"&& Max$(%s.fEdep)<200",
				CTCsI.Data(), i+firstStrip, CTX.Data(), CTX.Data(), CTCsI.Data());
		tr->Draw(var, con + "&& trigger==3", "", 10000000);
		TString hTitle;
		hTitle.Form("dE-E: CsI==%d", i+firstStrip);
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle(hTitle.Data());
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("MeV");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("MeV");
		gPad->Update();

		cTritium[i+firstStrip]->SetLineWidth(3);
		cTritium[i+firstStrip]->Draw();
		gPad->Update();

		tr->SetMarkerColor(kGreen);
		tr->SetMarkerSize(1.4);

		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";
		con = "(fHeFlagRT==1 || fHeFlagLT==1) && " + genCon
				+ "&&" + targetCondition
				+ " && " + Form("fHeMeasuredCorrected.E()-%f<%f", m3He, cut3HeEnergy)
				+ "&&" + Form("%s.fBlockNb == %d", CTCsI.Data(), i+firstStrip);

		tr->Draw(var, con, "same");
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
//		Long64_t currTritiumCount = tr->Draw(var, con + " && trigger==3", "same");
//		tCount += currTritiumCount;
//		cout << currTritiumCount << endl;
		gPad->Update();


	}//for crystals

	Info("DrawCleanTritons", "%lld tritons found in whole data.", tCount);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////




void DrawMMspectrumTritiumSelection() {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMMtritiumSelection",
			"cHeMMts: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on",
			1400, 1150);
	c->Divide(3,3);

	////////////////////
	// r(beam) = 9 mm
	////////////////////

//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";
	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";
	con = "fHeFlag==1  && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && Length$(" + RTY + ") "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(1);
	tr->Draw("fTritiumKinMeasuredCorrected>>hT9(50, 30., 130.)", con);
	((TH1F*)gPad->GetPrimitive("hT9"))->SetTitle("measured E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hT9"))->GetXaxis()->SetTitle("E(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hT9"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	con.Append(" && fTritiumKinMeasuredCorrected>65.");
	tr->SetLineColor(kGreen);
	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(4);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeasT(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeasT"))->SetTitle("measured E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeasT"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeasT"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(7);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalcT(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalcT"))->SetTitle("calculated E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalcT"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalcT"))->GetYaxis()->SetTitle("counts");

	gPad->Update();
//return;


	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	con = "fHeFlag==1 && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && Length$(" + RTY + ")"
			+ "&&" + RTY + ".fEdep*1000<30. "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(2);
	tr->Draw("fTritiumKinMeasuredCorrected>>hT8(50, 30., 130.)", con);
	((TH1F*)gPad->GetPrimitive("hT8"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hT8"))->GetXaxis()->SetTitle("E(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hT8"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	con.Append(" && fTritiumKinMeasuredCorrected>65.");
	tr->SetLineColor(kGreen);
	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8T(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8T"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8T"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8T"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(8);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc8T(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalc8T"))->SetTitle("calculated E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalc8T"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalc8T"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	con = "fHeFlag==1  && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && " "Length$(" + RTY + ")"
			+ " && " + RTY + ".fEdep*1000<30. "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(3);
	tr->Draw("fTritiumKinMeasuredCorrected>>hT7(50, 30., 130.)", con);
	((TH1F*)gPad->GetPrimitive("hT7"))->SetTitle("measured E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hT7"))->GetXaxis()->SetTitle("E(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hT7"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	con.Append(" && fTritiumKinMeasuredCorrected>65.");
	tr->SetLineColor(kGreen);
	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(6);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7T(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas7T"))->SetTitle("measured E(^{3}He), r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7T"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7T"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

	c->cd(9);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc7T(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalc7T"))->SetTitle("calculated E(^{3}He), r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalc7T"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalc7T"))->GetYaxis()->SetTitle("counts");
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


	con = "fHeFlag==1 && " + MakeGeneralTritiumCut()
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
