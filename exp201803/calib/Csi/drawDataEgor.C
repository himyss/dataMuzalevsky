void fitH(TH1F *h, TF1 *g)
{
  Double_t rmax, rmin;

  Int_t i = h->GetMaximumBin();
  while(h->GetBinContent(i) > 0.5*h->GetMaximum()) {
    rmax = h->GetBinCenter(i+1);
    i++;
  }
  
  i = h->GetMaximumBin();
  while(h->GetBinContent(i) > 0.5*h->GetMaximum()) {
    rmin = h->GetBinLowEdge(i-1);
    i--;
  }

  //cout << "########" << endl << rmin << " "  << rmax << endl;
  g->SetParLimits(1,rmin,rmax);
  g->SetRange(rmin,rmax);
  h->Fit("g","R");
  //ofile << g->GetParameter(1) << endl; 
}

// main macro function
// ===================
void drawDataEgor()
{
  Int_t par1,par2,par3,par4;

  par3=1;

  TString inFilename("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out40_33.root");
  TString inTreeName("tree");
  TString outPdfDir("pdf");

  // Open the input file
  // ========================================================================
  TFile *f1 = new TFile(inFilename, "READ");
  if (f1->IsZombie()) {
    cerr << "Could not open file '" << inFilename << "'" << endl;
    return;
  } else {
    cerr << "Input file '" << inFilename << "' opened." << endl;
  }
  // ========================================================================

  // Get the input tree
  // ========================================================================
  TTree *t1 = (TTree*)f1->Get(inTreeName);
  if (t1 == NULL) {
    cerr << "Could not find tree '" << inTreeName << "' in file '" << inFilename << "'" << endl;
    return;
  } else {
    cerr << "Input tree '" << inTreeName << "' found." << endl;
  }
  ////t1->SetMakeClass(1);
  // ========================================================================

/*
  if (par1) {

    cerr << "Processing 'par1' part." << endl;

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

  } // end of 'par1' part

  if (par2) {

    cerr << "Processing 'par2' part." << endl;

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

  } // end of 'par2' part*/

  if (par3) {

    cerr << "Processing 'par3' part." << endl;

    TH1I *hmulX = new TH1I("hmulX","x multiplicity",4,1,5);
    TH1I *hmulY = new TH1I("hmulY","y multiplicity",4,1,5);

    TH2F *h1;
    TH2F *h2;     
   

    TFile *f1 = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/out40_33.root");
    TTree *t1 = (TTree*)f1->Get("tree");
    TCanvas *c2 = new TCanvas("c2","Si amp^times",1800,1000);
    c2->Divide(2,2);
    c2->cd(1);
    gPad->SetLogz();
    //t1->Draw("SQY_L[4]:tSQY_L[4]>>htemp1(400,1000,1400,100,0,90)","tSQY_L[4]>0 && SQY_L[4]>0","box",5000000,0);
    t1->Draw("SQX_L[8]:tSQX_L[8]>>htemp1(400,200,600,100,0,90)","tSQX_L[8]>0 && SQX_L[8]>0 && trigger==1","box",29000000,0);
    h1 = (TH2F*)gPad->GetPrimitive("htemp1");
    //cout << h1 << endl;
    //c2->cd(3);
    h1->Draw();    


    c2->cd(2);
    gPad->SetLogz();
    //c2_2->SetLogz();
    //t1->Draw("SQY_L[4]:tSQY_L[4]>>htemp2(400,1000,1400,100,0,90)","tSQY_L[4]>0 && SQY_L[4]>0 && multY_L>1","box",5000000,0);
    t1->Draw("SQX_L[28]:tSQX_L[28]>>htemp2(400,200,600,100,0,90)","tSQX_L[28]>0 && SQX_L[28]>0 && trigger==1","box",29000000,0);
    h2 = (TH2F*)gPad->GetPrimitive("htemp2");
    h2->Draw();   

    //h2->Draw();
    c2->cd(3);
    gPad->SetLogz();
    //t1->Draw("SQY_L[]:tSQY_L[]>>htemp3(400,1000,1400,100,0,90)","tSQY_L[]>0 && SQY_L[]>0","col",5000000,0);
    t1->Draw("SQX_L[]:tSQX_L[]>>htemp3(400,200,600,100,0,90)","tSQX_L[]>0 && SQX_L[]>0 && trigger==1","col",29000000,0);
    //t1->Draw("SQY_L[12]:tSQY_L[12]","multY_L==2","",4000000,0);

    c2->cd(4);
    gPad->SetLogz();
    //t1->Draw("SQY_L[]:tSQY_L[]>>htemp4(400,1000,1400,100,0,90)","multY_L==1 && tSQY_L[]>0 && SQY_L[]>0","col",5000000,0);
    t1->Draw("SQX_L[]:tSQX_L[]>>htemp4(400,200,600,100,0,90)","multX_L==1 && tSQX_L[]>0 && SQX_L[]>0 && trigger==1","col",29000000,0);
    
  } // end of 'par3' part


/*
  if (par4) {

    cerr << "Processing 'par4' part." << endl;

    // Open output text file
    // ========================================================================
   // TString outTxtFilename("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/positionstest.txt");
    TString outTxtFilename("tParY_L.clb");
    ofstream outcalfile;
    outcalfile.open(outTxtFilename.Data());
    if (!outcalfile.is_open()) {
      cerr << "Could not open output text file'" << outTxtFilename << "'" << endl;
      return;
    } else {
      cerr << "Opened output text file '" << outTxtFilename << "'" << endl;
    }

	    
    // ========================================================================

    //TH1::AddDirectory(kFALSE);

    // Create a Gaussian function
    TF1* g = new TF1("g", "gaus", 1000., 1200.);
    //g->SetParLimits(0, 1., 1e+7);
    g->SetParLimits(1, 1000., 1200.);
    g->SetParLimits(2, 1., 50.);
  
    Int_t nhists = 32;
    Int_t ncanvases = nhists/4;
    Double_t shift,zeroLevel;

    TH1F *hX[32];
    TH1F *hY[16];
    TH2F *h2D[32];  

    TH1F* h = new TH1F("h","temp hist", 140,1020.,1160.);
    TH2F *h2 = new TH2F("h2","temp 2d hist",140,1020.,1160.,400,0.,90.);

    TString hname,h2name;
    //for(Int_t i=0;i<nhists;i++) {
    //  TString hname;
   //   hname.Form("h%d",i+1);
    //  hX[i] = new TH1F(hname.Data(),"title",1200,0,1200);
   // }

    outcalfile << 2 << endl << nhists<< endl;

    // Create canvases
    // ========================================================================
    TCanvas* c[8]; // works only if ncanvases==8
    for(Int_t i=0; i<8; i++) {
      TString cName;
      cName.Form("c_%d",i);
      c[i] = new TCanvas(cName.Data(),"calibrated spectra",1000,1000);
      c[i]->Divide(2,2);
    }

    TCanvas* c2[8]; // works only if ncanvases==8
    for(Int_t i=0; i<8; i++) {
      TString cName;
      cName.Form("c2_%d",i);
      c2[i] = new TCanvas(cName.Data(),"2-dim calibrated spectra",1000,1000);
      c2[i]->Divide(2,2);
    }
    cerr << "Canvases created." << endl;
    // ========================================================================

    for (Int_t i=0;i<nhists;i++)
    {

      cerr << "i=" << i << endl;


      hname.Form("h%d",i);

      TString cut;
      cut.Form("SQX_L[%d]>14",i);
      //cut.Form("tSQX_L[%d]>1000 && tSQX_L[%d]<1600",i,i,i);

      TString vary1;
      //vary1.Form("tSQX_L[%d]>>(200,1000,1200)",i);
      vary1.Form("tSQX_L[%d]>>h%d(800,1000,1800)",i,i);

      Int_t count = i/4;
      Int_t nPad = (i%4)+1;

      c[count]->cd(nPad);
      t1->Draw(vary1.Data(),cut.Data(),"",100000,0);

      hX[i] = (TH1F*)gPad->GetPrimitive(hname.Data());
      hX[i]->SetTitle(hname.Data());
      fitH(hX[i],g);
      if(i==0) {
        zeroLevel = g->GetParameter(1);
        shift = 0;
      } 
      shift = zeroLevel - g->GetParameter(1);
	    outcalfile
	    << setprecision(4) << shift*0.3 << "\t"
	    << setprecision(4) << "0.3" << "\t\t" //E=a+bN
	    << "0" << endl;

    
      c[count]->Update();

      c2[count]->cd(nPad);      

      h2name.Form("h2_%d",i);
      TString cut1;      
      cut1.Form("tSQX_L[%d]>900 && tSQX_L[%d]<1600",i,i);

      TString vary;
      vary.Form("SQX_L[%d]:tSQX_L[%d]>>h2_%d(800,1000.,1800.,100,0.,90)",i,i,i);
      //gPad->SetLogz();
      t1->Draw(vary.Data(),"","",5000000,0);

     
      h2D[i] = (TH2F*)gPad->GetPrimitive(h2name.Data());
      TString title;
      title.Form("2-dim %d",i);
      h2D[i]->SetTitle(title.Data());
      //h2D[i]->Draw();

      c2[count]->Update();

    }

    // Export canvases into output PDF files
    // ========================================================================
    for (Int_t iCanv=0; iCanv<ncanvases; iCanv++) {
      TString outFilename;
      outFilename.Form("%s/canv_%d.pdf", outPdfDir.Data(), iCanv);
      c[iCanv]->SaveAs(outFilename);
      outFilename.Form("%s/canv2_%d.pdf", outPdfDir.Data(), iCanv);
      c2[iCanv]->SaveAs(outFilename);
    }
    cerr << "Exported canvases into output PDF files." << endl;
    // ========================================================================


  } // end of 'par4' part*/

}
