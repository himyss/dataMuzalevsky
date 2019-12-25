void drawID() {
  
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1906/analysed/be10_ct_1-4_cut.root");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  TCanvas *cBeam = new TCanvas("cBeam","",1800,1000);  
  cBeam->Divide(2,1);

  cBeam->cd(1);
  ch->Draw("F5.:tF5-tF3 >> deToF5(400,30,130,14000,2000,16000)","","col");
  cBeam->Update();

  ch->SetMarkerColor(kBlack);
  cBeam->cd(2);
  ch->Draw("F5.:tF5-tF3 >> deToF5_black(400,30,130,14000,2000,16000)","","");
  cBeam->Update();

  ch->SetMarkerColor(kRed);
  ch->Draw("F5.:tF5-tF3 >> deToF5_red(400,30,130,14000,2000,16000)","flagToF","same");
  cBeam->Update();

  cBeam->Print("/home/oem/Desktop/pics/exp1904/dE_ToF.png");

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  ch->Draw("a20_1:a1_1>>id1(500,1.,50,500,0.1,12)","flag1 && flagToF","col");
  c1->Print("/home/oem/Desktop/pics/exp1904/de_E_1.pdf");

  TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  ch->Draw("a20_2:a1_2>>id2(500,1.,50,500,0.1,12)","flag2 && flagToF","col");
  c2->Print("/home/oem/Desktop/pics/exp1904/de_E_2.pdf");

  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  ch->Draw("a20_3:a1_3>>id3(500,1.,50,500,0.1,12)","flag3 && flagToF","col");
  c3->Print("/home/oem/Desktop/pics/exp1904/de_E_3.pdf");

  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  ch->Draw("a20_4:a1_4>>id4(500,1.,50,500,0.1,12)","flag4 && flagToF","col");
  c4->Print("/home/oem/Desktop/pics/exp1904/de_E_4.pdf");

// return;
  TString canName,cut,hDraw;
  TCanvas *c_arr[16];
  for(Int_t i=0;i<16;i++){
    canName.Form("c%d",i+1);
    c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
  }

  for(Int_t i=0;i<16;i++) {
 // { Int_t i =14;
    c_arr[i]->cd();
    // c1->cd(i+1);
    ch->SetMarkerSize(0.5);
    ch->SetMarkerColor(kBlack);
    cut.Form("nCsI==%d && flagToF",i);
    // hDraw.Form("a20_4:a1_4>>h%d(500,0.3,50,500,0.3,5)",i);
    hDraw.Form("X_C:aCsI>>CentId_%d(500,0,4048,500,1,100)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
  }

  c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf[");
  c_arr[0]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  for(Int_t i=1;i<15;i++) {
    c_arr[i]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  }
  c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf");
  c_arr[15]->Print("/home/oem/Desktop/pics/exp1904/de_E_cent.pdf]");


  // c1->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf");
  // c1->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf[");
  // c1->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf");
  // c2->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf");
  // c3->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf");
  // c4->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf");
  // c4->Print("/home/oem/Desktop/pics/exp1904/de_E.pdf]");


  // c1->Print("/home/oem/Desktop/pics/exp1904/de_E1.png");
  // c2->Print("/home/oem/Desktop/pics/exp1904/de_E2.png");
  // c3->Print("/home/oem/Desktop/pics/exp1904/de_E3.png");
  // c4->Print("/home/oem/Desktop/pics/exp1904/de_E4.png");


  return;
}