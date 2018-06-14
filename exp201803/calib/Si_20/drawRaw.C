void drawRaw(){

  TELoss fAlphaSi;
  fAlphaSi.SetEL(1, 2.321); // density in g/cm3
	fAlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//	mSi.SetZP(1., 1.);		//protons
	fAlphaSi.SetZP(2., 4.);		//alphas, Z, A
	fAlphaSi.SetEtab(100000, 200.);	// ?, MeV calculate ranges
	fAlphaSi.SetDeltaEtab(300);


  TString cut[16];
  TString cut_0[16];
  TString cut1("");
  TString cut2("");
  TString cut3("");
  TString cut4("");
  
  
  TString hDraw,hname,hcut;

  TH1F *h0,*h1,*h2,*h[300];

  TString space(" || ");
  for(Int_t i =0;i<16;i++) {
    cut[i].Form("SQY_L[%d]>130",i);
    cut_0[i].Form("SQY_L[%d]<130",i);

    if(i==0) {
      cut1 = cut[0];
      cut3 = cut[0];
      cut4 = cut_0[0];
    }
    if(i<8) cut1 = cut1 + " || " + cut[i];

    if(i==8) cut2 = cut[8];
    if(i>7 && i<16) cut2 = cut2 + " || " + cut[i];

    cut3 = cut3 + " || " + cut[i];
    cut4 = cut4 + " && " + cut_0[i];
  }


  TChain *ch0 = new TChain("AnalysisxTree");
	ch0->Add("/media/analysis_nas/exp201804/calib/si_after/si-1_si-20_35cm_0deg_new1_*.root");
  


// reading input pars
  Float_t parYL1[16],parYL2[16];
  ifstream myfile4;
  TString line4;
  Int_t count=-2;
//  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/SQY_L.cal");
  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQY_L.cal");
  while (! myfile4.eof() ){
    line4.ReadLine(myfile4);
    if(count < 0){
      count++;
      continue;
    }
    if(line4.IsNull()) break;
    sscanf(line4.Data(),"%g %g", parYL1+count,parYL2+count);
    count++;
  }

  cout << endl << " pars for YL strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parYL1[i] << " " << parYL2[i] << endl;    

  // angles for DL in strips SQY_L
  Double_t alpha[16];
  for(Int_t i=0;i<16;i++) {
    if(i<8) alpha[i] = atan(3.625*(7.5-i)/350.);
    if(i>7) alpha[i] = atan(3.625*(0.5+i-8)/350.);
  }

  cout << "angles for DL in strips SQY_L [Rad]" << endl;
  for(Int_t i=0;i<16;i++) {
    cout << alpha[i] << " ";
  }
  cout << endl;

  // angles for SQ20 strips
  Double_t betta[32];
  for(Int_t i=0;i<32;i++) {
    if(i<16) betta[i] = atan(1.8125*(15.5-i)/350.);
    if(i>15) betta[i] = atan(1.8125*(0.5+i-16)/350.);
  }

  cout << "angles for SQX_L strips [Rad]" << endl;
  for(Int_t i=0;i<32;i++) {
    cout << betta[i]<< " ";
  }
  cout << endl;

//
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
  TSpectrum sc;	//by default for 100 peaks

	Double_t fitMin, fitMax, fitStep;
  TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);
  
  Double_t upFitBorder,lowFitBorder,E[2],E0[2],nCh[2],th[2],thAv;
  upFitBorder = 0.5; lowFitBorder = 0.5;

  // initial alpha energies [MeV] 
  E0[0] = 7.6869;
  E0[1] = 6.0024;

  Int_t m;

  TH2F *hTh = new TH2F("hTh","thickness distr",32,0,32,16,0,16);
  for(Int_t i =0;i<32;i++) {
    for(Int_t j=0;j<16;j++) {
      hTh->SetBinContent(i,j,0);
    }
  }  

  TCanvas *c[32];
  TString cName,cTitle;
  Int_t nPad,nCan;
  for(Int_t i=0;i<32;i++) {
    cName.Form("c%d",i);
    cTitle.Form("eDepostis in %d strip",i); 
    c[i] = new TCanvas(cName.Data(),cTitle.Data(),1800,1000);
    c[i]->Divide(4,4);
  }
  c[0]->cd(1);
  ch0->Draw("NeEvent.SQY_L[7]>>edepN(850,150,1000)","NeEvent.SQX_L[15]>200 && NeEvent.SQY_L[7]>150 && NeEvent.SQY_L[7]<1000","");
  h[0] = (TH1F*)gPad->GetPrimitive("edepN");
  numPoints = h[0]->GetEntries();
  cout << numPoints <<  "  npoints in GOOD spectra" << endl;

  for(Int_t i=0;i<32;i++) { // strips in SQ20 (0-15) SQX_L (0-31)
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
      hDraw.Form("(NeEvent.SQY_L[%d]*%f + %f)>>edep%d_%d(200,0.7,7)",nStr,parYL2[nStr],parYL1[nStr],i,nStr);
      //cout << hDraw.Data() << " asd asdasdasd " << parYL2[15] << endl;return; 
      hname.Form("edep%d_%d",i,nStr);
      //hcut.Form("NeEvent.SQY_R[%d]>200",i);
      hcut.Form("NeEvent.SQX_L[%d]>200 && NeEvent.SQY_L[%d]>150 && NeEvent.SQY_L[%d]<1000 && NeEvent.SQY_R[]>200",i,nStr,nStr);
      ch0->Draw(hDraw.Data(),hcut.Data(),"");
      h[i] = (TH1F*)gPad->GetPrimitive(hname.Data());
      nPoints  = h[i]->GetEntries();
      //cout << nPoints << " nentries!!! and relation " << nPoints/numPoints << endl;
      if(nPoints/numPoints < 0.1) flag = 1;
      
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
          return;
        }
        cout << nopeaks << endl;
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




        //cout << "sorted positions and heights " << endl;
       // for(Int_t a=0;a<pm->GetN();a++) {
        //  cout << peakPositionS[a] << " " << peakHightS[a] << endl;
        //}


        fitStep = hSpectrum->GetXaxis()->GetBinWidth(0);
        
        //фитирование гауссом
       // cout << "thickness!!" << endl; 
        for(Int_t k = 0; k < 1; k++) {
          //cout << peakPosition[k] << " " << peakHight[k] << endl;
          //fitting range:
	        //shift a range of fit and search for raw boarder of peak determined by fUpperPeakRelativeHight
	        //maximum
	        m = 0;
	        Double_t currentHight = peakHightS[k];
	        while ( currentHight > (peakHightS[k]*upFitBorder) ) {
		        m++;
		        fitMax = static_cast<Double_t>(peakPositionS[k]) + m*fitStep;
		        currentHight = hSpectrum->GetBinContent(hSpectrum->GetXaxis()->FindBin(fitMax));
	        }

	        //minimum
	        m = 0;
	        currentHight = peakHightS[k];
	        while ( currentHight > (peakHightS[k]*lowFitBorder) ) {
		        m++;
		        fitMin = static_cast<Double_t>(peakPositionS[k]) - m*fitStep;
		        currentHight = hSpectrum->GetBinContent(hSpectrum->GetXaxis()->FindBin(fitMin));
	        }

          //fitting
          fitAuto->SetRange(fitMin,fitMax);
          hSpectrum->Fit("fitAuto", "R+", "", fitMin, fitMax);
          //cout << fitAuto->GetParameter(1) << " " ;
          nCh[k] = fitAuto->GetParameter(1);
          E[k] = nCh[k];

          //th[2],thAv
          th[k] = fAlphaSi.GetR(E0[k],E[k]);
          cout << nCh[k] << " " << E[k]<< " " << th[k] << endl;
        } // nopeaks == 2
        
        //thAv = (th[0] + th[1])/2.;
        cout << "angles for this ITERATION " << endl;
        cout << " y x " << endl;
        cout << i << " " << nStr << endl;
        cout << alpha[nStr] << " " << betta[i] << endl;
        thAv = th[0];
        thAv = ( thAv - 0.2 - (2.44/cos(alpha[nStr])) )/cos(betta[i]);
      } // if flag == 0
      if(flag == 1) {
        cout << " BAD SPECTRA THICK ==40 " << endl;
        thAv = 40.;
      }
      hTh->SetBinContent(i+1, nStr+1, thAv);
//SetBinContent(Int_t binx, Int_t biny, Double_t content)
      cout  << "THICKNESS"<< endl << thAv << endl;
  
/*
      peakPosition = pm->GetX();
      peakHight = pm->GetY();
      for(Int_t j=0;j<nopeaks;j++) {
        cout << peakPosition[j] << " " <<  peakHight[j] << endl;


  for(Int_t i=0;i<2;i++) { // strips in SQ20 (0-15)
    for(Int_t nStr = 0;nStr<3;nStr++) { // strips in SQY_L (0-14)

      }*/

      c[i]->Update();
      //c[0]->Update();
    } // nStr
  }// i

  // outfile
  TFile *fw = new TFile("pdf/thick32.root", "RECREATE");
	if (fw->IsOpen() == 0) {
		Error("CalculateCalibParameters", "File %s was not created and won't be processed", "pdf/thick.root");
		return 1;
	}
  fw->cd();
  hTh->Write();
	fw->Close();

  // printing canvases
  TString fileName;
  for(Int_t i=0;i<32;i++){
    fileName.Form("pdf/SQ20_%d.png",i);
    c[i]->Print(fileName.Data());
  } 

  return;


  
}
