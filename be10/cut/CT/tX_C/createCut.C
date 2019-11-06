{
  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cut.root");
  cout << ch->GetEntries() << endl;


  Int_t i = 31;
  TString cut,hdraw;
  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);

  // for(Int_t i =0;i<16;i++){
  c1->cd();
  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);      
  cut.Form("nX_C==%d && flagCent",i);
  hdraw.Form("X_C:tX_C-tF5>>h%d(500,-200,0,500,0,105)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");
 
  ch->SetMarkerColor(kRed);
  ch->SetMarkerStyle(7);
  cut.Form("nX_C==%d && nh3 && flagCent",i);
  hdraw.Form("X_C:tX_C-tF5>>h_cut_%d(500,-200,0,500,0,105)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");


}