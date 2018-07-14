void toCalib() { 
	

  TString cut[10];
  cut[0].Form("(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165 > 100 && (NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165 < 200"); // ToF cut
  cut[1].Form("NeEvent.nx1>0 && NeEvent.nx2>0 && NeEvent.ny1>0 && NeEvent.ny2>0"); //MWPC >0



    // Reading cal parameters 
  Float_t parXL1[32], parXL2[32],parYL1[16],parYL2[16],parXR1[32], parXR2[32],parYR1[16],parYR2[16],tPx_l1[32],tPx_l2[32],tPy_l1[16],tPy_l2[16],parCsR1[32],parCsR2[32],par201[16],par202[16];
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

  ifstream myfile3;
  TString line3;
  count=-2;
  myfile3.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQX_L.cal");
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
  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQY_L.cal");
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

  // get pars for positions of times
  cout << endl << " time parameters " << endl;
  ifstream myfile5;
  TString line5;
  myfile5.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/tParX_L.clb");
  count = -2;
  while (! myfile5.eof() ){
    line5.ReadLine(myfile5);
    if(count < 0){
      count++;
      continue;
    }
    if(line5.IsNull()) break;
    sscanf(line5.Data(),"%g %g", tPx_l1+count,tPx_l2+count);
    count++;
  }
  cout << endl << " pars for X time positions" << endl;
  for(Int_t i=0;i<32;i++) cout << tPx_l1[i] << " " << tPx_l2[i] << endl;      

  ifstream myfile6;
  TString line6;
  myfile6.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/tParY_L.clb");
  count = -2;
  while (! myfile6.eof() ){
    line6.ReadLine(myfile6);
    if(count < 0){
      count++;
      continue;
    }
    if(line6.IsNull()) break;
    sscanf(line6.Data(),"%g %g", tPy_l1+count,tPy_l2+count);
    count++;
  }
  cout << endl << " pars for Y time positions" << endl;
  for(Int_t i=0;i<16;i++) cout << tPy_l1[i] << " " << tPy_l2[i] << endl;      

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

  ifstream myfile8;
  TString line8;
  count=-2;
  myfile8.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQ20.cal");
  while (! myfile8.eof() ) {
    line8.ReadLine(myfile8);
    if(count < 0){
      count++;
      continue;
    }
    if(line8.IsNull()) break;
    sscanf(line8.Data(),"%g %g", par201+count,par202+count);
    count++;
  }  

  cout << endl << " pars for SQ20 strips" << endl;
  for(Int_t i=0;i<16;i++) cout << par201[i] << " " << par202[i] << endl; 

  //------------------------------------------------------------------------------ 
  TString input_file;
  Float_t zeroPos,shitf;

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
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,mult20,multY_Lt,multX_Lt,multY_Rt,multX_Rt,mult20t,multCsi_R,multCsi_L,timeF5,thresh_X,thresh_Y,thresh_CsI,nCh_L,nCh_R;
  bool ToFflag;
  Float_t maxCsI_R,maxCsI_L;

  // Creating outfile,outtree
  TFile *fw = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14_identificationH3_3.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("CsI_L",&CsI_L,"CsI_L[16]/F");
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
  tw->Branch("multX_L",&multX_L,"multX_L/I");

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
	    count=0;
  maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  //for (Long64_t jentry=0; jentry<maxE;jentry++) {
  for (Long64_t jentry=1; jentry<50;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;

    //----------------------------- CsI module
    for(Int_t i=0;i<16;i++) { // обнуление
      CsI_R[i] = 0;
      CsI_L[i] = 0;
      tCsI_R[i] = 0;
      tCsI_L[i] = 0;
    }
    multCsi_R = 0;
    multCsi_L = 0;    
    //searching for maxAmp of CsI_R and CsI_L
    maxCsI_R = 0; nCh_R = -10;
    maxCsI_L = 0; nCh_L = -10;
    for(Int_t i=0;i<16;i++) {
      if(maxCsI_R<NeEvent_CsI_R[i]) {
        maxCsI_R = NeEvent_CsI_R[i];
        nCh_R = i;  
      }
      if(maxCsI_L<NeEvent_CsI_L[i]) {
        maxCsI_L = NeEvent_CsI_L[i];
        nCh_L = i;  
      }
    }
    // calculation of the multiplicity
    for(Int_t i=0;i<16;i++){
      if(NeEvent_CsI_R[i]==maxCsI_R && maxCsI_R>0) multCsi_R++;
      if(NeEvent_CsI_L[i]==maxCsI_L && maxCsI_L>0) multCsi_L++;
    }

    //Fill
    for(Int_t i=0;i<16;i++) { 
      if(i==nCh_R) {
        CsI_R[i] = NeEvent_CsI_R[i];
        tCsI_R[i] = NeEvent_tCsI_R[i];
      }
      if(i==nCh_L) {
        CsI_L[i] = NeEvent_CsI_L[i];
        tCsI_L[i] = NeEvent_tCsI_L[i];
      }
    }   
    //----------------------------- endl of CsI module

    //----------------------------- Si Det module
    for(Int_t i=0;i<32;i++) { // обнуление
      SQX_L[i] = 0;
      tSQX_L[i] = 0;
      SQX_R[i] = 0;
      tSQX_R[i] = 0;
      if(i<16) {
        SQY_L[i] = 0;
        tSQY_L[i] = 0;
        SQY_R[i] = 0;
        tSQY_R[i] = 0;
        SQ20[i] = 0;
        tSQ20[i] = 0;
      }  
    }
    multY_R = 0; 
    multY_L = 0;
    multX_R = 0;
    multX_L = 0;
    mult20 = 0;
    //Fill
cout << " asdasdasdasd !!! " << endl;
    for(Int_t i=0; i<32; i++) {
      SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
      SQX_L[i] = NeEvent_SQX_L[i]*parXL2[i] + parXL1[i];
      tSQX_R[i] = NeEvent_tSQX_R[i]*0.3;
      tSQX_L[i] = NeEvent_tSQX_L[i]*0.3;

      if(SQX_R[i]>1.3) multX_R++; 
      if(SQX_L[i]>1.3) multX_L++; 
      //tSQX_L[i] = NeEvent_tSQX_L[i]*tPx_l2[i] + tPx_l1[i];

      if(i<16){
        SQY_R[i] = NeEvent_SQY_R[i]*parYR2[i] + parYR1[i];
        SQY_L[i] = NeEvent_SQY_L[i]*parYL2[i] + parYL1[i];
        SQ20[i] = NeEvent_SQ20[i]*par202[i] + par201[i];

        if(SQY_R[i]>1.3) multY_R++; 
        if(SQY_L[i]>1.3) multY_L++; 
        if(SQ20[i]>1.) mult20++; 

        tSQY_R[i] = NeEvent_tSQY_R[i]*0.3;
        tSQY_L[i] = NeEvent_tSQY_L[i]*0.3;
        tSQ20[i] = NeEvent_tSQ20[i]*0.3;
        //cout << tSQ20[i] << " " << SQ20[i] << endl;
        cout << tSQY_L[i] << " " << SQY_L[i] << endl;
        //tSQY_L[i] = NeEvent_tSQY_L[i]*tPy_l2[i] + tPy_l1[i];
      }
    }

   /* if(multX_R>0 && multY_R && multY_L>0 &&  multX_L>0 && mult20>0) {
      cout << "YR XR XL YL 20 " << endl << multY_R << " " <<  multX_R << " " << multX_L << " " << multY_L<< " " << mult20 << endl;
      count ++;
    }*/

    //----------------------------- end of Si Det module


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

    /*
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
      SQX_L[i]=0.;
      tSQX_R[i]=0.;
      tSQX_L[i]=0.;
      if(i<16) {
        CsI_R[i]=0.;
        SQY_R[i]=0.;
      //  SQY_L[i]=0.;
        tSQY_R[i]=0.;
      //  tSQY_L[i]=0.;
        CsI_R[i] = 0;
      }
      if(i<4){
        F3[i] = 0.;
        F5[i] = 0.;
        tF5[i] = 0.;
        tF3[i] = 0.;
      }
    }
  


    for(Int_t i=0; i<32; i++) {
      SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
      //SQX_L[i] = NeEvent_SQX_L[i]*parXL2[i] + parXL1[i];
      if(SQX_R[i]>1.) multX_R++; 
      tSQX_R[i] = NeEvent_tSQX_R[i]*0.3;
      //tSQX_L[i] = NeEvent_tSQX_L[i]*tPx_l2[i] + tPx_l1[i];
     // tSQX_L[i] = NeEvent_tSQX_L[i]*0.3;
      if(i<4) {
        F3[i] = NeEvent_F3[i];
        F5[i] = NeEvent_F5[i];
        tF3[i] = NeEvent_tF3[i]*0.125+89.165;
        tF5[i] = NeEvent_tF5[i]*0.125+89.165;
      }
      if(i==nChannel) {
        CsI_R[i] = NeEvent_CsI_R[i];
        //
        //if(CsI_R[i]>145) thresh_CsI=0; 
      }


      if(i<16){
        if(CsI_R[i]>145) multCsi_R++;
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
    trigger = NeEvent_trigger;*/
	  //if(multX_R>0 && multY_R>0 && timeF5>0 && multCsi_R==1) {
      tw->Fill();
    //}			
  }//entries
//  fw->cd();
//	tw->Write();
	//fw->Close();
  cout << " events nubmer"<<  count << endl;
}
