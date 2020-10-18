#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);



Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void draw(){

  create_IDs();
  create_cuts();

  nCoins = 0;
  // readPar("CsI_anh",pCsI_1,pCsI_2);
  // readCuts();
  // return;
  gStyle->SetOptStat(0);
  Bool_t tritium = 1;
  Bool_t he3_1 = 0;
  Bool_t he3_2 = 0;
  Bool_t he3_3 = 0;
  Bool_t he3_4 = 0;
  Bool_t tCsI_s = 0;
  Bool_t target = 0;
  Bool_t centtimes = 0;
  Bool_t CsI_tracking = 0;
  Bool_t tSQ20 = 0;
  Bool_t tSQThick = 0;
  Bool_t neutronID = 0;


  TChain *ch = new TChain("tree");
  ch->Add("/mnt/data/exp1904/analysed/selected/h7/h7_*.root");
  cout << ch->GetEntries() << endl;


  TChain *ch1 = new TChain("tree");
  ch1->Add("/mnt/data/exp1904/analysed/selected/h7/h7_*.root");
  cout << ch1->GetEntries() << endl;

  TString hdraw, cut;

  if (tritium) {

    TCanvas *c3h = new TCanvas("c3h","",1800,1000);  
    ch->SetMarkerStyle(1);
    c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {

    // Int_t i = 15;

    c3h->cd(i+1);    
    cut.Form("nCsI_track==%d && flagCent && arCsI[%d]>0",i,i);
    // hdraw.Form("X_C:aCsI>>h%d(300,0,150,300,2,90)",pCsI_1[i],pCsI_2[i],i);

    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);
    hdraw.Form("X_C:arCsI[%d] >>h%d_cut",i,i);
    ch->Draw(hdraw.Data(),cut.Data(),"",20000000,0);
    c3h->Update();

    cut6he[i]->SetLineColor(kRed);
    cut6he[i]->Draw("same");

    // ch->SetMarkerColor(kRed);
    // ch->SetMarkerStyle(6);
    // cut += " && (nh3_1 || nh3_2 || nh3_3 || nh3_4)";
    // hdraw.Form("X_C:arCsI[%d]",i);
    // ch->Draw(hdraw.Data(),cut.Data(),"same");
    // c3h->Update();

      // ch->SetMarkerStyle(20);
      // ch->SetMarkerColor(kRed);
      // cut.Form("nCsI_track==%d && flagCent && nh2 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
      // hdraw.Form("X_C:arCsI[%d]",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();
    
    }
 
    // c3h->Print("/home/muzalevskii/Desktop/de_E_triton_dead.png");

  }

}

void readCuts() {

  TFile *f;
  TString cutName;

  cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T1/li6_cut.root");
  f = new TFile(cutName.Data());
  TCutG *cut6Li_1 = (TCutG*)f->Get("CUTG");
  if (!cut6Li_1) {
    cout << "no cut " << cutName.Data() << endl;
    exit(-1);
  }    
  delete f;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/C_T/triton/h3_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/C_T/tCsI/tCsI_full_%d.root",i);
    f = new TFile(cutName.Data());
    CsI_cut[i] = (TCutG*)f->Get("CUTG");
    if (!CsI_cut[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<32;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/C_T/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    dssd_x_cut[i] = (TCutG*)f->Get("CUTG");
    if (!dssd_x_cut[i]) {
      cout << i  << " no cut"<< endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T2/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T3/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T4/he3/he3_%d.root",i);
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
  Int_t count=-2;
  TString file = "/home/muzalevskii/work/macro/h7_1904/parameters/" + fileName + ".cal";
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

