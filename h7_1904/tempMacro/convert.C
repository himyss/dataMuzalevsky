void zeroVars();
void fillSi(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

//outtree vars
Int_t trigger; 

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16];
Float_t tDSDX_L[16],tDSDY_L[16],tSSD20_L[16];

// flags
Float_t *nullPtr = NULL;

// Sipars
Float_t pSQ20_L1[16],pSQ20_L2[16];

Float_t pDSDX_L1[16],pDSDY_L1[16];
Float_t pDSDX_L2[16],pDSDY_L2[16];

//
Int_t multX_L,mult20_L,multY_L;


void convert() {

  TChain *ch = new TChain("er");
  ch->Add("/home/oem/work/data/exp1811/digi/clb/dsd_20_l_03*");
  // ch->Add("/home/oem/work/data/exp1811/raw/clb/dsd_20_l_04_000");
  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  readPar("ssd20_l_new_newthin",pSQ20_L1,pSQ20_L2);
  readPar("DSDY_L_newthin",pDSDY_L1,pDSDY_L2);
  readPar("DSDX_L_newthin",pDSDX_L1,pDSDX_L2);
//--------------------------------------------------------------------------------
  ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();

  TClonesArray *v_DSDX_L = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_DSDY_L = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD20_L = new TClonesArray("ERQTelescopeSiDigi");
  TClonesArray *v_SSD_L = new TClonesArray("ERQTelescopeSiDigi");

  // setbranchAdress
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X",&v_DSDX_L);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_Y",&v_DSDY_L);
  ch->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0",&v_SSD20_L);

  ch->SetBranchAddress("EventHeader.",&header);

  // Creating outfile,outtree
  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("DSDX_L",&DSDX_L,"DSDX_L[16]/F");
  tw->Branch("DSDY_L",&DSDY_L,"DSDY_L[16]/F");
  tw->Branch("SSD20_L",&SSD20_L,"SSD20_L[16]/F");
  tw->Branch("tDSDX_L",&tDSDX_L,"tDSDX_L[16]/F");
  tw->Branch("tDSDY_L",&tDSDY_L,"tDSDY_L[16]/F");
  tw->Branch("tSSD20_L",&tSSD20_L,"tSSD20_L[16]/F");

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry=0;nentry<100000;nentry++) {    
    if(nentry%100000==0) cout << "#Event " << nentry << "#" << endl;
    ch->GetEntry(nentry);

    zeroVars();

    // // // fill the vars
    trigger = header->GetTrigger();

    fillSi(v_DSDX_L,DSDX_L,tDSDX_L,pDSDX_L1,nullPtr);
    fillSi(v_DSDY_L,DSDY_L,tDSDY_L,pDSDY_L1,nullPtr);
    fillSi(v_SSD20_L,SSD20_L,tSSD20_L,pSQ20_L1,nullPtr);

    // fillSi(v_DSDX_L,DSDX_L,tDSDX_L,pDSDX_L1,pDSDX_L2);
    // fillSi(v_DSDY_L,DSDY_L,tDSDY_L,pDSDY_L1,pDSDY_L2);
    // fillSi(v_SSD20_L,SSD20_L,tSSD20_L,pSQ20_L1,pSQ20_L2);
    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  trigger = -1;


  for(Int_t i=0;i<16;i++) {
    DSDX_L[i] = 0;
    DSDY_L[i] = 0;
    SSD20_L[i] = 0;
    tDSDX_L[i] = 0;
    tDSDY_L[i] = 0;
    tSSD20_L[i] = 0;
  }

}

void fillSi(TClonesArray *data,Float_t* amp,Float_t* time,Float_t *par1,Float_t *par2) {
  if(!data) return;
  if(data->GetEntriesFast()==0) return;
  Bool_t isCal = kTRUE;
  if(par1 == NULL || par2 == NULL) isCal = kFALSE;

  Int_t nCh;
  for(Int_t i=0;i<data->GetEntriesFast();i++) {
    nCh = ((ERQTelescopeSiDigi*)data->At(i))->GetStripNb();
    if (isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep()*(*(par2+nCh)) + (*(par1+nCh));
    if (!isCal) *(amp+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetEdep();
    *(time+nCh) = ((ERQTelescopeSiDigi*)data->At(i))->GetTime();
  } 
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/oem/work/software/expertroot/input/parameters/" + fileName + ".cal";
  myfile.open(file.Data());
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    if(count < 0){
      count++;
      continue;
    }
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g %g", par1+count,par2+count);
    count++;
  }
  cout << endl << fileName.Data() << endl;
  for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

  return;
}

