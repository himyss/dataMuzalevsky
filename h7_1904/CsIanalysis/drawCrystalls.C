void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Float_t p_anh1[16],p_anh2[16];
Float_t p1[16],p2[16];


void drawCrystalls(){

  readPar("CsI",p1,p2);
  readPar("CsI_Sep",p_anh1,p_anh2);

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/h7_4_selected.root");
  cout << ch->GetEntries() << endl;
  
  TString hDraw,hCut;

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // c1->Divide(4,4);

  gStyle->SetOptStat(0);
  ch->SetMarkerStyle(7);
  for(Int_t i=0;i<16;i++) {

    hCut.Form("nCsI_track==%d && nX_C!=-1",i);
    hDraw.Form("X_C:arCsI[%d]",i);
    ch->SetMarkerColor(i+1);
    // c1->cd(i+1);

    if (i==0) ch->Draw(hDraw.Data(),hCut.Data(),"",1000000,0);
    if (i!=0) ch->Draw(hDraw.Data(),hCut.Data(),"same",1000000,0);

    c1->Update();

  }

  TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // c1->Divide(4,4);

  ch->SetMarkerStyle(7);
  for(Int_t i=0;i<16;i++) {

    hCut.Form("nCsI_track==%d && nX_C!=-1",i);
    hDraw.Form("X_C:((arCsI[%d]-%f)/%f)*%f + %f",i,p1[i],p2[i],p_anh2[i],p_anh1[i]);
    ch->SetMarkerColor(i+1);
    // c1->cd(i+1);

    if (i==0) ch->Draw(hDraw.Data(),hCut.Data(),"",1000000,0);
    if (i!=0) ch->Draw(hDraw.Data(),hCut.Data(),"same",1000000,0);

    c2->Update();

  }

}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=0;
  TString file = "/home/ivan/work/soft/er/input/exp1904_pars/" + fileName + ".cal";
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