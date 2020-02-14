void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cut3h[16],*cutX_C[32],*cut8he[16],*cut6he[16];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];
TCutG *cut6Li;

Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void create_cut(){

  readCuts();

  nCoins = 0;

  TChain *ch = new TChain("tree");

  // ch->Add("/media/ivan/data/exp1906/be10/analysed/tmp/second.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/tmp/first.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;
  Int_t i = 15;

  TCanvas *c3h = new TCanvas("c3h","",1000,1000);
  ch->SetMarkerStyle(7);
  ch->SetMarkerColor(kBlack);      
  cut.Form("flagCent && nCsI_track==%d",i);
  hdraw.Form("X_C:arCsI[%d]>>h%d(4000,0,4000,200,0,100)",i,i);
  ch->Draw(hdraw.Data(),cut.Data(),"");
  c3h->Update();

  ch->SetMarkerStyle(20);
  ch->SetMarkerColor(kRed);
  cut.Form("flagCent && nCsI_track==%d && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
  hdraw.Form("X_C:arCsI[%d]",i,i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");
  c3h->Update();

  cut8he[i]->SetLineColor(kRed);
  cut6he[i]->SetLineColor(kBlue);
  cut6he[i]->SetLineWidth(2);
  cut6he[i]->Draw("same");
  cut8he[i]->Draw("same");

}

void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10_Nov/cut/CT/litium/secondPars/Li9_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10_Nov/cut/CT/litium/he6/firstVol/he6_%d.root",i);
    f = new TFile(cutName.Data());
    cut6he[i] = (TCutG*)f->Get("CUTG");
    if (!cut6he[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10_Nov/cut/CT/litium/he8/firstVol/he8_%d.root",i);
    f = new TFile(cutName.Data());
    cut8he[i] = (TCutG*)f->Get("CUTG");
    if (!cut8he[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10_Nov/cut/CT/tCsI/tCsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<32;i++) {
    cutName.Form("/home/ivan/work/macro/be10_Nov/cut/CT/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/T1/he3/cut_he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/T2/he3/cut_he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/T3/he3/cut_he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(-1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/h7_1904/cutsNovPars/T4/he3/cut_he3_%d.root",i);
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


