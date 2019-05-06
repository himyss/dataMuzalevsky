void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Float_t pDSDY_R1[16];
Float_t pDSDY_R2[16];
Float_t pSQ20_R1[16],pSQ20_R2[16];

Float_t rpar1[16],rpar2[16];

void drawRight(){
  readPar("SSD20_R",pSQ20_R1,pSQ20_R2);
  readPar("pedestals_right",rpar1,rpar2);
  readPar("DSDY_R_newthin",pDSDY_R1,pDSDY_R2);

  TChain *ch = new TChain("er");
  // ch->Add("/home/oem/work/data/exp1811/digi/clb/dsd_20_l_03*");
  ch->Add("/home/oem/work/data/exp1811/digi/clb/dsd_20_r_02_000*");  
  cout << "Found " << ch->GetEntries() << " entries" << endl;

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(4,4);

  TString hDraw,cut;

  for(Int_t i=0;i<16;i++) {
    hDraw.Form("(ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0.fEdep*%lf +%lf)",pDSDY_R2[i],pDSDY_R1[i]);
    cut.Form("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0.fStripNb==%d && (ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0.fEdep*%lf +%lf)<10",i,pDSDY_R2[i],pDSDY_R1[i]);
    c1->cd(i+1);
    ch->Draw(hDraw.Data(),cut.Data(),"");
    c1->Update();
  }


return;
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/oem/work/software/expertroot/input/parameters/" + fileName + ".cal";
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
