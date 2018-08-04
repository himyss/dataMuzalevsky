void toCalib_old() { 
	
    // Reading cal parameters 
  Float_t parXL1[32], parXL2[32],parYL1[16],parYL2[16],parXR1[32], parXR2[32],parYR1[16],parYR2[16];
  //------------------------------------------------------------------------------ 
  // for 1 mm Si detector
  TString line1;
  ifstream myfile1;
  Int_t count=-2;
  myfile1.open("/media/user/work/data/analysisexp1804/presentPars/SQX_R.cal");
  while (! myfile1.eof() ){
    line1.ReadLine(myfile1);
    if(count < 0){
      count++;
      continue;
    }
    if(line1.IsNull()) break;
    sscanf(line1.Data(),"%g %g", parXR1+count,parXR2+count);
    count++;
  }
  cout << endl << " pars for XR strips" << endl;
  for(Int_t i=0;i<32;i++) cout << parXR1[i] << " " << parXR2[i] << endl;  

  ifstream myfile2;
  TString line2;
  count=-2;
  myfile2.open("/media/user/work/data/analysisexp1804/presentPars/SQY_R.cal");
  while (! myfile2.eof() ){
    line2.ReadLine(myfile2);
    if(count < 0){
      count++;
      continue;
    }
    if(line2.IsNull()) break;
    sscanf(line2.Data(),"%g %g", parYR1+count,parYR2+count);
    count++;
  }

  cout << endl << " pars for YR strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parYR1[i] << " " << parYR2[i] << endl;   

  Float_t parCsR1[32],parCsR2[32];
  ifstream myfile7;
  TString line7;
  count=-2;
  myfile7.open("/media/user/work/data/analysisexp1804/presentPars/csi_r_ec.clb");
  while (! myfile7.eof() ) {
    line7.ReadLine(myfile7);
    if(count < 0){
      count++;
      continue;
    }
    if(line7.IsNull()) break;
    sscanf(line7.Data(),"%g %g", parCsR1+count,parCsR2+count);
    count++;
  }  

  cout << endl << " pars for CsR strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parCsR1[i] << " " << parCsR2[i] << endl; 

  Float_t tAngle = 12.;
  //------------------------------------------------------------------------------ 
  TChain *t = new TChain("AnalysisxTree");

  Float_t tF5[4],tF3[4],CsI_L[16],tCsI_L[16],CsI_R[16],tCsI_R[16],SQX_L[32],SQY_L[16],tSQX_L[32],tSQY_L[16],SQX_R[32],SQY_R[16],tSQX_R[32],tSQY_R[16],SQ20[16],tSQ20[16],
          x1,x2,y1,y2,x1n,x2n,y1n,y2n,ToF,deBeam,zt,yt,xt;

  UShort_t   NeEvent_CsI_L[16],NeEvent_tCsI_L[16],NeEvent_CsI_R[16],NeEvent_tCsI_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16],
             NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_SQ20[16],NeEvent_tSQ20[16],
             NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_nx1,NeEvent_nx2,NeEvent_ny1,NeEvent_ny2,NeEvent_x1[32],NeEvent_x2[32],NeEvent_y1[32],NeEvent_y2[32];

  TBranch *b_NeEvent_CsI_L,*b_NeEvent_tCsI_L,*b_NeEvent_CsI_R,*b_NeEvent_tCsI_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,
          *b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_SQ20,*b_NeEvent_tSQ20,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,
          *b_NeEvent_nx1,*b_NeEvent_nx2,*b_NeEvent_ny1,*b_NeEvent_ny2,*b_NeEvent_x1,*b_NeEvent_x2,*b_NeEvent_y1,*b_NeEvent_y2,*b_NeEvent_trigger;

  Int_t NeEvent_trigger,trigger,nx1,nx2,ny1,ny2;

  Long64_t nentries1;
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,mult20,multY_Lt,multX_Lt,multY_Rt,multX_Rt,mult20t,multCsi_R,multCsi_L,timeF5,thresh_X,thresh_Y,thresh_CsI,nCh_L,nCh_R;

  Int_t ToFflag,Csi_Rflag,MWPCflag,SQRflag; //! flags

  Float_t maxCsI_R,maxCsI_L;

  const Float_t    MWPC1_X_displacement  = -1.0;
  const Float_t    MWPC1_Y_displacement  = -2.1375;
  const Float_t    MWPC2_X_displacement  = 0.2;
  const Float_t    MWPC2_Y_displacement  = -1.125;

  const Float_t    MWPC1_X_zero_position = -15.5*1.25;
  const Float_t    MWPC1_Y_zero_position = -15.5*1.25;
  const Float_t    MWPC2_X_zero_position = -15.5*1.25;
  const Float_t    MWPC2_Y_zero_position = -15.5*1.25;


 // Creating outfile,outtree
  TFile *fw = new TFile("/media/user/work/data/analysisexp1804/h5_14_tritium_bogumilMWPC.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  //tw->Branch("CsI_L",&CsI_L,"CsI_L[16]/F");
  //tw->Branch("tCsI_L",&tCsI_L,"tCsI_L[16]/F");
  tw->Branch("CsI_R",&CsI_R,"CsI_R[16]/F");
  tw->Branch("tCsI_R",&tCsI_R,"tCsI_R[16]/F");
  /*tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("tSQX_L",&tSQX_L,"tSQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("tSQY_L",&tSQY_L,"tSQY_L[16]/F");
  tw->Branch("SQ20",&SQ20,"SQ20[16]/F");
  tw->Branch("tSQ20",&tSQ20,"tSQ20[16]/F");*/

  tw->Branch("SQX_R",&SQX_R,"SQX_R[32]/F");
  tw->Branch("tSQX_R",&tSQX_R,"tSQX_R[32]/F");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
  tw->Branch("tSQY_R",&tSQY_R,"tSQY_R[16]/F");

  tw->Branch("ToF",&ToF,"ToF/F");
  tw->Branch("deBeam",&deBeam,"deBeam/F");

  tw->Branch("nx1",&nx1,"nx1/I");
  tw->Branch("ny1",&ny1,"ny1/I");
  tw->Branch("nx2",&nx2,"nx2/I");
  tw->Branch("ny2",&ny2,"ny2/I");

  tw->Branch("x1",&x1,"x1/F");
  tw->Branch("x2",&x2,"x2/F");
  tw->Branch("y1",&y1,"y1/F");
  tw->Branch("y2",&y2,"y2/F");
  tw->Branch("yt",&yt,"yt/F");
  tw->Branch("xt",&xt,"xt/F");  

  tw->Branch("trigger",&trigger,"trigger/I");

 // tw->Branch("multY_L",&multY_L,"multY_L/I");
 // tw->Branch("multX_L",&multX_L,"multX_L/I");
  tw->Branch("multY_R",&multY_R,"multY_R/I");
  tw->Branch("multX_R",&multX_R,"multX_R/I");

  tw->Branch("multY_Lt",&multY_Lt,"multY_Lt/I");
  tw->Branch("multX_Lt",&multX_Lt,"multX_Lt/I");
  tw->Branch("multY_Rt",&multY_Rt,"multY_Rt/I");
  tw->Branch("multX_Rt",&multX_Rt,"multX_Rt/I");

	t->Add("/media/user/work/data/exp1804/h5_14_00*.root");
  nentries1 = t->GetEntries();
  cout << " Number of InPut entries: "<< nentries1 << endl;

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
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  for (Long64_t jentry=0; jentry<1000000;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;
    // обнуление
    trigger=0;


    //----------------------------- CsI module
    for(Int_t i=0;i<16;i++) { // обнуление
      CsI_R[i] = 0;
      CsI_L[i] = 0;
      tCsI_R[i] = 0;
      tCsI_L[i] = 0;
    }
    multCsi_R = 0;
    multCsi_L = 0;
    Csi_Rflag = 0;    
    //searching for maxAmp of CsI_R and CsI_L, time selection NeEvent_tCsI_R[i]>0

    maxCsI_R = 0; nCh_R = -10;
    maxCsI_L = 0; nCh_L = -10;
    for(Int_t i=0;i<16;i++) {
      if(maxCsI_R<NeEvent_CsI_R[i] && NeEvent_tCsI_R[i]>0) {
        maxCsI_R = NeEvent_CsI_R[i];
        nCh_R = i;  
      }
      if(maxCsI_L<NeEvent_CsI_L[i] && NeEvent_tCsI_L[i]>0) {
        maxCsI_L = NeEvent_CsI_L[i];
        nCh_L = i;  
      }
    }
 
    // calculation of the multiplicity
    for(Int_t i=0;i<16;i++){
      if(NeEvent_CsI_R[i]==maxCsI_R && maxCsI_R>0) multCsi_R++;
      if(NeEvent_CsI_L[i]==maxCsI_L && maxCsI_L>0) multCsi_L++;
    }
    
    // Csi_R energy threshold
    if(maxCsI_R<200) Csi_Rflag--;
    //multiplicity selection
    if(multCsi_R!=1) Csi_Rflag--;   
  
    //Fill
    CsI_R[nCh_R] = NeEvent_CsI_R[nCh_R];
    tCsI_R[nCh_R] = NeEvent_tCsI_R[nCh_R]*0.3;
    CsI_L[nCh_L] = NeEvent_CsI_L[nCh_L];
    tCsI_L[nCh_L] = NeEvent_tCsI_L[nCh_L]*0.3;   

    //Csi_Rflag MUST BE = 0 !!!
    //----------------------------- endl of CsI module

    //----------------------------- ToF module
    // обнуление
    ToF=0;
    deBeam=0;
    ToFflag = 0;

    for(Int_t i=0;i<4;i++) {
     // if(tF5[i]-tF3[i]<100 || tF5[i]-tF3[i]>200) ToFflag--;
      for(Int_t j=i;j<4;j++) {
        if(NeEvent_tF5[i]-NeEvent_tF5[j]<-20 || NeEvent_tF5[i]-NeEvent_tF5[j]>20) ToFflag--;
        if(NeEvent_tF3[i]-NeEvent_tF3[j]<-20 || NeEvent_tF3[i]-NeEvent_tF3[j]>20) ToFflag--;
        if(NeEvent_F5[i]+NeEvent_F3[j]<10) ToFflag--;
      }
    }
    //fill
    deBeam = (NeEvent_F5[0]+NeEvent_F5[1]+NeEvent_F5[2]+NeEvent_F5[3]+NeEvent_F3[0]+NeEvent_F3[1]+NeEvent_F3[2]+NeEvent_F3[3])*0.25;
    ToF = (NeEvent_tF5[0]+NeEvent_tF5[1]+NeEvent_tF5[2]+NeEvent_tF5[3] - NeEvent_tF3[0]-NeEvent_tF3[1]-NeEvent_tF3[2]-NeEvent_tF3[3])*0.25*0.125 + 89.165;
    if(ToF<100 || ToF>200) ToFflag--; 
    //TOFFLAG MUST BE = 0!!
    //----------------------------- end of ToF module


    //----------------------------- MWPC
    // обнуление 
    MWPCflag = 1;

    x1 = -100.;
    y1 = -100.;
    x2 = -100.;
    y2 = -100.;
    xt = -100.;
    yt = -100.;
   
    /*if(NeEvent_ny1>1) {
      cout << endl << "####EVENT####" << endl;
      //cout << NeEvent_nx1 << " x1 multyplicity !" << endl;
    }*/
    nx1 = NeEvent_nx1;
    ny1 = NeEvent_ny1;
    nx2 = NeEvent_nx2;
    ny2 = NeEvent_ny2;

    if(nx1>10 || ny1>10 || nx2>10 || ny2>10) continue;

    if(nx1==0) {MWPCflag = MWPCflag*0;}
    if(nx1==1) {
      MWPCflag = MWPCflag*1;
      x1n = NeEvent_x1[0];
    }
    if(nx1>1) {
      for(Int_t i=0;i<nx1-1;i++) {
        if((NeEvent_x1[i+1]-NeEvent_x1[i])!=1) {
          MWPCflag = MWPCflag*0;
        }
      }
     /* for(Int_t i=0;i<NeEvent_nx1;i++) {
        cout << NeEvent_x1[i] << endl;
      }*/
      if(MWPCflag==1) {
        x1n = (NeEvent_x1[0]+NeEvent_x1[nx1-1])/2.;

        /*cout << endl << "$$$GOODEVENT$$$ " << nx1  << " " << x1n << endl;
       // cout << NeEvent_nx1 << " x1 multyplicity !" << endl;
        for(Int_t i=0;i<nx1;i++) {
          cout << NeEvent_x1[i] << endl;
        }*/

      }
    }    

    if(NeEvent_nx2==0) {MWPCflag = MWPCflag*0;}
    if(NeEvent_nx2==1) {
      MWPCflag = MWPCflag*1;
      x2n = NeEvent_x2[0];
    }
    if(NeEvent_nx2>1) {
      for(Int_t i=0;i<nx2-1;i++) {
        if((NeEvent_x2[i+1]-NeEvent_x2[i])!=1) {
          MWPCflag = MWPCflag*0;
        }
      }
      if(MWPCflag==1) {
        x2n = (NeEvent_x2[0]+NeEvent_x2[nx2-1])/2.;
      }
    } 

    if(ny1==0) {MWPCflag = MWPCflag*0;}
    if(ny1==1) {
      MWPCflag = MWPCflag*1;
      y1n=NeEvent_y1[0];
    }
    if(ny1>1) {
      for(Int_t i=0;i<ny1-1;i++) {
        if((NeEvent_y1[i+1]-NeEvent_y1[i])!=1) {
          MWPCflag = MWPCflag*0;
        }
      }
      if(MWPCflag==1) {
        y1n = (NeEvent_y1[0]+NeEvent_y1[ny1-1])/2.;
      }
    }  

    if(NeEvent_ny2==0) {MWPCflag = MWPCflag*0;}
    if(NeEvent_ny2==1) {
      MWPCflag = MWPCflag*1;
      y2n = NeEvent_y2[0];
    }
    if(NeEvent_ny2>1) {
      for(Int_t i=0;i<ny2-1;i++) {
        if((NeEvent_y2[i+1]-NeEvent_y2[i])!=1) {
          MWPCflag = MWPCflag*0;
        }
      }
      if(MWPCflag==1) {
        y2n = (NeEvent_y2[0]+NeEvent_y2[ny2-1])/2.;
      }
    } 


    if(MWPCflag==1) { // рассматриваем события с множественностью 1 в MWPC или кластером БОГУМИЛ

      x1 = MWPC1_X_zero_position + MWPC1_X_displacement+x1n*1.25;
      y1 = MWPC1_Y_zero_position + MWPC1_Y_displacement + y1n*1.25;

      x2 = MWPC2_X_zero_position + MWPC2_X_displacement + x2n*1.25;
      y2 = MWPC2_Y_zero_position + MWPC2_Y_displacement + y2n*1.25;

      xt = (546*x1 + 816*(x2-x1))/(546 - (x2-x1)*tan(TMath::DegToRad()*tAngle));
      yt = (y2-y1)*(xt-x1)/(x2-x1) + y1;
      zt = 546.*(xt-x1)/(x2-x1) - 816;

    }




/*
    if(MWPCflag==1) { // рассматриваем события с множественностью 1 в MWPC или кластером

      x1 = (x1n+0.5)*1.25-20. + MWPC1_X_displacement;
      y1 = (y1n+0.5)*1.25-20. + MWPC1_Y_displacement;

      x2 = (x2n+0.5)*1.25-20. + MWPC2_X_displacement;
      y2 = (y2n+0.5)*1.25-20. + MWPC2_Y_displacement;

      xt = (546*x1 + 816*(x2-x1))/(546 - (x2-x1)*tan(TMath::DegToRad()*tAngle));
      yt = (y2-y1)*(xt-x1)/(x2-x1) + y1;
      zt = 546.*(xt-x1)/(x2-x1) - 816;

    }*/
    //----------------------------- MWPC


/*
    //----------------------------- MWPC module
    // обнуление 
    x1 = -100.;
		y1 = -100.;
		x2 = -100.;
		y2 = -100.;
		xt = -100.;
		yt = -100.;
    MWPCflag = 0;

    if(NeEvent_nx1!=1 || NeEvent_ny1!=1 || NeEvent_nx2!=1 || NeEvent_ny2!=1) MWPCflag--; 

	  x1 = (NeEvent_x1[0]+0.5)*1.25-20.;
	  y1 = (NeEvent_y1[0]+0.5)*1.25-20.;

	  x2 = (NeEvent_x2[0]+0.5)*1.25-20.;
	  y2 = (NeEvent_y2[0]+0.5)*1.25-20.;

    xt = (546*x1 + 816*(x2-x1))/(546 - (x2-x1)*tan(TMath::DegToRad()*tAngle));
	  yt = (y2-y1)*(xt-x1)/(x2-x1) + y1;
    zt = 546.*(xt-x1)/(x2-x1) - 816;

    //MWPCflag must be = 0!!
    //----------------------------- end of MWPC module
*/
    
    //----------------------------- SQ_R module

    // обнуление 
    for(Int_t i = 0; i<32;i++) {
      SQX_R[i]=0.;
      tSQX_R[i]=0.;
      if(i<16) {
        SQY_R[i]=0.;
        tSQY_R[i]=0.;
      }
    }
    SQRflag = 0;
    multY_R = 0;
    multX_R = 0;

    //fill
    for(Int_t i=0; i<32; i++) {
      SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
      if(SQX_R[i]>1.5) multX_R++; 
      tSQX_R[i] = NeEvent_tSQX_R[i]*0.3;
      if(i<16){
        SQY_R[i] = NeEvent_SQY_R[i]*parYR2[i] + parYR1[i];
        if(SQY_R[i]>1.5) multY_R++; 
        tSQY_R[i] = NeEvent_tSQY_R[i]*0.3;
      }
    }
    
    // energy threshold 1.5 MeV
    if(multY_R<1 || multX_R<1) SQRflag--;
    // time gates
    for(Int_t i=0;i<32;i++){ 
      if(i>16){ // CFD LED times (walk)
        if(tSQX_R[i]*0.3-tF5[0]*0.125 < -60 || tSQX_R[i]*0.3-tF5[0]*0.125>60) SQRflag--;
        if(tSQY_R[i]*0.3-tF5[0]*0.125 < -100 || tSQY_R[i]*0.3-tF5[0]*0.125>100) SQRflag--;
      }
      if(i>15){ // both times by CFD 
        if(tSQX_R[i]*0.3-tF5[0]*0.125 < 30 || tSQX_R[i]*0.3-tF5[0]*0.125>110) SQRflag--;
      }
    }

    trigger = NeEvent_trigger;
	  //if(multX_R>0 && multY_R>0 && timeF5>0 && multCsi_R>0 && thresh_Y==1 && thresh_X==1 && thresh_CsI==1) {
      if(ToFflag==0 && Csi_Rflag==0 && MWPCflag==1) tw->Fill();
   // }			
  }//entries
  fw->cd();
	tw->Write();
	fw->Close();
}
