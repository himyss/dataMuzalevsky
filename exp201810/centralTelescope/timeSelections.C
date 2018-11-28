void zeroVars();

//outtree vars
Int_t trigger; 

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Bool_t timesDSDX_C,timesDSDX_C,timesCsI;

void timeSelections() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("aCsI",&aCsI);
  ch->SetBranchAddress("tCsI",&tCsI);
  ch->SetBranchAddress("nCsI",&nCsI);

  ch->SetBranchAddress("DSDX_C",DSDX_C);
  ch->SetBranchAddress("tDSDX_C",&tDSDX_C);
  ch->SetBranchAddress("DSDY_C",&DSDY_C); 
  ch->SetBranchAddress("tDSDY_C",&tDSDY_C);


  TFile *fw = new TFile("/media/user/work/data/Analysed1811/selected/central_time.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger.",&trigger,"trigger/I");

  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("DSDX_C",&DSDX_C,"DSDX_C[32]/F");
  tw->Branch("tDSDX_C",&tDSDX_C,"tDSDX_C[32]/F");
  tw->Branch("DSDY_C",&DSDY_C,"DSDY_C[32]/F");
  tw->Branch("tDSDY_C",&tDSDY_C,"tDSDY_C[32]/F");

  for(Int_t nentry=0;nentry<1000;nentry++) {
    ch->GetEntry(nentry);
    zeroVars();

    for(Int_t i=0;i<32;i++) {
      
    }


    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  timesDSDX_C = kFALSE;
  timesDSDX_C = kFALSE;
  timesCsI = kFALSE;
}