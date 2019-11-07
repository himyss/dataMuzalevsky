
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

  Int_t i = 15;

  ch->SetMarkerStyle(7);
  ch->SetMarkerColor(kBlack);      
  cut.Form("n20_2==%d && flag2",i);
  hdraw.Form("a20_2:a1_2>>h%d2(100,1,30,100,0.5,5)",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");

  ch->SetMarkerStyle(20);

  ch->SetMarkerColor(kBlue);      
  cut += " && nh3";
  hdraw.Form("a20_2:a1_2>>h%d2_he(100,1,30,100,0.5,5)",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");

  ch->SetMarkerStyle(20);
  ch->SetMarkerColor(kRed);      
  cut += " && nhe3_2";
  hdraw.Form("a20_2:a1_2>>h%d2_coin(100,1,30,100,0.5,5)",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");

  c3h->Update();


}
