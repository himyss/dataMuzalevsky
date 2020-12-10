#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_IDs.C"
#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_dE_ToF.C"

void readCuts();
void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16);


Float_t NDpar[32],zeropar[32];
Float_t pCsI_1[16],pCsI_2[16];

Int_t nCoins;

void create_cut(){

  // readPar("ND_tac",NDpar,zeropar,32);

  create_dE_ToF();
  create_IDs();
  create_cuts();

  nCoins = 0;
  // readPar("CsI_anh",pCsI_1,pCsI_2);
  // readCuts();
  // return;
  gStyle->SetOptStat(0);
  Bool_t tritium = 0;
  Bool_t he3_1 = 1;
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
  Bool_t neutrons = 0;
  Bool_t vetoAnalyse = 0;


  TChain *ch = new TChain("tree");
  // ch->Add("/mnt/data/exp1904/analysed/selected/h7_newBeamDet/h7_ct_*_cut.root");
  // ch->Add("/mnt/data/exp1904/analysed/selected/siTriggers/h7_ct_*_cut.root");
  // ch->Add("/mnt/data/exp1904/analysed/selected/h7_csIanalysis/h7_ct_*");
  // ch->Add("/mnt/data/exp1904/analysed/reco/h7_csianalysis/h7_ct_*.root");
  //ch->Add("/mnt/data/exp1904/analysed/selected/h7_csIanalysis/h7_ct_*_cut.root");

  ch->Add("/media/ivan/data/exp1904/analysed/selected/noTargetSelection/h7_ct_*");
  cout << ch->GetEntries() << endl;

  TChain *ch1 = new TChain("tree");
  ch1->Add("/media/ivan/data/exp1904/analysed/reco/h7_nov2020/h7_ct*");
  cout << ch1->GetEntries() << endl;

  TChain *ch_cal = new TChain("tree");
  // ch1->Add("/mnt/data/exp1904/analysed/selected/h7/h7_*.root");
  // ch_cal->Add("/mnt/data/exp1904/analysed/cal/h7_veto/h7_*.root");
  // cout << ch_cal->GetEntries() << endl;



  TString cutTriangle1("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4./7.))");
  TString cut,hdraw;

  if (neutronID) {


    // TCanvas *c_id_clb = new TCanvas("c_id_clb","",1000,1000);  

    // c_id_clb->cd();
    // ch->Draw("F5+F3:tF5-tF3>>(500,30,110,10000,0,30000)","","col");
    // c_id_clb->Update();

    TCanvas *c_clb_times = new TCanvas("c_clb_times","",1000,1000);  
    c_clb_times->Divide(2,2);

    c_clb_times->cd(1);
    ch->Draw("ND_time[18]-diafTime>>(200,-285,-250)","ND_amp[18]>0 && n9Li");
    c_clb_times->Update();

    ch->SetLineColor(kRed);
    ch->Draw("ND_time[18]-diafTime","n9Li && neutron && ND_amp[18]>0 ","same");
    c_clb_times->Update();

    c_clb_times->cd(2);
    ch->SetLineColor(kBlue);
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);
    ch->Draw("ND_tac[18]:ND_amp[18]","ND_amp[18]>0");
    c_clb_times->Update();    

    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kRed);
    ch->Draw("ND_tac[18]:ND_amp[18]","neutron && ND_amp[18]>0","same");
    c_clb_times->Update(); 

    c_clb_times->cd(3);
    ch->Draw("ND_time[18]-diafTime >> timeZoom(1000,-285,-250)","n9Li && ND_amp[18]>0 ");
    c_clb_times->Update();

    ch->SetLineColor(kRed);
    ch->Draw("ND_time[18]-diafTime","n9Li && neutron && ND_amp[18]>0","same");
    c_clb_times->Update();


    c_clb_times->cd(4);
    ch1->SetLineColor(kBlue);
    ch1->Draw("ND_time[18]*0.125-diafTime>> timeEXP(1000,-290,-250)","ND_amp[18]>0","");
    c_clb_times->Update();

    ch1->SetLineColor(kRed);
    ch1->Draw("ND_time[18]*0.125-diafTime","neutron && ND_time[18]>0","same");
    c_clb_times->Update();


  }


  if (tCsI_s) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(4,4);
    for(Int_t i=0;i<16;i++) {

      c1->cd(i+1);

      ch1->SetMarkerColor(kBlack);      
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5>>h%d",i,i,i);
      cut.Form("nCsI_track==%d && trCsI[%d]-tF5>200 && trCsI[%d]-tF5<600",i,i,i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      // gPad->SetLogz();/
      ch1->Draw(hdraw.Data(),cut.Data(),"",500000,0);
      // gPad->SetLogz();
      c1->Update();


      ch1->SetMarkerColor(kRed);      
      hdraw.Form("arCsI[%d]:trCsI[%d]-tF5>>h_cut%d",i,i,i);
      cut.Form("flagCent && nCsI_track==%d && trCsI[%d]-tF5>200 && trCsI[%d]-tF5<600",i,i,i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      // gPad->SetLogz();/
      ch1->Draw(hdraw.Data(),cut.Data(),"same",500000,0);
      // gPad->SetLogz();
      c1->Update();


      CsI_cut[i]->SetLineWidth(1);
      CsI_cut[i]->SetLineColor(kRed);
      CsI_cut[i]->Draw("same");
      c1->Update();

    }
  }

  if (tritium) {

  TString cutTriangle1("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4./7.))");

  TCanvas *c3h = new TCanvas("c3h","",1800,1000);  
  
  ch1->SetMarkerStyle(1);
  c3h->Divide(4,4);
  for(Int_t i=0;i<16;i++) {
    // Int_t i = 9;
    c3h->cd(i+1);  
    ch1->SetMarkerStyle(1);
    cut.Form("nCsI_track==%d && X_C<80 && flagCent",i);
    
    ch1->SetMarkerColor(kBlack);
    hdraw.Form("X_C:arCsI[%d]",i);
    ch1->Draw(hdraw.Data(),cut.Data(),"",10000000,0);
    c3h->Update();


    cut.Form("nAlpha && nCsI_track==%d && X_C<80 && flagCent",i);
    
    ch1->SetMarkerColor(kRed);
    ch1->Draw(hdraw.Data(),cut.Data(),"same");
    c3h->Update();

    cut4he[i]->SetLineColor(kRed);
    cut4he[i]->Draw();

    cut.Form("nhe6 && nCsI_track==%d && X_C<80 && flagCent",i);
    
    ch1->SetMarkerColor(kBlue);
    ch1->Draw(hdraw.Data(),cut.Data(),"same");
    c3h->Update();

    cut6he[i]->SetLineColor(kBlue);
    cut6he[i]->Draw();

    c3h->Update();
  }

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
    for(Int_t i=16;i<32;i++) {
      c3h->cd(i+1-16);
      ch1->SetMarkerColor(kBlack);      
      cut.Form("nX_C==%d && trigger!=1",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch1->Draw(hdraw.Data(),cut.Data(),"",1000000,0);
      c3h->Update();
      
      ch1->SetMarkerColor(kRed);      
      cut.Form("nX_C==%d && flagCent",i);
      hdraw.Form("X_C:tX_C-tF5>>h%d_cut",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);

      ch1->Draw(hdraw.Data(),cut.Data(),"same",1000000,0);
      c3h->Update();

      dssd_x_cut[i]->SetLineColor(kRed);
      dssd_x_cut[i]->Draw("same");


      c3h->Update();
    }
  }

  if (he3_1) {

    TCanvas *c1 = new TCanvas("c1","title",1800,1000);
    c1->cd();

    Int_t i = 15;

    ch->SetMarkerStyle(6); 
    ch->SetMarkerColor(kBlack);      
    cut.Form("n20_1==%d && a1_1+a20_1_un<20 && flag1 && a20_1<1.5 && multv_1==0",i);
    cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
    hdraw.Form("a20_1:a1_1+a20_1_un>>h%d_he31",i);
    ch->Draw(hdraw.Data(),cut.Data(),"");
    c1->Update();

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
      ch1->SetMarkerStyle(1);
      ch1->SetMarkerColor(kBlack);      
      cut.Form("flag2 && a1_2+a20_2_un<35 && a20_2<5 && n20_2==%d && multv_2==0",i);
      hdraw.Form("a20_2:a1_2+a20_2_un>>h%d1",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();


      ch1->SetMarkerStyle(20);
      ch1->SetMarkerSize(0.7);  
      ch1->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_2";
      hdraw.Form("a20_2:a1_2+a20_2_un",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch1->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_2[i]->SetLineWidth(1);
      cuthe3_2[i]->SetLineColor(kRed);
      cuthe3_2[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }

    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_2.pdf]");
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
      ch1->SetMarkerStyle(1);
      ch1->SetMarkerColor(kBlack);      
      cut.Form("flag3 && a1_3+a20_3_un<65 && a20_3<8 && n20_3==%d && multv_3==0",i);
      hdraw.Form("a20_3:a1_3+a20_3_un>>h%d1",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();

      ch1->SetMarkerStyle(20);
      ch1->SetMarkerSize(0.7);
      ch1->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_3";
      hdraw.Form("a20_3:a1_3+a20_3_un",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch1->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_3[i]->SetLineWidth(1);
      cuthe3_3[i]->SetLineColor(kRed);
      cuthe3_3[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_3.pdf]");
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
      ch1->SetMarkerStyle(1);
      ch1->SetMarkerColor(kBlack);      
      cut.Form("flag4 && a1_4+a20_4_un<40 && a20_4<5 && n20_4==%d && multv_4==0",i);
      hdraw.Form("a20_4:a1_4+a20_4_un>>h%d1",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      ch1->Draw(hdraw.Data(),cut.Data(),"");
      // c3h->Update();
      c_arr[i]->Update();


      ch1->SetMarkerStyle(20);
      ch1->SetMarkerSize(0.7);
      ch1->SetMarkerColor(kRed);      
      // cut.Form("n20_1==%d && nhe3_1 && nh3",i);
      cut += " && nhe3_4";
      hdraw.Form("a20_4:a1_4+a20_4_un",i);
      // hdraw.Form("X_C.:aCsI>>h%d",i);
      nCoins+= ch1->Draw(hdraw.Data(),cut.Data(),"same");
      // c3h->Update();

      cuthe3_4[i]->SetLineWidth(1);
      cuthe3_4[i]->SetLineColor(kRed);
      cuthe3_4[i]->Draw("same");
      c_arr[i]->Update();
      // c3h->Update();
    }
    
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf[");
    c_arr[0]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    for(Int_t i=1;i<15;i++) {
      c_arr[i]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    }
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf");
    c_arr[15]->Print("/home/ivan/Desktop/tmp/de_E_4.pdf]");
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

    // TCanvas *c_id_clb = new TCanvas("c_id_clb","",1000,1000);  

    // c_id_clb->cd();
    // ch->Draw("F5+F3:tF5-tF3>>(500,30,110,10000,0,30000)","","col");
    // c_id_clb->Update();

    TCanvas *c_clb_times = new TCanvas("c_clb_times","",1000,1000);  
    c_clb_times->Divide(2,2);

    c_clb_times->cd(1);
    ch->Draw("ND_time_cal-diafTime >> (200,0,25)","ND_amp>0 && n10Be");
    c_clb_times->Update();

    ch->SetLineColor(kRed);
    ch->Draw("ND_time_cal-diafTime","n10Be && neutron && ND_amp>0 ","same");
    c_clb_times->Update();

    c_clb_times->cd(2);
    ch->SetLineColor(kBlue);
    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kBlack);
    ch->Draw("ND_tac[18]:ND_amp[18]","ND_amp[18]>0");
    c_clb_times->Update();    

    ch->SetMarkerStyle(1);
    ch->SetMarkerColor(kRed);
    ch->Draw("ND_tac[18]:ND_amp[18]","neutron && ND_amp[18]>0","same");
    c_clb_times->Update(); 

    c_clb_times->cd(3);
    ch->SetLineColor(kBlue);
    ch->Draw("ND_time_cal[18]-diafTime >> timesOverlap(200,0,25)","ND_amp[18]>0 && n10Be");
    c_clb_times->Update();

    ch->SetLineColor(kRed);
    ch->Draw("ND_time_cal[22]-diafTime","ND_amp[22]>0 && n10Be ","same");
    c_clb_times->Update();

    c_clb_times->cd(4);
    ch->SetLineColor(kBlue);
    ch->Draw("ND_energy*1000 >> energies(500,0,100)","ND_energy>0 && neutron && ND_amp>0 && n10Be");
    c_clb_times->Update();



  }


}


void readPar(TString fileName,Float_t *par1,Float_t *par2,Int_t size=16){

  TString line;
  ifstream myfile;
  Int_t count=0;
  TString file = "/home/ivan/work/macro/h7_1904/parameters/" + fileName + ".cal";
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

