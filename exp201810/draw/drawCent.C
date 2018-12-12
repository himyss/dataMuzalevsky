void drawCent() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_times.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  // c1->Divide(4,4);
  TString cut,hDraw;
  for(Int_t i=0;i<1;i++) {
    // c1->cd(i+1);
    // c1->GetPad(i+1)->SetLogz();
    hDraw.Form("X_C:aCsI >> h%d(400,0,2500,400,0,0.07)",i);
    cut.Form("nCsI==3 && X_C>0 && aCsI>0 && fXt>-9 && fXt<7 && fYt>-6 && fYt<10");
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c1->Update();
  }
  // c1->Print("/home/user/Desktop/3H.png");
}