{
  TFile *f = new TFile("/home/muzalevsky/AculUti/exp1804/calib/si_1mm/SQY_L_full_calibrated_spectra.root");
  const Int_t nhists = 16;
  TH1F *h[nhists];



  TString hname,cName;
  TTree *t = (TTree*)f->Get("AnalysisxTree");
  for(Int_t i=0;i<nhists;i++) {
    hname.Form("HistSQY_L[%d]Efull",i);
    h[i] = (TH1F*)f->Get(hname.Data()); 
  }
  
  TF1* g1 = new TF1("g1", "gaus", 4.4, 4.6);
  g1->SetParLimits(0,1.,150.);
  g1->SetParLimits(1,4.,5.);
  g1->SetParLimits(2,0.1,3.);

  TF1* g2 = new TF1("g2", "gaus", 5.12, 5.35);
  g2->SetParLimits(0,1.,150.);
  g2->SetParLimits(1,5.12,5.35);
  g2->SetParLimits(2,0.1,3.);

  TF1* g3 = new TF1("g3", "gaus", 5.65, 5.95);
  g3->SetParLimits(0,1.,150.);
  g3->SetParLimits(1,5.65,5.95);
  g3->SetParLimits(2,0.1,3.);

  TF1* g4 = new TF1("g4", "gaus", 7.25, 7.65);
  g4->SetParLimits(0,1.,150.);
  g4->SetParLimits(1,7.25,7.65);
  g4->SetParLimits(2,0.1,3.);
  
  const Int_t ncan = 4;
  TCanvas *c[ncan];
  for(Int_t i=0;i<ncan;i++){
    cName.Form("c%d",i+1);
    TCanvas *c[i] = new TCanvas(cName.Data(),"calibrated spectra",1000,1000);
    c[i]->Divide(2,2);
  }

  /*c1->cd(1);
  h[0]->Draw();
  h[0]->Rebin(8);
  h[0]->GetXaxis()->SetRangeUser(4.,8.);
  h[0]->Fit("g1","R+");
  h[0]->Fit("g2","R+");
  h[0]->Fit("g3","R+");
  h[0]->Fit("g4","R+");*/

	ofstream outcalfile;
	outcalfile.open("/home/muzalevsky/AculUti/exp1804/calib/si_1mm/check_cali.txt");
	if (!outcalfile.is_open()) {
		cout <<"Output file was not opened" << endl;
		return;
	}

  Int_t count=-1;
  Int_t nPad;
  for(Int_t i=0;i<nhists;i++) {
    count = i/4;
    nPad = (i%4)+1;
    c[count]->cd(nPad);

    h[i]->Draw();
    h[i]->Rebin(5);
    h[i]->Fit("g1","R+");
    h[i]->Fit("g2","R+");
    h[i]->Fit("g3","R+");
    h[i]->Fit("g4","R+");
    h[i]->GetXaxis()->SetRangeUser(4.,8.);
    c[count]->Update();
    outcalfile << g1->GetParameter(1) << "\t" << g2->GetParameter(1) << "\t" << g3->GetParameter(1) << "\t" << g4->GetParameter(1) << endl; 
  }

  return;
}
