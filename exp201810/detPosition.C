void detPosition(){

  TChain *t = new TChain("AnalysisxTree");
  t->Add("/media/user/work/data/exp201810/calib/Left_20um/dsd_20_l_03_*");
  if(!t) {
    return;
  }
  // t->SetMakeClass(1);
//--------------------------------------------------------------------------------
        // DRAW RAW spectra
  // TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);
  // TString hDraw;
  // for(Int_t i=0;i<16;i++) {
  //   c1->cd(i+1);  
  //   hDraw.Form("DSDX_L[%d]>>hx_%d(385,115,500)",i,i);
  //   t->Draw(hDraw.Data(),"",""); 
  //   c1->Update();
  // }
  // c1->Print("/home/user/Desktop/DSDX_L.png");

  // TCanvas *c2 = new TCanvas("c2","title",1800,1000);
  // c2->Divide(4,4);
  // for(Int_t i=0;i<16;i++) {
  //   c2->cd(i+1);
  //   hDraw.Form("DSDY_L[%d]>>hy_%d(385,115,500)",i,i);
  //   t->Draw(hDraw.Data(),"","");
  //   c2->Update();
  // }
  // c2->Print("/home/user/Desktop/DSDY_L.png");

  // TCanvas *c3 = new TCanvas("c3","title",1800,1000);
  // c3->Divide(4,4);
  // for(Int_t i=0;i<16;i++) {
  //   c3->cd(i+1);
  //   hDraw.Form("SSD20_L[%d]>>h20_%d(500,100,600)",i,i);
  //   t->Draw(hDraw.Data(),"","");
  //   c3->Update();
  // }
  // c3->Print("/home/user/Desktop/SQ20.png");


  //--------------------------------------------------------------------------------
  TH2I *hD = new TH2I("hD","profile DSSD",16,0,16,16,0,16);
  TH2I *hDc = new TH2I("hDc","profile DSSD calibrated",16,-30,30,16,-30,30);

  t->SetMakeClass(1);
  UShort_t DSDX[16],DSDY[16],DS20[16];
  t->SetBranchAddress("NeEvent.DSDX_L[16]",DSDX);
  t->SetBranchAddress("NeEvent.DSDY_L[16]",DSDY);
  t->SetBranchAddress("NeEvent.SSD20_L[16]",DS20);  

  Int_t multyX,multyY,multy20;
  Int_t nChX,nChY,nCh20;
  Double_t x,y;

  Int_t nentries = t->GetEntries();
  for(Int_t nentry=1;nentry<nentries;nentry++) {
    //--------------------------------------------------------------------------------
    // obnulenie
    multyX=0;
    multyY=0;
    multy20=0;
    nChX=-1;
    nChY=-1;
    nCh20=-1;
    //--------------------------------------------------------------------------------
    t->GetEntry(nentry);
    //calculate the multiplicity
    for(Int_t i=0;i<16;i++) {
      if(DSDX[i]>110){
        multyX++;
        nChX = i;
      }
      if(DSDY[i]>110){
        multyY++;
        nChY=i;
      } 
      if(DS20[i]>140){
        multy20++;
        nCh20=i;
      } 
    }
    if(multyX!=1 || multyY!=1 || multy20!=1) continue;
    //--------------------------------------------------------------------------------
    // cout << nChX <<" " << nChY << endl;
    hD->Fill(nChX,nChY);
    x = nChX*3.75 - 30;
    y = nChY*3.75 - 30;    
    hDc->Fill(x,y);

  }

  TFile *f = new TFile("/media/user/work/data/exp201810/workdir/thinDet/profile.root","RECREATE");
  f->cd();
  hD->Write();
  hDc->Write();  
  f->Close();


}