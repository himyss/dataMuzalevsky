{

  TChain *ch = new TChain("tree");
  ch->Add("/home/muzalevsky/work/exp1803/data/exp1804/h5_14_id1_test.root");

  Float_t CsI_R[16],SQX_R[32],CsI,SQX[8];
  ch->SetBranchAddress("CsI_R",CsI_R);
  ch->SetBranchAddress("SQX_R",SQX_R);

  TFile *fw = new TFile("CsI_7.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("CsI",&CsI,"CsI/F");
  tw->Branch("SQX",&SQX,"SQX[8]/F");


  for(Int_t nevent=0;nevent<ch->GetEntries();nevent++){
    ch->GetEntry(nevent);

    CsI = 0;
    for(Int_t i =0;i<8;i++){
      SQX[i] = 0;
    }   

    CsI = CsI_R[4];
    for(Int_t i =0;i<8;i++){
      SQX[i] = SQX_R[i+8];
    } 
    tw->Fill();
  }  
  fw->cd();
  tw->Write();
  fw->Close();
}
