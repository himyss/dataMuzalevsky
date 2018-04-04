void mmSpectrum()
{


	TFile *fr = new TFile("sim_digi.root");
	TTree *tr = (TTree*)fr->Get("er");
	tr->AddFriend("er", "reco.root");

	TClonesArray *tracksT12 = new TClonesArray("ERQTelescopeTrack", 10);
	tr->SetBranchAddress("ERQTelescopeTrack_DoubleSi_SD2_XY_1", &tracksT12);

	TClonesArray *digiT11 = new TClonesArray("ERQTelescopeSiDigi", 10);
	tr->SetBranchAddress("ERQTelescopeSiDigi_DoubleSi_SD1_XY_0_X", &digiT11);

	TClonesArray *beamDet = new TClonesArray("ERBeamDetParticle", 10);
	tr->SetBranchAddress("BeamDetParticle.", &beamDet);

	TFile *fw = new TFile("output.root", "RECREATE");
	TTree *tw = new TTree("out","a simple Tree with simple variables");

	const Int_t noXstrips22 = 32;
	const Int_t noYstrips22 = 32;

	Float_t x, y, z;
	Float_t e3He;
	TLorentzVector *p3He = new TLorentzVector();
	TLorentzVector *p6He = new TLorentzVector();

//	tw->Branch("x",&x,"x/F");
//	tw->Branch("y",&y,"y/F");
//	tw->Branch("z",&z,"z/F");
	tw->Branch("e3He",&e3He,"energy/F");

	tw->Branch("particle3He.", "TLorentzVector", &p3He);
	tw->Branch("particle6He.", "TLorentzVector", &p6He);

//	Double_t dE, E;

	//read all entries and fill the histograms
	Long64_t nentries = tr->GetEntriesFast();
//	nentries = 1000;
	for (Long64_t i = 0; i < nentries; i++) {
		tr->GetEntry(i);

//		dE = 0;
		e3He = 0;
		x = 0; y = 0; z = 0;
		p3He->SetXYZT(0, 0, 0, 0);
		p6He->SetXYZT(0, 0, 0, 0);

		for (int iPoint = 0; iPoint < tracksT12->GetEntriesFast(); iPoint++) {
			ERQTelescopeTrack* t = (ERQTelescopeTrack*)tracksT12->At(iPoint);

//			if (tracksT12->GetEntriesFast() == 1) {
			if (tracksT12->GetEntriesFast() == 1 && digiT11->GetEntriesFast() == 1) {

				ERQTelescopeSiDigi* dig = (ERQTelescopeSiDigi*)digiT11->At(iPoint);

//				if()
				x = t->fTelescopeX-t->fTargetX;
				y = t->fTelescopeY-t->fTargetY;
				z = t->fTelescopeZ-t->fTargetZ;
//				e3He = t->fSumEdep;
				e3He = t->fSumEdep + dig->fEdep;

				TVector3 p;
				p.SetXYZ(x, y, z);
				p.SetMag( TMath::Sqrt( TMath::Power(e3He + 2.809,2) - TMath::Power(2.809, 2) ) );
				p3He->SetVect(p);
				p3He->SetE(e3He + 2.809);
			}

		}

		for (Int_t bdPoint = 0; bdPoint < beamDet->GetEntriesFast(); bdPoint++) {
			ERBeamDetParticle *beam = (ERBeamDetParticle*)beamDet->At(bdPoint);

			if (beamDet->GetEntriesFast() == 1) {
//				cout << beam->fTargetState.E() << endl;
				*p6He = beam->fTargetState;
//				cout << p6He->E() << endl;
			}
		}

		tw->Fill();

	}

	tw->Write();
	fw->Close();

//	if (gROOT->IsBatch())
//		return;

}

