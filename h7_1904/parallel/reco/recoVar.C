#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void calculateBeam();
void zerovars();
void neutronEnergy();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);
void neutronID();
void fillND_positions();
void getNeutronXY(Float_t* x, Float_t* y,Float_t dist);

void reco7H();
void reco6H_side();
void reco6H_cent();
void reco7He_side();
void reco7He_cent();

void rotate7H();
void rotate6H();

#include "/home/muzalevskii/work/macro/h7_1904/parallel/reco/recoInput.h"
#include "/home/muzalevskii/work/macro/h7_1904/parallel/reco/recoOutput.h"

TVector3 pos_ND[48],pos_ND_target[48];
Float_t ND_time_position[48],ND_position[48];

//------------------------------------------------------------------------------------------------
// calibration pars
Float_t timeNDpar1[32],timeNDpar2[32];
//------------------------------------------------------------------------------------------------
TELoss f8HeSi;
//------------------------------------------------------------------------------------------------
// Vectors for boost
TVector3 bVect_R,bVect_7H; 
TVector3 bVect_6H,bVect_7He;
//------------------------------------------------------------------------------------------------
// Lorentz Vectors
TLorentzVector lv_d2;
TLorentzVector lv_R;
TLorentzVector lv_tmp;
//------------------------------------------------------------------------------------------------
// Int
Int_t numND;
//------------------------------------------------------------------------------------------------
// Float
Float_t mass,momentum;
Float_t ND_posTarget[32],x_ND_p[32],y_ND_p[32];



void recoVar(Int_t nRun=0) {

  fillND_positions();

  create_IDs();
  create_cuts();

  readPar("timesND",timeNDpar1,timeNDpar2,32);

  f8HeSi.SetEL(1, 2.321); // density in g/cm3
  f8HeSi.AddEL(14., 28.086, 1);  //Z, mass
  f8HeSi.SetZP(2., 8.);   //alphas, Z, A
  f8HeSi.SetEtab(300000, 250.); // ?, MeV calculate ranges
  f8HeSi.SetDeltaEtab(300);

  TChain *ch = new TChain("tree");
  TString inPutFileName;
  inPutFileName.Form("/mnt/data/exp1904/analysed/calcEnergies/h7/h7_ct_%d_reco.root",nRun);
  ch->Add(inPutFileName.Data());;
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

  ch->SetBranchAddress("fXt.",&fXt);
  ch->SetBranchAddress("fYt.",&fYt); 
  ch->SetBranchAddress("fXf.",&fXf);
  ch->SetBranchAddress("fYf.",&fYf);
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

  ch->SetBranchAddress("a20_2.",&a20_2);
  ch->SetBranchAddress("a20_2_un.",&a20_2_un);
  ch->SetBranchAddress("t20_2.",&t20_2);
  ch->SetBranchAddress("n20_2.",&n20_2);

  ch->SetBranchAddress("a1_2.",&a1_2);
  ch->SetBranchAddress("t1_2.",&t1_2);
  ch->SetBranchAddress("n1_2.",&n1_2);

  ch->SetBranchAddress("a20_3.",&a20_3);
  ch->SetBranchAddress("a20_3_un.",&a20_3_un);
  ch->SetBranchAddress("t20_3.",&t20_3);
  ch->SetBranchAddress("n20_3.",&n20_3);

  ch->SetBranchAddress("a1_3.",&a1_3);
  ch->SetBranchAddress("t1_3.",&t1_3);
  ch->SetBranchAddress("n1_3.",&n1_3);

  ch->SetBranchAddress("a20_4.",&a20_4);
  ch->SetBranchAddress("a20_4_un.",&a20_4_un);
  ch->SetBranchAddress("t20_4.",&t20_4);
  ch->SetBranchAddress("n20_4.",&n20_4);

  ch->SetBranchAddress("a1_4.",&a1_4);
  ch->SetBranchAddress("t1_4.",&t1_4);
  ch->SetBranchAddress("n1_4.",&n1_4);

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

  ch->SetBranchAddress("nhe4_1.",&nhe4_1);
  ch->SetBranchAddress("nhe4_2.",&nhe4_2);
  ch->SetBranchAddress("nhe4_3.",&nhe4_3);
  ch->SetBranchAddress("nhe4_4.",&nhe4_4);

  ch->SetBranchAddress("nh3_1.",&nh3_1);
  ch->SetBranchAddress("nh3_2.",&nh3_2);
  ch->SetBranchAddress("nh3_3.",&nh3_3);
  ch->SetBranchAddress("nh3_4.",&nh3_4);

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

  ch->SetBranchAddress("e_1.",&e_1);
  ch->SetBranchAddress("e_2.",&e_2);
  ch->SetBranchAddress("e_3.",&e_3);
  ch->SetBranchAddress("e_4.",&e_4);
  ch->SetBranchAddress("centE.",&centE);

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

  ch->SetBranchAddress("av_1.",&av_1);
  ch->SetBranchAddress("tv_1.",&tv_1);
  ch->SetBranchAddress("nv_1.",&nv_1);

  ch->SetBranchAddress("av_2.",&av_2);
  ch->SetBranchAddress("tv_2.",&tv_2);
  ch->SetBranchAddress("nv_2.",&nv_2);

  ch->SetBranchAddress("av_3.",&av_3);
  ch->SetBranchAddress("tv_3.",&tv_3);
  ch->SetBranchAddress("nv_3.",&nv_3);

  ch->SetBranchAddress("av_4.",&av_4);
  ch->SetBranchAddress("tv_4.",&tv_4);
  ch->SetBranchAddress("nv_4.",&nv_4);

  TString outPutFileName;
  outPutFileName.Form("/mnt/data/exp1904/analysed/reco/h7/h7_ct_%d_mm.root",nRun);
  // outPutFileName.Form("test_%d_new.root",nRun);

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

// Lorentz Vectors

  tw->Branch("lv_he8","TLorentzVector",&lv_he8);

  tw->Branch("lv_h7","TLorentzVector",&lv_h7);
  tw->Branch("lv_he3","TLorentzVector",&lv_he3);
  tw->Branch("lv_h3","TLorentzVector",&lv_h3);
  tw->Branch("lv_h3_CMH7","TLorentzVector",&lv_h3_CMH7);
  tw->Branch("lv_h7_CMR","TLorentzVector",&lv_h7_CMR);

  tw->Branch("lv_he4","TLorentzVector",&lv_he4);
  tw->Branch("lv_h3_CMH6","TLorentzVector",&lv_h3_CMH6);
  tw->Branch("lv_h6","TLorentzVector",&lv_h6);
  tw->Branch("lv_h6_CMR","TLorentzVector",&lv_h6_CMR);
  tw->Branch("lv_he4_CMH6","TLorentzVector",&lv_he4_CMH6);
  tw->Branch("lv_he8_CMH6","TLorentzVector",&lv_he8_CMH6);

  tw->Branch("lv_he7","TLorentzVector",&lv_he7);
  tw->Branch("lv_he7_CMR","TLorentzVector",&lv_he7_CMR);
  tw->Branch("lv_he4_CMHe7","TLorentzVector",&lv_he4_CMHe7);

  tw->Branch("lv_neutron","TLorentzVector",&lv_neutron);
  tw->Branch("lv_neutron_CMH6","TLorentzVector",&lv_neutron_CMH6);

  tw->Branch("lv_h3_CMH6_rot","TLorentzVector",&lv_h3_CMH6_rot);
  tw->Branch("lv_h3_CMH7_rot","TLorentzVector",&lv_h3_CMH7_rot);

  tw->Branch("lv_h6qFrame","TLorentzVector",&lv_h6qFrame);
  tw->Branch("lv_h3qFrame","TLorentzVector",&lv_h3qFrame);

// arrays 
  tw->Branch("ND_time_cal",&ND_time_cal,"ND_time_cal[32]/F");
  tw->Branch("ND_energy",&ND_energy,"ND_energy[32]/F");
  tw->Branch("tND_cal",&tND_cal,"tND_cal/F");
  tw->Branch("aND",&aND,"aND/F");
  tw->Branch("tND",&tND,"tND/F");
  tw->Branch("tacND",&tacND,"tacND/F");
  tw->Branch("numND",&numND,"numND/I");
  tw->Branch("eNeutron",&eNeutron,"eNeutron/F");

// h7
  tw->Branch("angle_he3_h7",&angle_he3_h7,"angle_he3_h7/F");
  tw->Branch("angle_h3_h7",&angle_h3_h7,"angle_h3_h7/F");
  tw->Branch("angle_he3_he8",&angle_he3_he8,"angle_he3_he8/F");
  tw->Branch("angle_h7_he8",&angle_h7_he8,"angle_h7_he8/F");
// h6
  tw->Branch("angle_he4_h6",&angle_he4_h6,"angle_he4_h6/F");
  tw->Branch("angle_h3_h6",&angle_h3_h6,"angle_h3_h6/F");
  tw->Branch("angle_he4_he8",&angle_he4_he8,"angle_he4_he8/F");
  tw->Branch("angle_h3_he8",&angle_h3_he8,"angle_h3_he8/F");
  tw->Branch("angle_h3_he8_CMH6",&angle_h3_he8_CMH6,"angle_h3_he8_CMH6/F");
  
// Floats
  tw->Branch("diafTime",&diafTime,"diafTime/F");
  tw->Branch("targetTime",&targetTime,"targetTime/F");

  // input options
  lv_d2.SetXYZT(0.,0.,0.,1.875612);

  Float_t xCent,yCent;
  xCent = 0.467;
  yCent = 0.026;

  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry = 0; nentry<50000;nentry++) {
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);
    
    if ( ((fXt-xCent)*(fXt-xCent) + (fYt-yCent)*(fYt-yCent))>9.5*9.5 ) continue;

    zerovars();

    calculateBeam();
    lv_R = lv_he8 + lv_d2;
    bVect_R = lv_R.BoostVector();

    neutronID();

    if (nh3 && flagCent && ( ( nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )) { // reco 7H
      reco7H();
      rotate7H();
    }

    if (nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )) { //  reco 6H     
      reco6H_side();
      rotate6H();
      // reco7He_cent();
    }
    // if (nAlpha && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) )) { //  reco 6H
    //   reco6H_cent();
    //   rotate6H();
    //   reco7He_side();
    // }


    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

return;

}

void calculateBeam() {

  TVector3 dir;
  dir.SetXYZ(fXt-x1c,fYt-y1c,815.);
  // dir.SetXYZ(x2c-x1c,y2c-y1c,545.);  
  Float_t phi = dir.Phi();
  Float_t theta = dir.Theta();

  Double_t len = dir.Mag();

  mass = 7.482538;

  Double_t velocity = 12320./(tF5-tF3 + 68.475);
  Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  Double_t kinEnergy = mass*((1/beta) - 1);

  kinEnergy =  f8HeSi.GetE(1000*kinEnergy, 540.)/1000.;

  targetTime = tF5 + 469./velocity;
  diafTime = tF5 + 365./velocity;
  Float_t velocityCorr = 299.792458*sqrt( (1-1/((kinEnergy/mass+1)*(kinEnergy/mass+1))) );
  targetTime += 469./velocityCorr;
  diafTime += 365./velocityCorr;

  Float_t pBeam = sqrt(kinEnergy*kinEnergy + 2*kinEnergy*mass);
  pBeam = TMath::Abs(pBeam);

  lv_he8.SetXYZM(pBeam*TMath::Sin(theta)*TMath::Cos(phi), pBeam*TMath::Sin(theta)*TMath::Sin(phi), pBeam*TMath::Cos(theta) ,mass);

}

void zerovars() {
  lv_tmp.SetXYZT(0,0,0,0);

  bVect_R.SetXYZ(0,0,0);
  bVect_7H.SetXYZ(0,0,0);
  bVect_6H.SetXYZ(0,0,0);
  bVect_7He.SetXYZ(0,0,0);

  lv_he8.SetXYZT(0,0,0,0);
  lv_R.SetXYZT(0,0,0,0);
  lv_h7.SetXYZT(0,0,0,0);
  lv_he3.SetXYZT(0,0,0,0);
  lv_h3.SetXYZT(0,0,0,0);

  lv_h3.SetXYZT(0,0,0,0);
  lv_he4.SetXYZT(0,0,0,0);
  lv_h6.SetXYZT(0,0,0,0);

  lv_h3_CMH7.SetXYZT(0,0,0,0);
  lv_h3_CMH6.SetXYZT(0,0,0,0);
  lv_he4_CMHe7.SetXYZT(0,0,0,0);
  lv_he4_CMH6.SetXYZT(0,0,0,0);
  lv_he8_CMH6.SetXYZT(0,0,0,0);

  lv_h7_CMR.SetXYZT(0,0,0,0);
  lv_h6_CMR.SetXYZT(0,0,0,0);

  lv_he7.SetXYZT(0,0,0,0);
  lv_he7_CMR.SetXYZT(0,0,0,0);

  lv_neutron.SetXYZT(0,0,0,0);
  lv_neutron_CMH6.SetXYZT(0,0,0,0);

  lv_h3_CMH7_rot.SetXYZT(0,0,0,0);
  lv_h3_CMH6_rot.SetXYZT(0,0,0,0);

  for(Int_t i=0;i<32;i++) {
    ND_time_cal[i] = -1;
    ND_energy[i] = -1;
    x_ND_p[i] = -1000000;
    y_ND_p[i] = -1000000;
  }
  tND_cal = -1;
  aND = -1;
  tacND = -1;
  numND = -1;
  eNeutron = -1;
  neutron = 0;


  angle_he3_h7 = -1000;
  angle_h3_h7 = -1000;
  angle_he4_h6 = -1000;
  angle_h3_h6 = -1000;

  angle_he3_he8 = -1000;
  angle_h7_he8 = -1000;
  angle_h3_he8 = -1000;
  angle_he4_he8 = -1000;
  angle_h3_he8_CMH6 = -1000;

  angle_h3_beam_CMH6 = -1000;
  angle_h3_q_CMH6 = -1000;
}

void neutronID() {

  Int_t multiplicity = 0;

  for (Int_t i=0;i<32;i++) {

    ND_time_cal[i] = ND_time[i] - timeNDpar1[i] + ND_time_position[i];
    if (ND_time[i]>0 && ND_amp[i]>0) {
      multiplicity++;
      numND = i;
    }
  }
  if (multiplicity==1) {
    aND = ND_amp[numND];
    tND = ND_time[numND];
    tND_cal = ND_time[numND] - timeNDpar1[numND] + ND_time_position[numND];
  }
  else {
    numND = -1;
  }

  mass = 0.939565;

  for (Int_t i=0;i<32;i++) {
    if (cutNeutron->IsInside(ND_amp[i] , ND_tac[i]) ) {
      neutron++;
      numND = i;
      
      Double_t velocity = ND_posTarget[i]/(ND_time_cal[i]-targetTime);
      Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
      ND_energy[i] = mass*((1/beta) - 1);
      eNeutron = ND_energy[i];

      getNeutronXY(x_ND_p+i,y_ND_p+i,323);

    }

  }
  if (neutron==1) {

    TVector3 dir;
    dir.SetXYZ(pos_ND_target[numND].Px()-fXt,pos_ND_target[numND].Py()-fYt,pos_ND_target[numND].Pz());

    momentum = sqrt(eNeutron*eNeutron + 2*eNeutron*mass);

    lv_neutron.SetXYZM(momentum*TMath::Sin(dir.Theta())*TMath::Cos(dir.Phi()), momentum*TMath::Sin(dir.Theta())*TMath::Sin(dir.Phi()), momentum*TMath::Cos(dir.Theta()) ,mass);
  }

}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/muzalevskii/work/macro/h7_1904/parameters/" + fileName + ".cal";
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
  //cout << endl << fileName.Data() << endl;
  //for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

  return;
}

void fillND_positions() {

  float NeutXYZ[45][3] = {  
  450., -300.,  1900.,
  300., -300.,  1925.,
  150., -300.,  1939.9,
  0.0,  -300.,  1945.,
  -150.,  -300.,  1939.9,
  -300.,  -300.,  1925.,
  -450.,  -300.,  1900.,
  450., -150.,  1900.,
  300., -150.,  1925.,
  150., -150.,  1939.9,
  0.0,  -150.,  1945.,
  -150.,  -150.,  1939.9,
  -300.,  -150.,  1925.,
  -450.,  -150.,  1900.,
  450., 0.0,  1900.,
  300., 0.0,  1925.,
  150., 0.0,  1939.9,
  -100.,  0.0,  1943.,
  -250.,  0.0,  1931.1,
  -400.,  0.0,  1909.4,
  -550.,  0.0,  1877.8,
  450., 150., 1900.,
  300., 150., 1925.,
  150., 150., 1939.9,
  0.0,  150., 1945.,
  -150.,  150., 1939.9,
  -300.,  150., 1925.,
  -450.,  150., 1900.,
  450., 300., 1900.,
  300., 300., 1925.,
  150., 300., 1939.9,
  0.0,  300., 1945.,
  -150.,  300., 1939.9,
  -300.,  300., 1925.,
  -450.,  300., 1900.,
  600., 300., 1865.,
  600., 150., 1865.,
  750., 0.0,  1820.2,
  600., 0.0,  1865.,
  600., -150.,  1865.,
  600., -300.,  1865.,
  -600.,  300., 1865.,
  -600.,  150., 1865.,
  -600.,  -150.,  1865.,
  -600.,  -300.,  1865.};
  //
  for (int i=0; i<45;i++){
        
      pos_ND[i].SetXYZ(NeutXYZ[i][0]-fXf,NeutXYZ[i][1]-fYf,NeutXYZ[i][2]+205.);    // in mm
      pos_ND_target[i].SetXYZ(NeutXYZ[i][0]-fXt,NeutXYZ[i][1]-fYt,NeutXYZ[i][2]);    // in mm
  //    printf("det %d:  position(x,y,z), mm = %f,%f,%f\n",i, pos_ND[i].X(),pos_ND[i].Y(), pos_ND[i].Z());      
  //    printf("det %d:  distance = %f  mm\n",i, pos_ND[i].Mag());
  //    printf("det %d:  tof = %f  ns\n",i, pos_ND[i].Mag()/299.729);
      // printf("%f\n",pos_ND[i].Mag()/299.729);
      ND_time_position[i] = pos_ND[i].Mag()/299.729;
      ND_posTarget[i] = pos_ND_target[i].Mag();
      ND_position[i] = pos_ND[i].Mag();
  }
}

void getNeutronXY(Float_t* x, Float_t* y,Float_t dist) {

  Float_t x_ND = pos_ND_target[numND].Px();
  Float_t y_ND = pos_ND_target[numND].Py();
  Float_t z_ND = pos_ND_target[numND].Pz();

  TVector3 dir;
  dir.SetXYZ(x_ND-fXt,y_ND-fYt,z_ND);

  Float_t phi = dir.Phi();
  Float_t theta = dir.Theta();

  *x = fXt + (x_ND-fXt)*dist/z_ND;
  *y = fYt + (y_ND-fYt)*dist/z_ND;
}

void reco7H() {

  Float_t energy;
  Float_t theta;
  Float_t phi;

  if (flag1 && nhe3_1 && !nhe3_2 && !nhe3_3 && !nhe3_4 ) {
    energy = e_1/1000.;
    theta = th_he3_1;
    phi = phi_he3_1;
  } 

  if (flag2 && nhe3_2 && !nhe3_1 && !nhe3_3 && !nhe3_4 ) {
    energy = e_2/1000.;
    theta = th_he3_2;
    phi = phi_he3_2;
  } 

  if (flag3 && nhe3_3 && !nhe3_1 && !nhe3_2 && !nhe3_4) {
    energy = e_3/1000.;
    theta = th_he3_3;
    phi = phi_he3_3;
  } 

  if (flag4 && nhe3_4 && !nhe3_2 && !nhe3_3 && !nhe3_1) {
    energy = e_4/1000.;
    theta = th_he3_4;
    phi = phi_he3_4;
  }  

  mass = 2.808391;  //MeV
  momentum = sqrt(energy*energy + 2*energy*mass);
  lv_he3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

  lv_h7 = lv_he8 + lv_d2 + (-lv_he3);
  lv_h7_CMR = lv_h7;
  lv_h7_CMR.Boost(-bVect_R);

  bVect_7H = lv_h7.BoostVector();

  angle_he3_h7 = lv_h7.Angle(lv_he3.Vect())*TMath::RadToDeg();

  energy = centE/1000.;
  mass = 2.80892; //GeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_h3.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);
  angle_h3_h7 = lv_h7.Angle(lv_h3.Vect())*TMath::RadToDeg();

  lv_h3_CMH7 = lv_h3;
  lv_h3_CMH7.Boost(-bVect_7H);

  angle_he3_he8 = lv_he8.Angle(lv_he3.Vect())*TMath::RadToDeg();
  angle_h7_he8 = lv_he8.Angle(lv_h7.Vect())*TMath::RadToDeg();

}

void reco6H_side() {

  Float_t energy;
  Float_t theta;
  Float_t phi;

  if (flag1 && nhe4_1 && !nhe4_2 && !nhe4_3 && !nhe4_4 ) {
    energy = e_1/1000.;
    theta = th_he3_1;
    phi = phi_he3_1;
  } 

  if (flag2 && nhe4_2 && !nhe4_1 && !nhe4_3 && !nhe4_4 ) {
    energy = e_2/1000.;
    theta = th_he3_2;
    phi = phi_he3_2;
  } 

  if (flag3 && nhe4_3 && !nhe4_1 && !nhe4_2 && !nhe4_4) {
    energy = e_3/1000.;
    theta = th_he3_3;
    phi = phi_he3_3;
  } 

  if (flag4 && nhe4_4 && !nhe4_2 && !nhe4_3 && !nhe4_1) {
    energy = e_4/1000.;
    theta = th_he3_4;
    phi = phi_he3_4;
  }  

  mass = 3.727378;  //MeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_he4.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);
  // if (lv_he4.

  lv_h6 = lv_he8 + lv_d2 + (-lv_he4);
  lv_h6_CMR = lv_h6;
  lv_h6_CMR.Boost(-bVect_R);

  bVect_6H = lv_h6.BoostVector();

  angle_he4_h6 = lv_h6.Angle(lv_he4.Vect())*TMath::RadToDeg();

  energy = centE/1000.;
  mass = 2.80892; //GeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_h3.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);
  angle_h3_h6 = lv_h6.Angle(lv_h3.Vect())*TMath::RadToDeg();

  lv_h3_CMH6 = lv_h3;
  lv_h3_CMH6.Boost(-bVect_6H);

  lv_he4_CMH6 = lv_he4;
  lv_he4_CMH6.Boost(-bVect_6H);

  lv_he8_CMH6 = lv_he8;
  lv_he8_CMH6.Boost(-bVect_6H);  

  angle_he4_he8 = lv_he8.Angle(lv_he4.Vect())*TMath::RadToDeg();
  angle_h3_he8 = lv_he8.Angle(lv_h3.Vect())*TMath::RadToDeg();
  angle_h3_he8_CMH6 = lv_he8_CMH6.Angle(lv_h3_CMH6.Vect())*TMath::RadToDeg();

  lv_neutron_CMH6 = lv_neutron;
  lv_neutron_CMH6.Boost(-bVect_6H);


  // if (1000*(lv_h6.Mag()-3*0.939565-2.808920)>3 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<5) {
  //   cout << endl;
  //   cout << 1000*(lv_he8.T()-lv_he8.Mag()) << " " << lv_he8.Theta()*TMath::RadToDeg() << " " << lv_he8.Phi()*TMath::RadToDeg() << endl;
  //   cout << 1000*(lv_he4.T()-lv_he4.Mag()) << " " << lv_he4.Theta()*TMath::RadToDeg() << " " << lv_he4.Phi()*TMath::RadToDeg() << endl;
  //   cout << lv_he4.Angle(lv_he8.Vect())*TMath::RadToDeg() << " " << lv_h6_CMR.Theta()*TMath::RadToDeg() << endl;
  //   cout << 1000*lv_h6.Mag() << " " << 1000*(lv_h6.Mag()-3*0.939565-2.808920) << endl;
  // }

  // cout << endl << 1000*(lv_he8.T()-lv_he8.Mag()) << " " << lv_he8.Theta()*TMath::RadToDeg() << " " << lv_he8.Phi()*TMath::RadToDeg() << endl;
  // cout << 1000*(lv_he4.T()-lv_he4.Mag()) << " " << lv_he4.Theta()*TMath::RadToDeg() << " " << lv_he4.Phi()*TMath::RadToDeg() << endl;
  // cout << lv_h6_CMR.Theta()*TMath::RadToDeg() << " " << lv_h6.Mag() << endl;

}


void reco6H_cent() {

  Float_t energy;
  Float_t theta;
  Float_t phi;

  if (flag1 && nh3_1 && !nh3_2 && !nh3_3 && !nh3_4 ) {
    energy = e_1/1000.;
    theta = th_he3_1;
    phi = phi_he3_1;
  } 

  if (flag2 && nh3_2 && !nh3_1 && !nh3_3 && !nh3_4 ) {
    energy = e_2/1000.;
    theta = th_he3_2;
    phi = phi_he3_2;
  } 

  if (flag3 && nh3_3 && !nh3_1 && !nh3_2 && !nh3_4) {
    energy = e_3/1000.;
    theta = th_he3_3;
    phi = phi_he3_3;
  } 

  if (flag4 && nh3_4 && !nh3_2 && !nh3_3 && !nh3_1) {
    energy = e_4/1000.;
    theta = th_he3_4;
    phi = phi_he3_4;
  }  

  mass = 2.80892; //GeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_h3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

  energy = centE/1000.;
  mass = 3.727378;
  momentum = sqrt(energy*energy + 2*energy*mass);
  lv_he4.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);

  lv_h6 = lv_he8 + lv_d2 + (-lv_he4);
  lv_h6_CMR = lv_h6;
  lv_h6_CMR.Boost(-bVect_R);
  
  bVect_6H = lv_h6.BoostVector();

  angle_he4_h6 = lv_h6.Angle(lv_he4.Vect())*TMath::RadToDeg();
  angle_h3_h6 = lv_h6.Angle(lv_h3.Vect())*TMath::RadToDeg();

  lv_h3_CMH6 = lv_h3;
  lv_h3_CMH6.Boost(-bVect_6H);

  angle_he4_he8 = lv_he8.Angle(lv_he4.Vect())*TMath::RadToDeg();
  angle_h3_he8 = lv_he8.Angle(lv_h3.Vect())*TMath::RadToDeg();

  lv_neutron_CMH6 = lv_neutron;
  lv_neutron_CMH6.Boost(-bVect_6H);

}

void reco7He_cent() {

  Float_t energy;
  Float_t theta;
  Float_t phi;

  if (flag1 && nhe4_1 && !nhe4_2 && !nhe4_3 && !nhe4_4 ) {
    energy = e_1/1000.;
    theta = th_he3_1;
    phi = phi_he3_1;
  } 

  if (flag2 && nhe4_2 && !nhe4_1 && !nhe4_3 && !nhe4_4 ) {
    energy = e_2/1000.;
    theta = th_he3_2;
    phi = phi_he3_2;
  } 

  if (flag3 && nhe4_3 && !nhe4_1 && !nhe4_2 && !nhe4_4) {
    energy = e_3/1000.;
    theta = th_he3_3;
    phi = phi_he3_3;
  } 

  if (flag4 && nhe4_4 && !nhe4_2 && !nhe4_3 && !nhe4_1) {
    energy = e_4/1000.;
    theta = th_he3_4;
    phi = phi_he3_4;
  }  

  mass = 3.727378;  //MeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_he4.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

  energy = centE/1000.;
  mass = 2.80892; //GeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_h3.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);

  lv_he7 = lv_he8 + lv_d2 + (-lv_h3);
  lv_he7_CMR = lv_he7;
  lv_he7_CMR.Boost(-bVect_R);

  bVect_7He = lv_he7.BoostVector();

  lv_he4_CMHe7 = lv_he4;
  lv_he4_CMHe7.Boost(-bVect_7He);

}

void reco7He_side() {

  Float_t energy;
  Float_t theta;
  Float_t phi;

  if (flag1 && nh3_1 && !nh3_2 && !nh3_3 && !nh3_4 ) {
    energy = e_1/1000.;
    theta = th_he3_1;
    phi = phi_he3_1;
  } 

  if (flag2 && nh3_2 && !nh3_1 && !nh3_3 && !nh3_4 ) {
    energy = e_2/1000.;
    theta = th_he3_2;
    phi = phi_he3_2;
  } 

  if (flag3 && nh3_3 && !nh3_1 && !nh3_2 && !nh3_4) {
    energy = e_3/1000.;
    theta = th_he3_3;
    phi = phi_he3_3;
  } 

  if (flag4 && nh3_4 && !nh3_2 && !nh3_3 && !nh3_1) {
    energy = e_4/1000.;
    theta = th_he3_4;
    phi = phi_he3_4;
  }   

  mass = 2.80892; //GeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_h3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

  energy = centE/1000.;
  mass = 3.727378;  //MeV
  momentum = sqrt(energy*energy + 2*energy*mass);

  lv_he4.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);

  lv_he7 = lv_he8 + lv_d2 + (-lv_h3);
  lv_he7_CMR = lv_he7;
  lv_he7_CMR.Boost(-bVect_R);

  bVect_7He = lv_he7.BoostVector();

  lv_he4_CMHe7 = lv_he4;
  lv_he4_CMHe7.Boost(-bVect_7He);
}

void rotate7H() {

  TLorentzVector lv_h3aLab = lv_h3;
  TLorentzVector lv_h7aLab = lv_h7;
  TLorentzVector lv_dAlab = lv_d2;

  TVector3 bVect_beam = lv_he8.BoostVector();

  lv_h3aLab.Boost(-bVect_beam);
  lv_h7aLab.Boost(-bVect_beam);
  lv_dAlab.Boost(-bVect_beam);

  TVector3 v_h7aLab = lv_h7aLab.Vect();
  TVector3 v_dAlab = lv_dAlab.Vect();

  TVector3 v_yMomenta(0,0,0);

  TVector3 v_zMomenta = v_h7aLab;
  v_zMomenta = v_h7aLab.Unit();

  TVector3 v_xMomenta = v_dAlab;
  v_xMomenta = v_zMomenta.Cross(v_xMomenta);
  v_xMomenta = v_xMomenta.Unit();

  v_yMomenta = v_zMomenta.Cross(v_xMomenta);
  v_yMomenta = v_yMomenta.Unit();

  TRotation rot_aLab;
  rot_aLab.RotateAxes(v_xMomenta,v_yMomenta,v_zMomenta);
  TLorentzRotation lrot_aLab(rot_aLab);

  TLorentzVector lv_h3qFrame = lv_h3aLab;
  lv_h3qFrame.Transform(lrot_aLab.Inverse());

  TLorentzVector lv_h7qFrame = lv_h7aLab;
  lv_h7qFrame.Transform(lrot_aLab.Inverse());

  TVector3 bVect_frame7H = lv_h7qFrame.BoostVector();
  lv_h3_CMH7_rot = lv_h3qFrame;
  lv_h3_CMH7_rot.Boost(-bVect_frame7H);
}


void rotate6H() {

  TLorentzVector lv_h3aLab = lv_h3;
  TLorentzVector lv_h6aLab = lv_h6;
  TLorentzVector lv_dAlab = lv_d2;

  TVector3 bVect_beam = lv_he8.BoostVector();

  lv_h3aLab.Boost(-bVect_beam);
  lv_h6aLab.Boost(-bVect_beam);
  lv_dAlab.Boost(-bVect_beam);

  TVector3 v_h6aLab = lv_h6aLab.Vect();
  TVector3 v_dAlab = lv_dAlab.Vect();

  TVector3 v_yMomenta(0,0,0);

  TVector3 v_zMomenta = v_h6aLab;
  v_zMomenta = v_h6aLab.Unit();

  TVector3 v_xMomenta = v_dAlab;
  v_xMomenta = v_zMomenta.Cross(v_xMomenta);
  v_xMomenta = v_xMomenta.Unit();

  v_yMomenta = v_zMomenta.Cross(v_xMomenta);
  v_yMomenta = v_yMomenta.Unit();

  TRotation rot_aLab;
  rot_aLab.RotateAxes(v_xMomenta,v_yMomenta,v_zMomenta);
  TLorentzRotation lrot_aLab(rot_aLab);

  lv_h3qFrame = lv_h3aLab;
  lv_h3qFrame.Transform(lrot_aLab.Inverse());

  lv_h6qFrame = lv_h6aLab;
  lv_h6qFrame.Transform(lrot_aLab.Inverse());
  // cout << lv_h6qFrame.Theta() << "  " << lv_h6qFrame.Phi()*TMath::RadToDeg() << " " << lv_dAlab.T()-lv_dAlab.Mag() << endl;

  TVector3 bVect_frame6H = lv_h6qFrame.BoostVector();
  lv_h3_CMH6_rot = lv_h3qFrame;
  lv_h3_CMH6_rot.Boost(-bVect_frame6H);

}


// void rotate6H() {

//   TLorentzVector lv_h3aLab = lv_h3;
//   TLorentzVector lv_he4aLab = lv_h6;
//   TLorentzVector lv_dAlab = lv_d2;

//   TVector3 bVect_beam = lv_he8.BoostVector();

//   lv_h3aLab.Boost(-bVect_beam);
//   lv_h6aLab.Boost(-bVect_beam);
//   lv_dAlab.Boost(-bVect_beam);

//   TVector3 v_he4 = lv_he4.Vect();
//   TVector3 v_he8 = lv_he8.Vect();

//   TVector3 v_yMomenta(0,0,0);

//   TVector3 v_zMomenta = v_he4;
//   v_zMomenta = v_he4.Unit();

//   TVector3 v_xMomenta = v_he8;
//   v_xMomenta = v_zMomenta.Cross(v_xMomenta);
//   v_xMomenta = v_xMomenta.Unit();

//   v_yMomenta = v_zMomenta.Cross(v_xMomenta);
//   v_yMomenta = v_yMomenta.Unit();

//   TRotation rot_aLab;
//   rot_aLab.RotateAxes(v_xMomenta,v_yMomenta,v_zMomenta);
//   TLorentzRotation lrot_aLab(rot_aLab);

//   TLorentzVector lv_h3qFrame = lv_h3aLab;
//   lv_h3qFrame.Transform(lrot_aLab.Inverse());

//   TLorentzVector lv_h6qFrame = lv_h6aLab;
//   lv_h6qFrame.Transform(lrot_aLab.Inverse());
//   // cout << lv_h6qFrame.Theta() << "  " << lv_h6qFrame.Phi()*TMath::RadToDeg() << " " << lv_dAlab.T()-lv_dAlab.Mag() << endl;

//   TVector3 bVect_frame6H = lv_h6qFrame.BoostVector();
//   lv_h3_CMH6_rot = lv_h3qFrame;
//   lv_h3_CMH6_rot.Boost(-bVect_frame6H);

//   // if (nh3 ) {
//   //   cout << "Theta from rotation " << lv_h3_CMH6_rot.Theta() << " " << lv_h3_CMH6.Angle(lv_he4_CMH6.Vect()) << endl;
//   //   // cout << he4
//   //   // cout << "Theta from two vec's " << lv_h3_CMH6.Angle(lv_he4_CMH6.Vect()) << " " << lv_h3_CMH6.T()-lv_h3_CMH6.Mag() << " "
//   //   //  << lv_he4_CMH6.T()-lv_he4_CMH6.Mag()  << " " << lv_he4.T()-lv_he4.Mag() << endl;
//   // }
// }

