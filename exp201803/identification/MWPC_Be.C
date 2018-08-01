void MWPC_Be() { 

  TChain *t = new TChain("AnalysisxTree");
  //TTree* 		t;

  Float_t CsI_L[16],tCsI_L[16],CsI_R[16],tCsI_R[16],SQX_L[32],SQY_L[16],tSQX_L[32],tSQY_L[16],SQX_R[32],SQY_R[16],tSQX_R[32],tSQY_R[16],SQ20[16],tSQ20[16],F3[4],tF3[4],F5[4],tF5[4],
          x1[32],x2[32],y1[32],y2[32];


  UShort_t   NeEvent_CsI_L[16],NeEvent_tCsI_L[16],NeEvent_CsI_R[16],NeEvent_tCsI_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16],
             NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_SQ20[16],NeEvent_tSQ20[16],
             NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_nx1,NeEvent_nx2,NeEvent_ny1,NeEvent_ny2,NeEvent_x1[32],NeEvent_x2[32],NeEvent_y1[32],NeEvent_y2[32];

  TBranch *b_NeEvent_CsI_L,*b_NeEvent_tCsI_L,*b_NeEvent_CsI_R,*b_NeEvent_tCsI_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,
          *b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_SQ20,*b_NeEvent_tSQ20,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,
          *b_NeEvent_nx1,*b_NeEvent_nx2,*b_NeEvent_ny1,*b_NeEvent_ny2,*b_NeEvent_x1,*b_NeEvent_x2,*b_NeEvent_y1,*b_NeEvent_y2,*b_NeEvent_trigger;

  Int_t NeEvent_trigger,trigger,nx1,ny1,nx2,ny2;

  Long64_t nentries1;
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,mult20,multY_Lt,multX_Lt,multY_Rt,multX_Rt,mult20t,multCsi_R,multCsi_L,timeF5,thresh_X,thresh_Y,thresh_CsI,nCh_L,nCh_R,MWPCflag;
  bool ToFflag;
  Float_t maxCsI_R,maxCsI_L;

  Float_t x1p,x2p,y1p,y2p,yt,xt,zt,xd,yd,zd,xCs,yCs,zCs,x1n,x2n,y1n,y2n;
  // Creating outfile,outtree
  TFile *fw = new TFile("/media/user/work/data/analysisexp1804/Be_MWPC.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("F3",&F3,"F3[4]/F");
  tw->Branch("tF3",&tF3,"tF3[4]/F");
  tw->Branch("F5",&F5,"F5[4]/F");
  tw->Branch("tF5",&tF5,"tF5[4]/F");
  tw->Branch("nx1",&nx1,"nx1/I");
  tw->Branch("ny1",&ny1,"ny1/I");
  tw->Branch("nx2",&nx2,"nx2/I");
  tw->Branch("ny2",&ny2,"ny2/I");
  tw->Branch("xt",&xt,"xt/F");
  tw->Branch("x2p",&x2p,"x2p/F");
  tw->Branch("yt",&yt,"yt/F");
  tw->Branch("y2p",&y2p,"y2p/F");
  tw->Branch("trigger",&trigger,"trigger/I");

  tw->Branch("multY_L",&multY_L,"multY_L/I");
  tw->Branch("multX_L",&multX_L,"multX_L/I");

	t->Add("/media/user/work/data/exp1804/h5_14_00*.root");
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
  Float_t tAngle = 12.;
  maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  for (Long64_t jentry=1; jentry<maxE;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;


    //----------------------------- ToF module
    // обнуление
    for(Int_t i=0;i<4;i++) { 
      F3[i] = 0.;
      F5[i] = 0.;
      tF5[i] = 0.;
      tF3[i] = 0.;
    }
    ToFflag = false;
    for(Int_t i=0;i<4;i++) {
      F3[i] = NeEvent_F3[i];
      F5[i] = NeEvent_F5[i];
      tF3[i] = NeEvent_tF3[i]*0.125+89.165;
      tF5[i] = NeEvent_tF5[i]*0.125+89.165;
      if(tF5[i]-tF3[i]>100 && tF5[i]-tF3[i]<200) ToFflag = true; 
    }
    //----------------------------- end of ToF module

    //----------------------------- MWPC
    // обнуление 
    MWPCflag = 1;

    x1p = -100.;
    y1p = -100.;
    x2p = -100.;
    y2p = -100.;
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

    if(nx1==0) {MWPCflag = MWPCflag*0;}
    if(nx1==1) {MWPCflag = MWPCflag*1;}
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
    if(NeEvent_nx2==1) {MWPCflag = MWPCflag*1;}
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
    if(ny1==1) {MWPCflag = MWPCflag*1;}
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
    if(NeEvent_ny2==1) {MWPCflag = MWPCflag*1;}
    if(NeEvent_ny2>1) {
      for(Int_t i=0;i<ny2-1;i++) {
        if((NeEvent_y2[i+1]-y2[i])!=1) {
          MWPCflag = MWPCflag*0;
        }
      }
      if(MWPCflag==1) {
        y2n = (NeEvent_y2[0]+NeEvent_y2[ny2-1])/2.;
      }
    } 

    if(MWPCflag==1) { // рассматриваем события с множественностью 1 в MWPC или кластером

      x1p = (NeEvent_x1[0]+0.5)*1.25-20.;
      y1p = (NeEvent_y1[0]+0.5)*1.25-20.;

      x2p = (NeEvent_x2[0]+0.5)*1.25-20.;
      y2p = (NeEvent_y2[0]+0.5)*1.25-20.;

      xt = (546*x1p + 816*(x2p-x1p))/(546 - (x2p-x1p)*tan(TMath::DegToRad()*tAngle));
      yt = (y2p-y1p)*(xt-x1p)/(x2p-x1p) + y1p;
      zt = 546.*(xt-x1p)/(x2p-x1p) - 816;

    }
    //----------------------------- MWPC
    trigger = NeEvent_trigger;

    if(MWPCflag==1) tw->Fill();		
  }//entries
  fw->cd();
	tw->Write();
  fw->Close();
}