// raw Data
TGraph *gCal, *gExp;
TH1F *hCal, *hExp;

// smooth Data
TH1F *hCal_smooth, *hExp_smooth;
TGraph *gCal_smooth, *gExp_smooth;

//CFD graphs
TGraph *gCFD_Cal_s, *gCFD_Exp_s;
TGraph *gCFD_Cal, *gCFD_Exp;

Double_t getLed_up(TH1F *hist, Double_t thresh);
Double_t getLed_low(TH1F *hist, Double_t thresh);

TGraph* SetGraphs(TH1F* hist);
TGraph* SetCFDGraph_static(TGraph *g, Double_t amp, Int_t delay);
TGraph* SetCFDGraph(TGraph *g, Double_t amp, Double_t delay,Double_t* CFDtime);
TGraph* SetCFDGraph_back(TGraph *g, Double_t amp, Double_t delay,Double_t* CFDtime);


Double_t tCFD_cal,tCFD_exp;

TGraph* shiftGraph(TGraph *g1, TGraph *g2, Double_t shift);
TH1F* shiftHisto(TH1F *h1, TH1F *h2, Double_t shift);

Double_t getPeregib(TGraph *g, Double_t x, Double_t range);