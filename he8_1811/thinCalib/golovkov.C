void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);


TString hCut,hDraw,histName;

TH1F *hFit[16];

TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

Double_t fitMin,fitMax;

Double_t k[16],k1[16];
Float_t rpar1[16],rpar2[16];
Float_t oldpar1[16],oldpar2[16];
Float_t newpar1[16],newpar2[16];


Double_t temp[16];

void golovkov() {
  
  gStyle->SetOptStat(0);
  readPar("SSD20_L",oldpar1,oldpar2);
  readPar("pedestalsLeft",rpar1,rpar2);
  // gStyle->SetOptStat(0);
  // TChain *ch1 = new TChain("tree"); //e4
  cout << endl;
  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1811/analysed/clb/dsd_20_l_03_shifted.root");
  cout << ch1->GetEntries() << endl;
  Double_t temp[16];

  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(3.,4);

  for(Int_t i=0;i<10;i++) {
    c3->cd(i+1);
    hCut.Form("n20_L==%d && nY_L==-1",i);
    histName.Form("h%d",i);
    hDraw.Form("a20_L_cal.>>h%d(90,5,6)",i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k[i] =  4.7/fitAuto->GetParameter(1);
    temp[i] = fitAuto->GetParameter(1);
    newpar2[i] = oldpar2[i]*k[i];
    c3->Update();
  }

  for (Int_t i=0;i<10;i++) {
    cout << temp[i] << endl;
  }
  cout << endl;
  for (Int_t i=0;i<10;i++) {
    cout << k[i] << endl;
  }

  cout << endl;
  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(3.,4);

  for(Int_t i=0;i<10;i++) {
    c4->cd(i+1);
    hCut.Form("n20_L==%d && nY_L!=-1",i);
    histName.Form("h%d_summ",i);
    hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ(130,6.5,8)",k[i],i);
    // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k1[i] =  fitAuto->GetParameter(1);
    c4->Update();
  }

  Double_t avk;
  for (Int_t i=0;i<10;i++) {
    cout << k1[i] << endl;
    avk += k1[i];
  }
  avk = avk/10.;
  cout <<  "AVERAGE " <<  avk << endl;

  TCanvas *c5 = new TCanvas("c5","",1800,1000);  
  c5->Divide(2.,3);

  TCanvas *c6 = new TCanvas("c6","",1800,1000);  
  c6->Divide(2.,3);

  for(Int_t i=10;i<16;i++) {
    c5->cd(i-9);
    hCut.Form("n20_L==%d && nY_L!=-1",i);
    histName.Form("h%d_summ",i);
    hDraw.Form("a20_L_cal + Y_L_cal>>h%d_summ(130,6.5,8)",i);
    // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    c5->Update();

    // cout <<  avk/fitAuto->GetParameter(1) << endl;
    temp[i] =  avk/fitAuto->GetParameter(1);

    c6->cd(i-9);
    hCut.Form("n20_L==%d && nY_L!=-1 && a20_L_cal + Y_L_cal>6.5 && a20_L_cal + Y_L_cal<8 && %lf + (%lf -1)*Y_L_cal/a20_L_cal>0.84 && %lf + (%lf -1)*Y_L_cal/a20_L_cal<1.05",i,temp[i],temp[i],temp[i],temp[i]);
    histName.Form("h%d_test",i);
    hDraw.Form("%lf + (%lf -1)*Y_L_cal/a20_L_cal >> h%d_test",temp[i],temp[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k[i] = fitAuto->GetParameter(1);
    c6->Update();
    newpar2[i] = oldpar2[i]*k[i];
  }

//   ofstream outcalfile;
//   outcalfile.open("e16.cal");
//   if (!outcalfile.is_open()) {
//     cout << "Output file ssd20_l_new.cal was not opened" << endl;
//     return;
//   }//if
 
//   for (Int_t i=10;i<16;i++) outcalfile << temp[i] << endl;

//   outcalfile.close();
// return;

  for(Int_t i=10;i<16;i++) {
    cout << temp[i] << endl;
  }

  cout  << " NEW Pars par2" << endl;
  for(Int_t i=0;i<16;i++) {
    cout << newpar2[i] << endl;
  }

  ofstream outcalfile;
  outcalfile.open("/home/oem/work/software/expertroot/input/parameters/ssd20_l_new_newthin.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd20_l_new.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << -rpar1[i]*newpar2[i] << "\t" << newpar2[i] << endl;

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
  TString file = "/home/oem/work/software/expertroot/input/parameters/" + fileName + ".cal";
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

