void toCalib() { 
	
    // Reading cal parameters 
  Float_t parXL1[32], parXL2[32],parYL1[16],parYL2[16],parXR1[32], parXR2[32],parYR1[16],parYR2[16];
  //------------------------------------------------------------------------------ 
  // for 1 mm Si detector
  TString line1;
  ifstream myfile1;
  Int_t count=-2;
  myfile1.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQX_R.cal");
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
  myfile2.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQY_R.cal");
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
  myfile7.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/csi_r_ec.clb");
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

  //------------------------------------------------------------------------------ 
  TString input_file;
  Float_t CsI_R[16],F3[4],tF3[4],F5[4],tF5[4],SQX_R[32],SQY_R[16],SQX_L[32],SQY_L[16],tSQX_R[32],tSQY_R[16],tSQX_L[32],tSQY_L[16],zeroPos,shitf;
  //TTree* 		t;
  TChain *t = new TChain("AnalysisxTree");
  UShort_t    NeEvent_CsI_R[16],NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16];
  TBranch    *b_NeEvent_CsI_R,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L,*b_NeEvent_trigger;
  Long64_t nentries1;
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,trigger,NeEvent_trigger,multCsi_R,timeF5,thresh_X,thresh_Y,thresh_CsI;

  // Creating outfile,outtree
  TFile *fw = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14_identificationH3_3.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");
  tw->Branch("CsI_R",&CsI_R,"CsI_R[16]/F");
 // tw->Branch("F3",&F3,"F3[4]/F");
 // tw->Branch("F5",&F5,"F5[4]/F");
 // tw->Branch("tF3",&tF3,"tF3[4]/F");
  tw->Branch("tF5",&tF5,"tF5[4]/F");
  tw->Branch("SQX_R",&SQX_R,"SQX_R[32]/F");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
 // tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
 // tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("tSQX_R",&tSQX_R,"tSQX_R[32]/F");
  tw->Branch("tSQY_R",&tSQY_R,"tSQY_R[16]/F");
 // tw->Branch("tSQX_L",&tSQX_L,"tSQX_L[32]/F");
 // tw->Branch("tSQY_L",&tSQY_L,"tSQY_L[16]/F");
 // tw->Branch("multY_L",&multY_L,"multY_L/I");
//  tw->Branch("multX_L",&multX_L,"multX_L/I");
  tw->Branch("trigger",&trigger,"trigger/I");

	t->Add("/media/analysis_nas/exp201804/rootfiles/h5_14_00*.root");
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
  t->SetBranchAddress("NeEvent.trigger", &NeEvent_trigger, &b_NeEvent_trigger);
	

  maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  for (Long64_t jentry=0; jentry<maxE;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;
    // обнуление
    trigger=0;
    for(Int_t i = 0; i<32;i++) {
      thresh_X = 1;
      thresh_Y = 1;
      thresh_CsI = 1;
      timeF5 = 0;
     // multY_L = 0;
     // multX_L = 0;
      multY_R = 0;
      multX_R = 0;
      multCsi_R=0;
      SQX_R[i]=0.;
     // SQX_L[i]=0.;
      tSQX_R[i]=0.;
     // tSQX_L[i]=0.;
      if(i<16) {
        CsI_R[i]=0.;
        SQY_R[i]=0.;
      //  SQY_L[i]=0.;
        tSQY_R[i]=0.;
      //  tSQY_L[i]=0.;
        CsI_R[i] = 0;
      }
      if(i<4){
       // F3[i] = 0.;
       // F5[i] = 0.;
        tF5[i] = 0.;
       // tF3[i] = 0.;
      }
    }

    for(Int_t i=0; i<32; i++) {
      SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
      //SQX_L[i] = NeEvent_SQX_L[i]*parXL2[i] + parXL1[i];
      if(SQX_R[i]>3) multX_R++; 
      if(SQX_R[i]>20) thresh_X=0; 
      tSQX_R[i] = NeEvent_tSQX_R[i]*0.3;
      //tSQX_L[i] = NeEvent_tSQX_L[i]*tPx_l2[i] + tPx_l1[i];
     // tSQX_L[i] = NeEvent_tSQX_L[i]*0.3;
      if(i<4) {
        //F3[i] = NeEvent_F3[i];
        //F5[i] = NeEvent_F5[i];
        //tF3[i] = NeEvent_tF3[i]*0.125;
        tF5[i] = NeEvent_tF5[i]*0.125;
      }
      if(i<16){
        CsI_R[i] = NeEvent_CsI_R[i]*parCsR2[i]+parCsR1[i];
        if(CsI_R[i]>0) multCsi_R++;
        if(CsI_R[i]>145) thresh_CsI=0;
        SQY_R[i] = NeEvent_SQY_R[i]*parYR2[i] + parYR1[i];
       // SQY_L[i] = NeEvent_SQY_L[i]*parYL2[i] + parYL1[i];
        if(SQY_R[i]>2.3) multY_R++; 
        if(SQY_R[i]>20) thresh_Y=0; 
        tSQY_R[i] = NeEvent_tSQY_R[i]*0.3;
        //tSQY_L[i] = NeEvent_tSQY_L[i]*tPy_l2[i] + tPy_l1[i];
       // tSQY_L[i] = NeEvent_tSQY_L[i]*0.3;
      }
    }
    for(Int_t j =0;j<32;j++){
      if(j<16 && (tF5[2]-tSQX_R[j])>-50 && (tF5[2]-tSQX_R[j])<50) timeF5++;
      if(j>15 && (tF5[2]-tSQX_R[j])>50 && (tF5[2]-tSQX_R[j])<100) timeF5++;
    }
    trigger = NeEvent_trigger;
	  if(multX_R>0 && multY_R>0 && timeF5>0 && multCsi_R>0 && thresh_Y==1 && thresh_X==1 && thresh_CsI==1) {
      tw->Fill();
    }			
  }//entries
  fw->cd();
	tw->Write();
	fw->Close();
}
