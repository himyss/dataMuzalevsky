{
  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/calibrated/be10_firstVol_new.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
  // c3h->Divide(4,4);

  // for(Int_t i=0;i<16;i++) {
  //   c3h->cd(i+1);
  Int_t i = 11;
  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);      
  cut.Form("multc_x==1",i);
  // hdraw.Form("DSD_X:aCsI>>h%d(1000,0,250,500,0,100)",i);
  hdraw.Form("arCsI[]:trCsI[]-tF5");
  // ch->SetMarkerStyle(8);
  ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
  c3h->Update();



}