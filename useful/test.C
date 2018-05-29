{
  Float_t summ[4],summX;

  TFile *fw = new TFile("test.root", "RECREATE");
  TTree *tw = new TTree("tree", "test data");
  tw->Branch("summ",&summ,"summ[4]/F");    
  tw->Branch("summX",&summX,"summX/F");
  for(Int_t i=0;i<10;i++) {
    for(Int_t j=0;j<4;j++) summ[j] = j+1;
    summX = 10;
    tw->Fill();
  }
  fw->Write();
  fw->Close();
}
