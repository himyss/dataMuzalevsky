
{
  // Int_t j = 5;
  // TString fileName;
  // fileName.Form("li_%d.root",j);
  // TFile *f = new TFile("li_1.root");
  // TCutG *cutL = (TCutG*)f->Get("CUTG");


  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_cut.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;

  TCanvas *c3h = new TCanvas("c3h","",1800,1000);  

  Int_t i = 15;

  ch->SetMarkerColor(kBlack);      
  cut.Form("nCsI==%d && flagCent",i);

  hdraw.Form("X_C:aCsI >> h1(4200,0,4200,300,20,100)");
  ch->Draw(hdraw.Data(),cut.Data(),"");


  ch->SetMarkerColor(kRed);
  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.8);    
  cut.Form("nCsI==%d && flagCent",i);
  cut += " && ( (nhe3_1 && flag1 && a1_1<20) || (nhe3_2 && flag2 && a1_2<20) || (nhe3_3 && flag3 && a1_3<20) || (nhe3_4 && flag4 && a1_4<20) )";
  hdraw.Form("X_C:aCsI >> h2(4200,0,4200,300,20,100)");
  ch->Draw(hdraw.Data(),cut.Data(),"same");

  // cutL->SetLineColor(kRed);
  // cutL->Draw("same");

  // c3h->Update();


}
