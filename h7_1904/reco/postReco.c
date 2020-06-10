#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void zerovars();
void createBranches();
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
Float_t x1c, y1c, x2c, y2c;
Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;
Float_t sideX,sideY;
Float_t frame1X,frame1Y,frame2X,frame2Y,frame3X,frame3Y;

Int_t flag1,flag2,flag3,flag4,flagCent;
Int_t nh3,nh2,nh1,nhe3_1,nhe3_2,nhe3_3,nhe3_4,neutron;
Int_t nhe4_1,nhe4_2,nhe4_3,nhe4_4;

Float_t e_1,e_2,e_3,e_4;
Float_t centE;
Float_t px,py,pz,pBeam;

Float_t th_he3_1,th_he3_2,th_he3_3,th_he3_4,th_h3,th_4n;
Float_t phi_he3_1,phi_he3_2,phi_he3_3,phi_he3_4,phi_h3;

TLorentzVector h3,he8,d2,he3,h7,h3CM,h4n,hBinary,n4;
TLorentzVector he3CM,h7CM; // reaction CMS
TLorentzVector he3CM_H7,h3CM_H7,h7CM_H7,h4nCM_H7,hBinary_CM; // reaction CMS
TLorentzVector h_n4h3,h_n4h3_CM,h_n4_he3,h_n4_he3_CM;

Double_t phi,theta;
Double_t momentum,energy,mass;

Float_t thetah7,phih7,phih3,thetah3,phihe3,thetahe3,thetahe8;
Float_t thetah7CM,phih7CM,phih3CM,thetah3CM,phihe3CM,thetahe3CM,theta4nCM;
Float_t mh7,eh7,eh3,ehe3,ehe8,eh3_CM,m4n,e4n,e4n_CM,mn4,en4;
Float_t v_he3,tof_he3;


Float_t angle_h3_h7,angle_h3_h7CM,angle_h3_h7CMreaction,angle_he3_h7,angle_he3_he8;
Float_t angle_n4_h3,angle_n4_h7,angle_bin_h3_CM,angle_bin_h3;
Float_t qReaction;

Int_t coincidence;
Float_t tND,aND,tacND,numND;
TVector3 bVect,bVect_H7;

Float_t targetTime;

Float_t e_4n_3He,e_4n_3H,e_4n_3He_CM,e_4n_3H_CM;

TTree* tw;

void postReco() { 
  create_IDs();

  // input
  TFile* reco_file = new TFile("/media/ivan/data/exp1904/ERanalysis/recoNew/h7_ct_00_0001.reco.root");
  TFile* digi_file = new TFile("/media/ivan/data/exp1904/ERanalysis/cleaned/h7_ct_00_0001.cleaned.root");
  TTree* reco_tree = (TTree*)reco_file->Get("er");
  TTree* tree = (TTree*)digi_file->Get("er");
  tree->AddFriend(reco_tree);

  TClonesArray* beamdet_track_arr = new TClonesArray("ERBeamDetTrack", 10);
  tree->SetBranchAddress("BeamDetTrack",&beamdet_track_arr);
  TClonesArray* t1_track_arr = new TClonesArray("ERQTelescopeTrack", 10);
  tree->SetBranchAddress("ERQTelescopeTrack_Telescope_1_SingleSi_SSD20_1_X_0Telescope_1_SingleSi_SSD_1_Y_1",&t1_track_arr);
  TClonesArray* t2_track_arr = new TClonesArray("ERQTelescopeTrack", 10);
  tree->SetBranchAddress("ERQTelescopeTrack_Telescope_2_SingleSi_SSD_2_X_4Telescope_2_SingleSi_SSD20_2_Y_3",&t2_track_arr);
  TClonesArray* t3_track_arr = new TClonesArray("ERQTelescopeTrack", 10);
  tree->SetBranchAddress("ERQTelescopeTrack_Telescope_3_SingleSi_SSD20_3_X_6Telescope_3_SingleSi_SSD_3_Y_7",&t3_track_arr);
  TClonesArray* t4_track_arr = new TClonesArray("ERQTelescopeTrack", 10);
  tree->SetBranchAddress("ERQTelescopeTrack_Telescope_4_SingleSi_SSD_4_X_10Telescope_4_SingleSi_SSD20_4_Y_9",&t4_track_arr);
  TClonesArray* ct_track_arr = new TClonesArray("ERQTelescopeTrack", 10);
  tree->SetBranchAddress("ERQTelescopeTrack_Central_telescope_DoubleSi_DSD_XY_0",&ct_track_arr);

  TClonesArray* beamdet_pt_arr = new TClonesArray("ERBeamDetParticle", 10);
  tree->SetBranchAddress("BeamDetParticle.",&beamdet_pt_arr);
  TClonesArray* t1_pt_arr = new TClonesArray("ERQTelescopeParticle", 10);
  tree->SetBranchAddress("ERQTelescopeParticle_Telescope_1_SingleSi_SSD20_1_X_0Telescope_1_SingleSi_SSD_1_Y_1_1000020030",&t1_pt_arr);
  TClonesArray* t2_pt_arr = new TClonesArray("ERQTelescopeParticle", 10);
  tree->SetBranchAddress("ERQTelescopeParticle_Telescope_2_SingleSi_SSD_2_X_4Telescope_2_SingleSi_SSD20_2_Y_3_1000020030",&t2_pt_arr);
  TClonesArray* t3_pt_arr = new TClonesArray("ERQTelescopeParticle", 10);
  tree->SetBranchAddress("ERQTelescopeParticle_Telescope_3_SingleSi_SSD20_3_X_6Telescope_3_SingleSi_SSD_3_Y_7_1000020030",&t3_pt_arr);
  TClonesArray* t4_pt_arr = new TClonesArray("ERQTelescopeParticle", 10);
  tree->SetBranchAddress("ERQTelescopeParticle_Telescope_4_SingleSi_SSD_4_X_10Telescope_4_SingleSi_SSD20_4_Y_9_1000020030",&t4_pt_arr);
  TClonesArray* ct_pt_arr = new TClonesArray("ERQTelescopeParticle", 10);
  tree->SetBranchAddress("ERQTelescopeParticle_Central_telescope_DoubleSi_DSD_XY_0_1000010030",&ct_pt_arr);

  ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();
  tree->SetBranchAddress("EventHeader.",&header);
  //output
  TFile* h7_file = new TFile("/media/ivan/data/exp1904/ERanalysis/analysed/tests/h7_test.root", "recreate");
  tw = new TTree("tw", "Tree with h7 Lorentz vectors");
  createBranches();

  // event loop
  // for (Long64_t i=0; i < tree->GetEntriesFast(); i++) {
  for (Long64_t i=0; i < 1000; i++) {
    tree->GetEntry(i);
 
    zerovars();

    const Int_t trigger = header->GetTrigger();

    const size_t he3_in_detectors_count = t1_pt_arr->GetEntriesFast() + t2_pt_arr->GetEntriesFast() 
        + t3_pt_arr->GetEntriesFast() + t4_pt_arr->GetEntriesFast();

    // read the BeamDet particle
    if (beamdet_pt_arr->GetEntriesFast() != 1 || beamdet_track_arr->GetEntriesFast() != 1) continue;
    const auto he8_track = static_cast<ERBeamDetTrack*>(beamdet_track_arr->At(0));
    const auto he8_pt  = static_cast<ERBeamDetParticle*>(beamdet_pt_arr->At(0));
    if ( pow(he8_track->GetTargetX(),2) + pow(he8_track->GetTargetY(),2)>0.9*0.9 ) continue;


    // read the Side detectors
    if ( t1_track_arr->GetEntriesFast() == 1 && t1_pt_arr->GetEntriesFast() == 1 ){
      const auto t1_track =  static_cast<ERQTelescopeTrack*>(t1_track_arr->At(0));
      const auto t1_pt =  static_cast<ERQTelescopeParticle*>(t1_pt_arr->At(0));
      flag1 = 1;
      if ( cuthe3_1[t1_track->GetXChannel()]->IsInside(t1_pt->GetCorrectedEdepInThickStation(), t1_pt->GetCorrectedEdepInThinStation()) ) {
        const auto he3 = t1_pt;
        nhe3_1 = 1;
      }  
    }

    if ( t2_track_arr->GetEntriesFast() == 1 ){
      const auto t2_track =  static_cast<ERQTelescopeTrack*>(t2_track_arr->At(0));
      const auto t2_pt =  static_cast<ERQTelescopeParticle*>(t2_pt_arr->At(0));
      flag2 = 1;
      if ( cuthe3_2[t2_track->GetYChannel()]->IsInside(t2_pt->GetCorrectedEdepInThickStation(), t2_pt->GetCorrectedEdepInThinStation()) ) {
        const auto he3 = t2_pt;
        nhe3_2 = 1;
      }  
    }

    if ( t3_track_arr->GetEntriesFast() == 1 ){
      const auto t3_track =  static_cast<ERQTelescopeTrack*>(t3_track_arr->At(0));
      const auto t3_pt =  static_cast<ERQTelescopeParticle*>(t3_pt_arr->At(0));
      flag3 = 1;
      if ( cuthe3_3[t3_track->GetXChannel()]->IsInside(t3_pt->GetCorrectedEdepInThickStation(), t3_pt->GetCorrectedEdepInThinStation()) ) {
        const auto he3 = t3_pt;
        nhe3_3 = 1;
      }         
    }

    if ( t4_track_arr->GetEntriesFast() == 1 ){
      const auto t4_track =  static_cast<ERQTelescopeTrack*>(t4_track_arr->At(0));
      const auto t4_pt =  static_cast<ERQTelescopeParticle*>(t4_pt_arr->At(0));
      flag4 = 1;
      if ( cuthe3_4[t4_track->GetYChannel()]->IsInside(t4_pt->GetCorrectedEdepInThickStation(), t4_pt->GetCorrectedEdepInThinStation()) ) {
        const auto he3 = t4_pt;
        nhe3_4 = 1;
      }      
    }

continue;

    //  &&  ) {
    //   const auto he3 = t1_pt;
    // }

    // if (t2_track_arr->GetEntriesFast() == 1 && cuthe3_2[t2_track->GetYChannel()]->IsInside(t2_pt->GetCorrectedEdepInThickStation(), t2_pt->GetCorrectedEdepInThinStation()) ) {
    //   const auto he3 = t2_pt;
    // }

    // if (t3_track_arr->GetEntriesFast() == 1 && cuthe3_3[t3_track->GetYChannel()]->IsInside(t3_pt->GetCorrectedEdepInThickStation(), t3_pt->GetCorrectedEdepInThinStation()) ) {
    //   const auto he3 = t3_pt;
    // }

    // if (t4_track_arr->GetEntriesFast() == 1 && cuthe3_4[t4_track->GetYChannel()]->IsInside(t4_pt->GetCorrectedEdepInThickStation(), t4_pt->GetCorrectedEdepInThinStation()) ) {
    //   const auto he3 = t4_pt;
    // }



  // if(flag1 && n1_1>-1 && n20_1>-1 && cuthe3_1[n20_1]->IsInside(a1_1+a20_1_un, a20_1)) {
  //   nhe3_1 = 1;
  //   return;
  // }

    // if ()

    // continue;
    // const auto he3 = t1_he3->GetEntriesFast() == 1 ? static_cast<ERQTelescopeParticle*>(t1_he3->At(0)) : 
    //                  t2_he3->GetEntriesFast() == 1 ? static_cast<ERQTelescopeParticle*>(t2_he3->At(0)) :
    //                  t3_he3->GetEntriesFast() == 1 ? static_cast<ERQTelescopeParticle*>(t3_he3->At(0)) :
    //                  t4_he3->GetEntriesFast() == 1 ? static_cast<ERQTelescopeParticle*>(t4_he3->At(0)) : 
    //                                                  nullptr;

    // if (t1_he3->GetEntriesFast() == 1) {
    //   flag1 = 1;
    //   const auto he3 = static_cast<ERQTelescopeParticle*>(t1_he3->At(0));
    // }                                                


    // const auto he8  = static_cast<ERBeamDetParticle*>(beamdet_he8->At(0));
    // const auto he3_lv = he3->GetLVInteraction();
    // const auto he8_lv = he8->GetLVTarget();
    // TLorentzVector h2_lv(0., 0., 0., 1.875612 /*GeV*/); 

    // TLorentzVector summVect = he8 + d2;
    // bVect = summVect.BoostVector();

    tw->Fill();
  }
  tw->Write();
  h7_file->Write();
}

void createBranches() {
 
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

  tw->Branch("aND",&aND,"aND/F");
  tw->Branch("tND",&tND,"tND/F");
  tw->Branch("tacND",&tacND,"tacND/F");
  tw->Branch("numND",&numND,"numND/F");

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

  tw->Branch("nhe4_1.",&nhe4_1,"nhe4_1/I");
  tw->Branch("nhe4_2.",&nhe4_2,"nhe4_2/I");
  tw->Branch("nhe4_3.",&nhe4_3,"nhe4_3/I");
  tw->Branch("nhe4_4.",&nhe4_4,"nhe4_4/I"); 

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

  tw->Branch("thetah7CM.",&thetah7CM,"thetah7CM/F");
  tw->Branch("phih7CM.",&phih7CM,"phih7CM/F");
  tw->Branch("thetahe3CM.",&thetahe3CM,"thetahe3CM/F");
  tw->Branch("phihe3CM.",&phihe3CM,"phihe3CM/F");
  tw->Branch("thetah3CM.",&thetah3CM,"thetah3CM/F");
  tw->Branch("phih3CM.",&phih3CM,"phih3CM/F");
  
  tw->Branch("thetahe3.",&thetahe3,"thetahe3/F");
  tw->Branch("phihe3.",&phihe3,"phihe3/F");

  tw->Branch("thetah3.",&thetah3,"thetah3/F");
  tw->Branch("phih3.",&phih3,"phih3/F");

  tw->Branch("mh7.",&mh7,"mh7/F");
  tw->Branch("eh7.",&eh7,"eh7/F");
  tw->Branch("en4.",&en4,"en4/F");
  tw->Branch("eh3.",&eh3,"eh3/F");
  tw->Branch("eh3_CM.",&eh3_CM,"eh3_CM/F");
  tw->Branch("ehe3.",&ehe3,"ehe3/F");
  tw->Branch("ehe8.",&ehe8,"ehe8/F");

  tw->Branch("px",&px,"px/F");
  tw->Branch("py",&py,"py/F");
  tw->Branch("pz",&pz,"pz/F");
  tw->Branch("pBeam",&pBeam,"pBeam/F");

  tw->Branch("v_he3.",&v_he3,"v_he3/F");
  tw->Branch("tof_he3.",&tof_he3,"tof_he3/F");

  // tw->Branch("qReaction.",&qReaction,"qReaction/F");

  tw->Branch("angle_h3_h7.",&angle_h3_h7,"angle_h3_h7/F");
  tw->Branch("angle_h3_h7CM.",&angle_h3_h7CM,"angle_h3_h7CM/F");
  tw->Branch("angle_h3_h7CMreaction.",&angle_h3_h7CMreaction,"angle_h3_h7CMreaction/F");

  tw->Branch("angle_he3_h7.",&angle_he3_h7,"angle_he3_h7/F");
  tw->Branch("angle_he3_he8.",&angle_he3_he8,"angle_he3_he8/F");

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

}

void zerovars() {

  targetTime = 0;

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

  theta4nCM = -10;
  thetah7CM = -10.;
  phih7CM = -100.;
  thetah3CM = -1000.;
  phih3CM = -10000.;
  angle_h3_h7CM = -100000;
  angle_h3_h7CMreaction = -100000;
  qReaction = -100.;
  angle_he3_h7 = -100;
  angle_he3_he8 = -100;
  th_4n = -100;

  m4n = -1.;
  e4n = -1.;
  e4n_CM = -1.;
  mh7 = -1.;
  eh7 = -1.;
  en4 = -1.;
  eh3 = -1.;
  eh3_CM = -1.;
  ehe3 = -1.;

  h7.SetXYZT(0,0,0,0);
  h3.SetXYZT(0,0,0,0);
  he3.SetXYZT(0,0,0,0);
  h7CM.SetXYZT(0,0,0,0);
  h3CM.SetXYZT(0,0,0,0);
  he3CM.SetXYZT(0,0,0,0);  
  bVect.SetXYZ(0,0,0);

  bVect_H7.SetXYZ(0,0,0);
  h3CM_H7.SetXYZT(0,0,0,0);
  he3CM_H7.SetXYZT(0,0,0,0);
  h7CM_H7.SetXYZT(0,0,0,0);
}

