void zeroVars();
void checktDSD_C();
void checkToF();
Bool_t CsIcuts();
//outtree vars
Int_t trigger; 

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t tF5,F5,tF3,F3;

Bool_t timesDSDX_C,timesDSDY_C,timesToF,timesCsI;

TCutG *cutCsI[16];

void timeSelections() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("aCsI.",&aCsI);
  ch->SetBranchAddress("tCsI.",&tCsI);
  ch->SetBranchAddress("nCsI.",&nCsI);

  ch->SetBranchAddress("DSDX_C",DSDX_C);
  ch->SetBranchAddress("tDSDX_C",&tDSDX_C);
  ch->SetBranchAddress("DSDY_C",&DSDY_C); 
  ch->SetBranchAddress("tDSDY_C",&tDSDY_C);

  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);


  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/exp201810/centralTelescope/cuts/CsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    delete f;
  }

  TFile *fw = new TFile("/media/user/work/data/Analysed1811/selected/central_times.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");

  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("DSDX_C",&DSDX_C,"DSDX_C[32]/F");
  tw->Branch("tDSDX_C",&tDSDX_C,"tDSDX_C[32]/F");
  tw->Branch("DSDY_C",&DSDY_C,"DSDY_C[32]/F");
  tw->Branch("tDSDY_C",&tDSDY_C,"tDSDY_C[32]/F");


  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);

    if (nCsI==9) {
      continue;
    } 

    zeroVars();

    timesCsI = CsIcuts();
    checktDSD_C();
    checkToF();


    if (timesDSDX_C==kTRUE && timesDSDY_C==kTRUE && timesCsI==kTRUE) tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  timesDSDX_C = kTRUE;
  timesDSDY_C = kTRUE;
  timesToF = kTRUE;
  timesCsI = kTRUE;
}

void checktDSD_C() {
  for(Int_t i=0;i<32;i++) {

    if (tDSDX_C[i]==0 && DSDX_C[i]==0) {
      timesDSDX_C = (timesDSDX_C && kTRUE);
    } else {
      if ( (tDSDX_C[i] - tF5 > 80) && (tDSDX_C[i] - tF5 <140)) {
        timesDSDX_C = (timesDSDX_C && kTRUE);
      } else {
        timesDSDX_C = (timesDSDX_C && kFALSE);
      }
    }

    if (tDSDY_C[i]==0 && DSDY_C[i]==0){
      timesDSDY_C = (timesDSDY_C && kTRUE);   
    } else {
      if ( (tDSDY_C[i] - tF5 > 80) && (tDSDY_C[i] - tF5 <140)){
        timesDSDY_C = (timesDSDY_C && kTRUE);    
      } else {
        timesDSDY_C = (timesDSDY_C && kFALSE);
      }
    } 
  
  }
}

void checkToF() {
  if(F5<2400 || F5<4400 || tF5-tF3<103 || tF5-tF3>115 || F3<2000 || F3<4000 ) timesToF = kFALSE;
  return;
}

Bool_t CsIcuts() {
  if(cutCsI[nCsI]->IsInside(tCsI-tF5, aCsI)) {
    return kTRUE;
  }
  else {
    return kFALSE;
  }
}
