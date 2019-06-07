void calCsI(){
  gStyle->SetOptStat(0);

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1811/analysed/h7_all_cut.root");
  cout << ch->GetEntries() << endl;

  ch->SetMarkerColor(kBlack);
  ch->SetMarkerStyle(20);
  ch->SetMarkerSize(0.2);

  Float_t pCsI1[16],pCsI2[16];


  TString hCut,hDraw,histName;


  Bool_t cal1,cal2;
  cal1=1;
  cal2=2;

  if(cal1) {

    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);

    TFile *f2;
    TString cutName;
    TCutG *cut[16];

    for(Int_t i=0;i<16;i++) {
      cutName.Form("/home/oem/work/macro/he8_1811/CsIcalibration/calCut/cut_%d.root",i);
      f2 = new TFile(cutName.Data());
      cut[i] = (TCutG*)f2->Get("CUTG");
      if (!cut[i]) {
        cout << i  << " no cut"<< endl;
        return;
      }
      delete f2;
    }

    TF1 *lin = new TF1("lin","[0]+x*[1]",250,2250);

    ofstream outcalfile;
    outcalfile.open("CsI_may.cal");
    if (!outcalfile.is_open()) {
      cout << "Output file CsI_may.cal was not opened" << endl;
      return;
    }//if
   
    Float_t par1[16],par2[16];

    TGraph *g[16];

    for(Int_t i=0;i<16;i++) {
      c1->cd(i+1);

      par1[i] = 1;
      par2[i] = 0;

      // ch->SetMarkerColor(kBlack);
      // hDraw.Form("aCsI_reco - Y_C : aCsI >> h%d(400,200,3500,400,0,200)",i);
      // hCut.Form("nh3 && nCsI==%d && Y_C>0",i);
      // ch->Draw(hDraw.Data(),hCut.Data(),"");
      // c1->Update();

      cutName.Form("cut%d",i);
      cut[i]->SetName(cutName.Data());
      cout << cut[i]->GetName() << endl;

      // ch->SetMarkerColor(kRed);
      hDraw.Form("aCsI_reco - Y_C : aCsI >> h_cut%d(400,200,3500,400,0,200)",i);
      hCut.Form("nh3 && nCsI==%d && Y_C>0 && cut%d",i,i);
      ch->Draw(hDraw.Data(),hCut.Data(),"");
      c1->Update();

      g[i] = (TGraph*)gPad->GetPrimitive("Graph");
      if (g[i]==0) continue;
      cout << g[i]->GetN() << endl;
      g[i]->Fit("lin","R");
      c1->Update();

      par2[i] = lin->GetParameter(1);
      par1[i] = lin->GetParameter(0);

    }

    // c1->Print("/home/oem/Desktop/pics/CsIcuts.png");
    for (Int_t i=0;i<16;i++) outcalfile << par1[i] << " " << par2[i] << endl;
  }

  // if (cal2) {

  //   TCanvas *с2 = new TCanvas("с2","",1800,1000);  
  //   с2->Divide(4,4);

  //   for(Int_t i=0;i<16;i++) {
  //     с2->cd(i+1);

  //     hDraw.Form("ebeam:aCsI_cal>>h%d(140,40,160,100,60,160)",i);
  //     hCut.Form("beamH3 && nh3 && nCsI==%d",i);
  //     ch->Draw(hDraw.Data(),hCut.Data(),"col");
  //     с2->Update();
  //   }


  


  return;
}

