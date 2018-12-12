void calctCsI() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/selected/central_times.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------


  TFile *f;
  TCutG *gCut;

  TH1F *h[16];
  Double_t a[16];

  TString hDraw,cut,hName,cutF3,fullcut,cutName;
  TCanvas *c1 = new TCanvas("c1","amp-time correlations",1800,1000);  
  c1->Divide(4,4); 
  for(Int_t i=0;i<16;i++){
    cutName.Form("cuts/CsI_%d.root",i);
    f = new TFile(cutName.Data());
    gCut = (TCutG*)f->Get("CUTG");
    c1->cd(i+1);
    hDraw.Form("aCsI:tCsI-tF5.>> h_%d(800,-400,400,800,0,4000)",i+1);
    hName.Form("h_%d",i+1);
    cut.Form("nCsI==%d",i);
    cutF3.Form(" && tF5.-tF3.>103 && tF5.-tF3.<115 && F5.>2400 && F5.<4400 && F3.>2000 && F3.<4000 && trigger!=1");
    fullcut = cut + cutF3; 
    // hDraw.Form("F5.:tF5.-tF3.");   
    ch->Draw(hDraw.Data(),fullcut.Data(),"cont");
    // gCut->Draw("same");
    c1->GetPad(i+1)->SetLogz();
    c1->Update();
  } 
  c1->Print("/home/user/Desktop/tCsI_cut.png");
  return;
}