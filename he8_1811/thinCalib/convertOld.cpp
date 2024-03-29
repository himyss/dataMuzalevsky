void zeroVars();
void fillSi();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);


Int_t threshY_L[16];

UShort_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16],tSSD20_L[16];


Float_t X_L,Y_L,a20_L,a20_L_cal,Y_L_cal;
Float_t sq20_l[16],tsq20_l[16];
// Siparst
Int_t n20_L,nY_L,nX_L;

Float_t pDSDX_L1[16],pDSDY_L1[16];
Float_t pDSDX_L2[16],pDSDY_L2[16];
Float_t pSQ20_L1[16],pSQ20_L2[16];
Float_t rpar1[16],rpar2[16];


Int_t trigger;

void convertOld() {

  threshY_L[0] = 80;
  threshY_L[1] = 103;
  threshY_L[2] = 81;
  threshY_L[3] = 106;
  threshY_L[4] = 105;
  threshY_L[5] = 112;
  threshY_L[6] = 97;
  threshY_L[7] = 108;
  threshY_L[8] = 111;
  threshY_L[9] = 116;
  threshY_L[10] = 116;
  threshY_L[11] = 110;
  threshY_L[12] = 110;
  threshY_L[13] = 113;
  threshY_L[14] = 98;
  threshY_L[15] = 99;


  readPar("DSDY_L_newthin",pDSDY_L1,pDSDY_L2);
  readPar("DSDX_L_newthin",pDSDX_L1,pDSDX_L2);
  readPar("pedestalsLeft",rpar1,rpar2);
  // readPar("ssd20_l_new",pSQ20_L1,pSQ20_L2);
  readPar("SSD20_L",pSQ20_L1,pSQ20_L2);
  // readPar("ssd20_l_ec",pSQ20_L1,pSQ20_L2);

// for(Int_t i=0;i<16;i++) cout << pSQ20_L2[i] << endl;
// return;
  TFile *inF = new TFile("/home/oem/work/data/exp1811/raw/clb/oldLib/dsd_20_l_03_full.root","READ");
  TTree *inTree = (TTree*)inF->Get("AnalysisxTree");
  inTree->SetMakeClass(1);

  inTree->SetBranchAddress("NeEvent.SSD20_L[16]",     SSD20_L);
  inTree->SetBranchAddress("NeEvent.tSSD20_L[16]",     tSSD20_L);  
  inTree->SetBranchAddress("NeEvent.DSDX_L[16]",       DSDX_L);
  inTree->SetBranchAddress("NeEvent.DSDY_L[16]",       DSDY_L);
  inTree->SetBranchAddress("NeEvent.trigger",     &trigger);

  TFile *outF = new TFile("/home/oem/work/data/exp1811/analysed/clb/oldLib/dsd_20_l_03_selected_shifted.root","RECREATE");
  TTree *outTree= new TTree("tree","data");

  outTree->Branch("X_L.",&X_L,"X_L/F");
  outTree->Branch("Y_L.",&Y_L,"Y_L/F");
  outTree->Branch("Y_L_cal.",&Y_L_cal,"Y_L_cal/F");  
  outTree->Branch("a20_L.",&a20_L,"a20_L/F");
  outTree->Branch("a20_L_cal.",&a20_L_cal,"a20_L_cal/F");
  outTree->Branch("nY_L.",&nY_L,"nY_L/I");
  outTree->Branch("nX_L.",&nX_L,"nX_L/I"); 
  outTree->Branch("n20_L.",&n20_L,"n20_L/I"); 

  outTree->Branch("sq20_l.",sq20_l,"sq20_l[16]/F");
  outTree->Branch("tsq20_l.",tsq20_l,"tsq20_l[16]/F");

  cout << inTree->GetEntries() << endl;
  for(Int_t nentry=1;nentry<inTree->GetEntries();nentry++) {
    if(nentry%100000==0) cout << "#Event " << nentry << "#" << endl;
  // for(Int_t nentry=1;nentry<10000;nentry++) {
    inTree->GetEntry(nentry);
    zeroVars();
    fillSi();

    outTree->Fill();
  }
  outF->cd();
  outTree->Write();
  outF->Close();
}

void zeroVars() {
  X_L = 0;
  Y_L = 0;
  a20_L = 0;
  nX_L = -1;
  nY_L = -1;
  n20_L = -1;
  Y_L_cal = 0;
  a20_L_cal = 0;
} 

void fillSi() {
  for(Int_t i=0;i<16;i++) {
    sq20_l[i] = SSD20_L[i]-rpar1[i];
    tsq20_l[i] = tSSD20_L[i];
  }


  Int_t nCh = -1; 
  Int_t count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDX_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1 && nCh>-1) {
    X_L = DSDX_L[nCh]*pDSDX_L2[nCh] + pDSDX_L1[nCh];
    nX_L = nCh;
  }
  nCh = -1;
  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDY_L[i]>threshY_L[i]){
      nCh = i;
      count++;
    } 
  }
  if(count==1 && nCh>-1) {
    Y_L_cal = DSDY_L[nCh]*pDSDY_L2[nCh] + pDSDY_L1[nCh];
    Y_L = DSDY_L[nCh];
    nY_L = nCh;    
  }
  nCh = -1;
  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (SSD20_L[i]>150){
      nCh = i;
      count++;
    } 
  }
  if(count==1 && nCh>-1) {
    a20_L = SSD20_L[nCh];
    // a20_L_cal = SSD20_L[nCh]*pSQ20_L2[nCh] + pSQ20_L1[nCh];
    a20_L_cal = (SSD20_L[nCh]-rpar1[nCh])*pSQ20_L2[nCh] ;    
    n20_L = nCh;
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
