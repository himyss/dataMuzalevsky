void drawAngles(){
  gStyle->SetOptStat(0);

  TCutG *mmCut;
  TFile *f1;

  Bool_t MM,angles,nikolski,kin;
  MM = 0;
  angles = 0;
  nikolski = 0;
  kin = 0;


  TChain *ch2 = new TChain("tree"); //e4
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_1_mm.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_thinT_mm.root");
  // ch2->Add("/media/ivan/data/exp1906/be10/analysed/tmp/be10_2_mmminus1.root");
  
  cout << ch2->GetEntries() << endl;

  // ch2->AddFriend("treeNew","/media/ivan/data/exp1904/analysed/oldPars/mm_400_25_new.root");

  TChain *ch1 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
  // ch1->Add("/media/ivan/data/exp1906/be10/analysed/be10_etarget_mm.root");
  cout << ch1->GetEntries() << endl;

  TChain *ch3 = new TChain("tree"); //e4
  // ch1->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
  ch3->Add("/media/ivan/data/exp1906/be10/analysed/be10_etarget_mm.root");
  cout << ch3->GetEntries() << endl;

  ch2->SetLineWidth(3.);
  ch1->SetLineWidth(3.);
  ch3->SetLineWidth(3.);

  //--------------------------------------------------------------------------------

    TF1 *fa = new TF1("fa","x*4/7",-5,20);
    fa->SetLineColor(kRed);

    TString cut, triangleCut;

    Bool_t mm = 1; 
    Bool_t testPars = 0;

    if (testPars) {

        TCanvas *c1 = new TCanvas("c1","",1800,1000);
        c1->Divide(2,2);
        Float_t Emin = 0;

        // ch1->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> h1(70,-5,30)",cut.Data(),"");
        // c1->Update();



        // ch2->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> h2(70,-5,30)",cut.Data(),"same");
        // c1->Update();

        c1->cd(1);
        ch1->SetLineColor(kBlack);
        cut.Form("(nhe3_1 && e_1<25 && e_1>%f) && flagCent",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h1",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("(nhe3_1 && e_1<25 && e_1>%f) && flagCent && nh3",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h1_coin",cut.Data(),"same");
        c1->Update();


        c1->cd(2);
        ch1->SetLineColor(kBlack);
        cut.Form("(nhe3_2 && e_2<25 && e_2>%f) && flagCent",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h2",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("(nhe3_2 && e_2<25 && e_2>%f) && flagCent && nh3",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h2_coin",cut.Data(),"same");
        c1->Update();   

        c1->cd(3);
        ch1->SetLineColor(kBlack);
        cut.Form("(nhe3_3 && e_3<25 && e_3>%f) && flagCent",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h3",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("(nhe3_3 && e_3<25 && e_3>%f) && flagCent && nh3",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h3_coin",cut.Data(),"same");
        c1->Update();


        c1->cd(4);
        ch1->SetLineColor(kBlack);
        cut.Form("(nhe3_4 && e_4<25 && e_4>%f) && flagCent",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h4",cut.Data(),"");
        c1->Update();

        ch1->SetLineColor(kRed);
        cut.Form("(nhe3_4 && e_4<25 && e_4>%f) && flagCent && nh3",Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        cut += " && ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> h4_coin",cut.Data(),"same");
        c1->Update();



    }

    if (mm) {

        // TString cutTriangle("(eh3_CM*1000<(0.5 + 1000*(mh7-4*0.939565-2.808920)*4/7.))");

        TCanvas *c2 = new TCanvas("c2","",1800,1000); 
        // c2->Divide(2,1);


        // Float_t Emin = 10.;
        // c2->cd(3);
        // ch2->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> highV10(70,-5,30)",cut.Data(),"");
        // c2->Update();

        // ch2->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> highVcut10(70,-5,30)",cut.Data(),"same");

        // c2->Update();

        // c2->cd(4);
        // ch1->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> lowV10(70,-5,30)",cut.Data(),"");
        // c2->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> lowVcut10(70,-5,30)",cut.Data(),"same");

        // c2->Update();



        //  Emin = 10.5;
        // c2->cd(5);
        // ch2->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> highV105(70,-5,30)",cut.Data(),"");
        // c2->Update();

        // ch2->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> highVcut105(70,-5,30)",cut.Data(),"same");

        // c2->Update();

        // c2->cd(6);
        // ch1->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> lowV105(70,-5,30)",cut.Data(),"");
        // c2->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> lowVcut105(70,-5,30)",cut.Data(),"same");

        // c2->Update();



        //  Emin = 11;
        // c2->cd(7);
        // ch2->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> highV11(70,-5,30)",cut.Data(),"");
        // c2->Update();

        // ch2->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch2->Draw("1000*(mh7-8.406868788) >> highVcut11(70,-5,30)",cut.Data(),"same");

        // c2->Update();

        // c2->cd(8);
        // ch1->SetLineColor(kBlack);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> lowV11(70,-5,30)",cut.Data(),"");
        // c2->Update();

        // ch1->SetLineColor(kRed);
        // cut.Form("((nhe3_1 && e_1<20 && e_1>%f) || (nhe3_2 && e_2<20 && e_2>%f) || (nhe3_3 && e_3<20 && e_3>%f) || (nhe3_4 && e_4<20 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch1->Draw("1000*(mh7-8.406868788) >> lowVcut11(70,-5,30)",cut.Data(),"same");

        // c2->Update();

        Float_t Emin = 0;
        // c2->cd(1);
        ch2->SetLineColor(kBlack);
        cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch2->Draw("1000*(mh7-8.406868788) >> highV(70,-5,30)",cut.Data(),"");
        c2->Update();

        ch2->SetLineColor(kRed);
        cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch2->Draw("1000*(mh7-8.406868788) >> highVcoin(70,-5,30)",cut.Data(),"same");

        // ch3->SetLineColor(kGreen);
        // cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch3->Draw("1000*(mh7-8.406868788) >> highVempty(70,-5,30)",cut.Data(),"same");

        // ch3->SetLineColor(kBlue);
        // cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        // ch3->Draw("1000*(mh7-8.406868788) >> highVemptyCoin(70,-5,30)",cut.Data(),"same");


        c2->Update();
return;
        c2->cd(2);
        ch1->SetLineColor(kBlack);
        cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent",Emin,Emin,Emin,Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> lowV(70,-5,30)",cut.Data(),"");
        c2->Update();

        ch1->SetLineColor(kRed);
        cut.Form("((nhe3_1 && e_1<25 && e_1>%f) || (nhe3_2 && e_2<25 && e_2>%f) || (nhe3_3 && e_3<25 && e_3>%f) || (nhe3_4 && e_4<25 && e_4>%f)) && flagCent && nh3",Emin,Emin,Emin,Emin);
        // cut.Form("(nhe3_2 && e_2<25)  && nh3");
        // cut += " &&  ((fXt-0.5)*(fXt-0.5) + (fYt-1)*(fYt-1))<8*8";
        ch1->Draw("1000*(mh7-8.406868788) >> lowVcoin(70,-5,30)",cut.Data(),"same");


        c2->Update();




        c2->Print("/home/ivan/Desktop/tmp/MM_8Li.pdf");
return;

return;

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

    }
   

}