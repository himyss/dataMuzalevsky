void readCuts();
TCutG *cutCsI[16],*cut3h[16],*cutX_C[16];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

TString cut,hdraw;
void createCut(){

      TChain *ch = new TChain("tree");
      ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cut.root");

      readCuts();
      TCanvas *c1 = new TCanvas("c1","title",1800,1000);

      Int_t i = 1;

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.5);
      ch->SetMarkerColor(kBlack);      
      cut.Form("n20_1==%d",i);
      hdraw.Form("a20_1:a1_1>>h%d1(300,1,35,300,0.1,5)",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c1->Update();

      ch->SetMarkerSize(0.7); 
      ch->SetMarkerColor(kBlue);      
      // cut.Form("n20_1==%d && nhe3_1",i);
      cut += " && nh3";
      hdraw.Form("a20_1:a1_1>>h%d_triton1(300,1,35,300,0.1,5)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();
      c1->Update();
      // ch->SetMarkerStyle(4);    
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1",i);
      // cut += " && nh3";
      // hdraw.Form("a20_1:a1_1>>h%d_he31",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      // ch->SetMarkerStyle(20);
      // ch->SetMarkerSize(0.8);
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      // cut += " && nhe3_1";
      // hdraw.Form("a20_1:a1_1>>h%d1_coin(300,1,35,300,0.1,5)",i);
      // // hdraw.Form("X_C.:aCsI>>h%d",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      // cuthe3_1[i]->SetLineWidth(2);
      // cuthe3_1[i]->SetLineColor(kRed);
      // cuthe3_1[i]->Draw("same");
      c1->Update();
      // c3h->Update();
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
      return;
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/C_T/tCsI/tCsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/draw/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/T1/tSQ20/tSQ20_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ20_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ20_1[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/T1/SQ1_1/tSQ1_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_1[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/T2/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/T3/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/he8_1904/cuts/T4/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_4[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

}
