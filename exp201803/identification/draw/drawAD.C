{

	TFile *f = new TFile("ad.root","READ");
	TH1F h = *(TH1F*)f->Get("hCM");
	TH1F h1 = *(TH1F*)f->Get("hCM");

	// gStyle->SetOptStat(0);

	h.SetLineWidth(3);
	// h.Smooth();
	h.GetXaxis()->SetTitleSize(0.05);
	h.GetXaxis()->SetTitleOffset(0.7);
	h.GetXaxis()->SetRangeUser(0,80);
	h.GetXaxis()->SetTitle("\\Theta_{CM}, deg");
	h.SetTitle("^{3}He angle aistribution");
	// h.DrawNormalized();
	h1.GetXaxis()->SetRangeUser(4,20);
	h1.SetLineColor(2);
	h1.SetLineWidth(3);
	h1.Draw();

	//c1->Print("/media/user/Download/sharedfolder/poster/pics/Ad.png");

}