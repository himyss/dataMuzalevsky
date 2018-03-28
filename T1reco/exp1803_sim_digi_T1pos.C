void exp1803_sim_digi_T1pos(Int_t nEvents = 100) {
	// --------------- Telescope T1 -------------------------------------------
	Double_t T1Dl = 0.5;         // [cm]
	Double_t T1PosZ = 10.;       // [cm]
	Double_t T1D1Thick = 0.002;  // [cm]
	Double_t T1D2Thick = 0.1;    // [cm]
	Double_t T1Side = 6.2;       // [cm]  this parameter should coincide with SD1 side length from /db/QTelescope/QTelescopeParts.xml
	Double_t T1Aperture = 3.1;   // [cm]
	// --------------- Telescope D1 -------------------------------------------
	Double_t D1PosZ = 20.;       // [cm]
	Double_t D1Thick = 0.03;     // [cm]
	// --------------- BeamDet ------------------------------------------------
	Double_t BeamDetLToF = 1500.;     // [cm]
	Double_t BeamDetPosZToF = -50;  // [cm]
	Double_t BeamDetLMWPC = 32.;     // [cm]
	Double_t BeamDetPosZMWPC = -8;  // [cm]
	// --------------- Beam start position ------------------------------------
	Double_t beamStartPosition = -1600;  // [cm]
//	Double_t beamStartPosition = -150;
	// --------------- Target -------------------------------------------------
	Double_t targetH2Thickness = 0.4;  // [cm] this parameter should coincide with target H2 thickness in /macro/geo/create_target_h2_geo.C
	//---------------------Files-----------------------------------------------
	TString outFile= "sim_digi.root";
	TString parFile= "par.root";
	TString workDirPath = gSystem->Getenv("VMCWORKDIR");
	TString paramFileQTelescope = workDirPath
			+ "/db/QTelescope/QTelescopeParts.xml";
	TString paramFileBeamDet = workDirPath
			+ "/db/BeamDet/BeamDetParts.xml";
	TString targetGeoFileName = workDirPath + "/geometry/target.h2.geo.root";
	TString gadastGeoFileName = workDirPath + "/geometry/partOfGadast.v1.geo.root";
	TString ndGeoFileName = workDirPath + "/geometry/ND.geo.root";
	TString magnetGeoFileName = workDirPath + "/geometry/magnet.geo.root";
	// ------------------------------------------------------------------------

	// -----   Timer   --------------------------------------------------------
	TStopwatch timer;
	timer.Start();
	// ------------------------------------------------------------------------

	// -----   Create simulation run   ----------------------------------------
	ERRunSim* run = new ERRunSim();
	/** Select transport engine
	 * TGeant3
	 * TGeant4
	 **/
	run->SetName("TGeant4");              // Transport engine
	run->SetOutputFile(outFile.Data());          // Output file
	// ------------------------------------------------------------------------
	// -----   Runtime database   ---------------------------------------------
	FairRuntimeDb* rtdb = run->GetRuntimeDb();
	//-------- Set MC event header --------------------------------------------
	ERDecayMCEventHeader* decayMCheader = new ERDecayMCEventHeader();
	run->SetMCEventHeader(decayMCheader);
	// -----   Create media   -------------------------------------------------
	run->SetMaterials("media.geo");       // Materials
	// -----   Create detectors  ----------------------------------------------
	FairModule* cave= new ERCave("CAVE");
	cave->SetGeometryFileName("cave.geo");
	run->AddModule(cave);

	Int_t verbose = 0;
	// -----  BeamDet Setup ---------------------------------------------------
	ERBeamDetSetup* setupBeamDet = ERBeamDetSetup::Instance();
	setupBeamDet->SetXmlParametersFile(paramFileBeamDet);

	// -----  BeamDet parameters ----------------------------------------------
	setupBeamDet->AddToF("ToF1", BeamDetPosZToF - BeamDetLToF);       //
	setupBeamDet->AddToF("ToF1", BeamDetPosZToF);                     //  BeamDet parts should be added in ascending order
	setupBeamDet->AddMWPC("MWPC1", BeamDetPosZMWPC - BeamDetLMWPC);   //  of Z-coordinate of part.
	setupBeamDet->AddMWPC("MWPC1", BeamDetPosZMWPC);                  //
//	setupBeamDet->SetSensitiveTarget();

	// -----   Create target  -------------------------------------------------
	FairModule* target = new ERTarget("targetH2", kTRUE, 1);
	target->SetGeometryFileName(targetGeoFileName);
	run->AddModule(target);

	// -----  QTelescope Setup ------------------------------------------------
	ERQTelescopeSetup* setupQTelescope = ERQTelescopeSetup::Instance();
	setupQTelescope->SetXmlParametersFile(paramFileQTelescope);

	// ----- T1 parameters ----------------------------------------------------
	TVector3 T1Rotation(0., 0., 0);
	Double_t xPos, yPos, zPos;
	TVector3* T1Translation;
	// ----- T1.1--------------------------------------------------------------
	setupQTelescope->AddSi("DoubleSi_SD1", TVector3(5, 2, T1PosZ   + T1D1Thick/2), T1Rotation,"X");
	setupQTelescope->AddSi("DoubleSi_SD2", TVector3(5, 2, T1PosZ + T1D1Thick +T1Dl + T1D2Thick/2), T1Rotation, "X");

	// ------QTelescope -------------------------------------------------------
	ERQTelescope* qtelescope= new ERQTelescope("ERQTelescope", kTRUE,verbose);
	run->AddModule(qtelescope);

	// ------BeamDet ----------------------------------------------------------
	ERBeamDet* beamdet= new ERBeamDet("ERBeamDet", kTRUE,verbose);
	run->AddModule(beamdet);

	FairPrimaryGenerator* primGen = new FairPrimaryGenerator();

	Double_t  kinE_MevPerNucleon = 1.;
	Double_t  kinE_MevPerNucleonMax = 32.;
	Int_t Z = 2, A = 6, Q = 2;
	TString ionName = "6He";

	ERIonMixGenerator* generator = new ERIonMixGenerator(ionName, Z, A, Q, 1);

	generator->AddBackgroundIon("Triton", 1, 3, 1, 0.2 / 0.20);
	generator->AddBackgroundIon("Alpha", 1, 4, 1, 0.4 / 0.60);
	generator->AddBackgroundIon("HE3", 2, 3, 2, 0.2 / 0.20);
	generator->AddBackgroundIon("Deuteron", 1, 2, 1, 0.2 / 0.20);
	generator->AddBackgroundIon("proton", 1, 1, 1, 0.2 / 0.20);

	Double32_t kin_energy = kinE_MevPerNucleon * 1e-3 * A; //GeV
	Double32_t kin_energy_max = kinE_MevPerNucleonMax * 1e-3 * A; //GeV
	generator->SetKinERange(0.001, 0.02);
	Double32_t sigmaTheta = 0.004*TMath::RadToDeg();
	generator->SetThetaSigma(0, 0);
	generator->SetThetaRange(15, 18);
	generator->SetPhiRange(0, 270);
	generator->SetBoxXYZ(5, 2, 5, 2, 2.);


	primGen->AddGenerator(generator);
	run->SetGenerator(primGen);
	// ------- Decayer --------------------------------------------------------
	Double_t massH5 = (2*939.565 + 2809.431)*0.001;  // [GeV]

	ERDecayer* decayer = new ERDecayer();
	ERDecayEXP1803* targetDecay = new ERDecayEXP1803();
	targetDecay->SetTargetVolumeName("tubeH2");
	targetDecay->SetTargetThickness(targetH2Thickness);
	decayer->AddDecay(targetDecay);
	run->SetDecayer(decayer);

	// ------- QTelescope Digitizer -------------------------------------------
	ERQTelescopeDigitizer* qtelescopeDigitizer = new ERQTelescopeDigitizer(verbose);
	qtelescopeDigitizer->SetSiElossThreshold(0);
	qtelescopeDigitizer->SetSiElossSigma(0);
	qtelescopeDigitizer->SetSiTimeSigma(0);

	qtelescopeDigitizer->SetCsIElossThreshold(0);
	qtelescopeDigitizer->SetCsIElossSigma(0);
	qtelescopeDigitizer->SetCsITimeSigma(0);
	run->AddTask(qtelescopeDigitizer);

	// -----  BeamDet Digitizer ----------------------------------------------
	ERBeamDetDigitizer* beamDetDigitizer = new ERBeamDetDigitizer(verbose);
	beamDetDigitizer->SetMWPCElossThreshold(0.0000012);
	beamDetDigitizer->SetToFTimeSigma(0.4/2.35);
	run->AddTask(beamDetDigitizer);

	// ------- BeamDet TrackFinder -------------------------------------------
	ERBeamDetTrackFinder* trackFinder = new ERBeamDetTrackFinder(verbose);
	run->AddTask(trackFinder);

	// ------- QTelescope TrackFinder -------------------------------------------
	ERQTelescopeTrackFinder* qtelescopeTrackFinder = new ERQTelescopeTrackFinder(verbose);
	qtelescopeTrackFinder->SetHitStation("DoubleSi_SD2_XY_1");
	qtelescopeTrackFinder->SetStripEdepRange(0., 100.);          // [GeV]
	qtelescopeTrackFinder->SetTargetPoint(0., 0., 0.);
//	qtelescopeTrackFinder->SetStripEdepRange(0.016, 100.);   // [GeV]
	qtelescopeTrackFinder->SetEdepMaxDiffXY(0.5);
	run->AddTask(qtelescopeTrackFinder);
	//-------Set visualisation flag to true------------------------------------
	run->SetStoreTraj(kTRUE);
	//-------Set LOG verbosity  -----------------------------------------------
	FairLogger::GetLogger()->SetLogScreenLevel("INFO");
	// -----   Initialize simulation run   ------------------------------------
	run->Init();
	Int_t nSteps = -15000;
	// -----   Runtime database   ---------------------------------------------
	Bool_t kParameterMerged = kTRUE;
	FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
	parOut->open(parFile.Data());
	rtdb->setOutput(parOut);
	rtdb->saveOutput();
	rtdb->print();
	//gMC->SetMaxNStep(nSteps);
	// -----   Run simulation  ------------------------------------------------
	run->Run(nEvents);

	// -----   Finish   -------------------------------------------------------
	timer.Stop();
	Double_t rtime = timer.RealTime();
	Double_t ctime = timer.CpuTime();
	std::cout << std::endl << std::endl;
	std::cout << "Macro finished succesfully." << std::endl;
	std::cout << "Output file is sim.root" << std::endl;
	std::cout << "Parameter file is par.root" << std::endl;
	std::cout << "Real time " << rtime << " s, CPU time " << ctime
			<< "s" << std::endl << std::endl;
}
