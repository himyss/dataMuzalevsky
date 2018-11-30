void calctCsIcut() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------

  TH1F *h[16];
  Double_t a[16];

  TString hDraw,cut,hName;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4); 
  for(Int_t i=0;i<16;i++){
    c1->cd(i+1);
    hDraw.Form("aCsI:tCsI-tF5 >> h_%d(300,0,1000,300,0,4000)",i+1);
    hName.Form("h_%d",i+1);
    cut.Form("(tCsI<175 || aCsI<1000) && nCsI==%d",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c1->GetPad(i+1)->SetLogz();
    c1->Update();
  } 
  c1->Print("/home/user/Desktop/tCsI_cut_cut.png");
  return;
}