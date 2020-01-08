TLine *lSide[16];
TLine *lCent[4];
TLine *lHol[4];

void setLinesBorders();

void drawSetup() {
  gStyle->SetOptStat(0);

  setLinesBorders();

  TString hDraw,hCut;
  // TString cutTriangle("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/be10_ct_thick_mm_515.root");

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
  // for(Int_t i=0;i<4;i++) {
  //   lCent[i]->SetLineColor(kGreen);
  //   lCent[i]->SetLineWidth(4);
  //   lCent[i]->Draw("same");

  //   lHol[i]->SetLineColor(kBlack);
  //   lHol[i]->SetLineWidth(4);
  //   lHol[i]->Draw("same");
  // }
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y1t:x1t >> distr1");
  hCut.Form("trigger==2 && (nhe3_1 && e_1<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<5");

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kGreen);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y1t:x1t >> distr1Low");
  hCut += (" && 1000*(mh7-8.406868788)<2.2");

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y2t:x2t >> distr2");
  hCut.Form("trigger==3 && (nhe3_2 && e_2<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<5");

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kGreen);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y2t:x2t >> distr2Low");
  hCut += (" && 1000*(mh7-8.406868788)<2.2");
  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();


  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y3t:x3t >> distr3");
  hCut.Form("trigger==4 && (nhe3_3 && e_3<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<5");

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kGreen);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y3t:x3t >> distr3Low");
  hCut += " && 1000*(mh7-8.406868788)< 2.2";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kRed);
  ch1->SetMarkerSize(0.8);
  hDraw.Form("y4t:x4t >> distr4");
  hCut.Form("trigger==5 && (nhe3_4 && e_4<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<5");

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  ch1->SetMarkerColor(kGreen);
  ch1->SetMarkerSize(1.);
  hDraw.Form("y4t:x4t >> distr4Low");
  hCut += " && 1000*(mh7-8.406868788)< 2.2";

  cout << ch1->Draw(hDraw.Data(),hCut.Data(),"same") << endl;
  setupCan->Update();

  setupCan->Print("/home/ivan/Desktop/scheme.png");

  TH1F *htemp;

  TCanvas *angleCan = new TCanvas("angleCan","lab angles",1800,1000);
  angleCan->Divide(2,2);

  angleCan->cd(1);

  ch1->SetLineColor(kGreen);
  hCut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += (" && 1000*(mh7-8.406868788)<2.2");

  hDraw.Form("angle_he3_he8 >> distr3he_second(20,5,25)");
  ch1->Draw(hDraw.Data(),hCut.Data(),"");

  htemp = (TH1F*)gPad->GetPrimitive("distr3he_second");
  htemp->GetXaxis()->SetTitle("3He lab angle, deg");
  htemp->GetYaxis()->SetTitle("counts/1 deg ");
  htemp->GetXaxis()->CenterTitle();
  htemp->GetYaxis()->CenterTitle();

  ch1->SetLineColor(kRed);
  hCut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += (" && 1000*(mh7-8.406868788)<5");
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hDraw.Form("angle_he3_he8 >> distr3heCut(20,5,25)");
  ch1->Draw(hDraw.Data(),hCut.Data(),"same");
  angleCan->Update();


  angleCan->cd(2);

  ch1->SetLineColor(kGreen);
  hCut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += (" && 1000*(mh7-8.406868788)<2.2");

  hDraw.Form("180-thetahe3CM >> distr3he_secondCM(20,0,20)");
  ch1->Draw(hDraw.Data(),hCut.Data(),"");

  htemp = (TH1F*)gPad->GetPrimitive("distr3he_secondCM");
  htemp->GetXaxis()->SetTitle("3He lab angle, deg");
  htemp->GetYaxis()->SetTitle("counts/1 deg ");
  htemp->GetXaxis()->CenterTitle();
  htemp->GetYaxis()->CenterTitle();

  ch1->SetLineColor(kRed);
  hCut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
  hCut += " && nX_C>-1 && nY_C>-1";  
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hCut += (" && 1000*(mh7-8.406868788)<5");
  hDraw.Form("180-thetahe3CM >> distr3heCutCM(20,0,20)");
  ch1->Draw(hDraw.Data(),hCut.Data(),"same");
  angleCan->Update();


  angleCan->cd(3);
  ch1->SetMarkerStyle(7);

  ch1->SetMarkerColor(kGreen);
  hCut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += (" && 1000*(mh7-8.406868788)<2.2");

  hDraw.Form("180-thetahe3CM:1000*(mh7-8.406868788) >> theta_MMcorr_low(70,-5,30,20,0,20)");
  ch1->Draw(hDraw.Data(),hCut.Data(),"");


  ch1->SetMarkerColor(kRed);
  hCut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
  hCut += " && nX_C>-1 && nY_C>-1";
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hCut += (" && 1000*(mh7-8.406868788)<5");

  hDraw.Form("180-thetahe3CM:1000*(mh7-8.406868788) >> theta_MMcorr_lowSecond(70,-5,30,20,0,20)");
  ch1->Draw(hDraw.Data(),hCut.Data(),"same");

  angleCan->Print("/home/ivan/Desktop/angles.png");

  TCanvas *c1 = new TCanvas("c1","",1800,1000);
  c1->Divide(2,2);
  

  c1->cd(1);
  ch1->SetLineColor(kGreen);
  hCut.Form("trigger==2 && (nhe3_1 && e_1<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<2.2");
  ch1->Draw("1000*(mh7-8.406868788) >> h1(70,-5,30)",hCut.Data(),"");
  c1->Update();

  ch1->SetLineColor(kRed);
  hCut.Form("trigger==2 && (nhe3_1 && e_1<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hCut += (" && 1000*(mh7-8.406868788)<5");  
  ch1->Draw("1000*(mh7-8.406868788) >> h1_low(70,-5,30)",hCut.Data(),"same");
  c1->Update();


  c1->cd(2);
  ch1->SetLineColor(kGreen);
  hCut.Form("trigger==3 && (nhe3_2 && e_2<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<2.2");
  ch1->Draw("1000*(mh7-8.406868788) >> h2(70,-5,30)",hCut.Data(),"");
  c1->Update();

  ch1->SetLineColor(kRed);
  hCut.Form("trigger==3 && (nhe3_2 && e_2<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hCut += (" && 1000*(mh7-8.406868788)<5");
  ch1->Draw("1000*(mh7-8.406868788) >> h2_low(70,-5,30)",hCut.Data(),"same");
  c1->Update();


  c1->cd(3);
  ch1->SetLineColor(kGreen);
  hCut.Form("trigger==4 && (nhe3_3 && e_3<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<2.2");
  ch1->Draw("1000*(mh7-8.406868788) >> h3(70,-5,30)",hCut.Data(),"");
  c1->Update();

  ch1->SetLineColor(kRed);
  hCut.Form("trigger==4 && (nhe3_3 && e_3<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hCut += (" && 1000*(mh7-8.406868788)<5");
  ch1->Draw("1000*(mh7-8.406868788) >> h3_low(70,-5,30)",hCut.Data(),"same");
  c1->Update();


  c1->cd(4);
  ch1->SetLineColor(kGreen);
  hCut.Form("trigger==5 && (nhe3_4 && e_4<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)<2.2");
  ch1->Draw("1000*(mh7-8.406868788) >> h4(70,-5,30)",hCut.Data(),"");
  c1->Update();

  ch1->SetLineColor(kRed);
  hCut.Form("trigger==5 && (nhe3_4 && e_4<25) && flagCent");
  hCut += (" && 1000*(mh7-8.406868788)>2.2");
  hCut += (" && 1000*(mh7-8.406868788)<5");
  ch1->Draw("1000*(mh7-8.406868788) >> h4_low(70,-5,30)",hCut.Data(),"same");
  c1->Update();

  c1->Print("/home/ivan/Desktop/mm.png");

}

void setLinesBorders() {

  lSide[0] = new TLine(-21.3,-4.2,-71.3,-4.2);
  lSide[1] = new TLine(-71.3,-4.2,-71.3,45.8);
  lSide[2] = new TLine(-71.3,45.8,-21.3,45.8);
  lSide[3] = new TLine(-21.3,45.8,-21.3,-4.2);

  lSide[4] = new TLine(4.2,-21.3,4.2,-71.3);
  lSide[5] = new TLine(4.2,-71.3,-45.8,-71.3);
  lSide[6] = new TLine(-45.8,-71.3,-45.8,-21.3);
  lSide[7] = new TLine(-45.8,-21.3,4.2,-21.3);

  lSide[8] = new TLine(21.3,4.2,71.3,4.2);
  lSide[9] = new TLine(71.3,4.2,71.3,-45.8);
  lSide[10] = new TLine(71.3,-45.8,21.3,-45.8);
  lSide[11] = new TLine(21.3,-45.8,21.3,4.2);

  lSide[12] = new TLine(-4.2,21.3,45.8,21.3);
  lSide[13] = new TLine(45.8,21.3,45.8,71.3);
  lSide[14] = new TLine(45.8,71.3,-4.2,71.3);
  lSide[15] = new TLine(-4.2,71.3,-4.2,21.3);

  lCent[0] = new TLine(-32,-32,32,-32);
  lCent[1] = new TLine(32,-32,32,32);
  lCent[2] = new TLine(32,32,-32,32);
  lCent[3] = new TLine(-32,32,-32,-32);

  lHol[0] = new TLine(-12.5,-12.5,12.5,-12.5);
  lHol[1] = new TLine(12.5,-12.5,12.5,12.5);
  lHol[2] = new TLine(12.5,12.5,-12.5,12.5);
  lHol[3] = new TLine(-12.5,12.5,-12.5,-12.5);

}