void check3He()
{


	TFile *fr = new TFile("sim_digi.root");
	TTree *tr = (TTree*)fr->Get("er");
	TClonesArray *tracks = new TClonesArray("ERQTelescopeTrack", 10);
	tr->SetBranchAddress("ERQTelescopeTrack_DoubleSi_SD2_XY_1", &tracks);

	TFile *fw = new TFile("output.root", "RECREATE");
	TTree *tw = new TTree("out","a simple Tree with simple variables");

	Float_t x, y, z, energy;
	TLorentzVector *particle = new TLorentzVector();

//	tw->Branch("x",&x,"x/F");
//	tw->Branch("y",&y,"y/F");
//	tw->Branch("z",&z,"z/F");
	tw->Branch("energy",&energy,"energy/F");

	tw->Branch("particle.", "TLorentzVector", &particle);

	Double_t dE, E;

	//read all entries and fill the histograms
	Long64_t nentries = tr->GetEntriesFast();
//	nentries = 1000;
	for (Long64_t i = 0; i < nentries; i++) {
		tr->GetEntry(i);

		dE = 0;
		E = 0;
		x = 0; y = 0; z = 0;
		particle->SetXYZT(0, 0, 0, 0);

		for (int iPoint = 0; iPoint < tracks->GetEntriesFast(); iPoint++) {
			ERQTelescopeTrack* t = (ERQTelescopeTrack*)tracks->At(iPoint);

			if (tracks->GetEntriesFast() == 1) {

				x = t->fTelescopeX-t->fTargetX;
				y = t->fTelescopeY-t->fTargetY;
				z = t->fTelescopeZ-t->fTargetZ;
				energy = t->fSumEdep;

				TVector3 p;
				p.SetXYZ(x, y, z);
				p.SetMag( TMath::Sqrt( TMath::Power(energy + 2.809,2) - TMath::Power(2.809, 2) ) );
				particle->SetVect(p);
				particle->SetE(energy + 2.809);
			}

		}

		tw->Fill();

	}

	tw->Write();
	fw->Close();

//	if (gROOT->IsBatch())
//		return;

}

