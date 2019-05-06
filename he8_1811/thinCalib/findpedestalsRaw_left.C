void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TString hCut,hDraw,histName;

TH1F *hFit[16];

TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

Double_t fitMin,fitMax;

Float_t oldpar1[16],oldpar2[16];
Float_t newpar1[16],newpar2[16];


Double_t temp[16];


void findpedestalsRaw_left() {
  
  readPar("SSD20_L",oldpar1,oldpar2);
  readPar("pedestalsLeft",newpar1,newpar2);

  TChain *ch2 = new TChain("stepRepackingxTree"); //e4
  // ch2->Add("/home/oem/work/data/exp1811/raw/clb/dsd_20_r_02_*");
  ch2->Add("/home/oem/work/data/exp1811/raw/clb/dsd_20_l_*");
  // ch2->Add("/home/oem/work/data/exp1811/digi/clb/dsd_20_l_03*");
  
  ch2->SetLineWidth(2.);
  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4,4);

  for(Int_t i=0;i<16;i++) {
    c1->cd(i+1);
    histName.Form("h%d_ped",i);
    hCut.Form("Left_telescope_SSD20_L.fData.fStChannel==%d && Left_telescope_tSSD20_L.@fData.GetEntries()==0",i);
    hDraw.Form("Left_telescope_SSD20_L.fData.fValue - %lf >>h%d_ped(40,0,40)",newpar1[i],i);
    ch2->Draw(hDraw.Data(),hCut.Data(),"");
    // hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    // findRange(hFit[i],&fitMax,&fitMin,0.3);
    // // cout << fitMax << " " << fitMin << endl;
    // fitAuto->SetRange(fitMin,fitMax);
    // hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    // // k[i] =  4.7843/fitAuto->GetParameter(1);
    // newpar1[i] = fitAuto->GetParameter(1) - 2.355*fitAuto->GetParameter(2);
    c1->Update();
  }
  // cout  << " NEW Pars par1" << endl;
  // for (Int_t i=0;i<16;i++) {
  //   cout << newpar1[i] << endl;
  // }

  // ofstream outcalfile;
  // outcalfile.open("/home/oem/work/data/exp1811/calibration/SSD20L/pedestals_left.cal");
  // if (!outcalfile.is_open()) {
  //   cout << "Output file ssd20_l_new.cal was not opened" << endl;
  //   return;
  // }//if

  // for (Int_t i=0;i<16;i++) outcalfile << -newpar1[i] << endl;

  // outcalfile.close();

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
