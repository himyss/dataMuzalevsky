void findThresolds() {
  
  TString hCut,hDraw,histName;

  // TChain *ch2 = new TChain("AnalysisxTree"); //e4
  // ch2->Add("/home/oem/work/data/exp1904/clb/20um_1mm*");



  // TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // c1->Divide(4,4);

  // for(Int_t i=0;i<16;i++) {
  // // { Int_t i = 0;
  //   c1->cd(i+1);
  //   // histName.Form("h%d_ped",i);
  //   hCut.Form("tSSD_20u_4[%d]!=0",i);
  //   hDraw.Form("SSD_20u_4[%d]:tSSD_20u_4[%d]>>h%d_ped(250,1000,1500,250,450,950)",i,i,i);
  //   ch2->Draw(hDraw.Data(),hCut.Data(),"col",1000000,0);
    

  //   c1->Update();
  // }

  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");



  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4,4);

  for(Int_t i=0;i<16;i++) {
    c1->cd(i+1);
    // histName.Form("h%d_ped",i);
    hCut.Form("n20_3==%d",i);
    // hDraw.Form("a20_4:t20_4>>h%d_ped(100,1000,1500,100,0,100)",i);
    hDraw.Form("a20_3>>h%d_ped(100,0,100)",i);
    ch2->Draw(hDraw.Data(),hCut.Data(),"",10000000,0);
    

    c1->Update();
  }

}