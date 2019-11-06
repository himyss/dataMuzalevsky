
{
  // Int_t j = 5;
  // TString fileName;
  // fileName.Form("li_%d.root",j);
  // TFile *f = new TFile("li_1.root");
  // TCutG *cutL = (TCutG*)f->Get("CUTG");


  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_cut.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  TCanvas *c3h = new TCanvas("c3h","",1800,1000);  

  Int_t i = 15;

  ch->SetMarkerColor(kBlack);      
  cut.Form("nCsI==%d && tX_C-tF5<-140",i);

  hdraw.Form("X_C:aCsI");
  ch->Draw(hdraw.Data(),cut.Data(),"");

  // cutL->SetLineColor(kRed);
  // cutL->Draw("same");

  // c3h->Update();


}
