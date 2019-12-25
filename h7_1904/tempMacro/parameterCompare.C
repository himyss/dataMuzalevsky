void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

void readPar1(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

  // Sipars
Float_t pSQ201_1[16],pSQ201_2[16];
Float_t pSQ202_1[16],pSQ202_2[16];
Float_t pSQ203_1[16],pSQ203_2[16];
Float_t pSQ204_1[16],pSQ204_2[16];

Float_t pSSD1_1[16],pSSD1_2[16];
Float_t pSSD2_1[16],pSSD2_2[16];
Float_t pSSD3_1[16],pSSD3_2[16];
Float_t pSSD4_1[16],pSSD4_2[16];

Float_t pSSD_V1_1[16],pSSD_V1_2[16];
Float_t pSSD_V2_1[16],pSSD_V2_2[16];
Float_t pSSD_V3_1[16],pSSD_V3_2[16];
Float_t pSSD_V4_1[16],pSSD_V4_2[16];


Float_t pSQ201_1mk[16],pSQ201_2mk[16];
Float_t pSQ202_1mk[16],pSQ202_2mk[16];
Float_t pSQ203_1mk[16],pSQ203_2mk[16];
Float_t pSQ204_1mk[16],pSQ204_2mk[16];

Float_t pSSD1_1mk[16],pSSD1_2mk[16];
Float_t pSSD2_1mk[16],pSSD2_2mk[16];
Float_t pSSD3_1mk[16],pSSD3_2mk[16];
Float_t pSSD4_1mk[16],pSSD4_2mk[16];

Float_t pSSD_V1_1mk[16],pSSD_V1_2mk[16];
Float_t pSSD_V2_1mk[16],pSSD_V2_2mk[16];
Float_t pSSD_V3_1mk[16],pSSD_V3_2mk[16];
Float_t pSSD_V4_1mk[16],pSSD_V4_2mk[16];

void parameterCompare(){
 
  readPar("ssd_20_1",pSQ201_1,pSQ201_2);
  readPar("ssd_20_2",pSQ202_1,pSQ202_2);
  readPar("ssd_20_3",pSQ203_1,pSQ203_2);
  readPar("ssd_20_4",pSQ204_1,pSQ204_2);

  readPar1("SSD_20u_1_calib",pSQ201_1mk,pSQ201_2mk);
  readPar1("SSD_20u_2_calib",pSQ202_1mk,pSQ202_2mk);
  readPar1("SSD_20u_3_calib",pSQ203_1mk,pSQ203_2mk);
  readPar1("SSD_20u_4_calib",pSQ204_1mk,pSQ204_2mk);
 cout << endl << "B pars" << endl;
  for(Int_t i = 0;i<16;i++){
    cout << pSQ201_1[i] << " " << pSQ201_1mk[i] << " "  << pSQ201_1[i] - pSQ201_1mk[i] << endl;
    // cout << pSQ201_2[i] << " " << pSQ201_2mk[i] << " "  << pSQ201_2[i]/pSQ201_2mk[i] << endl;
  }

  cout << endl << "lin pars" << endl;
  for(Int_t i = 0;i<16;i++){
    // cout << pSQ201_1[i] << " " << pSQ201_1mk[i] << " "  << pSQ201_1[i] - pSQ201_1mk[i] << endl;
    cout << pSQ201_2[i] << " " << pSQ201_2mk[i] << " "  << pSQ201_2[i]/pSQ201_2mk[i] << endl;
  }

 cout << endl << " SECOND B pars" << endl;
  for(Int_t i = 0;i<16;i++){
    cout << pSQ202_1[i] << " " << pSQ202_1mk[i] << " "  << pSQ202_1[i] - pSQ202_1mk[i] << endl;
    // cout << pSQ201_2[i] << " " << pSQ201_2mk[i] << " "  << pSQ201_2[i]/pSQ201_2mk[i] << endl;
  }

  cout << endl << "lin pars" << endl;
  for(Int_t i = 0;i<16;i++){
    // cout << pSQ201_1[i] << " " << pSQ201_1mk[i] << " "  << pSQ201_1[i] - pSQ201_1mk[i] << endl;
    cout << pSQ202_2[i] << " " << pSQ202_2mk[i] << " "  << pSQ202_2[i]/pSQ202_2mk[i] << endl;
  }

 cout << endl << " THIRD B pars" << endl;
  for(Int_t i = 0;i<16;i++){
    cout << pSQ203_1[i] << " " << pSQ203_1mk[i] << " "  << pSQ203_1[i] - pSQ203_1mk[i] << endl;
    // cout << pSQ201_2[i] << " " << pSQ201_2mk[i] << " "  << pSQ201_2[i]/pSQ201_2mk[i] << endl;
  }

  cout << endl << "lin pars" << endl;
  for(Int_t i = 0;i<16;i++){
    // cout << pSQ201_1[i] << " " << pSQ201_1mk[i] << " "  << pSQ201_1[i] - pSQ201_1mk[i] << endl;
    cout << pSQ203_2[i] << " " << pSQ203_2mk[i] << " "  << pSQ203_2[i]/pSQ203_2mk[i] << endl;
  }

 cout << endl << " FOURTH B pars" << endl;
  for(Int_t i = 0;i<16;i++){
    cout << pSQ204_1[i] << " " << pSQ204_1mk[i] << " "  << pSQ204_1[i] - pSQ204_1mk[i] << endl;
    // cout << pSQ201_2[i] << " " << pSQ201_2mk[i] << " "  << pSQ201_2[i]/pSQ201_2mk[i] << endl;
  }

  cout << endl << "lin pars" << endl;
  for(Int_t i = 0;i<16;i++){
    // cout << pSQ201_1[i] << " " << pSQ201_1mk[i] << " "  << pSQ201_1[i] - pSQ201_1mk[i] << endl;
    cout << pSQ204_2[i] << " " << pSQ204_2mk[i] << " "  << pSQ204_2[i]/pSQ204_2mk[i] << endl;
  }


}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
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


void readPar1(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/ivan/work/soft/er/input/exp1904_pars/MKpars/" + fileName + ".cal";
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
