void curveTimes(){
  TChain *ch = new TChain("er");
  ch->Add("/media/user/work/data/analysisexp1804/Ana11/new/he8_*");

  cout << "Found " << ch->GetEntries() << " entries" << endl;
//--------------------------------------------------------------------------------
// reading input pars
  Float_t shift[16],temp;
  ifstream myfile;
  TString line;
  Int_t count = 0;
//  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/SQY_L.cal");
  myfile.open("/media/user/work/macro/exp201810/timeCalibrations/parameters/tDSD_L_X.cal");
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g %g", shift+count, &temp);
    count++;
  }

  cout << endl << " time pars for strips" << endl;
  for(Int_t i=0;i<16;i++) cout << shift[i] << endl; 
  //--------------------------------------------------------------------------------
  TF1 *pol = new TF1("pol","[0]/(x+[1]) + [2]",-5.,25.);
  pol->SetParLimits(1,-2,5);
  pol->SetParLimits(0,0.001,10.);
  pol->SetParLimits(2,0.,0.01);

  TH1F *h[16];
  TGraph *g[16];

  TString cut,hdraw,Ecut,fullCut,histoName,lPar;
  TString X,Y,histo,total;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);
  c1->Divide(4,4);
  for(Int_t  i=0;i<16;i++) {
    c1->cd(i+1);
    lPar = std::to_string(shift[i]);
    // hdraw.Form("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fEdep:ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fTime - BeamDetToFDigi2.fTime >> h_%d(80,40,120,100,0.001,0.005)",i+1);
    Y.Form("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fEdep:");
    X.Form("(ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fTime-");
    X = X + lPar + TString(")");
    histo.Form(">> h_%d(120,-10,50,200,0.0,0.07)",i+1);

    hdraw = Y+X+histo;

    cut.Form("EventHeader.fTrigger==2 && ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fStripNb==%d",i);
    Ecut.Form("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fEdep>0.005 && ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fEdep<0.05");
    // histoName.Form("h_%d",i+1);
    fullCut = cut + TString(" && ") + Ecut;
    ch->Draw(hdraw.Data(),fullCut.Data(),"",1000000);
    g[i] = (TGraph*)gPad->GetPrimitive("Graph");
    g[i]->Fit("pol","R");
    c1->Update();
  }
return;

}