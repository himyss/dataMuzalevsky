void showData(){

	TFile* f = new TFile("/home/muzalevsky/expertroot/macro/muzalevsky/full.root");
	TTree* t = (TTree*) f->Get("er");
	TClonesArray* tracks = new TClonesArray("ERMCTrack",13);
	t->SetBranchAddress("MCTrack", &tracks);

	TFile *f1 = new TFile("/home/muzalevsky/expertroot/macro/muzalevsky/kin.root","RECREATE");
	TTree *tree = new TTree("tree","kin");
	TLorentzVector n1; //= new TLorentzVector();
	TLorentzVector n2; //= new TLorentzVector();
	TLorentzVector h5; //= new TLorentzVector();
	TLorentzVector h3; //= new TLorentzVector();

	tree->Branch("n1.", &n1); 
	tree->Branch("n2.", &n2); 
	tree->Branch("h5.", &h5); 
	tree->Branch("h3.", &h3);

	Int_t pdg,mID,tID,h3ID;
	Int_t nN,flag,nh3,nEvents;
	nEvents = 0;
	for(Int_t i=0; i<t->GetEntries();i++){
	// for(Int_t i=0; i<10;i++){
		// cout << " next event " << endl; 
		nN = 0; // number of neutrons
		nh3 = 0;
		flag = 0; // flag ( if 1 fill the tree, 0  - not)
		t->GetEntry(i);

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	if(pdg == 1000010050) {
	    		flag = 1; // if there is an H5 in steck this event is interesting
	    		nEvents ++ ;
	    		track->Get4Momentum(h5);
	    		// cout << "found ";
	    	}	
	    	// if( pdg == 1000010030 ) {h3ID = mID; nh3++;} // if i want to choose the right neutrons i need to know their motherID
	    } 
	    if(flag!=1) continue;

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	if(pdg == 1000010030) { // if i want to choose the right neutrons i need to know their motherID
	    		h3ID = mID; 
	    		nh3++;
	    		track->Get4Momentum(h3);
	    	} 
	    } 
	    if(nh3!=1) continue;  // i want to read events with 1 h3 only

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();

	    	if( (pdg == 2112) && (mID == h3ID) ) {
	    		nN++;
	    		if(nN == 1) track->Get4Momentum(n1);
	    		if(nN == 2) track->Get4Momentum(n2);
	    	}

	    	// cout << track->GetPdgCode() << endl;
		}
		if(nN!=2) {cout << nN << " wtf "<< i << endl;}
		tree->Fill();
	} // t->GetEntries()

	cout << nEvents;
	tree->Write();
	f1->Close();
	return;
}


	/*	t->GetEntry(1619);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;
		t->GetEntry(2519);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
	    cout << endl << "next event " << endl;
		t->GetEntry(3950);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;
		t->GetEntry(5847);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;
		t->GetEntry(6900);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;*/