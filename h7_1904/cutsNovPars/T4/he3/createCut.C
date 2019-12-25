void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cut3h[16],*cutX_C[32];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void createCut(){
  nCoins = 0;
  readPar("CsI",pCsI_1,pCsI_2);
  readCuts();
  // return;
// return;
  gStyle->SetOptStat(0);
  Bool_t tritium = 0;
  Bool_t he3_1 = 1;
  Bool_t he3_2 = 0;
  Bool_t he3_3 = 0;
  Bool_t he3_4 = 0;
  Bool_t tCsI_s = 0;
  Bool_t target = 0;
  Bool_t centtimes = 0;
  Bool_t CsI_tracking = 0;


  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/he8_*.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  if (tCsI_s) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);
    for(Int_t i=0;i<16;i++) {

      c1->cd(i+1);

      ch->SetMarkerColor(kBlack);      
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5>>h%d",i,i,i);
      cut.Form("nCsI_track==%d",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      // gPad->SetLogz();/
      ch->Draw(hdraw.Data(),cut.Data(),"",500000,0);
      // gPad->SetLogz();
      c1->Update();


      ch->SetMarkerColor(kRed);      
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5>>h_cut%d",i,i,i);
      cut.Form("flagCent && nCsI_track==%d",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      // gPad->SetLogz();/
      ch->Draw(hdraw.Data(),cut.Data(),"same",500000,0);
      // gPad->SetLogz();
      c1->Update();


      cutCsI[i]->SetLineWidth(1);
      cutCsI[i]->SetLineColor(kRed);
      cutCsI[i]->Draw("same");
      c1->Update();

    }
  }

  if (tritium) {
    TCanvas *c3h = new TCanvas("c3h","",1800,1000);  
    c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c3h->cd(i+1);    
      cut.Form("flagCent && nCsI_track==%d",i);
      // hdraw.Form("X_C:aCsI>>h%d(300,0,150,300,2,90)",pCsI_1[i],pCsI_2[i],i);

      hdraw.Form("X_C:(arCsI[%d]-%f)/%f >>h%d(500,0,4000,200,0,25)",i,pCsI_1[i],pCsI_2[i],i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->SetMarkerColor(kBlack);
      ch->SetMarkerStyle(7);
      ch->Draw(hdraw.Data(),cut.Data(),"",10000000,0);


      cut.Form("flagCent && nCsI_track==%d && nh3",i);
      // hdraw.Form("X_C:aCsI>>h%d(300,0,150,300,2,90)",pCsI_1[i],pCsI_2[i],i);

      hdraw.Form("X_C:(arCsI[%d]-%f)/%f >>h%d_cut(500,0,4000,200,0,25)",i,pCsI_1[i],pCsI_2[i],i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->SetMarkerColor(kRed);
      ch->SetMarkerStyle(7);
      ch->Draw(hdraw.Data(),cut.Data(),"same",10000000,0);

      cut3h[i]->Draw("same");
      // ch->Draw(hdraw.Data(),cut.Data(),"");
     
      c3h->Update();

    }
 
  }

  if (target) {
    TCanvas *c4 = new TCanvas("c4","target cut",1000,1000);  
    cout << ch->Draw("fYt:fXt>>h_target(100,-30,30,100,-30,30)","nCsI>-1 && X_C>0","col") << endl;

    ch->SetMarkerColor(kRed);
    ch->Draw("fYt:fXt>>h_targetCut(100,-30,30,100,-30,30)","nCsI>-1 && X_C>0 && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<9*9","same");
  }

  if (centtimes) {
    TCanvas *c3h = new TCanvas("c3h","",1800,1000);  
    c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c3h->cd(i+1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("nX_C==%d && trigger!=1",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      c3h->Update();
      
      ch->SetMarkerColor(kRed);      
      cut.Form("nX_C==%d && flagCent",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d_cut",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch->Draw(hdraw.Data(),cut.Data(),"same",1000000,0);
      c3h->Update();

      cutX_C[i]->SetLineColor(kRed);
      cutX_C[i]->Draw("same");


      c3h->Update();
    }
  }

  if (he3_1) {
    TCanvas *c3h_1 = new TCanvas("c3h_1","",1800,1000);

    // TString canName;
    // TCanvas *c_arr[16];
    // for(Int_t i=0;i<16;i++){
    //   canName.Form("cHe3_1_%d",i+1);
    //   c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    // }

    // c3h->Divide(4,4);
    // for(Int_t i=0;i<16;i++) 
    { 
    
      Int_t i=15;
      // c_arr->cd(i+1);
      // c3h_1->cd();
      // c_arr[i.q]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);  
      // ch->SetMarkerColor(i+1);       
      cut.Form("n20_4==%d && flag4",i);
      // cut.Form("flag1");
      hdraw.Form("a20_4:a1_4+a20_4_un>>h%d1(700,1,30,500,0.5,4)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"col");
      // c_arr[i]->Update();
      // c_ar/r[i]->Update();
      // c3h

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);   
      ch->SetMarkerColor(kGreen);           
      // cut.Form("n20_1==%d && nhe3_1",i);
      cut += " && nh3";
      hdraw.Form("a20_4:a1_4+a20_4_un>>h%d_triton1(700,1,30,500,0.5,4)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      c3h_1->Update();

      // ch->SetMarkerStyle(20);
      // ch->SetMarkerSize(1);
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      // cut += " && nhe3_1 && a1_1<20";
      // hdraw.Form("a20_1:a1_1>>h%d1_coin(100,1,30,100,0.5,5)",i);
      // // hdraw.Form("X_C.:aCsI>>h%d",i);
      // nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // // c3h->Update();

      // cuthe3_1[i]->SetLineWidth(1);
      // cuthe3_1[i]->SetLineColor(kRed);
      // cuthe3_1[i]->Draw("same");
      // c_arr[i]->Update();
      // c_arr[i]->Update();
      // c3h->Update();
    }
    
    // c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_1.pdf");
    // c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_1.pdf[");
    // c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_1.pdf");
    // for(Int_t i=1;i<15;i++) {
    //   c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_1.pdf");
    // }
    // c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_1.pdf");
    // c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_1.pdf]");
  }

  if (he3_2) {
    TCanvas *c3h_2 = new TCanvas("c3h_2","",1800,1000);

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
      hdraw.Form("a20_2:a1_2>>h%d1(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);  
      ch->SetMarkerColor(kGreen);      
      // cut.Form("n20_1==%d && nhe3_1",i);
      cut += " && nh3";
      hdraw.Form("a20_2:a1_2>>h%d_triton1(100,1,30,100,0.5,5)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();
      c_arr[i]->Update();
      // ch->SetMarkerStyle(4);    
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1",i);
      // cut += " && nh3";
      // hdraw.Form("a20_1:a1_1>>h%d_he31",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(1);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_2 && a1_2<20";
      hdraw.Form("a20_2:a1_2>>h%d1_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_2[i]->SetLineWidth(1);
      cuthe3_2[i]->SetLineColor(kRed);
      cuthe3_2[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf]");
  }

   if (he3_3) {
    TCanvas *c3h = new TCanvas("c3h_3","",1800,1000);

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
      hdraw.Form("a20_3:a1_3>>h%d1(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);  
      ch->SetMarkerColor(kGreen);      
      // cut.Form("n20_1==%d && nhe3_1",i);
      cut += " && nh3";
      hdraw.Form("a20_3:a1_3>>h%d_triton1(100,1,30,100,0.5,5)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();
      c_arr[i]->Update();
      // ch->SetMarkerStyle(4);    
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1",i);
      // cut += " && nh3";
      // hdraw.Form("a20_1:a1_1>>h%d_he31",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(1);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_3 && a1_3<20";
      hdraw.Form("a20_3:a1_3>>h%d1_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_3[i]->SetLineWidth(1);
      cuthe3_3[i]->SetLineColor(kRed);
      cuthe3_3[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf]");
  }

  if (he3_4) {
    TCanvas *c3h = new TCanvas("c3h_4","",1800,1000);

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
      hdraw.Form("a20_4:a1_4>>h%d1(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);   
      ch->SetMarkerColor(kGreen);      
      // cut.Form("n20_1==%d && nhe3_1",i);
      cut += " && nh3";
      hdraw.Form("a20_4:a1_4>>h%d_triton1(100,1,30,100,0.5,5)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();
      c_arr[i]->Update();
      // ch->SetMarkerStyle(4);    
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1",i);
      // cut += " && nh3";
      // hdraw.Form("a20_1:a1_1>>h%d_he31",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(1);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_4 && a1_4<20";
      hdraw.Form("a20_4:a1_4>>h%d1_coin(100,1,30,100,0.5,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_4[i]->SetLineWidth(1);
      cuthe3_4[i]->SetLineColor(kRed);
      cuthe3_4[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf]");
  }


  if (CsI_tracking) {



    // TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    // c1->Divide(4,4);
    // for(Int_t i=0;i<16;i++) {

    //   c1->cd(i+1);

    //   ch->SetMarkerColor(kBlack);      
    //   hdraw.Form("");
    //   cut.Form("nCsI_track==%d",i);
    //   ch->Draw("xCt",cut.Data(),"");
    //   // gPad->SetLogz();
    //   c1->Update();

    // }  


    // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
    // c2->Divide(4,4);
    // for(Int_t i=0;i<16;i++) {

    //   c2->cd(i+1);

    //   ch->SetMarkerColor(kBlack);      

    //   cut.Form("nCsI_track==%d",i);
    //   ch->Draw("yCt",cut.Data(),"");
    //   // gPad->SetLogz();
    //   c2->Update();

    // } 

    TCanvas *c3 = new TCanvas("c3","",1800,1000);
    ch->Draw("nCsI-nCsI_track","flagCent","");

  }

}

void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/C_T/triton/h3_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts_MKpars/he3_1/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/C_T/tCsI/tCsI_full_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<32;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/C_T/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/T2/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts_MKpars/he3_3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts_MKpars/he3_4/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_4[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  cout << " CUTS are read" << endl;
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=0;
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

