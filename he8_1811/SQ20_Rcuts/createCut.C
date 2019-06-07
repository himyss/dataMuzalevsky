{
  
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all_cut.root");
  cout << ch->GetEntries() << endl;

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);

  ch->Draw("a20_R:t20_R-tF5 >> (500,-60,60,500,0,30)","n20_R==15","col");

}