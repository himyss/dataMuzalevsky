 { 

  TChain *ch1 = new TChain("tree");
  ch1->Add("/media/oem/data/exp1906/analysed/be10_ct_cut.root");

  TChain *ch2 = new TChain("tree");
  ch2->Add("/media/oem/data/exp1906/analysed/be10_ct.root");

  // TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(2,1);

  // c1->cd(1);
  // ch1->Draw("X_C:aCsI >> h1(1000,0,3000,100,0,60)","nCsI==1 && flagCent","col");

  // c1->cd(2);
  // ch2->Draw("X_C:aCsI >> h2(1000,0,3000,100,0,60)","nCsI==1 && flagCent","col");

 TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(2,1);

  // c1->cd(1);
  // ch1->Draw("X_C:aCsI >> h1(1000,0,3000,100,0,60)","nCsI==1 && flagCent","col");

  ch2->Draw("multc_x:X_C_max","X_C_max>5 && X_C_max<60","BOX");
// Max$(formula)
  // ch2->Draw("nX_C:X_C","X_C>5 && X_C<60","BOX");

}