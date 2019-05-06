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

Float_t temp1[16];

// 7.45559
void golovkov1() {
  
  gStyle->SetOptStat(0);
  readPar("SSD20_R",oldpar1,oldpar2);
  readPar("pedestals_right",rpar1,rpar2);
  // gStyle->SetOptStat(0);
  // TChain *ch1 = new TChain("tree"); //e4
  cout << endl;
  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1811/analysed/clbdsd_20_r_02_selected1.root");
  cout << ch1->GetEntries() << endl;
  Double_t temp[16];

  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(4,4);
  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(4,4);

  for(Int_t i=0;i<16;i++) {
    c3->cd(i+1);
    hCut.Form("n20_R==%d",i);
    histName.Form("h%d",i);
    hDraw.Form("a20_R_cal + Y_R_cal.>>h%d(180,6.8,9.5)",i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.7);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    temp[i] =  7.4039/fitAuto->GetParameter(1);
    temp1[i] = 7.4039/fitAuto->GetParameter(1);

    c4->cd(i+1);
    hCut.Form("n20_R==%d && nY_R!=-1 && a20_R_cal + Y_R_cal>6.8 && a20_R_cal + Y_R_cal<9 && %lf + (%lf -1)*Y_R_cal/a20_R_cal>0.7 && %lf + (%lf -1)*Y_R_cal/a20_R_cal<1.4",i,temp[i],temp[i],temp[i],temp[i]);
    histName.Form("h%d_test",i);
    hDraw.Form("%lf + (%lf -1)*Y_R_cal/a20_R_cal >> h%d_test",temp[i],temp[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k[i] = fitAuto->GetParameter(1);
    cout << k[i]  << endl;
    c4->Update();
    newpar2[i] = oldpar2[i]*k[i];


    c3->Update();
  }

  cout  << " NEW Pars par2" << endl;
  for(Int_t i=0;i<16;i++) {
    // cout << newpar2[i] << endl;
    cout <<  k[i] << endl;
  }

  ofstream outcalfile;
  outcalfile.open("/home/oem/work/software/expertroot/input/parameters/ssd20_R_new_newthin.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd20_R_new.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << rpar1[i]*newpar2[i] << "\t" << newpar2[i] << endl;

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

