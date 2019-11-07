{
  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cut.root");
  cout << ch->GetEntries() << endl;


  Int_t i = 15;

  TString cut,hdraw;
  TCanvas *c1 = new TCanvas("c1","title",1800,1000);

  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);      
  cut.Form("n1_4==%d",i);
  hdraw.Form("a1_4:t1_4-tF5>>h%d1",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");

  c1->Update();

  ch->SetMarkerStyle(7);
  ch->SetMarkerColor(kRed);      
  cut.Form("n1_4==%d && nhe3_4",i);
  hdraw.Form("a1_4:t1_4-tF5>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");

  c1->Update();



}