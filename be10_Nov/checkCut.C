void checkCut() {
  
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1906/analysed/be10_ct.root");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  TChain *ch1 = new TChain("tree");
  ch1->Add("/home/oem/work/data/exp1906/analysed/be_10_cut.root");  

  TCanvas *c1 = new TCanvas("c1","",1800,1000);
  c1->Divide(2,1);

  c1->cd(1);  
  ch->Draw("F5:tF5-tF3 >> f5(1000,40,130,12000,0,12000)","","col");

  c1->cd(2);  
  ch1->Draw("F5:tF5-tF3 >> f5_cut(1000,40,130,12000,0,12000)","","col");
  // ch->Draw("F5:tF5-tF3 >> f5_cut(400,0,200,12000,4000,16000)","F5>4500 && F5>7500 &&  tF5-tF3>66.5 && tF5-tF3<71","col");

}