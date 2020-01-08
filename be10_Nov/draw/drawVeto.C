drawVeto(){
  
  TChain *ch = new TChain("tree");
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cal.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/be10_cal_firstVol.root");

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);

  ch->Draw("SQ20_1[0]:SSD_1[]");

}