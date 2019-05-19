
Int_t GetClusterMult(TClonesArray *data);
void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);


ERQTelescopeCsIDigi* processCsI(TClonesArray *data);
Int_t GetClusterMWPC(TClonesArray *data);
Int_t GetClusterSi(TClonesArray *data);

void zeroVars();
void tempfunc(TClonesArray *data);

void fillCsI(ERQTelescopeCsIDigi *data);
void fillSi(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2);
void fillarrayCsI(TClonesArray *data,Float_t* amp,Float_t* time);

void fillF5(TClonesArray *data);
void fillF3(TClonesArray *data);
void fillMWPC(TClonesArray *data,Float_t *wire);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

//outtree vars
Int_t trigger; 

Float_t F5,tF5,F3,tF3;

Int_t wirex1,wirex2,wirey1,wirey2;
Float_t tMWPC;

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;

//

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Float_t arCsI[16],trCsI[16];

Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16];
Float_t DSDX_L_ch[16],DSDY_L_ch[16],SSD20_L_ch[16];
Float_t tDSDX_L[16],tDSDY_L[16],tSSD20_L[16],tSSD_L[16];

Float_t SSD20_R[16],SSDY_R[16],SSD_R[16];
Float_t tSSD20_R[16],tSSDY_R[16],tSSD_R[16];

// flags
Bool_t flagCsI;


// Sipars
Float_t pSQ20_L1[16],pSQ20_L2[16];
Float_t pSQ20_R1[16],pSQ20_R2[16];

Float_t pDSDX_L1[16],pDSDY_L1[16],pSSDY_R1[16];
Float_t pDSDX_L2[16],pDSDY_L2[16],pSSDY_R2[16];

Float_t pDSDX_C1[32],pDSDX_C2[32];
Float_t pDSDY_C1[32],pDSDY_C2[32];

Float_t pSSD_R1[16],pSSD_R2[16];
Float_t pSSD_L1[16],pSSD_L2[16];

Float_t pCsI_1[16],pCsI_2[16];

Float_t *nullPtr = NULL;

//
Int_t multX_L,mult20_L,multY_L;


void convert() {

  TChain *ch = new TChain("er");
  ch->Add("/home/oem/work/data/exp1904/digi/h7/h7_*");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  // // readPar("ssd20_l_ec",pSQ20_L1,pSQ20_L2);
  // readPar("ssd20_l_new_newthin",pSQ20_L1,pSQ20_L2);
  // // readPar("empty16",pSQ20_L1,pSQ20_L2);

  // readPar("SSD20_R",pSQ20_R1,pSQ20_R2);
  // readPar("SSDY_R",pSSDY_R1,pSSDY_R2);
  
  // // readPar("empty16",pDSDY_L1,pDSDY_L2);
  // readPar("DSDY_L_newthin",pDSDY_L1,pDSDY_L2);
  // readPar("DSDX_L_newthin",pDSDX_L1,pDSDX_L2);

  // readPar("SSD_R",pSSD_R1,pSSD_R2);
  // readPar("SSD_L",pSSD_L1,pSSD_L2);

  // readPar("DSDX_C",pDSDX_C1,pDSDX_C2,32);
  // readPar("DSDY_C",pDSDY_C1,pDSDY_C2,32);
  // readPar("CsI",pCsI_1,pCsI_2);
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

  // ch->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X",&v_DSDX_C);
  // ch->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_Y",&v_DSDY_C);
  // ch->SetBranchAddress("ERQTelescopeCsIDigi_Central_telescope_CsI_0",&v_CsI);

  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_1_SingleSi_SSD20_1_X_0",&v_SSD20_1);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_1_SingleSi_SSD_1_Y_1",&v_SSD_1);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_1_SingleSi_SSD_V_1_Y_2",&v_SSD_V_1);  

  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_2_SingleSi_SSD20_2_Y_3",&v_SSD20_2);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_2_SingleSi_SSD_2_X_4",&v_SSD_2);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_2_SingleSi_SSD_V_2_X_5",&v_SSD_V_2);  

  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_3_SingleSi_SSD20_3_X_6",&v_SSD20_3);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_3_SingleSi_SSD_3_Y_7",&v_SSD_3);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_3_SingleSi_SSD_V_3_Y_8",&v_SSD_V_3);  

  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_4_SingleSi_SSD20_4_Y_9",&v_SSD20_4);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_4_SingleSi_SSD_4_X_10",&v_SSD_4);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Telescope_4_SingleSi_SSD_V_4_X_11",&v_SSD_V_4);  

  ch->SetBranchAddress("EventHeader.",&header);

  TFile *f;
  TString cutName;

  // Creating outfile,outtree

  TFile *fw = new TFile("/home/oem/work/data/exp1904/analysed/h7_test.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");

  tw->Branch("tMWPC.",&tMWPC,"tMWPC/F");
  tw->Branch("wirex1.",&wirex1,"wirex1/I");
  tw->Branch("wirex2.",&wirex2,"wirex2/I");
  tw->Branch("wirey1.",&wirey1,"wirey1/I");
  tw->Branch("wirey2.",&wirey2,"wirey2/I");

  tw->Branch("x1c.",&x1c,"x1c/F"); // position in MWPC in mm
  tw->Branch("y1c.",&y1c,"y1c/F");
  tw->Branch("x2c.",&x2c,"x2c/F");
  tw->Branch("y2c.",&y2c,"y2c/F"); 
  tw->Branch("fXt.",&fXt,"fXt/F"); // beam profile at the target plane
  tw->Branch("fYt.",&fYt,"fYt/F"); 


  // for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) {
  for(Int_t nentry=0;nentry<1000000;nentry++) {    
    if(nentry%100000==0) cout << "#Event " << nentry << "#" << endl;
    ch->GetEntry(nentry);
    
    if(v_MWPCx1->GetEntriesFast()==0) continue;
    if(v_MWPCx2->GetEntriesFast()==0) continue;
    if(v_MWPCy1->GetEntriesFast()==0) continue;
    if(v_MWPCy2->GetEntriesFast()==0) continue;
    if(v_F3->GetEntriesFast()==0) continue;
    if(v_F5->GetEntriesFast()==0) continue;

    if (GetClusterMWPC(v_MWPCx1)!=1) continue;
    if (GetClusterMWPC(v_MWPCx2)!=1) continue;
    if (GetClusterMWPC(v_MWPCy1)!=1) continue;
    if (GetClusterMWPC(v_MWPCy2)!=1) continue;

    zeroVars();

    trigger = header->GetTrigger();

    fillF5(v_F5);
    fillF3(v_F3);

    tMWPC = ((ERBeamDetMWPCDigi*)v_MWPCx1->At(0))->GetTime();

    if (tMWPC - tF5 > 195 || tMWPC - tF5 <150) continue;

    // cout << "first plane" << endl;
    fillMWPC(v_MWPCx1,&wirex1);
    // cout << "second plane" << endl;
    fillMWPC(v_MWPCy1,&wirey1);
    // cout << "third plane" << endl;
    fillMWPC(v_MWPCx2,&wirex2);
    // cout << "fourth plane" << endl;
    fillMWPC(v_MWPCy2,&wirey2);

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
    wire1 = ((ERBeamDetMWPCDigi*)data->At(i))->GetWireNb();
    wire2 = ((ERBeamDetMWPCDigi*)data->At(i-1))->GetWireNb();

    //todo number 32 is related to number of wires
    // and should be taken from Parameters
    if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 32) {
      noclusters++;
    }
  }

  return noclusters;
}

void zeroVars() {
  trigger = -1;

  F5 = 0;
  tF5 = 0;
  F3 = 0;
  tF3 = 0;

  wirex1 = -1;
  wirex2 = -1;
  wirey1 = -1;
  wirey2 = -1;
  tMWPC = 0;

  x1c = -50;
  y1c = -50;
  x2c = -50;
  y2c = -50;

  fXt = -100;
  fYt = -100;

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

void fillMWPC(TClonesArray *data,Float_t *wire) {
  if (!data) return;

  *(wire) = ((ERBeamDetMWPCDigi*)data->At(0))->GetWireNb() + ((ERBeamDetMWPCDigi*)data->At(data->GetEntriesFast()-1))->GetWireNb();
  *(wire) = *(wire)/2; 

  return;
}

void MWPCprojection() {

  const Float_t fMWPCwireStepX1 = -1.25;
  const Float_t fMWPCwireStepY1 = 1.25;   //step between two wires
  const Float_t fMWPCwireStepX2 = -1.25;    //step between two wires
  const Float_t fMWPCwireStepY2 = 1.25;   //step between two wires

  const Float_t fMWPC1_X_offset = 0.;
  const Float_t fMWPC1_Y_offset = 0.;

  const Float_t fMWPC2_X_offset = 0.112500;
  const Float_t fMWPC2_Y_offset = 0.537500;

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

// Int_t GetClusterMult(TClonesArray *data) {

//   if (!data) return 0;

//   Int_t entries = data->GetEntriesFast();

//   if (entries<2) return entries;

//   Int_t strip1, strip2;
//   Int_t noclusters = 1;

//   for (Int_t i = 1; i < entries; i++) {
//     //check if entries are in specific order
//     strip1 = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
//     strip2 = ((ERQTelescopeSiDigi*)data->At(i-1))->GetStripNb();

//     if ( abs(strip1 - strip2) > 1 && abs(strip1 - strip2) < 16) noclusters++;
//   }

//   return noclusters;
// }

// ERQTelescopeCsIDigi* processCsI(TClonesArray *data) {

//   // cout << "processCsI was called " << endl;
//   if (!data) return NULL;
//   if(data->GetEntriesFast()==0) return NULL;

//   Double_t maxAmp = 0;
//   ERQTelescopeCsIDigi *temp_CsI;
//   ERQTelescopeCsIDigi *temp_CsImax;
//   // find maximum 
//   for(Int_t i = 0; i < data->GetEntriesFast(); i++) {
//     temp_CsI = ((ERQTelescopeCsIDigi*)data->At(i));
//     if(temp_CsI->GetEdep() > maxAmp) {
//       maxAmp = temp_CsI->GetEdep();
//       temp_CsImax = temp_CsI; 
//     } 
//   }
//   // check if there is only 1 maximum
//   Int_t nMax = 0;
//   for(Int_t i=0; i<data->GetEntriesFast(); i++) {
//     if (((ERQTelescopeCsIDigi*)data->At(i))->GetEdep() == maxAmp) nMax++;
//   }
//   if (nMax!=1) {
//     cout << nMax << endl; 
//     flagCsI=kFALSE;
//     return NULL;
//   }

//   return temp_CsImax;
// }



// Int_t GetClusterSi(TClonesArray *data) {
//   if (!data) return 0;

//   Int_t entries = data->GetEntriesFast();

//   if (entries<2) return entries;

//   Int_t wire1, wire2;
//   Int_t noclusters = 1;

//   for (Int_t i = 1; i < entries; i++) {
//     //check if entries are in specific order
//     wire1 = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
//     wire2 = ((ERQTelescopeSiDigi*)data->At(i-1))->GetStripNb();

//     //todo number 32 is related to number of wires
//     // and should be taken from Parameters
//     if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 16) noclusters++;
//   }

//   return noclusters;
// }

// void fillCsI(ERQTelescopeCsIDigi *data) {
//   if (!data) return;
//   nCsI = data->GetBlockNb();
//   tCsI = data->GetTime();
//   aCsI = data->GetEdep();
//   aCsI_cal = data->GetEdep()*pCsI_2[nCsI] + pCsI_1[nCsI];
//   return;  
// }

// void fillSi(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2) {
//   if(!data) return;
//   if(data->GetEntriesFast()==0) return;
//   Bool_t isCal = kTRUE;
//   if(par1 == NULL || par2 == NULL) isCal = kFALSE;

//   Int_t nCh;
//   for(Int_t i=0;i<data->GetEntriesFast();i++) {
//     nCh = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
//     if (isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep()*(*(par2+nCh)) + (*(par1+nCh));
//     if (!isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep();
//     *(time+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetTime();
//   } 
// }

// void fillarrayCsI(TClonesArray *data,Float_t* amp,Float_t* time) {
//   if(!data) return;
//   if(data->GetEntriesFast()==0) return;

//   Int_t nCh;
//   for(Int_t i=0;i<data->GetEntriesFast();i++) {
//     nCh = ((ERQTelescopeCsIDigi*)data->At(i))->GetBlockNb();
//     *(amp+nCh) = ((ERQTelescopeCsIDigi*)data->At(i))->GetEdep();
//     *(time+nCh) = ((ERQTelescopeCsIDigi*)data->At(i))->GetTime();
//     // cout << nCh << " " << *(amp+nCh) << " " << *(time+nCh) << endl;
//   }
//   return;
// }



// void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

//   TString line;
//   ifstream myfile;
//   Int_t count=-2;
//   TString file = "/home/oem/work/software/expertroot/input/parameters/" + fileName + ".cal";
//   myfile.open(file.Data());
//   while (! myfile.eof() ){
//     line.ReadLine(myfile);
//     if(count < 0){
//       count++;
//       continue;
//     }
//     if(line.IsNull()) break;
//     sscanf(line.Data(),"%g %g", par1+count,par2+count);
//     count++;
//   }
//   cout << endl << fileName.Data() << endl;
//   for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

//   return;
// }

