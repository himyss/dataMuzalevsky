void thickness(){

  TELoss fAlphaSi;
  fAlphaSi.SetEL(1, 2.321); // density in g/cm3
	fAlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//	mSi.SetZP(1., 1.);		//protons
	fAlphaSi.SetZP(2., 4.);		//alphas, Z, A
	fAlphaSi.SetEtab(100000, 200.);	// ?, MeV calculate ranges
	fAlphaSi.SetDeltaEtab(300);

  
  ifstream myfile3;
  TString line3;
  Int_t count=-2;
  //myfile3.open("/home/muzalevsky/work/exp1803/data/siCal/SQX_L.cal");
  myfile3.open("/home/muzalevsky/work/temp/SQX_L.cal");
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

  //cout << endl << " pars for XL strips" << endl;
  //for(Int_t i=0;i<32;i++) cout << parXL1[i] << " " << parXL2[i] << endl;   

  ifstream myfile4;
  TString line4;
  count=-2;
//  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/SQY_L.cal");
  myfile4.open("/home/muzalevsky/work/temp/SQY_L.cal");
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

  ifstream myfile7;
  TString line7;
  count=-2;
  myfile7.open("/home/muzalevsky/work/temp/SQ20.cal");
  while (! myfile7.eof() ){
    line7.ReadLine(myfile7);
    if(count < 0){
      count++;
      continue;
    }
    if(line7.IsNull()) break;
    sscanf(line7.Data(),"%g %g", par20_1+count,par20_2+count);
    count++;
  }



  
  
  Float_t SQX_L[32],SQY_L[16],SQ20[16],thick;
  Int_t multY_L,multX_L,multY_R,multX_R,multSQ20,trigger,NeEvent_trigger,flag,flag1;
		
  TFile *f = new TFile("out.root");
  TTree *t = (TTree*)f->Get("tree");

  t->SetBranchAddress("SQX_L",&SQX_L);
  t->SetBranchAddress("SQY_L",&SQY_L);
  t->SetBranchAddress("SQ20",&SQ20);
  t->SetBranchAddress("multY_L",&multY_L);
  t->SetBranchAddress("multX_L",&multX_L);
  t->SetBranchAddress("multSQ20",&multSQ20);
//	TH2F(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup)
//:Fill(Double_t x, Double_t y)
  TH2F *thickness = new TH2F("thickness", "thickness distribution", 16, 0, 15, 16, 0, 16);
  
  /*for(Int_t i=0;i<tree->GetEntries();i++) {
    if(multY_L!=1 && multX_L!=1 && multSQ20!=1) continue;
  
    for(Int_t x=0;x<16;x++) { //x strips
      for(Int_t y=0;y<16;y++) { // y cuts
        if(SQ20[x]>200*par20_2[x] + par20_1[x]) {
          if(SQY_L[y]>3.2) { // for 7.8 MeV alpha
            thick = fAlphaSi.GetR(7.6869, SQY_L[y]);
            thickness
          } // if SQY_L[y]
        } // if SQ20[x]     
      } // y
    }// x


  }*/

  

    


  /*t1->SetBranchAddress("ev",&ev);

  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("SQ20",&SQ20,"SQ20[16]/F");
  tw->Branch("multY_L",&multY_L,"multY_L/I");
  tw->Branch("multX_L",&multX_L,"multX_L/I");
  tw->Branch("multSQ20",&multSQ20,"multSQ20/I");
  tw->Branch("trigger",&trigger,"trigger/I");*/


}
