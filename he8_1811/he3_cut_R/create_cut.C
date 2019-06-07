void create_cut() {

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all_cut.root");

  //--------------------------------------------------------------------------------
  TString canName,hDraw,cut;

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);

  // for(Int_t i=0;i<16;i++) {
 { Int_t i = 2;
    // c_arr[i]->cd();
    // c1->cd(i+1);
    cut.Form("flagRight && Y_R>0 && n20_R==%d",i);
    hDraw.Form("a20_R:Y_R>>h%d(200,0,50,200,0,4)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"col");
    c1->Update();

    ch->SetMarkerSize(1.);
    cut.Form("flagRight && Y_R>0 && n20_R==%d && nh3",i);
    ch->SetMarkerColor(kRed);
    ch->SetMarkerStyle(20);
    hDraw.Form("a20_R:Y_R>>h_red%d(200,0,50,200,0,4)",i);
    ch->Draw(hDraw.Data(),cut.Data(),"same");

  }

return;
  
}