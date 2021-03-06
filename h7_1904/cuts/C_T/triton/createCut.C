#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);


Float_t NDpar[32],zeropar[32];
Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void createCut(){

  readPar("ND_tac",NDpar,zeropar,32);

  create_IDs();
  create_cuts();

  nCoins = 0;
  // readPar("CsI_anh",pCsI_1,pCsI_2);
  // readCuts();
  // return;
  gStyle->SetOptStat(0);
  Bool_t tritium = 1;
  Bool_t he3_1 = 0;
  Bool_t he3_2 = 0;
  Bool_t he3_3 = 0;
  Bool_t he3_4 = 0;
  Bool_t tCsI_s = 0;
  Bool_t target = 0;
  Bool_t centtimes = 0;
  Bool_t CsI_tracking = 0;
  Bool_t tSQ20 = 0;
  Bool_t tSQThick = 0;
  Bool_t neutronID = 0;
  Bool_t vetoAnalyse = 0;


  TChain *ch = new TChain("tree");
  // ch->Add("/mnt/data/exp1904/analysed/selected/h7_newBeamDet/h7_ct_*_cut.root");
  // ch->Add("/mnt/data/exp1904/analysed/selected/siTriggers/h7_ct_*_cut.root");
  // ch->Add("/mnt/data/exp1904/analysed/selected/h7_csIanalysis/h7_ct_*");
  ch->Add("/mnt/data/exp1904/analysed/reco/h7_csianalysis/h7_ct_*.root");
  cout << ch->GetEntries() << endl;


  TChain *ch1 = new TChain("tree");
  // ch1->Add("/mnt/data/exp1904/analysed/selected/h7/h7_*.root");
  ch1->Add("/mnt/data/exp1904/analysed/selected/h7_csIanalysis/h7_*.root");
  cout << ch1->GetEntries() << endl;
  
  TChain *ch_cal = new TChain("tree");
  // ch1->Add("/mnt/data/exp1904/analysed/selected/h7/h7_*.root");
  ch_cal->Add("/mnt/data/exp1904/analysed/cal/h7_veto/h7_*.root");
  cout << ch_cal->GetEntries() << endl;



  TString cutTriangle1("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4./7.))");
  TString cut,hdraw;

  if (neutronID) {


    TCanvas *cNeutron = new TCanvas("cNeutron","",1000,1000);  
    // cNeutron->Divide(2,2);
    ch->SetMarkerStyle(1);


    // ch->SetMarkerColor(kBlack);      
    // hdraw.Form("tacND+%lf:aND",NDpar[0]);
    // // hdraw.Form("X_C.:aCsI>>h%d",i);
    // // gPad->SetLogz();/
    // ch->Draw(hdraw.Data(),"","",20000000,0);

    // ch->SetMarkerColor(kRed);      
    // hdraw.Form("tacND+%lf:aND",NDpar[0]);
    // // hdraw.Form("X_C.:aCsI>>h%d",i);
    // // gPad->SetLogz();/
    // ch->Draw(hdraw.Data(),"neutron","same",20000000,0);
    // cNeutron->Update();

      ch->SetMarkerColor(1);      
      hdraw.Form("ND_tac[]:ND_amp[]");
      ch->Draw(hdraw.Data(),"ND_tac[]>0 && ND_amp[]>0","",1000000,0);
      cutNeutron->Draw(""); 
      cNeutron->Update();   

      ch->SetMarkerColor(kRed);      
      hdraw.Form("ND_tac[]:ND_amp[]");
      ch->Draw(hdraw.Data(),"ND_tac[]>0 && ND_amp[]>0 && neutron","same",1000000,0);
      cNeutron->Update();  


return;
      // ch->SetMarkerColor(kMagenta);  
      // ch->SetMarkerStyle(20);      
      // hdraw.Form("ND_tac[]:ND_amp[]");
      // cout << ch->Draw(hdraw.Data(),"ND_tac[]>0 && ND_amp[]>0 && neutron>0","same",10000000,0) << endl;
      // cutNeutron->Draw(""); 
      // cNeutron->Update(); 

      // ch->SetMarkerColor(kRed);      
      // hdraw.Form("ND_tac[]:ND_amp(610,-10,600,1000,-10,4100)[]");
      // cout << ch->Draw(hdraw.Data(),"neutron==1 && ND_tac[]>0 && ND_amp(610,-10,600,1000,-10,4100)[]>0","same") << endl;
      // cNeutron->Update();

      // ch->SetMarkerColor(kGreen);      
      // ch->SetMarkerStyle(8);
      // hdraw.Form("ND_tac[]:ND_amp(610,-10,600,1000,-10,4100)[]");
      // cout << ch->Draw(hdraw.Data(),"neutron>1 && ND_tac[]>0 && ND_amp(610,-10,600,1000,-10,4100)[]>0","same") << endl;
      // cNeutron->Update();


    // }




    // ch->SetMarkerColor(kGreen); 
    // ch->SetMarkerStyle(20);     
    // hdraw.Form("tacND:aND");
    // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
    // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
    // // cut += " && " + cutTriangle1;
    // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
    // cut += " && neutron";
    // cout << ch1->Draw(hdraw.Data(),cut.Data(),"same") << endl;

    // gPad->SetLogz();
    cNeutron->Update();


  }


  if (tCsI_s) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);
    for(Int_t i=0;i<16;i++) {

      c1->cd(i+1);

      ch->SetMarkerColor(kBlack);      
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5>>h%d",i,i,i);
      cut.Form("nCsI_track==%d && trCsI[%d]-tF5>200 && trCsI[%d]-tF5<600",i,i,i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      // gPad->SetLogz();/
      ch->Draw(hdraw.Data(),cut.Data(),"",500000,0);
      // gPad->SetLogz();
      c1->Update();


      ch->SetMarkerColor(kRed);      
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5>>h_cut%d",i,i,i);
      cut.Form("flagCent && nCsI_track==%d && trCsI[%d]-tF5>200 && trCsI[%d]-tF5<600",i,i,i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      // gPad->SetLogz();/
      ch->Draw(hdraw.Data(),cut.Data(),"same",500000,0);
      // gPad->SetLogz();
      c1->Update();


      // CsI_cut[i]->SetLineWidth(1);
      // CsI_cut[i]->SetLineColor(kRed);
      // CsI_cut[i]->Draw("same");
      c1->Update();

    }
  }

  if (tritium) {

  TString cutTriangle1("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4./7.))");

  TCanvas *c3h = new TCanvas("c3h","",1000,1000);  
  
  ch1->SetMarkerStyle(1);
  // c3h->Divide(4,4);
  // for(Int_t i=0;i<16;i++) {
    Int_t i = 15;
    // c3h->cd(i+1);  
    ch->SetMarkerStyle(1);
    cut.Form("nCsI_track==%d && X_C<25 && flagCent",i);
    
    ch->SetMarkerColor(kBlack);
    hdraw.Form("X_C:arCsI[%d] >>(500,0,140,500,0,25)",i);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    c3h->Update();


    cut.Form("nCsI_track==%d && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
    // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
    cut += " && " + cutTriangle1;
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
    ch->SetMarkerStyle(20);
    ch->SetMarkerColor(kRed);
    hdraw.Form("X_C:arCsI[%d]",i);
    ch->Draw(hdraw.Data(),cut.Data(),"same");
    c3h->Update();

    // cut3h[i]->SetLineColor(kBlue);
    // cut3h[i]->Draw();
    c3h->Update();

    // c3h->SaveAs("triton0.root");
  // }

    return;

 
    //   c3h->cd(2);
    // // Int_t i = 10;  
    //   cut.Form("nCsI_track==%d && flagCent",i,i);
    //   // Int_t i = 3;
    //   // cut.Form("nCsIflagCent",i);

    //   ch1->SetLineColor(kBlack);
    //   hdraw.Form("arCsI[%d] >>h%d_cut1(1000,0,120)",i,i);
    //   // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
    //   ch1->Draw(hdraw.Data(),cut.Data(),"",5660651,0);
    //   c3h->Update();


    //   ch1->SetLineColor(kRed);
    //   hdraw.Form("arCsI[%d]",i,i);
    //   // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
    //   ch1->Draw(hdraw.Data(),cut.Data(),"same",5660651,5660651);
    //   c3h->Update();

    //   ch1->SetLineColor(kGreen);
    //   hdraw.Form("arCsI[%d]",i,i);
    //   // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
    //   ch1->Draw(hdraw.Data(),cut.Data(),"same",5660651,11321302);
    //   c3h->Update();

    //   ch1->SetLineColor(kBlue);
    //   hdraw.Form("arCsI[%d]",i,i);
    //   // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
    //   ch1->Draw(hdraw.Data(),cut.Data(),"same",5660651,16981953);
    //   c3h->Update();




/*    TCanvas *c3h = new TCanvas("c3h","",1000,1000);  
    ch->SetMarkerStyle(20);
    ch->SetMarkerSize(0.7);
    c3h->Divide(2,1);
    // for(Int_t i=0;i<16;i++) {
    //   c3h->cd(i+1);
    {
      c3h->cd(1);

      Int_t i = 10;  
    // Int_t i = 10;  
      cut.Form("nCsI_track==%d && flagCent",i,i);
      // Int_t i = 3;
      // cut.Form("nCsIflagCent",i);
      ch->SetMarkerStyle(1);

      ch->SetMarkerColor(kBlack);
      hdraw.Form("X_C:arCsI[%d] >>h%d_cut(1000,0,120,500,0,30)",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"",5660651,0);
      c3h->Update();

      ch->SetMarkerColor(kRed);
      hdraw.Form("X_C:arCsI[%d]",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same",5660651,5660651);
      c3h->Update();

      ch->SetMarkerColor(kGreen);
      hdraw.Form("X_C:arCsI[%d]",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same",5660651,11321302);
      c3h->Update();


      ch->SetMarkerColor(kBlue);
      hdraw.Form("X_C:arCsI[%d]",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch->Draw(hdraw.Data(),cut.Data(),"same",5660651,16981953);
      c3h->Update();

 
      c3h->cd(2);
    // Int_t i = 10;  
      cut.Form("nCsI_track==%d && flagCent",i,i);
      // Int_t i = 3;
      // cut.Form("nCsIflagCent",i);

      ch1->SetMarkerColor(kBlack);
      hdraw.Form("X_C:arCsI[%d] >>h%d_cut1(1000,0,120,500,0,30)",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"",5660651,0);
      c3h->Update();


      ch1->SetMarkerColor(kRed);
      hdraw.Form("X_C:arCsI[%d]",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"same",5660651,5660651);
      c3h->Update();

      ch1->SetMarkerColor(kGreen);
      hdraw.Form("X_C:arCsI[%d]",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"same",5660651,11321302);
      c3h->Update();

      ch1->SetMarkerColor(kBlue);
      hdraw.Form("X_C:arCsI[%d]",i,i);
      // hdraw.Form("X_C:arCsI[%d] >> (1000,0,120,1000,0.q,25)",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"same",5660651,16981953);
      c3h->Update();*/


return;

      // for(Int_t i=0;i<16;i++) {

      //   ch->SetMarkerColor(kGreen);
      //   hdraw.Form("X_C:arCsI[%d]",i);
      //   cut.Form("nCsI_track==%d && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
      //   cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
      //   cut += " && " + cutTriangle1;
      //   cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
      //   cout << ch->Draw(hdraw.Data(),cut.Data(),"same") << endl;
      //   c3h->Update();

      // }
      // ch->SetMarkerSize(1.2);
      // for(Int_t i=0;i<16;i++) {

      //   ch->SetMarkerColor(kRed);
      //   hdraw.Form("X_C:arCsI[%d]",i);
      //   cut.Form("nCsI_track==%d && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
      //   cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
      //   cut += " && " + cutTriangle1;
      //   cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
      //   cut += " && 1000*(mh7-4*0.939565-2.808920)<3.5";
      //   cout << ch->Draw(hdraw.Data(),cut.Data(),"same") << endl;
      //   c3h->Update();

      // }


      // ch1->SetMarkerStyle(1);
      // ch1->SetMarkerColor(kRed);
      // // hdraw.Form("X_C:arCsI[%d] >>h%d_cut(1000,0,120,500,0,30)",i,i);
      // hdraw.Form("X_C:arCsI[%d]",i);
      // ch1->Draw(hdraw.Data(),cut.Data(),"same",26885700, 26885700);
      // c3h->Update();

      // ch1->SetMarkerStyle(1);
      // ch1->SetMarkerColor(kGreen);
      // // hdraw.Form("X_C:arCsI[%d] >>h%d_cut(1000,0,120,500,0,30)",i,i);
      // hdraw.Form("X_C:arCsI[%d]",i);
      // ch1->Draw(hdraw.Data(),cut.Data(),"same",26885700, 53771400);
      // c3h->Update();

      // ch1->SetMarkerStyle(1);
      // ch1->SetMarkerColor(kBlue);
      // // hdraw.Form("X_C:arCsI[%d] >>h%d_cut(1000,0,120,500,0,30)",i,i);
      // hdraw.Form("X_C:arCsI[%d]",i);
      // ch1->Draw(hdraw.Data(),cut.Data(),"same",26885700, 80657100);
      // c3h->Update();

      // ch->SetMarkerColor(kRed);
      // ch->SetMarkerStyle(7);
      // // cut.Form("nCsI_track==%d && flagCent && X_C<30 && arCsI[%d]<120",i,i);
      // cut.Form("nCsI_track==%d && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
      // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
      // cut += " && " + cutTriangle1;
      // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
      // cout << ch->Draw(hdraw.Data(),cut.Data(),"same") << endl;
      // c3h->Update();

      // c3h->Update();
      //  cut3h[i]->SetLineColor(kRed);
      // cut3h[i]->Draw();
      // c3h->Update();
    // }
      // return;
//     for(Int_t i=0;i<16;i++) {
//       cut.Form("nCsI_track==%d && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
//       cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//       cut += " && " + cutTriangle1;
//       cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
//       ch->SetMarkerStyle(8);
//       ch->SetMarkerColor(kRed);
//       hdraw.Form("X_C:arCsI[%d]",i,i);
//       cout << ch->Draw(hdraw.Data(),cut.Data(),"same") << endl;
//       c3h->Update();
//     }

      // ch->SetMarkerStyle(20);
      // ch->SetMarkerColor(kRed);
      // cut.Form("nCsI_track==%d && flagCent && nh2 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )",i);
      // hdraw.Form("X_C:arCsI[%d]",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();
    
    // }
 
    // c3h->Print("/home/muzalevskii/Desktop/figures/ID_cent.png");

  }

  if (target) {
    TCanvas *c4 = new TCanvas("c4","target cut",1000,1000);  
    cout << ch->Draw("fYt:fXt>>h_target(100,-30,30,100,-30,30)","nCsI>-1 && X_C>0","col") << endl;

    ch->SetMarkerColor(kRed);
    ch->Draw("fYt:fXt>>h_targetCut(100,-30,30,100,-30,30)","nCsI>-1 && X_C>0 && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<9*9","same");
  }

  if (centtimes) {
    TCanvas *c3h = new TCanvas("c3h","",1800,1000);  
    c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      c3h->cd(i+1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("nX_C==%d && trigger!=1",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      c3h->Update();
      
      ch->SetMarkerColor(kRed);      
      cut.Form("nX_C==%d && flagCent",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d_cut",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch->Draw(hdraw.Data(),cut.Data(),"same",1000000,0);
      c3h->Update();

      dssd_x_cut[i]->SetLineColor(kRed);
      dssd_x_cut[i]->Draw("same");


      c3h->Update();
    }
  }

  if (he3_1) {

//     TCanvas *c_ampVeto = new TCanvas("c_ampVeto","",1800,1000);
//     c_ampVeto->Divide(2,2);

//     c_ampVeto->cd(1);      
//     cut.Form("flag1 && a1_1+a20_1_un<65 && a20_1<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_1==1";
//     hdraw.Form("av_1 >> h_amp1(1000,900,1900)");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c_ampVeto->Update();

//     c_ampVeto->cd(2);      
//     cut.Form("flag2 && a1_2+a20_2_un<65 && a20_2<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_2==1";
//     hdraw.Form("av_2 >> h_amp2(1000,900,1900)");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c_ampVeto->Update();

//     c_ampVeto->cd(3);      
//     cut.Form("flag3 && a1_3+a20_3_un<65 && a20_3<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_3==1";
//     hdraw.Form("av_3 >> h_amp3(1000,900,1900)");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c_ampVeto->Update();

//     c_ampVeto->cd(4);      
//     cut.Form("flag4 && a1_4+a20_4_un<65 && a20_4<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_4==1";
//     hdraw.Form("av_4 >> h_amp4(1000,900,1900)");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c_ampVeto->Update();
// // return;

//     TCanvas *c1 = new TCanvas("c1","",1800,1000);
//     c1->Divide(2,2);

//     c1->cd(1);      
//     cut.Form("flag1 && a1_1+a20_1_un<65 && a20_1<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_1>0";
//     hdraw.Form("off_multv_1");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c1->Update();

//     c1->cd(2);      
//     cut.Form("flag2 && a1_2+a20_2_un<65 && a20_2<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_2>0";
//     hdraw.Form("off_multv_2");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c1->Update();

//     c1->cd(3);      
//     cut.Form("flag3 && a1_3+a20_3_un<65 && a20_3<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_3>0";
//     hdraw.Form("off_multv_3");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c1->Update();

//     c1->cd(4);      
//     cut.Form("flag4 && a1_4+a20_4_un<65 && a20_4<8");
//     cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9 && off_multv_4>0";
//     hdraw.Form("off_multv_4");
//     ch->Draw(hdraw.Data(),cut.Data(),"");
//     c1->Update();


    TCanvas *c3h_1 = new TCanvas("c3h_1","",1800,1000);
    c3h_1->Divide(2,2);
    // TString canName;
    // TCanvas *c_arr[16];
    // for(Int_t i=0;i<16;i++){
    //   canName.Form("cHe3_1_%d",i+1);
    //   c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    // }

    // c3h->Divide(4,4);
    // for(Int_t i=0;i<16;i++) { 
    
    Int_t i=0;
      // c_arr->cd(i+1);
    c3h_1->cd(1);
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);      
    cut.Form("flag1 && a1_1+a20_1_un<65 && a20_1<8 && off_multv_1==0",i);
    cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
    hdraw.Form("a20_1:a1_1+a20_1_un>>h%d1(1000,1,40,1000,0.,8)",i);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    c3h_1->Update();

    c3h_1->cd(2);
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);      
    // cut.Form("flag2 && a1_2+a20_2_un<65 && a20_2<8 && off_multv_2==0",i);
    cut.Form("flag2 && off_multv_2==0",i);
    cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
    cut += " && n20_2>4 && n20_2<10 && n1_2>4 && n1_2<10";
    hdraw.Form("a20_2:a1_2+a20_2_un>>h%d2(1000,1,40,1000,0.,8)",i);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    c3h_1->Update();
return;
    c3h_1->cd(3);
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);      
    cut.Form("flag3 && a1_3+a20_3_un<65 && a20_3<8 && off_multv_3==0",i);
    cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
    hdraw.Form("a20_3:a1_3+a20_3_un>>h%d3(1000,1,40,1000,0.,8)",i);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    c3h_1->Update();

    c3h_1->cd(4);
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);      
    cut.Form("flag4 && a1_4+a20_4_un<65 && a20_4<8 && off_multv_4==0",i);
    cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
    hdraw.Form("a20_4:a1_4+a20_4_un>>h%d4(1000,1,40,1000,0.,8)",i);
    ch->Draw(hdraw.Data(),cut.Data(),"col");
    c3h_1->Update();
    // return;
    // c_arr[i]->Update();
    // c_ar/r[i]->Update();
    // c3h

      // ch->SetMarkerStyle(20);
      // ch->SetMarkerSize(0.7);   
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1",i);
      // cut += " && nhe3_1";
      // hdraw.Form("a20_1:a1_1+a20_1_un>>h%d_he31",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h_1->Update();


      // c_arr[i]->Update();

      // ch->SetMarkerStyle(4);
      // ch->SetMarkerSize(1.2);    
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1",i);
      // cut += " && nhe3_1";
      // hdraw.Form("a20_1:a1_1+a20_1_un>>h%d_he31",i);
      // ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c_arr[i]->Update();

      // ch->SetMarkerStyle(20);
      // ch->SetMarkerSize(1);
      // ch->SetMarkerColor(kRed);      
      // // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      // cut += " && nhe3_1 && a1_1<20";
      // hdraw.Form("a20_1:a1_1>>h%d1_coin(100,1,30,100,0.5,5)",i);
      // // hdraw.Form("X_C.:aCsI>>h%d",i);
      // nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // // c3h->Update();

    //   cuthe3_1[i]->SetLineColor(kRed);
    //   cuthe3_1[i]->Draw("same");
    //   c_arr[i]->Update();
    //   c_arr[i]->Update();

    //   TString printName;
    //   printName.Form("/home/muzalevskii/Desktop/figures/de_E_1_%d_dead.png",i);
    //   c_arr[i]->Print(printName.Data());
    //   // c3h->Update();
    // }
    
    // c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_1.pdf");
    // c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_1.pdf[");
    // c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_1.pdf");
    // for(Int_t i=1;i<15;i++) {
    //   c_arr[i]->Print("/home/muzalevskii/Desktop/de_E_1.pdf");
    // }
    // c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_1.pdf");
    // c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_1.pdf]");
  }

  if (he3_2) {
    TCanvas *c3h_2 = new TCanvas("c3h_2","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_2_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("flag2 && a1_2+a20_2_un<65 && a20_2<8 && n20_2==%d",i);
      hdraw.Form("a20_2:a1_2+a20_2_un>>h%d1",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();


      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);  
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_2";
      hdraw.Form("a20_2:a1_2+a20_2_un",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_2[i]->SetLineWidth(1);
      cuthe3_2[i]->SetLineColor(kRed);
      cuthe3_2[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }

    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_2.pdf");
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_2.pdf[");
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_2.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/muzalevskii/Desktop/de_E_2.pdf");
    }
    c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_2.pdf");
    c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_2.pdf]");
  }

   if (he3_3) {
    TCanvas *c3h = new TCanvas("c3h_3","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_3_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("flag3 && a1_3+a20_3_un<65 && a20_3<8 && n20_3==%d",i);
      hdraw.Form("a20_3:a1_3+a20_3_un>>h%d1",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();

      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_3";
      hdraw.Form("a20_3:a1_3+a20_3_un",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_3[i]->SetLineWidth(1);
      cuthe3_3[i]->SetLineColor(kRed);
      cuthe3_3[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_3.pdf");
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_3.pdf[");
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_3.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/muzalevskii/Desktop/de_E_3.pdf");
    }
    c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_3.pdf");
    c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_3.pdf]");
  }

  if (he3_4) {
    TCanvas *c3h = new TCanvas("c3h_4","",1800,1000);

    TString canName;
    TCanvas *c_arr[16];
    for(Int_t i=0;i<16;i++){
      canName.Form("cHe3_4_%d",i+1);
      c_arr[i] = new TCanvas(canName.Data(),"title",1800,1000);
    }

    // c3h->Divide(4,4);
    for(Int_t i=0;i<16;i++) {
      // c3h->cd(i+1);
      c_arr[i]->cd();
      ch->SetMarkerStyle(1);
      ch->SetMarkerColor(kBlack);      
      cut.Form("flag4 && a1_4+a20_4_un<65 && a20_4<8 && n20_4==%d",i);
      hdraw.Form("a20_4:a1_4+a20_4_un>>h%d1",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();


      ch->SetMarkerStyle(20);
      ch->SetMarkerSize(0.7);
      ch->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_4";
      hdraw.Form("a20_4:a1_4+a20_4_un",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_4[i]->SetLineWidth(1);
      cuthe3_4[i]->SetLineColor(kRed);
      cuthe3_4[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_4.pdf");
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_4.pdf[");
    c_arr[0]->Print("/home/muzalevskii/Desktop/de_E_4.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/muzalevskii/Desktop/de_E_4.pdf");
    }
    c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_4.pdf");
    c_arr[15]->Print("/home/muzalevskii/Desktop/de_E_4.pdf]");
  }


  if (CsI_tracking) {



    // TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    // c1->Divide(4,4);
    // for(Int_t i=0;i<16;i++) {

    //   c1->cd(i+1);

    //   ch->SetMarkerColor(kBlack);      
    //   hdraw.Form("");
    //   cut.Form("nCsI_track==%d",i);
    //   ch->Draw("xCt",cut.Data(),"");
    //   // gPad->SetLogz();
    //   c1->Update();

    // }  


    // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
    // c2->Divide(4,4);
    // for(Int_t i=0;i<16;i++) {

    //   c2->cd(i+1);

    //   ch->SetMarkerColor(kBlack);      

    //   cut.Form("nCsI_track==%d",i);
    //   ch->Draw("yCt",cut.Data(),"");
    //   // gPad->SetLogz();
    //   c2->Update();

    // } 

    TCanvas *c3 = new TCanvas("c3","",1800,1000);
    ch->Draw("nCsI-nCsI_track","flagCent","");

  }


  if (tSQ20) {

    TCanvas *c_sq20 = new TCanvas("c_sq20","",1000,1800);
    c_sq20->Divide(2,1);

    c_sq20->cd(1);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a20_4:t20_4-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a20_4:t20_4-tF5","flag4","same",1000000,0);

    c_sq20->cd(2);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a1_4:t1_4-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a1_4:t1_4-tF5","flag4","same",1000000,0);

return;

    c_sq20->cd(2);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a20_2:t20_2-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a20_2:t20_2-tF5","flag2","same",1000000,0);

    c_sq20->cd(3);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a20_3:t20_3-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a20_3:t20_3-tF5","flag3","same",1000000,0);

    c_sq20->cd(4);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a20_4:t20_4-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a20_4:t20_4-tF5","flag4","same",1000000,0);
  }

  if (tSQThick) {

    TCanvas *c_sqthick = new TCanvas("c_sqthick","",1000,1800);
    c_sqthick->Divide(2,2);

    c_sqthick->cd(1);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a1_1:t1_1-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a1_1:t1_1-tF5","flag1","same",1000000,0);

    c_sqthick->cd(2);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a1_2:t1_2-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a1_2:t1_2-tF5","flag2","same",1000000,0);

    c_sqthick->cd(3);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a1_3:t1_3-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a1_3:t1_3-tF5","flag3","same",1000000,0);

    c_sqthick->cd(4);
    ch->SetMarkerColor(kBlack);
    ch->Draw("a1_4:t1_4-tF5","","",1000000,0);

    ch->SetMarkerColor(kRed);
    ch->Draw("a1_4:t1_4-tF5","flag4","same",1000000,0);
    c_sqthick->Update();
  }

  if (vetoAnalyse) {
    cout << " asdasd " << endl;
      TCanvas *c_veto = new TCanvas("c_veto","",1800,1000);
      c_veto->Divide(2,2);

      // c_veto->cd(1);
      // ch->SetMarkerStyle(1);
      // ch->SetMarkerColor(kBlack);      
      // cut.Form("trigger==2 && flag1 && a1_1+a20_1_un<65 && a20_1<8 && multv_1==0 && !flagCent");
      // hdraw.Form("a20_1:a1_1+a20_1_un>>hveto1(500,0,70,500,0,7)");
      // ch->Draw(hdraw.Data(),cut.Data(),"col");
      // c_veto->Update();

      // c_veto->cd(2);     
      // cut.Form("trigger==3 && flag2 && a1_2+a20_2_un<65 && a20_2<8 && multv_2==0 && !flagCent");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
      // hdraw.Form("a20_2:a1_2+a20_2_un>>hveto2(500,0,70,500,0,7)");
      // ch->Draw(hdraw.Data(),cut.Data(),"col");
      // c_veto->Update();

      // c_veto->cd(3);   
      // cut.Form("trigger==4 && flag3 && a1_3+a20_3_un<65 && a20_3<8 && multv_3==0 && !flagCent");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
      // hdraw.Form("a20_3:a1_3+a20_3_un>>hfveto3(500,0,70,500,0,7)");
      // ch->Draw(hdraw.Data(),cut.Data(),"col");
      // c_veto->Update();

      // c_veto->cd(4);      
      // cut.Form("trigger==5 && flag4 && a1_4+a20_4_un<65 && a20_4<8 && multv_4==0 && !flagCent");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
      // hdraw.Form("a20_4:a1_4+a20_4_un>>hveto4(500,0,70,500,0,7)");
      // ch->Draw(hdraw.Data(),cut.Data(),"col");
      // c_veto->Update();

      // TCanvas *c_veto = new TCanvas("c_veto","",1800,1000);
      // c_veto->Divide(2,2);

      // ch_cal->SetMarkerStyle(1);
      // ch_cal->SetMarkerColor(kBlack); 

      
      // // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";

      c_veto->cd(1);
      // hdraw.Form("off_multv_1:SSD_V1[7]>>hveto1(150,-10,140)");
      hdraw.Form("off_multv_1:SSD_V1[7]");
      // hdraw.Form("off_multv_2:SSD_V2");
      hdraw.Form("off_multv_2");
      cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V1[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      ch->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      c_veto->Update();


      c_veto->cd(2);
      // hdraw.Form("SSD_V2[7]>>hveto2(150,-10,140)");
      // hdraw.Form("SSD_V2[7]");
      hdraw.Form("SSD_V2");
      cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V2[7]>0";
      // cut += " && SSD_V2[7]>20";
      cut += " && off_multv_2==0";
      ch->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      c_veto->Update();
return;
// return;

      // c_veto->cd(3);
      // hdraw.Form("SSD_V3[7]>>hveto3(150,-10,140)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V3[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      // c_veto->Update();

      // c_veto->cd(4);
      // hdraw.Form("SSD_V4[7]>>hveto4(150,-10,140)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V4[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      // c_veto->Update();

// return;
      // TCanvas *c_veto_s = new TCanvas("c_veto_s","",1800,1000);
      // c_veto_s->Divide(2,2);

      // ch_cal->SetMarkerStyle(1);
      // ch_cal->SetMarkerColor(kBlack); 

      
      // // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";

      // c_veto_s->cd(1);
      // hdraw.Form("SSD_V1[7]>>hveto1_s(1000,-10,4100)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V1[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      // c_veto_s->Update();


      // c_veto_s->cd(2);
      // hdraw.Form("SSD_V2[7]>>hveto2_s(1000,-10,4100)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V2[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      // c_veto_s->Update();

      // c_veto_s->cd(3);
      // hdraw.Form("SSD_V3[7]>>hveto3_s(1000,-10,4100)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V3[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      // c_veto_s->Update();

      // c_veto_s->cd(4);
      // hdraw.Form("SSD_V4[7]>>hveto4_s(1000,-10,4100)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && tSSD_V4[7]>0";
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
      // c_veto_s->Update();

      
      // TCanvas *c_veto_full = new TCanvas("c_veto_full","",1800,1000);
      // c_veto_full->Divide(2,2);

      // ch_cal->SetMarkerStyle(1);
      // ch_cal->SetMarkerColor(kBlack); 

      // c_veto_full->cd(1);
      // hdraw.Form("SSD_V1[7]>>hveto1_full(400,-10,390)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");

      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      // c_veto_full->Update();


      // c_veto_full->cd(2);
      // hdraw.Form("SSD_V2[7]>>hveto2_full(400,-10,390)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");

      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      // c_veto_full->Update();

      // c_veto_full->cd(3);
      // hdraw.Form("SSD_V3[7]>>hveto3_full(400,-10,390)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");

      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      // c_veto_full->Update();

      // c_veto_full->cd(4);
      // hdraw.Form("SSD_V4[7]>>hveto4_sfull(1000,-10,390)");
      // cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");

      // ch_cal->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      // c_veto_full->Update();

// return;




      // c_veto->cd(1);
      // hdraw.Form("SSD_V1:tSSD_V1>>hveto1(610,-10,600,200,-10,190)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"col",1000000,0);
      // c_veto->Update();


      // c_veto->cd(2);
      // hdraw.Form("SSD_V2:tSSD_V2>>hveto2(610,-10,600,200,-10,190)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"col",1000000,0);
      // c_veto->Update();

      // c_veto->cd(3);
      // hdraw.Form("SSD_V3:tSSD_V3>>hveto3(610,-10,600,200,-10,190)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"col",1000000,0);
      // c_veto->Update();

      // c_veto->cd(4);
      // hdraw.Form("SSD_V4:tSSD_V4>>hveto4(610,-10,600,200,-10,190)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"col",1000000,0);
      // c_veto->Update();

      return;


      TCanvas *c_veto_amp = new TCanvas("c_veto_amp","",1800,1000);
      c_veto_amp->Divide(4,4);

      
      ch_cal->SetMarkerStyle(1);
      ch_cal->SetMarkerColor(kBlack); 

      cut.Form("((fXt)*(fXt) + (fYt)*(fYt))<9*9");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";

      c_veto_amp->cd(1);
      hdraw.Form("SSD_V1[0]:tSSD_V1[0]>>hveto0_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(2);
      hdraw.Form("SSD_V1[1]:tSSD_V1[1]>>hveto1_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(3);
      hdraw.Form("SSD_V1[2]:tSSD_V1[2]>>hveto2_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(4);
      hdraw.Form("SSD_V1[3]:tSSD_V1[3]>>hveto3_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(5);
      hdraw.Form("SSD_V1[4]:tSSD_V1[4]>>hveto4_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(6);
      hdraw.Form("SSD_V1[5]:tSSD_V1[5]>>hveto5_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(7);
      hdraw.Form("SSD_V1[6]:tSSD_V1[6]>>hveto6_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(8);
      hdraw.Form("SSD_V1[7]:tSSD_V1[7]>>hveto7_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();            

      c_veto_amp->cd(9);
      hdraw.Form("SSD_V1[8]:tSSD_V1[8]>>hveto8_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(10);
      hdraw.Form("SSD_V1[9]:tSSD_V1[9]>>hveto9_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(11);
      hdraw.Form("SSD_V1[10]:tSSD_V1[10]>>hveto10_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(12);
      hdraw.Form("SSD_V1[11]:tSSD_V1[11]>>hveto11_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(13);
      hdraw.Form("SSD_V1[12]:tSSD_V1[12]>>hveto12_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(14);
      hdraw.Form("SSD_V1[13]:tSSD_V1[13]>>hveto13_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(15);
      hdraw.Form("SSD_V1[14]:tSSD_V1[14]>>hveto14_amp(610,-10,600,1000,-10,4100)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      c_veto_amp->cd(16);
      hdraw.Form("SSD_V1[15]:tSSD_V1[15]>>hveto15_amp(610,-10,600,100,-2,10)");
      ch_cal->Draw(hdraw.Data(),cut.Data(),"",100000,0);
      c_veto_amp->Update();

      // c_veto_amp->cd(2);     
      // cut.Form("flag2 && a1_2+a20_2_un<65 && a20_2<8 && multv_2==0");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
      // hdraw.Form("SSD_V2:tSSD_V2>>hveto2_amp(610,-10,600,1000,-10,4100)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"");
      // c_veto_amp->Update();

      // c_veto_amp->cd(3);   
      // cut.Form("flag3 && a1_3+a20_3_un<65 && a20_3<8 && multv_3==0");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
      // hdraw.Form("SSD_V3:tSSD_V3>>hfveto3_amp(610,-10,600,1000,-10,4100)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"");
      // c_veto_amp->Update();

      // c_veto_amp->cd(4);      
      // cut.Form("flag4 && a1_4+a20_4_un<65 && a20_4<8 && multv_4==0");
      // cut += " && ((fXt)*(fXt) + (fYt)*(fYt))<9*9";
      // hdraw.Form("SSD_V4:tSSD_V4>>hveto4_amp(610,-10,600,1000,-10,4100)");
      // ch_cal->Draw(hdraw.Data(),cut.Data(),"");
      // c_veto_amp->Update();

  }

}


void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=0;
  TString file = "/home/muzalevskii/work/macro/h7_1904/parameters/" + fileName + ".cal";
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

