{
  
  TChain *ch = new TChain("er");
  ch->Add("/media/ivan/data/exp1904/digi/h7_ct_11_*.root");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;


  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(4,4);

  TString cut,hdraw;

  for(Int_t i=0;i<16;i++) {
    
    c1->cd(i+1);

    hdraw.Form("1000*Max$(ERQTelescopeCsIDigi_Central_telescope_CsI_0.fEdep)");
    cut.Form("ERQTelescopeCsIDigi_Central_telescope_CsI_0.fBlockNb==%d",i);

    ch->Draw(hdraw.Data(),cut.Data(),"");

    // tv__tree->Draw("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_XY_0_X.fEdep:Max$(ERQTelescopeCsIDigi_Central_telescope_CsI_0.fEdep)","","", 21217, 0);
    c1->Update();
  }



}