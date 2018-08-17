void deTOF(){

	TChain *ch = new TChain("AnalysisxTree");
	ch->Add("/media/user/work/data/exp1804/h5_14_0*.root");

	TChain *ch1 = new TChain("tree");
	// ch1->Add("/media/user/work/data/analysisexp1804/h5_14_tritium_bogumilMWPC.root");
	ch1->Add("/media/user/work/data/analysisexp1804/h5_14_id1_test.root");


	TCanvas *c1 = new TCanvas("c1","dE-ToF",1800,1000);
	// c1->Divide(2,1);
	// gStyle->SetOptStat(0);

	// c1->cd(1);

	// ch1->Draw("yt:xt-5>>hB(30,-25,25,30,-25,25)","trigger==1","cont");
	// TH2F *hB = (TH2F*)gPad->GetPrimitive("hB");

	// hB->GetXaxis()->SetTitle("x,mm");
	// hB->GetXaxis()->CenterTitle();
	// hB->GetXaxis()->SetTitleSize(0.05);
	// hB->GetXaxis()->SetTitleOffset(0.75);
	// // hB->GetXaxis()->SetTitleColor(2);	


	// hB->GetYaxis()->SetTitle("y,mm");
	// hB->GetYaxis()->CenterTitle();
	// hB->GetYaxis()->SetTitleSize(0.05);
	// hB->GetYaxis()->SetTitleOffset(0.75);
	// // hB->GetYaxis()->SetTitleColor(2);	

	// c1->cd(2);
	// ch->Draw("4.12*(NeEvent.F5[]+NeEvent.F3[])/1500.:(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165>>h1(200,110,190,1000,0.1,14.)","trigger==1","cont",1000000,0);
	cout << ch->Draw("4.12*(NeEvent.F5[]+NeEvent.F3[])/1500.:(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165>>h1(100,169,181,1000,2.5,6.5)","trigger==1","col") << endl;
	TH2F *h1_1 = (TH2F*)gPad->GetPrimitive("h1");

	h1_1->GetXaxis()->SetTitle("ToF, ns");
	h1_1->GetXaxis()->CenterTitle();
	h1_1->GetXaxis()->SetTitleSize(0.05);
	h1_1->GetXaxis()->SetTitleOffset(0.75);
	// h1_1->GetXaxis()->SetTitleColor(2);	

	h1_1->GetYaxis()->SetTitle("dE,MeV");
	h1_1->GetYaxis()->CenterTitle();
	// h1_1->GetYaxis()->SetTitleColor(2);			
	h1_1->GetYaxis()->SetTitleSize(0.05);
	h1_1->GetYaxis()->SetTitleOffset(0.75);

	// c1->SetLogz();

	c1->Update();

	// c1->Print("/media/user/Download/sharedfolder/poster/pics/de-ToF.png");
	return;
}
 