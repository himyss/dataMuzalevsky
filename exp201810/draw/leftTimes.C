// tv__tree->Draw("a20_L:t20_L-tF5","a20_L>0 && n20_L==0","", 1851629, 0);



void leftTimes() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_selected.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4);
  TString cut,hDraw;
  for(Int_t i=0;i<16;i++) {
    c1->cd(i+1);
    hDraw.Form("X_L:tX_L-tF5 >> h%d(200,-50,200,200,0,0.07)",i);
    cut.Form("X_L>0 && nX_L==%d",i);
    ch->Draw(hDraw.Data(),cut.Data(),"");
    c1->Update();
  }
  // c1->Print("/home/user/Desktop/3H.png");
}