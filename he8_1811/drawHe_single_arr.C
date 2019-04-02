void drawHe_single_arr() {
  TChain *ch = new TChain("tree");
  // ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
  // ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut_CsIarray.root");
  ch->Add("/home/oem/work/data/exp1811/analysed/he8_trigger2_cut.root");
  
    // ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_selected.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  gStyle->SetOptStat(0);

  TCutG *cutCsI_s[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16];

  TFile *f1;
  TString cutName;
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


  //--------------------------------------------------------------------------------

  // TString cut,hDraw;
  Double_t marSize = 1.3;

  TMarker *m10_1 = new TMarker(6.7503,3.2497, 34);
  m10_1->SetMarkerSize(marSize);
  m10_1->SetMarkerColor(kRed);

  TMarker *m10_2 = new TMarker(7.3376, 2.6624, 34);
  m10_2->SetMarkerSize(marSize);
  m10_2->SetMarkerColor(kRed);

  TMarker *m10_3 = new TMarker(8.0198, 1.9802, 34);
  m10_3->SetMarkerSize(marSize);
  m10_3->SetMarkerColor(kRed);

  TMarker *m10_4 = new TMarker(8.3988, 1.6012, 34);
  m10_4->SetMarkerSize(marSize);
  m10_4->SetMarkerColor(kRed);


  TMarker *m20_1 = new TMarker(18.089,1.9113, 34);
  m20_1->SetMarkerSize(marSize);
  m20_1->SetMarkerColor(kRed);

  TMarker *m20_2 = new TMarker(18.445,1.5546, 34);
  m20_2->SetMarkerSize(marSize);
  m20_2->SetMarkerColor(kRed); 

  TMarker *m20_3 = new TMarker(18.861,1.1387, 34);
  m20_3->SetMarkerSize(marSize);
  m20_3->SetMarkerColor(kRed); 

  TMarker *m20_4 = new TMarker(19.08,0.91975, 34);
  m20_4->SetMarkerSize(marSize);
  m20_4->SetMarkerColor(kRed);  



  TMarker *m1 = new TMarker(28.586, 1.4136, 34);
  m1->SetMarkerSize(marSize);
  m1->SetMarkerColor(kRed);

  TMarker *m2 = new TMarker(28.869, 1.1315, 34);
  m2->SetMarkerSize(marSize);
  m2->SetMarkerColor(kRed);

  TMarker *m3 = new TMarker(29.168, 0.83237, 34);
  m3->SetMarkerSize(marSize);
  m3->SetMarkerColor(kRed);

  TMarker *m4 = new TMarker(29.329, 0.67113, 34);
  m4->SetMarkerSize(marSize);
  m4->SetMarkerColor(kRed);


  TString cut,hDraw;
  Bool_t usingtarget = kFALSE; 
  
  gStyle->SetOptStat(0);
Int_t coinh7 = 0;
Int_t tmpC;

  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(4,4);

  for(Int_t i=0;i<16;i++) {
  // {Int_t i=13;



    c3->cd(i+1);
    cut.Form("flagLeft==1 && n20_L==%d",i);
    hDraw.Form("a20_L:X_L>>h1_%d(200,0,70,200,0,5)",i);

    // ch->SetMarkerColor(i+1);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c3->Update();
    cut.Form("nhe3==1 && nh3==1 && flagCent==1 && flagLeft==1 && n20_L==%d && X_L+a20_L<20",i);
    hDraw.Form("a20_L:X_L>>h_coin_%d(200,0,70,200,0,5)",i);
    ch->SetMarkerColor(kRed);
    ch->SetMarkerStyle(20);
    ch->SetMarkerSize(1);
    tmpC = ch->Draw(hDraw.Data(),cut.Data(),"same");
    cout << tmpC << endl;
    ch->SetMarkerColor(kBlack);
    coinh7 = coinh7+ tmpC;
    cuthe3[i]->SetLineColor(kRed);
    cuthe3[i]->Draw("same");
    // m1->Draw("same");
    // m2->Draw("same");
    // m3->Draw("same");
    // m4->Draw("same");

    // m10_1->Draw("same");
    // m10_2->Draw("same");
    // m10_3->Draw("same");
    // m10_4->Draw("same");

    // m20_1->Draw("same");
    // m20_2->Draw("same");
    // m20_3->Draw("same");
    // m20_4->Draw("same");


    c3->Update();
  }
  // c3->Print("/home/user/Desktop/pictures/de-E_all_coincidence.png");
  cout << coinh7 << " in total" << endl;

/*
  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(2,2);
  c4->cd(1);
  cut.Form("n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

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
  if (usingtarget) cut = cut + TString(" && nTarget==1");

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
  if (usingtarget) cut = cut + TString(" && nTarget==1");

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
  if (usingtarget) cut = cut + TString(" && nTarget==1");

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


  ch->SetMarkerColor(kRed);
  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.7);

  TCanvas *c5 = new TCanvas("c5","",1800,1000);  
  c5->Divide(2,2);
  c5->cd(1);
  cut.Form("n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",6);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

  hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",6);
  cut.Form("nh3==1 && n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent_arr==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();


  c5->Update();
  c5->cd(2);
  cut.Form("n20_L==1 && a20_L>0 && X_L>0 && flagLeft==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",7);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

  hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",7);
  cut.Form("nh3==1 && n20_L==2 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent_arr==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();



  c5->Update();
  c5->cd(3);
  cut.Form("n20_L==9 && a20_L>0 && X_L>0");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",10);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

  hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",10);
  cut.Form("nh3==1 && n20_L==9 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent_arr==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();



  c5->Update();
  c5->cd(4);
  cut.Form("n20_L==10 && a20_L>0 && X_L>0");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  hDraw.Form("a20_L:X_L>>h1%d_new(200,0,70,200,0,5)",11);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  c5->Update();

  hDraw.Form("a20_L:X_L>>h_h3%d_new(200,0,70,200,0,5)",11);
  cut.Form("nh3==1 && n20_L==10 && a20_L>0 && X_L>0 && flagLeft==1 && flagCent_arr==1");
  if (usingtarget) cut = cut + TString(" && nTarget==1");

  ch->Draw(hDraw.Data(),cut.Data(),"same");
  c5->Update();



  c5->Update();

  */
}