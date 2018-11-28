void beamTest() {

  TString fileName("/media/user/work/data/exp201810/calib/testToF_0001.root");
  TFile *f = new TFile(fileName.Data());
  if(!f) {
    cout << "File " << fileName.Data() << " does not exist." << endl;
    return;
  }

  TString treeName("AnalysisxTree");
  TTree *t = (TTree*)f->Get(treeName.Data());
  if(!t) {
    cout << "Tree " << treeName.Data() << " does not exist." << endl;
    return;
  }

//--------------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1","F5",1800,1000);
  c1->Divide(2,2);

  c1->cd(1);
  t->Draw("F5[0]:tF5[0]*0.125>>hF5_0(50,427,433,1800,0,1800)","","col");

  c1->cd(2);
  t->Draw("F5[1]:tF5[1]*0.125>>hF5_1(50,427,433,1800,0,1800)","","col");

  c1->cd(3);
  t->Draw("F5[2]:tF5[2]*0.125>>hF5_2(50,427,433,1800,0,1800)","","col");

  c1->cd(4);
  t->Draw("F5[3]:tF5[3]*0.125>>hF5_3(50,427,433,1800,0,1800)","","col");

  TCanvas *c2 = new TCanvas("c2","F3",1800,1000);
  c2->Divide(2,2);

  c2->GetPad(1)->SetLogz();
  c2->cd(1);
  t->Draw("F3[0]:tF3[0]*0.125>>F3_0(100,300,380,2000,0,2000)","tF3[0]*0.125>310 && tF3[0]*0.125<370","col");

  c2->GetPad(2)->SetLogz();
  c2->cd(2);
  t->Draw("F3[1]:tF3[1]*0.125>>F3_1(100,300,380,2000,0,2000)","tF3[1]*0.125>310 && tF3[1]*0.125<370","col");

  c2->GetPad(3)->SetLogz();
  c2->cd(3);
  t->Draw("F3[2]:tF3[2]*0.125>>F3_2(100,300,380,2000,0,2000)","tF3[2]*0.125>310 && tF3[2]*0.125<370","col");

  c2->GetPad(4)->SetLogz();
  c2->cd(4);
  t->Draw("F3[2]:tF3[3]*0.125>>F3_3(100,300,380,2000,0,2000)","tF3[3]*0.125>310 && tF3[3]*0.125<370","col");

  TCanvas *c3 = new TCanvas("c3","tF3",1800,1000);
  c3->Divide(2,2);

  c3->cd(1);
  t->Draw("tF3[0]*0.125>>tF3_0(100,300,400)","","");

  c3->cd(2);
  t->Draw("tF3[1]*0.125>>tF3_1(100,300,400)","","");

  c3->cd(3);
  t->Draw("tF3[2]*0.125>>tF3_2(100,300,400)","","");

  c3->cd(4);
  t->Draw("tF3[3]*0.125>>tF3_3(300,0,300)","","");


}