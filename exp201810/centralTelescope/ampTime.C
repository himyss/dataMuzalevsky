void ampTime() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central.root");
  cout << ch->GetEntries() << endl;

  //--------------------------------------------------------------------------------
  TString     hDraw,cut;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4);  
  for(Int_t i=0;i<16;i++){
    c1->cd(i+1);
    c1->GetPad(i)->SetLogz();
    hDraw.Form("DSDX_C[%d]:tDSDX_C[%d]>>h_%d(400,0,1200,400,0,0.1)",i,i,i+1);
    ch->Draw(hDraw.Data(),"","col");
    c1->Update();
  }

  TCanvas *c2 = new TCanvas("c2","amp-time correlations",1800,1000);  
  c2->Divide(4,4);  
  for(Int_t i=16;i<32;i++){
    c2->cd(i+1-16);
    c2->GetPad(i-16)->SetLogz();
    hDraw.Form("DSDX_C[%d]:tDSDX_C[%d]>>h_%d(400,0,1200,400,0,0.1)",i,i,i+1);
    ch->Draw(hDraw.Data(),"","col");
    c2->Update();
  }
  c1->Print("/home/user/Desktop/amptimeT1.png");
  c2->Print("/home/user/Desktop/amptimeT2.png");

  return;
}