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
//#include "TMarker.h"
//#include "TLegend.h"
//#include "TLegendEntry.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"


#include <iostream>

using std::cout;
using std::endl;

#endif

#include "cutsRTY.cxx"
#include "cutsRT20X.cxx"
//#include "cutsHelium3.cxx"
//#include "cutsTritium.cxx"

//RT first layer
TString RT20X = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0";
//RT second layer
TString RTY = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0";
//RT third layer
TString RT3rd = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0";

//left telescope
TString LT20X = "ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0";
TString LTY = "ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_Y";
TString LTX = "ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X";
TString LT3rd = "ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD_L_X_0";


//CT x strips
TString CTY = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_Y.fStripNb";
//CT y strips
TString CTX = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X";

TString TOF2 = "BeamDetToFDigi2.fTime";

	//trigger==2: Left telescope
	//trigger==3: Right telescope


TChain *tr;
TChain *trIn;

//auxiliary variables
TString var;
TString con;

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0);
//void InitMarkers();
//void InitCorrectedMarkers();
void InitExternalCuts();

void DrawMults();
void DrawRTPositions();
void DrawLTPositions();
void DrawCTPositions();
void DrawDetectedPoints();
void DrawCTstripNumbering();
void DrawCheckBeam();
void DrawCheckRightTelescope();


//global conditions:
TString targetCondition;
TString timeCondY;
TString MWPCtimeCondition;
TString beamIdCondition;

void showRTposition(const Bool_t allStat = 0) {


	const Bool_t showViewer = 0;

	InitTrees(allStat);
//	InitTrees(allStat, 1);

//	InitMarkers();


	InitExternalCuts();

//	InitCorrectedMarkers();

	if (showViewer) tr->StartViewer();
//	return;

//	DrawMults();
	DrawRTPositions();
	DrawLTPositions();
//	DrawCTPositions();
//	DrawDetectedPoints();
//	DrawCTstripNumbering();
//	DrawCheckBeam();
//	DrawCheckRightTelescope();

	return;
}

void InitTrees(const Bool_t allStat = 0, const Bool_t background = 0) {
	TString inFile;
	const Int_t run = 7;
	//	const Int_t noFiles = 22;
	const Int_t noFiles = 7;

//	TString	inPath = "~/data/exp1811/calibrated_filtered/reco/";
	TString	inPath = "~/data/exp1811/calibrated_filtered_CsI_both/reco/";

	tr = new TChain("reco");
	if (!background) {
		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.reco.root", inPath.Data(), run, i);
			tr->Add(inFile.Data());
		}

		if (allStat) {
//			inFile.Form("%she8_%02d_*", inPath.Data(), 7);
//			tr->Add(inFile.Data());
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
		inPath = "~/data/exp1811/calibrated_filtered_CsI_both/";

		trIn = new TChain("er");
		for (Int_t i = 1; i <= noFiles; i++) {
			inFile.Form("%she8_%02d_%04d.Digi.root", inPath.Data(), run, i);
			trIn->Add(inFile.Data());
		}

		if (allStat) {
//			inFile.Form("%she8_%02d_*", inPath.Data(), 7);
//			trIn->Add(inFile.Data());
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

		inPath = "~/data/exp1811/calibrated_filtered/background_filtered/reco/";

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
		inPath = "~/data/exp1811/calibrated_filtered/background_filtered/";
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

void InitExternalCuts() {
	const Bool_t useFirstLayerCuts = 1;
	const Bool_t useSecondLayerCuts = 1;
	const Bool_t useHeliumCuts = 1;
	const Bool_t useTritiumCuts = 1;

	if (useSecondLayerCuts) {
		cutsRT20X();
	}

	if (useSecondLayerCuts) {
		cutsRTY();
	}

	if (useHeliumCuts) {
//		cutsHelium3();
	}

	if (useTritiumCuts) {
//		cutsTritium();
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

/*TString MakeGeneralTritiumCut() {

	TString cut;

	//for 16 crystals except No.9
	cut.Form(" (%s", cTritium[0]->GetName());
	for (Int_t i = 1; i < 16; i++) {
		if (i==9) continue;
		cut.Append(" || " + (TString)cTritium[i]->GetName());
	}
	cut.Append(")");

//	cout << cut << endl;

	return cut;
}*/

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

void DrawMults() {

	TCanvas *c = new TCanvas("cMults", "cMults: Auxiliary information on multiplicities in RT", 1000, 1000);
	c->Divide(2,2);

	c->cd(1);
	tr->Draw("trigger", "", "");
	gPad->Update();

	c->cd(4);
	var.Form("Length$(%s)", RTY.Data());
	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, con, "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult Y");
	gPad->Update();

	c->cd(3);
	var.Form("Length$(%s)", RT20X.Data());
	con.Form("Length$(%s)>0", RT20X.Data());
	tr->Draw(var, con, "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Mult X");
	gPad->Update();

}

void DrawRTPositions() {

	TCanvas *c = new TCanvas("cRightPositions", "cRightPositions: Auxiliary information on positions in RT", 1500, 1000);
	c->Divide(4,2);
	c->ToggleEventStatus();
	c->ToggleEditor();

	c->cd(1);
//	tr->Draw("fYrtLocal", "fYrtLocal>-100.");
	tr->Draw("fPointRT.Theta()*TMath::RadToDeg()", "fPointRT.Theta()*TMath::RadToDeg()>0.");
	gPad->Update();

	c->cd(2);
	var.Form("fYrtLocal:%s.fStripNb", RTY.Data());
	con.Form("Length$(%s)==1 && fYrtLocal>-100.", RTY.Data());
	tr->Draw(var, con, "box");
	gPad->Update();

	c->cd(4);
//	tr->Draw("fTrack", "fYpoint.fZ>0.");
//	tr->Draw("fYpoint.Theta()*TMath::RadToDeg()", "fYpoint.fZ>0.");
	tr->Draw("fPointRT.Y():fPointRT.Z():fPointRT.X()", "");
	gPad->Update();

	c->cd(3);
	tr->SetMarkerSize(0.5);
	//	tr->Draw("fXpoint.fZ:fXpoint.fX>>htemp(200, -180., 0., 200, 0. 180.)", "", "box");
	tr->Draw("fYpointRT2.fZ:fYpointRT2.fY", "", "");
	gPad->Update();

	c->cd(5);
	tr->Draw("fXrtLocal", "fXrtLocal>-100.");
	gPad->Update();

	c->cd(6);
	var.Form("%s.fStripNb:fXrtLocal", RT20X.Data());
	con.Form("Length$(%s)==1 && fXrtLocal>-100.", RT20X.Data());
	tr->Draw(var, con, "box");
	gPad->Update();

	c->cd(8);
//	tr->Draw("fXpoint.fX", "");
//	tr->Draw("fXpoint.Theta()*TMath::RadToDeg()", "fXpoint.fZ>0.");
//	tr->Draw("fXpointLocalRotated.Theta()*TMath::RadToDeg()", "fXpoint.fZ>0.");
	tr->Draw("fPointRT.fZ:fPointRT.fX");
	gPad->Update();
	tr->Draw("fXpointRT1.fZ:fXpointRT1.fX", "", "same");
	gPad->Update();

	c->cd(7);
	tr->SetMarkerSize(0.5);
//	tr->Draw("fXpoint.fZ:fXpoint.fX>>htemp(200, -180., 0., 200, 0. 180.)", "", "box");
	tr->Draw("fXpointRT1.fZ:fXpointRT1.fX", "", "");
//	((TGraph*)gPad->GetPrimitive("Graph"))->GetXaxis()->SetLimits(-80., 80.);
//	((TGraph*)gPad->GetPrimitive("Graph"))->GetHistogram()->SetAxisRange(-50., 50.);
//	return;
	gPad->Update();
//	tr->SetMarkerColor(kRed);
//	tr->Draw("fXpointLocal.fZ:fXpointLocal.fX", "", "same");
//	gPad->Update();
//	tr->SetMarkerColor(kGreen);
//	tr->Draw("fXpointLocalRotated.fZ:fXpointLocalRotated.fX", "", "same");
//	gPad->Update();
//	tr->SetMarkerColor(kMagenta);
//	tr->Draw("fXpointLocalShifted.fZ:fXpointLocalShifted.fX", "", "same");
//	gPad->Update();


}

void DrawLTPositions() {

	TCanvas *c = new TCanvas("cLeftPositions", "cLeftPositions: Auxiliary information on positions in LT", 1500, 1000);
	c->Divide(4,2);
	c->ToggleEventStatus();
	c->ToggleEditor();

	c->cd(1);
//	tr->Draw("fYrtLocal", "fYrtLocal>-100.");
	tr->Draw("fPointLT.Theta()*TMath::RadToDeg()", "fPointLT.Theta()*TMath::RadToDeg()>0.");
	gPad->Update();

	c->cd(2);
	var.Form("fYltLocal:%s.fStripNb", LTY.Data());
	con.Form("Length$(%s)==1 && fYltLocal>-100.", LTY.Data());
	tr->Draw(var, con, "box");
	gPad->Update();

	c->cd(4);
//	tr->Draw("fTrack", "fYpoint.fZ>0.");
//	tr->Draw("fYpoint.Theta()*TMath::RadToDeg()", "fYpoint.fZ>0.");
	tr->Draw("fPointLT.Y():fPointLT.Z():fPointLT.X()", "");
	gPad->Update();

	c->cd(3);
	tr->SetMarkerSize(0.5);
	//	tr->Draw("fXpoint.fZ:fXpoint.fX>>htemp(200, -180., 0., 200, 0. 180.)", "", "box");
	tr->Draw("fYpointLT2.fZ:fYpointLT2.fY", "", "");
	gPad->Update();

	c->cd(5);
	tr->Draw("fXltLocal", "fXltLocal>-100.");
	gPad->Update();

	c->cd(6);
	var.Form("%s.fStripNb:fXltLocal", LT20X.Data());
	con.Form("Length$(%s)==1 && fXltLocal>-100.", LT20X.Data());
	tr->Draw(var, con, "box");
	gPad->Update();

	c->cd(8);
//	tr->Draw("fXpoint.fX", "");
//	tr->Draw("fXpoint.Theta()*TMath::RadToDeg()", "fXpoint.fZ>0.");
//	tr->Draw("fXpointLocalRotated.Theta()*TMath::RadToDeg()", "fXpoint.fZ>0.");
	tr->Draw("fPointLT.fZ:fPointLT.fX");
	gPad->Update();
	tr->Draw("fXpointLT1.fZ:fXpointLT1.fX", "", "same");
	gPad->Update();

	c->cd(7);
	tr->SetMarkerSize(0.5);
//	tr->Draw("fXpoint.fZ:fXpoint.fX>>htemp(200, -180., 0., 200, 0. 180.)", "", "box");
	tr->Draw("fXpointLT1.fZ:fXpointLT1.fX", "", "");
//	((TGraph*)gPad->GetPrimitive("Graph"))->GetXaxis()->SetLimits(-80., 80.);
//	((TGraph*)gPad->GetPrimitive("Graph"))->GetHistogram()->SetAxisRange(-50., 50.);
//	return;
	gPad->Update();
//	tr->SetMarkerColor(kRed);
//	tr->Draw("fXpointLocal.fZ:fXpointLocal.fX", "", "same");
//	gPad->Update();
//	tr->SetMarkerColor(kGreen);
//	tr->Draw("fXpointLocalRotated.fZ:fXpointLocalRotated.fX", "", "same");
//	gPad->Update();
//	tr->SetMarkerColor(kMagenta);
//	tr->Draw("fXpointLocalShifted.fZ:fXpointLocalShifted.fX", "", "same");
//	gPad->Update();


}

void DrawCTstripNumbering() {

	//Si X layer
	TString CTX = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X";
	//Si Y layer
	TString CTY = "ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_Y";

	TString targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";

	TCanvas *c = new TCanvas("cCentralStrips", "cCentralStrips: Auxiliary information on positions in CT", 1500, 1000);
	c->Divide(3,2);
	c->ToggleEventStatus();
	c->ToggleEditor();

	c->cd(1);
	var.Form("%s.fStripNb", CTX.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired X strip C 1mm, trigger==3");
	gPad->Update();

	c->cd(2);
	var.Form("%s.fStripNb", CTX.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired Y strip C 1mm, trigger==3");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fXt<0.";
	tr->SetLineColor(kRed);
	tr->Draw(var, targetCondition + " && trigger==3", "same");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fXt>0.";
	tr->SetLineColor(kGreen);
	tr->Draw(var, targetCondition + " && trigger==3", "same");
	gPad->Update();

	c->cd(3);
	tr->SetMarkerColor(kBlack);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", "", "");
	//	tr->Draw("fPointCT.X():fPointCT.Y():fPointCT.Z()", "", "same");
	gPad->Update();

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";
	tr->SetMarkerColor(kYellow);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", targetCondition, "same");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fXt<0.";
	tr->SetMarkerColor(kRed);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", targetCondition, "same");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fXt>0.";
	tr->SetMarkerColor(kGreen);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", targetCondition, "same");
	gPad->Update();

	c->cd(4);
	tr->SetLineColor(kBlack);
	var.Form("%s.fStripNb", CTY.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired Y strip C 1mm, trigger==3");
	gPad->Update();

	c->cd(5);
	var.Form("%s.fStripNb", CTY.Data());
	//	con.Form("Length$(%s)>0", RTY.Data());
	tr->Draw(var, "trigger==3", "");
	((TH1F*)gPad->GetPrimitive("htemp"))->SetTitle("Fired Y strip C 1mm, trigger==3");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fYt<0.";
	tr->SetLineColor(kRed);
	tr->Draw(var, targetCondition + " && trigger==3", "same");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fYt>0.";
	tr->SetLineColor(kGreen);
	tr->Draw(var, targetCondition + " && trigger==3", "same");
	gPad->Update();

	c->cd(6);
	tr->SetMarkerColor(kBlack);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", "", "");
	gPad->Update();

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";
	tr->SetMarkerColor(kYellow);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", targetCondition, "same");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fYt<0.";
	tr->SetMarkerColor(kRed);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", targetCondition, "same");

	targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2 && fYt>0.";
	tr->SetMarkerColor(kGreen);
	tr->Draw("fPointTarget.Y():fPointTarget.X()", targetCondition, "same");
	gPad->Update();

}

void DrawCTPositions() {

	TCanvas *c = new TCanvas("cCentralPositions", "cCentralPositions: Auxiliary information on positions in CT", 1500, 1000);
	c->Divide(4,2);
	c->ToggleEventStatus();
	c->ToggleEditor();

	c->cd(1);
	tr->Draw("fPointCT.fY", "fPointCT.fZ>0.");
//	tr->Draw("fPointCT.Theta()*TMath::RadToDeg()", "fPointCT.Theta()*TMath::RadToDeg()>0.");
	gPad->Update();

	c->cd(2);
	var.Form("fPointCT.fY:%s.fStripNb", CTY.Data());
	con.Form("Length$(%s)==1 && fPointCT.fZ>0.", CTY.Data());
	tr->Draw(var, con, "box");
	gPad->Update();

	c->cd(4);
//	tr->Draw("fTrack", "fYpoint.fZ>0.");
//	tr->Draw("fYpoint.Theta()*TMath::RadToDeg()", "fYpoint.fZ>0.");
	tr->Draw("fPointCT.Y():fPointCT.X()", "fPointCT.Y()!=0. && fPointCT.X()!=0.", "box");
	gPad->Update();

	c->cd(3);
	tr->SetMarkerSize(0.5);
	//	tr->Draw("fXpoint.fZ:fXpoint.fX>>htemp(200, -180., 0., 200, 0. 180.)", "", "box");
	tr->Draw("fPointCT.fZ:fPointCT.fY", "", "");
	gPad->Update();

	c->cd(5);
	tr->Draw("fPointCT.fX", "fPointCT.fZ>0.");
	gPad->Update();

	c->cd(6);
	var.Form("%s.fStripNb:fPointCT.fX", CTX.Data());
	con.Form("Length$(%s)==1 && fPointCT.fZ>0.", CTX.Data());
	tr->Draw(var, con, "box");
	gPad->Update();

	c->cd(8);
//	tr->Draw("fXpoint.fX", "");
//	tr->Draw("fXpoint.Theta()*TMath::RadToDeg()", "fXpoint.fZ>0.");
//	tr->Draw("fXpointLocalRotated.Theta()*TMath::RadToDeg()", "fXpoint.fZ>0.");
	tr->Draw("fPointCT.fZ:fPointCT.fX");
	gPad->Update();
//	tr->Draw("fXpointRT1.fZ:fXpointRT1.fX", "", "same");
	gPad->Update();

	c->cd(7);
	TH3F *h = new TH3F("h", "h title", 20, -90., 90., 20, 0., 300., 20, -80., 80.);
	h->Draw();

	tr->SetMarkerColor(kRed);
	tr->Draw("fPointCT.Y():fPointCT.Z():fPointCT.X()", "", "same");
	tr->SetMarkerColor(kGreen);
	tr->Draw("fPointRT.Y():fPointRT.Z():fPointRT.X()", "", "same");
//	tr->Draw("fPointCT.X():fPointCT.Y():fPointCT.Z()", "", "same");

	gPad->Update();


}

void DrawDetectedPoints() {

	TCanvas *c = new TCanvas("cPoints", "cPoints: Auxiliary information on positions", 1500, 1000);
//	c->Divide(4,2);
	c->ToggleEventStatus();
	c->ToggleEditor();
//	c->cd(7);
	TH3F *h = new TH3F("h", "h title", 20, -90., 90., 20, 0., 300., 20, -80., 80.);
	h->Draw();

	tr->SetMarkerColor(kRed);
	tr->Draw("fPointCT.Y():fPointCT.Z():fPointCT.X()", "", "same");
	gPad->Update();

	tr->SetMarkerColor(kGreen);
	tr->Draw("fPointRT.Y():fPointRT.Z():fPointRT.X()", "", "same");
	//	tr->Draw("fPointCT.X():fPointCT.Y():fPointCT.Z()", "", "same");
	gPad->Update();

	tr->SetMarkerColor(kBlack);
	tr->Draw("fPointTarget.Y():fPointTarget.Z():fPointTarget.X()", "", "same");
	//	tr->Draw("fPointCT.X():fPointCT.Y():fPointCT.Z()", "", "same");
	gPad->Update();

	TString targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";

	tr->SetMarkerColor(kRed);
	tr->Draw("fPointTarget.Y():fPointTarget.Z():fPointTarget.X()", targetCondition, "same");
	//	tr->Draw("fPointCT.X():fPointCT.Y():fPointCT.Z()", "", "same");
	gPad->Update();

	TLatex *txt1 = new TLatex(0.12, 0.52, "f(x,y)");
	txt1->SetTextColor(kBlue);
	txt1->SetTextFont(42);
	txt1->Draw();
	gPad->Update();
}

void DrawCheckBeam() {

	TString targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";

	TCanvas *c = new TCanvas("cBeam", "cBeam: Auxiliary information on positions", 1500, 1000);
	c->Divide(3,2);
	c->ToggleEventStatus();
	c->ToggleEditor();

	c->cd(1);
	tr->Draw("fBeamToF.fE - 7482.538", "fBeamToF.fE>0.", "");
	gPad->Update();

	c->cd(2);
	tr->Draw("fBeamToF.P()", "fBeamToF.fE>0.", "");
	gPad->Update();

	c->cd(3);
	tr->Draw("fBeamToF.fP.fY:fBeamToF.fP.fX", "fBeamToF.fE>0.", "col");
	gPad->Update();

	c->cd(4);
//	tr->Draw("fBeamKinEtof", "fBeamToF.fE>0.", "");
	tr->Draw("fBeamTarget.Theta()*TMath::RadToDeg()", "fBeamTarget.fE>0.", "");
	gPad->Update();
	tr->SetLineColor(kRed);
	tr->Draw("fBeamTarget.Theta()*TMath::RadToDeg()", "fBeamTarget.fE>0. && " + targetCondition, "same");

	c->cd(5);
	tr->SetLineColor(kBlue+2);
	tr->Draw("fBeamMomentumToF.Mag()", "fBeamToF.fE>0.", "");
	gPad->Update();

	c->cd(6);
	tr->Draw("fBeamTarget.fE - 7482.538", "fBeamTarget.fE>0.", "");

	tr->SetLineColor(kRed);
	tr->Draw("fBeamTarget.fE - 7482.538", "fBeamTarget.fE>0. && " + targetCondition, "same");

	gPad->Update();

}

void DrawCheckRightTelescope() {

	TString targetCondition = "( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2";

	TCanvas *c = new TCanvas("cHeE", "cHeE: Auxiliary information on positions", 1500, 1000);
	c->Divide(4,2);
	c->ToggleEventStatus();
	c->ToggleEditor();

	c->cd(1);
	tr->Draw("fHeKinMeasured", "fHeKinMeasured>0.", "");
	gPad->Update();

	c->cd(2);
	tr->Draw("fHeKinMeasuredCorrected", "fHeKinMeasuredCorrected>0.", "");
	gPad->Update();

	c->cd(3);
	tr->Draw("fHeKinCalculated", "fHeKinCalculated>0.", "");
	gPad->Update();

	c->cd(4);
	tr->Draw("fHeKinCalculatedMap", "fHeKinCalculatedMap>0.", "");
	gPad->Update();

	c->cd(5);
	tr->Draw("fHeKinMeasured - fHeKinMeasured", "fHeKinMeasured>0.", "");
	gPad->Update();

	c->cd(6);
	tr->Draw("fHeKinMeasuredCorrected - fHeKinMeasured", "fHeKinMeasuredCorrected>0.", "");
	gPad->Update();

	c->cd(7);
	tr->Draw("fHeKinCalculated - fHeKinMeasured", "fHeKinCalculated>0. && fHeKinCalculated-fHeKinMeasured>-5.", "");
	gPad->Update();

	c->cd(8);
	tr->Draw("fHeKinCalculatedMap - fHeKinMeasured", "fHeKinCalculatedMap>0.", "");
	gPad->Update();

}
