void dl_map(){

  TFile *f = new TFile("dl_map.root","RECREATE");
  TH2F *hmap = new TH2F("hmap","map of the effective dl ration",16,0,16,16,0,16);

  Float_t a;

  Float_t x0,y0;
  x0 = -20.8 - 25;
  y0 = 46.3 + 25;

  Float_t x,y;
  Float_t angle[16][16];
  // x = -20.8;
  // y = 46.3; 
  // a = 270./sqrt(270*270 + x*x + y*y);
  // cout << TMath::ACos(a)*TMath::RadToDeg() << endl;

  // cout << TMath::ATan(sqrt(x*x + y*y)/270.)*TMath::RadToDeg() << endl;

  for(Int_t i=0;i<16;i++) {
    for(Int_t j=0;j<16;j++) {
      x = x0 + i*50./16;
      y = y0 - j*50./16;
      // angle[i][j] = 270./sqrt(270*270 + x*x + y*y);
      angle[i][j] = TMath::ATan(sqrt(x*x + y*y)/270.)*TMath::RadToDeg();
      hmap->SetBinContent(i+1,j+1,angle[i][j]);
    }
  }
  // angle[]
  // for(Int_t )

  hmap->Draw("TEXTCOLZ");

  f->cd();
  hmap->Write();
  f->Close();

  return;
}