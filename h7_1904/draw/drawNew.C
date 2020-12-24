#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void drawNew(){
  create_IDs();
  create_cuts();

  // gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH1F *htemp2;
  TH1F *htemp;
  TH2F *htemp2D;

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1904/analysed/reco/h7/h7_ct_*.root");
  cout << ch1->GetEntries () << " csiAnalyse" << endl;
  ch1->SetMarkerStyle(20);


  TChain *chOld = new TChain("tree"); //e4
  chOld->Add("/media/ivan/data/exp1904/analysed/reco/h7_nov2020/h7_ct_*.root");
  cout << chOld->GetEntries () << " csiAnalyse" << endl;
  chOld->SetMarkerStyle(20);

  TF1 *fa = new TF1("fa","x*1/2",0,35);
  fa->SetLineColor(kRed);

  TF1 *fa1 = new TF1("fa1","x*4/7",0,25);
  fa1->SetLineColor(kRed);

  TF1 *fa2 = new TF1("fa2","x*3/7",0,40);
  fa2->SetLineColor(kRed);

  TF1 *f6 = new TF1("f6","x*6",-5,20);
  f6->SetLineColor(kRed);

  TF1 *f36 = new TF1("f36","x*5/6",0,35);
  f36->SetLineColor(kRed);  

  Bool_t             mm_7h = 1;

  TString cut, triangleCut, hdraw;

  if (mm_7h) {
    TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
    c_mm->Divide(2,2);

    c_mm->cd(1);

    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("1000*(lv_h7.Mag()-4*0.939565-2.808920) >> h_mm(67,0,20)",cut.Data(),"") << endl;
    c_mm->Update();

    c_mm->cd(2);

    ch1->SetMarkerColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("1000*(lv_h3_CMH7.T()-lv_h3_CMH7.Mag()):1000*(lv_h7.Mag()-4*0.939565-2.808920)",cut.Data(),"") << endl;
    fa1->Draw("same");
    c_mm->Update();

    c_mm->cd(3);

    ch1->SetLineColor(kBlack);
    cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
    cout << ch1->Draw("lv_h7_CMR.Theta()*TMath::RadToDeg():1000*(lv_h7.Mag()-4*0.939565-2.808920)",cut.Data(),"") << endl;
    c_mm->Update();

    


  }



}