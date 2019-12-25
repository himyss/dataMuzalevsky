void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th);
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TString hCut,hDraw,histName;

TH1F *hFit[16];

TF1 *fitAuto = new TF1("fitAuto", "gaus",0,10);

Double_t fitMin,fitMax;

Double_t k1[16];

Float_t p1[16],p4[16];

Float_t temp[16];

void cal_s20_1() {

  gStyle->SetOptStat(0);

  readPar("pedestal1",p4,p1);

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");
  cout << endl<< ch1->GetEntries() << endl;
  Double_t temp[16];

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4.,4);

  for(Int_t i=0;i<16;i++) {
    // cout << " wtf " << endl;
    c1->cd(i+1);
    hCut.Form("n20_1==%d && n1==-1",i);
    histName.Form("h%d",i);
    hDraw.Form("a20_1.>>h%d(300,700,1000)",i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data()); 
    findRange(hFit[i],&fitMax,&fitMin,0.5);
    cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k1[i] =  4.6718/fitAuto->GetParameter(1); // 4.6718 - eAlpha after passing 0.75 (dl of det + dl of source) of Si (Lise) 
    c1->Update();
  }

  TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  c2->Divide(4.,4);
  Double_t posAv = 0;

  for(Int_t i=0;i<16;i++) {
    c2->cd(i+1);

    ch1->SetLineColor(kBlue);
    hCut.Form("n20_1==%d && a20_1>200 && a1>0 && n1!=-1",i);
    hDraw.Form("a20_1*%lf + a1 >> hSumm_%d(200,6.5,8)",k1[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    histName.Form("hSumm_%d",i);
    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data()); 
    findRange(hFit[i],&fitMax,&fitMin,0.5);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    cout << fitAuto->GetParameter(1);
    posAv += fitAuto->GetParameter(1);

    c2->Update();
  }
  cout << "average position of the last peak " << posAv/16 << endl;

  ofstream outcalfile;
  outcalfile.open("/home/oem/work/software/AculUti/data/exp1904/ssd_20u_1.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd20_l_new.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << -p4[i]*k1[i] << "\t" << k1[i] << endl;

  outcalfile.close();

  return;
}

void findRange(TH1F *h,Double_t* fUp,Double_t* fDown,Double_t th) {
  Int_t nBin = h->GetMaximumBin();

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