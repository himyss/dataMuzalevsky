void drawHe_single() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
    // ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_selected.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  TLine *l1 = new TLine(20.69,1,20.69,2.5);
  l1->SetLineColor(kRed);
  l1->SetLineWidth(3);
  TLine *l2 = new TLine(15,1.8,25,1.8);
  l2->SetLineColor(kRed);
  l2->SetLineWidth(3);

  TLine *l3 = new TLine(7.22,2.5,7.22,3.5);
  l3->SetLineColor(kRed);
  l3->SetLineWidth(3);
  TLine *l4 = new TLine(5,3.11,10,3.11);
  l4->SetLineColor(kRed);
  l4->SetLineWidth(3);

  TLine *l5 = new TLine(29.01,1,29.01,2);
  l5->SetLineColor(kRed);
  l5->SetLineWidth(3);
  TLine *l6 = new TLine(25,1.43,35,1.43);
  l6->SetLineColor(kRed);
  l6->SetLineWidth(3);

  // --------------------------------------------------------------------------------
  
  // gStyle->SetOptStat(0);
  // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // c2->Divide(4,4);
  TString cut,hDraw;
  // ch->SetMarkerStyle(20);
  // ch->SetMarkerSize(0.6);
  // // c1->cd(2);
  // for(Int_t i=0;i<16;i++) {
  // // {Int_t i=15;
  //   c2->cd(i+1);
  //   // cut.Form("nY_L==%d && n20_L==12 && nHe8==1 && nMWPC==1 && vetoFlag==0 && nTarget==0 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
  //   cut.Form("nY_L==%d && n20_L==14 && nHe8==1 && nMWPC==1 && vetoFlag==0 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
  //   hDraw.Form("a20_L:X_L>>h%d(300,0,70,300,0,5)",i);

  //   // ch->SetMarkerColor(i+1);
  //   ch->Draw(hDraw.Data(),cut.Data(),"");
  //   // l1->Draw("same");
  //   // l2->Draw("same");

  //   // l3->Draw("same");
  //   // l4->Draw("same");

  //   // l5->Draw("same");
  //   // l6->Draw("same");

  //   // else ch->Draw(hDraw.Data(),cut.Data(),"same");
  //   c2->Update();
  // }

  //--------------------------------------------------------------------------------
  gStyle->SetOptStat(0);

  // TString cut,hDraw;

  TMarker *m10_1 = new TMarker(6.7503,3.2497, 20);
  m10_1->SetMarkerSize(0.7);
  m10_1->SetMarkerColor(kRed);

  TMarker *m10_2 = new TMarker(7.3376, 2.6624, 20);
  m10_2->SetMarkerSize(0.7);
  m10_2->SetMarkerColor(kRed);

  TMarker *m10_3 = new TMarker(8.0198, 1.9802, 20);
  m10_3->SetMarkerSize(0.7);
  m10_3->SetMarkerColor(kRed);

  TMarker *m10_4 = new TMarker(8.3988, 1.6012, 20);
  m10_4->SetMarkerSize(0.7);
  m10_4->SetMarkerColor(kRed);


  TMarker *m20_1 = new TMarker(18.089,1.9113, 20);
  m20_1->SetMarkerSize(0.7);
  m20_1->SetMarkerColor(kRed);

  TMarker *m20_2 = new TMarker(18.445,1.5546, 20);
  m20_2->SetMarkerSize(0.7);
  m20_2->SetMarkerColor(kRed); 

  TMarker *m20_3 = new TMarker(18.861,1.1387, 20);
  m20_3->SetMarkerSize(0.7);
  m20_3->SetMarkerColor(kRed); 

  TMarker *m20_4 = new TMarker(19.08,0.91975, 20);
  m20_4->SetMarkerSize(0.7);
  m20_4->SetMarkerColor(kRed);  



  TMarker *m1 = new TMarker(28.586, 1.4136, 20);
  m1->SetMarkerSize(0.7);
  m1->SetMarkerColor(kRed);

  TMarker *m2 = new TMarker(28.869, 1.1315, 20);
  m2->SetMarkerSize(0.7);
  m2->SetMarkerColor(kRed);

  TMarker *m3 = new TMarker(29.168, 0.83237, 20);
  m3->SetMarkerSize(0.7);
  m3->SetMarkerColor(kRed);

  TMarker *m4 = new TMarker(29.329, 0.67113, 20);
  m4->SetMarkerSize(0.7);
  m4->SetMarkerColor(kRed);




  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4,4);
  // ch->SetMarkerStyle(20);
  // ch->SetMarkerSize(0.6);
  // c1->cd(2);
  for(Int_t i=0;i<16;i++) {
  // {Int_t i=10;

    c1->cd(i+1);
    // cut.Form("nY_L==%d && n20_L==12 && nHe8==1 && nMWPC==1 && vetoFlag==0 && nTarget==1 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
    cut.Form("X_Ltimes==1 && Y_Ltimes==1&& n20_L==%d && nHe8==1 && nMWPC==1 && vetoFlag==0 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
    hDraw.Form("a20_L:X_L>>h%d(200,0,70,200,0,5)",i);

    // ch->SetMarkerColor(i+1);
    // ch->Draw(hDraw.Data(),cut.Data(),"col");

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


    // else ch->Draw(hDraw.Data(),cut.Data(),"same");
    c1->Update();
  }


  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(4,4);
  // ch->SetMarkerStyle(20);
  // ch->SetMarkerSize(0.6);
  // c1->cd(2);
  for(Int_t i=0;i<16;i++) {
  // {Int_t i=10;



    c3->cd(i+1);
    // cut.Form("nY_L==%d && n20_L==12 && nHe8==1 && nMWPC==1 && vetoFlag==0 && nTarget==1 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
    cut.Form("timesCsI==1 && X_Ltimes==1 && Y_Ltimes==1&& n20_L==%d && nHe8==1 && nMWPC==1 && vetoFlag==0 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
    hDraw.Form("a20_L:X_L>>h1_%d(200,0,70,200,0,5)",i);

    // ch->SetMarkerColor(i+1);
    // ch->Draw(hDraw.Data(),cut.Data(),"col");
    c3->Update();
    cut.Form("timesCsI==1 && nh3==1 && X_Ltimes==1 && Y_Ltimes==1 && n20_L==%d && nHe8==1 && nMWPC==1 && vetoFlag==0 && a20_L>0 && X_L>0 && t20_L-tF5<100",i);
    hDraw.Form("a20_L:X_L>>h_coin_%d(200,0,70,200,0,5)",i);
    ch->SetMarkerColor(kRed);
    ch->SetMarkerStyle(7);
    // ch->Draw(hDraw.Data(),cut.Data(),"same");
    ch->SetMarkerColor(kBlack);

    c3->Update();
  }
ch->SetMarkerColor(kRed);
ch->SetMarkerStyle(7);
ch->SetMarkerSize(2);

  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(2,2);
  c4->cd(1);
  cut.Form("n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1");
  hDraw.Form("a20_L:X_L>>h%d_new(200,0,70,200,0,5)",6);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c4->Update();

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

c4->Update();
  c4->cd(2);
  cut.Form("n20_L==2 && a20_L>0 && X_L>0 && flagLeft==1");
  hDraw.Form("a20_L:X_L>>h%d_new(200,0,70,200,0,5)",7);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c4->Update();


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

c4->Update();
  c4->cd(3);
  cut.Form("n20_L==9 && a20_L>0 && X_L>0 && flagLeft==1");
  hDraw.Form("a20_L:X_L>>h%d_new(200,0,70,200,0,5)",10);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c4->Update();

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

c4->Update();
  c4->cd(4);
  cut.Form("n20_L==10 && a20_L>0 && X_L>0 && flagLeft==1");
  hDraw.Form("a20_L:X_L>>h%d_new(200,0,70,200,0,5)",11);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c4->Update();


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

  c4->Update();

  ch->SetMarkerSize(0.7);
  ch->SetMarkerStyle(20);

 TCanvas *c5 = new TCanvas("c5","",1800,1000);  
  c5->Divide(2,2);
  c5->cd(1);
  cut.Form("n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1");
  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",6);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

  hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",6);
  cut.Form("nh3==1 && n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent==1");
  ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();


c5->Update();
  c5->cd(2);
  cut.Form("n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1");
  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",7);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",7);
cut.Form("nh3==1 && n20_L==2 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent==1");
ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();



c5->Update();
  c5->cd(3);
  cut.Form("n20_L==9 && a20_L>0 && X_L>0");
  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",10);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",10);
cut.Form("nh3==1 && n20_L==9 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent==1");
ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();



c5->Update();
  c5->cd(4);
  cut.Form("n20_L==10 && a20_L>0 && X_L>0");
  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",11);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",11);
cut.Form("nh3==1 && n20_L==10 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent==1");
ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();



  c5->Update();

  
}