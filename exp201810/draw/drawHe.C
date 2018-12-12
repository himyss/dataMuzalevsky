void drawHe() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_times.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // c1->Divide(1,2);
  TString cut,hDraw;

  // c1->cd(1);
  ch->Draw("a20_L:X_L+a20_L>>h1(300,0,0.07,300,0,0.005)","a20_L>0 && X_L>0 && t20_L-tF5<100 && fXt>-9 && fXt<7","");
  c1->Update();

  // c1->cd(2);
  ch->SetMarkerColor(kRed);
  ch->SetMarkerSize(1);
  ch->SetMarkerStyle(3);
  ch->Draw("a20_L:X_L+a20_L>>h2(300,0,0.07,300,0,0.005)","a20_L>0 && X_L>0 && t20_L-tF5<100 && fXt>-9 && fXt<7 && nh3==1","same");
  c1->Update();

  TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // c1->Divide(1,2);

  c2->cd();
  ch->Draw("a20_L:X_L+a20_L>>h3(300,0,0.07,300,0,0.005)","a20_L>0 && X_L>0 && t20_L-tF5<100 && fXt>-9 && fXt<7","col");
  c2->Update();


  
}