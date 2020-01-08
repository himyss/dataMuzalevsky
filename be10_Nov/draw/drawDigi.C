void drawDigi(){
  
  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/be10_cal_1.root");
  cout << ch->GetEntries() << endl;

  TString hdraw,hcut;

  TCanvas *c1 = new TCanvas("c1","de_E",1800,1000);
  c1->Divide(2,2);

  Int_t stripN;

  c1->cd(1);
  hdraw.Form("SQ20_1[]:SSD1[] >>de_E1(200,1,60,200,0.1,5)");
  hcut.Form("trigger==2");  
  ch->Draw(hdraw.Data(),hcut.Data(),"col");
  hcut.Form("trigger==2 && "); 


  c1->cd(2);
  hdraw.Form("SQ20_2[]:SSD2[] >>de_E2(200,1,60,200,0.1,5)");
  hcut.Form("trigger==3");  
  ch->Draw(hdraw.Data(),hcut.Data(),"col");



}