#include "/home/ivan/work/macro/be10/cut/be10Cut.C"
void calcVectorTel1(Int_t n20, Int_t n1);
void calcVectorTel2(Int_t n20, Int_t n1);
void calcVectorTel3(Int_t n20, Int_t n1);
void calcVectorTel4(Int_t n20, Int_t n1);
void calcVectorCent(Int_t nX,Int_t nY);

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
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

void litium();
void litium9();
void checkHe3();
void timesSQ20();
void timesSQ1();

// reconstruction
void GetXYLeft();
void GetXYCent();

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
Int_t multCsI;

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

TCutG *cutCsI[16],*cutLi[16],*cutLi9[16],*cutLi8[16],*cutX_C[32];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

Float_t th_he3_1,th_he3_2,th_he3_3,th_he3_4,th_h3;
Float_t phi_he3_1,phi_he3_2,phi_he3_3,phi_he3_4,phi_h3;

Float_t pCsI_1[16],pCsI_2[16];

Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;

Double_t dTel = 173.;

void selection1() {

  be10Cut();
  readPar("CsI_anh",pCsI_1,pCsI_2);
  readCuts();

  TChain *ch = new TChain("tree");
  
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_cal.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/be10_cal_secondVol.root");
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_etarget.root");
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/beamDiagnostics/be10_2_cal.root");

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

  ch->SetBranchAddress("multCsI",&multCsI);

  readThickness();

  // TFile *fw = new TFile("/media/ivan/data/exp1906/be10/analysed/full_data/be10_2_cut.root", "RECREATE");
  // TFile *fw = new TFile("/media/ivan/data/exp1906/be10/analysed/be10_2_li8_cut.root", "RECREATE");
  TFile *fw = new TFile("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_cut_secondVol.root", "RECREATE");
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

  tw->Branch("th_he3_1.",&th_he3_1,"th_he3_1/F");
  tw->Branch("th_he3_2.",&th_he3_2,"th_he3_2/F");
  tw->Branch("th_he3_3.",&th_he3_3,"th_he3_3/F");
  tw->Branch("th_he3_4.",&th_he3_4,"th_he3_4/F");
  tw->Branch("th_h3.",&th_h3,"th_h3/F");

  tw->Branch("phi_he3_1.",&phi_he3_1,"phi_he3_1/F");
  tw->Branch("phi_he3_2.",&phi_he3_2,"phi_he3_2/F");
  tw->Branch("phi_he3_3.",&phi_he3_3,"phi_he3_3/F");
  tw->Branch("phi_he3_4.",&phi_he3_4,"phi_he3_4/F");
  tw->Branch("phi_h3.",&phi_h3,"phi_h3/F");

  tw->Branch("x1t",&x1t,"x1t/F");
  tw->Branch("x2t",&x2t,"x2t/F");
  tw->Branch("x3t",&x3t,"x3t/F");
  tw->Branch("x4t",&x4t,"x4t/F");
  tw->Branch("y1t",&y1t,"y1t/F");
  tw->Branch("y2t",&y2t,"y2t/F");
  tw->Branch("y3t",&y3t,"y3t/F");
  tw->Branch("y4t",&y4t,"y4t/F");
  tw->Branch("xCt",&xCt,"xCt/F");
  tw->Branch("yCt",&yCt,"yCt/F");

  tw->Branch("multv_1",&multv_1,"multv_1/I");
  tw->Branch("multv_2",&multv_2,"multv_2/I");
  tw->Branch("multv_3",&multv_3,"multv_3/I");
  tw->Branch("multv_4",&multv_4,"multv_4/I");
  tw->Branch("multCsI",&multCsI,"multCsI/I");

  Float_t xCent,yCent;
  xCent = 0.5;
  yCent = 1;

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<1000;nentry++) {     
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);

    // if (trigger==1) continue;

    checkToF();
    if (!timesToF) continue;

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xCent)*(fXt-xCent) + (fYt-yCent)*(fYt-yCent))>9*9 ) continue;

    fillSi();

    if (nCsI>-1) {
      // cout << nCsI << endl;
      CsItimes();
    }
    DSD_Cselect();
    // 
    if (flagCent && nCsI>-1) {
      litium9();      
    }

    correct();

    timesSQ20();
    timesSQ1();

    checkHe3(); 
    if (nhe3_1) calcVectorTel1(n20_1, n1_1);
    if (nhe3_2) calcVectorTel2(n20_2, n1_2);
    if (nhe3_3) calcVectorTel3(n20_3, n1_3);
    if (nhe3_4) calcVectorTel4(n20_4, n1_4);

    if (nh3) calcVectorCent(nX_C,nY_C);

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
  a20_1_un = 0;

  a20_2 = 0;
  t20_2 = 0;
  n20_2 = -1;
  a20_2_un = 0;

  a20_3 = 0;
  t20_3 = 0;
  n20_3 = -1;
  a20_3_un = 0;

  a20_4 = 0;
  t20_4 = 0;
  n20_4 = -1;
  a20_4_un = 0;

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

  th_he3_1 = -100;
  th_he3_2 = -100;
  th_he3_3 = -100;
  th_he3_4 = -100;
  th_h3 = -100;

  phi_he3_1 = -100;
  phi_he3_2 = -100;
  phi_he3_3 = -100;
  phi_he3_4 = -100;
  phi_h3 = -100;

  x1t = 0;
  y1t = 0; 
  x2t = 0;
  y2t = 0;
  x3t = 0;
  y3t = 0;
  x4t = 0;
  y4t = 0;
  xCt = 0;
  yCt = 0;
} 

void checkToF() {
  if ( cutF5->IsInside(tF5-tF3, 0.25*F5) && cutF3->IsInside(tF5-tF3, 0.25*F3)) timesToF = kTRUE;
  else timesToF = kFALSE;
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
  TFile *f1 = new TFile("/home/ivan/work/soft/er/input/exp1904_pars/thickness1.root","READ");
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
  TFile *f2 = new TFile("/home/ivan/work/soft/er/input/exp1904_pars/thickness2.root","READ");
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
  TFile *f3 = new TFile("/home/ivan/work/soft/er/input/exp1904_pars/thickness3.root","READ");
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
  TFile *f4 = new TFile("/home/ivan/work/soft/er/input/exp1904_pars/thickness4.root","READ");
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
 
Int_t graphMult = 0;

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
  // if (multc_x>1 && nCsI>-1) {
  //   for(Int_t i=0;i<32;i++) {
  //     if (cutLi[nCsI]->IsInside(aCsI, DSD_X[i])) {
  //       X_C = DSD_X[i];
  //       tX_C = tDSD_X[i];
  //       nX_C = i;
  //       graphMult++;
  //     } 
  //   }
  //   if (graphMult!=1) {
  //       X_C = 0;
  //       tX_C = 0;
  //       nX_C = -1;
  //   }
  // }

  graphMult = 0;
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
  // if (multc_y>1 && nCsI>-1) {
  //   for(Int_t i=0;i<32;i++) {
  //     if (cutLi[nCsI]->IsInside(aCsI, DSD_X[i])) {
  //       graphMult++;
  //       Y_C = DSD_Y[i];
  //       tY_C = tDSD_Y[i];
  //       nY_C = i;
  //     }
  //   }
  //   if (graphMult!=1) {
  //       Y_C = 0;
  //       tY_C = 0;
  //       nY_C = -1;
  //   }
  // }

  graphMult = 0;
  // T1
  if (mult20_1==1 && mult1_1==1) {
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
  // else {
  //   for(Int_t i=0;i<16;i++) { // SQ20 loop
  //     for(Int_t j=0;j<16;j++) {
  //       if (cuthe3_1[i]->IsInside(SSD1[j], SQ20_1[i]) && SSD1[j]<25.) {
  //         a20_1 = SQ20_1[i];
  //         t20_1 = tSQ20_1[i];
  //         n20_1 = i;

  //         a1_1 = SSD1[i];
  //         t1_1 = tSSD1[i];
  //         n1_1 = i;

  //         graphMult++;
  //       } 
  //     }
  //   }
  //   if (graphMult!=1) {
  //     a20_1 = 0;
  //     t20_1 = 0;
  //     n20_1 = -1;

  //     a1_1 = 0;
  //     t1_1 = 0;
  //     n1_1 = -1;      
  //   }
  // }

  // T2
  graphMult = 0;
  if (mult20_2==1 && mult1_2==1) {
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
  // else {
  //   for(Int_t i=0;i<16;i++) { // SQ20 loop
  //     for(Int_t j=0;j<16;j++) {
  //       if (cuthe3_2[i]->IsInside(SSD2[j], SQ20_2[i]) && SSD2[j]<25.) {
  //         a20_2 = SQ20_2[i];
  //         t20_2 = tSQ20_2[i];
  //         n20_2 = i;
  //         a1_2 = SSD2[i];
  //         t1_2 = tSSD2[i];
  //         n1_2 = i;

  //         graphMult++;
  //       } 
  //     }
  //   }
  //   if (graphMult!=1) {
  //     a20_2 = 0;
  //     t20_2 = 0;
  //     n20_2 = -1;
  //     a1_2 = 0;
  //     t1_2 = 0;
  //     n1_2 = -1;
  //   }
  // }


  // T3
  graphMult = 0;
  if (mult20_3==1 && mult1_3==1) {
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
  // else {
  //   for(Int_t i=0;i<16;i++) { // SQ20 loop
  //     for(Int_t j=0;j<16;j++) {
  //       if (cuthe3_3[i]->IsInside(SSD3[j], SQ20_3[i]) && SSD3[j]<25.) {
  //         a20_3 = SQ20_3[i];
  //         t20_3 = tSQ20_3[i];
  //         n20_3 = i;
  //         a1_3 = SSD3[i];
  //         t1_3 = tSSD3[i];
  //         n1_3 = i;          
  //         graphMult++;
  //       } 
  //     }
  //   }
  //   if (graphMult!=1) {
  //     a20_3 = 0;
  //     t20_3 = 0;
  //     n20_3 = -1;
  //     a1_3 = 0;
  //     t1_3 = 0;
  //     n1_3 = -1; 

  //   }
  // }

  // T4
  graphMult = 0;
  if (mult20_4==1 && mult1_4==1) {
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
  // else {
  //   for(Int_t i=0;i<16;i++) { // SQ20 loop
  //     for(Int_t j=0;j<16;j++) {
  //       if (cuthe3_4[i]->IsInside(SSD4[j], SQ20_4[i]) && SSD4[j]<25.) {
  //         a20_4 = SQ20_4[i];
  //         t20_4 = tSQ20_4[i];
  //         n20_4 = i;

  //         a1_4 = SSD4[i];
  //         t1_4 = tSSD4[i];
  //         n1_4 = i;          
  //         graphMult++;
  //       } 
  //     }
  //   }
  //   if (graphMult!=1) {
  //     a20_4 = 0;
  //     t20_4 = 0;
  //     n20_4 = -1;

  //     a1_4 = 0;
  //     t1_4 = 0;
  //     n1_4 = -1;       
  //   }
  // }

}

void correct() {
  if (n20_1>-1 && n1_1>-1) {
    a20_1_un = a20_1;
    a20_1 = a20_1*20./fThickness1[n20_1][n1_1];
    if (fThickness1[n20_1][n1_1]<10 || fThickness1[n20_1][n1_1] > 30) {
      // cout << " flag 1" << endl;
      // cout << fThickness1[n20_1][n1_1] << " " << n20_1 << " " << n1_1 << endl;
      flag1 = 0;
    }
  }
  else flag1 = 0;
  
  a20_2_un = a20_2;
  a20_2 = a20_2*20./fThickness2[n20_2][n1_2];
  if (fThickness2[n20_2][n1_2]<10 || fThickness2[n20_2][n1_2] > 30) {
    flag2 = 0;
  }

  a20_3_un = a20_3;
  a20_3 = a20_3*20./fThickness3[n20_3][n1_3];
  if (fThickness3[n20_3][n1_3]<10 || fThickness3[n20_3][n1_3] > 30) {
    flag3 = 0;
  }

  a20_4_un = a20_4;
  a20_4 = a20_4*20./fThickness4[n20_4][n1_4];
  if (fThickness4[n20_4][n1_4]<10 || fThickness3[n20_4][n1_4] > 30) {
    flag4 = 0;
  }

  return;
}

void litium9() {
  if(nCsI>-1 && nX_C>-1 && cutLi9[nCsI]->IsInside(aCsI, X_C)) {
    nh3 = 1;
    return;
  }
  else {
    nh3 = 0;
    return;
  }
}

void checkHe3() {
  if(flag1 && n1_1>-1 && n20_1>-1 && a1_1<20 && cuthe3_1[n20_1]->IsInside(a1_1, a20_1)) {
    nhe3_1 = 1;
  }
  else {
    nhe3_1 = 0;
  }

  if(flag2 && n1_2>-1 && n20_2>-1 && a1_2<20 && cuthe3_2[n20_2]->IsInside(a1_2, a20_2)) {
    nhe3_2 = 1;
  }
  else {
    nhe3_2 = 0;
  }

  if(flag3 && n1_3>-1 && n20_3>-1 && a1_3<20 && cuthe3_3[n20_3]->IsInside(a1_3, a20_3)) {
    nhe3_3 = 1;
  }
  else {
    nhe3_3 = 0;
  }

  if(flag4 && n1_4>-1 && n20_4>-1 && a1_4<20 && cuthe3_4[n20_4]->IsInside(a1_4, a20_4)) {
    nhe3_4 = 1;
  }
  else {
    nhe3_4 = 0;
  }

}

void CsItimes() {
  if(nCsI>-1 && cutCsI[nCsI]->IsInside(tCsI-tF5,aCsI) ) { 
    return;
  }
  else {
    flagCent = 0;
    // cout << " CsI times" << endl;  
    return; 
  }
} 

void DSD_Cselect() {
  // cout << nCsI << endl;
  if(nX_C>-1 && cutX_C[nX_C]->IsInside(tX_C-tF5,X_C) ) { 
    return;
  }
  else {
    flagCent = 0;
    // cout << " CsI times" << endl;  
    return; 
  }
} 

void timesSQ20() {
  // if(n20_1>-1 && cutSQ20_1[n20_1]->IsInside(t20_1-tF5, a20_1)==kFALSE) {  
  //   flag1 = 0;  
  // }

  if (t20_1-tF5<-10 || t20_1-tF5>60) flag1 = 0;

  if (t20_2-tF5<-10 || t20_2-tF5>60) flag2 = 0;

  if (t20_3-tF5<-10 || t20_3-tF5>60) flag3 = 0;

  if (t20_4-tF5<-10 || t20_4-tF5>60) flag4 = 0;

}  

void timesSQ1() {
  // if(n1_1>-1 && !cutSQ1_1[n1_1]->IsInside(t1_1-tF5, a1_1)) {  
  //   flag1 = 0;  
  // }
  if (t1_1-tF5 < 0 && t1_1-tF5>50) flag1=0;

  if (t1_2-tF5 < 0 && t1_2-tF5>50) flag2=0;

  if (t1_3-tF5 < 0 && t1_3-tF5>50) flag3=0;

  if(n1_4>-1 && cutSQ1_4[n1_4]->IsInside(t1_4-tF5,a1_4) ) { 
    flag4 = flag4*1;
  }
  else flag4 = 0;
}  


void readCuts() {

  TFile *f;
  TString cutName;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/litium/li_%d.root",i);
    f = new TFile(cutName.Data());
    cutLi[i] = (TCutG*)f->Get("CUTG");
    if (!cutLi[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/litium/secondPars/li8/Li8_%d.root",i);
    f = new TFile(cutName.Data());
    cutLi8[i] = (TCutG*)f->Get("CUTG");
    if (!cutLi8[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/litium/secondPars/Li9_%d.root",i);
    f = new TFile(cutName.Data());
    cutLi9[i] = (TCutG*)f->Get("CUTG");
    if (!cutLi9[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }    
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/tCsI/tCsI_%d.root",i);
    f = new TFile(cutName.Data());
    cutCsI[i] = (TCutG*)f->Get("CUTG");
    if (!cutCsI[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<32;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/CT/tX_C/tX_C_%d.root",i);
    f = new TFile(cutName.Data());
    cutX_C[i] = (TCutG*)f->Get("CUTG");
    if (!cutX_C[i]) {
      cout << i  << " no cut"<< endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T1/tSQ20/tSQ20_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ20_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ20_1[i]) {
      cout << i  << " no cut"<< endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T1/SQ1_1/tSQ1_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_1[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_1[i]) {
      cout << i  << " no cut"<< endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T1/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_1[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_1[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T2/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_2[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_2[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T3/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_3[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_3[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T4/he3/he3_%d.root",i);
    f = new TFile(cutName.Data());
    cuthe3_4[i] = (TCutG*)f->Get("CUTG");
    if (!cuthe3_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/ivan/work/macro/be10/cut/T4/tSSD4/tSSD4_%d.root",i);
    f = new TFile(cutName.Data());
    cutSQ1_4[i] = (TCutG*)f->Get("CUTG");
    if (!cutSQ1_4[i]) {
      cout << "no cut " << cutName.Data() << endl;
      exit(1);
    }
    delete f;
  }

}

void calcVectorTel1(Int_t n20, Int_t n1) {

  Double_t x20;
  x20 = -(22.8625 + n20*50./16);

  Double_t y1;
  y1 = 48.925 - n1*60./16;

  TVector3 tel1V;
  tel1V.SetXYZ(x20 - fXt,y1*173./188 - fYt,173.);

  x1t = x20;
  y1t = y1*173./188;

  th_he3_1 = tel1V.Theta();
  phi_he3_1 = tel1V.Phi();

  return;
}

void calcVectorTel2(Int_t n20, Int_t n1) {

  Double_t y20;
  y20 = -(22.8625 + n20*50./16);

  Double_t x1;
  x1 = -(48.925 - n1*60./16);

  TVector3 tel1V;
  tel1V.SetXYZ(x1*173./188 - fXt,y20 - fYt,173);

  x2t = x1*173./188;
  y2t = y20;

  th_he3_2 = tel1V.Theta();
  phi_he3_2 = tel1V.Phi();

  return;
}

void calcVectorTel3(Int_t n20, Int_t n1) {

  Double_t x20;
  x20 = 22.8625 + n20*50./16;

  Double_t y1;
  y1 = -(48.925 - n1*60./16);

  TVector3 tel1V;
  tel1V.SetXYZ(x20 - fXt,y1*173./188 - fYt,173);

  x3t = x20;
  y3t = y1*173./188;

  th_he3_3 = tel1V.Theta();
  phi_he3_3 = tel1V.Phi();

  return;
}

void calcVectorTel4(Int_t n20, Int_t n1) {

  Double_t y20;
  y20 = 22.8625 + n20*50./16;

  Double_t x1;
  x1 = 48.925 - n1*60./16;

  TVector3 tel1V;
  tel1V.SetXYZ(x1*173./188 - fXt,y20 - fYt,173);

  x4t = x1*173./188;
  y4t = y20;

  th_he3_4 = tel1V.Theta();
  phi_he3_4 = tel1V.Phi();

  return tel1V.Theta();
}

void calcVectorCent(Int_t nX,Int_t nY) {

  Double_t xC = 31. - nX*64./32;
  Double_t yC = 31. - nY*64./32;
  Double_t zC = 323.;

  TVector3 tel1V;
  tel1V.SetXYZ(xC - fXt,yC - fYt,zC);

  xCt = xC;
  yCt = yC;

  th_h3 = tel1V.Theta();
  phi_h3 = tel1V.Phi();

  return;
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/ivan/work/soft/er/input/exp1904_pars/" + fileName + ".cal";
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