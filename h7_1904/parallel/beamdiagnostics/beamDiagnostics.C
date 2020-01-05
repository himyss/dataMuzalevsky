void calcVectorCent(Int_t nX,Int_t nY);
void calcFrameCoordinates(Float_t* x, Float_t* y,Float_t distanance);
void calculateBeam();

void zeroVars();
void checkToF();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void fillSi();

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC;
Int_t wirex1,wirex2,wirey1,wirey2;

Float_t X_C,tX_C,Y_C,tY_C;
Int_t nX_C,nY_C;
//
Float_t DSD_X[32],DSD_Y[32];
Float_t tDSD_X[32],tDSD_Y[32];

// reconstructed

Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t frame1X,frame1Y,frame2X,frame2Y,frame3X,frame3Y;
// flags
Bool_t timesToF,timesMWPC;

Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;

TLorentzVector he8;
TELoss f8HeSi;
Float_t px,py,pz,pBeam;
Float_t energy;
Float_t thetahe8;
Float_t phihe8;

void beamDiagnostics(Int_t nFile=0) {

  f8HeSi.SetEL(1, 2.321); // density in g/cm3
  f8HeSi.AddEL(14., 28.086, 1);  //Z, mass
  f8HeSi.SetZP(2., 8.);   //alphas, Z, A
  f8HeSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
  f8HeSi.SetDeltaEtab(300);

  TChain *ch = new TChain("tree");
  TString inPutFileName;
  inPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/calibrated/newCal/h7_%d_cal.root",nFile);
  ch->Add(inPutFileName.Data());

  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);

  ch->SetBranchAddress("tMWPC.",&tMWPC);
  ch->SetBranchAddress("wirex1.",&wirex1);
  ch->SetBranchAddress("wirex2.",&wirex2);
  ch->SetBranchAddress("wirey1.",&wirey1);
  ch->SetBranchAddress("wirey2.",&wirey2);

  ch->SetBranchAddress("DSD_X",&DSD_X);
  ch->SetBranchAddress("tDSD_X",&tDSD_X);
  ch->SetBranchAddress("DSD_Y",&DSD_Y); 
  ch->SetBranchAddress("tDSD_Y",&tDSD_Y);

  TString outPutFileName;
  outPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/beamDiagnostics/beamHe8_%d.root",nFile);
  // outPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/selected/test.root",nFile);

  TFile *fw = new TFile(outPutFileName.Data(), "RECREATE");
  // TFile *fw = new TFile("test.root", "RECREATE");
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

  tw->Branch("nX_C.",&nX_C,"nX_C/I");
  tw->Branch("nY_C.",&nY_C,"nY_C/I");

  tw->Branch("frame1X",&frame1X,"frame1X/F");
  tw->Branch("frame2X",&frame2X,"frame2X/F");
  tw->Branch("frame3X",&frame3X,"frame3X/F");
  tw->Branch("frame1Y",&frame1Y,"frame1Y/F");
  tw->Branch("frame2Y",&frame2Y,"frame2Y/F");
  tw->Branch("frame3Y",&frame3Y,"frame3Y/F");

  tw->Branch("xCt",&xCt,"xCt/F");
  tw->Branch("yCt",&yCt,"yCt/F");
  tw->Branch("fXt",&fXt,"fXt/F");
  tw->Branch("fYt",&fYt,"fYt/F");

  tw->Branch("px",&px,"px/F");
  tw->Branch("py",&py,"py/F");
  tw->Branch("pz",&pz,"pz/F");
  tw->Branch("pBeam",&pBeam,"pBeam/F");
  tw->Branch("energy",&energy,"energy/F");

  tw->Branch("thetahe8",&thetahe8,"thetahe8/F");
  tw->Branch("phihe8",&phihe8,"phihe8/F");

  Float_t xCent,yCent;
  xCent = 0.5;
  yCent = 1;

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<1000;nentry++) {     
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);

    if (trigger!=1) continue;

    zeroVars();

    MWPCprojection();
    if ( ((fXt-xCent)*(fXt-xCent) + (fYt-yCent)*(fYt-yCent))>9*9 ) continue;

    calculateBeam();

    fillSi();

    if (nX_C>-1 && nY_C>-1) {
      calcVectorCent(nX_C,nY_C);
      calcFrameCoordinates(&frame1X,&frame1Y,173.);
      calcFrameCoordinates(&frame2X,&frame2Y,188.);
      calcFrameCoordinates(&frame3X,&frame3Y,198.);      
    }


    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {

  frame1X = -1000.;
  frame2X = -1000.;
  frame3X = -1000.;
  frame1Y = -1000.;
  frame2Y = -1000.;
  frame3Y = -1000.;

  nX_C = -1;
  nY_C = -1;

  x1c = -50;
  y1c = -50;
  x2c = -50;
  y2c = -50;

  fXt = -100;
  fYt = -100;

  xCt = -1000;
  yCt = -1000;

  px = -1000;
  py = -1000;
  pz = -1000;
  pBeam = -1000;

  energy = -1000;
  thetahe8 = -1000;
  phihe8 = -1000;

}

void MWPCprojection() {

  const Float_t fMWPCwireStepX1 = -1.25;
  const Float_t fMWPCwireStepY1 = 1.25;   //step between two wires
  const Float_t fMWPCwireStepX2 = -1.25;    //step between two wires
  const Float_t fMWPCwireStepY2 = 1.25;   //step between two wires

  const Float_t fMWPC1_X_offset = 0.;
  const Float_t fMWPC1_Y_offset = 0.;
  // const Float_t fMWPC2_X_offset = 0;
  // const Float_t fMWPC2_Y_offset = 0;

  const Float_t fMWPC2_X_offset = 0.112500;
  const Float_t fMWPC2_Y_offset = 0.537500;

  const Float_t fMWPCz1 = -815.;  //z coordinate of the center of MWPC1
  const Float_t fMWPCz2 = -270.;  //z coordinate of the center of MWPC2

  Float_t xtc, ytc;
  //cluster multiplicity equal to 1
  x1c = GetPosition(wirex1, fMWPCwireStepX1, fMWPC1_X_offset);
  y1c = GetPosition(wirey1, fMWPCwireStepY1, fMWPC1_Y_offset);

  x2c = GetPosition(wirex2, fMWPCwireStepX2, fMWPC2_X_offset);
  y2c = GetPosition(wirey2, fMWPCwireStepY2, fMWPC2_Y_offset);

  xtc = x1c - (x2c -x1c)*fMWPCz1/(fMWPCz2-fMWPCz1);
  ytc = y1c + (xtc - x1c)*(y2c-y1c)/(x2c-x1c);

  fXt = xtc;
  fYt = ytc;
}

Float_t GetPosition(Float_t wire, Float_t wireStep,
    Float_t planeOffset) {
  //TODO: number of wires (16) as parameter
  //TODO: omit gRandom
  return (wire - 16.5)*wireStep + planeOffset;
}


void fillSi() {
 
  Int_t multy = 0;
  Float_t amp = -1;
  Float_t time = -1;
  Int_t channel = -1;

  for(Int_t i=0;i<32;i++) {
    if (DSD_X[i]>1. && tDSD_X[i]>0){ // 1 MeV  offline-threshold
      amp = DSD_X[i];
      time = tDSD_X[i];
      channel = i;
      multy++;
    } 
  }
  if (multy==1) {
    X_C = amp;
    tX_C = time;
    nX_C = channel;
  }

  multy = 0;
  amp = -1;
  time = -1;
  channel = -1;
  for(Int_t i=0;i<32;i++) {
    if (DSD_Y[i]>1. && tDSD_Y[i]>0){ // 1 MeV  offline-threshold
      amp = DSD_Y[i];
      time = tDSD_Y[i];
      channel = i;
      multy++;
    } 
  }
  if (multy==1) {
    Y_C = amp;
    tY_C = time;
    nY_C = channel;
  }

}

void calcVectorCent(Int_t nX,Int_t nY) {

  Double_t xC = 31. - nX*64./32;
  Double_t yC = 31. - nY*64./32;
  Double_t zC = 323.;

  TVector3 tel1V;
  tel1V.SetXYZ(xC - fXt,yC - fYt,zC);

  xCt = xC;
  yCt = yC;

  return;
}

void calcFrameCoordinates(Float_t* x, Float_t* y,Float_t distanance) {
  *x = fXt + (xCt-fXt)*distanance/323.;
  *y = fYt + (yCt-fYt)*distanance/323.;
}

void calculateBeam() {

  TVector3 dir;
  dir.SetXYZ(fXt-x1c,fYt-y1c,815.);
  // dir.SetXYZ(x2c-x1c,y2c-y1c,545.);  
  phihe8 = dir.Phi();
  thetahe8 = dir.Theta();

  Float_t mass = 7.482538;

  Double_t velocity = 12320./(tF5-tF3 + 68.475);
  Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  Double_t kinEnergy = mass*((1/beta) - 1);

  kinEnergy =  f8HeSi.GetE(1000*kinEnergy, 644.)/1000.;
  energy = kinEnergy;

  pBeam = sqrt(kinEnergy*kinEnergy + 2*kinEnergy*mass);

  pBeam = TMath::Abs(pBeam);
  he8.SetXYZM(pBeam*TMath::Sin(thetahe8)*TMath::Cos(phihe8), pBeam*TMath::Sin(thetahe8)*TMath::Sin(phihe8), pBeam*TMath::Cos(thetahe8) ,mass);

  px = he8.Px();
  py = he8.Py();
  pz = he8.Pz();

  return;
}
