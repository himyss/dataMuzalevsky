#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void draw(){
  create_IDs();
  create_cuts();

  // gStyle->SetOptStat(0);

  TH1F *htemp1;
  TH1F *htemp2;
  TH1F *htemp;
  TH2F *htemp2D;

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/mnt/data/exp1904/analysed/reco/h7/h7_old/h7*.root");
  cout << ch1->GetEntries () << " csiAnalyse" << endl;

  TChain *chThinDet = new TChain("tree"); //e4
  chThinDet->Add("/mnt/data/exp1904/analysed/reco/thinDetLarge/h7_ct_*.root"); 
  cout << chThinDet->GetEntries () << " thinDet" << endl;

  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/mnt/data/exp1904/analysed/reco/noTargetSelection/h7_ct_*.root");
  // ch1->Add("/mnt/data/exp1904/analysed/reco/h7_newBeamDet/h7_ct_*_mm_cut.root");

  TChain *ch_ect = new TChain("tree"); //e4
  ch_ect->Add("/mnt/data/exp1904/analysed/reco/emptyTarget/h7_ct_*");

  TChain *ch3 = new TChain("tree");
  ch3->Add("/mnt/data/exp1904/analysed/reco/h7_ND_cal/h7*.root");
  cout << endl << ch3->GetEntries() << endl;


  TChain *chBeam = new TChain("tree");
  // chBeam->Add("/media/ivan/data/exp1904/analysed/novPars/beamDiagnostics/beamHe8_*.root");

  cout << ch1->GetEntries() << endl;
  Int_t nEvents = ch1->GetEntries();

  ch2->SetLineColor(kRed);
  ch2->SetMarkerColor(kRed);
  ch2->SetMarkerStyle(20);
  ch2->SetLineWidth(3.);
  
  ch1->SetLineColor(kBlack);
  ch1->SetLineWidth(3.);
  ch1->SetMarkerStyle(20);

  ch1->SetLineColor(kBlack);
  ch1->SetLineWidth(3.);
  ch1->SetMarkerStyle(20);

  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*1/2",0,35);
    fa->SetLineColor(kRed);

    TF1 *fa1 = new TF1("fa1","x*4/7",0,25);
    fa->SetLineColor(kBlack);

    TF1 *fa2 = new TF1("fa2","x*2/7",0,20);
    fa2->SetLineColor(kRed);

    TF1 *f6 = new TF1("f6","x*6",-5,20);
    f6->SetLineColor(kRed);

    TF1 *f36 = new TF1("f36","x*5/9",0,25);
    f36->SetLineColor(kRed);    


    TString cut, triangleCut, hdraw;


    TString cutTriangle3("(eh3_CM*1000>(1000*(mh7-4*0.939565-2.808920)*2/7.))");

    TString cutTriangle2("(eh3_CM*1000<(0.5 + 1000*(mh6-3*0.939565-2.808920)*1./2.))");

    TString cutTriangle2_1("(eh3_CM*1000<(0.5 + 1000*(mh6-3*0.939565-2.808920)*1./4.))");


    TString cutTriangle1("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4./7.))");

    TString cutTriangle1_1("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*2./7.))");

    TString kinematicsHe7("(1000*(he4_c_cms.E()-he4_c_cms.Mag())<(1000*(mhe7-3*0.939565-3.727379)*3/7 ))");

    // TString kinematicsHe7("(1000*(he6_c_cms.E()-he6_c_cms.Mag())<(1000*(mhe7-3*0.939565-3.727379)*7/36 ))");

    // TString cutTriangle2("(eh3_CM*1000>(1000*(mh7-4*0.939565-2.808920)*2./7.))");       

    TBox *box_gs = new TBox(0., 0, 3., 190);
    box_gs->SetFillColor(kBlack-10);
    box_gs->SetLineColor(kBlack-10);

    TBox *box_es = new TBox(4., 0, 7., 190);
    box_es->SetFillColor(kRed-10);
    box_es->SetLineColor(kRed-10);

    TCanvas *c_aCM,*c_aCM_dif,*c_aLab,*c_aLab_diff,*c_triangle,*c_triangle_diff,*c_theta_1d,*c_theta_1d_diff;
    TCanvas *c_mm,*c_mm_diff,*cRangle,*cRangle_diff,*c_proj,*c_beamDiagnostics,*c_beamDiagnostics1;
    TCanvas *c_3helabCM,*c_3helabCM_diff,*c_kinTriangle_track,*c_kinTriangle_track_diff,*c_triangleSQ,*c_triangleSQ_diff;
    TCanvas *c_triangleSQ_y,*c_triangleSQ_diff_y,*c_wolski,*c_wolski_diff,*c_wolski1,*c_wolski1_diff,*c_mm_fake,*c_num;
    TCanvas *c_he7_diff,*c_he7_summ,*c_treiman;
    // Bool_t mm_7h = 0;
    // Bool_t reactionAngle = 0;
    // Bool_t tAnglevsMM = 0;
    // Bool_t tAngleLABvsMM = 0;
    // Bool_t kinTriangle = 0;
    // Bool_t distr_tAngleCM = 0;
    Bool_t mm_9Li = 0;
    Bool_t h3_binaryAngle = 0;

    Bool_t             mm_7h = 0;
    Bool_t             fake_mm_7h = 0;
    Bool_t             energies_mm = 0;
    Bool_t             fake_energies_mm = 0;
    Bool_t     reactionAngle = 0;
    Bool_t       kinTriangle = 0;
    Bool_t             mm_6h = 1;
    Bool_t             energies6h_mm = 0;
    Bool_t      tritonAngle = 0;
    Bool_t      he3_kinematics = 0;
    Bool_t      he3_ID = 0;
    Bool_t      numerical = 0;
    Bool_t             mm_7he = 0;
    Bool_t             rAngle_7He = 0;
    Bool_t             treiman_yang = 0;
    Bool_t             beamEnergy = 0;
    Bool_t tests = 0;
    // Bool_t wolskiTriangle1 = 0;


    // Bool_t             mm_7h = 1;
    // Bool_t     reactionAngle = 1;
    // Bool_t        tAnglevsMM = 1;
    // Bool_t     tAngleLABvsMM = 1;
    // Bool_t       kinTriangle = 1;
    // Bool_t    distr_tAngleCM = 0; // 
    // Bool_t h3_binaryAngle_CM = 1;
    // Bool_t   beamDiagnostics = 0; // 
    // Bool_t    theta3HeCM_LAB = 0; // 
    // Bool_t    kinTriangleSQ = 1;
    Bool_t wolskiTriangle = 0;
    Bool_t wolskiTriangle1 = 0;

        // cut += " && 1000*(mh7-4*0.939565-2.808920)>0 && 1000*(mh7-4*0.939565-2.808920)<3.";
        // cut += " && 1000*(mh7-4*0.939565-2.808920)>4 && 1000*(mh7-4*0.939565-2.808920)<7";
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";

        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17"; 

        // cut += " && (y1t*y1t+x1t*x1t)<1600";
    // 
    // cut += " && (y3t*y3t+x3t*x3t)<1600";
    // cut += " && (y4t*y4t+x4t*x4t)<1600";


    if (mm_7h) {

        c_mm = new TCanvas("c_mm","",1000,1000);
        // c_mm->Divide(2,2);

        // c_mm->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h_mm(67,0,20)",cut.Data(),"") << endl;

        cut += " && " + cutTriangle1;
        ch1->SetLineColor(kRed);
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();
return;
        // c_mm->cd(2);

        c_mm->cd(2);

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm->Update();

        cut += " && " + cutTriangle1;
        ch1->SetMarkerColor(kRed);
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

return;

        // ch1->SetLineColor(kMagenta);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && neutron>1";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();


        // ch1->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        // cut += " && thetah7CM<18 && thetah7CM>10";
        // cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();


        // c_mm->cd(2);

        // ch1->SetLineColor(kBlack);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && thetah7CM>18 && thetah7CM<25";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(50,0,20)",cut.Data(),"") << endl;
        // c_mm->Update();


        // ch_ect->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && thetah7CM>18 && thetah7CM<25";
        // cout << ch_ect->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        // cut += " && thetah7CM<12";
        // cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        // c_mm->cd(3);

        // ch1->SetLineColor(kBlack);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && thetah7CM>25";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(50,0,20)",cut.Data(),"") << endl;
        // c_mm->Update();


        // ch_ect->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        //  cut += " && thetah7CM>25";
        // cout << ch_ect->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        // c_mm->cd(4);

        // ch1->SetLineColor(kBlack);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // // cut += " && thetah7CM<18 && thetah7CM>10";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full4(50,0,20)",cut.Data(),"") << endl;
        // c_mm->Update();


        // ch_ect->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        //  // cut += " && thetah7CM>25";
        // cout << ch_ect->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();


        // ch1->SetLineColor(kRed);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        // cut += " && thetah7CM<13";
        // cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        // ch1->SetLineColor(kBlack);

        // cut.Form("flagCent && nh3");
        // cut += " && ( (nhe3_1 && flag1 && a1_1!=0 && a1_2==0 && a1_3==0 && a1_4==0)";
        // cut += " || (nhe3_2 && flag2 && a1_2!=0 && a1_1==0 && a1_3==0 && a1_4==0)";
        // cut += " || (nhe3_3 && flag3 && a1_3!=0 && a1_1==0 && a1_2==0 && a1_4==0)";
        // cut += " || (nhe3_4 && flag4 && a1_4!=0 && a1_1==0 && a1_2==0 && a1_3==0) )";

        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

/*return;


//         ch1->SetLineColor(kRed);
//         cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1_1;
//         cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
//         cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
// return;
        // ch_ect->SetLineColor(kRed);
        // cout << ch_ect->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        TH1F *tempH1 = (TH1F*)gPad->GetPrimitive("mm_full_p1");

        ofstream fout;
        fout.open("sent/mm27_35_45.txt");

        Double_t x,y;

        for(Int_t i=1;i<tempH1->GetNbinsX()+1;i++) {
            x = tempH1->GetBinCenter(i);
            y = tempH1->GetBinContent(i);
            fout << i << " " << x << " " << y << endl;
        }
        fout.close();



        // ch1->SetLineColor(kBlue);
        // cut += " && frame1X<12.5+0.5 && frame1X>-12.5+0.5";
        // cut += " && frame1Y<12.5-1.33 && frame1Y>-12.5-1.33";
        // cut += " && frame2X<12.5+0.5 && frame2X>-12.5+0.5";
        // cut += " && frame2Y<12.5-1.33 && frame2Y>-12.5-1.33";
        // cut += " && frame3X<12.5+0.5 && frame3X>-12.5+0.5";
        // cut += " && frame3Y<12.5-1.33 && frame3Y>-12.5-1.33";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        // ch1->SetLineColor(kMagenta);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && neutron";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        // ch1->SetLineColor(kGreen);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

      c_mm->Print("/home/muzalevskii/Desktop/figures/mm27_35_45.png");

        // c_mm->Print("/home/muzalevskii/Desktop/figures/mm47_0_18.pdf");
return;
        c_mm_diff = new TCanvas("c_mm_diff","",1000,1000);
        c_mm_diff->Divide(2,2);

        c_mm_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_1 && flag1");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(133,-5,25)",cut.Data(),"") << endl;

        htemp1 = (TH1F*)gPad->GetPrimitive("mm_1");
        htemp1->SetTitle("1 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();           
        c_mm_diff->Update();

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_2 && flag2");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(133,-10,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_2");
        htemp1->SetTitle("2 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();           
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_3 && flag3");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";

        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(133,-10,30)",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(133,-10,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_3");
        htemp1->SetTitle("3 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle(); 
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();                     
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_4 && flag4");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";     
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(133,-10,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_4");
        htemp1->SetTitle("4 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();  
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();   
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->Print("/home/muzalevskii/Desktop/mm_diff.png");*/
    }

    if (mm_6h) {


        c_mm = new TCanvas("c_mm","",1000,1000);
        // c_mm->Divide(2,2);

        // c_mm->cd(1);
        ch1->SetMarkerStyle(6);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && neutron>0";
        // cut += " && e_1<35 && e_2<35 && e_3<35 && e_4<35";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920) >> mm_6h(35,0,35)",cut.Data(),"") << endl;

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();


return;

        c_mm->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920)",cut.Data(),"") << endl;

        ch1->SetMarkerColor(kRed);
        cut += " && " + cutTriangle2;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

        fa->SetLineColor(kRed);
        fa->Draw("same");

        // c_mm->Print("./sent/info_6h.png");
        // c_mm->SaveAs("./sent/mm_6h.C");
  

//         c_mm->cd(2);

//         ch1->SetMarkerColor(kBlack);
//         cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
//         cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
//         //cut += " && eh3_CM*1000>0";
//         cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920) ",cut.Data(),"") << endl;
//   fa->SetLineColor(kRed);
//         fa->Draw("same");

        c_mm->cd(3);

        ch1->SetMarkerStyle(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && neutron>0";
        // cut.Form("((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5");
        cout << ch3->Draw("eNeutronCM*1000:1000*(mh6-3*0.939565-2.808920) ",cut.Data(),"") << endl;
        // cout << ch1->Draw("ND_tac:ND_amp",cut.Data(),"",1000000,0) << endl;

        // ch1->SetMarkerColor(kRed);
        // ch1->SetMarkerStyle(20);
        // cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        // cut += " && neutron>0";
        // cout << ch1->Draw("ND_tac:ND_amp","((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 && neutron","same",1000000,0) << endl;
     
        // ch3->SetMarkerColor(1);
        // cout << ch3->Draw("ND_tac:ND_amp",cut.Data(),"",1000000,0) << endl;
        // for (Int_t i = 1;i<10;i++) {
        //   cut.Form("numND==%d",i);
        //   ch3->SetMarkerColor(i+1);
        //   cout << ch3->Draw("ND_tac:ND_amp",cut.Data(),"same",1000000,0) << endl;

        // }



  f36->SetLineColor(kRed);
        f36->Draw("same");
        c_mm->Update();

        c_mm->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && neutron>0";
        cout << ch1->Draw("1000*eNeutron ",cut.Data(),"") << endl;
        c_mm->Update();
cout << " asdasd " << endl;
        // c_mm->SaveAs("info.root");
        c_mm->Print("info_6H.png");
        // c_mm->SaveAs("info_7H.C");
return;
    }


    if (energies_mm) {

        ch1->SetLineWidth(1);

        c_mm = new TCanvas("c_mm","",1000,1000);
        c_mm->Divide(3,1);

        c_mm->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        cut += " && " + cutTriangle1;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && e_1<20 && e_2<20 && e_3<20 && e_4<20";



        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";   

        cout << ch1->Draw("eh3_CM*1000 >> specHe3",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("specHe3");
        htemp1->SetTitle("3H energy in 7H CMS");
        htemp1->GetXaxis()->SetTitle("E_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.083MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        // ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && frame1X<13.1 && frame1X>-11.9";
        // // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // // cut += " && frame2X<13.1 && frame2X>-11.9";
        // // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // // cut += " && frame3X<13.1 && frame3X>-11.9";
        // // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cout << ch1->Draw("eh3_CM*1000",cut.Data(),"same") << endl;
        // c_mm->Update();


        // ch1->SetLineColor(kBlue);
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cout << ch1->Draw("eh3_CM*1000",cut.Data(),"same") << endl;
        // c_mm->Update();



        c_mm->cd(2);

        ch1->SetMarkerStyle(20);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && e_1<20 && e_2<20 && e_3<20 && e_4<20";
        cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_mm->Update();

        // ch1->SetMarkerStyle(20);
        // ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // // cut += " && frame1X<13.1 && frame1X>-11.9";
        // // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // // cut += " && frame2X<13.1 && frame2X>-11.9";
        // // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // // cut += " && frame3X<13.1 && frame3X>-11.9";
        // // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        // cut += " && " + cutTriangle1;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();
        // fa->SetLineColor(kRed);
        // fa->Draw("same");

        // ch1->SetMarkerColor(kBlue);
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();


        c_mm->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && " + cutTriangle1;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && e_1<20 && e_2<20 && e_3<20 && e_4<20";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(84,-5,20)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_full");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        // ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && frame1X<13.1 && frame1X>-11.9";
        // // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // // cut += " && frame2X<13.1 && frame2X>-11.9";
        // // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // // cut += " && frame3X<13.1 && frame3X>-11.9";
        // // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();


        // ch1->SetLineColor(kBlue);
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();

        c_mm->Print("/home/muzalevskii/Desktop/mm_info.jpg");
return;

        TCanvas *tempCanvas = new TCanvas("tempCanvas","title",1000,1000);
        tempCanvas->cd();


        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");

        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && thetah7CM>0 && thetah7CM<20";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full_temp(84,-5,20)",cut.Data(),"") << endl;
        return;

// //

//         c_mm->cd(4);
//         ch1->SetLineColor(kBlack);
//         cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
//         // cut.Form("( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe3_3 && flag3) || (nhe4_4 && flag4) )");
//         // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
//         // cut += " && " + cutTriangle1;
//         cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";

//         cout << ch1->Draw("eh3_CM*1000 >> specHe4",cut.Data(),"") << endl;
//         // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
//         htemp1 = (TH1F*)gPad->GetPrimitive("specHe4");
//         htemp1->SetTitle("3H energy in 7H CMS");
//         htemp1->GetXaxis()->SetTitle("E_MeV");
//         htemp1->GetXaxis()->CenterTitle();
//         htemp1->GetYaxis()->SetTitle("Events/0.144MeV");
//         htemp1->GetYaxis()->CenterTitle(); 

//         ch1->SetLineColor(kRed);
//         cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
//         cut += " && " + cutTriangle1;
//         cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
//         cout << ch1->Draw("eh3_CM*1000",cut.Data(),"same") << endl;
//         c_mm->Update();

//         c_mm->cd(5);

//         ch1->SetMarkerStyle(1);
//         ch1->SetMarkerColor(kBlack);
//         ch1->SetLineColor(kBlack);
//         ch1->SetLineWidth(1);
//         cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";       
//         cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> fake_triangle(84,-5,20,45,0,15)",cut.Data(),"col") << endl;
//         c_mm->Update();

//         // ch1->SetMarkerColor(kRed);
//         // cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe3_3 && flag3) || (nhe4_4 && flag4) )");
//         // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";   
//         // cut += " && " + cutTriangle1;    
//         // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        
//         fa->SetLineColor(kRed);
//         fa->Draw("same");
//         c_mm->Update();

//         c_mm->cd(6);

//         ch1->SetLineColor(kBlack);
//         cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");;
//         cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
//         cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> fake_mm_full(133,-10,30)",cut.Data(),"") << endl;
//         // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
//         htemp1 = (TH1F*)gPad->GetPrimitive("fake_mm_full");
//         htemp1->SetTitle("Total MM spectrum");
//         htemp1->GetXaxis()->SetTitle("E_t_MeV");
//         htemp1->GetXaxis()->CenterTitle();
//         htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
//         htemp1->GetYaxis()->CenterTitle(); 

//         ch1->SetLineColor(kRed);
//         cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");;
//         cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;
//         cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         c_mm->Update();

// */

        // TCanvas *c_profile = new TCanvas("c_profile","",1800,900);
        // c_profile->Divide(2,1);

        // c_profile->cd(1);
        // ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // ch1->Draw("fYt:fXt >> p1(64,-20,20,64,-20,20)",cut.Data(),"");
        // c_profile->Update();

        // ch1->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        // ch1->Draw("fYt:fXt",cut.Data(),"same");
        // c_profile->Update();


        // c_profile->cd(2);
        // ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // ch1->Draw("fYt:fXt >> p2(64,-20,20,64,-20,20)",cut.Data(),"");
        // c_profile->Update();

        // ch1->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76"; 
        // cut += " && " + cutTriangle1;       
        // ch1->Draw("fYt:fXt",cut.Data(),"same");
        // c_profile->Update();


    }

   if (fake_energies_mm) {

        c_mm_fake = new TCanvas("c_mm_fake","",1800,600);
        c_mm_fake->Divide(3,1);

        c_mm_fake->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) ) && eh3_CM*1000<15");
        // cut.Form("( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe3_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";

        cout << ch1->Draw("eh3_CM*1000 >> specHe4",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("specHe4");
        htemp1->SetTitle("3H energy in 7H CMS");
        htemp1->GetXaxis()->SetTitle("E_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.144MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && " + cutTriangle1;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("eh3_CM*1000",cut.Data(),"same") << endl;
        c_mm_fake->Update();

        c_mm_fake->cd(2);

        ch1->SetMarkerStyle(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";       
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> fake_triangle(100,-5,20,50,0,15)",cut.Data(),"col") << endl;
        c_mm_fake->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe3_3 && flag3) || (nhe4_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";   
        // cut += " && " + cutTriangle1;    
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        
        fa->SetLineColor(kRed);
        fa->Draw("same");
        c_mm_fake->Update();

        c_mm_fake->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> fake_mm_full(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("fake_mm_full");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");;
        cut += " && " + cutTriangle1;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm_fake->Update();

        c_mm_fake->Print("/home/muzalevskii/Desktop/mm_info_he4.png");

    }

    if (fake_mm_7h) {


        c_mm = new TCanvas("c_mm","",1000,1000);
        c_mm->cd();

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_full(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-3*0.939565-2.808920) >> mm_full(84,-10,20)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_full");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle(); 


        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

// return;
        c_mm->Print("/home/muzalevskii/Desktop/mm_full.png");
// return;
        c_mm_diff = new TCanvas("c_mm_diff","",1000,1000);
        c_mm_diff->Divide(2,2);

        c_mm_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe4_1 && flag1");
        // cut.Form("nhe4_1 && flag1");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_1");
        htemp1->SetTitle("1 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();           
        c_mm_diff->Update();

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe4_2 && flag2");
        // cut.Form("nhe4_2 && flag2");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_2");
        htemp1->SetTitle("2 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();           
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe4_3 && flag3");
        // cut.Form("nhe4_3 && flag3");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(100,-33,30)",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(133,-10,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_3");
        htemp1->SetTitle("3 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle(); 
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();                     
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nhe4_4 && flag4");
        // cut.Form("nhe4_4 && flag4");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;  
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";     
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(133,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_4");
        htemp1->SetTitle("4 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();  
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();   
        c_mm_diff->Update();    

        ch1->SetLineColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;

        c_mm_diff->Print("/home/muzalevskii/Desktop/mm_diff.png");
    }


    if (reactionAngle) {


        cRangle = new TCanvas("cRangle","",1000,1000);
        // cRangle->Divide(2,1);
        cRangle->cd();

//         htemp1 = (TH1F*)gPad->GetPrimitive("distrRangle");
//         htemp1->SetTitle("Reaction Angle CM");
//         htemp1->GetXaxis()->SetTitle("rAngle_deg");
//         htemp1->GetXaxis()->CenterTitle();  
//         htemp1->GetYaxis()->SetTitle("Events/1deg");
//         htemp1->GetYaxis()->CenterTitle();   
//         cRangle->Update();    

//         cRangle->Update();  

//         ch1->SetLineColor(kRed);
//         cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
//         // cut += " && frame1X<13.1 && frame1X>-11.9";
//         // cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         // cut += " && frame2X<13.1 && frame2X>-11.9";
//         // cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         // cut += " && frame3X<13.1 && frame3X>-11.9";
//         // cut += " && frame3Y<13.24 && frame3Y>-11.76";
//         cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;
//         cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
//         cRangle->Update();  


//         ch1->SetLineColor(kBlue);
//         cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76"; 
//         cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;
//         cout << ch1->Draw("thetah7CM",cut.Data(),"same") << endl;
//         cRangle->Update();  

        TH2F *hfake_0 = new TH2F("hfake_1","Total reaction angle vs MM",10000,0,20,10000,0.,45);
        hfake_0->GetXaxis()->SetTitle("E_t_MeV");
        hfake_0->GetXaxis()->CenterTitle();
        hfake_0->GetYaxis()->SetTitle("7H angle CMS");
        hfake_0->GetYaxis()->CenterTitle();
        hfake_0->GetYaxis()->SetTitleOffset(1.3);

        box_gs->SetY2(45.);
        box_es->SetY2(45.);
        box_gs->SetY1(0.);
        box_es->SetY1(0.);

        //hfake_0->Draw();

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch2->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        cRangle->Update();

        TGraph *gtemp = (TGraph*)gPad->GetPrimitive("Graph");

        ofstream fout;
        fout.open("sent/rAngle_ect.txt");

        Double_t x,y;

        for(Int_t i=0;i<gtemp->GetN();i++) {
            gtemp->GetPoint(i,x,y);
            fout << i << " " << x << " " << y << endl;
        }
        fout.close();

  cRangle->Print("rAngle_ect.png");
return;
        ch2->SetMarkerColor(kRed);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch2->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        cRangle->Update();


return;
        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && " + cutTriangle1;
        // cut += " && frame1X<12.5+0.5 && frame1X>-12.5+0.5";
        // cut += " && frame1Y<12.5-1.33 && frame1Y>-12.5-1.33";
        // cut += " && frame2X<12.5+0.5 && frame2X>-12.5+0.5";
        // cut += " && frame2Y<12.5-1.33 && frame2Y>-12.5-1.33";
        // cut += " && frame3X<12.5+0.5 && frame3X>-12.5+0.5";
        // cut += " && frame3Y<12.5-1.33 && frame3Y>-12.5-1.33";
        // cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // cRangle->Update();


        // ch1->SetMarkerColor(kMagenta);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && " + cutTriangle1;
        // cut += " && neutron==1";
        // cut += " && frame1X<12.5+0.5 && frame1X>-12.5+0.5";
        // cut += " && frame1Y<12.5-1.33 && frame1Y>-12.5-1.33";
        // cut += " && frame2X<12.5+0.5 && frame2X>-12.5+0.5";
        // cut += " && frame2Y<12.5-1.33 && frame2Y>-12.5-1.33";
        // cut += " && frame3X<12.5+0.5 && frame3X>-12.5+0.5";
        // cut += " && frame3Y<12.5-1.33 && frame3Y>-12.5-1.33";
        // cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // cRangle->Update();


        // ch1->SetMarkerColor(kGreen);
        // ch1->SetMarkerStyle(20);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";; 
        // cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // cRangle->Update();

//         cRangle->Print("/home/muzalevskii/Desktop/rAngle.png"); 

// return;
//         cRangle_diff = new TCanvas("cRangle_diff","",1000,1000);
//         cRangle_diff->Divide(2,2);

//         cRangle_diff->cd(2);

//         hfake_0->Draw();
//         // box_gs->Draw("same");
//         // box_es->Draw("same");

//         ch1->SetMarkerColor(kBlack);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76";       
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         // htemp1 = (TH1F*)gPad->GetPrimitive("htemp");
//         // htemp1->SetTitle("1 Telescope correlation");
//         // htemp1->GetYaxis()->SetTitle("rAngle_deg");
//         // htemp1->GetYaxis()->CenterTitle();  
//         // htemp1->GetXaxis()->SetTitle("E_t_MeV");
//         // htemp1->GetXaxis()->CenterTitle();            
//         cRangle_diff->Update();

//         ch1->SetMarkerColor(kRed);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76";         
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         cRangle_diff->Update();

//         cRangle_diff->cd(4);
//         hfake_0->Draw();

//         ch1->SetMarkerColor(kBlack);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76";        
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         // htemp1 = (TH1F*)gPad->GetPrimitive("htemp");
//         // htemp1->SetTitle("2 Telescope correlation");
//         // htemp1->GetYaxis()->SetTitle("rAngle_deg");
//         // htemp1->GetYaxis()->CenterTitle();  
//         // htemp1->GetXaxis()->SetTitle("E_t_MeV");
//         // htemp1->GetXaxis()->CenterTitle();          
//         cRangle_diff->Update();

//         ch1->SetMarkerColor(kRed);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;      
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76"; 
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         cRangle_diff->Update();    

//         cRangle_diff->cd(3);
//         hfake_0->Draw();

//         ch1->SetMarkerColor(kBlack);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76";         
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         // htemp1 = (TH1F*)gPad->GetPrimitive("htemp");
//         // htemp1->SetTitle("3 Telescope correlation");
//         // htemp1->GetYaxis()->SetTitle("rAngle_deg");
//         // htemp1->GetYaxis()->CenterTitle();  
//         // htemp1->GetXaxis()->SetTitle("E_t_MeV");
//         // htemp1->GetXaxis()->CenterTitle();        
//         cRangle_diff->Update();

//         ch1->SetMarkerColor(kRed);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76"; 
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         cRangle_diff->Update();    

//         cRangle_diff->cd(1);
//         hfake_0->Draw();
//         // hfake_0->Draw();
//         // box_gs->Draw("same");
//         // box_es->Draw("same");

//         ch1->SetMarkerColor(kBlack);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76"; 
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         // htemp1 = (TH1F*)gPad->GetPrimitive("htemp");
//         // htemp1->SetTitle("4 Telescope correlation");
//         // htemp1->GetYaxis()->SetTitle("rAngle_deg");
//         // htemp1->GetYaxis()->CenterTitle();  
//         // htemp1->GetXaxis()->SetTitle("E_t_MeV");
//         // htemp1->GetXaxis()->CenterTitle();         
//         cRangle_diff->Update();

//         ch1->SetMarkerColor(kRed);
//         cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
//         // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
//         cut += " && " + cutTriangle1;
//         cut += " && frame1X<13.1 && frame1X>-11.9";
//         cut += " && frame1Y<13.24 && frame1Y>-11.76";
//         cut += " && frame2X<13.1 && frame2X>-11.9";
//         cut += " && frame2Y<13.24 && frame2Y>-11.76";
//         cut += " && frame3X<13.1 && frame3X>-11.9";
//         cut += " && frame3Y<13.24 && frame3Y>-11.76";         
//         cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
//         cRangle_diff->Update();

//         cRangle_diff->Print("/home/muzalevskii/Desktop/rAngle_diff.png");
    }

    if (energies6h_mm) {

        c_mm = new TCanvas("c_mm","",1800,1000);
/*        c_mm->Divide(3,1);

        c_mm->cd(1);

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut.Form("( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";   

        cout << ch1->Draw("thetah6CM:1000*(mh6-3*0.939565-2.808920) >> specHe3",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-3*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("specHe3");
        htemp1->SetTitle("3H energy in 6H CMS");
        htemp1->GetXaxis()->SetTitle("E_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.144MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && " + cutTriangle2;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("thetah6CM:1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();

        c_mm->cd(2);

        ch1->SetMarkerStyle(20);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920) >> htriangle(60,-10,30,40,0,20)",cut.Data(),"col") << endl;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920) >> htriangle(120,-10,30,80,0,20)",cut.Data(),"col") << endl;
        c_mm->Update();

        ch1->SetMarkerStyle(20);
        ch1->SetMarkerColor(kMagenta);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        // cut += " && " + cutTriangle2;
        cut += " && neutron";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();
        fa->SetLineColor(kRed);
        fa->Draw("same");

        fa1->SetLineColor(kRed);
        fa1->Draw("same");


        c_mm->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920) >> mm_full(40,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-3*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_full");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.4MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && " + cutTriangle2;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();


        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && " + cutTriangle2_1;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();


        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");

        cut += " && " + cutTriangle2;
        cut += " && neutron";
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();


// 
return;*/


        c_mm->Divide(2,1);

        c_mm->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && thetah6CM>=16";
        cut += " && " + cutTriangle2;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920) >> mm_full(40,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-3*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_full");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.4MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        ch_ect->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && thetah6CM>=16";
        cut += " && " + cutTriangle2;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch_ect->Draw("1000*(mh6-3*0.939565-2.808920) >> mm_ect",cut.Data(),"same") << endl;
        c_mm->Update();

        TH1F *htemp1D = (TH1F*)gPad->GetPrimitive("mm_ect");
        TH1F *hClone = (TH1F*)htemp1D->Clone();

        Int_t amp = 6;
        for (Int_t i=1;i<hClone->GetNbinsX();i++) {
            hClone->SetBinContent(i,amp*htemp1D->GetBinContent(i));
        } 


        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";
        cut += " && thetah6CM>=16";
        cut += " && " + cutTriangle2;
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920) >> mm_full1(40,-10,30)",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-3*0.939565-2.808920) >> mm_full(100,-33,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_full1");
        htemp1->SetTitle("Total MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.4MeV");
        htemp1->GetYaxis()->CenterTitle(); 

        hClone->SetLineColor(kRed);
        hClone->Draw("same");


        c_mm->cd(2);


        ch1->SetMarkerStyle(20);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cut += " && thetah6CM>=16";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920) >> htriangle(60,-10,30,40,0,20)",cut.Data(),"col") << endl;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920) >> htriangle(120,-10,30,80,0,20)",cut.Data(),"col") << endl;
        c_mm->Update();



        ch_ect->SetMarkerStyle(20);
        ch_ect->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cut += " && thetah6CM>=16";
        // cut += " && frame1X<13.1 && frame1X>-11.9";
        // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // cut += " && frame2X<13.1 && frame2X>-11.9";
        // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // cut += " && frame3X<13.1 && frame3X>-11.9";
        // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        cout << ch_ect->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920) >> htriangle(120,-10,30,80,0,20)",cut.Data(),"col") << endl;
        c_mm->Update();

        // ch1->SetMarkerStyle(20);
        // ch1->SetMarkerColor(kMagenta);
        // cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        // // cut += " && frame1X<13.1 && frame1X>-11.9";
        // // cut += " && frame1Y<13.24 && frame1Y>-11.76";
        // // cut += " && frame2X<13.1 && frame2X>-11.9";
        // // cut += " && frame2Y<13.24 && frame2Y>-11.76";
        // // cut += " && frame3X<13.1 && frame3X>-11.9";
        // // cut += " && frame3Y<13.24 && frame3Y>-11.76";        
        // // cut += " && " + cutTriangle2;
        // cut += " && neutron";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();
        fa->SetLineColor(kRed);
        fa->Draw("same");

        fa1->SetLineColor(kRed);
        fa1->Draw("same");



        return;


        ch1->SetLineColor(kMagenta);
        cut.Form("nh3 && flagCent && ( (nhe4_1 && flag1) || (nhe4_2 && flag2) || (nhe4_3 && flag3) || (nhe4_4 && flag4) )");

        cut += " && " + cutTriangle2;
        cut += " && neutron";
        cut += " && e_1<25 && e_2<25&& e_3<25 && e_4<25";
        cout << ch1->Draw("1000*(mh6-3*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_mm->Update();
//        

        // c_mm->Print("/home/muzalevskii/Desktop/mm_info.png");

    }

    if (kinTriangle) {


        TH2F *hfake_1 = new TH2F("hfake_1","Total reaction angle vs MM",10000,-5,20,10000,0.,15);

        c_triangle = new TCanvas("c_triangle","",1800,1000);
        // c_triangle->Divide(2,1);

        c_triangle->cd();

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_triangle->Update();

        ch2->SetMarkerColor(kRed);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        //cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.*8. ";
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        fa1->Draw("same");
        // fa2->Draw("same");
  c_triangle->Print("triangle_antiCut.png");

return;

        ch_ect->SetMarkerColor(kGreen);
        ch_ect->SetMarkerStyle(20);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cout << ch_ect->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        fa1->Draw("same");
        fa2->Draw("same");

        c_triangle->cd(2);

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;

        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5-2.4 && frame1Y>-12.5-2.4";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5-2.4 && frame2Y>-12.5-2.4";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5-2.4 && frame3Y>-12.5-2.4";

        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_triangle->Update();


        fa1->Draw("same");
        fa2->Draw("same");


        ch_ect->SetMarkerColor(kGreen);
        ch_ect->SetMarkerStyle(20);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5-2.4 && frame1Y>-12.5-2.4";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5-2.4 && frame2Y>-12.5-2.4";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5-2.4 && frame3Y>-12.5-2.4";        
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        cout << ch_ect->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        fa1->Draw("same");
        fa2->Draw("same");


        c_triangle->cd(3);

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_triangle->Update();

        ch_ect->SetMarkerColor(kGreen);
        ch_ect->SetMarkerStyle(20);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        cout << ch_ect->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        c_triangle->cd(4);

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";

        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5-2.4 && frame1Y>-12.5-2.4";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5-2.4 && frame2Y>-12.5-2.4";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5-2.4 && frame3Y>-12.5-2.4";

        cout << ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_triangle->Update();

        ch_ect->SetMarkerColor(kGreen);
        ch_ect->SetMarkerStyle(20);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5-2.4 && frame1Y>-12.5-2.4";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5-2.4 && frame2Y>-12.5-2.4";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5-2.4 && frame3Y>-12.5-2.4";        
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && ((fXf)*(fXf) + (fYf)*(fYf))<12.*12.";
        cout << ch_ect->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        c_triangle->Update();

        // ch1->SetMarkerColor(kBlack);
        // cut.Form("flagCent && nh3");
        // cut += " && ( (nhe3_1 && flag1 && a1_1!=0 && a1_2==0 && a1_3==0 && a1_4==0)";
        // cut += " || (nhe3_2 && flag2 && a1_2!=0 && a1_1==0 && a1_3==0 && a1_4==0)";
        // cut += " || (nhe3_3 && flag3 && a1_3!=0 && a1_1==0 && a1_2==0 && a1_4==0)";
        // cut += " || (nhe3_4 && flag4 && a1_4!=0 && a1_1==0 && a1_2==0 && a1_3==0) )";

        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_mm->Update();


        // ch1->SetMarkerColor(kBlue);
        // cut += " && frame1X<12.5+0.5 && frame1X>-12.5+0.5";
        // cut += " && frame1Y<12.5-1.33 && frame1Y>-12.5-1.33";
        // cut += " && frame2X<12.5+0.5 && frame2X>-12.5+0.5";
        // cut += " && frame2Y<12.5-1.33 && frame2Y>-12.5-1.33";
        // cut += " && frame3X<12.5+0.5 && frame3X>-12.5+0.5";
        // cut += " && frame3Y<12.5-1.33 && frame3Y>-12.5-1.33";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle->Update();


        // ch1->SetMarkerColor(kMagenta);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && neutron";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle->Update();

        // ch1->SetMarkerColor(kYellow);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cut += " && neutron";
        // cut += " && tacND<500";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle->Update();




        // ch1->SetMarkerColor(kGreen);
        // ch1->SetMarkerStyle(20);
        // cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // c_triangle->Update();

        // c_triangle->Print("/home/muzalevskii/Desktop/triangle.png");

return;

        c_triangle_diff = new TCanvas("c_triangle_diff","",1000,1000);
        c_triangle_diff->Divide(2,2);

        c_triangle_diff->cd(2);
        hfake_1->Draw();
        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_1 && flag1");
        // cut.Form("nhe3_1 && flag1");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle1",cut.Data(),"same") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(133,-10,30)",cut.Data(),"") << endl;          
        c_triangle_diff->Update();

        ch1->SetMarkerColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        fa->Draw("same");


        c_triangle_diff->cd(4);

        hfake_1->Draw();

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_2 && flag2");
        // cut.Form("nhe3_2 && flag2");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle2",cut.Data(),"same") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(133,-10,30)",cut.Data(),"") << endl;          
        c_triangle_diff->Update();    

        ch1->SetMarkerColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        fa->Draw("same");


        c_triangle_diff->cd(3);
        hfake_1->Draw();

        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_3 && flag3");
        // cut.Form("nhe3_3 && flag3");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(133,-10,30)",cut.Data(),"") << endl;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle3",cut.Data(),"same") << endl;                    
        c_triangle_diff->Update();    

        ch1->SetMarkerColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        fa->Draw("same");


        c_triangle_diff->cd(1);
        hfake_1->Draw();
        ch1->SetMarkerColor(kBlack);
        cut.Form("flagCent && nh3 && nhe3_4 && flag4");
        // cut.Form("nhe3_4 && flag4");
        // cut += " && (fXt*fXt + fYt*fYt)<10*10 ";
        // cut += " && " + cutTriangle1;  
        // cut += " && thetah7CM>0 && thetah7CM<20";
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";     
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle4",cut.Data(),"same") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(133,-10,30)",cut.Data(),"") << endl;  
        c_triangle_diff->Update();    

        ch1->SetMarkerColor(kRed);
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        fa->Draw("same");

    }

    if (tritonAngle) {

        box_gs->SetY2(1.);
        box_es->SetY2(1.);
        box_gs->SetY1(-1.);
        box_es->SetY1(-1.);


        c_aCM = new TCanvas("c_aCM","",1800,1000); 
        c_aCM->Divide(2,1);

        // c_aCM->cd(1);

        // ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cout << ch1->Draw("thetah3CM >> (30,0,180)",cut.Data(),"") << endl;
        // c_aCM->Update();    

        // ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cut += " && " + cutTriangle1;
        // cout << ch1->Draw("thetah3CM",cut.Data(),"same") << endl;
        // c_aCM->Update();  

        // c_aCM->cd(2);

        // TH2F *hfake_1 = new TH2F("hfake_1","Total cos(3H_CM) vs MM",10000,-5,20,10000,-1.,1);
        // hfake_1->Draw();
        // hfake_1->GetXaxis()->SetTitle("E_t");
        // hfake_1->GetXaxis()->CenterTitle();
        // hfake_1->GetYaxis()->SetTitle("cos(3H_CM)");
        // hfake_1->GetYaxis()->CenterTitle();
        // hfake_1->GetYaxis()->SetTitleOffset(1.3);

        // ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
       


        // c_aCM->Update();    

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        c_aCM->Update();         

        TGraph *gtemp = (TGraph*)gPad->GetPrimitive("Graph");

        ofstream fout;
        fout.open("sent/cos3H_MM_triangle.txt");

        Double_t x,y;

        for(Int_t i=0;i<gtemp->GetN()+1;i++) {
            gtemp->GetPoint(i+1,x,y);
            fout << i+1 << " " << x << " " << y << endl;
        }
        fout.close();

        // c_aCM->Print("/home/muzalevskii/Desktop/triton_angles.png");

    }

    if (he3_kinematics) {

        c_aLab = new TCanvas("c_aLab","title");
        // c_aLab->Divide(2,1);

        // c_aLab->cd(1);

        // ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        // // cut += " && " + cutTriangle1;
        // cout << ch1->Draw("ehe3*1000:angle_he3_he8",cut.Data(),"") << endl;
        // c_aLab->Update();         

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
  cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<8.5*8.5 ";
        cut += " && " + cutTriangle1;
        cout << ch1->Draw("ehe3*1000:angle_he3_he8",cut.Data(),"") << endl;
        c_aLab->Update(); 

        c_aLab->Print("kin3He.png");
return;

   
    }


    if (he3_ID) {

        TCanvas *c_id = new TCanvas("c_id","title",1000,1000);

        c_id->cd();

        ch1->SetMarkerStyle(7);
        // cut.Form("flag1 && a1_1+a20_1_un<65 && a20_1<8");
        // hdraw.Form("a20_1:a1_1+a20_1_un>>h1(500,0,15,500,0,1.5)");
        // ch1->Draw(hdraw.Data(),cut.Data(),"",5000000,0);
        // c_id->Update();
        

        ch1->SetMarkerStyle(1);
        // ch1->SetMarkerColor(kRed);
        cut.Form("flagCent");
        // cut += " && nh3_1";
        hdraw.Form("X_C:arCsI[%s] >>(500,0,200,500,0,80)","nCsI_track");
        ch1->Draw(hdraw.Data(),cut.Data(),"col",1000000,0);
        // cut3h_1->Draw("same");
        c_id->Update();

    }

    if (mm_7he) {

        c_he7_summ = new TCanvas("c_he7","",1800,1000);
        c_he7_summ->Divide(2,1);

        c_he7_summ->cd(1);

        ch1->SetLineColor(kBlue);
        cut.Form("nAlpha && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) )");
        cut += " && 1000*(he4_c_cms.E()-he4_c_cms.Mag())<15";
        cut += " && frame1X<13. && frame1X>-12.";
        cut += " && frame1Y<11.2 && frame1Y>-13.8";
        cut += " && frame2X<13. && frame2X>-12.";
        cut += " && frame2Y<11.2 && frame2Y>-13.8";
        cut += " && frame3X<13. && frame3X>-12.";
        cut += " && frame3Y<11.2 && frame3Y>-13.8";        
        cout << ch1->Draw("1000*(mhe7-3*0.939565-3.727379) >> mm_he7_full(100,0,30)",cut.Data(),"") << endl;
        c_he7_summ->Update();

        ch1->SetLineColor(kMagenta);
        cut.Form("nAlpha && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) ) && ");
        cut += kinematicsHe7;
        cut += " && 1000*(he4_c_cms.E()-he4_c_cms.Mag())<15";
        cut += " && frame1X<13. && frame1X>-12.";
        cut += " && frame1Y<11.2 && frame1Y>-13.8";
        cut += " && frame2X<13. && frame2X>-12.";
        cut += " && frame2Y<11.2 && frame2Y>-13.8";
        cut += " && frame3X<13. && frame3X>-12.";
        cut += " && frame3Y<11.2 && frame3Y>-13.8";         
        cout << ch1->Draw("1000*(mhe7-3*0.939565-3.727379)",cut.Data(),"same") << endl;
        c_he7_summ->Update();

        c_he7_summ->cd(2);

        ch1->SetMarkerColor(kBlue);
        cut.Form("nAlpha && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) )");
        cut += " && 1000*(he4_c_cms.E()-he4_c_cms.Mag())<15";
        cut += " && frame1X<13. && frame1X>-12.";
        cut += " && frame1Y<11.2 && frame1Y>-13.8";
        cut += " && frame2X<13. && frame2X>-12.";
        cut += " && frame2Y<11.2 && frame2Y>-13.8";
        cut += " && frame3X<13. && frame3X>-12.";
        cut += " && frame3Y<11.2 && frame3Y>-13.8";     
        cout << ch1->Draw("1000*(he4_c_cms.E()-he4_c_cms.Mag()):1000*(mhe7-3*0.939565-3.727379)",cut.Data(),"") << endl;
        c_he7_summ->Update();

        ch1->SetMarkerColor(kMagenta);
        cut.Form("nAlpha && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) ) && ");
        cut += kinematicsHe7;
        cut += " && 1000*(he4_c_cms.E()-he4_c_cms.Mag())<15";
        cut += " && frame1X<13. && frame1X>-12.";
        cut += " && frame1Y<11.2 && frame1Y>-13.8";
        cut += " && frame2X<13. && frame2X>-12.";
        cut += " && frame2Y<11.2 && frame2Y>-13.8";
        cut += " && frame3X<13. && frame3X>-12.";
        cut += " && frame3Y<11.2 && frame3Y>-13.8";          
        cout << ch1->Draw("1000*(he4_c_cms.E()-he4_c_cms.Mag()):1000*(mhe7-3*0.939565-3.727379)",cut.Data(),"same") << endl;
        fa->Draw("same");
        c_he7_summ->Update();
return;
        c_he7_diff = new TCanvas("c_he7_diff","",1000,1000);
        c_he7_diff->Divide(2,2);

        c_he7_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("nAlpha && flagCent && nh3_1 && flag1");
        cout << ch1->Draw("1000*(mhe7-3*0.939565-3.727379) >> mm_he7_1(100,0,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_he7_1");
        htemp1->SetTitle("1 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();           
        c_he7_diff->Update();

        c_he7_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("nAlpha && flagCent && nh3_2 && flag2");
        cout << ch1->Draw("1000*(mhe7-3*0.939565-3.727379) >> mm_he7_2(100,0,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_he7_2");
        htemp1->SetTitle("2 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle();
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();           
        c_he7_diff->Update();    

        c_he7_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nAlpha && flagCent && nh3_3 && flag3");
        cout << ch1->Draw("1000*(mhe7-3*0.939565-3.727379) >> mm_he7_3(100,0,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_he7_3");
        htemp1->SetTitle("3 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t");
        htemp1->GetXaxis()->CenterTitle(); 
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();                     
        c_he7_diff->Update();    

        c_he7_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nAlpha && flagCent && nh3_4 && flag4");    
        cout << ch1->Draw("1000*(mhe7-3*0.939565-3.727379) >> mm_he7_4(100,0,30)",cut.Data(),"") << endl;
        htemp1 = (TH1F*)gPad->GetPrimitive("mm_he7_4");
        htemp1->SetTitle("4 Telescope MM spectrum");
        htemp1->GetXaxis()->SetTitle("E_t_MeV");
        htemp1->GetXaxis()->CenterTitle();  
        htemp1->GetYaxis()->SetTitle("Events/0.3MeV");
        htemp1->GetYaxis()->CenterTitle();   
        fa->Draw("same");
        c_he7_diff->Update(); 

c_he7_diff->Print("/home/muzalevskii/Desktop/mm7he_he3_decay_diff.png");
    }   

    if (rAngle_7He) {

        c_he7_summ = new TCanvas("c_he7","",1800,1000);
        c_he7_summ->Divide(2,1);

        c_he7_summ->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nhe6 && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) )");   
        cout << ch1->Draw("180-h3_side_CMS.Theta()*TMath::RadToDeg()>>distrRangle(25,0,25)",cut.Data(),"") << endl;
        c_he7_summ->Update();

        htemp1 = (TH1F*)gPad->GetPrimitive("distrRangle");
        htemp1->SetTitle("Reaction Angle CM");
        htemp1->GetXaxis()->SetTitle("rAngle_deg");
        htemp1->GetXaxis()->CenterTitle();  
        htemp1->GetYaxis()->SetTitle("Events/1deg");
        htemp1->GetYaxis()->CenterTitle();  

        ch1->SetLineColor(kRed);
        cut.Form("nhe6 && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) ) && ");
        cut += kinematicsHe7;        
        cout << ch1->Draw("180-h3_side_CMS.Theta()*TMath::RadToDeg()",cut.Data(),"same") << endl;
        c_he7_summ->Update();

        c_he7_summ->cd(2);

        ch1->SetMarkerColor(kBlack);
        cut.Form("nhe6 && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) )");  
        cout << ch1->Draw("180-h3_side_CMS.Theta()*TMath::RadToDeg():1000*(mhe7-3*0.939565-3.727379)",cut.Data(),"") << endl;
        c_he7_summ->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nhe6 && flagCent && ( (nh3_1 && flag1) || (nh3_2 && flag2) || (nh3_3 && flag3) || (nh3_4 && flag4) ) && ");
        cut += kinematicsHe7;        
        cout << ch1->Draw("180-h3_side_CMS.Theta()*TMath::RadToDeg():1000*(mhe7-3*0.939565-3.727379)",cut.Data(),"same") << endl;
        c_he7_summ->Update();

        c_he7_summ->Print("/home/muzalevskii/Desktop/sent/rAngle_7He.png");

return;

    }

    if (treiman_yang) {

        ch_ect->SetLineWidth(3);

        TCanvas *c_treiman = new TCanvas("c_treiman","title",1000,1000);

        c_treiman->Divide(2,2);

        c_treiman->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";
        cut += " && 1000*(mh7-4*0.939565-2.808920)<6.5";
        cout << ch1->Draw("cos(lv_h3Frame7h.Theta()) >> h1(10,-1,1)",cut.Data()) << endl;
        c_treiman->Update();

        c_treiman->cd(2);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";   
        cut += " && 1000*(mh7-4*0.939565-2.808920)<6.5";   
        cout << ch1->Draw("lv_h3Frame7h.Phi()*TMath::RadToDeg()>> h2(20,-180,180)",cut.Data()) << endl;
        c_treiman->Update();

        c_treiman->cd(3);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";      
        cout << ch1->Draw("1000*(lv_h3Frame7h.T()-lv_h3Frame7h.Mag())",cut.Data()) << endl;
        c_treiman->Update();

        c_treiman->cd(4);
        cut.Form("flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && e_1<25 && e_2<25 && e_3<25 && e_4<25";
        cut += " && " + cutTriangle1;
        cut += " && ((fXt-0.467)*(fXt-0.467) + (fYt-0.026)*(fYt-0.026))<9*9 ";      
        cout << ch1->Draw("1000*(lv_h3Frame7h.Mag())",cut.Data()) << endl;
        c_treiman->Update();

    }

    if (beamEnergy) {

        TCanvas *c_beamEnergy = new TCanvas("c_beamEnergy","title",1000,1000);
        c_beamEnergy->Divide(4,4);

        for (Int_t i =0;i<16;i++) {

            c_beamEnergy->cd(i+1);

            ch3->SetLineColor(kBlack);
            cut.Form("trigger==1 && nCsI_track==%d && flagCent && 1000*ehe8>190 && 1000*ehe8<195",i,i);
            hdraw.Form("arCsI[%d] >>h%d_cut",i,i);
            ch3->Draw(hdraw.Data(),cut.Data(),"",15999650,0);
            c_beamEnergy->Update(); 

            ch3->SetLineColor(kRed);
            cut.Form("trigger==1 && nCsI_track==%d && flagCent && 1000*ehe8>190 && 1000*ehe8<195",i,i);
            hdraw.Form("arCsI[%d]",i,i);
            ch3->Draw(hdraw.Data(),cut.Data(),"same",15999650,15999650);
            c_beamEnergy->Update();

            ch3->SetLineColor(kBlue);
            cut.Form("trigger==1 && nCsI_track==%d && flagCent && 1000*ehe8>190 && 1000*ehe8<195",i,i);
            hdraw.Form("arCsI[%d]",i,i);
            ch3->Draw(hdraw.Data(),cut.Data(),"same",15999651,31999300);
            c_beamEnergy->Update();
        
        }

    }

    if (tests) {

        TCanvas *c_test = new TCanvas("c_test","title",1000,1000);
        c_test->Divide(2,1); 

        c_test->cd(1);
        ch1->SetMarkerStyle(8);
        ch1->SetMarkerColor(kBlack);
        ch1->Draw("1000*eNeutron:centE","tND_cal>0 && neutron && flagCent && nhe6","");
        c_test->Update();

  ch1->SetMarkerColor(kRed);
        ch1->Draw("1000*eNeutron:centE","trigger==1 && tND_cal>0 && neutron && flagCent && nhe6","same");
        c_test->Update();

        c_test->cd(2);
        ch1->SetMarkerStyle(8);
        ch1->SetMarkerColor(kBlack);
        ch1->Draw("1000*eNeutron:centE","tND_cal>0 && neutron && flagCent && nAlpha","");
        c_test->Update();

       ch1->SetMarkerColor(kRed);
        ch1->Draw("1000*eNeutron:centE","trigger==1 && tND_cal>0 && neutron && flagCent && nAlpha","same");
        c_test->Update();

        // c_test->cd(2);
        // ch1->SetMarkerStyle(1);
        // ch1->SetLineColor(kBlack);
        // ch1->Draw("1000*eNeutron>> e1(100,0,100)","tND_cal>0 && neutron && flagCent && (nhe6 || nAlpha)");
        // c_test->Update();


        // c_test->cd(3);
        // ch2->SetMarkerStyle(1);
        // ch2->SetLineColor(kBlack);
        // ch2->Draw("tND_cal-targetTime >> tof2(100,0,100)","tND_cal>0 && neutron && flagCent && (nhe6 || nAlpha)","");
        // c_test->Update();

        // c_test->cd(4);
        // ch2->SetMarkerStyle(1);
        // ch2->SetLineColor(kBlack);
        // ch2->Draw("1000*eNeutron>> e2(100,0,100)","tND_cal>0 && neutron && flagCent && (nhe6 || nAlpha)");
        // c_test->Update();

        c_test->SaveAs("canvasEnergies1.root");

    }



} 
