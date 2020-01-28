void draw(){
  // gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH2F *htemp2;

  TChain *ch2 = new TChain("tree"); //e4
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_mm_secondVol.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_firstVol_mm.root");  
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_mm_secondVol.root");
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_firstVol_mm.root");



  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/eTarget/h7_ect_*_mm_frame.root");
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/targetCut/13/h7_ct_*_mm_frame_newPars.root");
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/h7_ct_*_mm_frame_newPars.root");

  cout << ch1->GetEntries() << endl;
  Int_t nEvents = ch1->GetEntries();

  ch2->SetLineColor(kRed);
  ch2->SetMarkerColor(kRed);
  ch2->SetMarkerStyle(20);
  ch2->SetLineWidth(3.);
  
  ch1->SetLineColor(kBlack);
  ch1->SetLineWidth(3.);
  ch1->SetMarkerStyle(20);
  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*4./7",-5,20);
    fa->SetLineColor(kRed);

    TF1 *f6 = new TF1("f6","x*6",-5,20);
    f6->SetLineColor(kRed);

    TF1 *f36 = new TF1("f36","x*36",-5,20);
    f36->SetLineColor(kRed);    


    TString cut, triangleCut;


    TString cutTriangle("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*4./7.))");

    TString cutTriangle2("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*2./7.))");        

    TBox *box_gs = new TBox(0., 0, 3., 190);
    box_gs->SetFillColor(kBlue-10);
    box_gs->SetLineColor(kBlue-10);

    TBox *box_es = new TBox(4., 0, 8., 190);
    box_es->SetFillColor(kMagenta-10);
    box_es->SetLineColor(kMagenta-10);

    TCanvas *c_aCM,*c_aCM_dif,*c_aLab,*c_aLab_diff,*c_triangle,*c_triangle_diff,*c_theta_1d,*c_theta_1d_diff;
    TCanvas *c_mm,*c_mm_diff,*cRangle,*cRangle_diff;


    Bool_t mm_7h = 1;
    Bool_t reactionAngle = 0;
    Bool_t tAnglevsMM = 0;
    Bool_t tAngleLABvsMM = 0;
    Bool_t kinTriangle = 0;
    Bool_t distr_tAngleCM = 0;
    Bool_t mm_9Li = 0;
    Bool_t h3_binaryAngle = 0;
    Bool_t h3_binaryAngle_CM = 0;

        // cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        // cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";

    if (mm_7h) {


        c_mm = new TCanvas("c_mm","",1000,1000);
        c_mm->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(25,-5,20)",cut.Data(),"") << endl;
        c_mm->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

        c_mm->Print("pdf/mm.pdf");

        c_mm_diff = new TCanvas("c_mm_diff","",1000,1000);
        c_mm_diff->Divide(2,2);

        c_mm_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(25,-5,20)",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        c_mm_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(25,-5,20)",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();


        c_mm_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(25,-5,20)",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        c_mm_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(25,-5,20)",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        c_mm->Print("pdf/mm_diff.pdf");
    }

        
    if (reactionAngle) {

        cRangle = new TCanvas("cRangle","",1000,1000);
        cRangle->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch1->Draw("thetah7CM >> h1(10,0,40)",cut.Data(),"") << endl;
        cRangle->Update();    

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle->Update();

        cRangle->Print("pdf/rAngle.pdf"); 

        cRangle_diff = new TCanvas("c_mm_diff","",1000,1000);
        cRangle_diff->Divide(2,2);

        cRangle_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cout << ch1->Draw("thetah7CM >> h2(10,0,40)",cut.Data(),"") << endl;
        cRangle_diff->Update();    

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        cRangle_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cout << ch1->Draw("thetah7CM >> h3(10,0,40)",cut.Data(),"") << endl;
        cRangle_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();


        cRangle_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cout << ch1->Draw("thetah7CM >> h4(10,0,40)",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        cRangle_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cout << ch1->Draw("thetah7CM  >> h5(10,0,40)",cut.Data(),"") << endl;
        cRangle_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        cRangle_diff->Print("pdf/rAngle_diff.pdf"); 
    }

    if (tAnglevsMM) {
        c_aCM = new TCanvas("c_aCM","",1000,1000); 

        TH2F *hfake_1 = new TH2F("hfake_1","title",10000,-10,19,10000,0.,190);
        hfake_1->Draw();

        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM->Update();    


        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM->Update(); 

        c_aCM->Print("pdf/tAngle_CM.pdf");

        c_aCM_dif = new TCanvas("c_aCM_dif","",1000,1000); 
        c_aCM_dif->Divide(2,2);

        c_aCM_dif->cd(2);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920) >> tel1",cut.Data(),"same") << endl;
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->cd(4);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920) >> tel2",cut.Data(),"same") << endl;
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->cd(3);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920) >> tel3",cut.Data(),"same") << endl;
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->cd(1);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920) >> tel4",cut.Data(),"same") << endl;
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->Print("pdf/tAngle_CM_diff.pdf");
    }
    // if (thetaH3_lab) {

    if (tAngleLABvsMM) {

        TH2F *hfake_2 = new TH2F("hfake_2","title",10000,-10,19,10000,0.,140);
        box_gs->SetY2(140);
        box_es->SetY2(140);

        c_aLab = new TCanvas("c_aLab","",1000,1000); 
        c_aLab->cd();

        hfake_2->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1",cut.Data(),"same");
        c_aLab->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1_cut",cut.Data(),"same");
        c_aLab->Update();       

        f6->Draw("same");
        f36->Draw("same");

        c_aLab->Print("pdf/t_h7_Angle.pdf");


        c_aLab_diff = new TCanvas("c_aLab_diff","",1000,1000); 
        c_aLab_diff->Divide(2,2);

        c_aLab_diff->cd(2);
        hfake_2->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1",cut.Data(),"same");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1_cut",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->cd(4);
        hfake_2->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_2",cut.Data(),"same");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_2_cut",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->cd(3);
        hfake_2->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_3",cut.Data(),"same");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_3_cut",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->cd(1);
        hfake_2->Draw();  
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_4",cut.Data(),"same");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_4_cut",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->Print("pdf/t_h7_Angle_diff.pdf");
    }

    if (kinTriangle) {

        TH2F *hfake_3 = new TH2F("hfake_3","title",10000,-10,19,10000,0.,11.5);
        box_gs->SetY2(11.5);
        box_es->SetY2(11.5);

        c_triangle = new TCanvas("c_triangle","",1000,1000);
        c_triangle->cd();

        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        fa->Draw("same");
        c_triangle->Update();

        c_triangle->Print("pdf/triangle.pdf");

        c_triangle_diff = new TCanvas("c_triangle_diff","",1000,1000);
        c_triangle_diff->Divide(2,2);

        c_triangle_diff->cd(2);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        fa->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->cd(4);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        fa->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->cd(3);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        fa->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->cd(1);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        fa->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->Print("pdf/triangle_diff.pdf");

    }

    if (distr_tAngleCM) {

        c_theta_1d = new TCanvas("c_theta_1d","",1000,1000);
        c_theta_1d->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah3CM >> angle_summ(20,0,180)",cut.Data());
        c_theta_1d->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d->Update();

        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d->Update();

        c_theta_1d->Print("pdf/tAngle1D.pdf");

        c_theta_1d_diff = new TCanvas("c_theta_1d_diff","",1000,1000);
        c_theta_1d_diff->Divide(2,2);

        c_theta_1d_diff->cd(2);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah3CM >> angle_1(20,0,180)",cut.Data());
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();


        c_theta_1d_diff->cd(4);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah3CM >> angle_2(20,0,180)",cut.Data());
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        c_theta_1d_diff->cd(3);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah3CM >> angle_3(20,0,180)",cut.Data());
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && nhe3_3 && flag4");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        c_theta_1d_diff->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah3CM >> angle_4(20,0,180)",cut.Data());
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        c_theta_1d_diff->Update();

        c_theta_1d_diff->Print("pdf/tAngle1D_diff.pdf");
    
    }

    if (mm_9Li) {

        TCanvas *thickSumm = new TCanvas("thickSumm","title",1000,1000);

        thickSumm->cd();

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent &&");
        cut += (" ( (flag1 && trigger==2 && nhe3_1)");
        cut += (" || (flag2 && trigger==3 && nhe3_2)");
        cut += (" || (flag3 && trigger==4 && nhe3_3)");
        cut += (" || (flag4 && trigger==5 && nhe3_4) )");

        ch2->Draw("1000*(mh7-8.406868788) >> MMSumm_thick(100,-7,30)",cut.Data(),"");

        ch2->SetLineColor(kRed);
        cut.Form("flagCent && nh3 &&");
        cut += (" ( (flag1 && trigger==2 && nhe3_1)");
        cut += (" || (flag2 && trigger==3 && nhe3_2)");
        cut += (" || (flag3 && trigger==4 && nhe3_3)");
        cut += (" || (flag4 && trigger==5 && nhe3_4) )");

        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        thickSumm->Update();

        thickSumm->Print("pdf/mm_9li.pdf");


        TCanvas *cMM = new TCanvas("cMM","",1000,1000);
        cMM->Divide(2,2);
        Float_t Emin = 0;

        cMM->cd(2);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("1000*(mh7-8.406868788) >> mm1",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag1 && trigger==2 && nhe3_1");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->cd(4);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2");
        ch2->Draw("1000*(mh7-8.406868788) >> mm2",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag2 && trigger==3 && nhe3_2");
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->cd(3);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 ");
        ch2->Draw("1000*(mh7-8.406868788) >> mm3",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag3 && trigger==4 && nhe3_3 ");
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->cd(1);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4");
        ch2->Draw("1000*(mh7-8.406868788) >> mm4",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag4 && trigger==5 && nhe3_4");
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->Print("pdf/mm_9li_diff.pdf");
    }
    
    if (h3_binaryAngle) {

        TCanvas *cBinary_diff = new TCanvas("cBinary_diff","",1000,1000);
        cBinary_diff->Divide(2,2);

        cBinary_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3 >> bin_angle_1",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        cBinary_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3 >> bin_angle_2",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

       
        cBinary_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3 >> bin_angle_3",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();   

        cBinary_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3 >> bin_angle_4",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        cBinary_diff->Print("pdf/binaryAngle_diff.pdf");

        TCanvas *cBinary = new TCanvas("cBinary","",1000,1000);
        cBinary->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3 >> bin_angle",cut.Data(),"");
        cBinary->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary->Update();

        cBinary->Print("pdf/binaryAngle.pdf");
    }

    if (h3_binaryAngle_CM) {

        TCanvas *cBinary_CM_diff = new TCanvas("cBinary_CM_diff","",1000,1000);
        cBinary_CM_diff->Divide(2,2);

        cBinary_CM_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3_CM >> bin_angleCM_1",cut.Data(),"");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

        cBinary_CM_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3_CM >> bin_angleCM_2",cut.Data(),"");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

       
        cBinary_CM_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3_CM >> bin_angleCM_3",cut.Data(),"");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();   

        cBinary_CM_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_bin_h3_CM >> bin_angleCM_4",cut.Data(),"");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("angle_bin_h3_CM",cut.Data(),"same");
        cBinary_CM_diff->Update();

        cBinary_CM_diff->Print("pdf/binaryAngle_CM_diff.pdf");


        TCanvas *cBinaryCM = new TCanvas("cBinaryCM","",1000,1000);
        cBinaryCM->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        // cut += " && " + cutTriangle2;
        ch1->Draw("cos(angle_bin_h3_CM*TMath::DegToRad()) >> bin_angleCM(10,-1,1)",cut.Data(),"");
        cBinaryCM->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        // cut += " && " + cutTriangle2;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<4.";
        ch1->Draw("cos(angle_bin_h3_CM*TMath::DegToRad())",cut.Data(),"same");
        cBinaryCM->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        // cut += " && " + cutTriangle2;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<8";
        ch1->Draw("cos(angle_bin_h3_CM*TMath::DegToRad())",cut.Data(),"same");
        cBinaryCM->Update();

        cBinaryCM->Print("pdf/binaryAngle_CM.pdf");
    }
}