void draw() {

        TString cut;

        TChain *ch1 = new TChain("tree");
        ch1->Add("/media/ivan/data/exp1904/analysed/novPars/selected/newCal/tmp/h7_ct_*_mm_newPars.root");

        TCanvas *c_mm_diff = new TCanvas("c_mm_diff","",1000,1000);
        c_mm_diff->Divide(2,2);

        c_mm_diff->cd(2);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_1 && flag1");
        
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_1",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        c_mm_diff->cd(4);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_2 && flag2");
        // 
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_2",cut.Data(),"") << endl;
        c_mm_diff->Update();    


        c_mm_diff->cd(3);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_3 && flag3");
        
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_3",cut.Data(),"") << endl;
        c_mm_diff->Update();    

        c_mm_diff->cd(1);

        ch1->SetLineColor(kBlack);
        cut.Form("nh3 && flagCent && nh3 && nhe3_4 && flag4");
        
        cout << ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> mm_4",cut.Data(),"") << endl;
        c_mm_diff->Update();    



        // c_mm_diff->Print("pdf/mm_diff.pdf");
}