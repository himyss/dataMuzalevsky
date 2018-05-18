{


  Int_t par1,par2,par3,par4;
  par4=1;

  TFile *f1 = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out.root");
  TTree *t1 = (TTree*)f1->Get("tree");
  

 /* if(par1) {

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

  if(par2) {

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
  }
*/
  if(par3) {

    TFile *f1 = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out.root");
    TTree *t1 = (TTree*)f1->Get("tree");
    TCanvas *c2 = new TCanvas("c2","Si amp^times",1800,1000);
    c2->Divide(2,2);
    c2->cd(1);
    t1->Draw("tSQX_L[10]","","",100000,0);

    c2->cd(2);
    t1->Draw("SQX_L[11]:tSQX_L[11]","","",100000);

    c2->cd(3);
    t1->Draw("SQX_L[12]:tSQX_L[12]","","",100000,0);

    c2->cd(4);
    t1->Draw("SQX_L[]:tSQX_L[]","","",100000,0);

  }


  if(par4) {
    Int_t nhists = 4,nPad,count;
    TH1F *hX[nhists],*hY[16],*h;
    TString hname,cName,cut,vary,vary1,vary2;

    TF1* g = new TF1("g", "gaus", 1000, 1200);
    g->SetParLimits(0,1.,150.);
    g->SetParLimits(1,1000,1200);
    g->SetParLimits(2,1.,50.);
  
    h = new TH1F("h","temp hist",100,1000,1200);

    for(Int_t i=0;i<nhists;i++) {
      hname.Form("h%d",i+1);
      hX[i] = new TH1F(hname.Data(),"title",100,1000,1200);
    }  
    Int_t ncanvases = nhists/4; 
    TCanvas *c[ncanvases];
    for(Int_t i=0;i<ncanvases;i++){
      cName.Form("c%d",i+1);
      c[i] = new TCanvas(cName.Data(),"calibrated spectra",1000,1000);
      c[i]->Divide(2,2);
    }

    for(Int_t i=0;i<nhists;i++) {
    
      cut.Form("SQX_L[%d]>14 && tSQX_L[%d]>1000 && tSQX_L[%d]<1200",i,i,i);
      //vary1.Form("tSQX_L[%d]>>(200,1000,1200)",i);
      vary1.Form("tSQX_L[%d]>>h",i);
      //vary1.Form("tSQX_L[%d]",i);
      count = i/4;
      nPad = (i%4)+1;
      c[count]->cd(nPad);
      t1->Draw(vary1.Data(),cut.Data(),"",100000,0);

      hX[i] = (TH1F*)gPad->GetPrimitive("h");
      hX[i]->Fit("g","R");
      
      c[count]->Update();


    }
    /*TCanvas *test = new TCanvas("test","title",1000,1000);
    test->cd();
    hX[0]->Draw();*/
      //t1->Draw("SQX_L[10]:tSQX_L[10]","","",1000000);


  }
}
