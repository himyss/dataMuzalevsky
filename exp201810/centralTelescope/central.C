Int_t GetClusterMult(TClonesArray *data);
ERQTelescopeCsIDigi* processCsI(TClonesArray *data);
Int_t GetClusterMWPC(TClonesArray *data);


void zeroVars();
void tempfunc(TClonesArray *data);

void fillCsI(ERQTelescopeCsIDigi *data);
void fillDSDX_C(TClonesArray *data);
void fillDSDY_C(TClonesArray *data);
void fillF5(TClonesArray *data);
void fillF3(TClonesArray *data);

Bool_t CsIcuts();
//outtree vars
Int_t trigger; 

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t F5,tF5,F3,tF3;

Int_t wirex1,wirex2,wirey1,wirey2;
Float_t tMWPC;

Int_t multX,multY;

TCutG *cutCsI[16];

void central() {

  TChain *ch = new TChain("er");
  ch->Add("/media/user/work/data/Analysed1811/he8_*");

  cout << "Found " << ch->GetEntries() << " entries" << endl;
//--------------------------------------------------------------------------------
  ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();

  TClonesArray *v_DSDX_C = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_DSDY_C = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_CsI = new TClonesArray("ERQTelescopeCsIDigi");

  TClonesArray *v_F5 = new TClonesArray("ERBeamDetTOFDigi");
  TClonesArray *v_F3 = new TClonesArray("ERBeamDetTOFDigi");  

  TClonesArray *v_MWPCx1 = new TClonesArray("ERBeamDetMWPCDigi");
  TClonesArray *v_MWPCy1 = new TClonesArray("ERBeamDetMWPCDigi");  
  TClonesArray *v_MWPCx2 = new TClonesArray("ERBeamDetMWPCDigi");
  TClonesArray *v_MWPCy2 = new TClonesArray("ERBeamDetMWPCDigi"); 


  ERQTelescopeSiDigi *m_DSDX_C;
  ERQTelescopeSiDigi *m_DSDY_C;
  ERQTelescopeCsIDigi *m_CsI;
  ERBeamDetTOFDigi *m_F5;
  ERBeamDetTOFDigi *m_F3;  

  Int_t multDSDX_C,multDSDY_C;

  // setbranchAdress
  ch->SetBranchAddress("BeamDetToFDigi2",&v_F5);
  ch->SetBranchAddress("BeamDetToFDigi1",&v_F3);

  ch->SetBranchAddress("BeamDetMWPCDigiX1",&v_MWPCx1);
  ch->SetBranchAddress("BeamDetMWPCDigiX2",&v_MWPCx2);
  ch->SetBranchAddress("BeamDetMWPCDigiY1",&v_MWPCy1);
  ch->SetBranchAddress("BeamDetMWPCDigiY2",&v_MWPCy2);  

  ch->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X",&v_DSDX_C);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_Y",&v_DSDY_C);
  ch->SetBranchAddress("ERQTelescopeCsIDigi_Central_telescope_CsI_0",&v_CsI);
 
  ch->SetBranchAddress("EventHeader.",&header);

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/exp201810/centralTelescope/cuts/CsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    delete f;
  }


  // Creating outfile,outtree

  TFile *fw = new TFile("/media/user/work/data/Analysed1811/selected/test.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");

  // tw->Branch("tMWPC.",&tMWPC,"tMWPC/F");
  // tw->Branch("wirex1.",&wirex1,"wirex1/I");
  // tw->Branch("wirex2.",&wirex2,"wirex2/I");
  // tw->Branch("wirey1.",&wirey1,"wirey1/I");
  // tw->Branch("wirey2.",&wirey2,"wirey2/I");

  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("DSDX_C",&DSDX_C,"DSDX_C[32]/F");
  tw->Branch("tDSDX_C",&tDSDX_C,"tDSDX_C[32]/F");
  tw->Branch("DSDY_C",&DSDY_C,"DSDY_C[32]/F");
  tw->Branch("tDSDY_C",&tDSDY_C,"tDSDY_C[32]/F");

  // tw->Branch("multX",&multX,"multX/I");
  // tw->Branch("multY",&multY,"multY/I");  

  for(Int_t nentry=1;nentry<1000000;nentry++) {
    if(nentry%100000==0) cout << "#Event " << nentry << "#" << endl;
    ch->GetEntry(nentry);

    multDSDX_C = GetClusterMult(v_DSDX_C);
    multDSDY_C = GetClusterMult(v_DSDY_C);

    if(multDSDX_C!=1 && multDSDY_C!=1) {
      continue;
    }

    m_CsI = processCsI(v_CsI);
    if(!m_CsI) {
      continue;
    }

    if (GetClusterMWPC(v_MWPCx1)!=1 || GetClusterMWPC(v_MWPCx2)!=1 || GetClusterMWPC(v_MWPCy1)!=1 || GetClusterMWPC(v_MWPCy2)!=1) {
      continue;
    }

    if(v_F5->GetEntriesFast()==0 || v_F3->GetEntriesFast()==0) {
      continue;
    }

    zeroVars();

    // fill the vars
    fillF5(v_F5);
    fillF3(v_F3);
    trigger = header->GetTrigger();
    fillCsI(m_CsI);
    fillDSDX_C(v_DSDX_C);
    fillDSDY_C(v_DSDY_C);    

    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

Int_t GetClusterMult(TClonesArray *data) {

  if (!data) return 0;

  Int_t entries = data->GetEntriesFast();

  if (entries<2) return entries;

  Int_t strip1, strip2;
  Int_t noclusters = 1;

  for (Int_t i = 1; i < entries; i++) {
    //check if entries are in specific order
    strip1 = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
    strip2 = ((ERQTelescopeSiDigi*)data->At(i-1))->GetStripNb();

   // cout << strip2 << "\t" << strip1 << endl;
    //todo number 32 is related to number of wires
    // and should be taken from Parameters
    if ( abs(strip1 - strip2) > 1 && abs(strip1 - strip2) < 16) noclusters++;
  }

  return noclusters;
}

void fillF5(TClonesArray *data){
  if (!data) return;
  ERBeamDetTOFDigi *temp_F5 = ((ERBeamDetTOFDigi*)data->At(0));
  if(!temp_F5) return;

  F5 = temp_F5->GetEdep();
  tF5 = temp_F5->GetTime();

  return; 
}

void fillF3(TClonesArray *data){
  if (!data) return;
  ERBeamDetTOFDigi *temp_F3 = ((ERBeamDetTOFDigi*)data->At(0));
  if(!temp_F3) return;

  F3 = temp_F3->GetEdep();
  tF3 = temp_F3->GetTime();

  return; 
}


ERQTelescopeCsIDigi* processCsI(TClonesArray *data) {

  // cout << "processCsI was called " << endl;
  if (!data) return NULL;

  Double_t maxAmp = 0;
  ERQTelescopeCsIDigi *temp_CsI;
  ERQTelescopeCsIDigi *temp_CsImax;
  // find maximum 
  for(Int_t i = 0; i < data->GetEntriesFast(); i++) {
    temp_CsI = ((ERQTelescopeCsIDigi*)data->At(i));
    // cout << CsI->GetEdep() << " " << CsI->GetBlockNb() << endl;
    if(temp_CsI->GetEdep() > maxAmp) {
      maxAmp = temp_CsI->GetEdep();
      temp_CsImax = temp_CsI; 
    } 
  }
  // check if there is only 1 maximum
  Int_t nMax = 0;
  for(Int_t i=0; i<data->GetEntriesFast(); i++) {
    if (((ERQTelescopeCsIDigi*)data->At(i))->GetEdep() == maxAmp) nMax++;
  }
  if (nMax!=1) return NULL;

  // if(temp_CsImax->GetBlockNb()==9) return NULL;

  return temp_CsImax;
}

void zeroVars() {
  multX=0;
  multY=0;
  trigger = 0;
  nCsI = 0;
  aCsI = 0;
  tCsI = 0;
  F5 = 0;
  tF5 = 0;
  F3 = 0;
  tF3 = 0;
  for(Int_t i=0;i<32;i++) {
    DSDX_C[i] = 0;
    DSDY_C[i] = 0;
    tDSDX_C[i] = 0;
    tDSDY_C[i] = 0;
  }
}

void fillCsI(ERQTelescopeCsIDigi *data) {
  nCsI = data->GetBlockNb();
  tCsI = data->GetTime();
  aCsI = data->GetEdep();
  return;  
}

void fillDSDX_C(TClonesArray *data) {
  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) {
    nCh = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
    DSDX_C[nCh] = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep();
    tDSDX_C[nCh] = ((ERQTelescopeSiDigi*)data->At(i))->GetTime()*25./30.;
  }
}

void fillDSDY_C(TClonesArray *data) {
  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) {
    nCh = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
    DSDY_C[nCh] = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep();
    tDSDY_C[nCh] = ((ERQTelescopeSiDigi*)data->At(i))->GetTime()*25./30.;
  }
}

void tempfunc(TClonesArray *data) {

   // cout << "processCsI was called " << endl;
  if (!data) return NULL;

  Double_t maxAmp = 0;
  ERQTelescopeCsIDigi *temp_CsI;
  ERQTelescopeCsIDigi *temp_CsImax;
  // find maximum 
  for(Int_t i = 0; i < data->GetEntriesFast(); i++) {
    temp_CsI = ((ERQTelescopeCsIDigi*)data->At(i));
    if(temp_CsI->GetEdep() < 1000 | temp_CsI->GetTime() < 175) multX++;
  }

  return;
}

Int_t GetClusterMWPC(TClonesArray *data) {

  if (!data) return 0;

  Int_t entries = data->GetEntriesFast();

  if (entries<2) return entries;

  Int_t wire1, wire2;
  Int_t noclusters = 1;

  for (Int_t i = 1; i < entries; i++) {
    //check if entries are in specific order
    wire1 = ((ERBeamDetMWPCDigi*)data->At(i))->GetWireNb();
    wire2 = ((ERBeamDetMWPCDigi*)data->At(i-1))->GetWireNb();

    //todo number 32 is related to number of wires
    // and should be taken from Parameters
    if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 32) noclusters++;
  }

  return noclusters;
}

Bool_t CsIcuts() {
  if(cutCsI[nCsI]->IsInside(tCsI-tF5, aCsI)) {
    return kTRUE;
  }
  else {
    return kFALSE;
  }
}
