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
void fillND(TClonesArray *data,Float_t* amp,Float_t* time,Float_t* tac,Float_t *par);
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

Float_t ND_time[32],ND_amp[32],ND_tac[32];

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
  
Float_t pND_1[32],pND_2[32];


Float_t *nullPtr = NULL;

//
Int_t mult20_1,mult1_1,multv_1;
Int_t mult20_2,mult1_2,multv_2;
Int_t mult20_3,mult1_3,multv_3;
Int_t mult20_4,mult1_4,multv_4;

Int_t multc_x,multc_y,multCsI;

void convert(Int_t nFile = 0) {

  TChain *ch = new TChain("er");
  TString inPutFileName;
  inPutFileName.Form("/mnt/data/exp1904/digi/h7_veto/h7_ct_%d*.root",nFile);
  // inPutFileName.Form("/mnt/data/exp1904/digi/h7/h7_ct_00*.root",nFile);

  // inPutFileName.Form("/mnt/data/exp1904/digi/h7/h7_ect_%d*.root",nFile);
  // inPutFileName.Form("/mnt/data/exp1904/ERanalysis/cleaned/h7_ct_00_0001.cleaned.root",nFile);
  ch->Add(inPutFileName.Data());
  cout << ch->GetEntries() << endl;


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

  TClonesArray *v_ND = new TClonesArray("ERNDDigi");

  // setbranchAdress
  ch->SetBranchAddress("BeamDetToFDigi2",&v_F5);
  ch->SetBranchAddress("BeamDetToFDigi1",&v_F3);

  ch->SetBranchAddress("BeamDetMWPCDigiX1",&v_MWPCx1);
  ch->SetBranchAddress("BeamDetMWPCDigiX2",&v_MWPCx2);
  ch->SetBranchAddress("BeamDetMWPCDigiY1",&v_MWPCy1);
  ch->SetBranchAddress("BeamDetMWPCDigiY2",&v_MWPCy2);  

  ch->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_XY_0_X",&v_DSDX_C);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_XY_0_Y",&v_DSDY_C);
  ch->SetBranchAddress("ERQTelescopeCsIDigi_Central_telescope_CsI_0",&v_CsI);

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

  ch->SetBranchAddress("NDDigi",&v_ND);

  ch->SetBranchAddress("EventHeader.",&header);

  TFile *f;
  TString cutName;

  // Creating outfile,outtree
  TString outPutFileName;
  outPutFileName.Form("/mnt/data/exp1904/analysed/cal/h7_noThresh/h7_ct_%d_cal.root",nFile);
  // outPutFileName.Form("/mnt/data/exp1904/analysed/cal/emptyTarget/h7_ect_%d_cal.root",nFile);
  // outPutFileName.Form("test_convert.root",nFile);
  TFile *fw = new TFile(outPutFileName.Data(), "RECREATE");
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

  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("arCsI",&arCsI,"arCsI[16]/F");
  tw->Branch("trCsI",&trCsI,"trCsI[16]/F");

  tw->Branch("DSD_X",&DSD_X,"DSD_X[32]/F");
  tw->Branch("DSD_Y",&DSD_Y,"DSD_Y[32]/F");
  tw->Branch("tDSD_X",&tDSD_X,"tDSD_X[32]/F");
  tw->Branch("tDSD_Y",&tDSD_Y,"tDSD_Y[32]/F");

  tw->Branch("ND_amp",&ND_amp,"ND_amp[32]/F");
  tw->Branch("ND_time",&ND_time,"ND_time[32]/F");
  tw->Branch("ND_tac",&ND_tac,"ND_tac[32]/F");

  tw->Branch("SQ20_1",&SQ20_1,"SQ20_1[16]/F");
  tw->Branch("tSQ20_1",&tSQ20_1,"tSQ20_1[16]/F");
  tw->Branch("SSD1",&SSD1,"SSD1[16]/F");
  tw->Branch("tSSD1",&tSSD1,"tSSD1[16]/F");
  tw->Branch("SSD_V1",&SSD_V1,"SSD_V1[16]/F");
  tw->Branch("tSSD_V1",&tSSD_V1,"tSSD_V1[16]/F");

  tw->Branch("SQ20_2",&SQ20_2,"SQ20_2[16]/F");
  tw->Branch("tSQ20_2",&tSQ20_2,"tSQ20_2[16]/F");
  tw->Branch("SSD2",&SSD2,"SSD2[16]/F");
  tw->Branch("tSSD2",&tSSD2,"tSSD2[16]/F");
  tw->Branch("SSD_V2",&SSD_V2,"SSD_V2[16]/F");
  tw->Branch("tSSD_V2",&tSSD_V2,"tSSD_V2[16]/F");

  tw->Branch("SQ20_3",&SQ20_3,"SQ20_3[16]/F");
  tw->Branch("tSQ20_3",&tSQ20_3,"tSQ20_3[16]/F");
  tw->Branch("SSD3",&SSD3,"SSD3[16]/F");
  tw->Branch("tSSD3",&tSSD3,"tSSD3[16]/F");
  tw->Branch("SSD_V3",&SSD_V3,"SSD_V3[16]/F");
  tw->Branch("tSSD_V3",&tSSD_V3,"tSSD_V3[16]/F");

  tw->Branch("SQ20_4",&SQ20_4,"SQ20_4[16]/F");
  tw->Branch("tSQ20_4",&tSQ20_4,"tSQ20_4[16]/F");
  tw->Branch("SSD4",&SSD4,"SSD4[16]/F");
  tw->Branch("tSSD4",&tSSD4,"tSSD4[16]/F");
  tw->Branch("SSD_V4",&SSD_V4,"SSD_V4[16]/F");
  tw->Branch("tSSD_V4",&tSSD_V4,"tSSD_V4[16]/F");

  tw->Branch("mult20_1",&mult20_1,"mult20_1/I");
  tw->Branch("mult1_1",&mult1_1,"mult1_1/I");
  tw->Branch("multv_1",&multv_1,"multv_1/I");

  tw->Branch("mult20_2",&mult20_2,"mult20_2/I");
  tw->Branch("mult1_2",&mult1_2,"mult1_2/I");
  tw->Branch("multv_2",&multv_2,"multv_2/I");

  tw->Branch("mult20_3",&mult20_3,"mult20_3/I");
  tw->Branch("mult1_3",&mult1_3,"mult1_3/I");
  tw->Branch("multv_3",&multv_3,"multv_3/I");

  tw->Branch("mult20_4",&mult20_4,"mult20_4/I");
  tw->Branch("mult1_4",&mult1_4,"mult1_4/I");
  tw->Branch("multv_4",&multv_4,"multv_4/I");

  tw->Branch("multc_x",&multc_x,"multc_x/I");
  tw->Branch("multc_y",&multc_y,"multc_y/I");  
  tw->Branch("multCsI",&multCsI,"multCsI/I");  

  Int_t counter = 0;
  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry=0;nentry<1000;nentry++) {    
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
    // cout << trigger << endl;
    trigger = header->GetTrigger();
    if (trigger==1) continue;
 
    mult20_1 = v_SSD20_1->GetEntries();
    // if (mult20_1>1) continue;
    mult1_1 = v_SSD_1->GetEntries();
    // if (mult1_1>1) continue;    
    multv_1 = v_SSD_V_1->GetEntries();

    mult20_2 = v_SSD20_2->GetEntries();
    // if (mult20_2>1) continue;      
    mult1_2 = v_SSD_2->GetEntries();
    // if (mult1_2>1) continue;    
    multv_2 = v_SSD_V_2->GetEntries();    

    mult20_3 = v_SSD20_3->GetEntries();
    // if (mult20_3>1) continue;    
    mult1_3 = v_SSD_3->GetEntries();
    // if (mult1_3>1) continue;
    multv_3 = v_SSD_V_3->GetEntries();

    mult20_4 = v_SSD20_4->GetEntries();
    // if (mult20_4>1) continue;
    mult1_4 = v_SSD_4->GetEntries();
    // if (mult1_4>1) continue;
    multv_4 = v_SSD_V_4->GetEntries();

    multc_x = v_DSDX_C->GetEntries();
    multc_y = v_DSDY_C->GetEntries();
    // if (multc_x>1 || multc_y>1) continue;
    multCsI = v_CsI->GetEntries();

    zeroVars();

  // beamdet
    fillF5(v_F5);
    fillF3(v_F3);

    tMWPC[0] = ((ERBeamDetMWPCDigi*)v_MWPCx1->At(0))->Time();
    tMWPC[1] = ((ERBeamDetMWPCDigi*)v_MWPCy1->At(0))->Time();
    tMWPC[2] = ((ERBeamDetMWPCDigi*)v_MWPCx2->At(0))->Time();
    tMWPC[3] = ((ERBeamDetMWPCDigi*)v_MWPCy2->At(0))->Time();

    // if (tMWPC[0] - tF5 > 98 || tMWPC[0] - tF5 < 77) continue;
    // if (tMWPC[1] - tF5 > 101 || tMWPC[1] - tF5 < 80) continue;
    // if (tMWPC[2] - tF5 > 95 || tMWPC[2] - tF5 < 78) continue;
    // if (tMWPC[3] - tF5 > 98 || tMWPC[3] - tF5 < 77) continue;

    fillMWPC(v_MWPCx1,&wirex1);
    fillMWPC(v_MWPCy1,&wirey1);
    fillMWPC(v_MWPCx2,&wirex2);
    fillMWPC(v_MWPCy2,&wirey2);

    MWPCprojection();

    // central telescope
    fillarrayCsI(v_CsI,arCsI,trCsI,pCsI_1,pCsI_2);
    fillND(v_ND,ND_amp,ND_time,ND_tac,pND_1);

    fillSi(v_DSDX_C,DSD_X,tDSD_X,pDSD_X1,pDSD_X2,&multc_x,2.5);
    fillSi(v_DSDY_C,DSD_Y,tDSD_Y,pDSD_Y1,pDSD_Y2,&multc_y,2.5);

    // side telescopes
    fillSi(v_SSD20_1,SQ20_1,tSQ20_1,pSQ201_1,pSQ201_2,&mult20_1,0.);
    fillSi(v_SSD_1,SSD1,tSSD1,pSSD1_1,pSSD1_2,&mult1_1,0.);
    fillSi(v_SSD_V_1,SSD_V1,tSSD_V1,pSSD_V1_1,pSSD_V1_2,&multv_1,0);
    multv_1 = v_SSD_V_1->GetEntries();

    fillSi(v_SSD20_2,SQ20_2,tSQ20_2,pSQ202_1,pSQ202_2,&mult20_2,0.);
    fillSi(v_SSD_2,SSD2,tSSD2,pSSD2_1,pSSD2_2,&mult1_2,0.);
    fillSi(v_SSD_V_2,SSD_V2,tSSD_V2,pSSD_V2_1,pSSD_V2_2,&multv_2,0);
    multv_2 = v_SSD_V_2->GetEntries();  

    fillSi(v_SSD20_3,SQ20_3,tSQ20_3,pSQ203_1,pSQ203_2,&mult20_3,0.);
    fillSi(v_SSD_3,SSD3,tSSD3,pSSD3_1,pSSD3_2,&mult1_3,0.);
    fillSi(v_SSD_V_3,SSD_V3,tSSD_V3,pSSD_V3_1,pSSD_V3_2,&multv_3,0);
    multv_3 = v_SSD_V_3->GetEntries();

    fillSi(v_SSD20_4,SQ20_4,tSQ20_4,pSQ204_1,pSQ204_2,&mult20_4,0.);
    fillSi(v_SSD_4,SSD4,tSSD4,pSSD4_1,pSSD4_2,&mult1_4,0.);
    fillSi(v_SSD_V_4,SSD_V4,tSSD_V4,pSSD_V4_1,pSSD_V4_2,&multv_4,0);
    multv_4 = v_SSD_V_4->GetEntries();

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
    tMWPC[i] = -1000;
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

    ND_tac[i] = 0;
    ND_amp[i] = 0;
    ND_time[i] = 0;
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

  const Float_t fMWPC1_X_offset = -0.9;
  const Float_t fMWPC1_Y_offset = -3.;

  const Float_t fMWPC2_X_offset = 0.3;
  const Float_t fMWPC2_Y_offset = -1.55;

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
    // if (isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Edep()*(*(par2+nCh)) + (*(par1+nCh));
    if (isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Edep();
    if (!isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Edep();
    *(time+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->Time();
    if ( isCal && ( *(amp+nCh)<=ampThreshold || *(time+nCh)<=timeThreshold ) ) {
      // *(amp+nCh) = 0;
      // *(time+nCh) = 0;
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
    // *(amp+nCh) = 1000*((ERQTelescopeCsIDigi*)data->At(i))->Edep()*(*(par2+nCh)) + (*(par1+nCh));
    *(amp+nCh) = ((ERQTelescopeCsIDigi*)data->At(i))->Edep();
    *(time+nCh) = ((ERQTelescopeCsIDigi*)data->At(i))->Time();
  }
  return;
}

void fillND(TClonesArray *data,Float_t* amp,Float_t* time,Float_t* tac,Float_t *par) {
  if(!data) return;
  if(data->GetEntriesFast()==0) return;

  // cout << "fillND executed " << endl;

  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) {
    nCh = ((ERNDDigi*)data->At(i))->Channel();
    *(amp+nCh) = ((ERNDDigi*)data->At(i))->Edep();
    *(time+nCh) = ((ERNDDigi*)data->At(i))->Time();
    *(tac+nCh) = ((ERNDDigi*)data->At(i))->TAC();
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
    //  cout << " ##ENTRY## " << endl;
    // for(Int_t i=0;i<16;i++) {
    //   if (arCsI[i]>0 && trCsI[i]>0) cout << i << " " << arCsI[i] << " " << trCsI[i] << endl;
    // }

    // // cout << " maximum choice " << endl;
    // // cout << nCsI << " " << aCsI << " " << tCsI << " " << endl;
    // // cout << " nMAX= " << nMax << endl;

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

