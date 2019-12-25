#include "/home/ivan/work/macro/h7_1904/cutsNovPars/cutTauCsIcal.cxx"

void readCuts();

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cut3h[16],*cutX_C[32];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

Float_t pCsI_1[16],pCsI_2[16];

void drawCalib(){

  cutTauCsIcal();
  readCuts();

  readPar("CsI_anh",pCsI_1,pCsI_2);

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/calibrated/h7_0_cal.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  Bool_t litium = 0;
  Bool_t he3_1 = 0;
  Bool_t he3_2 = 0;
  Bool_t he3_3 = 0;
  Bool_t he3_4 = 0;
  Bool_t tSQ20 = 0;
  Bool_t centTimes = 1;

  if (centTimes) {

    TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
    c3h->Divide(4,4);

    for(Int_t i=0;i<16;i++) {
      c3h->cd(i+1);
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("multc_x==1 && trigger!=1",i);
      // hdraw.Form("DSD_X:aCsI>>h%d(1000,0,250,500,0,100)",i);
      // hdraw.Form("DSD_X:arCsI[%d]*%f + %f >> h%d(1000,0,150,100,0,20)",i,pCsI_2[i],pCsI_1[i],i);
      // hdraw.Form("DSD_X:arCsI[%d] >> h%d(1000,0,4000,100,0,20)",i,i);
      // hdraw.Form("arCsI[%d]*%f + %f:trCsI[%d]-tF5 >> h%d",i,pCsI_2[i],pCsI_1[i],i,i);
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5 >> h%d",i,i,i);
      // ch->SetMarkerStyle(8);
      ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      c3h->Update();

      cutCsI[i]->SetLineColor(kRed);
      cutCsI[i]->Draw("same");

    }

  }

  // if (litium) {

  //   TString canName;
  //   TCanvas *c_arr[16];
  //   for(Int_t i=0;i<16;i++){
  //     canName.Form("cHe3_1_%d",i+1);
  //     c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
  //   }
  //   // TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
  //   // c3h->Divide(4,4);

  //   for(Int_t i=0;i<16;i++) {
  //     // c3h->cd(i+1);
  //     c_arr[i]->cd();
  //     ch->SetMarkerStyle(1);
  //     ch->SetMarkerColor(kBlack);      
  //     cut.Form("nCsI==%d && multc_x==1",i);
  //     // hdraw.Form("DSD_X:aCsI>>h%d(1000,0,250,500,0,100)",i);
  //     hdraw.Form("DSD_X.:aCsI*%f + %f>>h%d",pCsI_2[i],pCsI_1[i],i);
  //     // ch->SetMarkerStyle(8);
  //     ch->Draw(hdraw.Data(),cut.Data(),"");
  //     c_arr[i]->Update();
  //     // c3h->Update();

     
  //     cutLi9[i]->SetLineWidth(2);
  //     cutLi9[i]->SetLineColor(kGreen);
  //     cutLi9[i]->Draw("same");

  //     cutLi[i]->SetLineWidth(2);
  //     cutLi[i]->SetLineColor(kRed);
  //     cutLi[i]->Draw("same");
  //     // c3h->Update();
  //     c_arr[i]->Update();
  //   }

  //   TString picName;
  //   for(Int_t i=0;i<16;i++) {
  //     picName.Form("/home/ivan/Desktop/tmp/png/de_E_li%d_all.png",i);
  //     c_arr[i]->Print(picName.Data());
  //   }

  // }

}

void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/C_T/triton/h3_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/C_T/tCsI/tCsI_full_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/C_T/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/T1/tSQ20/tSQ20_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ20_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ20_1[i]) {
      cout << i  << " no cut"<< endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/T1/SQ1_1/tSQ1_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_1[i]) {
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
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/T3/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cuts/T4/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_4[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=0;
  TString file = "/home/ivan/work/macro/h7_1904/parameters/" + fileName + ".cal";
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