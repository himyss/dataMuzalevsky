#include <fstream>
#include "TCanvas.h"

using namespace std;

void drawh5(){
		
	ERMCTrack *n1 = new ERMCTrack();
	ERMCTrack *n2 = new ERMCTrack();
	ERMCTrack *h3 = new ERMCTrack();
	ERMCTrack *h5 = new ERMCTrack();
	ERMCTrack *he3 = new ERMCTrack();
	ERMCTrack *he6 = new ERMCTrack();

	TFile *fr = new TFile("/store/ivan/EXP1803/Kinematics/kin3.root", "READ");
	TTree *tr = (TTree*)fr->Get("tree");

	tr->SetBranchAddress("n1.",&n1);
	tr->SetBranchAddress("n2.",&n2);
	tr->SetBranchAddress("h3.",&h3);
	tr->SetBranchAddress("h5.",&h5);
	tr->SetBranchAddress("he3.",&he3);
	tr->SetBranchAddress("he6.",&he6);

	TCut cHeLocus = "(he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass())<0.02";
	TCut cGS = "(1000*fh5it.Mag() - 2809.432 - 2*939.565)<2.6";

	TLorentzVector fn1,fn2,fh3,fh5,fhe3,fhe6,fh2,fn1CM,fn2CM,fh3CM,fh5CM,fhe3CM,fh5it;
	TLorentzVector temp,tempCM;
	TVector3 bVect;
	Double_t angle,angleCM;
	fh2.SetXYZT(0,0,0,1.87612); 
//c1
	// pad
	TH1F *h5EX = new TH1F("h5EX","h5 spectrum",500,0,180);
	TH1F *he6T = new TH1F("he6T","beam energy",500,0,400);
	TH1F *he6Theta = new TH1F("he6Theta","beam direction: theta",500,0,180);
	TH1F *he6Phi = new TH1F("he6Phi","beam direction: phi",500,0,180);

	TH2F *he3Theta2 = new TH2F("he3Theta2","he3 theta vs CM",500,0,180,500,0,40); //cd2 
	TH2F *h5Theta2 = new TH2F("h5Theta2","h5 theta vs CM",500,0,180,500,0,40);

	TH2F *he3t_thetCM = new TH2F("he3t_thetCM","he3 t vs thetaCM",500,0,180,500,0,100); // cd3
	TH2F *h5t_thetCM = new TH2F("h5t_thetCM","h5 t vs thetaCM",500,0,180,500,0,100);

	TH1F *he3ThetaCM = new TH1F("he3ThetaCM","he3 theta CM",70,0,180); // cd4

	TH2F *he3_h5_theta = new TH2F("he3_h5_theta","h5 t he3",500,0,24,500,0,40); //cd5

	TH2F *he3t_thet = new TH2F("he3t_thet","he3 t vs theta",500,0,40,500,0,100);
	TH2F *h5t_thet = new TH2F("h5t_thet","h5 t vs theta",500,0,40,500,0,150);


//c2
	TH2F *he3Theta2cut = new TH2F("he3Theta2cut","he3 theta vs CM cut",500,0,180,500,0,40); //cd2 
	TH2F *h5Theta2cut = new TH2F("h5Theta2cut","h5 theta vs CM cut",500,0,180,500,0,40);

//c3
	TH1F *he3ThetaCMcut = new TH1F("he3t_thetCMcut","he3 t vs thetaCM cut",70,0,180);
	TH1F *h3CMP = new TH1F("h3CMP","h3CMP",100,0,90);
	TH1F *h3CMPcut = new TH1F("h3CMPcut","h3CMPcut",100,0,90);
	TH1F *h3CMPcut1 = new TH1F("h3CMPcut1","h3CMPcut1",100,0,90);

	TH1F *n1CMP = new TH1F("n1CMP","n1CMP",100,0,90);
	TH1F *n1CMPcut = new TH1F("n1CMPcut","n1CMPcut",100,0,90);
	TH1F *n1CMPcut1 = new TH1F("n1CMPcut1","n1CMPcut1",100,0,90);

	TH1F *n2CMP = new TH1F("n2CMP","n2CMP",100,0,90);
	TH1F *n2CMPcut = new TH1F("n2CMPcut","n2CMPcut",100,0,90);
	TH1F *n2CMPcut1 = new TH1F("n2CMPcut1","n2CMPcut1",100,0,90);

	TH1F *hn1 = new TH1F("hn1","theta between n1 and n2",50,0.,50.);
	TH1F *hn1CM = new TH1F("hn1CM","thetaCM between n1 and n2",50,0.,180.);
	TH1F *hn1cut = new TH1F("hn1cut","theta between n1 and n2 cut",50,0.,50.);
	TH1F *hn1CMcut = new TH1F("hn1CMcut","thetaCM between n1 and n2 cut",50,0.,180.);

	for(Int_t i=0; i<tr->GetEntries();i++){
	//for(Int_t i=0; i<10;i++){
		tr->GetEntry(i);

		fn1 = n1->GetVector();
		fn2 = n2->GetVector();
		fh5 = h5->GetVector();
		fhe6 = he6->GetVector();
		temp = fh2;
		bVect = fh2.BoostVector();
		temp.Boost(-bVect);

		fn1CM = n1->GetVector();
		fn2CM = n2->GetVector();
		fh3CM = h3->GetVector();
		fh5CM = h5->GetVector();
		fhe3CM = he3->GetVector();
		fh5it = h5->GetVector();

		fn1CM.Boost(-fh5.BoostVector());
		fn2CM.Boost(-fh5.BoostVector());
		fh3CM.Boost(-fh5.BoostVector());
		fhe3CM.Boost(-(fh2 + fhe6).BoostVector());
		fh5CM.Boost(-(fh2 + fhe6).BoostVector());
		fh5it.Boost(-fh5.BoostVector());

		fn1CM.SetTheta(TMath::Pi() - fn1CM.Theta());
		fhe3CM.SetTheta(TMath::Pi() - fhe3CM.Theta());

		// fh5CM.SetTheta(TMath::Pi() - fh5CM.Theta());

		// h5EX->Fill(h5->GetMass() - n1->GetMass() - n2->GetMass() - h3->GetMass()); // h5 spectrum
		he6T->Fill(1000*(he6->GetEnergy() - he6->GetMass()));
		// he6Theta->Fill(fhe6.Theta()*TMath::RadToDeg());
		// he6Phi->Fill(fhe6.Phi()*TMath::RadToDeg());

		he3ThetaCM->Fill(fhe3CM.Theta()*TMath::RadToDeg());
		he3Theta2->Fill(fhe3CM.Theta()*TMath::RadToDeg(),he3->GetTheta()*TMath::RadToDeg());
		h5Theta2->Fill(fh5CM.Theta()*TMath::RadToDeg(),h5->GetTheta()*TMath::RadToDeg());

		he3t_thetCM->Fill(fhe3CM.Theta()*TMath::RadToDeg(),1000*(he3->GetEnergy() - he3->GetMass())/3.);
		h5t_thetCM->Fill(fh5CM.Theta()*TMath::RadToDeg(),1000*(h5->GetEnergy() - h5->GetMass())/5.);
		he3_h5_theta->Fill(h5->GetTheta()*TMath::RadToDeg(),he3->GetTheta()*TMath::RadToDeg());

		he3t_thet->Fill(he3->GetTheta()*TMath::RadToDeg(),1000*(he3->GetEnergy() - he3->GetMass())/3.);
		h5t_thet->Fill(fh5.Theta()*TMath::RadToDeg(),1000*(h5->GetEnergy() - h5->GetMass())/5.);

		if((he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass()) < 0.02) {
			he3Theta2cut->Fill(fhe3CM.Theta()*TMath::RadToDeg(),he3->GetTheta()*TMath::RadToDeg());
			h5Theta2cut->Fill(fh5CM.Theta()*TMath::RadToDeg(),h5->GetTheta()*TMath::RadToDeg());
		}
		if ((he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass()) < 0.02) {
			he3ThetaCMcut->Fill(fhe3CM.Theta()*TMath::RadToDeg());
		}

		h3CMP->Fill(1000*fh3CM.P());
		if((1000*fh5it.Mag() - 2809.432 - 2*939.565)<2.6) {
			h3CMPcut->Fill(1000*fh3CM.P());
		}
		if((he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass()) < 0.02) {
			h3CMPcut1->Fill(1000*fh3CM.P());
		}

		n1CMP->Fill(1000*fn1CM.P());
		if((1000*fh5it.Mag() - 2809.432 - 2*939.565)<2.6) {
			n1CMPcut->Fill(1000*fn1CM.P());
		}
		if((he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass()) < 0.02) {
			n1CMPcut1->Fill(1000*fn1CM.P());
		}


		n2CMP->Fill(1000*fn2CM.P());
		if((1000*fh5it.Mag() - 2809.432 - 2*939.565)<2.6) {
			n2CMPcut->Fill(1000*fn2CM.P());
		}
		if((he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass()) < 0.02) {
			n2CMPcut1->Fill(1000*fn2CM.P());
		}

		angle = fn1.Angle(fn2.Vect())*TMath::RadToDeg();  // get angle between v1 and v2
		angleCM = fn1CM.Angle(fn2CM.Vect())*TMath::RadToDeg();
		hn1->Fill(angle);
		hn1CM->Fill(angleCM);
		if((he3->GetTheta())*TMath::RadToDeg() < 32 && (he3->GetEnergy() - he3->GetMass()) < 0.02) {
			hn1cut->Fill(angle);
			hn1CMcut->Fill(angleCM);
		}

	}
	

	// draw		
	const Int_t ww = 1400;
	const Int_t wh = 1000;

	TH1F *htemp;

	TCanvas *cInt = new TCanvas("cInt", "Standard LISE++ output", ww, wh);
	cInt->Divide(3,2);

	cInt->cd(1);

	TPad *padInput = (TPad*)gPad;

	padInput->Divide(2,2);
	padInput->cd(1);
	tr->Draw("1000*(h5->GetMass() - h3->GetMass() - n1->GetMass() - n2->GetMass())");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{T} (MeV)");
	htemp->SetTitle("5H spectrum");

	padInput->cd(2);
	tr->SetLineColor(kBlack);
	// tr->Draw("(he6.fEnergy - he6.fMass)/6.", "");
	he6T->Draw();
	// htemp = (TH1F*)gPad->GetPrimitive("htemp");
	he6T->GetXaxis()->SetTitle("E_{beam} (MeV)");
	he6T->SetTitle("beam energy");

	padInput->cd(3);
	tr->Draw("he6->GetTheta()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{beam} (rad)");
	htemp->SetTitle("beam direction");

	padInput->cd(4);
	tr->Draw("he6->GetPhi()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Phi_{beam} (rad)");
	htemp->SetTitle("beam direction");

	cInt->cd(2);
	he3Theta2->SetMarkerColor(kBlue);
	he3Theta2->Draw();
	h5Theta2->SetMarkerColor(kRed);
	h5Theta2->Draw("same");
	he3Theta2->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3Theta2->GetYaxis()->SetTitle("\\Theta_{lab} (deg)");
	he3Theta2->SetTitle("binary reaction: no cut");	

	cInt->cd(3);
	he3t_thetCM->SetMarkerColor(4);
	he3t_thetCM->Draw();
	h5t_thetCM->SetMarkerColor(2);
	h5t_thetCM->Draw("same");
	he3t_thetCM->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3t_thetCM->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	he3t_thetCM->SetTitle("binary reaction: no cut");

	cInt->cd(4);
	he3ThetaCM->SetLineColor(1);
	he3ThetaCM->Draw();
	he3ThetaCM->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3ThetaCM->SetTitle("input reaction angle");

	cInt->cd(5);
	tr->SetMarkerColor(kBlack);
	tr->Draw("he3->GetTheta()*TMath::RadToDeg():h5->GetTheta()*TMath::RadToDeg()", "");
	// he3_h5_theta->SetMarkerColor(kRed);
	// he3_h5_theta->Draw("same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab}(5H) (deg)");
	htemp->GetYaxis()->SetTitle("\\Theta_{lab}(3He) (deg)");
	htemp->SetTitle("binary reaction: no cut");

// 	cInt->cd(5);
// //	tr->Draw("kin.GetHM() - 4690.362", "");
// 	tr->SetMarkerColor(kBlack);
// 	tr->Draw("he3->GetTheta()*TMath::RadToDeg():h5->GetTheta()*TMath::RadToDeg()", "");
// 	htemp = (TH1F*)gPad->GetPrimitive("htemp");
// 	htemp->GetXaxis()->SetTitle("\\Theta_{lab}(5H) (deg)");
// 	htemp->GetYaxis()->SetTitle("\\Theta_{lab}(3He) (deg)");
// 	htemp->SetTitle("binary reaction: no cut");

	cInt->cd(6);
	tr->SetMarkerColor(kBlue);
	tr->Draw("1000*(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("1000*(h5->GetEnergy() - h5->GetMass())/5:h5->GetTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("binary reaction: no cut");

	TCanvas *c1 = new TCanvas("c1", "Standard LISE++ output", ww, wh);
	c1->Divide(3,2);

	c1->cd(1);
	he3Theta2->SetMarkerColor(kBlue);
	he3Theta2->Draw();
	h5Theta2->SetMarkerColor(kRed);
	h5Theta2->Draw("same");
	he3Theta2->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3Theta2->GetYaxis()->SetTitle("\\Theta_{lab} (deg)");
	he3Theta2->SetTitle("binary reaction: no cut");

	he3Theta2cut->SetMarkerColor(kGreen);
	he3Theta2cut->Draw("same");
	h5Theta2cut->SetMarkerColor(kGreen);
	h5Theta2cut->Draw("same");

	c1->cd(2);
	tr->SetMarkerColor(kBlue);
	tr->Draw("1000*(n1->GetEnergy() - n1->GetMass()):n1->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("1000*(n2->GetEnergy() - n2->GetMass()):n2->GetTheta()*TMath::RadToDeg()", "", "same");
//	tr->Draw("kin.GetTritonT()/3.:kin.GetTritonTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("neutrons");

	c1->cd(3);
	tr->SetMarkerColor(kBlack);
	tr->Draw("1000*(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", "", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("triton");

	c1->cd(4);
	tr->SetMarkerColor(kBlue);
	tr->Draw("1000*(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("1000*(h5->GetEnergy() - h5->GetMass())/5.:h5->GetTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("binary reaction: cut");

	tr->SetMarkerColor(kGreen);
	tr->Draw("1000*(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", cHeLocus,"same");
	tr->Draw("1000*(h5->GetEnergy() - h5->GetMass())/5.:h5->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");

	c1->cd(5);
	tr->SetMarkerColor(kBlack);
	tr->Draw("1000*(n1->GetEnergy() - n1->GetMass()):n1->GetTheta()*TMath::RadToDeg()", "", "");
	tr->Draw("1000*(n2->GetEnergy() - n2->GetMass()):n2->GetTheta()*TMath::RadToDeg()", "", "same");
	tr->SetMarkerColor(kGreen);
	tr->Draw("1000*(n1->GetEnergy() - n1->GetMass()):n1->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("1000*(n2->GetEnergy() - n2->GetMass()):n2->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("neutrons: green cut");

	c1->cd(6);
	tr->SetMarkerColor(kBlack);
	tr->Draw("1000*(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kGreen);
	tr->Draw("1000*(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("triton: green cut");

	TCanvas *c2 =  new TCanvas("c2", "CMS of 5H", ww, wh);
	c2->Divide(4,2);

	c2->cd(1);
	TPad *padInputChoice = (TPad*)gPad;
	padInputChoice->Divide(1,2);

	padInputChoice->cd(1);
//	tr->Draw("kin.GetHeTheta()*TMath::RadToDeg():kin.GetHTheta()*TMath::RadToDeg()", "");
//	tr->Draw("kin.GetHCMS().Mag() - 4690.36244");
	tr->Draw("1000*(h5->GetMass() - h3->GetMass() - n1->GetMass() - n2->GetMass())");
	tr->SetLineColor(kRed);
	//tr->Draw("1000*(h5->GetMass() - h3->GetMass() - n1->GetMass() - n2->GetMass())", cGS, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{T} (MeV)");
	htemp->SetTitle("5H energy spectrum");

	padInputChoice->cd(2);
	he3ThetaCM->Draw();
	he3ThetaCMcut->SetLineColor(kGreen);
	he3ThetaCMcut->Draw("same");
	he3ThetaCM->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3ThetaCM->SetTitle("input reaction angle: green cut");

	c2->cd(2);

	h3CMP->SetLineColor(kBlack);
	h3CMP->Draw();
	h3CMPcut->SetLineColor(kRed);
	h3CMPcut->Draw("same");
	h3CMP->GetXaxis()->SetTitle("p_{5H CM}(^{3}H) (MeV/c)");
	h3CMP->SetTitle("CMS of 5H: no cut");
//	htemp->SetName("beam direction");


	c2->cd(3);

	n1CMP->SetLineColor(kBlack);
	n1CMP->Draw();
	n1CMPcut->SetLineColor(kRed);
	n1CMPcut->Draw("same");
	n1CMP->GetXaxis()->SetTitle("p_{5H CM}(^{1}n) (MeV/c)");
	n1CMP->SetTitle("CMS of 5H: no cut");

	c2->cd(4);
	n2CMP->SetLineColor(kBlack);
	n2CMP->Draw();
	n2CMPcut->SetLineColor(kRed);
	n2CMPcut->Draw("same");
	n2CMP->GetXaxis()->SetTitle("p_{5H CM}(^{2}n) (MeV/c)");
	n2CMP->SetTitle("CMS of 5H: no cut");



	c2->cd(5);
	tr->SetMarkerColor(kBlue);
	tr->Draw("(he3->GetVector()).P()/3.:he3->GetTheta()*TMath::RadToDeg()", "");
//	tr->Draw("kin.GetHeT()/3.:kin.GetHeTheta()*TMath::RadToDeg()", "");
	tr->SetMarkerColor(kRed);
//	tr->Draw("kin.GetHT()/5.:kin.GetHTheta()*TMath::RadToDeg()", "", "same");
	tr->Draw("(h5->GetVector()).P()/5.:h5->GetTheta()*TMath::RadToDeg()", "", "same");


/*	tr->SetMarkerColor(kGreen);
	tr->Draw("3_He.fImpulse.P()/3.:3_He->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("5_H.fImpulse.P()/5.:5_H->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("|p|_{lab} (MeV.A^{-1}.c^{-1})");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("kinematics: green cut");*/

	c2->cd(6);
	h3CMPcut1->SetLineColor(kGreen);
	h3CMPcut1->Draw();
	h3CMPcut1->GetXaxis()->SetTitle("p_{5H CM}(^{3}H) (MeV/c)");
	h3CMPcut1->SetTitle("CMS of 5H: green cut");

	c2->cd(7);
	n1CMPcut1->SetLineColor(kGreen);
	n1CMPcut1->Draw();
	n1CMPcut1->GetXaxis()->SetTitle("p_{5H CM}(n_{1}) (MeV/c)");
	n1CMPcut1->SetTitle("CMS of 5H: green cut");



	c2->cd(8);
	n2CMPcut1->SetLineColor(kGreen);
	n2CMPcut1->Draw();
	n2CMPcut1->GetXaxis()->SetTitle("p_{5H CM}(n_{1}) (MeV/c)");
	n2CMPcut1->SetTitle("CMS of 5H: green cut");

	c2->cd(4);
	hn1->Draw();
	hn1cut->SetLineColor(8);
	hn1cut->Draw("same");
	c2->cd(8);
	hn1CM->Draw();
	hn1CMcut->SetLineColor(8);
	hn1CMcut->Draw("same");


	cInt->Print("output.pdf");
	cInt->Print("output.pdf[");
	cInt->Print("output.pdf");
	c1->Print("output.pdf");
	c2->Print("output.pdf");
	c2->Print("output.pdf]");


}
