void readThickness();
void setTables();
void zeroVars();

void calculateCoordinates();
void tritonProjection(Float_t *x,Float_t *y,Double_t distance);

TELoss *f3HeSi;
TELoss *f3HeMylar;
TELoss *f3HeSteel;
TELoss *f3HeTarget;

TELoss *f3HSi;
TELoss *f3HMylar;
TELoss *f3HSteel;
TELoss *f3HTarget;
TELoss *f3HPlastic;
TELoss *f3HKeramic;

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
Float_t frame1X,frame1Y,frame2X,frame2Y,frame3X,frame3Y;

Float_t tritonX1,tritonY1;
Float_t tritonX2,tritonY2;
Float_t tritonX3,tritonY3;
Float_t tritonX4,tritonY4;

// flags
Bool_t timesToF,timesMWPC;

Double_t fThickness1[16][16],fThickness2[16][16],fThickness3[16][16],fThickness4[16][16];

Int_t flag1,flag2,flag3,flag4,flagCent;
Int_t nh3,nhe3_1,nhe3_2,nhe3_3,nhe3_4;

Float_t e_1,e_2,e_3,e_4;
Float_t centE;

Float_t th_he3_1,th_he3_2,th_he3_3,th_he3_4,th_h3;
Float_t phi_he3_1,phi_he3_2,phi_he3_3,phi_he3_4,phi_h3;

Float_t thickness;
//--------------------------------------------------------------------------------

void calcEnergies(Int_t nRun=0) {

  TChain *ch = new TChain("tree");

  TString inPutFileName;
  inPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/selected/newCal/h7_%d_cut.root",nRun);
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


  TString outPutFileName;
  outPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/calcEnergies/thinVar/h7_%d_reco.root",nRun);

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

  // readThickness();
  setTables();

  Float_t thCoeff1 = 0.94;
  Float_t thCoeff2 = 0.98;
  Float_t thCoeff3 = 0.97;
  Float_t thCoeff4 = 0.88;

  // for(Int_t nentry = 0; nentry<1000;nentry++) {
  for(Int_t nentry = 0; nentry<ch->GetEntries();nentry++) {
    if(nentry%100000==0) cout << "#ENTRY " << nentry << "#" << endl;
    // cout << nentry << endl;
    ch->GetEntry(nentry);

    zeroVars(); 

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
      thickness = 3000./cos(th_he3_1);
      e_1 = f3HeTarget->GetE0(e_1,thickness);
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
      thickness = 3000./cos(th_he3_2);
      e_2 = f3HeTarget->GetE0(e_2,thickness);
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
      thickness = 3000./cos(th_he3_3);
      e_3 = f3HeTarget->GetE0(e_3,thickness);
    }

    if(nhe3_4) {
      // Si
      // e_4 = f3HeSi->GetE0(a20_4_un,4./cos(th_he3_4)) + a1_4; // 1.5 micron - DL between thin and thick sensitive areas (DL thin about 1 mik)
      // e_4 = f3HeSi->GetE0(e_4,0.5/cos(th_he3_4)); //dl of thin det

      e_4 = a1_4;

      thickness = (fThickness4[n20_4][n1_4]*thCoeff3+2.27)/cos(th_he3_4); // 0.5 - DL of thick det
      e_4 = f3HeSi->GetE0(e_4,thickness);   

      // mylar
      thickness = 3.5/cos(th_he3_4);
      e_4 = f3HeMylar->GetE0(e_4,thickness);

      // steel
      thickness = 6./cos(th_he3_4);
      e_4 = f3HeSteel->GetE0(e_4,thickness);

      // deuterium target
      thickness = 3000./cos(th_he3_4);
      e_4 = f3HeTarget->GetE0(e_4,thickness);
    }

    if(nh3) {
      // Si
      centE = arCsI[nCsI_track] + X_C; 

      // if (frame3X>12.5 || frame3X<-12.5 || frame3Y>12.5 || frame3Y<-12.5) {
      //   if (frame3X<-12.5 && frame3Y>-12.5) { // 1 telescope
      //     if (frame3X<-18.5 && frame3Y>-6.5) { // Si sensitive area

      //     }
      //     else { // FR4 frame

      //     }
      //   }
      //   cout << "reco triton in the 3 plane" << endl;
      // }

      // if (frame2X>12.5 || frame2X<-12.5 || frame2Y>12.5 || frame2Y<-12.5) {
      //   cout << "reco triton in the 2 plane" << endl;
      // }

      // if (frame1X>12.5 || frame1X<-12.5 || frame1Y>12.5 || frame1Y<-12.5) {
      //   cout << "reco triton in the 1 plane" << endl;
      // }

      // mylar
      thickness = 3.5/cos(th_h3);
      centE = f3HMylar->GetE0(centE,thickness);

      // steel
      thickness = 6./cos(th_h3);
      centE = f3HSteel->GetE0(centE,thickness);

      // deuterium target
      thickness = 3000./cos(th_h3);
      centE = f3HTarget->GetE0(centE,thickness);
    }

    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void readThickness() {
  cout << "thickness of the first detector " << endl;
  TFile *f1 = new TFile("/home/ivan/work/macro/h7_1904/parameters/thicknessMap_calib_90_all_SSD_1m_1_real.root","READ");
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
  TFile *f2 = new TFile("/home/ivan/work/macro/h7_1904/parameters/thicknessMap_alltel_90_SSD_1m_2_real.root","READ");
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
  TFile *f3 = new TFile("/home/ivan/work/macro/h7_1904/parameters/thicknessMap_calib_90_all_SSD_1m_3_switch_new.root","READ");
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
  TFile *f4 = new TFile("/home/ivan/work/macro/h7_1904/parameters/thicknessMap_calib_90_all_SSD_1m_4_real.root","READ");
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
  return;
}

void zeroVars() {

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
