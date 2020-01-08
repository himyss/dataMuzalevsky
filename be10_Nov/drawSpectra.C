void readCuts();

TCutG *cutCsI[16],*cut3h[16];
TCutG *cuthe3[16];

void drawSpectra() {
  
  // readCuts();

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1906/analysed/be_10_reco.root");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  // ch->SetMarkerStyle(20);

  // TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // ch->Draw("a20_1_un:a1_1>>id1(500,1.,40,250,0.1,5)","flag1","col");
  // ch->Draw("a20_1_un:a1_1>>id1_he3(500,1.,40,250,0.1,5)","flag1 && nhe3_1","same");
  // c1->Print("/home/oem/Desktop/de_E_1.pdf");

  // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // ch->Draw("a20_2_un:a1_2>>id2(500,1.,40,250,0.1,5)","flag2","col");
  // ch->Draw("a20_2_un:a1_2>>id2_he3(500,1.,40,250,0.1,5)","flag2 && nhe3_2","same");
  // c2->Print("/home/oem/Desktop/de_E_2.pdf");

  // TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  // ch->Draw("a20_3_un:a1_3>>id3(500,1.,40,250,0.1,5)","flag3","col");
  // ch->Draw("a20_3_un:a1_3>>id3_he3(500,1.,40,250,0.1,5)","flag3 && nhe3_3","same");
  // c3->Print("/home/oem/Desktop/de_E_3.pdf");

  // TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  // ch->Draw("a20_4_un:a1_4>>id4(500,1.,40,250,0.1,5)","flag4","col");
  // ch->Draw("a20_4_un:a1_4>>idhe3_4(500,1.,40,250,0.1,5)","flag4 && nhe3_4","same");
  // c4->Print("/home/oem/Desktop/de_E_4.pdf");


  TCanvas *cHe3 = new TCanvas("cHe3","spectra",1800,1000);
  cHe3->Divide(2,2);

  cHe3->cd(1);
  ch->Draw("e_1 >> s1(200,4,30)","flag1 && nhe3_1","");

  cHe3->cd(2);
  ch->Draw("e_2>> s2(200,4,30)","flag2 && nhe3_2","");

  cHe3->cd(3);
  ch->Draw("e_3>> s3(200,4,30)","flag3 && nhe3_3","");

  cHe3->cd(4);
  ch->Draw("e_4>> s4(200,4,30)","flag4 && nhe3_4","");

  cHe3->Print("/home/oem/Desktop/spectra.pdf");

// // return;
 //  TString canName,cut,hDraw;
 //  TCanvas *c_arr[16];
 //  for(Int_t i=0;i<16;i++){
 //    canName.Form("c%d",i+1);
 //    c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
 //  }

 //  for(Int_t i=0;i<16;i++) {
 // // { Int_t i =14;
 //    c_arr[i]->cd();
 //    // c1->cd(i+1);
 //    ch->SetMarkerSize(0.5);
 //    ch->SetMarkerColor(kBlack);
 //    cut.Form("nCsI==%d",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,50)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"col");
 //    c_arr[i]->Update();
 //  }

 //  c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
 //  c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf[");
 //  c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
 //  for(Int_t i=1;i<15;i++) {
 //    c_arr[i]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
 //  }
 //  c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
 //  c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf]");

 //  TString canName,cut,hDraw;
 //  TCanvas *c_arr[16];
 //  for(Int_t i=0;i<16;i++){
 //    canName.Form("c%d",i+1);
 //    c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
 //  }

 //  for(Int_t i=0;i<16;i++) {
 // // {Int_t i = 0;
 //    c_arr[i]->cd();

 //    cut.Form("n20_1==%d && flag1",i);
 //    hDraw.Form("a20_1:a1_1 >>h%d(500,0.5,40,250,0.1,5)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"col");

 //    ch->SetMarkerStyle(20);
 //    ch->SetMarkerSize(0.9);
 //    ch->SetMarkerColor(kGreen);
 //    cut.Form("n20_1==%d && flag1 && nh3",i);
 //    hDraw.Form("a20_1:a1_1 >>hred%d(500,0.5.,40,250,0.1,5)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"same");

 //    ch->SetMarkerSize(1.3);
 //    ch->SetMarkerColor(kRed);
 //    cut.Form("n20_1==%d && flag1 && nh3 && nhe3_1",i);
 //    hDraw.Form("a20_1:a1_1 >>hcoin%d(500,0.5,40,250,0.1,5)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"same");

 //    cuthe3[i]->Draw("same");

 //    c_arr[i]->Update();
 //  }

}