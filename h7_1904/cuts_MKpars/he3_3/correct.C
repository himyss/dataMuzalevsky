TCutG *cutCsI[16],*cut3h[16],*cutX_C[16];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];

void correct(){
  
  TChain *ch = new TChain("tree");
  // ch->Add("/media/ivan/data/exp1904/analysed/beamDiagnostics/se*");
  ch->Add("/media/ivan/data/exp1904/analysed/MKpars/select_noveto.root");
  // ch->Add("/media/ivan/data/exp1904/analysed/oldPars/mm_400.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;
  TCanvas *c1 = new TCanvas("c1","title",1800,1000);

  Int_t i = 1;

  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);
  ch->SetMarkerStyle(7); 
  cut.Form("n20_3==%d && a1_3<30 && a1_3>0 && a20_3>0.1 && a20_3<3",i);
  hdraw.Form("a20_3:a1_3>>h%d1",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");
  // c3h->Update();
  c1->Update();

  ch->SetMarkerStyle(4);    
  ch->SetMarkerColor(kRed);      
  // cut.Form("n20_1==%d && nhe3_1",i);
  cut += " && nh3";
  hdraw.Form("a20_3:a1_3>>h%d_triton1",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");
  // c3h->Update();
  c1->Update();


}
