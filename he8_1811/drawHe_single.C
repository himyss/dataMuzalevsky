void drawHe_single() {
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/he8_missing_mass.root");
  
    // ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_selected.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------


  // --------------------------------------------------------------------------------
  
  // gStyle->SetOptStat(0);
  // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // c2->Divide(4,4);
  TString cut,hDraw;


  //--------------------------------------------------------------------------------
  gStyle->SetOptStat(0);

  // TString cut,hDraw;

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(2,2);
  c1->cd(1);

  Int_t i =0;
  ch->SetMarkerSize(0.5);
  ch->SetMarkerColor(kBlack);
  cut.Form("flagLeft && X_L>0 && n20_L>8");
  hDraw.Form("a20_L:X_L>>h%d(400,0,50,400,0,4)",i);
  ch->Draw(hDraw.Data(),cut.Data(),"col");
  
  // ch->SetMarkerSize(0.5);
  // cut.Form("flagLeft && X_L>0 && nh3 && flagCent");
  // ch->SetMarkerColor(kRed);
  ch->SetMarkerStyle(20);
  // hDraw.Form("a20_L:X_L>>hred%d(200,0,50,200,0,4)",i);
  // ch->Draw(hDraw.Data(),cut.Data(),"same");

  ch->SetMarkerSize(0.7);
  cut.Form("flagLeft && X_L>0 && nh3 && nhe3 && flagCent && n20_L>8");
  ch->SetMarkerColor(kMagenta);
  hDraw.Form("a20_L:X_L>>hred_he3_%d(200,0,50,200,0,4)",i);
  ch->Draw(hDraw.Data(),cut.Data(),"same");


  ch->SetMarkerColor(kBlack);
  ch->SetMarkerSize(1);
  c1->cd(2);
  ch->Draw("1000*ehe3/3.:angle_he3_he8 >> h2D_1","nhe3 && flagLeft && flagCent && nh3 && n20_L>8","");

  c1->cd(3);
  ch->Draw("1000*ehe3/3.:angle_he3_h7 >> h2D_2","nhe3 && flagLeft && flagCent && nh3 && n20_L>8","");



  c1->Update();




  
}