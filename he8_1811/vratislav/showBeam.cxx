#if !defined(__CLING__)


//#include "../install/include/conversion/ConvertRepackedToCalibrated.h"
//#include "../install/include/data/DetEventCommon.h"
#include "TFile.h"
//#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH2F.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"


#include <iostream>

using std::cout;
using std::endl;

#endif

void showBeam() {

	const Bool_t drawC1 = 1;
	const Bool_t drawC2 = 1;
	const Bool_t drawC3 = 1;

	TString inFile = "he8_10_0001.reco.root";
	TString inPath = "~/data/exp1811/analysed/reco/";

	TFile *fr = new TFile(inPath + inFile);
	TTree *tr = (TTree*)fr->Get("reco");

	TFile *frIn = new TFile("~/data/exp1811/analysed/he8_10_0001.Digi.root");
	TTree *trIn = (TTree*)frIn->Get("er");
	tr->AddFriend(trIn);

//	tr->StartViewer();
//	trIn->StartViewer();
	TString hTitle;

////////////////////////////////////////////////
//	c1
////////////////////////////////////////////////

	if (drawC1) {
		TCanvas *c1 = new TCanvas("c1", "diagnostics", 1000, 1000);
		c1->Divide(2,2);

		c1->cd(1);
		tr->Draw("trigger", "");
		c1->Update();

		c1->cd(2);
		//	tr->Draw("BeamDetMWPCDigiY1.fWireNb:BeamDetMWPCDigiX1.fWireNb", "Length$(BeamDetMWPCDigiX1)>0 && Length$(BeamDetMWPCDigiY1)>0", "col");
		tr->Draw("BeamDetMWPCDigiY1.fWireNb:BeamDetMWPCDigiX1.fWireNb", "BeamDetMWPCDigiY1.fWireNb", "col");
		c1->Update();

		c1->cd(3);
		//	tr->Draw("Length$(BeamDetMWPCDigiX1)", "Length$(BeamDetMWPCDigiX1)>0");

		c1->cd(4);
		//	tr->Draw("Length$(BeamDetMWPCDigiY1)", "Length$(BeamDetMWPCDigiY1)>0");
	}

////////////////////////////////////////////////
//	c2
////////////////////////////////////////////////

	if (drawC2) {
		TCanvas *c2 = new TCanvas("c2", "MWPC projections", 1500, 1000);
		c2->Divide(3,2);

		c2->cd(1);
		tr->Draw("trigger", "");
		tr->Draw("BeamDetMWPCDigiY1.fWireNb:BeamDetMWPCDigiX1.fWireNb", "trigger==2 && BeamDetMWPCDigiY1.fWireNb>0", "col");
		c2->Update();

		c2->cd(4);
		//	tr->Draw("BeamDetMWPCDigiY1.fWireNb:BeamDetMWPCDigiX1.fWireNb", "Length$(BeamDetMWPCDigiX1)>0 && Length$(BeamDetMWPCDigiY1)>0", "col");
		tr->Draw("BeamDetMWPCDigiY1.fWireNb:BeamDetMWPCDigiX1.fWireNb", "trigger==3 && BeamDetMWPCDigiY1.fWireNb>0", "col");
		c2->Update();
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("MWPC1: trigger==3");


		c2->cd(2);
		tr->Draw("BeamDetMWPCDigiY2.fWireNb:BeamDetMWPCDigiX2.fWireNb", "trigger==2 && BeamDetMWPCDigiY2.fWireNb>0", "col");
		c2->Update();

		c2->cd(5);
		tr->Draw("BeamDetMWPCDigiY2.fWireNb:BeamDetMWPCDigiX2.fWireNb", "trigger==3 && BeamDetMWPCDigiY2.fWireNb>0", "col");
		c2->Update();
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("MWPC2: trigger==3");

		c2->cd(3);
		tr->Draw("fYt:fXt", "trigger==2 && fYt>-40. && fXt>-40.");
		tr->SetMarkerColor(kRed);
		tr->Draw("fYt:fXt", "trigger==2 && ( (fYt)^2 + (fXt)^2 ) < 8.^2", "same");
		c2->Update();

		c2->cd(6);
		tr->SetMarkerColor(kBlack);
		tr->Draw("fYt:fXt", "trigger==3 && fYt>-40. && fXt>-40.");
		tr->Draw("fYt:fXt", "trigger==3 && fYt>-40. && fXt>-40.", "col");
		tr->SetMarkerColor(kRed);
//		tr->Draw("fYt:fXt", "trigger==3 && ( (fYt-2)^2 + (fXt+3)^2 ) < 9.^2", "same");
		c2->Update();
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("Profile at TP: trigger==3");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("Xt (mm)");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("Yt (mm)");

	}

////////////////////////////////////////////////
//	c3
////////////////////////////////////////////////

	if (drawC3) {
		TCanvas *c3 = new TCanvas("c3", "beam ID", 1000, 1000);
		c3->Divide(2,2);

		c3->cd(1);
		tr->Draw("BeamDetToFDigi2.fEdep:BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime",
				"BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >100."
				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 300."
				" && BeamDetToFDigi2.fEdep<8000."
				" && fTrigger==3","col");
//		hTitle.Form("dE-tau: CsI==%d", i+firstStrip);
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("dE-Tau");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("tF5 - tF3 (ns)");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("E_F5 (ch)");


		c3->cd(3);
		cout << tr->Draw("BeamDetToFDigi2.fEdep:BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime",
				"BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >100."
				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 300."
				" && BeamDetToFDigi2.fEdep<8000."
				" && fTrigger==2","col") << endl;
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("dE-Tau: trigger==2");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("tF5 - tF3 (ns)");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("E_F5 (ch)");

		tr->SetMarkerColor(kRed);

		cout << tr->Draw("BeamDetToFDigi2.fEdep:BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime",
				"BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >200."
				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 240."
				" && BeamDetToFDigi2.fEdep>2600."
				" && BeamDetToFDigi2.fEdep<4300."
				" && fTrigger==2",
				"same") << endl;

		c3->cd(4);
		cout << tr->Draw("BeamDetToFDigi2.fEdep:BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime",
				"BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >100."
				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 300."
				" && BeamDetToFDigi2.fEdep<8000."
				" && fTrigger==3","col") << endl;
		((TH2F*)gPad->GetPrimitive("htemp"))->SetTitle("dE-Tau: trigger==3");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetXTitle("tF5 - tF3 (ns)");
		((TH2F*)gPad->GetPrimitive("htemp"))->SetYTitle("E_F5 (ch)");

		tr->SetMarkerColor(kRed);

		cout << tr->Draw("BeamDetToFDigi2.fEdep:BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime",
				"BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime >200."
				" && BeamDetToFDigi2.fTime - BeamDetToFDigi1.fTime < 240."
				" && BeamDetToFDigi2.fEdep>2600."
				" && BeamDetToFDigi2.fEdep<4300."
				" && fTrigger==3",
				"same") << endl;
	}
}

