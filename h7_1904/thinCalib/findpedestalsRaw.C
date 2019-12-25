void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TString hCut,hDraw,histName;

TH1F *hFit[16];

TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

Double_t fitMin,fitMax;

Float_t oldpar1[16],oldpar2[16];
Float_t newpar1[16],newpar2[16];

Float_t p1[16],p2[16],p3[16],p4[16];



Float_t temp[16];


void findpedestalsRaw() {
  
  readPar("pedestal1",p1,temp);
  readPar("pedestal2",p2,temp);
  readPar("pedestal3",p3,temp);
  readPar("pedestal4",p4,temp);



  TChain *ch2 = new TChain("stepRepackingxTree"); //e4
  ch2->Add("/home/oem/work/data/exp1904/raw/clb/20um_1mm*");
  // ch2->Add("/home/oem/work/data/exp1811/digi/clb/dsd_20_l_03*");
  ch2->SetLineWidth(2.);
  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4,4);

  for(Int_t i=0;i<16;i++) {
    c1->cd(i+1);
    histName.Form("h%d_ped",i);
    hCut.Form("Telescope_4_SSD20_4.fData.fStChannel==%d && Telescope_4_tSSD20_4.@fData.GetEntries()==0",i);
    hDraw.Form("Telescope_4_SSD20_4.fData.fValue - %lf >>h%d_ped(150,0,150)",p4[i],i);
    ch2->Draw(hDraw.Data(),hCut.Data(),"");
    // hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    // findRange(hFit[i],&fitMax,&fitMin,0.1);
    // // cout << fitMax << " " << fitMin << endl;
    // fitAuto->SetRange(fitMin,fitMax);
    // hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);

    // newpar1[i] = fitAuto->GetParameter(1) - 2.355*fitAuto->GetParameter(2);
    c1->Update();
  }
  cout  << " NEW Pars par1" << endl;
  for (Int_t i=0;i<16;i++) {
    cout << newpar1[i] << endl;
  }

  // ofstream outcalfile;
  // outcalfile.open("/home/oem/work/software/AculUti/data/exp1904/pedestal4.cal");
  // if (!outcalfile.is_open()) {
  //   cout << "Output file ssd20_l_new.cal was not opened" << endl;
  //   return;
  // }//if

  // for (Int_t i=0;i<16;i++) outcalfile << newpar1[i] << endl;

  // outcalfile.close();

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
