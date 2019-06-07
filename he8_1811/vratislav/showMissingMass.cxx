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
//todo: to be deleted:
#include "cutsHelium4.cxx"
//#include "cutsTritium.cxx"
#include "cutsTritiumCal.cxx"
#include "cutsCsIcal.cxx"

//RT first layer
const TString RT20X = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0";
//RT second layer
const TString RTY = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0";
//RT third layer
const TString RT3rd = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0";

//CsI layer
const TString CTCsI = "ERQTelescopeCsIDigi_Central_telescope_CsI_0";

TChain *tr;
TChain *trIn;

TMarker *mP[3][4];  //[energies][particles], energies: 10, 20, 30 MeV, particles: 3,4,6,8He
TMarker *mPcorrected[16][3][4]; //the same but for different strips

//auxiliary variables
TString var;
TString con;

//global conditions:
TString targetCondition;
TString timeCondY;
TString timeCondCsI;
TString MWPCtimeCondition;
TString beamIdCondition;

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0);
void InitMarkers();
void InitCorrectedMarkers();
void InitExternalCuts();
void DrawIDplotCorrectedWithCutsFinal (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0);
void DrawTargetPosition(TString beamProjCondition = "");

void DrawPartAngles(TString beamProjCondition = "");
void DrawMMspectrumTwoMethodsComparison();
void DrawMMspectrumTritiumSelection();
void DrawMMspectrumCM();
void DrawMMspectrumPureTriangle();
void DrawMMspectrumAngles();
void DrawMMspectrumAnalysis();
void DrawCorrelationsEnergies();
void DrawCorrelationsAngles();
void DrawAngularAnalysis();
void DrawMMsplitted3HeLABAngle();


void showMissingMass(const Bool_t allStat = 1) {

	InitTrees(allStat);
//	InitTrees(allStat, 1);

	InitMarkers();
	InitCorrectedMarkers();

	InitExternalCuts();

//	DrawIDplotCorrectedWithCutsFinal(4, 2);
//	DrawIDplotCorrectedWithCutsFinal(12, 0);
//	DrawTargetPosition();
//	DrawPartAngles();

	DrawMMspectrumTwoMethodsComparison();
//	DrawMMspectrumTritiumSelection();
	DrawMMspectrumCM();
	DrawMMspectrumPureTriangle();
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
	const Int_t run = 10;
	const Int_t noFiles = 23;
//	const Int_t noFiles = 7;

//	TString	inPath = "~/data/exp1811/calibrated_filtered/reco/";
//	TString	inPath = "~/data/exp1811/calibrated_filtered_CsI/reco/";
	TString	inPath = "~/data/exp1811/calibrated_filtered_CsI/reco_6H/";

	tr = new TChain("reco");
	if (!background) {
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
		}

//		inPath = "~/data/exp1811/calibrated_filtered/";
		inPath = "~/data/exp1811/calibrated_filtered_CsI/";
		trIn = new TChain("er");
		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.Digi.root", inPath.Data(), run, i);
			trIn->Add(inFile.Data());
		}

		if (allStat) {
			inFile.Form("%she8_%02d_*", inPath.Data(), 7);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 8);
			trIn->Add(inFile.Data());
			inFile.Form("%she8_%02d_*", inPath.Data(), 9);
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
		inPath = "~/data/exp1811/calibrated_filtered_CsI/background/reco/";

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
		inPath = "~/data/exp1811/calibrated_filtered_CsI/background/";
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

}

void InitMarkers() {
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
	const Bool_t useCsICuts = 1;

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

	if (useCsICuts) {
		cutsCsI();
	}

	//time condition for Y strips from cutsRTY()
	timeCondY.Form("(cutRTY_0 || cutRTY_1 || cutRTY_2 || cutRTY_3"
			" || cutRTY_4 || cutRTY_5 || cutRTY_6 || cutRTY_7"
			" || cutRTY_8 || cutRTY_9 || cutRTY_10 || cutRTY_11"
			" || cutRTY_12 || cutRTY_13 || cutRTY_14 || cutRTY_15)");

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

TString MakeGeneralHeliumCut() {

	TString cut;

	//for all 16 strips in thin detector
	cut.Form(" ( (fRTEStripCorr == %d && %s)", 0, cHelium3[0]->GetName());
	for (Int_t i = 1; i < 16; i++) {
		TString stripCondition;
		stripCondition.Form(" || (fRTEStripCorr ==%d && %s)", i, cHelium3[i]->GetName());
		cut.Append(stripCondition);
	}
	cut.Append(")");

//	cout << endl << cut << endl << endl;

	return cut;
}

TString MakeGeneralRT20TimeCut() {

	TString cut;

	//for all 16 strips in thin detector
	cut.Form(" ( (fRTEStripCorr == %d && %s)", 0, cRT20X[0]->GetName());
	for (Int_t i = 1; i < 16; i++) {
		TString stripCondition;
		stripCondition.Form(" || (fRTEStripCorr ==%d && %s)", i, cRT20X[i]->GetName());
		cut.Append(stripCondition);
	}
	cut.Append(")");

//	cout << endl << cut << endl << endl;

	return cut;
}

TString MakeHeCut(/*const Int_t strip*/) {
	//if strip == 16 than for all strips


	TString condition;

	/*condition.Form("fRTEStripCorr == %d && Length$(%s) == 1 && Length$(%s) == 0 "
			"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
			"",
			strip, RTY.Data(), RT3rd.Data(),
			RTY.Data()

	);*/

	condition.Form("Length$(%s) == 1 && Length$(%s) == 1 && Length$(%s) == 0 "
//			"&& fRTEdepCorr > 0. && fRTEdepCorr < 0.005 && %s.fEdep < 0.05 "
			"",
			RT20X.Data(), RTY.Data(), RT3rd.Data()
//			RTY.Data()

	);

	//add target condition
	condition.Append("&&" + targetCondition);

	//add tritium coincidences
//	TString tritium = MakeGeneralTritiumCut();
	condition.Append(" && " + MakeGeneralTritiumCut());

	//add 3He ID cut
//	condition.Append(" && " + (TString)cHelium3[strip]->GetName());
	condition.Append(" && " + MakeGeneralHeliumCut());

	//add RT time cuts
//	condition.Append(" && " + TString(cRT20X[strip]->GetName()));
	condition.Append(" && " + MakeGeneralRT20TimeCut());
	condition.Append(" && " + timeCondY );

	//following conditions are already
	//taken into account during Digi process

	//add MWPC time condition
//	condition.Append(" && " + MWPCtimeCondition);

	//add beam condition
//	condition.Append(" && " + beamIdCondition);

	return condition;
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

void DrawIDplotCorrectedWithCutsFinal (const Int_t showNoStrips = 12,
		Int_t firstStrip = 0) {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
//	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, used %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cHeID", "cHeID: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1300, 1000);
	Int_t noPads = DivideCanvas(c, firstStrip, showNoStrips);

	Long64_t tCount = 0;

	for (Int_t i = 0; i < noPads; i++) {
		c->cd(i+1);

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
		con.Append(" && " + targetCondition);
		tr->Draw(var, con, "same");
		gPad->Update();

		//draw with tritium coincidences
		tr->SetMarkerColor(kBlue);
		tr->SetMarkerSize(0.9);
		TString tritium = MakeGeneralTritiumCut();
		con.Append(" && " + tritium);
		tr->Draw(var, con, "same");
		gPad->Update();

//		continue;

		//draw with all conditions
		tr->SetMarkerColor(kGreen);

		/*
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
		*/

//		con = MakeHeCut(i+firstStrip);
//		con.Form("fRTEStripCorr == %d && %s", i+firstStrip, MakeHeCut().Data());
//		Long64_t currTritiumCount = tr->Draw(var, con, "same", drawEntries);
		con.Form("fRTEStripCorr == %d && fHeFlag==0", i+firstStrip);
		con.Form("fRTEStripCorr == %d && fHeFlag==0 && %s.fEdep>0.", i+firstStrip, RTY.Data());

		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9^2";
		con.Form("fRTEStripCorr == %d && fHeFlag==1 && %s.fEdep>0.", i+firstStrip, RTY.Data());
		Long64_t currTritiumCount = tr->Draw(var, con
				+ " && " + MakeGeneralTritiumCut()
				+ "&&" + targetCondition,
				"same");
		tCount += currTritiumCount;
		cout << currTritiumCount << endl;

		gPad->Update();

		cHelium3[i+firstStrip]->Draw();
	}

	Info("DrawCleanTritons", "%lld 3He-3H coincidences found in whole data.", tCount);

	DrawTargetPosition(targetCondition);

}

void DrawTargetPosition(TString beamProjCondition = "") {

//	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
//	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, used %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cTargetPosMM", "cTargetPosMM: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1000, 1000);
//	c->Divide(2,2);

//	c->cd(1);
	tr->SetMarkerSize(0.2);
	tr->SetMarkerColor(kBlack);
	tr->Draw("fYt:fXt", "fYt>-40. && fXt>-40.", "col");
//	tr->Draw("fXt", "fYt>-40. && fXt>-40.", "col");
	gPad->Update();
	tr->SetMarkerSize(0.9);
	tr->SetMarkerColor(kBlue);
//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 6^2";
	if (beamProjCondition == "") {
		targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9^2";
	} else {
		targetCondition = beamProjCondition;
	}
//	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 10.5^2";
	tr->Draw("fYt:fXt", "fHeFlag==1", "same");
	gPad->Update();
	tr->SetMarkerColor(kGreen);
//	cout << tr->Draw("fYt:fXt", "fHeFlag==1 && " + MakeGeneralTritiumCut(), "same") << endl;
	cout << tr->Draw("fYt:fXt", "fHeFlag==1 && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition, "same") << endl;
	gPad->Update();

}

void DrawPartAngles(TString beamProjCondition = "") {

//	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
//	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, used %lld entries",
			tr->GetEntries());

	TCanvas *c = new TCanvas("cAngles", "cAngles: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on", 1000, 1000);
	c->Divide(2,2);

	c->cd(1);
//	tr->SetMarkerSize(0.2);
//	tr->SetMarkerColor(kBlack);
	tr->Draw("fHeMeasuredCorrected.Theta()*TMath::RadToDeg()", "fHeMeasuredCorrected.Theta()>0.", "");
//	tr->Draw("fXt", "fYt>-40. && fXt>-40.", "col");
	gPad->Update();

	c->cd(2);
	//	tr->SetMarkerSize(0.2);
	//	tr->SetMarkerColor(kBlack);
		tr->Draw("fBeamMomentumTarget.Theta()*TMath::RadToDeg()", "fBeamMomentumTarget.Theta()>0.", "");
	//	tr->Draw("fXt", "fYt>-40. && fXt>-40.", "col");
		gPad->Update();

	c->cd(3);
//	tr->Draw("fBeamMomentumTarget.Theta()*TMath::RadToDeg()", "fBeamMomentumTarget.Theta()>0.", "");
	gPad->Update();

	c->cd(4);

}

void DrawMMspectrumTwoMethodsComparison() {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM",
			"cHeMM: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on",
			1500, 1000);
	c->Divide(3,2);

	////////////////////
	// r(beam) = 9 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<30. "
//			+ " && Max$(" + CTCsI + ".fEdep)<60"
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(1);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(14, -5., 21.)", con);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->SetTitle("measured E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(4);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc(13, -5., 21.)", con);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc(14, -5., 21.)", con);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalc"))->SetTitle("calculated E(^{3}He), r_{beam} = 9 mm");
//	((TH1F*)gPad->GetPrimitive("hMMcalc"))->RebSetOffTitle("calculated E(^{3}He), r_{beam} = 9 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalc"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalc"))->GetYaxis()->SetTitle("counts");

	gPad->Update();
//return;


	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<30. "
//			+ " && Max$(" + CTCsI + ".fEdep)<60"
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(2);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(14, -5., 21.)", con);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas8(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	c->cd(5);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc8(13, -5., 21.)", con);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc8(14, -5., 21.)", con);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc8(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalc8"))->SetTitle("calculated E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalc8"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalc8"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	////////////////////
	// r(beam) = 7 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 7.^2";

	con = "fHeFlag==1  && "
			+ MakeGeneralTritiumCut() + " && "
			+ targetCondition + " && "
			"Length$(" + RTY + ") && "
			+ RTY + ".fEdep*1000<30. "
//			+ " && Max$(" + CTCsI + ".fEdep)<60"
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(3);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(13, -5., 21.)", con);
	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(14, -5., 21.)", con);
//	tr->Draw("fHydrogenMeasuredCorrected.Mag()-2808.92-4*939.565>>hMMmeas7(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->SetTitle("measured E(^{3}He), r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas7"))->GetYaxis()->SetTitle("counts");

	gPad->Update();

	c->cd(6);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc7(13, -5., 21.)", con);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc7(14, -5., 21.)", con);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc7(17, -5., 20.5)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalc7"))->SetTitle("calculated E(^{3}He), r_{beam} = 7 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalc7"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalc7"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

}

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

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 9.^2";

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

void DrawMMspectrumCM() {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM",
			"cHeMMts: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on",
			1400, 1000);
	c->Divide(3,2);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	//////////////////////////////
	//Golovkov triangle
	//////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "4*x/7", 0, 16);
	TString conTriangleMeas = " && fTMeasuredCorrectedCM.E()-2808.92 <= 4/7*(fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565)";
	TString conTriangleCalc = " && fTCalculatedCM.E()-2808.92 <= 4/7*(fHydrogenCalculated.Mag()-2808.92-4*939.565)";

	conTriangleMeas.Append(" && fTritiumKinMeasuredCorrected>65.");
	conTriangleCalc.Append(" && fTritiumKinMeasuredCorrected>65.");

	////////////////////////////
	//7H MM measured
	////////////////////////////

	con = "fHeFlag==1 && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && Length$(" + RTY + ")"
			+ "&&" + RTY + ".fEdep*1000<30. "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

	c->cd(1);
//	tr->Draw("fHydrogenCalculatedCM.Mag()>>hT8(14, -5., 21.)", con);
//	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92>>hTcmMeas(20, -5., 10.)", con);
//	tr->SetMarkerSize(0.9);
//	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fT.E()-2808.92", con);
	((TH1F*)gPad->GetPrimitive("hTcmMeas"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hTcmMeas"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
	((TH1F*)gPad->GetPrimitive("hTcmMeas"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

//	con.Append(" && fTritiumKinMeasuredCorrected>65.");
	tr->SetLineColor(kGreen);
//	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(2);
	//	tr->Draw("fHydrogenCalculatedCM.Mag()>>hT8(14, -5., 21.)", con);
	//	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
	tr->SetMarkerSize(0.9);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr E(^{3}He) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + conTriangleMeas,
			"same");
	tr->SetMarkerColor(kBlack);

	c->cd(3);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565>>hMMmeas8CM(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMmeas8CM"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CM"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMmeas8CM"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
			con + conTriangleMeas,
			"same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	////////////////////////////
	//7H MM calculated
	////////////////////////////

	c->cd(4);
	tr->Draw("fTCalculatedCM.E()-2808.92>>hTcmCalc(20, -5., 10.)", con);
	tr->SetMarkerSize(0.5);
	//	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fT.E()-2808.92", con);
		((TH1F*)gPad->GetPrimitive("hTcmCalc"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
		((TH1F*)gPad->GetPrimitive("hTcmCalc"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
		((TH1F*)gPad->GetPrimitive("hTcmCalc"))->GetYaxis()->SetTitle("counts");
	gPad->Update();

	//	con.Append(" && fTritiumKinMeasuredCorrected>65.");
	tr->SetLineColor(kGreen);
	//	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(5);
	tr->SetMarkerSize(0.9);
	//	tr->Draw("fHydrogenCalculatedCM.Mag()>>hT8(14, -5., 21.)", con);
	//	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
	tr->Draw("fTCalculatedCM.E()-2808.92:fHydrogenCalculatedCM.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr E(^{3}He) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
	tr->SetMarkerColor(kRed);
	tr->Draw("fTCalculatedCM.E()-2808.92:fHydrogenCalculatedCM.Mag()-2808.92-4*939.565",
			con + conTriangleCalc,
			"same");
	tr->SetMarkerColor(kBlack);
	gPad->Update();

	c->cd(6);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc8CM(14, -5., 21.)", con);
	((TH1F*)gPad->GetPrimitive("hMMcalc8CM"))->SetTitle("calculated E(^{3}He), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("hMMcalc8CM"))->GetXaxis()->SetTitle("MM calculated (MeV)");
	((TH1F*)gPad->GetPrimitive("hMMcalc8CM"))->GetYaxis()->SetTitle("counts");
	gPad->Update();
	tr->SetLineColor(kGreen);
	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565",
			con + conTriangleCalc,
			"same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

}

void DrawMMspectrumPureTriangle() {

	Info("DrawIDplotCorrectedWithCutsFinal", "Function used for check and correction of 3He cuts");
	const Long64_t drawEntries = 100000000;
	Info("DrawIDplotCorrectedWithCutsFinal",
			"High statistics needed, slow drawing; used %lld entries of %lld",
			drawEntries, tr->GetEntries());

	TCanvas *c = new TCanvas("cHeMM_CM_pureTriangle",
			"cHeMMts: dE-E: 20mcm vs. 1mm, mults==1, corrected for thickness, veto on",
			1000, 500);
	c->Divide(2,1);

	////////////////////
	// r(beam) = 8 mm
	////////////////////

	targetCondition = "( (fYt-2.1)^2 + (fXt+2.2)^2 ) < 8.^2";

	//////////////////////////////
	//Golovkov triangle
	//////////////////////////////

	TF1 *fTriangle = new TF1("fGT", "4*x/7", 0, 16);
	TString conTriangleMeas = " && fTMeasuredCorrectedCM.E()-2808.92 <= 4/7*(fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565)";
	TString conTriangleCalc = " && fTCalculatedCM.E()-2808.92 <= 4/7*(fHydrogenCalculated.Mag()-2808.92-4*939.565)";

	conTriangleMeas.Append(" && fTritiumKinMeasuredCorrected>65.");
	conTriangleCalc.Append(" && fTritiumKinMeasuredCorrected>65.");

	////////////////////////////
	//7H MM measured
	////////////////////////////

	con = "fHeFlag==1 && " + MakeGeneralTritiumCut()
			+ " && " + targetCondition
			+ " && Length$(" + RTY + ")"
			+ "&&" + RTY + ".fEdep*1000<30. "
			+ "&& (fAngleLABhtMeasuredCorrected*TMath::RadToDeg())^2<100.";

//	c->cd(1);
////	tr->Draw("fHydrogenCalculatedCM.Mag()>>hT8(14, -5., 21.)", con);
////	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
//	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92>>hTcmMeas(20, -5., 10.)", con);
////	tr->SetMarkerSize(0.9);
////	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fT.E()-2808.92", con);
//	((TH1F*)gPad->GetPrimitive("hTcmMeas"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
//	((TH1F*)gPad->GetPrimitive("hTcmMeas"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
//	((TH1F*)gPad->GetPrimitive("hTcmMeas"))->GetYaxis()->SetTitle("counts");
//	gPad->Update();

//	con.Append(" && fTritiumKinMeasuredCorrected>65.");
	tr->SetLineColor(kGreen);
//	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
	tr->SetLineColor(kBlue+2);
	gPad->Update();

	c->cd(1);
	//	tr->Draw("fHydrogenCalculatedCM.Mag()>>hT8(14, -5., 21.)", con);
	//	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
	tr->SetMarkerSize(0.9);
	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr E(^{3}He) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
//	tr->SetMarkerColor(kRed);
//	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
//			con + conTriangleMeas,
//			"same");
//	tr->SetMarkerColor(kBlack);

//	c->cd(3);
//	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565>>hMMmeas8CM(14, -5., 21.)", con);
//	((TH1F*)gPad->GetPrimitive("hMMmeas8CM"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
//	((TH1F*)gPad->GetPrimitive("hMMmeas8CM"))->GetXaxis()->SetTitle("MM measured (MeV)");
//	((TH1F*)gPad->GetPrimitive("hMMmeas8CM"))->GetYaxis()->SetTitle("counts");
//	gPad->Update();
//	tr->SetLineColor(kGreen);
//	tr->Draw("fHydrogenMeasuredCorrectedCM.Mag()-2808.92-4*939.565",
//			con + conTriangleMeas,
//			"same");
//	tr->SetLineColor(kBlue+2);
//	gPad->Update();

	////////////////////////////
	//7H MM calculated
	////////////////////////////

//	c->cd(4);
//	tr->Draw("fTCalculatedCM.E()-2808.92>>hTcmCalc(20, -5., 10.)", con);
//	tr->SetMarkerSize(0.5);
//	//	tr->Draw("fTMeasuredCorrectedCM.E()-2808.92:fT.E()-2808.92", con);
//		((TH1F*)gPad->GetPrimitive("hTcmCalc"))->SetTitle("measured E(^{3}He), r_{beam} = 8 mm");
//		((TH1F*)gPad->GetPrimitive("hTcmCalc"))->GetXaxis()->SetTitle("E_{CM}(^{3}H) (MeV)");
//		((TH1F*)gPad->GetPrimitive("hTcmCalc"))->GetYaxis()->SetTitle("counts");
//	gPad->Update();
//
//	//	con.Append(" && fTritiumKinMeasuredCorrected>65.");
//	tr->SetLineColor(kGreen);
//	//	tr->Draw("fTritiumKinMeasuredCorrected", con, "same");
//	tr->SetLineColor(kBlue+2);
//	gPad->Update();

	c->cd(2);
	tr->SetMarkerSize(0.9);
	//	tr->Draw("fHydrogenCalculatedCM.Mag()>>hT8(14, -5., 21.)", con);
	//	tr->Draw("fHydrogenCalculatedCM.M()-2808.92-4*939.565>>hT8(14, -5., 21.)", con);
	tr->Draw("fTCalculatedCM.E()-2808.92:fHydrogenCalculatedCM.Mag()-2808.92-4*939.565", con);
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("measured, corr E(^{3}He) with E(^{3}H), r_{beam} = 8 mm");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitle("MM measured (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetXaxis()->SetTitleSize(0.05);
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitle("E(^{3}H) CM (MeV)");
	((TH1F*)gPad->GetPrimitive("htemp"))->GetYaxis()->SetTitleSize(0.05);
	gPad->Update();
	fTriangle->Draw("same");
	gPad->Update();
//	tr->SetMarkerColor(kRed);
//	tr->Draw("fTCalculatedCM.E()-2808.92:fHydrogenCalculatedCM.Mag()-2808.92-4*939.565",
//			con + conTriangleCalc,
//			"same");
//	tr->SetMarkerColor(kBlack);
//	gPad->Update();

//	c->cd(6);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565>>hMMcalc8CM(14, -5., 21.)", con);
//	((TH1F*)gPad->GetPrimitive("hMMcalc8CM"))->SetTitle("calculated E(^{3}He), r_{beam} = 8 mm");
//	((TH1F*)gPad->GetPrimitive("hMMcalc8CM"))->GetXaxis()->SetTitle("MM calculated (MeV)");
//	((TH1F*)gPad->GetPrimitive("hMMcalc8CM"))->GetYaxis()->SetTitle("counts");
//	gPad->Update();
//	tr->SetLineColor(kGreen);
//	tr->Draw("fHydrogenCalculated.Mag()-2808.92-4*939.565",
//			con + conTriangleCalc,
//			"same");
//	tr->SetLineColor(kBlue+2);
//	gPad->Update();

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
