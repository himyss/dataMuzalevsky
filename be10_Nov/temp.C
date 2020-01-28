{

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_mm_secondVol.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_firstVol_mm.root");

  ch->SetMarkerStyle(7);
  ch->Draw("thetah7:th_h3*TMath::RadToDeg()","nh3 && thetah7 - th_h3>-10","");

  TF1 *fa = new TF1("fa","x",0,10);
  fa->SetLineColor(kRed);
  fa->Draw("same");

}