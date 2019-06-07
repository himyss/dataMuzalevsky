void setTables();
void zeroVars();
void checkToF();
void cutMWPC();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void CsIselect();
void CsIselect_arr();
void DSD_Cselect();
void SSD20_Lselect();
void X_Lselect();
void Y_Lselect();

void fillSi();
void fillCsI();

void readThickness();
void readCsImap();

void triton();
void heIsotope();
void triton_arr();
void checkHe3();

// reconstruction
void GetXYLeft();
void GetXYCent();

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);
Float_t calculateBeam();

const Double_t angleLeft =  17.;
const Double_t leftDistance = 180.;

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC,wirex1,wirex2,wirey1,wirey2;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Int_t nCsI_s;
Float_t aCsI_s,tCsI_s,aCsI_reco;

Float_t arCsI[16],trCsI[16];

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_L_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L;
//
Float_t DSDX_C[32],DSDY_C[32];
Float_t tDSDX_C[32],tDSDY_C[32];

Float_t DSDX_L[16],DSDY_L[16],SSD20_L[16],SSD_L[16],tDSDX_L[16],tDSDY_L[16],tSSD20_L[16],tSSD_L[16];
Float_t DSDX_L_ch[16],DSDY_L_ch[16],SSD20_L_ch[16];

Float_t X_L_ch,Y_L_ch,a20_L_ch,a20_L_uncorr_ch;
// reconstructed

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xCent,yCent,zCent;
// flags
Bool_t timesToF,timesMWPC,vetoFlag;

Double_t fThicknessRight[16][16];
Double_t fThicknessLeft[16][16];

Int_t CsImap[32][32];


TCutG *cutCsI[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16],*cutHeIsotope;
Int_t nh3,nh3_s,nTarget,nHe8,nMWPC,nhe3,nHeIsotope;
Int_t flagLeft,flagCent,flagCent_arr,mult20,multX,multY,fTarget;

Int_t number = 0;

TELoss *f3HeSi;
TELoss *f3HeMylar;
TELoss *f3HeSteel;
TELoss *f3HeTarget;

TELoss *f3HSi;
TELoss *f3HMylar;
TELoss *f3HSteel;
TELoss *f3HTarget;

TVector3 dirLeft,dirCent,dirBeam;
Double_t angleCent;
Float_t ebeam;
Int_t beamH3;
Float_t pCsI1[16],pCsI2[16];

Float_t tempE, tempThick;
void calctritons() {
  // setTables();
  readPar("CsI_may",pCsI1,pCsI2);

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all.root");
  // ch->Add("/home/oem/work/data/exp1811/calibration/CsI/DSD_CsI_focused_all.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------  
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("aCsI.",&aCsI);
  ch->SetBranchAddress("aCsI_cal.",&aCsI_cal);
  ch->SetBranchAddress("tCsI.",&tCsI);
  ch->SetBranchAddress("nCsI.",&nCsI);

  ch->SetBranchAddress("arCsI",&arCsI);
  ch->SetBranchAddress("trCsI",&trCsI);

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

  ch->SetBranchAddress("DSDX_L_ch",&DSDX_L_ch);
  ch->SetBranchAddress("DSDY_L_ch",&DSDY_L_ch);
  ch->SetBranchAddress("SSD20_L_ch",&SSD20_L_ch);

  TFile *f,*f1,*f2,*fHe;
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

  cutName.Form("/home/oem/work/macro/he8_1811/CsI_6.root");
  fHe = new TFile(cutName.Data());
  cutHeIsotope = (TCutG*)fHe->Get("CUTG");
  delete fHe;

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
    cutName.Form("/home/oem/work/macro/he8_1811/helium3/he3_%d.root",i);
    f2 = new TFile(cutName.Data());
    cuthe3[i] = (TCutG*)f2->Get("CUTG");
    if (!cuthe3[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f2;
  }


  readThickness();
  // readCsImap();

  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/h7_all_3h_cut1.root", "RECREATE");
  // TFile *fw = new TFile("test.root", "RECREATE");  
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
  tw->Branch("aCsI_reco.",&aCsI_reco,"aCsI_reco/F");
  tw->Branch("aCsI_cal.",&aCsI_cal,"aCsI_cal/F");
  tw->Branch("tCsI.",&tCsI,"tCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("X_C.",&X_C,"X_C/F");
  tw->Branch("nX_C.",&nX_C,"nX_C/I");
  tw->Branch("tX_C.",&tX_C,"tX_C/F");
  tw->Branch("Y_C.",&Y_C,"Y_C/F");
  tw->Branch("tY_C.",&tY_C,"tY_C/F");
  tw->Branch("nY_C.",&nY_C,"nY_C/I");

  tw->Branch("x1c.",&x1c,"x1c/F");
  tw->Branch("y1c.",&y1c,"y1c/F");
  tw->Branch("x2c.",&x2c,"x2c/F");
  tw->Branch("y2c.",&y2c,"y2c/F"); 
  tw->Branch("fXt.",&fXt,"fXt/F");
  tw->Branch("fYt.",&fYt,"fYt/F"); 

  tw->Branch("xCent.",&xCent,"xCent/F");
  tw->Branch("yCent.",&yCent,"yCent/F");
  tw->Branch("zCent.",&zCent,"zCent/F");

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nHeIsotope.",&nHeIsotope,"nHeIsotope/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");

  tw->Branch("ebeam.",&ebeam,"ebeam/F");
  tw->Branch("beamH3.",&beamH3,"beamH3/I");
  tw->Branch("fTarget.",&fTarget,"fTarget/I");

  Float_t xTarget,yTarget;
  xTarget = -1.;
  yTarget = 2.2;

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<2000000;nentry++) {     
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << "###ENTRY " << nentry << "###" << endl;
    ch->GetEntry(nentry);

    // if (nCsI!=6) continue;

    beamH3 = 1;
    nh3 = 0;
    nHeIsotope = 0;
    nhe3 = 0;
    timesMWPC = kTRUE;
    timesToF = kTRUE;
    vetoFlag = 0;
    flagLeft = 1;
    flagCent = 1;
    flagCent_arr = 1;

    checkToF();
    if (!timesToF) continue;;

    cutMWPC();
    if (!timesMWPC) continue;

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xTarget)*(fXt-xTarget) + (fYt-yTarget)*(fYt-yTarget))>8*8 ) fTarget=0;

    fillSi();
    fillCsI();

    CsIselect();

    DSD_Cselect();

    if(flagCent) {
      heIsotope();
      triton();
      GetXYCent();
    }

    if (flagCent && nh3) {
      dirCent.SetXYZ(xCent-fXt, yCent-fYt, zCent);
      angleCent = dirCent.Theta();
      Float_t thickness = 1500./cos(angleCent);
      aCsI_reco = f3HSi->GetE0dE(Y_C, thickness);
      if (beamH3) {
        ebeam = calculateBeam();

        dirBeam.SetXYZ(x2c-x1c, y2c-y1c, 545.);
        ebeam = f3HSi->GetE(ebeam,644./cos(dirBeam.Theta())); 
        ebeam = f3HTarget->GetE(ebeam,6000./cos(angleCent)); 
        ebeam = f3HSteel->GetE(ebeam,12./cos(angleCent));
        ebeam = f3HMylar->GetE(ebeam,7/cos(angleCent)); 
        ebeam = f3HSi->GetE(ebeam,1510./cos(angleCent));
      }
    }

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  ebeam = 0;
  aCsI_cal = 0;

  fTarget=1;

  X_C = 0;
  tX_C = 0;
  Y_C = 0;
  tY_C = 0;
  X_L = 0;
  Y_L = 0;

  nX_C = -1;
  nY_C = -1;

  aCsI_reco = 0;

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
  // if(F5<400 || F5>1300 || tF5-tF3<60 || tF5-tF3>75 || F3<300 || F3>1250 ) beamH3=0;
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
  TFile *f1 = new TFile("/media/user/work/macro/he8_1811/parameters/thicknessRight.root","READ");
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
  if(nCsI>-1 && nCsI!=9 && cutCsI[nCsI]->IsInside(tCsI-tF5, aCsI)) {
    return;
  }
  else {
    flagCent = 0; 
    // aCsI = 0;
    // nCsI = -1;
    // tCsI = 0;  
    return; 
  }
}  

void fillCsI() {
  // Int_t crystN = CsImap[nX_C][nY_C];
  // if (crystN<0 || crystN>15) return; 
  // nCsI_s = crystN;
  // aCsI_s = arCsI[crystN];
  // tCsI_s = trCsI[crystN];

  aCsI_cal = aCsI*pCsI2[nCsI] + pCsI1[nCsI];
  return;
}

void DSD_Cselect() {

  if ( (tX_C - tF5 < 118) || (tX_C - tF5 > 135)) {
    flagCent = 0;
    flagCent_arr = 0;
    // X_C = 0;
    // nX_C = -1;
    // tX_C = 0;
  }
  if ( (tY_C - tF5 < 123) || (tY_C - tF5 >135)){
    flagCent = 0;
    flagCent_arr = 0;
    // Y_C = 0;
    // nY_C = -1;
    // tY_C = 0;    
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
  multX = count;
  if(count==1) {
    X_L = DSDX_L[nCh];
    tX_L = tDSDX_L[nCh];
    nX_L = nCh;

    X_L_ch = DSDX_L_ch[nCh];
  }

  count = 0;
  for(Int_t i=0;i<16;i++) {
    if (DSDY_L[i]>0 && tDSDY_L[i]>0){
      nCh = i;
      count++;
    } 
  }
  multY = count;
  if(count==1) {
    Y_L = DSDY_L[nCh];
    Y_L_ch = DSDY_L_ch[nCh];
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
  mult20 = count;
  if(count==1) {
    a20_L = SSD20_L[nCh];
    a20_L_ch = SSD20_L_ch[nCh];
    t20_L = tSSD20_L[nCh];
    n20_L = nCh;
  }
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

void heIsotope() {

  if(nCsI>-1 && nCsI!=9 && cutHeIsotope->IsInside(aCsI_cal, X_C)) {
    nHeIsotope = 1;
    return;
  }
  else {
    nHeIsotope = 0;
    return;
  }
}


void GetXYCent() {
  // coordinates in the system of detector
  xCent = 32. - nX_C*64./32;
  yCent = 32. - nY_C*64./32;
  zCent = 280.;

  return;
}

void setTables() {

// Si
  f3HSi = new TELoss();
  f3HSi->SetEL(1, 2.321); // density in g/cm3
  f3HSi->AddEL(14., 28.086, 1);  //Z, mass
  f3HSi->SetZP(1., 3.);   //alphas, Z, A
  f3HSi->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HSi->SetDeltaEtab(300);

  // mylar
  f3HMylar = new TELoss();
  f3HMylar->SetEL(1, 1.39); // density in g/cm3
  f3HMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
  f3HMylar->AddEL(1., 1.00784, 0.36);
  f3HMylar->AddEL(8., 15.99903, 0.19);
  f3HMylar->SetZP(1., 3.);   //alphas, Z, A
  f3HMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HMylar->SetDeltaEtab(300);

  // steel
  f3HSteel = new TELoss();
  f3HSteel->SetEL(1, 8.0); // density in g/cm3
  f3HSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
  f3HSteel->AddEL(26., 55.845, 0.74);  
  f3HSteel->AddEL(28., 58.6934, 0.19);
  f3HSteel->SetZP(1., 3.);   //alphas, Z, A
  f3HSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HSteel->SetDeltaEtab(300);

  // deuterium target
  f3HTarget = new TELoss();
  f3HTarget->SetEL(1, 0.0018431); // density in g/cm3
  f3HTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f3HTarget->SetZP(1., 3.);   //alphas, Z, A
  f3HTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HTarget->SetDeltaEtab(300);
  //--------------------------------------------------------------------------------

  return;
}


Float_t calculateBeam() {

  Float_t mass = 2.80892;

  Float_t velocity = 12320./(tF5-tF3 + 68.475);
  Float_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  Float_t kinEnergy = 1000*mass*((1/beta) - 1);


  return kinEnergy;
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
