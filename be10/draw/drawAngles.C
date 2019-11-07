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
  ch2->Add("/media/ivan/data/exp1906/be10/analysed/be10_2_mm.root");
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

    }
   

}