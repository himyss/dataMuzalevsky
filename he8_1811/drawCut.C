void drawCut(){
  
  Bool_t tritium = kFALSE;
  Bool_t tCsI = kTRUE;
  Bool_t target = kFALSE;
  Bool_t centtimes = kFALSE;
  Bool_t sq20times = kFALSE;
  Bool_t X_Lcuts = kFALSE;
  Bool_t Y_Lcuts = kFALSE;

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");


  TCutG *cutCsI[16],*cut3h[16],*cutX_L[16],*cutY_L[16];
  TString cutName;
  TFile *f1;

  for(Int_t i=0;i<16;i++) {
    // cutName.Form("/media/user/work/macro/exp201810/draw/cuts/CsI_%d.root",i);
    cutName.Form("/media/user/work/macro/he8_1811/tritonCuts/CsI_%d.root",i);
    f1 = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/cutX_L/X_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutX_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutX_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/cutY_L/Y_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutY_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutY_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }



  TString cut,hdraw;

  if (tritium) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c1->cd(i+1);
      cut.Form("nCsI==%d && flagCent==1",i);
      // tree->Draw("DSDX_C:aCsI","nCsI==0","", 1004737, 0);
      hdraw.Form("X_C.:aCsI>>h%d(300,0,5000,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col", 1004737, 0);
      cut3h[i]->SetLineColor(kRed);
      cut3h[i]->Draw("same");
      c1->Update();
    }

    TCanvas *c2 = new TCanvas("c2","",1800,1000);  
    c2->cd();
    ch->Draw("X_C.:aCsI>>h(300,0,5000,300,0,100)","nCsI==2","col", 1004737, 0);
    cut3h[2]->Draw("same");
    c2->Update();
  }

  if (tCsI) {
    TCanvas *c3 = new TCanvas("c3","",1800,1000);  
    c3->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c3->cd(i+1);
      cut.Form("nCsI==%d && flagCent==1",i);
      // tree->Draw("DSDX_C:aCsI","nCsI==0","", 1004737, 0);
      hdraw.Form("aCsI:tCsI-tF5");
      ch->Draw(hdraw.Data(),cut.Data(),"", 1004737, 0);
      ch->SetMarkerColor(kRed);
      cut.Form("nCsI==%d && flagCent==1",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same", 1004737, 0);
      ch->SetMarkerColor(kBlack);
      c3->Update();
    }
  }

  if (target) {
    TCanvas *c4 = new TCanvas("c4","target cut",1800,1000);
    ch->SetMarkerColor(kBlack);  
    ch->Draw("fYt:fXt","","", 1004737, 0);
    ch->SetMarkerColor(kRed);
    ch->Draw("fYt:fXt","nTarget==1","same", 1004737, 0);
    ch->SetMarkerColor(kBlack);
  } 

  if (centtimes) {
    TCanvas *c5 = new TCanvas("c5","",1800,1000);
    c5->Divide(1,2);

    c5->cd(1);
    ch->SetMarkerColor(kBlack);  
    ch->Draw("X_C:tX_C - tF5","","", 1004737, 0);
    ch->SetMarkerColor(kRed);
    ch->Draw("X_C:tX_C - tF5","timesDSDX_C==1","same", 1004737, 0);
    ch->SetMarkerColor(kBlack);

    c5->cd(2);
    ch->SetMarkerColor(kBlack);  
    ch->Draw("Y_C:tY_C - tF5","","", 1004737, 0);
    ch->SetMarkerColor(kRed);
    ch->Draw("Y_C:tY_C - tF5","timesDSDY_C==1","same", 1004737, 0);
    ch->SetMarkerColor(kBlack);
  }

  if (sq20times) {
    TCanvas *c6 = new TCanvas("c6","sq20_L times",1800,1000);
    c6->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c6->cd(i+1);
      cut.Form("n20_L==%d",i);
      // tree->Draw("DSDX_C:aCsI","nCsI==0","", 1004737, 0);
      hdraw.Form("a20_L:t20_L-tF5");
      ch->Draw(hdraw.Data(),cut.Data(),"", 1004737, 0);
      ch->SetMarkerColor(kRed);
      cut.Form("n20_L==%d && SQ20_L_flag==1",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same", 1004737, 0);
      ch->SetMarkerColor(kBlack);
      c6->Update();
    }

  }

  if (X_Lcuts) {
    TCanvas *c7 = new TCanvas("c7","",1800,1000);  
    c7->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c7->cd(i+1);
      // tX_L-tF5, X_L
      // tree->Draw("DSDX_C:aCsI","nCsI==0","", 1004737, 0);
      cut.Form("nX_L==%d",i);
      hdraw.Form("X_L:tX_L-tF5",i);
      ch->SetMarkerColor(kBlack);
      ch->Draw(hdraw.Data(),cut.Data(),"", 1004737, 0);

      cutX_L[i]->Draw("same");
      c7->Update();
    }
  }

  if (Y_Lcuts) {
    TCanvas *c8 = new TCanvas("c8","",1800,1000);  
    c8->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c8->cd(i+1);
      // tree->Draw("DSDX_C:aCsI","nCsI==0","", 1004737, 0);
      cut.Form("nY_L==%d",i);
      hdraw.Form("Y_L:tY_L-tF5",i);
      ch->SetMarkerColor(kBlack);
      ch->Draw(hdraw.Data(),cut.Data(),"", 1004737, 0);
      cutX_L[i]->Draw("same");
      c8->Update();
    }
  }


}