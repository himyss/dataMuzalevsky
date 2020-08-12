Int_t GetClusterMWPC(TClonesArray *data);
void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void fillSi(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2,Int_t *multiplicity, Float_t ampThreshold,Float_t timeThreshold=0);
void fillarrayCsI(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2);

void processCsI_cal();

void zeroVars();

void fillF5(TClonesArray *data);
void fillF3(TClonesArray *data);
void fillMWPC(TClonesArray *data,Float_t *wire);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Int_t GetClusterSi(TClonesArray *data);
Int_t GetClusterMult(TClonesArray *data);
ERQTelescopeCsIDigi* processCsI(TClonesArray *data);

void fillCsI(ERQTelescopeCsIDigi *data);
//outtree vars
Int_t trigger; 

Float_t F5,tF5,F3,tF3;

Float_t wirex1,wirex2,wirey1,wirey2;
Float_t tMWPC[4];

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Float_t arCsI[16],trCsI[16];

Float_t DSD_X[32],DSD_Y[32];
Float_t tDSD_X[32],tDSD_Y[32];

Float_t SQ20_1[16],SSD1[16],SSD_V1[16];
Float_t tSQ20_1[16],tSSD1[16],tSSD_V1[16];


Float_t SQ20_2[16],SSD2[16],SSD_V2[16];
Float_t tSQ20_2[16],tSSD2[16],tSSD_V2[16];

Float_t SQ20_3[16],SSD3[16],SSD_V3[16];
Float_t tSQ20_3[16],tSSD3[16],tSSD_V3[16];

Float_t SQ20_4[16],SSD4[16],SSD_V4[16];
Float_t tSQ20_4[16],tSSD4[16],tSSD_V4[16];

// Sipars
Float_t pSQ201_1[16],pSQ201_2[16];
Float_t pSQ202_1[16],pSQ202_2[16];
Float_t pSQ203_1[16],pSQ203_2[16];
Float_t pSQ204_1[16],pSQ204_2[16];

Float_t pSSD1_1[16],pSSD1_2[16];
Float_t pSSD2_1[16],pSSD2_2[16];
Float_t pSSD3_1[16],pSSD3_2[16];
Float_t pSSD4_1[16],pSSD4_2[16];

Float_t pSSD_V1_1[16],pSSD_V1_2[16];
Float_t pSSD_V2_1[16],pSSD_V2_2[16];
Float_t pSSD_V3_1[16],pSSD_V3_2[16];
Float_t pSSD_V4_1[16],pSSD_V4_2[16];


Float_t pDSD_X1[32],pDSD_X2[32];
Float_t pDSD_Y1[32],pDSD_Y2[32];

Float_t pCsI_1[16],pCsI_2[16];

Float_t *nullPtr = NULL;

//
Int_t mult20_1,mult1_1,multv_1;
Int_t mult20_2,mult1_2,multv_2;
Int_t mult20_3,mult1_3,multv_3;
Int_t mult20_4,mult1_4,multv_4;

Int_t multc_x,multc_y,multCsI;

void convert(TString InFile, TString OutFile) {

  TChain *ch = new TChain("er");
  ch->Add(InFile.Data());
  // ch->Add("/media/ivan/data/exp1904/digi/h7/h7_ct_40*.root");
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  // readPar("SSD_20u_1_cal",pSQ201_1,pSQ201_2);
  // readPar("SSD_20u_2_cal",pSQ202_1,pSQ202_2);
  // readPar("SSD_20u_3_cal",pSQ203_1,pSQ203_2);
  // readPar("SSD_20u_4_cal",pSQ204_1,pSQ204_2);

  // readPar("SSD_1m_1_cal",pSSD1_1,pSSD1_2);
  // readPar("SSD_1m_2_cal",pSSD2_1,pSSD2_2);
  // readPar("SSD_1m_3_cal",pSSD3_1,pSSD3_2);
  // readPar("SSD_1m_4_cal",pSSD4_1,pSSD4_2);

  // readPar("SSD_1m_1_v_cal",pSSD_V1_1,pSSD_V1_2);
  // readPar("SSD_1m_2_v_cal",pSSD_V2_1,pSSD_V2_2);  
  // readPar("SSD_1m_3_v_cal",pSSD_V3_1,pSSD_V3_2);
  // readPar("SSD_1m_4_v_cal",pSSD_V4_1,pSSD_V4_2);

  // readPar("DSSD_X",pDSD_X1,pDSD_X2,32);
  // readPar("DSSD_Y",pDSD_Y1,pDSD_Y2,32);

  // readPar("empty16",pCsI_1,pCsI_2);

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

  TClonesArray *v_SSD_V_1 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD20_1 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_1 = new TClonesArray("ERQTelescopeSiDigi");

  TClonesArray *v_SSD_V_2 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD20_2 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_2 = new TClonesArray("ERQTelescopeSiDigi");

  TClonesArray *v_SSD_V_3 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD20_3 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_3 = new TClonesArray("ERQTelescopeSiDigi");

  TClonesArray *v_SSD_V_4 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD20_4 = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_4 = new TClonesArray("ERQTelescopeSiDigi");


  // setbranchAdress
  ch->SetBranchAddress("BeamDetToFDigi2",&v_F5);
  ch->SetBranchAddress("BeamDetToFDigi1",&v_F3);

  ch->SetBranchAddress("BeamDetMWPCDigiX1",&v_MWPCx1);
  ch->SetBranchAddress("BeamDetMWPCDigiX2",&v_MWPCx2);
  ch->SetBranchAddress("BeamDetMWPCDigiY1",&v_MWPCy1);
  ch->SetBranchAddress("BeamDetMWPCDigiY2",&v_MWPCy2);  

  ch->SetBranchAddress("EventHeader.",&header);

  TFile *f;
  TString cutName;

  // Creating outfile,outtree
  TFile *fw = new TFile(OutFile.Data(), "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");

  tw->Branch("tMWPC.",&tMWPC,"tMWPC[4]/F");
  tw->Branch("wirex1.",&wirex1,"wirex1/F");
  tw->Branch("wirex2.",&wirex2,"wirex2/F");
  tw->Branch("wirey1.",&wirey1,"wirey1/F");
  tw->Branch("wirey2.",&wirey2,"wirey2/F");

  tw->Branch("x1c.",&x1c,"x1c/F"); // position in MWPC in mm
  tw->Branch("y1c.",&y1c,"y1c/F");
  tw->Branch("x2c.",&x2c,"x2c/F");
  tw->Branch("y2c.",&y2c,"y2c/F"); 
  tw->Branch("fXt.",&fXt,"fXt/F"); // beam profile at the target plane
  tw->Branch("fYt.",&fYt,"fYt/F"); 

  // for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) {
  for(Int_t nentry=0;nentry<100;nentry++) {    
    if(nentry%1000000==0) cout << "#Event " << nentry << "#" << endl;
    ch->GetEntry(nentry);
    if(v_MWPCx1->GetEntriesFast()==0) continue;
    if(v_MWPCx2->GetEntriesFast()==0) continue;
    if(v_MWPCy1->GetEntriesFast()==0) continue;
    if(v_MWPCy2->GetEntriesFast()==0) continue;

    if (GetClusterMWPC(v_MWPCx1)!=1) continue;
    if (GetClusterMWPC(v_MWPCx2)!=1) continue;
    if (GetClusterMWPC(v_MWPCy1)!=1) continue;
    if (GetClusterMWPC(v_MWPCy2)!=1) continue;  

    trigger = header->GetTrigger();

    zeroVars();

  // beamdet
    fillF5(v_F5);
    fillF3(v_F3);
  
    tMWPC[0] = ((ERBeamDetMWPCDigi*)v_MWPCx1->At(0))->Time();
    tMWPC[1] = ((ERBeamDetMWPCDigi*)v_MWPCy1->At(0))->Time();
    tMWPC[2] = ((ERBeamDetMWPCDigi*)v_MWPCx2->At(0))->Time();
    tMWPC[3] = ((ERBeamDetMWPCDigi*)v_MWPCy2->At(0))->Time();

    fillMWPC(v_MWPCx1,&wirex1);
    fillMWPC(v_MWPCy1,&wirey1);
    fillMWPC(v_MWPCx2,&wirex2);
    fillMWPC(v_MWPCy2,&wirey2);

    MWPCprojection();

    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

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
    wire1 = ((ERBeamDetMWPCDigi*)data->At(i))->Channel();
    wire2 = ((ERBeamDetMWPCDigi*)data->At(i-1))->Channel();

    //todo number 32 is related to number of wires
    // and should be taken from Parameters
    if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 32) {
      noclusters++;
    }
  }

  return noclusters;
}

void zeroVars() {
  // trigger = -1;

  F5 = 0;
  tF5 = 0;
  F3 = 0;
  tF3 = 0;

  wirex1 = -1;
  wirex2 = -1;
  wirey1 = -1;
  wirey2 = -1;
  
  for(Int_t i = 0;i<4;i++) {
    tMWPC[i] = 0;
  }

  x1c = -50;
  y1c = -50;
  x2c = -50;
  y2c = -50;

  fXt = -100;
  fYt = -100;

  nCsI = -1;
  aCsI = 0;
  tCsI = 0;

  for(Int_t i=0;i<16;i++) {
    arCsI[i] = 0;
    trCsI[i] = 0;

    SQ20_1[i] = 0;
    SSD1[i] = 0;
    SSD_V1[i] = -10;
    tSQ20_1[i] = 0;
    tSSD1[i] = 0;
    tSSD_V1[i] = -10;

    SQ20_2[i] = 0;
    SSD2[i] = 0;
    SSD_V2[i] = 0;
    tSQ20_2[i] = 0;
    tSSD2[i] = -10;
    tSSD_V2[i] = -10;

    SQ20_3[i] = 0;
    SSD3[i] = 0;
    SSD_V3[i] = 0;
    tSQ20_3[i] = 0;
    tSSD3[i] = -10;
    tSSD_V3[i] = -10;

    SQ20_4[i] = 0;
    SSD4[i] = 0;
    SSD_V4[i] = 0;
    tSQ20_4[i] = 0;
    tSSD4[i] = -10;
    tSSD_V4[i] = -10;
  }

  for(Int_t i=0;i<32;i++) {
    DSD_X[i] = 0;
    DSD_Y[i] = 0;
    tDSD_X[i] = 0;
    tDSD_Y[i] = 0;
  }

}

void fillF5(TClonesArray *data){
  if (!data) return;
  ERBeamDetTOFDigi *temp_F5 = ((ERBeamDetTOFDigi*)data->At(0));
  if(!temp_F5) return;

  F5 = temp_F5->Edep();
  tF5 = temp_F5->Time();

  return; 
}

void fillF3(TClonesArray *data){
  if (!data) return;
  ERBeamDetTOFDigi *temp_F3 = ((ERBeamDetTOFDigi*)data->At(0));
  if(!temp_F3) return;

  F3 = temp_F3->Edep();
  tF3 = temp_F3->Time();

  return; 
}

void fillMWPC(TClonesArray *data,Float_t *wire) {
  if (!data) return;

  *(wire) = ((ERBeamDetMWPCDigi*)data->At(0))->Channel() + ((ERBeamDetMWPCDigi*)data->At(data->GetEntriesFast()-1))->Channel();
  *(wire) = *(wire)/2; 

  return;
}

void MWPCprojection() {

  const Float_t fMWPCwireStepX1 = -1.25;
  const Float_t fMWPCwireStepY1 = 1.25;   //step between two wires
  const Float_t fMWPCwireStepX2 = -1.25;    //step between two wires
  const Float_t fMWPCwireStepY2 = 1.25;   //step between two wires

  const Float_t fMWPC1_X_offset = 0;
  const Float_t fMWPC1_Y_offset = 0;

  const Float_t fMWPC2_X_offset = 0;
  const Float_t fMWPC2_Y_offset = 0;

  const Float_t fMWPCz1 = -815.;  //z coordinate of the center of MWPC1
  const Float_t fMWPCz2 = -270.;  //z coordinate of the center of MWPC2

  Float_t xtc, ytc;
  //cluster multiplicity equal to 1
  x1c = GetPosition(wirex1, fMWPCwireStepX1, fMWPC1_X_offset);
  y1c = GetPosition(wirey1, fMWPCwireStepY1, fMWPC1_Y_offset);

  x2c = GetPosition(wirex2, fMWPCwireStepX2, fMWPC2_X_offset);
  y2c = GetPosition(wirey2, fMWPCwireStepY2, fMWPC2_Y_offset);

  xtc = x1c - (x2c -x1c)*fMWPCz1/(fMWPCz2-fMWPCz1);
  ytc = y1c + (xtc - x1c)*(y2c-y1c)/(x2c-x1c);

  fXt = xtc;
  fYt = ytc;
}

Float_t GetPosition(Float_t wire, Float_t wireStep,
    Float_t planeOffset) {
  //TODO: number of wires (16) as parameter
  //TODO: omit gRandom
  return (wire - 16.5)*wireStep + planeOffset;
}

void fillSi(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2,Int_t *multiplicity, Float_t ampThreshold,Float_t timeThreshold=0) {
  if(!data) return;
  if(data->GetEntriesFast()==0) return;
  Bool_t isCal = kTRUE;
  if(par1 == NULL || par2 == NULL) isCal = kFALSE;

  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) { 
    nCh = ((ERQTelescopeSiDigi*)data->At(i))->Channel();
    // cout << 1000*((ERQTelescopeSiDigi*)data->At(i))->Edep()*(*(par2+nCh)) + (*(par1+nCh)) << " " << nCh << " " << *(par2+nCh) << " " << *(par1+nCh) << endl;
    if (isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Edep();
    if (!isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Edep();
    *(time+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Time();
    if ( isCal && ( *(amp+nCh)<=ampThreshold || *(time+nCh)<=timeThreshold ) ) {
      *(amp+nCh) = 0;
      *(time+nCh) = 0;
      *multiplicity = *multiplicity - 1;
    } 
  } 
}

void fillarrayCsI(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2) {
  if(!data) return;
  if(data->GetEntriesFast()==0) return;

  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) {
    nCh = ((ERQTelescopeCsIDigi*)data->At(i))->Channel();
    *(amp+nCh) = ((ERQTelescopeCsIDigi*)data->At(i))->Edep();
    *(time+nCh) = ((ERQTelescopeCsIDigi*)data->At(i))->Time();
  }
  return;
}

void processCsI_cal() {

  for(Int_t i=0;i<16;i++){
    if (arCsI[i]>aCsI) {
      tCsI = trCsI[i];
      nCsI = i;
      aCsI = arCsI[i];
    }
  }

  Int_t nMax = 0;
  for(Int_t i=0;i<16;i++){
    if (arCsI[i]==aCsI) {
      nMax++;
    }
  }


  if (nMax!=1) {
     cout << " ##ENTRY## " << endl;
    for(Int_t i=0;i<16;i++) {
      if (arCsI[i]>0 && trCsI[i]>0) cout << i << " " << arCsI[i] << " " << trCsI[i] << endl;
    }

    cout << " maximum choice " << endl;
    cout << nCsI << " " << aCsI << " " << tCsI << " " << endl;
    cout << " nMAX= " << nMax << endl;

    nCsI = -1;
    tCsI = 0;
    aCsI = 0;
  } 
 
  return;
}


void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=0;
  TString file = "/home/ivan/work/macro/h7_1904/parameters/" + fileName + ".cal";
  myfile.open(file.Data());
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    // if(count < 0){
    //   count++;
    //   continue;
    // }
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g %g", par1+count,par2+count);
    count++;
  }
  cout << endl << fileName.Data() << endl;
  for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

  return;
}

