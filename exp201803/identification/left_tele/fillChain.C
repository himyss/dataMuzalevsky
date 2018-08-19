void fillChain() { 
	
    // Reading cal parameters 
  Float_t parXL1[32],parXL2[32],parYL1[16],parYL2[16],parXR1[32], parXR2[32],parYR1[16],parYR2[16],par201[16],par202[16],parCsR1[16],parCsR2[16];
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

  ifstream myfile3;
  TString line3;
  count=-2;
  myfile3.open("/media/user/work/data/analysisexp1804/presentPars/SQX_L.cal");
  while (! myfile3.eof() ){
    line3.ReadLine(myfile3);
    if(count < 0){
      count++;
      continue;
    }
    if(line3.IsNull()) break;
    sscanf(line3.Data(),"%g %g", parXL1+count,parXL2+count);
    count++;
  }

  cout << endl << " pars for XL strips" << endl;
  for(Int_t i=0;i<32;i++) cout << parXL1[i] << " " << parXL2[i] << endl;   

  ifstream myfile4;
  TString line4;
  count=-2;
  myfile4.open("/media/user/work/data/analysisexp1804/presentPars/SQY_L.cal");
  while (! myfile4.eof() ){
    line4.ReadLine(myfile4);
    if(count < 0){
      count++;
      continue;
    }
    if(line4.IsNull()) break;
    sscanf(line4.Data(),"%g %g", parYL1+count,parYL2+count);
    count++;
  }

  cout << endl << " pars for YL strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parYL1[i] << " " << parYL2[i] << endl;     

  ifstream myfile5;
  TString line5;
  count=-2;
  myfile5.open("/media/user/work/data/analysisexp1804/presentPars/SQ20.cal");
  while (! myfile5.eof() ){
    line5.ReadLine(myfile5);
    if(count < 0){
      count++;
      continue;
    }
    if(line5.IsNull()) break;
    sscanf(line5.Data(),"%g %g", par201+count,par202+count);
    count++;
  }

  cout << endl << " pars for 20um strips" << endl;
  for(Int_t i=0;i<16;i++) cout << par201[i] << " " << par202[i] << endl; 

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
          x1,x2,y1,y2,x1n,x2n,y1n,y2n,ToF,deBeam,zt,yt,xt,CsI,tCsI;

  UShort_t   NeEvent_CsI_L[16],NeEvent_tCsI_L[16],NeEvent_CsI_R[16],NeEvent_tCsI_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16],
             NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_SQ20[16],NeEvent_tSQ20[16],
             NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_nx1,NeEvent_nx2,NeEvent_ny1,NeEvent_ny2,NeEvent_x1[32],NeEvent_x2[32],NeEvent_y1[32],NeEvent_y2[32];

  TBranch *b_NeEvent_CsI_L,*b_NeEvent_tCsI_L,*b_NeEvent_CsI_R,*b_NeEvent_tCsI_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,
          *b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_SQ20,*b_NeEvent_tSQ20,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,
          *b_NeEvent_nx1,*b_NeEvent_nx2,*b_NeEvent_ny1,*b_NeEvent_ny2,*b_NeEvent_x1,*b_NeEvent_x2,*b_NeEvent_y1,*b_NeEvent_y2,*b_NeEvent_trigger;

  Int_t NeEvent_trigger,trigger,nx1,nx2,ny1,ny2,nCsI;

  Long64_t nentries1;
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,mult20,multY_Lt,multX_Lt,multY_Rt,multX_Rt,mult20t,multCsi_R,multCsi_L,timeF5,thresh_X,thresh_Y,thresh_CsI,nCh_L,nCh_R;

  Int_t ToFflag,Csi_Rflag,MWPCflag,SQRflag,SQLflag,SQ20flag,flag,flagR,flagL; //! flags

  Float_t maxCsI_R,maxCsI_L;

  Float_t tx1,tx2,ty1,ty2,tyt,txt,tzt;

  const Float_t    MWPC1_X_displacement  = -1.0;
  const Float_t    MWPC1_Y_displacement  = -2.1375;
  const Float_t    MWPC2_X_displacement  = 0.2;
  const Float_t    MWPC2_Y_displacement  = -1.125;

  const Float_t    MWPC1_X_zero_position = -15.5*1.25;
  const Float_t    MWPC1_Y_zero_position = -15.5*1.25;
  const Float_t    MWPC2_X_zero_position = -15.5*1.25;
  const Float_t    MWPC2_Y_zero_position = -15.5*1.25;

 // Creating outfile,outtree
  TFile *fw = new TFile("/media/user/work/data/analysisexp1804/tmp.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  //tw->Branch("CsI_L",&CsI_L,"CsI_L[16]/F");
  //tw->Branch("tCsI_L",&tCsI_L,"tCsI_L[16]/F");
  tw->Branch("CsI_R",&CsI_R,"CsI_R[16]/F");
  tw->Branch("tCsI_R",&tCsI_R,"tCsI_R[16]/F");

  tw->Branch("CsI",&CsI_R,"CsI_R/F");
  tw->Branch("tCsI",&tCsI_R,"tCsI_R/F");
  tw->Branch("nCsI",&nCsI,"nCsI/I");


  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("tSQX_L",&tSQX_L,"tSQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("tSQY_L",&tSQY_L,"tSQY_L[16]/F");
  tw->Branch("SQ20",&SQ20,"SQ20[16]/F");
  tw->Branch("tSQ20",&tSQ20,"tSQ20[16]/F");

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

  tw->Branch("flagR",&flagR,"flagR/I");
  tw->Branch("flagL",&flagL,"flagL/I");

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
  for (Long64_t jentry=0; jentry<1000;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;
    // обнуление
    trigger = NeEvent_trigger;
    flag=0;
    flagR = 0;
    flagL = 0;

    //----------------------------- CsI module
    for(Int_t i=0;i<16;i++) { // обнуление
      CsI_R[i] = 0;
      tCsI_R[i] = 0;
    }
    CsI = 0;
    tCsI = 0;
    nCsI = -10;

    multCsi_R = 0;
    Csi_Rflag = 0;    
    //searching for maxAmp of CsI_R and CsI_L, time selection NeEvent_tCsI_R[i]>0

    maxCsI_R = 0; nCh_R = -10;
    for(Int_t i=0;i<16;i++) {
      if(maxCsI_R<NeEvent_CsI_R[i] && NeEvent_tCsI_R[i]>0) {
        maxCsI_R = NeEvent_CsI_R[i];
        nCh_R = i;

        nCsI = i;
        CsI = NeEvent_CsI_R[i];  
        tCsI = NeEvent_tCsI_R[i];
      }
    }
 
    // calculation of the multiplicity
    for(Int_t i=0;i<16;i++){
      if(NeEvent_CsI_R[i]==maxCsI_R && maxCsI_R>0) multCsi_R++;
    }
    
    // Csi_R energy threshold
    if(maxCsI_R<200) Csi_Rflag--;
    //multiplicity selection
    if(multCsi_R!=1) Csi_Rflag--;   
  
    //Fill
    CsI_R[nCh_R] = NeEvent_CsI_R[nCh_R]*parCsR2[nCh_R] + parCsR1[nCh_R];
    tCsI_R[nCh_R] = NeEvent_tCsI_R[nCh_R]*0.3; 

    CsI = CsI*parCsR2[nCsI] + parCsR1[nCsI];
    tCsI = tCsI*0.3;

    // amp-time cut (340,430)
    if((tCsI - NeEvent_tF5[0]*0.125)<365 || (tCsI - NeEvent_tF5[0]*0.125)>430) Csi_Rflag--;


    //Csi_Rflag MUST BE = 0 !!!
    //----------------------------- endl of CsI module

    //----------------------------- ToF module
    // обнуление
    ToF=0;
    deBeam=0;
    ToFflag = 0;

    // for(Int_t i=0;i<4;i++) {
    //  // if(tF5[i]-tF3[i]<100 || tF5[i]-tF3[i]>200) ToFflag--;
    //   for(Int_t j=i;j<4;j++) {
    //     if(NeEvent_tF5[i]-NeEvent_tF5[j]<-20 || NeEvent_tF5[i]-NeEvent_tF5[j]>20) ToFflag--;
    //     if(NeEvent_tF3[i]-NeEvent_tF3[j]<-20 || NeEvent_tF3[i]-NeEvent_tF3[j]>20) ToFflag--;
    //     if(NeEvent_F5[i]+NeEvent_F3[j]<10) ToFflag--;

    //   }
    // }
    //fill
    deBeam = (NeEvent_F5[0]+NeEvent_F5[1]+NeEvent_F5[2]+NeEvent_F5[3]+NeEvent_F3[0]+NeEvent_F3[1]+NeEvent_F3[2]+NeEvent_F3[3]);
    ToF = (NeEvent_tF5[0]+NeEvent_tF5[1]+NeEvent_tF5[2]+NeEvent_tF5[3] - NeEvent_tF3[0]-NeEvent_tF3[1]-NeEvent_tF3[2]-NeEvent_tF3[3])*0.25*0.125 + 89.165;
    if(ToF<100 || ToF>200) ToFflag--; 
    if(ToFflag!=0) continue;
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

      if(MWPCflag==1) {
        x1n = (NeEvent_x1[0]+NeEvent_x1[nx1-1])/2.;
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
    if(NeEvent_ny1>1) {
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

    if(MWPCflag!=1) continue;
    //----------------------------- MWPC

/*
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

    //fill
    for(Int_t i=0; i<32; i++) {
      SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
      tSQX_R[i] = NeEvent_tSQX_R[i]*0.3;
      if(i<16){
        SQY_R[i] = NeEvent_SQY_R[i]*parYR2[i] + parYR1[i];
        tSQY_R[i] = NeEvent_tSQY_R[i]*0.3;
      }
    }

    for(Int_t i=0;i<32;i++){ 
      if(i<16){ // CFD LED times (walk)
        if(tSQX_R[i] - NeEvent_tF5[0]*0.125 > -70 && tSQX_R[i] - NeEvent_tF5[0]*0.125<0 && tSQX_R[i]>0 && SQX_R[i]>1.5) SQRflag++;
        if(tSQY_R[i] - NeEvent_tF5[0]*0.125 > -70 && tSQY_R[i] - NeEvent_tF5[0]*0.125<0 && tSQY_R[i]>0 && SQY_R[i]>1.5) SQRflag++;
      }
      if(i>15){ // both times by CFD 
        if(tSQX_R[i] - NeEvent_tF5[0]*0.125 > 40 && tSQX_R[i] - NeEvent_tF5[0]*0.125<90 && tSQX_R[i]>0 && SQX_R[i]>1.5) SQRflag++;
      }
    }
    // if(SQRflag!=2) continue;
    //----------------------------- end of SQ_R module


    //----------------------------- SQ_L module

    // обнуление 
    for(Int_t i = 0; i<32;i++) {
      SQX_L[i]=0.;
      tSQX_L[i]=0.;
      if(i<16) {
        SQY_L[i]=0.;
        tSQY_L[i]=0.;
      }
    }
    SQLflag = 0;

    //fill
    for(Int_t i=0; i<32; i++) {
      SQX_L[i] = NeEvent_SQX_L[i]*parXL2[i] + parXL1[i];
      tSQX_L[i] = NeEvent_tSQX_L[i]*0.3;
      if(i<16){
        SQY_L[i] = NeEvent_SQY_L[i]*parYL2[i] + parYL1[i];
        tSQY_L[i] = NeEvent_tSQY_L[i]*0.3;
      }
    }

    for(Int_t i=0;i<32;i++){ 
      if(i<16){ // CFD LED times (walk)
        if(tSQX_L[i] - NeEvent_tF5[0]*0.125 > -70 && tSQX_L[i] - NeEvent_tF5[0]*0.125<0 && tSQX_L[i]>0 && SQX_L[i]>1.5) SQLflag++;
        if(tSQY_L[i] - NeEvent_tF5[0]*0.125 > -70 && tSQY_L[i] - NeEvent_tF5[0]*0.125<0 && tSQY_L[i]>0 && SQY_L[i]>1.5) SQLflag++;
      }
      if(i>15){ // both times by CFD 
        if(tSQX_L[i] - NeEvent_tF5[0]*0.125 > 40 && tSQX_L[i] - NeEvent_tF5[0]*0.125<90 && tSQX_L[i]>0 && SQX_L[i]>1.5) SQLflag++;
      }
    }

    // if(SQLflag>0) cout << SQLflag << endl;
    // continue;
    //----------------------------- end of SQ_L module

    //----------------------------- SQ20 module

    // обнуление 
    for(Int_t i = 0; i<16;i++) {
      SQ20[i]=0.;
      tSQ20[i]=0.;
    }
    SQ20flag = 0;
    mult20 = 0;

    //fill
    for(Int_t i=0; i<16; i++) {
      SQ20[i] = NeEvent_SQ20[i]*par202[i] + par201[i]; 
      tSQ20[i] = NeEvent_tSQ20[i]*0.3;
    }

    for(Int_t i=0;i<16;i++){ 
      if(SQ20[i]>1. && tSQ20[i] - NeEvent_tF5[0]*0.125 > 30 && tSQ20[i] - NeEvent_tF5[0]*0.125<170 && tSQ20[i]>0) SQ20flag++;
    }

    //----------------------------- en of SQ20 module 



    if(Csi_Rflag==0 && SQRflag==2) flag = 1;
    if(SQ20flag==1 && SQLflag==2) flag = 1;
    if(flag!=1) continue;*/
    tw->Fill();
   // }			
  }//entries
  fw->cd();
	tw->Write();
	fw->Close();
}
