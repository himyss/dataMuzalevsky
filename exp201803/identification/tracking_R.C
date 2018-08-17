void tracking_R() { 

  TChain *t = new TChain("AnalysisxTree");
  //TTree*    t;

  Float_t CsI_L[16],tCsI_L[16],CsI_R[16],tCsI_R[16],SQX_L[32],SQY_L[16],tSQX_L[32],tSQY_L[16],SQX_R[32],SQY_R[16],tSQX_R[32],tSQY_R[16],SQ20[16],tSQ20[16],F3[4],tF3[4],F5[4],tF5[4],
          nx1,nx2,ny1,ny2,x1[32],x2[32],y1[32],y2[32];


  UShort_t   NeEvent_CsI_L[16],NeEvent_tCsI_L[16],NeEvent_CsI_R[16],NeEvent_tCsI_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16],
             NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_SQ20[16],NeEvent_tSQ20[16],
             NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_nx1,NeEvent_nx2,NeEvent_ny1,NeEvent_ny2,NeEvent_x1[32],NeEvent_x2[32],NeEvent_y1[32],NeEvent_y2[32];

  TBranch *b_NeEvent_CsI_L,*b_NeEvent_tCsI_L,*b_NeEvent_CsI_R,*b_NeEvent_tCsI_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,
          *b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_SQ20,*b_NeEvent_tSQ20,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,
          *b_NeEvent_nx1,*b_NeEvent_nx2,*b_NeEvent_ny1,*b_NeEvent_ny2,*b_NeEvent_x1,*b_NeEvent_x2,*b_NeEvent_y1,*b_NeEvent_y2,*b_NeEvent_trigger;

  Int_t NeEvent_trigger,trigger;

  Long64_t nentries1;
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,mult20,multY_Lt,multX_Lt,multY_Rt,multX_Rt,mult20t,multCsi_R,multCsi_L,timeF5,thresh_X,thresh_Y,thresh_CsI,nCh_L,nCh_R,Nst_X,Nst_Y;
  bool ToFflag;
  Float_t maxCsI_R,maxCsI_L;

  Float_t x1p,x2p,y1p,y2p,yt,xt,zt,xd,yd,zd,xCs,yCs,zCs;
  Int_t nCs,nCsM;

  Float_t xCs0,yCs0,zCs0,xCsi_max,xCsi_min,yCsi_max,yCsi_min,aCsiM; //!

  // Creating outfile,outtree
  TFile *fw = new TFile("tracking_r.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  /*tw->Branch("CsI_L",&CsI_L,"CsI_L[16]/F");
  tw->Branch("tCsI_L",&tCsI_L,"tCsI_L[16]/F");
  tw->Branch("CsI_R",&CsI_R,"CsI_R[16]/F");
  tw->Branch("tCsI_R",&tCsI_R,"tCsI_R[16]/F");
  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("tSQX_L",&tSQX_L,"tSQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("tSQY_L",&tSQY_L,"tSQY_L[16]/F");
  tw->Branch("SQX_R",&SQX_R,"SQX_R[32]/F");
  tw->Branch("tSQX_R",&tSQX_R,"tSQX_R[32]/F");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
  tw->Branch("tSQY_R",&tSQY_R,"tSQY_R[16]/F");
  tw->Branch("SQ20",&SQ20,"SQ20[16]/F");
  tw->Branch("tSQ20",&tSQ20,"tSQ20[16]/F");
  tw->Branch("F3",&F3,"F3[4]/F");
  tw->Branch("tF3",&tF3,"tF3[4]/F");
  tw->Branch("F5",&F5,"F5[4]/F");
  tw->Branch("tF5",&tF5,"tF5[4]/F");
  tw->Branch("nx1",&nx1,"nx1/F");
  tw->Branch("ny1",&ny1,"ny1/F");
  tw->Branch("nx2",&nx2,"nx2/F");
  tw->Branch("ny2",&ny2,"ny2/F");
  tw->Branch("x1",&x1,"x1[32]/F");
  tw->Branch("x2",&x2,"x2[32]/F");
  tw->Branch("y1",&y1,"y1[32]/F");
  tw->Branch("y2",&y2,"y2[32]/F");
  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("multY_L",&multY_L,"multY_L/I");
  tw->Branch("multX_L",&multX_L,"multX_L/I");*/

  tw->Branch("xt",&xt,"xt/F");
  tw->Branch("yt",&yt,"yt/F");
  tw->Branch("zt",&zt,"zt/F");
  tw->Branch("xd",&xd,"xd/F");
  tw->Branch("yd",&yd,"yd/F");
  tw->Branch("zd",&zd,"zd/F");
  tw->Branch("xCs",&xCs,"xCs/F");
  tw->Branch("yCs",&yCs,"yCs/F");
  tw->Branch("zCs",&zCs,"zCs/F");

  tw->Branch("xCs0",&xCs0,"xCs0/F");
  tw->Branch("yCs0",&yCs0,"yCs0/F");
  tw->Branch("zCs0",&zCs0,"zCs0/F");

  tw->Branch("nCs",&nCs,"nCs/I");
  tw->Branch("nCsM",&nCsM,"nCsM/I");

  tw->Branch("multX_R",&multX_R,"multX_R/I");
  tw->Branch("multY_R",&multY_R,"multY_R/I");

  tw->Branch("trigger",&trigger,"trigger/I");

  t->Add("/home/user/work/data/exp1804/h5_14_00*");
  nentries1 = t->GetEntries();
  cout << " Number of InPut entries: "<< nentries1 << endl;

  //for(Int_t n=10;n<12;n++) {
  //  input_file.Form("/media/analysis_nas/exp201804/rootfiles/h5_14_00%d.root",n);   
  //  f[n] = new TFile(input_file.Data());
  //  if (f[n]->IsZombie()) {
   //   cerr << "Input file was not opened " << input_file.Data() << endl;
   //   return 1;
   // }
  //cout <<  input_file.Data() << " filename " << endl;
  //f[n]->GetObject("AnalysisxTree",t);
  t->SetMakeClass(1);

  t->SetBranchAddress("NeEvent.CsI_L[16]", NeEvent_CsI_L, &b_NeEvent_CsI_L);
  t->SetBranchAddress("NeEvent.tCsI_L[16]", NeEvent_tCsI_L, &b_NeEvent_tCsI_L);
  t->SetBranchAddress("NeEvent.CsI_R[16]", NeEvent_CsI_R, &b_NeEvent_CsI_R);
  t->SetBranchAddress("NeEvent.tCsI_R[16]", NeEvent_tCsI_R, &b_NeEvent_tCsI_R);
  t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
  t->SetBranchAddress("NeEvent.SQY_L[16]", NeEvent_SQY_L, &b_NeEvent_SQY_L); 
  t->SetBranchAddress("NeEvent.tSQX_L[32]", NeEvent_tSQX_L, &b_NeEvent_tSQX_L);
  t->SetBranchAddress("NeEvent.tSQY_L[16]", NeEvent_tSQY_L, &b_NeEvent_tSQY_L);
  t->SetBranchAddress("NeEvent.SQX_R[32]", NeEvent_SQX_R, &b_NeEvent_SQX_R);
  t->SetBranchAddress("NeEvent.SQY_R[16]", NeEvent_SQY_R, &b_NeEvent_SQY_R);
  t->SetBranchAddress("NeEvent.tSQX_R[32]", NeEvent_tSQX_R, &b_NeEvent_tSQX_R);
  t->SetBranchAddress("NeEvent.tSQY_R[16]", NeEvent_tSQY_R, &b_NeEvent_tSQY_R);
  t->SetBranchAddress("NeEvent.SQ20[16]", NeEvent_SQ20, &b_NeEvent_SQ20);
  t->SetBranchAddress("NeEvent.tSQ20[16]", NeEvent_tSQ20, &b_NeEvent_tSQ20);
  t->SetBranchAddress("NeEvent.F3[4]", NeEvent_F3, &b_NeEvent_F3);
  t->SetBranchAddress("NeEvent.tF3[4]", NeEvent_tF3, &b_NeEvent_tF3);
  t->SetBranchAddress("NeEvent.F5[4]", NeEvent_F5, &b_NeEvent_F5);
  t->SetBranchAddress("NeEvent.tF5[4]", NeEvent_tF5, &b_NeEvent_tF5);
  t->SetBranchAddress("NeEvent.nx1", &NeEvent_nx1, &b_NeEvent_nx1);
  t->SetBranchAddress("NeEvent.ny1", &NeEvent_ny1, &b_NeEvent_ny1);
  t->SetBranchAddress("NeEvent.nx2", &NeEvent_nx2, &b_NeEvent_nx2);
  t->SetBranchAddress("NeEvent.ny2", &NeEvent_ny2, &b_NeEvent_ny2);
  t->SetBranchAddress("NeEvent.x1[32]", NeEvent_x1, &b_NeEvent_x1);
  t->SetBranchAddress("NeEvent.y1[32]", NeEvent_y1, &b_NeEvent_y1);
  t->SetBranchAddress("NeEvent.x2[32]", NeEvent_x2, &b_NeEvent_x2);
  t->SetBranchAddress("NeEvent.y2[32]", NeEvent_y2, &b_NeEvent_y2);
  t->SetBranchAddress("NeEvent.trigger", &NeEvent_trigger, &b_NeEvent_trigger);
  maxE = nentries1;

    xCsi_max = -1000;
    yCsi_max = -1000;
    xCsi_min = 1000;
    yCsi_min = 1000;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  //for (Long64_t jentry=0; jentry<20000;jentry++) {
  for (Long64_t jentry=1; jentry<maxE;jentry++) {
    t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;

 
    trigger = NeEvent_trigger;

    // MWPC
    // обнуление 

    x1p = -100.;
    y1p = -100.;
    x2p = -100.;
    y2p = -100.;
    xt = -100.;
    yt = -100.;
    
    // SQ_R
    //обнуление
    multX_R=0;
    multY_R=0;
    multCsi_R=0;


    for(Int_t i=0;i<32;i++) {
      if(NeEvent_tSQX_R[i]>0) {
        multX_R++;
      }
    } 

    for(Int_t i=0;i<16;i++) {
      if(NeEvent_tSQY_R[i]>0) {
        multY_R++;
      }
    } 
    //cout << " ########EVENT####### " << endl; 


    if(NeEvent_nx1==1 && NeEvent_ny1==1 && NeEvent_nx2==1 && NeEvent_ny2==1) { // рассматриваем события с множественностью 1 в MWPC и SQL
      if (NeEvent_x1[0]<1000 && NeEvent_y1[0]<1000) {
        x1p = NeEvent_x1[0]*1.25-20.;
        y1p = NeEvent_y1[0]*1.25-20.;
      }

      if (NeEvent_x2[0]<1000 && NeEvent_y2[0]<1000) {
        x2p = NeEvent_x2[0]*1.25-20.;
        y2p = NeEvent_y2[0]*1.25-20.;
      }

      if (x1p > -50. && y1p > -50. && x2p > -50. && y2p > -50.) { // what is this
        xt = (546*x1p + 816*(x2p-x1p))/(546 - (x2p-x1p)*tan(TMath::DegToRad()*12.));
       // xt = ((x2p-x1p)*816./546.) + x1p; 
        yt = (y2p-y1p)*(xt-x1p)/(x2p-x1p) + y1p;
        //zt = xt*sin(12.*TMath::DegToRad()); 
        zt = 546.*(xt-x1p)/(x2p-x1p) - 816;
      }

      
      //SQ_L track
      for(Int_t i=0;i<32;i++) {
        if(NeEvent_tSQX_R[i]>0) {
          Nst_X = i;
        }
      }
      for(Int_t i=0;i<16;i++) {
        if(NeEvent_tSQY_R[i]>0) {
          Nst_Y = i;
        }
      } 
      
    /*  xd = (Nst_X - 15.5)*58./32 - 380*sin(TMath::DegToRad()*12.);
      yd = (Nst_Y - 7.5)*58./16 ;
      zd = xd*sin(TMath::DegToRad()*12.) + 230.*cos(TMath::DegToRad()*12.);*/
      
      xd = -(Nst_X - 15.5)*58./32;
      yd = (Nst_Y - 7.5)*58./16 ;
      zd = 0.;

     /* xd = xd*cos(TMath::DegToRad()*12.) - yd*sin(TMath::DegToRad()*12.);
      yd = xd*sin(TMath::DegToRad()*12.) + yd*cos(TMath::DegToRad()*12.);
      zd = xd*sin(TMath::DegToRad()*12.) + 230.*cos(TMath::DegToRad()*12.);*/

      xd = xd*cos(TMath::DegToRad()*6.95) + zd*sin(TMath::DegToRad()*6.95);
      zd = -xd*sin(TMath::DegToRad()*6.95) + zd*cos(TMath::DegToRad()*6.95);
    
      xd = xd + 290.*sin(TMath::DegToRad()*6.95);
      zd = zd + 290.*cos(TMath::DegToRad()*6.95);

      //CsI track

      //-------

      //zCs = ( (zd*(xt-xd)/(zt-zd)) - 236*(cos(TMath::DegToRad()*12.) + sin(TMath::DegToRad()*12.)) - xd )/( (xt-xd)/(zt-zd) - sin(TMath::DegToRad()*12.) );
      zCs = ( (-xd+296.*sin(TMath::DegToRad()*6.95)+zd*(xt-xd)/(zt-zd))*tan(TMath::DegToRad()*6.95) + 296.*cos(TMath::DegToRad()*6.95) )/( 1 + tan(TMath::DegToRad()*6.95)*(xt-xd)/(zt-zd) );
      xCs = (zCs-zd)*(xt-xd)/(zt-zd) + xd;
      yCs = (zCs-zd)*(yt-yd)/(zt-zd) + yd;  
      //---------------

      xCs0 = xCs - 296.*sin(TMath::DegToRad()*6.95);
      zCs0 = zCs - 296.*cos(TMath::DegToRad()*6.95);

      xCs0 = xCs0*cos(TMath::DegToRad()*6.95) - zCs0*sin(TMath::DegToRad()*6.95); 
      zCs0 = xCs0*sin(TMath::DegToRad()*6.95) + zCs0*cos(TMath::DegToRad()*6.95);

      yCs0 = yCs;

      nCs = -10;
      nCsM=-10;

      if(xCs0<=(-33. + 66./4)) {
        if(yCs0>=33. - 66./4) nCs=15;
        if((yCs0>=33. - 2*66./4) && (yCs0<=33. - 66./4)) nCs=11;
        if((yCs0>=33. - 3*66./4) && (yCs0<=33. - 2*66./4)) nCs=7;
       // if((yCs0>33. - 4*66./4) && (yCs0<33. - 3*66./4)) nCs=3;
        if(yCs0<=33. - 3*66./4) nCs=3;
      }

      if((xCs0<=(-33. + 2*66./4)) && (xCs0>=(-33. + 66./4))) {
        if(yCs0>=33. - 66./4) nCs=14;
        if((yCs0>=33. - 2*66./4) && (yCs0<=33. - 66./4)) nCs=10;
        if((yCs0>=33. - 3*66./4) && (yCs0<=33. - 2*66./4)) nCs=6;
       // if((yCs0>33. - 4*66./4) && (yCs0<33. - 3*66./4)) nCs=2;
        if(yCs0<=33. - 3*66./4) nCs=2;
      }

      if((xCs0<=(-33. + 3*66./4)) && (xCs0>=(-33. + 2*66./4))) {
        if(yCs0>=33. - 66./4) nCs=13;
        if((yCs0>=33. - 2*66./4) && (yCs0<=33. - 66./4)) nCs=9;
        if((yCs0>=33. - 3*66./4) && (yCs0<=33. - 2*66./4)) nCs=5;
        //if((yCs0>33. - 4*66./4) && (yCs0<33. - 3*66./4)) nCs=1;
        if(yCs0<=33. - 3*66./4) nCs=1;
      }

      //if((xCs0<(-33. + 4*66./4)) && (xCs0>(-33. + 3*66./4))) {
      if(xCs0>=(-33. + 3*66./4)) {
        if(yCs0>=33. - 66./4) nCs=12;
        if((yCs0>=33. - 2*66./4) && (yCs0<=33. - 66./4)) nCs=8;
        if((yCs0>=33. - 3*66./4) && (yCs0<=33. - 2*66./4)) nCs=4;
        //if((yCs0>33. - 4*66./4) && (yCs0<33. - 3*66./4)) nCs=0;
        if(yCs0<=33. - 3*66./4) nCs=0;
      }
     // if(nCs==-10) cout << xd << " " << yd << " " << zd << " " << zt << endl;

      aCsiM = -10;
      for(Int_t i=0;i<16;i++) {
        if(aCsiM<NeEvent_CsI_R[i]) {
          aCsiM = NeEvent_CsI_R[i];
          nCsM = i;
        }
      }     
      if(nCs>-1 && aCsiM>=-1) tw->Fill();
    }
    //}     
  }//entries
  //cout << xCsi_max << " " << xCsi_min << " " << yCsi_max << " " << yCsi_min << endl;
  fw->cd();
  tw->Write();
  fw->Close();
}
