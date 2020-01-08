void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Float_t p_m1[16],p_m2[16];
Float_t p1[16],p2[16];


void tmp(){

  readPar("ssd_20u_4",p1,p2);
  readPar("SSD_20u_4_cal",p_m1,p_m2);

  // TChain *ch = new TChain("tree");
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_firstVol_cut.root");
  // ch->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_secondVol_cut.root");

  // TChain *chX = new TChain("tree");
  // chX->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_firstVol_cut_X.root");
  // chX->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_secondVol_cut_X.root");
  
  // TChain *chY = new TChain("tree");
  // chY->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_firstVol_cut_Y.root");
  // chY->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_secondVol_cut_Y.root");

  TChain *chXY = new TChain("tree");
  chXY->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_firstVol_cut_old.root");
  chXY->Add("/media/ivan/data/exp1906/be10/analysed/novPars/selection/be10_secondVol_cut_old.root");


  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(2,1);
  c1->cd(1);

  TString hDraw,hCut;
  chXY->SetMarkerStyle(7);

  for(Int_t i = 0;i<16;i++) {

    hDraw.Form("a20_4:a1_4 >> h%d(500,0,30,100,0,5)",i);
    hCut.Form("n20_4==%d && flag4",i);
    cout << hDraw.Data() << endl;
    chXY->SetMarkerColor(i+1);

    if (i==0) chXY->Draw(hDraw.Data(),hCut.Data(),"");
    if (i>0)  chXY->Draw(hDraw.Data(),hCut.Data(),"same");

    c1->Update();

  }

  // TCanvas *c2 = new TCanvas("c2","title",1800,1000);
  // c2->Divide(4,4);
  // TString hDraw,hCut;
  chXY->SetMarkerStyle(7);
  c1->cd(2);

  for(Int_t i = 0;i<16;i++) {
    // c2->cd(i+1);
    hDraw.Form("((a20_4-%f)/%f)*%f + %f:a1_4 >> h%d_new(500,0,30,100,0,5)",p_m1[i],p_m2[i],p2[i],p1[i],i);
    hCut.Form("n20_4==%d && flag4",i);
    cout << hDraw.Data() << endl;
    chXY->SetMarkerColor(i+1);

    // chXY->Draw(hDraw.Data(),hCut.Data(),"");

    if (i==0)  chXY->Draw(hDraw.Data(),hCut.Data(),"");
    if (i>0)  chXY->Draw(hDraw.Data(),hCut.Data(),"same");
    // cutg->SetLineColor(kRed);
    // cutg->Draw("same");

    c1->Update();
  }

  // c1->Print("/home/ivan/Desktop/dE-E.png");


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