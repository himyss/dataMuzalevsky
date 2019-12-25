void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

void calibrate_thin() {
  
  Float_t p1[16],p2[16],p3[16],p4[16];

  readPar("pedestal4",p4,p1);

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");
  cout << endl<< ch1->GetEntries() << endl;

  TCanvas *c5 = new TCanvas("c5","",1800,1000);  
  c5->Divide(4.,4);

  TH1F *hFit[16];
  Double_t temp[16],k[16];
  Float_t avk = 7.36699;

  TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

  Double_t fitMin,fitMax;

  TString hcut,hform,hname;

  for(Int_t i=0;i<16;i++) {
    c5->cd(i+1);

    ch1->SetLineColor(kBlue);
    hcut.Form("n20_3==%d && a3>0",i);
    ch1->Draw("a3.",hcut.Data(),"");

    hcut.Form("n20_3==%d && a3>3.5 && a3<6",i);
    ch1->SetLineColor(kGreen);
    hform.Form("a3>>h1_%d",i);
    hname.Form("h1_%d",i);
    ch1->Draw(hform.Data(),hcut.Data(),"same");

    hFit[i] = (TH1F*)gPad->GetPrimitive(hname.Data()); 
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);

    temp[i] =  avk - fitAuto->GetParameter(1); // приходится умножать на 2 исправить

    c5->Update();
  }

  TCanvas *c6 = new TCanvas("c6","",1800,1000);  
  c6->Divide(4.,4);


  for(Int_t i=0;i<16;i++) {
    c6->cd(i+1);

    ch1->SetLineColor(kBlue);
    hcut.Form("n20_3==%d && a20_3>200",i);
    ch1->Draw("a20_3.",hcut.Data(),"");

    hcut.Form("n20_3==%d && a3>3.5 && a3<6 && a20_3>200 && n3!=-1",i);
    ch1->SetLineColor(kGreen);
    hform.Form("a20_3>>h2_%d",i);
    hname.Form("h2_%d",i);
    ch1->Draw(hform.Data(),hcut.Data(),"same");

    hFit[i] = (TH1F*)gPad->GetPrimitive(hname.Data()); 
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);


    cout << "position in thin detector " << fitAuto->GetParameter(1) << endl;
    k[i] = temp[i]/fitAuto->GetParameter(1);

    c6->Update();
  }

  TCanvas *c7 = new TCanvas("c7","",1800,1000);  
  c7->Divide(4.,4);

  for(Int_t i=0;i<16;i++) {
    c7->cd(i+1);

    ch1->SetLineColor(kBlue);
    hcut.Form("n20_3==%d && a20_3>200 && a3>0 && n3!=-1",i);
    hform.Form("a20_3*%lf + a3",k[i]);
    ch1->Draw(hform.Data(),hcut.Data(),"");

    c7->Update();
  }


  ofstream outcalfile;
  outcalfile.open("/home/oem/work/software/AculUti/data/exp1904/ssd_20u_3.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd20_l_new.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << -p4[i]*k[i] << "\t" << k[i] << endl;

  outcalfile.close();



}

void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th) {
  Int_t nBin = h->GetMaximumBin();
  // cout << nBin << endl;
  // cout << h->GetBinContent(nBin) << " " <<  h->GetMaximum()*th << endl;
  // return;

  while (h->GetBinContent(nBin) > h->GetMaximum()*th || h->GetBinContent(nBin+1) > h->GetMaximum()*th) {
    nBin++;
  }
  *fUp = h->GetBinCenter(nBin+1);

  nBin = h->GetMaximumBin();

  while (h->GetBinContent(nBin) > h->GetMaximum()*th || h->GetBinContent(nBin-1) > h->GetMaximum()*th) {
    nBin--;
  }
  *fDown = h->GetBinCenter(nBin-1);

  return;
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){
  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/oem/work/software/AculUti/data/exp1904/" + fileName + ".cal";
  myfile.open(file.Data());
  while (! myfile.eof() ){
    line.ReadLine(myfile);
    if(count < 0){
      count++;
      continue;
    }
    if(line.IsNull()) break;
    sscanf(line.Data(),"%g %g", par1+count,par2+count);
    count++;
  }
  cout << endl << fileName.Data() << endl;
  for(Int_t i=0;i<size;i++) cout << par1[i] << " " << par2[i] << endl;

  return;
}
