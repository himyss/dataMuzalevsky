void drawHe_Right() {

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all_cut.root");

  //--------------------------------------------------------------------------------
  TString canName,hDraw,cut;

  TCutG *cutCsI_s[16],*cut3h[16],*cutX_L[16],*cutY_L[16],*cutSQ20_L[16],*cuthe3[16],*cutSQ20_R[16],*cutY_R[16],*cuthe3_R[16];
  TString cutName;
  TFile *f1;

  for(Int_t i=0;i<16;i++) {
    cutName.Form("/home/oem/work/macro/he8_1811/he3_cut_R/he3_%d.root",i);
    f1 = new TFile(cutName.Data());
    cuthe3_R[i] = (TCutG*)f1->Get("CUTG");
    if (!cuthe3_R[i]) {
      cout << i  << " no cut"<< endl;
      return;
    }
    delete f1;
  }

  TCanvas *c_arr[16];
  for(Int_t i=0;i<16;i++){
    canName.Form("c%d",i+1);
    c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
  }
  // TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);

Int_t nC = 0;
Int_t temp;
  for(Int_t i=0;i<16;i++) {
 // { Int_t i =14;
    c_arr[i]->cd();
    // c1->cd(i+1);
    cut.Form("flagRight && Y_R>0 && n20_R==%d",i);
    hDraw.Form("a20_R:Y_R>>h%d(200,0,50,200,0,4)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    

    ch->SetMarkerSize(1);
    cut.Form("flagRight && Y_R>0 && n20_R==%d && nh3",i);
    ch->SetMarkerColor(kRed);
    ch->SetMarkerStyle(20);
    hDraw.Form("a20_R:Y_R>>h_red%d(200,0,50,200,0,4)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"same");

    cuthe3_R[i]->SetLineColor(kBlack);
    cuthe3_R[i]->Draw("same");

    ch->SetMarkerSize(2);
    cut.Form("flagRight && Y_R>0 && n20_R==%d && nh3 && nhe3_R",i);
    ch->SetMarkerColor(kMagenta);
    hDraw.Form("a20_R:Y_R>>h_mag%d(200,0,50,200,0,4)",i);
    nC += ch->Draw(hDraw.Data(),cut.Data(),"same");

    c_arr[i]->Update();

  }

cout << nC << endl;

  // c_arr[0]->Print("/home/oem/Desktop/pics/de_E_right_all.pdf");
  // c_arr[0]->Print("/home/oem/Desktop/pics/de_E_right_all.pdf[");
  // c_arr[0]->Print("/home/oem/Desktop/pics/de_E_right_all.pdf");
  // for(Int_t i=1;i<15;i++) {
  //   c_arr[i]->Print("/home/oem/Desktop/pics/de_E_right_all.pdf");
  // }
  // c_arr[15]->Print("/home/oem/Desktop/pics/de_E_right_all.pdf");
  // c_arr[15]->Print("/home/oem/Desktop/pics/de_E_right_all.pdf]");

return;
  
}