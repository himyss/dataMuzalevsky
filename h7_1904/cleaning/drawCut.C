#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cut3h[16],*cutX_C[32],*cut6he[16];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];
TCutG *cut6Li,*cutNeutron;
Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void drawCut(){
  nCoins = 0;
  // readPar("CsI_anh",pCsI_1,pCsI_2);
  create_cuts(); 
  // return;
  gStyle->SetOptStat(0);
  Bool_t tCsI_s = 1;
  Bool_t centtimes = 1;
  Bool_t vetoTime = 1;
  Bool_t tSQ20 = 1;
  Bool_t tSQThick = 1;

  TChain *ch = new TChain("er");

  ch->Add("/mnt/data/exp1904/cleaned/h7_final/h7_ct*");
  cout << ch->GetEntries() << endl;

  // TChain *ch1 = new TChain("er");
  // ch1->Add("/mnt/data/exp1904/cleaned/h7/h7_ct_*.root");
  // cout << ch1->GetEntries() << endl;

  TString cut,hdraw;

  if (tCsI_s) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);
    for(Int_t i=0;i<16;i++) {

      c1->cd(i+1);

      ch->SetMarkerColor(kBlack);      

      hdraw.Form("ERQTelescopeCsIDigi_Central_telescope_CsI_0.fEdep:ERQTelescopeCsIDigi_Central_telescope_CsI_0.fTime-BeamDetToFDigi2.fTime");
      cut.Form("ERQTelescopeCsIDigi_Central_telescope_CsI_0.fChannel==%d",i);

      ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);

      c1->Update();

      CsI_cut[i]->SetLineWidth(1);
      CsI_cut[i]->SetLineColor(kRed);
      CsI_cut[i]->Draw();
      c1->Update();

    }
  }

  if (centtimes) {
    TCanvas *c3h = new TCanvas("c3h","",1800,1000);  
    c3h->Divide(4,4);
    for(Int_t i=16;i<32;i++) {
      c3h->cd(i+1-16);
      ch->SetMarkerColor(kBlack);      
      cut.Form("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_XY_0_X.fChannel==%d",i);
      hdraw.Form("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_XY_0_X.fEdep:ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_XY_0_X.fTime-BeamDetToFDigi2.fTime>>h%d",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      c3h->Update();

      dssd_x_cut[i]->SetLineColor(kRed);
      dssd_x_cut[i]->Draw("same");


      c3h->Update();
    }
  }

  if (vetoTime) {

    TCanvas *cveto = new TCanvas("cveto","",1800,1000);
    cveto->Divide(2,2);

    cveto->cd(1);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_1_SingleSi_SSD_V_1_Y_2.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);
    cveto->Update();  
    
    cveto->cd(2);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_2_SingleSi_SSD_V_2_X_5.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);
    cveto->Update();  

    cveto->cd(3);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_3_SingleSi_SSD_V_3_Y_8.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);
    cveto->Update();

    cveto->cd(4);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_4_SingleSi_SSD_V_4_X_11.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);
    cveto->Update();
  }

  if (tSQ20) {

    TCanvas *c_sq20 = new TCanvas("c_sq20","",1000,1800);
    c_sq20->Divide(2,2);

    c_sq20->cd(1);
    ch->SetLineColor(kBlack);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_1_SingleSi_SSD20_1_X_0.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);

    c_sq20->cd(2);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_2_SingleSi_SSD20_2_Y_3.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);

    c_sq20->cd(3);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_3_SingleSi_SSD20_3_X_6.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);

    c_sq20->cd(4);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_4_SingleSi_SSD20_4_Y_9.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);

  }

  if (tSQThick) {

    TCanvas *c_sqthick = new TCanvas("c_sqthick","",1000,1800);
    c_sqthick->Divide(2,2);

    c_sqthick->cd(1);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_1_SingleSi_SSD_1_Y_1.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);  
    c_sqthick->Update();

    c_sqthick->cd(2);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_2_SingleSi_SSD_2_X_4.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);  
    c_sqthick->Update();

    c_sqthick->cd(3);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_3_SingleSi_SSD_3_Y_7.fTime-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);  
    c_sqthick->Update();

    c_sqthick->cd(4);
    hdraw.Form("ERQTelescopeSiDigi_Telescope_4_SingleSi_SSD_4_X_10.fEdep-BeamDetToFDigi2.fTime");
    ch->Draw(hdraw.Data(),"","",1000000,0);  
    c_sqthick->Update();        
    
}




}
void readCuts() {

  TFile *f;
  TString cutName;

  cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/ND/Neutron.root");
  f = new TFile(cutName.Data());
  cutNeutron = (TCutG*)f->Get("CUTG");
  if (!cutNeutron) {
    cout << "no cut " << cutName.Data() << endl;
    exit(-1);
  }    
  delete f;

  cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T1/li6_cut.root");
  f = new TFile(cutName.Data());
  cut6Li = (TCutG*)f->Get("CUTG");
  if (!cut6Li) {
    cout << "no cut " << cutName.Data() << endl;
    exit(-1);
  }    
  delete f;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cutsNovPars/C_T/6He/he6_%d.root",i);
    f = new TFile(cutName.Data());
    cut6he[i] = (TCutG*)f->Get("CUTG");
    if (!cut6he[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cutsNovPars/C_T/triton/h3_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cutsNovPars/C_T/tCsI/tCsI_full_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<32;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cutsNovPars/C_T/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T1/he3/canvas/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T2/he3/canvas/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T3/he3/canvas/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/muzalevskii/work/macro/h7_1904/cuts/T4/he3/canvas/he3_%d.root",i);
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

