void drawRaw(){

  TELoss fAlphaSi;
  fAlphaSi.SetEL(1, 2.321); // density in g/cm3
  fAlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//  mSi.SetZP(1., 1.);    //protons
  fAlphaSi.SetZP(2., 4.);   //alphas, Z, A
  fAlphaSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
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

  //cout << "cut1 "<< cut1.Data() << endl;
  //cout << "cut2 "<< cut2.Data() << endl;
  //cout << "cut3 "<< cut3.Data() << endl;
  //cout << "cut4 "<< cut4.Data() << endl;

  TChain *ch = new TChain("AnalysisxTree");
  //ch->Add("/media/analysis_nas/exp201804/calib/si_after/si-1_si-20_35cm_45deg_new1_00*.root");
  //ch->Add("/media/analysis_nas/exp201804/calib/si_after/si-1_si-20_35cm_60deg_00*.root");

  TChain *ch0 = new TChain("AnalysisxTree");
  ch0->Add("/media/analysis_nas/exp201804/calib/si_after/si-1_si-20_35cm_0deg_new1_*.root");
  

 // -0.4293 0.006653    0

/*  TCanvas *c1 = new TCanvas("c1","raw data",1800,1000);
  c1->Divide(3,2);

  c1->cd(1);
  ch->Draw("NeEvent.SQY_L[7]*0.006653-0.4293 >> hy_0(200,0.435590,8)","","",1000000,1);
  h[0] = (TH1F*)gPad->GetPrimitive("hy_0");
  h[0]->GetXaxis()->SetTitle("Edep in 1mm middle Y strip");
  h[0]->GetXaxis()->SetTitleColor(2);
  h[0]->GetXaxis()->SetTitleOffset(0.75);
  h[0]->GetXaxis()->SetTitleSize(0.047);
  h[0]->GetXaxis()->CenterTitle();
  c1->Update();

  c1->cd(4);
  ch->Draw("NeEvent.SQY_L[15]*0.006501-0.4096 >> hy_15(200,0.435590,8)","","",10000000,1);
  h[1] = (TH1F*)gPad->GetPrimitive("hy_15");
  h[1]->GetXaxis()->SetTitle("Edep in 1mm last Y strip");
  h[1]->GetXaxis()->SetTitleColor(2);
  h[1]->GetXaxis()->SetTitleOffset(0.75);
  h[1]->GetXaxis()->SetTitleSize(0.047);
  h[1]->GetXaxis()->CenterTitle();
  c1->Update();

  c1->cd(2);
  ch->Draw("NeEvent.SQX_L[15]*0.006454+0.09241 >> hx_15(200,1.383210,8)","","",10000000,1);
  ch->Draw("NeEvent.SQX_L[0]*0.006705-0.001022 >> hx_0(200,1.339978,8)","","same",10000000,1);
  h[2] = (TH1F*)gPad->GetPrimitive("hx_15");
  h[2]->GetXaxis()->SetTitle("Edep in 1mm middle(blue) and first/left(green) X strip");
  h[2]->GetXaxis()->SetTitleColor(2);
  h[2]->GetXaxis()->SetTitleOffset(0.75);
  h[2]->GetXaxis()->SetTitleSize(0.047);
  h[2]->GetXaxis()->CenterTitle();

  h[3] = (TH1F*)gPad->GetPrimitive("hx_0");
  h[3]->SetLineColor(3);

  c1->Update();

  c1->cd(5);
  ch->Draw("NeEvent.SQX_L[31]*0.006666+0.1119 >> hx_31(200,1.445100,8)","","",10000000,1);
  h[4] = (TH1F*)gPad->GetPrimitive("hx_31");
  h[4]->GetXaxis()->SetTitle("Edep in 1mm last/right X strip");
  h[4]->GetXaxis()->SetTitleColor(2);
  h[4]->GetXaxis()->SetTitleOffset(0.75);
  h[4]->GetXaxis()->SetTitleSize(0.047);
  h[4]->GetXaxis()->CenterTitle();
  c1->Update();

  c1->cd(3);
  ch->Draw("NeEvent.SQY_R[0] >> h20_0(1300,200,1500)","","",10000000,1);
  h[5] = (TH1F*)gPad->GetPrimitive("h20_0");
  h[5]->GetXaxis()->SetTitle("Edep of 20mkm first/left strip");
  h[5]->GetXaxis()->SetTitleColor(2);
  h[5]->GetXaxis()->SetTitleOffset(0.75);
  h[5]->GetXaxis()->SetTitleSize(0.047);
  h[5]->GetXaxis()->CenterTitle();

  c1->Update();

  c1->cd(6);
  ch->Draw("NeEvent.SQY_R[15] >> h20_15(1300,200,1500)","","",10000000,1);
  h[6] = (TH1F*)gPad->GetPrimitive("h20_15");
  h[6]->GetXaxis()->SetTitle("Edep in 20mkm last/right strip");
  h[6]->GetXaxis()->SetTitleColor(2);
  h[6]->GetXaxis()->SetTitleOffset(0.75);
  h[6]->GetXaxis()->SetTitleSize(0.047);
  h[6]->GetXaxis()->CenterTitle();
  c1->Update();



  TCanvas *c2 = new TCanvas("c2","selection of SQ20 data",1800,1000);
  c2->Divide(2,2);

  c2->cd(1);
  ch->Draw("NeEvent.SQY_R[15] >> h22_0-7(1300,200,1500)",cut1.Data(),"",10000000,1);
  h[7] = (TH1F*)gPad->GetPrimitive("h22_0-7");
  h[7]->GetXaxis()->SetTitle("Edep in first half of 20mkm last/right strip (strips 0-7 of SQY_L were fired)");
  h[7]->GetXaxis()->SetTitleColor(2);
  h[7]->GetXaxis()->SetTitleOffset(0.75);
  h[7]->GetXaxis()->SetTitleSize(0.047);
  h[7]->GetXaxis()->CenterTitle();
  c2->Update();

  c2->cd(2);
  ch->Draw("NeEvent.SQY_R[15] >> h22_8-15(1300,200,1500)",cut2.Data(),"",10000000,1);
  h[8] = (TH1F*)gPad->GetPrimitive("h22_8-15");
  h[8]->GetXaxis()->SetTitle("Edep in second half of 20mkm last/right strip (strips 8-15 of SQY_L were fired)");
  h[8]->GetXaxis()->SetTitleColor(2);
  h[8]->GetXaxis()->SetTitleOffset(0.75);
  h[8]->GetXaxis()->SetTitleSize(0.047);
  h[8]->GetXaxis()->CenterTitle();
  c2->Update();

  c2->cd(3);
  ch->Draw("NeEvent.SQY_R[15] >> h22_0-15(1300,200,1500)",cut3.Data(),"",10000000,1);
  h[9] = (TH1F*)gPad->GetPrimitive("h22_0-15");
  h[9]->GetXaxis()->SetTitle("Edep in 20mkm last/right strip (strips 0-15 of SQY_L were fired)");
  h[9]->GetXaxis()->SetTitleColor(2);
  h[9]->GetXaxis()->SetTitleOffset(0.75);
  h[9]->GetXaxis()->SetTitleSize(0.047);
  h[9]->GetXaxis()->CenterTitle();
  c2->Update();


  c2->cd(4);
  ch->Draw("NeEvent.SQY_R[15] >> h22_underThr(1300,200,1500)",cut4.Data(),"",10000000,1);
  h[10] = (TH1F*)gPad->GetPrimitive("h22_underThr");
  h[10]->GetXaxis()->SetTitle("Edep in 20mkm last/right strip (strips 0-15 of SQY_L were NOT fired)");
  h[10]->GetXaxis()->SetTitleColor(2);
  h[10]->GetXaxis()->SetTitleOffset(0.75);
  h[10]->GetXaxis()->SetTitleSize(0.047);
  h[10]->GetXaxis()->CenterTitle();
  c2->Update();
*/
/*
/// calibration
  TF1* g1 = new TF1("g1", "gaus", 1040, 1125);
  g1->SetParLimits(0,1.,5000.);
  g1->SetParLimits(1,1040.,1125.);
  g1->SetParLimits(2,5,100.);

  TF1* g2 = new TF1("g2", "gaus", 1200, 1270);
  g2->SetParLimits(0,1.,5000.);
  g2->SetParLimits(1,1200.,1270.);
  g2->SetParLimits(2,1320.,1400.);

  TF1* g3 = new TF1("g3", "gaus", 1320, 1400);
  g3->SetParLimits(0,1.,5000.);
  g3->SetParLimits(1,1320.,1400.);
  g3->SetParLimits(2,5,100.);

  Double_t peakPosition,peakHight,x[3],y[3],e[3],temp;
  // energies after passing through 0.75 mkm dl
  y[0] = 4.7844;
  y[1] = 5.4895;
  y[2] = 6.0024;

  TList *functions;
  TPolyMarker *pm;
  TGraph *g[50];
  TF1 *lin = new TF1("lin","[0]*x+[1]",0,1500);

  ofstream outcalfile;
  outcalfile.open("par_20_60.cal");
  if (!outcalfile.is_open()) {
    Error("drawRaw", "Output file %s was not opened", "prepar_20.cal");
    return 0;
  }//if

  ofstream outXfile;
  outXfile.open("positions_20_60.cal");
  if (!outXfile.is_open()) {
    Error("drawRaw", "Output file %s was not opened", "positions_20.cal");
    return 0;
  }//if


  Float_t dl[16];
  ifstream myfile;
  TString line;
  Int_t count=0;
  myfile.open("/home/muzalevsky/work/temp/deadLayers.txt");
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g", dl+count);
    count++;
  }
  for(Int_t i=0;i<16;i++) {
    cout << dl[i]<<endl;
  }

  TCanvas *c4 = new TCanvas("c4","raw 20 mkm data trigger=3",1800,1000);
  c4->Divide(4,4);

  TCanvas *c5 = new TCanvas("c5","linfits",1800,1000);
  c5->Divide(4,4);


  for(Int_t i=0;i<16;i++) {
    cout << " new pad " << i+1 << endl;
    c4->cd(i+1);
    hDraw.Form("NeEvent.SQY_R[%d] >> h20_60_%d(1100,500,1600)",i,i);
    hname.Form("h20_60_%d",i);
    ch->Draw(hDraw.Data(),"NeEvent.trigger==3","",10000000,1);
    h[i] = (TH1F*)gPad->GetPrimitive(hname.Data());
    h[i]->ShowPeaks(20,"", 0.5);
    c4->Update();

    functions = h[i]->GetListOfFunctions();
    pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    //cout << *pm->GetY() << endl;
    for(Int_t j=0;j<3;j++) {
      x[j] = *(pm->GetX()+j);
      cout << x[j] << " ";
    } 
    cout <<endl<< "sorted " << endl;

    for (Int_t m = 0; m < 2; ++m){ 
      for (Int_t n = 0; n < 2; ++n){ 
        if(x[n] > x[n+1]) { 
            temp = x[n]; 
            x[n] = x[n+1]; 
            x[n+1] = temp; 
        }
      } 
    }
    for(Int_t j=0;j<3;j++) {
       cout << x[j] << " ";
    } 
    cout << endl;

    
    // recalculation energies using different effective dead layers for different strips
    cout << " shifted energies " << endl;
    for(Int_t j =0;j<16;j++) {
      for(Int_t k=0;k<3;k++) {
        e[k] = fAlphaSi.GetE(y[k],dl[j]);
        //cout << e[k] << " ";
      }
      //cout << endl;
    }

    g[i] = new TGraph(3,x,e);
    c5->cd(i+1);
    g[i]->SetMarkerSize(3);
    g[i]->Draw("AL*");
    g[i]->Fit("lin");
    c5->Update();
    outcalfile << setprecision(4) << lin->GetParameter(1) << "\t" << lin->GetParameter(0) << "\t" << endl;
    outXfile << setprecision(4) << x[0] << "\t" << x[1] << "\t" << x[2] << endl;

    //for (Int_t m = 0; m < 3; m++)  {
    //    cout << x[m] << " ";
    //}
    //cout << endl;
   
  }
*/

/*  cout << ch0->GetEntries() << " entr " << endl;
  Double_t peakPosition,peakHight,x[3],y[3],temp;
  y[0] = 4.7844;
  y[1] = 5.4895;
  y[2] = 6.0024;

  TList *functions;
  TPolyMarker *pm;
  TGraph *g[50];
  TF1 *lin = new TF1("lin","[0]*x+[1]",0,1500);

  ofstream outcalfile;
  outcalfile.open("prepar_20.cal");
  if (!outcalfile.is_open()) {
    Error("drawRaw", "Output file %s was not opened", "prepar_20.cal");
    return 0;
  }//if

  ofstream outXfile;
  outXfile.open("positions_20.cal");
  if (!outXfile.is_open()) {
    Error("drawRaw", "Output file %s was not opened", "positions_20.cal");
    return 0;
  }//if


  TCanvas *c4 = new TCanvas("c4","raw 20 mkm data trigger=3",1800,1000);
  c4->Divide(4,4);

  //TCanvas *c5 = new TCanvas("c5","linfits",1800,1000);
  //c5->Divide(4,4);
  Double_t x0;

  for(Int_t i=0;i<16;i++) {
    cout << " new pad " << i+1 << endl;
    c4->cd(i+1);
    hDraw.Form("NeEvent.SQY_R[%d] >> h20_%d(1400,200,1600)",i,i);
    hname.Form("h20_%d",i);
    ch0->Draw(hDraw.Data(),"NeEvent.trigger==3","",7876702,1);
    h[i] = (TH1F*)gPad->GetPrimitive(hname.Data());
    //x0 = h[i]->GetBinCenter(h[i]->GetMaximumBin());
    gStyle->SetStatW(0.3);                
    // Set width of stat-box (fraction of pad size)
    gStyle->SetStatH(0.4);

    c4->Update();

    //functions = h[i]->GetListOfFunctions();
    //pm = (TPolyMarker*)functions->FindObject("TPolyMarker");
    //cout << *pm->GetY() << endl;
    //for(Int_t j=0;j<3;j++) {
      //x[j] = *(pm->GetX()+j);
     // cout << x[j] << " ";
    //} 
    //cout <<endl<< "sorted " << endl;

    for (Int_t m = 0; m < 2; ++m){ 
      for (Int_t n = 0; n < 2; ++n){ 
        if(x[n] > x[n+1]) { 
            temp = x[n]; 
            x[n] = x[n+1]; 
            x[n+1] = temp; 
        }
      } 
    }
    //g[i] = new TGraph(3,x,y);
    //c5->cd(i+1);
    //g[i]->SetMarkerSize(3);
    //g[i]->Draw("AL*");
   // g[i]->Fit("lin");
    //c5->Update();
    //outcalfile << setprecision(4) << lin->GetParameter(1) << "\t" << lin->GetParameter(0) << "\t" << endl;
    outXfile << setprecision(4) << x0 << endl;

    //for (Int_t m = 0; m < 3; m++)  {
    //    cout << x[m] << " ";
    //}
    //cout << endl;
   
  }

*/

//thickness determination

/*Int_t SearchPeaks(const TH1 *hin, Double_t sigma, Option_t *option, const Int_t searchedpeaks)
{
  //Function searching peaks in inputed TH1 spectrum and selects the peaks in the histogram.
  //
  //  hin:
  //  sigma:
  //  option:
  //  threshold:
  //  searchedpeaks:

  TSpectrum sc; //by default for 100 peaks
  Int_t nopeaks = sc.Search(hin, sigma, "goff", fFitPeakThreshold);

  TString opt = option;
  opt.ToLower();

  const Double_t tStep = 0.05;


  if (!nopeaks) {
    return 0;
  }

  if (opt.Contains("goff")) {
    return nopeaks;
  }

  TPolyMarker *pm = (TPolyMarker*)hin->GetListOfFunctions()->FindObject("TPolyMarker");
  if (pm) {
    hin->GetListOfFunctions()->Remove(pm);
    delete pm;
  }
  pm = new TPolyMarker(nopeaks, sc.GetPositionX(), sc.GetPositionY());
  hin->GetListOfFunctions()->Add(pm);
  pm->SetMarkerStyle(23);
  pm->SetMarkerColor(kRed);
  pm->SetMarkerSize(1.3);

  return nopeaks;
}

Int_t AculCalibration::PeaksFitting(TH1* hSpectrum, Option_t* option, Double_t sigmamin)
{

  if (!hSpectrum) {
    cout<< "raw spec was not found " << endl;
    return 1;
  }
  Int_t dimension = hSpectrum->GetDimension();
  if (dimension > 1) {
    Error("PeaksFitting", "Only implemented for 1-d histograms");
    return 1;
  }

  TString opt = option;
  opt.ToLower();

  if (!kRaNOPEAKS) {
    Error("PeaksFitting", "kRaNOPEAKS is set to zero; calibration spectrum must be set");
    return 1;
  }

  const Int_t peaksNumber = SearchPeaks(hSpectrum, sigmamin, "", kRaNOPEAKS);

  if (peaksNumber != kRaNOPEAKS) {
    Info("PeaksFitting", "In histogram %s was found %d peaks", hSpectrum->GetName(), peaksNumber);
    return 1;
  }
  //should be optional output
  Info("PeaksFitting", "Number of peaks in %s: %d", hSpectrum->GetName(), peaksNumber);

  //working array for peaks, there are founded in accidental order
  Double_t peak[peaksNumber];
  Double_t *peakPosition;
  Double_t *peakHight;

  TList *functions = hSpectrum->GetListOfFunctions();
  TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker");

  peakPosition = pm->GetX();
  peakHight = pm->GetY();

  for (Int_t i = 0; i < peaksNumber; i++) {

    Double_t fitMin = 0;
    Double_t fitMax = 0;
    Double_t fitStep = hSpectrum->GetXaxis()->GetBinWidth(0);
//    cout << fitStep << endl;
//    cout << fLowerPeakRelativeHight << "\t" << fUpperPeakRelativeHight << endl;

    //fitting range:
    //shift a range of fit and search for raw boarder of peak determined by fUpperPeakRelativeHight
    //maximum
    Int_t j = 0;
    Double_t currentHight = peakHight[i];
    while ( currentHight > (peakHight[i]*fUpperPeakRelativeHight) ) {
      j++;
      fitMax = static_cast<Double_t>(peakPosition[i]) + j*fitStep;
      currentHight = hSpectrum->GetBinContent(hSpectrum->GetXaxis()->FindBin(fitMax));
    }

    //minimum
    j = 0;
    currentHight = peakHight[i];
    while ( currentHight > (peakHight[i]*fLowerPeakRelativeHight) ) {
      j++;
      fitMin = static_cast<Double_t>(peakPosition[i]) - j*fitStep;
      currentHight = hSpectrum->GetBinContent(hSpectrum->GetXaxis()->FindBin(fitMin));
    }

    //fitting
    if (opt.Contains("gp")) {
      Info("PeaksFitting", "Option containing gp");
      char fncname[20];
      sprintf(fncname, "gaus_aux_%d", i);
      TF1 *gausAux = new TF1(fncname, "gaus", fitMin - 10, fitMax + 10);    //pomocny gaus
      hSpectrum->Fit(fncname, "0 Q", "", fitMin - 15, fitMax + 15);       //prvotni fitovani

      sprintf(fncname, "auto_gp_%d", i);
      TF1 *fitAuto = new TF1(fncname, "gaus(0) + pol0(3)", fitMin - 15, fitMax + 15);   //fce pro automaticke fitovani
      fitAuto->SetParameter(0, gausAux->GetParameter(0));   //nastavovani parametru fitovaci fce
      fitAuto->SetParameter(1, gausAux->GetParameter(1));
      fitAuto->SetParameter(2, gausAux->GetParameter(2));

      hSpectrum->Fit(fncname, "0 R Q +", "", fitMin - 15, fitMax + 15); //dodelat zapis vsech fci
      hSpectrum->GetFunction(fncname)->ResetBit(TF1::kNotDraw);
      peak[i] = fitAuto->GetParameter(1);     //zapis asi pozice v kanalech do pomocneho pole
      if (opt.Contains("V")) {
        Info("PeaksFitting", "Peak position is\t %4.2f \tresolution is \t %2.1f %%", fitAuto->GetParameter(1), 235*(fitAuto->GetParameter(2))/(fitAuto->GetParameter(1)));
      }
    }
    else {
      char fncname[20];
      sprintf(fncname, "auto_g%d", i);
      TF1 *fitAuto = new TF1(fncname, "gaus", fitMin, fitMax);    //fce pro automaticke fitovani
//      cout << fitMin << "\t" << fitMax << endl;
//      fitAuto->SetParameter(2, fitMax-fitMin);
      fitAuto->SetLineWidth(fFitFuncLineWidth);
      hSpectrum->Fit(fncname, "+ 0 R Q", "", fitMin - 1, fitMax + 1);
//      hSpectrum->GetFunction(fncname)->ResetBit(TF1::kNotDraw);
      hSpectrum->GetFunction(fncname)->InvertBit(TF1::kNotDraw);
      peak[i] = fitAuto->GetParameter(1);     //zapis asi pozice v kanalech do pomocneho pole
      if (opt.Contains("v")) {
        Info("PeaksFitting", "Peak position is\t%4.2f\tresolution is \t%2.1f %%", fitAuto->GetParameter(1), 235*(fitAuto->GetParameter(2))/(fitAuto->GetParameter(1)));
      }
    }//else
    //end of fitting
  }//for over all analyzed peaks

  //peaks sorting
  Int_t j[peaksNumber];
  TMath::Sort(peaksNumber, peak, j, kFALSE);
  fPeak.Set(peaksNumber);
  for (Int_t i = 0; i < peaksNumber; i++) {
    fPeak[i] = peak[j[i]];
    //printf("\tPeak peak\t%f\n", fPeak[i]);
  }

  if (!opt.Contains("q") || opt.Contains("v")) {
    Info("PeaksFitting", "Control output:");
    for (Int_t i = 0; i < peaksNumber; i++) {
      printf("\tPeak position is\t%f\n", fPeak[i]);
    }
  }

  //  provest kontrolu pomerne polohy piku,
  //  jestli jsou spatne, provest urcita opatreni,
  //  napr. zapis daneho histogramu do souboru,
  //  zapis do souboru s chybama, vypis na obrazovku, ...
  for (Int_t i = 0; i < peaksNumber; i++) {
      if ( !( (((1-fPeakPositionTolerance)*(fEnergy[0]/fEnergy[i])) < (fPeak[0]/fPeak[i])) && (((1+fPeakPositionTolerance)*(fEnergy[0]/fEnergy[i])) > (fPeak[0]/fPeak[i])) ) ) {
      //printf("\tPeaksFitt fEnergy\t%f\n", fEnergy[i]);    
      if (fCalInformation  && opt.Contains("writebad")) {
        fCalInformation->cd();
        hSpectrum->Write();
      }
      //return 2;
    }
  }//for

  return 0;
}
*/


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
  Double_t betta[16];
  for(Int_t i=0;i<16;i++) {
    if(i<8) betta[i] = atan(3.125*(7.5-i)/339.5);
    if(i>7) betta[i] = atan(3.125*(0.5+i-8)/339.5);
  }

  cout << "angles for SQ20 strips [Rad]" << endl;
  for(Int_t i=0;i<16;i++) {
    cout << betta[i] << " ";
  }
  cout << endl;

//
  TH1* hSpectrum;

  Int_t peaksNumber,nopeaks;
  Double_t peak[peaksNumber];
  Double_t *peakPosition;
  Double_t *peakHight;
  Double_t *peakPositionS;//sorted peaks
  Double_t *peakHightS;

  Double_t minPos,minH;

  TList *functions;
  TPolyMarker *pm;
  TSpectrum sc; //by default for 100 peaks

  Double_t fitMin, fitMax, fitStep;
  TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);
  
  Double_t upFitBorder,lowFitBorder,E[2],E0[2],nCh[2],th[2],thAv;
  upFitBorder = 0.5; lowFitBorder = 0.5;

  // initial alpha energies [MeV] 
  E0[0] = 7.6869;
  E0[1] = 6.0024;

  Int_t m;

  TH2F *hTh = new TH2F("hTh","thickness distr",16,0,15,15,0,14);
  for(Int_t i =0;i<16;i++) {
    for(Int_t j=0;j<15;j++) {
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

  
  for(Int_t i=0;i<16;i++) { // strips in SQ20 (0-15)
    for(Int_t nStr =0;nStr<15;nStr++) { // strips in SQY_L (0-14)

      cout << "#########" << endl << "SQ20 " << i << " SQY_L " << nStr << endl;
      //nCan = i/16;
      //nPad = i - nCan*16 + 1;
      c[i]->cd(nStr+1);
   /* }  
  return;
    TCanvas *c6 = new TCanvas("c6","Edeposit distr",1800,1000);
    c6->Divide(4,4);
    for(Int_t i=0;i<4;i++) {
      c6->cd(i+1);*/

      // обнуление
      fitMin = 0;
      fitMax = 0;
      peakPosition = NULL;
      peakHight = NULL;
      peakPositionS = NULL;
      peakHightS = NULL;

      // заполнение гистограмм через tree->Draw()
      hDraw.Form("NeEvent.SQY_L[%d]>>edep%d_%d(870,130,1000)",nStr,i,nStr);
      hname.Form("edep%d_%d",i,nStr);
      hcut.Form("NeEvent.SQY_R[%d]>200",i);
      ch0->Draw(hDraw.Data(),hcut.Data(),"");
      h[i] = (TH1F*)gPad->GetPrimitive(hname.Data());
      
      hSpectrum = h[i];
      if (!hSpectrum) {
        cout<< "raw spec was not found " << endl;
        return 1;
      }    
      
      // подсчёт количества пиков
      nopeaks = sc.Search(hSpectrum, 8, "goff", 0.35);
      if (nopeaks<2) {
        cout << " less than 2 peaks were found " << endl;
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

     /* cout << "positions and heights " << endl;
      for(Int_t a=0;a<pm->GetN();a++) {
        cout << peakPosition[a] << " " << peakHight[a] << endl;
      }*/

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




      /*cout << "sorted positions and heights " << endl;
      for(Int_t a=0;a<pm->GetN();a++) {
        cout << peakPositionS[a] << " " << peakHightS[a] << endl;
      }*/


      fitStep = hSpectrum->GetXaxis()->GetBinWidth(0);
      
      //фитирование гауссом
      cout << "thickness!!" << endl; 
      for(Int_t k = 0; k < 2; k++) {
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
        E[k] = nCh[k]*parYL2[nStr] + parYL1[nStr];

        //th[2],thAv
        th[k] = fAlphaSi.GetR(E0[k],E[k]);
        cout << nCh[k] << " " << E[k]<< " " << th[k] << endl;
      } // nopeaks == 2
      
      thAv = (th[0] + th[1])/2.;
      thAv = ( thAv - 0.2 - (2.44/cos(alpha[nStr])) )/cos(betta[i]);
      hTh->SetBinContent(i, nStr, thAv);
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
    } // nStr
  }// i
 
  // outfile
  TFile *fw = new TFile("pdf/thick.root", "RECREATE");
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
    fileName.Form("pdf/SQ20_%d.png",i);
    c[i]->Print(fileName.Data());
  } 

  return;


  
}
