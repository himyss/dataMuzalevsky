void track_beam() { 
	

 

  TChain *t = new TChain("AnalysisxTree");
  //TTree* 		t;

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
  TFile *fw = new TFile("track_beam.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("xt",&xt,"xt/F");
  tw->Branch("yt",&yt,"yt/F");
  tw->Branch("zt",&zt,"zt/F");
 
  tw->Branch("trigger",&trigger,"trigger/I");

	t->Add("/media/analysis_nas/exp201804/rootfiles/h5_14_00*");
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
  //for (Long64_t jentry=0; jentry<20000;jentry++) {
  for (Long64_t jentry=0; jentry<maxE;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;

    trigger = NeEvent_trigger;

    x1p = -100.;
		y1p = -100.;
		x2p = -100.;
		y2p = -100.;
		xt = -100.;
		yt = -100.;

    if(NeEvent_nx1==1 && NeEvent_ny1==1 && NeEvent_nx2==1 && NeEvent_ny2==1) { // рассматриваем события с множественностью 1 в MWPC
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

      tw->Fill();
    }
    //}			
  }//entries
  //cout << xCsi_max << " " << xCsi_min << " " << yCsi_max << " " << yCsi_min << endl;
  fw->cd();
	tw->Write();
	fw->Close();
}
