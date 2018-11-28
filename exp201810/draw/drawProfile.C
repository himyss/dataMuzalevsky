void drawProfile(){
    
  gStyle->SetOptStat(0);

  TString fileName("/media/user/work/data/exp201810/workdir/thinDet/profile.root");
  TFile *f = new TFile(fileName.Data());
  if(!f) {
    cout << "File " << fileName.Data() << " does not exist." << endl;
    return;
  }

  TString hName("hDc");
  TH2I *hDc = (TH2I*)f->Get(hName.Data());
  if(!hDc) {
    cout << "Histo " << hName.Data() << " does not exist." << endl;
    return;
  }

//--------------------------------------------------------------------------------
  hDc->Draw("COL");
  // TBox *b = new TBox(3.75 - 30, 3.75 - 30, 3.75*15-30, 3.75*14-30);
  // b->SetLineWidth(3);
  // b->SetLineColor(1);
  TLine *f1 = new TLine(3.75 - 30,3.75 - 30,3.75*15-30,3.75 - 30);
  f1->SetLineColor(kRed);
  f1->SetLineWidth(4);

  TLine *f2 = new TLine(3.75*15-30,3.75 - 30,3.75*15-30,3.75*14-30);
  f2->SetLineColor(kRed);
  f2->SetLineWidth(4);

  TLine *f3 = new TLine(3.75*15-30,3.75*14-30,3.75 - 30,3.75*14-30);
  f3->SetLineColor(kRed);
  f3->SetLineWidth(4);

  TLine *f4 = new TLine(3.75 - 30,3.75*14-30,3.75 - 30,3.75 - 30);
  f4->SetLineColor(kRed);
  f4->SetLineWidth(4);



  TLine *f5 = new TLine(3.75 - 30,3.75 - 30,3.75*15-30,3.75*14-30);
  f5->SetLineColor(kRed);
  f5->SetLineWidth(2);

  TLine *f6 = new TLine(3.75*15-30,3.75 - 30,3.75 - 30,3.75*14-30);
  f6->SetLineColor(kRed);
  f6->SetLineWidth(2);

  // b->SetFillColorAlpha(1, 1);
  // b->SetFillColor(color);
  f1->Draw("same");
  f2->Draw("same");
  f3->Draw("same");  
  f4->Draw("same");

  f5->Draw("same");  
  f6->Draw("same");

 }