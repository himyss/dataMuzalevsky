void drawCent() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central_times.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4);
  TString cut,hDraw;
  for(Int_t i=0;i<16;i++) {
    c1->cd(i+1);
    c1->GetPad(i+1)->SetLogz();
    hDraw.Form("DSDX_C:aCsI >> h%d(200,0,2000,200,0,0.0116)",i);
    cut.Form("nCsI==%d && DSDX_C>0 && trigger!=1",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c1->Update();
  }
  c1->Print("/home/user/Desktop/3H.png");
}