#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

// TCutG *cutCsI[16],*cut3h[16],*cutX_C[32];
// TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
// TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
// TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
// TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];
// TCutG *cutHe3_total1;
// TCutG *cut6Li_1;

// Float_t pCsI_1[16],pCsI_2[16];

// Int_t nCoins;

void temp(){
  create_IDs();

  // nCoins = 0;
  // readPar("CsI_anh",pCsI_1,pCsI_2);
  // readCuts();
  // return; 

  TChain *ch = new TChain("tree");

  ch->Add("/mnt/data/exp1904/analysed/selected/h7_newBeamDet/h7_ct_*");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;


  // TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);

  // for(Int_t i=0;i<16;i++) {

  //   c1->cd(i+1);

  //   // Int_t i =0;
  //   ch->SetMarkerStyle(1);
  //   ch->SetMarkerColor(kBlack);      
  //   cut.Form("flag1 && a20_1<4 && a1_1+a20_1_un<35 && n20_1==%d",i);
  //   // cut += cutg1->GetName();
  //   hdraw.Form("a20_1:a1_1+a20_1_un>>h%d1",i);
  //   ch->Draw(hdraw.Data(),cut.Data(),"");
  //   c1->Update();

  //   ch->SetMarkerStyle(1);
  //   ch->SetMarkerSize(0.5);   
  //   ch->SetMarkerColor(kGreen);      
  //   // cut.Form("n20_1==%d && nhe3_1",i);
  //   cut += " && multv_1==0";
  //   hdraw.Form("a20_1:a1_1+a20_1_un>>h%d_triton1",i);
  //   ch->Draw(hdraw.Data(),cut.Data(),"same");
  //   c1->Update();

  //   cuthe3_1[i]->SetLineColor(kRed);
  //   cuthe3_1[i]->Draw("same");
  //   c1->Update();
  // }


  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(4,4);

  for(Int_t i=0;i<16;i++) {

    c1->cd(i+1);

    // Int_t i =0;
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);      
    cut.Form("flag2 && a20_2<4 && a1_2+a20_2_un<35 && n20_2==%d",i);
    // cut += cutg1->GetName();
    hdraw.Form("a20_2:a1_2+a20_2_un>>h%d1",i);
    ch->Draw(hdraw.Data(),cut.Data(),"");
    c1->Update();

    ch->SetMarkerStyle(1);
    ch->SetMarkerSize(0.5);   
    ch->SetMarkerColor(kGreen);      
    // cut.Form("n20_1==%d && nhe3_1",i);
    cut += " && multv_2==0";
    hdraw.Form("a20_2:a1_2+a20_2_un>>h%d_triton1",i);
    ch->Draw(hdraw.Data(),cut.Data(),"same");
    c1->Update();

    cuthe3_1[i]->SetLineColor(kRed);
    cuthe3_1[i]->Draw("same");
    c1->Update();
  }

}