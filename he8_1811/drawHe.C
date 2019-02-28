void drawHe() {

// 
  TCutG *cutCsI_s[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16];
  TString cutName;
  TFile *f1;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/he3_cut/he3_%d.root",i);
    f1 = new TFile(cutName.Data());
    cuthe3[i] = (TCutG*)f1->Get("CUTG");
    if (!cuthe3[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }



  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/he8_trigger2_cut.root");

  TChain *ch1 = new TChain("tree");
  ch1->Add("/home/oem/work/data/exp1811/analysed/noTarget/he8_emtpytarget_cut.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  gStyle->SetOptStat(0);
  // TCanvas *c1 = new TCanvas("c1","",1800,1000);  

  TString cut,hDraw;

  Int_t nCoi = 0;



    TMarker *m1 = new TMarker(10 - 1.42, 1.42, 20);
    m1->SetMarkerSize(1.5);
    m1->SetMarkerColor(kGreen);

    TMarker *m2 = new TMarker(15 - 0.98, 0.98, 20);
    m2->SetMarkerSize(1.5);
    m2->SetMarkerColor(kGreen);

    TMarker *m3 = new TMarker(20 - 0.756, 0.756, 20);
    m3->SetMarkerSize(1.5);
    m3->SetMarkerColor(kGreen);

    TMarker *m4 = new TMarker(25 - 0.64234, 0.64234, 20);
    m4->SetMarkerSize(1.5);
    m4->SetMarkerColor(kGreen);



    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("c%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

  // c1->Divide(4,4);

  for(Int_t i=0;i<16;i++) {
// Int_t i=0;
    // c1->cd(i+1);
    c_arr[i]->cd();
    cut.Form("flagLeft && X_L>0 && n20_L==%d",i);
    hDraw.Form("a20_L:X_L>>h%d(400,0,50,400,0,4)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    
ch->SetMarkerSize(1.);
    cut.Form("flagLeft && X_L>0 && nh3 && flagCent && n20_L==%d",i);
    ch->SetMarkerColor(kRed);
    ch->SetMarkerStyle(20);
    hDraw.Form("a20_L:X_L>>hred%d(200,0,50,200,0,4)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"same");


    ch->SetMarkerSize(1.5);
    cut.Form("flagLeft && X_L>0 && nh3 && nhe3 && flagCent && n20_L==%d",i);
    ch->SetMarkerColor(kMagenta);
    // ch->SetMarkerColor(kYellow);
    hDraw.Form("a20_L:X_L>>hred_he3_%d(200,0,50,200,0,4)",i);
    nCoi += ch->Draw(hDraw.Data(),cut.Data(),"same");


    ch1->SetMarkerStyle(20);
    ch1->SetMarkerSize(1.5);
    cut.Form("flagLeft && X_L>0 && nh3 && nhe3 && flagCent && n20_L==%d",i);
    ch1->SetMarkerColor(kBlack);
    // ch->SetMarkerColor(kYellow);
    hDraw.Form("a20_L:X_L>>hred_fon_he3_%d(200,0,50,200,0,4)",i);
    ch1->Draw(hDraw.Data(),cut.Data(),"same");


    c_arr[i]->Update();
    // c1->Update();

    m1->Draw("same");
    m2->Draw("same");
    m3->Draw("same");
    m4->Draw("same");

    // for(Int_t i=0;i<16;i++){
      cuthe3[i]->SetLineColor(kBlack);
      cuthe3[i]->Draw("same"); 
    // }


  // TLine *l1 = new TLine(10., 0, 10., 4);
  // l1->SetLineColor(kRed);
  // l1->SetLineWidth(3.);
  // l1->Draw("same");


  // TLine *l2 = new TLine(15., 0, 15., 4);
  // l2->SetLineColor(kRed);
  // l2->SetLineWidth(3.);
  // l2->Draw("same");

  // TLine *l3 = new TLine(20., 0, 20., 4);
  // l3->SetLineColor(kRed);
  // l3->SetLineWidth(3.);
  // l3->Draw("same");

  // TLine *l4 = new TLine(25., 0, 25., 4);
  // l4->SetLineColor(kRed);
  // l4->SetLineWidth(3.);
  // l4->Draw("same");


  }

  c_arr[0]->Print("/home/oem/Desktop/pics/de_E_all.pdf");
  c_arr[0]->Print("/home/oem/Desktop/pics/de_E_all.pdf[");
  c_arr[0]->Print("/home/oem/Desktop/pics/de_E_all.pdf");
  for(Int_t i=1;i<15;i++) {
    c_arr[i]->Print("/home/oem/Desktop/pics/de_E_all.pdf");
  }
  c_arr[15]->Print("/home/oem/Desktop/pics/de_E_all.pdf");
  c_arr[15]->Print("/home/oem/Desktop/pics/de_E_all.pdf]");



cout << nCoi << endl;
return;
  // c1->cd(1);
  
  // m1->Draw("same");
  // c1->cd(2);
  // ch->Draw("a20_L:X_L>>h3(200,0,50,200,0,3)","flagLeft==1 && X_L>0 && n20_L==1","col");
  


  // c1->cd(2);
  // ch->Draw("a20_L:X_L>>h2(200,0,50,200,0,3)","flagLeft==1 && X_L>0 && n20_L==2","col");
  
  // ch->SetMarkerColor(kRed);
  // ch->SetMarkerStyle(20);
  // ch->SetMarkerSize(1);
  // // ch->Draw("a20_L:X_L>>h2(300,0,30,300,0,3)","flagLeft==1 && nh3==1 && flagCent==1","same");
  // c1->Update();



  // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // c2->Divide(2,1);

  // c2->cd(2);
  // ch->Draw("a20_L:X_L>>h3(300,0,70,300,0,5)","flagLeft==1","col");
  // ch->SetMarkerColor(kRed);
  // ch->SetMarkerStyle(20);
  // ch->SetMarkerSize(1.);
  // ch->Draw("a20_L:X_L>>h4(300,0,70,300,0,5)","flagLeft==1 && nh3==1 && flagCent==1","same");
  // c2->Update();


  // TCanvas *c3 = new TCanvas("c3","",1800,1000);  

  // ch1->Draw("a20_L:X_L>>h1_05(300,0,70,300,0,5)","flagLeft==1","col");
  // ch1->SetMarkerColor(kGreen);
  // ch1->SetMarkerStyle(20);
  // ch1->SetMarkerSize(0.5);
  // ch1->Draw("a20_L:X_L>>h2_05(300,0,70,300,0,5)","flagLeft==1 && nh3==1 && flagCent==1","same");
  // c3->Update();

  // TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  // // c1->Divide(2,1);

  // // c1->cd(1);
  // ch1->Draw("a20_L:X_L+a20_L>>h3_05(300,0,70,300,0,5)","flagLeft==1","col");
  // ch1->SetMarkerColor(kGreen);
  // ch1->SetMarkerStyle(20);
  // ch1->SetMarkerSize(0.5);
  // ch1->Draw("a20_L:X_L+a20_L>>h4_05(300,0,70,300,0,5)","flagLeft==1 && nh3==1 && flagCent==1","same");
  // c4->Update();

  // TCanvas *c5 = new TCanvas("c5","",1800,1000);  

  // ch2->Draw("a20_L:X_L>>h1_10(300,0,70,300,0,5)","flagLeft==1","col");
  // ch2->SetMarkerColor(kGreen);
  // ch2->SetMarkerStyle(20);
  // ch2->SetMarkerSize(0.5);
  // ch2->Draw("a20_L:X_L>>h2_10(300,0,70,300,0,5)","flagLeft==1 && nh3==1 && flagCent==1","same");
  // c5->Update();

  // TCanvas *c6 = new TCanvas("c6","",1800,1000);  

  // ch2->Draw("a20_L:X_L+a20_L>>h3_10(300,0,70,300,0,5)","flagLeft==1","col");
  // ch2->SetMarkerColor(kGreen);
  // ch2->SetMarkerStyle(20);
  // ch2->SetMarkerSize(0.5);
  // ch2->Draw("a20_L:X_L+a20_L>>h4_10(300,0,70,300,0,5)","flagLeft==1 && nh3==1 && flagCent==1","same");
  // c6->Update();





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

  // c1->cd(2);
  // ch->Draw("a20_L:X_L>>h1-2(300,0,70,300,0,5)","flagLeft==1","");
  // c1->Update();   
 
  // ch->SetMarkerColor(kGreen);
  // ch->SetMarkerStyle(20);
  // ch->SetMarkerSize(0.5);
  // ch->Draw("a20_L:X_L>>h1-2_3(300,0,70,300,0,5)","nh3==1 && flagLeft==1","same");
  // c1->Update(); 

  // c1->Print("/home/user/Desktop/pictures/de-Eafter_all.png");
}