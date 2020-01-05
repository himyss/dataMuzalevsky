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
// ch2->Add("/media/ivan/data/exp1904/analysed/MKpars/mm.root");
  cout << ch2->GetEntries() << endl;

  // ch2->AddFriend("treeNew","/media/ivan/data/exp1904/analysed/oldPars/mm_400_25_new.root");

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/h7_*");
  // ch1->Add("/media/ivan/data/exp1904/analysed/MKpars/mma_400.root");
  cout << ch1->GetEntries() << endl;
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

    ch1->SetLineColor(kBlack);
    ch1->SetLineWidth(3.);
    ch1->SetMarkerStyle(20);
  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*4/7",-5,20);
    fa->SetLineColor(kRed);

    TString cut, triangleCut;
    // gStyle->SetOptStat(0);
    Bool_t twoTriangles = 0;
    Bool_t mm = 1; 
    Bool_t reactionAngle = 0;
    Bool_t tritonCorr = 0;
    Bool_t heliumE = 0;
    Bool_t target = 0;
    Bool_t setupReco = 0;

    if (twoTriangles) {

        TCanvas *c1 = new TCanvas("c1","",1800,1000); 

        ch1->SetMarkerColor(kBlack);
        cut.Form("((nhe3_1 && e_1<20) || (nhe3_2 && e_2<20) || (nhe3_3 && e_3<20) || (nhe3_4 && e_4<20)) && nh3");
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle(10000,-5,20,10000,0,12)",cut.Data(),"");
        c1->Update();

        ch2->SetMarkerColor(kRed);
        cut.Form("((nhe3_1 && e_1<20) || (nhe3_2 && e_2<20) || (nhe3_3 && e_3<20) || (nhe3_4 && e_4<20)) && nh3");
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle(10000,-5,20,10000,0,12)",cut.Data(),"same");
        c1->Update();

        fa->Draw("same");
        c1->Update();

    }

    if (mm) {

        TString cutTriangle("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");

        TCanvas *c2 = new TCanvas("c2","",1800,1000); 
        c2->Divide(3,1);

        c2->cd(1);
        cut.Form("((flag1 && nhe3_1 && e_1<25) || (flag2 && nhe3_2 && e_2<25) || (flag3 && nhe3_3 && e_3<25) || (flag4 && nhe3_4 && e_4<25)) && nh3 && flagCent");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5(30,-5,25)",cut.Data(),"");
        TH1F *hMM = (TH1F*)gPad->GetPrimitive("h5");
        hMM->GetXaxis()->SetRangeUser(-5,20);
        // hMM->SetBinOffset(0.25); 
        c2->Update();

        ch1->SetLineColor(kRed);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        cut += " && " + cutTriangle;
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut(30,-5,25)",cut.Data(),"same");
        c2->Update();


        ch1->SetLineColor(kBlue);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut += " && " + cutTriangle;

        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut_sq(30,-5,25)",cut.Data(),"same");
        c2->Update();


        // // cut.Form("(nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) && nh3 && (e_1<20 && e_2<20 && e_3<20 && e_4<20)");
        // // ch1->SetLineColor(kRed);
        // // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h5_cut(25,-5,20)",cut.Data(),"same");

        c2->cd(2);

        // // cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> triangle",cut.Data(),"");
        // c2->Update();

       
        ch1->SetMarkerColor(kBlack);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle(10000,-5,20,10000,0,12)",cut.Data(),"");
        c2->Update();

        // 
        ch1->SetMarkerColor(kRed);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && " + cutTriangle;
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_cut(10000,-5,20,10000,0,12)",cut.Data(),"same");
        c2->Update();


        ch1->SetMarkerColor(kBlue);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && " + cutTriangle;

        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5"; 

        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_cut_sq(10000,-5,20,10000,0,12)",cut.Data(),"same");
        c2->Update();

        fa->Draw("same");
        c2->Update();


        c2->cd(3);
        ch1->SetMarkerColor(kBlack);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngle",cut.Data(),"");
        c2->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && " + cutTriangle;
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngleCut",cut.Data(),"same");
        c2->Update();

        ch1->SetMarkerColor(kBlue);
        cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && " + cutTriangle;

        cut += " && frame1X<12.5 && frame1X>-12.5";
        cut += " && frame1Y<12.5 && frame1Y>-12.5";
        cut += " && frame2X<12.5 && frame2X>-12.5";
        cut += " && frame2Y<12.5 && frame2Y>-12.5";
        cut += " && frame3X<12.5 && frame3X>-12.5";
        cut += " && frame3Y<12.5 && frame3Y>-12.5";                

        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngleCut_sq",cut.Data(),"same");
        c2->Update();


    }




}