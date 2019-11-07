#include "/home/ivan/work/macro/be10/cut/be10Cut.C"
void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cutLi[16],*cutLi9[16],*cutX_C[32];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

Float_t pCsI_1[16],pCsI_2[16];

void drawCut(){
  be10Cut();
  gStyle->SetOptStat(0);
  readCuts();
  readPar("CsI_anh",pCsI_1,pCsI_2);

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cut.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_cut.root");
  // ch->Add("/media/ivan/data/exp1904/analysed/oldPars/mm_400.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  Bool_t litium = 0;
  Bool_t he3_1 = 1;
  Bool_t he3_2 = 1;
  Bool_t he3_3 = 1;
  Bool_t he3_4 = 1;
  Bool_t tSQ20 = 0;
  Bool_t timesCsI = 0;
  Bool_t centTimes = 0;
  Bool_t detectors = 0;
  Bool_t ToF = 0;

  if (timesCsI) {
    TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
    c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c3h->cd(i+1);
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("nCsI==%d && flagCent",i);
      hdraw.Form("aCsI:tCsI-tF5>>h%d1(1000,250,600,4200,0,4200)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      c3h->Update();

      cutCsI[i]->SetLineColor(kRed);
      cutCsI[i]->SetLineWidth(2);
      cutCsI[i]->Draw("same");
      c3h->Update();
    }
  }

 if (centTimes) {

    TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
    c3h->Divide(4,4);
    for(Int_t i=0;i<32;i++) {
      c3h->cd(i+1);
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("nX_C==%d",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d1(500,-200,0,500,0,105)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      c3h->Update();

      cutX_C[i]->SetLineColor(kRed);
      cutX_C[i]->SetLineWidth(2);
      cutX_C[i]->Draw("same");
      c3h->Update();
    }

  }



  if (litium) {
    TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
    c3h->Divide(4,4);
    // TString canName;
    // TCanvas *c_arr[16];
    // for(Int_t i=0;i<16;i++){
    //   canName.Form("cHe3_1_%d",i+1);
    //   c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    // }

    for(Int_t i=0;i<16;i++) {
      c3h->cd(i+1);
      // c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("nCsI==%d && flagCent",i);
      hdraw.Form("X_C:aCsI>>h%d(4200,0,4200,300,20,100)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      // c_arr[i]->Update();
      c3h->Update();

      // ch->SetMarkerColor(kRed); 
      // // ch->SetMarkerStyle(20);
      // // ch->SetMarkerSize(0.8);     
      // // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      // cut += " && nh3";
      // hdraw.Form("X_C:aCsI>>h%d_cut",i);
      // // hdraw.Form("X_C.:aCsI>>h%d",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // // c3h->Update();
      // c_arr[i]->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerColor(kGreen); 
      // ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.5);     
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && ( (flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4))";
      hdraw.Form("X_C:aCsI>>h%d_cut(4200,0,4200,300,20,100)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      c3h->Update();
      // c_arr[i]->Update();

      // ch->SetMarkerStyle(20);
      ch->SetMarkerColor(kRed); 
      // ch->SetMarkerStyle(20);
      // ch->SetMarkerSize(0.8);     
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nh3";
      hdraw.Form("X_C:aCsI>>h%d_coin(4200,0,4200,300,20,100)",i);
      // // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      c3h->Update();
      // c_arr[i]->Update();

      // cutLi9[i]->SetLineWidth(2);
      // cutLi9[i]->SetLineColor(kGreen);
      // cutLi9[i]->Draw("same");

      // cutLi[i]->SetLineWidth(2);
      // cutLi[i]->SetLineColor(kRed);
      // cutLi[i]->Draw("same");
      // c_arr[i]->Update();
    }
    c3h->Print("/home/ivan/Desktop/tmp/de_E_1.pdf");
    // c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_li_all.pdf");
    // c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_li_all.pdf[");
    // c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_li_all.pdf");
    // for(Int_t i=1;i<15;i++) {
    //   c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_li_all.pdf");
    // }
    // c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_li_all.pdf");
    // c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_li_all.pdf]");

  }


  if (he3_1) {
    // TCanvas *c3h = new TCanvas("c3h","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_1_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("n20_1==%d && flag1",i);
      hdraw.Form("a20_1:a1_1>>h%d1(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c_arr[i]->Update();
      // c3h->Update();

      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kBlue);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nh3";
      hdraw.Form("a20_1:a1_1>>h%d1_he(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_1";
      hdraw.Form("a20_1:a1_1>>h%d1_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      cuthe3_1[i]->SetLineWidth(2);
      cuthe3_1[i]->SetLineColor(kRed);
      cuthe3_1[i]->Draw("");
      c_arr[i]->Update();

      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E1_all.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E1_all.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E1_all.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E1_all.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E1_all.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E1_all.pdf]");


  }

  if (he3_2) {
    // TCanvas *c3h = new TCanvas("c3h","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_2_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("n20_2==%d && flag2",i);
      hdraw.Form("a20_2:a1_2>>h%d2(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c_arr[i]->Update();
      // c3h->Update();

      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kBlue);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nh3";
      hdraw.Form("a20_2:a1_2>>h%d2_he(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_2";
      hdraw.Form("a20_2:a1_2>>h%d2_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      cuthe3_2[i]->SetLineWidth(2);
      cuthe3_2[i]->SetLineColor(kRed);
      cuthe3_2[i]->Draw("");
      c_arr[i]->Update();

      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E2_all.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E2_all.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E2_all.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E2_all.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E2_all.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E2_all.pdf]");
  }

  if (he3_3) {
    // TCanvas *c3h = new TCanvas("c3h","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_3_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("n20_3==%d && flag3",i);
      hdraw.Form("a20_3:a1_3>>h%d3(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c_arr[i]->Update();
      // c3h->Update();

      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kBlue);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nh3";
      hdraw.Form("a20_3:a1_3>>h%d3_he(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_3";
      hdraw.Form("a20_3:a1_3>>h%d3_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      cuthe3_3[i]->SetLineWidth(2);
      cuthe3_3[i]->SetLineColor(kRed);
      cuthe3_3[i]->Draw("");
      c_arr[i]->Update();

      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E3_all.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E3_all.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E3_all.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E3_all.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E3_all.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E3_all.pdf]");
  }

  if (he3_4) {
    // TCanvas *c3h = new TCanvas("c3h","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_4_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("n20_4==%d && flag4",i);
      hdraw.Form("a20_4:a1_4>>h%d3(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c_arr[i]->Update();
      // c3h->Update();

      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kBlue);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nh3";
      hdraw.Form("a20_4:a1_4>>h%d4_he(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      ch->SetMarkerStyle(7);
      // ch->SetMarkerSize(0.4);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_4";
      hdraw.Form("a20_4:a1_4>>h%d3_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();


      cuthe3_4[i]->SetLineWidth(2);
      cuthe3_4[i]->SetLineColor(kRed);
      cuthe3_4[i]->Draw("");
      c_arr[i]->Update();

      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E4_all.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E4_all.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E4_all.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E4_all.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E4_all.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E4_all.pdf]");
  }

  if (tSQ20) {
    TCanvas * c2 = new TCanvas("c2","title",1800,1000);
    c2->Divide(4,4);

    for(Int_t i =11;i<12;i++) {
      c2->cd(i+1);
      // Int_t i = 1;
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("n1_4==%d",i);
      hdraw.Form("a1_4:t1_4-tF5>>h%d1",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");

      c2->Update();

      ch->SetMarkerColor(kRed);      
      cut.Form("n1_4==%d && flag4",i);
      hdraw.Form("a1_4:t1_4-tF5>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");

      c2->Update();


      // cutSQ1_4[i]->SetLineColor(kRed);
      // cutSQ1_4[i]->SetLineWidth(2);
      // cutSQ1_4[i]->Draw("");

    }
  }

  if (detectors) {
    TCanvas * c1 = new TCanvas("c1","title",1000,1000);

    ch->SetMarkerColor(1);
    ch->SetMarkerStyle(20);
    ch->Draw("y1t:x1t >> d1(300,-100,100,300,-100,100) ","flag1","");

    ch->SetMarkerColor(2);
    // ch->SetMarkerStyle(20);
    ch->Draw("y2t:x2t >> d2(300,-100,100,300,-100,100)","flag2","same");

    ch->SetMarkerColor(3);
    // ch->SetMarkerStyle(20);
    ch->Draw("y3t:x3t >> d3(300,-100,100,300,-100,100)","flag3","same");

    ch->SetMarkerColor(4);
    // ch->SetMarkerStyle(20);
    ch->Draw("y4t:x4t >> d4(300,-100,100,300,-100,100)","flag4","same");

  }

  if (ToF) {
    TCanvas *cToF = new TCanvas("cToF","title",1000,1000);
    // cToF->Divide(2,1);

    cToF->cd(1);
    ch->Draw("F5:tF5-tF3 >> F5(1000,63,75,6000,3000,9000)","","col");

    // cutF5->SetLineColor(kRed);
    // cutF5->SetLineWidth(2);
    // cutF5->Draw("same");

    // cToF->cd(2);
    // ch->Draw("F3:tF5-tF3 >> F3(1000,0,200,8000,0,8000)","col");

    // cutF3->SetLineColor(kRed);
    // cutF3->SetLineWidth(2);
    // cutF3->Draw("same");

  }


}


void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/litium/li_%d.root",i);
    f = new TFile(cutName.Data());
    cutLi[i] = (TCutG*)f->Get("CUTG");
    if (!cutLi[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/litium/firstPars/Li9_%d.root",i);
    f = new TFile(cutName.Data());
    cutLi9[i] = (TCutG*)f->Get("CUTG");
    if (!cutLi9[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/tCsI/tCsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<32;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T1/tSQ20/tSQ20_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ20_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ20_1[i]) {
      cout << i  << " no cut"<< endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T1/SQ1_1/tSQ1_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_1[i]) {
      cout << i  << " no cut"<< endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T2/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T3/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T4/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_4[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T4/tSSD4/tSSD4_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_4[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/ivan/work/soft/er/input/exp1904_pars/" + fileName + ".cal";
  myfile.open(file.Data());
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    if(count < 0){
      count++;
      continue;
    }
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g %g", par1+count,par2+count);
    count++;
  }
  cout << endl << fileName.Data() << endl;
  for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

  return;
}

