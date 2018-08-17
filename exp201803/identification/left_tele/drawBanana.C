void drawBanana(){

  TF1 *f = new TF1("f","50/(x)",10,200);
  // TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10);

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/analysisexp1804/tmp.root");

  TCanvas *c1 = new TCanvas("c1","de-E plots");
  c1->Divide(2,1);
  //TH2F *h = new TH2F("h","dE-E",500,0,4000,500,0,50);
  TString hDraw,hCut,hName;

  TH2F *hSum,*htemp[16];
  hSum = new TH2F("hSum","summ dE-E",500,1,20,500,1,12);

  TFile *fw = new TFile("bananaNew.root", "RECREATE");
  fw->cd();

  c1->cd(1);  
  for(Int_t i=0;i<16;i++){
    // c1->cd(i+1);

    // tree->Draw("SQ20[7]:SQY_L>>(200,1,20,200,1,12)","SQ20[7]>1 && SQY_L>1.5 && trigger==3","col")

    hDraw.Form("SQ20[%d]:SQX_L>>h(500,1,20,500,1,12)",i);
    hCut.Form("SQ20[%d]>1 && SQX_L>1.5 && trigger==3",i);
    ch->Draw(hDraw.Data(),hCut.Data(),"col");

    htemp[i] = (TH2F*)gPad->GetPrimitive("h");

    // cout << htemp->GetEntries() << endl;
    hSum->Add(htemp[i]);
    //if(i!=0) ch->Draw(hDraw.Data(),hCut.Data(),"same");
    c1->Update();
    cout <<  i << endl;
    //gPad->SetLogz();

  }
  c1->cd(2);
  hSum->Draw("col");
  // f->Draw("same");
  // f->SetLineWidth(2);
  // f->SetLineColor(4);
  c1->Update();



  hSum->Write();
  fw->Close();

}
