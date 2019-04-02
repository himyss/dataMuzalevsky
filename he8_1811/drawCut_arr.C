void drawCut_arr(){
  gStyle->SetOptStat(0);
  Bool_t tritium = 0;
  Bool_t tritiumCal = 1;
  Bool_t he3 = 0;
  Bool_t tCsI_s = 0;
  Bool_t tCsI_s_s = kFALSE;
  Bool_t target = kFALSE;
  Bool_t centtimes = 0;
  Bool_t sq20times = 0;
  Bool_t X_Lcuts = 0;
  Bool_t Y_Lcuts = 0;


  TChain *ch1 = new TChain("tree");
  ch1->Add("/home/oem/work/data/exp1811/analysed/noTarget/he8_emtpytarget_cut.root");
  cout << ch1->GetEntries() << endl;

  TChain *ch = new TChain("tree");
  // ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
  ch->Add("/home/oem/work/data/exp1811/analysed/he8_trigger2_cut.root");
  // ch->Add("/media/user/work/data/Analysed1811/selected/he8_full_cut_emptyTarget.root");
  // cout << ch->GetEntries() << endl;

  TCutG *cutCsI_s[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16];
  TString cutName;
  TFile *f1;

  for(Int_t i=0;i<16;i++) {
    // cutName.Form("/media/user/work/macro/exp201810/draw/cuts/CsI_s_%d.root",i);
    cutName.Form("/home/oem/work/macro/he8_1811/tritonCuts/h3_%d.root",i);
    f1 = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/CsItimeCuts/CsI_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutCsI_s[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }


  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/cutX_L/X_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutX_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutX_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/cutY_L/Y_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutY_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutY_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/SQ20_Lcuts/sq20_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutSQ20_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutSQ20_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/helium3/he3_%d.root",i);
    f1 = new TFile(cutName.Data());
    cuthe3[i] = (TCutG*)f1->Get("CUTG");
    if (!cuthe3[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }



  TString cut,hdraw;

  if (tritium) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c1->cd(i+1);
      cut.Form("nCsI==%d && aCsI>0 && X_C>0 && flagCent",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("X_C.:aCsI>>h%d(300,0,4000,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");

      ch->SetMarkerColor(kRed);
      ch->SetMarkerStyle(20);
      cut.Form("nCsI==%d && nhe3 && aCsI>0 && X_C>0 && flagCent && flagLeft",i);
      hdraw.Form("X_C.:aCsI>>h_he3_%d(300,0,4000,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      ch->SetMarkerColor(kMagenta);
      ch->SetMarkerStyle(20);
      cut.Form("nCsI==%d && nhe3 && aCsI>0 && X_C>0 && nh3 && flagCent && flagLeft",i);
      hdraw.Form("X_C.:aCsI>>h_he3_coin_%d(300,0,4000,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      ch1->SetMarkerColor(kBlack);
      ch1->SetMarkerStyle(20);
      cut.Form("nCsI==%d && nhe3 && aCsI>0 && X_C>0 && nh3 && flagCent && flagLeft",i);
      hdraw.Form("X_C.:aCsI>>h_he3_coin_fon_%d(300,0,4000,300,0,20)",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"same");


      cut3h[i]->SetLineWidth(1);
      cut3h[i]->SetLineColor(kRed);
      cut3h[i]->Draw("same");
      c1->Update();
    }


      // cut.Form("nh3==1 && trigger==2 && nCsI==%d && flagCent==1",i);
      // // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);

      // hdraw.Form("X_C.:aCsI>>h_h3_%d(300,0,5000,300,0,20)",i);

      // ch->SetMarkerColor(kRed);
      // ch->SetMarkerStyle(20);
      // ch->SetMarkerSize(0.7);
      // cut.Form("nhe3==1 && nh3==1 && trigger==2 && nCsI==%d && flagCent==1",i);
      // hdraw.Form("X_C.:aCsI>>h%d_1(300,0,5000,300,0,20)",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");

      // cut3h[i]->SetLineColor(kRed);
      // cut3h[i]->Draw("same");
      
    // // c1->Print("/home/user/Desktop/redmine/triton.png");
    // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
    // c2->cd();
    // ch->Draw("X_C.:aCsI_s>>h(300,0,5000,300,0,100)","nCsI_s==2","col");
    // cut3h[2]->Draw("same");
    // c2->Update();
  }

if (tritiumCal) {
    TCanvas *c1_c = new TCanvas("c1_c","",1800,1000);  
    c1_c->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c1_c->cd(i+1);
      cut.Form("nCsI==%d && aCsI>0 && X_C>0 && flagCent",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("X_C.:aCsI_cal>>h%d(300,0,100,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");

      ch->SetMarkerColor(kRed);
      ch->SetMarkerStyle(20);
      cut.Form("nCsI==%d && nhe3 && aCsI>0 && X_C>0 && flagCent && flagLeft",i);
      hdraw.Form("X_C.:aCsI_cal>>h_he3_%d(300,0,100,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      ch->SetMarkerColor(kMagenta);
      ch->SetMarkerStyle(20);
      cut.Form("nCsI==%d && nhe3 && aCsI>0 && X_C>0 && nh3 && flagCent && flagLeft",i);
      hdraw.Form("X_C.:aCsI_cal>>h_he3_coin_%d(300,0,100,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      ch1->SetMarkerColor(kBlack);
      ch1->SetMarkerStyle(20);
      cut.Form("nCsI==%d && nhe3 && aCsI>0 && X_C>0 && nh3 && flagCent && flagLeft",i);
      hdraw.Form("X_C.:aCsI_cal>>h_he3_coin_fon_%d(300,0,100,300,0,20)",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"same");


      c1_c->Update();
    }
  }

  if (he3) {
    TCanvas *c1_h3 = new TCanvas("c1_h3","",1800,1000);  
    c1_h3->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
    // Int_t i=0;
      c1_h3->cd(i+1);
      cut.Form("n20_L==%d && flagLeft==1",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("a20_L.:X_L>>h_he3%d(200,0,70,200,0,5)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      cuthe3[i]->SetLineColor(kRed);
      cuthe3[i]->Draw("same");
      c1_h3->Update();
    } 

    TCanvas *c1_h3_single = new TCanvas("c1_h3_single","",1800,1000);  

    // for(Int_t i=0;i<16;i++) {
    {Int_t i=0;
      c1_h3_single->cd(i+1);
      cut.Form("trigger==2 && n20_L==%d && flagLeft==1",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("a20_L.:X_L>>h_he3_single_%d(200,0,70,200,0,5)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      cuthe3[i]->SetLineColor(kRed);
      cuthe3[i]->Draw("same");
      c1_h3_single->Update();
    } 


  }

  if (tCsI_s) {
    TCanvas *c3 = new TCanvas("c3","",1800,1000);  
    c3->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c3->cd(i+1);
      cut.Form("nCsI==%d",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("aCsI:tCsI-tF5 >> h_CsI_1_%d(200,-400,300,200,0,3000)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      cutCsI_s[i]->Draw("same");
      cutCsI_s[i]->SetLineColor(kBlack);
      cutCsI_s[i]->SetLineWidth(2);
      ch->SetMarkerColor(kRed);
      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.1); 

      cut.Form("nCsI==%d && flagCent",i);
      hdraw.Form("aCsI:tCsI-tF5 >> h_CsI_2_%d(200,-400,300,200,0,3000)");
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      c3->Update();
    }
    // c3->Print("/home/user/Desktop/redmine/CsI_cuts.png");
  }


  if (target) {
    TCanvas *c4 = new TCanvas("c4","target cut",1000,1000);
    ch->SetMarkerColor(kBlack);  
    cout << ch->Draw("fYt:fXt>>h_target(300,-30,30,300,-30,30)","","col") << endl;
    ch->SetMarkerColor(kRed);
    cout << ch->Draw("fYt:fXt>>h_target_cut(300,-30,30,300,-30,30)","trigger==2 && nTarget==1","same");
    ch->SetMarkerColor(kBlack);
  } 

  if (centtimes) {
    TCanvas *c5 = new TCanvas("c5","",1800,1000);
    c5->Divide(4,4);

    for(Int_t i=0;i<16;i++) {
      c5->cd(i+1);
// hdraw cutName
      cutName.Form("trigger==2 && nY_C==%d && tY_C - tF5>123 && tY_C - tF5<135",i);
      ch->SetMarkerColor(kBlack);  
      ch->Draw("Y_C:tY_C - tF5",cutName.Data(),"");
      ch->SetMarkerColor(kRed);
      cutName = cutName + TString(" && flagCent==1");
      ch->Draw("Y_C:tY_C - tF5",cutName.Data(),"same");

      c5->Update();
    }

    TCanvas *c5_1 = new TCanvas("c5_1","",1800,1000);
    c5_1->Divide(4,4);

    for(Int_t i=0;i<16;i++) {
      c5_1->cd(i+1);
// hdraw cutName
      cutName.Form("trigger==2 && nX_C==%d && tX_C - tF5>80 && tX_C - tF5<135",i);
      ch->SetMarkerColor(kBlack);  
      ch->Draw("X_C:tX_C - tF5",cutName.Data(),"");
      ch->SetMarkerColor(kRed);
      cutName = cutName + TString(" && flagCent==1");
      ch->Draw("X_C:tX_C - tF5",cutName.Data(),"same");

      c5_1->Update();
    }


    // c5->cd(1);
    // ch->SetMarkerColor(kBlack);  
    // ch->Draw("X_C:tX_C - tF5","","");
    // ch->SetMarkerColor(kRed);
    // ch->Draw("X_C:tX_C - tF5","flagCent_arr==1","same");
    // ch->SetMarkerColor(kBlack);

    // c5->cd(2);
    // ch->SetMarkerColor(kBlack);  
    // ch->Draw("Y_C:tY_C - tF5","","", 1004737, 0);
    // ch->SetMarkerColor(kRed);
    // ch->Draw("Y_C:tY_C - tF5","flagCent_arr==1","same");
    // ch->SetMarkerColor(kBlack);
  }

  if (sq20times) {

    TCanvas *c6 = new TCanvas("c6","sq20_L times",1800,1000);
    c6->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c6->cd(i+1);
      cut.Form("n20_L==%d && t20_L-tF5>0 && t20_L-tF5<120",i);
      hdraw.Form("a20_L_uncorr:t20_L-tF5 >> h_tsq20_%d(300,0,120,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");

      ch->SetMarkerColor(kRed);
      cut.Form("n20_L==%d && flagLeft && t20_L-tF5>0 && t20_L-tF5<120",i);
      hdraw.Form("a20_L_uncorr:t20_L-tF5 >> h_tsq20_red_%d(300,0,120,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      cutSQ20_L[i]->SetLineColor(kBlack);
      cutSQ20_L[i]->Draw("same");

      c6->Update();
    }
    // c6->Print("/home/user/Desktop/pictures/t20_L_all.png");

  }

  if (X_Lcuts) {
    TCanvas *c7 = new TCanvas("c7","",1800,1000);  
    c7->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c7->cd(i+1);
      // tX_L-tF5, X_L
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      cut.Form("nX_L==%d && tX_L-tF5<200",i);
      hdraw.Form("X_L:tX_L-tF5 >> h_X_L_%d(300,-60,100,500,0,100)",i);
      ch->SetMarkerColor(kBlack);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      ch->SetMarkerColor(kRed);
      hdraw.Form("X_L:tX_L-tF5 >> h_X_L_red_%d(300,-60,100,500,0,100)",i);
      cut.Form("nX_L==%d && flagLeft==1",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      cutX_L[i]->SetLineColor(kBlack);
      cutX_L[i]->SetLineWidth(2);
      cutX_L[i]->Draw("same");
      c7->Update();
    }
  }

  if (Y_Lcuts) {
    TCanvas *c8 = new TCanvas("c8","",1800,1000);  
    c8->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c8->cd(i+1);
      cut.Form(" nY_L==%d && tY_L-tF5<200",i);
      hdraw.Form("Y_L:tY_L-tF5>>h_Y_L_%d(300,-70,100,500,0,100)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");

      ch->SetMarkerColor(kRed);
      cut.Form("nY_L==%d && tY_L-tF5<200 && flagLeft",i);
      hdraw.Form("Y_L:tY_L-tF5>>h_Y_L_red_%d(300,-70,100,500,0,100)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      cutY_L[i]->SetLineColor(kBlack);
      cutY_L[i]->Draw("same");
      c8->Update();
    }

  }


}