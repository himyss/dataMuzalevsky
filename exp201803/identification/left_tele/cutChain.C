void cutChain(){
  
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/analysisexp1804/h5_14_1.root");

  TFile *f = new TFile("/media/user/work/macro/exp201803/identification/left_tele/cut/tritium.root");
  TCutG *cut = (TCutG*)f->Get("CUTG");

  Float_t CsI,SQX_R[32],SQY_R[16],SQX_L[32],SQY_L[16],SQ20[16];
  Int_t trigger,flagL,flagR;

  ch->SetBranchAddress("CsI", &CsI);
  ch->SetBranchAddress("SQX_R", SQX_R);
  ch->SetBranchAddress("SQY_R", SQY_R);
  ch->SetBranchAddress("SQX_L", SQX_L);
  ch->SetBranchAddress("SQY_L", SQY_L);
  ch->SetBranchAddress("SQ20", SQ20);
  ch->SetBranchAddress("trigger", &trigger);
  ch->SetBranchAddress("flagL", &flagL);
  ch->SetBranchAddress("flagR", &flagR);




  Int_t flagT;

  TFile *fw = new TFile("/media/user/work/data/analysisexp1804/h5_14_03_tritium.root", "RECREATE");
  TTree *tw = new TTree("tree", "tritium 70-90MeV cut");

  tw->Branch("CsI",&CsI,"CsI/F");
  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("SQ20",&SQ20,"SQ20[16]/F");
  tw->Branch("SQX_R",&SQX_R,"SQX_R[32]/F");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
  tw->Branch("trigger",&trigger,"trigger/I");
  tw->Branch("flagT",&flagT,"flagT/I");
  tw->Branch("flagL",&flagL,"flagL/I");
  tw->Branch("flagR",&flagR,"flagR/I");

  for(Int_t n=0;n<ch->GetEntries();n++){
    flagT = 0;
    ch->GetEntry(n);
    // if(trigger!=3) continue;
    for(Int_t i=0;i<32;i++){
      if(cut->IsInside(CsI+SQX_R[i],SQX_R[i])==1 && flagR==1) flagT=1;
    }
    tw->Fill();
  }

  fw->cd();
  tw->Write();
  fw->Close();

}