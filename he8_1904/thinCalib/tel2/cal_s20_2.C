void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TString hCut,hDraw,histName;

TH1F *hFit[16];

TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

Double_t fitMin,fitMax;

Double_t k[16],k1[16];
Float_t oldpar1[16],oldpar2[16];
Float_t newpar1[16],newpar2[16];

Float_t p1[16],p2[16],p3[16],p4[16];

Float_t temp[16];

void cal_s20_2() {

  gStyle->SetOptStat(0);

  readPar("pedestal2",p2,temp);
  readPar("ssd_20u_1",oldpar1,oldpar2);

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");
  cout << endl<< ch1->GetEntries() << endl;
  Double_t temp[16];

  Float_t avk = 7.41778; // from the calibration of the first telescope

  TCanvas *c1 = new TCanvas("c4","",1800,1000);  
  c1->Divide(4.,4);

  TCanvas *c2 = new TCanvas("c6","",1800,1000);  
  c2->Divide(4.,4);

  for(Int_t i=0;i<16;i++) {
    // cout << " wtf " << endl;
    c1->cd(i+1);
    hCut.Form("n20_2==%d && n2!=-1",i);
    histName.Form("h%d_summ",i);
    hDraw.Form("(a20_2.*%f) + a2>>h%d_summ(100,6,9)",oldpar2[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());  
    findRange(hFit[i],&fitMax,&fitMin,0.5);

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k[i] =  avk/fitAuto->GetParameter(1);
    c1->Update();
// continue;
    c2->cd(i+1);
      // && %lf + (%lf -1)*a4/a20_4_cal>0.5 && %lf + (%lf -1)*a4/a20_4_cal<1.5
    hCut.Form("a20_2>50 && n20_2==%d && n2!=-1 && (a20_2.*%f) + a2 > 6.5 && (a20_2.*%f) + a2 <10 ",i,oldpar2[i],oldpar2[i]);
    histName.Form("h%d_test",i);
    hDraw.Form("%lf + (%lf -1)*a2/(a20_2.*%f) >> h%d_test",k[i],k[i],oldpar2[i],i);
    // hDraw.Form("(7.32143 - a4)/a20_4_cal >> h%d_test",temp[i],temp[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    c2->Update();

    k1[i] = fitAuto->GetParameter(1);
    cout << k1[i] << endl;
  }
// return;
  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(4.,4);
  Double_t posAv = 0;

  for(Int_t i=0;i<16;i++) {
    c3->cd(i+1);
    hCut.Form("n20_2==%d && n2!=-1",i);
    histName.Form("h%d_summCal",i);
    hDraw.Form("(a20_2.*%f*%lf) + a2>>h%d_summCal(100,6,9)",oldpar2[i],k1[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data()); 
    findRange(hFit[i],&fitMax,&fitMin,0.5);

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    posAv += fitAuto->GetParameter(1);
    cout << fitAuto->GetParameter(1) << endl;
    c3->Update();
  }
  cout << posAv/16 << endl;
  ofstream outcalfile;
  outcalfile.open("/home/oem/work/software/AculUti/data/exp1904/ssd_20u_2.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd_20u_2.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << -p2[i]*k1[i]*oldpar2[i] << "\t" << k1[i]*oldpar2[i] << endl;

  outcalfile.close();

return;

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

