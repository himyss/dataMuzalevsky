Double_t calcVectorTel1(Int_t n20, Int_t n1);
Double_t calcVectorTel2(Int_t n20, Int_t n1);
Double_t calcVectorTel3(Int_t n20, Int_t n1);
Double_t calcVectorTel4(Int_t n20, Int_t n1);

Double_t theta[16][16]; // angles (stripnum in 20, strip num in 1-mm)

void calcThickness(){

  TELoss fAlphaSi;
  fAlphaSi.SetEL(1, 2.321); // density in g/cm3
  fAlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//  mSi.SetZP(1., 1.);    //protons
  fAlphaSi.SetZP(2., 4.);   //alphas, Z, A
  fAlphaSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
  fAlphaSi.SetDeltaEtab(300);
  
  for(Int_t i=0;i<16;i++) {
    for(Int_t j=0;j<16;j++) {
      theta[i][j] = calcVectorTel1(i,j);
    }
  }

  
  TString hDraw,hname,hcut;

  TH1F *h0,*h1,*h2,*h[300];


  TChain *ch0 = new TChain("tree");
  ch0->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");  
  if (!ch0) {
    cout << "/home/oem/work/data/exp1904/clb/20um_1mm*" << endl;
  }  

// //
  TH1* hSpectrum;

  Int_t peaksNumber,nopeaks,flag;
  Double_t peak[peaksNumber];
  Double_t *peakPosition;
  Double_t *peakHight;
  Double_t *peakPositionS;//sorted peaks
  Double_t *peakHightS;

  Double_t minPos,minH,numPoints,nPoints;

  TList *functions;
  TPolyMarker *pm;
  TSpectrum sc; //by default for 100 peaks

  Double_t fitMin, fitMax, fitStep;
  TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);
  
  Double_t upFitBorder,lowFitBorder,E[2],E0[2],nCh[2],th[2],thAv;
  upFitBorder = 0.3; lowFitBorder = 0.3;

  // initial alpha energies [MeV] 
  E0[0] = 7.6869;
  E0[1] = 6.0024;

  Int_t m;
  TVector3 dir,source(0,0,0);

  TH2F *hTh = new TH2F("hTh","thickness distr",16,0,16,16,0,16);
  for(Int_t i =0;i<16;i++) {
    for(Int_t j=0;j<16;j++) {
      hTh->SetBinContent(i,j,0);
    }
  }  


  TCanvas *c[16];
  TString cName,cTitle;
  Int_t nPad,nCan;
  for(Int_t i=0;i<16;i++) {
    cName.Form("c%d",i);
    cTitle.Form("eDepostis in %d strip",i); 
    c[i] = new TCanvas(cName.Data(),cTitle.Data(),1800,1000);
    c[i]->Divide(4,4);
  }
  c[0]->cd(1);
  ch0->Draw("a1>>edepN(300,1,9)","n1==7 && n20_1==7","");
  h[0] = (TH1F*)gPad->GetPrimitive("edepN");
  numPoints = h[0]->GetEntries();
  cout << numPoints <<  "  npoints in GOOD spectra" << endl;
// }


  for(Int_t i=0;i<16;i++) { // strips in SQ20 (0-15) SQX_L (0-31)
    for(Int_t nStr = 0;nStr<16;nStr++) { // strips in SQY_L (0-15)
      cout << endl << "#########" << endl << "SQ20 " << i << " SQY_L " << nStr << endl;
      //nCan = i/16;
      //nPad = i - nCan*16 + 1;
      c[i]->cd(nStr+1);
      //c[0]->cd(nStr+1);

      // обнуление
      fitMin = 0;
      fitMax = 0;
      peakPosition = NULL;
      peakHight = NULL;
      peakPositionS = NULL;
      peakHightS = NULL;
      nPoints = 0;
      flag = 0;
      
      // заполнение гистограмм через tree->Draw()
      hDraw.Form("a1>>edep%d_%d(130,0.7,7)",i,nStr);
      //cout << hDraw.Data() << " asd asdasdasd " << parYL2[15] << endl;return; 
      hname.Form("edep%d_%d",i,nStr);
      hcut.Form("n1==%d && n20_1==%d ",nStr,i);
      ch0->Draw(hDraw.Data(),hcut.Data(),"");
      h[i] = (TH1F*)gPad->GetPrimitive(hname.Data());
      nPoints  = h[i]->GetEntries();
      cout << nPoints << " nentries!!! and relation " << nPoints/numPoints << endl;
      if(nPoints/numPoints < 0.05) flag = 1;
      if(flag == 0) {
        hSpectrum = h[i];
        if (!hSpectrum) {
          cout<< "raw spec was not found " << endl;
          return 1;
        }    
        
        // подсчёт количества пиков
        nopeaks = sc.Search(hSpectrum, 8, "goff", 0.3);
        if (nopeaks<1) {
          cout << " less than 1 peak were found " << endl;
          hTh->SetBinContent(i+1, nStr+1, 50);
          continue;
        }
        cout << "nopeaks " <<  nopeaks << endl;

        //functions = hSpectrum->GetListOfFunctions();
        //pm = (TPolyMarker*)functions->FindObject("TPolyMarker");

        pm = new TPolyMarker(nopeaks, sc.GetPositionX(), sc.GetPositionY());
        hSpectrum->GetListOfFunctions()->Add(pm);
        pm->SetMarkerStyle(23);
        pm->SetMarkerColor(kRed);
        pm->SetMarkerSize(1.3);
        
        peakPosition = pm->GetX();
        peakHight = pm->GetY();

        peakPositionS = new Double_t [pm->GetN()];
        peakHightS = new Double_t [pm->GetN()];

        for(Int_t a=0;a<pm->GetN();a++) {
          peakPositionS[a] = peakPosition[a];
          peakHightS[a] = peakHight[a];
        }

        //peakPositionS = pm->GetX();
        //peakHightS = pm->GetY();

        //cout << "positions and heights " << endl;
        //for(Int_t a=0;a<pm->GetN();a++) {
        //  cout << peakPosition[a] << " " << peakHight[a] << endl;
        //}

        for (Int_t b = 0; b < pm->GetN(); ++b){ 
          for (Int_t a = 0; a < pm->GetN()-1; ++a){ 
            if(peakPositionS[a] < peakPositionS[a+1]) { 
                minPos = peakPositionS[a]; 
                minH = peakHightS[a]; 

                peakPositionS[a] = peakPositionS[a+1]; 
                peakHightS[a] = peakHightS[a+1];

                peakPositionS[a+1] = minPos; 
                peakHightS[a+1] = minH;
            }
          } 
        }  

        cout << "sorted positions and heights " << endl;
        for(Int_t a=0;a<pm->GetN();a++) {
         cout << peakPositionS[a] << " " << peakHightS[a] << endl;
        }

        fitStep = hSpectrum->GetXaxis()->GetBinWidth(0);

        //фитирование гауссом
       // cout << "thickness!!" << endl; 
        // for(Int_t k = 0; k < 1; k++) {
        //   //cout << peakPosition[k] << " " << peakHight[k] << endl;
        //   //fitting range:
        //   //shift a range of fit and search for raw boarder of peak determined by fUpperPeakRelativeHight
        //   //maximum
        //   m = 0;
        //   Double_t currentHight = peakHightS[k];
        //   while ( currentHight > (peakHightS[k]*upFitBorder) ) {
        //     m++;
        //     fitMax = static_cast<Double_t>(peakPositionS[k]) + m*fitStep;
        //     currentHight = hSpectrum->GetBinContent(hSpectrum->GetXaxis()->FindBin(fitMax));
        //   }

        //   //minimum
        //   m = 0;
        //   currentHight = peakHightS[k];
        //   while ( currentHight > (peakHightS[k]*lowFitBorder) ) {
        //     m++;
        //     fitMin = static_cast<Double_t>(peakPositionS[k]) - m*fitStep;
        //     currentHight = hSpectrum->GetBinContent(hSpectrum->GetXaxis()->FindBin(fitMin));
        //   }

        //   //fitting
        //   fitAuto->SetRange(fitMin,fitMax);
        //   hSpectrum->Fit("fitAuto", "R+", "", fitMin, fitMax);
        //   c[i]->Update();
        //   // cout <<"fitPAR " << fitAuto->GetParameter(1) << " " ;
        //   nCh[k] = fitAuto->GetParameter(1);
        //   cout << peakPositionS[k]  << " and  " <<  nCh[k] << endl;
        //   E[k] = nCh[k];
        //   //th[2],thAv
        //   th[k] = fAlphaSi.GetR(E0[k],E[k]);
        //   cout << E0[k] << " " << E[k]<< " " << th[k] << " " << k << endl;
        // } // nopeaks == 2
        
        nCh[0] = peakPositionS[0];
        E[0] = nCh[0];
        //th[2],thAv
        th[0] = fAlphaSi.GetR(E0[0],E[0]);
        cout << E0[0] << " " << E[0]<< " " << th[0] << endl;

        // thAv = (th[0] + th[1])/2.;
        // cout << "angles for this ITERATION " << endl;
        // cout << " y x " << endl;
        // cout << i << " " << nStr << " " << nCh[0]<< endl;
        // cout << alpha[nStr] << " " << betta[i] << endl;
        // thAv = nCh[0];
        thAv = th[0]*cos(theta[i][nStr]) - 0.5 - 0.25; // dl of thick det and dl of the source
      } // if flag == 0
      if(flag == 1) {
        cout << " BAD SPECTRA THICK == 40 " << endl;
        thAv = 50.;
      }
      hTh->SetBinContent(i+1, nStr+1, thAv);
//SetBinContent(Int_t binx, Int_t biny, Double_t content)
      cout  << "THICKNESS"<< endl << thAv << endl;
      
      c[i]->Update();
    } // nStr
  }// i
        

  // outfile
  TFile *fw = new TFile("/home/oem/work/software/AculUti/data/thickness1.root", "RECREATE");
  if (fw->IsOpen() == 0) {
   Error("CalculateCalibParameters", "File %s was not created and won't be processed", "pdf/thick.root");
   return 1;
  }
  fw->cd();
  hTh->Write();
  fw->Close();

  // printing canvases
  TString fileName;
  for(Int_t i=0;i<16;i++){
    fileName.Form("pdf/SQ20_L%d.png",i);
    c[i]->Print(fileName.Data());
  } 

  return;

}

Double_t calcVectorTel1(Int_t n20, Int_t n1) {

  Double_t x20;
  x20 = 46.3 + (n20-7.5)*16./50;

  Double_t y1;
  y1 = 20.8 + (7.5-n1)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x20,y1*255./270,255);

  return tel1V.Theta();
}

Double_t calcVectorTel2(Int_t n20, Int_t n1) {

  Double_t y20;
  y20 = -46.3 + (n20-7.5)*16./50;

  Double_t x1;
  x1 = 20.8 + (7.5-n1)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x1*255./270,y20,255);

  return tel1V.Theta();
}

Double_t calcVectorTel3(Int_t n20, Int_t n1) {

  Double_t x20;
  x20 = -46.3 - (n20-7.5)*16./50;

  Double_t y1;
  y1 = -20.8 + (n1-7.5)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x20,y1*255./270,255);

  return tel1V.Theta();
}

Double_t calcVectorTel4(Int_t n20, Int_t n1) {

  Double_t y20;
  y20 = 46.3 + (n20-7.5)*16./50;

  Double_t x1;
  x1 = -20.8 + (n1-7.5)*16./60;

  TVector3 tel1V;
  tel1V.SetXYZ(x1*255./270,y20,255);

  return tel1V.Theta();
}