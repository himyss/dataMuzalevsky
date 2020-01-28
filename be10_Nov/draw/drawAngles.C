TCutG *cutg1,*cutg2,*cutg3,*cutg4;

#include "/home/ivan/work/macro/be10_Nov/draw/cuts/mmCuts.C"

void drawAngles(){
  // gStyle->SetOptStat(0);

  mmCuts();

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_mm_thin.root");
  cout << ch1->GetEntries() << endl;

  TChain *ch2 = new TChain("tree"); //e4
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_mm_secondVol.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_firstVol_mm.root");  
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_mm_secondVol.root");
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_firstVol_mm.root");

  cout << ch2->GetEntries() << endl;
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/reserved/be10_ct_mm_initial.root");

  ch2->AddFriend("intree","/media/ivan/data/exp1906/be10/analysed/novPars/reco/reserved/be10_ct_mm_initial.root");
// return;
// return;

  TChain *ch3 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
  // ch3->Add("/media/ivan/data/exp1906/be10/analysed/be10_etarget_mm.root");
  // cout << ch3->GetEntries() << endl;

  ch2->SetLineWidth(2.);
  ch1->SetLineWidth(2.);
  ch3->SetLineWidth(2.);

  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*4/7",-5,20);
    fa->SetLineColor(kRed);

    TString cut, triangleCut;

    Bool_t he3_vs_mm = 1;
    Bool_t summMM = 0;
    Bool_t mm = 1; 
    Bool_t testPars = 0;
    Bool_t testPars1 = 0;
    Bool_t reactionAngle = 0;



    Float_t Emin = 0;


    TH1F *htemp;
    TCanvas *c1,*c2,*cBlue,*cMM,*canvasMM;

    Float_t border1,border2,border3,border4;

    Float_t b1_1,b1_2,b1_3,b1_4;
    Float_t b2_1,b2_2,b2_3,b2_4;

    if (he3_vs_mm) {

        c2 = new TCanvas("c2","",1800,1000);
        c2->Divide(2,2);
        Float_t Emin = 0;

        ch2->SetMarkerStyle(7);

        c2->cd(1);
        ch2->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("e_1:1000*(mh7-8.406868788) >> h12D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch2->SetMarkerColor(kRed);
        // cut.Form("(1000*(mh7-8.406868788)>-0.6 || e_1>8.54) && flagCent && flag1 && trigger==2 && nhe3_1 && e_1<25 && 1000*(mh7-8.406868788)<%f && 1000*(mh7-8.406868788)>%f",b2_1,b1_1);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && ");
        cut += cutg1->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";

        ch2->Draw("e_1:1000*(mh7-8.406868788) >> h12DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        c2->Update();
        cutg1->Draw("same");


        c2->cd(2);
        ch2->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("e_2:1000*(mh7-8.406868788) >> h22D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch2->SetMarkerColor(kRed);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && ");
        cut += cutg2->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("e_2:1000*(mh7-8.406868788) >> h22DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        c2->Update();
        cutg2->Draw("same");


        c2->cd(3);
        ch2->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("e_3:1000*(mh7-8.406868788) >> h32D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch2->SetMarkerColor(kRed);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && ");
        cut += cutg3->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("e_3:1000*(mh7-8.406868788) >> h32DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        cutg3->Draw("same");
        c2->Update();


        c2->cd(4);
        ch2->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("e_4:1000*(mh7-8.406868788) >> h42D(70,-5,5,100,5,14)",cut.Data(),"");
        c2->Update();

        ch2->SetMarkerColor(kRed);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && ");
        cut += cutg4->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("e_4:1000*(mh7-8.406868788) >> h42DCUT(70,-5,5,100,5,14)",cut.Data(),"same");
        cutg4->Draw("same");
        c2->Update();

        c2->Print("/home/ivan/Desktop/correlation.pdf");

    }
   
    if (mm) {

        Float_t p1,p2,p3,p4,w1,w2,w3,w4;

        cMM = new TCanvas("cMM","",1800,1000);
        cMM->Divide(2,2);
        Float_t Emin = 0;

        cMM->cd(1);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("1000*(mh7-8.406868788) >> mm1",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && ");
        // cut += " && 1000*(9.325505+1.875612-2.808391-mh7_in)<100 && ";       
        cut += cutg1->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("1000*(mh7-8.406868788) >> mm1_coin",cut.Data(),"same");
        cMM->Update();

        TH1F *htemp = (TH1F*)gPad->GetPrimitive("mm1_coin");
        cout << htemp->GetMean() << " " << htemp->GetEntries() << endl;
        p1 = htemp->GetMean();
        w1 = htemp->GetEntries();

        cMM->cd(2);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("1000*(mh7-8.406868788) >> mm2",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && ");
        cut += cutg2->GetName();    
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("1000*(mh7-8.406868788) >> mm2_coin",cut.Data(),"same");
        cMM->Update();

        htemp = (TH1F*)gPad->GetPrimitive("mm2_coin");
        cout << htemp->GetMean() << " " << htemp->GetEntries() << endl;

        p2 = htemp->GetMean();
        w2 = htemp->GetEntries();

        cMM->cd(3);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 ");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("1000*(mh7-8.406868788) >> mm3",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && ");
        // cut += "1000*(9.325505+1.875612-2.808391-mh7_in)<100 && ";
        cut += cutg3->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";        
        ch2->Draw("1000*(mh7-8.406868788) >> mm3_coin",cut.Data(),"same");
        cMM->Update();

        htemp = (TH1F*)gPad->GetPrimitive("mm3_coin");
        cout << htemp->GetMean() << " " << htemp->GetEntries() << endl;

        p3 = htemp->GetMean();
        w3 = htemp->GetEntries();

        cMM->cd(4);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4");
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("1000*(mh7-8.406868788) >> mm4",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && ");
        // cut += "1000*(9.325505+1.875612-2.808391-mh7_in)<100 && ";
        cut += cutg4->GetName();
        cut += " &&  (fXt*fXt + fYt*fYt)<10*10";
        ch2->Draw("1000*(mh7-8.406868788) >> mm4_coin",cut.Data(),"same");
        cMM->Update();

        htemp = (TH1F*)gPad->GetPrimitive("mm4_coin");
        cout << htemp->GetMean() << " " << htemp->GetEntries() << endl;

        p4 = htemp->GetMean();
        w4 = htemp->GetEntries();

        cout << (p1*w1 + p2*w2 + p3*w3 + p4*w4)/(w1+w2+w3+w4) << endl;

        cMM->Print("/home/ivan/Desktop/4mm_coin.pdf");

    }
   
    if (summMM) {

        // canvasMM = new TCanvas("canvasMM","title",1800,1000);
        // // canvasMM->Divide(2,1);

        // canvasMM->cd();

        // ch1->SetLineColor(kBlack);
        // // cut.Form("flagCent && 1000*(mh7-8.406868788)<1.9 && 1000*(mh7-8.406868788)>-1.9 &&");
        // cut.Form("flagCent &&");
        // cut += (" ( (flag1 && trigger==2 && nhe3_1 && e_1<25)");
        // cut += (" || (flag2 && trigger==3 && nhe3_2 && e_2<25)");
        // cut += (" || (flag3 && trigger==4 && nhe3_3 && e_3<25)");
        // cut += (" || (flag4 && trigger==5 && nhe3_4 && e_4<25) )");
        // ch1->Draw("1000*(mh7-8.406868788) >> MMSumm_thin",cut.Data(),"");

        // ch1->SetLineColor(kGreen);
        // cut.Form("flagCent && nh3 &&");
        // cut += (" ( (flag1 && trigger==2 && nhe3_1 && e_1<25)");
        // cut += (" || (flag2 && trigger==3 && nhe3_2 && e_2<25)");
        // cut += (" || (flag3 && trigger==4 && nhe3_3 && e_3<25)");
        // cut += (" || (flag4 && trigger==5 && nhe3_4 && e_4<25) )");
        // ch1->Draw("1000*(mh7-8.406868788) >> MMSumm_cut_thin",cut.Data(),"same");
        // canvasMM->Update();

        // canvasMM->cd(2);

        Long64_t numEntries = 3000000;

        Long64_t startEntry = 14464279 - numEntries;
        // startEntry = 0;

        TCanvas *thickSumm = new TCanvas("thickSumm","title",1800,1000);

        thickSumm->cd();

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent &&");
        cut += (" ( (flag1 && trigger==2 && nhe3_1 && e_1<25)");
        cut += (" || (flag2 && trigger==3 && nhe3_2 && e_2<25)");
        cut += (" || (flag3 && trigger==4 && nhe3_3 && e_3<25)");
        cut += (" || (flag4 && trigger==5 && nhe3_4 && e_4<25) )");
        cut += (" && 1000*(mh7-8.406868788)>-5 && 1000*(mh7-8.406868788)<30");

        ch2->Draw("1000*(mh7-8.406868788) >> MMSumm_thick(100,-7,30)",cut.Data(),"");

        ch2->SetLineColor(kGreen);
        cut.Form("flagCent && nh3 &&");
        cut += (" ( (flag1 && trigger==2 && nhe3_1 && e_1<25)");
        cut += (" || (flag2 && trigger==3 && nhe3_2 && e_2<25)");
        cut += (" || (flag3 && trigger==4 && nhe3_3 && e_3<25)");
        cut += (" || (flag4 && trigger==5 && nhe3_4 && e_4<25) )");
        cut += (" && 1000*(mh7-8.406868788)>-5 && 1000*(mh7-8.406868788)<30");
        ch2->Draw("1000*(mh7-8.406868788) >> MMSumm_cut_thick",cut.Data(),"same");
        thickSumm->Update();

        // ch2->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 &&");
        // cut += (" ( (flag1 && trigger==2 && nhe3_1 && e_1<25)");
        // cut += (" || (flag2 && trigger==3 && nhe3_2 && e_2<25)");
        // cut += (" || (flag3 && trigger==4 && nhe3_3 && e_3<25)");
        // cut += (" || (flag4 && trigger==5 && nhe3_4 && e_4<25) )");
        // ch2->Draw("1000*(mh7-8.406868788) >> MMSumm_thick_gs_3",cut.Data(),"same");
        // thickSumm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("MMSumm_thick_gs_3");
        cout << htemp->GetMean() << " " << htemp->GetEntries() << endl;

    }
   

}