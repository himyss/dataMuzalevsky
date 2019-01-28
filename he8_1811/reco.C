void calculateBeam();
void zerovars();

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xCent,yCent,zCent;

Float_t tF5,F5,tF3,F3;

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_R,Y_R,t20_R,tY_R,a20_L_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L,n20_R,nY_R;

Int_t flagLeft,flagCent,flagCent_arr;

Int_t nh3,nh3_s,nhe3;

// new
Float_t leftE4,leftE24,leftEcal;
Float_t centE;

TLorentzVector h3,he8,d2,he3,h7,h3CM,he3CM,h7CM;

Double_t phi,theta;
Double_t momentum,energy,mass;

Float_t thetah7,phih7,phih3,thetah3,phihe3,thetahe3;
Float_t thetah7CM,phih7CM,phih3CM,thetah3CM,phihe3CM,thetahe3CM;
Float_t mh7,eh7,eh3,ehe3,ehe8;

Float_t angle_h3_h7,angle_h3_h7CM;
Float_t qReaction;

TVector3 bVect;

void reco() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/he8_reco_new.root");
  cout << ch->GetEntries() << " total number of Entries" << endl;
  //--------------------------------------------------------------------------------

  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);

  ch->SetBranchAddress("nh3.",&nh3);
  ch->SetBranchAddress("nh3_s.",&nh3_s);
  ch->SetBranchAddress("nhe3.",&nhe3);

  ch->SetBranchAddress("flagLeft.",&flagLeft);
  ch->SetBranchAddress("flagCent.",&flagCent);
  ch->SetBranchAddress("flagCent_arr.",&flagCent_arr);

  ch->SetBranchAddress("x1c.",&x1c);
  ch->SetBranchAddress("y1c.",&y1c);
  ch->SetBranchAddress("x2c.",&x2c);
  ch->SetBranchAddress("y2c.",&y2c); 
  ch->SetBranchAddress("fXt.",&fXt);
  ch->SetBranchAddress("fYt.",&fYt); 

  ch->SetBranchAddress("xLeft.",&xLeft);
  ch->SetBranchAddress("yLeft.",&yLeft);
  ch->SetBranchAddress("zLeft.",&zLeft);

  ch->SetBranchAddress("xCent.",&xCent);
  ch->SetBranchAddress("yCent.",&yCent);
  ch->SetBranchAddress("zCent.",&zCent);

  ch->SetBranchAddress("leftE4.",&leftE4);
  ch->SetBranchAddress("leftE24.",&leftE24);
  ch->SetBranchAddress("leftEcal.",&leftEcal);

  ch->SetBranchAddress("centE.",&centE);


  TFile *fw = new TFile("/media/user/work/data/Analysed1811/selected/he8_missing_mass3.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nh3_s.",&nh3_s,"nh3_s/I");
  tw->Branch("nhe3.",&nhe3,"nhe3/I");

  tw->Branch("flagLeft.",&flagLeft,"flagLeft/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  tw->Branch("flagCent_arr.",&flagCent_arr,"flagCent_arr/I");

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
  tw->Branch("ehe3.",&ehe3,"ehe3/F");
  tw->Branch("ehe8.",&ehe8,"ehe8/F");

  // tw->Branch("qReaction.",&qReaction,"qReaction/F");

  tw->Branch("angle_h3_h7.",&angle_h3_h7,"angle_h3_h7/F");
  tw->Branch("angle_h3_h7CM.",&angle_h3_h7CM,"angle_h3_h7CM/F");

  tw->Branch("h7.", "TLorentzVector", &h7);
  tw->Branch("h3.", "TLorentzVector", &h3);
  tw->Branch("he3.", "TLorentzVector", &he3);
  tw->Branch("he8.", "TLorentzVector", &he8);
  // input options
  d2.SetPxPyPzE(0.,0.,0.,1.875612);

  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
  // for(Int_t nentry = 0; nentry<200;nentry++) {
    if(nentry%100==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);
    zerovars();

    calculateBeam();
    TLorentzVector summVect = he8 + d2;
    bVect = summVect.BoostVector();
    // cout << summVect.Px() << " " << bVect.Py() << " " << bVect.Pz() << endl;

    if (nhe3) {
      energy = leftEcal/1000.;
      mass = 2.808391;  //MeV

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

      // CM
      h3CM = h3;
      h3CM.Boost(-bVect); 
      thetah3CM = h3CM.Theta()*TMath::RadToDeg();
      phih3CM = h3CM.Phi()*TMath::RadToDeg();
    } 
    
    if (nh3==1 && nhe3==1) {
      angle_h3_h7 = h7.Angle(h3.Vect())*TMath::RadToDeg(); 
      angle_h3_h7CM = h7CM.Angle(h3CM.Vect())*TMath::RadToDeg(); 
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

  Double_t velocity = 12320./(tF5-tF3 + 68.553);
  Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  Double_t kinEnergy = mass*((1/beta) - 1);

  kinEnergy = kinEnergy*0.95;
  ehe8 = kinEnergy;

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
  qReaction = -100.;

  mh7 = -1.;
  eh7 = -1.;
  eh3 = -1.;
  ehe3 = -1.;

  h7.SetXYZT(0,0,0,0);
  h3.SetXYZT(0,0,0,0);
  he3.SetXYZT(0,0,0,0);
  h7CM.SetXYZT(0,0,0,0);
  h3CM.SetXYZT(0,0,0,0);
  he3CM.SetXYZT(0,0,0,0);  
  bVect.SetXYZ(0,0,0);
}