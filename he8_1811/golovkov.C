void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);

  TString hCut,hDraw,histName;

  TH1F *hFit[16];

  TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

  Double_t fitMin,fitMax;

  Double_t k[16];

void golovkov() {
  
  gStyle->SetOptStat(0);


  // gStyle->SetOptStat(0);

  // TChain *ch1 = new TChain("tree"); //e4
  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_cut.root");
  // ch1->Add("/home/oem/work/data/exp1811/analysed/clb/oldLib/dsd_20_l_04_selected.root");
  ch1->Add("/home/oem/work/data/exp1811/analysed/clb/oldLib/dsd_20_l_03_selected.root");
  
  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(3.,4);

  Double_t temp[16];

  for(Int_t i=0;i<10;i++) {
    c3->cd(i+1);
    hCut.Form("n20_L==%d && nY_L==-1",i);
    histName.Form("h%d",i);
    hDraw.Form("a20_L_cal.>>h%d(87,5,6)",i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k[i] =  4.7/fitAuto->GetParameter(1);

    c3->Update();
  }

  for (Int_t i=0;i<10;i++) {
    cout << k[i] << endl;
  }

  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(3.,4);

  for(Int_t i=0;i<10;i++) {
    c4->cd(i+1);
    hCut.Form("n20_L==%d && nY_L!=-1",i);
    histName.Form("h%d_summ",i);
    hDraw.Form("a20_L_cal*%lf + Y_L>>h%d_summ(150,6.5,8)",k[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");
    c4->Update();
  }


  // for(Int_t i=0;i<10;i++) {
  //   cout << 4.7/temp[i] << endl;
  // }


}


void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th) {
  Int_t nBin = h->GetMaximumBin();
  // cout << nBin << endl;
  // cout << h->GetBinContent(nBin) << " " <<  h->GetMaximum()*th << endl;
  // return;

  while (h->GetBinContent(nBin) > h->GetMaximum()*th || h->GetBinContent(nBin+1) > h->GetMaximum()*th) {
    nBin++;
  }
  *fUp = h->GetBinCenter(nBin+1);

  nBin = h->GetMaximumBin();

  while (h->GetBinContent(nBin) > h->GetMaximum()*th || h->GetBinContent(nBin-1) > h->GetMaximum()*th) {
    nBin--;
  }
  *fDown = h->GetBinCenter(nBin-1);

  return;
}