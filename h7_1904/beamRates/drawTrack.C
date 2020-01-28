void drawTrack() {
  
  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/newCal/test/track0/h7_ct_*_cut_newPars.root");
  cout << ch->GetEntries() << endl;

  TChain *ch1 = new TChain("tree");
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/beamDiagnostics/selected/h7_ct_*_cut_newPars.root");
  cout << ch1->GetEntries() << endl;



  TString cut;

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(3,2);

  c1->cd(1);
  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  ch->Draw("y1c:x1c >> mwpc1(32,-20,20,32,-20,20)",cut.Data(),"col",60000000);
  c1->Update();

  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.9);
  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  cut += " && fabs(y1c)<2 && fabs(x1c)<2";
  ch->Draw("y1c:x1c",cut.Data(),"same",60000000);
  c1->Update();

  c1->cd(2);
  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  ch->Draw("y2c:x2c >> mwpc2(32,-20,20,32,-20,20)",cut.Data(),"col",60000000);
  c1->Update();

  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  cut += " && fabs(y2c)<2 && fabs(x2c)<2";
  ch->Draw("y2c:x2c",cut.Data(),"same",60000000);
  c1->Update();

  c1->cd(3);
  cut.Form("trigger!=1 && nX_C>0 && nY_C>0");
  ch1->Draw("fYt:fXt >> target(64,-20,20,64,-20,20)",cut.Data(),"col",60000000);
  c1->Update();

  cut.Form("trigger!=1 && nX_C>0 && nY_C>0");
  cut += " && fabs(fYt)<1 && fabs(fXt)<1";
  ch->Draw("fYt:fXt",cut.Data(),"same",60000000);
  c1->Update();

  Float_t xCent = 0;
  Float_t yCent = 0;

  TEllipse *dia = new TEllipse(xCent,yCent,12.5);
  dia->SetLineColor(kRed);
  dia->SetLineWidth(3);
  dia->SetFillStyle(0); 
  dia->Draw();

  TLine *lh = new TLine(xCent,yCent-12.5,xCent,yCent+12.5);
  lh->SetLineColor(kRed);
  lh->SetLineWidth(2);
  lh->Draw();


  TLine *lv = new TLine(xCent-12.5,yCent,xCent+12.5,yCent);
  lv->SetLineColor(kRed);
  lv->SetLineWidth(2);
  lv->Draw();

  c1->cd(4);
  // cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  // ch->Draw("xCt:yCt >> centT(32,-32,32,32,-32,32)",cut.Data(),"col",60000000);
  // c1->Update();

  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  cut += " && fabs(y1c)<2 && fabs(x1c)<2";
  cut += " && fabs(y2c)<2 && fabs(x2c)<2";
  cut += " && fabs(fYt)<1 && fabs(fXt)<1";  
  ch->Draw("yCt:xCt >> centT(32,-32,32,32,-32,32)","trigger==1 && nX_C>0 && nY_C>0","col",60000000);
  c1->Update();

  TH2F *h2D = (TH2F*)gPad->GetPrimitive("centT");
  TF2 *fitf = new TF2("fitf","bigaus",-4,4,-4,4);
  h2D->Fit(fitf);
  c1->Update();

  c1->cd(5);
  // ch->SetLineColor(kBlack);
  // cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  // ch->Draw("xCt >> xCent(32,-32,32)",cut.Data(),"",60000000);
  // c1->Update();

  ch->SetLineColor(kBlack);
  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  cut += " && fabs(y1c)<2 && fabs(x1c)<2";
  cut += " && fabs(y2c)<2 && fabs(x2c)<2";
  cut += " && fabs(fYt)<1 && fabs(fXt)<1";   
  ch->Draw("xCt >> xCent(32,-32,32)",cut.Data(),"",60000000);

  TH1F *h1D = (TH1F*)gPad->GetPrimitive("xCent");
  TF1 *fit_g = new TF1("fit_g","gaus",-5,5);
  h1D->Fit(fit_g,"R");
  c1->Update();

  c1->cd(6);
  // ch->SetLineColor(kBlack);
  // cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  // ch->Draw("yCt >> yCent(32,-32,32)",cut.Data(),"",60000000);
  c1->Update();

  ch->SetLineColor(kBlack);
  cut.Form("trigger==1 && nX_C>0 && nY_C>0");
  cut += " && fabs(y1c)<2 && fabs(x1c)<2";
  cut += " && fabs(y2c)<2 && fabs(x2c)<2";
  cut += " && fabs(fYt)<1 && fabs(fXt)<1";   
  ch->Draw("yCt >> yCent(32,-32,32)",cut.Data(),"",60000000);
  c1->Update();

  fit_g->SetRange(-5,3);
  h1D = (TH1F*)gPad->GetPrimitive("yCent");
  h1D->Fit(fit_g,"R");
  c1->Update();
}