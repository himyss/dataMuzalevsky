{
  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1904/analysed/oldPars/select_noveto.root");

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(2,2);

  c1->cd(1);
  ch1->Draw("phi_he3_1*TMath::RadToDeg()","th_he3_1>0 && phi_he3_1>0","");

  c1->cd(2);
  ch1->Draw("th_he3_1*TMath::RadToDeg()","th_he3_1>0 && phi_he3_1>0","");

  c1->cd(3);
  ch1->Draw("phi_he3_1*TMath::RadToDeg()","th_he3_1*TMath::RadToDeg()>7 && th_he3_1*TMath::RadToDeg()<8 && phi_he3_1>0","");

}