void profile(){
  

  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_ct_thinTarget_cut.root");
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_ct_firstVol_cut.root");
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_ct_secondVol_cut.root");

  // TChain *ch2 = new TChain("tree"); //e4

  TCanvas *c1 = new TCanvas("c1","beamProfile",1000,1000);
  c1->Divide(2,2);

  c1->cd(1);
  cout << ch2->Draw("trigger","trigger==1") << endl;
  c1->Update();

  c1->cd(2);
  cout << ch2->Draw("trigger","trigger==2") << endl;
  c1->Update();

  c1->cd(3);
  cout << ch2->Draw("trigger","trigger==3") << endl;
  c1->Update();

  c1->cd(4);
  cout << ch2->Draw("trigger","trigger==4") << endl;
  c1->Update();

  c1->cd(1);
  cout << ch2->Draw("trigger","trigger==5") << endl;
  c1->Update();

  return;
}