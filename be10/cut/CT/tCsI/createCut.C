{
  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cut.root");
  cout << ch->GetEntries() << endl;


  // Int_t i = 15;
  TString cut,hdraw;
  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);

  // for(Int_t i =0;i<16;i++){
  c1->cd();
  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);      
  cut.Form("nCsI==%d && flagCent",i);
  hdraw.Form("aCsI:tCsI-tF5>>h%d(1000,250,600,4200,0,4200)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");
 
  ch->SetMarkerColor(kRed);
  ch->SetMarkerStyle(7);
  cut.Form("nCsI==%d && nh3 && flagCent && X_C>30 && X_C<45",i);
  hdraw.Form("aCsI:tCsI-tF5>>h_cut_%d(1000,250,600,4200,0,4200)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");

// return;
  TCanvas *c2 = new TCanvas("c2","title",1800,1000);
  c2->cd();
  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);      
  cut.Form("nCsI==%d && flagCent",i);
  hdraw.Form("X_C:aCsI>>hLi%d(4200,0,4200,300,20,100)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");

  ch->SetMarkerStyle(7);
  ch->SetMarkerColor(kRed);      
  cut.Form("nCsI==%d && flagCent && nh3 && X_C>30 && X_C<45",i);
  hdraw.Form("X_C:aCsI>>hLi_cut%d(4200,0,4200,300,20,100)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");


}