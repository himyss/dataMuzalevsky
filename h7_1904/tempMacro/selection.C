void zeroVars();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

void fillSi();
//outtree vars
Int_t trigger; 


Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_L_uncorr,a20_L_cal,Y_L_cal;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L;

Int_t mult20,multx,multY;

Float_t sq20_l[16],tsq20_l[16],sq20_l_cal[16];
//

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16],tDSDX_L[16],tDSDY_L[16],tSSD20_L[16],tSSD_L[16];


Float_t threshY_L[16];

Float_t pDSDX_L1[16],pDSDY_L1[16];
Float_t pDSDX_L2[16],pDSDY_L2[16];
Float_t pSQ20_L1[16],pSQ20_L2[16];

Float_t rpar1[16],rpar2[16];



void selection() {


  readPar("ssd20_l_new_newthin",pSQ20_L1,pSQ20_L2);
  readPar("DSDY_L_newthin",pDSDY_L1,pDSDY_L2);
  readPar("DSDX_L_newthin",pDSDX_L1,pDSDX_L2);
  // // readPar("SSD20_L",pSQ20_L1,pSQ20_L2);
  // readPar("ssd20_l_new_newthin",pSQ20_L1,pSQ20_L2);  
  // readPar("pedestalsLeft",rpar1,rpar2);


  // readPar("empty16",pDSDY_L1,pDSDY_L2);
  // readPar("empty16",pDSDX_L1,pDSDX_L2);
  // readPar("SSD20_L",pSQ20_L1,pSQ20_L2);
  readPar("empty16",pSQ20_L1,pSQ20_L2);  
  readPar("pedestalsLeft",rpar1,rpar2);


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

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03.root");
  
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("DSDX_L",&DSDX_L);
  ch->SetBranchAddress("DSDY_L",&DSDY_L);
  ch->SetBranchAddress("SSD20_L",&SSD20_L);
  ch->SetBranchAddress("tDSDX_L",&tDSDX_L);
  ch->SetBranchAddress("tDSDY_L",&tDSDY_L);
  ch->SetBranchAddress("tSSD20_L",&tSSD20_L);
  TFile *f,*f1,*f2;
  TString cutName;


  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_trigger2_cut.root", "RECREATE");
  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_cut.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_shifted.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_selected_newpar.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("X_L.",&X_L,"X_L/F");
  tw->Branch("Y_L.",&Y_L,"Y_L/F");
  tw->Branch("Y_L_cal.",&Y_L_cal,"Y_L_cal/F");
  tw->Branch("a20_L.",&a20_L,"a20_L/F");
  tw->Branch("a20_L_cal.",&a20_L_cal,"a20_L_cal/F");
  tw->Branch("nY_L.",&nY_L,"nY_L/I");
  tw->Branch("nX_L.",&nX_L,"nX_L/I"); 
  tw->Branch("n20_L.",&n20_L,"n20_L/I"); 

  tw->Branch("mult20.",&mult20,"mult20/I");
  tw->Branch("multx.",&multx,"multx/I");
  tw->Branch("multY.",&multY,"multY/I");

  tw->Branch("sq20_l_cal.",sq20_l_cal,"sq20_l_cal[16]/F");
  tw->Branch("sq20_l.",sq20_l,"sq20_l[16]/F");
  tw->Branch("tsq20_l.",tsq20_l,"tsq20_l[16]/F");

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<100;nentry++) {     
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << "###ENTRY " << nentry << "###" << endl;
    ch->GetEntry(nentry);

    zeroVars();

    fillSi();

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  mult20 = 0;
  multx = 0;
  multY = 0;
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
    sq20_l_cal[i] = SSD20_L[i]*pSQ20_L2[i] + pSQ20_L1[i];
  }

  Int_t nCh = -1; 
  Int_t count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDX_L[i]>0 && tDSDX_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  multx = count;
  if(count==1 && nCh>-1) {
    X_L = DSDX_L[nCh]*pDSDX_L2[nCh] + pDSDX_L1[nCh];
    nX_L = nCh;
  }
  nCh = -1;
  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDY_L[i]>0 && tDSDY_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  multY = count;
  if(count==1 && nCh>-1) {
    Y_L_cal = DSDY_L[nCh]*pDSDY_L2[nCh] + pDSDY_L1[nCh];
    Y_L = DSDY_L[nCh];
    nY_L = nCh;    
  }
  nCh = -1;
  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (SSD20_L[i]>0 && tSSD20_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  mult20 = count;
  if(count==1 && nCh>-1) {
    a20_L = SSD20_L[nCh] - rpar1[nCh];
    a20_L_cal = (SSD20_L[nCh] - rpar1[nCh])*pSQ20_L2[nCh];
    // a20_L_cal = SSD20_L[nCh]*pSQ20_L2[nCh] + pSQ20_L1[nCh];
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

