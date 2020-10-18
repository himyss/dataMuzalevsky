{
	TString cut, triangleCut, hdraw;
	TChain *ch1 = new TChain("tree"); //e4
	// ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/eTarget/h7_ect_*_mm_frame.root");
	ch1->Add("/mnt/data/exp1904/analysed/reco/siTriggers/h7_ct_*_mm_cut.root");
	// ch1->Add("/media/ivan/data/exp1904/analysed/novPars/reco/track0/h7_ct_*_mm_frame_newPars.root");
    cout << ch1->GetEntries() << endl;
 //    cInt->cd(3);

    TCanvas *c1 = new TCanvas("c1","title",1000,1000);
    c1->cd();

    ch1->SetMarkerStyle(1);
    cut.Form("flag4 && a1_4+a20_4_un<65 && a20_4<8");
    hdraw.Form("a20_4:a1_4+a20_4_un >> (1000,0,20,1000,0,1.5)");
    // ch1->Draw(hdraw.Data(),cut.Data(),"col",5000000,0);
    ch1->Draw(hdraw.Data(),cut.Data(),"col");


}
