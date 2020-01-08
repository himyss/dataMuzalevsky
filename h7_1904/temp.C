{

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/calibrated/newCal/eTarget/h7*"); 

  cout << ch1->GetEntries() << endl;


}