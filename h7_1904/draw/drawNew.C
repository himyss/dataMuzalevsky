//#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
//#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void drawNew(){
  //create_IDs();
  //create_cuts();

  gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH1F *htemp2;
  TH1F *htemp;
  TH2F *htemp2D;

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/mnt/data/exp1904/analysed/reco/h7/h7_ct_*_mm.root");
  cout << ch1->GetEntries () << " csiAnalyse" << endl;
  ch1->SetMarkerStyle(8);
  ch1->SetLineColor(kBlack);
  ch1->SetMarkerColor(kBlack);

  TF1 *fa = new TF1("fa","x*1/2",0,35);
  fa->SetLineColor(kRed);

  TF1 *fa1 = new TF1("fa1","x*4/7",0,25);
  fa1->SetLineColor(kRed);

  TF1 *fa2 = new TF1("fa2","x*3/7",0,40);
  fa2->SetLineColor(kRed);

  TF1 *f6 = new TF1("f6","x*6",-5,20);
  f6->SetLineColor(kRed);

  TF1 *f36 = new TF1("f36","x*5/6",0,35);
  f36->SetLineColor(kRed);  

  TString cut6H("( 1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag())<(1000*(lv_h6.Mag()-3*0.939565-2.808920)*1/2 + 0.5))");
  TString cut7H("( 1000*(lv_h3_CMH7.T()-lv_h3_CMH7.Mag())<(1000*(lv_h7.Mag()-4*0.939565-2.808920)*4/7 + 0.5))");

  Bool_t             mm_7h = 0;
  Bool_t             mm_6h = 1;
  Bool_t             angular_6h = 0;

  TString cut, triangleCut, hdraw;

  if (mm_7h) {
    TCanvas *c_mm = new TCanvas("c_mm","",1000,1000);
    c_mm->Divide(2,2);

    c_mm->cd(1);

    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("1000*(lv_h7.Mag()-4*0.939565-2.808920) >> h_mm(67,0,20)",cut.Data(),"") << endl;

    ch1->SetLineColor(kRed);
    cut += " && " + cut7H;
    cout << ch1->Draw("1000*(lv_h7.Mag()-4*0.939565-2.808920)",cut.Data(),"same") << endl;
    c_mm->Update();

    c_mm->cd(2);

    ch1->SetMarkerColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("1000*(lv_h3_CMH7.T()-lv_h3_CMH7.Mag()):1000*(lv_h7.Mag()-4*0.939565-2.808920)",cut.Data(),"") << endl;
    fa1->Draw("same");
    c_mm->Update();

    c_mm->cd(3);

    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("lv_h7_CMR.Theta()*TMath::RadToDeg():1000*(lv_h7.Mag()-4*0.939565-2.808920)",cut.Data(),"") << endl;
    c_mm->Update();

    c_mm->cd(4);

    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    // cut.Form("flagCent && nAlpha && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("1000*(lv_he4_CMHe7.T()-lv_he4_CMHe7.Mag()):1000*(lv_he7.Mag()-3*0.939565-3.727378)",cut.Data(),"") << endl;
    c_mm->Update();
    fa2->Draw("same");

  }

  if (mm_6h) {

    TH2F *hfake_0 = new TH2F("hfake_1","triton angle in 6H CMS vs MM",10000,0,35,10000,-1.,1);
    hfake_0->GetXaxis()->SetTitle("E_t_MeV");
    hfake_0->GetXaxis()->CenterTitle();
    hfake_0->GetYaxis()->SetTitle("3H angle 6H frame");
    hfake_0->GetYaxis()->CenterTitle();
    hfake_0->GetYaxis()->SetTitleOffset(1.3);

    TLine *l1 = new TLine(2.5, -1., 2.5, 1.);
    l1->SetLineColor(kRed);
    TLine *l2 = new TLine(5., -1., 5., 1.);
    l2->SetLineColor(kRed);
    TLine *l3 = new TLine(7.5, -1., 7.5, 1.);
    l3->SetLineColor(kRed);
    TLine *l4 = new TLine(10., -1., 10., 1.);
    l4->SetLineColor(kRed);
    TLine *l5 = new TLine(12.5, -1., 12.5, 1.);
    l5->SetLineColor(kRed);
    TLine *l6 = new TLine(15., -1., 15., 1.);
    l5->SetLineColor(kRed);
    TLine *l7 = new TLine(17.5, -1., 17.5, 1.);
    l7->SetLineColor(kRed);
    TLine *l8 = new TLine(20, -1., 20, 1.);
    l8->SetLineColor(kRed);
    TLine *l9 = new TLine(22.5, -1., 22.5, 1.);
    l9->SetLineColor(kRed);
    TLine *l10 = new TLine(25, -1., 25, 1.);
    l10->SetLineColor(kRed);
    TLine *l11 = new TLine(27.5, -1., 27.5, 1.);
    l11->SetLineColor(kRed);
    TLine *l12 = new TLine(30, -1., 30, 1.);
    l12->SetLineColor(kRed);
    TLine *l13 = new TLine(32.5, -1., 32.5, 1.);
    l13->SetLineColor(kRed);

    ch1->SetMarkerStyle(6);

    TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
    c_mm->Divide(2,2);

    c_mm->cd(1);
    ch1->SetLineWidth(1);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35"; 
    cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
    c_mm->Update();


    ch1->SetLineColor(kRed);
    cut += " && " + cut6H;
    cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
    c_mm->Update();

    ch1->SetLineColor(kBlue);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
    c_mm->Update();

    TH1F* htemp = (TH1F*)gPad->GetPrimitive("htemp");
    htemp->SetTitle("6H MM");
    htemp->GetXaxis()->SetTitle("E_t");
    htemp->GetXaxis()->CenterTitle();
    htemp->GetXaxis()->SetTitleSize(0.06);
    htemp->GetXaxis()->SetTitleOffset(0.61);  ; 

    c_mm->cd(2);
    ch1->SetMarkerColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cout << ch1->Draw("1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
    c_mm->Update();

    ch1->SetMarkerColor(kRed);
    cut += " && " + cut6H;
    cout << ch1->Draw("1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
    c_mm->Update();

    fa->Draw("same");

    htemp = (TH1F*)gPad->GetPrimitive("htemp");
    htemp->SetTitle("Triton kinematic triangle for 6H");
    htemp->GetXaxis()->SetTitle("E_t");
    htemp->GetXaxis()->CenterTitle();
    htemp->GetXaxis()->SetTitleSize(0.06);
    htemp->GetXaxis()->SetTitleOffset(0.61);  
    htemp->GetYaxis()->SetTitle("triton energy 6H CMS");
    htemp->GetYaxis()->CenterTitle(); 
    htemp->GetYaxis()->SetTitleSize(0.06);
    htemp->GetYaxis()->SetTitleOffset(0.31);  

    c_mm->cd(3);
    ch1->SetMarkerColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cout << ch1->Draw("lv_h6_CMR.Theta()*TMath::RadToDeg():1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
    c_mm->Update();

    ch1->SetMarkerColor(kRed);
    cut += " && " + cut6H;
    cout << ch1->Draw("lv_h6_CMR.Theta()*TMath::RadToDeg():1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
    c_mm->Update();

    htemp = (TH1F*)gPad->GetPrimitive("htemp");
    htemp->SetTitle("Reaction angle, deg VS 6H MM");
    htemp->GetXaxis()->SetTitle("E_t");
    htemp->GetXaxis()->CenterTitle();
    htemp->GetXaxis()->SetTitleSize(0.06);
    htemp->GetXaxis()->SetTitleOffset(0.61);  
    htemp->GetYaxis()->SetTitle("Reaction angle, deg");
    htemp->GetYaxis()->CenterTitle(); 
    htemp->GetYaxis()->SetTitleSize(0.06);
    htemp->GetYaxis()->SetTitleOffset(0.31); 

    c_mm->cd(4);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && neutron";
    cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920) >> neutMM(35,0,35)",cut.Data(),"") << endl;
    c_mm->Update();

    htemp = (TH1F*)gPad->GetPrimitive("neutMM");
    htemp->SetTitle("6H MM, neutron coincedence");
    htemp->GetXaxis()->SetTitle("E_t");
    htemp->GetXaxis()->CenterTitle();
    htemp->GetXaxis()->SetTitleSize(0.06);
    htemp->GetXaxis()->SetTitleOffset(0.61);  
return;
    c_mm->cd(5);
    ch1->SetMarkerColor(kBlack);
    ch1->SetMarkerStyle(8);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && neutron";
    cout << ch1->Draw("1000*(lv_neutron_CMH6.T()-lv_neutron_CMH6.Mag()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
    c_mm->Update();
    fa->Draw("same");    

    htemp = (TH1F*)gPad->GetPrimitive("htemp");
    htemp->SetTitle("Neutron kinematic triangle for 6H");
    htemp->GetXaxis()->SetTitle("E_t");
    htemp->GetXaxis()->CenterTitle();
    htemp->GetXaxis()->SetTitleSize(0.06);
    htemp->GetXaxis()->SetTitleOffset(0.61);  
    htemp->GetYaxis()->SetTitle("Neutron energy 6H CMS");
    htemp->GetYaxis()->CenterTitle(); 
    htemp->GetYaxis()->SetTitleSize(0.06);
    htemp->GetYaxis()->SetTitleOffset(0.31); 

    c_mm->cd(6);
    ch1->SetMarkerColor(kBlack);
    ch1->SetMarkerStyle(6);

    hfake_0->Draw();
    l1->Draw("same");
    l2->Draw("same");
    l3->Draw("same");
    l4->Draw("same");
    l5->Draw("same");
    l6->Draw("same");
    l7->Draw("same");
    l8->Draw("same");
    l9->Draw("same");
    l10->Draw("same");
    l11->Draw("same");
    l12->Draw("same");
    l13->Draw("same");

    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
    c_mm->Update();

    c_mm->Print("canvas1.png");
return;
    TCanvas *c_mm_s = new TCanvas("c_mm_s","",1800,1000);
    c_mm_s->Divide(4,4);  

    c_mm_s->cd(1);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>0 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<2.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut1(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();  

    c_mm_s->cd(2);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>2.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut2(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();      

    c_mm_s->cd(3);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<7.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut3(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(4);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>7.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<10";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut4(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(5);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>10 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<12.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut5(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(6);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>12.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<15";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut6(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(7);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>15 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<17.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut7(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(8);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>17.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<20";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut8(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(9);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>20 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<22.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut9(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(10);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>22.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<25";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut10(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(11);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>25 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<27.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut11(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(12);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>27.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<30";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut12(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(13);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>30 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<32.5";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut13(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->cd(14);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cut += " && " + cut6H;
    cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>32.5 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<35";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()) >> mmcut14(30,-1,1)",cut.Data(),"") << endl;
    c_mm_s->Update();   

    ch1->SetLineColor(kRed);
    cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta())",cut.Data(),"same") << endl;
    c_mm_s->Update();

    c_mm_s->Print("canvas2.png");

  }

  if (angular_6h) {

    TCanvas *c_ang = new TCanvas("c_ang","",1800,1000);
    c_ang->Divide(2,2);

    c_ang->cd(1);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cout << ch1->Draw("cos(lv_h3_CMH6.Theta()):1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag())",cut.Data(),"") << endl;
    c_ang->Update();

    c_ang->cd(2);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cout << ch1->Draw("1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag()):1000*(lv_h3.T()-lv_h3.Mag())",cut.Data(),"") << endl;
    c_ang->Update();

    c_ang->cd(3);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cout << ch1->Draw("cos(lv_he4_CMH6.Theta()):1000*(lv_he4_CMH6.T()-lv_he4_CMH6.Mag())",cut.Data(),"") << endl;
    c_ang->Update();

    c_ang->cd(4);
    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
    cout << ch1->Draw("cos(lv_he8_CMH6.Theta()):1000*(lv_he8_CMH6.T()-lv_he8_CMH6.Mag())",cut.Data(),"") << endl;
    c_ang->Update();

  }



}

