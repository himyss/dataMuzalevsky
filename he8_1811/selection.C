void zeroVars();
void checkToF();
void cutMWPC();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void CsIselect();
void DSD_Cselect();
void SSD20_Lselect();
void SSD20_Rselect();
void X_Lselect();
void Y_Lselect();
void Y_Rselect();

void fillSi();

void readThickness();

void triton();
void checkHe3();
void checkHe3_R();

// reconstruction
void GetXYLeft();
void GetXYCent();
void GetXYRight();

const Double_t angleLeft =  17.;
const Double_t leftDistance = 180.;
const Double_t rightDistance = 180.;

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC,wirex1,wirex2,wirey1,wirey2;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_L_uncorr,Y_R,tY_R,a20_R,t20_R,a20_R_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L,n20_R,nY_R;

//
Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16],tDSDX_L[16],tDSDY_L[16],tSSD20_L[16],tSSD_L[16];

Float_t SSDY_R[16],SSD20_R[16],SSD_R[16],tSSDY_R[16],tSSD20_R[16],tSSD_R[16];
// reconstructed

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xRight,yRight,zRight;
Float_t xCent,yCent,zCent;
// flags
Bool_t timesToF,timesMWPC,vetoFlag;

Double_t fThicknessRight[16][16];
Double_t fThicknessLeft[16][16];

TCutG *cutCsI[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cutSQ20_R[16],*cuthe3[16],*cutY_R[16],*cuthe3_R[16];
Int_t nh3,nTarget,nhe3,nhe3_R;
Int_t flagLeft,flagCent,flagRight;

void selection() {
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all.root");

  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("aCsI.",&aCsI);
  ch->SetBranchAddress("aCsI_cal.",&aCsI_cal);
  ch->SetBranchAddress("tCsI.",&tCsI);
  ch->SetBranchAddress("nCsI.",&nCsI);

  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);

  ch->SetBranchAddress("tMWPC.",&tMWPC);
  ch->SetBranchAddress("wirex1.",&wirex1);
  ch->SetBranchAddress("wirex2.",&wirex2);
  ch->SetBranchAddress("wirey1.",&wirey1);
  ch->SetBranchAddress("wirey2.",&wirey2);

  ch->SetBranchAddress("DSDX_C",&DSDX_C);
  ch->SetBranchAddress("tDSDX_C",&tDSDX_C);
  ch->SetBranchAddress("DSDY_C",&DSDY_C); 
  ch->SetBranchAddress("tDSDY_C",&tDSDY_C);

  ch->SetBranchAddress("DSDX_L",&DSDX_L);
  ch->SetBranchAddress("DSDY_L",&DSDY_L);
  ch->SetBranchAddress("SSD20_L",&SSD20_L);
  ch->SetBranchAddress("SSD_L",&SSD_L);
  ch->SetBranchAddress("tDSDX_L",&tDSDX_L);
  ch->SetBranchAddress("tDSDY_L",&tDSDY_L);
  ch->SetBranchAddress("tSSD20_L",&tSSD20_L);
  ch->SetBranchAddress("tSSD_L",&tSSD_L);

  ch->SetBranchAddress("SSDY_R",&SSDY_R);
  ch->SetBranchAddress("SSD20_R",&SSD20_R);
  ch->SetBranchAddress("SSD_R",&SSD_R);
  ch->SetBranchAddress("tSSDY_R",&tSSDY_R);
  ch->SetBranchAddress("tSSD20_R",&tSSD20_R);
  ch->SetBranchAddress("tSSD_R",&tSSD_R);

  TFile *f,*f1,*f2;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/CsItimeCuts/CsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/tritonCuts/h3_%d.root",i);
    f1 = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/cutX_L/X_L_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutX_L[i] = (TCutG*)f2->Get("CUTG");
    if (!cutX_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/cutY_L/Y_L_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutY_L[i] = (TCutG*)f2->Get("CUTG");
    if (!cutY_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/cutY_R/Y_R_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutY_R[i] = (TCutG*)f2->Get("CUTG");
    if (!cutY_R[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/SQ20_Lcuts/sq20_L_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutSQ20_L[i] = (TCutG*)f2->Get("CUTG");
    if (!cutSQ20_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/SQ20_Rcuts/sq20_R_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutSQ20_R[i] = (TCutG*)f2->Get("CUTG");
    if (!cutSQ20_R[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/helium3/he3_%d.root",i);
    f2 = new TFile(cutName.Data());
    cuthe3[i] = (TCutG*)f2->Get("CUTG");
    if (!cuthe3[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/he3_cut_R/he3_%d.root",i);
    f2 = new TFile(cutName.Data());
    cuthe3_R[i] = (TCutG*)f2->Get("CUTG");
    if (!cuthe3_R[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  readThickness();

  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/h7_all_cut.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger.",&trigger,"trigger/I");

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
  tw->Branch("aCsI_cal.",&aCsI_cal,"aCsI_cal/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("X_C.",&X_C,"X_C/F");
  tw->Branch("nX_C.",&nX_C,"nX_C/I");
  tw->Branch("tX_C.",&tX_C,"tX_C/F");
  tw->Branch("Y_C.",&Y_C,"Y_C/F");
  tw->Branch("tY_C.",&tY_C,"tY_C/F");
  tw->Branch("nY_C.",&nY_C,"nY_C/I");

  tw->Branch("X_L.",&X_L,"X_L/F");
  tw->Branch("Y_L.",&Y_L,"Y_L/F");
  tw->Branch("nY_L.",&nY_L,"nY_L/I");
  tw->Branch("nX_L.",&nX_L,"nX_L/I");
  tw->Branch("a20_L.",&a20_L,"a20_L/F");
  tw->Branch("n20_L.",&n20_L,"n20_L/I");
  tw->Branch("a20_L_uncorr.",&a20_L_uncorr,"a20_L_uncorr/F"); 
  tw->Branch("tX_L.",&tX_L,"tX_L/F");
  tw->Branch("tY_L.",&tY_L,"tY_L/F");
  tw->Branch("t20_L.",&t20_L,"t20_L/F");

  tw->Branch("Y_R.",&Y_R,"Y_R/F");
  tw->Branch("nY_R.",&nY_R,"nY_R/I");
  tw->Branch("a20_R.",&a20_R,"a20_R/F");
  tw->Branch("n20_R.",&n20_R,"n20_R/I");
  tw->Branch("a20_R_uncorr.",&a20_R_uncorr,"a20_R_uncorr/F"); 
  tw->Branch("tY_R.",&tY_R,"tY_R/F");
  tw->Branch("t20_R.",&t20_R,"t20_R/F");

  tw->Branch("x1c.",&x1c,"x1c/F");
  tw->Branch("y1c.",&y1c,"y1c/F");
  tw->Branch("x2c.",&x2c,"x2c/F");
  tw->Branch("y2c.",&y2c,"y2c/F"); 
  tw->Branch("fXt.",&fXt,"fXt/F");
  tw->Branch("fYt.",&fYt,"fYt/F"); 

  tw->Branch("xLeft.",&xLeft,"xLeft/F");
  tw->Branch("yLeft.",&yLeft,"yLeft/F");
  tw->Branch("zLeft.",&zLeft,"zLeft/F");

  tw->Branch("xCent.",&xCent,"xCent/F");
  tw->Branch("yCent.",&yCent,"yCent/F");
  tw->Branch("zCent.",&zCent,"zCent/F");

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nhe3.",&nhe3,"nhe3/I");
  tw->Branch("nhe3_R.",&nhe3_R,"nhe3_R/I");
  
  tw->Branch("flagLeft.",&flagLeft,"flagLeft/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  tw->Branch("flagRight.",&flagRight,"flagRight/I");

  // tw->Branch("nTarget.",&nTarget,"nTarget/I");

  Float_t xTarget,yTarget;
  xTarget = -1.;
  yTarget = 2.2;

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<1000000;nentry++) {     
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;
    ch->GetEntry(nentry);

    nh3 = 0;
    nhe3 = 0;
    nhe3_R = 0;
    timesMWPC = kTRUE;
    timesToF = kTRUE;
    flagLeft = 1;
    flagRight = 1;
    flagCent = 1;

    checkToF();
    if (!timesToF) continue;

    cutMWPC();
    if (!timesMWPC) continue;

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xTarget)*(fXt-xTarget) + (fYt-yTarget)*(fYt-yTarget))>8*8 ) continue;

    fillSi();

    CsIselect();
    DSD_Cselect();

    if (trigger==2 && n20_L>-1 && nY_L>-1 && nX_L>-1) {
      SSD20_Lselect();
      X_Lselect();
      Y_Lselect();
    }

    if (trigger==3 && n20_R>-1 && nY_R>-1) {
      SSD20_Rselect();
      Y_Rselect();
    }

    if(flagCent) {
      triton();
      GetXYCent();
    }

    if (flagLeft) {
      checkHe3();
      GetXYLeft();
    }

    if (flagRight) {
      checkHe3_R();
      GetXYRight();
    }
    

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  X_C = 0;
  tX_C = 0;
  Y_C = 0;
  tY_C = 0;
  X_L = 0;
  Y_L = 0;
  a20_L = 0;
  a20_L_uncorr = 0;
  tX_L = 0;
  tY_L = 0;
  t20_L = 0;

  Y_R = 0;
  a20_R = 0;
  a20_R_uncorr = 0;
  tY_R = 0;
  t20_R = 0;

  nX_C = -1;
  nY_C = -1;
  nX_L = -1;
  nY_L = -1;
  n20_L = -1;
  nY_R = -1;
  n20_R = -1;

  xLeft = -50;
  yLeft = -50;
  zLeft = -50;

  xRight= -50;
  yRight= -50;
  zRight= -50;

  xCent = -50;
  yCent = -50;
  zCent = -50;

  x1c = -50;
  y1c = -50;
  x2c = -50;
  y2c = -50;

  fXt = -100;
  fYt = -100;

} 

void checkToF() {
  if(F5<2600 || F5>4300 || tF5-tF3<103 || tF5-tF3>115 || F3<2000 || F3>4000 ) timesToF = kFALSE;
  return;
}

void cutMWPC() {
  if ( (tMWPC - tF5)<65 || (tMWPC - tF5)>95 ) timesMWPC = kFALSE;
}

void MWPCprojection() {

  const Float_t fMWPCwireStepX1 = -1.25;
  const Float_t fMWPCwireStepY1 = 1.25;   //step between two wires
  const Float_t fMWPCwireStepX2 = -1.25;    //step between two wires
  const Float_t fMWPCwireStepY2 = 1.25;   //step between two wires

  const Float_t fMWPC1_X_offset = 0.;
  const Float_t fMWPC1_Y_offset = 0.;
  // const Float_t fMWPC2_X_offset = 0;
  // const Float_t fMWPC2_Y_offset = 0;

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

void readThickness() {
  cout << "thickness Left detector " << endl;
  TFile *f = new TFile("/home/oem/work/software/expertroot/input/parameters/thicknessLeft_new.root","READ");
  if (f->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThicknessLeft[i][j] = 20.;
        cout << fThicknessLeft[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick = (TH2F*)f->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThicknessLeft[i][j] = hThick->GetBinContent(i+1,j+1);
        if (j==15) fThicknessLeft[i][j] = 100.;
        cout << fThicknessLeft[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f;

cout << "thickness Right detector " << endl;
  TFile *f1 = new TFile("/home/oem/work/software/expertroot/input/parameters/thicknessRight.root","READ");
  if (f1->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThicknessRight[i][j] = 20.;
        cout << fThicknessRight[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick1 = (TH2F*)f1->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThicknessRight[i][j] = hThick1->GetBinContent(i+1,j+1);
        cout << fThicknessRight[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f1;

  return;
}


void CsIselect() {
  if (nCsI==9) {
    flagCent = 0;
    return; 
  }

  // cout << " check " << endl;
  if(nCsI>-1 && nCsI!=9 && cutCsI[nCsI]->IsInside(tCsI-tF5, aCsI)) {\
    flagCent = 1;  
    return;
  }
  else {
    flagCent = 0;  
    return; 
  }
}  

void DSD_Cselect() {

  if ( (tX_C - tF5 < 118) || (tX_C - tF5 > 135)) {
    flagCent = 0;
  }
  if ( (tY_C - tF5 < 123) || (tY_C - tF5 >135)){
    flagCent = 0;   
  }

}

void fillSi() {
 
  Int_t nCh;
  Int_t count = 0;
  for(Int_t i=0;i<32;i++) {
    if (DSDX_C[i]>0 && tDSDX_C[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    X_C = DSDX_C[nCh];
    tX_C = tDSDX_C[nCh];
    nX_C = nCh;
  }

  count = 0;
  for(Int_t i=0;i<32;i++) {
    if (DSDY_C[i]>0 && tDSDY_C[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    Y_C = DSDY_C[nCh];
    tY_C = tDSDY_C[nCh];
    nY_C = nCh;
  }

  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDX_L[i]>0 && tDSDX_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    X_L = DSDX_L[nCh];
    tX_L = tDSDX_L[nCh];
    nX_L = nCh;

  }

  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDY_L[i]>0 && tDSDY_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    Y_L = DSDY_L[nCh];
    tY_L = tDSDY_L[nCh];
    nY_L = nCh;    
  }

  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (SSD20_L[i]>0 && tSSD20_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    a20_L = SSD20_L[nCh];
    t20_L = tSSD20_L[nCh];
    n20_L = nCh;
  }

  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (SSD20_R[i]>0 && tSSD20_R[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    a20_R = SSD20_R[nCh];
    t20_R = tSSD20_R[nCh];
    n20_R = nCh;
  }

  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (SSDY_R[i]>0 && tSSDY_R[i]>0){
      nCh = i;
      count++;
    } 
  }
  if(count==1) {
    Y_R = SSDY_R[nCh];
    tY_R = tSSDY_R[nCh];
    nY_R = nCh;    
  }

}

void SSD20_Lselect() {
  a20_L_uncorr = a20_L;

  a20_L = a20_L*20./fThicknessLeft[n20_L][nY_L];

  if (n20_L>-1 && n20_L<16 && a20_L>0 && cutSQ20_L[n20_L]->IsInside(t20_L-tF5, a20_L)) {
    flagLeft = 1;
  }
  else {
    flagLeft = 0;
  }
    // check if thickness if reasonable
  if (fThicknessLeft[n20_L][nY_L]<10 || fThicknessLeft[n20_L][nY_L] > 30) {
    flagLeft = 0;
  }

  return;
}

void SSD20_Rselect() {
  a20_R_uncorr = a20_R;

  a20_R = a20_R*20./fThicknessRight[n20_R][nY_R];

  if (fThicknessRight[n20_R][nY_R]<10 || fThicknessRight[n20_R][nY_R] > 30) {
    flagRight = 0;
    return;
  }

  if (n20_R>-1 && n20_R<16 && a20_R>0 && cutSQ20_R[n20_R]->IsInside(t20_R-tF5, a20_R_uncorr)) {
    return;
  }
  else {
    flagRight = 0;
    return;
  }
  return;
}

void triton() {

  if(nCsI>-1 && nCsI!=9 && cut3h[nCsI]->IsInside(aCsI, X_C)) {
    nh3 = 1;
    return;
  }
  else {
    nh3 = 0;
    return;
  }
}

void checkHe3() {
  if(nX_L>-1 && n20_L>-1 && cuthe3[n20_L]->IsInside(X_L, a20_L)) {
    nhe3 = 1;
    return;
  }
  else {
    nhe3 = 0;
    return;
  }
}

void checkHe3_R() {
  if(nY_R>-1 && n20_R>-1 && cuthe3_R[n20_R]->IsInside(Y_R, a20_R)) {
    nhe3_R = 1;
    return;
  }
  else {
    nhe3_R = 0;
    return;
  }
}


void X_Lselect() {
  // cout << " check " << endl;
  if(nX_L>-1 && nX_L<16 && X_L>0 && cutX_L[nX_L]->IsInside(tX_L-tF5, X_L)) {
    
    return;
  }
  else {
    flagLeft = 0;
    // X_L = 0;
    // tX_L = 0;
    // nX_L = -1;  
  }

}

void Y_Lselect() {
  // cout << " check " << endl;
  if(nY_L>-1 && nY_L<16 && Y_L>0 && cutY_L[nY_L]->IsInside(tY_L-tF5, Y_L)) {
    // cout << "fine!" << endl;
    return;
  }
  else {
    flagLeft = 0;
    // Y_L = 0;
    // tY_L = 0;
    // nY_L = -1;    
  }

}

void Y_Rselect() {

  if(nY_R>-1 && nY_R<16 && Y_R>0 && cutY_R[nY_R]->IsInside(tY_R-tF5, Y_R)) {
    return;
  }
  else {
    flagRight = 0;
    return;
  }

}

void GetXYLeft() {
  // coordinates in the system of detector
  xLeft = 30. - nX_L*60./16;
  yLeft = - 30. + nY_L*60./16;
  zLeft = 0;

  // rotate the detector
  xLeft = xLeft*cos(angleLeft*TMath::DegToRad());
  zLeft = xLeft*sin(angleLeft*TMath::DegToRad());

  // transfer the detector
  xLeft = xLeft + leftDistance*sin(angleLeft*TMath::DegToRad());
  zLeft = zLeft + leftDistance*cos(angleLeft*TMath::DegToRad());

  return;
}

void GetXYRight() {
  // coordinates in the system of detector
  xRight = 30. + n20_R*60./16;
  yRight = - 30. + nY_R*60./16;
  zRight = 0;

  // rotate the detector
  xRight = yRight*cos(-angleLeft*TMath::DegToRad());
  yRight = xRight*sin(-angleLeft*TMath::DegToRad());

  // transfer the detector
  xRight = xRight + leftDistance*sin(-angleLeft*TMath::DegToRad());
  zRight = zRight + leftDistance*cos(-angleLeft*TMath::DegToRad());

  return;
}

void GetXYCent() {
  // coordinates in the system of detector
  xCent = 32. - nX_C*64./32;
  yCent = 32. - nY_C*64./32;
  zCent = 280.;

  return;
}
