void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);

Float_t pD1_1[16],pD1_2[16];
Float_t pD2_1[16],pD2_2[16];
Float_t pD3_1[16],pD3_2[16];
Float_t pD4_1[16],pD4_2[16];

Float_t p201_1[16],p201_2[16];
Float_t p202_1[16],p202_2[16];
Float_t p203_1[16],p203_2[16];
Float_t p204_1[16],p204_2[16];

Float_t par1[16],par2[16];

void drawPedestals() {
  
  readPar("ssd_20u_1",p201_1,p201_2);
  readPar("ssd_20u_2",p202_1,p202_2);
  readPar("ssd_20u_3",p203_1,p203_2);
  readPar("ssd_20u_4",p204_1,p204_2);

  readPar("SSD_1m_1",pD1_1,pD1_2);
  readPar("SSD_1m_2",pD2_1,pD2_2);
  readPar("SSD_1m_3",pD3_1,pD3_2);
  readPar("SSD_1m_4",pD4_1,pD4_2);


  gStyle->SetOptStat(0);
  // TChain *ch = new TChain("AnalysisxTree");
  // ch->Add("/home/oem/work/data/exp1904/clb/20um_1mm*");

  TChain *ch = new TChain("tree");
  ch->Add("/home/oem/work/data/exp1904/clb/analysed/20um_1mm_cal.root");

  // TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  // c1->Divide(4,4);

  // TString hDraw,cut;

  // for(Int_t i=0;i<16;i++) {
  //   c1->cd(i+1);
  //   ch->SetLineColor(kBlack);
  //   hDraw.Form("a20_4*%lf+a4 >> h%d(200,3,8)",p204_2[i],i);
  //   cut.Form("n4>-1 && n20_4 ==%d",i);
  //   ch->Draw(hDraw.Data(),cut.Data(),"");
  //   c1->Update();

  //   ch->SetLineColor(kRed);
  //   hDraw.Form("a20_4_cal+a4 >> h_cal%d(200,3,8)",i);
  //   cut.Form("n4>-1 && n20_4 ==%d",i);
  //   ch->Draw(hDraw.Data(),cut.Data(),"same");
  //   c1->Update();


  // }

  TCanvas *c2 = new TCanvas("c2","title",1800,1000);
  c2->Divide(2,2);
  c2->cd(1);
  ch->Draw("n20_1:a20_1_cal+a1 >> h1(300,1.,8,16,0,16)","n1==-1","BOX");
  // ch->Draw("a20_1_cal+a1 >> h1(300,1.,8)","n1!=1 && a20_1>50","");

  c2->cd(2);
  ch->Draw("n20_2:a20_2_cal+a2 >> h2(300,1.,8,16,0,16)","n2==-1","BOX"); 

  c2->cd(3);
  ch->Draw("n20_3:a20_3_cal+a3 >> h3(300,1.,8,16,0,16)","n3==-1","BOX"); 

  c2->cd(4);
  ch->Draw("n20_4:a20_4_cal + a4 >> h4(300,1.,8,16,0,16)","n4==-1","BOX");
  // // // // c2->Print("/home/oem/Desktop/calibration4.png");

  return;
}

void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){
  TString line;
  ifstream myfile;
  Int_t count=-2;
  TString file = "/home/oem/work/software/AculUti/data/exp1904/" + fileName + ".cal";
  myfile.open(file.Data());
  if(!myfile.is_open()){
    cout << "no such file " << file.Data() << endl;
    return;
  } 
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