void drawAngles(){
  // gStyle->SetOptStat(0);

  TChain *ch2 = new TChain("tree"); //e4
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_mm.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/parVariation/targetTh/be10_thinT_6.5mm_mm.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/tmp/be10_2_mmminus1.root");
  
  cout << ch2->GetEntries() << endl;

  // ch2->AddFriend("treeNew","/media/ivan/data/exp1904/analysed/oldPars/mm_400_25_new.root");

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/thinDetTh/be10_ct_all_mmThin.root");
  // ch1->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/thinDetTh/be10_ct_all_mmThick.root");

  cout << ch1->GetEntries() << endl;

  TChain *ch3 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
  // ch3->Add("/media/ivan/data/exp1906/be10/analysed/be10_etarget_mm.root");
  // cout << ch3->GetEntries() << endl;

  ch2->SetLineWidth(3.);
  ch1->SetLineWidth(3.);
  ch3->SetLineWidth(3.);

  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*4/7",-5,20);
    fa->SetLineColor(kRed);

    TString cut, triangleCut;

    Bool_t he3_vs_mm = 0;
    Bool_t summMM = 1;
    Bool_t mm = 1; 
    Bool_t testPars = 0;
    Bool_t testPars1 = 0;
    Bool_t reactionAngle = 0;



    Float_t Emin = 0;


    TH1F *htemp;
    TCanvas *c1,*c2,*cBlue,*cMM,*canvasMM;

    if (testPars) {

        c1 = new TCanvas("c1","",1800,1000);
        c1->Divide(2,2);
        

        c1->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f)",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> corr1(70,-5,30)",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f) && 1000*(mh7-8.406868788)<2.2",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> corr1_low(70,-5,30)",cut.Data(),"same");
        c1->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f) && nh3",Emin);
        // ch1->Draw("1000*(mh7-8.406868788) >> h1_coin(70,-5,30)",cut.Data(),"same");
        // c1->Update();

        // ch1->SetLineColor(kBlue);
        // cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f) && nh3",Emin);

        // cut += " && frame1X<12.5 && frame1X>-12.5";
        // cut += " && frame1Y<12.5 && frame1Y>-12.5";
        // cut += " && frame2X<12.5 && frame2X>-12.5";
        // cut += " && frame2Y<12.5 && frame2Y>-12.5";
        // cut += " && frame3X<12.5 && frame3X>-12.5";
        // cut += " && frame3Y<12.5 && frame3Y>-12.5"; 

        // ch1->Draw("1000*(mh7-8.406868788) >> h1_coin_fr(70,-5,30)",cut.Data(),"same");
        // c1->Update();


        c1->cd(2);
        ch1->SetLineColor(kBlack);
        cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f)",Emin);
        ch1->Draw("1000*(mh7-8.406868788) >> corr2(70,-5,30)",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f) && 1000*(mh7-8.406868788)<2.2",Emin);
        ch1->Draw("1000*(mh7-8.406868788) >> corr2_low(70,-5,30)",cut.Data(),"same");
        c1->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        // ch1->Draw("1000*(mh7-8.406868788) >> h2_coin(70,-5,30)",cut.Data(),"same");
        // c1->Update();   

        // ch1->SetLineColor(kBlue);
        // cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && frame1X<12.5 && frame1X>-12.5";
        // cut += " && frame1Y<12.5 && frame1Y>-12.5";
        // cut += " && frame2X<12.5 && frame2X>-12.5";
        // cut += " && frame2Y<12.5 && frame2Y>-12.5";
        // cut += " && frame3X<12.5 && frame3X>-12.5";
        // cut += " && frame3Y<12.5 && frame3Y>-12.5"; 

        // ch1->Draw("1000*(mh7-8.406868788) >> h2_coin_fr(70,-5,30)",cut.Data(),"same");
        // c1->Update(); 


        c1->cd(3);
        ch1->SetLineColor(kBlack);
        cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f)",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        ch1->Draw("1000*(mh7-8.406868788) >> corr3(70,-5,30)",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f) && 1000*(mh7-8.406868788)<2.2",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        ch1->Draw("1000*(mh7-8.406868788) >> corr3_low(70,-5,30)",cut.Data(),"same");
        c1->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // ch1->Draw("1000*(mh7-8.406868788) >> h3_coin(70,-5,30)",cut.Data(),"same");
        // c1->Update();

        // ch1->SetLineColor(kBlue);
        // cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && frame1X<12.5 && frame1X>-12.5";
        // cut += " && frame1Y<12.5 && frame1Y>-12.5";
        // cut += " && frame2X<12.5 && frame2X>-12.5";
        // cut += " && frame2Y<12.5 && frame2Y>-12.5";
        // cut += " && frame3X<12.5 && frame3X>-12.5";
        // cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        // ch1->Draw("1000*(mh7-8.406868788) >> h3_coin_fr(70,-5,30)",cut.Data(),"same");
        // c1->Update();


        c1->cd(4);
        ch1->SetLineColor(kBlack);
        cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f)",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> corr4(70,-5,30)",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f) && 1000*(mh7-8.406868788)<2.2",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> corr4_low(70,-5,30)",cut.Data(),"same");
        c1->Update();


        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // ch1->Draw("1000*(mh7-8.406868788) >> h4_coin(70,-5,30)",cut.Data(),"same");
        // c1->Update();

        // ch1->SetLineColor(kBlue);
        // cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f) && flagCent && nh3",Emin);
        // cut += " && frame1X<12.5 && frame1X>-12.5";
        // cut += " && frame1Y<12.5 && frame1Y>-12.5";
        // cut += " && frame2X<12.5 && frame2X>-12.5";
        // cut += " && frame2Y<12.5 && frame2Y>-12.5";
        // cut += " && frame3X<12.5 && frame3X>-12.5";
        // cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        // ch1->Draw("1000*(mh7-8.406868788) >> h4_coin_fr(70,-5,30)",cut.Data(),"same");
        // c1->Update();


    }

    if (testPars1) {

        cBlue = new TCanvas("cBlue","",1800,1000);
        cBlue->Divide(2,2);
        

        cBlue->cd(1);

        ch1->SetLineColor(kBlue);
        cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f) && nh3",Emin);
        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        ch1->Draw("1000*(mh7-8.406868788) >> h1_coin_fr(140,-5,30)",cut.Data(),"");
        cBlue->Update();

        cBlue->cd(2);
        ch1->SetLineColor(kBlue);
        cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f) && flagCent && nh3",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        ch1->Draw("1000*(mh7-8.406868788) >> h2_coin_fr(140,-5,30)",cut.Data(),"");
        cBlue->Update(); 

        cBlue->cd(3);
        ch1->SetLineColor(kBlue);
        cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f) && flagCent && nh3",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        ch1->Draw("1000*(mh7-8.406868788) >> h3_coin_fr(140,-5,30)",cut.Data(),"");
        cBlue->Update();

        cBlue->cd(4);
        ch1->SetLineColor(kBlue);
        cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f) && flagCent && nh3",Emin);
        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        ch1->Draw("1000*(mh7-8.406868788) >> h4_coin_fr(140,-5,30)",cut.Data(),"");
        cBlue->Update();
    }


    Float_t border1,border2,border3,border4;
    // border1 = 1.6;
    // border2 = 2.2;
    // border3 = 1.5;
    // border4 = 1.9;

    border1 = -1.2;
    border2 = 1.2;
    border3 = 1.9;
    border4 = 1.9;

    if (he3_vs_mm) {

        c2 = new TCanvas("c2","",1800,1000);
        c2->Divide(2,2);
        Float_t Emin = 0;

        ch1->SetMarkerStyle(7);

        c2->cd(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("trigger==2 && (nhe3_1 && e_1<25)");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("e_1:1000*(mh7-8.406868788) >> h12D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && trigger==2 && (nhe3_1 && e_1<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("e_1:1000*(mh7-8.406868788) >> h12DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        c2->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f) && nh3",Emin);
        // ch1->Draw("e_1:1000*(mh7-8.406868788) >> h1_coin2D(70,-5,5,100,5,14)",cut.Data(),"same");
        // c2->Update();


        c2->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("trigger==3 && (nhe3_2 && e_2<25)");
        ch1->Draw("e_2:1000*(mh7-8.406868788) >> h22D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && trigger==3 && (nhe3_2 && e_2<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        ch1->Draw("e_2:1000*(mh7-8.406868788) >> h22DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        c2->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f) && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        // ch1->Draw("e_2:1000*(mh7-8.406868788) >> h2_coin2D(70,-5,5,100,5,14)",cut.Data(),"same");
        // c2->Update();   



        c2->cd(3);
        ch1->SetMarkerColor(kBlack);
        cut.Form("trigger==4 && (nhe3_3 && e_3<25)");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        ch1->Draw("e_3:1000*(mh7-8.406868788) >> h32D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && trigger==4 && (nhe3_3 && e_3<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        ch1->Draw("e_3:1000*(mh7-8.406868788) >> h32DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        c2->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // ch1->Draw("e_3:1000*(mh7-8.406868788) >> h3_coin2D(70,-5,5,100,5,14)",cut.Data(),"same");
        // c2->Update();


        c2->cd(4);
        ch1->SetMarkerColor(kBlack);
        cut.Form("trigger==5 && nhe3_4 && e_4<25");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("e_4:1000*(mh7-8.406868788) >> h42D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && trigger==5 && (nhe3_4 && e_4<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("e_4:1000*(mh7-8.406868788) >> h42DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        c2->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // ch1->Draw("e_4:1000*(mh7-8.406868788) >> h4_coin2D(70,-5,5,100,5,14)",cut.Data(),"same");
        // c2->Update();

    }
   
    if (mm) {

        cMM = new TCanvas("cMM","",1800,1000);
        cMM->Divide(2,2);
        Float_t Emin = 0;

        cMM->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && trigger==2 && (flag1 && nhe3_1 && e_1<25)");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> h1(30,-5,5)",cut.Data(),"");
        cMM->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && trigger==2 && (nhe3_1 && flag1 && e_1<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> h1CUT(30,-5,5)",cut.Data(),"same");
        cMM->Update();
        htemp = (TH1F*)gPad->GetPrimitive("h1CUT");
        cout << htemp->GetMean() << " 1 g.s. position" << endl;

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==2 && (nhe3_1 && e_1<25 && e_1>%f) && nh3",Emin);
        // ch1->Draw("1000*(mh7-8.406868788) >> h1_coin(20,-5,5)",cut.Data(),"same");
        // cMM->Update();

        cMM->cd(2);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && trigger==3 && (flag2 && nhe3_2 && e_2<25)");
        ch1->Draw("1000*(mh7-8.406868788) >> h2(30,-5,5)",cut.Data(),"");
        cMM->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && trigger==3 && (flag2 && nhe3_2 && e_2<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        ch1->Draw("1000*(mh7-8.406868788) >> h2CUT(30,-5,5)",cut.Data(),"same");
        cMM->Update();

        htemp = (TH1F*)gPad->GetPrimitive("h2CUT");
        cout << htemp->GetMean() << " 2 g.s. position" << endl;

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==3 && (nhe3_2 && e_2<25 && e_2>%f) && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");

        // ch1->Draw("1000*(mh7-8.406868788) >> h2_coin(20,-5,5)",cut.Data(),"same");
        // cMM->Update();   

        cMM->cd(3);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && trigger==4 && (flag3 && nhe3_3 && e_3<25)");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> h3(30,-5,5)",cut.Data(),"");
        cMM->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && trigger==4 && (flag3 && nhe3_3 && e_3<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> h3CUT(30,-5,5)",cut.Data(),"same");
        cMM->Update();

        htemp = (TH1F*)gPad->GetPrimitive("h3CUT");
        cout << htemp->GetMean() << " 3 g.s. position" << endl;

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==4 && (nhe3_3 && e_3<25 && e_3>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // ch1->Draw("1000*(mh7-8.406868788) >> h3_coin(20,-5,5)",cut.Data(),"same");
        // cMM->Update();

        cMM->cd(4);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && trigger==5 && (flag4 && nhe3_4 && e_4<25)");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> h4(30,-5,5)",cut.Data(),"");
        cMM->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && trigger==5 && (flag4 && nhe3_4 && e_4<25) && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",border2,border1);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> h4CUT(30,-5,5)",cut.Data(),"same");
        cMM->Update();

        htemp = (TH1F*)gPad->GetPrimitive("h4CUT");
        cout << htemp->GetMean() << " 4 g.s. position" << endl;

        // ch1->SetLineColor(kRed);
        // cut.Form("trigger==5 && (nhe3_4 && e_4<25 && e_4>%f) && flagCent && nh3",Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // ch1->Draw("1000*(mh7-8.406868788) >> h4_coin(20,-5,5)",cut.Data(),"same");
        // cMM->Update();

        cMM->Print("/home/ivan/Desktop/4mm_coin.png");

    }
   
    if (summMM) {

        canvasMM = new TCanvas("canvasMM");
        canvasMM->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && ( (flag1 && trigger==2 && (flag1 && nhe3_1 && e_1<25))");
        cut += (" || (flag2 && trigger==3 && (flag2 && nhe3_2 && e_2<25))");
        cut += (" || (flag3 && trigger==4 && (flag3 && nhe3_3 && e_3<25))");
        cut += (" || (flag4 && trigger==5 && (flag4 && nhe3_4 && e_4<25)) )");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> MMSumm(20,-5,5)",cut.Data(),"");

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && nh3 && 1000*(mh7-8.406868788)<1.9 && 1000*(mh7-8.406868788)>-1.9 && ( (flag 1 && trigger==2 && (flag1 && nhe3_1 && e_1<25))");
        cut += (" || (flag2 && trigger==3 && (flag2 && nhe3_2 && e_2<25))");
        cut += (" || (flag3 && trigger==4 && (flag3 && nhe3_3 && e_3<25))");
        cut += (" || (flag4 && trigger==5 && (flag4 && nhe3_4 && e_4<25)) )");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch1->Draw("1000*(mh7-8.406868788) >> MMSumm_cut(20,-5,5)",cut.Data(),"same");
        canvasMM->Update();

        canvasMM->Print("/home/ivan/Desktop/summMM_coin.png");

    }

    if (reactionAngle) {

        TCanvas *cRangle = new TCanvas("cRangle");
        // cRangle->Divide(2,1);

        // cRangle->cd(1);

        cut.Form("nh3 && trigger!=4 && 1000*(mh7-8.406868788)>1.9 && 1000*(mh7-8.406868788)<3.5 && ( (trigger==2 && (flag1 && nhe3_1 && e_1<25))");
        cut += (" || (trigger==3 && (flag2 && nhe3_2 && e_2<25))");
        // cut += (" || (trigger==4 && (flag3 && nhe3_3 && e_3<25))");
        cut += (" || (trigger==5 && (flag4 && nhe3_4 && e_4<25)) )");
        ch1->SetLineWidth(1);
        ch1->Draw("angle_he3_he8 >> reactionAngle(20,0,30)",cut.Data(),"");
        TH1F *angleHist = (TH1F*)gPad->GetPrimitive("reactionAngle");
        cRangle->Update();
return;
        TString hCut,histName,borders,hDraw;
        ch1->SetLineWidth(3);
        Float_t counts[20],angle[20];
        for(Int_t i=0;i<20;i++) {
            borders.Form(" && angle_he3_he8>%f && angle_he3_he8<%f",i*1.5,(i+1)*1.5);
            hCut = cut + borders;
            histName.Form("angleCut_%d",i);
            hDraw.Form("angle_he3_he8 >> angleCut_%d(20,0,30)",i);
            ch1->SetLineColor(i%4 + 1);
            counts[i] = ch1->Draw(hDraw.Data(),hCut.Data(),"same");
            angle[i] = angleHist->GetBinCenter(i+1);
            cout << angle[i] << " " << counts[i] << endl;
            cRangle->Update();
        }
        // ch1->Draw("thetah7 >> (50,0,5)","thetah7>0 && thetah7<0.1");
        // TH1F *angleHist = (TH1F*)gPad->GetPrimitive(histName.Data());

        // }

        cout << angleHist->GetNbinsX() << endl;
        TGraph *g = new TGraph(angleHist->GetNbinsX(),angle,counts);
        cRangle->cd(2);
        g->SetMarkerColor(kBlack);
        g->Draw("AL*");
        cRangle->Update();

    }

}