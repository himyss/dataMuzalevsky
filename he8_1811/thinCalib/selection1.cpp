void zeroVars();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

void fillSi();
//outtree vars
Int_t trigger; 


Float_t X_C,tX_C,Y_C,tY_C,X_R,Y_R,a20_R,tY_R,t20_R,a20_R_uncorr,a20_R_cal,Y_R_cal;
Int_t nY_R,n20_R;

Float_t sq20_r[16],tsq20_r[16],sq20_r_cal[16];
//

Float_t DSDY_R[16],SSD20_R[16],tDSDY_R[16],tSSD20_R[16];

Int_t mult20,multx,multY;

Float_t threshY_R[16];

Float_t pDSDY_R1[16];
Float_t pDSDY_R2[16];
Float_t pSQ20_R1[16],pSQ20_R2[16];

Float_t rpar1[16],rpar2[16];

void selection1() {

  // readPar("ssd20_l_new_newthin",pSQ20_L1,pSQ20_L2);
  readPar("DSDY_R_newthin",pDSDY_R1,pDSDY_R2);
  // readPar("SSD20_R",pSQ20_R1,pSQ20_R2);
  readPar("ssd20_R_new_newthin",pSQ20_R1,pSQ20_R2);  
  readPar("pedestals_right",rpar1,rpar2);


  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/clb/dsd_20_r_02.root");
  
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("DSDY_R",&DSDY_R);
  ch->SetBranchAddress("SSD20_R",&SSD20_R);
  ch->SetBranchAddress("tDSDY_R",&tDSDY_R);
  ch->SetBranchAddress("tSSD20_R",&tSSD20_R);
  TFile *f,*f1,*f2;
  TString cutName;


  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_trigger2_cut.root", "RECREATE");
  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clbdsd_20_r_02_selected.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_selected_newpar.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("Y_R.",&Y_R,"Y_R/F");
  tw->Branch("Y_R_cal.",&Y_R_cal,"Y_R_cal/F");
  tw->Branch("a20_R.",&a20_R,"a20_R/F");
  tw->Branch("a20_R_cal.",&a20_R_cal,"a20_R_cal/F");
  tw->Branch("nY_R.",&nY_R,"nY_R/I"); 
  tw->Branch("n20_R.",&n20_R,"n20_R/I"); 

  tw->Branch("mult20.",&mult20,"mult20/I");
  tw->Branch("multY.",&multY,"multY/I");

  tw->Branch("sq20_r_cal.",sq20_r_cal,"sq20_r_cal[16]/F");
  tw->Branch("sq20_r.",sq20_r,"sq20_r[16]/F");
  tw->Branch("tsq20_r.",tsq20_r,"tsq20_r[16]/F");

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
  multY = 0;

  Y_R = 0;
  a20_R = 0;
  nY_R = -1;
  n20_R = -1;
  Y_R_cal = 0;
  a20_R_cal = 0;
} 


void fillSi() {

  for(Int_t i=0;i<16;i++) {
    sq20_r[i] = SSD20_R[i]+rpar1[i];
    tsq20_r[i] = tSSD20_R[i];
    sq20_r_cal[i] = SSD20_R[i]*pSQ20_R2[i] + pSQ20_R1[i];
  }

  Int_t nCh = -1; 
  Int_t count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDY_R[i]>0 && tDSDY_R[i]>0){
      nCh = i;
      count++;
    } 
  }
   multY = count;
  if(count==1 && nCh>-1) {
    Y_R_cal = DSDY_R[nCh]*pDSDY_R2[nCh] + pDSDY_R1[nCh];
    Y_R = DSDY_R[nCh];
    nY_R = nCh;    
  }
  nCh = -1;
  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (SSD20_R[i]>150 && tSSD20_R[i]>0){
      nCh = i;
      count++;
    } 
  }
  mult20 = count;
  if(count==1 && nCh>-1) {
    a20_R = SSD20_R[nCh];
    // a20_R_cal = (SSD20_R[nCh] + rpar1[nCh])*pSQ20_R2[nCh];
    a20_R_cal = SSD20_R[nCh]*pSQ20_R2[nCh] + pSQ20_R1[nCh];
    n20_R = nCh;
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

