void readCuts();

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cutLi[16],*cutLi9[16],*cutX_C[16];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

Float_t pCsI_1[16],pCsI_2[16];

void createCut(){
  readCuts();

  readPar("CsI_anh",pCsI_1,pCsI_2);

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/calibrated/be10_ct_thinTarget.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  Bool_t litium = 0;
  Bool_t he3_0 = 0;
  Bool_t he3_2 = 0;
  Bool_t he3_3 = 0;
  Bool_t he3_4 = 0;
  Bool_t tSQ20 = 0;
  Bool_t centTimes = 1;

  if (centTimes) {

    TCanvas *c3h = new TCanvas("c3h","title",1800,1000);
    // c3h->Divide(4,4);

    // for(Int_t i=0;i<16;i++) {
    //   c3h->cd(i+1);
      Int_t i = 31;
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("multc_x==1",i);
      // hdraw.Form("DSD_X:aCsI>>h%d(1000,0,250,500,0,100)",i);
      hdraw.Form("DSD_X[%d]:tDSD_X[%d]-tF5 >> h%d(300,-200,-130,300,0,105)",i,i,i);
      // ch->SetMarkerStyle(8);
      ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      c3h->Update();


    // }

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
    cutName.Form("/home/ivan/work/macro/be10_Nov/cut/CT/litium/secondPars/Li9_%d.root",i);
    f = new TFile(cutName.Data());
    cutLi9[i] = (TCutG*)f->Get("CUTG");
    if (!cutLi9[i]) {
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