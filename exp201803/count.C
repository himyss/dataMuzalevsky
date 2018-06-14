void count() { 
  TString input_file;
  Float_t CsI_R[16],F3[4],tF3[4],F5[4],tF5[4],SQX_R[32],SQY_R[16],SQX_L[32],SQY_L[16],tSQX_R[32],tSQY_R[16],tSQX_L[32],tSQY_L[16],zeroPos,shitf;
  //TTree* 		t;
  TChain *t = new TChain("AnalysisxTree");
  UShort_t    NeEvent_CsI_R[16],NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4],NeEvent_SQX_R[32],NeEvent_SQY_R[16],NeEvent_SQX_L[32],NeEvent_SQY_L[16],NeEvent_tSQX_R[32],NeEvent_tSQY_R[16],NeEvent_tSQX_L[32],NeEvent_tSQY_L[16];
  TBranch    *b_NeEvent_CsI_R,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5,*b_NeEvent_SQX_R,*b_NeEvent_SQY_R,*b_NeEvent_SQX_L,*b_NeEvent_SQY_L,*b_NeEvent_tSQX_R,*b_NeEvent_tSQY_R,*b_NeEvent_tSQX_L,*b_NeEvent_tSQY_L,*b_NeEvent_trigger;
  Long64_t nentries1;
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,trigger,NeEvent_trigger,x,y;

  // Creating outfile,outtree
  TFile *fw = new TFile("out.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  //tw->Branch("mult1mm",&mult1mm,"mult1mm[32][16]/F");
  tw->Branch("trigger",&trigger,"trigger/I");

  // Creating outCountfile
  TFile *fcount = new TFile("count.root", "RECREATE");

	t->Add("/media/analysis_nas/exp201804/calib/si_after/si-1_si-20_35cm_0deg_new1_*.root");

  t->SetMakeClass(1);
  t->SetBranchAddress("NeEvent.SQY_R[16]", NeEvent_SQY_R, &b_NeEvent_SQY_R);
  t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
  t->SetBranchAddress("NeEvent.SQY_L[16]", NeEvent_SQY_L, &b_NeEvent_SQY_L);
  t->SetBranchAddress("NeEvent.trigger", &NeEvent_trigger, &b_NeEvent_trigger);
	
  TH2I *nSQ = new TH2I("nSQ","counts in 1 mm det",32,0,32,16,0,16);
  for(Int_t i = 0; i<32;i++) { 
    for(Int_t j = 0; j<16;j++) {    
        nSQ->SetBinContent(i,j,0);
    }
  }

  TH2I *nSQmm = new TH2I("nSQmm","counts in 1 mm det",32,0,58,16,0,58);
  for(Int_t i = 0; i<32;i++) { 
    for(Int_t j = 0; j<16;j++) {    
        nSQmm->SetBinContent(i,j,0);
    }
  }

  nentries1 = t->GetEntries();
  cout << nentries1 << endl;

  maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  for (Long64_t jentry=0; jentry<maxE;jentry++) {
	  t->GetEntry(jentry);
    // обнуление
    trigger=0;
    multY_R = 0;
    multY_L = 0; 
    multX_L = 0; 
    for(Int_t i = 0; i<32;i++) { 
      SQX_L[i]=0.;
      if(i<16) {
        SQY_R[i]=0.;
        SQY_L[i]=0.;
      }
    }
    
    for(Int_t i=0; i<32; i++) {
      SQX_L[i] = NeEvent_SQX_L[i];
      if(SQX_L[i]>200){
        multX_L++;
        x = i;
      } 
      if(i<16){
        SQY_R[i] = NeEvent_SQY_R[i];
        if(SQY_R[i]>200){
          multY_R++;
        }
        SQY_L[i] = NeEvent_SQY_L[i];
        if(SQY_L[i]>150){
          y = i; 
          multY_L++;
        }
      }
    }
    if(multY_L==1 && multX_L==1 && multY_R>0){
      nSQ->SetBinContent(x,y,nSQ->GetBinContent(x,y)+1);
      nSQmm->SetBinContent(x,y,nSQmm->GetBinContent(x,y)+1);
    }
    trigger = NeEvent_trigger;
	  tw->Fill();			
  }//entries
  fw->cd();
	tw->Write();
	fw->Close();
  
  fcount->cd();
  nSQ->Write();
  nSQmm->Write();
  fcount->Close();

}
