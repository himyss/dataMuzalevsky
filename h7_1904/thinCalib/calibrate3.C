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

void calibrate3() {
  
  gStyle->SetOptStat(0);
  readPar("ssd20",oldpar1,oldpar2);

  readPar("pedestal1",p1,temp);
  readPar("pedestal2",p2,temp);
  readPar("pedestal3",p3,temp);
  readPar("pedestal4",p4,temp);
  cout << endl;

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cut.root");
  cout << ch1->GetEntries() << endl;
  Double_t temp[16];
  TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  c3->Divide(3.,3);

  for(Int_t i=0;i<9;i++) {
    c3->cd(i+1);
    hCut.Form("n20_3==%d && n3==-1 && a20_3>50",i);
    histName.Form("h%d",i);
    hDraw.Form("(a20_3.*%f) + %f>>h%d(200,8.5,10)",oldpar2[i],oldpar1[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.6);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k[i] =  4.6718/fitAuto->GetParameter(1);
    temp[i] = fitAuto->GetParameter(1);
    newpar2[i] = oldpar2[i]*k[i];
    c3->Update();
  }

  // for (Int_t i=0;i<9;i++) {
  //   cout << temp[i] << endl;
  // }
  // cout << endl;
  // for (Int_t i=0;i<9;i++) {
  //   cout << k[i] << endl;
  // }

  // cout << endl;
  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(3.,3);

  for(Int_t i=0;i<9;i++) {
    c4->cd(i+1);
    hCut.Form("n20_3==%d && n3!=-1 && a20_3>50",i);
    histName.Form("h%d_summ",i);
    hDraw.Form("%lf*a20_3. + a3>>h%d_summ(100,6,9)",newpar2[i],i);
    // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ(130,6.5,8)",k[i],i);
    // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
    ch1->Draw(hDraw.Data(),hCut.Data(),"");

    hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
    // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
    findRange(hFit[i],&fitMax,&fitMin,0.5);
    // cout << fitMax << " " << fitMin << endl;

    fitAuto->SetRange(fitMin,fitMax);
    hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
    k1[i] =  fitAuto->GetParameter(1);
    c4->Update();
  }

  Double_t avk1;
  for (Int_t i=0;i<9;i++) {
    cout << k1[i] << endl;
    avk1 += k1[i];
  }
  cout << avk1/9. << endl;
  return;
  TCanvas *c5 = new TCanvas("c5","",1800,1000);  
  c5->Divide(3.,3);

  Float_t avk = 7.36699;


  TString hcut,hform,hname;

  for(Int_t i=10;i<16;i++) {
    c5->cd(i+1-10);

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
  c6->Divide(3.,3);


  for(Int_t i=10;i<16;i++) {
    c6->cd(i+1-10);

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

    newpar2[i] = oldpar2[i]*k[i];

    c6->Update();
  }

  TCanvas *c7 = new TCanvas("c7","",1800,1000);  
  c7->Divide(4.,4);

  for(Int_t i=0;i<16;i++) {
    c7->cd(i+1);

    ch1->SetLineColor(kBlue);
    hcut.Form("n20_3==%d",i);
    hform.Form("a20_3*%lf + a3",newpar2[i]);
    ch1->Draw(hform.Data(),hcut.Data(),"");

    c7->Update();
  }


// return;
//   TCanvas *c5 = new TCanvas("c5","",1800,1000);  
//   c5->Divide(3.,3);

//   TCanvas *c6 = new TCanvas("c6","",1800,1000);  
//   c6->Divide(3.,3);

//   for(Int_t i=9;i<16;i++) {
//     c5->cd(i-8);
//     hCut.Form("n20_1==%d && n1!=-1",i);
//     histName.Form("h%d_summ",i);
//     hDraw.Form("(0.5*a20_1.*%f) + %f + a1>>h%d_summ(100,6,9)",oldpar2[i],oldpar1[i],i); // приходится умножать на 2 исправить
//     // hDraw.Form("a20_L_cal*%lf + Y_L_cal>>h%d_summ",k[i],i);
//     ch1->Draw(hDraw.Data(),hCut.Data(),"");

//     hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
//     // cout << hFit[i]->GetBinCenter(hFit[i]->GetMaximumBin()) << endl;  
//     findRange(hFit[i],&fitMax,&fitMin,0.6);
//     // cout << fitMax << " " << fitMin << endl;
//     fitAuto->SetRange(fitMin,fitMax);
//     hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
//     c5->Update();

//     cout <<  avk/fitAuto->GetParameter(1) << endl;
//     temp[i] =  avk/fitAuto->GetParameter(1); // приходится умножать на 2 исправить
//     cout << temp[i] << endl; 

//     c6->cd(i-8);
//     hCut.Form("n20_1==%d && n1!=-1 && (0.5*a20_1.*%f) + %f + a1>6.5 && (0.5*a20_1.*%f) + %f + a1<10 && %lf + (%lf -1)*a1/a20_1>0.84 && %lf + (%lf -1)*a1/a20_1<1.05",i,oldpar2[i],oldpar1[i],oldpar2[i],oldpar1[i],temp[i],temp[i],temp[i],temp[i]);
//     histName.Form("h%d_test",i);
//     hDraw.Form("%lf + (%lf -1)*a1/a20_1 >> h%d_test",temp[i],temp[i],i);
//     ch1->Draw(hDraw.Data(),hCut.Data(),"");

//     hFit[i] = (TH1F*)gPad->GetPrimitive(histName.Data());
//     findRange(hFit[i],&fitMax,&fitMin,0.6);
//     // cout << fitMax << " " << fitMin << endl;
//     fitAuto->SetRange(fitMin,fitMax);
//     hFit[i]->Fit("fitAuto", "R+", "", fitMin, fitMax);
//     k[i] = fitAuto->GetParameter(1);
//     c6->Update();
//     newpar2[i] = 0.5*oldpar2[i]*k[i];
//   }

  // ofstream outcalfile;
  // outcalfile.open("e16.cal");
  // if (!outcalfile.is_open()) {
  //   cout << "Output file ssd20_l_new.cal was not opened" << endl;
  //   return;
  // }//if
 
  // for (Int_t i=10;i<16;i++) outcalfile << temp[i] << endl;

// //   outcalfile.close();
// // return;

  // for(Int_t i=9;i<16;i++) {
  //   cout << temp[i] << endl;
  // }

  cout  << " NEW Pars par2" << endl;
  for(Int_t i=0;i<16;i++) {
    cout << newpar2[i] << endl;
  }

  ofstream outcalfile;
  outcalfile.open("/home/oem/work/software/AculUti/data/exp1904/ssd_20u_1.cal");
  if (!outcalfile.is_open()) {
    cout << "Output file ssd20_l_new.cal was not opened" << endl;
    return;
  }//if

  outcalfile << "2" << endl;
  outcalfile << "16" << endl;  
  for (Int_t i=0;i<16;i++) outcalfile << -p1[i]*newpar2[i] << "\t" << newpar2[i] << endl;

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

