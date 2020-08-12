void draw(){


// 	TF1 *f = new TF1("f1","1/( sqrt(1-(1/x)*(1/x)) ) - 1",1,10000);
// 	// f->SetRange()
// 	f->Draw();
// return;

	TChain *chCal = new TChain("tree");
	chCal->Add("/mnt/data/exp2001/data/analysed/reco/crun09_0001.lmd.reco.root");

	TChain *ch = new TChain("tree");
	ch->Add("/mnt/data/exp2001/data/analysed/reco/run*.root");

	Bool_t ID = 0;
	Bool_t profile = 1;


	if (ID) {

		TCanvas *c1 = new TCanvas("c1","title",1800,1000);
		c1->Divide(2,3);

		c1->cd(1);
		chCal->Draw("F5+F3:tF5-tF3+68.475","","cont",24598,0);
		gPad->SetLogz(1);
		c1->Update();

		c1->cd(2);
		ch->Draw("F5+F3:tF5-tF3+68.475","","cont",24598,0);
		gPad->SetLogz(1);	
		c1->Update();

		c1->cd(3);
		chCal->Draw("tF5-tF3+68.475","","",24598,0);
		gPad->SetLogy(1);
		c1->Update();

		c1->cd(4);
		ch->Draw("tF5-tF3+68.475","","",24598,0);
		gPad->SetLogy(1);
		c1->Update();

		c1->cd(5);
		ch->SetLineColor(kBlue);
		chCal->Draw("1000*(he8.E()-he8.Mag())","","",24598,0);
		c1->Update();

		c1->cd(6);
		ch->Draw("1000*(he8.E()-he8.Mag())","","",24598,0);
		c1->Update();

	}

	if (profile) {

		TCanvas *c2 = new TCanvas("c2","title",1800,1000);
		c2->Divide(2,2);

		c2->cd(1);
		ch->Draw("y1c:x1c >> profile1(32,-20,20,32,-20,20)","trigger==1","col");
		c2->Update();

		c2->cd(2);
		ch->Draw("y2c:x2c >> profile2(32,-20,20,32,-20,20)","trigger==1","col");
		c2->Update();

		c2->cd(3);
		chCal->Draw("y1c:x1c >> profile3(32,-20,20,32,-20,20)","trigger==1","col");
		c2->Update();

		c2->cd(4);
		chCal->Draw("y2c:x2c >> profile4(32,-20,20,32,-20,20)","trigger==1","col");
		c2->Update();


	}


}