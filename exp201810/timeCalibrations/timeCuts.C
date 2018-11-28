void timeCuts(){
  
  TChain *ch = new TChain("er");
  ch->Add("/media/user/work/data/analysisexp1804/Ana11/new/he8_*");

  cout << "Found " << ch->GetEntries() << " entries" << endl;

  ofstream file; 
  file.open("parameters/tSSD20_L.cal");

  ofstream curves; 
  curves.open("parameters/curves/curv_tDSD_L_X.par");
//--------------------------------------------------------------------------------
  TF1 *f = new TF1("f","gaus",360,480);
  TF1 *pol = new TF1("pol","[0]/(x+[1]) + [2]",325,400);
  // pol->SetParLimits(1,-300,-400);
  // pol->SetParLimits(0,0.0001,0.01);
  // pol->SetParLimits(2,0.,0.01);

  TH1F *h[16];
  TGraph *g[16];

  TString cut,hdraw,Ecut,fullCut,histoName;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);
  c1->Divide(4,4);
  for(Int_t  i=0;i<16;i++) {
    c1->cd(i+1);
    hdraw.Form("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fEdep:ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fTime >> h_%d(60,360,420,100,0,0.01)",i+1);
    cut.Form("EventHeader.fTrigger==2 && ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fStripNb==%d",i);
    Ecut.Form("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fEdep>0.0005 && ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fEdep<0.07");
    histoName.Form("h_%d",i+1);
    fullCut = cut;// + TString(" && ") + Ecut;
    // cout << fullCut << endl;
    ch->Draw(hdraw.Data(),fullCut.Data(),"",1000000,0);
    //
    c1->Update();

    // hdraw.Form("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fTime >> h_%d(60,360,420)",i+1);
    // cut.Form("EventHeader.fTrigger==2 && ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fStripNb==%d",i);
    // Ecut.Form("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fEdep>0.025 && ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0.fEdep<0.07");
    // histoName.Form("h_%d",i+1);
    // fullCut = cut;// + TString(" && ") + Ecut;
    // // cout << fullCut << endl;
    // ch->Draw(hdraw.Data(),fullCut.Data(),"",10000000,0);
    // h[i] = (TH1F*)gPad->GetPrimitive(histoName.Data());
    // h[i]->Fit("f","R");
    // //
    // file << f->GetParameter(1) << "  0.3"<< endl; 
    // c1->Update();
  }
  c1->Print("parameters/tSSD20_L_fits.png");
  file.close();
  return;

  // hdraw.Form("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fEdep:ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fTime - BeamDetToFDigi2.fTime >> h(200,-50,50,150,0.005,0.07)");
  // cut.Form("EventHeader.fTrigger==2 && ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fStripNb==15");
  // Ecut.Form("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fEdep>0.005 && ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_X.fEdep<0.07");
  // fullCut = cut + TString(" && ") + Ecut;

  // ch->Draw(hdraw.Data(),fullCut.Data(),"",10000000,0);
}