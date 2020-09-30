void readThickness();
void setTables();
void zeroVars();

void reconstruct6He();
void reconstructAlha();
void reconstruct3He();
void reconstruct3H();
void reconstruct2H();
void reconstruct4He();
void calculateCoordinates();
void tritonProjection(Float_t *x,Float_t *y,Double_t distance);
void reconstruct_side_3H();

TELoss *f3HeSi;
TELoss *f3HeMylar;
TELoss *f3HeSteel;
TELoss *f3HeTarget;

TELoss *f6HeSi;
TELoss *f6HeMylar;
TELoss *f6HeSteel;
TELoss *f6HeTarget;
TELoss *f6HePlastic;
TELoss *f6HeKeramic;

TELoss *f4HeSi;
TELoss *f4HeMylar;
TELoss *f4HeSteel;
TELoss *f4HeTarget;
TELoss *f4HePlastic;
TELoss *f4HeKeramic;

TELoss *f3HSi;
TELoss *f3HMylar;
TELoss *f3HSteel;
TELoss *f3HTarget;
TELoss *f3HPlastic;
TELoss *f3HKeramic;

TELoss *f2HSi;
TELoss *f2HMylar;
TELoss *f2HSteel;
TELoss *f2HTarget;
TELoss *f2HPlastic;
TELoss *f2HKeramic;

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC;
Int_t wirex1,wirex2,wirey1,wirey2;

Int_t nCsI,nCsI_track;
Float_t aCsI,tCsI;
Float_t aCsI_reco;

Float_t arCsI[16],trCsI[16];

Float_t a20_1,t20_1,a20_1_un;
Int_t n20_1;

Float_t a1_1,t1_1;
Int_t n1_1;

Float_t av_1,tv_1;
Int_t nv_1;

Float_t a20_2,t20_2,a20_2_un;
Int_t n20_2;

Float_t a1_2,t1_2;
Int_t n1_2;

Float_t av_2,tv_2;
Int_t nv_2;

Float_t a20_3,t20_3,a20_3_un;
Int_t n20_3;

Float_t a1_3,t1_3;
Int_t n1_3;

Float_t av_3,tv_3;
Int_t nv_3;

Float_t a20_4,t20_4,a20_4_un;
Int_t n20_4;

Float_t a1_4,t1_4;
Int_t n1_4;

Float_t av_4,tv_4;
Int_t nv_4;

Float_t X_C,tX_C,Y_C,tY_C;
Int_t nX_C,nY_C;
//

Float_t fXt,fYt;
Float_t fXf,fYf;
Float_t x1c, y1c, x2c, y2c;
Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;
Float_t frame1X,frame1Y,frame2X,frame2Y,frame3X,frame3Y;

Float_t tritonX1,tritonY1;
Float_t tritonX2,tritonY2;
Float_t tritonX3,tritonY3;
Float_t tritonX4,tritonY4;

// flags
Bool_t timesToF,timesMWPC;

Double_t fThickness1[16][16],fThickness2[16][16],fThickness3[16][16],fThickness4[16][16];

Int_t flag1,flag2,flag3,flag4,flagCent;
Int_t nh3,nh2,nh1,nhe3_1,nhe3_2,nhe3_3,nhe3_4,neutron;
Int_t frame;
Int_t nhe4_1,nhe4_2,nhe4_3,nhe4_4;
Int_t nh3_1,nh3_2,nh3_3,nh3_4;
Int_t nAlpha,nhe6;

Float_t e_1,e_2,e_3,e_4;
Float_t centE;

Float_t th_he3_1,th_he3_2,th_he3_3,th_he3_4,th_h3;
Float_t phi_he3_1,phi_he3_2,phi_he3_3,phi_he3_4,phi_h3;

Float_t thickness;

Float_t xOffset,yOffset,zOffset;
Float_t tND,aND,tacND,numND;
Float_t ND_time[32],ND_amp[32],ND_tac[32];

Float_t SSD1[16],SQ20_1[16],tSSD1[16],tSQ20_1[16],SSD_V1[16],tSSD_V1[16];
Float_t SSD2[16],SQ20_2[16],tSSD2[16],tSQ20_2[16],SSD_V2[16],tSSD_V2[16];
Float_t SSD3[16],SQ20_3[16],tSSD3[16],tSQ20_3[16],SSD_V3[16],tSSD_V3[16];
Float_t SSD4[16],SQ20_4[16],tSSD4[16],tSQ20_4[16],SSD_V4[16],tSSD_V4[16];
//--------------------------------------------------------------------------------

Float_t thCoeff1 = 1.;
Float_t thCoeff2 = 1.;
Float_t thCoeff3 = 1.;
Float_t thCoeff4 = 1.;

void calcEnergies_ect(Int_t nRun=0) {

  xOffset = 0;
  yOffset = -2.4;
  zOffset = 0.;


  // xOffset = 0.5;
  // yOffset = -1.3;
  // zOffset = 3.;


  TChain *ch = new TChain("tree");

  TString inPutFileName;
  inPutFileName.Form("/mnt/data/exp1904/analysed/selected/emptyTarget/h7_ct_%d_cut.root",nRun);
  // inPutFileName.Form("/mnt/data/exp1904/analysed/selected/emptyTarget/h7_ct_%d_cut.root",nRun);
  ch->Add(inPutFileName.Data());
  cout << ch->GetEntries() << " total number of Entries" << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger.",&trigger);

  ch->SetBranchAddress("aCsI.",&aCsI);
  ch->SetBranchAddress("tCsI.",&tCsI);
  ch->SetBranchAddress("nCsI.",&nCsI);

  ch->SetBranchAddress("nCsI_track.",&nCsI_track);
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

  ch->SetBranchAddress("X_C.",&X_C);
  ch->SetBranchAddress("nX_C.",&nX_C);
  ch->SetBranchAddress("tX_C.",&tX_C);
  ch->SetBranchAddress("Y_C.",&Y_C);
  ch->SetBranchAddress("tY_C.",&tY_C);
  ch->SetBranchAddress("nY_C.",&nY_C);

  ch->SetBranchAddress("fXf.",&fXf);
  ch->SetBranchAddress("fYf.",&fYf);
  ch->SetBranchAddress("fXt.",&fXt);
  ch->SetBranchAddress("fYt.",&fYt); 
  ch->SetBranchAddress("x1c.",&x1c);
  ch->SetBranchAddress("y1c.",&y1c);
  ch->SetBranchAddress("x2c.",&x2c);
  ch->SetBranchAddress("y2c.",&y2c); 

  ch->SetBranchAddress("frame1X",&frame1X);
  ch->SetBranchAddress("frame2X",&frame2X);
  ch->SetBranchAddress("frame3X",&frame3X);
  ch->SetBranchAddress("frame1Y",&frame1Y);
  ch->SetBranchAddress("frame2Y",&frame2Y);
  ch->SetBranchAddress("frame3Y",&frame3Y);

  ch->SetBranchAddress("x1t",&x1t);
  ch->SetBranchAddress("x2t",&x2t);
  ch->SetBranchAddress("x3t",&x3t);
  ch->SetBranchAddress("x4t",&x4t);
  ch->SetBranchAddress("y1t",&y1t);
  ch->SetBranchAddress("y2t",&y2t);
  ch->SetBranchAddress("y3t",&y3t);
  ch->SetBranchAddress("y4t",&y4t);
  ch->SetBranchAddress("xCt",&xCt);
  ch->SetBranchAddress("yCt",&yCt);

  ch->SetBranchAddress("a20_1.",&a20_1);
  ch->SetBranchAddress("a20_1_un.",&a20_1_un);
  ch->SetBranchAddress("t20_1.",&t20_1);
  ch->SetBranchAddress("n20_1.",&n20_1);

  ch->SetBranchAddress("a1_1.",&a1_1);
  ch->SetBranchAddress("t1_1.",&t1_1);
  ch->SetBranchAddress("n1_1.",&n1_1);

  ch->SetBranchAddress("av_1.",&av_1);
  ch->SetBranchAddress("tv_1.",&tv_1);
  ch->SetBranchAddress("nv_1.",&nv_1);

  ch->SetBranchAddress("a20_2.",&a20_2);
  ch->SetBranchAddress("a20_2_un.",&a20_2_un);
  ch->SetBranchAddress("t20_2.",&t20_2);
  ch->SetBranchAddress("n20_2.",&n20_2);

  ch->SetBranchAddress("a1_2.",&a1_2);
  ch->SetBranchAddress("t1_2.",&t1_2);
  ch->SetBranchAddress("n1_2.",&n1_2);

  ch->SetBranchAddress("av_2.",&av_2);
  ch->SetBranchAddress("tv_2.",&tv_2);
  ch->SetBranchAddress("nv_2.",&nv_2);

  ch->SetBranchAddress("a20_3.",&a20_3);
  ch->SetBranchAddress("a20_3_un.",&a20_3_un);
  ch->SetBranchAddress("t20_3.",&t20_3);
  ch->SetBranchAddress("n20_3.",&n20_3);

  ch->SetBranchAddress("a1_3.",&a1_3);
  ch->SetBranchAddress("t1_3.",&t1_3);
  ch->SetBranchAddress("n1_3.",&n1_3);

  ch->SetBranchAddress("av_3.",&av_3);
  ch->SetBranchAddress("tv_3.",&tv_3);
  ch->SetBranchAddress("nv_3.",&nv_3);

  ch->SetBranchAddress("a20_4.",&a20_4);
  ch->SetBranchAddress("a20_4_un.",&a20_4_un);
  ch->SetBranchAddress("t20_4.",&t20_4);
  ch->SetBranchAddress("n20_4.",&n20_4);

  ch->SetBranchAddress("a1_4.",&a1_4);
  ch->SetBranchAddress("t1_4.",&t1_4);
  ch->SetBranchAddress("n1_4.",&n1_4);

  ch->SetBranchAddress("av_4.",&av_4);
  ch->SetBranchAddress("tv_4.",&tv_4);
  ch->SetBranchAddress("nv_4.",&nv_4);

  ch->SetBranchAddress("flag1.",&flag1);
  ch->SetBranchAddress("flag2.",&flag2);
  ch->SetBranchAddress("flag3.",&flag3);
  ch->SetBranchAddress("flag4.",&flag4);
  ch->SetBranchAddress("flagCent.",&flagCent);

  ch->SetBranchAddress("nh3.",&nh3);
  ch->SetBranchAddress("nh2.",&nh2);
  ch->SetBranchAddress("nh1.",&nh1);
  ch->SetBranchAddress("nhe3_1.",&nhe3_1);
  ch->SetBranchAddress("nhe3_2.",&nhe3_2);
  ch->SetBranchAddress("nhe3_3.",&nhe3_3);
  ch->SetBranchAddress("nhe3_4.",&nhe3_4);

  ch->SetBranchAddress("nh3_1.",&nh3_1);
  ch->SetBranchAddress("nh3_2.",&nh3_2);
  ch->SetBranchAddress("nh3_3.",&nh3_3);
  ch->SetBranchAddress("nh3_4.",&nh3_4);

  ch->SetBranchAddress("nhe4_1.",&nhe4_1);
  ch->SetBranchAddress("nhe4_2.",&nhe4_2);
  ch->SetBranchAddress("nhe4_3.",&nhe4_3);
  ch->SetBranchAddress("nhe4_4.",&nhe4_4);

  ch->SetBranchAddress("nAlpha.",&nAlpha);
  ch->SetBranchAddress("nhe6.",&nhe6);  

  ch->SetBranchAddress("th_he3_1.",&th_he3_1);
  ch->SetBranchAddress("th_he3_2.",&th_he3_2);
  ch->SetBranchAddress("th_he3_3.",&th_he3_3);
  ch->SetBranchAddress("th_he3_4.",&th_he3_4);
  ch->SetBranchAddress("th_h3.",&th_h3);

  ch->SetBranchAddress("phi_he3_1.",&phi_he3_1);
  ch->SetBranchAddress("phi_he3_2.",&phi_he3_2);
  ch->SetBranchAddress("phi_he3_3.",&phi_he3_3);
  ch->SetBranchAddress("phi_he3_4.",&phi_he3_4);
  ch->SetBranchAddress("phi_h3.",&phi_h3);

  ch->SetBranchAddress("neutron.",&neutron);

  // ch->SetBranchAddress("aND",&aND);
  // ch->SetBranchAddress("tND",&tND);
  // ch->SetBranchAddress("tacND",&tacND);
  // ch->SetBranchAddress("numND",&numND);

  ch->SetBranchAddress("ND_amp",&ND_amp);
  ch->SetBranchAddress("ND_time",&ND_time);
  ch->SetBranchAddress("ND_tac",&ND_tac);

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

  TString outPutFileName;
  outPutFileName.Form("/mnt/data/exp1904/analysed/calcEnergies/emptyTarget/h7_ct_%d_reco.root",nRun);
  // outPutFileName.Form("/mnt/data/exp1904/analysed/calcEnergies/emptyTarget/h7_ct_%d_reco.root",nRun);

  TFile *fw = new TFile(outPutFileName.Data(), "RECREATE");
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

  tw->Branch("nCsI_track.",&nCsI_track,"nCsI_track/I");
  tw->Branch("arCsI",&arCsI,"arCsI[16]/F");
  tw->Branch("trCsI",&trCsI,"trCsI[16]/F");

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
  tw->Branch("fXf.",&fXf,"fXf/F");
  tw->Branch("fYf.",&fYf,"fYf/F");


  tw->Branch("frame1X",&frame1X,"frame1X/F");
  tw->Branch("frame2X",&frame2X,"frame2X/F");
  tw->Branch("frame3X",&frame3X,"frame3X/F");
  tw->Branch("frame1Y",&frame1Y,"frame1Y/F");
  tw->Branch("frame2Y",&frame2Y,"frame2Y/F");
  tw->Branch("frame3Y",&frame3Y,"frame3Y/F");

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

  tw->Branch("a20_1.",&a20_1,"a20_1/F");
  tw->Branch("a20_1_un.",&a20_1_un,"a20_1_un/F");
  tw->Branch("t20_1.",&t20_1,"t20_1/F");
  tw->Branch("n20_1.",&n20_1,"n20_1/I");

  tw->Branch("a1_1.",&a1_1,"a1_1/F");
  tw->Branch("t1_1.",&t1_1,"t1_1/F");
  tw->Branch("n1_1.",&n1_1,"n1_1/I");

  tw->Branch("av_1.",&av_1,"av_1/F");
  tw->Branch("tv_1.",&tv_1,"tv_1/F");
  tw->Branch("nv_1.",&nv_1,"nv_1/I");

  tw->Branch("a20_2.",&a20_2,"a20_2/F");
  tw->Branch("a20_2_un.",&a20_2_un,"a20_2_un/F");
  tw->Branch("t20_2.",&t20_2,"t20_2/F");
  tw->Branch("n20_2.",&n20_2,"n20_2/I");

  tw->Branch("a1_2.",&a1_2,"a1_2/F");
  tw->Branch("t1_2.",&t1_2,"t1_2/F");
  tw->Branch("n1_2.",&n1_2,"n1_2/I");

  tw->Branch("av_2.",&av_2,"av_2/F");
  tw->Branch("tv_2.",&tv_2,"tv_2/F");
  tw->Branch("nv_2.",&nv_2,"nv_2/I");

  tw->Branch("a20_3.",&a20_3,"a20_3/F");
  tw->Branch("a20_3_un.",&a20_3_un,"a20_3_un/F");
  tw->Branch("t20_3.",&t20_3,"t20_3/F");
  tw->Branch("n20_3.",&n20_3,"n20_3/I");

  tw->Branch("a1_3.",&a1_3,"a1_3/F");
  tw->Branch("t1_3.",&t1_3,"t1_3/F");
  tw->Branch("n1_3.",&n1_3,"n1_3/I");

  tw->Branch("av_3.",&av_3,"av_3/F");
  tw->Branch("tv_3.",&tv_3,"tv_3/F");
  tw->Branch("nv_3.",&nv_3,"nv_3/I");

  tw->Branch("a20_4.",&a20_4,"a20_4/F");
  tw->Branch("a20_4_un.",&a20_4_un,"a20_4_un/F");
  tw->Branch("t20_4.",&t20_4,"t20_4/F");
  tw->Branch("n20_4.",&n20_4,"n20_4/I");

  tw->Branch("a1_4.",&a1_4,"a1_4/F");
  tw->Branch("t1_4.",&t1_4,"t1_4/F");
  tw->Branch("n1_4.",&n1_4,"n1_4/I");

  tw->Branch("av_4.",&av_4,"av_4/F");
  tw->Branch("tv_4.",&tv_4,"tv_4/F");
  tw->Branch("nv_4.",&nv_4,"nv_4/I");

  tw->Branch("flag1.",&flag1,"flag1/I");
  tw->Branch("flag2.",&flag2,"flag2/I");
  tw->Branch("flag3.",&flag3,"flag3/I");
  tw->Branch("flag4.",&flag4,"flag4/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  tw->Branch("neutron.",&neutron,"neutron/I");

  // tw->Branch("aND",&aND,"aND/F");
  // tw->Branch("tND",&tND,"tND/F");
  // tw->Branch("tacND",&tacND,"tacND/F");
  // tw->Branch("numND",&numND,"numND/F");

  tw->Branch("ND_amp",&ND_amp,"ND_amp[32]/F");
  tw->Branch("ND_time",&ND_time,"ND_time[32]/F");
  tw->Branch("ND_tac",&ND_tac,"ND_tac[32]/F");

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nh2.",&nh2,"nh2/I");
  tw->Branch("nh1.",&nh1,"nh1/I");
  tw->Branch("nhe3_1.",&nhe3_1,"nhe3_1/I");
  tw->Branch("nhe3_2.",&nhe3_2,"nhe3_2/I");
  tw->Branch("nhe3_3.",&nhe3_3,"nhe3_3/I");
  tw->Branch("nhe3_4.",&nhe3_4,"nhe3_4/I");

  tw->Branch("nh3_1.",&nh3_1,"nh3_1/I");
  tw->Branch("nh3_2.",&nh3_2,"nh3_2/I");
  tw->Branch("nh3_3.",&nh3_3,"nh3_3/I");
  tw->Branch("nh3_4.",&nh3_4,"nh3_4/I");

  tw->Branch("nhe4_1.",&nhe4_1,"nhe4_1/I");
  tw->Branch("nhe4_2.",&nhe4_2,"nhe4_2/I");
  tw->Branch("nhe4_3.",&nhe4_3,"nhe4_3/I");
  tw->Branch("nhe4_4.",&nhe4_4,"nhe4_4/I"); 

  tw->Branch("nAlpha.",&nAlpha,"nAlpha/I");
  tw->Branch("nhe6.",&nhe6,"nhe6/I");

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

  tw->Branch("e_1.",&e_1,"e_1/F");
  tw->Branch("e_2.",&e_2,"e_2/F");
  tw->Branch("e_3.",&e_3,"e_3/F");
  tw->Branch("e_4.",&e_4,"e_4/F");

  tw->Branch("centE.",&centE,"centE/F");

  tw->Branch("SQ20_1",&SQ20_1,"SQ20_1[16]/F");
  tw->Branch("tSQ20_1",&tSQ20_1,"tSQ20_1[16]/F");
  tw->Branch("SSD1",&SSD1,"SSD1[16]/F");
  tw->Branch("tSSD1",&tSSD1,"tSSD1[16]/F");
  tw->Branch("SSD_V1",&SSD_V1,"SSD_V1[16]/F");
  tw->Branch("tSSD_V1",&tSSD_V1,"tSSD_V1[16]/F");

  tw->Branch("SQ20_2",&SQ20_2,"SQ20_2[16]/F");
  tw->Branch("tSQ20_2",&tSQ20_2,"tSQ20_2[16]/F");
  tw->Branch("SSD2",&SSD2,"SSD2[16]/F");
  tw->Branch("tSSD2",&tSSD2,"tSSD2[16]/F");
  tw->Branch("SSD_V2",&SSD_V2,"SSD_V2[16]/F");
  tw->Branch("tSSD_V2",&tSSD_V2,"tSSD_V2[16]/F");

  tw->Branch("SQ20_3",&SQ20_3,"SQ20_3[16]/F");
  tw->Branch("tSQ20_3",&tSQ20_3,"tSQ20_3[16]/F");
  tw->Branch("SSD3",&SSD3,"SSD3[16]/F");
  tw->Branch("tSSD3",&tSSD3,"tSSD3[16]/F");
  tw->Branch("SSD_V3",&SSD_V3,"SSD_V3[16]/F");
  tw->Branch("tSSD_V3",&tSSD_V3,"tSSD_V3[16]/F");

  tw->Branch("SQ20_4",&SQ20_4,"SQ20_4[16]/F");
  tw->Branch("tSQ20_4",&tSQ20_4,"tSQ20_4[16]/F");
  tw->Branch("SSD4",&SSD4,"SSD4[16]/F");
  tw->Branch("tSSD4",&tSSD4,"tSSD4[16]/F");
  tw->Branch("SSD_V4",&SSD_V4,"SSD_V4[16]/F");
  tw->Branch("tSSD_V4",&tSSD_V4,"tSSD_V4[16]/F");

  readThickness();
  setTables();

  // for(Int_t nentry = 0; nentry<1000;nentry++) {
  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);

    zeroVars(); 

    if (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) reconstruct3He();
    if (nhe4_1 || nhe4_2 || nhe4_3 || nhe4_4) reconstruct4He();
    if (nAlpha) reconstructAlha();
    if (nhe6) reconstruct6He();
    if (nh3) reconstruct3H();
    if (nh2) reconstruct2H();
    if (nh3_1 || nh3_2 || nh3_3 || nh3_4) reconstruct_side_3H();

    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void readThickness() {
  cout << "thickness of the first detector " << endl;
  TFile *f1 = new TFile("/home/muzalevskii/work/macro/h7_1904/parameters/thicknessMap_calib_90_all_SSD_1m_1_real.root","READ");
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
    TH2F *hThick1 = (TH2F*)f1->Get("thicknessMap_calib_90_all_SSD_1m_1_realHist");
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
  TFile *f2 = new TFile("/home/muzalevskii/work/macro/h7_1904/parameters/thicknessMap_alltel_90_SSD_1m_2_real.root","READ");
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
    TH2F *hThick2 = (TH2F*)f2->Get("thicknessMap_alltel_90_SSD_1m_2_realHist");
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
  TFile *f3 = new TFile("/home/muzalevskii/work/macro/h7_1904/parameters/thicknessMap_calib_90_all_SSD_1m_3_switch_new.root","READ");
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
    TH2F *hThick3 = (TH2F*)f3->Get("thicknessMap_calib_90_all_SSD_1m_3_switch_realHist");
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
  TFile *f4 = new TFile("/home/muzalevskii/work/macro/h7_1904/parameters/thicknessMap_calib_90_all_SSD_1m_4_real.root","READ");
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
    TH2F *hThick4 = (TH2F*)f4->Get("thicknessMap_calib_90_all_SSD_1m_4_realHist");
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

void setTables() {

// Si
  f3HeSi = new TELoss();
  f3HeSi->SetEL(1, 2.321); // density in g/cm3
  f3HeSi->AddEL(14., 28.086, 1);  //Z, mass
  f3HeSi->SetZP(2., 3.);   //alphas, Z, A
  f3HeSi->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HeSi->SetDeltaEtab(300);

  // mylar
  f3HeMylar = new TELoss();
  f3HeMylar->SetEL(1, 1.39); // density in g/cm3
  f3HeMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
  f3HeMylar->AddEL(1., 1.00784, 0.36);
  f3HeMylar->AddEL(8., 15.99903, 0.19);
  f3HeMylar->SetZP(2., 3.);   //alphas, Z, A
  f3HeMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HeMylar->SetDeltaEtab(300);

  // steel
  f3HeSteel = new TELoss();
  f3HeSteel->SetEL(1, 8.0); // density in g/cm3
  f3HeSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
  f3HeSteel->AddEL(26., 55.845, 0.74);  
  f3HeSteel->AddEL(28., 58.6934, 0.19);
  f3HeSteel->SetZP(2., 3.);   //alphas, Z, A
  f3HeSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HeSteel->SetDeltaEtab(300);

  // deuterium target
  f3HeTarget = new TELoss();
  f3HeTarget->SetEL(1, 0.0020635); // density in g/cm3
  f3HeTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f3HeTarget->SetZP(2., 3.);   //alphas, Z, A
  f3HeTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HeTarget->SetDeltaEtab(300);
  //--------------------------------------------------------------------------------

  // tritium
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
  f3HTarget->SetEL(1, 0.0020635); // density in g/cm3
  f3HTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f3HTarget->SetZP(1., 3.);   //alphas, Z, A
  f3HTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HTarget->SetDeltaEtab(300);

  f3HPlastic = new TELoss();
  f3HPlastic->SetEL(1, 2.); // density in g/cm3
  f3HPlastic->AddEL(6., 12.0096, 0.403846);  //Z, mass
  f3HPlastic->AddEL(1., 1.00784, 0.480769);
  f3HPlastic->AddEL(17., 32.564584, 0.019231);
  f3HPlastic->AddEL(8., 15.99903, 0.096154);
  f3HPlastic->SetZP(1., 3.);   //alphas, Z, A
  f3HPlastic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HPlastic->SetDeltaEtab(300);

  f3HKeramic = new TELoss();
  f3HKeramic->SetEL(1, 3.8); // density in g/cm3
  f3HKeramic->AddEL(13., 25.126494, 0.4);  //Z, mass
  f3HKeramic->AddEL(8., 15.99903, 0.6);
  f3HKeramic->SetZP(1., 3.);   //alphas, Z, A
  f3HKeramic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HKeramic->SetDeltaEtab(300);

  //--------------------------------------------------------------------------------

  // deuterium
// Si
  f2HSi = new TELoss();
  f2HSi->SetEL(1, 2.321); // density in g/cm3
  f2HSi->AddEL(14., 28.086, 1);  //Z, mass
  f2HSi->SetZP(1., 2.);   //alphas, Z, A
  f2HSi->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f2HSi->SetDeltaEtab(300);

  // mylar
  f2HMylar = new TELoss();
  f2HMylar->SetEL(1, 1.39); // density in g/cm3
  f2HMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
  f2HMylar->AddEL(1., 1.00784, 0.36);
  f2HMylar->AddEL(8., 15.99903, 0.19);
  f2HMylar->SetZP(1., 2.);   //alphas, Z, A
  f2HMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f2HMylar->SetDeltaEtab(300);

  // steel
  f2HSteel = new TELoss();
  f2HSteel->SetEL(1, 8.0); // density in g/cm3
  f2HSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
  f2HSteel->AddEL(26., 55.845, 0.74);  
  f2HSteel->AddEL(28., 58.6934, 0.19);
  f2HSteel->SetZP(1., 2.);   //alphas, Z, A
  f2HSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f2HSteel->SetDeltaEtab(300);

  // deuterium target
  f2HTarget = new TELoss();
  f2HTarget->SetEL(1, 0.0020635); // density in g/cm3
  f2HTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f2HTarget->SetZP(1., 2.);   //alphas, Z, A
  f2HTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f2HTarget->SetDeltaEtab(300);

  f2HPlastic = new TELoss();
  f2HPlastic->SetEL(1, 2.); // density in g/cm3
  f2HPlastic->AddEL(6., 12.0096, 0.403846);  //Z, mass
  f2HPlastic->AddEL(1., 1.00784, 0.480769);
  f2HPlastic->AddEL(17., 32.564584, 0.019231);
  f2HPlastic->AddEL(8., 15.99903, 0.096154);
  f2HPlastic->SetZP(1., 2.);   //alphas, Z, A
  f2HPlastic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f2HPlastic->SetDeltaEtab(300);

  f2HKeramic = new TELoss();
  f2HKeramic->SetEL(1, 3.8); // density in g/cm3
  f2HKeramic->AddEL(13., 25.126494, 0.4);  //Z, mass
  f2HKeramic->AddEL(8., 15.99903, 0.6);
  f2HKeramic->SetZP(1., 2.);   //alphas, Z, A
  f2HKeramic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f2HKeramic->SetDeltaEtab(300);

  //--------------------------------------------------------------------------------

// Si
  f4HeSi = new TELoss();
  f4HeSi->SetEL(1, 2.321); // density in g/cm3
  f4HeSi->AddEL(14., 28.086, 1);  //Z, mass
  f4HeSi->SetZP(2., 4.);   //alphas, Z, A
  f4HeSi->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f4HeSi->SetDeltaEtab(300);

  // mylar
  f4HeMylar = new TELoss();
  f4HeMylar->SetEL(1, 1.39); // density in g/cm3
  f4HeMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
  f4HeMylar->AddEL(1., 1.00784, 0.36);
  f4HeMylar->AddEL(8., 15.99903, 0.19);
  f4HeMylar->SetZP(2., 4.);   //alphas, Z, A
  f4HeMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f4HeMylar->SetDeltaEtab(300);

  // steel
  f4HeSteel = new TELoss();
  f4HeSteel->SetEL(1, 8.0); // density in g/cm3
  f4HeSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
  f4HeSteel->AddEL(26., 55.845, 0.74);  
  f4HeSteel->AddEL(28., 58.6934, 0.19);
  f4HeSteel->SetZP(2., 4.);   //alphas, Z, A
  f4HeSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f4HeSteel->SetDeltaEtab(300);

  // deuterium target
  f4HeTarget = new TELoss();
  f4HeTarget->SetEL(1, 0.0020635); // density in g/cm3
  f4HeTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f4HeTarget->SetZP(2., 4.);   //alphas, Z, A
  f4HeTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f4HeTarget->SetDeltaEtab(300);

  f4HePlastic = new TELoss();
  f4HePlastic->SetEL(1, 2.); // density in g/cm3
  f4HePlastic->AddEL(6., 12.0096, 0.403846);  //Z, mass
  f4HePlastic->AddEL(1., 1.00784, 0.480769);
  f4HePlastic->AddEL(17., 32.564584, 0.019231);
  f4HePlastic->AddEL(8., 15.99903, 0.096154);
  f4HePlastic->SetZP(2., 4.);   //alphas, Z, A
  f4HePlastic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f4HePlastic->SetDeltaEtab(300);

  f4HeKeramic = new TELoss();
  f4HeKeramic->SetEL(1, 3.8); // density in g/cm3
  f4HeKeramic->AddEL(13., 25.126494, 0.4);  //Z, mass
  f4HeKeramic->AddEL(8., 15.99903, 0.6);
  f4HeKeramic->SetZP(2., 4.);   //alphas, Z, A
  f4HeKeramic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f4HeKeramic->SetDeltaEtab(300);

  //--------------------------------------------------------------------------------

  //--------------------------------------------------------------------------------

// Si
  f6HeSi = new TELoss();
  f6HeSi->SetEL(1, 2.321); // density in g/cm3
  f6HeSi->AddEL(14., 28.086, 1);  //Z, mass
  f6HeSi->SetZP(2., 6.);   //alphas, Z, A
  f6HeSi->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f6HeSi->SetDeltaEtab(300);

  // mylar
  f6HeMylar = new TELoss();
  f6HeMylar->SetEL(1, 1.39); // density in g/cm3
  f6HeMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
  f6HeMylar->AddEL(1., 1.00784, 0.36);
  f6HeMylar->AddEL(8., 15.99903, 0.19);
  f6HeMylar->SetZP(2., 6.);   //alphas, Z, A
  f6HeMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f6HeMylar->SetDeltaEtab(300);

  // steel
  f6HeSteel = new TELoss();
  f6HeSteel->SetEL(1, 8.0); // density in g/cm3
  f6HeSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
  f6HeSteel->AddEL(26., 55.845, 0.74);  
  f6HeSteel->AddEL(28., 58.6934, 0.19);
  f6HeSteel->SetZP(2., 6.);   //alphas, Z, A
  f6HeSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f6HeSteel->SetDeltaEtab(300);

  // deuterium target
  f6HeTarget = new TELoss();
  f6HeTarget->SetEL(1, 0.0020635); // density in g/cm3
  f6HeTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f6HeTarget->SetZP(2., 4.);   //alphas, Z, A
  f6HeTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f6HeTarget->SetDeltaEtab(300);

  f6HePlastic = new TELoss();
  f6HePlastic->SetEL(1, 2.); // density in g/cm3
  f6HePlastic->AddEL(6., 12.0096, 0.403846);  //Z, mass
  f6HePlastic->AddEL(1., 1.00784, 0.480769);
  f6HePlastic->AddEL(17., 32.564584, 0.019231);
  f6HePlastic->AddEL(8., 15.99903, 0.096154);
  f6HePlastic->SetZP(2., 6.);   //alphas, Z, A
  f6HePlastic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f6HePlastic->SetDeltaEtab(300);

  f6HeKeramic = new TELoss();
  f6HeKeramic->SetEL(1, 3.8); // density in g/cm3
  f6HeKeramic->AddEL(13., 25.126494, 0.4);  //Z, mass
  f6HeKeramic->AddEL(8., 15.99903, 0.6);
  f6HeKeramic->SetZP(2., 6.);   //alphas, Z, A
  f6HeKeramic->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f6HeKeramic->SetDeltaEtab(300);

  //--------------------------------------------------------------------------------

  return;
}

void zeroVars() {

  frame = 0;
  centE = 0;
  e_1 = 0;
  e_2 = 0;
  e_3 = 0;
  e_4 = 0;

  tritonX1 = -100;
  tritonY1 = -100;
  tritonX2 = -100;
  tritonY2 = -100;
  tritonX3 = -100;
  tritonY3 = -100;  
  tritonX4 = -100;
  tritonY4 = -100;  

return;
} 

void reconstruct3He() {

  if(nhe3_1) {
      // Si

      // e_1 = f3HeSi->GetE0(a20_1_un,4./cos(th_he3_1)) + a1_1; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_1 = f3HeSi->GetE0(e_1,0.5/cos(th_he3_1)); //dl of thin det
      e_1 = a1_1;

      thickness = (fThickness1[n20_1][n1_1]*thCoeff1+1.87)/cos(th_he3_1); // 0.5 - DL of thick det
      e_1 = f3HeSi->GetE0(e_1,thickness);

      // mylar
      thickness = 3.5/cos(th_he3_1);
      e_1 = f3HeMylar->GetE0(e_1,thickness);

      // steel
      thickness = 6./cos(th_he3_1);
      e_1 = f3HeSteel->GetE0(e_1,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_1);
      // e_1 = f3HeTarget->GetE0(e_1,thickness);
    }

    if(nhe3_2) {
      // Si
      // e_2 = f3HeSi->GetE0(a20_2_un,4./cos(th_he3_2)) + a1_2; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_2 = f3HeSi->GetE0(e_2,0.5/cos(th_he3_2)); //dl of thin det


      e_2 = a1_2;

      thickness = (fThickness2[n20_2][n1_2]*thCoeff2+1.87)/cos(th_he3_2); // 0.5 - DL of thick det
      e_2 = f3HeSi->GetE0(e_2,thickness);

      // mylar
      thickness = 3.5/cos(th_he3_2);
      e_2 = f3HeMylar->GetE0(e_2,thickness);

      // steel
      thickness = 6./cos(th_he3_2);
      e_2 = f3HeSteel->GetE0(e_2,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_2);
      // e_2 = f3HeTarget->GetE0(e_2,thickness);
    }

    if(nhe3_3) {
      // Si
      // e_3 = f3HeSi->GetE0(a20_3_un,4./cos(th_he3_3)) + a1_3; // 4 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_3 = f3HeSi->GetE0(e_3,0.5/cos(th_he3_3)); //dl of thin det

      e_3 = a1_3;

      thickness = (fThickness3[n20_3][n1_3]*thCoeff3+2.53)/cos(th_he3_3); // 0.5 - DL of thick det
      e_3 = f3HeSi->GetE0(e_3,thickness);    

      // mylar
      thickness = 3.5/cos(th_he3_3);
      e_3 = f3HeMylar->GetE0(e_3,thickness);

      // steel
      thickness = 6./cos(th_he3_3);
      e_3 = f3HeSteel->GetE0(e_3,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_3);
      // e_3 = f3HeTarget->GetE0(e_3,thickness);
    }

    if(nhe3_4) {
      // Si
      // e_4 = f3HeSi->GetE0(a20_4_un,4./cos(th_he3_4)) + a1_4; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_4 = f3HeSi->GetE0(e_4,0.5/cos(th_he3_4)); //dl of thin det

      e_4 = a1_4;

      thickness = (fThickness4[n20_4][n1_4]*thCoeff4+2.27)/cos(th_he3_4); // 0.5 - DL of thick det
      e_4 = f3HeSi->GetE0(e_4,thickness);   

      // mylar
      thickness = 3.5/cos(th_he3_4);
      e_4 = f3HeMylar->GetE0(e_4,thickness);

      // steel
      thickness = 6./cos(th_he3_4);
      e_4 = f3HeSteel->GetE0(e_4,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_4);
      // e_4 = f3HeTarget->GetE0(e_4,thickness);
    }
}

void reconstruct3H() {

    // Si
    centE = arCsI[nCsI_track] + X_C; 

    // 3 plane
    if (frame3X>12.5+xOffset || frame3X<-12.5+xOffset || frame3Y>12.5+yOffset || frame3Y<-12.5+yOffset) {

      if (frame3X<-12.5+xOffset && frame3Y>-12.5+yOffset) { // 1 telescope
        if (frame3X<-18.5+xOffset && frame3Y>-6.5+yOffset) {  // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X<12.5+xOffset && frame3Y<-12.5+yOffset) { // 2 telescope
        if (frame3X<6.5+xOffset && frame3Y<-18.5+yOffset) { // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>12.5+xOffset && frame3Y<12.5+yOffset) { // 3 telescope
        if (frame3X>18.5+xOffset && frame3Y<6.5+yOffset) { // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>-12.5+xOffset && frame3Y>12.5+yOffset) { // 4 telescope
        if (frame3X>-6.5+xOffset && frame3Y>18.5+yOffset) { // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    // 2 plane
    if (frame2X>12.5+xOffset || frame2X<-12.5+xOffset || frame2Y>12.5+yOffset || frame2Y<-12.5+yOffset) {

      if (frame2X<-12.5+xOffset && frame2Y>-12.5+yOffset) { // 1 telescope
        if (frame2X<-18.5+xOffset && frame2Y>-6.5+yOffset) {  // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X<12.5+xOffset && frame2Y<-12.5+yOffset) { // 2 telescope
        if (frame2X<6.5+xOffset && frame2Y<-18.5+yOffset) { // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>12.5+xOffset && frame2Y<12.5+yOffset) { // 3 telescope
        if (frame2X>18.5+xOffset && frame2Y<6.5+yOffset) { // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>-12.5+xOffset && frame2Y>12.5+yOffset) { // 4 telescope
        if (frame2X>-6.5+xOffset && frame2Y>18.5+yOffset) { // Si sensitive area
          centE = f3HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f3HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    if (frame1X>12.5+xOffset || frame1X<-12.5+xOffset || frame1Y>12.5+yOffset || frame1Y<-12.5+yOffset) {

      if (frame1X<-12.5+xOffset && frame1Y>-12.5+yOffset) { // 1 telescope
        if (frame1X<-21.3+xOffset && frame1Y>-3.7+yOffset) {  // Si sensitive area
          centE = f3HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f3HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X<12.5+xOffset && frame1Y<-12.5+yOffset) { // 2 telescope
        if (frame1X<3.7+xOffset && frame1Y<-21.3+yOffset) {  // Si sensitive area
          centE = f3HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f3HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>12.5+xOffset && frame1Y<12.5+yOffset) { // 3 telescope
        if (frame1X>21.3+xOffset && frame1Y<3.7+yOffset) {  // Si sensitive area
          centE = f3HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f3HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>-12.5+xOffset && frame1Y>12.5+yOffset) { // 3 telescope
        if (frame1X>-3.7+xOffset && frame1Y>21.3+yOffset) {  // Si sensitive area
          centE = f3HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f3HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

    }

    // mylar
    thickness = 3.5/cos(th_h3);
    centE = f3HMylar->GetE0(centE,thickness);

    // steel
    thickness = 6./cos(th_h3);
    centE = f3HSteel->GetE0(centE,thickness);

    // deuterium target
    // thickness = 3000./cos(th_h3);
    // centE = f3HTarget->GetE0(centE,thickness);
    
}


void reconstruct2H() {

    // Si
    centE = arCsI[nCsI_track] + X_C; 

    // 3 plane
    if (frame3X>12.5+xOffset || frame3X<-12.5+xOffset || frame3Y>12.5+yOffset || frame3Y<-12.5+yOffset) {

      if (frame3X<-12.5+xOffset && frame3Y>-12.5+yOffset) { // 1 telescope
        if (frame3X<-18.5+xOffset && frame3Y>-6.5+yOffset) {  // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X<12.5+xOffset && frame3Y<-12.5+yOffset) { // 2 telescope
        if (frame3X<6.5+xOffset && frame3Y<-18.5+yOffset) { // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>12.5+xOffset && frame3Y<12.5+yOffset) { // 3 telescope
        if (frame3X>18.5+xOffset && frame3Y<6.5+yOffset) { // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>-12.5+xOffset && frame3Y>12.5+yOffset) { // 4 telescope
        if (frame3X>-6.5+xOffset && frame3Y>18.5+yOffset) { // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    // 2 plane
    if (frame2X>12.5+xOffset || frame2X<-12.5+xOffset || frame2Y>12.5+yOffset || frame2Y<-12.5+yOffset) {

      if (frame2X<-12.5+xOffset && frame2Y>-12.5+yOffset) { // 1 telescope
        if (frame2X<-18.5+xOffset && frame2Y>-6.5+yOffset) {  // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X<12.5+xOffset && frame2Y<-12.5+yOffset) { // 2 telescope
        if (frame2X<6.5+xOffset && frame2Y<-18.5+yOffset) { // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>12.5+xOffset && frame2Y<12.5+yOffset) { // 3 telescope
        if (frame2X>18.5+xOffset && frame2Y<6.5+yOffset) { // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>-12.5+xOffset && frame2Y>12.5+yOffset) { // 4 telescope
        if (frame2X>-6.5+xOffset && frame2Y>18.5+yOffset) { // Si sensitive area
          centE = f2HSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f2HPlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    if (frame1X>12.5+xOffset || frame1X<-12.5+xOffset || frame1Y>12.5+yOffset || frame1Y<-12.5+yOffset) {

      if (frame1X<-12.5+xOffset && frame1Y>-12.5+yOffset) { // 1 telescope
        if (frame1X<-21.3+xOffset && frame1Y>-3.7+yOffset) {  // Si sensitive area
          centE = f2HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f2HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X<12.5+xOffset && frame1Y<-12.5+yOffset) { // 2 telescope
        if (frame1X<3.7+xOffset && frame1Y<-21.3+yOffset) {  // Si sensitive area
          centE = f2HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f2HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>12.5+xOffset && frame1Y<12.5+yOffset) { // 3 telescope
        if (frame1X>21.3+xOffset && frame1Y<3.7+yOffset) {  // Si sensitive area
          centE = f2HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f2HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>-12.5+xOffset && frame1Y>12.5+yOffset) { // 3 telescope
        if (frame1X>-3.7+xOffset && frame1Y>21.3+yOffset) {  // Si sensitive area
          centE = f2HSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f2HKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

    }

    // mylar
    thickness = 3.5/cos(th_h3);
    centE = f2HMylar->GetE0(centE,thickness);

    // steel
    thickness = 6./cos(th_h3);
    centE = f2HSteel->GetE0(centE,thickness);

    // deuterium target
    // thickness = 3000./cos(th_h3);
    // centE = f2HTarget->GetE0(centE,thickness);
    

}



void reconstruct4He() {


  if(nhe4_1) {
      // Si

      // e_1 = f3HeSi->GetE0(a20_1_un,4./cos(th_he3_1)) + a1_1; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_1 = f3HeSi->GetE0(e_1,0.5/cos(th_he3_1)); //dl of thin det
      e_1 = a1_1;

      thickness = (fThickness1[n20_1][n1_1]*thCoeff1+1.87)/cos(th_he3_1); // 0.5 - DL of thick det
      e_1 = f4HeSi->GetE0(e_1,thickness);

      // mylar
      thickness = 3.5/cos(th_he3_1);
      e_1 = f4HeMylar->GetE0(e_1,thickness);

      // steel
      thickness = 6./cos(th_he3_1);
      e_1 = f4HeSteel->GetE0(e_1,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_1);
      // e_1 = f4HeTarget->GetE0(e_1,thickness);
    }

    if(nhe4_2) {
      // Si
      // e_2 = f3HeSi->GetE0(a20_2_un,4./cos(th_he3_2)) + a1_2; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_2 = f3HeSi->GetE0(e_2,0.5/cos(th_he3_2)); //dl of thin det

      e_2 = a1_2;

      thickness = (fThickness2[n20_2][n1_2]*thCoeff2+1.87)/cos(th_he3_2); // 0.5 - DL of thick det
      e_2 = f4HeSi->GetE0(e_2,thickness);

      // mylar
      thickness = 3.5/cos(th_he3_2);
      e_2 = f4HeMylar->GetE0(e_2,thickness);

      // steel
      thickness = 6./cos(th_he3_2);
      e_2 = f4HeSteel->GetE0(e_2,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_2);
      // e_2 = f4HeTarget->GetE0(e_2,thickness);
    }

    if(nhe4_3) {
      // Si
      // e_3 = f3HeSi->GetE0(a20_3_un,4./cos(th_he3_3)) + a1_3; // 4 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_3 = f3HeSi->GetE0(e_3,0.5/cos(th_he3_3)); //dl of thin det

      e_3 = a1_3;

      thickness = (fThickness3[n20_3][n1_3]*thCoeff3+2.53)/cos(th_he3_3); // 0.5 - DL of thick det
      e_3 = f4HeSi->GetE0(e_3,thickness);    

      // mylar
      thickness = 3.5/cos(th_he3_3);
      e_3 = f4HeMylar->GetE0(e_3,thickness);

      // steel
      thickness = 6./cos(th_he3_3);
      e_3 = f4HeSteel->GetE0(e_3,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_3);
      // e_3 = f4HeTarget->GetE0(e_3,thickness);
    }

    if(nhe4_4) {
      // Si
      // e_4 = f3HeSi->GetE0(a20_4_un,4./cos(th_he3_4)) + a1_4; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_4 = f3HeSi->GetE0(e_4,0.5/cos(th_he3_4)); //dl of thin det

      e_4 = a1_4;

      thickness = (fThickness4[n20_4][n1_4]*thCoeff4+2.27)/cos(th_he3_4); // 0.5 - DL of thick det
      e_4 = f4HeSi->GetE0(e_4,thickness);   

      // mylar
      thickness = 3.5/cos(th_he3_4);
      e_4 = f4HeMylar->GetE0(e_4,thickness);

      // steel
      thickness = 6./cos(th_he3_4);
      e_4 = f4HeSteel->GetE0(e_4,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_4);
      // e_4 = f4HeTarget->GetE0(e_4,thickness);
    }
}


void reconstruct_side_3H() {

  if(nh3_1) {
      // Si

      // e_1 = f3HeSi->GetE0(a20_1_un,4./cos(th_he3_1)) + a1_1; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_1 = f3HeSi->GetE0(e_1,0.5/cos(th_he3_1)); //dl of thin det
      e_1 = a1_1;

      thickness = (fThickness1[n20_1][n1_1]*thCoeff1+1.87)/cos(th_he3_1); // 0.5 - DL of thick det
      e_1 = f3HSi->GetE0(e_1,thickness);

      // mylar
      thickness = 3.5/cos(th_he3_1);
      e_1 = f3HMylar->GetE0(e_1,thickness);

      // steel
      thickness = 6./cos(th_he3_1);
      e_1 = f3HSteel->GetE0(e_1,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_1);
      // e_1 = f3HTarget->GetE0(e_1,thickness);
    }

    if(nh3_2) {
      // Si
      // e_2 = f3HeSi->GetE0(a20_2_un,4./cos(th_he3_2)) + a1_2; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_2 = f3HeSi->GetE0(e_2,0.5/cos(th_he3_2)); //dl of thin det


      e_2 = a1_2;

      thickness = (fThickness2[n20_2][n1_2]*thCoeff2+1.87)/cos(th_he3_2); // 0.5 - DL of thick det
      e_2 = f3HSi->GetE0(e_2,thickness);

      // mylar
      thickness = 3.5/cos(th_he3_2);
      e_2 = f3HMylar->GetE0(e_2,thickness);

      // steel
      thickness = 6./cos(th_he3_2);
      e_2 = f3HSteel->GetE0(e_2,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_2);
      // e_2 = f3HTarget->GetE0(e_2,thickness);
    }

    if(nh3_3) {
      // Si
      // e_3 = f3HeSi->GetE0(a20_3_un,4./cos(th_he3_3)) + a1_3; // 4 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_3 = f3HeSi->GetE0(e_3,0.5/cos(th_he3_3)); //dl of thin det

      e_3 = a1_3;

      thickness = (fThickness3[n20_3][n1_3]*thCoeff3+2.53)/cos(th_he3_3); // 0.5 - DL of thick det
      e_3 = f3HSi->GetE0(e_3,thickness);    

      // mylar
      thickness = 3.5/cos(th_he3_3);
      e_3 = f3HMylar->GetE0(e_3,thickness);

      // steel
      thickness = 6./cos(th_he3_3);
      e_3 = f3HSteel->GetE0(e_3,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_3);
      // e_3 = f3HTarget->GetE0(e_3,thickness);
    }

    if(nh3_4) {
      // Si
      // e_4 = f3HeSi->GetE0(a20_4_un,4./cos(th_he3_4)) + a1_4; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_4 = f3HeSi->GetE0(e_4,0.5/cos(th_he3_4)); //dl of thin det

      e_4 = a1_4;

      thickness = (fThickness4[n20_4][n1_4]*thCoeff4+2.27)/cos(th_he3_4); // 0.5 - DL of thick det
      e_4 = f3HSi->GetE0(e_4,thickness);   

      // mylar
      thickness = 3.5/cos(th_he3_4);
      e_4 = f3HMylar->GetE0(e_4,thickness);

      // steel
      thickness = 6./cos(th_he3_4);
      e_4 = f3HSteel->GetE0(e_4,thickness);

      // deuterium target
      // thickness = 3000./cos(th_he3_4);
      // e_4 = f3HTarget->GetE0(e_4,thickness);
    }
}


void reconstructAlha() {

    // Si
    centE = arCsI[nCsI_track] + X_C; 

    // 3 plane
    if (frame3X>12.5+xOffset || frame3X<-12.5+xOffset || frame3Y>12.5+yOffset || frame3Y<-12.5+yOffset) {

      if (frame3X<-12.5+xOffset && frame3Y>-12.5+yOffset) { // 1 telescope
        if (frame3X<-18.5+xOffset && frame3Y>-6.5+yOffset) {  // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X<12.5+xOffset && frame3Y<-12.5+yOffset) { // 2 telescope
        if (frame3X<6.5+xOffset && frame3Y<-18.5+yOffset) { // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>12.5+xOffset && frame3Y<12.5+yOffset) { // 3 telescope
        if (frame3X>18.5+xOffset && frame3Y<6.5+yOffset) { // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>-12.5+xOffset && frame3Y>12.5+yOffset) { // 4 telescope
        if (frame3X>-6.5+xOffset && frame3Y>18.5+yOffset) { // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    // 2 plane
    if (frame2X>12.5+xOffset || frame2X<-12.5+xOffset || frame2Y>12.5+yOffset || frame2Y<-12.5+yOffset) {

      if (frame2X<-12.5+xOffset && frame2Y>-12.5+yOffset) { // 1 telescope
        if (frame2X<-18.5+xOffset && frame2Y>-6.5+yOffset) {  // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X<12.5+xOffset && frame2Y<-12.5+yOffset) { // 2 telescope
        if (frame2X<6.5+xOffset && frame2Y<-18.5+yOffset) { // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>12.5+xOffset && frame2Y<12.5+yOffset) { // 3 telescope
        if (frame2X>18.5+xOffset && frame2Y<6.5+yOffset) { // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>-12.5+xOffset && frame2Y>12.5+yOffset) { // 4 telescope
        if (frame2X>-6.5+xOffset && frame2Y>18.5+yOffset) { // Si sensitive area
          centE = f4HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f4HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    if (frame1X>12.5+xOffset || frame1X<-12.5+xOffset || frame1Y>12.5+yOffset || frame1Y<-12.5+yOffset) {

      if (frame1X<-12.5+xOffset && frame1Y>-12.5+yOffset) { // 1 telescope
        if (frame1X<-21.3+xOffset && frame1Y>-3.7+yOffset) {  // Si sensitive area
          centE = f4HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f4HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X<12.5+xOffset && frame1Y<-12.5+yOffset) { // 2 telescope
        if (frame1X<3.7+xOffset && frame1Y<-21.3+yOffset) {  // Si sensitive area
          centE = f4HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f4HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>12.5+xOffset && frame1Y<12.5+yOffset) { // 3 telescope
        if (frame1X>21.3+xOffset && frame1Y<3.7+yOffset) {  // Si sensitive area
          centE = f4HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f4HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>-12.5+xOffset && frame1Y>12.5+yOffset) { // 3 telescope
        if (frame1X>-3.7+xOffset && frame1Y>21.3+yOffset) {  // Si sensitive area
          centE = f4HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f4HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

    }

    // mylar
    thickness = 3.5/cos(th_h3);
    centE = f4HeMylar->GetE0(centE,thickness);

    // steel
    thickness = 6./cos(th_h3);
    centE = f4HeSteel->GetE0(centE,thickness);

    // deuterium target
    // thickness = 3000./cos(th_h3);
    // centE = f4HeTarget->GetE0(centE,thickness);
    

}


void reconstruct6He() {

    // Si
    centE = arCsI[nCsI_track] + X_C; 

    // 3 plane
    if (frame3X>12.5+xOffset || frame3X<-12.5+xOffset || frame3Y>12.5+yOffset || frame3Y<-12.5+yOffset) {

      if (frame3X<-12.5+xOffset && frame3Y>-12.5+yOffset) { // 1 telescope
        if (frame3X<-18.5+xOffset && frame3Y>-6.5+yOffset) {  // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X<12.5+xOffset && frame3Y<-12.5+yOffset) { // 2 telescope
        if (frame3X<6.5+xOffset && frame3Y<-18.5+yOffset) { // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>12.5+xOffset && frame3Y<12.5+yOffset) { // 3 telescope
        if (frame3X>18.5+xOffset && frame3Y<6.5+yOffset) { // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame3X>-12.5+xOffset && frame3Y>12.5+yOffset) { // 4 telescope
        if (frame3X>-6.5+xOffset && frame3Y>18.5+yOffset) { // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    // 2 plane
    if (frame2X>12.5+xOffset || frame2X<-12.5+xOffset || frame2Y>12.5+yOffset || frame2Y<-12.5+yOffset) {

      if (frame2X<-12.5+xOffset && frame2Y>-12.5+yOffset) { // 1 telescope
        if (frame2X<-18.5+xOffset && frame2Y>-6.5+yOffset) {  // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X<12.5+xOffset && frame2Y<-12.5+yOffset) { // 2 telescope
        if (frame2X<6.5+xOffset && frame2Y<-18.5+yOffset) { // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>12.5+xOffset && frame2Y<12.5+yOffset) { // 3 telescope
        if (frame2X>18.5+xOffset && frame2Y<6.5+yOffset) { // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }

      if (frame2X>-12.5+xOffset && frame2Y>12.5+yOffset) { // 4 telescope
        if (frame2X>-6.5+xOffset && frame2Y>18.5+yOffset) { // Si sensitive area
          centE = f6HeSi->GetE0(centE,1000./cos(th_h3));
        }
        else { // FR4 frame
          centE = f6HePlastic->GetE0(centE,3000./cos(th_h3));
        }
      }
    }

    if (frame1X>12.5+xOffset || frame1X<-12.5+xOffset || frame1Y>12.5+yOffset || frame1Y<-12.5+yOffset) {

      if (frame1X<-12.5+xOffset && frame1Y>-12.5+yOffset) { // 1 telescope
        if (frame1X<-21.3+xOffset && frame1Y>-3.7+yOffset) {  // Si sensitive area
          centE = f6HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f6HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X<12.5+xOffset && frame1Y<-12.5+yOffset) { // 2 telescope
        if (frame1X<3.7+xOffset && frame1Y<-21.3+yOffset) {  // Si sensitive area
          centE = f6HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f6HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>12.5+xOffset && frame1Y<12.5+yOffset) { // 3 telescope
        if (frame1X>21.3+xOffset && frame1Y<3.7+yOffset) {  // Si sensitive area
          centE = f6HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f6HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

      if (frame1X>-12.5+xOffset && frame1Y>12.5+yOffset) { // 3 telescope
        if (frame1X>-3.7+xOffset && frame1Y>21.3+yOffset) {  // Si sensitive area
          centE = f6HeSi->GetE0(centE,20./cos(th_h3));
        }
        else { // Keramik frame
          centE = f6HeKeramic->GetE0(centE,660./cos(th_h3));
        }
      }

    }

    // mylar
    thickness = 3.5/cos(th_h3);
    centE = f6HeMylar->GetE0(centE,thickness);

    // steel
    thickness = 6./cos(th_h3);
    centE = f6HeSteel->GetE0(centE,thickness);

    // deuterium target
    // thickness = 3000./cos(th_h3);
    // centE = f6HeTarget->GetE0(centE,thickness);
    

}

