#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void drawTMP(){
  create_IDs();
  create_cuts();

  gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH1F *htemp2;
  TH1F *htemp;
  TH2F *htemp2D;

  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/mnt/data/exp1904/analysed/reco/h7/h7_ct_*_mm.root");
  ch1->Add("/mnt/data/exp1904/analysed/reco/h7/h7_ct_*_mm.root");
  cout << ch1->GetEntries () << " csiAnalyse" << endl;
  ch1->SetMarkerStyle(8);
  ch1->SetLineColor(kBlack);
  ch1->SetMarkerColor(kBlack);

  TF1 *fa = new TF1("fa","x*1/2",0,35);
  fa->SetLineColor(kRed);

  TF1 *fa1 = new TF1("fa1","x*4/7",0,25);
  fa1->SetLineColor(kRed);

  TF1 *fa2 = new TF1("fa2","x*3/7",0,40);
  fa2->SetLineColor(kRed);

  TF1 *f6 = new TF1("f6","x*6",-5,20);
  f6->SetLineColor(kRed);

  TF1 *f36 = new TF1("f36","x*5/6",0,35);
  f36->SetLineColor(kRed);  

  TString cut6H("( 1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag())<(1000*(lv_h6.Mag()-3*0.939565-2.808920)*1/2 + 0.5))");
  TString cut6H_neutrons("( 1000*(lv_neutron_CMH6.T()-lv_neutron_CMH6.Mag())<(1000*(lv_h6.Mag()-3*0.939565-2.808920)*5/6 + 0.5))");


  Bool_t             angular_6h = 0;

  TString cut, triangleCut, hdraw;

  Bool_t fig1 = 0;
  Bool_t fig2 = 0;
  Bool_t fig3 = 0;
  Bool_t fig4 = 0;
  Bool_t fig5 = 0;
  Bool_t fig6 = 0;
  Bool_t fig7 = 7;
  Bool_t fig8 = 0;

    if (fig1) {

        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);

        ch1->SetLineWidth(2);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920) >> htemp1(100,-10,40)",cut.Data(),"") << endl;
        c_mm->Update();
        ch1->SetLineColor(kRed);
        cut += " && " + cut6H;
        cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("events/0.5");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(0.63);
        c_mm->Update(); 

        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("Missing-mass spectrum 6H","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.07);
        legend1->Draw("same");
        c_mm->Update();

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/mm_full.C");
        return;
    }

    if (fig2) {

        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm->Update();

        cut += " && " + cut6H;
        ch1->SetMarkerColor(kRed);
        cout << ch1->Draw("1000*(lv_h3_CMH6.T()-lv_h3_CMH6.Mag()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Triton kinematic triangle");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("Triton energy in 6H CMS, MeV");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(0.63); 

        fa->Draw("same"); 

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_triangle.C");

        TCanvas *c_1 = new TCanvas("c_1","",1800,1000);
        c_1->cd();

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("lv_h6_CMR.Theta()*TMath::RadToDeg():1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
        c_1->Update();

        cut += " && " + cut6H;
        ch1->SetMarkerColor(kRed);
        cout << ch1->Draw("lv_h6_CMR.Theta()*TMath::RadToDeg():1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Reaction angle vs 6H MM");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("Reaction angle, deg");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(0.63); 

        c_1->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/angular.C");
        
        return;
    }

    if (fig3) {

        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
        c_mm->Divide(2,2);

        c_mm->cd(1);
        ch1->SetLineWidth(2);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<9";
        cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920) >> htemp1(40,0,40)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("events");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.05);
        htemp->GetYaxis()->SetTitleOffset(0.63); 

        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("ThetaCM < 9","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.07);
        legend1->Draw("same");

        c_mm->cd(2);
        ch1->SetLineWidth(2);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>9 && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
        cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920) >> htemp2(40,0,40)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("events");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.05);
        htemp->GetYaxis()->SetTitleOffset(0.63); 

        auto legend2 = new TLegend(0.1,0.9,0.9,1.);
        legend2->SetHeader("9 < ThetaCM < 14","C"); // option "C" allows to center the heade
        legend2->SetTextColor(kRed);
        legend2->SetTextSize(0.07);
        legend2->Draw("same");

        c_mm->cd(3);
        ch1->SetLineWidth(2);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>14 && lv_h6_CMR.Theta()*TMath::RadToDeg()<20";
        cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920) >> htemp3(40,0,40)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("events");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.05);
        htemp->GetYaxis()->SetTitleOffset(0.63); 

        auto legend3 = new TLegend(0.1,0.9,0.9,1.);
        legend3->SetHeader("14 < ThetaCM < 20","C"); // option "C" allows to center the heade
        legend3->SetTextColor(kRed);
        legend3->SetTextSize(0.07);
        legend3->Draw("same");

        c_mm->cd(4);
        ch1->SetLineWidth(2);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>20";
        cout << ch1->Draw("1000*(lv_h6.Mag()-3*0.939565-2.808920) >> htemp4(40,0,40)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("events");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.05);
        htemp->GetYaxis()->SetTitleOffset(0.63); 

        auto legend4 = new TLegend(0.1,0.9,0.9,1.);
        legend4->SetHeader("ThetaCM > 20","C"); // option "C" allows to center the heade
        legend4->SetTextColor(kRed);
        legend4->SetTextSize(0.07);
        legend4->Draw("same");

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/mm_selection.C");

        return;
    }

    if (fig4) {

        ch1->SetMarkerSize(0.4);
        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
        c_mm->Divide(2,1);

        c_mm->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cout << ch1->Draw("angle_h3_he8_CMH6:1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(1.09); 
    
        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("Correlation with angle between 3H and Beam in 6H CMS","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.035);
        legend1->Draw("same");
        c_mm->Update();

        c_mm->cd(2);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg():1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(1.09);  
    
        auto legend2 = new TLegend(0.1,0.9,0.9,1.);
        legend2->SetHeader("Correlation with angle between 3H and q in 6H CMS","C"); // option "C" allows to center the heade
        legend2->SetTextColor(kRed);
        legend2->SetTextSize(0.035);
        legend2->Draw("same");
        c_mm->Update();

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_q_corr.C");

        TCanvas *c_mm1 = new TCanvas("c_mm1","",1800,1000);
        c_mm1->Divide(2,1);

        c_mm1->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cout << ch1->Draw("cos(angle_h3_he8_CMH6*TMath::DegToRad()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(1.09); 
    
        auto legend3 = new TLegend(0.1,0.9,0.9,1.);
        legend3->SetHeader("Correlation with cos angle between 3H and Beam in 6H CMS","C"); // option "C" allows to center the heade
        legend3->SetTextColor(kRed);
        legend3->SetTextSize(0.035);
        legend3->Draw("same");
        c_mm1->Update();

        c_mm1->cd(2);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()):1000*(lv_h6.Mag()-3*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Missing-mass spectrum 6H");
        htemp->GetXaxis()->SetTitle("E_t");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.04);
        htemp->GetXaxis()->SetTitleOffset(0.85);  
        htemp->GetYaxis()->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.04);
        htemp->GetYaxis()->SetTitleOffset(1.09);  
    
        auto legend4 = new TLegend(0.1,0.9,0.9,1.);
        legend4->SetHeader("Correlation with cos angle between 3H and q in 6H CMS","C"); // option "C" allows to center the heade
        legend4->SetTextColor(kRed);
        legend4->SetTextSize(0.035);
        legend4->Draw("same");
        c_mm1->Update();

        c_mm1->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_q_corrCos.C");

        return;
    }

    if (fig5) {

        ch1->SetMarkerSize(0.4);
        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
        c_mm->Divide(2,2);

        c_mm->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<3";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp1(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("3H and Beam angle,6H CMS, MM<3","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.08);
        legend1->Draw("same");
        c_mm->Update();

        c_mm->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>3 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<6";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp2(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend2 = new TLegend(0.1,0.9,0.9,1.);
        legend2->SetHeader("3H and Beam angle,6H CMS, 3<MM<6","C"); // option "C" allows to center the heade
        legend2->SetTextColor(kRed);
        legend2->SetTextSize(0.08);
        legend2->Draw("same");
        c_mm->Update();

        c_mm->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>6 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<9";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp3(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend3 = new TLegend(0.1,0.9,0.9,1.);
        legend3->SetHeader("3H and Beam angle,6H CMS, 6<MM<9","C"); // option "C" allows to center the heade
        legend3->SetTextColor(kRed);
        legend3->SetTextSize(0.08);
        legend3->Draw("same");
        c_mm->Update();

        c_mm->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>9";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp4(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend4 = new TLegend(0.1,0.9,0.9,1.);
        legend4->SetHeader("3H and Beam angle,6H CMS, MM>9","C"); // option "C" allows to center the heade
        legend4->SetTextColor(kRed);
        legend4->SetTextSize(0.08);
        legend4->Draw("same");
        c_mm->Update();

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_beam_selection.C");




        TCanvas *c_mm1 = new TCanvas("c_mm1","",1800,1000);
        c_mm1->Divide(2,2);

        c_mm1->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<3";
        cout << ch1->Draw("cos(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp1Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend5 = new TLegend(0.1,0.9,0.9,1.);
        legend5->SetHeader("3H and Beam cos angle,6H CMS, MM<3","C"); // option "C" allows to center the heade
        legend5->SetTextColor(kRed);
        legend5->SetTextSize(0.08);
        legend5->Draw("same");
        c_mm->Update();

        c_mm1->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>3 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<6";
        cout << ch1->Draw("(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp2Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend6 = new TLegend(0.1,0.9,0.9,1.);
        legend6->SetHeader("3H and Beam cos angle,6H CMS, 3<MM<6","C"); // option "C" allows to center the heade
        legend6->SetTextColor(kRed);
        legend6->SetTextSize(0.08);
        legend6->Draw("same");
        c_mm->Update();

        c_mm1->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>6 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<9";
        cout << ch1->Draw("(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp3Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend7 = new TLegend(0.1,0.9,0.9,1.);
        legend7->SetHeader("3H and Beam cos angle,6H CMS, 6<MM<9","C"); // option "C" allows to center the heade
        legend7->SetTextColor(kRed);
        legend7->SetTextSize(0.08);
        legend7->Draw("same");
        c_mm1->Update();

        c_mm1->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>9";
        cout << ch1->Draw("(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp4Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend8 = new TLegend(0.1,0.9,0.9,1.);
        legend8->SetHeader("3H and Beam cos angle,6H CMS, MM>9","C"); // option "C" allows to center the heade
        legend8->SetTextColor(kRed);
        legend8->SetTextSize(0.08);
        legend8->Draw("same");
        c_mm1->Update();

        c_mm1->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_beam_Cos_selection.C");

        return;
    }

    if (fig6) {

        ch1->SetMarkerSize(0.4);
        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
        c_mm->Divide(2,2);

        c_mm->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<3";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp1(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("3H and q angle,6H CMS, MM<3","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.08);
        legend1->Draw("same");
        c_mm->Update();

        c_mm->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>3 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<6";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp2(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend2 = new TLegend(0.1,0.9,0.9,1.);
        legend2->SetHeader("3H and q angle,6H CMS, 3<MM<6","C"); // option "C" allows to center the heade
        legend2->SetTextColor(kRed);
        legend2->SetTextSize(0.08);
        legend2->Draw("same");
        c_mm->Update();

        c_mm->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>6 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<9";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp3(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend3 = new TLegend(0.1,0.9,0.9,1.);
        legend3->SetHeader("3H and q angle,6H CMS, 6<MM<9","C"); // option "C" allows to center the heade
        legend3->SetTextColor(kRed);
        legend3->SetTextSize(0.08);
        legend3->Draw("same");
        c_mm->Update();

        c_mm->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>9";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp4(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend4 = new TLegend(0.1,0.9,0.9,1.);
        legend4->SetHeader("3H and q angle,6H CMS, MM>9","C"); // option "C" allows to center the heade
        legend4->SetTextColor(kRed);
        legend4->SetTextSize(0.08);
        legend4->Draw("same");
        c_mm->Update();

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_q_selection.C");


        TCanvas *c_mm1 = new TCanvas("c_mm1","",1800,1000);
        c_mm1->Divide(2,2);

        c_mm1->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<3";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp1Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend5 = new TLegend(0.1,0.9,0.9,1.);
        legend5->SetHeader("3H and q cos angle,6H CMS, MM<3","C"); // option "C" allows to center the heade
        legend5->SetTextColor(kRed);
        legend5->SetTextSize(0.08);
        legend5->Draw("same");
        c_mm1->Update();

        c_mm1->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>3 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<6";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp6Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp6Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend6 = new TLegend(0.1,0.9,0.9,1.);
        legend6->SetHeader("3H and q cos angle,6H CMS, 3<MM<6","C"); // option "C" allows to center the heade
        legend6->SetTextColor(kRed);
        legend6->SetTextSize(0.08);
        legend6->Draw("same");
        c_mm1->Update();

        c_mm1->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>6 && 1000*(lv_h6.Mag()-3*0.939565-2.808920)<9";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp3Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend7 = new TLegend(0.1,0.9,0.9,1.);
        legend7->SetHeader("3H and q cos angle,6H CMS, 6<MM<9","C"); // option "C" allows to center the heade
        legend7->SetTextColor(kRed);
        legend7->SetTextSize(0.08);
        legend7->Draw("same");
        c_mm1->Update();

        c_mm1->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && 1000*(lv_h6.Mag()-3*0.939565-2.808920)>9";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp4Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend8 = new TLegend(0.1,0.9,0.9,1.);
        legend8->SetHeader("3H and q cos angle,6H CMS, MM>9","C"); // option "C" allows to center the heade
        legend8->SetTextColor(kRed);
        legend8->SetTextSize(0.08);
        legend8->Draw("same");
        c_mm1->Update();

        c_mm1->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_q_Cos_selection.C");

        return;

    }

    if (fig7) {

        ch1->SetMarkerSize(0.4);
        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
        c_mm->Divide(2,2);

        c_mm->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<9";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp1(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("3H and Beam angle,6H CMS, ThetaCM<9","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.08);
        legend1->Draw("same");
        c_mm->Update();

        c_mm->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>9 && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp2(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend2 = new TLegend(0.1,0.9,0.9,1.);
        legend2->SetHeader("3H and Beam angle,6H CMS, 9<ThetaCM<14","C"); // option "C" allows to center the heade
        legend2->SetTextColor(kRed);
        legend2->SetTextSize(0.08);
        legend2->Draw("same");
        c_mm->Update();

        c_mm->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>14 && lv_h6_CMR.Theta()*TMath::RadToDeg()<20";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp3(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend3 = new TLegend(0.1,0.9,0.9,1.);
        legend3->SetHeader("3H and Beam angle,6H CMS, 14<ThetaCM<20","C"); // option "C" allows to center the heade
        legend3->SetTextColor(kRed);
        legend3->SetTextSize(0.08);
        legend3->Draw("same");
        c_mm->Update();

        c_mm->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>20";
        cout << ch1->Draw("angle_h3_he8_CMH6 >> htemp4(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4");
        htemp->SetTitle("Angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against beam, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend4 = new TLegend(0.1,0.9,0.9,1.);
        legend4->SetHeader("3H and Beam angle,6H CMS, ThetaCM>20","C"); // option "C" allows to center the heade
        legend4->SetTextColor(kRed);
        legend4->SetTextSize(0.08);
        legend4->Draw("same");
        c_mm->Update();

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_beam_ThetaCuts.C");



        TCanvas *c_mm1 = new TCanvas("c_mm1","",1800,1000);
        c_mm1->Divide(2,2);

        c_mm1->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<9";
        cout << ch1->Draw("cos(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp1Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend5 = new TLegend(0.1,0.9,0.9,1.);
        legend5->SetHeader("3H and Beam cos angle,6H CMS, ThetaCM<9","C"); // option "C" allows to center the heade
        legend5->SetTextColor(kRed);
        legend5->SetTextSize(0.08);
        legend5->Draw("same");
        c_mm->Update();

        c_mm1->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>9 && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
        cout << ch1->Draw("cos(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp2Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend6 = new TLegend(0.1,0.9,0.9,1.);
        legend6->SetHeader("3H and Beam cos angle,6H CMS, 9<ThetaCM<14","C"); // option "C" allows to center the heade
        legend6->SetTextColor(kRed);
        legend6->SetTextSize(0.08);
        legend6->Draw("same");
        c_mm1->Update();

        c_mm1->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>14 && lv_h6_CMR.Theta()*TMath::RadToDeg()<20";
        cout << ch1->Draw("cos(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp3Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend7 = new TLegend(0.1,0.9,0.9,1.);
        legend7->SetHeader("3H and Beam cos angle,6H CMS, 14<ThetaCM<20","C"); // option "C" allows to center the heade
        legend7->SetTextColor(kRed);
        legend7->SetTextSize(0.08);
        legend7->Draw("same");
        c_mm1->Update();

        c_mm1->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>20";
        cout << ch1->Draw("cos(angle_h3_he8_CMH6*TMath::DegToRad()) >> htemp4Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4Cos");
        htemp->SetTitle("Cos angle between 3h and beam in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against beam");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend8 = new TLegend(0.1,0.9,0.9,1.);
        legend8->SetHeader("3H and Beam cos angle,6H CMS, ThetaCM>20","C"); // option "C" allows to center the heade
        legend8->SetTextColor(kRed);
        legend8->SetTextSize(0.08);
        legend8->Draw("same");
        c_mm1->Update();

        c_mm1->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_beam_Cos_ThetaCuts.C");

        return;
    }

    if (fig8) {

        ch1->SetMarkerSize(0.4);
        TCanvas *c_mm = new TCanvas("c_mm","",1800,1000);
        c_mm->Divide(2,2);

        c_mm->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<9";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp1(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend1 = new TLegend(0.1,0.9,0.9,1.);
        legend1->SetHeader("3H and q angle,6H CMS, ThetaCM<9","C"); // option "C" allows to center the heade
        legend1->SetTextColor(kRed);
        legend1->SetTextSize(0.08);
        legend1->Draw("same");
        c_mm->Update();

        c_mm->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>9 && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp2(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend2 = new TLegend(0.1,0.9,0.9,1.);
        legend2->SetHeader("3H and q angle,6H CMS, 9<ThetaCM<14","C"); // option "C" allows to center the heade
        legend2->SetTextColor(kRed);
        legend2->SetTextSize(0.08);
        legend2->Draw("same");
        c_mm->Update();

        c_mm->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>14 && lv_h6_CMR.Theta()*TMath::RadToDeg()<20";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp3(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend3 = new TLegend(0.1,0.9,0.9,1.);
        legend3->SetHeader("3H and q angle,6H CMS, 14<ThetaCM<20","C"); // option "C" allows to center the heade
        legend3->SetTextColor(kRed);
        legend3->SetTextSize(0.08);
        legend3->Draw("same");
        c_mm->Update();

        c_mm->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>20";
        cout << ch1->Draw("lv_h3_CMH6_rot.Theta()*TMath::RadToDeg() >> htemp4(45,0,180)",cut.Data(),"") << endl;
        c_mm->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4");
        htemp->SetTitle("Angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Theta(3H) against q, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend4 = new TLegend(0.1,0.9,0.9,1.);
        legend4->SetHeader("3H and q angle,6H CMS, ThetaCM>20","C"); // option "C" allows to center the heade
        legend4->SetTextColor(kRed);
        legend4->SetTextSize(0.08);
        legend4->Draw("same");
        c_mm->Update();

        c_mm->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_q_ThetaCuts.C");




        TCanvas *c_mm1 = new TCanvas("c_mm1","",1800,1000);
        c_mm1->Divide(2,2);

        c_mm1->cd(1);

        ch1->SetMarkerColor(kBlack);
        ch1->SetMarkerStyle(8);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()<9";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp1Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp1Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend5 = new TLegend(0.1,0.9,0.9,1.);
        legend5->SetHeader("3H and q cos angle,6H CMS, ThetaCM<9","C"); // option "C" allows to center the heade
        legend5->SetTextColor(kRed);
        legend5->SetTextSize(0.08);
        legend5->Draw("same");
        c_mm1->Update();

        c_mm1->cd(2);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>9 && lv_h6_CMR.Theta()*TMath::RadToDeg()<14";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp2Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp2Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend6 = new TLegend(0.1,0.9,0.9,1.);
        legend6->SetHeader("3H and q cos angle,6H CMS, 9<ThetaCM<14","C"); // option "C" allows to center the heade
        legend6->SetTextColor(kRed);
        legend6->SetTextSize(0.08);
        legend6->Draw("same");
        c_mm1->Update();

        c_mm1->cd(3);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>14 && lv_h6_CMR.Theta()*TMath::RadToDeg()<20";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp3Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp3Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend7 = new TLegend(0.1,0.9,0.9,1.);
        legend7->SetHeader("3H and q cos angle,6H CMS, 14<ThetaCM<20","C"); // option "C" allows to center the heade
        legend7->SetTextColor(kRed);
        legend7->SetTextSize(0.08);
        legend7->Draw("same");
        c_mm1->Update();

        c_mm1->cd(4);

        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cut6H;
        cut += " && lv_h6_CMR.Theta()*TMath::RadToDeg()>20";
        cout << ch1->Draw("cos(lv_h3_CMH6_rot.Theta()) >> htemp4Cos(45,-1,1)",cut.Data(),"") << endl;
        c_mm1->Update();

        htemp = (TH1F*)gPad->GetPrimitive("htemp4Cos");
        htemp->SetTitle("Cos angle between 3h and q in 6HCMS");
        htemp->GetXaxis()->SetTitle("Cos theta(3H) against q");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetXaxis()->SetTitleSize(0.05);
        htemp->GetXaxis()->SetTitleOffset(0.75);  
        htemp->GetYaxis()->SetTitle("events/4");
        htemp->GetYaxis()->CenterTitle(); 
        htemp->GetYaxis()->SetTitleSize(0.07);
        htemp->GetYaxis()->SetTitleOffset(0.45); 
    
        auto legend8 = new TLegend(0.1,0.9,0.9,1.);
        legend8->SetHeader("3H and q cos angle,6H CMS, ThetaCM>20","C"); // option "C" allows to center the heade
        legend8->SetTextColor(kRed);
        legend8->SetTextSize(0.08);
        legend8->Draw("same");
        c_mm1->Update();

        c_mm1->SaveAs("/home/muzalevskii/work/articles/H-6_notes/scripts/triton_q_Cos_ThetaCuts.C");

        return;

    }

}

