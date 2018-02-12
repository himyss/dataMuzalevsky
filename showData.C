void showData(){

	TFile* f = new TFile("/home/muzalevsky/expertroot/macro/muzalevsky/full.root");
	TTree* t = (TTree*) f->Get("er");
	TClonesArray* tracks = new TClonesArray("ERMCTrack",13);
	t->SetBranchAddress("MCTrack", &tracks);

	TFile *f1 = new TFile("/home/muzalevsky/expertroot/macro/muzalevsky/kin.root","RECREATE");
	TTree *tree = new TTree("tree","kin");
	TLorentzVector *n1 = new TLorentzVector();
	TLorentzVector *n2 = new TLorentzVector();
	TLorentzVector *h5 = new TLorentzVector();

	tree->Branch("n1.", &n1); 
	tree->Branch("n2.", &n2); 
	tree->Branch("h5.", &h5); 

	Int_t pdg,mID,tID,h3ID;
	Int_t nN,flag,nh3;

	for(Int_t i=0; i<t->GetEntries();i++){
	// for(Int_t i=0; i<10;i++){
		// cout << " next event " << endl; 
		nN = 0; // number of neutrons
		nh3 = 0;
		flag = 0; // flag ( if 1 fill the tree, 0  - not)
		t->GetEntry(i);



		/*for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	cout << pdg << endl;
	    } */


		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	if( pdg == 1000010050 ) {
	    		flag = 1; // if there is an H5 in steck this event is interesting
	    		// cout << "found ";
	    	}	
	    	// if( pdg == 1000010030 ) {h3ID = mID; nh3++;} // if i want to choose the right neutrons i need to know their motherID
	    } 

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	if( (pdg == 1000010030) && (flag == 1) ) {h3ID = mID; nh3++;} // if i want to choose the right neutrons i need to know their motherID
	    } 


		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();

	    	if( (pdg == 2112) && (mID == h3ID) && (flag == 1) ) {
	    		// track->Get4Momentum(n1);
	    		nN++;
	    	} 
	    	// cout << track->GetPdgCode() << endl;
		}
		if((flag == 1) && (nN!=2)) {cout << nh3 << " wtf "<< i << endl;}
	}

	tree->Write();
	f1->Close();
	return;
}