void fitH(TH1F *h, TF1 *g) {
  Double_t rmax, rmin;

  Int_t i=h->GetMaximumBin();
  while(h->GetBinContent(i) > 0.5*h->GetMaximum()) {
    rmax = h->GetBinCenter(i+1);
    i++;
  }
  
  i=h->GetMaximumBin();
  while(h->GetBinContent(i) > 0.5*h->GetMaximum()) {
    rmin = h->GetBinLowEdge(i-1);
    i--;
  }
  //cout << "########" << endl << rmin << " "  << rmax << endl;
  g->SetParLimits(1,rmin,rmax);
	g->SetRange(rmin,rmax);
  h->Fit("g","R");
  //ofile << g->GetParameter(1) << endl; 
  return;
}

void drawData(){


  Int_t par1,par2,par3,par4;
  TString canname;
  par4=1;

  TFile *f1 = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out70.root");
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

  if(par3) {

    TFile *f1 = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out.root");
    TTree *t1 = (TTree*)f1->Get("tree");
    TCanvas *c2 = new TCanvas("c2","Si amp^times",1800,1000);
    c2->Divide(2,1);
    c2->cd(1);
    t1->Draw("SQX_L[12]:tSQX_L[12]","","",4000000,0);
    
    c2->cd(2);
    //c2_2->SetLogz();
    t1->Draw("SQX_L[]:tSQX_L[]>>(500,500,2500,100,0,90)","","col",5000000,0);

  }
*/

  if(par4) {
    Int_t nhists = 16,nPad,count;
    TH1F *hX[nhists],*hY[16],*h;
    TString hname,cName,cut,vary,vary1,vary2;
    TH2F *h2D[16];  

	  ofstream outcalfile;
	  outcalfile.open("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/positionstest.txt");
	  if (!outcalfile.is_open()) {
		  cout <<"Output file was not opened" << endl;
		  return;
	  }

    TF1* g = new TF1("g", "gaus", 900, 1600);
    //g->SetParLimits(0,1.,1e+5);
    g->SetParLimits(1,1000,1600);
    g->SetParLimits(2,1.,50.);
  
    h = new TH1F("h","temp hist",750,900,750);
    TH2F *h2 = new TH2F("h2","temp 2d hist",200,0,90,750,900,1750);

    /*for(Int_t i=0;i<nhists;i++) {
      hname.Form("h%d",i+1);
      hX[i] = new TH1F(hname.Data(),"title",1200,0,1200);
    }*/ 
    Int_t ncanvases = nhists/4; 
    TCanvas *c[ncanvases];
    for(Int_t i=0;i<ncanvases;i++){
      cName.Form("c%d",i);
      c[i] = new TCanvas(cName.Data(),"calibrated spectra",1000,1000);
      c[i]->Divide(2,2);
    }

    TCanvas *c2[ncanvases];
    for(Int_t i=0;i<ncanvases;i++){
      cName.Form("c2%d",i+1);
      c2[i] = new TCanvas(cName.Data()," 2-dim calibrated spectra",1000,1000);
      c2[i]->Divide(2,2);
    }

    for(Int_t i=0;i<nhists;i++) {
      hname.Form("h%d",i);
      cut.Form("SQY_L[%d]>14 && tSQY_L[%d]>900 && tSQY_L[%d]<1600",i,i,i);
      //cut.Form("tSQX_L[%d]>1000 && tSQX_L[%d]<1600",i,i,i);
      //vary1.Form("tSQX_L[%d]>>(200,1000,1200)",i);
      vary1.Form("tSQY_L[%d]>>h",i);

      count = i/4;
      nPad = (i%4)+1;
      c[count]->cd(nPad);
      t1->Draw(vary1.Data(),cut.Data(),"",500000,0);

      hX[i] = (TH1F*)gPad->GetPrimitive("h");
      hX[i]->SetTitle(hname.Data());
      fitH(hX[i],g);
     
      c[count]->Update();

      c2[count]->cd(nPad);      
      
      vary.Form("SQY_L[%d]:tSQY_L[%d]>>h2",i,i);
      t1->Draw(vary.Data(),"","",500000,0);
      c2[count]->Update();
      //h2D[i] = (TH2F*)gPad->GetPrimitive("h2");
      //h2D[i]->Draw();

    }
    /*TCanvas *test = new TCanvas("test","title",1000,1000);
    test->cd();
    hX[0]->Draw();*/
      //t1->Draw("SQX_L[10]:tSQX_L[10]","","",1000000);

	/* c[0]->Print("output.pdf");
	  c[0]->Print("output.pdf[");
    for(Int_t j=1;j<ncanvases;j++) {
      c[j]->Print("output.pdf");
    }
    for(Int_t j=0;j<ncanvases-1;j++) {
      c2[j]->Print("output.pdf");
    }
	  c2[ncanvases-1]->Print("output.pdf]");

	  c[0]->Print("output1.pdf");
	  c[0]->Print("output1.pdf[");
    for(Int_t j=1;j<ncanvases-1;j++) {
      c[j]->Print("output1.pdf");
    }
	  c[ncanvases-1]->Print("output1.pdf]");*/


  }
}
