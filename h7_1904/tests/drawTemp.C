void drawTemp() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/targetCut/13/h7_ct_*_mm_frame_newPars.root");
  cout << ch->GetEntries() << endl;

  ch->SetMarkerStyle(7);

  TCanvas *c1 = new TCanvas("c1","",1900,1000); 
  c1->Divide(2,2);

  c1->cd(1);
  ch->Draw("t20_1","nhe3_1 && flag1 && ehe8>0.198 && ehe8<0.205");
  c1->Update();

  c1->cd(2);
  ch->Draw("v_he3*(t20_1):sqrt((x1t-fXt)*(x1t-fXt) + (y1t-fYt)*(y1t-fYt))","nhe3_1 && flag1 && ehe8>0.198 && ehe8<0.205");
  c1->Update();

  c1->cd(3);
  ch->Draw("tof_he3:sqrt((x1t-fXt)*(x1t-fXt) + (y1t-fYt)*(y1t-fYt))","nhe3_1 && flag1");
  c1->Update();

}