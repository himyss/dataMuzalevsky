void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

TCutG *cutCsI[16],*cut3h[16],*cutX_C[32];
TCutG *cuthe3_1[16],*cutSQ20_1[16],*cutSQ1_1[16];
TCutG *cuthe3_2[16],*cutSQ20_2[16],*cutSQ1_2[16];
TCutG *cuthe3_3[16],*cutSQ20_3[16],*cutSQ1_3[16];
TCutG *cuthe3_4[16],*cutSQ20_4[16],*cutSQ1_4[16];
TCutG *cutHe3_total1;

Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void create_cut(){
  nCoins = 0;

  TChain *ch = new TChain("tree");

  ch->Add("/media/ivan/data/exp1906/be10/analysed/tmp/second.root");
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/tmp/first.root");
  cout << ch->GetEntries() << endl;

  TString cut,hdraw;
  Int_t i = 7;

  TCanvas *c3h = new TCanvas("c3h","",1000,1000);
  ch->SetMarkerStyle(7);
  ch->SetMarkerColor(kBlack);      
  cut.Form("flagCent && nCsI_track==%d",i);
  hdraw.Form("X_C:arCsI[%d]>>h%d(4000,0,4000,200,0,100)",i,i);
  ch->Draw(hdraw.Data(),cut.Data(),"");
  c3h->Update();

  ch->SetMarkerStyle(20);
  ch->SetMarkerColor(kRed);
  cut.Form("flagCent && nCsI_track==%d && (nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4)",i);
  hdraw.Form("X_C:arCsI[%d]",i);
  ch->Draw(hdraw.Data(),cut.Data(),"same");
  c3h->Update();


}
  

