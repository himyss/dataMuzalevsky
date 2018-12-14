Int_t GetClusterMult(TClonesArray *data);
ERQTelescopeCsIDigi* processCsI(TClonesArray *data);
Int_t GetClusterMWPC(TClonesArray *data);
Int_t GetClusterSi(TClonesArray *data);

void zeroVars();
void tempfunc(TClonesArray *data);

void fillCsI(ERQTelescopeCsIDigi *data);
void fillSi(TClonesArray *data,Float_t* amp,Float_t* time);

void fillF5(TClonesArray *data);
void fillF3(TClonesArray *data);
void fillMWPC(TClonesArray *data,Float_t *wire);

//outtree vars
Int_t trigger; 

Float_t F5,tF5,F3,tF3;

Float_t wirex1,wirex2,wirey1,wirey2;
Float_t tMWPC;

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16];
Float_t tDSDX_L[16],tDSDY_L[16],tSSD20_L[16],tSSD_L[16];

Float_t SSD20_R[16],SSDY_R[16],SSD_R[16];
Float_t tSSD20_R[16],tSSDY_R[16],tSSD_R[16];

// flags
Bool_t flagCsI;

void convert() {

  TChain *ch = new TChain("er");
  ch->Add("/media/user/work/data/Analysed1811/digi/BeamDetSelection/he8_10*");
  // ch->Add("/media/user/work/data/Analysed1811/digi/he8_10_0001.Digi.root");

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

  TClonesArray *v_DSDX_L = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_DSDY_L = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD20_L = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_L = new TClonesArray("ERQTelescopeSiDigi");

  TClonesArray *v_SSD20_R = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSDY_R = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_R = new TClonesArray("ERQTelescopeSiDigi");

  // 
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
 
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X",&v_DSDX_L);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_Y",&v_DSDY_L);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0",&v_SSD20_L);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD_L_X_0",&v_SSD_L);

  ch->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0",&v_SSD20_R);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0",&v_SSDY_R);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0",&v_SSD_R);  

  ch->SetBranchAddress("EventHeader.",&header);

  TFile *f;
  TString cutName;

  // Creating outfile,outtree

  TFile *fw = new TFile("/media/user/work/data/Analysed1811/selected/trigger1.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");

  tw->Branch("tMWPC.",&tMWPC,"tMWPC/F");
  tw->Branch("wirex1.",&wirex1,"wirex1/F");
  tw->Branch("wirex2.",&wirex2,"wirex2/F");
  tw->Branch("wirey1.",&wirey1,"wirey1/F");
  tw->Branch("wirey2.",&wirey2,"wirey2/F");

  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("DSDX_C",&DSDX_C,"DSDX_C[32]/F");
  tw->Branch("tDSDX_C",&tDSDX_C,"tDSDX_C[32]/F");
  tw->Branch("DSDY_C",&DSDY_C,"DSDY_C[32]/F");
  tw->Branch("tDSDY_C",&tDSDY_C,"tDSDY_C[32]/F");

  tw->Branch("DSDX_L",&DSDX_L,"DSDX_L[16]/F");
  tw->Branch("DSDY_L",&DSDY_L,"DSDY_L[16]/F");
  tw->Branch("SSD20_L",&SSD20_L,"SSD20_L[16]/F");
  tw->Branch("SSD_L",&SSD_L,"SSD_L[16]/F");
  tw->Branch("tDSDX_L",&tDSDX_L,"tDSDX_L[16]/F");
  tw->Branch("tDSDY_L",&tDSDY_L,"tDSDY_L[16]/F");
  tw->Branch("tSSD20_L",&tSSD20_L,"tSSD20_L[16]/F");
  tw->Branch("tSSD_L",&tSSD_L,"tSSD_L[16]/F");
  tw->Branch("SSD20_R",&SSD20_R,"SSD20_R[16]/F");
  tw->Branch("SSDY_R",&SSDY_R,"SSDY_R[16]/F");
  tw->Branch("SSD_R",&SSD_R,"SSD_R[16]/F");
  tw->Branch("tSSD20_R",&tSSD20_R,"tSSD20_R[16]/F");
  tw->Branch("tSSDY_R",&tSSDY_R,"tSSDY_R[16]/F");
  tw->Branch("tSSD_R",&tSSD_R,"tSSD_R[16]/F");

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) {
    if(nentry%100000==0) cout << "#Event " << nentry << "#" << endl;
    ch->GetEntry(nentry);
    flagCsI = kTRUE;
    // if(v_MWPCx1->GetEntriesFast()==0) continue;
    // if(v_MWPCx2->GetEntriesFast()==0) continue;
    // if(v_MWPCy1->GetEntriesFast()==0) continue;
    // if(v_MWPCy2->GetEntriesFast()==0) continue;
    if(v_F3->GetEntriesFast()==0) continue;
    if(v_F5->GetEntriesFast()==0) continue;

    if (GetClusterMWPC(v_MWPCx1)!=1) continue;
    if (GetClusterMWPC(v_MWPCx2)!=1) continue;
    if (GetClusterMWPC(v_MWPCy1)!=1) continue;
    if (GetClusterMWPC(v_MWPCy2)!=1) continue;
    
    if (GetClusterSi(v_DSDX_C)>1) continue;
    if (GetClusterSi(v_DSDY_C)>1) continue;

    if (GetClusterSi(v_SSD20_R)>1) continue;
    if (GetClusterSi(v_SSDY_R)>1) continue;
    if (GetClusterSi(v_SSD_R)>1) continue;

    if (GetClusterSi(v_DSDX_L)>1) continue;
    if (GetClusterSi(v_DSDY_L)>1) continue;
    if (GetClusterSi(v_SSD20_L)>1) continue;
    if (GetClusterSi(v_SSD_L)>1) continue;

    
    m_CsI = processCsI(v_CsI); // kinda CsIClusters
    if(!flagCsI) {
      continue;
    }

    zeroVars();

    // // fill the vars
    trigger = header->GetTrigger();

    fillF5(v_F5);
    fillF3(v_F3);

    tMWPC = ((ERBeamDetMWPCDigi*)v_MWPCx1->At(0))->GetTime();
    fillMWPC(v_MWPCx1,&wirex1);
    fillMWPC(v_MWPCx2,&wirex2);
    fillMWPC(v_MWPCy1,&wirey1);
    fillMWPC(v_MWPCy2,&wirey2);

    fillCsI(m_CsI);
    fillSi(v_DSDY_C,DSDY_C,tDSDY_C); 
    fillSi(v_DSDX_C,DSDX_C,tDSDX_C);   

    fillSi(v_DSDX_L,DSDX_L,tDSDX_L);
    fillSi(v_DSDY_L,DSDY_L,tDSDY_L);
    fillSi(v_SSD20_L,SSD20_L,tSSD20_L);
    fillSi(v_SSD_L,SSD_L,tSSD_L);

    fillSi(v_SSD20_R,SSD20_R,tSSD20_R);
    fillSi(v_SSDY_R,SSDY_R,tSSDY_R);
    fillSi(v_SSD_R,SSD_R,tSSD_R);

    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  trigger = -1;

  F5 = 0;
  tF5 = 0;
  F3 = 0;
  tF3 = 0;

  wirex1 = -10;
  wirex2 = -10;
  wirey1 = -10;
  wirey2 = -10;
  tMWPC = 0;

  nCsI = 0;
  aCsI = 0;
  tCsI = 0;

  for(Int_t i=0;i<16;i++) {
    DSDX_L[i] = 0;
    DSDY_L[i] = 0;
    SSD20_L[i] = 0;
    SSD_L[i] = 0;
    tDSDX_L[i] = 0;
    tDSDY_L[i] = 0;
    tSSD20_L[i] = 0;
    tSSD_L[i] = 0;
  }

  for(Int_t i=0;i<16;i++) {
    SSD20_R[i] = 0;
    SSDY_R[i] = 0;
    SSD_R[i] = 0;
    tSSD20_R[i] = 0;
    tSSDY_R[i] = 0;
    tSSD_R[i] = 0;
  }

  for(Int_t i=0;i<32;i++) {
    DSDX_C[i] = 0;
    DSDY_C[i] = 0;
    tDSDX_C[i] = 0;
    tDSDY_C[i] = 0;
  }
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

    if ( abs(strip1 - strip2) > 1 && abs(strip1 - strip2) < 16) noclusters++;
  }

  return noclusters;
}

ERQTelescopeCsIDigi* processCsI(TClonesArray *data) {

  // cout << "processCsI was called " << endl;
  if (!data) return NULL;
  if(data->GetEntriesFast()==0) return NULL;

  Double_t maxAmp = 0;
  ERQTelescopeCsIDigi *temp_CsI;
  ERQTelescopeCsIDigi *temp_CsImax;
  // find maximum 
  for(Int_t i = 0; i < data->GetEntriesFast(); i++) {
    temp_CsI = ((ERQTelescopeCsIDigi*)data->At(i));
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
  if (nMax!=1) {
    cout << nMax << endl; 
    flagCsI = kFALSE;
    return NULL;
  }

  return temp_CsImax;
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

Int_t GetClusterSi(TClonesArray *data) {
  if (!data) return 0;

  Int_t entries = data->GetEntriesFast();

  if (entries<2) return entries;

  Int_t wire1, wire2;
  Int_t noclusters = 1;

  for (Int_t i = 1; i < entries; i++) {
    //check if entries are in specific order
    wire1 = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
    wire2 = ((ERQTelescopeSiDigi*)data->At(i-1))->GetStripNb();

    //todo number 32 is related to number of wires
    // and should be taken from Parameters
    if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 16) noclusters++;
  }

  return noclusters;
}

void fillMWPC(TClonesArray *data,Float_t *wire) {
  if (!data) return;

  *(wire) = ((ERBeamDetMWPCDigi*)data->At(0))->GetWireNb() + ((ERBeamDetMWPCDigi*)data->At(data->GetEntriesFast()-1))->GetWireNb();
  *(wire) = *(wire)/2; 

  return;
}

void fillCsI(ERQTelescopeCsIDigi *data) {
  if (!data) return;
  nCsI = data->GetBlockNb();
  tCsI = data->GetTime();
  aCsI = data->GetEdep();
  return;  
}

void fillSi(TClonesArray *data,Float_t* amp,Float_t* time) {
  if(!data) return;
  if(data->GetEntriesFast()==0) return;

  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) {
    nCh = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
    *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep();
    *(time+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetTime();
  } 
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
