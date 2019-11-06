
{
  // Int_t j = 5;
  // TString fileName;
  // fileName.Form("li_%d.root",j);
  // TFile *f = new TFile("li_1.root");
  // TCutG *cutL = (TCutG*)f->Get("CUTG");


  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_cut_newMult.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  TCanvas *c3h = new TCanvas("c3h","",1800,1000);  

  Int_t i = 2;

  ch->SetMarkerStyle(1);
  ch->SetMarkerColor(kBlack);      
  cut.Form("nCsI==%d && flagCent",i);

  hdraw.Form("X_C:aCsI");
  ch->Draw(hdraw.Data(),cut.Data(),"");

  ch->SetMarkerColor(kRed); 
  ch->SetMarkerStyle(8);     
  cut.Form("nCsI==%d && flagCent && ( (flag1 && nhe3_1) || (flag2 && nhe3_2) || (flag3 && nhe3_3) || (flag4 && nhe3_4))",i);

  hdraw.Form("X_C:aCsI");
  ch->Draw(hdraw.Data(),cut.Data(),"same");


}
