Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;
Float_t x1t,y1t,x2t,y2t,x3t,y3t,x4t,y4t,xCt,yCt;
Int_t nh3,nhe3_1,nhe3_2,nhe3_3,nhe3_4;

Double_t planeFunc(Double_t *x, Double_t *par);

TPolyLine3D *setupLine[32];

void drawFrame(Float_t distance);
void drawSensitive(Float_t distance);
void drawHole(Float_t distance);

void scheme3D() {

  gStyle->SetOptStat(0);
  gStyle->SetCanvasPreferGL(kTRUE);

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/newCal/h7_*");

  ch->SetBranchAddress("fXt.",&fXt);
  ch->SetBranchAddress("fYt.",&fYt); 

  ch->SetBranchAddress("xCt",&xCt);
  ch->SetBranchAddress("yCt",&yCt);

  ch->SetBranchAddress("nh3.",&nh3);

  TString hDraw,hCut;

  TCanvas *c1 = new TCanvas("c1","setup scheme",1000,1000);
  c1->cd();

  ch->SetMarkerStyle(7);

  TH3F *canVas = new TH3F("canVas","background hist",100,-100,100,100,-100,100,100,-1,400);
  canVas->Draw();

  drawFrame(173.);
  drawFrame(188.);
  drawFrame(198.);

  drawSensitive(173.);

  drawHole(201.);

  Int_t nEvents = 30000;

  ch->SetLineColor(kBlack);  
  ch->Draw("0:fYt:fXt >> hTarget(60,-10,10,60,-10,10,1,-0.3,0.3)","trigger!=1 && nh3","same",nEvents,0);

  ch->SetMarkerColor(kBlue);
  ch->Draw("323:yCt:xCt >> hCent(64,-32,32,64,-32,32,1,322,324)","trigger!=1 && nh3","same",nEvents,0);


  TPolyLine3D *traj;

  Float_t xt[2],yt[2],zt[2];

  for(Int_t i = 0;i<nEvents;i++) {
    ch->GetEntry(i);
    if (nh3==0) continue;

    xt[0] = fXt;
    xt[1] = xCt;
    yt[0] = fYt;
    yt[1] = yCt;
    zt[0] = 0.;
    zt[1] = 323.;

    traj = new TPolyLine3D(2, xt, yt, zt);
    traj->Draw("same");
  }


return;

}

void drawFrame(Float_t distance) {

  Float_t x[16][2],y[16][2],z[2];

  z[0] = distance;
  z[1] = distance;

  for(Int_t i=0;i<16;i++) {
    setupLine[i] = new TPolyLine3D(2);
    setupLine[i]->SetLineColor(kGreen+3);
    setupLine[i]->SetLineWidth(4);
  }

  x[0][0] = -12.5;
  y[0][0] = -12.5;
  x[0][1] = -12.5;
  y[0][1] = 47.5;

  x[1][0] = -12.5;
  y[1][0] = 47.5;
  x[1][1] = -72.5;
  y[1][1] = 47.5;

  x[2][0] = -72.5;
  y[2][0] = 47.5;
  x[2][1] = -72.5;
  y[2][1] = -12.5;

  x[3][0] = -72.5;
  y[3][0] = -12.5;
  x[3][1] = -12.5;
  y[3][1] = -12.5;

//
  x[4][0] = 12.5;
  y[4][0] = -12.5;
  x[4][1] = -47.5;
  y[4][1] = -12.5;

  x[5][0] = -47.5;
  y[5][0] = -12.5;
  x[5][1] = -47.5;
  y[5][1] = -72.5;

  x[6][0] = -47.5;
  y[6][0] = -72.5;
  x[6][1] = 12.5;
  y[6][1] = -72.5;

  x[7][0] = 12.5;
  y[7][0] = -72.5;
  x[7][1] = 12.5;
  y[7][1] = -12.5;

// 
  x[8][0] = 12.5;
  y[8][0] = 12.5;
  x[8][1] = 72.5;
  y[8][1] = 12.5;

  x[9][0] = 72.5;
  y[9][0] = 12.5;
  x[9][1] = 72.5;
  y[9][1] = -47.5;

  x[10][0] = 72.5;
  y[10][0] = -47.5;
  x[10][1] = 12.5;
  y[10][1] = -47.5;

  x[11][0] = 12.5;
  y[11][0] = -47.5;
  x[11][1] = 12.5;
  y[11][1] = 12.5;
// 
  x[12][0] = -12.5;
  y[12][0] = 12.5;
  x[12][1] = -12.5;
  y[12][1] = 72.5;

  x[13][0] = -12.5;
  y[13][0] = 72.5;
  x[13][1] = 47.5;
  y[13][1] = 72.5;

  x[14][0] = 47.5;
  y[14][0] = 72.5;
  x[14][1] = 47.5;
  y[14][1] = 12.5;

  x[15][0] = 47.5;
  y[15][0] = 12.5;
  x[15][1] = -12.5;
  y[15][1] = 12.5;

  for (Int_t j=0;j<16;j++) {
    for(Int_t i=0;i<2;i++) {
      setupLine[j]->SetPoint(i, x[j][i], y[j][i], z[i]);
    }
    setupLine[j]->Draw("same");
  }

}


void drawSensitive(Float_t distance) {

  Float_t x[16][2],y[16][2],z[2];

  z[0] = distance;
  z[1] = distance;

  for(Int_t i=0;i<16;i++) {
    setupLine[i] = new TPolyLine3D(2);
    setupLine[i]->SetLineColor(kGray+2);
    setupLine[i]->SetLineWidth(4);
  }

  x[0][0] = -21.3;
  y[0][0] = -4.2;
  x[0][1] = -71.3;
  y[0][1] = -4.2;

  x[1][0] = -71.3;
  y[1][0] = -4.2;
  x[1][1] = -71.3;
  y[1][1] = 45.8;

  x[2][0] = -71.3;
  y[2][0] = 45.8;
  x[2][1] = -21.3;
  y[2][1] = 45.8;

  x[3][0] = -21.3;
  y[3][0] = 45.8;
  x[3][1] = -21.3;
  y[3][1] = -4.2;

//
  x[4][0] = 4.2;
  y[4][0] = -21.3;
  x[4][1] = -45.8;
  y[4][1] = -21.3;

  x[5][0] = -45.8;
  y[5][0] = -21.3;
  x[5][1] = -45.8;
  y[5][1] = -71.3;

  x[6][0] = -45.8;
  y[6][0] = -71.3;
  x[6][1] = 4.2;
  y[6][1] = -71.3;

  x[7][0] = 4.2;
  y[7][0] = -71.3;
  x[7][1] = 4.2;
  y[7][1] = -21.3;

// 
  x[8][0] = 21.3;
  y[8][0] = 4.2;
  x[8][1] = 71.3;
  y[8][1] = 4.2;

  x[9][0] = 71.3;
  y[9][0] = 4.2;
  x[9][1] = 71.3;
  y[9][1] = -45.8;

  x[10][0] = 71.3;
  y[10][0] = -45.8;
  x[10][1] = 21.3;
  y[10][1] = -45.8;

  x[11][0] = 21.3;
  y[11][0] = -45.8;
  x[11][1] = 21.3;
  y[11][1] = 4.2;
// 
  x[12][0] = -4.2;
  y[12][0] = 21.3;
  x[12][1] = 45.8;
  y[12][1] = 21.3;

  x[13][0] = 45.8;
  y[13][0] = 21.3;
  x[13][1] = 45.8;
  y[13][1] = 71.3;

  x[14][0] = 45.8;
  y[14][0] = 71.3;
  x[14][1] = -4.2;
  y[14][1] = 71.3;

  x[15][0] = -4.2;
  y[15][0] = 71.3;
  x[15][1] = -4.2;
  y[15][1] = 21.3;

  for (Int_t j=0;j<16;j++) {
    for(Int_t i=0;i<2;i++) {
      setupLine[j]->SetPoint(i, x[j][i], y[j][i], z[i]);
    }
    setupLine[j]->Draw("same");
  }

}

void drawHole(Float_t distance) {

  Float_t x[4][2],y[4][2],z[2];

  z[0] = distance;
  z[1] = distance;

  for(Int_t i=0;i<16;i++) {
    setupLine[i] = new TPolyLine3D(2);
    setupLine[i]->SetLineColor(kRed+2);
    setupLine[i]->SetLineWidth(4);
  }

  x[0][0] = -12.5;
  y[0][0] = -12.5;
  x[0][1] = 12.5;
  y[0][1] = -12.5;

  x[1][0] = 12.5;
  y[1][0] = -12.5;
  x[1][1] = 12.5;
  y[1][1] = 12.5;

  x[2][0] = 12.5;
  y[2][0] = 12.5;
  x[2][1] = -12.5;
  y[2][1] = 12.5;

  x[3][0] = -12.5;
  y[3][0] = 12.5;
  x[3][1] = -12.5;;
  y[3][1] = -12.5;

  for (Int_t j=0;j<4;j++) {
    for(Int_t i=0;i<2;i++) {
      setupLine[j]->SetPoint(i, x[j][i], y[j][i], z[i]);
    }
    setupLine[j]->Draw("same");
  }

}

