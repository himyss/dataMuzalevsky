void drawBanana(){

  TF1 *f = new TF1("f","50/(x)",10,200);
  // TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10);

  TChain *ch = new TChain("tree");
  // ch->Add("/media/user/work/data/analysisexp1804/h5_14_1.root");
  ch->Add("/media/user/work/data/analysisexp1804/h5_14_03_tritium.root");

  TCanvas *c1 = new TCanvas("c1","de-E plots",1800,1000);
  c1->Divide(4,4);
  //TH2F *h = new TH2F("h","dE-E",500,0,4000,500,0,50);
  TString hDraw,hCut,hName,hDraw1,hCut1;

  TH2F *hSum,*htemp[16];
  hSum = new TH2F("hSum","summ dE-E",500,1,20,500,1,12);

  // TFile *fw = new TFile("bananaNew.root", "RECREATE");
  // fw->cd();

 
  for(Int_t i=0;i<16;i++){
    c1->cd(i+1);

    // tree->Draw("SQ20[7]:SQY_L>>(200,1,20,200,1,12)","SQ20[7]>1 && SQY_L>1.5 && trigger==3","col")
    // ch->SetMarkerStyle(8);
    // hDraw.Form("SQ20[%d]:(SQY_L+SQ20[%d])>>h_%d(100,1.,30,100,1.,6)",i,i,i);
    hDraw.Form("SQ20[%d]:(SQY_L+SQ20[%d])>>h_%d(100,1.,30,100,1.,6)",i,i,i);
    hCut.Form("SQ20[%d]>1.5 && SQY_L>1.5 && trigger==3 && flagL==1 && flagT==1",i);

    hDraw1.Form("SQ20[%d]:(SQY_L+SQ20[%d])>>hC_%d(100,1.,30,100,1.,6)",i,i,i);
    hCut1.Form("SQ20[%d]>1.5 && SQY_L>1.5 && trigger==3 && flagL==1",i);


    ch->SetMarkerColor(kBlack);
    ch->Draw(hDraw.Data(),hCut.Data(),"");

    // ch->SetMarkerColor(kRed);
    // ch->Draw(hDraw1.Data(),hCut1.Data(),"same");

    // htemp[i] = (TH2F*)gPad->GetPrimitive("h");

    // cout << htemp->GetEntries() << endl;
    // hSum->Add(htemp[i]);
    //if(i!=0) ch->Draw(hDraw.Data(),hCut.Data(),"same");
    c1->Update();
    cout <<  i << endl;
    //gPad->SetLogz();

  }
  // c1->cd(2);
  // hSum->Draw("col");
  // f->Draw("same");
  // f->SetLineWidth(2);
  // f->SetLineColor(4);


  // hSum->Write();
  // fw->Close();

}
