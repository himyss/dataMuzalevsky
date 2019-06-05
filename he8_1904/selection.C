void zeroVars();
void checkToF();
void cutMWPC();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void CsIselect();
void CsIselect_arr();
void DSD_Cselect();
void SQ20_1select();
void X_Lselect();
void Y_Lselect();

void fillSi();
void fillCsI();

void readThickness();
void readCsImap();

void triton();
void triton_arr();
void checkHe3();

// reconstruction
void GetXYLeft();
void GetXYCent();

const Double_t angleLeft =  17.;
const Double_t leftDistance = 180.;

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC;
Int_t wirex1,wirex2,wirey1,wirey2;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Float_t a20_1,t20_1;
Int_t n20_1;

Float_t a1_1,t1_1;
Int_t n1_1;

Int_t multv_1,mult20_1,mult1_1;
Int_t multc_y,multc_x;

Int_t nCsI_s;
Float_t aCsI_s,tCsI_s;

Float_t arCsI[16],trCsI[16];

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_L_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L;
//
Float_t DSD_X[32],DSD_Y[32];
Float_t tDSD_X[32],tDSD_Y[32];

Float_t SSD1[16],DSDY_L[16],SQ20_1[16],SSD_L[16],tSSD1[16],tDSDY_L[16],tSQ20_1[16],tSSD_L[16];
Float_t SSD1_ch[16],DSDY_L_ch[16],SQ20_1_ch[16];

// reconstructed

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xCent,yCent,zCent;
// flags
Bool_t timesToF,timesMWPC,vetoFlag;


Double_t fThickness1[16][16];

Int_t CsImap[32][32];


TCutG *cutCsI[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16];
Int_t nh3,nh3_s,nTarget,nHe8,nMWPC,nhe3;
Int_t flag1,flagCent,flagCent_arr,mult20,multX,multY;

Int_t number = 0;

void selection() {
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1904/analysed/h7/h7_run0_26.root");

  // ch->Add("/home/oem/work/data/exp1811/analysed/notarget.root");
  
  // ch->Add("/home/oem/work/data/exp1811/analysed/he8_trigger2_noCal.root");

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

  ch->SetBranchAddress("DSD_X",&DSD_X);
  ch->SetBranchAddress("tDSD_X",&tDSD_X);
  ch->SetBranchAddress("DSD_Y",&DSD_Y); 
  ch->SetBranchAddress("tDSD_Y",&tDSD_Y);

  ch->SetBranchAddress("SSD1",&SSD1);
  ch->SetBranchAddress("SQ20_1",&SQ20_1);
  ch->SetBranchAddress("tSSD1",&tSSD1);
  ch->SetBranchAddress("tSQ20_1",&tSQ20_1);

  ch->SetBranchAddress("multv_1",&multv_1);
  ch->SetBranchAddress("mult20_1",&mult20_1);
  ch->SetBranchAddress("mult1_1",&mult1_1);

  ch->SetBranchAddress("multc_x",&multc_x);
  ch->SetBranchAddress("multc_y",&multc_y);

  TFile *f,*f1,*f2;
  TString cutName;

  readThickness();

  TFile *fw = new TFile("/home/oem/work/data/exp1904/analysed/h7/h7_cut.root", "RECREATE");

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

  tw->Branch("a20_1.",&a20_1,"a20_1/F");
  tw->Branch("t20_1.",&t20_1,"t20_1/F");
  tw->Branch("n20_1.",&n20_1,"n20_1/I");

  tw->Branch("a1_1.",&a1_1,"a1_1/F");
  tw->Branch("t1_1.",&t1_1,"t1_1/F");
  tw->Branch("n1_1.",&n1_1,"n1_1/I");

  tw->Branch("flag1.",&flag1,"flag1/I");

  Float_t xCent,yCent;
  xCent = -1.;
  yCent = 2.2;

  // for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  for(Int_t nentry=0;nentry<20000000;nentry++) {     
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);

    if (trigger!=2) continue;

    checkToF();
    if (!timesToF) continue;

    cutMWPC();
    if (!timesMWPC) continue;

    if (multv_1>0 || mult20_1>1 || mult1_1>1) continue;

    if (multc_x>1 || multc_y>1) continue;

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xCent)*(fXt-xCent) + (fYt-yCent)*(fYt-yCent))>8*8 ) continue;

    fillSi();
    // cout << n1_1 << " " << n20_1 << " " << fThickness1[]
    // fillCsI();

    // CsIselect();
    // CsIselect_arr();

    // DSD_Cselect();
    SQ20_1select();

    // X_Lselect();
    // Y_Lselect();

    // if(flagCent) {
    //   triton();
    //   triton_arr();
    //   GetXYCent();
    // }

    // if (flag1) {
    //   checkHe3();
    //   GetXYLeft();
    // }

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {

  aCsI = 0;
  tCsI = 0;
  nCsI = -1;

  X_C = 0;
  tX_C = 0;
  Y_C = 0;
  tY_C = 0;

  nX_C = -1;
  nY_C = -1;

  x1c = -50;
  y1c = -50;
  x2c = -50;
  y2c = -50;

  fXt = -100;
  fYt = -100;

  a20_1 = 0;
  t20_1 = 0;
  n20_1 = -1;

  flag1 = 1;

} 

void checkToF() {
  if (F5<2200 || F5>4200 || tF5-tF3<103 || tF5-tF3>117 || F3<2200 || F3>4200 ) timesToF = kFALSE;
  else timesToF = kTRUE;
  return;
}

void cutMWPC() {
  if ( (tMWPC - tF5)<75 || (tMWPC - tF5)>97.5 ) timesMWPC = kFALSE;
  else timesMWPC = kTRUE;
  return;
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
  cout << "thickness of the first detector " << endl;
  TFile *f = new TFile("/home/oem/work/software/AculUti/data/thickness1.root","READ");
  if (f->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness1[i][j] = 20.;
        cout << fThickness1[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick = (TH2F*)f->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness1[i][j] = hThick->GetBinContent(i+1,j+1);
        cout << fThickness1[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f;

}



void fillCsI() {
  Int_t crystN = CsImap[nX_C][nY_C];
  if (crystN<0 || crystN>15) return; 
  nCsI_s = crystN;
  aCsI_s = arCsI[crystN];
  tCsI_s = trCsI[crystN];
  return;
}

void fillSi() {
 
  for(Int_t i=0;i<32;i++) {
    if (DSD_X[i]>0 && tDSD_X[i]>0){
      X_C = DSD_X[i];
      tX_C = tDSD_X[i];
      nX_C = i;
      break;
    } 
  }

  for(Int_t i=0;i<32;i++) {
    if (DSD_Y[i]>0 && tDSD_Y[i]>0){
      Y_C = DSD_Y[i];
      tY_C = tDSD_Y[i];
      nY_C = i;
      break;
    } 
  }

  for(Int_t i=0;i<16;i++) {
    if (SQ20_1[i]>0 && tSQ20_1[i]>0){
      a20_1 = SQ20_1[i];
      t20_1 = tSQ20_1[i];
      n20_1 = i;
      break;
    } 
  }

  for(Int_t i=0;i<16;i++) {
    if (SSD1[i]>0 && tSSD1[i]>0){
      a1_1 = SSD1[i];
      t1_1 = tSSD1[i];
      n1_1 = i;
      break;
    } 
  }


}

void GetXYLeft() {
  // coordinates in the system of detector
  xLeft = 30. - nX_L*60./16;
  yLeft = 30. - nY_L*60./16;
  zLeft = 0;

  // rotate the detector
  xLeft = xLeft*cos(angleLeft*TMath::DegToRad());
  zLeft = xLeft*sin(angleLeft*TMath::DegToRad());

  // transfer the detector
  xLeft = xLeft + leftDistance*sin(angleLeft*TMath::DegToRad());
  zLeft = zLeft + leftDistance*cos(angleLeft*TMath::DegToRad());

  return;
}

void GetXYCent() {
  // coordinates in the system of detector
  xCent = 32. - nX_C*64./32;
  yCent = 32. - nY_C*64./32;
  zCent = 280.;

  return;
}

void SQ20_1select() {
  a20_1 = a20_1*20./fThickness1[n20_1][n1_1];
  if (fThickness1[n20_1][n1_1]<10 || fThickness1[n20_1][n1_1] > 30) {
    flag1 = 0;
    return;
  }
  return;
}

