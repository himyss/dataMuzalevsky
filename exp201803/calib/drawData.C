{

 /* TFile *f = new TFile("cal_CsI.root");
  TTree *t = (TTree*)f->Get("tree");

  TCanvas *c1 = new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  tree->Draw("F5+F3:tF5-tF3","F5>0","col");
*/

  TFile *f = new TFile("/media/analysis_nas/exp201803/rootfiles/csi00_0001.root");
  TTree *t = (TTree*)f->Get("AnalysisxTree");
  TCanvas *c2 = new TCanvas();
  c2->Divide(2,2);
  c1_1->SetLogz();
  c2->cd(1);
  TH2F *h1 = new TH2F("h1","TOF",500,100.,1000.,500,0.,7000.);
  t->Draw("NeEvent.F5[0]+NeEvent.F3[0] : NeEvent.tF5[0]-NeEvent.tF3[0] >> h1","","col");

  c2->cd(2);
  TH2F *h2 = new TH2F("h2","TOF cut",100,600.,750.,100,300.,800.);
  c1_2->SetLogz();
  t->Draw("NeEvent.F5[0]+NeEvent.F3[0]:NeEvent.tF5[0]-NeEvent.tF3[0] >> h2","","col");

  c2->cd(3);
  t->Draw("NeEvent.SQX_R[0]","NeEvent.SQX_R[0]>0 && NeEvent.SQX_R[0]<2000","");

  c2->cd(4);
  t->Draw("NeEvent.SQX_R[]","NeEvent.tF5[]-NeEvent.tF3[] > 600 && NeEvent.tF5[]-NeEvent.tF3[] < 750 && NeEvent.F5[]+NeEvent.F3[]>300 && NeEvent.F5[]+NeEvent.F3[]<800 && NeEvent.SQX_R[]>0","");
  
  TCanvas *c1 = new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  t->Draw("NeEvent.SQX_R[]:NeEvent.CsI_R[]","","");
  c1->cd(2);
  t->Draw("NeEvent.SQX_R[0]:NeEvent.CsI_R[0]","","");
  c1->cd(3);
  t->Draw("NeEvent.SQX_R[0]","NeEvent.SQX_R[0]>0 && NeEvent.SQX_R[0]<2000","");
  c1->cd(4);
  t->Draw("NeEvent.SQX_R[0]:NeEvent.CsI_R[0]","NeEvent.SQX_R[0]>200 && NeEvent.CsI_R[0]>100","");

}
