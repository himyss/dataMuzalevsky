void drawCuts(){
  Float_t parCsR2[16],parCsR1[16],par202[16],par201[16];
  ifstream myfile7;
  TString line7;
  Int_t count=-2;
  myfile7.open("/media/user/work/data/analysisexp1804/presentPars/csi_r_ec.clb");
  while (! myfile7.eof() ) {
    line7.ReadLine(myfile7);
    if(count < 0){
      count++;
      continue;
    }
    if(line7.IsNull()) break;
    sscanf(line7.Data(),"%g %g", parCsR1+count,parCsR2+count);
    count++;
  }  

  cout << endl << " pars for CsR strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parCsR1[i] << " " << parCsR2[i] << endl; 

  ifstream myfile5;
  TString line5;
  count=-2;
  myfile5.open("/media/user/work/data/analysisexp1804/presentPars/SQ20.cal");
  while (! myfile5.eof() ){
    line5.ReadLine(myfile5);
    if(count < 0){
      count++;
      continue;
    }
    if(line5.IsNull()) break;
    sscanf(line5.Data(),"%g %g", par201+count,par202+count);
    count++;
  }

  cout << endl << " pars for 20um strips" << endl;
  for(Int_t i=0;i<16;i++) cout << par201[i] << " " << par202[i] << endl; 


  TChain *t = new TChain("AnalysisxTree");
  t->Add("/media/user/work/data/exp1804/h5_14_00*.root");
  cout << t->GetEntries() << endl;


  TString gName,gDraw,gCut;
  TString gName1,gDraw1,gCut1;

  TGraph *g;

  // TCanvas *c1 = new TCanvas("c1","cuts",1800,1000);
  // c1->Divide(4,4);

  // for(Int_t i=0;i<16;i++){

  //   gName.Form("g%d",i+1);
  //   gDraw.Form("NeEvent.SQY_R[%d]:NeEvent.tSQY_R[%d]*0.3 - NeEvent.tF5[0]*0.125",i,i);
  //   gCut.Form("NeEvent.SQY_R[%d]>150",i);

  //   gDraw1.Form("NeEvent.SQY_R[%d]:NeEvent.tSQY_R[%d]*0.3 - NeEvent.tF5[0]*0.125",i,i);
  //   gCut1.Form("NeEvent.SQY_R[%d]>150 && NeEvent.tSQY_R[%d]*0.3 - NeEvent.tF5[0]*0.125 > -70 && NeEvent.tSQY_R[%d]*0.3 - NeEvent.tF5[0]*0.125<0",i,i,i);


  //   c1->cd(i+1);
  //   t->SetMarkerColor(kBlack);
  //   t->Draw(gDraw.Data(),gCut.Data(),"", 1000000, 0);

  //   t->SetMarkerColor(kRed);
  //   t->Draw(gDraw1.Data(),gCut1.Data(),"same", 1000000, 0);


  //   c1->Update();
  // }


  TCanvas *c1 = new TCanvas("c1","cuts",1800,1000);
  c1->Divide(4,4);

  for(Int_t i=0;i<16;i++){

    gName.Form("g%d",i+1);
    gDraw.Form("NeEvent.SQ20[%d]*%f+%f:NeEvent.tSQ20[%d]*0.3 - NeEvent.tF5[0]*0.125",i,par202[i],par201[i],i);
    gCut.Form("NeEvent.tSQ20[%d]>0 && NeEvent.tSQ20[%d]*0.3 - NeEvent.tF5[0]*0.125 > 0 && NeEvent.tSQ20[%d]*0.3 - NeEvent.tF5[0]*0.125<250",i,i,i);

    gDraw1.Form("NeEvent.SQ20[%d]*%f+%f:NeEvent.tSQ20[%d]*0.3 - NeEvent.tF5[0]*0.125",i,par202[i],par201[i],i);
    gCut1.Form("NeEvent.SQ20[%d]*%f+%f>1 && NeEvent.tSQ20[%d]>0 && NeEvent.tSQ20[%d]*0.3 - NeEvent.tF5[0]*0.125 > 30 && NeEvent.tSQ20[%d]*0.3 - NeEvent.tF5[0]*0.125<170",i,par202[i],par201[i],i,i,i);


    c1->cd(i+1);
    t->SetMarkerColor(kBlack);
    t->Draw(gDraw.Data(),gCut.Data(),"", 10000000, 0);

    t->SetMarkerColor(kRed);
    t->SetMarkerStyle(8);
    t->Draw(gDraw1.Data(),gCut1.Data(),"same", 10000000, 0);


    c1->Update();
  }




  // TCanvas *c1 = new TCanvas("c1","cuts",1800,1000);
  // c1->Divide(4,4);

  // for(Int_t i=0;i<16;i++){

  //   gName.Form("g%d",i+1);
  //   gDraw.Form("NeEvent.CsI_R[%d]*%f+%f:NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125",i,parCsR2[i],parCsR1[i],i);
  //   // gCut.Form("NeEvent.tCsI_R[%d]>0 && NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125 > 0 && NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125<250",i,i,i);
  //   gCut.Form("trigger==3 && NeEvent.CsI_R[%d]*%f+%f>0 && NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125>300 && NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125<600",i,parCsR2[i],parCsR1[i],i,i);

  //   gDraw1.Form("NeEvent.CsI_R[%d]*%f+%f:NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125",i,parCsR2[i],parCsR1[i],i);
  //   gCut1.Form("trigger==3 && NeEvent.CsI_R[%d]*%f+%f>0 && NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125>365 && NeEvent.tCsI_R[%d]*0.3 - NeEvent.tF5[0]*0.125<430",i,parCsR2[i],parCsR1[i],i,i);


  //   c1->cd(i+1);
  //   t->SetMarkerColor(kBlack);
  //   t->Draw(gDraw.Data(),gCut.Data(),"", 1000000, 0);
  //   // if(i>0) t->Draw(gDraw.Data(),gCut.Data(),"same", 1000000, 0);

  //   t->SetMarkerColor(kRed);
  //   // t->SetMarkerStyle(8);
  //   t->Draw(gDraw1.Data(),gCut1.Data(),"same", 1000000, 0);


  //   c1->Update();
  // }

  // t->Draw("(NeEvent.F5[0]+NeEvent.F5[1]+NeEvent.F5[2]+NeEvent.F5[3]+NeEvent.F3[0]+NeEvent.F3[1]+NeEvent.F3[2]+NeEvent.F3[3]):(NeEvent.tF5[0]+NeEvent.tF5[1]+NeEvent.tF5[2]+NeEvent.tF5[3] - NeEvent.tF3[0]-NeEvent.tF3[1]-NeEvent.tF3[2]-NeEvent.tF3[3])*0.25*0.125 + 89.165>>(200,100,200,200,1000,20000)","","",100000,0);
  


  // ->Draw("NeEvent.SQ20[7]:NeEvent.tSQ20[7]*0.3-NeEvent.F5[]*0.125","NeEvent.tSQ20[7]>0","", 741848, 0);
  return;
}