void zeroVars();
void checkToF();
void cutMWPC();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void CsIselect();
void DSD_Cselect();
void SSD20_Lselect();
void X_Lselect();
void Y_Lselect();

void fillSi();

void readThickness();

void coincidense();
//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC,wirex1,wirex2,wirey1,wirey2;

Int_t nCsI;
Float_t aCsI,tCsI;


Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_R,Y_R,t20_R,tY_R;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L,n20_R,nY_R;
//
Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16],tDSDX_L[16],tDSDY_L[16],tSSD20_L[16],tSSD_L[16];

Float_t SSD20_R[16],SSDY_R[16],SSD_R[16],tSSD20_R[16],tSSDY_R[16],tSSD_R[16];

// reconstructed


Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
// flagsё
Bool_t timesDSDX_C,timesDSDY_C,timesToF,timesCsI,timesMWPC,vetoFlag;
Double_t fThicknessRight[16][16];
Double_t fThicknessLeft[16][16];

TCutG *cutCsI[16],*cut3h[16],*cutX_L[16],*cutY_L[16];
  Int_t nh3,nTarget,nHe8,nMWPC;

void selection() {
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_10_newnew_20Cal.root");
  // ch->Add("/media/user/work/data/Analysed1811/selected/profile.root");
  
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("aCsI.",&aCsI);
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
  ch->SetBranchAddress("SSD20_R",&SSD20_R);
  ch->SetBranchAddress("SSDY_R",&SSDY_R);
  ch->SetBranchAddress("SSD_R",&SSD_R);
  ch->SetBranchAddress("tSSD20_R",&tSSD20_R);
  ch->SetBranchAddress("tSSDY_R",&tSSDY_R);
  ch->SetBranchAddress("tSSD_R",&tSSD_R);

  TFile *f,*f1,*f2;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/exp201810/centralTelescope/cuts/CsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/macro/exp201810/draw/cuts/CsI_%d.root",i);
    f1 = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f1->Get("CUTG");
    delete f1;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/data/Analysed1811/siParTests/analysed/cutX_L/X_L_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutX_L[i] = (TCutG*)f2->Get("CUTG");
    if (!cutX_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/media/user/work/data/Analysed1811/siParTests/analysed/cutY_L/Y_L_%d.root",i);
    f2 = new TFile(cutName.Data());
    cutY_L[i] = (TCutG*)f2->Get("CUTG");
    if (!cutY_L[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }


  readThickness();
  TFile *fw = new TFile("/media/user/work/data/Analysed1811/siParTests/analysed/he8_10_new_selected_20Cal.root", "RECREATE");
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

  tw->Branch("fXt.",&fXt,"fXt/F");
  tw->Branch("fYt.",&fYt,"fYt/F");  

  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("X_C",&X_C,"X_C/F");
  tw->Branch("nX_C",&nX_C,"nX_C/I");
  tw->Branch("tX_C",&tX_C,"tX_C/F");
  tw->Branch("Y_C",&Y_C,"Y_C/F");
  tw->Branch("tY_C",&tY_C,"tY_C/F");
  tw->Branch("nY_C",&nY_C,"nY_C/I");

  tw->Branch("X_L",&X_L,"X_L/F");
  tw->Branch("Y_L",&Y_L,"Y_L/F");
  tw->Branch("nY_L",&nY_L,"nY_L/I");
  tw->Branch("nX_L",&nX_L,"nX_L/I");
  tw->Branch("a20_L",&a20_L,"a20_L/F");
  tw->Branch("n20_L",&n20_L,"n20_L/I");
  tw->Branch("tX_L",&tX_L,"tX_L/F");
  tw->Branch("tY_L",&tY_L,"tY_L/F");
  tw->Branch("t20_L",&t20_L,"t20_L/F");

  tw->Branch("a20_R",&a20_R,"a20_R/F");
  tw->Branch("n20_R",&n20_R,"n20_R/I");
  tw->Branch("Y_R",&Y_R,"Y_R/F");
  tw->Branch("nY_R",&nY_R,"nY_R/I");
  tw->Branch("t20_R",&t20_R,"t20_R/F");
  tw->Branch("tY_R",&tY_R,"tY_R/F");

  tw->Branch("x1c",&x1c,"x1c/F");
  tw->Branch("y1c",&y1c,"y1c/F");
  tw->Branch("x2c",&x2c,"x2c/F");
  tw->Branch("y2c",&y2c,"y2c/F"); 

  tw->Branch("nh3",&nh3,"nh3/I");
  tw->Branch("nHe8",&nHe8,"nHe8/I");  
  tw->Branch("nMWPC",&nMWPC,"nMWPC/I");  
  tw->Branch("nTarget",&nTarget,"nTarget/I");
  tw->Branch("vetoFlag",&vetoFlag,"vetoFlag/I");

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<1000;nentry++) {     
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;

    vetoFlag = 0;
    nh3 = 0;
    nMWPC = 0;
    nHe8 = 0;
    nTarget = 0;
    ch->GetEntry(nentry);

    timesMWPC = kTRUE;
    timesDSDX_C = kTRUE;
    timesDSDY_C = kTRUE;
    timesToF = kTRUE;
    timesCsI = kTRUE;

    checkToF();
    if (timesToF) nHe8 = 1;

    cutMWPC();
    if (timesMWPC) nMWPC = 1;

    MWPCprojection();
    if ( ((fXt+0.6)*(fXt+0.6) + (fYt+2.5)*(fYt+2.5))>8.5*8.5 ) nTarget = 1;

    zeroVars();
    fillSi();

    for(Int_t i=0;i<16;i++) {
      if(SSD_L[i]>0 && tSSD_L[i]>0) vetoFlag = 1;
    }

    // if (aCsI>0) CsIselect();

    DSD_Cselect();
    SSD20_Lselect();
    X_Lselect();
    Y_Lselect();
    // coincidense();

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
  tX_L = 0;
  tY_L = 0;
  t20_L = 0;
  a20_R = 0;
  Y_R = 0;
  t20_R = 0;
  tY_R = 0;

  nX_C = -1;
  nY_C = -1;
  nX_L = -1;
  nY_L = -1;
  n20_L = -1;
  n20_R = -1;
  nY_R = -1;
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
  const Float_t fMWPC2_X_offset = 1.1375;
  const Float_t fMWPC2_Y_offset = 0.7125;

  const Float_t fMWPCz1 = -815.;  //z coordinate of the center of MWPC1
  const Float_t fMWPCz2 = -270.;  //z coordinate of the center of MWPC2

  Float_t xtc, ytc;
  //cluster multiplicity equal to 1
  x1c = GetPosition(wirex1, fMWPCwireStepX1, fMWPC1_X_offset);
  y1c = GetPosition(wirey1, fMWPCwireStepY1, fMWPC1_Y_offset);

  x2c = GetPosition(wirex2, fMWPCwireStepX2, fMWPC2_X_offset);
  y2c = GetPosition(wirey1, fMWPCwireStepY2, fMWPC2_Y_offset);

  xtc = x1c - (x2c -x1c)*fMWPCz1/(fMWPCz2-fMWPCz1);
  ytc = y1c - (y2c -y1c)*fMWPCz1/(fMWPCz2-fMWPCz1);

  fXt = xtc;
  fYt = ytc;

}

Float_t GetPosition(Float_t wire, Float_t wireStep,
    Float_t planeOffset) {
  //TODO: number of wires (16) as parameter
  //TODO: omit gRandom
  return (wire + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16.)*wireStep + planeOffset;
}


void readThickness() {
  cout << "thickness Left detector " << endl;
  TFile *f = new TFile("/media/user/work/software/fork/useranalysis/calibration/parameters/thicknessLeft.root","READ");
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
        cout << fThicknessLeft[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f;
  return;
}

  // if(fThicknessLeft[nCh20][nCh100]<10 || fThicknessLeft[nCh20][nCh100] > 30) return;

  // Double_t dE = m_SSD20->GetValue()*par20_2 + par20_1;
  // dE = dE*20./fThicknessLeft[nCh20][nCh100];
  // Double_t Etotal = m_DSDX->GetValue()*par100_2 + par100_1 + dE;
  // }


void CsIselect() {
  // cout << " check " << endl;
  if(nCsI>-1 && nCsI!=9 && cutCsI[nCsI]->IsInside(tCsI-tF5, aCsI)) {
    // cout << "fine!" << endl;
    return;
  }
  else {
    aCsI = 0;
    tCsI = 0;
    nCsI = -1;    
  }
}  

void DSD_Cselect() {

  if ( (tX_C - tF5 < 80) && (tX_C - tF5 > 140)) {
    tX_C = 0;
    X_C = 0;
  }
  if ( (tY_C - tF5 < 80) || (tY_C - tF5 >140)){
    tY_C = 0;
    Y_C = 0;
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
    // check if thickness if reasonable
  if(fThicknessLeft[n20_L][nY_L]<10 || fThicknessLeft[n20_L][nY_L] > 30) {
    a20_L = 0;
    t20_L = 0;
    n20_L = -1;
  }
  // cout << fThicknessLeft[n20_L][nY_L] << endl;
  a20_L = a20_L*20./fThicknessLeft[n20_L][nY_L];
  return;
}

void coincidense(){

  if(nCsI>-1 && nCsI!=9 && cut3h[nCsI]->IsInside(aCsI, X_C)) {
    nh3 = 1;
    return;
  }
  else {
    nh3 = 0;
    return;
  }

}

void X_Lselect() {
  // cout << " check " << endl;
  if(nX_L>-1 && nX_L<16 && X_L>0 && cutX_L[nX_L]->IsInside(tX_L-tF5, X_L)) {
    // cout << "fine!" << endl;
    return;
  }
  else {
    X_L = 0;
    tX_L = 0;
    nX_L = -1;    
  }


}

void Y_Lselect() {
  // cout << " check " << endl;
  if(nY_L>-1 && nY_L<16 && Y_L>0 && cutY_L[nY_L]->IsInside(tY_L-tF5, Y_L)) {
    // cout << "fine!" << endl;
    return;
  }
  else {
    Y_L = 0;
    tY_L = 0;
    nY_L = -1;    
  }


}