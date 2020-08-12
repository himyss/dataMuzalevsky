#include "processData.h"

void processData() {

	Double_t amplification = 0.5;

	TChain *chCal = new TChain("tree");
	chCal->Add("/mnt/data/exp2001/data/analysed/reco/crun09_0001.lmd.reco.root");

	TChain *ch = new TChain("tree");
	ch->Add("/mnt/data/exp2001/data/analysed/reco/run*.root");


	TCanvas *c_raw = new TCanvas("c_raw","raw Data",1800,1000);
	c_raw->Divide(2,3);

	c_raw->cd(1);
	// chCal->Draw("tF5-tF3+68.475 >> h1(71,160,170)","","");
	chCal->Draw("tF5-tF3+68.475 >> h1(500,160,170)","","");
	c_raw->Update();

	hCal = (TH1F*)gPad->GetPrimitive("h1");

	c_raw->cd(2);
	// ch->Draw("tF5-tF3+68.475 >> h2(71,160,170)","","");
	ch->Draw("tF5-tF3+68.475 >> h2(200,160,170)","","");
	// gPad->SetLogy(1);
	c_raw->Update();

	hExp = (TH1F*)gPad->GetPrimitive("h2");	

	c_raw->cd(3);
	gCal = SetGraphs(hCal);
	gCal->Draw("AL*");
	c_raw->Update();

	c_raw->cd(4);
	gExp = SetGraphs(hExp);
	gExp->Draw("AL*");
	c_raw->Update();

	// c_raw->cd(5);
	// gCFD_Cal = SetCFDGraph(gCal, amplification, 1.5,&tCFD_cal);
	// gCFD_Cal->Draw("AL*");
	// cout << tCFD_cal << " "  << gCFD_Cal->GetN() << endl;

	// c_raw->Update();

	// c_raw->cd(6);
	// gCFD_Exp = SetCFDGraph(gExp, amplification, 1.5,&tCFD_exp);
	// gCFD_Exp->Draw("AL*");
	// c_raw->Update();

	// cout << tCFD_exp << " " << gCFD_Exp->GetN() << endl;


	// smooth
	TCanvas *c_smooth = new TCanvas("c_smooth","smooth Data",1800,1000);
	c_smooth->Divide(3,4);

	c_smooth->cd(1);
	hCal_smooth = (TH1F*)hCal->Clone();
	hCal_smooth->Smooth(2);
	hCal_smooth->Draw();
	c_smooth->Update();

	c_smooth->cd(2);
	hExp_smooth = (TH1F*)hExp->Clone();
	hExp_smooth->Smooth(2);
	hExp_smooth->Draw();
	c_smooth->Update();

	c_smooth->cd(3);
	hExp_smooth->Draw();

	TH1F *hCal_smooth_shift = shiftHisto(hCal_smooth,hExp_smooth, 0);
	hCal_smooth_shift->SetLineColor(kRed);
	hCal_smooth_shift->Draw("same");
	c_smooth->Update();

	// graphs
	c_smooth->cd(4);
	gCal_smooth = SetGraphs(hCal_smooth);
	gCal_smooth->Draw("AL*");
	c_smooth->Update();

	c_smooth->cd(5);
	gExp_smooth = SetGraphs(hExp_smooth);
	gExp_smooth->Draw("AL*");
	c_smooth->Update();


	// CFD
	c_smooth->cd(7);
	Double_t timeCal;
	TGraph *gCal_smooth_CFD = SetCFDGraph(gCal_smooth, amplification, 1.5 ,&timeCal);
	cout << "CFDtime on lvl " << amplification << " for Calibration data: " << timeCal << endl;
	gCal_smooth_CFD->Draw("AL*");

	TMarker *mCal_cfd = new TMarker(timeCal, gCal_smooth_CFD->Eval(timeCal), 20);
	mCal_cfd->SetMarkerColor(kRed);
	mCal_cfd->Draw("same");

	TLine *l_zero = new TLine(*(gCal_smooth_CFD->GetX()), 0, *(gCal_smooth_CFD->GetX()+gCal_smooth_CFD->GetN()-1),0);
	l_zero->SetLineColor(kRed);
	l_zero->Draw("same");

	c_smooth->Update();

	c_smooth->cd(8);
	Double_t timeExp;
	TGraph *gExp_smooth_CFD = SetCFDGraph(gExp_smooth, amplification, 1.5 ,&timeExp);
	cout << "CFDtime on lvl " << amplification << " for Experimental data: " << timeExp << endl;
	gExp_smooth_CFD->Draw("AL*");

	TMarker *mExp_cfd = new TMarker(timeExp, gExp_smooth_CFD->Eval(timeExp), 20);
	mExp_cfd->SetMarkerColor(kRed);
	mExp_cfd->Draw("same");

	l_zero->Draw("same");

	c_smooth->Update();


	// CFD
	c_smooth->cd(10);
	Double_t timeCal_low;
	TGraph *gCal_back_CFD = SetCFDGraph_back(gCal_smooth, amplification, 0.5 ,&timeCal_low);
	cout << "Low Energy CFDtime on lvl " << amplification << " for Calibration data: " << timeCal_low << endl;
	gCal_back_CFD->Draw("AL*");

	TMarker *mCal_cfd_back = new TMarker(timeCal_low, gCal_back_CFD->Eval(timeCal_low), 20);
	mCal_cfd_back->SetMarkerColor(kRed);
	mCal_cfd_back->Draw("same");

	l_zero->Draw("same");

	c_smooth->Update();

	c_smooth->cd(11);
	Double_t timeExp_low;
	TGraph *gExp_back_CFD = SetCFDGraph_back(gExp_smooth, amplification, 0.5 ,&timeExp_low);
	cout << "Low Energy CFDtime on lvl " << amplification << " for Experimental data: " << timeExp_low << endl;
	gExp_back_CFD->Draw("AL*");

	TMarker *mExp_cfd_back = new TMarker(timeExp_low, gExp_back_CFD->Eval(timeExp_low), 20);
	mExp_cfd_back->SetMarkerColor(kRed);
	mExp_cfd_back->Draw("same");

	l_zero->Draw("same");

	c_smooth->Update();


	// draw TimeStamps
	c_smooth->cd(4);

	TMarker *mCal = new TMarker(timeCal, gCal_smooth->Eval(timeCal), 20);
	mCal->SetMarkerColor(kRed);
	mCal->Draw("same");

	TMarker *mCal_back = new TMarker(timeCal_low, gCal_smooth->Eval(timeCal_low), 20);
	mCal_back->SetMarkerColor(kGreen);
	mCal_back->Draw("same");

	TLine *lCal = new TLine(*(gCal_smooth->GetX()), hCal_smooth->GetMaximum()/2, *(gCal_smooth->GetX()+gCal_smooth->GetN()-1), hCal_smooth->GetMaximum()/2);
	lCal->SetLineColor(kRed);
	lCal->Draw("same");

	c_smooth->Update();

	c_smooth->cd(5);

	TMarker *mExp = new TMarker(timeExp, gExp_smooth->Eval(timeExp), 20);
	mExp->SetMarkerColor(kRed);
	mExp->Draw("same");

	TMarker *mExp_back = new TMarker(timeExp_low, gExp_smooth->Eval(timeExp_low), 20);
	mExp_back->SetMarkerColor(kGreen);
	mExp_back->Draw("same");

	TLine *lExp = new TLine(*(gExp_smooth->GetX()), hExp_smooth->GetMaximum()/2, *(gExp_smooth->GetX()+gExp_smooth->GetN()-1), hExp_smooth->GetMaximum()/2);
	lExp->SetLineColor(kRed);
	lExp->Draw("same");

	c_smooth->Update();

	cout << " Bin width: " << hExp_smooth->GetBinWidth(1) << endl;

	// c_smooth->Update();

	// TCanvas *c2 = new TCanvas("c2","title",1000,1000);
	// c2->cd();
	// // c2->Divide(2,1);

	// // c2->cd(1);
	// TGraph *tempGraph = shiftGraph(gExp,gCal,0.4);
	// tempGraph->SetLineColor(kRed);
	// tempGraph->Draw();
	// gCal->Draw("same");
	// c2->Update();

return;

	cout << "Calibration data. Bin width: " << hCal->GetBinWidth(1) << endl;
	cout << getLed_low(hCal,10) << " ";
	cout << getLed_low(hCal,100) << " ";
	cout << getLed_low(hCal,300) << " ";
	cout << getLed_low(hCal,500) << endl << endl;
	// cout << getLed_up(hCal,100) << endl;

	cout << "EXP data. Bin width: " << hExp->GetBinWidth(1) << endl;
	cout << getLed_low(hExp,10) << " ";
	cout << getLed_low(hExp,100) << " ";
	cout << getLed_low(hExp,300) << " ";
	cout << getLed_low(hExp,500) << endl;

}

Double_t getLed_low(TH1F *hist, Double_t thresh) {

	for (Int_t i=1;i<hist->GetNbinsX()+1;i++){
		if (hist->GetBinContent(i)>thresh) {
			return hist->GetBinCenter(i);
		}
	}

	return -1;
}

Double_t getLed_up(TH1F *hist, Double_t thresh) {

	for (Int_t i=hist->GetNbinsX();i>0;i--){
		if (hist->GetBinContent(i)>thresh) {
			return hist->GetBinCenter(i);
		}
	}

	return -1;
}

TGraph* SetGraphs(TH1F* hist) {

	TGraph *g = new TGraph();

	for (Int_t i=0; i<hist->GetNbinsX(); i++) {
		g->SetPoint(i, hist->GetBinCenter(i+1), hist->GetBinContent(i+1));
	}

	return g;
}


TGraph* SetCFDGraph_static(TGraph *g, Double_t amp, Int_t delay) {

	Double_t stepX = *(g->GetX()+1) - *(g->GetX());

	TGraph *gCFD = new TGraph();
	gCFD->Set(g->GetN() + delay);

	for (Int_t i=0;i<gCFD->GetN();i++) {
		static Double_t yVal;
		static Double_t xVal;

		if (i<delay) {
			yVal = *(g->GetY()+i)*amp*(-1);
			xVal = *(g->GetX()+i)-delay*stepX;
		}

		if (i>=delay && i<g->GetN()) {
			yVal = *(g->GetY()+i)*amp*(-1) + *(g->GetY()+i-delay);
			xVal = *(g->GetX()+i-delay);
		}

		if (i>=g->GetN()) {
			yVal = *(g->GetY()+i-delay-1);
			xVal = *(g->GetX()+i-delay-1);
		}

		gCFD->SetPoint(i, xVal, yVal);

	}

	return gCFD;
}

TGraph* shiftGraph(TGraph *g1, TGraph *g2, Double_t shift) {

	Double_t max1,max2;

	max1 = *(g1->GetY());
	for (Int_t i=0;i<g1->GetN();i++) {
		if (max1<*(g1->GetY()+i)) max1 = *(g1->GetY()+i);
	}

	max2 = *(g2->GetY());
	for (Int_t i=0;i<g2->GetN();i++) {
		if (max2<*(g2->GetY()+i)) max2 = *(g2->GetY()+i);
	}

	Double_t amp = max2/max1;

	TGraph *gTemp = new TGraph();
	gTemp->Set(g1->GetN());

	for (Int_t i=0;i<gTemp->GetN();i++) {
		gTemp->SetPoint(i,*(g1->GetX()+i)+shift, *(g1->GetY()+i)*amp );
	}

	return gTemp;

}

TH1F* shiftHisto(TH1F *h1, TH1F *h2, Double_t shift) {

	Int_t binShift = shift/h1->GetBinWidth(1);
	Double_t amp = h2->GetMaximum()/h1->GetMaximum();

	TH1F *htemp = (TH1F*)h1->Clone();

	for(Int_t i=1;i<htemp->GetNbinsX()+1;i++) {

		if(i+binShift<=htemp->GetNbinsX()) htemp->SetBinContent(i,h1->GetBinContent(i-binShift)*amp);
		else {
			htemp->SetBinContent(i,0);
		}

	}

	return htemp;

}


TGraph* SetCFDGraph_back(TGraph *g, Double_t amp, Double_t delay,Double_t* CFDtime) {

	const Double_t timeStep = 0.05;
	Double_t mytime = *(g->GetX());

	Double_t timeMin  = mytime;
	Double_t timeMax  = mytime;
	Double_t valMin  = *(g->GetY());
	Double_t valMax  = *(g->GetY());

	Int_t nBins = ( *(g->GetX()+g->GetN()-1) - *(g->GetX()) + delay)/timeStep;

	TGraph *gCFD = new TGraph();
	gCFD->Set(nBins);

	for (Int_t i=0;i<gCFD->GetN();i++) {
		static Double_t yVal;

		if ( mytime<delay+*(g->GetX()) ) {
			yVal = g->Eval(mytime);
		}

		// if ( mytime>=*(g->GetX()) && mytime< *(g->GetX()+g->GetN()-1)+delay ) {
		if ( mytime>=delay+*(g->GetX()) && mytime< *(g->GetX()+g->GetN()-1) ) {
			yVal = g->Eval(mytime-delay)*amp*(-1) + g->Eval(mytime);
		}

		if ( mytime>= *(g->GetX()+g->GetN()-1) ) {
			yVal = g->Eval(mytime-delay)*amp*(-1);
		}

		if (yVal>valMax) {
			valMax = yVal;
			timeMax = mytime;
		}

		if (yVal<valMin) {
			valMin = yVal;
			timeMin = mytime;
		}

		gCFD->SetPoint(i, mytime, yVal);

		mytime += timeStep;
	}

	mytime = timeMin;
	while( (gCFD->Eval(mytime) <= 0) && (mytime >= timeMax) /*&& (time >= TminCFD)*/ ) {
		*CFDtime = mytime;
		mytime -= timeStep;
	}

	return gCFD;
}

TGraph* SetCFDGraph(TGraph *g, Double_t amp, Double_t delay,Double_t* CFDtime) {

	const Double_t timeStep = 0.05;
	Double_t mytime = *(g->GetX()) - delay;

	Double_t timeMin  = mytime;
	Double_t timeMax  = mytime;
	Double_t valMin  = *(g->GetY());
	Double_t valMax  = *(g->GetY());

	Int_t nBins = ( *(g->GetX()+g->GetN()-1) - *(g->GetX()) + delay)/timeStep;

	TGraph *gCFD = new TGraph();
	gCFD->Set(nBins);

	for (Int_t i=0;i<gCFD->GetN();i++) {
		static Double_t yVal;

		if ( mytime<*(g->GetX()) ) {
			yVal = g->Eval(mytime+delay)*amp*(-1);
		}

		if ( mytime>=*(g->GetX()) && mytime< *(g->GetX()+g->GetN()-1)-delay ) {
			yVal = g->Eval(mytime+delay)*amp*(-1) + g->Eval(mytime);
		}

		if ( mytime>= *(g->GetX()+g->GetN()-1)-delay ) {
			yVal = g->Eval(mytime);
		}

		if (yVal>valMax) {
			valMax = yVal;
			timeMax = mytime;
		}

		if (yVal<valMin) {
			valMin = yVal;
			timeMin = mytime;
		}

		gCFD->SetPoint(i, mytime, yVal);

		mytime += timeStep;
	}

	mytime = timeMin;
	while( (gCFD->Eval(mytime) <= 0) && (mytime <= timeMax) /*&& (time >= TminCFD)*/ ) {
		*CFDtime = mytime;
		mytime += timeStep;
	}

	return gCFD;
}

Double_t  getPeregib(TGraph *g, Double_t x, Double_t range) {


	Double_t max = 0;

	Double_t xHalf = *(g->GetX()+g->GetN()-1);


	return 0;

}