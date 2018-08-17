{

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/analysisexp1804/tmp.root");

  TString hDraw,hCut;

  TCanvas *c1 = new TCanvas("c1","c1",1800,1000);
  c1->Divide(4,4);

  for(Int_t i=0;i<16;i++){
    c1->cd(i+1);
    hDraw.Form("SQ20[%d]:SQY_L[]>>h%d(100,1,17,100,1,4)",i,i);
    hCut.Form("SQ20[%d]>1 && SQY_L[]>1",i);
    ch->Draw(hDraw.Data(),hCut.Data(),"col");
    c1->Update();
  }
  return;
}