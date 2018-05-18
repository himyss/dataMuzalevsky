//---------------------------------------------------------
Double_t fitf(Double_t *x,Double_t *par) {  // creating fit function
  Int_t A,Z;
  A = 4; Z = 2;
  Double_t fitval = par[4] + par[0]*( x[0]*(1 - (par[1]*A*Z*Z/x[0])*TMath::Log(1 + (1/(par[1]*A*Z*Z/x[0])) ) ) + par[3]*par[1]*A*Z*Z*TMath::Log( (x[0]+par[1]*A*Z*Z)/(A*par[2]+par[1]*A*Z*Z) ) );
  return fitval;
}
//---------------------------------------------------------

void CsI_fill() { 
	
    // Reading cal parameters 
  Float_t parXL1[32], parXL2[32],parYL1[16],parYL2[16],parXR1[32], parXR2[32],parYR1[16],parYR2[16];
  //------------------------------------------------------------------------------ 
  // for 1 mm Si detector
  TString line1;
  ifstream myfile1;
  Int_t count=-2;
  myfile1.open("/home/muzalevsky/work/exp1803/data/siCal/SQX_R.cal");
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
  myfile2.open("/home/muzalevsky/work/exp1803/data/siCal/SQY_R.cal");
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
  myfile3.open("/home/muzalevsky/work/exp1803/data/siCal/SQX_L.cal");
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
  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/SQY_L.cal");
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

    
  //------------------------------------------------------------------------------ 
	TFile *f[100]; 
  TString input_file;
  Float_t CsI_R[16],F3[4],tF3[4],F5[4],tF5[4],SQX_R[32],SQY_R[16],SQX_L[32],SQY_L[16],tSQX_R[32],tSQY_R[16],tSQX_L[32],tSQY_L[16];
  TTree* 		t;
  UShort_t    NeEvent_CsI_R[16],NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16];
  TBranch    *b_NeEvent_CsI_R,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L;
  Long64_t nentries1;
  Int_t maxE;

  // Creating outfile,outtree
  TFile *fw = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/outtest.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");
  tw->Branch("CsI_R",&CsI_R,"CsI_R[16]/F");
  tw->Branch("F3",&F3,"F3[4]/F");
  tw->Branch("F5",&F5,"F5[4]/F");
  tw->Branch("tF3",&tF3,"tF3[4]/F");
  tw->Branch("tF5",&tF5,"tF5[4]/F");
  tw->Branch("SQX_R",&SQX_R,"SQX_R[32]/F");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("tSQX_R",&tSQX_R,"tSQX_R[32]/F");
  tw->Branch("tSQY_R",&tSQY_R,"tSQY_R[16]/F");
  tw->Branch("tSQX_L",&tSQX_L,"tSQX_L[32]/F");
  tw->Branch("tSQY_L",&tSQY_L,"tSQY_L[16]/F");

  for(Int_t n=10;n<30;n++) {
    input_file.Form("/media/analysis_nas/exp201804/rootfiles/h5_14_00%d.root",n);		
    f[n] = new TFile(input_file.Data());
    if (f[n]->IsZombie()) {
	    cerr << "Input file was not opened " << input_file.Data() << endl;
	    return 1;
    }

	  f[n]->GetObject("AnalysisxTree",t);
	  t->SetMakeClass(1);
	  t->SetBranchAddress("NeEvent.CsI_R[16]", NeEvent_CsI_R, &b_NeEvent_CsI_R);
	  t->SetBranchAddress("NeEvent.F3[4]", NeEvent_F3, &b_NeEvent_F3);
	  t->SetBranchAddress("NeEvent.tF3[4]", NeEvent_tF3, &b_NeEvent_tF3);
	  t->SetBranchAddress("NeEvent.F5[4]", NeEvent_F5, &b_NeEvent_F5);
	  t->SetBranchAddress("NeEvent.tF5[4]", NeEvent_tF5, &b_NeEvent_tF5);
	  t->SetBranchAddress("NeEvent.SQX_R[32]", NeEvent_SQX_R, &b_NeEvent_SQX_R);
	  t->SetBranchAddress("NeEvent.SQY_R[16]", NeEvent_SQY_R, &b_NeEvent_SQY_R);
	  t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
	  t->SetBranchAddress("NeEvent.SQY_L[16]", NeEvent_SQY_L, &b_NeEvent_SQY_L);
	  t->SetBranchAddress("NeEvent.tSQX_R[32]", NeEvent_tSQX_R, &b_NeEvent_tSQX_R);
	  t->SetBranchAddress("NeEvent.tSQY_R[16]", NeEvent_tSQY_R, &b_NeEvent_tSQY_R);
	  t->SetBranchAddress("NeEvent.tSQX_L[32]", NeEvent_tSQX_L, &b_NeEvent_tSQX_L);
	  t->SetBranchAddress("NeEvent.tSQY_L[16]", NeEvent_tSQY_L, &b_NeEvent_tSQY_L);
		
	  nentries1 = t->GetEntries();
    cout << nentries1 << endl;
    
    maxE = nentries1;
    cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
	  for (Long64_t jentry=0; jentry<maxE;jentry++) {
		  t->GetEntry(jentry);
    
      // обнуление
      for(Int_t i = 0; i<32;i++) {
        SQX_R[i]=0.;
        SQX_L[i]=0.;
        tSQX_R[i]=0.;
        tSQX_L[i]=0.;
        if(i<16) {
          CsI_R[i]=0.;
          SQY_R[i]=0.;
          SQY_L[i]=0.;
          tSQY_R[i]=0.;
          tSQY_L[i]=0.;
        }
        if(i<4){
          F3[i] = 0.;
          F5[i] = 0.;
          tF5[i] = 0.;
          tF3[i] = 0.;
        }
      }

       // selecting nice events
      //if( (NeEvent_F5[0]+NeEvent_F3[0]>400) && (NeEvent_F5[0]+NeEvent_F3[0]<750) && (NeEvent_tF5[0]-NeEvent_tF3[0]>640) && (NeEvent_tF5[0]-NeEvent_tF3[0]<750) && 
      //    (NeEvent_F5[1]+NeEvent_F3[1]>400) && (NeEvent_F5[1]+NeEvent_F3[1]<750) && (NeEvent_tF5[1]-NeEvent_tF3[1]>640) && (NeEvent_tF5[1]-NeEvent_tF3[1]<750) && 
      //    (NeEvent_F5[2]+NeEvent_F3[2]>400) && (NeEvent_F5[2]+NeEvent_F3[2]<750) && (NeEvent_tF5[2]-NeEvent_tF3[2]>640) && (NeEvent_tF5[2]-NeEvent_tF3[2]<750) && 
      //    (NeEvent_F5[3]+NeEvent_F3[3]>400) && (NeEvent_F5[3]+NeEvent_F3[3]<750) && (NeEvent_tF5[3]-NeEvent_tF3[3]>640) && (NeEvent_tF5[3]-NeEvent_tF3[3]<750) ) {
      //}

      for(Int_t i=0; i<32; i++) {
        SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
        SQX_L[i] = NeEvent_SQX_L[i]*parXL2[i] + parXL1[i];
        tSQX_R[i] = NeEvent_tSQX_R[i];
        tSQX_L[i] = NeEvent_tSQX_L[i];
        if(i<16){
          CsI_R[i] = NeEvent_CsI_R[i];
          SQY_R[i] = NeEvent_SQY_R[i]*parYR2[i] + parYR1[i];
          SQY_L[i] = NeEvent_SQY_L[i]*parYL2[i] + parYL1[i];
          tSQY_R[i] = NeEvent_tSQY_R[i];
          tSQY_L[i] = NeEvent_tSQY_L[i];
        }
        if(i<4) {
          F3[i] = NeEvent_F3[i];
          F5[i] = NeEvent_F5[i];
          tF3[i] = NeEvent_tF3[i];
          tF5[i] = NeEvent_tF5[i];
        }
      }
		  tw->Fill();			
	  }//entries
  }//nfiles
  fw->cd();
	tw->Write();
	fw->Close();
}
