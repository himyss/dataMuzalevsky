
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

  Int_t i = 12;

  ch->SetMarkerStyle(7);
  ch->SetMarkerColor(kBlack);      
  cut.Form("n20_3==%d && flag3",i);
  hdraw.Form("a20_3:a1_3>>h%d3(100,1,30,100,0.5,5)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"");
  // c_arr[i]->Update();
  c3h->Update();

  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.7);
  ch->SetMarkerColor(kBlue);      
  // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
  cut += " && nh3";
  hdraw.Form("a20_3:a1_3>>h%d3_he(100,1,30,100,0.5,5)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");
  c3h->Update();


  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.7);
  ch->SetMarkerColor(kRed);      
  // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
  cut += " && nhe3_3";
  hdraw.Form("a20_3:a1_3>>h%d3_coin(100,1,30,100,0.5,5)",i);
  // hdraw.Form("X_C.:aCsI>>h%d",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");

  c3h->Update();


}
