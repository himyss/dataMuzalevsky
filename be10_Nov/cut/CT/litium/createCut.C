
{
  // Int_t j = 5;
  // TString fileName;
  // fileName.Form("li_%d.root",j);
  // TFile *f = new TFile("li_1.root");
  // TCutG *cutL = (TCutG*)f->Get("CUTG");


  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_cut.root");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_cut.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  TCanvas *c3h = new TCanvas("c3h","",1800,1000);  

  Int_t i = 10;

  ch->SetMarkerColor(kBlack);      
  cut.Form("nCsI==%d && flagCent",i);

  hdraw.Form("X_C:aCsI >> (4200,0,4200,300,20,100)");
  ch->Draw(hdraw.Data(),cut.Data(),"");

}
