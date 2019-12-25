void drawNew(){

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/oldPars/selected.root");

  TString hDraw,hCut;

  // hCut = ""; 

  TCanvas *c1 = new TCanvas("c1","setup scheme",1000,1000);
  c1->cd();

  ch->Draw("fYt:fXt >> (50,-15,15,50,-15,15) ","trigger==1 && nX_C>-1 && nCsI>-1 && fabs(fXt)<15","col");
  c1->Update();

  TEllipse *el = new TEllipse(0.5,1,10);
  el->SetLineColor(kRed);
  el->Draw("same");
}
