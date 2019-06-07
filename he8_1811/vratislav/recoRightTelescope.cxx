#if !defined(__CLING__)


#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TStopwatch.h"
#include "TH2F.h"
#include "TVector3.h"
//#include "TLine.h"
#include "TLorentzVector.h"
#include "TCutG.h"

#include "TROOT.h"

#include "../../beamtime/data/ERBeamTimeEventHeader.h"
#include "../../BeamDet/data/ERBeamDetMWPCDigi.h"
#include "../../telescope/data/ERQTelescopeSiDigi.h"
#include "../../telescope/data/ERQTelescopeCsIDigi.h"

#include "../../BeamDet/data/ERBeamDetTOFDigi.h"

//TELoss library
#include "../../../AculUtilsNew/TELoss/TELoss.h"

#include <iostream>

using std::cout;
using std::endl;

#endif

//RT cuts
#include "cutsRTY.cxx"
#include "cutsRT20X.cxx"
#include "cutsHelium3.cxx"
//#include "cutsHelium3false.cxx"
#include "cutsHelium4.cxx"

//CT cuts
//#include "cutsTritium.cxx"
#include "cutsTritiumCal.cxx"
#include "cutsCsIcal.cxx"

//data members to read
TClonesArray *v_RTY;
TClonesArray *v_RT20;
TClonesArray *v_RTveto;

TClonesArray *v_CTSiX;
TClonesArray *v_CTSiY;
TClonesArray *v_CTCsI;

TClonesArray *v_BD_F3;
TClonesArray *v_BD_F5;


void InitExternalCuts();
void Reset();
void MWPCprojection(TClonesArray *dataX1, TClonesArray *dataY1, TClonesArray *dataX2, TClonesArray *dataY2);

Int_t GetClusterMult(TClonesArray *data);
Float_t GetClusterWire(TClonesArray *data);
Float_t GetPosition(Float_t wire, Float_t wireStep, Float_t planeOffset);

void RT20EdepCorrection(/*TClonesArray *dataSi1mmR, TClonesArray *dataSi20R*/);
void PositionInRT(/*TClonesArray *dataSi1mmR, TClonesArray *dataSi20R*/);

void PositionInCT(/*TClonesArray *dataSi1mmR, TClonesArray *dataSi20R*/);

void Fill4VectorsReactionInput();
void Fill4VectorsHe();
void Fill4VectorsAlphaRT();
void Fill4VectorsTritium();

Bool_t FlagHe();
Bool_t Flag4He();
Bool_t FlagTritium();

void Hydrogen7MissingMass();
void Hydrogen6MissingMass();

void FillHistThickness();
void SetTELossTables();

/////////////////////////////////////////////
//variables to be written in new TTree
Int_t trigger;
/////////////////////////////////////////////

//beam
Float_t fXt;
Float_t fYt;
TVector3 fPointTarget;
TVector3 fBeamDirection;
TVector3 fBeamMomentumToF;
TVector3 fBeamMomentumTarget;

Double_t fToF;
Double_t fBeamKinEtof;
Double_t fBeamKinEtarget;

//right telescope
Float_t fRT20EdepCorrected;
Int_t fRT20StripNbCorrected;
Float_t fMeasuredEdep;

Float_t fYrtLocal;
Float_t fXrtLocal;

TVector3 fXpointRT1;	//in first layer, Y=0
TVector3 fYpointRT2;	//in second layer, X=0
TVector3 fPointRT;

Double_t fAngleBeam3He;

//right telescope helium-3
Double_t fHeKinMeasured;
Double_t fHeKinMeasuredCorrected;
Double_t fHeKinCalculated;
Double_t fHeKinCalculatedMap;



//temporary branches
//	TVector3 fXpointLocal;
//	TVector3 fXpointLocalShifted;
//	TVector3 fXpointLocalRotated;

TVector3 fHeMomentumMeasured;
TVector3 fHeMomentumMeasuredCorrected;
TVector3 fHeMomentumCalculated;
TVector3 fHeMomentumCalculatedMap;

//alpha
//TVector3 f4HeMomentumMeasuredCorrected;

Double_t fAngleLABhtMeasured;
Double_t fAngleLABhtMeasuredCorrected;
Double_t fAngleLABhtCalculated;

Double_t fAngleLAB7hBeamMeasured;
Double_t fAngleLAB7hBeamMeasuredCorrected;
Double_t fAngleLAB7hBeamCalculated;

Double_t fAngleLAB3HeBeamMeasured;
Double_t fAngleLAB3HeBeamMeasuredCorrected;
Double_t fAngleLAB3HeBeamCalculated;

//6H
Double_t fAngleLAB6HtMeasuredCorrected;
Double_t fAngleLAB6HBeamMeasuredCorrected;
Double_t fAngleLAB4HeBeamMeasuredCorrected;

Bool_t fHeFlag;
Bool_t f4HeFlag;
Bool_t fTFlag;

//central telescope
TVector3 fPointCT;

TVector3 fCentralDirection;
Double_t fAngleLAB3HBeam;
Double_t fTritiumKinMeasuredCorrected;
TVector3 fTritiumMomentumMeasuredCorrected;

//particles
TLorentzVector fHeMeasured;
TLorentzVector fHeMeasuredCorrected;
TLorentzVector fHeCalculated;
TLorentzVector fHeCalculatedMap;

TLorentzVector f4HeMeasuredCorrected;

TLorentzVector fT;
TLorentzVector fTMeasuredCorrectedCM;
TLorentzVector fTCalculatedCM;
TLorentzVector fTMeasuredCorrectedCM6H;
TLorentzVector fBeamToF;
TLorentzVector fBeamTarget;
TLorentzVector fTarget;

TLorentzVector fHydrogenMeasured;
TLorentzVector fHydrogenMeasuredCorrected;
TLorentzVector fHydrogenCalculated;
TLorentzVector fHydrogenCalculatedMap;

TLorentzVector fHydrogen6MeasuredCorrected;

TLorentzVector fHydrogenMeasuredCorrectedCM;
TLorentzVector fHydrogenCalculatedCM;

TLorentzVector fHydrogen6MeasuredCorrectedCM;

//////////////////////////////////////////////
// parameters and tools used for analysis
//////////////////////////////////////////////

TH2F *hThickness;

TELoss *f3HeSi;
TELoss *f3HeMylar;
TELoss *f3HeSteel;
TELoss *f3HeTarget;

TELoss *f4HeSi;
TELoss *f4HeMylar;
TELoss *f4HeSteel;
TELoss *f4HeTarget;

TELoss *f8HeSi;
TELoss *f8HeMylar;
TELoss *f8HeSteel;
TELoss *f8HeDeuterium;

TELoss *f3HSi;
TELoss *f3HMylar;
TELoss *f3HSteel;
TELoss *f3HTarget;

//global variables for paths
//TString inPath;
//TString outPath;
TString inPath = "~/data/exp1811/calibrated_filtered/";
TString outPath = "~/data/exp1811/calibrated_filtered/reco/";
//TString inPath = "~/data/exp1811/calibrated_filtered_CsI/";
//TString outPath = "~/data/exp1811/calibrated_filtered_CsI/reco/";

//constants related to geometry
//todo: check these distances
const Float_t k1mmDist = 180.;			//in mm, this is used as the local frame
const Float_t kThinDist = 180.-12.5;	//in mm
const Float_t kSQR_Y_size = 60.;	//in mm
const Int_t kSQR_Y_strips = -16;
const Int_t kSQR_X_strips = -16;
const Float_t kSQR20_X_size = 50.;	//in mm
const Float_t kSQR20_Y_size = 50.;	//in mm

//todo: change other constants to Double_t because of the work with TVector3
const Double_t kCentralSiDist = 280.;
const Int_t kSQC_X_strips = -32;	//direction checked
const Int_t kSQC_Y_strips = -32;	//direction checked
const Double_t kSQC_X_size = 60.;
const Double_t kSQC_Y_size = 60.;

const Double_t kSQR20_Xoffset = -2.5;	//in mm
//todo: check this offset
const Double_t kSQR20_Yoffset = 0.;		//in mm

const Double_t kSQR_angle = -17.;		//in deg

//selection of the beam at target plane
//const Double_t kBeamSelection = 10.5;		//in mm, radius, 84 coincidences found
const Double_t kBeamSelection = 9.;			//in mm, radius, 75 coincidences found
const Double_t kCenterX = -2.2;			//in mm
const Double_t kCenterY = 2.1;				//in mm

//constants related to physics
//masses obtained from NuDat 2.7
Double_t kDeuteriumMass = 1875.613;	//mass of 2H in MeV
Double_t kBeamMass = 7482.539;		//mass of 8He in MeV
Double_t kHeMass = 2808.391;		//mass of 3He in MeV
Double_t k4HeMass = 3727.379;		//mass of 4He in MeV
Double_t kTritiumMass = 2808.921;	//mass of 3H in MeV


//constants related to thicknesses
const Double_t kMWPCthickness = 644.; 	//in ns, effective thickness in Si equivalent
const Double_t kMylarThickness = 3.5;
const Double_t kSteelThickness = 6.;
const Double_t kTargetThickness = 6000.;

//auxiliary variables used for continuous data processing
Int_t mapYbin, mapXbin;

void recoFile(const Int_t noRun, const Int_t noFile, const Long64_t entries, const Bool_t background = 0) {

	TString inFile;
	inFile.Form("he8_%02d_%04d.Digi.root", noRun, noFile);
	TString outFile;
	outFile.Form("he8_%02d_%04d.reco.root", noRun, noFile);


	//	TString inPath = "~/data/exp1811/analysed/";
	//	TString
	//	inPath = "~/data/exp1811/calibrated/";
	//	TString outPath = "~/data/exp1811/analysed/recoFiltered/";
	//	TString
	//	outPath = "~/data/exp1811/calibrated/reco/";

	//	cout << background << endl;

	if (background) {
		inFile.Form("he8_empty_target_%02d_00%02d.Digi.root", noRun, noFile);
		outFile.Form("he8_empty_target_%02d_%04d.reco.root", noRun, noFile);

		//		inPath = "~/data/exp1811/calibrated/background/";
		//		outPath = "~/data/exp1811/calibrated/background/reco/";
	}

	Info("recoFile", "Processing file %s%s", inPath.Data(), inFile.Data());
	Info("recoFile", "Results will be stored in %s%s", outPath.Data(), outFile.Data());

	//	return;

	//	FillHistThickness();

	//////////////////////////
	//Input file
	//////////////////////////
	TFile *fr = new TFile(inPath + inFile);
	if (fr->IsZombie()) {
		Error("recoFile", "File %s%s was not open.", inPath.Data(), inFile.Data());
		return;
	}
	TTree *tr = (TTree*)fr->Get("er");

	//	TChain *tr = new TChain("er");
	//	tr->Add("~/data/exp1811/analysed/he8_07_000*");

	//	tr->StartViewer();
	cout << "Found " << tr->GetEntries() << " entries" << endl;

	ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();

	TClonesArray *v_MWPCx1 = new TClonesArray("ERBeamDetMWPCDigi");
	TClonesArray *v_MWPCy1 = new TClonesArray("ERBeamDetMWPCDigi");
	TClonesArray *v_MWPCx2 = new TClonesArray("ERBeamDetMWPCDigi");
	TClonesArray *v_MWPCy2 = new TClonesArray("ERBeamDetMWPCDigi");

	//	TClonesArray *v_RTY = new TClonesArray("ERQTelescopeSiDigi");
	//	TClonesArray *v_RT20 = new TClonesArray("ERQTelescopeSiDigi");
	v_RTY = new TClonesArray("ERQTelescopeSiDigi");
	v_RT20 = new TClonesArray("ERQTelescopeSiDigi");
	v_RTveto = new TClonesArray("ERQTelescopeSiDigi");

	v_CTSiX = new TClonesArray("ERQTelescopeSiDigi");
	v_CTSiY = new TClonesArray("ERQTelescopeSiDigi");
	v_CTCsI = new TClonesArray("ERQTelescopeCsIDigi");

	v_BD_F3 = new TClonesArray("ERBeamDetTOFDigi");
	//	cout << v_BD_F3 << endl;
	v_BD_F5 = new TClonesArray("ERBeamDetTOFDigi");

	tr->SetBranchAddress("EventHeader.",&header);

	tr->SetBranchAddress("BeamDetMWPCDigiX1",&v_MWPCx1);
	tr->SetBranchAddress("BeamDetMWPCDigiX2",&v_MWPCx2);
	tr->SetBranchAddress("BeamDetMWPCDigiY1",&v_MWPCy1);
	tr->SetBranchAddress("BeamDetMWPCDigiY2",&v_MWPCy2);

	tr->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0",&v_RTY);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0",&v_RT20);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0",&v_RTveto);

	tr->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_Y",&v_CTSiY);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Central_telescope_DoubleSi_DSD_C_XY_0_X",&v_CTSiX);
	tr->SetBranchAddress("ERQTelescopeCsIDigi_Central_telescope_CsI_0",&v_CTCsI);

	tr->SetBranchAddress("BeamDetToFDigi1",&v_BD_F3);
	tr->SetBranchAddress("BeamDetToFDigi2",&v_BD_F5);

	//////////////////////////
	//output file
	//////////////////////////
	TFile *fw = new TFile(outPath + outFile, "RECREATE");
	if (fw->IsZombie()) {
		Error("recoFile", "File %s%s was not open.", outPath.Data(), outFile.Data());
		return;
	}
	TTree *tw = new TTree("reco", "Selected reconstructed variables");

	//	Int_t trigger;
	tw->Branch("trigger",&trigger,"trigger/I");

	//beam
	tw->Branch("fXt",&fXt,"fXt/F");
	tw->Branch("fYt",&fYt,"fYt/F");
	tw->Branch("fPointTarget", "TVector3", &fPointTarget);
	tw->Branch("fBeamDirection", "TVector3", &fBeamDirection);
	tw->Branch("fBeamMomentumToF", "TVector3", &fBeamMomentumToF);
	tw->Branch("fBeamMomentumTarget", "TVector3", &fBeamMomentumTarget);

	tw->Branch("fToF",&fToF,"fToF/D");
	tw->Branch("fBeamKinEtof",&fBeamKinEtof,"fBeamKinEtof/D");
	tw->Branch("fBeamKinEtarget",&fBeamKinEtarget,"fBeamKinEtarget/D");

	//right telescope
	tw->Branch("fMeasuredEdep",&fMeasuredEdep,"fMeasuredEdep/F");
	tw->Branch("fRTEdepCorr",&fRT20EdepCorrected,"fRT20EdepCorrected/F");
	tw->Branch("fRTEStripCorr",&fRT20StripNbCorrected,"fRT20StripNbCorrected/I");

	tw->Branch("fYrtLocal", &fYrtLocal, "fYrtLocal/F");
	tw->Branch("fXrtLocal", &fXrtLocal, "fXrtLocal/F");

	tw->Branch("fXpointRT1", "TVector3", &fXpointRT1);
	tw->Branch("fYpointRT2", "TVector3", &fYpointRT2);
	tw->Branch("fPointRT", "TVector3", &fPointRT);
	tw->Branch("fAngleBeam3He",&fAngleBeam3He,"fAngleBeam3He/D");
	//	tw->Branch("fTrack", "TLine", &fTrack);

	//helium-3
	tw->Branch("fHeKinMeasured",&fHeKinMeasured,"fHeKinMeasured/D");
	tw->Branch("fHeKinMeasuredCorrected",&fHeKinMeasuredCorrected,"fHeKinMeasuredCorrected/D");
	tw->Branch("fHeKinCalculated",&fHeKinCalculated,"fHeKinCalculated/D");
	tw->Branch("fHeKinCalculatedMap",&fHeKinCalculatedMap,"fHeKinCalculatedMap/D");

	//central telescope
	tw->Branch("fPointCT", "TVector3", &fPointCT);
	tw->Branch("fCentralDirection", "TVector3", &fCentralDirection);
	tw->Branch("fAngleLAB3HBeam",&fAngleLAB3HBeam,"fAngleLAB3HBeam/D");
	tw->Branch("fTritiumKinMeasuredCorrected",&fTritiumKinMeasuredCorrected,"fTritiumKinMeasuredCorrected/D");

	//particles:
	tw->Branch("fHeMeasured", "TLorentzVector", &fHeMeasured);
	tw->Branch("fHeMeasuredCorrected", "TLorentzVector", &fHeMeasuredCorrected);
	tw->Branch("fHeCalculated", "TLorentzVector", &fHeCalculated);
	tw->Branch("fHeCalculatedMap", "TLorentzVector", &fHeCalculatedMap);

	tw->Branch("f4HeMeasuredCorrected", "TLorentzVector", &f4HeMeasuredCorrected);

	//angles:
	tw->Branch("fAngleLABhtMeasured",&fAngleLABhtMeasured,"fAngleLABhtMeasured/D");
	tw->Branch("fAngleLABhtMeasuredCorrected",&fAngleLABhtMeasuredCorrected,"fAngleLABhtMeasuredCorrected/D");
	tw->Branch("fAngleLABhtCalculated",&fAngleLABhtCalculated,"fAngleLABhtCalculated/D");

	tw->Branch("fAngleLAB7hBeamMeasured",&fAngleLAB7hBeamMeasured,"fAngleLAB7hBeamMeasured/D");
	tw->Branch("fAngleLAB7hBeamMeasuredCorrected",&fAngleLAB7hBeamMeasuredCorrected,"fAngleLAB7hBeamMeasuredCorrected/D");
	tw->Branch("fAngleLAB7hBeamCalculated",&fAngleLAB7hBeamCalculated,"fAngleLAB7hBeamCalculated/D");


	tw->Branch("fAngleLAB3HeBeamMeasured",&fAngleLAB3HeBeamMeasured,"fAngleLAB3HeBeamMeasured/D");
	tw->Branch("fAngleLAB3HeBeamMeasuredCorrected",&fAngleLAB3HeBeamMeasuredCorrected,"fAngleLAB3HeBeamMeasuredCorrected/D");
	tw->Branch("fAngleLAB3HeBeamCalculated",&fAngleLAB3HeBeamCalculated,"fAngleLAB3HeBeamCalculated/D");

	//6H
	tw->Branch("fAngleLAB6HtMeasuredCorrected",&fAngleLAB6HtMeasuredCorrected,"fAngleLAB6HtMeasuredCorrected/D");
	tw->Branch("fAngleLAB6HBeamMeasuredCorrected",&fAngleLAB6HBeamMeasuredCorrected,"fAngleLAB6HBeamMeasuredCorrected/D");
	tw->Branch("fAngleLAB4HeBeamMeasuredCorrected",&fAngleLAB4HeBeamMeasuredCorrected,"fAngleLAB4HeBeamMeasuredCorrected/D");

	//tritium
	tw->Branch("fT", "TLorentzVector", &fT);
	tw->Branch("fTMeasuredCorrectedCM", "TLorentzVector", &fTMeasuredCorrectedCM);
	tw->Branch("fTCalculatedCM", "TLorentzVector", &fTCalculatedCM);
	tw->Branch("fTMeasuredCorrectedCM6H", "TLorentzVector", &fTMeasuredCorrectedCM6H);

	//beam
	tw->Branch("fBeamToF", "TLorentzVector", &fBeamToF);
	tw->Branch("fBeamTarget", "TLorentzVector", &fBeamTarget);
	tw->Branch("fTarget", "TLorentzVector", &fTarget);

	//7H
	tw->Branch("fHydrogenMeasured", "TLorentzVector", &fHydrogenMeasured);
	tw->Branch("fHydrogenMeasuredCorrected", "TLorentzVector", &fHydrogenMeasuredCorrected);
	tw->Branch("fHydrogenCalculated", "TLorentzVector", &fHydrogenCalculated);
	tw->Branch("fHydrogenCalculatedMap", "TLorentzVector", &fHydrogenCalculatedMap);

	tw->Branch("fHydrogen6MeasuredCorrected", "TLorentzVector", &fHydrogen6MeasuredCorrected);

	tw->Branch("fHydrogenMeasuredCorrectedCM", "TLorentzVector", &fHydrogenMeasuredCorrectedCM);
	tw->Branch("fHydrogenCalculatedCM", "TLorentzVector", &fHydrogenCalculatedCM);

	tw->Branch("fHydrogen6MeasuredCorrectedCM", "TLorentzVector", &fHydrogen6MeasuredCorrectedCM);

	//flags
	tw->Branch("fHeFlag",&fHeFlag,"fHeFlag/O");
	tw->Branch("f4HeFlag",&f4HeFlag,"f4HeFlag/O");
	tw->Branch("fTFlag",&fTFlag,"fTFlag/O");

	//todo: temporary branches to be deleted
	//	tw->Branch("fXpointLocal", "TVector3", &fXpointLocal);
	//	tw->Branch("fXpointLocalRotated", "TVector3", &fXpointLocalRotated);
	//	tw->Branch("fXpointLocalShifted", "TVector3", &fXpointLocalShifted);

	Long64_t noEntries = tr->GetEntries();
	if (entries < noEntries) noEntries = entries;
	if (entries == 0) noEntries = tr->GetEntries();
	//	Long64_t noEntries = 100000;

	//set TEloss tables

	InitExternalCuts();

	SetTELossTables();

	//todo: first event is triggered by 1 for some reason

	//	for(Long64_t nentry = 1; nentry < noEntries; nentry++) {
	for(Long64_t nentry = 0; nentry < noEntries; nentry++) {

		if(nentry%100000==0) cout << "#Event " << nentry << "#" << endl;

		Reset();

		tr->GetEntry(nentry);

		trigger = header->GetTrigger();

		MWPCprojection(v_MWPCx1, v_MWPCy1, v_MWPCx2, v_MWPCy2);

		//	    RT20EdepCorrection(v_RTY, v_RT20);
		RT20EdepCorrection();

		PositionInRT(/*v_RTY, v_RT20*/);

		PositionInCT();

		Fill4VectorsReactionInput();

		Fill4VectorsHe();
		Fill4VectorsAlphaRT();

		Fill4VectorsTritium();

		fHeFlag = FlagHe();
		f4HeFlag = Flag4He();
		fTFlag = FlagTritium();

		if (fHeFlag) {
			Hydrogen7MissingMass();
		}

		if (f4HeFlag) {
			Hydrogen6MissingMass();
		}

		tw->Fill();

	}

	fw->cd();
	tw->Write();
	fw->Close();
	Info("recoFile", "File %s was closed.", outFile.Data());
	Info("recoFile", "Processing of file %s finished.", inFile.Data());
	fr->cd();
	fr->Close();
	Info("recoFile", "File %s was closed.", inFile.Data());

}

void InitInputTree() {}
void InitOutputTree() {}

void InitExternalCuts() {

	//right telescope
	const Bool_t useFirstLayerCuts = 1;
	const Bool_t useSecondLayerCuts = 1;
	const Bool_t useHeliumCuts = 1;
	const Bool_t useAlphaCuts = 1;

	//left telescope
	const Bool_t useTritiumCuts = 1;
	const Bool_t useCsICuts = 0;

	if (useSecondLayerCuts) {
		cutsRT20X();
	}

	if (useSecondLayerCuts) {
		cutsRTY();
	}

	if (useHeliumCuts) {
		cutsHelium3();
	}

	if (useAlphaCuts) {
		cutsHelium4();
	}

	if (useTritiumCuts) {
		cutsTritium();
	}

	if (useCsICuts) {
		cutsCsI();
	}
}

void Reset() {
	trigger = 0;

	fXt = -50.;
	fYt = -50.;

	fToF = 0.;
	fBeamKinEtof = 0.;
	fBeamKinEtarget = 0.;

	fRT20EdepCorrected = 0.;
	fRT20StripNbCorrected = -1;
	fMeasuredEdep = 0.;

	fYrtLocal = -100.;
	fXrtLocal = -100.;
	fPointTarget.SetXYZ(0., 0., -50.);
	fBeamDirection.SetXYZ(0., 0., 0.);
	fBeamMomentumToF.SetXYZ(0., 0., 0.);
	fBeamMomentumTarget.SetXYZ(0., 0., 0.);

	fXpointRT1.SetXYZ(0., 0., 0.);
	fYpointRT2.SetXYZ(0., 0., 0.);
	fPointRT.SetXYZ(0., 0., 0.);
	fAngleBeam3He = TMath::Pi();

	fHeKinCalculated = 0.;
	fHeKinCalculatedMap = 0.;
	fHeKinMeasured = 0.;
	fHeKinMeasuredCorrected = 0.;

	fPointCT.SetXYZ(0., 0., 0.);
	fCentralDirection.SetXYZ(0., 0., 0.);
	fAngleLAB3HBeam = TMath::Pi();
	fTritiumKinMeasuredCorrected = 0.;

	fHeMeasured.SetPxPyPzE(0., 0., 0., 0.);
	fHeMeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);
	fHeCalculated.SetPxPyPzE(0., 0., 0., 0.);
	fHeCalculatedMap.SetPxPyPzE(0., 0., 0., 0.);

	f4HeMeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);

	fAngleLABhtMeasured = 0.;
	fAngleLABhtMeasuredCorrected = 0.;
	fAngleLABhtCalculated = 0.;

	fAngleLAB7hBeamMeasured = 0.;
	fAngleLAB7hBeamMeasuredCorrected = 0.;
	fAngleLAB7hBeamCalculated = 0.;

	fAngleLAB3HeBeamMeasured = 0.;
	fAngleLAB3HeBeamMeasuredCorrected = 0.;
	fAngleLAB3HeBeamCalculated = 0.;

	//6H
	fAngleLAB6HtMeasuredCorrected = 0.;
	fAngleLAB6HBeamMeasuredCorrected = 0.;
	fAngleLAB4HeBeamMeasuredCorrected = 0.;

	fT.SetPxPyPzE(0., 0., 0., 0.);
	fTMeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);
	fTCalculatedCM.SetPxPyPzE(0., 0., 0., 0.);
	fTMeasuredCorrectedCM6H.SetPxPyPzE(0., 0., 0., 0.);

	fBeamToF.SetPxPyPzE(0., 0., 0., 0.);
	fBeamTarget.SetPxPyPzE(0., 0., 0., 0.);
	fTarget.SetPxPyPzE(0., 0., 0., 0.);

	fHydrogenMeasured.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogenMeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogenCalculated.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogenCalculatedMap.SetPxPyPzE(0., 0., 0., 0.);

	fHydrogen6MeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);

	fHydrogenMeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogenCalculatedCM.SetPxPyPzE(0., 0., 0., 0.);

	fHydrogen6MeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);

	fHeFlag = 0;
	f4HeFlag = 0;
	fTFlag = 0;
	//	fTrack.SetX1(0.);
	//	fTrack.SetX2(0.);
	//	fTrack.SetY1(0.);
	//	fTrack.SetY2(0.);

	//	fXpointLocal.SetXYZ(0., 0., 0.);
	//	fXpointLocalRotated.SetXYZ(0., 0., 0.);
	//	fXpointLocalShifted.SetXYZ(0., 0., 0.);

}

Double_t GetP(const Double_t kinE, const Double_t mass) {

	return TMath::Sqrt( kinE*kinE + 2*kinE*mass );

}

Int_t GetClusterMult(TClonesArray *data)
{

	if (!data) return 0;

	Int_t entries = data->GetEntriesFast();

	if (entries<2) return entries;

	Int_t wire1, wire2;
	Int_t noclusters = 1;



	for (Int_t i = 1; i < entries; i++) {
		//check if entries are in specific order
		wire1 = ((ERBeamDetMWPCDigi*)data->At(i))->GetWireNb();
		wire2 = ((ERBeamDetMWPCDigi*)data->At(i-1))->GetWireNb();

		//		cout << wire2 << "\t" << wire1 << endl;
		//todo number 32 is related to number of wires
		// and should be taken from Parameters
		if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 32) noclusters++;
	}

	return noclusters;
}

Float_t GetClusterWire(TClonesArray *data)
{
	//working correctly only for cluster multiplicity equal to 1
	//get wire number in, generally, half-numbers, i.e. if cluster
	//consists from 2 wires n and n+1, cluster position is n+0.5

	Int_t wire1 = ((ERBeamDetMWPCDigi*)data->At(0))->GetWireNb();

	return (Float_t)wire1 + 0.5*((Float_t)data->GetEntriesFast()-1.);

} //--------------------------------------------------------------------

Float_t GetPosition(Float_t wire, Float_t wireStep,
		Float_t planeOffset) {
	//TODO: number of wires (16) as parameter
	//TODO: omit gRandom
	return (wire + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16)*wireStep + planeOffset;
}

void MWPCprojection(TClonesArray *dataX1, TClonesArray *dataY1, TClonesArray *dataX2, TClonesArray *dataY2) {

	if (GetClusterMult(dataX1)!=1 || GetClusterMult(dataY1)!=1 || GetClusterMult(dataX2)!=1 || GetClusterMult(dataY2)!=1) {
		return;
	}

	const Float_t fMWPCwireStepX1 = -1.25;
	const Float_t fMWPCwireStepY1 = 1.25;		//step between two wires
	const Float_t fMWPCwireStepX2 = -1.25;		//step between two wires
	const Float_t fMWPCwireStepY2 = 1.25;		//step between two wires

	const Float_t fMWPC1_X_offset = 0.;
	const Float_t fMWPC1_Y_offset = 0.;
	const Float_t fMWPC2_X_offset = 0.;
	const Float_t fMWPC2_Y_offset = 0.;

	const Float_t kMWPCz1 = -815.;	//z coordinate of the center of MWPC1
	const Float_t kMWPCz2 = -270.;	//z coordinate of the center of MWPC2

	Float_t x1c, y1c, x2c, y2c, xtc, ytc;

	Float_t wireC[4]; //x1, y1, x2, y2

	TClonesArray* v_MWPC[4] = { dataX1, dataY1, dataX2, dataY2 };	//x1, y1, x2, y2


	for (Int_t i = 0; i < 4; i++) {
		wireC[i] = GetClusterWire(v_MWPC[i]);
	}


	//cluster multiplicity equal to 1
	x1c = GetPosition(wireC[0], fMWPCwireStepX1, fMWPC1_X_offset);
	y1c = GetPosition(wireC[1], fMWPCwireStepY1, fMWPC1_Y_offset);

	x2c = GetPosition(wireC[2], fMWPCwireStepX2, fMWPC2_X_offset);
	y2c = GetPosition(wireC[3], fMWPCwireStepY2, fMWPC2_Y_offset);

	xtc = x1c - (x2c -x1c)*kMWPCz1/(kMWPCz2-kMWPCz1);
	ytc = y1c - (y2c -y1c)*kMWPCz1/(kMWPCz2-kMWPCz1);

	fXt = xtc;
	fYt = ytc;

	fPointTarget.SetXYZ(fXt, fYt, 0.);
	//beam direction
	TVector3 beamDirection(fXt-x1c, fYt-y1c, -kMWPCz1);
	//	fBeamDirection.SetXYZ(fXt-x1c, fYt-y1c, kMWPCz1);
	fBeamDirection = beamDirection.Unit();
	//	cout << fBeamDirection.Mag() << endl;

}

void RT20EdepCorrection(/*TClonesArray *dataSi1mmR, TClonesArray *dataSi20R*/) {

	//	cout << data->GetEntriesFast() << endl;
	if (v_RT20->GetEntriesFast() != 1 || v_RTY->GetEntriesFast() != 1) {
		return;
	}

	if (fXt < -40. || fYt < -40.) {
		return;
	}

	//	const Double_t kSQ20_norm_thickness = 20.;
	const Double_t kSQ20_norm_thickness = 23.;

	Float_t y1mm = -100.;
	Float_t y20mcm = -100;
	Float_t x20mcm = -100;
	//	TVector3 vHit20mcm;
	TVector3 vNorm(0.,0.,1.);
	Double_t angleRight;

	//todo: offset is not used in this function

	//	Int_t mapYbin, mapXbin;
	Double_t currThickness;

	//signum strips
	Int_t signXstrips = (kSQR_X_strips>0) - (kSQR_X_strips<0);
	Int_t signYstrips = (kSQR_Y_strips>0) - (kSQR_Y_strips<0);


	//	Int_t xStrip = ((ERQTelescopeSiDigi*)dataSi20R->At(0))->GetStripNb();
	//	Int_t yStrip = ((ERQTelescopeSiDigi*)dataSi1mmR->At(0))->GetStripNb();
	Int_t xStrip = ((ERQTelescopeSiDigi*)v_RT20->At(0))->GetStripNb();
	Int_t yStrip = ((ERQTelescopeSiDigi*)v_RTY->At(0))->GetStripNb();

	//todo: try to investigate 20 mcm offset
	y1mm = ( yStrip + 0.5 )*kSQR_Y_size/kSQR_Y_strips - signYstrips*kSQR_Y_size/2.;	//ok
	x20mcm = ( xStrip + 0.5 )*kSQR20_X_size/kSQR_X_strips - signXstrips*kSQR20_X_size/2.;	//ok


	//	TMath::Sign()
	//vHit1mm conversion to plane of thin detector
	//	y20mcm = y1mm*zThin/z1mm;
	//	vHit20mcm.SetXYZ(x20mcm-fXt, y20mcm-fYt, zThin);
	//	angleRight = vHit20mcm.Angle(vNorm);

	y20mcm = (y1mm-fYt)*kThinDist/k1mmDist;
	y20mcm = y20mcm+fYt;
	//	vHit20mcm.SetXYZ(x20mcm, y20mcm, zThin);
	//	angleRight = vHit20mcm.Angle(vNorm);

	//	if ( yStrip < 3 || yStrip > 13 ) {
	////	if ( xStrip > 6 ) {
	////		cout << xStrip << "\t" << x20mcm << endl;
	//		cout << yStrip << "\t" << y1mm  << "\t" << y20mcm << "\t" << fYt << endl;
	//	}

	//check if the particle passed through sensitive area of thin detector
	if ( y20mcm < (kSQR20_Y_size/2.) && y20mcm > (-kSQR20_Y_size/2.) ) {
		//		x20mcm = vHit20mcm.X()+fXt;
		//		y20mcm = vHit20mcm.Y()+fYt;

		mapYbin = y20mcm*kSQR_Y_strips/kSQR_Y_size - kSQR_Y_strips/2.;	//ok
		//		mapXbin = x20mcm*kSQL_20_strips/kSQ20_X_size - kSQL_20_strips/2.;	//ok
		mapXbin = xStrip;	//ok
		//		mapYbin = yStrip;

		//calculation of corrected energy
		//TODO: check the mapping here at second
		currThickness = hThickness->GetBinContent(mapXbin+1, mapYbin+1);		//1 the best effect at c8
		//		currThickness = hThickness->GetBinContent(15-mapXbin+1, mapYbin+1);		//2 observable effect at c8
		//		currThickness = hThickness->GetBinContent(mapXbin+1, 15-mapYbin+1);		//3 definitely worse than without correction
		//		currThickness = hThickness->GetBinContent(15-mapXbin+1, 15-mapYbin+1);	//4  definitely worse than without correction
		//		cout << xStrip << "\t" << yStrip << "\t" << currThickness << endl;

		//		measuredEdep = (Double_t)((ERQTelescopeSiDigi*)dataSi20R->At(0))->GetEdep();
		fMeasuredEdep = (Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetEdep();
		fRT20EdepCorrected = (kSQ20_norm_thickness/currThickness)*fMeasuredEdep;
		fRT20StripNbCorrected = xStrip;

		//		cout << measuredEdep << "\t" << fRT20EdepCorrected << "\t" << currThickness << endl;

		//		cout << fRT20EdepCorrected << "\t" << fRT20StripNbCorrected << endl;

	}//if inside the map


	//	if

	return;
}

void PositionInRT(/*TClonesArray *dataSi1mmR, TClonesArray *dataSi20R*/) {
	if (v_RTY->GetEntriesFast() != 1 || v_RT20->GetEntriesFast() != 1) {
		return;
	}

	if (fXt < -40. || fYt < -40.) {
		return;
	}


	////////////////////////////////////////////////////////////
	// coordinate Y in local frame of the right telescope
	// (plane of the 1mm Si detector - second layer - is
	// regarded as the local frame
	////////////////////////////////////////////////////////////
	Float_t y1mm = -100.;

	Int_t signYstrips = (kSQR_Y_strips>0) - (kSQR_Y_strips<0);
	const Int_t yStrip = ((ERQTelescopeSiDigi*)v_RTY->At(0))->GetStripNb();

	y1mm = ( yStrip + 0.5 )*kSQR_Y_size/kSQR_Y_strips - signYstrips*kSQR_Y_size/2.;	//ok

	fYpointRT2.SetXYZ(0., y1mm, k1mmDist);
	fYpointRT2.RotateY(kSQR_angle*TMath::DegToRad());

	////////////////////////////////////////////////////////////
	// coordinate X in local frame of the right telescope
	// (plane of the 1mm Si detector - second layer - is
	// regarded as the local frame
	////////////////////////////////////////////////////////////

	//coordinate X in plane of the 20 mcm detector
	Float_t x20mcm = -100.;

	const Int_t signXstrips = (kSQR_X_strips>0) - (kSQR_X_strips<0);
	const Int_t xStrip = ((ERQTelescopeSiDigi*)v_RT20->At(0))->GetStripNb();

	x20mcm = kSQR20_Xoffset + ( xStrip + 0.5 )*kSQR20_X_size/kSQR_X_strips - signXstrips*kSQR20_X_size/2.;	//ok

	//	fXpointLocal.SetXYZ(x20mcm-kSQR20_Xoffset, 0., kThinDist);
	//	fXpointLocalShifted.SetXYZ(x20mcm, 0., kThinDist);
	//
	//	fXpointLocalRotated = fXpointLocal;
	//	fXpointLocalRotated.RotateY(kSQR_angle*TMath::DegToRad());

	//set X and Z coordinates (projection to XZ plane
	fXpointRT1.SetXYZ(x20mcm, 0., kThinDist);
	//	fXpoint.SetXYZ(x20mcm+kSQR20_Xoffset, 0., kThinZ);

	//rotation as the detector is rotated
	fXpointRT1.RotateY(kSQR_angle*TMath::DegToRad());

	//projection to plane of the second layer
	// in 5 steps:
	//
	// 1) shift for projection of the beam: new X = X(20) - X(target)
	// 2) calculation of angle beta between shifted track and detector normal
	//		using TVector::Theta() method
	// 3) change shifted detector magnitude for track distance between
	//		the first and the second RT layer:
	//		a) trackDistance = kDist*cos(beta)
	//		b) newMag = shiftedMag + trackDistance
	// 4) new X coordinate in 1mm detector plane:
	//		x of shifted projection with newMag + X(target)

	// 1)
	TVector3 vAux(0., 0., 0.);
	vAux.SetXYZ(fXpointRT1.X() - fXt, 0., fXpointRT1.Z());

	// 2)
	//todo: use "-" sign because Theta is always positive but
	//	our constant angle is negative
	Double_t beta = -vAux.Theta() - kSQR_angle*TMath::DegToRad();

	// 3)
	Double_t trackBetweenLayersDistance = (Double_t)(k1mmDist - kThinDist)/TMath::Cos(beta);
	//	Double_t trackBetweenLayersDistance = (Double_t)(k1mmDist - kThinDist)/TMath::Cos(kSQR_angle)/TMath::Cos(beta);
	Double_t shiftedMag = vAux.Mag();
	vAux.SetMag(shiftedMag + trackBetweenLayersDistance);

	// 4)
	fPointRT.SetXYZ(vAux.X() + fXt, fYpointRT2.Y(), vAux.Z());

	//asign calculated variables to tree branches:
	fYrtLocal = y1mm;
	fXrtLocal = x20mcm;
}

void PositionInCT(/*TClonesArray *dataSi1mmR, TClonesArray *dataSi20R*/) {
	if (v_CTSiX->GetEntriesFast() != 1 || v_CTSiY->GetEntriesFast() != 1) {
		//		cout << "return mult" << endl;
		return;
	}

	if (fXt < -40. || fYt < -40.) {
		//		cout << "return target" << endl;
		return;
	}


	////////////////////////////////////////////////////////////
	// coordinate Y in local frame of the central Si telescope
	// (plane of the Si detector is regarded as the local frame)
	////////////////////////////////////////////////////////////
	Double_t yCT = -100.;

	//todo: make as the function; its repeating too often
	Int_t signYstrips = (kSQC_Y_strips>0) - (kSQC_Y_strips<0);
	Int_t yStrip = ((ERQTelescopeSiDigi*)v_CTSiY->At(0))->GetStripNb();

	yCT = ( yStrip + 0.5 )*kSQC_Y_size/kSQC_Y_strips - signYstrips*kSQC_Y_size/2.;	//ok

	////////////////////////////////////////////////////////////
	// coordinate X in local frame of the central Si telescope
	// (plane of the Si detector is regarded as the local frame)
	////////////////////////////////////////////////////////////

	//coordinate X in plane of the 20 mcm detector
	Double_t xCT = -100.;

	Int_t signXstrips = (kSQC_X_strips>0) - (kSQC_X_strips<0);
	Int_t xStrip = ((ERQTelescopeSiDigi*)v_CTSiX->At(0))->GetStripNb();

	xCT = ( xStrip + 0.5 )*kSQC_X_size/kSQC_X_strips - signXstrips*kSQC_X_size/2.;	//ok

	//fill vector with point
	fPointCT.SetXYZ(xCT, yCT, kCentralSiDist);

}

void Fill4VectorsReactionInput() {
	//target
	fTarget.SetPxPyPzE(0., 0., 0., kDeuteriumMass);

	//beam

	if (fBeamDirection.Mag()==0.) return;

	//times in F3 and F5 already corrected for calibration parameter
	Double_t fF3t = ( (ERBeamDetTOFDigi*)v_BD_F3->At(0) )->GetTime()/2.;
	Double_t fF5t = ( (ERBeamDetTOFDigi*)v_BD_F5->At(0) )->GetTime()/2.;

	const Double_t kToF = 68.553;				//in ns; reported by SK on Redmine
	//	const Double_t kToF = 68.475;				//in ns; reported by MS
	//	const Double_t kToF = 89.165;				//in ns, my old parameter
	//	const Double_t kToF = 87.8;					//in ns; SK, 11.01.19, EXP1803 and EXP1804
	//	const Double_t kToF = 82.132;				//in ns; SK, 10.10.18, EXP1803 and EXP1804
	//	const Double_t kToF = 89.171;				//in ns; SK, 10.10.18, beginning of EXP1803 and EXP1804
	const Double_t kToFbase = 12320.; 			//in mm
	const Double_t kSpeedOfLight = 299.792458;	//mm in ns

	fToF = (fF5t - fF3t) + kToF;

	Double_t velocity = kToFbase/fToF;
	Double_t beta = velocity/kSpeedOfLight;
	Double_t gamma = 1./TMath::Sqrt(1-beta*beta);

	Double_t kinE = kBeamMass*(gamma - 1);

	//energy and 4vector at ToF exit
	fBeamKinEtof = kinE;

	Double_t momentum = TMath::Sqrt( kinE*kinE + 2*kinE*kBeamMass );

	fBeamMomentumToF = fBeamDirection;
	fBeamMomentumToF.SetMag(momentum);

	fBeamToF.SetVectM(fBeamMomentumToF, kBeamMass);

	//energy and 4vector in the center of the target
	//energy losses for:
	//	- MWPC (in Si equivalent)
	//	- mylar
	//	- steel
	//	- half of target gass
	kinE = f8HeSi->GetE(kinE, kMWPCthickness);
	kinE = f8HeMylar->GetE(kinE, kMylarThickness);
	kinE = f8HeSteel->GetE(kinE, kSteelThickness);
	fBeamKinEtarget = f8HeDeuterium->GetE(kinE, kTargetThickness/2.);

	momentum = TMath::Sqrt( fBeamKinEtarget*fBeamKinEtarget + 2*fBeamKinEtarget*kBeamMass );

	fBeamMomentumTarget = fBeamDirection;
	fBeamMomentumTarget.SetMag(momentum);

	fBeamTarget.SetVectM(fBeamMomentumTarget, kBeamMass);

}

Bool_t FlagTritium() {


	if (v_CTSiX->GetEntries()!=1 || v_CTSiY->GetEntries()!=1) {
		return kFALSE;
	}

	const Double_t measuredXtime =
			(Double_t)((ERQTelescopeSiDigi*)v_CTSiX->At(0))->GetTime()- ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;
	if (measuredXtime<100. || measuredXtime>135.) return kFALSE;

	const Double_t measuredYtime =
			(Double_t)((ERQTelescopeSiDigi*)v_CTSiY->At(0))->GetTime()- ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;
	if (measuredYtime<100. || measuredYtime>135.) return kFALSE;

	return kTRUE;

	Bool_t flagID = 0.;

	//	cut.Form(" (%s", cTritium[0]->GetName());
	for (Int_t i = 0; i < 16; i++) {
		if (i==9) continue;
		//todo: maximum amplitude in CsI inside the cut
		//			if ( (TString)cTritium[i]->GetName() ) /*return 0*/;
	}

	//		v_RTY->Get

	//	return 0;
}

Bool_t FlagHe() {
	//return 1 if 3He was found
	//coincidences with tritium not taken into account


	if (v_RT20->GetEntries()!=1 || v_RTY->GetEntries()!=1 || v_RTveto->GetEntries()!=0) {
		return kFALSE;
	}


	//add target condition
	if ( ( (fYt-kCenterY)*(fYt-kCenterY) + (fXt-kCenterX)*(fXt-kCenterX) ) >= kBeamSelection*kBeamSelection) {
		return kFALSE;
	}

	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetEdep();
	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RTY->At(0))->GetEdep();

	if( !( (measuredEdepX>0.) && (measuredEdepY>0.) && (fRT20EdepCorrected>0.) ) ) return kFALSE;

	//add 3He ID cut
	Bool_t flagHeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if ( fRT20StripNbCorrected==i && cHelium3[i]->IsInside(measuredEdepY, (Double_t)fRT20EdepCorrected*1000.) ) {
			flagHeCut = kTRUE;
			//			if (measuredEdepY<0.5) {
			//				cout << "!!!!!!!!!!!!!!!!!!!!!!!\t" << measuredEdepY << endl;
			//			}
		}
	}

	//add RT time cuts
	const Double_t measuredXtime =
			(Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	//	TString cut;
	Bool_t flagRTXtimeCut = 0;
	//for all 16 strips in thin detector
	for (Int_t i = 0; i < 16; i++) {
		if (fRT20StripNbCorrected==i && cRT20X[i]->IsInside(measuredXtime, measuredEdepX)) {
			flagRTXtimeCut = kTRUE;
		}
	}


	const Double_t measuredYtime =
			(Double_t)((ERQTelescopeSiDigi*)v_RTY->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	Bool_t flagRTYtimeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if (fRT20StripNbCorrected==i && cRTY[i]->IsInside(measuredYtime, measuredEdepY)) {
			flagRTYtimeCut = kTRUE;
		}
	}

	return flagHeCut*flagRTXtimeCut*flagRTYtimeCut;
}

Bool_t Flag4He() {
	//return 1 if 4He was found
	//coincidences with tritium not taken into account


	if (v_RT20->GetEntries()!=1 || v_RTY->GetEntries()!=1 || v_RTveto->GetEntries()!=0) {
		return kFALSE;
	}


	//add target condition
	if ( ( (fYt-kCenterY)*(fYt-kCenterY) + (fXt-kCenterX)*(fXt-kCenterX) ) >= kBeamSelection*kBeamSelection) {
		return kFALSE;
	}

	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetEdep();
	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RTY->At(0))->GetEdep();

	if( !( (measuredEdepX>0.) && (measuredEdepY>0.) && (fRT20EdepCorrected>0.) ) ) return kFALSE;

	//add 3He ID cut
	Bool_t flagHeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if ( fRT20StripNbCorrected==i && cHelium4[i]->IsInside(measuredEdepY, (Double_t)fRT20EdepCorrected*1000.) ) {
			flagHeCut = kTRUE;
			//			if (measuredEdepY<0.5) {
			//				cout << "!!!!!!!!!!!!!!!!!!!!!!!\t" << measuredEdepY << endl;
			//			}
		}
	}

	//add RT time cuts
	const Double_t measuredXtime =
			(Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	//	TString cut;
	Bool_t flagRTXtimeCut = 0;
	//for all 16 strips in thin detector
	for (Int_t i = 0; i < 16; i++) {
		if (fRT20StripNbCorrected==i && cRT20X[i]->IsInside(measuredXtime, measuredEdepX)) {
			flagRTXtimeCut = kTRUE;
		}
	}


	const Double_t measuredYtime =
			(Double_t)((ERQTelescopeSiDigi*)v_RTY->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	Bool_t flagRTYtimeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if (fRT20StripNbCorrected==i && cRTY[i]->IsInside(measuredYtime, measuredEdepY)) {
			flagRTYtimeCut = kTRUE;
		}
	}

	return flagHeCut*flagRTXtimeCut*flagRTYtimeCut;
}

void Fill4VectorsHe() {

	if (v_RT20->GetEntriesFast() != 1 || v_RTY->GetEntriesFast() != 1) {
		return;
	}

	if (fXt < -40. || fYt < -40.) {
		return;
	}

	const Double_t kDeadLayerBetweenSi = 1.;			//in mcm
	const Double_t kDeadLayerEntranceThin = 0.5;			//in mcm
	//todo: check meaning of normalized thickness
	//	const Double_t kThinDetNormalizedThickness = 20.; 	//in mcm
	const Double_t kThinDetNormalizedThickness = 23.; 	//in mcm

	Double_t kinE = 0;

	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RTY->At(0))->GetEdep();
	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetEdep();

	//////////////////////////////////////////////
	// direction of particles registered in RT
	//////////////////////////////////////////////

	TVector3 rtDirection(fPointRT.X() - fXt, fPointRT.Y() - fYt, fPointRT.Z());
	rtDirection.Unit();

	//angle of 8He to 3He
	fAngleBeam3He = rtDirection.Angle(fBeamDirection);

	//////////////////////////////////////////////
	// calculation of 3He kinetic energies
	//////////////////////////////////////////////

	//clean measured
	fHeKinMeasured = measuredEdepX + measuredEdepY;

	//corrected for dead layers
	//	- between Si detectors
	//	- entrance of thin Si
	//	- target geometry

	//todo: think about entrance angle
	kinE = f3HeSi->GetE0(measuredEdepY, kDeadLayerBetweenSi);
	kinE = kinE + measuredEdepX;
	//todo: think about entrance angle
	kinE = f3HeSi->GetE0(kinE, kDeadLayerEntranceThin);

	//output angle of trajectory regarding the Z
	const Double_t angle = rtDirection.Theta();

	//	cout << angle*TMath::RadToDeg() << "\t" << TMath::Cos(angle)
	//	<< "\t" << kTargetThickness << "\t" << kTargetThickness/TMath::Cos(angle) << endl;

	kinE = f3HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	//	if (kinE<20.) cout << kinE << "\t";
	kinE = f3HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	//	if (kinE<20.) cout << kinE << endl;
	kinE = f3HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	fHeKinMeasuredCorrected = kinE;

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

	//todo: think about entrance angle
	//todo: think about thickness used for calculation
	//	kinE = f3HeSi->GetE0(measuredEdepY, kDeadLayerBetweenSi+kDeadLayerEntranceThin+kThinDetNormalizedThickness);
	//	kinE = f3HeSi->GetE0(measuredEdepY, kThinDetNormalizedThickness);
	kinE = f3HeSi->GetE0(measuredEdepY, hThickness->GetBinContent(mapXbin+1, mapYbin+1));
	//todo: !!!! solve the entrance angle for target
	kinE = f3HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	kinE = f3HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f3HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	fHeKinCalculated = kinE;

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry
	fHeKinCalculatedMap = 0.;

	//////////////////////////////////////////////
	// filling of 3He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;

	//clean measured
	momentum = GetP(fHeKinMeasured, kHeMass);

	fHeMomentumMeasured = rtDirection;
	fHeMomentumMeasured.SetMag(momentum);

	fHeMeasured.SetVectM(fHeMomentumMeasured, kHeMass);

	//corrected for dead layers
	//	- between Si detectors
	//	- entrance of thin Si
	//	- target geometry

	momentum = GetP(fHeKinMeasuredCorrected, kHeMass);

	fHeMomentumMeasuredCorrected = rtDirection;
	fHeMomentumMeasuredCorrected.SetMag(momentum);

	fHeMeasuredCorrected.SetVectM(fHeMomentumMeasuredCorrected, kHeMass);

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

	momentum = GetP(fHeKinCalculated, kHeMass);

	fHeMomentumCalculated = rtDirection;
	fHeMomentumCalculated.SetMag(momentum);

	fHeCalculated.SetVectM(fHeMomentumCalculated, kHeMass);

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

	//todo: write this

	//////////////////////////////////////////////
	// filling of 3He 4vectors in CMS of 7H
	//////////////////////////////////////////////
}

void Fill4VectorsAlphaRT() {

	if (v_RT20->GetEntriesFast() != 1 || v_RTY->GetEntriesFast() != 1) {
		return;
	}

	if (fXt < -40. || fYt < -40.) {
		return;
	}

	const Double_t kDeadLayerBetweenSi = 1.;			//in mcm
	const Double_t kDeadLayerEntranceThin = 0.5;			//in mcm
	//todo: check meaning of normalized thickness
	//	const Double_t kThinDetNormalizedThickness = 20.; 	//in mcm
	const Double_t kThinDetNormalizedThickness = 23.; 	//in mcm

	Double_t kinE = 0;

	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RTY->At(0))->GetEdep();
	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetEdep();

	//////////////////////////////////////////////
	// direction of particles registered in RT
	//////////////////////////////////////////////

	TVector3 rtDirection(fPointRT.X() - fXt, fPointRT.Y() - fYt, fPointRT.Z());
	rtDirection.Unit();

	//////////////////////////////////////////////
	// calculation of 3He kinetic energies
	//////////////////////////////////////////////

	//corrected for dead layers
	//	- between Si detectors
	//	- entrance of thin Si
	//	- target geometry

	//todo: think about entrance angle
	kinE = f4HeSi->GetE0(measuredEdepY, kDeadLayerBetweenSi);
	kinE = kinE + measuredEdepX;
	//todo: think about entrance angle
	kinE = f4HeSi->GetE0(kinE, kDeadLayerEntranceThin);

	//output angle of trajectory regarding the Z
	const Double_t angle = rtDirection.Theta();

	kinE = f4HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	//	if (kinE<20.) cout << kinE << "\t";
	kinE = f4HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	//	if (kinE<20.) cout << kinE << endl;
	kinE = f4HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	//////////////////////////////////////////////
	// filling of 4He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;
	momentum = GetP(kinE, k4HeMass);

	TVector3 f4HeMomentumMeasuredCorrected = rtDirection;
	f4HeMomentumMeasuredCorrected.SetMag(momentum);

//	fHeMeasuredCorrected;
	f4HeMeasuredCorrected.SetVectM(f4HeMomentumMeasuredCorrected, k4HeMass);

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

//	momentum = GetP(fHeKinCalculated, kHeMass);
//
//	fHeMomentumCalculated = rtDirection;
//	fHeMomentumCalculated.SetMag(momentum);
//
//	fHeCalculated.SetVectM(fHeMomentumCalculated, kHeMass);

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

}

void Fill4VectorsTritium() {

	if (v_CTSiX->GetEntriesFast() != 1 || v_CTSiY->GetEntriesFast() != 1) {
		return;
	}

	if (fXt < -40. || fYt < -40.) {
		return;
	}

	//////////////////////////////////////////////
	// direction of particles registered in RT
	//////////////////////////////////////////////

	fCentralDirection.SetXYZ(fPointCT.X() - fXt, fPointCT.Y() - fYt, fPointCT.Z());
	fCentralDirection.Unit();

	//////////////////////////////////////////////
	// angle between 3H and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB3HBeam = fCentralDirection.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// kinetic energy in LAB registered in CT
	//////////////////////////////////////////////
	Double_t kinE = 0;

	//energy deposit in X strip
	const Double_t measuredEdepSi = 1000*(Double_t)((ERQTelescopeSiDigi*)v_CTSiX->At(0))->GetEdep();

	//maximum energy in CsI
	Double_t maxEdepCsI = 0;

	for (Int_t i = 0; i < v_CTCsI->GetEntries(); i++) {
		Double_t measuredEdepCsI = (Double_t)((ERQTelescopeCsIDigi*)v_CTCsI->At(i))->GetEdep();
		//		cout << "\t" << measuredEdepCsI << endl;
		if (measuredEdepCsI > maxEdepCsI) maxEdepCsI = measuredEdepCsI;
	}
	//	cout << maxEdepCsI << "\t" << v_CTCsI->GetEntries() << endl;

	//uncorrected for dead layers in detectors
	kinE = measuredEdepSi + maxEdepCsI;

	const Double_t angle = fCentralDirection.Theta();

	kinE = f3HMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	kinE = f3HSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f3HTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	fTritiumKinMeasuredCorrected = kinE;

	//////////////////////////////////////////////
	// filling of 3He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;

	//clean measured
	momentum = GetP(fTritiumKinMeasuredCorrected, kTritiumMass);

	fTritiumMomentumMeasuredCorrected = fCentralDirection;
	fTritiumMomentumMeasuredCorrected.SetMag(momentum);

	fT.SetVectM(fTritiumMomentumMeasuredCorrected, kTritiumMass);

}

void Hydrogen7MissingMass() {

	if (v_CTSiX->GetEntriesFast() != 1 || v_CTSiY->GetEntriesFast() != 1) {

		//todo: very silly workaround:
		fHeFlag = 0;

		return;
	}

	if (fXt < -40. || fYt < -40.) {

		//todo: very silly workaround:
		fHeFlag = 0;

		return;
	}


	fHydrogenMeasured = fBeamTarget + fTarget - fHeMeasured;
	fHydrogenMeasuredCorrected = fBeamTarget + fTarget - fHeMeasuredCorrected;
	fHydrogenCalculated = fBeamTarget + fTarget - fHeCalculated;
	fHydrogenCalculatedMap = fBeamTarget + fTarget - fHeCalculatedMap;

	//////////////////////////////////////////////
	// filling of 7H 4vectors in CMS of 7H
	//////////////////////////////////////////////

	TVector3 beta;
	beta = fHydrogenMeasuredCorrected.BoostVector();
	fHydrogenMeasuredCorrectedCM = fHydrogenMeasuredCorrected;
	fHydrogenMeasuredCorrectedCM.Boost(-beta);

	beta = fHydrogenCalculated.BoostVector();
	fHydrogenCalculatedCM = fHydrogenCalculated;
	fHydrogenCalculatedCM.Boost(-beta);

	//////////////////////////////////////////////
	// filling of 3H 4vectors in CMS of 7H
	//////////////////////////////////////////////

	beta = fHydrogenMeasuredCorrected.BoostVector();
	fTMeasuredCorrectedCM = fT;
	fTMeasuredCorrectedCM.Boost(-beta);

	beta = fHydrogenCalculated.BoostVector();
	fTCalculatedCM = fT;
	fTCalculatedCM.Boost(-beta);

	//////////////////////////////////////////////
	// !!!!!!filling of 7H 4vectors in CMS of 7H
	// todo: something different
	//////////////////////////////////////////////

	fAngleLABhtMeasured = fHydrogenMeasured.Angle(fCentralDirection);
	if (fAngleLABhtMeasured*TMath::RadToDeg()*fAngleLABhtMeasured*TMath::RadToDeg() < 1.) {
		cout << fAngleLABhtMeasured*TMath::RadToDeg() << "\t"
				<< fHydrogenMeasured.Mag() - kTritiumMass - 4*939.565 << "\t"
				<< fHydrogenMeasured.Theta()*TMath::RadToDeg() << "\t"
				<< fCentralDirection.Theta()
				<< endl;
	}
	fAngleLABhtMeasuredCorrected = fHydrogenMeasuredCorrected.Angle(fCentralDirection);
	fAngleLABhtCalculated = fHydrogenCalculated.Angle(fCentralDirection);

	//////////////////////////////////////////////
	// angle between 7H and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB7hBeamMeasured = fHydrogenMeasured.Angle(fBeamMomentumTarget);
	if (fAngleLAB7hBeamMeasured*TMath::RadToDeg()*fAngleLAB7hBeamMeasured*TMath::RadToDeg() < 1.) {
		cout << fAngleLAB7hBeamMeasured*TMath::RadToDeg() << "\t"
				<< fHydrogenMeasured.Mag() - kTritiumMass - 4*939.565 << endl;
	}
	fAngleLAB7hBeamMeasuredCorrected = fHydrogenMeasuredCorrected.Angle(fBeamMomentumTarget);
	fAngleLAB7hBeamCalculated = fHydrogenCalculated.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// angle between 3He and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB3HeBeamMeasured = fHeMeasured.Angle(fBeamMomentumTarget);
	fAngleLAB3HeBeamMeasuredCorrected = fHeMeasuredCorrected.Angle(fBeamMomentumTarget);
	fAngleLAB3HeBeamCalculated = fHeCalculated.Angle(fBeamMomentumTarget);


}

void Hydrogen6MissingMass() {

	if (v_CTSiX->GetEntriesFast() != 1 || v_CTSiY->GetEntriesFast() != 1) {

		//todo: very silly workaround:
		f4HeFlag = 0;

		return;
	}

	if (fXt < -40. || fYt < -40.) {

		//todo: very silly workaround:
		f4HeFlag = 0;

		return;
	}

	fHydrogen6MeasuredCorrected = fBeamTarget + fTarget - f4HeMeasuredCorrected;

	//////////////////////////////////////////////
	// filling of 7H 4vectors in CMS of 7H
	//////////////////////////////////////////////

	const TVector3 beta = fHydrogen6MeasuredCorrected.BoostVector();
	fHydrogen6MeasuredCorrectedCM = fHydrogen6MeasuredCorrected;
	fHydrogen6MeasuredCorrectedCM.Boost(-beta);

	//////////////////////////////////////////////
	// filling of 3H 4vectors in CMS of 7H
	//////////////////////////////////////////////

	fTMeasuredCorrectedCM6H = fT;
	fTMeasuredCorrectedCM6H.Boost(-beta);

	//////////////////////////////////////////////
	// !!!!!!filling of 7H 4vectors in CMS of 7H
	// todo: something different
	//////////////////////////////////////////////

	fAngleLAB6HtMeasuredCorrected = fHydrogen6MeasuredCorrected.Angle(fCentralDirection);

	//////////////////////////////////////////////
	// angle between 7H and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB6HBeamMeasuredCorrected = fHydrogen6MeasuredCorrected.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// angle between 3He and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB4HeBeamMeasuredCorrected = f4HeMeasuredCorrected.Angle(fBeamMomentumTarget);


}

void FillHistThickness() {
	hThickness = new TH2F("hThicknessR", "Map of thickness for right 20 mcm detector", 16, 0., 16., 16, 0., 16.);

	Float_t thickR20[16][16] =
	{21.1, 21.1, 21.5, 21.9, 22.7, 22.7, 22.4, 21.5, 20.1, 19.1, 17.8, 17.0, 15.7, 15.5, 14.4, 14.4,
			21.1, 21.1, 21.5, 21.9, 22.7, 22.7, 22.4, 21.5, 20.1, 19.1, 17.8, 17.0, 15.7, 15.5, 14.4, 14.4,
			21.9, 21.9, 22.4, 23.1, 24.0, 23.7, 23.6, 22.7, 21.4, 20.1, 19.0, 18.0, 16.6, 16.4, 14.9, 14.4,
			21.9, 21.9, 22.6, 23.4, 24.1, 23.9, 23.7, 23.1, 21.9, 20.6, 19.2, 18.4, 16.8, 16.3, 14.5, 14.0,
			22.7, 22.7, 23.4, 24.6, 25.1, 25.1, 24.8, 24.4, 22.6, 21.7, 20.3, 19.7, 17.6, 16.7, 14.8, 14.1,
			22.4, 22.4, 23.5, 24.5, 25.2, 25.3, 25.3, 24.4, 22.5, 21.6, 20.9, 19.9, 18.0, 16.7, 14.7, 14.0,
			22.6, 22.6, 23.7, 24.8, 25.5, 25.3, 25.2, 24.5, 22.6, 21.9, 21.0, 20.1, 18.3, 17.2, 14.9, 14.3,
			21.9, 21.9, 23.2, 24.5, 25.3, 24.9, 24.6, 23.8, 22.3, 21.4, 20.4, 19.6, 18.0, 17.3, 14.6, 14.1,
			21.9, 21.9, 23.0, 24.6, 25.2, 25.1, 24.5, 23.9, 22.2, 21.2, 20.3, 19.6, 18.1, 17.4, 15.1, 14.4,
			21.9, 21.9, 23.0, 24.5, 25.5, 25.4, 25.3, 24.3, 22.5, 21.3, 20.0, 19.6, 18.2, 17.3, 15.3, 14.0,
			21.7, 21.7, 22.7, 23.9, 24.9, 25.1, 24.8, 24.0, 22.1, 21.0, 19.6, 19.4, 18.0, 17.3, 15.1, 14.4,
			21.7, 21.7, 22.7, 24.0, 25.0, 24.6, 24.5, 23.5, 21.9, 20.9, 19.8, 19.6, 18.3, 17.6, 15.8, 14.8,
			21.3, 21.3, 22.3, 23.4, 23.9, 23.7, 23.5, 22.6, 21.2, 20.4, 19.5, 19.3, 18.1, 17.6, 16.0, 15.1,
			21.2, 21.2, 22.2, 22.9, 23.4, 23.2, 22.8, 21.8, 20.4, 19.7, 19.1, 18.9, 18.1, 17.9, 16.4, 15.3,
			20.5, 20.5, 21.3, 21.7, 22.1, 21.6, 21.1, 20.4, 18.9, 18.3, 17.7, 17.7, 17.1, 17.5, 16.1, 15.1,
			20.5, 20.5, 21.3, 21.7, 22.0, 21.2, 20.6, 19.7, 18.5, 18.0, 17.4, 17.6, 17.1, 17.6, 16.4, 15.3};


	for (Int_t i = 0; i <= 15; i++) {
		for (Int_t j = 0; j <= 15; j++) {
			hThickness->SetBinContent(i+1, j+1, thickR20[15-i][j]);	//[X, Y]
		}
	}

	/*for (Int_t i = 0; i < 16; i++) {
		for (Int_t j = 0; j < 16; j++) {
			hThickness->SetBinContent(j+1, i+1, thickR20[i][j]);
		}
	}*/

	//	hThickness->Print();

	TCanvas *cH = new TCanvas("cH", "Map of thickness inhomogeneity", 1000, 1000);
	hThickness->Draw("col text");
	cH->Update();
}

void FillHistThicknessNew() {
	hThickness = new TH2F("hThicknessR", "Map of thickness for right 20 mcm detector", 16, 0., 16., 16, 0., 16.);

	Float_t thickR20[16][16] =
			// y0 --> y15 or y15 --> y0?
	{20.8, 21.1, 21.5, 21.8, 22.5, 22.5, 22.2, 21.5, 20.0, 19.0, 17.7, 17.0, 15.7, 15.5, 14.3, 14.0,	//x15
			20.8, 21.1, 21.5, 21.8, 22.5, 22.5, 22.2, 21.5, 20.0, 19.0, 17.7, 17.0, 15.7, 15.5, 14.3, 14.0,
			21.5, 21.9, 22.5, 23.0, 23.8, 23.7, 23.5, 22.9, 21.3, 20.1, 18.8, 18.0, 16.6, 16.4, 14.9, 14.2,
			21.5, 21.9, 22.6, 23.3, 24.1, 23.9, 23.9, 23.3, 21.7, 20.5, 19.3, 18.3, 16.9, 16.2, 14.5, 14.1,
			22.0, 22.6, 23.5, 24.3, 25.2, 25.1, 24.9, 24.3, 22.7, 21.5, 20.4, 19.7, 17.5, 16.6, 14.8, 14.3,
			22.0, 22.5, 23.3, 24.4, 25.2, 25.3, 25.1, 24.3, 22.6, 21.6, 20.9, 19.9, 17.9, 16.8, 14.6, 14.1,
			22.0, 22.5, 23.5, 24.6, 25.5, 25.5, 25.2, 24.4, 22.6, 21.9, 20.8, 20.1, 18.3, 17.2, 14.8, 14.3,
			21.5, 21.8, 23.0, 24.3, 25.2, 25.0, 24.5, 23.7, 22.4, 21.2, 20.3, 19.6, 18.0, 17.2, 14.7, 14.3,
			21.4, 21.7, 23.0, 24.3, 25.3, 25.0, 24.6, 23.9, 22.1, 21.2, 20.1, 19.4, 18.0, 17.3, 15.0, 14.4,
			21.1, 21.9, 23.0, 24.3, 25.4, 25.4, 25.3, 24.3, 22.5, 21.3, 20.1, 19.5, 18.1, 17.3, 15.2, 14.5,
			21.0, 21.5, 22.6, 23.7, 24.9, 25.0, 24.9, 24.0, 22.1, 21.0, 19.7, 19.3, 17.9, 17.2, 15.2, 14.5,
			21.0, 21.5, 22.6, 23.7, 24.9, 24.6, 24.5, 23.6, 21.9, 20.9, 19.8, 19.5, 18.2, 17.7, 15.9, 14.8,
			20.9, 21.3, 22.3, 23.2, 24.0, 23.7, 23.5, 22.7, 21.2, 20.3, 19.5, 19.3, 18.1, 17.7, 16.0, 14.8,
			20.9, 21.3, 22.2, 22.6, 23.4, 23.1, 22.6, 21.8, 20.3, 19.7, 19.0, 18.9, 18.0, 17.9, 16.3, 15.0,
			20.0, 20.5, 21.2, 21.7, 22.2, 21.6, 21.1, 20.2, 18.9, 18.4, 17.8, 17.7, 17.1, 17.4, 16.2, 15.5,		//x2
			20.0, 20.4, 21.2, 21.6, 21.9, 21.1, 20.7, 19.7, 18.5, 18.0, 17.4, 17.5, 17.1, 17.5, 16.5, 15.5};	//x1
	//		100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};					//x0






	for (Int_t i = 0; i <= 15; i++) {
		for (Int_t j = 0; j <= 15; j++) {
			hThickness->SetBinContent(i+1, j+1, thickR20[15-i][j]);
			if (i==0) {
				cout << 15-i << "\t" << thickR20[15-i][j] << endl;
			}
		}
	}

	hThickness->GetXaxis()->SetTitle("X strips");
	hThickness->GetYaxis()->SetTitle("Y strips");

	TCanvas *cH = new TCanvas("cH", "Map of thickness inhomogeneity", 1000, 1000);
	hThickness->Draw("col text");
	cH->Update();
}

void FillHistThicknessFromHist(TString infile) {
	//	hThickness = new TH2F("hThicknessR", "Map of thickness for right 20 mcm detector", 16, 0., 16., 16, 0., 16.);

	TFile *fileHist = TFile::Open(infile);
	TH2F *hTemp = (TH2F*)fileHist->Get("hTh");

	gROOT->cd();

	hThickness = new TH2F(*hTemp);

	hTemp = NULL;
	fileHist->Close();

	hThickness->SetNameTitle("hThicknessR", "Map of thickness for right 20 mcm detector");

	hThickness->GetXaxis()->SetTitle("X strips");
	hThickness->GetYaxis()->SetTitle("Y strips");

	//	TCanvas *cH = new TCanvas("cH", "Map of thickness inhomogeneity", 1000, 1000);
	//	hThickness->Draw("col text");
	//	cH->Update();
}

void SetTELossTables() {

	//parameters
	const Double_t kRhoSi = 2.329;
	const Double_t kRhoMylar = 1.39;
	const Double_t kRhoSteel = 8.0;
	const Double_t kSiZ = 14.;
	const Double_t kSiA = 28.086;

	//	const Double_t kRhoDeuterium = 0.00090841;	//obsolete
	const Double_t kRhoDeuterium = 0.0018431;	//according to Ivan
	const Double_t kDeuteriumZ = 1.;
	const Double_t kDeuteriumA = 2.0141017778;

	///////////////////
	// 3He
	///////////////////

	// Si
	f3HeSi = new TELoss();
	f3HeSi->SetEL(1, kRhoSi); // density in g/cm3
	f3HeSi->AddEL(kSiZ, kSiA, 1);  //Z, mass
	f3HeSi->SetZP(2., 3.);   //alphas, Z, A
	f3HeSi->SetEtab(100000, 200.); // ?, MeV calculate ranges

	// mylar
	f3HeMylar = new TELoss();
	f3HeMylar->SetEL(1, kRhoMylar); // density in g/cm3
	f3HeMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
	f3HeMylar->AddEL(1., 1.00784, 0.36);
	f3HeMylar->AddEL(8., 15.99903, 0.19);
	f3HeMylar->SetZP(2., 3.);   //alphas, Z, A
	f3HeMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges

	// steel
	f3HeSteel = new TELoss();
	f3HeSteel->SetEL(1, kRhoSteel); // density in g/cm3
	f3HeSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
	f3HeSteel->AddEL(26., 55.845, 0.74);
	f3HeSteel->AddEL(28., 58.6934, 0.19);
	f3HeSteel->SetZP(2., 3.);   //alphas, Z, A
	f3HeSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges

	// deuterium target
	f3HeTarget = new TELoss();
	f3HeTarget->SetEL(1, kRhoDeuterium); // density in g/cm3
	f3HeTarget->AddEL(kDeuteriumZ, kDeuteriumA, 1);  //Z, mass
	f3HeTarget->SetZP(2., 3.);   //alphas, Z, A
	f3HeTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges
	//--------------------------------------------------------------------------------


	///////////////////
	// 4He
	///////////////////

	// Si
	f4HeSi = new TELoss();
	f4HeSi->SetEL(1, kRhoSi); // density in g/cm3
	f4HeSi->AddEL(kSiZ, kSiA, 1);  //Z, mass
	f4HeSi->SetZP(2., 4.);   //alphas, Z, A
	f4HeSi->SetEtab(100000, 200.); // ?, MeV calculate ranges

	// mylar
	f4HeMylar = new TELoss();
	f4HeMylar->SetEL(1, kRhoMylar); // density in g/cm3
	f4HeMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
	f4HeMylar->AddEL(1., 1.00784, 0.36);
	f4HeMylar->AddEL(8., 15.99903, 0.19);
	f4HeMylar->SetZP(2., 4.);   //alphas, Z, A
	f4HeMylar->SetEtab(100000, 200.); // ?, MeV calculate ranges

	// steel
	f4HeSteel = new TELoss();
	f4HeSteel->SetEL(1, kRhoSteel); // density in g/cm3
	f4HeSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
	f4HeSteel->AddEL(26., 55.845, 0.74);
	f4HeSteel->AddEL(28., 58.6934, 0.19);
	f4HeSteel->SetZP(2., 4.);   //alphas, Z, A
	f4HeSteel->SetEtab(100000, 200.); // ?, MeV calculate ranges

	// deuterium target
	f4HeTarget = new TELoss();
	f4HeTarget->SetEL(1, kRhoDeuterium); // density in g/cm3
	f4HeTarget->AddEL(kDeuteriumZ, kDeuteriumA, 1);  //Z, mass
	f4HeTarget->SetZP(2., 4.);   //alphas, Z, A
	f4HeTarget->SetEtab(100000, 200.); // ?, MeV calculate ranges

	///////////////////
	// 3H
	///////////////////
	// Si
	f3HSi = new TELoss();
	f3HSi->SetEL(1, kRhoSi); // density in g/cm3
	f3HSi->AddEL(14., 28.086, 1);  //Z, mass
	f3HSi->SetZP(1., 3.);   //alphas, Z, A
	f3HSi->SetEtab(150000, 150.); // ?, MeV calculate ranges

	// mylar
	f3HMylar = new TELoss();
	f3HMylar->SetEL(1, kRhoMylar); // density in g/cm3
	f3HMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
	f3HMylar->AddEL(1., 1.00784, 0.36);
	f3HMylar->AddEL(8., 15.99903, 0.19);
	f3HMylar->SetZP(1., 3.);   //alphas, Z, A
	f3HMylar->SetEtab(150000, 150.); // ?, MeV calculate ranges

	// steel
	f3HSteel = new TELoss();
	f3HSteel->SetEL(1, kRhoSteel); // density in g/cm3
	f3HSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
	f3HSteel->AddEL(26., 55.845, 0.74);
	f3HSteel->AddEL(28., 58.6934, 0.19);
	f3HSteel->SetZP(1., 3.);   //alphas, Z, A
	f3HSteel->SetEtab(150000, 150.); // ?, MeV calculate ranges

	// deuterium target
	f3HTarget = new TELoss();
	f3HTarget->SetEL(1, 0.00090841); // density in g/cm3
	f3HTarget->AddEL(1., 2.0141017778, 1);  //Z, mass
	f3HTarget->SetZP(1., 3.);   //alphas, Z, A
	f3HTarget->SetEtab(150000, 150.); // ?, MeV calculate ranges

	///////////////////
	// 8He beam
	///////////////////
	// Si
	f8HeSi = new TELoss();
	f8HeSi->SetEL(1, kRhoSi); // density in g/cm3
	f8HeSi->AddEL(kSiZ, kSiA, 1);  //Z, mass
	f8HeSi->SetZP(2., 8.);   //alphas, Z, A
	f8HeSi->SetEtab(150000, 300.); // ?, MeV calculate ranges

	// mylar
	f8HeMylar = new TELoss();
	f8HeMylar->SetEL(1, kRhoMylar); // density in g/cm3
	f8HeMylar->AddEL(6., 12.0096, 0.45);  //Z, mass
	f8HeMylar->AddEL(1., 1.00784, 0.36);
	f8HeMylar->AddEL(8., 15.99903, 0.19);
	f8HeMylar->SetZP(2., 8.);   //alphas, Z, A
	f8HeMylar->SetEtab(150000, 300.); // ?, MeV calculate ranges

	// steel
	f8HeSteel = new TELoss();
	f8HeSteel->SetEL(1, kRhoSteel); // density in g/cm3
	f8HeSteel->AddEL(24., 51.9962, 0.07);  //Z, mass
	f8HeSteel->AddEL(26., 55.845, 0.74);
	f8HeSteel->AddEL(28., 58.6934, 0.19);
	f8HeSteel->SetZP(2., 8.);   //alphas, Z, A
	f8HeSteel->SetEtab(150000, 300.); // ?, MeV calculate ranges

	// deuterium
	f8HeDeuterium = new TELoss();
	f8HeDeuterium->SetEL(1, kRhoDeuterium); // density in g/cm3
	f8HeDeuterium->AddEL(kDeuteriumZ, kDeuteriumA, 1);  //Z, mass
	f8HeDeuterium->SetZP(2., 8.);   //Z, A
	f8HeDeuterium->SetEtab(150000, 300.); // ?, MeV calculate ranges
}

void recoRightTelescope(const Int_t run = 10, const Int_t from = 1, const Int_t to = 24,
		const Int_t noevents = 0, const Bool_t background = 0) {

	TStopwatch stopwatch;
	stopwatch.Start();

	//	FillHistThickness();
	//	FillHistThicknessNew();


	//todo: change the thickness file
	//	TString thicknessFile = "parameters/thicknessRight.root";
	TString thicknessFile = "parameters/thicknessRight_new.root";

	FillHistThicknessFromHist(thicknessFile);

	//	return;

	//	cout << "\t" << background << endl;

	for (Int_t i = from; i <= to; i++) {
		recoFile(run, i, noevents, background);
		Info("recoRightTelescope", "File processing finished in %f seconds", stopwatch.RealTime());
		stopwatch.Continue();
		//		stopwatch.
		cout << endl << endl;
	}

	cout << "Finished in "<< stopwatch.RealTime() << " seconds" << endl;
	cout << "Finished in "<< stopwatch.RealTime()/60. << " minutes" << endl;
}

void recoRightTelescopeAllData() {

	TStopwatch stopwatch;
	stopwatch.Start();

	//	FillHistThickness();
	//	FillHistThicknessNew();

//	//	TString inPath = "~/data/exp1811/analysed/";
//	TString inPath = "~/data/exp1811/calibrated/";
//	//	TString outPath = "~/data/exp1811/analysed/recoFiltered/";
//	TString outPath = "~/data/exp1811/calibrated/reco/";
//	inPath = "~/data/exp1811/calibrated_filtered/";
//	outPath = "~/data/exp1811/calibrated_filtered/reco/";
	inPath = "~/data/exp1811/calibrated_filtered_CsI/";
//	outPath = "~/data/exp1811/calibrated_filtered_CsI/reco/";
//	outPath = "~/data/exp1811/calibrated_filtered_CsI/reco_false3He/";
	outPath = "~/data/exp1811/calibrated_filtered_CsI/reco_6H/";

	Int_t from = 7;
	Int_t to = 22;

	Int_t filesInRun[23] = {0, 0, 0, 0, 0, 0, 0,
			22, 2, 4, 24, 14, 4,
			2, 20, 12, 8, 7, 10,
			1, 14, 1, 6
	};

	for (Int_t i = from; i <= to; i++) {
		recoRightTelescope(i, 1, filesInRun[i]);
		Info("recoRightTelescopeAllData", "Run %d processed in %f seconds.", i, stopwatch.RealTime());
		stopwatch.Continue();
		cout << endl << endl;
	}

	cout << "Finished in "<< stopwatch.RealTime() << " seconds" << endl;
	cout << "Finished in "<< stopwatch.RealTime()/60. << " minutes" << endl;
}

void recoRightTelescopeAllDataBackground() {

	TStopwatch stopwatch;
	stopwatch.Start();

	//	FillHistThickness();
	//	FillHistThicknessNew();

	//	inPath = "~/data/exp1811/calibrated_filtered/background_filtered/";
	//	outPath = "~/data/exp1811/calibrated_filtered/background_filtered/reco/";
	inPath = "~/data/exp1811/calibrated_filtered_CsI/background/";
	outPath = "~/data/exp1811/calibrated_filtered_CsI/background/reco/";

	//runs
	Int_t from = 24;
	Int_t to = 31;

	Int_t filesInRun[32] = {0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 1,	//19-24
			1, 4, 8, 1, 18, 5,	//25-30
			1					//31
	};

	for (Int_t i = from; i <= to; i++) {
		recoRightTelescope(i, 1, filesInRun[i], 0, 1);
		Info("recoRightTelescopeAllData", "Run %d processed in %f seconds.", i, stopwatch.RealTime());
		stopwatch.Continue();
		cout << endl << endl;
	}

	cout << "Finished in "<< stopwatch.RealTime() << " seconds" << endl;
	cout << "Finished in "<< stopwatch.RealTime()/60. << " minutes" << endl;
}
