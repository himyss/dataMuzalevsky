{
  gStyle->SetOptStat(0);

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1904/analysed/h7/h7_test.root"); 

  ch1->SetMarkerSize(0.7);
  // ch1->SetMarkerColor(kRed);
  ch1->SetMarkerStyle(20);


  TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  c2->Divide(3,1);

  c2->cd(1);
  ch1->Draw("multc_x >> mult1(5,1,6)","","");

  c2->cd(2);
  ch1->Draw("multc_y >> mult2(5,1,6)","",""); 

  c2->cd(3);
  ch1->Draw("multCsI >> mult3(16,1,16)","","");

  c2->Update();

  c2->Print("/home/oem/Desktop/pics/exp1904/mult_cent.png");

  return;
}