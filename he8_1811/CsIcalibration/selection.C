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

void checkhe4();
void checkhe8();
void triton();
void CsI_heIsotope();
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

Float_t tMWPC,wirex1,wirex2,wirey1,wirey2;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Int_t nCsI_s;
Float_t aCsI_s,tCsI_s;

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


TCutG *cutCsI[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16],*cuthe4,*cuthe8,*cutCsI_isotope;
Int_t nh3,nh3_s,nTarget,nhe8,nMWPC,nhe3,nhe4,nheIsotope;
Int_t flagLeft,flagCent,flagCent_arr,mult20,multX,multY;


Int_t number = 0;

void selection() {
  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all.root");
  // ch->Add("/home/oem/work/data/exp1811/analysed/notarget_all trigger.root");
  // ch->Add("/home/oem/work/data/exp1811/analysed/he8_alltriggers.root");
  

  // ch->Add("/home/oem/work/data/exp1811/analysed/notarget.root");
  
  // ch->Add("/home/oem/work/data/exp1811/analysed/he8_trigger2_noCal.root");

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

  TFile *f,*f1,*f2,*f3,*f4,*f5;
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

  cutName.Form("/home/oem/work/macro/he8_1811/he4_CsI_cut.root");
  f5 = new TFile(cutName.Data());
  cutCsI_isotope = (TCutG*)f5->Get("CUTG");
  delete f5;  

  cutName.Form("/home/oem/work/macro/he8_1811/alphaCut.root");
  f3 = new TFile(cutName.Data());
  cuthe4 = (TCutG*)f3->Get("CUTG");
  delete f3;

  cutName.Form("/home/oem/work/macro/he8_1811/he8_cut.root");
  f4 = new TFile(cutName.Data());
  cuthe8 = (TCutG*)f4->Get("CUTG");
  delete f4;

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
  readCsImap();

  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/h7_all_cut.root", "RECREATE");
   // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_alltriggers_cut.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_trigger2_nocal_cut.root", "RECREATE");  
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/notarget_cut_alltriggers.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_selected.root", "RECREATE");
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

  tw->Branch("aCsI_s.",&aCsI_s,"aCsI_s/F");
  tw->Branch("tCsI_s.",&tCsI_s,"tCsI_s/F");
  tw->Branch("nCsI_s.",&nCsI_s,"nCsI_s/I");

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

  tw->Branch("X_L_ch.",&X_L_ch,"X_L_ch/F");
  tw->Branch("Y_L_ch.",&Y_L_ch,"Y_L_ch/F");
  tw->Branch("a20_L_ch.",&a20_L_ch,"a20_L_ch/F");
  tw->Branch("a20_L_uncorr_ch.",&a20_L_uncorr_ch,"a20_L_uncorr_ch/F"); 

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
  tw->Branch("mult20.",&mult20,"mult20/I");
  tw->Branch("multX.",&multX,"multX/I");  
  tw->Branch("multY.",&multY,"multY/I");   
  tw->Branch("nhe3.",&nhe3,"nhe3/I");
  tw->Branch("nhe4.",&nhe4,"nhe4/I");
  tw->Branch("nheIsotope.",&nheIsotope,"nheIsotope/I");  
  tw->Branch("nhe8.",&nhe8,"nhe8/I");  

  tw->Branch("flagLeft.",&flagLeft,"flagLeft/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  // tw->Branch("flagCent_arr.",&flagCent_arr,"flagCent_arr/I");

  // tw->Branch("nTarget.",&nTarget,"nTarget/I");

  Float_t xTarget,yTarget;
  xTarget = -1.;
  yTarget = 2.2;

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<1000000;nentry++) {     
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << "###ENTRY " << nentry << "###" << endl;
    ch->GetEntry(nentry);
    if (trigger==1) continue;

    nh3 = 0;
    nh3_s = 0;
    nhe3 = 0;
    nhe4 = 0;
    nheIsotope = 0;
    nhe8 = 0;
    timesMWPC = kTRUE;
    timesToF = kTRUE;
    vetoFlag = 0;
    flagLeft = 1;
    flagCent = 1;
    flagCent_arr = 1;

    checkToF();
    if (!timesToF) continue;

    cutMWPC();
    if (!timesMWPC) continue;

    for(Int_t i=0;i<16;i++) {
      if(SSD_L[i]>0 && tSSD_L[i]>0) vetoFlag = 1;
    }
    if(vetoFlag) continue; 

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xTarget)*(fXt-xTarget) + (fYt-yTarget)*(fYt-yTarget))>8*8 ) continue;

    fillSi();
    fillCsI();

    CsIselect();
    // CsIselect_arr();

    DSD_Cselect();
    SSD20_Lselect();

    X_Lselect();
    Y_Lselect();

    if(flagCent) {
      triton();
      CsI_heIsotope();
      // triton_arr();
      GetXYCent();
    }

    if (flagLeft) {
      if(n20_L==13) {
        checkhe4();
        checkhe8();
      }
      checkHe3();
      GetXYLeft();
    }

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {
  mult20 = 0;
  multX = 0;
  multY = 0;

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

  nX_C = -1;
  nY_C = -1;
  nX_L = -1;
  nY_L = -1;
  n20_L = -1;

  nCsI_s = 0;
  aCsI_s = 0;
  tCsI_s = 0;

  xLeft = -50;
  yLeft = -50;
  zLeft = -50;

  xCent = -50;
  yCent = -50;
  zCent = -50;

  x1c = -50;
  y1c = -50;
  x2c = -50;
  y2c = -50;

  fXt = -100;
  fYt = -100;

  X_L_ch = 0;
  Y_L_ch = 0;
  a20_L_ch = 0;
  a20_L_uncorr_ch = 0;
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

  // if(fThicknessLeft[nCh20][nCh100]<10 || fThicknessLeft[nCh20][nCh100] > 30) return;

  // Double_t dE = m_SSD20->GetValue()*par20_2 + par20_1;
  // dE = dE*20./fThicknessLeft[nCh20][nCh100];
  // Double_t Etotal = m_DSDX->GetValue()*par100_2 + par100_1 + dE;
  // }


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

void CsIselect_arr() {

  if (nCsI_s==9) {
    flagCent_arr = 0;
    return; 
  }

  // cout << " check " << endl;
  if(nCsI_s>-1 && nCsI_s!=9 && cutCsI[nCsI_s]->IsInside(tCsI_s-tF5, aCsI_s)) {
    return;
  }
  else {
    flagCent_arr = 0;
    // aCsI_s = 0;
    // nCsI_s = -1;
    // tCsI_s = 0;  
    return; 
  }
}

void fillCsI() {
  Int_t crystN = CsImap[nX_C][nY_C];
  if (crystN<0 || crystN>15) return; 
  nCsI_s = crystN;
  aCsI_s = arCsI[crystN];
  tCsI_s = trCsI[crystN];
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

void SSD20_Lselect() {
  a20_L_uncorr = a20_L;
  a20_L_uncorr_ch = a20_L_ch;

  a20_L = a20_L*20./fThicknessLeft[n20_L][nY_L];
  a20_L_ch = a20_L_ch*20./fThicknessLeft[n20_L][nY_L];

  // if (n20_L>-1 && n20_L<16 && a20_L>0 && cutSQ20_L[n20_L]->IsInside(t20_L-tF5, a20_L)) {
    
  //   // a20_L = a20_L*20./fThicknessLeft[n20_L][nY_L];
  // }
  // else {
  //   flagLeft = 0;
  // }

  // if (t20_L-tF5<40 || t20_L-tF5>120) { //time cuts
  //   flagLeft = 0;
  //   // t20_L = 0;
  //   // a20_L = 0;
  //   // n20_L = -1;
  //   return; 
  // }
    // check if thickness if reasonable
  if (fThicknessLeft[n20_L][nY_L]<10 || fThicknessLeft[n20_L][nY_L] > 30) {
    flagLeft = 0;
    // t20_L = 0;
    // a20_L = 0;
    // n20_L = -1;
    return;
  }
  // cout << fThicknessLeft[n20_L][nY_L] << endl;
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

void CsI_heIsotope() {

  if(nCsI>-1 && nCsI==6 && cutCsI_isotope->IsInside(aCsI_cal, X_C)) {
    nheIsotope = 1;
    return;
  }
  else {
    nheIsotope = 0;
    return;
  }
}


void triton_arr() {

  if(nCsI_s>-1 && nCsI_s!=9 && cut3h[nCsI_s]->IsInside(aCsI_s, X_C)) {
    nh3_s = 1;
    return;
  }
  else {
    nh3_s = 0;
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

void checkhe4() {
  if(nX_L>-1 && n20_L>-1 && cuthe4->IsInside(X_L, a20_L)) {
    nhe4 = 1;
    return;
  }
  else {
    nhe4 = 0;
    return;
  }
}

void checkhe8() {
  if(nX_L>-1 && n20_L>-1 && cuthe8->IsInside(X_L, a20_L)) {
    nhe8 = 1;
    return;
  }
  else {
    nhe8 = 0;
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

void readCsImap() {
  for(Int_t i=0;i<8;i++) {
    for(Int_t j=0;j<8;j++) {
      CsImap[i][j] = 7;
    }
  }

  for(Int_t i=8;i<16;i++) {
    for(Int_t j=0;j<8;j++) {
      CsImap[i][j] = 6;
    }
  }

  for(Int_t i=16;i<24;i++) {
    for(Int_t j=0;j<8;j++) {
      CsImap[i][j] = 5;
    }
  } 

  for(Int_t i=24;i<32;i++) {
    for(Int_t j=0;j<8;j++) {
      CsImap[i][j] = 4;
    }
  }

//----------------------------------
  for(Int_t i=0;i<8;i++) {
    for(Int_t j=8;j<16;j++) {
      CsImap[i][j] = 3;
    }
  }

  for(Int_t i=8;i<16;i++) {
    for(Int_t j=8;j<16;j++) {
      CsImap[i][j] = 2;
    }
  }

  for(Int_t i=16;i<24;i++) {
    for(Int_t j=8;j<16;j++) {
      CsImap[i][j] = 1;
    }
  } 

  for(Int_t i=24;i<32;i++) {
    for(Int_t j=8;j<16;j++) {
      CsImap[i][j] = 0;
    }
  }
//----------------------------------

  for(Int_t i=0;i<8;i++) {
    for(Int_t j=16;j<24;j++) {
      CsImap[i][j] = 15;
    }
  }

  for(Int_t i=8;i<16;i++) {
    for(Int_t j=16;j<24;j++) {
      CsImap[i][j] = 14;
    }
  }

  for(Int_t i=16;i<24;i++) {
    for(Int_t j=16;j<24;j++) {
      CsImap[i][j] = 13;
    }
  } 

  for(Int_t i=24;i<32;i++) {
    for(Int_t j=16;j<24;j++) {
      CsImap[i][j] = 12;
    }
  }
//----------------------------------

  for(Int_t i=0;i<8;i++) {
    for(Int_t j=24;j<32;j++) {
      CsImap[i][j] = 11;
    }
  }

  for(Int_t i=8;i<16;i++) {
    for(Int_t j=24;j<32;j++) {
      CsImap[i][j] = 10;
    }
  }

  for(Int_t i=16;i<24;i++) {
    for(Int_t j=24;j<32;j++) {
      CsImap[i][j] = 9;
    }
  } 

  for(Int_t i=24;i<32;i++) {
    for(Int_t j=24;j<32;j++) {
      CsImap[i][j] = 8;
    }
  }
}
//----------------------------------

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

void GetXYCent() {
  // coordinates in the system of detector
  xCent = 32. - nX_C*64./32;
  yCent = 32. - nY_C*64./32;
  zCent = 280.;

  return;
}