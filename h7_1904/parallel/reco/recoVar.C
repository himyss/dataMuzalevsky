#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void calculateBeam();
void zerovars();
void neutronEnergy();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);
void neutronID();
void fillND_positions();
void getNeutronXY(Float_t* x, Float_t* y,Float_t dist);


TELoss f8HeSi;

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC;
Float_t wirex1,wirex2,wirey1,wirey2;

Int_t nCsI,nCsI_track;
Float_t aCsI,tCsI;
Float_t aCsI_reco;

Float_t arCsI[16],trCsI[16];

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

Float_t X_C,tX_C,Y_C,tY_C;
Int_t nX_C,nY_C;
//

Float_t fXt,fYt;
Float_t fXf,fYf;
Float_t x1c, y1c, x2c, y2c;
Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;
Float_t sideX,sideY;
Float_t frame1X,frame1Y,frame2X,frame2Y,frame3X,frame3Y;

Int_t flag1,flag2,flag3,flag4,flagCent;
Int_t nh3,nh2,nh1,nhe3_1,nhe3_2,nhe3_3,nhe3_4,neutron;
Int_t nhe4_1,nhe4_2,nhe4_3,nhe4_4;
Int_t nh3_1,nh3_2,nh3_3,nh3_4;
Int_t nAlpha,nhe6;

Float_t e_1,e_2,e_3,e_4;
Float_t centE;
Float_t px,py,pz,pBeam;

Float_t th_he3_1,th_he3_2,th_he3_3,th_he3_4,th_h3,th_4n;
Float_t phi_he3_1,phi_he3_2,phi_he3_3,phi_he3_4,phi_h3;


TLorentzVector h3,he8,d2,he3,h7,h3CM,h4n,hBinary,n4,h3_side,h3_side_CMS,he7;
TLorentzVector he3CM,h7CM; // reaction CMS
TLorentzVector he3CM_H7,h3CM_H7,h7CM_H7,h4nCM_H7,hBinary_CM,hBinary_7H; // reaction CMS
TLorentzVector h_n4h3,h_n4h3_CM,h_n4_he3,h_n4_he3_CM;
TLorentzVector h6,he4,h6CM,h3CM_H6;
TLorentzVector hBinary_aLab;

TLorentzVector he4_c,he6_c,he4_c_cms,he6_c_cms;

TLorentzVector h3_CMbeam,h7_CMbeam,h3_CM_treiman,h3_binary,lv_neutron,lv_neutronCM;
Float_t h3_binary_phi,h3_binary_theta;

// Float_t e_he4_c,e_he4_c_CMS,e_he6_c,e_he6_c_CMS;

Double_t phi,theta;
Double_t momentum,energy,mass;

Float_t thetah7,phih7,phih3,thetah3,phihe3,thetahe3,thetahe8,thetaNeutronCM;
Float_t thetah7CM,phih7CM,phih3CM,thetah3CM,phihe3CM,thetahe3CM,theta4nCM,thetah6CM;
Float_t mh7,eh7,eh3,ehe3,ehe8,eh3_CM,m4n,e4n,e4n_CM,mn4,en4,eNeutron,eNeutronCM;
Float_t mh6;
Float_t v_he3,tof_he3;
Float_t mhe7;

Float_t angle_h3_h7,angle_h3_h7CM,angle_h3_h7CMreaction,angle_he3_h7,angle_he3_he8;
Float_t angle_n4_h3,angle_n4_h7,angle_bin_h3_CM,angle_bin_h3,angle_h7_he8;
Float_t angle_h3Side_he8,angle_he7_he8;
Float_t qReaction;

Int_t coincidence;
Float_t tND,aND,tacND,tND_cal;
Int_t numND;
Float_t ND_time[32],ND_amp[32],ND_tac[32],ND_energy[32],ND_tof[32],ND_energyCM[32],ND_time_cal[32];
TVector3 bVect,bVect_H7,bVect_He7,bVect_H6,bVect_beam,bVect_treiman;

TLorentzVector lv_qMomenta,lv_dAlab,lv_h7aLab,lv_h3aLab,lv_h3qFrame,lv_h7qFrame,lv_h3Frame7h;
TVector3 v_xMomenta,v_yMomenta,v_zMomenta;

Float_t targetTime,diafTime;

Float_t e_4n_3He,e_4n_3H,e_4n_3He_CM,e_4n_3H_CM;

Float_t SSD1[16],SQ20_1[16],tSSD1[16],tSQ20_1[16],SSD_V1[16],tSSD_V1[16];
Float_t SSD2[16],SQ20_2[16],tSSD2[16],tSQ20_2[16],SSD_V2[16],tSSD_V2[16];
Float_t SSD3[16],SQ20_3[16],tSSD3[16],tSQ20_3[16],SSD_V3[16],tSSD_V3[16];
Float_t SSD4[16],SQ20_4[16],tSSD4[16],tSQ20_4[16],SSD_V4[16],tSSD_V4[16];

Float_t av_1,tv_1;
Int_t nv_1;

Float_t av_2,tv_2;
Int_t nv_2;

Float_t av_3,tv_3;
Int_t nv_3;

Float_t av_4,tv_4;
Int_t nv_4;

Float_t timeNDpar1[32],timeNDpar2[32];
Float_t ND_time_position[45],ND_position[45],ND_posTarget[45];
Float_t NDpar[32],zeropar[32];

Float_t x_ND_p,y_ND_p;

TVector3 pos_ND[45];    // in mm
TVector3 pos_ND_target[45];    // in mm

void recoVar(Int_t nRun=0) {

  fillND_positions();


  create_IDs();
  create_cuts();

  readPar("timesND",timeNDpar1,timeNDpar2,32);
  readPar("ND_tac",NDpar,zeropar,32);

  f8HeSi.SetEL(1, 2.321); // density in g/cm3
  f8HeSi.AddEL(14., 28.086, 1);  //Z, mass
  f8HeSi.SetZP(2., 8.);   //alphas, Z, A
  f8HeSi.SetEtab(300000, 250.); // ?, MeV calculate ranges
  f8HeSi.SetDeltaEtab(300);

  TChain *ch = new TChain("tree");
  TString inPutFileName;
  inPutFileName.Form("/media/ivan/data/exp1904/analysed/calcEnergies/h7_nov2020/h7_ct_%d_reco.root",nRun);
  // inPutFileName.Form("/media/ivan/data/exp1904/analysed/calcEnergies/noTargetSelection/h7_ct_%d_reco.root",nRun);

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
  outPutFileName.Form("/media/ivan/data/exp1904/analysed/reco/h7_nov2020/h7_ct_%d_mm.root",nRun);
  // outPutFileName.Form("/media/ivan/data/exp1904/analysed/reco/noTargetSelection/h7_ct_%d_mm_cut.root",nRun);


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

  tw->Branch("tND_cal",&tND_cal,"tND_cal/F");
  tw->Branch("aND",&aND,"aND/F");
  tw->Branch("tND",&tND,"tND/F");
  tw->Branch("tacND",&tacND,"tacND/F");
  tw->Branch("numND",&numND,"numND/I");
  tw->Branch("eNeutron",&eNeutron,"eNeutron/F");
  tw->Branch("eNeutronCM",&eNeutronCM,"eNeutronCM/F");

  tw->Branch("thetaNeutronCM",&thetaNeutronCM,"thetaNeutronCM/F");

  tw->Branch("x_ND_p",&x_ND_p,"x_ND_p/F");
  tw->Branch("y_ND_p",&y_ND_p,"y_ND_p/F");  

  tw->Branch("ND_amp",&ND_amp,"ND_amp[32]/F");
  tw->Branch("ND_time",&ND_time,"ND_time[32]/F");
  tw->Branch("ND_time_cal",&ND_time_cal,"ND_time_cal[32]/F");
  tw->Branch("ND_tac",&ND_tac,"ND_tac[32]/F");
  tw->Branch("ND_energy",&ND_energy,"ND_energy[32]/F");
  tw->Branch("ND_energyCM",&ND_energyCM,"ND_energyCM[32]/F");

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
  tw->Branch("sideX",&sideX,"sideX/F");
  tw->Branch("sideY",&sideY,"sideY/F");

  tw->Branch("frame1X",&frame1X,"frame1X/F");
  tw->Branch("frame2X",&frame2X,"frame2X/F");
  tw->Branch("frame3X",&frame3X,"frame3X/F");
  tw->Branch("frame1Y",&frame1Y,"frame1Y/F");
  tw->Branch("frame2Y",&frame2Y,"frame2Y/F");
  tw->Branch("frame3Y",&frame3Y,"frame3Y/F");

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
  tw->Branch("nh2.",&nh2,"nh2/I");
  tw->Branch("nh1.",&nh1,"nh1/I");
  tw->Branch("nhe3_1.",&nhe3_1,"nhe3_1/I");
  tw->Branch("nhe3_2.",&nhe3_2,"nhe3_2/I");
  tw->Branch("nhe3_3.",&nhe3_3,"nhe3_3/I");
  tw->Branch("nhe3_4.",&nhe3_4,"nhe3_4/I");
  tw->Branch("neutron.",&neutron,"neutron/I");

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
  tw->Branch("thetah7.",&thetah7,"thetah7/F");
  tw->Branch("phih7.",&phih7,"phih7/F");

  tw->Branch("thetah6CM.",&thetah6CM,"thetah6CM/F");
  tw->Branch("thetah7CM.",&thetah7CM,"thetah7CM/F");
  tw->Branch("phih7CM.",&phih7CM,"phih7CM/F");
  tw->Branch("thetahe3CM.",&thetahe3CM,"thetahe3CM/F");
  tw->Branch("phihe3CM.",&phihe3CM,"phihe3CM/F");
  tw->Branch("thetah3CM.",&thetah3CM,"thetah3CM/F");
  tw->Branch("phih3CM.",&phih3CM,"phih3CM/F");
  
  tw->Branch("thetahe3.",&thetahe3,"thetahe3/F");
  tw->Branch("phihe3.",&phihe3,"phihe3/F");

  tw->Branch("thetahe8.",&thetahe8,"thetahe8/F");

  tw->Branch("thetah3.",&thetah3,"thetah3/F");
  tw->Branch("phih3.",&phih3,"phih3/F");


  tw->Branch("mh6.",&mh6,"mh6/F");
  tw->Branch("mh7.",&mh7,"mh7/F");
  tw->Branch("eh7.",&eh7,"eh7/F");
  tw->Branch("en4.",&en4,"en4/F");
  tw->Branch("eh3.",&eh3,"eh3/F");
  tw->Branch("eh3_CM.",&eh3_CM,"eh3_CM/F");
  tw->Branch("ehe3.",&ehe3,"ehe3/F");
  tw->Branch("ehe8.",&ehe8,"ehe8/F");
  tw->Branch("mhe7.",&mhe7,"mhe7/F");

  tw->Branch("px",&px,"px/F");
  tw->Branch("py",&py,"py/F");
  tw->Branch("pz",&pz,"pz/F");
  tw->Branch("pBeam",&pBeam,"pBeam/F");

  tw->Branch("v_he3.",&v_he3,"v_he3/F");
  tw->Branch("tof_he3.",&tof_he3,"tof_he3/F");

  // tw->Branch("qReaction.",&qReaction,"qReaction/F");

  tw->Branch("angle_h7_he8.",&angle_h7_he8,"angle_h7_he8/F");

  tw->Branch("angle_h3_h7.",&angle_h3_h7,"angle_h3_h7/F");
  tw->Branch("angle_h3_h7CM.",&angle_h3_h7CM,"angle_h3_h7CM/F");
  tw->Branch("angle_h3_h7CMreaction.",&angle_h3_h7CMreaction,"angle_h3_h7CMreaction/F");

  tw->Branch("angle_he3_h7.",&angle_he3_h7,"angle_he3_h7/F");
  tw->Branch("angle_he3_he8.",&angle_he3_he8,"angle_he3_he8/F");

  tw->Branch("angle_he7_he8.",&angle_he7_he8,"angle_he7_he8/F");
  tw->Branch("angle_h3Side_he8.",&angle_h3Side_he8,"angle_h3Side_he8/F");

  tw->Branch("m4n.",&m4n,"m4n/F");
  tw->Branch("e4n.",&e4n,"e4n/F");
  tw->Branch("th_4n.",&th_4n,"th_4n/F");

  tw->Branch("e4n_CM.",&e4n_CM,"e4n_CM/F");
  tw->Branch("theta4nCM.",&theta4nCM,"theta4nCM/F");

  tw->Branch("angle_bin_h3_CM.",&angle_bin_h3_CM,"angle_bin_h3_CM/F");
  tw->Branch("angle_bin_h3.",&angle_bin_h3,"angle_bin_h3/F");
  tw->Branch("angle_n4_h7.",&angle_n4_h7,"angle_n4_h7/F");
  tw->Branch("angle_n4_h3.",&angle_n4_h3,"angle_n4_h3/F");

  tw->Branch("e_4n_3H.",&e_4n_3H,"e_4n_3H/F");
  tw->Branch("e_4n_3H_CM.",&e_4n_3H_CM,"e_4n_3H_CM/F");
  tw->Branch("e_4n_3He.",&e_4n_3He,"e_4n_3He/F");
  tw->Branch("e_4n_3He_CM.",&e_4n_3He_CM,"e_4n_3He_CM/F");

  tw->Branch("targetTime.",&targetTime,"targetTime/F");
  tw->Branch("diafTime.",&diafTime,"diafTime/F");

  tw->Branch("he6_c","TLorentzVector",&he6_c);
  tw->Branch("he6_c_cms","TLorentzVector",&he6_c_cms);

  tw->Branch("he4_c","TLorentzVector",&he4_c);
  tw->Branch("he4_c_cms","TLorentzVector",&he4_c_cms);
  tw->Branch("he7","TLorentzVector",&he7);
  tw->Branch("h3_side","TLorentzVector",&h3_side);
  tw->Branch("h3_side_CMS","TLorentzVector",&h3_side_CMS);
  tw->Branch("he8","TLorentzVector",&he8);

  tw->Branch("hBinary","TLorentzVector",&hBinary);
  tw->Branch("hBinary_CM","TLorentzVector",&hBinary_CM);
  tw->Branch("hBinary_aLab","TLorentzVector",&hBinary_aLab);

  tw->Branch("lv_h3qFrame","TLorentzVector",&lv_h3qFrame);
  tw->Branch("lv_h3Frame7h","TLorentzVector",&lv_h3Frame7h);

  tw->Branch("lv_neutron","TLorentzVector",&lv_neutron);
  tw->Branch("lv_neutronCM","lv_neutronCM",&lv_neutronCM);
  

  // tw->Branch("h3_CM_treiman","TLorentzVector",&h3_CM_treiman);
  // tw->Branch("h3_CMbeam","TLorentzVector",&h3_CMbeam);
  // tw->Branch("h7_CMbeam","TLorentzVector",&h7_CMbeam);

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

  tw->Branch("av_1.",&av_1,"av_1/F");
  tw->Branch("tv_1.",&tv_1,"tv_1/F");
  tw->Branch("nv_1.",&nv_1,"nv_1/I");

  tw->Branch("av_2.",&av_2,"av_2/F");
  tw->Branch("tv_2.",&tv_2,"tv_2/F");
  tw->Branch("nv_2.",&nv_2,"nv_2/I");

  tw->Branch("av_3.",&av_3,"av_3/F");
  tw->Branch("tv_3.",&tv_3,"tv_3/F");
  tw->Branch("nv_3.",&nv_3,"nv_3/I");

  tw->Branch("av_4.",&av_4,"av_4/F");
  tw->Branch("tv_4.",&tv_4,"tv_4/F");
  tw->Branch("nv_4.",&nv_4,"nv_4/I");

  // input options
  d2.SetPxPyPzE(0.,0.,0.,1.875612);

  Float_t xCent,yCent;
  xCent = 0.467;
  yCent = 0.026;


  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry = 0; nentry<10000;nentry++) {
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);
    
    if ( ((fXt-xCent)*(fXt-xCent) + (fYt-yCent)*(fYt-yCent))>9.5*9.5 ) continue;

    zerovars();

    if (flag1) {
      sideX = x1t;
      sideY = y1t;
    }

    if (flag2) {
      sideX = x2t;
      sideY = y2t;
    }

    if (flag3) {
      sideX = x3t;
      sideY = y3t;
    }

    if (flag4) {
      sideX = x4t;
      sideY = y4t;
    }

    calculateBeam();

    TLorentzVector summVect = he8 + d2;
    bVect = summVect.BoostVector();

    if (nh3_1 || nh3_2 || nh3_3 || nh3_4) { // reco He7

      if (nh3_1) {
        energy = e_1/1000.;
        theta = th_he3_1;
        phi = phi_he3_1;
      } 

      if (nh3_2) {
        energy = e_2/1000.;
        theta = th_he3_2;
        phi = phi_he3_2;
      } 

      if (nh3_3) {
        energy = e_3/1000.;
        theta = th_he3_3;
        phi = phi_he3_3;
      } 

      if (nh3_4) {
        energy = e_4/1000.;
        theta = th_he3_4;
        phi = phi_he3_4;
      }

      mass = 2.80892;  //MeV
      momentum = sqrt(energy*energy + 2*energy*mass);
      h3_side.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

      he7 = he8 + d2 + (-h3_side);
      mhe7 = sqrt(he7.E()*he7.E() - he7.Px()*he7.Px() - he7.Py()*he7.Py() - he7.Pz()*he7.Pz());

      bVect_He7 = he7.BoostVector();

      h3_side_CMS = h3_side;
      h3_side_CMS.Boost(-bVect);

      angle_h3Side_he8 = he8.Angle(h3_side.Vect())*TMath::RadToDeg();
      angle_he7_he8 = he8.Angle(he7.Vect())*TMath::RadToDeg();

    }


    if (nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )) { //  reco 6H

      if (nhe4_1 && flag1) {
        energy = e_1/1000.;
        theta = th_he3_1;
        phi = phi_he3_1;       
      }

      if (nhe4_2 && flag2) {
        energy = e_2/1000.;
        theta = th_he3_2;
        phi = phi_he3_2;
      }

      if (nhe4_3 && flag3) {
        energy = e_3/1000.;
        theta = th_he3_3;
        phi = phi_he3_3;            
      }

      if (nhe4_4 && flag4) {
        energy = e_4/1000.;
        theta = th_he3_4;
        phi = phi_he3_4;        
      }

      mass = 3.727378;  //MeV
      momentum = sqrt(energy*energy + 2*energy*mass);

      he4.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);
      h6 = he8 + d2 + (-he4);
      mh6 = sqrt(h6.E()*h6.E() - h6.Px()*h6.Px() - h6.Py()*h6.Py() - h6.Pz()*h6.Pz());

      h6CM = h6;
      bVect_H6 = h6.BoostVector();

      h6CM.Boost(-bVect); 
      thetah6CM = h6CM.Theta()*TMath::RadToDeg();

      energy = centE/1000.;
      mass = 2.80892; //GeV

      // TVector3 dir;
      // dir.SetXYZ(xCent,yCent,zCent);
      // phi = dir.Phi();
      // theta = dir.Theta();
      theta = th_h3;
      phi = phi_h3;

      momentum = sqrt(energy*energy + 2*energy*mass);

      h3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);
      // h3.SetPtEtaPhiM(momentum, theta, phi, mass);

      thetah3 = h3.Theta()*TMath::RadToDeg();
      phih3 = h3.Phi()*TMath::RadToDeg();
      eh3 = h3.T() - mass;

    }


    if (nh3 && flagCent && ( ( nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4)  )) { // reco 7H

      if (flag1 && nhe3_1 && !nhe3_2 && !nhe3_3 && !nhe3_4 ) {
        // if (e_1>20 || centE<40) continue;
        energy = e_1/1000.;
        theta = th_he3_1;
        phi = phi_he3_1;
      } 

      if (flag2 && nhe3_2 && !nhe3_1 && !nhe3_3 && !nhe3_4 ) {
        // if (n20_2==0 || n20_2==1) continue;
        // if (e_2>20 || centE<40) continue;
        energy = e_2/1000.;
        theta = th_he3_2;
        phi = phi_he3_2;
      } 

      if (flag3 && nhe3_3 && !nhe3_1 && !nhe3_2 && !nhe3_4) {
        // if (e_3>20 || centE<40) continue;
        energy = e_3/1000.;
        theta = th_he3_3;
        phi = phi_he3_3;
      } 

      if (flag4 && nhe3_4 && !nhe3_2 && !nhe3_3 && !nhe3_1) {
        // if (e_4>20 || centE<40) continue;
        energy = e_4/1000.;
        theta = th_he3_4;
        phi = phi_he3_4;
      } 

      mass = 2.808391;  //MeV

      momentum = sqrt(energy*energy + 2*energy*mass);

      // he3.SetPtEtaPhiM(momentum, theta, phi, mass);
      he3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

      thetahe3 = he3.Theta()*TMath::RadToDeg();
      phihe3 = he3.Phi()*TMath::RadToDeg();
      ehe3 = he3.T() - mass;
      v_he3 = sqrt(1-(mass/he3.T()*(mass/he3.T())) )*299.792458; // mm per nanosec
      tof_he3 = sqrt( (x1t - fXt)*(x1t - fXt) + (y1t - fYt)*(y1t - fYt) )/(v_he3);

      h7 = he8 + d2 + (-he3);
      bVect_H7 = h7.BoostVector();

      thetah7 = h7.Theta()*TMath::RadToDeg();
      phih7 = h7.Phi()*TMath::RadToDeg();
      mh7 = sqrt(h7.E()*h7.E() - h7.Px()*h7.Px() - h7.Py()*h7.Py() - h7.Pz()*h7.Pz());
      eh7 = h7.E() - mh7;

      // CM
      he3CM = he3;
      he3CM.Boost(-bVect); 
      thetahe3CM = he3CM.Theta()*TMath::RadToDeg();
      phihe3CM = he3CM.Phi()*TMath::RadToDeg();      

      h7CM = h7;
      h7CM.Boost(-bVect); 
      thetah7CM = h7CM.Theta()*TMath::RadToDeg();
      phih7CM = h7CM.Phi()*TMath::RadToDeg();

      h7CM_H7 = h7;
      h7CM_H7.Boost(-bVect_H7);
      // cout << h7CM_H7.T();


      energy = centE/1000.;
      mass = 2.80892; //GeV

      // TVector3 dir;
      // dir.SetXYZ(xCent,yCent,zCent);
      // phi = dir.Phi();
      // theta = dir.Theta();
      theta = th_h3;
      phi = phi_h3;

      momentum = sqrt(energy*energy + 2*energy*mass);

      h3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);
      // h3.SetPtEtaPhiM(momentum, theta, phi, mass);

      thetah3 = h3.Theta()*TMath::RadToDeg();
      phih3 = h3.Phi()*TMath::RadToDeg();
      eh3 = h3.T() - mass;

      h3CM_H7 = h3;
      h3CM_H7.Boost(-bVect_H7);
      eh3_CM = h3CM_H7.T() - mass;
      thetah3CM = h3CM_H7.Theta()*TMath::RadToDeg();
      phih3CM = h3CM_H7.Phi()*TMath::RadToDeg();


      h4n = he8 + d2 + (-he3) + (-h3);
      // m4n = sqrt(h4n.E()*h4n.E() - h4n.Px()*h4n.Px() - h4n.Py()*h4n.Py() - h4n.Pz()*h4n.Pz());
      m4n = h4n.Mag();
      e4n = h4n.E() - m4n;
      // e4n = h4n.Mag() - m4n;
      th_4n = h4n.Theta()*TMath::RadToDeg();

      h4nCM_H7 = h4n;
      h4nCM_H7.Boost(-bVect_H7);
      e4n_CM = h4nCM_H7.T() - m4n;
      theta4nCM = h4nCM_H7.Theta()*TMath::RadToDeg();

      h_n4h3 = h4n - h3;
      h_n4h3_CM = h_n4h3;
      h_n4h3_CM.Boost(-bVect_H7);

      e_4n_3H = sqrt(h_n4h3.Px()*h_n4h3.Px() + h_n4h3.Py()*h_n4h3.Py() + h_n4h3.Pz()*h_n4h3.Pz());
      e_4n_3H = e_4n_3H/((2*2.80892*m4n)/(2.80892+m4n));
      e_4n_3H_CM = h_n4h3_CM.Px()*h_n4h3_CM.Px() + h_n4h3_CM.Py()*h_n4h3_CM.Py() + h_n4h3_CM.Pz()*h_n4h3_CM.Pz();
      e_4n_3H_CM = e_4n_3H_CM/((2*2.80892*m4n)/(2.80892+m4n));

      h_n4_he3 = h4n - he3;
      h_n4_he3_CM = h_n4_he3;
      h_n4_he3_CM.Boost(-bVect_H7);

      e_4n_3He = sqrt(h_n4_he3.Px()*h_n4_he3.Px() + h_n4_he3.Py()*h_n4_he3.Py() + h_n4_he3.Pz()*h_n4_he3.Pz());
      e_4n_3He = e_4n_3He/((2*2.808391*m4n)/(2.808391+m4n));
      e_4n_3He_CM = h_n4_he3_CM.Px()*h_n4_he3_CM.Px() + h_n4_he3_CM.Py()*h_n4_he3_CM.Py() + h_n4_he3_CM.Pz()*h_n4_he3_CM.Pz();
      e_4n_3He_CM = e_4n_3He_CM/((2*2.808391*m4n)/(2.808391+m4n));
  
    }
    
    if (nh3 && ( (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) || (nhe4_1 || nhe4_2 || nhe4_3 || nhe4_4) ) ) {
      angle_h3_h7CM = h7CM_H7.Angle(h3CM_H7.Vect())*TMath::RadToDeg();
      angle_h3_h7 = h7.Angle(h3.Vect())*TMath::RadToDeg(); 
      angle_h3_h7CMreaction = h7CM.Angle(h3CM.Vect())*TMath::RadToDeg(); 
      angle_he3_h7 = h7.Angle(he3.Vect())*TMath::RadToDeg();
      angle_he3_he8 = he8.Angle(he3.Vect())*TMath::RadToDeg();

      angle_n4_h7 = h7.Angle(h4n.Vect())*TMath::RadToDeg();
      angle_n4_h3 = h3.Angle(h4n.Vect())*TMath::RadToDeg();

      // angle_bin_h3_CM = h3CM_H7.Angle(hBinary.Vect())*TMath::RadToDeg();
      // angle_bin_h3 = h3.Angle(hBinary.Vect())*TMath::RadToDeg();

      angle_h7_he8 = he8.Angle(h7.Vect())*TMath::RadToDeg();
    }

    if (nhe6 && (nh3_1 || nh3_2 || nh3_3 || nh3_4) ) {

      energy = centE/1000.;
      mass = 5.605535; //GeV

      theta = th_h3;
      phi = phi_h3;
      momentum = sqrt(energy*energy + 2*energy*mass);

      he6_c.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);
    
      he6_c_cms = he6_c;
      he6_c_cms.Boost(-bVect_He7);

    }

    if (nAlpha && (nh3_1 || nh3_2 || nh3_3 || nh3_4) ) {

      he4_c.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);
    
      he4_c_cms = he4_c;
      he4_c_cms.Boost(-bVect_He7);

      h6 = he8 + d2 + (-he4);
      mh6 = sqrt(h6.E()*h6.E() - h6.Px()*h6.Px() - h6.Py()*h6.Py() - h6.Pz()*h6.Pz());

      h6CM = h6;
      bVect_H6 = h6.BoostVector();

      mass = 2.80892; //GeV
      h3CM_H6 = h3_side;
      h3CM_H6.Boost(-bVect_H6);
      eh3_CM = h3CM_H6.T() - mass;

    }

    if (nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )) {

      mass = 2.80892; //GeV
      h3CM_H6 = h3;
      h3CM_H6.Boost(-bVect_H6);
      eh3_CM = h3CM_H6.T() - mass;

    }

    if (nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )) { // treiman jang
      lv_h3aLab = h3;
      lv_h7aLab = h7;
      lv_dAlab = d2;

      bVect_beam = he8.BoostVector();

      lv_h3aLab.Boost(-bVect_beam);
      lv_h7aLab.Boost(-bVect_beam);
      lv_dAlab.Boost(-bVect_beam);

      TVector3 v_h7aLab = lv_h7aLab.Vect();
      TVector3 v_dAlab = lv_dAlab.Vect();

      TVector3 v_yMomenta(0,0,0);

      v_zMomenta = v_h7aLab;
      v_zMomenta = v_h7aLab.Unit();

      v_xMomenta = v_dAlab;
      v_xMomenta = v_zMomenta.Cross(v_xMomenta);
      v_xMomenta = v_xMomenta.Unit();

      v_yMomenta = v_zMomenta.Cross(v_xMomenta);
      v_yMomenta = v_yMomenta.Unit();
      
      TRotation rot_aLab;
      rot_aLab.RotateAxes(v_xMomenta,v_yMomenta,v_zMomenta);
      TLorentzRotation lrot_aLab(rot_aLab);

      lv_h3qFrame = lv_h3aLab;
      lv_h3qFrame.Transform(lrot_aLab.Inverse());

      lv_h7qFrame = lv_h7aLab;
      lv_h7qFrame.Transform(lrot_aLab.Inverse());

      TVector3 bVect_frame7H = lv_h7qFrame.BoostVector();
      lv_h3Frame7h = lv_h3qFrame;
      lv_h3Frame7h.Boost(-bVect_frame7H);

    }

    neutronID();

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
  phi = dir.Phi();
  theta = dir.Theta();

  Double_t len = dir.Mag();

  mass = 7.482538;

  Double_t velocity = 12320./(tF5-tF3 + 68.475);
  Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  Double_t kinEnergy = mass*((1/beta) - 1);

  // cout << "F1 and F2 " << tF5 << " " << tF3 << endl;
  // cout << tF5-tF3 + 68.475 << " " << 1000*kinEnergy << endl;

  kinEnergy =  f8HeSi.GetE(1000*kinEnergy, 540.)/1000.;
  // kinEnergy = kinEnergy*0.95;
  ehe8 = kinEnergy;

  targetTime = tF5 + 469./velocity;
  diafTime = tF5 + 365./velocity;
  Float_t velocityCorr = 299.792458*sqrt( (1-1/((kinEnergy/mass+1)*(kinEnergy/mass+1))) );
  targetTime += 469./velocityCorr;
  diafTime += 365./velocityCorr;

  // cout << velocityCorr << endl;

  pBeam = sqrt(kinEnergy*kinEnergy + 2*kinEnergy*mass);
  pBeam = TMath::Abs(pBeam);

  he8.SetXYZM(pBeam*TMath::Sin(theta)*TMath::Cos(phi), pBeam*TMath::Sin(theta)*TMath::Sin(phi), pBeam*TMath::Cos(theta) ,mass);
  thetahe8 = he8.Theta();

  px = he8.Px();
  py = he8.Py();
  pz = he8.Pz();

}

void zerovars() {

  aND = -1;
  tND = -100000;
  tND_cal = -100000;
  numND = -1;
  tacND = -1000;

  targetTime = 0;
  diafTime = 0;

  e_4n_3H = -10;
  e_4n_3H_CM = -10;
  e_4n_3He = -10;
  e_4n_3He_CM = -10;

  px = -1000;
  py = -1000;
  pz = -1000;
  pBeam = -1000;

  v_he3 = 0;
  tof_he3 = 0;

  sideY = 0;
  sideX = 0;

  thetahe8 = -100;
  thetah7 = -10.;
  phih7 = -100.;
  thetah3 = -1000.;
  phih3 = -500.;
  angle_h3_h7 = -100;

  angle_bin_h3_CM = -100;
  angle_bin_h3 = -100;;
  angle_n4_h7 = -100;
  angle_n4_h3 = -100;
  angle_h7_he8 = -100;

  angle_h3Side_he8 = -100;
  angle_he7_he8 = -100;

  theta4nCM = -10;
  thetah7CM = -10.;
  thetah6CM = -10.;
  phih7CM = -100.;
  thetah3CM = -1000.;
  phih3CM = -10000.;
  angle_h3_h7CM = -100000;
  angle_h3_h7CMreaction = -100000;
  qReaction = -100.;
  angle_he3_h7 = -100;
  angle_he3_he8 = -100;
  th_4n = -100;


  mhe7 = -100;
  m4n = -1.;
  e4n = -1.;
  e4n_CM = -1.;
  mh7 = -1.;
  mh6 = -1.;
  eh7 = -1.;
  en4 = -1.;
  eh3 = -1.;
  eh3_CM = -1.;
  ehe3 = -1.;

  he7.SetXYZT(0,0,0,0);
  h7.SetXYZT(0,0,0,0);
  h6.SetXYZT(0,0,0,0);
  h3.SetXYZT(0,0,0,0);
  he3.SetXYZT(0,0,0,0);
  he8.SetXYZT(0,0,0,0);
  h7CM.SetXYZT(0,0,0,0);
  h3CM.SetXYZT(0,0,0,0);
  he3CM.SetXYZT(0,0,0,0);  
  bVect.SetXYZ(0,0,0);

  h3CM_H6.SetXYZT(0,0,0,0);  

  bVect_H7.SetXYZ(0,0,0);
  h3CM_H7.SetXYZT(0,0,0,0);
  he3CM_H7.SetXYZT(0,0,0,0);
  h7CM_H7.SetXYZT(0,0,0,0);

  he4_c.SetXYZT(0,0,0,0);
  he4_c_cms.SetXYZT(0,0,0,0);

  he6_c.SetXYZT(0,0,0,0);
  he6_c_cms.SetXYZT(0,0,0,0);

  he7.SetXYZT(0,0,0,0);

  h3_side.SetXYZT(0,0,0,0);
  h3_side_CMS.SetXYZT(0,0,0,0);

  h3_CM_treiman.SetXYZT(0,0,0,0);
  h3_CMbeam.SetXYZT(0,0,0,0);
  h7_CMbeam.SetXYZT(0,0,0,0);

  hBinary.SetXYZT(0,0,0,0);
  hBinary_CM.SetXYZT(0,0,0,0);
  hBinary_7H.SetXYZT(0,0,0,0);
  hBinary_aLab.SetXYZT(0,0,0,0);
  lv_h3qFrame.SetXYZT(0,0,0,0);
  lv_h7qFrame.SetXYZT(0,0,0,0);
  lv_h3Frame7h.SetXYZT(0,0,0,0);

  lv_neutron.SetXYZT(0,0,0,0);
  lv_neutronCM.SetXYZT(0,0,0,0);

  x_ND_p = -10000;
  y_ND_p = -10000;

  neutron = 0;
  eNeutron = -1;
  eNeutronCM = -1;
  thetaNeutronCM = -1;

  for (Int_t i = 0;i<32;i++) {
    ND_energy[i] = -1;
    ND_energyCM[i] = -1;
    ND_tof[i] = ND_time[i];
    ND_time_cal[i] = -1;
  }
  numND = -1;

}

void neutronID() {

  Int_t multiplicity = 0;

  for (Int_t i=0;i<32;i++) {

    // ND_tac[i] = ND_tac[i]+NDpar[i];
    ND_time_cal[i] = ND_time[i]*0.125 - timeNDpar1[i] + ND_time_position[i];
    // ND_time_cal[i] = ND_time[i]*0.125 - timeNDpar1[i] + (targetTime-diafTime) + ND_time_position[i];
    if (ND_time[i]>0 && ND_amp[i]>0) {
      multiplicity++;
      numND = i;
    }
  }
  if (multiplicity==1) {
    aND = ND_amp[numND];
    tND = ND_time[numND];
    tND_cal = ND_time[numND]*0.125 - timeNDpar1[numND] + ND_time_position[numND];
  }
  else {
    numND = -1;
  }

  mass = 0.939565;
  /*for (Int_t i=0;i<32;i++) {
    if (ND_time[i]>0) {
      ND_time[i] = ND_time[i]*0.125 - timeNDpar1[i] + 290./30.;
    }
  }*/

  for (Int_t i=0;i<32;i++) {
    // if ( neutron ) {
    if (cutNeutron->IsInside(ND_amp[i] , ND_tac[i]) ) {
      neutron++;
      numND = i;
      
      Double_t velocity = ND_posTarget[i]/(ND_time_cal[i]-targetTime);
      // Double_t velocity = ND_posTarget[i]/(ND_time_cal[i]);
      // Double_t velocity = 2700./(40.);
      Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
      ND_energy[i] = mass*((1/beta) - 1);
      eNeutron = ND_energy[i];

      getNeutronXY(&x_ND_p,&y_ND_p,323);
      // cout << ND_time[i]-targetTime << " " << ND_energy[i] << endl;

      if (nh3 && flagCent && ( ( nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4)  )) {
        momentum = sqrt(ND_energy[i]*ND_energy[i] + 2*ND_energy[i]*mass);
        // lv_neutron.SetXYZM(0, 0, momentum ,mass);

        lv_neutronCM = lv_neutron;
        lv_neutronCM.Boost(-bVect_H7);
        ND_energyCM[i] = lv_neutronCM.T() - mass;
        eNeutronCM = ND_energyCM[i];
        thetaNeutronCM = lv_neutronCM.Theta()*TMath::RadToDeg();
      }

      if (nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )) {
        momentum = sqrt(ND_energy[i]*ND_energy[i] + 2*ND_energy[i]*mass);
        // lv_neutron.SetXYZM(0, 0, momentum ,mass);

        lv_neutronCM = lv_neutron;
        lv_neutronCM.Boost(-bVect_H6);
        ND_energyCM[i] = lv_neutronCM.T() - mass;
        eNeutronCM = ND_energyCM[i];
        thetaNeutronCM = lv_neutronCM.Theta()*TMath::RadToDeg();
      }
    
    }

  }

}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/ivan/work/macro/h7_1904/parameters/" + fileName + ".cal";
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
      // cout << ND_time_position[i] << " " << ND_position[i] << endl;
  }
}

void getNeutronXY(Float_t* x, Float_t* y,Float_t dist) {

  Float_t x_ND = pos_ND[numND].Px();
  Float_t y_ND = pos_ND[numND].Py();
  Float_t z_ND = pos_ND[numND].Pz();

  TVector3 dir;
  dir.SetXYZ(x_ND-fXt,y_ND-fYt,z_ND);

  phi = dir.Phi();
  theta = dir.Theta();

  Double_t len = dir.Mag();

  mass = 0.939565;

  Float_t pNeutron = sqrt(eNeutron*eNeutron + 2*eNeutron*mass);
  pNeutron = TMath::Abs(pNeutron);

  lv_neutron.SetXYZM(pNeutron*TMath::Sin(theta)*TMath::Cos(phi), pNeutron*TMath::Sin(theta)*TMath::Sin(phi), pNeutron*TMath::Cos(theta) ,mass);

  *x = fXt + (x_ND-fXt)*dist/z_ND;
  *y = fYt + (y_ND-fYt)*dist/z_ND;

}