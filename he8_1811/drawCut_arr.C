void drawCut_arr(){
  gStyle->SetOptStat(0);
  Bool_t tritium = kTRUE;
  Bool_t he3 = kFALSE;
  Bool_t tCsI_s = kFALSE;
  Bool_t tCsI_s_s = kFALSE;
  Bool_t target = kFALSE;
  Bool_t centtimes = kFALSE;
  Bool_t sq20times = kFALSE;
  Bool_t X_Lcuts = kFALSE;
  Bool_t Y_Lcuts = kFALSE;

  TChain *ch = new TChain("tree");
  // ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
  ch->Add("/media/user/work/data/Analysed1811/selected/he8_full_cut_CsIarray.root");
  // ch->Add("/media/user/work/data/Analysed1811/selected/he8_full_cut_emptyTarget.root");
  // cout << ch->GetEntries() << endl;

  TCutG *cutCsI_s[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16];
  TString cutName;
  TFile *f1;

  for(Int_t i=0;i<16;i++) {
    // cutName.Form("/media/user/work/macro/exp201810/draw/cuts/CsI_s_%d.root",i);
    cutName.Form("/media/user/work/macro/he8_1811/tritonCuts/CsI_%d.root",i);
    f1 = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/CsItimeCuts/CsI_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutCsI_s[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }


  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/cutX_L/X_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutX_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutX_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/cutY_L/Y_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutY_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutY_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/SQ20_Lcuts/sq20_L_%d.root",i);
    f1 = new TFile(cutName.Data());
    cutSQ20_L[i] = (TCutG*)f1->Get("CUTG");
    if (!cutSQ20_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/he8_1811/he3_cut/he3_%d.root",i);
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
      cut.Form("trigger==2 && nCsI==%d && flagCent==1",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("X_C.:aCsI>>h%d(300,0,5000,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");

      // cut.Form("nh3==1 && trigger==2 && nCsI==%d && flagCent==1",i);
      // // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);

      // hdraw.Form("X_C.:aCsI>>h_h3_%d(300,0,5000,300,0,20)",i);

      ch->SetMarkerColor(kRed);
      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);
      cut.Form("nhe3==1 && nh3==1 && trigger==2 && nCsI==%d && flagCent==1",i);
      hdraw.Form("X_C.:aCsI>>h%d_1(300,0,5000,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      // cut3h[i]->SetLineColor(kRed);
      // cut3h[i]->Draw("same");
      c1->Update();
    }
    // // c1->Print("/home/user/Desktop/redmine/triton.png");
    // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
    // c2->cd();
    // ch->Draw("X_C.:aCsI_s>>h(300,0,5000,300,0,100)","nCsI_s==2","col");
    // cut3h[2]->Draw("same");
    // c2->Update();
  }

  if (he3) {
    TCanvas *c1_h3 = new TCanvas("c1_h3","",1800,1000);  
    c1_h3->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
    // Int_t i=0;
      c1_h3->cd(i+1);
      cut.Form("trigger==2 && n20_L==%d && flagLeft==1",i);
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
      cut.Form("trigger==2 && nCsI_s==%d",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("aCsI_s:tCsI_s-tF5 >> h_CsI_1_%d(200,-400,300,200,0,3000)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      ch->SetMarkerColor(kRed);
      // cutCsI_s[i]->Draw("same");
      // cutCsI_s[i]->SetLineColor(kRed);
      ch->SetMarkerColor(kRed);
      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.1); 

      cut.Form("trigger==2 && nCsI_s==%d && flagCent_arr==1",i);
      hdraw.Form("aCsI_s:tCsI_s-tF5 >> h_CsI_2_%d(200,-400,300,200,0,3000)");
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      ch->SetMarkerColor(kBlack);
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
      cutName = cutName + TString(" && flagCent_arr==1");
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
      cutName = cutName + TString(" && flagCent_arr==1");
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
    // TCanvas *c6 = new TCanvas("c6","sq20_L times",1800,1000);
    // c6->Divide(4,4);
    // for(Int_t i=0;i<16;i++) {
    //   c6->cd(i+1);
    //   cut.Form("n20_L==%d && t20_L-tF5>0 && t20_L-tF5<150",i);
    //   // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
    //   hdraw.Form("a20_L:t20_L-tF5");
    //   ch->Draw(hdraw.Data(),cut.Data(),"");
    //   // ch->SetMarkerColor(kRed);
    //   // cut.Form("n20_L==%d && flagLeft==1 && t20_L-tF5>40 && t20_L-tF5<100",i);
    //   // ch->Draw(hdraw.Data(),cut.Data(),"same");
    //   // ch->SetMarkerColor(kBlack);
    //   c6->Update();
    // }

    // TCanvas *c7 = new TCanvas("c7","sq20_L times",1800,1000);
    // // for(Int_t i=0;i<16;i++) 
    // {
    //   Int_t i = 3;
    //   // c6->cd(i+1);
    //   cut.Form("n20_L==%d",i);
    //   // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
    //   hdraw.Form("a20_L:t20_L-tF5");
    //   ch->Draw(hdraw.Data(),cut.Data(),"");
    //   // ch->SetMarkerColor(kRed);
    //   // cut.Form("n20_L==%d && flagLeft==1 && t20_L-tF5>40 && t20_L-tF5<100",i);
    //   // ch->Draw(hdraw.Data(),cut.Data(),"same");
    //   // ch->SetMarkerColor(kBlack);
    //   c7->Update();
    // }


    TCanvas *c6 = new TCanvas("c6","sq20_L times",1800,1000);
    c6->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c6->cd(i+1);
      cut.Form("trigger==2 && n20_L==%d && t20_L-tF5>0 && t20_L-tF5<120",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("a20_L:t20_L-tF5 >> h_tsq20_%d(300,0,120,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      cutSQ20_L[i]->SetLineColor(kRed);
      cutSQ20_L[i]->Draw("same");
      // ch->SetMarkerColor(kRed);
      // cut.Form("n20_L==%d && flagLeft==1 && t20_L-tF5>40 && t20_L-tF5<100",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // ch->SetMarkerColor(kBlack);
      c6->Update();
    }
    c6->Print("/home/user/Desktop/pictures/t20_L_all.png");

    TCanvas *c6_single = new TCanvas("c6_single","sq20_L times",1800,1000);
    c6_single->Divide(2,1);
    // for(Int_t i=0;i<16;i++) {
    
    { c6_single->cd(1);
      Int_t i = 10;
      // c6_single->cd(i+1);
      cut.Form("trigger==2 && n20_L==%d",i);
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      hdraw.Form("a20_L_uncorr:t20_L-tF5 >> h_tsq20_signgle_%d(300,0,120,300,0,20)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      cutSQ20_L[i]->SetLineColor(kRed);
      cutSQ20_L[i]->Draw("same");

      cut.Form("trigger==2 && n20_L==%d",i);
      hdraw.Form("a20_L_uncorr:t20_L-tF5 >> h_tsq20_signgle1_%d(300,0,120,300,0,20)",i);
      c6_single->cd(2);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      cutSQ20_L[i]->SetLineColor(kRed);
      cutSQ20_L[i]->Draw("same");
      // ch->SetMarkerColor(kRed);
      // cut.Form("n20_L==%d && flagLeft==1 && t20_L-tF5>40 && t20_L-tF5<100",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // ch->SetMarkerColor(kBlack);
      c6_single->Update();
      c6_single->Print("/home/user/Desktop/pictures/t20_L_single.png");
    }


    // TCanvas *c9 = new TCanvas("c7","sq20_L times",1800,1000);
    // // for(Int_t i=0;i<16;i++) 
    // {
    //   Int_t i = 3;
    //   // c6->cd(i+1);
    //   cut.Form("n20_L==%d",i);
    //   // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
    //   hdraw.Form("a20_L:t20_L-tF5 >> hcolSingle_%d(300,0,120,300,0,20)");
    //   ch->Draw(hdraw.Data(),cut.Data(),"col");
    //   // ch->SetMarkerColor(kRed);
    //   // cut.Form("n20_L==%d && flagLeft==1 && t20_L-tF5>40 && t20_L-tF5<100",i);
    //   // ch->Draw(hdraw.Data(),cut.Data(),"same");
    //   // ch->SetMarkerColor(kBlack);
    //   c9->Update();
    // }




  }

  if (X_Lcuts) {
    TCanvas *c7 = new TCanvas("c7","",1800,1000);  
    c7->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c7->cd(i+1);
      // tX_L-tF5, X_L
      // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
      cut.Form("trigger==2 && nX_L==%d && tX_L-tF5<200",i);
      hdraw.Form("X_L:tX_L-tF5 >> h_X_L_%d(500,-50,150,500,0,100)",i);
      ch->SetMarkerColor(kBlack);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      // ch->SetMarkerColor(kRed);
      // cut.Form("nX_L==%d && flagLeft==1",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      cutX_L[i]->SetLineColor(kRed);
      cutX_L[i]->SetLineWidth(2);
      cutX_L[i]->Draw("same");
      c7->Update();
    }
    c7->Print("/home/user/Desktop/pictures/tX_L_all.png");
    // c7->Print("/home/user/Desktop/redmine/X_L_cuts.png");
  }

  if (Y_Lcuts) {
    // TCanvas *c8 = new TCanvas("c8","",1800,1000);  
    // c8->Divide(4,4);
    // for(Int_t i=0;i<16;i++) {
    //   c8->cd(i+1);
    //   // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
    //   cut.Form("trigger==2 && nY_L==%d && tY_L-tF5<200",i);
    //   hdraw.Form("Y_L:tY_L-tF5>>h_Y_L_%d(500,-70,150,500,0,100)",i);
    //   ch->SetMarkerColor(kBlack);
    //   ch->Draw(hdraw.Data(),cut.Data(),"col");
    //   cutY_L[i]->SetLineColor(kRed);
    //   cutY_L[i]->Draw("same");
    //   c8->Update();
    // }
    // c8->Print("/home/user/Desktop/pictures/tY_L_all.png");
    TCanvas *c9 = new TCanvas("c9","",1800,1000);
    c9->Divide(2,1);
    c9->cd(1);
    Int_t i = 13; 
    // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
    cut.Form("trigger==2 && nY_L==%d && tY_L-tF5<200",i);
    hdraw.Form("Y_L:tY_L-tF5>>h_Y_L_single_%d(500,-70,150,500,0,100)",i);
    ch->SetMarkerColor(kBlack);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    cutY_L[i]->SetLineWidth(2.5);
    cutY_L[i]->SetLineColor(kRed);
    cutY_L[i]->Draw("same");
    c9->Update();

    c9->cd(2);
i = 9; 
    // tX_L-tF5, X_L
    // tree->Draw("DSDX_C:aCsI_s","nCsI_s==0","", 1004737, 0);
    cut.Form("trigger==2 && nX_L==%d && tX_L-tF5<200",i);
    hdraw.Form("X_L:tX_L-tF5 >> h_X_L__single%d(500,-50,150,500,0,100)",i);
    ch->SetMarkerColor(kBlack);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    // ch->SetMarkerColor(kRed);
    // cut.Form("nX_L==%d && flagLeft==1",i);
    // ch->Draw(hdraw.Data(),cut.Data(),"same");
    cutX_L[i]->SetLineColor(kRed);
    cutX_L[i]->SetLineWidth(2.5);
    cutX_L[i]->Draw("same");
    c9->Update();
    


    c9->Print("/home/user/Desktop/pictures/tY_X_L_L_single.png");
  }


}