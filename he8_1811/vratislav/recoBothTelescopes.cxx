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

//LT cuts
#include "cutsLTY.cxx"
#include "cutsLT20X.cxx"
#include "cutsLTHelium3.cxx"
#include "cutsLTHelium4.cxx"

//CT cuts
//#include "cutsTritium.cxx"
#include "cutsTritiumCal.cxx"
#include "cutsCsIcal.cxx"

///////////////////////////
//data members to read
///////////////////////////

//right telescope
TClonesArray *v_RTY;
TClonesArray *v_RT20;
TClonesArray *v_RTveto;

//right telescope
TClonesArray *v_LTY;
TClonesArray *v_LTX;
TClonesArray *v_LT20;
TClonesArray *v_LTveto;

//central telescope
TClonesArray *v_CTSiX;
TClonesArray *v_CTSiY;
TClonesArray *v_CTCsI;

//ToF
TClonesArray *v_BD_F3;
TClonesArray *v_BD_F5;


void InitExternalCuts();
void Reset();
void MWPCprojection(TClonesArray *dataX1, TClonesArray *dataY1, TClonesArray *dataX2, TClonesArray *dataY2);

Int_t GetClusterMult(TClonesArray *data);
Float_t GetClusterWire(TClonesArray *data);
Float_t GetPosition(Float_t wire, Float_t wireStep, Float_t planeOffset);

void RT20EdepCorrection();
void LT20EdepCorrection();
void PositionInRT();
void PositionInLT();

void PositionInCT();

void Fill4VectorsReactionInput();

void Fill4VectorsHeRT();
void Fill4VectorsAlphaRT();

void Fill4VectorsHeLT();
void Fill4VectorsAlphaLT();

void Fill4VectorsTritium();

Bool_t FlagHeRT();
Bool_t FlagHeLT();
Bool_t Flag4HeRT();
Bool_t Flag4HeLT();
Bool_t FlagTritium();

void Hydrogen7MissingMass();
void Hydrogen6MissingMass();

//void FillHistThickness();
void SetTELossTables();

//void recoBothTelescopesAllData();

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
Float_t fRTMeasuredEdep;

//left telescope
Double_t fLT20EdepCorrected;
Int_t fLT20StripNbCorrected;
Double_t fLTMeasuredEdep;

Float_t fYrtLocal;
Float_t fXrtLocal;

Float_t fYltLocal;
Float_t fXltLocal;

TVector3 fXpointRT1;	//in first layer, Y=0
TVector3 fYpointRT2;	//in second layer, X=0
TVector3 fPointRT;

TVector3 fXpointLT1;	//in first layer, Y=0
TVector3 fYpointLT2;	//in second layer, X=0
TVector3 fPointLT;

Double_t fAngleBeam3He;

Double_t fHeKinMeasuredCorrected;

TVector3 fHeMomentumMeasuredCorrected;

Double_t fAngleLABhtMeasuredCorrected;

Double_t fAngleCMof7HhtMeasuredCorrected;

Double_t fAngleLAB7hBeamMeasuredCorrected;

Double_t fAngleLAB3HeBeamMeasuredCorrected;

//6H
Double_t fAngleLAB6HtMeasuredCorrected;
Double_t fAngleLAB6HBeamMeasuredCorrected;
Double_t fAngleLAB4HeBeamMeasuredCorrected;

Bool_t fHeFlagRT;
Bool_t fHeFlagLT;

Bool_t f4HeFlagRT;
Bool_t f4HeFlagLT;
Bool_t fTFlag;

//central telescope
TVector3 fPointCT;

TVector3 fCentralDirection;
Double_t fAngleLAB3HBeam;
TVector3 fTritiumMomentumMeasuredCorrected;
TVector3 fDeuteriumMomentumMeasuredCorrected;

//particles
TLorentzVector fHeMeasuredCorrected;
TLorentzVector f3HeMeasuredCorrectedCMreaction;

TLorentzVector f4HeMeasuredCorrected;
TLorentzVector f4HeMeasuredCorrectedCMreaction;

TLorentzVector fT;
TLorentzVector fD;
TLorentzVector fTMeasuredCorrectedCM;
TLorentzVector fDMeasuredCorrectedCM;
TLorentzVector fTMeasuredCorrectedCM6H;
TLorentzVector fDMeasuredCorrectedCM6H;
TLorentzVector fBeamToF;
TLorentzVector fBeamTarget;
TLorentzVector fTarget;

//7H
TLorentzVector fHydrogenMeasuredCorrected;
TLorentzVector fHydrogenMeasuredCorrectedCM;
TLorentzVector fHydrogenMeasuredCorrectedCMreaction;

//6H
TLorentzVector fHydrogen6MeasuredCorrected;
TLorentzVector fHydrogen6MeasuredCorrectedCM;
TLorentzVector fHydrogen6MeasuredCorrectedCMreaction;

//////////////////////////////////////////////
// parameters and tools used for analysis
//////////////////////////////////////////////

TH2F *hThicknessR;
TH2F *hThicknessL;

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
//right telescope
const Float_t k1mmDistR = 180.;			//in mm, this is used as the local frame
const Float_t kThinDistR = 180.-12.5;	//in mm
const Float_t kSQR_Y_size = 60.;	//in mm
const Int_t kSQR_Y_strips = -16;
const Int_t kSQR_X_strips = -16;
const Float_t kSQR20_X_size = 50.;	//in mm
const Float_t kSQR20_Y_size = 50.;	//in mm

const Double_t kSQR20_Xoffset = -2.5;	//in mm
//todo: check this offset
const Double_t kSQR20_Yoffset = 0.;		//in mm
const Double_t kSQR_angle = -17.;		//in deg

//left telescope
const Float_t k1mmDistL = 180.;			//in mm, this is used as the local frame
const Float_t kThinDistL = 180.-12.5;	//in mm
const Float_t kSQL_Y_size = 60.;	//in mm
const Int_t kSQL_Y_strips = 16;
const Int_t kSQL_X_strips = -16;
const Float_t kSQL20_X_size = 50.;	//in mm
const Float_t kSQL20_Y_size = 50.;	//in mm
//
const Double_t kSQL20_Xoffset = 2.5;	//in mm
////todo: check this offset
//const Double_t kSQL20_Yoffset = 0.;		//in mm
const Double_t kSQL_angle = 17.;		//in deg

//todo: change other constants to Double_t because of the work with TVector3
//central telescope
const Double_t kCentralSiDist = 280.;
const Int_t kSQC_X_strips = -32;	//direction checked
const Int_t kSQC_Y_strips = -32;	//direction checked
const Double_t kSQC_X_size = 60.;
const Double_t kSQC_Y_size = 60.;

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

	if (background) {
		inFile.Form("he8_empty_target_%02d_00%02d.Digi.root", noRun, noFile);
		outFile.Form("he8_empty_target_%02d_%04d.reco.root", noRun, noFile);
	}

	Info("recoFile", "Processing file %s%s", inPath.Data(), inFile.Data());
	Info("recoFile", "Results will be stored in %s%s", outPath.Data(), outFile.Data());


	//////////////////////////
	//Input file
	//////////////////////////
	TFile *fr = new TFile(inPath + inFile);
	if (fr->IsZombie()) {
		Error("recoFile", "File %s%s was not open.", inPath.Data(), inFile.Data());
		return;
	}
	TTree *tr = (TTree*)fr->Get("er");
	cout << "Found " << tr->GetEntries() << " entries" << endl;

	ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();

	TClonesArray *v_MWPCx1 = new TClonesArray("ERBeamDetMWPCDigi");
	TClonesArray *v_MWPCy1 = new TClonesArray("ERBeamDetMWPCDigi");
	TClonesArray *v_MWPCx2 = new TClonesArray("ERBeamDetMWPCDigi");
	TClonesArray *v_MWPCy2 = new TClonesArray("ERBeamDetMWPCDigi");

	v_RTY = new TClonesArray("ERQTelescopeSiDigi");
	v_RT20 = new TClonesArray("ERQTelescopeSiDigi");
	v_RTveto = new TClonesArray("ERQTelescopeSiDigi");

	v_LTY = new TClonesArray("ERQTelescopeSiDigi");
	v_LT20 = new TClonesArray("ERQTelescopeSiDigi");
	v_LTveto = new TClonesArray("ERQTelescopeSiDigi");

	v_CTSiX = new TClonesArray("ERQTelescopeSiDigi");
	v_CTSiY = new TClonesArray("ERQTelescopeSiDigi");
	v_CTCsI = new TClonesArray("ERQTelescopeCsIDigi");

	v_BD_F3 = new TClonesArray("ERBeamDetTOFDigi");
	v_BD_F5 = new TClonesArray("ERBeamDetTOFDigi");

	tr->SetBranchAddress("EventHeader.",&header);

	tr->SetBranchAddress("BeamDetMWPCDigiX1",&v_MWPCx1);
	tr->SetBranchAddress("BeamDetMWPCDigiX2",&v_MWPCx2);
	tr->SetBranchAddress("BeamDetMWPCDigiY1",&v_MWPCy1);
	tr->SetBranchAddress("BeamDetMWPCDigiY2",&v_MWPCy2);

	tr->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0",&v_RTY);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD20_R_X_0",&v_RT20);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_SingleSi_SSD_R_Y_0",&v_RTveto);

	tr->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_Y",&v_LTY);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD20_L_X_0",&v_LT20);
	tr->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SSD_L_X_0",&v_LTveto);

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
	tw->Branch("fRTMeasuredEdep",&fRTMeasuredEdep,"fRTMeasuredEdep/F");
	tw->Branch("fRTEdepCorr",&fRT20EdepCorrected,"fRT20EdepCorrected/F");
	tw->Branch("fRTEStripCorr",&fRT20StripNbCorrected,"fRT20StripNbCorrected/I");

	//left telescope
	tw->Branch("fLTMeasuredEdep",&fLTMeasuredEdep,"fLTMeasuredEdep/D");
	tw->Branch("fLT20EdepCorrected",&fLT20EdepCorrected,"fLT20EdepCorrected/D");
	tw->Branch("fLT20StripNbCorrected",&fLT20StripNbCorrected,"fLT20StripNbCorrected/I");

	tw->Branch("fYrtLocal", &fYrtLocal, "fYrtLocal/F");
	tw->Branch("fXrtLocal", &fXrtLocal, "fXrtLocal/F");

	tw->Branch("fYltLocal", &fYltLocal, "fYltLocal/F");
	tw->Branch("fXltLocal", &fXltLocal, "fXltLocal/F");

	tw->Branch("fXpointRT1", "TVector3", &fXpointRT1);
	tw->Branch("fYpointRT2", "TVector3", &fYpointRT2);
	tw->Branch("fPointRT", "TVector3", &fPointRT);

	tw->Branch("fXpointLT1", "TVector3", &fXpointLT1);
	tw->Branch("fYpointLT2", "TVector3", &fYpointLT2);
	tw->Branch("fPointLT", "TVector3", &fPointLT);
	tw->Branch("fAngleBeam3He",&fAngleBeam3He,"fAngleBeam3He/D");

	//helium-3
	tw->Branch("fHeKinMeasuredCorrected",&fHeKinMeasuredCorrected,"fHeKinMeasuredCorrected/D");

	//central telescope
	tw->Branch("fPointCT", "TVector3", &fPointCT);
	tw->Branch("fCentralDirection", "TVector3", &fCentralDirection);
	tw->Branch("fAngleLAB3HBeam",&fAngleLAB3HBeam,"fAngleLAB3HBeam/D");

	//particles:
	tw->Branch("fHeMeasuredCorrected", "TLorentzVector", &fHeMeasuredCorrected);
	tw->Branch("f3HeMeasuredCorrectedCMreaction", "TLorentzVector", &f3HeMeasuredCorrectedCMreaction);

	tw->Branch("f4HeMeasuredCorrected", "TLorentzVector", &f4HeMeasuredCorrected);
	tw->Branch("f4HeMeasuredCorrectedCMreaction", "TLorentzVector", &f4HeMeasuredCorrectedCMreaction);

	//angles:
	tw->Branch("fAngleLABhtMeasuredCorrected",&fAngleLABhtMeasuredCorrected,"fAngleLABhtMeasuredCorrected/D");

	tw->Branch("fAngleCMof7HhtMeasuredCorrected",&fAngleCMof7HhtMeasuredCorrected,"fAngleCMof7HhtMeasuredCorrected/D");


	tw->Branch("fAngleLAB7hBeamMeasuredCorrected",&fAngleLAB7hBeamMeasuredCorrected,"fAngleLAB7hBeamMeasuredCorrected/D");

	tw->Branch("fAngleLAB3HeBeamMeasuredCorrected",&fAngleLAB3HeBeamMeasuredCorrected,"fAngleLAB3HeBeamMeasuredCorrected/D");

	//6H
	tw->Branch("fAngleLAB6HBeamMeasuredCorrected",&fAngleLAB6HBeamMeasuredCorrected,"fAngleLAB6HBeamMeasuredCorrected/D");
//	tw->Branch("fAngleLAB7hBeamMeasuredCorrected",&fAngleLAB6hBeamMeasuredCorrected,"fAngleLAB7hBeamMeasuredCorrected/D");
	tw->Branch("fAngleLAB4HeBeamMeasuredCorrected",&fAngleLAB4HeBeamMeasuredCorrected,"fAngleLAB4HeBeamMeasuredCorrected/D");

	//tritium
	tw->Branch("fT", "TLorentzVector", &fT);
	tw->Branch("fTMeasuredCorrectedCM", "TLorentzVector", &fTMeasuredCorrectedCM);
	tw->Branch("fTMeasuredCorrectedCM6H", "TLorentzVector", &fTMeasuredCorrectedCM6H);

	//deuterium
	tw->Branch("fD", "TLorentzVector", &fD);
	tw->Branch("fDMeasuredCorrectedCM6H", "TLorentzVector", &fDMeasuredCorrectedCM6H);
	tw->Branch("fDMeasuredCorrectedCM", "TLorentzVector", &fDMeasuredCorrectedCM);

	//beam
	tw->Branch("fBeamToF", "TLorentzVector", &fBeamToF);
	tw->Branch("fBeamTarget", "TLorentzVector", &fBeamTarget);
	tw->Branch("fTarget", "TLorentzVector", &fTarget);

	//7H
	tw->Branch("fHydrogenMeasuredCorrected", "TLorentzVector", &fHydrogenMeasuredCorrected);
	tw->Branch("fHydrogenMeasuredCorrectedCM", "TLorentzVector", &fHydrogenMeasuredCorrectedCM);
	tw->Branch("fHydrogenMeasuredCorrectedCMreaction", "TLorentzVector", &fHydrogenMeasuredCorrectedCMreaction);

	//6H
	tw->Branch("fHydrogen6MeasuredCorrected", "TLorentzVector", &fHydrogen6MeasuredCorrected);
	tw->Branch("fHydrogen6MeasuredCorrectedCM", "TLorentzVector", &fHydrogen6MeasuredCorrectedCM);
	tw->Branch("fHydrogen6MeasuredCorrectedCMreaction", "TLorentzVector", &fHydrogen6MeasuredCorrectedCMreaction);

	//flags
	tw->Branch("fHeFlagRT",&fHeFlagRT,"fHeFlagRT/O");
	tw->Branch("fHeFlagLT",&fHeFlagLT,"fHeFlagLT/O");
	tw->Branch("f4HeFlagRT",&f4HeFlagRT,"f4HeFlagRT/O");
	tw->Branch("f4HeFlagLT",&f4HeFlagLT,"f4HeFlagLT/O");
	tw->Branch("fTFlag",&fTFlag,"fTFlag/O");

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

		//beam
		MWPCprojection(v_MWPCx1, v_MWPCy1, v_MWPCx2, v_MWPCy2);
		Fill4VectorsReactionInput();

		//central telescope
		PositionInCT();
		Fill4VectorsTritium();

		//right telescope
		RT20EdepCorrection();
		PositionInRT();
		Fill4VectorsHeRT();
		Fill4VectorsAlphaRT();

		//left telescope
		LT20EdepCorrection();
		PositionInLT();
		Fill4VectorsHeLT();
		Fill4VectorsAlphaLT();

		//flags
		fHeFlagRT = FlagHeRT();
		f4HeFlagRT = Flag4HeRT();

		fHeFlagLT = FlagHeLT();
		f4HeFlagLT = Flag4HeLT();

		fTFlag = FlagTritium();

		//missing mass
		if (fHeFlagRT || fHeFlagLT) {
			Hydrogen7MissingMass();
		}

		if (f4HeFlagRT || f4HeFlagLT) {
			Hydrogen6MissingMass();
//			Hydrogen6MissingMassFromD();
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
		cutsLT20X();
	}

	if (useSecondLayerCuts) {
		cutsRTY();
		cutsLTY();
	}

	if (useHeliumCuts) {
		cutsHelium3();
		cutsLTHelium3();
	}

	if (useAlphaCuts) {
		cutsHelium4();
		cutsLTHelium4();
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
	fRTMeasuredEdep = 0.;

	fLT20EdepCorrected = 0.;
	fLT20StripNbCorrected = -1;
	fLTMeasuredEdep = 0.;

	fYrtLocal = -100.;
	fXrtLocal = -100.;

	fYltLocal = -100.;
	fXltLocal = -100.;

	fPointTarget.SetXYZ(0., 0., -50.);
	fBeamDirection.SetXYZ(0., 0., 0.);
	fBeamMomentumToF.SetXYZ(0., 0., 0.);
	fBeamMomentumTarget.SetXYZ(0., 0., 0.);

	fXpointRT1.SetXYZ(0., 0., 0.);
	fYpointRT2.SetXYZ(0., 0., 0.);
	fPointRT.SetXYZ(0., 0., 0.);

	fXpointLT1.SetXYZ(0., 0., 0.);
	fYpointLT2.SetXYZ(0., 0., 0.);
	fPointLT.SetXYZ(0., 0., 0.);
	fAngleBeam3He = TMath::Pi();

	fHeKinMeasuredCorrected = 0.;

	fPointCT.SetXYZ(0., 0., 0.);
	fCentralDirection.SetXYZ(0., 0., 0.);
	fAngleLAB3HBeam = TMath::Pi();

	fHeMeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);
	f3HeMeasuredCorrectedCMreaction.SetPxPyPzE(0., 0., 0., 0.);

	f4HeMeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);
	f4HeMeasuredCorrectedCMreaction.SetPxPyPzE(0., 0., 0., 0.);

	fAngleLABhtMeasuredCorrected = 0.;

	fAngleCMof7HhtMeasuredCorrected = 0.;

	fAngleLAB7hBeamMeasuredCorrected = 0.;

	fAngleLAB3HeBeamMeasuredCorrected = 0.;

	//6H
	fAngleLAB6HBeamMeasuredCorrected = 0.;
	fAngleLAB4HeBeamMeasuredCorrected = 0.;

	//tritium
	fT.SetPxPyPzE(0., 0., 0., 0.);
	fTMeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);
	fTMeasuredCorrectedCM6H.SetPxPyPzE(0., 0., 0., 0.);

	//deuterium
	fD.SetPxPyPzE(0., 0., 0., 0.);
	fDMeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);
	fDMeasuredCorrectedCM6H.SetPxPyPzE(0., 0., 0., 0.);

	fBeamToF.SetPxPyPzE(0., 0., 0., 0.);
	fBeamTarget.SetPxPyPzE(0., 0., 0., 0.);
	fTarget.SetPxPyPzE(0., 0., 0., 0.);

	fHydrogenMeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogenMeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogenMeasuredCorrectedCMreaction.SetPxPyPzE(0., 0., 0., 0.);


	fHydrogen6MeasuredCorrected.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogen6MeasuredCorrectedCM.SetPxPyPzE(0., 0., 0., 0.);
	fHydrogen6MeasuredCorrectedCMreaction.SetPxPyPzE(0., 0., 0., 0.);

	fHeFlagRT = 0;
	fHeFlagLT = 0;
	f4HeFlagRT = 0;
	f4HeFlagLT = 0;
	fTFlag = 0;

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

void RT20EdepCorrection() {

	if (trigger!=3) {
		return;
	}

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

	y20mcm = (y1mm-fYt)*kThinDistR/k1mmDistR;
	y20mcm = y20mcm+fYt;
	//	vHit20mcm.SetXYZ(x20mcm, y20mcm, zThin);
	//	angleRight = vHit20mcm.Angle(vNorm);


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
		currThickness = hThicknessR->GetBinContent(mapXbin+1, mapYbin+1);		//1 the best effect at c8

		fRTMeasuredEdep = (Double_t)((ERQTelescopeSiDigi*)v_RT20->At(0))->GetEdep();
		fRT20EdepCorrected = (kSQ20_norm_thickness/currThickness)*fRTMeasuredEdep;
		fRT20StripNbCorrected = xStrip;

	}//if inside the map

	return;
}

void LT20EdepCorrection() {

	if (trigger!=2) {
		return;
	}

	if (v_LT20->GetEntriesFast() != 1 || v_LTY->GetEntriesFast() != 1) {
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
	TVector3 vNorm(0.,0.,1.);
	Double_t angleRight;

	//todo: offset is not used in this function

	//	Int_t mapYbin, mapXbin;
	Double_t currThickness;

	//signum strips
	Int_t signXstrips = (kSQL_X_strips>0) - (kSQL_X_strips<0);
	Int_t signYstrips = (kSQL_Y_strips>0) - (kSQL_Y_strips<0);


	Int_t xStrip = ((ERQTelescopeSiDigi*)v_LT20->At(0))->GetStripNb();
	Int_t yStrip = ((ERQTelescopeSiDigi*)v_LTY->At(0))->GetStripNb();

	//todo: try to investigate 20 mcm offset
	y1mm = ( yStrip + 0.5 )*kSQL_Y_size/kSQL_Y_strips - signYstrips*kSQL_Y_size/2.;	//ok
	x20mcm = ( xStrip + 0.5 )*kSQL20_X_size/kSQL_X_strips - signXstrips*kSQL20_X_size/2.;	//ok


	//	TMath::Sign()
	//vHit1mm conversion to plane of thin detector
	//	y20mcm = y1mm*zThin/z1mm;
	//	vHit20mcm.SetXYZ(x20mcm-fXt, y20mcm-fYt, zThin);
	//	angleRight = vHit20mcm.Angle(vNorm);

	y20mcm = (y1mm-fYt)*kThinDistL/k1mmDistL;
	y20mcm = y20mcm+fYt;
	//	vHit20mcm.SetXYZ(x20mcm, y20mcm, zThin);
	//	angleRight = vHit20mcm.Angle(vNorm);


	//check if the particle passed through sensitive area of thin detector
	if ( y20mcm < (kSQL20_Y_size/2.) && y20mcm > (-kSQL20_Y_size/2.) ) {
		//		x20mcm = vHit20mcm.X()+fXt;
		//		y20mcm = vHit20mcm.Y()+fYt;

		//todo: this statement was changed
		mapYbin = y20mcm*kSQL_Y_strips/kSQL_Y_size + signYstrips*kSQL_Y_strips/2.;	//ok
		//		mapXbin = x20mcm*kSQL_20_strips/kSQ20_X_size - kSQL_20_strips/2.;	//ok
		mapXbin = xStrip;	//ok
		//		mapYbin = yStrip;



		//calculation of corrected energy
		//TODO: check the mapping here at second
		currThickness = hThicknessL->GetBinContent(mapXbin+1, mapYbin+1);		//1 the best effect at c8
//		cout << y1mm << "\t" << mapYbin << "\t" << yStrip
//				<< currThickness << "\t" << kSQ20_norm_thickness
//				<< endl;

		fLTMeasuredEdep = (Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetEdep();
		fLT20EdepCorrected = (kSQ20_norm_thickness/currThickness)*fLTMeasuredEdep;
		fLT20StripNbCorrected = xStrip;

//		cout << y1mm << "\t" << mapYbin << "\t" << yStrip << "\t"
//				<< currThickness << "\t" << kSQ20_norm_thickness << "\t"
//				<< fLTMeasuredEdep << "\t" << fLT20EdepCorrected << "\t"
//				<< endl;
//		cout << fLTMeasuredEdep << "\t" << fLT20EdepCorrected << endl;

	}//if inside the map

	return;
}

void PositionInRT() {

	if (trigger!=3) {
		return;
	}

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

	fYpointRT2.SetXYZ(0., y1mm, k1mmDistR);
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
	fXpointRT1.SetXYZ(x20mcm, 0., kThinDistR);
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
	Double_t trackBetweenLayersDistance = (Double_t)(k1mmDistR - kThinDistR)/TMath::Cos(beta);
	//	Double_t trackBetweenLayersDistance = (Double_t)(k1mmDist - kThinDist)/TMath::Cos(kSQR_angle)/TMath::Cos(beta);
	Double_t shiftedMag = vAux.Mag();
	vAux.SetMag(shiftedMag + trackBetweenLayersDistance);

	// 4)
	fPointRT.SetXYZ(vAux.X() + fXt, fYpointRT2.Y(), vAux.Z());

	//asign calculated variables to tree branches:
	fYrtLocal = y1mm;
	fXrtLocal = x20mcm;
}

void PositionInLT() {

	if (trigger!=2) {
		return;
	}

	if (v_LTY->GetEntriesFast() != 1 || v_LT20->GetEntriesFast() != 1) {
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

	Int_t signYstrips = (kSQL_Y_strips>0) - (kSQL_Y_strips<0);
	const Int_t yStrip = ((ERQTelescopeSiDigi*)v_LTY->At(0))->GetStripNb();

	y1mm = ( yStrip + 0.5 )*kSQL_Y_size/kSQL_Y_strips - signYstrips*kSQL_Y_size/2.;	//ok

	fYpointLT2.SetXYZ(0., y1mm, k1mmDistL);
	fYpointLT2.RotateY(kSQL_angle*TMath::DegToRad());

	////////////////////////////////////////////////////////////
	// coordinate X in local frame of the right telescope
	// (plane of the 1mm Si detector - second layer - is
	// regarded as the local frame
	////////////////////////////////////////////////////////////

	//coordinate X in plane of the 20 mcm detector
	Float_t x20mcm = -100.;

	const Int_t signXstrips = (kSQL_X_strips>0) - (kSQL_X_strips<0);
	const Int_t xStrip = ((ERQTelescopeSiDigi*)v_LT20->At(0))->GetStripNb();

	x20mcm = kSQL20_Xoffset + ( xStrip + 0.5 )*kSQL20_X_size/kSQL_X_strips - signXstrips*kSQL20_X_size/2.;	//ok

	//	fXpointLocal.SetXYZ(x20mcm-kSQR20_Xoffset, 0., kThinDist);
	//	fXpointLocalShifted.SetXYZ(x20mcm, 0., kThinDist);
	//
	//	fXpointLocalRotated = fXpointLocal;
	//	fXpointLocalRotated.RotateY(kSQR_angle*TMath::DegToRad());

	//set X and Z coordinates (projection to XZ plane
	fXpointLT1.SetXYZ(x20mcm, 0., kThinDistL);
	//	fXpoint.SetXYZ(x20mcm+kSQR20_Xoffset, 0., kThinZ);

	//rotation as the detector is rotated
	fXpointLT1.RotateY(kSQL_angle*TMath::DegToRad());

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
	vAux.SetXYZ(fXpointLT1.X() - fXt, 0., fXpointLT1.Z());

	// 2)
	//todo: use "+" sign because Theta is always positive and
	//	our constant angle is also positive
	Double_t beta = vAux.Theta() - kSQL_angle*TMath::DegToRad();

	// 3)
	Double_t trackBetweenLayersDistance = (Double_t)(k1mmDistL - kThinDistL)/TMath::Cos(beta);
	//	Double_t trackBetweenLayersDistance = (Double_t)(k1mmDist - kThinDist)/TMath::Cos(kSQR_angle)/TMath::Cos(beta);
	Double_t shiftedMag = vAux.Mag();
	vAux.SetMag(shiftedMag + trackBetweenLayersDistance);

	// 4)
	fPointLT.SetXYZ(vAux.X() + fXt, fYpointLT2.Y(), vAux.Z());

	//asign calculated variables to tree branches:
	fYltLocal = y1mm;
	fXltLocal = x20mcm;
}

void PositionInCT() {
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

Bool_t FlagHeRT() {
	//return 1 if 3He was found
	//coincidences with tritium not taken into account

	if (trigger!=3) {
		return kFALSE;
	}

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

Bool_t FlagHeLT() {
	//return 1 if 3He was found
	//coincidences with tritium not taken into account

	if (trigger!=2) {
		return kFALSE;
	}

	if (v_LT20->GetEntries()!=1 || v_LTY->GetEntries()!=1 || v_LTveto->GetEntries()!=0) {
		return kFALSE;
	}


	//add target condition
	if ( ( (fYt-kCenterY)*(fYt-kCenterY) + (fXt-kCenterX)*(fXt-kCenterX) ) >= kBeamSelection*kBeamSelection) {
		return kFALSE;
	}

	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetEdep();
	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LTY->At(0))->GetEdep();

	if( !( (measuredEdepX>0.) && (measuredEdepY>0.) && (fLT20EdepCorrected>0.) ) ) return kFALSE;

	//add 3He ID cut
	Bool_t flagHeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if ( fLT20StripNbCorrected==i && cLTHelium3[i]->IsInside(measuredEdepY, (Double_t)fLT20EdepCorrected*1000.) ) {
			flagHeCut = kTRUE;
		}
	}

	//add LT time cuts
	const Double_t measuredXtime =
			(Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	//	TString cut;
	Bool_t flagLTXtimeCut = 0;
	//taken from showLT.cxx, common for all strips
//	if (measuredXtime>60. && measuredXtime<80.) flagLTXtimeCut = kTRUE;
	for (Int_t i = 0; i < 16; i++) {
		if (fLT20StripNbCorrected==i && cLT20X[i]->IsInside(measuredXtime, measuredEdepX)) {
			flagLTXtimeCut = kTRUE;
		}
	}


	const Double_t measuredYtime =
			(Double_t)((ERQTelescopeSiDigi*)v_LTY->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	Bool_t flagLTYtimeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if (fLT20StripNbCorrected==i && cLTY[i]->IsInside(measuredYtime, measuredEdepY)) {
			flagLTYtimeCut = kTRUE;
		}
	}

	return flagHeCut*flagLTXtimeCut*flagLTYtimeCut;
}

Bool_t Flag4HeRT() {
	//return 1 if 4He was found
	//coincidences with tritium not taken into account
	if (trigger!=3) {
		return kFALSE;
	}

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

Bool_t Flag4HeLT() {
	//return 1 if 4He was found
	//coincidences with tritium not taken into account
	if (trigger!=2) {
		return kFALSE;
	}

	if (v_LT20->GetEntries()!=1 || v_LTY->GetEntries()!=1 || v_LTveto->GetEntries()!=0) {
		return kFALSE;
	}


	//add target condition
	if ( ( (fYt-kCenterY)*(fYt-kCenterY) + (fXt-kCenterX)*(fXt-kCenterX) ) >= kBeamSelection*kBeamSelection) {
		return kFALSE;
	}

	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetEdep();
	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LTY->At(0))->GetEdep();

	if( !( (measuredEdepX>0.) && (measuredEdepY>0.) && (fLT20EdepCorrected>0.) ) ) return kFALSE;

	//add 3He ID cut
	Bool_t flagHeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if ( fLT20StripNbCorrected==i && cLTHelium4[i]->IsInside(measuredEdepY, (Double_t)fLT20EdepCorrected*1000.) ) {
			flagHeCut = kTRUE;
			//			if (measuredEdepY<0.5) {
			//				cout << "!!!!!!!!!!!!!!!!!!!!!!!\t" << measuredEdepY << endl;
			//			}
		}
	}

	//add RT time cuts
	const Double_t measuredXtime =
			(Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	//	TString cut;
	Bool_t flagLTXtimeCut = 0;
	//for all 16 strips in thin detector
	for (Int_t i = 0; i < 16; i++) {
		if (fLT20StripNbCorrected==i && cLT20X[i]->IsInside(measuredXtime, measuredEdepX)) {
			flagLTXtimeCut = kTRUE;
		}
	}


	const Double_t measuredYtime =
			(Double_t)((ERQTelescopeSiDigi*)v_LTY->At(0))->GetTime() - ((ERBeamDetTOFDigi*)v_BD_F5->At(0))->GetTime()/2.;

	Bool_t flagLTYtimeCut = 0;
	for (Int_t i = 0; i < 16; i++) {
		if (fLT20StripNbCorrected==i && cLTY[i]->IsInside(measuredYtime, measuredEdepY)) {
			flagLTYtimeCut = kTRUE;
		}
	}

	return flagHeCut*flagLTXtimeCut*flagLTYtimeCut;
}

void Fill4VectorsHeRT() {

	if (trigger!=3) {
		return;
	}

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

	kinE = f3HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	kinE = f3HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f3HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	fHeKinMeasuredCorrected = kinE;

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

	//todo: think about entrance angle
	//todo: think about thickness used for calculation
	//	kinE = f3HeSi->GetE0(measuredEdepY, kDeadLayerBetweenSi+kDeadLayerEntranceThin+kThinDetNormalizedThickness);
	//	kinE = f3HeSi->GetE0(measuredEdepY, kThinDetNormalizedThickness);
//	kinE = f3HeSi->GetE0(measuredEdepY, hThicknessR->GetBinContent(mapXbin+1, mapYbin+1));
//	//todo: !!!! solve the entrance angle for target
//	kinE = f3HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
//	kinE = f3HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
//	kinE = f3HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	//////////////////////////////////////////////
	// filling of 3He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;

	//corrected for dead layers
	//	- between Si detectors
	//	- entrance of thin Si
	//	- target geometry

	momentum = GetP(fHeKinMeasuredCorrected, kHeMass);

	fHeMomentumMeasuredCorrected = rtDirection;
	fHeMomentumMeasuredCorrected.SetMag(momentum);

	fHeMeasuredCorrected.SetVectM(fHeMomentumMeasuredCorrected, kHeMass);

}

void Fill4VectorsHeLT() {

	if (trigger!=2) {
		return;
	}

	if (v_LT20->GetEntriesFast() != 1 || v_LTY->GetEntriesFast() != 1) {
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

	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LTY->At(0))->GetEdep();
	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetEdep();

	//////////////////////////////////////////////
	// direction of particles registered in RT
	//////////////////////////////////////////////

	TVector3 rtDirection(fPointLT.X() - fXt, fPointLT.Y() - fYt, fPointLT.Z());
	rtDirection.Unit();

	//angle of 8He to 3He
	fAngleBeam3He = rtDirection.Angle(fBeamDirection);

	//////////////////////////////////////////////
	// calculation of 3He kinetic energies
	//////////////////////////////////////////////

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

	kinE = f3HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	kinE = f3HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f3HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	fHeKinMeasuredCorrected = kinE;

	//calculated from E dep in 1mm
	// - all Si dead layers and thin detector thickness taken as ?
	// - target geometry

	//todo: think about entrance angle
	//todo: think about thickness used for calculation
	//	kinE = f3HeSi->GetE0(measuredEdepY, kDeadLayerBetweenSi+kDeadLayerEntranceThin+kThinDetNormalizedThickness);
	//	kinE = f3HeSi->GetE0(measuredEdepY, kThinDetNormalizedThickness);
//	kinE = f3HeSi->GetE0(measuredEdepY, hThicknessR->GetBinContent(mapXbin+1, mapYbin+1));
//	//todo: !!!! solve the entrance angle for target
//	kinE = f3HeMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
//	kinE = f3HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
//	kinE = f3HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	//////////////////////////////////////////////
	// filling of 3He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;

	//corrected for dead layers
	//	- between Si detectors
	//	- entrance of thin Si
	//	- target geometry

	momentum = GetP(fHeKinMeasuredCorrected, kHeMass);

	fHeMomentumMeasuredCorrected = rtDirection;
	fHeMomentumMeasuredCorrected.SetMag(momentum);

	fHeMeasuredCorrected.SetVectM(fHeMomentumMeasuredCorrected, kHeMass);

}

void Fill4VectorsAlphaRT() {

	if (trigger!=3) {
		return;
	}

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
	kinE = f4HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f4HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	//////////////////////////////////////////////
	// filling of 4He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;
	momentum = GetP(kinE, k4HeMass);

	TVector3 f4HeMomentumMeasuredCorrected = rtDirection;
	f4HeMomentumMeasuredCorrected.SetMag(momentum);

	f4HeMeasuredCorrected.SetVectM(f4HeMomentumMeasuredCorrected, k4HeMass);

}

void Fill4VectorsAlphaLT() {

	if (trigger!=2) {
		return;
	}

	if (v_LT20->GetEntriesFast() != 1 || v_LTY->GetEntriesFast() != 1) {
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

	const Double_t measuredEdepY = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LTY->At(0))->GetEdep();
	const Double_t measuredEdepX = 1000*(Double_t)((ERQTelescopeSiDigi*)v_LT20->At(0))->GetEdep();

	//////////////////////////////////////////////
	// direction of particles registered in RT
	//////////////////////////////////////////////

	TVector3 rtDirection(fPointLT.X() - fXt, fPointLT.Y() - fYt, fPointLT.Z());
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
	kinE = f4HeSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f4HeTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	//////////////////////////////////////////////
	// filling of 4He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;
	momentum = GetP(kinE, k4HeMass);

	TVector3 f4HeMomentumMeasuredCorrected = rtDirection;
	f4HeMomentumMeasuredCorrected.SetMag(momentum);

	f4HeMeasuredCorrected.SetVectM(f4HeMomentumMeasuredCorrected, k4HeMass);

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
		if (measuredEdepCsI > maxEdepCsI) maxEdepCsI = measuredEdepCsI;
	}

	//uncorrected for dead layers in detectors
	kinE = measuredEdepSi + maxEdepCsI;

	const Double_t angle = fCentralDirection.Theta();

	kinE = f3HMylar->GetE0(kinE, kMylarThickness/TMath::Cos(angle));
	kinE = f3HSteel->GetE0(kinE, kSteelThickness/TMath::Cos(angle));
	kinE = f3HTarget->GetE0(kinE, kTargetThickness/2./TMath::Cos(angle));

	//////////////////////////////////////////////
	// filling of 3He 4vectors
	//////////////////////////////////////////////

	Double_t momentum = 0.;
	Double_t momentumD = 0.;

	//clean measured
	momentum = GetP(kinE, kTritiumMass);
	momentumD = GetP(kinE, kDeuteriumMass);

	fTritiumMomentumMeasuredCorrected = fCentralDirection;
	fTritiumMomentumMeasuredCorrected.SetMag(momentum);

	fDeuteriumMomentumMeasuredCorrected = fCentralDirection;
	fDeuteriumMomentumMeasuredCorrected.SetMag(momentumD);

	fT.SetVectM(fTritiumMomentumMeasuredCorrected, kTritiumMass);
	fD.SetVectM(fDeuteriumMomentumMeasuredCorrected, kDeuteriumMass);

}

void Hydrogen7MissingMass() {

	if (v_CTSiX->GetEntriesFast() != 1 || v_CTSiY->GetEntriesFast() != 1) {

		//todo: very silly workaround:
		fHeFlagRT = 0;

		return;
	}

	if (fXt < -40. || fYt < -40.) {

		//todo: very silly workaround:
		fHeFlagRT = 0;

		return;
	}


	fHydrogenMeasuredCorrected = fBeamTarget + fTarget - fHeMeasuredCorrected;

	//////////////////////////////////////////////
	// filling of 7H 4vectors in CMS of 7H
	//////////////////////////////////////////////

	TVector3 beta;
	beta = fHydrogenMeasuredCorrected.BoostVector();
	fHydrogenMeasuredCorrectedCM = fHydrogenMeasuredCorrected;
	fHydrogenMeasuredCorrectedCM.Boost(-beta);

	//////////////////////////////////////////////
	// filling of 3H 4vectors in CMS of 7H
	//////////////////////////////////////////////

//	beta = fHydrogenMeasuredCorrected.BoostVector();
	fTMeasuredCorrectedCM = fT;
	fTMeasuredCorrectedCM.Boost(-beta);

	//////////////////////////////////////////////
	// filling of 2H 4vectors in CMS of 7H
	//////////////////////////////////////////////

	fDMeasuredCorrectedCM = fD;
	fDMeasuredCorrectedCM.Boost(-beta);

	//////////////////////////////////////////////
	// !!!!!!filling of 7H 4vectors in CMS of 7H
	// todo: something different
	//////////////////////////////////////////////

	fAngleLABhtMeasuredCorrected = fHydrogenMeasuredCorrected.Angle(fCentralDirection);

	//new not tested variable
//	fAngleCMof7HhtMeasuredCorrected = fHydrogenMeasuredCorrectedCM.Angle(fTMeasuredCorrectedCM.Vect());
	fAngleCMof7HhtMeasuredCorrected = fHydrogenMeasuredCorrected.Angle(fTMeasuredCorrectedCM.Vect());

	fAngleLAB7hBeamMeasuredCorrected = fHydrogenMeasuredCorrected.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// angle between 3He and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB3HeBeamMeasuredCorrected = fHeMeasuredCorrected.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// Filling vectors in CM of reaction
	//////////////////////////////////////////////
	TLorentzVector reactionCM = fBeamTarget + fTarget;
	TVector3 betaReaction = reactionCM.BoostVector();

	f3HeMeasuredCorrectedCMreaction = fHeMeasuredCorrected;
	f3HeMeasuredCorrectedCMreaction.Boost(-betaReaction);

	fHydrogenMeasuredCorrectedCMreaction = fHydrogenMeasuredCorrected;
	fHydrogenMeasuredCorrectedCMreaction.Boost(-betaReaction);

}

void Hydrogen6MissingMass() {

	if (v_CTSiX->GetEntriesFast() != 1 || v_CTSiY->GetEntriesFast() != 1) {

		//todo: very silly workaround:
		f4HeFlagRT = 0;

		return;
	}

	if (fXt < -40. || fYt < -40.) {

		//todo: very silly workaround:
		f4HeFlagRT = 0;

		return;
	}

	fHydrogen6MeasuredCorrected = fBeamTarget + fTarget - f4HeMeasuredCorrected;

	//////////////////////////////////////////////
	// filling of 7H 4vectors in CMS of 6H
	//////////////////////////////////////////////

	//////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// transitions between coordinate systems were checked for 6H
	// and they work well (precision 10^-12 MeV)
	//////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	const TVector3 beta = fHydrogen6MeasuredCorrected.BoostVector();
	fHydrogen6MeasuredCorrectedCM = fHydrogen6MeasuredCorrected;
	fHydrogen6MeasuredCorrectedCM.Boost(-beta);

	//////////////////////////////////////////////
	// filling of 3H 4vectors in CMS of 6H
	//////////////////////////////////////////////

	fTMeasuredCorrectedCM6H = fT;
	fTMeasuredCorrectedCM6H.Boost(-beta);

	//////////////////////////////////////////////
	// filling of 2H 4vectors in CMS of 6H
	//////////////////////////////////////////////

	fDMeasuredCorrectedCM6H = fD;
	fDMeasuredCorrectedCM6H.Boost(-beta);

	//////////////////////////////////////////////
	// !!!!!!filling of 6H 4vectors in CMS of 6H
	// todo: something different
	//////////////////////////////////////////////

	fAngleLAB6HtMeasuredCorrected = fHydrogen6MeasuredCorrected.Angle(fCentralDirection);

	//////////////////////////////////////////////
	// angle between 6H and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB6HBeamMeasuredCorrected = fHydrogen6MeasuredCorrected.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// angle between 4He and 8He in LAB
	//////////////////////////////////////////////
	fAngleLAB4HeBeamMeasuredCorrected = f4HeMeasuredCorrected.Angle(fBeamMomentumTarget);

	//////////////////////////////////////////////
	// Filling vectors in CM of reaction
	//////////////////////////////////////////////
	TLorentzVector reactionCM = fBeamTarget + fTarget;
	TVector3 betaReaction = reactionCM.BoostVector();

	f4HeMeasuredCorrectedCMreaction = f4HeMeasuredCorrected;
	f4HeMeasuredCorrectedCMreaction.Boost(-betaReaction);

	fHydrogen6MeasuredCorrectedCMreaction = fHydrogen6MeasuredCorrected;
	fHydrogen6MeasuredCorrectedCMreaction.Boost(-betaReaction);
}

void FillHistThicknessFromHistR(TString infile) {

	TFile *fileHist = TFile::Open(infile);
	TH2F *hTemp = (TH2F*)fileHist->Get("hTh");

	gROOT->cd();

	hThicknessR = new TH2F(*hTemp);

	hTemp = NULL;
	fileHist->Close();

	hThicknessR->SetNameTitle("hThicknessR", "Map of thickness for right 20 mcm detector");

	hThicknessR->GetXaxis()->SetTitle("X strips");
	hThicknessR->GetYaxis()->SetTitle("Y strips");
}

void FillHistThicknessFromHistL(TString infile) {

	TFile *fileHist = TFile::Open(infile);
	TH2F *hTemp = (TH2F*)fileHist->Get("hTh");

	gROOT->cd();

	hThicknessL = new TH2F(*hTemp);

	hTemp = NULL;
	fileHist->Close();

	hThicknessL->SetNameTitle("hThicknessL", "Map of thickness for left 20 mcm detector");

	hThicknessL->GetXaxis()->SetTitle("X strips");
	hThicknessL->GetYaxis()->SetTitle("Y strips");
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
	f3HTarget->SetEL(1, kRhoDeuterium); // density in g/cm3
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

void recoBothTelescopes(const Int_t run = 10, const Int_t from = 1, const Int_t to = 24,
		const Int_t noevents = 0, const Bool_t background = 0) {

	TStopwatch stopwatch;
	stopwatch.Start();

	//	FillHistThickness();
	//	FillHistThicknessNew();


	//todo: change the thickness file
	//	TString thicknessFile = "parameters/thicknessRight.root";
	TString thicknessFileR = "parameters/thicknessRight_new.root";
	TString thicknessFileL = "parameters/thicknessLeft.root";

	FillHistThicknessFromHistR(thicknessFileR);
	FillHistThicknessFromHistL(thicknessFileL);

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

void recoBothTelescopesAllData() {

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
//	inPath = "~/data/exp1811/calibrated_filtered_CsI/";
//	outPath = "~/data/exp1811/calibrated_filtered_CsI/reco/";
//	outPath = "~/data/exp1811/calibrated_filtered_CsI/reco_false3He/";
//	outPath = "~/data/exp1811/calibrated_filtered_CsI/reco_6H/";

	//both telescopes
	inPath = "~/data/exp1811/calibrated_filtered_CsI_both/";
	outPath = "~/data/exp1811/calibrated_filtered_CsI_both/reco/";

	Int_t from = 7;
	Int_t to = 22;

	Int_t filesInRun[23] = {0, 0, 0, 0, 0, 0, 0,
			22, 2, 4, 24, 14, 4,
			2, 20, 12, 8, 7, 10,
			1, 14, 1, 6
	};

	for (Int_t i = from; i <= to; i++) {
		recoBothTelescopes(i, 1, filesInRun[i]);
		Info("recoBothTelescopesAllData", "Run %d processed in %f seconds.", i, stopwatch.RealTime());
		stopwatch.Continue();
		cout << endl << endl;
	}

	cout << "Finished in "<< stopwatch.RealTime() << " seconds" << endl;
	cout << "Finished in "<< stopwatch.RealTime()/60. << " minutes" << endl;

//	return;
}

void recoBothTelescopeAllDataBackground() {

	TStopwatch stopwatch;
	stopwatch.Start();

	//	FillHistThickness();
	//	FillHistThicknessNew();

	//	inPath = "~/data/exp1811/calibrated_filtered/background_filtered/";
	//	outPath = "~/data/exp1811/calibrated_filtered/background_filtered/reco/";

//	inPath = "~/data/exp1811/calibrated_filtered_CsI/background/";
//	outPath = "~/data/exp1811/calibrated_filtered_CsI/background/reco/";

	inPath = "~/data/exp1811/calibrated_filtered_CsI_both/background/";
	outPath = "~/data/exp1811/calibrated_filtered_CsI_both/background_reco/";

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
		recoBothTelescopes(i, 1, filesInRun[i], 0, 1);
		Info("recoRightTelescopeAllData", "Run %d processed in %f seconds.", i, stopwatch.RealTime());
		stopwatch.Continue();
		cout << endl << endl;
	}

	cout << "Finished in "<< stopwatch.RealTime() << " seconds" << endl;
	cout << "Finished in "<< stopwatch.RealTime()/60. << " minutes" << endl;
}
