void ampTime() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central.root");
  cout << ch->GetEntries() << endl;

  //--------------------------------------------------------------------------------
  TString hDraw,cut;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4);  
  for(Int_t i=0;i<16;i++){
    c1->cd(i+1);
    hDraw.Form("DSDY_C[%d]:tDSDY_C[%d]-tF5>>h_%d(400,60,260,200,0,0.1)",i,i,i+1);
    cut.Form("DSDY_C[%d]>0 && tDSDY_C[%d]>0 && tF5>0",i,i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c1->GetPad(i+1)->SetLogz();
    c1->Update();
  }

  TCanvas *c2 = new TCanvas("c2","amp-time correlations",1800,1000);  
  c2->Divide(4,4);  
  for(Int_t i=16;i<32;i++){
    c2->cd(i+1-16);
    hDraw.Form("DSDY_C[%d]:tDSDY_C[%d]-tF5>>h_%d(400,60,260,200,0,0.1)",i,i,i+1);
    cut.Form("DSDY_C[%d]>0 && tDSDY_C[%d]>0 && tF5>0",i,i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c2->GetPad(i+1-16)->SetLogz();
    c2->Update();
  }

  c1->Print("/home/user/Desktop/timeDSDX1.png");
  c2->Print("/home/user/Desktop/timeDSDX2.png");


  return;
}