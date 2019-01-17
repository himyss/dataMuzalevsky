void drawHe() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
    // ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_selected.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // c1->Divide(2,1);
  TString cut,hDraw;

  // c1->cd(2);
  ch->Draw("a20_L:X_L>>h1(300,0,70,300,0,5)","nHe8==1 && nMWPC==1 && vetoFlag==0 && nTarget==0 && a20_L>0 && X_L>0 && t20_L-tF5<100","col");
  c1->Update();


  TMarker *m10_1 = new TMarker(6.7503,3.2497, 20);
  m10_1->SetMarkerSize(1.5);
  m10_1->SetMarkerColor(kRed);

  TMarker *m10_2 = new TMarker(7.3376, 2.6624, 20);
  m10_2->SetMarkerSize(1.5);
  m10_2->SetMarkerColor(kRed);

  TMarker *m10_3 = new TMarker(8.0198, 1.9802, 20);
  m10_3->SetMarkerSize(1.5);
  m10_3->SetMarkerColor(kRed);

  TMarker *m10_4 = new TMarker(8.3988, 1.6012, 20);
  m10_4->SetMarkerSize(1.5);
  m10_4->SetMarkerColor(kRed);


  TMarker *m20_1 = new TMarker(18.089,1.9113, 20);
  m20_1->SetMarkerSize(1.5);
  m20_1->SetMarkerColor(kRed);

  TMarker *m20_2 = new TMarker(18.445,1.5546, 20);
  m20_2->SetMarkerSize(1.5);
  m20_2->SetMarkerColor(kRed); 

  TMarker *m20_3 = new TMarker(18.861,1.1387, 20);
  m20_3->SetMarkerSize(1.5);
  m20_3->SetMarkerColor(kRed); 

  TMarker *m20_4 = new TMarker(19.08,0.91975, 20);
  m20_4->SetMarkerSize(1.5);
  m20_4->SetMarkerColor(kRed);  



  TMarker *m1 = new TMarker(28.586, 1.4136, 20);
  m1->SetMarkerSize(1.5);
  m1->SetMarkerColor(kRed);

  TMarker *m2 = new TMarker(28.869, 1.1315, 20);
  m2->SetMarkerSize(1.5);
  m2->SetMarkerColor(kRed);

  TMarker *m3 = new TMarker(29.168, 0.83237, 20);
  m3->SetMarkerSize(1.5);
  m3->SetMarkerColor(kRed);

  TMarker *m4 = new TMarker(29.329, 0.67113, 20);
  m4->SetMarkerSize(1.5);
  m4->SetMarkerColor(kRed);


    m1->Draw("same");
    m2->Draw("same");
    m3->Draw("same");
    m4->Draw("same");

    m10_1->Draw("same");
    m10_2->Draw("same");
    m10_3->Draw("same");
    m10_4->Draw("same");

    m20_1->Draw("same");
    m20_2->Draw("same");
    m20_3->Draw("same");
    m20_4->Draw("same");   
  
}