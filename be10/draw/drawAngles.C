void drawAngles(){
  // gStyle->SetOptStat(0);

  TCutG *mmCut;
  TFile *f1;

  Bool_t MM,angles,nikolski,kin;
  MM = 0;
  angles = 0;
  nikolski = 0;
  kin = 0;


  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_mm.root");
  cout << ch2->GetEntries() << endl;

  // ch2->AddFriend("treeNew","/media/ivan/data/exp1904/analysed/oldPars/mm_400_25_new.root");

  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1904/analysed/oldPars/mm_400_25.root");

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

    Bool_t mm = 1; 
    Bool_t reactionAngle = 0;
    Bool_t tritonCorr = 0;
    Bool_t heliumE = 0;
    Bool_t target = 0;

    if (mm) {

        // TString cutTriangle("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");

        TCanvas *c2 = new TCanvas("c2","",1800,1000); 
        c2->Divide(2,1);

        c2->cd(1);
        ch2->SetLineColor(kBlack);
        cut.Form("((nhe3_1 && e_1<20) || (nhe3_2 && e_2<20) || (nhe3_3 && e_3<20) || (nhe3_4 && e_4<20)) && nh3");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch2->Draw("1000*(mh7-8.406868788) >> triangle(35,-5,30)",cut.Data(),"");
        c2->Update();

        c2->cd(2);

        ch2->SetMarkerColor(kBlack);
        ch2->SetMarkerStyle(20);
        // cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        // cut.Form("(nhe3_1 && e_1<20) && nh3 && flag1");
        cut.Form("(nhe3_1 && e_1<20) && nh3 && flag1");
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch2->Draw("e_1:1000*(mh7-8.406868788) >> h1(35,-5,30,25,5,25)",cut.Data(),"");
        c2->Update();    

        cut.Form("(nhe3_2 && e_2<20) && nh3 && flag2");
        ch2->Draw("e_2:1000*(mh7-8.406868788)>> h2(35,-5,30,25,5,25)",cut.Data(),"same");
        c2->Update(); 

        cut.Form("(nhe3_3 && e_3<20) && nh3 && flag3");
        ch2->Draw("e_3:1000*(mh7-8.406868788)>> h3(35,-5,30,25,5,25)",cut.Data(),"same");
        c2->Update(); 

        cut.Form("(nhe3_4 && e_4<20) && nh3 && flag4");
        ch2->Draw("e_4:1000*(mh7-8.406868788)>> h4(35,-5,30,25,5,25)",cut.Data(),"same");
        c2->Update();

        // c2->Print("/home/ivan/Desktop/tmp/missing_mass_7_only.pdf");
return;        
        ch2->SetMarkerColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch2->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle",cut.Data(),"");
        c2->Update();

        // 
        ch1->SetMarkerColor(kRed);
        // cut.Form("((nhe3_1 && e_1<25) || (nhe3_2 && e_2<25) || (nhe3_3 && e_3<25) || (nhe3_4 && e_4<25)) && nh3");
        cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " && " + cutTriangle;
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("eh3_CM*1000:1000*(mh7-4*0.939565-2.808920) >> triangle_cut",cut.Data(),"same");
        c2->Update();

        fa->Draw("same");
        c2->Update();
    }

    if (heliumE) {

        TString cutTriangle("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");

        TCanvas *canHe = new TCanvas("canHe","",1800,1000); 
        canHe->Divide(2,2);

        canHe->cd(1);
        cut.Form("nhe3_1  && nh3 && 1000*(mh7-4*0.939565-2.808920)<10");
        cut += " && " + cutTriangle;
        ch1->Draw("e_1",cut.Data(),"");
        canHe->Update();

        canHe->cd(2);
        cut.Form("nhe3_2  && nh3 && 1000*(mh7-4*0.939565-2.808920)<10");
        cut += " && " + cutTriangle;
        ch1->Draw("e_2",cut.Data(),"");
        canHe->Update();

        canHe->cd(3);
        cut.Form("nhe3_3  && nh3 && 1000*(mh7-4*0.939565-2.808920)<10");
        cut += " && " + cutTriangle;
        ch1->Draw("e_3",cut.Data(),"");
        canHe->Update();

        canHe->cd(4);
        cut.Form("nhe3_4  && nh3 && 1000*(mh7-4*0.939565-2.808920)<10");
        cut += " && " + cutTriangle;
        ch1->Draw("e_4",cut.Data(),"");
        canHe->Update();        
    }

    if (reactionAngle){
        TCanvas *can = new TCanvas("can","",1800,1000);
        can->Divide(2,1);

        // can->cd(1);
        // cut.Form("(nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) && nh3");
        // ch1->Draw("thetah7CM",cut.Data(),"");   
        // can->Update();

        can->cd(2);
        ch1->SetMarkerColor(kBlack);
        cut.Form("(nhe3_1 || nhe3_3 || nhe3_4) && nh3");
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngle",cut.Data(),"");
        can->Update();

        ch1->SetMarkerColor(kRed);
        cut.Form("(nhe3_1 || nhe3_3 || nhe3_4) && nh3 && (eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("thetah7CM:1000*(mh7-4*0.939565-2.808920) >> rAngleCut",cut.Data(),"same");
        can->Update();

    }

    if (tritonCorr){ 
        TCanvas *h3Corr = new TCanvas("h3Corr","",1800,1000);
        h3Corr->Divide(2,1);

        h3Corr->cd(1);
        ch1->Draw("1000*eh3_CM.","(nhe3_1 || nhe3_3 || nhe3_4) && nh3 && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8","");
        h3Corr->Update();

        h3Corr->cd(2);
        ch1->SetMarkerColor(kBlack);
        ch1->Draw("thetah3.:1000*(mh7-4*0.939565-2.808920)","(nhe3_1 || nhe3_3 || nhe3_4) && nh3 && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8","");
        h3Corr->Update();

        ch1->SetMarkerColor(kRed);
        ch1->Draw("thetah3.:1000*(mh7-4*0.939565-2.808920)","(nhe3_1 || nhe3_3 || nhe3_4) && nh3 && (eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.)) && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8","same");
        h3Corr->Update();
    }

    if (target) {
        TCanvas *c4 = new TCanvas("c4","target cut",1000,1000);  
        c4->Divide(2,1);

        c4->cd(1);
        ch1->Draw("fYt:fXt>>h_target(100,-30,30,100,-30,30)","","col",100000,0);

        TString cutTriangle("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");
        cut.Form("(nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) && nh3"); 

        cut += " && " + cutTriangle;
        cout << cut.Data() << endl;

        ch1->SetMarkerColor(kRed);
        ch1->SetMarkerStyle(20);
        ch1->Draw("fYt:fXt>>h_targetCut(100,-30,30,100,-30,30)",cut.Data(),"same");

        c4->cd(2);
        ch1->Draw("fYt:fXt>>h_targetCutLego(100,-30,30,100,-30,30)",cut.Data(),"LEGO");

    }

}