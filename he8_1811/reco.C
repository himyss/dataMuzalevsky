void calculateBeam();
void zerovars();

TELoss f8HeSi;

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xCent,yCent,zCent;
Float_t xRight,yRight,zRight;

Float_t tF5,F5,tF3,F3;

Float_t trigger;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_L_uncorr,Y_R,tY_R,a20_R,t20_R,a20_R_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L,n20_R,nY_R;

Int_t flagLeft,flagCent,flagRight;

Int_t nh3,nhe3_R,nhe3;

// new
Float_t rightE4,rightE24,rightEcal;
Float_t leftE4,leftE24,leftEcal;
Float_t centE;

TLorentzVector h3,he8,d2,he3,h7,h3CM;
TLorentzVector he3CM,h7CM; // reaction CMS
TLorentzVector he3CM_H7,h3CM_H7,h7CM_H7; // reaction CMS

Double_t phi,theta;
Double_t momentum,energy,mass;

Float_t thetah7,phih7,phih3,thetah3,phihe3,thetahe3;
Float_t thetah7CM,phih7CM,phih3CM,thetah3CM,phihe3CM,thetahe3CM;
Float_t mh7,eh7,eh3,ehe3,ehe8,eh3CM7H;

Float_t angle_h3_h7,angle_h3_h7CM,angle_h3_h7CMreaction,angle_he3_h7,angle_he3_he8;
Float_t qReaction;


TVector3 bVect,bVect_H7;

void reco() {
  f8HeSi.SetEL(1, 2.321); // density in g/cm3
  f8HeSi.AddEL(14., 28.086, 1);  //Z, mass
  f8HeSi.SetZP(2., 8.);   //alphas, Z, A
  f8HeSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
  f8HeSi.SetDeltaEtab(300);

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/he8_reco.root");
  // ch->Add("/home/oem/work/data/exp1811/analysed/he8_emtpytarget_reco.root");
  cout << ch->GetEntries() << " total number of Entries" << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger.",&trigger);

  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);

  ch->SetBranchAddress("nh3.",&nh3);
  ch->SetBranchAddress("nhe3.",&nhe3);
  ch->SetBranchAddress("nhe3_R.",&nhe3_R); 

  ch->SetBranchAddress("flagLeft.",&flagLeft);
  ch->SetBranchAddress("flagCent.",&flagCent);
  ch->SetBranchAddress("flagRight.",&flagRight);

  ch->SetBranchAddress("X_C.",&X_C);
  ch->SetBranchAddress("nX_C.",&nX_C);
  ch->SetBranchAddress("Y_C.",&Y_C);
  ch->SetBranchAddress("nY_C.",&nY_C);

  ch->SetBranchAddress("aCsI.",&aCsI);
  // ch->SetBranchAddress("tCsI.",&tCsI);
  ch->SetBranchAddress("nCsI.",&nCsI);
  ch->SetBranchAddress("aCsI_cal.",&aCsI_cal);

  ch->SetBranchAddress("X_L.",&X_L);
  ch->SetBranchAddress("Y_L.",&Y_L);
  ch->SetBranchAddress("nY_L.",&nY_L);
  ch->SetBranchAddress("nX_L.",&nX_L);
  ch->SetBranchAddress("a20_L.",&a20_L);
  ch->SetBranchAddress("n20_L.",&n20_L);
  ch->SetBranchAddress("a20_L_uncorr.",&a20_L_uncorr); 

  ch->SetBranchAddress("Y_R.",&Y_R);
  ch->SetBranchAddress("nY_R.",&nY_R);
  ch->SetBranchAddress("a20_R.",&a20_R);
  ch->SetBranchAddress("n20_R.",&n20_R);
  ch->SetBranchAddress("a20_R_uncorr.",&a20_R_uncorr); 

  ch->SetBranchAddress("x1c.",&x1c);
  ch->SetBranchAddress("y1c.",&y1c);
  ch->SetBranchAddress("x2c.",&x2c);
  ch->SetBranchAddress("y2c.",&y2c); 
  ch->SetBranchAddress("fXt.",&fXt);
  ch->SetBranchAddress("fYt.",&fYt); 

  ch->SetBranchAddress("xLeft.",&xLeft);
  ch->SetBranchAddress("yLeft.",&yLeft);
  ch->SetBranchAddress("zLeft.",&zLeft);

  ch->SetBranchAddress("xRight.",&xRight);
  ch->SetBranchAddress("yRight.",&yRight);
  ch->SetBranchAddress("zRight.",&zRight);

  ch->SetBranchAddress("xCent.",&xCent);
  ch->SetBranchAddress("yCent.",&yCent);
  ch->SetBranchAddress("zCent.",&zCent);

  ch->SetBranchAddress("leftE4.",&leftE4);
  ch->SetBranchAddress("leftE24.",&leftE24);
  ch->SetBranchAddress("leftEcal.",&leftEcal);

  ch->SetBranchAddress("rightE4.",&rightE4);
  ch->SetBranchAddress("rightE24.",&rightE24);
  ch->SetBranchAddress("rightEcal.",&rightEcal);

  ch->SetBranchAddress("centE.",&centE);

  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_missing_mass.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_emtpytarget_mm.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger.",&trigger,"trigger/F");

  tw->Branch("aCsI.",&aCsI,"aCsI/I");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");
  tw->Branch("aCsI_cal.",&aCsI_cal,"aCsI_cal/F");

  tw->Branch("X_C.",&X_C,"X_C/F");
  tw->Branch("nX_C.",&nX_C,"nX_C/I");
  tw->Branch("Y_C.",&Y_C,"Y_C/F");
  tw->Branch("nY_C.",&nY_C),"nY_C/I";

  tw->Branch("X_L.",&X_L,"X_L/F");
  tw->Branch("Y_L.",&Y_L,"Y_L/F");
  tw->Branch("nY_L.",&nY_L,"nY_L/I");
  tw->Branch("nX_L.",&nX_L,"nY_L/I");
  tw->Branch("a20_L.",&a20_L,"a20_L/F");
  tw->Branch("n20_L.",&n20_L,"n20_L/I");
  tw->Branch("a20_L_uncorr.",&a20_L_uncorr,"a20_L_uncorr/F"); 

  tw->Branch("Y_R.",&Y_R,"Y_R/F");
  tw->Branch("nY_R.",&nY_R,"nY_R/I");
  tw->Branch("a20_R.",&a20_R,"a20_R/F");
  tw->Branch("n20_R.",&n20_R,"n20_R/I");
  tw->Branch("a20_R_uncorr.",&a20_R_uncorr,"a20_R_uncorr/F"); 

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nhe3_R.",&nhe3_R,"nhe3_R/I");
  tw->Branch("nhe3.",&nhe3,"nhe3/I");

  tw->Branch("flagLeft.",&flagLeft,"flagLeft/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  tw->Branch("flagRight.",&flagRight,"flagRight/I");

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
  tw->Branch("eh3CM7H.",&eh3CM7H,"eh3CM7H/F");
  tw->Branch("ehe3.",&ehe3,"ehe3/F");
  tw->Branch("ehe8.",&ehe8,"ehe8/F");

  // tw->Branch("qReaction.",&qReaction,"qReaction/F");

  tw->Branch("angle_h3_h7.",&angle_h3_h7,"angle_h3_h7/F");
  tw->Branch("angle_h3_h7CM.",&angle_h3_h7CM,"angle_h3_h7CM/F");
  tw->Branch("angle_h3_h7CMreaction.",&angle_h3_h7CMreaction,"angle_h3_h7CMreaction/F");

  tw->Branch("angle_he3_h7.",&angle_he3_h7,"angle_he3_h7/F");
  tw->Branch("angle_he3_he8.",&angle_he3_he8,"angle_he3_he8/F");

  tw->Branch("h7.", "TLorentzVector", &h7);
  tw->Branch("h3.", "TLorentzVector", &h3);
  tw->Branch("he3.", "TLorentzVector", &he3);
  tw->Branch("he8.", "TLorentzVector", &he8);
  // input options
  d2.SetPxPyPzE(0.,0.,0.,1.875612);

  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry = 0; nentry<20000;nentry++) {
    if(nentry%10000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);
    zerovars();

    calculateBeam();
    TLorentzVector summVect = he8 + d2;
    bVect = summVect.BoostVector();
    // cout << summVect.Px() << " " << bVect.Py() << " " << bVect.Pz() << endl;

    if (nhe3 && !nhe3_R) {
      energy = leftE4/1000.;
      mass = 2.808391000;  //MeV
// 2809.431806
      TVector3 dir;
      dir.SetXYZ(xLeft,yLeft,zLeft);
      phi = dir.Phi();
      theta = dir.Theta();

      momentum = sqrt(energy*energy + 2*energy*mass);

      // he3.SetPtEtaPhiM(momentum, theta, phi, mass);
      he3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

      thetahe3 = he3.Theta()*TMath::RadToDeg();
      phihe3 = he3.Phi()*TMath::RadToDeg();
      ehe3 = he3.T() - mass;

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
    }

   if (nhe3_R && !nhe3) {
      energy = rightE4/1000.;
      mass = 2.808391000;  //MeV
// 2809.431806
      TVector3 dir;
      dir.SetXYZ(xRight,yRight,zRight);
      phi = dir.Phi();
      theta = dir.Theta();

      momentum = sqrt(energy*energy + 2*energy*mass);

      // he3.SetPtEtaPhiM(momentum, theta, phi, mass);
      he3.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

      thetahe3 = he3.Theta()*TMath::RadToDeg();
      phihe3 = he3.Phi()*TMath::RadToDeg();
      ehe3 = he3.T() - mass;

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
    }


    if (nh3) {
      energy = centE/1000.;
      mass = 2.80892; //GeV

      TVector3 dir;
      dir.SetXYZ(xCent,yCent,zCent);
      phi = dir.Phi();
      theta = dir.Theta();

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

      h3CM = h3;
      h3CM.Boost(-bVect); 
      thetah3CM = h3CM.Theta()*TMath::RadToDeg();
      phih3CM = h3CM.Phi()*TMath::RadToDeg();

      if (nhe3==1 || nhe3_R){
        h3CM_H7 = h3;
        h3CM_H7.Boost(-bVect_H7);
      }

    } 
    
    if (nh3==1 && (nhe3==1 || nhe3_R==1)) {
      angle_h3_h7CM = h7CM_H7.Angle(h3CM_H7.Vect())*TMath::RadToDeg();
      eh3CM7H = h3CM_H7.T() - 2.80892;

      angle_h3_h7 = h7.Angle(h3.Vect())*TMath::RadToDeg(); 
      angle_h3_h7CMreaction = h7CM.Angle(h3CM.Vect())*TMath::RadToDeg(); 
      angle_he3_h7 = h7.Angle(he3.Vect())*TMath::RadToDeg();
      angle_he3_he8 = he8.Angle(he3.Vect())*TMath::RadToDeg();
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

  kinEnergy =  f8HeSi.GetE(1000*kinEnergy, 644.)/1000.;
  // kinEnergy = kinEnergy*0.95;
  ehe8 = kinEnergy;

  // kinEnergy = 0.1979;
  // ehe8 = kinEnergy;

  momentum = sqrt(kinEnergy*kinEnergy + 2*kinEnergy*mass);

  momentum = TMath::Abs(momentum);
  he8.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

  // he8.SetPtEtaPhiM(momentum, theta, phi, mass);
  // cout << he8.Px() << " " << he8.Py() << " " << he8.Pz() << endl;

  return;
}

void zerovars() {
  thetah7 = -10.;
  phih7 = -100.;
  thetah3 = -1000.;
  phih3 = -500.;
  angle_h3_h7 = -100;

  thetah7CM = -10.;
  phih7CM = -100.;
  thetah3CM = -1000.;
  phih3CM = -10000.;
  angle_h3_h7CM = -100000;
  angle_h3_h7CMreaction = -100000;
  qReaction = -100.;
  angle_he3_h7 = -100;
  angle_he3_he8 = -100;

  mh7 = -1.;
  eh7 = -1.;
  eh3 = -1.;
  ehe3 = -1.;
  eh3CM7H = -1;

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