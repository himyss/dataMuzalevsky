void drawAngles(){
  gStyle->SetOptStat(0);

  TCutG *mmCut;
  TFile *f1;

  Bool_t MM,angles,nikolski,kin;
  MM = 0;
  angles = 1;
  nikolski = 0;
  kin = 0;


  // TFile *file1 = new TFile("/media/ivan/data/exp1904/analysed/oldPars/mm_400_25_new.root");
  // TTree *tr = (TTree*)file1->Get("treeNew");

  // tr->AddFriend("tree","/media/ivan/data/exp1904/analysed/oldPars/mm_400.root");


  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/eTarget/h7_ct_*_mm_frame_newPars.root");
  cout << ch2->GetEntries() << endl;

  // ch2->AddFriend("treeNew","/media/ivan/data/exp1904/analysed/oldPars/mm_400_25_new.root");

  TChain *ch3 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/eTarget/h7_ect_*_mm_frame.root");
  ch3->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/coin6He/h7_ct_*_mm_frame_newPars.root");
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/h7_ct_*_mm_frame_newPars.root");


  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/eTarget/h7_ect_*_mm_frame.root");
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/targetCut/13/h7_ct_*_mm_frame_newPars.root");
  // ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/h7_ct_6Li_*_mm_frame_newPars.root");


  TChain *ch4 = new TChain("tree");
  ch4->Add("/media/ivan/data/exp1904/analysed/novPars/reco/h7_ct_6Li_*_mm_frame_newPars.root");


  cout << ch1->GetEntries() << endl;
  Int_t nEvents = ch1->GetEntries();
  // ch1->SetName("treeNew");
  // cout << ch1->GetName() << endl;
  // return;
// return;
  // TChain *ch2 = new TChain("tree"); //e4
  // ch2->Add("/home/oem/work/data/exp1811/analysed/he8_emtpytarget_mm.root");
  // cout << ch1->GetEntries() << " total number of Entries" << endl;
// return;
    ch2->SetLineColor(kRed);
    ch2->SetMarkerColor(kRed);
    ch2->SetMarkerStyle(20);
    ch2->SetLineWidth(3.);

    ch1->SetLineColor(kBlack);
    ch1->SetLineWidth(3.);
    ch1->SetMarkerStyle(20);
  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*18",-5,20);
    fa->SetLineColor(kRed);

    TString cut, triangleCut;
    // gStyle->SetOptStat(0);
    Bool_t tetraN = 0;
    Bool_t thetaH3_lab = 0;
    Bool_t mm = 0; 
    Bool_t reactionAngle = 0;
    Bool_t tritonCorr = 0;
    Bool_t tritonAngleCM = 0;
    Bool_t he3_corr = 0;
    Bool_t target = 0;
    Bool_t setupReco = 0;
    Bool_t fourMM = 0;
    Bool_t fourTriangles = 0;

    TString cutTriangle("(eh3_CM*1000<(1000*(mh7-4*0.939565-2.808920)*4./7.))");

    if (thetaH3_lab) {

        TCanvas *c1 = new TCanvas("c1","",1800,1000); 

        c1->Divide(2,2);

        c1->cd(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1_cut",cut.Data(),"same");
        c1->Update();

        c1->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_2",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_2_cut",cut.Data(),"same");
        c1->Update();

        // fa->Draw("same");

        c1->cd(3);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_3",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_3_cut",cut.Data(),"same");
        c1->Update();

        // fa->Draw("same");

        c1->cd(4);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_4",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_4_cut",cut.Data(),"same");
        c1->Update();
        // fa->Draw("same");



        return;



        // TCanvas *c1 = new TCanvas("c1","",1800,1000); 

        c1->Divide(2,2);

        c1->cd(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_1_cut",cut.Data(),"same");
        c1->Update();

        fa->Draw("same");

        c1->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_2",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_2_cut",cut.Data(),"same");
        c1->Update();

        fa->Draw("same");

        c1->cd(3);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_3",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_3_cut",cut.Data(),"same");
        c1->Update();

        fa->Draw("same");

        c1->cd(4);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_4",cut.Data());
        c1->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h3h7_lab_4_cut",cut.Data(),"same");
        c1->Update();
        fa->Draw("same");

return;
        c1->Print("/home/ivan/Desktop/tmp/png/4angle_h3_h7_lab_corr.png");


        TCanvas *cTheta = new TCanvas("cTheta","",1800,1000); 

        cTheta->Divide(2,2);

        cTheta->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        ch1->Draw("angle_h3_h7 >> h3h7_lab_1_1d",cut.Data());
        cTheta->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7 >> h3h7_lab_1_cut_1d",cut.Data(),"same");
        cTheta->Update();

        cTheta->cd(2);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        ch1->Draw("angle_h3_h7 >> h3h7_lab_2_1d",cut.Data());
        cTheta->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7 >> h3h7_lab_2_cut_1d",cut.Data(),"same");
        cTheta->Update();

        cTheta->cd(3);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        ch1->Draw("angle_h3_h7 >> h3h7_lab_3_1d",cut.Data());
        cTheta->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7 >> h3h7_lab_3_cut_1d",cut.Data(),"same");
        cTheta->Update();

        cTheta->cd(4);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        ch1->Draw("angle_h3_h7 >> h3h7_lab_4_1d",cut.Data());
        cTheta->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        ch1->Draw("angle_h3_h7 >> h3h7_lab_4_cut_1d",cut.Data(),"same");
        cTheta->Update();

        cTheta->Print("/home/ivan/Desktop/tmp/png/4angle_h3_h7_lab.png");


        TCanvas *hMM_3h = new TCanvas("hMM_3h","title",1800,1000);
        hMM_3h->Divide(2,2);

        hMM_3h->cd(1);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        hMM_3h->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hMM_3h->Update();


        hMM_3h->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        hMM_3h->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hMM_3h->Update();

        hMM_3h->cd(3);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        hMM_3h->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hMM_3h->Update();

        hMM_3h->cd(4);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        hMM_3h->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("cos(thetah3CM*TMath::DegToRad()):1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hMM_3h->Update();

        hMM_3h  ->Print("/home/ivan/Desktop/tmp/png/4angle_h3_h7_CM.png");

        return;        
    }

    if (mm) {

        TCanvas *c2 = new TCanvas("c2","",1800,1000); 
        c2->Divide(2,1);

        c2->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1(40,-4,21)",cut.Data(),"") << endl;

        c2->Update();

        ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_1_cut(40,4,21)",cut.Data(),"same") << endl;

        c2->Update();

        ch2->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_1_cut_eTarget(40,-4,21)",cut.Data(),"same") << endl;

        c2->Update();

        c2->cd(2);

        ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_1",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_1_cut",cut.Data(),"same") << endl;
        c2->Update();

        ch2->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_1_cut_eTarget",cut.Data(),"same") << endl;
        c2->Update();

        fa->Draw("same");
        c2->Update();


return;
        c2->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(20,-4.02,20.98)",cut.Data(),"") << endl;

        c2->Update();

        ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_2_cut(20,-4.02,20.98)",cut.Data(),"same") << endl;

        c2->Update();

        ch2->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_2_cut_eTarget(20,-4.02,20.98)",cut.Data(),"same") << endl;

        c2->Update();

        c2->cd(4);

        ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_2(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_2_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        ch2->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_2_cut_eTarget(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();


        c2->cd(5);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_4 && flag4) )");
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(20,-4.02,20.98)",cut.Data(),"") << endl;

        c2->Update();

        ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_3_cut(20,-4.02,20.98)",cut.Data(),"same") << endl;

        c2->Update();

        ch2->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_4 && flag4) )");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_3_cut_eTarget(20,-4.02,20.98)",cut.Data(),"same") << endl;

        c2->Update();

        c2->cd(6);

        ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_4 && flag4) )");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_3(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_3_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        ch2->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_4 && flag4) )");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_3_cut_eTarget(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();


        c2->cd(7);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) )");
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(20,-4.02,20.98)",cut.Data(),"") << endl;

        c2->Update();

        ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_4_cut(20,-4.02,20.98)",cut.Data(),"same") << endl;

        c2->Update();

        ch2->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) )");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_4_cut_eTarget(20,-4.02,20.98)",cut.Data(),"same") << endl;

        c2->Update();

        c2->cd(8);

        ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) )");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_4(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_4_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        ch2->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) )");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_4_cut_eTarget(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();


        fa->Draw("same");
        c2->Update();
return;
//
        c2->cd(3);

        ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2(20,-4.02,20.98)",cut.Data(),"") << endl;

        c2->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_2_cut",cut.Data(),"same") << endl;
        c2->Update();

        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_2_cut_eTarget",cut.Data(),"same") << endl;
        c2->Update();

        c2->cd(4);

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_2(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_2_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_2_cut_eTarget(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();


        fa->Draw("same");
        c2->Update();
//

        c2->cd(5);

        ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3(20,-4.02,20.98)",cut.Data(),"") << endl;
        c2->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_3_cut",cut.Data(),"same") << endl;
        c2->Update();

        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_3_cut_eTarget",cut.Data(),"same") << endl;
        c2->Update();

        c2->cd(6);

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_3(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_3_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_3_cut_eTarget(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        fa->Draw("same");
        c2->Update();
//
        c2->cd(7);

        ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4(20,-4.02,20.98)",cut.Data(),"") << endl;

        c2->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_4_cut",cut.Data(),"same") << endl;
        c2->Update();

        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cout << ch2->Draw("1000*(mh7-4*0.939565-2.808920)>> mm_4_cut_eTarget",cut.Data(),"same") << endl;
        c2->Update();

        c2->cd(8);

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_4(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_4_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();

        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_4_cut_eTarget(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        c2->Update();


        fa->Draw("same");
        c2->Update();
//        


        c2->Print("/home/ivan/Desktop/tmp/png/mmAll_4.png");

return;

        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // ch1->SetLineColor(kRed);
        // cut += " && " + cutTriangle;
        // // cout << ch1->Draw("trigger",cut.Data(),"") << endl;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut",cut.Data(),"same") << endl;
        // // TH1F *hMM_tel1 = (TH1F*)gPad->GetPrimitive("h5_coin");
        // // hMM_tel1->GetXaxis()->SetRangeUser(-5,20);
        // // hMM->SetBinOffset(0.25); 
        // c2->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut",cut.Data(),"same") << endl;
        // c2->Update();


        // ch1->SetLineColor(kBlue);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // // cut += " && " + cutTriangle;

        // cut += " && frame1X<12.5 && frame1X>-12.5";
        // cut += " && frame1Y<12.5 && frame1Y>-12.5";
        // cut += " && frame2X<12.5 && frame2X>-12.5";
        // cut += " && frame2Y<12.5 && frame2Y>-12.5";
        // cut += " && frame3X<12.5 && frame3X>-12.5";
        // cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        // cut += " && " + cutTriangle;
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut_sq(25,-5,20)",cut.Data(),"same",nEvents,0);
        // c2->Update();


        // ch2->SetLineColor(kGreen);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // // cut += " && " + cutTriangle;

        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_back(25,-5,20)",cut.Data(),"same");
        // c2->Update();


        // cut.Form("(nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) && nh3 && (e_1<20 && e_2<20 && e_3<20 && e_4<20)");
        // ch1->SetLineColor(kRed);
        // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut(25,-5,20)",cut.Data(),"same");

        // c2->cd(2);

        // // cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> triangle",cut.Data(),"");
        // c2->Update();

        // c2->cd(2);
        // ch1->SetMarkerColor(kBlack);
        // // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle(10000,-5,20,10000,0,12)",cut.Data(),"",nEvents,0) << endl;
        // c2->Update();


        
        // ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && " + cutTriangle;
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_cut(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        // c2->Update();

        // fa->Draw("same");
        // c2->Update();

        c2->Print("/home/ivan/Desktop/tmp/png/mm_noCoin.png");


        c2->cd(3);

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;


        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_triangle",cut.Data(),"") << endl;
        c2->Update();



return;

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " && " + cutTriangle;

        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17"; 

        // cut += " && " + cutTriangle;

        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_cut_sq(10000,-5,20,10000,0,12)",cut.Data(),"same",nEvents,0) << endl;
        // c2->Update();

        // ch2->SetMarkerColor(kGreen);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // cout << ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_back(10000,-5,20,10000,0,12)",cut.Data(),"same") << endl;
        // c2->Update();

        // fa->Draw("same");
        // c2->Update();


        c2->cd(3);
        ch1->SetMarkerColor(kBlack);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && flagCent");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngle",cut.Data(),"",nEvents,0);
        c2->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && " + cutTriangle;
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngleCut",cut.Data(),"same",nEvents,0);
        // c2->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && " + cutTriangle;

        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17";                

        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngleCut_sq",cut.Data(),"same",nEvents,0);
        // c2->Update();

        // ch2->SetMarkerColor(kGreen);
        // cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngle_back",cut.Data(),"same");
        // c2->Update();


        c2->Print("/home/ivan/Desktop/tmp/png/mmAll_noCoin.png");

    }
    
    if (tetraN) {

        ch4->SetMarkerStyle(7);

        TCanvas *kinN4 = new TCanvas("kinN4","title",1800,1000);
        kinN4->Divide(2,2);

        kinN4->cd(1);
        cut.Form("nhe3_1 && flag1");
        cout << ch4->Draw("1000*eh7:angle_h7_he8",cut.Data(),"") << endl;
        kinN4->Update();        

        kinN4->cd(2);
        cut.Form("nhe3_1 && flag1");
        cout << ch4->Draw("1000*ehe3:angle_he3_he8 >> (60,0,30,40,0,80)",cut.Data(),"col") << endl;
        kinN4->Update();  

        kinN4->cd(3);
        cut.Form("nhe3_1 && flag1");
        cout << ch4->Draw("1000*ehe3:1000*(mh7-4*0.939565)",cut.Data(),"") << endl;
        kinN4->Update();  

        kinN4->cd(4);
        ch4->SetLineColor(kBlack);
        cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch4->Draw("1000*(5.601518524+mh7-7.482538-1.875612)",cut.Data(),"") << endl;

        ch4->SetLineColor(kRed);
        cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("1000*(5.601518524+mh7-7.482538-1.875612)",cut.Data(),"same") << endl;
        kinN4->Update();  

        TCanvas *n4_tria = new TCanvas("n4_tria","title",1800,1000);
        n4_tria->Divide(2,1);

        n4_tria->cd(1);
        ch4->SetLineColor(kBlack);
        cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch4->Draw("1000*(mh7-4*0.939565) >> mm_n4_total",cut.Data(),"") << endl;
        n4_tria->Update();

        ch4->SetLineColor(kRed);
        cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"same") << endl;
        n4_tria->Update();

        n4_tria->cd(2);
        ch4->SetMarkerColor(kBlack);
        cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch4->Draw("thetah7CM:1000*(mh7-4*0.939565)",cut.Data(),"") << endl;
        n4_tria->Update();

        ch4->SetMarkerColor(kRed);
        cut.Form("( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("thetah7CM:1000*(mh7-4*0.939565)",cut.Data(),"same") << endl;
        n4_tria->Update();


        TCanvas *cTetra = new TCanvas("cTetra","",1000,1000); 
        cTetra->Divide(2,2);

        cTetra->cd(1);
        ch4->SetLineColor(kBlack);
        cut.Form("nhe3_1 && flag1");
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"") << endl;
        cTetra->Update();

        ch4->SetLineColor(kRed);
        cut.Form("nhe3_1 && flag1");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"same") << endl;
        cTetra->Update();


        cTetra->cd(2);
        ch4->SetLineColor(kBlack);
        cut.Form("nhe3_2 && flag2");
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"") << endl;
        cTetra->Update();

        ch4->SetLineColor(kRed);
        cut.Form("nhe3_2 && flag2");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"same") << endl;
        cTetra->Update();


        cTetra->cd(3);
        ch4->SetLineColor(kBlack);
        cut.Form("nhe3_3 && flag3");
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"") << endl;
        cTetra->Update();

        ch4->SetLineColor(kRed);
        cut.Form("nhe3_3 && flag3");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"same") << endl;
        cTetra->Update();        

        cTetra->cd(4);
        ch4->SetLineColor(kBlack);
        cut.Form("nhe3_4 && flag4");
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"") << endl;
        cTetra->Update();

        ch4->SetLineColor(kRed);
        cut.Form("nhe3_4 && flag4");
        cut += " && 1000*ehe3>30 && 1000*ehe3<60";
        cout << ch4->Draw("1000*(mh7-4*0.939565)",cut.Data(),"same") << endl;
        cTetra->Update();

    }

    if(setupReco) {

        TCanvas *setupCan = new TCanvas("setupCan","reconstruction scheme",1000,1000);
        setupCan->cd();
        ch1->SetMarkerStyle(20);

        ch1->Draw("sideY:-sideX >> (96,-150,150,96,-150,150)","(flag1 || flag2 || flag3 || flag4) && sideY!=0 && sideX!=0","col");
        setupCan->Update();



        TLine *l1 = new TLine(21.3,-4.2,71.3,-4.2);
        TLine *l2 = new TLine(71.3,-4.2,71.3,45.8);
        TLine *l3 = new TLine(71.3,45.8,21.3,45.8);
        TLine *l4 = new TLine(21.3,45.8,21.3,-4.2);
        l1->SetLineColor(kRed);
        l2->SetLineColor(kRed);
        l3->SetLineColor(kRed);
        l4->SetLineColor(kRed);

        l1->Draw("same");
        l2->Draw("same");
        l3->Draw("same");
        l4->Draw("same");



    }

    // ch1->Draw("thetahe8.",cut.Data(),"");


    if (reactionAngle) {

        TCanvas *rAngle = new TCanvas("rAngle","",1800,1000); 

        rAngle->Divide(4,2);

        rAngle->cd(1);

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM<14";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_low_1(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        // rAngle->cd(2);

        // ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // ch1->Draw("thetah7CM",cut.Data(),"");
        // rAngle->Update();

        // ch1->SetLineColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah7CM<14";
        // ch1->Draw("thetah7CM",cut.Data(),"same");
        // rAngle->Update();

        // ch1->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah7CM>14";
        // ch1->Draw("thetah7CM",cut.Data(),"same");
        // rAngle->Update();

        rAngle->cd(5);

        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM>14";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_high_1(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();


        rAngle->cd(2);

        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM<15";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_low_2(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        rAngle->cd(6);

        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM>15";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_high_2(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        rAngle->cd(3);
        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM<16";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_low_3(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        rAngle->cd(7);
        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM>16";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_high_3(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        rAngle->cd(4);
        ch1->SetLineColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM<17";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_low_4(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        rAngle->cd(8);
        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && thetah7CM>17";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_high_4(20,-4.02,20.98)",cut.Data(),"") << endl;
        rAngle->Update();

        return;        
    }

    if (tritonCorr) {

        TCanvas *tAngle = new TCanvas("tAngle","",1800,1000); 

        // tAngle->Divide(4,2);
        tAngle->cd();

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM:eh3",cut.Data(),"") << endl;
        tAngle->Update();

        ch1->SetMarkerColor(kBlue);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && frame1X<13.05 && frame1X>-11.95";
        cut += " && frame1Y<13.83 && frame1Y>-11.17";
        cut += " && frame2X<13.05 && frame2X>-11.95";
        cut += " && frame2Y<13.83 && frame2Y>-11.17";
        cut += " && frame3X<13.05 && frame3X>-11.95";
        cut += " && frame3Y<13.83 && frame3Y>-11.17"; 
        cout << ch1->Draw("eh3_CM:eh3",cut.Data(),"same") << endl;
        tAngle->Update();

    }

    if (he3_corr) {

        TCanvas *he3_mm = new TCanvas("he3_mm","",1800,1000); 

        // tAngle->Divide(4,2);
        he3_mm->cd();

        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        he3_mm->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        he3_mm->Update();
    }

    if (tritonAngleCM) {

        // TCanvas *hMM_3h = new TCanvas("hMM_3h","",1800,1000); 

        // hMM_3h->Divide(3,1);

        // hMM_3h->cd(1);
        // ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>mm(20,-4,21)",cut.Data(),"") << endl;
        // hMM_3h->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>mm_cut(20,-4,21)",cut.Data(),"same") << endl;
        // hMM_3h->Update();

        // ch1->SetLineColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>nn_cut_angle(20,-4,21)",cut.Data(),"same") << endl;
        // hMM_3h->Update();

        // ch1->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cut += " && thetah7CM>17";        
        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>nn_cut_angle_r(20,-4,21)",cut.Data(),"same") << endl;
        // hMM_3h->Update();
                
        // ch1->SetLineColor(kMagenta);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cut += " && thetah7CM>17";

        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17"; 

        // cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>nn_cut_angle_r_fr(20,-4,21)",cut.Data(),"same") << endl;
        // hMM_3h->Update();                



        // hMM_3h->cd(2);
        // ch1->SetMarkerColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // // cut += " && " + cutTriangle;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        // hMM_3h->Update();

        // ch1->SetMarkerColor(kRed);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // hMM_3h->Update();

        // ch1->SetMarkerColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";        
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // hMM_3h->Update();

        // ch1->SetMarkerColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cut += " && thetah7CM>17"; 
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // hMM_3h->Update();


        // ch1->SetMarkerColor(kMagenta);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cut += " && thetah7CM>17"; 
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17";         
        // cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        // hMM_3h->Update();


        // fa->Draw("same");


        // hMM_3h->cd(3);
        // ch1->SetLineColor(kBlack);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // // cut += " && thetah3CM<100";
        // cout << ch1->Draw("thetah3CM >> angle",cut.Data(),"") << endl;
        // hMM_3h->Update();        

        // ch1->SetLineColor(kBlue);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cout << ch1->Draw("thetah3CM >> angle_cut",cut.Data(),"same") << endl;
        // hMM_3h->Update();  

        // ch1->SetLineColor(kGreen);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cut += " && thetah7CM>17";         
        // cout << ch1->Draw("thetah3CM >> angle_cut_r",cut.Data(),"same") << endl;
        // hMM_3h->Update();  

        // ch1->SetLineColor(kMagenta);
        // cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<60";
        // cut += " && thetah7CM>17";  
        // cut += " && frame1X<13.05 && frame1X>-11.95";
        // cut += " && frame1Y<13.83 && frame1Y>-11.17";
        // cut += " && frame2X<13.05 && frame2X>-11.95";
        // cut += " && frame2Y<13.83 && frame2Y>-11.17";
        // cut += " && frame3X<13.05 && frame3X>-11.95";
        // cut += " && frame3Y<13.83 && frame3Y>-11.17";                 
        // cout << ch1->Draw("thetah3CM >> angle_cut_r_fr",cut.Data(),"same") << endl;
        // hMM_3h->Update(); 

        TCanvas *hMM_3h = new TCanvas("hMM_3h","",1800,1000); 

        hMM_3h->Divide(3,1);

        hMM_3h->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>mm(20,-4,21)",cut.Data(),"") << endl;
        hMM_3h->Update();

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>mm_cut(20,-4,21)",cut.Data(),"same") << endl;
        hMM_3h->Update();

        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)<5";
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920)>>nn_cut_angle_r(20,-4,21)",cut.Data(),"same") << endl;
        hMM_3h->Update();
                

        hMM_3h->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"") << endl;
        hMM_3h->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hMM_3h->Update();

        ch1->SetMarkerColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)<5";        
        cout << ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920)",cut.Data(),"same") << endl;
        hMM_3h->Update();

        fa->Draw("same");

        hMM_3h->cd(3);
        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        // cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM",cut.Data(),"") << endl;
        hMM_3h->Update();        

        ch1->SetLineColor(kRed);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        // cut += " && thetah3CM<100";
        cout << ch1->Draw("thetah3CM >> angle",cut.Data(),"same") << endl;
        hMM_3h->Update();     

        ch1->SetLineColor(kGreen);
        cut.Form("nh3 && flagCent && nh3 && ( (nhe3_1 && flag1) || (nhe3_2 && flag2) || (nhe3_3 && flag3) || (nhe3_4 && flag4) )");
        cut += " && " + cutTriangle;
        cut += " && 1000*(mh7-4*0.939565-2.808920)<5";         
        cout << ch1->Draw("thetah3CM",cut.Data(),"same") << endl;
        hMM_3h->Update();  


    }



}