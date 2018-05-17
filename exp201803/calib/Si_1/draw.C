void draw() {

	TFile *f = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/outCal.root");
	TTree *t = (TTree*)f->Get("tree");

  TCanvas *c = new TCanvas("c","correlations",1800,1000);
  
  TF1 *fun = new TF1("fun","x",0,10);
 // TF1 *fun1 = new TF1("fun1","0.95*x",0,10);
  //TF1 *fun2 = new TF1("fun2","0.15*x",0,10); 

  c->Divide(2,1);
  c->cd(1); 
  //t->Draw("clasterX:SQY_L","SQY_L[]>1",""); 
  t->Draw("SQX_L[10] + SQX_L[11] + SQX_L[9]:SQY_L[]","SQX_L[10]>1 && SQY_L[]>1 && SQX_L[9]<1 && SQX_L[11]<1","");
  fun->Draw("same");
  c->Update();  
  c->cd(2);
  t->Draw("SQX_L[10]:SQY_L[]","SQX_L[10]>1 && SQY_L[]>1",""); 
  fun->Draw("same");

  /*TCanvas *c1 = new TCanvas("c1","specs",1800,1000);
  c1->Divide(8,4);
  TString hname;
  for(Int_t i=0;i<32;i++) {
    hname.Form("SQX_L[%d]",i);
    c1->cd(i+1);
    t->Draw(hname.Data(),"SQX_L[10]>1 && SQX_L[10]>0.15*summY && SQX_L[10]<0.95*summY","");
    c1->Update();
  }*/
}
