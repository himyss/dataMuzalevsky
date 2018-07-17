{

  TChain *ch = new TChain("tree");
	ch->Add("tracking1.root");

  TCanvas *c1 = new TCanvas("c1","canvas",1800,1000);
  c1->Divide(2,2);
  c1->cd(1);
  ch->Draw("nCsM","","");

  c1->cd(2);
  ch->Draw("nCs","","");
  
  c1->cd(3);
  ch->Draw("yCs0:xCs0","","col");

  c1->cd(4);
  ch->Draw("nCsM - nCs","","");


//ch->Draw("nCs","nCsM==9","", 32184, 0);
}
