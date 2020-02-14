void drawSICK(){
  gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH1F *htemp2;
  TH1F *htemp;
  TH2F *htemp2D;


  TChain *ch2 = new TChain("tree"); //e4
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_mm_secondVol.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/be10_ct_firstVol_mm.root");  
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_mm_secondVol.root");
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/novPars/reco/parVariation/sideTel/be10_ct_firstVol_mm.root");



  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/eTarget/h7_ect_*_mm_frame.root");
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/h7_ct_*_mm_frame.root");
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/h7_ct_*_mm_frame_newPars.root");

  TChain *chBeam = new TChain("tree");
  chBeam->Add("/media/ivan/data/exp1904/analysed/novPars/beamDiagnostics/beamHe8_*.root");

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

    TF1 *fa = new TF1("fa","x*4/7",-5,20);
    fa->SetLineColor(kBlack);

    TF1 *fa2 = new TF1("fa2","x*2/7",-5,20);
    fa2->SetLineColor(kRed);

    TF1 *f6 = new TF1("f6","x*6",-5,20);
    f6->SetLineColor(kRed);

    TF1 *f36 = new TF1("f36","x*36",-5,20);
    f36->SetLineColor(kRed);    


    TString cut, triangleCut;


    TString cutTriangle("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*4/7.))");

    TString cutTriangle2("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*2/7.))");

    TString cutTriangle1("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*4./7.))");

    // TString cutTriangle2("(eh3_CM*1000>(1000*(mh7-4*0.939565-2.808920)*2./7.))");       

    TBox *box_gs = new TBox(0., 0, 3., 190);
    box_gs->SetFillColor(kBlue-10);
    box_gs->SetLineColor(kBlue-10);

    TBox *box_es = new TBox(4., 0, 7., 190);
    box_es->SetFillColor(kMagenta-10);
    box_es->SetLineColor(kMagenta-10);

    TCanvas *c_aCM,*c_aCM_dif,*c_aLab,*c_aLab_diff,*c_triangle,*c_triangle_diff,*c_theta_1d,*c_theta_1d_diff;
    TCanvas *c_mm,*c_mm_diff,*cRangle,*cRangle_diff,*c_proj,*c_beamDiagnostics,*c_beamDiagnostics1;
    TCanvas *c_3helabCM,*c_3helabCM_diff,*c_kinTriangle_track,*c_kinTriangle_track_diff;


    // Bool_t mm_7h = 0;
    // Bool_t reactionAngle = 0;
    // Bool_t tAnglevsMM = 0;
    // Bool_t tAngleLABvsMM = 0;
    // Bool_t kinTriangle = 0;
    // Bool_t distr_tAngleCM = 0;
    Bool_t mm_9Li = 0;
    Bool_t h3_binaryAngle = 0;

    Bool_t             mm_7h = 0;
    Bool_t     reactionAngle = 0;
    Bool_t        tAnglevsMM = 0;
    Bool_t     tAngleLABvsMM = 0;
    Bool_t       kinTriangle = 1;
    Bool_t    distr_tAngleCM = 0;
    Bool_t h3_binaryAngle_CM = 0;
    Bool_t   beamDiagnostics = 0;
    Bool_t    theta3HeCM_LAB = 0;


   TCutG *cutg1 = new TCutG("cutg1",17);
   cutg1->SetVarX("1000*(mh7-4*0.939565-2.808920)");
   cutg1->SetVarY("eh3_CM*1000");
   cutg1->SetTitle("Graph");
   cutg1->SetFillColor(1);
   cutg1->SetPoint(0,3.31281,1.38659);
   cutg1->SetPoint(1,3.1409,1.211);
   cutg1->SetPoint(2,2.64665,0.756544);
   cutg1->SetPoint(3,2.96899,0.549972);
   cutg1->SetPoint(4,3.89302,0.663587);
   cutg1->SetPoint(5,4.15089,1.01476);
   cutg1->SetPoint(6,4.7311,1.31429);
   cutg1->SetPoint(7,7.933,2.19222);
   cutg1->SetPoint(8,8.98597,2.63635);
   cutg1->SetPoint(9,8.64214,3.25607);
   cutg1->SetPoint(10,7.30981,3.51428);
   cutg1->SetPoint(11,5.05344,2.68799);
   cutg1->SetPoint(12,3.37728,1.84105);
   cutg1->SetPoint(13,3.09792,1.6448);
   cutg1->SetPoint(14,3.18388,1.56218);
   cutg1->SetPoint(15,3.26984,1.5002);
   cutg1->SetPoint(16,3.31281,1.38659);




        // cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        // cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";

        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17"; 


    if (mm_7h) {


        c_mm = new TCanvas("c_mm","",1000,1000);
        c_mm->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(25,-5,20)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_full");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();

        c_mm->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

        // ch1->SetLineColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<12.5+0.55 && frame1X>-12.5+0.55";
        // cut += " && frame1Y<12.5+1.33 && frame1Y>-12.5+1.33";
        // cut += " && frame2X<12.5+0.55 && frame2X>-12.5+0.55";
        // cut += " && frame2Y<12.5+1.33 && frame2Y>-12.5+1.33";
        // cut += " && frame3X<12.5+0.55 && frame3X>-12.5+0.55";
        // cut += " && frame3Y<12.5+1.33 && frame3Y>-12.5+1.33";         
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        c_mm->Print("pdf/mm_full.pdf");


        c_mm_diff = new TCanvas("c_mm_diff","",1000,1000);
        c_mm_diff->Divide(2,2);

        c_mm_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(25,-5,20)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_1");
        htemp1->SetTitle("1 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        c_mm_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update(); 

        c_mm_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        // cut += " && " + cutTriangle1;        
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(25,-5,20)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_2");
        htemp1->SetTitle("2 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();        
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah7CM<12";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        c_mm_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(25,-5,20)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_3");
        htemp1->SetTitle("3 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();           
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah7CM<12";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        c_mm_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;         
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(25,-5,20)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_4");
        htemp1->SetTitle("4 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();          
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_diff->Update();

        c_mm_diff->Print("pdf/mm_diff.pdf");
    }
   
    if (reactionAngle) {

        cRangle = new TCanvas("cRangle","",1000,1000);
        cRangle->cd();

        TH2F *hfake_0 = new TH2F("hfake_1","Total reaction angle vs MM",10000,-5,20,10000,0.,45);
        hfake_0->GetXaxis()->SetTitle("E_t");
        hfake_0->GetXaxis()->CenterTitle();
        hfake_0->GetYaxis()->SetTitle("7H angle CMS");
        hfake_0->GetYaxis()->CenterTitle();
        hfake_0->GetYaxis()->SetTitleOffset(1.3);

        box_gs->SetY2(45.);
        box_es->SetY2(45.);
        box_gs->SetY1(0.);
        box_es->SetY1(0.);

        hfake_0->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");


        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle->Update();  

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle2;
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<12.5+0.55 && frame1X>-12.5+0.55";
        // cut += " && frame1Y<12.5+1.33 && frame1Y>-12.5+1.33";
        // cut += " && frame2X<12.5+0.55 && frame2X>-12.5+0.55";
        // cut += " && frame2Y<12.5+1.33 && frame2Y>-12.5+1.33";
        // cut += " && frame3X<12.5+0.55 && frame3X>-12.5+0.55";
        // cut += " && frame3Y<12.5+1.33 && frame3Y>-12.5+1.33";
        // cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // cRangle->Update();

        cRangle->Print("pdf/rAngle.pdf"); 


        cRangle_diff = new TCanvas("cRangle_diff","",1000,1000);
        cRangle_diff->Divide(2,2);

        cRangle_diff->cd(2);

        hfake_0->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;        
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_0->SetTitle("1 telescope reaction angle vs MM");        
        cRangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        cRangle_diff->cd(4);

        hfake_0->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;        
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_0->SetTitle("2 telescope reaction angle vs MM");        
        cRangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;        
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle_diff->Update();    

        cRangle_diff->cd(3);

        hfake_0->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;        
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_0->SetTitle("3 telescope reaction angle vs MM");        
        cRangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;        
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle_diff->Update();    

        cRangle_diff->cd(1);

        hfake_0->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_0->SetTitle("4 telescope reaction angle vs MM");        
        cRangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle_diff->Update();

        cRangle_diff->Print("pdf/rAngle_diff.pdf"); 
    }

    if (tAnglevsMM) {

        box_gs->SetY2(1.);
        box_es->SetY2(1.);
        box_gs->SetY1(-1.);
        box_es->SetY1(-1.);


        c_aCM = new TCanvas("c_aCM","",1000,1000); 

        TH2F *hfake_1 = new TH2F("hfake_1","Total cos(3H_CM) vs MM",10000,-5,20,10000,-1.,1);
        hfake_1->Draw();
        hfake_1->GetXaxis()->SetTitle("E_t");
        hfake_1->GetXaxis()->CenterTitle();
        hfake_1->GetYaxis()->SetTitle("cos(3H_CM)");
        hfake_1->GetYaxis()->CenterTitle();
        hfake_1->GetYaxis()->SetTitleOffset(1.3);

        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM->Update();    


        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
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
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_1->SetTitle("Telescope 1 cos(3H CM) vs MM");
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->cd(4);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_1->SetTitle("Telescope 2 cos(3H CM) vs MM");
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->cd(3);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_1->SetTitle("Telescope 3 cos(3H CM) vs MM");
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->cd(1);
        hfake_1->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_1->SetTitle("Telescope 4 cos(3H CM) vs MM");
        c_aCM_dif->Update();     

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_aCM_dif->Update(); 

        c_aCM_dif->Print("pdf/tAngle_CM_diff.pdf");
    }

    if (tAngleLABvsMM) {

        TH2F *hfake_2 = new TH2F("hfake_2","Total squared angle 3H 7H vs MM",10000,-5,20,10000,0.,140);
        box_gs->SetY2(140);
        box_es->SetY2(140);
        box_gs->SetY1(0.);
        box_es->SetY1(0.);


        c_aLab = new TCanvas("c_aLab","",1000,1000); 
        c_aLab->cd();

        hfake_2->Draw();
        hfake_2->GetXaxis()->SetTitle("E_t");
        hfake_2->GetXaxis()->CenterTitle();
        hfake_2->GetYaxis()->SetTitle("Squared angle 3H 7H, deg^2");
        hfake_2->GetYaxis()->CenterTitle();
        hfake_2->GetYaxis()->SetTitleOffset(1.3);

        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        c_aLab->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) ",cut.Data(),"same");
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
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;        
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        hfake_2->SetTitle("Telescope 1 squared angle 3H 7H vs MM");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->cd(4);
        hfake_2->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        hfake_2->SetTitle("Telescope 2 squared angle 3H 7H vs MM");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->cd(3);
        hfake_2->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        hfake_2->SetTitle("Telescope 3 squared angle 3H 7H vs MM");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->cd(1);
        hfake_2->Draw();  
        box_gs->Draw("same");
        box_es->Draw("same");

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        hfake_2->SetTitle("Telescope 4 squared angle 3H 7H vs MM");
        c_aLab_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        c_aLab_diff->Update();

        f6->Draw("same");
        f36->Draw("same");

        c_aLab_diff->Print("pdf/t_h7_Angle_diff.pdf");
    }

    if (kinTriangle) {

        c_triangle = new TCanvas("c_triangle","",1000,1000);
        c_triangle->cd();

        TH2F *hfake_3 = new TH2F("hfake_3","Total kinematic triangle",10000,-5,20,10000,0.,8);
        // box_gs->SetY2(8);
        // box_es->SetY2(8);

        // hfake_3->Draw();
        // hfake_3->GetXaxis()->SetTitle("E_t");
        // hfake_3->GetXaxis()->CenterTitle();
        // hfake_3->GetYaxis()->SetTitle("3H energy CMS");
        // hfake_3->GetYaxis()->CenterTitle();
        // hfake_3->GetYaxis()->SetTitleOffset(1.3);

        // box_gs->Draw("same");
        // box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";

        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_triangle->Update();

        ch1->SetMarkerColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 && ";
        cut += cutg1->GetName(); 
        // cut += " && eh3_CM*1000<8 && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<18";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cutg1->Draw("same");
        c_triangle->Update();


// 
        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle->Update();
        fa2->Draw("same");
        fa->Draw("same");
        c_triangle->Update();




return;
        c_triangle->Print("pdf/triangle.pdf");

        c_triangle_diff = new TCanvas("c_triangle_diff","",1000,1000);
        c_triangle_diff->Divide(2,2);

        c_triangle_diff->cd(2);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_3->SetTitle("Telescope 1 kinematic triangle");
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17"; 
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle_diff->Update();

        fa->Draw("same");
        fa2->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->cd(4);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_3->SetTitle("Telescope 2 kinematic triangle");
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && " + cutTriangle2;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17";         
        // // cut += " && " + cutTriangle2;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle_diff->Update();

        fa->Draw("same");
        fa2->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->cd(3);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_3->SetTitle("Telescope 3 kinematic triangle");
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        // cut += " && " + cutTriangle2;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17";         
        // // cut += " && " + cutTriangle2;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle_diff->Update();

        

        fa->Draw("same");
        fa2->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->cd(1);
        hfake_3->Draw();
        box_gs->Draw("same");
        box_es->Draw("same");        

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hfake_3->SetTitle("Telescope 4 kinematic triangle");
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle_diff->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17"; 
        // // cut += " && " + cutTriangle2;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle_diff->Update();

        fa->Draw("same");
        fa2->Draw("same");
        c_triangle_diff->Update();

        c_triangle_diff->Print("pdf/triangle_diff.pdf");
    }

    if (distr_tAngleCM) {

        c_theta_1d = new TCanvas("c_theta_1d","",1000,1000);
        c_theta_1d->cd();

        // ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // ch1->Draw("thetah3CM >> h_thetah3CM(20,0,180)",cut.Data());

        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("thetah3CM >> h_thetah3CM(20,0,180)",cut.Data(),"");
        c_theta_1d->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->Draw("thetah3CM",cut.Data(),"same");
        htemp1 = (TH1F*)gPad->GetPrimitive("h_thetah3CM");
        htemp1->SetTitle("Total theta 3H CMS, with 4/7 triangle cut. Blue: MM<3. Purple 4<MM<7");
        htemp1->GetXaxis()->SetTitle("Theta 3H CMS, deg");
        htemp1->GetXaxis()->CenterTitle();
        c_theta_1d->Update();

        c_theta_1d->Print("pdf/tAngle1D.pdf");
    }

    if (h3_binaryAngle_CM) {

        TCanvas *cBinaryCM = new TCanvas("cBinaryCM","",1000,1000);
        cBinaryCM->cd();


        TH2F *hfake_4 = new TH2F("hfake_4","Total Angle between 3H and rMomentum in CMS vs MM",10000,-5,20,10000,0.,180);
        hfake_4->GetXaxis()->SetTitle("E_t");
        hfake_4->GetXaxis()->CenterTitle();
        hfake_4->GetYaxis()->SetTitle("Angle between 3H and rMomentum in CMS");
        hfake_4->GetYaxis()->CenterTitle();
        hfake_4->GetYaxis()->SetTitleOffset(1.3);
        hfake_4->Draw();

        box_gs->SetY2(180.);
        box_es->SetY2(180.);

        box_gs->Draw("same");
        box_es->Draw("same");  

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        cBinaryCM->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        cBinaryCM->Update();

        cBinaryCM->Print("pdf/binaryAngle_CM.pdf");


        TCanvas *cBinary_CM_diff = new TCanvas("cBinary_CM_diff","",1000,1000);
        cBinary_CM_diff->Divide(2,2);

        cBinary_CM_diff->cd(2);

        hfake_4->Draw();
        hfake_4->SetTitle("Telescope1 angle between 3H and rMomentum in CMS vs MM");
        box_gs->Draw("same");
        box_es->Draw("same"); 

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();

        cBinary_CM_diff->cd(4);

        hfake_4->Draw();
        hfake_4->SetTitle("Telescope2 angle between 3H and rMomentum in CMS vs MM");
        box_gs->Draw("same");
        box_es->Draw("same"); 

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();

       
        cBinary_CM_diff->cd(3);

        hfake_4->Draw();
        hfake_4->SetTitle("Telescope3 angle between 3H and rMomentum in CMS vs MM");
        box_gs->Draw("same");
        box_es->Draw("same"); 

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920) ",cut.Data(),"same");
        gPad->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();   

        cBinary_CM_diff->cd(1);

        hfake_4->Draw();
        hfake_4->SetTitle("Telescope4 angle between 3H and rMomentum in CMS vs MM");
        box_gs->Draw("same");
        box_es->Draw("same"); 

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle2;
        ch1->Draw("angle_bin_h3_CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same");
        gPad->Update();

        cBinary_CM_diff->Print("pdf/binaryAngle_CM_diff.pdf");
    }

    if (beamDiagnostics) {

        c_beamDiagnostics = new TCanvas("c_beamDiagnostics","Beam Diagnostic",1800,1000); 
        c_beamDiagnostics->Divide(2,2);

        c_beamDiagnostics->cd(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        ch1->Draw("fYt:fXt >> targetprofile(39,-12,12,39,-12,12)",cut.Data(),"box");
        htemp2D = (TH2F*)gPad->GetPrimitive("targetprofile");
        htemp2D->SetTitle("Profile at the target plane 7H events");
        htemp2D->GetXaxis()->SetTitle("X, mm");
        htemp2D->GetXaxis()->CenterTitle();
        htemp2D->GetYaxis()->SetTitle("Y, mm");
        htemp2D->GetYaxis()->CenterTitle();
        c_beamDiagnostics->Update();

        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->SetMarkerColor(kBlue);
        ch1->Draw("fYt:fXt",cut.Data(),"same");

        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->SetMarkerColor(kRed);
        ch1->Draw("fYt:fXt",cut.Data(),"same");

        c_beamDiagnostics->cd(2);

        ch1->SetMarkerColor(kBlack);
        ch1->Draw("yCt:xCt >> centralProfile(32,-32,32,32,-32,32)",cut.Data(),"box");
        htemp2D = (TH2F*)gPad->GetPrimitive("centralProfile");
        htemp2D->SetTitle("Profile at the central SSD plane 7H events");
        htemp2D->GetXaxis()->SetTitle("X, mm");
        htemp2D->GetXaxis()->CenterTitle();
        htemp2D->GetYaxis()->SetTitle("Y, mm");
        htemp2D->GetYaxis()->CenterTitle();

        ch1->SetMarkerColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";        
        ch1->Draw("yCt:xCt",cut.Data(),"same");

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("yCt:xCt",cut.Data(),"same");

        c_beamDiagnostics->Update();

        c_beamDiagnostics->cd(3);
        ch1->SetMarkerColor(kBlack);
        ch1->Draw("py/pBeam:px/pBeam >>relationMom(43,-0.05,0.05,43,-0.05,0.05) ",cut.Data(),"box");
        htemp2D = (TH2F*)gPad->GetPrimitive("relationMom");
        htemp2D->SetTitle("pBeam_y/pBeam vs pBeam_x/pBeam");
        htemp2D->GetXaxis()->SetTitle("px/pBeam");
        htemp2D->GetXaxis()->CenterTitle();
        htemp2D->GetYaxis()->SetTitle("py/pBeam");
        htemp2D->GetYaxis()->CenterTitle();

        ch1->SetMarkerColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";        
        ch1->Draw("py/pBeam:px/pBeam",cut.Data(),"same");

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("py/pBeam:px/pBeam",cut.Data(),"same");

        c_beamDiagnostics->Update();        

        c_beamDiagnostics->cd(4);
        ch1->SetLineColor(kBlack);
        ch1->Draw("(pBeam-pz)/pBeam >> dispertion(50,0,0.001)",cut.Data(),"");
        htemp = (TH1F*)gPad->GetPrimitive("dispertion");
        htemp->SetTitle("Dispertion");
        htemp->GetXaxis()->SetTitle("px/pBeam");
        htemp->GetXaxis()->CenterTitle();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";        
        ch1->Draw("(pBeam-pz)/pBeam",cut.Data(),"same");

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("(pBeam-pz)/pBeam",cut.Data(),"same");

        c_beamDiagnostics->Update();

        c_beamDiagnostics->Print("pdf/beam7H.pdf");

        c_beamDiagnostics1 = new TCanvas("c_beamDiagnostics1","Beam Diagnostics trigger==1",1800,1000); 
        c_beamDiagnostics1->Divide(2,2);

        c_beamDiagnostics1->cd(1);
        cut.Form("trigger==1");
        chBeam->Draw("fYt:fXt >> targetprofile1(39,-12,12,39,-12,12)",cut.Data(),"col");
        htemp2D = (TH2F*)gPad->GetPrimitive("targetprofile1");
        htemp2D->SetTitle("Profile at the target plane trigger==1");
        htemp2D->GetXaxis()->SetTitle("X, mm");
        htemp2D->GetXaxis()->CenterTitle();
        htemp2D->GetYaxis()->SetTitle("Y, mm");
        htemp2D->GetYaxis()->CenterTitle();
        c_beamDiagnostics1->Update();

        c_beamDiagnostics1->cd(2);

        chBeam->Draw("yCt:xCt >> centralProfile1(32,-32,32,32,-32,32)",cut.Data(),"col");
        htemp2D = (TH2F*)gPad->GetPrimitive("centralProfile1");
        htemp2D->SetTitle("Profile at the central SSD plane trigger==1");
        htemp2D->GetXaxis()->SetTitle("X, mm");
        htemp2D->GetXaxis()->CenterTitle();
        htemp2D->GetYaxis()->SetTitle("Y, mm");
        htemp2D->GetYaxis()->CenterTitle();        
        c_beamDiagnostics1->Update();

        c_beamDiagnostics1->cd(3);
        chBeam->Draw("py/pBeam:px/pBeam >>relationMom1(43,-0.05,0.05,43,-0.05,0.05) ",cut.Data(),"col");
        htemp2D = (TH2F*)gPad->GetPrimitive("relationMom1");
        htemp2D->SetTitle("pBeam_y/pBeam vs pBeam_x/pBeam trigger==1");
        htemp2D->GetXaxis()->SetTitle("px/pBeam");
        htemp2D->GetXaxis()->CenterTitle();
        htemp2D->GetYaxis()->SetTitle("py/pBeam");
        htemp2D->GetYaxis()->CenterTitle();        
        c_beamDiagnostics1->Update();        

        c_beamDiagnostics1->cd(4);
        chBeam->Draw("(pBeam-pz)/pBeam >> dispertion1(50,0,0.001)",cut.Data(),"");
        htemp = (TH1F*)gPad->GetPrimitive("dispertion1");
        htemp->SetTitle("Dispertion trigger==1");
        htemp->GetXaxis()->SetTitle("px/pBeam");
        htemp->GetXaxis()->CenterTitle();                 
        c_beamDiagnostics1->Update();

        c_beamDiagnostics1->Print("pdf/beamTotal.pdf");
    }

    if (theta3HeCM_LAB) {

        c_3helabCM = new TCanvas("c_3helabCM","3He angle LAB CM correlation",1000,1000);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle1;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data());

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle2;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data(),"same");

        htemp = (TH1F*)gPad->GetPrimitive("htemp");
        htemp->SetTitle("Total 3He lab cm correlation");
        htemp->GetXaxis()->SetTitle("theta 3He CM, deg");
        htemp->GetXaxis()->CenterTitle();
        htemp->GetYaxis()->SetTitle("theta 3He LAB, deg");
        htemp->GetYaxis()->CenterTitle();
        c_3helabCM->Update();

        c_3helabCM->Print("pdf/h3angleCorr.pdf");

        c_3helabCM_diff = new TCanvas("c_3helabCM_diff","3He angle LAB CM correlation diff",1000,1000);
        c_3helabCM_diff->Divide(2,2);

        c_3helabCM_diff->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && " + cutTriangle1;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data());
        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_1 && flag1");
        cut += " && " + cutTriangle2;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data(),"same");   
        c_3helabCM_diff->Update();

        htemp2 = (TH1F*)gPad->GetPrimitive("htemp");
        htemp2->GetXaxis()->SetRangeUser(htemp->GetXaxis()->GetXmin(),htemp->GetXaxis()->GetXmax());
        htemp2->GetYaxis()->SetRangeUser(htemp->GetYaxis()->GetXmin(),htemp->GetYaxis()->GetXmax());
        htemp2->SetTitle("1 telescope 3He lab cm correlation");
        htemp2->GetXaxis()->SetTitle("E_t");
        htemp2->GetXaxis()->CenterTitle();
        htemp2->GetYaxis()->SetTitle("7H angle CMS");
        htemp2->GetYaxis()->CenterTitle();  
        c_3helabCM_diff->Update();

       
        c_3helabCM_diff->cd(4);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && " + cutTriangle1;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data());
        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_2 && flag2");
        cut += " && " + cutTriangle2;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data(),"same");   
        c_3helabCM_diff->Update();

        htemp2 = (TH1F*)gPad->GetPrimitive("htemp");
        htemp2->GetXaxis()->SetRangeUser(htemp->GetXaxis()->GetXmin(),htemp->GetXaxis()->GetXmax());
        htemp2->GetYaxis()->SetRangeUser(htemp->GetYaxis()->GetXmin(),htemp->GetYaxis()->GetXmax());
        htemp2->SetTitle("2 telescope 3He lab cm correlation");
        htemp2->GetXaxis()->SetTitle("E_t");
        htemp2->GetXaxis()->CenterTitle();
        htemp2->GetYaxis()->SetTitle("7H angle CMS");
        htemp2->GetYaxis()->CenterTitle();  
        c_3helabCM_diff->Update();

        c_3helabCM_diff->cd(3);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && " + cutTriangle1;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data());
        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_3 && flag3");
        cut += " && " + cutTriangle2;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data(),"same");   
        c_3helabCM_diff->Update();

        htemp2 = (TH1F*)gPad->GetPrimitive("htemp");
        htemp2->GetXaxis()->SetRangeUser(htemp->GetXaxis()->GetXmin(),htemp->GetXaxis()->GetXmax());
        htemp2->GetYaxis()->SetRangeUser(htemp->GetYaxis()->GetXmin(),htemp->GetYaxis()->GetXmax());
        htemp2->SetTitle("3 telescope 3He lab cm correlation");
        htemp2->GetXaxis()->SetTitle("E_t");
        htemp2->GetXaxis()->CenterTitle();
        htemp2->GetYaxis()->SetTitle("7H angle CMS");
        htemp2->GetYaxis()->CenterTitle();  
        c_3helabCM_diff->Update();

        c_3helabCM_diff->cd(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && " + cutTriangle1;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data());
        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nhe3_4 && flag4");
        cut += " && " + cutTriangle2;
        ch1->Draw("thetahe3:thetahe3CM",cut.Data(),"same");   
        c_3helabCM_diff->Update();

        htemp2 = (TH1F*)gPad->GetPrimitive("htemp");
        htemp2->GetXaxis()->SetRangeUser(htemp->GetXaxis()->GetXmin(),htemp->GetXaxis()->GetXmax());
        htemp2->GetYaxis()->SetRangeUser(htemp->GetYaxis()->GetXmin(),htemp->GetYaxis()->GetXmax());
        htemp2->SetTitle("4 telescope 3He lab cm correlation");
        htemp2->GetXaxis()->SetTitle("E_t");
        htemp2->GetXaxis()->CenterTitle();
        htemp2->GetYaxis()->SetTitle("7H angle CMS");
        htemp2->GetYaxis()->CenterTitle();  
        c_3helabCM_diff->Update();

        c_3helabCM_diff->Print("pdf/h3angleCorr_diff.pdf");

    }

/*
    if (mm_9Li) {

        TCanvas *thickSumm = new TCanvas("thickSumm","title",1000,1000);

        thickSumm->cd();

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent &&");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += (" ( (flag1 && trigger==2 && nhe3_1)");
        cut += (" || (flag2 && trigger==3 && nhe3_2)");
        cut += (" || (flag3 && trigger==4 && nhe3_3)");
        cut += (" || (flag4 && trigger==5 && nhe3_4) )");

        ch2->Draw("1000*(mh7-8.406868788) >> MMSumm_thick(100,-7,30)",cut.Data(),"");

        ch2->SetLineColor(kRed);
        cut.Form("flagCent && nh3 &&");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
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
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("1000*(mh7-8.406868788) >> mm1",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag1 && trigger==2 && nhe3_1");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->cd(4);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        ch2->Draw("1000*(mh7-8.406868788) >> mm2",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag2 && trigger==3 && nhe3_2");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->cd(3);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 ");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        ch2->Draw("1000*(mh7-8.406868788) >> mm3",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag3 && trigger==4 && nhe3_3 ");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        ch2->Draw("1000*(mh7-8.406868788)",cut.Data(),"same");
        cMM->Update();

        cMM->cd(1);

        ch2->SetLineColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        ch2->Draw("1000*(mh7-8.406868788) >> mm4",cut.Data(),"");
        cMM->Update();

        ch2->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && flag4 && trigger==5 && nhe3_4");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
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
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3 >> bin_angle_1",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag1 && trigger==2 && nhe3_1 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        cBinary_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3 >> bin_angle_2",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag2 && trigger==3 && nhe3_2 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

       
        cBinary_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3 >> bin_angle_3",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag3 && trigger==4 && nhe3_3 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();   

        cBinary_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3 >> bin_angle_4",cut.Data(),"");
        cBinary_diff->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        ch1->SetLineColor(kRed);
        cut.Form("flagCent && flag4 && trigger==5 && nhe3_4 && nh3");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary_diff->Update();

        cBinary_diff->Print("pdf/binaryAngle_diff.pdf");

        TCanvas *cBinary = new TCanvas("cBinary","",1000,1000);
        cBinary->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        ch1->Draw("angle_bin_h3 >> bin_angle",cut.Data(),"");
        cBinary->Update();

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        ch1->Draw("angle_bin_h3",cut.Data(),"same");
        cBinary->Update();

        cBinary->Print("pdf/binaryAngle.pdf");
    }*/

    
}