Double_t calcVectorTel1(Int_t n20, Int_t n1);
Double_t calcVectorTel2(Int_t n20, Int_t n1);
Double_t calcVectorTel3(Int_t n20, Int_t n1);
Double_t calcVectorTel4(Int_t n20, Int_t n1);

void readCuts();

void zeroVars();
void checkToF();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void CsItimes();
void DSD_Cselect();
void correct();
void X_Lselect();
void Y_Lselect();

void fillSi();

void readThickness();

void triton();
void checkHe3();
void timesSQ20();
void timesSQ1();

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC;
Int_t wirex1,wirex2,wirey1,wirey2;

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t a20_1,t20_1,a20_1_un;
Int_t n20_1;

Float_t a1_1,t1_1;
Int_t n1_1;

Float_t a20_2,t20_2,a20_2_un;
Int_t n20_2;

Float_t a1_2,t1_2;
Int_t n1_2;

Float_t a20_3,t20_3,a20_3_un;
Int_t n20_3;

Float_t a1_3,t1_3;
Int_t n1_3;

Float_t a20_4,t20_4,a20_4_un;
Int_t n20_4;

Float_t a1_4,t1_4;
Int_t n1_4;

Int_t multv_1,mult20_1,mult1_1;
Int_t multv_2,mult20_2,mult1_2;
Int_t multv_3,mult20_3,mult1_3;
Int_t multv_4,mult20_4,mult1_4;
Int_t multc_y,multc_x;

Float_t X_C,tX_C,Y_C,tY_C;
Int_t nX_C,nY_C;
//
Float_t DSD_X[32],DSD_Y[32];
Float_t tDSD_X[32],tDSD_Y[32];

Float_t SSD1[16],SQ20_1[16],tSSD1[16],tSQ20_1[16],SSD_V1[16],tSSD_V1[16];
Float_t SSD2[16],SQ20_2[16],tSSD2[16],tSQ20_2[16],SSD_V2[16],tSSD_V2[16];
Float_t SSD3[16],SQ20_3[16],tSSD3[16],tSQ20_3[16],SSD_V3[16],tSSD_V3[16];
Float_t SSD4[16],SQ20_4[16],tSSD4[16],tSQ20_4[16],SSD_V4[16],tSSD_V4[16];
// reconstructed

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;

// flags
Bool_t timesToF,timesMWPC;

Double_t fThickness1[16][16],fThickness2[16][16],fThickness3[16][16],fThickness4[16][16];

Int_t flag1,flag2,flag3,flag4,flagCent;
Int_t nh3,nhe3_1,nhe3_2,nhe3_3,nhe3_4;

TCutG *cutCsI[16],*cut3h[16],*cutX_C[16];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];
TCutG *ToF_F5,*ToF_F3;

TCutG *cut1_he3,*cut2_he3,*cut3_he3,*cut4_he3;

Float_t v_he3_1,v_he3_2,v_he3_3,v_he3_4;

void selection_june() {

  readCuts();

  TChain *ch = new TChain("tree");
  ch->Add("/media/oem/data/exp1906/analysed/be10_ct.root");

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
  ch->SetBranchAddress("SSD_V1",&SSD_V1);
  ch->SetBranchAddress("tSSD_V1",&tSSD_V1);

  ch->SetBranchAddress("SSD2",&SSD2);
  ch->SetBranchAddress("SQ20_2",&SQ20_2);
  ch->SetBranchAddress("tSSD2",&tSSD2);
  ch->SetBranchAddress("tSQ20_2",&tSQ20_2);
  ch->SetBranchAddress("SSD_V2",&SSD_V2);
  ch->SetBranchAddress("tSSD_V2",&tSSD_V2);

  ch->SetBranchAddress("SSD3",&SSD3);
  ch->SetBranchAddress("SQ20_3",&SQ20_3);
  ch->SetBranchAddress("tSSD3",&tSSD3);
  ch->SetBranchAddress("tSQ20_3",&tSQ20_3);
  ch->SetBranchAddress("SSD_V3",&SSD_V3);
  ch->SetBranchAddress("tSSD_V3",&tSSD_V3);

  ch->SetBranchAddress("SSD4",&SSD4);
  ch->SetBranchAddress("SQ20_4",&SQ20_4);
  ch->SetBranchAddress("tSSD4",&tSSD4);
  ch->SetBranchAddress("tSQ20_4",&tSQ20_4);
  ch->SetBranchAddress("SSD_V4",&SSD_V4);
  ch->SetBranchAddress("tSSD_V4",&tSSD_V4);

  ch->SetBranchAddress("multv_1",&multv_1);
  ch->SetBranchAddress("mult20_1",&mult20_1);
  ch->SetBranchAddress("mult1_1",&mult1_1);

  ch->SetBranchAddress("multv_2",&multv_2);
  ch->SetBranchAddress("mult20_2",&mult20_2);
  ch->SetBranchAddress("mult1_2",&mult1_2);

  ch->SetBranchAddress("multv_3",&multv_3);
  ch->SetBranchAddress("mult20_3",&mult20_3);
  ch->SetBranchAddress("mult1_3",&mult1_3);

  ch->SetBranchAddress("multv_4",&multv_4);
  ch->SetBranchAddress("mult20_4",&mult20_4);
  ch->SetBranchAddress("mult1_4",&mult1_4);

  ch->SetBranchAddress("multc_x",&multc_x);
  ch->SetBranchAddress("multc_y",&multc_y);

  readThickness();

  TFile *fw = new TFile("/media/oem/data/exp1906/analysed/be10_ct_cut.root", "RECREATE");
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
  tw->Branch("a20_1_un.",&a20_1_un,"a20_1_un/F");
  tw->Branch("t20_1.",&t20_1,"t20_1/F");
  tw->Branch("n20_1.",&n20_1,"n20_1/I");

  tw->Branch("a1_1.",&a1_1,"a1_1/F");
  tw->Branch("t1_1.",&t1_1,"t1_1/F");
  tw->Branch("n1_1.",&n1_1,"n1_1/I");

  tw->Branch("a20_2.",&a20_2,"a20_2/F");
  tw->Branch("a20_2_un.",&a20_2_un,"a20_2_un/F");
  tw->Branch("t20_2.",&t20_2,"t20_2/F");
  tw->Branch("n20_2.",&n20_2,"n20_2/I");

  tw->Branch("a1_2.",&a1_2,"a1_2/F");
  tw->Branch("t1_2.",&t1_2,"t1_2/F");
  tw->Branch("n1_2.",&n1_2,"n1_2/I");

  tw->Branch("a20_3.",&a20_3,"a20_3/F");
  tw->Branch("a20_3_un.",&a20_3_un,"a20_3_un/F");
  tw->Branch("t20_3.",&t20_3,"t20_3/F");
  tw->Branch("n20_3.",&n20_3,"n20_3/I");

  tw->Branch("a1_3.",&a1_3,"a1_3/F");
  tw->Branch("t1_3.",&t1_3,"t1_3/F");
  tw->Branch("n1_3.",&n1_3,"n1_3/I");

  tw->Branch("a20_4.",&a20_4,"a20_4/F");
  tw->Branch("a20_4_un.",&a20_4_un,"a20_4_un/F");
  tw->Branch("t20_4.",&t20_4,"t20_4/F");
  tw->Branch("n20_4.",&n20_4,"n20_4/I");

  tw->Branch("a1_4.",&a1_4,"a1_4/F");
  tw->Branch("t1_4.",&t1_4,"t1_4/F");
  tw->Branch("n1_4.",&n1_4,"n1_4/I");

  tw->Branch("flag1.",&flag1,"flag1/I");
  tw->Branch("flag2.",&flag2,"flag2/I");
  tw->Branch("flag3.",&flag3,"flag3/I");
  tw->Branch("flag4.",&flag4,"flag4/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");


  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nhe3_1.",&nhe3_1,"nhe3_1/I");
  tw->Branch("nhe3_2.",&nhe3_2,"nhe3_2/I");
  tw->Branch("nhe3_3.",&nhe3_3,"nhe3_3/I");
  tw->Branch("nhe3_4.",&nhe3_4,"nhe3_4/I");

  tw->Branch("v_he3_1.",&v_he3_1,"v_he3_1/F");
  tw->Branch("v_he3_2.",&v_he3_2,"v_he3_2/F");
  tw->Branch("v_he3_3.",&v_he3_3,"v_he3_3/F");
  tw->Branch("v_he3_4.",&v_he3_4,"v_he3_4/F");

  Float_t xCent,yCent;
  xCent = -1;
  yCent = 1;

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<1000000;nentry++) {     
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);

    if (trigger==1) continue;

    checkToF();
    if (!timesToF) continue;

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xCent)*(fXt-xCent) + (fYt-yCent)*(fYt-yCent))>8*8 ) continue;

    fillSi();

    CsItimes();
    DSD_Cselect();

    correct();

    timesSQ20();
    timesSQ1();

    checkHe3(); 
    if (nhe3_1) v_he3_1 = calcVectorTel1(n20_1, n1_1);
    if (nhe3_2) v_he3_2 = calcVectorTel2(n20_2, n1_2);
    if (nhe3_3) v_he3_3 = calcVectorTel3(n20_3, n1_3);
    if (nhe3_4) v_he3_4 = calcVectorTel4(n20_4, n1_4);

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

  a20_2 = 0;
  t20_2 = 0;
  n20_2 = -1;

  a20_3 = 0;
  t20_3 = 0;
  n20_3 = -1;

  a20_4 = 0;
  t20_4 = 0;
  n20_4 = -1;

  flag1 = 1;
  flag2 = 1;
  flag3 = 1;
  flag4 = 1;
  flagCent = 1;

  nh3 = 0;
  nhe3_1 = 0;
  nhe3_2 = 0;
  nhe3_3 = 0;
  nhe3_4 = 0;

  a1_1 = 0;
  n1_1 = -1;
  t1_1 = 0;

  a1_2 = 0;
  n1_2 = -1;
  t1_2 = 0;  

  a1_3 = 0;
  n1_3 = -1;
  t1_3 = 0; 

  a1_4 = 0;
  n1_4 = -1;
  t1_4 = 0;

  v_he3_1 = -100;
  v_he3_2 = -100;
  v_he3_3 = -100;
  v_he3_4 = -100;
} 

void checkToF() {
  // if (F5<4500 || F5>7500 || tF5-tF3<66.5 || tF5-tF3>71 || F3<4300 || F3>7000 ) timesToF = 0;
  // return;
  if ( (ToF_F5->IsInside(tF5-tF3,F5)) && (ToF_F3->IsInside(tF5-tF3,F3)) ) timesToF = 1;
  else timesToF = 0;
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
  TFile *f1 = new TFile("/home/oem/work/software/expertroot/input/exp1904_pars/thickness1.root","READ");
  if (f1->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness1[i][j] = 20.;
        cout << fThickness1[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick1 = (TH2F*)f1->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness1[i][j] = hThick1->GetBinContent(i+1,j+1);
        cout << fThickness1[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f1;

  cout  << endl << "thickness of the SECOND detector " << endl;
  TFile *f2 = new TFile("/home/oem/work/software/expertroot/input/exp1904_pars/thickness2.root","READ");
  if (f2->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness2[i][j] = 20.;
        cout << fThickness2[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick2 = (TH2F*)f2->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness2[i][j] = hThick2->GetBinContent(i+1,j+1);
        cout << fThickness2[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f2;


  cout  << endl << "thickness of the THIRD detector " << endl;
  TFile *f3 = new TFile("/home/oem/work/software/expertroot/input/exp1904_pars/thickness3.root","READ");
  if (f3->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness3[i][j] = 20.;
        cout << fThickness3[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick3 = (TH2F*)f3->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness3[i][j] = hThick3->GetBinContent(i+1,j+1);
        cout << fThickness3[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f3;


  cout  << endl << "thickness of the FOURTH detector " << endl;
  TFile *f4 = new TFile("/home/oem/work/software/expertroot/input/exp1904_pars/thickness4.root","READ");
  if (f4->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness4[i][j] = 20.;
        cout << fThickness4[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick4 = (TH2F*)f4->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness4[i][j] = hThick4->GetBinContent(i+1,j+1);
        cout << fThickness4[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f4;

}

void fillSi() {
 
 if (multc_x==1) {
    for(Int_t i=0;i<32;i++) {
      if (DSD_X[i]>0 && tDSD_X[i]>0){
        X_C = DSD_X[i];
        tX_C = tDSD_X[i];
        nX_C = i;
        break;
      } 
    }
  }

  if (multc_y==1) {
    for(Int_t i=0;i<32;i++) {
      if (DSD_Y[i]>0 && tDSD_Y[i]>0){
        Y_C = DSD_Y[i];
        tY_C = tDSD_Y[i];
        nY_C = i;
        break;
      } 
    }
  }

  // T1
  if (mult20_1==1 && mult1_1==1 && multv_1==0) {
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

  // T2
  if (mult20_2==1 && mult1_2==1 && multv_2==0) {
    for(Int_t i=0;i<16;i++) {
      if (SQ20_2[i]>0 && tSQ20_2[i]>0){
        a20_2 = SQ20_2[i];
        t20_2 = tSQ20_2[i];
        n20_2 = i;
        break;
      } 
    }

    for(Int_t i=0;i<16;i++) {
      if (SSD2[i]>0 && tSSD2[i]>0){
        a1_2 = SSD2[i];
        t1_2 = tSSD2[i];
        n1_2 = i;
        break;
      } 
    }
  }

  // T3
  if (mult20_3==1 && mult1_3==1 && multv_3==0) {
    for(Int_t i=0;i<16;i++) {
      if (SQ20_3[i]>0 && tSQ20_3[i]>0){
        a20_3 = SQ20_3[i];
        t20_3 = tSQ20_3[i];
        n20_3 = i;
        break;
      } 
    }

    for(Int_t i=0;i<16;i++) {
      if (SSD3[i]>0 && tSSD3[i]>0){
        a1_3 = SSD3[i];
        t1_3 = tSSD3[i];
        n1_3 = i;
        break;
      } 
    }
  }
  // T4
  if (mult20_4==1 && mult1_4==1 && multv_4==0) {
    for(Int_t i=0;i<16;i++) {
      if (SQ20_4[i]>0 && tSQ20_4[i]>0){
        a20_4 = SQ20_4[i];
        t20_4 = tSQ20_4[i];
        n20_4 = i;
        break;
      } 
    }

    for(Int_t i=0;i<16;i++) {
      if (SSD4[i]>0 && tSSD4[i]>0){
        a1_4 = SSD4[i];
        t1_4 = tSSD4[i];
        n1_4 = i;
        break;
      } 
    }
  }

}

void correct() {
  if (n20_1>-1 && n1_1>-1) {
    a20_1_un = a20_1;
    a20_1 = a20_1*20./fThickness1[n20_1][n1_1];
    if (fThickness1[n20_1][n1_1]<10 || fThickness1[n20_1][n1_1] > 30) flag1 = 0;
  }
  else flag1 = 0;
  
  if (n20_2>-1 && n1_2>-1){
    a20_2_un = a20_2;
    a20_2 = a20_2*20./fThickness2[n20_2][n1_2];
    if (fThickness2[n20_2][n1_2]<10 || fThickness2[n20_2][n1_2] > 30) flag2 = 0;
  }
  else flag2 = 0;

  if (n20_3>-1 && n1_3>-1) {
    a20_3_un = a20_3;
    a20_3 = a20_3*20./fThickness3[n20_3][n1_3];
    if (fThickness3[n20_3][n1_3]<10 || fThickness3[n20_3][n1_3] > 30) flag3 = 0;
  }
  else flag3 = 0;

  if (n20_4>-1 && n1_4>-1){
    a20_4_un = a20_4;
    a20_4 = a20_4*20./fThickness4[n20_4][n1_4];
    if (fThickness4[n20_4][n1_4]<10 || fThickness3[n20_4][n1_4] > 30) {
      flag4 = 0;
    }
  }
  else flag4 = 0;

  return;
}

void triton() {
  if(nCsI>-1 && nX_C>-1 && cut3h[nCsI]->IsInside(aCsI, X_C)) {
    nh3 = 1;
    return;
  }
  else {
    nh3 = 0;
    return;
  }
}

void checkHe3() {
  if(flag1 && n1_1>-1 && n20_1>-1 && cut1_he3->IsInside(a1_1, a20_1)) {
    nhe3_1 = 1;
  }
  else {
    nhe3_1 = 0;
  }

  if(flag2 && n1_2>-1 && n20_2>-1 && cut2_he3->IsInside(a1_2, a20_2)) {
    nhe3_2 = 1;
  }
  else {
    nhe3_2 = 0;
  }

  if(flag3 && n1_3>-1 && n20_3>-1 && cut3_he3->IsInside(a1_3, a20_3)) {
    nhe3_3 = 1;
  }
  else {
    nhe3_3 = 0;
  }

  if(flag4 && n1_4-1 && n20_4>-1 && cut4_he3->IsInside(a1_4, a20_4)) {
    nhe3_4 = 1;
  }
  else {
    nhe3_4 = 0;
  }

}

void CsItimes() {
  if (tCsI-tF5<300 || tCsI-tF5>500) flagCent = 0;
}  

void DSD_Cselect() {

  if (tX_C-tF5<-200 || tX_C-tF5>-100) flagCent = 0;

}  

void timesSQ20() {

  if (t20_1-tF5<0 || t20_1-tF5>60) flag1 = 0;

  if (t20_2-tF5<0 || t20_2-tF5>60) flag2 = 0;

  if (t20_3-tF5<0 || t20_3-tF5>60) flag3 = 0;

  if (t20_4-tF5<0 || t20_4-tF5>60) flag4 = 0;

}  

void timesSQ1() {

  if (t1_1-tF5<-0 || t1_1-tF5>30) flag1 = 0;

  if (t1_2-tF5<-0 || t1_2-tF5>30) flag2 = 0;

  if (t1_3-tF5<0 || t1_3-tF5>30) flag3 = 0;

  if (t1_4-tF5<-100 || t1_4-tF5>0) flag4 = 0;
}  


void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/C_T/triton/h3_%d.root",i);
    f = new TFile(cutName.Data());
    cut3h[i] = (TCutG*)f->Get("CUTG");
    if (!cut3h[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/C_T/tCsI/tCsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/draw/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T1/tSQ20/tSQ20_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ20_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ20_1[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T1/SQ1_1/tSQ1_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_1[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T2/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T3/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1904/cuts/T4/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_4[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      return;
    }
    delete f;
  }

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_1.root");
  f = new TFile(cutName.Data());
  cut1_he3 = (TCutG*)f->Get("CUTG");
  if (!cut1_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_2.root");
  f = new TFile(cutName.Data());
  cut2_he3 = (TCutG*)f->Get("CUTG");
  if (!cut2_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_3.root");
  f = new TFile(cutName.Data());
  cut3_he3 = (TCutG*)f->Get("CUTG");
  if (!cut3_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/he3_4.root");
  f = new TFile(cutName.Data());
  cut4_he3 = (TCutG*)f->Get("CUTG");
  if (!cut4_he3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/ToF_F3.root");
  f = new TFile(cutName.Data());
  ToF_F3 = (TCutG*)f->Get("CUTG");
  if (!ToF_F3) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

  cutName.Form("/home/oem/work/macro/he8_1904/be10/ToF_F5.root");
  f = new TFile(cutName.Data());
  ToF_F5 = (TCutG*)f->Get("CUTG");
  if (!ToF_F5) {
    cout << "no cut " << cutName.Data() << endl;
    return;
  }
  delete f;

}
Double_t calcVectorTel1(Int_t n20, Int_t n1) {

  Double_t x20;
  x20 = 46.3 + (n20-7.5)*16./50;

  Double_t y1;
  y1 = 20.8 + (7.5-n1)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x20 - fXt,y1*255./270 - fYt,255);

  return tel1V.Theta();
}

Double_t calcVectorTel2(Int_t n20, Int_t n1) {

  Double_t y20;
  y20 = -46.3 + (n20-7.5)*16./50;

  Double_t x1;
  x1 = 20.8 + (7.5-n1)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x1*255./270 - fXt,y20 - fYt,255);

  return tel1V.Theta();
}

Double_t calcVectorTel3(Int_t n20, Int_t n1) {

  Double_t x20;
  x20 = -46.3 - (n20-7.5)*16./50;

  Double_t y1;
  y1 = -20.8 + (n1-7.5)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x20 - fXt,y1*255./270 - fYt,255);

  return tel1V.Theta();
}

Double_t calcVectorTel4(Int_t n20, Int_t n1) {

  Double_t y20;
  y20 = 46.3 + (n20-7.5)*16./50;

  Double_t x1;
  x1 = -20.8 + (n1-7.5)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x1*255./270 - fXt,y20 - fYt,255);

  return tel1V.Theta();
}