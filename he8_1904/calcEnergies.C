void readThickness();
void setTables();

TELoss *f3HeSi;
TELoss *f3HeMylar;
TELoss *f3HeSteel;
TELoss *f3HeTarget;

TELoss *f3HSi;
TELoss *f3HMylar;
TELoss *f3HSteel;
TELoss *f3HTarget;

Float_t tF5,F5,tF3,F3;

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xCent,yCent,zCent;

Int_t nCsI;
Float_t aCsI,tCsI,aCsI_cal;

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_R,Y_R,t20_R,tY_R,a20_L_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L,n20_R,nY_R;

Int_t flagLeft,flagCent,flagCent_arr;

Int_t nh3,nh3_s,nhe3;

Double_t fThicknessLeft[16][16];
Double_t thickness;
// new
Float_t leftE4,leftE24,leftEcal;
Float_t centE;

TVector3 dirLeft,dirCent;
Double_t angleLeft,angleCent;
//--------------------------------------------------------------------------------

void calcEnergies() {

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/he8_trigger2_cut.root");
  // ch->Add("/home/oem/work/data/exp1811/analysed/notarget_cut.root");
  cout << ch->GetEntries() << " total number of Entries" << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);
 
  ch->SetBranchAddress("aCsI.",&aCsI);
  // ch->SetBranchAddress("tCsI.",&tCsI);
  ch->SetBranchAddress("nCsI.",&nCsI);
  ch->SetBranchAddress("aCsI_cal.",&aCsI_cal);


  ch->SetBranchAddress("X_C.",&X_C);
  ch->SetBranchAddress("nX_C.",&nX_C);
  ch->SetBranchAddress("Y_C.",&Y_C);
  ch->SetBranchAddress("nY_C.",&nY_C);

  ch->SetBranchAddress("X_L.",&X_L);
  ch->SetBranchAddress("Y_L.",&Y_L);
  ch->SetBranchAddress("nY_L.",&nY_L);
  ch->SetBranchAddress("nX_L.",&nX_L);
  ch->SetBranchAddress("a20_L.",&a20_L);
  ch->SetBranchAddress("n20_L.",&n20_L);
  ch->SetBranchAddress("a20_L_uncorr.",&a20_L_uncorr); 

  ch->SetBranchAddress("nh3.",&nh3);
  ch->SetBranchAddress("nh3_s.",&nh3_s);
  ch->SetBranchAddress("nhe3.",&nhe3);

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

  ch->SetBranchAddress("flagLeft.",&flagLeft);
  ch->SetBranchAddress("flagCent.",&flagCent);
  
  TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_reco.root", "RECREATE");
  // TFile *fw = new TFile("/home/oem/work/data/exp1811/analysed/he8_emtpytarget_reco.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");
 
  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("aCsI_cal.",&aCsI_cal,"aCsI_cal/F");
  // ch->SetBranchAddress("tCsI.",&tCsI);
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

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

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nh3_s.",&nh3_s,"nh3_s/I");
  tw->Branch("nhe3.",&nhe3,"nhe3/I");

  tw->Branch("x1c.",&x1c,"x1c/F");
  tw->Branch("y1c.",&y1c,"y1c/F");
  tw->Branch("x2c.",&x2c,"x2c/F");
  tw->Branch("y2c.",&y2c,"y2c/F"); 
  tw->Branch("fXt.",&fXt,"fXt/F");
  tw->Branch("fYt.",&fYt,"fYt/F"); 
  
  tw->Branch("xLeft.",&xLeft,"xLeft/F");
  tw->Branch("yLeft.",&yLeft,"yLeft/F");
  tw->Branch("zLeft.",&zLeft,"zLeft/F");

  tw->Branch("xCent.",&xCent,"xCent/F");
  tw->Branch("yCent.",&yCent,"yCent/F");
  tw->Branch("zCent.",&zCent,"zCent/F");

  tw->Branch("flagLeft.",&flagLeft,"flagLeft/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");

  tw->Branch("leftE4.",&leftE4,"leftE4/F");
  tw->Branch("leftE24.",&leftE24,"leftE24/F");
  tw->Branch("leftEcal.",&leftEcal,"leftEcal/F");

  tw->Branch("centE.",&centE,"centE/F");

  readThickness();
  setTables();

  // for(Int_t nentry = 0; nentry<1000;nentry++) {
  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
    if(nentry%1000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);

    // if (flagLeft==0 && flagCent==0) continue;
    // if (nhe3==0 && nh3==0) continue;

    if(flagLeft) {
      dirLeft.SetXYZ(xLeft-fXt, yLeft-fYt, zLeft);
      angleLeft = dirLeft.Theta();
    }

    if(flagCent) {
      dirCent.SetXYZ(xCent-fXt, yCent-fYt, zCent);
      angleCent = dirCent.Theta();
    }

    leftE4 = 0;
    leftE24 = 0;
    leftEcal = 0;
    centE = 0;

    if(flagLeft && nhe3) {
      // Si

      leftE24 = f3HeSi->GetE0(X_L,20.5); // 3 micron - DL in thick

      thickness = fThicknessLeft[n20_L][nY_L] + 0.5; // 3 micron - DL in thick
      leftE4 = f3HeSi->GetE0(X_L,thickness);

      leftEcal = f3HeSi->GetE0(X_L,1.5) + a20_L_uncorr; // 4 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // cout << leftE24 << endl;

      // mylar
      thickness = 3.5/cos(angleLeft);

      leftE24 = f3HeMylar->GetE0(leftE24,thickness);
      leftE4 = f3HeMylar->GetE0(leftE4,thickness);
      leftEcal = f3HeMylar->GetE0(leftEcal,thickness);

      // cout << leftE24 << endl;

      // steel
      thickness = 6./cos(angleLeft);

      leftE24 = f3HeSteel->GetE0(leftE24,thickness);
      leftE4 = f3HeSteel->GetE0(leftE4,thickness);
      leftEcal = f3HeSteel->GetE0(leftEcal,thickness);
      // cout << leftE24 << endl;

      // deuterium target
      thickness = 3000./cos(angleLeft);

      leftE24 = f3HeTarget->GetE0(leftE24,thickness);
      leftE4 = f3HeTarget->GetE0(leftE4,thickness);
      leftEcal = f3HeTarget->GetE0(leftEcal,thickness);
      // cout << leftE24 << endl;
    }

    if(flagCent && nh3) {
      // Si
      thickness = 1500./cos(angleCent);
      centE = f3HSi->GetE0dE(X_C, thickness);

      // mylar
      thickness = 3.5/cos(angleCent);
      centE = f3HMylar->GetE0(centE,thickness);

      // steel
      thickness = 6./cos(angleCent);
      centE = f3HSteel->GetE0(centE,thickness);

      // deuterium target
      thickness = 3000./cos(angleCent);
      centE = f3HTarget->GetE0(centE,thickness);
      // cout << centE << endl;
    }

    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}


void readThickness() {
  cout << "thickness Left detector " << endl;
  TFile *f = new TFile("/home/oem/work/software/expertroot/input/parameters/thicknessLeft_new.root","READ");
  if (f->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThicknessLeft[i][j] = 20.;
        cout << fThicknessLeft[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    TH2F *hThick = (TH2F*)f->Get("hTh");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThicknessLeft[i][j] = hThick->GetBinContent(i+1,j+1);
        if (j==15) fThicknessLeft[i][j] = 100.;
        cout << fThicknessLeft[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f;

  return;
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
  f3HeTarget->SetEL(1, 0.0018431); // density in g/cm3
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
  f3HTarget->SetEL(1, 0.0018431); // density in g/cm3
  f3HTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
  f3HTarget->SetZP(1., 3.);   //alphas, Z, A
  f3HTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HTarget->SetDeltaEtab(300);
  //--------------------------------------------------------------------------------
  return;
}
