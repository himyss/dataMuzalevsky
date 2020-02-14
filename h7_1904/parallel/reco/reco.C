void calculateBeam();
void zerovars();

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
Float_t x1c, y1c, x2c, y2c;
Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;
Float_t sideX,sideY;
Float_t frame1X,frame1Y,frame2X,frame2Y,frame3X,frame3Y;

Int_t flag1,flag2,flag3,flag4,flagCent;
Int_t nh3,nhe3_1,nhe3_2,nhe3_3,nhe3_4;

Float_t e_1,e_2,e_3,e_4;
Float_t centE;
Float_t px,py,pz,pBeam;

Float_t th_he3_1,th_he3_2,th_he3_3,th_he3_4,th_h3,th_4n;
Float_t phi_he3_1,phi_he3_2,phi_he3_3,phi_he3_4,phi_h3;


TLorentzVector h3,he8,d2,he3,h7,h3CM,h4n,hBinary;
TLorentzVector he3CM,h7CM; // reaction CMS
TLorentzVector he3CM_H7,h3CM_H7,h7CM_H7,h4nCM_H7,hBinary_CM; // reaction CMS

Double_t phi,theta;
Double_t momentum,energy,mass;

Float_t thetah7,phih7,phih3,thetah3,phihe3,thetahe3,thetahe8;
Float_t thetah7CM,phih7CM,phih3CM,thetah3CM,phihe3CM,thetahe3CM,theta4nCM;
Float_t mh7,eh7,eh3,ehe3,ehe8,eh3_CM,m4n,e4n,e4n_CM;
Float_t v_he3,tof_he3;


Float_t angle_h3_h7,angle_h3_h7CM,angle_h3_h7CMreaction,angle_he3_h7,angle_he3_he8;
Float_t angle_n4_h3,angle_n4_h7,angle_bin_h3_CM,angle_bin_h3;
Float_t qReaction;

Int_t coincidence;

TVector3 bVect,bVect_H7;

void reco(Int_t nRun=0) {
  f8HeSi.SetEL(1, 2.321); // density in g/cm3
  f8HeSi.AddEL(14., 28.086, 1);  //Z, mass
  f8HeSi.SetZP(2., 8.);   //alphas, Z, A
  f8HeSi.SetEtab(300000, 250.); // ?, MeV calculate ranges
  f8HeSi.SetDeltaEtab(300);

  TChain *ch = new TChain("tree");
  TString inPutFileName;
  inPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/calcEnergies/track0/targetCut/13/h7_ct_%d_reco_newPars.root",nRun);
  // inPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/calcEnergies/track0/eTarget/h7_ct_%d_reco_newPars.root",nRun);
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
  ch->SetBranchAddress("nhe3_1.",&nhe3_1);
  ch->SetBranchAddress("nhe3_2.",&nhe3_2);
  ch->SetBranchAddress("nhe3_3.",&nhe3_3);
  ch->SetBranchAddress("nhe3_4.",&nhe3_4);

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


  TString outPutFileName;
  // outPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/reco/eTarget/h7_ect_%d_mm_frame.root",nRun);
  outPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/reco/h7_ct_%d_mm_frame.root",nRun);
  // outPutFileName.Form("test.root",nRun);

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

  // input options
  d2.SetPxPyPzE(0.,0.,0.,1.875612);

  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry = 0; nentry<2000000;nentry++) {
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);

    // if ( (fXt*fXt + fYt*fYt)>9*9 ) continue;

    zerovars();

    if (trigger==2) {
      sideX = x1t;
      sideY = y1t;
    }

    if (trigger==3) {
      sideX = x2t;
      sideY = y2t;
    }

    if (trigger==4) {
      sideX = x3t;
      sideY = y3t;
    }

    if (trigger==5) {
      sideX = x4t;
      sideY = y4t;
    }

    calculateBeam();
    TLorentzVector summVect = he8 + d2;
    bVect = summVect.BoostVector();
    // cout << summVect.Px() << " " << bVect.Py() << " " << bVect.Pz() << endl;

    // if (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) cout << " wtf" << endl;

    
    coincidence = 0;
    if (nh3 && flagCent && nh3 && nhe3_1 && flag1 && !nhe3_2 && !nhe3_3 && !nhe3_4) {
      // if (e_1>20 || centE<40) continue;
      energy = e_1/1000.;
      theta = th_he3_1;
      phi = phi_he3_1;
      coincidence++;
    } 

    if (nh3 && flagCent && nh3 && nhe3_2 && flag2 && !nhe3_1 && !nhe3_3 && !nhe3_4) {
      // if (n20_2==0 || n20_2==1) continue;
      // if (e_2>20 || centE<40) continue;
      energy = e_2/1000.;
      theta = th_he3_2;
      phi = phi_he3_2;
      coincidence++;
    } 

    if (nh3 && flagCent && nh3 && nhe3_3 && flag3 && !nhe3_1 && !nhe3_2 && !nhe3_4 ) {
      // if (e_3>20 || centE<40) continue;
      energy = e_3/1000.;
      theta = th_he3_3;
      phi = phi_he3_3;
      coincidence++;
    } 

    if (nh3 && flagCent && nh3 && nhe3_4 && flag4 && !nhe3_2 && !nhe3_3 && !nhe3_1) {
      // if (e_4>20 || centE<40) continue;
      energy = e_4/1000.;
      theta = th_he3_4;
      phi = phi_he3_4;
      coincidence++;
    } 

    if(coincidence!=1) continue;
    // energy = leftE4/1000.;
    mass = 2.808391;  //MeV

    // TVector3 dir;
    // dir.SetXYZ(xLeft,yLeft,zLeft);
    // phi = dir.Phi();
    // theta = dir.Theta();

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

    hBinary.SetXYZT(he8.X()/8, he8.Y()/8, he8.Z()/8, he8.T()/8);
    hBinary += -he3;
    hBinary_CM = hBinary;
    h7CM_H7.Boost(-bVect_H7);

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

    if (nh3) {
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
      // if (h3.T() == h3.Mag()) { 
      //   cout << xCent << " " << yCent << " " << zCent << endl;
      //   // cout << h3.T() << " " << h3.Mag() << " " << mass << endl;
      // }
      // CM
      // h3CM = h3;
      // h3CM.Boost(-bVect); 
      // thetah3CM = h3CM.Theta()*TMath::RadToDeg();
      // phih3CM = h3CM.Phi()*TMath::RadToDeg();

      if (nh3 && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)) {
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
      }
      
    } 
    
    if (nh3 && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)) {
      angle_h3_h7CM = h7CM_H7.Angle(h3CM_H7.Vect())*TMath::RadToDeg();
      angle_h3_h7 = h7.Angle(h3.Vect())*TMath::RadToDeg(); 
      angle_h3_h7CMreaction = h7CM.Angle(h3CM.Vect())*TMath::RadToDeg(); 
      angle_he3_h7 = h7.Angle(he3.Vect())*TMath::RadToDeg();
      angle_he3_he8 = he8.Angle(he3.Vect())*TMath::RadToDeg();

      angle_n4_h7 = h7.Angle(h4n.Vect())*TMath::RadToDeg();
      angle_n4_h3 = h3.Angle(h4n.Vect())*TMath::RadToDeg();

      angle_bin_h3_CM = h3CM_H7.Angle(hBinary.Vect())*TMath::RadToDeg();
      angle_bin_h3 = h3.Angle(hBinary.Vect())*TMath::RadToDeg();
    }

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

  kinEnergy =  f8HeSi.GetE(1000*kinEnergy, 565.5)/1000.;
  // kinEnergy = kinEnergy*0.95;
  ehe8 = kinEnergy;

  // cout << ehe8 << endl;
  // kinEnergy = 0.1979;
  // ehe8 = kinEnergy;

  pBeam = sqrt(kinEnergy*kinEnergy + 2*kinEnergy*mass);
  pBeam = TMath::Abs(pBeam);

  he8.SetXYZM(pBeam*TMath::Sin(theta)*TMath::Cos(phi), pBeam*TMath::Sin(theta)*TMath::Sin(phi), pBeam*TMath::Cos(theta) ,mass);
  thetahe8 = he8.Theta();

  px = he8.Px();
  py = he8.Py();
  pz = he8.Pz();

  return;
}

void zerovars() {

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