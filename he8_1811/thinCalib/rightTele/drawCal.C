void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Float_t par1[16],par2[16],pDSDY_L1[16],pDSDY_L2[16];

void drawCal() {

  gStyle->SetOptStat(0);
  // readPar("ssd20_l_new",par1,par2);

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1811/analysed/clb/oldLib/dsd_20_l_03_selected_new.root");

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // c1->Divide(4,4);

  TString hDraw,hCut;

  hDraw.Form("n20_L:a20_L_cal + Y_L_cal >>(600,3,8,16,0,16)");
  ch1->Draw(hDraw.Data(),"","box");
  c1->Update();

  return;
}
