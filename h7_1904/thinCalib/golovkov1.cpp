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

void golovkov1() {
  // 7.39878
  gStyle->SetOptStat(0);
  readPar("ssd20",oldpar1,oldpar2);
  // readPar("ssd_20u_4",oldpar1,oldpar2);

  readPar("pedestal1",p1,temp);
  readPar("pedestal2",p2,temp);
  readPar("pedestal3",p3,temp);
  readPar("pedestal4",p4,temp);

  // for(Int_t i=0;i<16;i++) {
  //   oldpar2[i] = oldpar2[i]/2.;
  //   oldpar1[i] = oldpar1[i]/2.;
  // }

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");
  cout << endl<< ch1->GetEntries() << endl;
  Double_t temp[16];


  cout << endl;

  // TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  // c4->Divide(4.,4);

  // for(Int_t i=0;i<16;i++) {
  //   // cout << " wtf " << endl;
  //   c4->cd(i+1);
  //   hCut.Form("n20_4==%d && n2!=-1",i);
  //   histName.Form("h%d_summ",i);
  //   hDraw.Form("(a20_4.*%f) + %f + a2>>h%d_summ(100,6,9)",oldpar2[i],oldpar1[i],i);
  //   // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ(130,6.5,8)",k[i],i);
  //   // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
  //   ch1->Draw(hDraw.Data(),hCut.Data(),"",1000000,0);

  //   hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
  //   // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
  //   findRange(hFit[i],&fitMax,&fitMin,0.5);
  //   // cout << fitMax << " " << fitMin << endl;

  //   fitAuto->SetRange(fitMin,fitMax);
  //   hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
  //   k1[i] =  fitAuto->GetParameter(1);
  //   c4->Update();
  // }
// 7.35613

  Float_t avk = 7.32143;

  TCanvas *c5 = new TCanvas("c5","",1800,1000);  
  // c5->Divide(4.,4);

  TCanvas *c6 = new TCanvas("c6","",1800,1000);  
  // c6->Divide(4.,4);

  // for(Int_t i=0;i<16;i++) {
    { Int_t i =0;
    // c5->cd(i+1);
    // hCut.Form("n20_4==%d && n4!=-1 && a20_4>50",i);
    // histName.Form("h%d_summ",i);
    // hDraw.Form("a20_4.*%lf*0.5 + %lf*0.5 + a4>>h%d_summ(100,6.5,8)",oldpar2[i],oldpar1[i],i); // приходится умножать на 2 исправить
    // // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
    // ch1->Draw(hDraw.Data(),hCut.Data(),"");

    // hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    // findRange(hFit[i],&fitMax,&fitMin,0.6);
    // // cout << fitMax << " " << fitMin << endl;
    // fitAuto->SetRange(fitMin,fitMax);
    // hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    // c5->Update();

    // c5->cd(i+1);
    hCut.Form("n20_4==%d && a20_4>50",i);
    histName.Form("h%d_summ",i);
    // hDraw.Form("a20_4_cal + a4>>h%d_summ(100,6.5,8)",i); // приходится умножать на 2 исправить
    hDraw.Form("a20_4_cal + a4>>h%d_summ(1000,0,8)",i); // приходится умножать на 2 исправить
    // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;
    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    c5->Update();


    cout <<  fitAuto->GetParameter(1) << endl;
    temp[i] =  avk/fitAuto->GetParameter(1); // приходится умножать на 2 исправить
    cout << temp[i] << endl; 

    // c6->cd(i+1);
    // hCut.Form("a20_4>50 && n20_4==%d && n4!=-1 && a20_4_cal + a4>6.5 && a20_4_cal + a4<10 && %lf + (%lf -1)*a4/a20_4_cal>0.5 && %lf + (%lf -1)*a4/a20_4_cal<1.5",i,temp[i],temp[i],temp[i],temp[i]);
    // histName.Form("h%d_test",i);
    // // hDraw.Form("%lf + (%lf -1)*a4/a20_4_cal >> h%d_test",temp[i],temp[i],i);
    // hDraw.Form("(7.32143 - a4)/a20_4_cal >> h%d_test",temp[i],temp[i],i);
    // ch1->Draw(hDraw.Data(),hCut.Data(),"");

    // hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // findRange(hFit[i],&fitMax,&fitMin,0.6);
    // // cout << fitMax << " " << fitMin << endl;
    // fitAuto->SetRange(fitMin,fitMax);
    // hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    // k[i] = fitAuto->GetParameter(1);
    // c6->Update();
    // newpar2[i] = oldpar2[i]*k[i];
  }
// return;
  for(Int_t i=0;i<16;i++) {
    cout << k[i] << endl;
  }

  // // ofstream outcalfile;
  // // outcalfile.open("e16.cal");
  // if (!outcalfile.is_open()) {
  //   cout << "Output file ssd20_l_new.cal was not opened" << endl;
  //   return;
  // }//if
 
  // for (Int_t i=10;i<16;i++) outcalfile << temp[i] << endl;

// //   outcalfile.close();
// // return;

  // for(Int_t i=10;i<16;i++) {
  //   cout << temp[i] << endl;
  // }

  cout  << " NEW Pars par2" << endl;
  for(Int_t i=0;i<16;i++) {
    cout << newpar2[i] << endl;
  }
  cout  << " Old Pars par2" << endl;
  for(Int_t i=0;i<16;i++) {
    cout << oldpar2[i] << endl;
  }

  ofstream outcalfile;
  outcalfile.open("/home/oem/Desktop/pars/ssd_20u_4.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd20_l_new.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << -p4[i]*newpar2[i] << "\t" << newpar2[i] << endl;

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

