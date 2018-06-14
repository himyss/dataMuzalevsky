{

  TFile *f = new TFile("count.root");
  TH2F *nSQmm = (TH2F*)f->Get("nSQmm");
  nSQmm->Draw("ColZ1");

  TBox *box = new TBox(3.1, -0.75, 53.1, 49.25);
  box->SetLineWidth(3);
  box->SetLineColor(2);
  box->SetFillStyle(0);
  box->Draw("same");
}
