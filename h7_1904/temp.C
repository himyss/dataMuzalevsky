{

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/selected/newCal/h7_*.root"); 
  cout << ch1->GetEntries() << endl;


  cout << ch1->Draw("trigger","nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )","") << endl;

  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/media/ivan/data/exp1904/analysed/novPars/selected/newCal/test/track0/h7_*.root"); 
  cout << ch2->GetEntries() << endl;

  cout << ch2->Draw("trigger","nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )","") << endl;


}