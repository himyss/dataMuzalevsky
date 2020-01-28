void drawBeam() {


  TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])");

  // gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH2F *htemp2;

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/parVariation/sideTel/be10_ct_thinTarget_cut_171.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/parVariation/sideTel/be10_ct_firstVol_cut_171.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/parVariation/sideTel/be10_ct_secondVol_cut_171.root");  
  cout << ch->GetEntries() << endl;


  TCanvas *c1 = new TCanvas("c1","title",1100,1100);


  ch->Draw("fYt:fXt >> profile(64,-20,20,64,-20,20)","trigger!=1 && nX_C>0 && nY_C>0","col");
  // htemp2 = (TH2F*)gPad->GetPrimitive("profile");


  // gPad->SetLogz();

  // Float_t xCent = -0.93;
  // Float_t yCent = 1.52;

  Float_t xCent = 0;
  Float_t yCent = 0;

  TEllipse *dia = new TEllipse(xCent,yCent,12.5);
  dia->SetLineColor(kRed);
  dia->SetLineWidth(3);
  dia->SetFillStyle(0); 
  dia->Draw();

  TLine *lh = new TLine(xCent,yCent-12.5,xCent,yCent+12.5);
  lh->SetLineColor(kRed);
  lh->SetLineWidth(2);
  lh->Draw();


  TLine *lv = new TLine(xCent-12.5,yCent,xCent+12.5,yCent);
  lv->SetLineColor(kRed);
  lv->SetLineWidth(2);
  lv->Draw();

  c1->Update();

  // c1->Print("tranc.png");

}