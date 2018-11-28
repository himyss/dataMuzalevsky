{
  TChain *ch = new TChain("er");
  ch->Add("/media/user/work/data/analysisexp1804/Ana11/new/he8_*");

  cout << "Found " << ch->GetEntries() << " entries" << endl;
//--------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4);
  TString cut,hDraw;
  for(Int_t i=0;i<16;i++) {
    c1->cd(i+1);
    c1->GetPad(i+1)->SetLogz();

    hDraw.Form("ERQTelescopeCsIDigi_Central_telescope_CsI_0.fEdep:ERQTelescopeCsIDigi_Central_telescope_CsI_0.fTime-BeamDetToFDigi2.fTime >> h_%d(300,-500,1000,300,0,4000)",i);
    cut.Form("ERQTelescopeCsIDigi_Central_telescope_CsI_0.fBlockNb==%d",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col",10000000,0);    
    c1->Update();
  }

} 