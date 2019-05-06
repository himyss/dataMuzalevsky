void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Float_t par1[16],par2[16],pDSDY_R1[16],pDSDY_R2[16];

void drawCal() {

  gStyle->SetOptStat(0);

  TString hDraw,hCut;
  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/home/oem/work/data/exp1811/analysed/clbdsd_20_R_02_selected1.root");
  ch1->Add("/home/oem/work/data/exp1811/analysed/clbdsd_20_r_02_selected1.root");

  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_selected_newpar.root");


  TCanvas *c1 = new TCanvas("c1","",1800,1000);   
  hDraw.Form("n20_R:a20_R_cal + Y_R_cal >>h1(600,3,9,16,0,16)");
  ch1->Draw(hDraw.Data(),"","box");
  c1->Update();

  hDraw.Form("n20_R:a20_R_cal + Y_R_cal >>h2(600,3,9,16,0,16)");
  ch2->SetLineColor(kRed);
  ch2->Draw(hDraw.Data(),"","box && same");

  c1->Update();

  c1->Print("/home/oem/Desktop/fullspecnew_all.png");
  // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // hDraw.Form("n20_R:a20_R_cal + Y_R_cal >>h4(600,3,8,16,0,16)");
  // ch1->Draw(hDraw.Data(),"nY_R>-1","box");
  // c2->Update();

  return;
}
