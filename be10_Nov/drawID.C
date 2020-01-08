void readCuts();

TCutG *cutCsI[16],*cut3h[16];
TCutG *cuthe3[16];

TCutG *cut1_he3,*cut2_he3,*cut3_he3,*cut4_he3;

void drawID() {
  
  readCuts();

  cut4_he3->SetLineWidth(2);

  cut3_he3->SetLineWidth(2);

  cut2_he3->SetLineWidth(2);

  cut1_he3->SetLineWidth(2);

  



  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1906/analysed/be_10_cut.root");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  ch->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  ch->Draw("a20_1:a1_1>>id1(500,0.1,40,250,0.1,5)","","col");
  ch->Draw("a20_1:a1_1>>id1_he3(500,1.,40,250,0.1,5)","flag1 && nhe3_1","same");
  cut1_he3->Draw("same");
  cut1_he3->SetLineColor(kRed);
  c1->Print("/home/oem/Desktop/pics/exp1904/de_E_1.pdf");

  TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  ch->Draw("a20_2:a1_2>>id2(500,0.1,40,250,0.1,5)","","col");
  ch->Draw("a20_2:a1_2>>id2_he3(500,1.,40,250,0.1,5)","flag2 && nhe3_2","same");
  c2->Print("/home/oem/Desktop/pics/exp1904/de_E_2.pdf");
  cut2_he3->Draw("same");
  cut2_he3->SetLineColor(kRed);


  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  ch->Draw("a20_3:a1_3>>id3(500,0.1,40,250,0.1,5)","","col");
  ch->Draw("a20_3:a1_3>>id3_he3(500,1.,40,250,0.1,5)","flag3 && nhe3_3","same");
  c3->Print("/home/oem/Desktop/pics/exp1904/de_E_3.pdf");
  cut3_he3->Draw("same");
  cut3_he3->SetLineColor(kRed);


  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  ch->Draw("a20_4:a1_4>>id4(500,0.1,40,250,0.1,5)","","col");
  ch->Draw("a20_4:a1_4>>id4_he(500,1.,40,250,0.1,5)","nhe3_4","same");  
  c4->Print("/home/oem/Desktop/pics/exp1904/de_E_4.pdf");
  cut4_he3->Draw("same");
  cut4_he3->SetLineColor(kRed);

// return;
// // return;
//   TString canName,cut,hDraw;
//   TCanvas *c_arr[16];
//   for(Int_t i=0;i<16;i++){
//     canName.Form("c%d",i+1);
//     c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
//   }
// // return;
//  //  c1->Divide(4,4);
//   for(Int_t i=0;i<16;i++) {
//  // { Int_t i =14;
//     c_arr[i]->cd();
//     // c1->cd(i+1);

//     ch->SetMarkerStyle(1);    
//     ch->SetMarkerSize(0.8);
//     ch->SetMarkerColor(kBlack);
//     cut.Form("nCsI==%d && flagCent",i);
//     // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
//     hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,100)",i);
//     ch->Draw(hDraw.Data(),cut.Data(),"col");

//     ch->SetMarkerStyle(20);
//     ch->SetMarkerColor(kRed);
//     cut.Form("nCsI==%d && flagCent && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
//     // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
//     hDraw.Form("X_C:aCsI>>CentCoin_%d(500,0,8096,500,1,100)",i);
//     ch->Draw(hDraw.Data(),cut.Data(),"same");

//     // c1->Update();
//     c_arr[i]->Update();
//   }


 //  c1->Divide(2,2);
 // // { Int_t i =14;
 //    // c_arr[i]->cd();
 //    c1->cd(1);

 //    Int_t i =4;
 //    ch->SetMarkerStyle(1);    
 //    ch->SetMarkerSize(0.8);
 //    ch->SetMarkerColor(kBlack);
 //    cut.Form("nCsI==%d && flagCent",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"");

 //    ch->SetMarkerStyle(20);
 //    ch->SetMarkerColor(kRed);
 //    cut.Form("nCsI==%d && flagCent && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentCoin_%d(500,0,8096,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"same");


 //    c1->cd(2);
 //     i = 6;
 //    ch->SetMarkerStyle(1);    
 //    ch->SetMarkerSize(0.8);
 //    ch->SetMarkerColor(kBlack);
 //    cut.Form("nCsI==%d && flagCent",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"");

 //    ch->SetMarkerStyle(20);
 //    ch->SetMarkerColor(kRed);
 //    cut.Form("nCsI==%d && flagCent && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentCoin_%d(500,0,8096,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"same");


 //    c1->cd(3);
 //     i = 7;
 //    ch->SetMarkerStyle(1);    
 //    ch->SetMarkerSize(0.8);
 //    ch->SetMarkerColor(kBlack);
 //    cut.Form("nCsI==%d && flagCent",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"");

 //    ch->SetMarkerStyle(20);
 //    ch->SetMarkerColor(kRed);
 //    cut.Form("nCsI==%d && flagCent && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentCoin_%d(500,0,8096,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"same");


 //    c1->cd(4);

 //     i = 8;
 //    ch->SetMarkerStyle(1);    
 //    ch->SetMarkerSize(0.8);
 //    ch->SetMarkerColor(kBlack);
 //    cut.Form("nCsI==%d && flagCent",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"");

 //    ch->SetMarkerStyle(20);
 //    ch->SetMarkerColor(kRed);
 //    cut.Form("nCsI==%d && flagCent && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
 //    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
 //    hDraw.Form("X_C:aCsI>>CentCoin_%d(500,0,8096,500,1,100)",i);
 //    ch->Draw(hDraw.Data(),cut.Data(),"same");

  // c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  // c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf[");
  // c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  // for(Int_t i=1;i<15;i++) {
  //   c_arr[i]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  // }
  // c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  // c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf]");

  // TString canName,cut,hDraw;
  // TCanvas *c_arr[16];
  // for(Int_t i=0;i<16;i++){
  //   canName.Form("c%d",i+1);
  //   c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
  // }


  // c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_1_all.pdf");
  // c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_1_all.pdf[");
  // c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_1_all.pdf");
  // for(Int_t i=1;i<15;i++) {
  //   c_arr[i]->Print("/home/oem/Desktop/pics/exp1904/de_E_1_all.pdf");
  // }
  // c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_1_all.pdf");
  // c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_1_all.pdf]");


  return;
}

void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/C_T/triton/h3_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

 cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_1.root");
  f = new TFile(cutName.Data());
  cut1_he3 = (TCutG*)f->Get("CUTG");
  if (!cut1_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_2.root");
  f = new TFile(cutName.Data());
  cut2_he3 = (TCutG*)f->Get("CUTG");
  if (!cut2_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_3.root");
  f = new TFile(cutName.Data());
  cut3_he3 = (TCutG*)f->Get("CUTG");
  if (!cut3_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_4.root");
  f = new TFile(cutName.Data());
  cut4_he3 = (TCutG*)f->Get("CUTG");
  if (!cut4_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

}
