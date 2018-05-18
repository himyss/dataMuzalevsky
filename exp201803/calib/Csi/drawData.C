{


  Int_t par1,par2,par3;
  par3=1;

  if(par1) {

    TFile *f = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out.root");
    TTree *t = (TTree*)f->Get("tree");
    TCanvas *c1 = new TCanvas();
    c1->Divide(2,2);
    c1->cd(1);
    c1_1->SetLogz();
//    t->Draw("F5[0]+F3[0] : tF5[0]-tF3[0] >> (500,100,700,500,100,4000)","","col");
    t->Draw("F5[]+F3[] : tF5[]-tF3[] >> (500,100,700,500,100,4000)","","col");

    c1->cd(2);
    c1_2->SetLogz();
    t->Draw("SQX_R : CsI_R","SQX_R>1.15 && CsI_R>0","col"); 

    c1->cd(3);
    //c1_3->SetLogz();
//    t->Draw("F5[0]+F3[0] : tF5[0]-tF3[0]","(F5[0]+F3[0])>300 && (F5[0]+F3[0])<700 && (tF5[0]-tF3[0])>540 && (tF5[0]-tF3[0])<640","col"); 
    t->Draw("F5[]+F3[] : tF5[]-tF3[]","(F5[]+F3[])>300 && (F5[]+F3[])<700 && (tF5[]-tF3[])>540 && (tF5[]-tF3[])<640",""); 

    //c1->cd(4);
    //t->Draw("SQX_R:CsI_R","SQX_R>1.15 && CsI_R>0 && (F5[]+F3[])>300 && (F5[]+F3[])<700 && (tF5[]-tF3[])>540 && (tF5[]-tF3[])<640",""); 
  }

  /*if(par2) {

    TCanvas *c2 = new TCanvas();
    c2->Divide(2,2);
    c1_1->SetLogz();
    c2->cd(1);
    TH2F *h1 = new TH2F("h1","TOF",500,100.,1000.,500,0.,7000.);
    t->Draw("NeEvent.F5[0]+NeEvent.F3[0] : NeEvent.tF5[0]-NeEvent.tF3[0] >> h1","","col");
    c2->Update();

    c2->cd(2);
    TH2F *h2 = new TH2F("h2","TOF cut",100,600.,750.,100,300.,800.);
    c1_2->SetLogz();
    t->Draw("NeEvent.F5[0]+NeEvent.F3[0]:NeEvent.tF5[0]-NeEvent.tF3[0] >> h2","","col");
    c2->Update();

    c2->cd(3);
    t->Draw("NeEvent.SQX_R[0]","NeEvent.SQX_R[0]>0 && NeEvent.SQX_R[0]<2000","");
    c2->Update();

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
  }*/

  if(par3) {

    TFile *f1 = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out.root");
    TTree *t1 = (TTree*)f1->Get("AnalysisxTree");
    TCanvas *c2 = new TCanvas("c2","Si amp^times",1800,1000);
    c2->Divide(2,2);
    c2->cd(1);
    t1->Draw("NeEvent.tSQX_L[10]","NeEvent.SQX_L[10]>600","");

    c2->cd(2);
    t1->Draw("NeEvent.SQX_L[11]:NeEvent.tSQX_L[11]","","");

    c2->cd(3);
    t1->Draw("NeEvent.SQX_L[12]:NeEvent.tSQX_L[12]","","");

    c2->cd(4);
    t1->Draw("NeEvent.SQX_L[]:NeEvent.tSQX_L[]","","");
    

  }
}
