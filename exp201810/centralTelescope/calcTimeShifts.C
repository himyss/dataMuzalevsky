void calcTimeShifts() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  TH1F *h[32];
  Double_t a[32];

  TString hDraw,cut,hName;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4); 
  for(Int_t i=0;i<16;i++){
    c1->cd(i+1);
    hDraw.Form("tDSDY_C[%d]-tF5>>h_%d(60,110,140)",i,i+1);
    hName.Form("h_%d",i+1);
    cut.Form("DSDY_C[%d]>0 && tDSDY_C[%d]>0 && tF5>0",i,i);
    ch->Draw(hDraw.Data(),cut.Data(),"",5000000,0);
    h[i] = (TH1F*)gPad->GetPrimitive(hName.Data());
    a[i] =  h[i]->GetBinCenter(h[i]->GetMaximumBin());
    c1->Update();
  } 

  TCanvas *c2 = new TCanvas("c2","amp-time correlations",1800,1000);  
  c2->Divide(4,4);  
  for(Int_t i=16;i<32;i++){
    c2->cd(i+1-16);
    hName.Form("h_%d",i+1);
    hDraw.Form("tDSDY_C[%d]-tF5>>h_%d(60,110,140)",i,i+1);
    cut.Form("DSDY_C[%d]>0 && tDSDY_C[%d]>0 && tF5>0",i,i);
    ch->Draw(hDraw.Data(),cut.Data(),"",5000000,0);
    h[i] = (TH1F*)gPad->GetPrimitive(hName.Data());
    a[i] = h[i]->GetBinCenter(h[i]->GetMaximumBin());
    c2->Update();
  }  

  for(Int_t i=0;i<32;i++) {
    cout << a[i] << endl;
  }

  return;


}