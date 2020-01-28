//outtree vars
Int_t trigger_in; 

Float_t tF5_in,F5_in,tF3_in,F3_in;

Float_t tMWPC_in;
Float_t wirex1_in,wirex2_in,wirey1_in,wirey2_in;

Int_t nCsI_in;
Float_t aCsI_in,tCsI_in;

Float_t a20_1_in,t20_1_in,a20_1_un_in;
Int_t n20_1_in;

Float_t a1_1_in,t1_1_in;
Int_t n1_1_in;

Float_t a20_2_in,t20_2_in,a20_2_un_in;
Int_t n20_2_in;

Float_t a1_2_in,t1_2_in;
Int_t n1_2_in;

Float_t a20_3_in,t20_3_in,a20_3_un_in;
Int_t n20_3_in;

Float_t a1_3_in,t1_3_in;
Int_t n1_3_in;

Float_t a20_4_in,t20_4_in,a20_4_un_in;
Int_t n20_4_in;

Float_t a1_4_in,t1_4_in;
Int_t n1_4_in;

Float_t X_C_in,tX_C_in,Y_C_in,tY_C_in;
Int_t nX_C_in,nY_C_in;
//

Float_t fXt_in,fYt_in;
Float_t x1c_in, y1c_in, x2c_in, y2c_in;
Float_t frame1X_in,frame1Y_in,frame2X_in,frame2Y_in,frame3X_in,frame3Y_in;
Float_t x1t_in,y1t_in,x2t_in,y2t_in,x3t_in,y3t_in,x4t_in,y4t_in,xCt_in,yCt_in;

Int_t flag1_in,flag2_in,flag3_in,flag4_in,flagCent_in;
Int_t nh3_in,nhe3_1_in,nhe3_2_in,nhe3_3_in,nhe3_4_in;

Float_t e_1_in,e_2_in,e_3_in,e_4_in;
Float_t centE_in;

Float_t th_he3_1_in,th_he3_2_in,th_he3_3_in,th_he3_4_in,th_h3_in,th_he3_in;
Float_t phi_he3_1_in,phi_he3_2_in,phi_he3_3_in,phi_he3_4_in,phi_h3_in;


TLorentzVector h3_in,he8_in,d2_in,he3_in,h7_in,h3CM_in;
TLorentzVector he3CM_in,h7CM_in; // reaction CMS
TLorentzVector he3CM_H7_in,h3CM_H7_in,h7CM_H7_in; // reaction CMS

Double_t phi_in,theta_in;
Double_t momentum_in,energy_in,mass_in;
Float_t pBeam_in;

Float_t thetah7_in,phih7_in,phih3_in,thetah3_in,phihe3_in,thetahe3_in,thetahe8_in,phihe8_in;
Float_t thetah7CM_in,phih7CM_in,phih3CM_in,thetah3CM_in,phihe3CM_in,thetahe3CM_in;
Float_t mh7_in,eh7_in,eh3_in,ehe3_in,ehe8_in,eh3_CM_in,ehe8_ToF_in;

Float_t angle_h3_h7_in,angle_h3_h7CM_in,angle_h3_h7CMreaction_in,angle_he3_h7_in,angle_he3_he8_in,angle_he3_he8CM_in;
Float_t qReaction_in;

Int_t coincidence_in;

TVector3 bVect_in,bVect_H7_in;

void testE(){

  TChain *t = new TChain("tree");
  t->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_mm_secondVol.root");
  t->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_firstVol_mm.root");


  t->SetBranchAddress("trigger.",&trigger_in);

  t->SetBranchAddress("F5.",&F5_in);
  t->SetBranchAddress("tF5.",&tF5_in);
  t->SetBranchAddress("F3.",&F3_in);
  t->SetBranchAddress("tF3.",&tF3_in);

  t->SetBranchAddress("tMWPC.",&tMWPC_in);
  t->SetBranchAddress("wirex1.",&wirex1_in);
  t->SetBranchAddress("wirex2.",&wirex2_in);
  t->SetBranchAddress("wirey1.",&wirey1_in);
  t->SetBranchAddress("wirey2.",&wirey2_in);
 
  t->SetBranchAddress("aCsI.",&aCsI_in);
  t->SetBranchAddress("tCsI.",&tCsI_in);
  t->SetBranchAddress("nCsI.",&nCsI_in);

  t->SetBranchAddress("X_C.",&X_C_in);
  t->SetBranchAddress("nX_C.",&nX_C_in);
  t->SetBranchAddress("tX_C.",&tX_C_in);
  t->SetBranchAddress("Y_C.",&Y_C_in);
  t->SetBranchAddress("tY_C.",&tY_C_in);
  t->SetBranchAddress("nY_C.",&nY_C_in);

  t->SetBranchAddress("x1c.",&x1c_in);
  t->SetBranchAddress("y1c.",&y1c_in);
  t->SetBranchAddress("x2c.",&x2c_in);
  t->SetBranchAddress("y2c.",&y2c_in); 
  t->SetBranchAddress("fXt.",&fXt_in);
  t->SetBranchAddress("fYt.",&fYt_in); 

  t->SetBranchAddress("frame1X",&frame1X_in);
  t->SetBranchAddress("frame2X",&frame2X_in);
  t->SetBranchAddress("frame3X",&frame3X_in);
  t->SetBranchAddress("frame1Y",&frame1Y_in);
  t->SetBranchAddress("frame2Y",&frame2Y_in);
  t->SetBranchAddress("frame3Y",&frame3Y_in);

  t->SetBranchAddress("x1t",&x1t_in);
  t->SetBranchAddress("x2t",&x2t_in);
  t->SetBranchAddress("x3t",&x3t_in);
  t->SetBranchAddress("x4t",&x4t_in);
  t->SetBranchAddress("y1t",&y1t_in);
  t->SetBranchAddress("y2t",&y2t_in);
  t->SetBranchAddress("y3t",&y3t_in);
  t->SetBranchAddress("y4t",&y4t_in);
  t->SetBranchAddress("xCt",&xCt_in);
  t->SetBranchAddress("yCt",&yCt_in);

  t->SetBranchAddress("a20_1.",&a20_1_in);
  t->SetBranchAddress("a20_1_un.",&a20_1_un_in);
  t->SetBranchAddress("t20_1.",&t20_1_in);
  t->SetBranchAddress("n20_1.",&n20_1_in);

  t->SetBranchAddress("a1_1.",&a1_1_in);
  t->SetBranchAddress("t1_1.",&t1_1_in);
  t->SetBranchAddress("n1_1.",&n1_1_in);

  t->SetBranchAddress("a20_2.",&a20_2_in);
  t->SetBranchAddress("a20_2_un.",&a20_2_un_in);
  t->SetBranchAddress("t20_2.",&t20_2_in);
  t->SetBranchAddress("n20_2.",&n20_2_in);

  t->SetBranchAddress("a1_2.",&a1_2_in);
  t->SetBranchAddress("t1_2.",&t1_2_in);
  t->SetBranchAddress("n1_2.",&n1_2_in);

  t->SetBranchAddress("a20_3.",&a20_3_in);
  t->SetBranchAddress("a20_3_un.",&a20_3_un_in);
  t->SetBranchAddress("t20_3.",&t20_3_in);
  t->SetBranchAddress("n20_3.",&n20_3_in);

  t->SetBranchAddress("a1_3.",&a1_3_in);
  t->SetBranchAddress("t1_3.",&t1_3_in);
  t->SetBranchAddress("n1_3.",&n1_3_in);

  t->SetBranchAddress("a20_4.",&a20_4_in);
  t->SetBranchAddress("a20_4_un.",&a20_4_un_in);
  t->SetBranchAddress("t20_4.",&t20_4_in);
  t->SetBranchAddress("n20_4.",&n20_4_in);

  t->SetBranchAddress("a1_4.",&a1_4_in);
  t->SetBranchAddress("t1_4.",&t1_4_in);
  t->SetBranchAddress("n1_4.",&n1_4_in);

  t->SetBranchAddress("flag1.",&flag1_in);
  t->SetBranchAddress("flag2.",&flag2_in);
  t->SetBranchAddress("flag3.",&flag3_in);
  t->SetBranchAddress("flag4.",&flag4_in);
  t->SetBranchAddress("flagCent.",&flagCent_in);

  t->SetBranchAddress("nh3.",&nh3_in);
  t->SetBranchAddress("nhe3_1.",&nhe3_1_in);
  t->SetBranchAddress("nhe3_2.",&nhe3_2_in);
  t->SetBranchAddress("nhe3_3.",&nhe3_3_in);
  t->SetBranchAddress("nhe3_4.",&nhe3_4_in);

  t->SetBranchAddress("th_he3_1.",&th_he3_1_in);
  t->SetBranchAddress("th_he3_2.",&th_he3_2_in);
  t->SetBranchAddress("th_he3_3.",&th_he3_3_in);
  t->SetBranchAddress("th_he3_4.",&th_he3_4_in);
  t->SetBranchAddress("th_he3.",&th_he3_in);

  t->SetBranchAddress("th_h3.",&th_h3_in);

  t->SetBranchAddress("phi_he3_1.",&phi_he3_1_in);
  t->SetBranchAddress("phi_he3_2.",&phi_he3_2_in);
  t->SetBranchAddress("phi_he3_3.",&phi_he3_3_in);
  t->SetBranchAddress("phi_he3_4.",&phi_he3_4_in);
  t->SetBranchAddress("phi_h3.",&phi_h3_in);

  t->SetBranchAddress("e_1.",&e_1_in);
  t->SetBranchAddress("e_2.",&e_2_in);
  t->SetBranchAddress("e_3.",&e_3_in);
  t->SetBranchAddress("e_4.",&e_4_in);

  t->SetBranchAddress("pBeam.",&pBeam_in);

  t->SetBranchAddress("centE.",&centE_in);
  t->SetBranchAddress("thetah7.",&thetah7_in);
  t->SetBranchAddress("phih7.",&phih7_in);

  t->SetBranchAddress("thetah7CM.",&thetah7CM_in);
  t->SetBranchAddress("phih7CM.",&phih7CM_in);
  t->SetBranchAddress("thetahe3CM.",&thetahe3CM_in);
  t->SetBranchAddress("phihe3CM.",&phihe3CM_in);
  t->SetBranchAddress("thetah3CM.",&thetah3CM_in);
  t->SetBranchAddress("phih3CM.",&phih3CM_in);
  
  t->SetBranchAddress("thetahe3.",&thetahe3_in);
  t->SetBranchAddress("phihe3.",&phihe3_in);

  t->SetBranchAddress("thetah3.",&thetah3_in);
  t->SetBranchAddress("phih3.",&phih3_in);

  t->SetBranchAddress("mh7.",&mh7_in);
  t->SetBranchAddress("eh7.",&eh7_in);
  t->SetBranchAddress("eh3.",&eh3_in);
  t->SetBranchAddress("eh3_CM.",&eh3_CM_in);
  t->SetBranchAddress("ehe3.",&ehe3_in);
  t->SetBranchAddress("ehe8.",&ehe8_in);
  t->SetBranchAddress("ehe8_ToF.",&ehe8_ToF_in);

  // t->SetBranchAddress("qReaction.",&qReaction,"qReaction/F");

  t->SetBranchAddress("angle_h3_h7.",&angle_h3_h7_in);
  t->SetBranchAddress("angle_h3_h7CM.",&angle_h3_h7CM_in);
  t->SetBranchAddress("angle_h3_h7CMreaction.",&angle_h3_h7CMreaction_in);

  t->SetBranchAddress("angle_he3_h7.",&angle_he3_h7_in);
  t->SetBranchAddress("angle_he3_he8.",&angle_he3_he8_in);
  t->SetBranchAddress("angle_he3_he8CM.",&angle_he3_he8CM_in);

  t->SetBranchAddress("thetahe8.",&thetahe8_in);
  t->SetBranchAddress("phihe8.",&phihe8_in);

  TFile *fout = new TFile("/media/ivan/data/exp1906/be10/analysed/novPars/reco/reserved/be10_ct_mm_initial.root", "RECREATE");  
  TTree *tout = new TTree("intree", "initial data");

  tout->Branch("trigger_in.",&trigger_in,"trigger_in/I");

  tout->Branch("F5_in.",&F5_in,"F5_in/F");
  tout->Branch("tF5_in.",&tF5_in,"tF5_in/F");
  tout->Branch("F3_in.",&F3_in,"F3_in/F");
  tout->Branch("tF3_in.",&tF3_in,"tF3_in/F");

  tout->Branch("tMWPC_in.",&tMWPC_in,"tMWPC_in/F");
  tout->Branch("wirex1_in.",&wirex1_in,"wirex1_in/F");
  tout->Branch("wirex2_in.",&wirex2_in,"wirex2_in/F");
  tout->Branch("wirey1_in.",&wirey1_in,"wirey1_in/F");
  tout->Branch("wirey2_in.",&wirey2_in,"wirey2_in/F");
 
  tout->Branch("aCsI_in.",&aCsI_in,"aCsI_in/F");
  tout->Branch("tCsI_in.",&tCsI_in,"tCsI_in/F");
  tout->Branch("nCsI_in.",&nCsI_in,"nCsI_in/I");

  tout->Branch("X_C_in.",&X_C_in,"X_C_in/F");
  tout->Branch("nX_C_in.",&nX_C_in,"nX_C_in/I");
  tout->Branch("tX_C_in.",&tX_C_in,"tX_C_in/F");
  tout->Branch("Y_C_in.",&Y_C_in,"Y_C_in/F");
  tout->Branch("tY_C_in.",&tY_C_in,"tY_C_in/F");
  tout->Branch("nY_C_in.",&nY_C_in,"nY_C_in/I");

  tout->Branch("x1c_in.",&x1c_in,"x1c_in/F");
  tout->Branch("y1c_in.",&y1c_in,"y1c_in/F");
  tout->Branch("x2c_in.",&x2c_in,"x2c_in/F");
  tout->Branch("y2c_in.",&y2c_in,"y2c_in/F"); 
  tout->Branch("fXt_in.",&fXt_in,"fXt_in/F");
  tout->Branch("fYt_in.",&fYt_in,"fYt_in/F"); 

  tout->Branch("frame1X_in",&frame1X_in,"frame1X_in/F");
  tout->Branch("frame2X_in",&frame2X_in,"frame2X_in/F");
  tout->Branch("frame3X_in",&frame3X_in,"frame3X_in/F");
  tout->Branch("frame1Y_in",&frame1Y_in,"frame1Y_in/F");
  tout->Branch("frame2Y_in",&frame2Y_in,"frame2Y_in/F");
  tout->Branch("frame3Y_in",&frame3Y_in,"frame3Y_in/F");

  tout->Branch("x1t_in",&x1t_in,"x1t_in/F");
  tout->Branch("x2t_in",&x2t_in,"x2t_in/F");
  tout->Branch("x3t_in",&x3t_in,"x3t_in/F");
  tout->Branch("x4t_in",&x4t_in,"x4t_in/F");
  tout->Branch("y1t_in",&y1t_in,"y1t_in/F");
  tout->Branch("y2t_in",&y2t_in,"y2t_in/F");
  tout->Branch("y3t_in",&y3t_in,"y3t_in/F");
  tout->Branch("y4t_in",&y4t_in,"y4t_in/F");
  tout->Branch("xCt_in",&xCt_in,"xCt_in/F");
  tout->Branch("yCt_in",&yCt_in,"yCt_in/F");

  tout->Branch("a20_1_in.",&a20_1_in,"a20_1_in/F");
  tout->Branch("a20_1_un_in.",&a20_1_un_in,"a20_1_un_in/F");
  tout->Branch("t20_1_in.",&t20_1_in,"t20_1_in/F");
  tout->Branch("n20_1_in.",&n20_1_in,"n20_1_in/I");

  tout->Branch("a1_1_in.",&a1_1_in,"a1_1_in/F");
  tout->Branch("t1_1_in.",&t1_1_in,"t1_1_in/F");
  tout->Branch("n1_1_in.",&n1_1_in,"n1_1_in/I");

  tout->Branch("a20_2_in.",&a20_2_in,"a20_2_in/F");
  tout->Branch("a20_2_un_in.",&a20_2_un_in,"a20_2_un_in/F");
  tout->Branch("t20_2_in.",&t20_2_in,"t20_2_in/F");
  tout->Branch("n20_2_in.",&n20_2_in,"n20_2_in/I");

  tout->Branch("a1_2_in.",&a1_2_in,"a1_2_in/F");
  tout->Branch("t1_2_in.",&t1_2_in,"t1_2_in/F");
  tout->Branch("n1_2_in.",&n1_2_in,"n1_2_in/I");

  tout->Branch("a20_3_in.",&a20_3_in,"a20_3_in/F");
  tout->Branch("a20_3_un_in.",&a20_3_un_in,"a20_3_un_in/F");
  tout->Branch("t20_3_in.",&t20_3_in,"t20_3_in/F");
  tout->Branch("n20_3_in.",&n20_3_in,"n20_3_in/I");

  tout->Branch("a1_3_in.",&a1_3_in,"a1_3_in/F");
  tout->Branch("t1_3_in.",&t1_3_in,"t1_3_in/F");
  tout->Branch("n1_3_in.",&n1_3_in,"n1_3_in/I");

  tout->Branch("a20_4_in.",&a20_4_in,"a20_4_in/F");
  tout->Branch("a20_4_un_in.",&a20_4_un_in,"a20_4_un_in/F");
  tout->Branch("t20_4_in.",&t20_4_in,"t20_4_in/F");
  tout->Branch("n20_4_in.",&n20_4_in,"n20_4_in/I");

  tout->Branch("a1_4_in.",&a1_4_in,"a1_4_in/F");
  tout->Branch("t1_4_in.",&t1_4_in,"t1_4_in/F");
  tout->Branch("n1_4_in.",&n1_4_in,"n1_4_in/I");

  tout->Branch("flag1_in.",&flag1_in,"flag1_in/I");
  tout->Branch("flag2_in.",&flag2_in,"flag2_in/I");
  tout->Branch("flag3_in.",&flag3_in,"flag3_in/I");
  tout->Branch("flag4_in.",&flag4_in,"flag4_in/I");
  tout->Branch("flagCent_in.",&flagCent_in,"flagCent_in/I");

  tout->Branch("nh3_in.",&nh3_in,"nh3_in/I");
  tout->Branch("nhe3_1_in.",&nhe3_1_in,"nhe3_1_in/I");
  tout->Branch("nhe3_2_in.",&nhe3_2_in,"nhe3_2_in/I");
  tout->Branch("nhe3_3_in.",&nhe3_3_in,"nhe3_3_in/I");
  tout->Branch("nhe3_4_in.",&nhe3_4_in,"nhe3_4_in/I");

  tout->Branch("th_he3_1_in.",&th_he3_1_in,"th_he3_1_in/F");
  tout->Branch("th_he3_2_in.",&th_he3_2_in,"th_he3_2_in/F");
  tout->Branch("th_he3_3_in.",&th_he3_3_in,"th_he3_3_in/F");
  tout->Branch("th_he3_4_in.",&th_he3_4_in,"th_he3_4_in/F");
  tout->Branch("th_he3_in.",&th_he3_in,"th_he3_in/F");

  tout->Branch("th_h3_in.",&th_h3_in,"th_h3_in/F");

  tout->Branch("phi_he3_1_in.",&phi_he3_1_in,"phi_he3_1_in/F");
  tout->Branch("phi_he3_2_in.",&phi_he3_2_in,"phi_he3_2_in/F");
  tout->Branch("phi_he3_3_in.",&phi_he3_3_in,"phi_he3_3_in/F");
  tout->Branch("phi_he3_4_in.",&phi_he3_4_in,"phi_he3_4_in/F");
  tout->Branch("phi_h3_in.",&phi_h3_in,"phi_h3_in/F");

  tout->Branch("e_1_in.",&e_1_in,"e_1_in/F");
  tout->Branch("e_2_in.",&e_2_in,"e_2_in/F");
  tout->Branch("e_3_in.",&e_3_in,"e_3_in/F");
  tout->Branch("e_4_in.",&e_4_in,"e_4_in/F");

  tout->Branch("pBeam_in.",&pBeam_in,"pBeam_in/F");

  tout->Branch("centE_in.",&centE_in,"centE_in/F");
  tout->Branch("thetah7_in.",&thetah7_in,"thetah7_in/F");
  tout->Branch("phih7_in.",&phih7_in,"phih7_in/F");

  tout->Branch("thetah7CM_in.",&thetah7CM_in,"thetah7CM_in/F");
  tout->Branch("phih7CM_in.",&phih7CM_in,"phih7CM_in/F");
  tout->Branch("thetahe3CM_in.",&thetahe3CM_in,"thetahe3CM_in/F");
  tout->Branch("phihe3CM_in.",&phihe3CM_in,"phihe3CM_in/F");
  tout->Branch("thetah3CM_in.",&thetah3CM_in,"thetah3CM_in/F");
  tout->Branch("phih3CM_in.",&phih3CM_in,"phih3CM_in/F");
  
  tout->Branch("thetahe3_in.",&thetahe3_in,"thetahe3_in/F");
  tout->Branch("phihe3_in.",&phihe3_in,"phihe3_in/F");

  tout->Branch("thetah3_in.",&thetah3_in,"thetah3_in/F");
  tout->Branch("phih3_in.",&phih3_in,"phih3_in/F");

  tout->Branch("mh7_in.",&mh7_in,"mh7_in/F");
  tout->Branch("eh7_in.",&eh7_in,"eh7_in/F");
  tout->Branch("eh3_in.",&eh3_in,"eh3_in/F");
  tout->Branch("eh3_CM_in.",&eh3_CM_in,"eh3_CM_in/F");
  tout->Branch("ehe3_in.",&ehe3_in,"ehe3_in/F");
  tout->Branch("ehe8_in.",&ehe8_in,"ehe8_in/F");
  tout->Branch("ehe8_ToF_in.",&ehe8_ToF_in,"ehe8_ToF_in/F");

  // tout->Branch("qReaction.",&qReaction,"qReaction/F");

  tout->Branch("angle_h3_h7_in.",&angle_h3_h7_in,"angle_h3_h7_in/F");
  tout->Branch("angle_h3_h7CM_in.",&angle_h3_h7CM_in,"angle_h3_h7CM_in/F");
  tout->Branch("angle_h3_h7CMreaction_in.",&angle_h3_h7CMreaction_in,"angle_h3_h7CMreaction_in/F");

  tout->Branch("angle_he3_h7_in.",&angle_he3_h7_in,"angle_he3_h7_in/F");
  tout->Branch("angle_he3_he8_in.",&angle_he3_he8_in,"angle_he3_he8_in/F");
  tout->Branch("angle_he3_he8CM_in.",&angle_he3_he8CM_in,"angle_he3_he8CM_in/F");

  tout->Branch("thetahe8_in.",&thetahe8_in,"thetahe8_in/F");
  tout->Branch("phihe8_in.",&phihe8_in,"phihe8_in/F");

  for(Int_t i=0;i<t->GetEntries();i++){
  // for(Int_t i=0;i<100;i++){
    t->GetEntry(i);


    tout->Fill();
  }

  fout->cd();
  tout->Write();
  fout->Close();

}