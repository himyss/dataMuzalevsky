void zeroVars();
void fillSi();

void fillSingleSi(UShort_t *amp,UShort_t *time,Float_t *maxAmp,Int_t *nCh,Float_t *par1,Float_t *par2);
void fillSingleSi20(UShort_t *amp,UShort_t *time,Float_t *maxAmp,Int_t *nCh,Float_t *par1,Float_t *par2,Float_t *ped);


void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

UShort_t SSD_1m_1[16],tSSD_1m_1[16],SSD_1m_2[16],tSSD_1m_2[16],SSD_1m_3[16],tSSD_1m_3[16],SSD_1m_4[16],tSSD_1m_4[16];
UShort_t SSD_20u_1[16],tSSD_20u_1[16],SSD_20u_2[16],tSSD_20u_2[16],SSD_20u_3[16],tSSD_20u_3[16],SSD_20u_4[16],tSSD_20u_4[16];

// for 1-mm dets
Float_t a1,t1,a2,t2,a3,t3,a4,t4;
Int_t n1,n2,n3,n4;

// for 20um dets
Float_t a20_1,t20_1,a20_2,t20_2,a20_3,t20_3,a20_4,t20_4;
Int_t n20_1,n20_2,n20_3,n20_4;

Float_t sq1[16],sq2[16],sq3[16],sq4[16];

Float_t a20_1_cal,a20_2_cal,a20_3_cal,a20_4_cal;

Float_t pD1_1[16],pD1_2[16];
Float_t pD2_1[16],pD2_2[16];
Float_t pD3_1[16],pD3_2[16];
Float_t pD4_1[16],pD4_2[16];

Float_t s1par1[16],s1par2[16];
Float_t s2par1[16],s2par2[16];
Float_t s3par1[16],s3par2[16];
Float_t s4par1[16],s4par2[16];

Float_t pZero1[16],pZero2[16];

Float_t p1[16],p2[16],p3[16],p4[16];

Float_t temp[16];

Int_t trigger;

void covert() {

  readPar("ssd_20u_1",s1par1,s1par2);
  readPar("ssd_20u_2",s2par1,s2par2);
  readPar("ssd_20u_3",s3par1,s3par2);
  readPar("ssd_20u_4",s4par1,s4par2);
  // readPar("tempCal",s4par1,s4par2);

  // for(Int_t i=0;i<16;i++) {
  //   oldpar2[i] = oldpar2[i]/2.;
  //   oldpar1[i] = oldpar1[i]/2.;
  // }

  readPar("SSD_1m_1",pD1_1,pD1_2);
  readPar("SSD_1m_2",pD2_1,pD2_2);
  readPar("SSD_1m_3",pD3_1,pD3_2);
  readPar("SSD_1m_4",pD4_1,pD4_2);

  readPar("empty16",pZero1,pZero2);

  readPar("pedestal1",p1,temp);
  readPar("pedestal2",p2,temp);
  readPar("pedestal3",p3,temp);
  readPar("pedestal4",p4,temp);

  TChain *inTree = new TChain("AnalysisxTree");
  inTree->Add("/home/oem/work/data/exp1904/clb/20um_1mm*");

  inTree->SetMakeClass(1);

  inTree->SetBranchAddress("NeEvent.SSD_1m_1[16]",     SSD_1m_1);
  inTree->SetBranchAddress("NeEvent.tSSD_1m_1[16]",    tSSD_1m_1);

  inTree->SetBranchAddress("NeEvent.SSD_1m_2[16]",     SSD_1m_2);
  inTree->SetBranchAddress("NeEvent.tSSD_1m_2[16]",    tSSD_1m_2);

  inTree->SetBranchAddress("NeEvent.SSD_1m_3[16]",     SSD_1m_3);
  inTree->SetBranchAddress("NeEvent.tSSD_1m_3[16]",    tSSD_1m_3);    

  inTree->SetBranchAddress("NeEvent.SSD_1m_4[16]",     SSD_1m_4);
  inTree->SetBranchAddress("NeEvent.tSSD_1m_4[16]",    tSSD_1m_4); 

  // 20 micron
  inTree->SetBranchAddress("NeEvent.SSD_20u_1[16]",     SSD_20u_1);
  inTree->SetBranchAddress("NeEvent.tSSD_20u_1[16]",    tSSD_20u_1);

  inTree->SetBranchAddress("NeEvent.SSD_20u_2[16]",     SSD_20u_2);
  inTree->SetBranchAddress("NeEvent.tSSD_20u_2[16]",    tSSD_20u_2);

  inTree->SetBranchAddress("NeEvent.SSD_20u_3[16]",     SSD_20u_3);
  inTree->SetBranchAddress("NeEvent.tSSD_20u_3[16]",    tSSD_20u_3);    

  inTree->SetBranchAddress("NeEvent.SSD_20u_4[16]",     SSD_20u_4);
  inTree->SetBranchAddress("NeEvent.tSSD_20u_4[16]",    tSSD_20u_4); 

  inTree->SetBranchAddress("NeEvent.trigger",     &trigger);

    TFile *outF = new TFile("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cal_1.root","RECREATE");
    TTree *outTree= new TTree("tree","data");

    //1 mm 
    outTree->Branch("a1.",&a1,"a1/F");
    outTree->Branch("a2.",&a2,"a2/F");
    outTree->Branch("a3.",&a3,"a3/F");
    outTree->Branch("a4.",&a4,"a4/F");

    // outTree->Branch("t1.",&t1,"t1/F");
    // outTree->Branch("t2.",&t2,"t2/F");
    // outTree->Branch("t3.",&t3,"t3/F");
    // outTree->Branch("t4.",&t4,"t4/F");

    outTree->Branch("n1.",&n1,"n1/I");
    outTree->Branch("n2.",&n2,"n2/I");
    outTree->Branch("n3.",&n3,"n3/I");
    outTree->Branch("n4.",&n4,"n4/I");

    // 20 um
    outTree->Branch("a20_1.",&a20_1,"a20_1/F");
    outTree->Branch("a20_2.",&a20_2,"a20_2/F");
    outTree->Branch("a20_3.",&a20_3,"a20_3/F");
    outTree->Branch("a20_4.",&a20_4,"a20_4/F");

    outTree->Branch("a20_1_cal.",&a20_1_cal,"a20_1_cal/F");
    outTree->Branch("a20_2_cal.",&a20_2_cal,"a20_2_cal/F");
    outTree->Branch("a20_3_cal.",&a20_3_cal,"a20_3_cal/F");
    outTree->Branch("a20_4_cal.",&a20_4_cal,"a20_4_cal/F");

    outTree->Branch("sq1",sq1,"sq1[16]/F");
    outTree->Branch("sq2",sq2,"sq2[16]/F");
    outTree->Branch("sq3",sq3,"sq3[16]/F");
    outTree->Branch("sq4",sq4,"sq4[16]/F");

    // outTree->Branch("t20_1.",&t20_1,"t20_1/F");
    // outTree->Branch("t20_2.",&t20_2,"t20_2/F");
    // outTree->Branch("t20_3.",&t20_3,"t20_3/F");
    // outTree->Branch("t20_4.",&t20_4,"t20_4/F");

    outTree->Branch("n20_1.",&n20_1,"n20_1/I");
    outTree->Branch("n20_2.",&n20_2,"n20_2/I");
    outTree->Branch("n20_3.",&n20_3,"n20_3/I");
    outTree->Branch("n20_4.",&n20_4,"n20_4/I");

    cout << inTree->GetEntries() << endl;
    // for(Int_t nentry=1;nentry<inTree->GetEntries();nentry++) {
    for(Int_t nentry=1;nentry<2000000;nentry++) {      
      if(nentry%10000==0) cout << "#Event " << nentry << "#" << endl;
    // for(Int_t nentry=1;nentry<10000;nentry++) {
      inTree->GetEntry(nentry);
      zeroVars();
      fillSi();

      fillSingleSi(SSD_1m_1,tSSD_1m_1,&a1,&n1,pD1_1,pD1_2); 
      fillSingleSi(SSD_1m_2,tSSD_1m_2,&a2,&n2,pD2_1,pD2_2);
      fillSingleSi(SSD_1m_3,tSSD_1m_3,&a3,&n3,pD3_1,pD3_2);
      fillSingleSi(SSD_1m_4,tSSD_1m_4,&a4,&n4,pD4_1,pD4_2);

      fillSingleSi20(SSD_20u_1,tSSD_20u_1,&a20_1,&n20_1,pZero1,pZero2,p1);
      fillSingleSi20(SSD_20u_2,tSSD_20u_2,&a20_2,&n20_2,pZero1,pZero2,p2);
      fillSingleSi20(SSD_20u_3,tSSD_20u_3,&a20_3,&n20_3,pZero1,pZero2,p3);
      fillSingleSi20(SSD_20u_4,tSSD_20u_4,&a20_4,&n20_4,pZero1,pZero2,p4);

      fillSingleSi20(SSD_20u_1,tSSD_20u_1,&a20_1_cal,&n20_1,s1par1,s1par2,p1);
      fillSingleSi20(SSD_20u_2,tSSD_20u_2,&a20_2_cal,&n20_2,s2par1,s2par2,p2);
      fillSingleSi20(SSD_20u_3,tSSD_20u_3,&a20_3_cal,&n20_3,s3par1,s3par2,p3);
      fillSingleSi20(SSD_20u_4,tSSD_20u_4,&a20_4_cal,&n20_4,s4par1,s4par2,p4);

      outTree->Fill();
    }
    outF->cd();
    outTree->Write();
    outF->Close();
}

void zeroVars() {

  for(Int_t i=0;i<16;i++) {
    sq1[i] = 0;
    sq2[i] = 0;
    sq3[i] = 0;
    sq4[i] = 0;
  }

  //for 1-mm dets
  a1=0;
  // t1=0;
  a2=0;
  // t2=0;
  a3=0;
  // t3=0;
  a4=0;
  // t4=0;
  n1=-1;
  n2=-1;
  n3=-1;
  n4=-1;

  //for 20um dets
  a20_1=0;
  // t20_1=0;
  a20_2=0;
  // t20_2=0;
  a20_3=0;
  // t20_3=0;
  a20_4=0;
  // t20_4=0;
  n20_1=-1;
  n20_2=-1;
  n20_3=-1;
  n20_4=-1;

  a20_1_cal=0;
  a20_2_cal=0;
  a20_3_cal=0;
  a20_4_cal=0;
} 

void fillSi() {

  for(Int_t i=0;i<16;i++) {
    sq1[i] = SSD_20u_1[i]*s1par2[i] + s1par1[i];
    sq2[i] = 0;
    sq3[i] = 0;
    sq4[i] = 0;
  }

}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){
  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/oem/work/software/AculUti/data/exp1904/" + fileName + ".cal";
  myfile.open(file.Data());
  if(!myfile.is_open()){
    cout << "no such file " << file.Data() << endl;
    return;
  } 
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    if(count < 0){
      count++;
      continue;
    }
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g %g", par1+count,par2+count);
    count++;
  }
  cout << endl << fileName.Data() << endl;
  for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

  return;
}

void fillSingleSi(UShort_t *amp,UShort_t *time,Float_t *maxAmp,Int_t *nCh,Float_t *par1,Float_t *par2) {
  Int_t ch = -1;
  Int_t count = 0;
  for(Int_t k=0;k<16;k++) {
    if(*(amp+k)>0 && *(time+k)>0) {
      ch = k;
      count++;
    }
  }
  if(count==1 && ch>-1) {
    *maxAmp = *(amp+ch)*(*(par2+ch)) + (*(par1+ch));
    *nCh = ch;
  } 
}

void fillSingleSi20(UShort_t *amp,UShort_t *time,Float_t *maxAmp,Int_t *nCh,Float_t *par1,Float_t *par2,Float_t *ped) {
  Int_t ch = -1;
  Int_t count = 0;
  for(Int_t k=0;k<16;k++) {
    if(*(amp+k)>0 && *(time+k)>0) {
      ch = k;
      count++;
    }
  }
  if(count==1 && ch>-1) {
    *maxAmp = *(amp+ch)*(*(par2+ch)) + (*(par1+ch));
    *nCh = ch;
  } 
}
