 {

  gStyle->SetOptStat(0);

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/calibration/CsI/DSD_CsI_focused_cut.root");
  cout << ch->GetEntries() << endl;

  TString hCut,hDraw,histName;


  // TCanvas *c1 = new TCanvas("c1","",1800,1000);  

  // ch->SetMarkerColor(kBlack);
  // ch->Draw("F5+F3:tF5-tF3 >> ToF1(500,0,150,500,0,12000)","","", 9147248, 0);
  // ch->SetMarkerColor(kRed);
  // ch->Draw("F5+F3:tF5-tF3 >> ToF2(500,0,150,500,0,12000)","beamH3","same", 9147248, 0);
  // c1->Update();

  // TCanvas *с2 = new TCanvas("с2","",1800,1000);  
  // с2->Divide(4,4);

  // for(Int_t i=0;i<16;i++) {
  //   с2->cd(i+1);

  //   hDraw.Form("aCsI_reco-Y_C:aCsI_cal>>h%d_reco(160,0,160,160,0,160)",i);
  //   hCut.Form("Y_C>0 && nh3 && nCsI==%d",i);

  //   ch->Draw(hDraw.Data(),hCut.Data(),"col");
  //   с2->Update();
  // }


  // TCanvas *с3 = new TCanvas("с3","",1800,1000);  
  // с3->Divide(4,4);

  // for(Int_t i=0;i<16;i++) {
  // // Int_t 
  //   с3->cd(i+1);

  //   hDraw.Form("ebeam:aCsI_cal",i);
  //   hCut.Form("beamH3 && nh3 && nCsI==%d",i);
  //   ch->Draw(hDraw.Data(),hCut.Data(),"");
  //   с3->Update();
  // }

  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(2,2);
  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.4);

  c4->cd(1);
  hCut.Form("X_C>0 && nCsI==%d",0);
  hDraw.Form("X_C.:aCsI_cal>>h%d(600,0,200,600,0,20)",0);
  ch->Draw(hDraw.Data(),hCut.Data(),"col");
  c4->Update();

  for(Int_t i=1;i<4;i++) {

    ch->SetMarkerColor(i);
     
    hCut.Form("nCsI==%d && X_C>0 && (X_C<12 || aCsI_cal<120)",i);
    hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",i);
    ch->Draw(hDraw.Data(),hCut.Data(),"same",40000000,0);
    c4->Update();

  }

  c4->cd(2);
  hCut.Form("X_C>0 && nCsI==%d && (X_C<12 || aCsI_cal<120)",4);
  hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",4);
  ch->Draw(hDraw.Data(),hCut.Data(),"",40000000,0);
  c4->Update();

  for(Int_t i=5;i<8;i++) {

    ch->SetMarkerColor(i-4);
     
    hCut.Form("nCsI==%d && X_C>0 && (X_C<12 || aCsI_cal<120)",i);
    hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",i);
    ch->Draw(hDraw.Data(),hCut.Data(),"same",40000000,0);
    c4->Update();

  }

  c4->cd(3);
  hCut.Form("X_C>0 && nCsI==%d && (X_C<12 || aCsI_cal<120)",8);
  hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",8);
  ch->Draw(hDraw.Data(),hCut.Data(),"",40000000,0);
  c4->Update();

  for(Int_t i=9;i<12;i++) {

    if (i==9) continue;
    ch->SetMarkerColor(i-8);

    hCut.Form("nCsI==%d && X_C>0 && (X_C<12 || aCsI_cal<120)",i);
    hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",i);
    ch->Draw(hDraw.Data(),hCut.Data(),"same",40000000,0);
    c4->Update();

  }

  c4->cd(4);
  hCut.Form("X_C>0 && nCsI==%d && (X_C<12 || aCsI_cal<120)",12);
  hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",12);
  ch->Draw(hDraw.Data(),hCut.Data(),"",40000000,0);
  c4->Update();

  for(Int_t i=13;i<16;i++) {

    ch->SetMarkerColor(i-12);

    hCut.Form("nCsI==%d && X_C>0 && (X_C<12 || aCsI_cal<120)",i);
    hDraw.Form("X_C.:aCsI_cal>>h%d(300,0,200,300,0,20)",i);
    ch->Draw(hDraw.Data(),hCut.Data(),"same",40000000,0);
    c4->Update();

  }





}