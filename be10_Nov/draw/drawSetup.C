TLine *lSide[16];
TLine *lCent[4];
TLine *lHol[4];

void setLinesBorders();

void drawSetup() {
  // gStyle->SetOptStat(0);

  setLinesBorders();

  TString hDraw,hCut;
  TString cutTriangle("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*4/7.))");
  TString cutTriangle2("(eh3_CM*1000>(1000*(mh7-4*0.939565-2.808920)*2/7.))");

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_mm_secondVol.root");
  ch1->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_firstVol_mm.root");


  TCanvas *c_Profile = new TCanvas("c_Profile","title",1000,1000);
  c_Profile->Divide(2,2);

  c_Profile->cd(1);

  ch1->SetMarkerStyle(20);
  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " &&  (fXt*fXt + fYt*fYt)<13*13";
  cout << ch1->Draw("y1c:x1c >> mwpc1Profile(32,-20,20,32,-20,20)",hCut.Data(),"col") << endl;
  c_Profile->Update();


  c_Profile->cd(2);

  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " &&  (fXt*fXt + fYt*fYt)<13*13";
  ch1->Draw("y2c:x2c >> mwpc2Profile(32,-20,20,32,-20,20)",hCut.Data(),"col");
  c_Profile->Update();



  c_Profile->cd(3);

  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " &&  (fXt*fXt + fYt*fYt)<13*13";
  ch1->Draw("fYt:fXt >> targetProfile(64,-20,20,64,-20,20)",hCut.Data(),"col");
  c_Profile->Update();



  c_Profile->cd(4);
  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " &&  (fXt*fXt + fYt*fYt)<13*13";
  ch1->Draw("yCt:xCt >> detProfile(32,-32,32,32,-32,32)",hCut.Data(),"col");
  c_Profile->Update();


return;
  TCanvas *c_Frames = new TCanvas("c_Frames","title",1800,600);
  c_Frames->Divide(3,1);

  c_Frames->cd(1);

  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  ch1->Draw("frame1Y:frame1X >> frame1Profile(32,-32,32,32,-32,32)",hCut.Data(),"");
  c_Frames->Update();

  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) ) && ");
  hCut += cutTriangle2;
  ch1->SetMarkerColor(kRed);
  ch1->Draw("frame1Y:frame1X",hCut.Data(),"same");
  c_Frames->Update();


  c_Frames->cd(2);

  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  ch1->Draw("frame2Y:frame2X >> frame2Profile(32,-32,32,32,-32,32)",hCut.Data(),"");
  c_Frames->Update();

  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) ) && ");
  hCut += cutTriangle2;
  ch1->SetMarkerColor(kRed);
  ch1->Draw("frame2Y:frame2X",hCut.Data(),"same");
  c_Frames->Update();

  c_Frames->cd(3);

  ch1->SetMarkerColor(kBlack);
  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  ch1->Draw("frame3Y:frame3X >> frame3Profile(32,-32,32,32,-32,32)",hCut.Data(),"");
  c_Frames->Update();

  hCut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) ) && ");
  hCut += cutTriangle2;
  ch1->SetMarkerColor(kRed);
  ch1->Draw("frame2Y:frame2X",hCut.Data(),"same");
  c_Frames->Update();

return;

  TCanvas *setupCan = new TCanvas("setupCan","reconstruction scheme",1000,1000);
  setupCan->cd();
  ch1->SetMarkerStyle(20);

  TH2F *hScale = new TH2F("hScale","setup scheme",10000,-80,80,10000,-80,80);
  hScale->Draw();

  for(Int_t i=0;i<16;i++) {
    lSide[i]->SetLineColor(kRed);
    lSide[i]->SetLineWidth(2);
    lSide[i]->Draw("same");
  }
  setupCan->Update();
  for(Int_t i=0;i<4;i++) {
    lCent[i]->SetLineColor(kGreen);
    lCent[i]->SetLineWidth(4);
    lCent[i]->Draw("same");

    lHol[i]->SetLineColor(kBlack);
    lHol[i]->SetLineWidth(4);
    lHol[i]->Draw("same");
  }
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y1t:x1t >> distr1");
  hCut.Form("nhe3_1 && nh3 && y1t!=0 && x1t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += " && " + cutTriangle;
  hCut += " && flag1 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();


  ch1->SetMarkerColor(kMagenta);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y1t:x1t");
  hCut.Form("nhe3_1 && nh3 && y1t!=0 && x1t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += " && " + cutTriangle;
  hCut += " && flag1 && flagCent";
  hCut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y2t:x2t >> distr2");
  hCut.Form("nhe3_2 && nh3 && y2t!=0 && x2t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && " + cutTriangle;
  hCut += " && flag2 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kMagenta);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y2t:x2t >> distr2Low");
  hCut.Form("nhe3_2 && nh3 && y2t!=0 && x2t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3";
  hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && " + cutTriangle;
  hCut += " && flag2 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y3t:x3t >> distr3");
  hCut.Form("nhe3_3 && nh3 && y3t!=0 && x3t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && " + cutTriangle;
  hCut += " && flag3 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kMagenta);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y3t:x3t >> distr3Low");
  hCut.Form("nhe3_3 && nh3 && y3t!=0 && x3t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && " + cutTriangle;
  hCut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3";
  hCut += " && flag3 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y4t:x4t >> distr4");
  hCut.Form("nhe3_4 && nh3 && y4t!=0 && x4t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && " + cutTriangle;
  hCut += " && flag4 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kMagenta);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y4t:x4t >> distr4Low");
  hCut.Form("nhe3_4 && nh3 && y4t!=0 && x4t!=0");
  // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && " + cutTriangle;
  hCut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3";
  hCut += " && flag4 && flagCent";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();


  ch1->SetMarkerColor(kGreen);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("yCt:xCt >> distrC");
  hCut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " && " + cutTriangle;


  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kBlue);
  ch1->SetMarkerSize(1.);
  hDraw.Form("yCt:xCt");
  hCut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " && " + cutTriangle;
  hCut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kBlack);
  ch1->SetMarkerSize(1.);
  hDraw.Form("yCt:xCt");
  hCut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
  hCut += " && " + cutTriangle;
  hCut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  // setupCan->Print("/home/ivan/Desktop/tmp/setupScheme4.pdf");

return;




  // ch1->SetMarkerColor(kGreen);
  // ch1->SetMarkerSize(0.8);
  // hDraw.Form("yCt-1:xCt-1 >> distrC");
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  // hCut += " && nX_C>-1 && nY_C>-1";
  // // hCut += " && " + cutTriangle;

  // cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  // setupCan->Update();

  // ch1->SetMarkerColor(kBlue);
  // ch1->SetMarkerSize(1.);
  // hDraw.Form("yCt-1:xCt-1 >> distrCLow");
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  // hCut += " && nX_C>-1 && nY_C>-1";
  // // hCut += " && " + cutTriangle;
  // hCut += " && 1000*(mh7-4*0.939565-2.808920)< 3.8";

  // cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  // setupCan->Update();

  // setupCan->Print("/home/ivan/Desktop/tmp/setupScheme.png");


  // TH1F *htemp;

  // TCanvas *angleCan = new TCanvas("angleCan","lab angles",1800,1000);
  // angleCan->Divide(2,1);

  // angleCan->cd(1);
  // ch1->SetLineColor(kBlack);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  // hCut += " && nX_C>-1 && nY_C>-1";
  // // hCut += " && " + cutTriangle;
  // hDraw.Form("thetahe3 >> distr3he(25,0,25)");
  // ch1->Draw(hDraw.Data(),hCut.Data(),"");

  // htemp = (TH1F*)gPad->GetPrimitive("distr3he");
  // htemp->GetXaxis()->SetTitle("3He lab angle, deg");
  // htemp->GetYaxis()->SetTitle("counts/1 deg ");
  // htemp->GetXaxis()->CenterTitle();
  // htemp->GetYaxis()->CenterTitle();

  // ch1->SetLineColor(kRed);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  // hCut += " && nX_C>-1 && nY_C>-1";
  // // hCut += " && " + cutTriangle;
  // hCut += " && 1000*(mh7-4*0.939565-2.808920)< 3.8";
  // hDraw.Form("thetahe3 >> distr3heCut(25,0,25)");
  // ch1->Draw(hDraw.Data(),hCut.Data(),"same");

  // angleCan->Update();

  // angleCan->cd(2);
  // ch1->SetLineColor(kBlack);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  // hCut += " && nX_C>-1 && nY_C>-1";
  // // hCut += " && " + cutTriangle;
  // hDraw.Form("thetah3 >> distr3h(20,0,10)");
  // ch1->Draw(hDraw.Data(),hCut.Data(),"");

  // htemp = (TH1F*)gPad->GetPrimitive("distr3h");
  // htemp->GetXaxis()->SetTitle("3H lab angle, deg");
  // htemp->GetYaxis()->SetTitle("counts/0.5 deg ");
  // htemp->GetXaxis()->CenterTitle();
  // htemp->GetYaxis()->CenterTitle();

  // ch1->SetLineColor(kRed);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
  // hCut += " && nX_C>-1 && nY_C>-1";
  // // hCut += " && " + cutTriangle;
  // hCut += " && 1000*(mh7-4*0.939565-2.808920)< 3.8";
  // hDraw.Form("thetah3 >> distr3hCut(20,0,10)");
  // ch1->Draw(hDraw.Data(),hCut.Data(),"same");

  // angleCan->Update();

  // angleCan->Print("/home/ivan/Desktop/tmp/anglesDist.png");

  // TCanvas *canMM = new TCanvas("canMM","lab angles",1800,1000);
  // canMM->Divide(2,1);

  // canMM->cd(1);
  // ch1->SetLineColor(kBlack);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && " + cutTriangle;
  // hCut += " && nX_C>-1 && nY_C>-1";
  // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm(30,-5,25)",hCut.Data(),"");
  // canMM->Update();

  // ch1->SetLineColor(kRed);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && " + cutTriangle;
  // hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && 1000*(mh7-4*0.939565-2.808920)< 3.8";
  // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mmCut(30,-5,25)",hCut.Data(),"same");
  // canMM->Update();


  // canMM->cd(2);
  // ch1->SetMarkerColor(kBlack);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && " + cutTriangle;
  // hCut += " && nX_C>-1 && nY_C>-1";
  // ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle(10000,-5,20,10000,0,12)",hCut.Data(),"");
  // canMM->Update();

  // ch1->SetMarkerColor(kRed);
  // hCut.Form("((flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4)) && nh3 && flagCent");
  // // hCut += " && " + cutTriangle;
  // hCut += " && nX_C>-1 && nY_C>-1";
  // hCut += " && 1000*(mh7-4*0.939565-2.808920)< 3.8";
  // ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangleCut(10000,-5,20,10000,0,12)",hCut.Data(),"same");
  // canMM->Update();
  
  // canMM->Print("/home/ivan/Desktop/tmp/mm_low.png");


}

void setLinesBorders() {

  Float_t xOffset = 1.53;
  Float_t yOffset = 2.24;
  // Float_t zOffset = 1.17876;

  lSide[0] = new TLine(-21.3+xOffset,-4.2+yOffset,-71.3+xOffset,-4.2+yOffset);
  lSide[1] = new TLine(-71.3+xOffset,-4.2+yOffset,-71.3+xOffset,45.8+yOffset);
  lSide[2] = new TLine(-71.3+xOffset,45.8+yOffset,-21.3+xOffset,45.8+yOffset);
  lSide[3] = new TLine(-21.3+xOffset,45.8+yOffset,-21.3+xOffset,-4.2+yOffset);

  lSide[4] = new TLine(4.2+xOffset,-21.3+yOffset,4.2+xOffset,-71.3+yOffset);
  lSide[5] = new TLine(4.2+xOffset,-71.3+yOffset,-45.8+xOffset,-71.3+yOffset);
  lSide[6] = new TLine(-45.8+xOffset,-71.3+yOffset,-45.8+xOffset,-21.3+yOffset);
  lSide[7] = new TLine(-45.8+xOffset,-21.3+yOffset,4.2+xOffset,-21.3+yOffset);

  lSide[8] = new TLine(21.3+xOffset,4.2+yOffset,71.3+xOffset,4.2+yOffset);
  lSide[9] = new TLine(71.3+xOffset,4.2+yOffset,71.3+xOffset,-45.8+yOffset);
  lSide[10] = new TLine(71.3+xOffset,-45.8+yOffset,21.3+xOffset,-45.8+yOffset);
  lSide[11] = new TLine(21.3+xOffset,-45.8+yOffset,21.3+xOffset,4.2+yOffset);

  lSide[12] = new TLine(-4.2+xOffset,21.3+yOffset,45.8+xOffset,21.3+yOffset);
  lSide[13] = new TLine(45.8+xOffset,21.3+yOffset,45.8+xOffset,71.3+yOffset);
  lSide[14] = new TLine(45.8+xOffset,71.3+yOffset,-4.2+xOffset,71.3+yOffset);
  lSide[15] = new TLine(-4.2+xOffset,71.3+yOffset,-4.2+xOffset,21.3+yOffset);

  lCent[0] = new TLine(-32,-32,32,-32);
  lCent[1] = new TLine(32,-32,32,32);
  lCent[2] = new TLine(32,32,-32,32);
  lCent[3] = new TLine(-32,32,-32,-32);

  lHol[0] = new TLine(-12.5,-12.5,12.5,-12.5);
  lHol[1] = new TLine(12.5,-12.5,12.5,12.5);
  lHol[2] = new TLine(12.5,12.5,-12.5,12.5);
  lHol[3] = new TLine(-12.5,12.5,-12.5,-12.5);



}