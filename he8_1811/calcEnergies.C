void readThickness();

TELoss f3HeSi;
TELoss f3HSi;

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t xLeft,yLeft,zLeft;
Float_t xCent,yCent,zCent;

Int_t nCsI;
Float_t aCsI,tCsI;

Float_t X_C,tX_C,Y_C,tY_C,X_L,Y_L,a20_L,tX_L,tY_L,t20_L,a20_R,Y_R,t20_R,tY_R,a20_L_uncorr;
Int_t nX_C,nY_C,nX_L,nY_L,n20_L,n20_R,nY_R;

Int_t flagLeft,flagCent,flagCent_arr;

Int_t nh3,nh3_s,nhe3;

Double_t fThicknessLeft[16][16];
Double_t thickness;
// new
Float_t leftE4,leftE24,leftEcal;
Float_t centE;


//--------------------------------------------------------------------------------

void calcEnergies() {
  f3HeSi.SetEL(1, 2.321); // density in g/cm3
  f3HeSi.AddEL(14., 28.086, 1);  //Z, mass
  f3HeSi.SetZP(2., 3.);   //alphas, Z, A
  f3HeSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HeSi.SetDeltaEtab(300);

  f3HSi.SetEL(1, 2.321); // density in g/cm3
  f3HSi.AddEL(14., 28.086, 1);  //Z, mass
  f3HSi.SetZP(1., 3.);   //alphas, Z, A
  f3HSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HSi.SetDeltaEtab(300);
  //--------------------------------------------------------------------------------


 //--------------------------------------------------------------------------------

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/he8_trigger2_cut.root");
  cout << ch->GetEntries() << " total number of Entries" << endl;
  //--------------------------------------------------------------------------------

  ch->SetBranchAddress("nh3.",&nh3);
  ch->SetBranchAddress("nh3_s.",&nh3_s);
  ch->SetBranchAddress("nhe3.",&nhe3);

  ch->SetBranchAddress("x1c.",&x1c);
  ch->SetBranchAddress("y1c.",&y1c);
  ch->SetBranchAddress("x2c.",&x2c);
  ch->SetBranchAddress("y2c.",&y2c); 
  ch->SetBranchAddress("fXt.",&fXt);
  ch->SetBranchAddress("fYt.",&fYt); 
  
  ch->SetBranchAddress("X_L.",&X_L);
  ch->SetBranchAddress("Y_L.",&Y_L);
  ch->SetBranchAddress("nY_L.",&nY_L);
  ch->SetBranchAddress("nX_L.",&nX_L);
  ch->SetBranchAddress("a20_L.",&a20_L);
  ch->SetBranchAddress("n20_L.",&n20_L);
  ch->SetBranchAddress("a20_L_uncorr.",&a20_L_uncorr); 

  ch->SetBranchAddress("X_C.",&X_C);
  ch->SetBranchAddress("nX_C.",&nX_C);
  ch->SetBranchAddress("Y_C.",&Y_C);
  ch->SetBranchAddress("nY_C.",&nY_C);

  ch->SetBranchAddress("flagLeft.",&flagLeft);
  ch->SetBranchAddress("flagCent.",&flagCent);
  ch->SetBranchAddress("flagCent_arr.",&flagCent_arr);

  TFile *fw = new TFile("/media/user/work/data/Analysed1811/selected/he8_reco.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nh3_s.",&nh3_s,"nh3_s/I");
  tw->Branch("nhe3.",&nhe3,"nhe3/I");

  tw->Branch("flagLeft.",&flagLeft,"flagLeft/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  tw->Branch("flagCent_arr.",&flagCent_arr,"flagCent_arr/I");

  tw->Branch("leftE4.",&leftE4,"leftE4/F");
  tw->Branch("leftE24.",&leftE24,"leftE24/F");
  tw->Branch("leftEcal.",&leftEcal,"leftEcal/F");

  tw->Branch("centE.",&centE,"centE/F");

  // cout << f3HeSi.GetE0(5.,20.) << endl;
  readThickness();

// cout << f3HeSi.GetE0dE(10., 1500.) << endl;
// return;
  // for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
  for(Int_t nentry = 0; nentry<1000;nentry++) {
    ch->GetEntry(nentry);

    leftE4 = 0;
    leftE24 = 0;
    leftEcal = 0;
    centE = 0;

    if(flagLeft && nhe3) {
      // Si
      f3HeSi.SetEL(1, 2.321); // density in g/cm3
      f3HeSi.AddEL(14., 28.086, 1);  //Z, mass

      leftE24 = X_L + f3HeSi.GetE0(a20_L,24.);

      thickness = fThicknessLeft[n20_L][nY_L] + 4.;
      leftE4 = X_L + f3HeSi.GetE0(a20_L,thickness);

      leftEcal = X_L + a20_L_uncorr;

      // mylar
      f3HeSi.SetEL(1, 1.39); // density in g/cm3
      f3HeSi.AddEL(6., 12.0096, 0.45);  //Z, mass
      f3HeSi.AddEL(1., 1.00784, 0.36);
      f3HeSi.AddEL(8., 15.99903, 0.19);

      // steel
      f3HeSi.SetEL(1, 8.0); // density in g/cm3
      f3HeSi.AddEL(24., 51.9962, 0.07);  //Z, mass
      f3HeSi.AddEL(26., 55.845, 0.74);  
      f3HeSi.AddEL(28., 58.6934, 0.19);  
      

    }

    if(flagLeft && nh3) {
      centE = X_C + f3HSi.GetE0dE(X_C, 1500.);
    }


  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}


void readThickness() {
  cout << "thickness Left detector " << endl;
  TFile *f = new TFile("/media/user/work/macro/he8_1811/parameters/thicknessLeft_new.root","READ");
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
        cout << fThicknessLeft[i][j] << " ";
      }
      cout << endl;
    }
  }
  delete f;

  return;
}
