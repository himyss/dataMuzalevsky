void drawExample() { 
  	
  TString input_file;
  TChain *fChain = new TChain("stepMonitoringxTree");
  fChain->Add("/media/analysis_nas/exp201804/rootfilesEgor/h5_14*");
  fChain->SetMakeClass(1);
  Int_t maxE,multY_L,multX_L,multY_R,multX_R,trigger,NeEvent_trigger,multCsi_R,timeF5,thresh_X,thresh_Y,thresh_CsI;


  // Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxDetEventFull1 = 1;
   static constexpr Int_t kMaxDetEventCommon = 1;
   static constexpr Int_t kMaxDAQ_status = 1;
   static constexpr Int_t kMaxDAQ_status_mtime = 1;
   static constexpr Int_t kMaxDAQ_status_mtime_fDetMessages = 1;
   static constexpr Int_t kMaxDAQ_status_scalers = 1;
   static constexpr Int_t kMaxDAQ_status_scalers_fDetMessages = 1;
   static constexpr Int_t kMaxLeft_telescope = 1;
   static constexpr Int_t kMaxLeft_telescope_SQX_L = 1;
   static constexpr Int_t kMaxLeft_telescope_SQX_L_fDetMessages = 32;
   static constexpr Int_t kMaxLeft_telescope_SQY_L = 1;
   static constexpr Int_t kMaxLeft_telescope_SQY_L_fDetMessages = 16;
   static constexpr Int_t kMaxLeft_telescope_CsI_L = 1;
   static constexpr Int_t kMaxLeft_telescope_CsI_L_fDetMessages = 16;
   static constexpr Int_t kMaxLeft_telescope_SQ20 = 1;
   static constexpr Int_t kMaxLeft_telescope_SQ20_fDetMessages = 16;
   static constexpr Int_t kMaxLeft_telescope_tSQ20 = 1;
   static constexpr Int_t kMaxLeft_telescope_tSQ20_fDetMessages = 18;
   static constexpr Int_t kMaxLeft_telescope_tSQX_L = 1;
   static constexpr Int_t kMaxLeft_telescope_tSQX_L_fDetMessages = 32;
   static constexpr Int_t kMaxLeft_telescope_tSQY_L = 1;
   static constexpr Int_t kMaxLeft_telescope_tSQY_L_fDetMessages = 14;
   static constexpr Int_t kMaxLeft_telescope_tCsI_L = 1;
   static constexpr Int_t kMaxLeft_telescope_tCsI_L_fDetMessages = 16;
   static constexpr Int_t kMaxRight_telescope = 1;
   static constexpr Int_t kMaxRight_telescope_SQX_R = 1;
   static constexpr Int_t kMaxRight_telescope_SQX_R_fDetMessages = 32;
   static constexpr Int_t kMaxRight_telescope_SQY_R = 1;
   static constexpr Int_t kMaxRight_telescope_SQY_R_fDetMessages = 16;
   static constexpr Int_t kMaxRight_telescope_CsI_R = 1;
   static constexpr Int_t kMaxRight_telescope_CsI_R_fDetMessages = 16;
   static constexpr Int_t kMaxRight_telescope_tSQX_R = 1;
   static constexpr Int_t kMaxRight_telescope_tSQX_R_fDetMessages = 31;
   static constexpr Int_t kMaxRight_telescope_tSQY_R = 1;
   static constexpr Int_t kMaxRight_telescope_tSQY_R_fDetMessages = 16;
   static constexpr Int_t kMaxRight_telescope_tCsI_R = 1;
   static constexpr Int_t kMaxRight_telescope_tCsI_R_fDetMessages = 16;
   static constexpr Int_t kMaxBeam_detector_ToF = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_F3 = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_F3_fDetMessages = 8;
   static constexpr Int_t kMaxBeam_detector_ToF_F5 = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_F5_fDetMessages = 8;
   static constexpr Int_t kMaxBeam_detector_ToF_F6 = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_F6_fDetMessages = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_tF3 = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_tF3_fDetMessages = 6;
   static constexpr Int_t kMaxBeam_detector_ToF_tF5 = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_tF5_fDetMessages = 4;
   static constexpr Int_t kMaxBeam_detector_ToF_tF6 = 1;
   static constexpr Int_t kMaxBeam_detector_ToF_tF6_fDetMessages = 1;
   static constexpr Int_t kMaxIgnore = 1;
   static constexpr Int_t kMaxIgnore_Ignore = 1;
   static constexpr Int_t kMaxIgnore_Ignore_fDetMessages = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC_tMWPC = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC_tMWPC_fDetMessages = 4;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC1 = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC1_fDetMessages = 30;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC2 = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC2_fDetMessages = 29;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC3 = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC3_fDetMessages = 30;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC4 = 1;
   static constexpr Int_t kMaxBeam_detector_MWPC_MWPC4_fDetMessages = 32;
   static constexpr Int_t kMaxNeutron_detector = 1;
   static constexpr Int_t kMaxNeutron_detector_neutTDC = 1;
   static constexpr Int_t kMaxNeutron_detector_neutTDC_fDetMessages = 18;
   static constexpr Int_t kMaxNeutron_detector_neutAmp = 1;
   static constexpr Int_t kMaxNeutron_detector_neutAmp_fDetMessages = 26;
   static constexpr Int_t kMaxNeutron_detector_neutTAC = 1;
   static constexpr Int_t kMaxNeutron_detector_neutTAC_fDetMessages = 27;

   // Declaration of leaf types
 //DetEventFull    *DetEventFull1_;
   UInt_t          DetEventFull1_TGo4CompositeEvent_fUniqueID;
   UInt_t          DetEventFull1_TGo4CompositeEvent_fBits;
   TString         DetEventFull1_TGo4CompositeEvent_fName;
   TString         DetEventFull1_TGo4CompositeEvent_fTitle;
   Bool_t          DetEventFull1_TGo4CompositeEvent_fbIsValid;
   Short_t         DetEventFull1_TGo4CompositeEvent_fIdentifier;
   Short_t         DetEventFull1_TGo4CompositeEvent_fNElements;
   Short_t         DetEventFull1_TGo4CompositeEvent_fMaxIndex;
 //DetEventCommon  *DetEventCommon_;
   UInt_t          DetEventCommon_TGo4EventElement_fUniqueID;
   UInt_t          DetEventCommon_TGo4EventElement_fBits;
   TString         DetEventCommon_TGo4EventElement_fName;
   TString         DetEventCommon_TGo4EventElement_fTitle;
   Bool_t          DetEventCommon_TGo4EventElement_fbIsValid;
   Short_t         DetEventCommon_TGo4EventElement_fIdentifier;
   UInt_t          DetEventCommon_trigger;
   UInt_t          DetEventCommon_scaler[16];
   UShort_t        DetEventCommon_mtime[2];
 //DetEventDetector *DAQ_status_;
   UInt_t          DAQ_status_TGo4CompositeEvent_fUniqueID;
   UInt_t          DAQ_status_TGo4CompositeEvent_fBits;
   TString         DAQ_status_TGo4CompositeEvent_fName;
   TString         DAQ_status_TGo4CompositeEvent_fTitle;
   Bool_t          DAQ_status_TGo4CompositeEvent_fbIsValid;
   Short_t         DAQ_status_TGo4CompositeEvent_fIdentifier;
   Short_t         DAQ_status_TGo4CompositeEvent_fNElements;
   Short_t         DAQ_status_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *DAQ_status_mtime_;
   UInt_t          DAQ_status_mtime_TGo4EventElement_fUniqueID;
   UInt_t          DAQ_status_mtime_TGo4EventElement_fBits;
   TString         DAQ_status_mtime_TGo4EventElement_fName;
   TString         DAQ_status_mtime_TGo4EventElement_fTitle;
   Bool_t          DAQ_status_mtime_TGo4EventElement_fbIsValid;
   Short_t         DAQ_status_mtime_TGo4EventElement_fIdentifier;
   Int_t           DAQ_status_mtime_fDetMessages_;
   UInt_t          DAQ_status_mtime_fDetMessages_fUniqueID[kMaxDAQ_status_mtime_fDetMessages];   //[DAQ_status_mtime.fDetMessages_]
   UInt_t          DAQ_status_mtime_fDetMessages_fBits[kMaxDAQ_status_mtime_fDetMessages];   //[DAQ_status_mtime.fDetMessages_]
   Short_t         DAQ_status_mtime_fDetMessages_fDetector[kMaxDAQ_status_mtime_fDetMessages];   //[DAQ_status_mtime.fDetMessages_]
   Short_t         DAQ_status_mtime_fDetMessages_fStation[kMaxDAQ_status_mtime_fDetMessages];   //[DAQ_status_mtime.fDetMessages_]
   Int_t           DAQ_status_mtime_fDetMessages_fStChannel[kMaxDAQ_status_mtime_fDetMessages];   //[DAQ_status_mtime.fDetMessages_]
   Int_t           DAQ_status_mtime_fDetMessages_fValue[kMaxDAQ_status_mtime_fDetMessages];   //[DAQ_status_mtime.fDetMessages_]
 //DetEventStation *DAQ_status_scalers_;
   UInt_t          DAQ_status_scalers_TGo4EventElement_fUniqueID;
   UInt_t          DAQ_status_scalers_TGo4EventElement_fBits;
   TString         DAQ_status_scalers_TGo4EventElement_fName;
   TString         DAQ_status_scalers_TGo4EventElement_fTitle;
   Bool_t          DAQ_status_scalers_TGo4EventElement_fbIsValid;
   Short_t         DAQ_status_scalers_TGo4EventElement_fIdentifier;
   Int_t           DAQ_status_scalers_fDetMessages_;
   UInt_t          DAQ_status_scalers_fDetMessages_fUniqueID[kMaxDAQ_status_scalers_fDetMessages];   //[DAQ_status_scalers.fDetMessages_]
   UInt_t          DAQ_status_scalers_fDetMessages_fBits[kMaxDAQ_status_scalers_fDetMessages];   //[DAQ_status_scalers.fDetMessages_]
   Short_t         DAQ_status_scalers_fDetMessages_fDetector[kMaxDAQ_status_scalers_fDetMessages];   //[DAQ_status_scalers.fDetMessages_]
   Short_t         DAQ_status_scalers_fDetMessages_fStation[kMaxDAQ_status_scalers_fDetMessages];   //[DAQ_status_scalers.fDetMessages_]
   Int_t           DAQ_status_scalers_fDetMessages_fStChannel[kMaxDAQ_status_scalers_fDetMessages];   //[DAQ_status_scalers.fDetMessages_]
   Int_t           DAQ_status_scalers_fDetMessages_fValue[kMaxDAQ_status_scalers_fDetMessages];   //[DAQ_status_scalers.fDetMessages_]
 //DetEventDetector *Left_telescope_;
   UInt_t          Left_telescope_TGo4CompositeEvent_fUniqueID;
   UInt_t          Left_telescope_TGo4CompositeEvent_fBits;
   TString         Left_telescope_TGo4CompositeEvent_fName;
   TString         Left_telescope_TGo4CompositeEvent_fTitle;
   Bool_t          Left_telescope_TGo4CompositeEvent_fbIsValid;
   Short_t         Left_telescope_TGo4CompositeEvent_fIdentifier;
   Short_t         Left_telescope_TGo4CompositeEvent_fNElements;
   Short_t         Left_telescope_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *Left_telescope_SQX_L_;
   UInt_t          Left_telescope_SQX_L_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_SQX_L_TGo4EventElement_fBits;
   TString         Left_telescope_SQX_L_TGo4EventElement_fName;
   TString         Left_telescope_SQX_L_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_SQX_L_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_SQX_L_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_SQX_L_fDetMessages_;
   UInt_t          Left_telescope_SQX_L_fDetMessages_fUniqueID[kMaxLeft_telescope_SQX_L_fDetMessages];   //[Left_telescope_SQX_L.fDetMessages_]
   UInt_t          Left_telescope_SQX_L_fDetMessages_fBits[kMaxLeft_telescope_SQX_L_fDetMessages];   //[Left_telescope_SQX_L.fDetMessages_]
   Short_t         Left_telescope_SQX_L_fDetMessages_fDetector[kMaxLeft_telescope_SQX_L_fDetMessages];   //[Left_telescope_SQX_L.fDetMessages_]
   Short_t         Left_telescope_SQX_L_fDetMessages_fStation[kMaxLeft_telescope_SQX_L_fDetMessages];   //[Left_telescope_SQX_L.fDetMessages_]
   Int_t           Left_telescope_SQX_L_fDetMessages_fStChannel[kMaxLeft_telescope_SQX_L_fDetMessages];   //[Left_telescope_SQX_L.fDetMessages_]
   Int_t           Left_telescope_SQX_L_fDetMessages_fValue[kMaxLeft_telescope_SQX_L_fDetMessages];   //[Left_telescope_SQX_L.fDetMessages_]
 //DetEventStation *Left_telescope_SQY_L_;
   UInt_t          Left_telescope_SQY_L_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_SQY_L_TGo4EventElement_fBits;
   TString         Left_telescope_SQY_L_TGo4EventElement_fName;
   TString         Left_telescope_SQY_L_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_SQY_L_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_SQY_L_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_SQY_L_fDetMessages_;
   UInt_t          Left_telescope_SQY_L_fDetMessages_fUniqueID[kMaxLeft_telescope_SQY_L_fDetMessages];   //[Left_telescope_SQY_L.fDetMessages_]
   UInt_t          Left_telescope_SQY_L_fDetMessages_fBits[kMaxLeft_telescope_SQY_L_fDetMessages];   //[Left_telescope_SQY_L.fDetMessages_]
   Short_t         Left_telescope_SQY_L_fDetMessages_fDetector[kMaxLeft_telescope_SQY_L_fDetMessages];   //[Left_telescope_SQY_L.fDetMessages_]
   Short_t         Left_telescope_SQY_L_fDetMessages_fStation[kMaxLeft_telescope_SQY_L_fDetMessages];   //[Left_telescope_SQY_L.fDetMessages_]
   Int_t           Left_telescope_SQY_L_fDetMessages_fStChannel[kMaxLeft_telescope_SQY_L_fDetMessages];   //[Left_telescope_SQY_L.fDetMessages_]
   Int_t           Left_telescope_SQY_L_fDetMessages_fValue[kMaxLeft_telescope_SQY_L_fDetMessages];   //[Left_telescope_SQY_L.fDetMessages_]
 //DetEventStation *Left_telescope_CsI_L_;
   UInt_t          Left_telescope_CsI_L_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_CsI_L_TGo4EventElement_fBits;
   TString         Left_telescope_CsI_L_TGo4EventElement_fName;
   TString         Left_telescope_CsI_L_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_CsI_L_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_CsI_L_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_CsI_L_fDetMessages_;
   UInt_t          Left_telescope_CsI_L_fDetMessages_fUniqueID[kMaxLeft_telescope_CsI_L_fDetMessages];   //[Left_telescope_CsI_L.fDetMessages_]
   UInt_t          Left_telescope_CsI_L_fDetMessages_fBits[kMaxLeft_telescope_CsI_L_fDetMessages];   //[Left_telescope_CsI_L.fDetMessages_]
   Short_t         Left_telescope_CsI_L_fDetMessages_fDetector[kMaxLeft_telescope_CsI_L_fDetMessages];   //[Left_telescope_CsI_L.fDetMessages_]
   Short_t         Left_telescope_CsI_L_fDetMessages_fStation[kMaxLeft_telescope_CsI_L_fDetMessages];   //[Left_telescope_CsI_L.fDetMessages_]
   Int_t           Left_telescope_CsI_L_fDetMessages_fStChannel[kMaxLeft_telescope_CsI_L_fDetMessages];   //[Left_telescope_CsI_L.fDetMessages_]
   Int_t           Left_telescope_CsI_L_fDetMessages_fValue[kMaxLeft_telescope_CsI_L_fDetMessages];   //[Left_telescope_CsI_L.fDetMessages_]
 //DetEventStation *Left_telescope_SQ20_;
   UInt_t          Left_telescope_SQ20_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_SQ20_TGo4EventElement_fBits;
   TString         Left_telescope_SQ20_TGo4EventElement_fName;
   TString         Left_telescope_SQ20_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_SQ20_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_SQ20_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_SQ20_fDetMessages_;
   UInt_t          Left_telescope_SQ20_fDetMessages_fUniqueID[kMaxLeft_telescope_SQ20_fDetMessages];   //[Left_telescope_SQ20.fDetMessages_]
   UInt_t          Left_telescope_SQ20_fDetMessages_fBits[kMaxLeft_telescope_SQ20_fDetMessages];   //[Left_telescope_SQ20.fDetMessages_]
   Short_t         Left_telescope_SQ20_fDetMessages_fDetector[kMaxLeft_telescope_SQ20_fDetMessages];   //[Left_telescope_SQ20.fDetMessages_]
   Short_t         Left_telescope_SQ20_fDetMessages_fStation[kMaxLeft_telescope_SQ20_fDetMessages];   //[Left_telescope_SQ20.fDetMessages_]
   Int_t           Left_telescope_SQ20_fDetMessages_fStChannel[kMaxLeft_telescope_SQ20_fDetMessages];   //[Left_telescope_SQ20.fDetMessages_]
   Int_t           Left_telescope_SQ20_fDetMessages_fValue[kMaxLeft_telescope_SQ20_fDetMessages];   //[Left_telescope_SQ20.fDetMessages_]
 //DetEventStation *Left_telescope_tSQ20_;
   UInt_t          Left_telescope_tSQ20_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_tSQ20_TGo4EventElement_fBits;
   TString         Left_telescope_tSQ20_TGo4EventElement_fName;
   TString         Left_telescope_tSQ20_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_tSQ20_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_tSQ20_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_tSQ20_fDetMessages_;
   UInt_t          Left_telescope_tSQ20_fDetMessages_fUniqueID[kMaxLeft_telescope_tSQ20_fDetMessages];   //[Left_telescope_tSQ20.fDetMessages_]
   UInt_t          Left_telescope_tSQ20_fDetMessages_fBits[kMaxLeft_telescope_tSQ20_fDetMessages];   //[Left_telescope_tSQ20.fDetMessages_]
   Short_t         Left_telescope_tSQ20_fDetMessages_fDetector[kMaxLeft_telescope_tSQ20_fDetMessages];   //[Left_telescope_tSQ20.fDetMessages_]
   Short_t         Left_telescope_tSQ20_fDetMessages_fStation[kMaxLeft_telescope_tSQ20_fDetMessages];   //[Left_telescope_tSQ20.fDetMessages_]
   Int_t           Left_telescope_tSQ20_fDetMessages_fStChannel[kMaxLeft_telescope_tSQ20_fDetMessages];   //[Left_telescope_tSQ20.fDetMessages_]
   Int_t           Left_telescope_tSQ20_fDetMessages_fValue[kMaxLeft_telescope_tSQ20_fDetMessages];   //[Left_telescope_tSQ20.fDetMessages_]
 //DetEventStation *Left_telescope_tSQX_L_;
   UInt_t          Left_telescope_tSQX_L_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_tSQX_L_TGo4EventElement_fBits;
   TString         Left_telescope_tSQX_L_TGo4EventElement_fName;
   TString         Left_telescope_tSQX_L_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_tSQX_L_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_tSQX_L_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_tSQX_L_fDetMessages_;
   UInt_t          Left_telescope_tSQX_L_fDetMessages_fUniqueID[kMaxLeft_telescope_tSQX_L_fDetMessages];   //[Left_telescope_tSQX_L.fDetMessages_]
   UInt_t          Left_telescope_tSQX_L_fDetMessages_fBits[kMaxLeft_telescope_tSQX_L_fDetMessages];   //[Left_telescope_tSQX_L.fDetMessages_]
   Short_t         Left_telescope_tSQX_L_fDetMessages_fDetector[kMaxLeft_telescope_tSQX_L_fDetMessages];   //[Left_telescope_tSQX_L.fDetMessages_]
   Short_t         Left_telescope_tSQX_L_fDetMessages_fStation[kMaxLeft_telescope_tSQX_L_fDetMessages];   //[Left_telescope_tSQX_L.fDetMessages_]
   Int_t           Left_telescope_tSQX_L_fDetMessages_fStChannel[kMaxLeft_telescope_tSQX_L_fDetMessages];   //[Left_telescope_tSQX_L.fDetMessages_]
   Int_t           Left_telescope_tSQX_L_fDetMessages_fValue[kMaxLeft_telescope_tSQX_L_fDetMessages];   //[Left_telescope_tSQX_L.fDetMessages_]
 //DetEventStation *Left_telescope_tSQY_L_;
   UInt_t          Left_telescope_tSQY_L_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_tSQY_L_TGo4EventElement_fBits;
   TString         Left_telescope_tSQY_L_TGo4EventElement_fName;
   TString         Left_telescope_tSQY_L_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_tSQY_L_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_tSQY_L_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_tSQY_L_fDetMessages_;
   UInt_t          Left_telescope_tSQY_L_fDetMessages_fUniqueID[kMaxLeft_telescope_tSQY_L_fDetMessages];   //[Left_telescope_tSQY_L.fDetMessages_]
   UInt_t          Left_telescope_tSQY_L_fDetMessages_fBits[kMaxLeft_telescope_tSQY_L_fDetMessages];   //[Left_telescope_tSQY_L.fDetMessages_]
   Short_t         Left_telescope_tSQY_L_fDetMessages_fDetector[kMaxLeft_telescope_tSQY_L_fDetMessages];   //[Left_telescope_tSQY_L.fDetMessages_]
   Short_t         Left_telescope_tSQY_L_fDetMessages_fStation[kMaxLeft_telescope_tSQY_L_fDetMessages];   //[Left_telescope_tSQY_L.fDetMessages_]
   Int_t           Left_telescope_tSQY_L_fDetMessages_fStChannel[kMaxLeft_telescope_tSQY_L_fDetMessages];   //[Left_telescope_tSQY_L.fDetMessages_]
   Int_t           Left_telescope_tSQY_L_fDetMessages_fValue[kMaxLeft_telescope_tSQY_L_fDetMessages];   //[Left_telescope_tSQY_L.fDetMessages_]
 //DetEventStation *Left_telescope_tCsI_L_;
   UInt_t          Left_telescope_tCsI_L_TGo4EventElement_fUniqueID;
   UInt_t          Left_telescope_tCsI_L_TGo4EventElement_fBits;
   TString         Left_telescope_tCsI_L_TGo4EventElement_fName;
   TString         Left_telescope_tCsI_L_TGo4EventElement_fTitle;
   Bool_t          Left_telescope_tCsI_L_TGo4EventElement_fbIsValid;
   Short_t         Left_telescope_tCsI_L_TGo4EventElement_fIdentifier;
   Int_t           Left_telescope_tCsI_L_fDetMessages_;
   UInt_t          Left_telescope_tCsI_L_fDetMessages_fUniqueID[kMaxLeft_telescope_tCsI_L_fDetMessages];   //[Left_telescope_tCsI_L.fDetMessages_]
   UInt_t          Left_telescope_tCsI_L_fDetMessages_fBits[kMaxLeft_telescope_tCsI_L_fDetMessages];   //[Left_telescope_tCsI_L.fDetMessages_]
   Short_t         Left_telescope_tCsI_L_fDetMessages_fDetector[kMaxLeft_telescope_tCsI_L_fDetMessages];   //[Left_telescope_tCsI_L.fDetMessages_]
   Short_t         Left_telescope_tCsI_L_fDetMessages_fStation[kMaxLeft_telescope_tCsI_L_fDetMessages];   //[Left_telescope_tCsI_L.fDetMessages_]
   Int_t           Left_telescope_tCsI_L_fDetMessages_fStChannel[kMaxLeft_telescope_tCsI_L_fDetMessages];   //[Left_telescope_tCsI_L.fDetMessages_]
   Int_t           Left_telescope_tCsI_L_fDetMessages_fValue[kMaxLeft_telescope_tCsI_L_fDetMessages];   //[Left_telescope_tCsI_L.fDetMessages_]
 //DetEventDetector *Right_telescope_;
   UInt_t          Right_telescope_TGo4CompositeEvent_fUniqueID;
   UInt_t          Right_telescope_TGo4CompositeEvent_fBits;
   TString         Right_telescope_TGo4CompositeEvent_fName;
   TString         Right_telescope_TGo4CompositeEvent_fTitle;
   Bool_t          Right_telescope_TGo4CompositeEvent_fbIsValid;
   Short_t         Right_telescope_TGo4CompositeEvent_fIdentifier;
   Short_t         Right_telescope_TGo4CompositeEvent_fNElements;
   Short_t         Right_telescope_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *Right_telescope_SQX_R_;
   UInt_t          Right_telescope_SQX_R_TGo4EventElement_fUniqueID;
   UInt_t          Right_telescope_SQX_R_TGo4EventElement_fBits;
   TString         Right_telescope_SQX_R_TGo4EventElement_fName;
   TString         Right_telescope_SQX_R_TGo4EventElement_fTitle;
   Bool_t          Right_telescope_SQX_R_TGo4EventElement_fbIsValid;
   Short_t         Right_telescope_SQX_R_TGo4EventElement_fIdentifier;
   Int_t           Right_telescope_SQX_R_fDetMessages_;
   UInt_t          Right_telescope_SQX_R_fDetMessages_fUniqueID[kMaxRight_telescope_SQX_R_fDetMessages];   //[Right_telescope_SQX_R.fDetMessages_]
   UInt_t          Right_telescope_SQX_R_fDetMessages_fBits[kMaxRight_telescope_SQX_R_fDetMessages];   //[Right_telescope_SQX_R.fDetMessages_]
   Short_t         Right_telescope_SQX_R_fDetMessages_fDetector[kMaxRight_telescope_SQX_R_fDetMessages];   //[Right_telescope_SQX_R.fDetMessages_]
   Short_t         Right_telescope_SQX_R_fDetMessages_fStation[kMaxRight_telescope_SQX_R_fDetMessages];   //[Right_telescope_SQX_R.fDetMessages_]
   Int_t           Right_telescope_SQX_R_fDetMessages_fStChannel[kMaxRight_telescope_SQX_R_fDetMessages];   //[Right_telescope_SQX_R.fDetMessages_]
   Int_t           Right_telescope_SQX_R_fDetMessages_fValue[kMaxRight_telescope_SQX_R_fDetMessages];   //[Right_telescope_SQX_R.fDetMessages_]
 //DetEventStation *Right_telescope_SQY_R_;
   UInt_t          Right_telescope_SQY_R_TGo4EventElement_fUniqueID;
   UInt_t          Right_telescope_SQY_R_TGo4EventElement_fBits;
   TString         Right_telescope_SQY_R_TGo4EventElement_fName;
   TString         Right_telescope_SQY_R_TGo4EventElement_fTitle;
   Bool_t          Right_telescope_SQY_R_TGo4EventElement_fbIsValid;
   Short_t         Right_telescope_SQY_R_TGo4EventElement_fIdentifier;
   Int_t           Right_telescope_SQY_R_fDetMessages_;
   UInt_t          Right_telescope_SQY_R_fDetMessages_fUniqueID[kMaxRight_telescope_SQY_R_fDetMessages];   //[Right_telescope_SQY_R.fDetMessages_]
   UInt_t          Right_telescope_SQY_R_fDetMessages_fBits[kMaxRight_telescope_SQY_R_fDetMessages];   //[Right_telescope_SQY_R.fDetMessages_]
   Short_t         Right_telescope_SQY_R_fDetMessages_fDetector[kMaxRight_telescope_SQY_R_fDetMessages];   //[Right_telescope_SQY_R.fDetMessages_]
   Short_t         Right_telescope_SQY_R_fDetMessages_fStation[kMaxRight_telescope_SQY_R_fDetMessages];   //[Right_telescope_SQY_R.fDetMessages_]
   Int_t           Right_telescope_SQY_R_fDetMessages_fStChannel[kMaxRight_telescope_SQY_R_fDetMessages];   //[Right_telescope_SQY_R.fDetMessages_]
   Int_t           Right_telescope_SQY_R_fDetMessages_fValue[kMaxRight_telescope_SQY_R_fDetMessages];   //[Right_telescope_SQY_R.fDetMessages_]
 //DetEventStation *Right_telescope_CsI_R_;
   UInt_t          Right_telescope_CsI_R_TGo4EventElement_fUniqueID;
   UInt_t          Right_telescope_CsI_R_TGo4EventElement_fBits;
   TString         Right_telescope_CsI_R_TGo4EventElement_fName;
   TString         Right_telescope_CsI_R_TGo4EventElement_fTitle;
   Bool_t          Right_telescope_CsI_R_TGo4EventElement_fbIsValid;
   Short_t         Right_telescope_CsI_R_TGo4EventElement_fIdentifier;
   Int_t           Right_telescope_CsI_R_fDetMessages_;
   UInt_t          Right_telescope_CsI_R_fDetMessages_fUniqueID[kMaxRight_telescope_CsI_R_fDetMessages];   //[Right_telescope_CsI_R.fDetMessages_]
   UInt_t          Right_telescope_CsI_R_fDetMessages_fBits[kMaxRight_telescope_CsI_R_fDetMessages];   //[Right_telescope_CsI_R.fDetMessages_]
   Short_t         Right_telescope_CsI_R_fDetMessages_fDetector[kMaxRight_telescope_CsI_R_fDetMessages];   //[Right_telescope_CsI_R.fDetMessages_]
   Short_t         Right_telescope_CsI_R_fDetMessages_fStation[kMaxRight_telescope_CsI_R_fDetMessages];   //[Right_telescope_CsI_R.fDetMessages_]
   Int_t           Right_telescope_CsI_R_fDetMessages_fStChannel[kMaxRight_telescope_CsI_R_fDetMessages];   //[Right_telescope_CsI_R.fDetMessages_]
   Int_t           Right_telescope_CsI_R_fDetMessages_fValue[kMaxRight_telescope_CsI_R_fDetMessages];   //[Right_telescope_CsI_R.fDetMessages_]
 //DetEventStation *Right_telescope_tSQX_R_;
   UInt_t          Right_telescope_tSQX_R_TGo4EventElement_fUniqueID;
   UInt_t          Right_telescope_tSQX_R_TGo4EventElement_fBits;
   TString         Right_telescope_tSQX_R_TGo4EventElement_fName;
   TString         Right_telescope_tSQX_R_TGo4EventElement_fTitle;
   Bool_t          Right_telescope_tSQX_R_TGo4EventElement_fbIsValid;
   Short_t         Right_telescope_tSQX_R_TGo4EventElement_fIdentifier;
   Int_t           Right_telescope_tSQX_R_fDetMessages_;
   UInt_t          Right_telescope_tSQX_R_fDetMessages_fUniqueID[kMaxRight_telescope_tSQX_R_fDetMessages];   //[Right_telescope_tSQX_R.fDetMessages_]
   UInt_t          Right_telescope_tSQX_R_fDetMessages_fBits[kMaxRight_telescope_tSQX_R_fDetMessages];   //[Right_telescope_tSQX_R.fDetMessages_]
   Short_t         Right_telescope_tSQX_R_fDetMessages_fDetector[kMaxRight_telescope_tSQX_R_fDetMessages];   //[Right_telescope_tSQX_R.fDetMessages_]
   Short_t         Right_telescope_tSQX_R_fDetMessages_fStation[kMaxRight_telescope_tSQX_R_fDetMessages];   //[Right_telescope_tSQX_R.fDetMessages_]
   Int_t           Right_telescope_tSQX_R_fDetMessages_fStChannel[kMaxRight_telescope_tSQX_R_fDetMessages];   //[Right_telescope_tSQX_R.fDetMessages_]
   Int_t           Right_telescope_tSQX_R_fDetMessages_fValue[kMaxRight_telescope_tSQX_R_fDetMessages];   //[Right_telescope_tSQX_R.fDetMessages_]
 //DetEventStation *Right_telescope_tSQY_R_;
   UInt_t          Right_telescope_tSQY_R_TGo4EventElement_fUniqueID;
   UInt_t          Right_telescope_tSQY_R_TGo4EventElement_fBits;
   TString         Right_telescope_tSQY_R_TGo4EventElement_fName;
   TString         Right_telescope_tSQY_R_TGo4EventElement_fTitle;
   Bool_t          Right_telescope_tSQY_R_TGo4EventElement_fbIsValid;
   Short_t         Right_telescope_tSQY_R_TGo4EventElement_fIdentifier;
   Int_t           Right_telescope_tSQY_R_fDetMessages_;
   UInt_t          Right_telescope_tSQY_R_fDetMessages_fUniqueID[kMaxRight_telescope_tSQY_R_fDetMessages];   //[Right_telescope_tSQY_R.fDetMessages_]
   UInt_t          Right_telescope_tSQY_R_fDetMessages_fBits[kMaxRight_telescope_tSQY_R_fDetMessages];   //[Right_telescope_tSQY_R.fDetMessages_]
   Short_t         Right_telescope_tSQY_R_fDetMessages_fDetector[kMaxRight_telescope_tSQY_R_fDetMessages];   //[Right_telescope_tSQY_R.fDetMessages_]
   Short_t         Right_telescope_tSQY_R_fDetMessages_fStation[kMaxRight_telescope_tSQY_R_fDetMessages];   //[Right_telescope_tSQY_R.fDetMessages_]
   Int_t           Right_telescope_tSQY_R_fDetMessages_fStChannel[kMaxRight_telescope_tSQY_R_fDetMessages];   //[Right_telescope_tSQY_R.fDetMessages_]
   Int_t           Right_telescope_tSQY_R_fDetMessages_fValue[kMaxRight_telescope_tSQY_R_fDetMessages];   //[Right_telescope_tSQY_R.fDetMessages_]
 //DetEventStation *Right_telescope_tCsI_R_;
   UInt_t          Right_telescope_tCsI_R_TGo4EventElement_fUniqueID;
   UInt_t          Right_telescope_tCsI_R_TGo4EventElement_fBits;
   TString         Right_telescope_tCsI_R_TGo4EventElement_fName;
   TString         Right_telescope_tCsI_R_TGo4EventElement_fTitle;
   Bool_t          Right_telescope_tCsI_R_TGo4EventElement_fbIsValid;
   Short_t         Right_telescope_tCsI_R_TGo4EventElement_fIdentifier;
   Int_t           Right_telescope_tCsI_R_fDetMessages_;
   UInt_t          Right_telescope_tCsI_R_fDetMessages_fUniqueID[kMaxRight_telescope_tCsI_R_fDetMessages];   //[Right_telescope_tCsI_R.fDetMessages_]
   UInt_t          Right_telescope_tCsI_R_fDetMessages_fBits[kMaxRight_telescope_tCsI_R_fDetMessages];   //[Right_telescope_tCsI_R.fDetMessages_]
   Short_t         Right_telescope_tCsI_R_fDetMessages_fDetector[kMaxRight_telescope_tCsI_R_fDetMessages];   //[Right_telescope_tCsI_R.fDetMessages_]
   Short_t         Right_telescope_tCsI_R_fDetMessages_fStation[kMaxRight_telescope_tCsI_R_fDetMessages];   //[Right_telescope_tCsI_R.fDetMessages_]
   Int_t           Right_telescope_tCsI_R_fDetMessages_fStChannel[kMaxRight_telescope_tCsI_R_fDetMessages];   //[Right_telescope_tCsI_R.fDetMessages_]
   Int_t           Right_telescope_tCsI_R_fDetMessages_fValue[kMaxRight_telescope_tCsI_R_fDetMessages];   //[Right_telescope_tCsI_R.fDetMessages_]
 //DetEventDetector *Beam_detector_ToF_;
   UInt_t          Beam_detector_ToF_TGo4CompositeEvent_fUniqueID;
   UInt_t          Beam_detector_ToF_TGo4CompositeEvent_fBits;
   TString         Beam_detector_ToF_TGo4CompositeEvent_fName;
   TString         Beam_detector_ToF_TGo4CompositeEvent_fTitle;
   Bool_t          Beam_detector_ToF_TGo4CompositeEvent_fbIsValid;
   Short_t         Beam_detector_ToF_TGo4CompositeEvent_fIdentifier;
   Short_t         Beam_detector_ToF_TGo4CompositeEvent_fNElements;
   Short_t         Beam_detector_ToF_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *Beam_detector_ToF_F3_;
   UInt_t          Beam_detector_ToF_F3_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_ToF_F3_TGo4EventElement_fBits;
   TString         Beam_detector_ToF_F3_TGo4EventElement_fName;
   TString         Beam_detector_ToF_F3_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_ToF_F3_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_ToF_F3_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_ToF_F3_fDetMessages_;
   UInt_t          Beam_detector_ToF_F3_fDetMessages_fUniqueID[kMaxBeam_detector_ToF_F3_fDetMessages];   //[Beam_detector_ToF_F3.fDetMessages_]
   UInt_t          Beam_detector_ToF_F3_fDetMessages_fBits[kMaxBeam_detector_ToF_F3_fDetMessages];   //[Beam_detector_ToF_F3.fDetMessages_]
   Short_t         Beam_detector_ToF_F3_fDetMessages_fDetector[kMaxBeam_detector_ToF_F3_fDetMessages];   //[Beam_detector_ToF_F3.fDetMessages_]
   Short_t         Beam_detector_ToF_F3_fDetMessages_fStation[kMaxBeam_detector_ToF_F3_fDetMessages];   //[Beam_detector_ToF_F3.fDetMessages_]
   Int_t           Beam_detector_ToF_F3_fDetMessages_fStChannel[kMaxBeam_detector_ToF_F3_fDetMessages];   //[Beam_detector_ToF_F3.fDetMessages_]
   Int_t           Beam_detector_ToF_F3_fDetMessages_fValue[kMaxBeam_detector_ToF_F3_fDetMessages];   //[Beam_detector_ToF_F3.fDetMessages_]
 //DetEventStation *Beam_detector_ToF_F5_;
   UInt_t          Beam_detector_ToF_F5_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_ToF_F5_TGo4EventElement_fBits;
   TString         Beam_detector_ToF_F5_TGo4EventElement_fName;
   TString         Beam_detector_ToF_F5_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_ToF_F5_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_ToF_F5_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_ToF_F5_fDetMessages_;
   UInt_t          Beam_detector_ToF_F5_fDetMessages_fUniqueID[kMaxBeam_detector_ToF_F5_fDetMessages];   //[Beam_detector_ToF_F5.fDetMessages_]
   UInt_t          Beam_detector_ToF_F5_fDetMessages_fBits[kMaxBeam_detector_ToF_F5_fDetMessages];   //[Beam_detector_ToF_F5.fDetMessages_]
   Short_t         Beam_detector_ToF_F5_fDetMessages_fDetector[kMaxBeam_detector_ToF_F5_fDetMessages];   //[Beam_detector_ToF_F5.fDetMessages_]
   Short_t         Beam_detector_ToF_F5_fDetMessages_fStation[kMaxBeam_detector_ToF_F5_fDetMessages];   //[Beam_detector_ToF_F5.fDetMessages_]
   Int_t           Beam_detector_ToF_F5_fDetMessages_fStChannel[kMaxBeam_detector_ToF_F5_fDetMessages];   //[Beam_detector_ToF_F5.fDetMessages_]
   Int_t           Beam_detector_ToF_F5_fDetMessages_fValue[kMaxBeam_detector_ToF_F5_fDetMessages];   //[Beam_detector_ToF_F5.fDetMessages_]
 //DetEventStation *Beam_detector_ToF_F6_;
   UInt_t          Beam_detector_ToF_F6_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_ToF_F6_TGo4EventElement_fBits;
   TString         Beam_detector_ToF_F6_TGo4EventElement_fName;
   TString         Beam_detector_ToF_F6_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_ToF_F6_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_ToF_F6_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_ToF_F6_fDetMessages_;
   UInt_t          Beam_detector_ToF_F6_fDetMessages_fUniqueID[kMaxBeam_detector_ToF_F6_fDetMessages];   //[Beam_detector_ToF_F6.fDetMessages_]
   UInt_t          Beam_detector_ToF_F6_fDetMessages_fBits[kMaxBeam_detector_ToF_F6_fDetMessages];   //[Beam_detector_ToF_F6.fDetMessages_]
   Short_t         Beam_detector_ToF_F6_fDetMessages_fDetector[kMaxBeam_detector_ToF_F6_fDetMessages];   //[Beam_detector_ToF_F6.fDetMessages_]
   Short_t         Beam_detector_ToF_F6_fDetMessages_fStation[kMaxBeam_detector_ToF_F6_fDetMessages];   //[Beam_detector_ToF_F6.fDetMessages_]
   Int_t           Beam_detector_ToF_F6_fDetMessages_fStChannel[kMaxBeam_detector_ToF_F6_fDetMessages];   //[Beam_detector_ToF_F6.fDetMessages_]
   Int_t           Beam_detector_ToF_F6_fDetMessages_fValue[kMaxBeam_detector_ToF_F6_fDetMessages];   //[Beam_detector_ToF_F6.fDetMessages_]
 //DetEventStation *Beam_detector_ToF_tF3_;
   UInt_t          Beam_detector_ToF_tF3_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_ToF_tF3_TGo4EventElement_fBits;
   TString         Beam_detector_ToF_tF3_TGo4EventElement_fName;
   TString         Beam_detector_ToF_tF3_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_ToF_tF3_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_ToF_tF3_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_ToF_tF3_fDetMessages_;
   UInt_t          Beam_detector_ToF_tF3_fDetMessages_fUniqueID[kMaxBeam_detector_ToF_tF3_fDetMessages];   //[Beam_detector_ToF_tF3.fDetMessages_]
   UInt_t          Beam_detector_ToF_tF3_fDetMessages_fBits[kMaxBeam_detector_ToF_tF3_fDetMessages];   //[Beam_detector_ToF_tF3.fDetMessages_]
   Short_t         Beam_detector_ToF_tF3_fDetMessages_fDetector[kMaxBeam_detector_ToF_tF3_fDetMessages];   //[Beam_detector_ToF_tF3.fDetMessages_]
   Short_t         Beam_detector_ToF_tF3_fDetMessages_fStation[kMaxBeam_detector_ToF_tF3_fDetMessages];   //[Beam_detector_ToF_tF3.fDetMessages_]
   Int_t           Beam_detector_ToF_tF3_fDetMessages_fStChannel[kMaxBeam_detector_ToF_tF3_fDetMessages];   //[Beam_detector_ToF_tF3.fDetMessages_]
   Int_t           Beam_detector_ToF_tF3_fDetMessages_fValue[kMaxBeam_detector_ToF_tF3_fDetMessages];   //[Beam_detector_ToF_tF3.fDetMessages_]
 //DetEventStation *Beam_detector_ToF_tF5_;
   UInt_t          Beam_detector_ToF_tF5_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_ToF_tF5_TGo4EventElement_fBits;
   TString         Beam_detector_ToF_tF5_TGo4EventElement_fName;
   TString         Beam_detector_ToF_tF5_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_ToF_tF5_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_ToF_tF5_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_ToF_tF5_fDetMessages_;
   UInt_t          Beam_detector_ToF_tF5_fDetMessages_fUniqueID[kMaxBeam_detector_ToF_tF5_fDetMessages];   //[Beam_detector_ToF_tF5.fDetMessages_]
   UInt_t          Beam_detector_ToF_tF5_fDetMessages_fBits[kMaxBeam_detector_ToF_tF5_fDetMessages];   //[Beam_detector_ToF_tF5.fDetMessages_]
   Short_t         Beam_detector_ToF_tF5_fDetMessages_fDetector[kMaxBeam_detector_ToF_tF5_fDetMessages];   //[Beam_detector_ToF_tF5.fDetMessages_]
   Short_t         Beam_detector_ToF_tF5_fDetMessages_fStation[kMaxBeam_detector_ToF_tF5_fDetMessages];   //[Beam_detector_ToF_tF5.fDetMessages_]
   Int_t           Beam_detector_ToF_tF5_fDetMessages_fStChannel[kMaxBeam_detector_ToF_tF5_fDetMessages];   //[Beam_detector_ToF_tF5.fDetMessages_]
   Int_t           Beam_detector_ToF_tF5_fDetMessages_fValue[kMaxBeam_detector_ToF_tF5_fDetMessages];   //[Beam_detector_ToF_tF5.fDetMessages_]
 //DetEventStation *Beam_detector_ToF_tF6_;
   UInt_t          Beam_detector_ToF_tF6_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_ToF_tF6_TGo4EventElement_fBits;
   TString         Beam_detector_ToF_tF6_TGo4EventElement_fName;
   TString         Beam_detector_ToF_tF6_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_ToF_tF6_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_ToF_tF6_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_ToF_tF6_fDetMessages_;
   UInt_t          Beam_detector_ToF_tF6_fDetMessages_fUniqueID[kMaxBeam_detector_ToF_tF6_fDetMessages];   //[Beam_detector_ToF_tF6.fDetMessages_]
   UInt_t          Beam_detector_ToF_tF6_fDetMessages_fBits[kMaxBeam_detector_ToF_tF6_fDetMessages];   //[Beam_detector_ToF_tF6.fDetMessages_]
   Short_t         Beam_detector_ToF_tF6_fDetMessages_fDetector[kMaxBeam_detector_ToF_tF6_fDetMessages];   //[Beam_detector_ToF_tF6.fDetMessages_]
   Short_t         Beam_detector_ToF_tF6_fDetMessages_fStation[kMaxBeam_detector_ToF_tF6_fDetMessages];   //[Beam_detector_ToF_tF6.fDetMessages_]
   Int_t           Beam_detector_ToF_tF6_fDetMessages_fStChannel[kMaxBeam_detector_ToF_tF6_fDetMessages];   //[Beam_detector_ToF_tF6.fDetMessages_]
   Int_t           Beam_detector_ToF_tF6_fDetMessages_fValue[kMaxBeam_detector_ToF_tF6_fDetMessages];   //[Beam_detector_ToF_tF6.fDetMessages_]
 //DetEventDetector *Ignore_;
   UInt_t          Ignore_TGo4CompositeEvent_fUniqueID;
   UInt_t          Ignore_TGo4CompositeEvent_fBits;
   TString         Ignore_TGo4CompositeEvent_fName;
   TString         Ignore_TGo4CompositeEvent_fTitle;
   Bool_t          Ignore_TGo4CompositeEvent_fbIsValid;
   Short_t         Ignore_TGo4CompositeEvent_fIdentifier;
   Short_t         Ignore_TGo4CompositeEvent_fNElements;
   Short_t         Ignore_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *Ignore_Ignore_;
   UInt_t          Ignore_Ignore_TGo4EventElement_fUniqueID;
   UInt_t          Ignore_Ignore_TGo4EventElement_fBits;
   TString         Ignore_Ignore_TGo4EventElement_fName;
   TString         Ignore_Ignore_TGo4EventElement_fTitle;
   Bool_t          Ignore_Ignore_TGo4EventElement_fbIsValid;
   Short_t         Ignore_Ignore_TGo4EventElement_fIdentifier;
   Int_t           Ignore_Ignore_fDetMessages_;
   UInt_t          Ignore_Ignore_fDetMessages_fUniqueID[kMaxIgnore_Ignore_fDetMessages];   //[Ignore_Ignore.fDetMessages_]
   UInt_t          Ignore_Ignore_fDetMessages_fBits[kMaxIgnore_Ignore_fDetMessages];   //[Ignore_Ignore.fDetMessages_]
   Short_t         Ignore_Ignore_fDetMessages_fDetector[kMaxIgnore_Ignore_fDetMessages];   //[Ignore_Ignore.fDetMessages_]
   Short_t         Ignore_Ignore_fDetMessages_fStation[kMaxIgnore_Ignore_fDetMessages];   //[Ignore_Ignore.fDetMessages_]
   Int_t           Ignore_Ignore_fDetMessages_fStChannel[kMaxIgnore_Ignore_fDetMessages];   //[Ignore_Ignore.fDetMessages_]
   Int_t           Ignore_Ignore_fDetMessages_fValue[kMaxIgnore_Ignore_fDetMessages];   //[Ignore_Ignore.fDetMessages_]
 //DetEventDetector *Beam_detector_MWPC_;
   UInt_t          Beam_detector_MWPC_TGo4CompositeEvent_fUniqueID;
   UInt_t          Beam_detector_MWPC_TGo4CompositeEvent_fBits;
   TString         Beam_detector_MWPC_TGo4CompositeEvent_fName;
   TString         Beam_detector_MWPC_TGo4CompositeEvent_fTitle;
   Bool_t          Beam_detector_MWPC_TGo4CompositeEvent_fbIsValid;
   Short_t         Beam_detector_MWPC_TGo4CompositeEvent_fIdentifier;
   Short_t         Beam_detector_MWPC_TGo4CompositeEvent_fNElements;
   Short_t         Beam_detector_MWPC_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *Beam_detector_MWPC_tMWPC_;
   UInt_t          Beam_detector_MWPC_tMWPC_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_MWPC_tMWPC_TGo4EventElement_fBits;
   TString         Beam_detector_MWPC_tMWPC_TGo4EventElement_fName;
   TString         Beam_detector_MWPC_tMWPC_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_MWPC_tMWPC_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_MWPC_tMWPC_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_MWPC_tMWPC_fDetMessages_;
   UInt_t          Beam_detector_MWPC_tMWPC_fDetMessages_fUniqueID[kMaxBeam_detector_MWPC_tMWPC_fDetMessages];   //[Beam_detector_MWPC_tMWPC.fDetMessages_]
   UInt_t          Beam_detector_MWPC_tMWPC_fDetMessages_fBits[kMaxBeam_detector_MWPC_tMWPC_fDetMessages];   //[Beam_detector_MWPC_tMWPC.fDetMessages_]
   Short_t         Beam_detector_MWPC_tMWPC_fDetMessages_fDetector[kMaxBeam_detector_MWPC_tMWPC_fDetMessages];   //[Beam_detector_MWPC_tMWPC.fDetMessages_]
   Short_t         Beam_detector_MWPC_tMWPC_fDetMessages_fStation[kMaxBeam_detector_MWPC_tMWPC_fDetMessages];   //[Beam_detector_MWPC_tMWPC.fDetMessages_]
   Int_t           Beam_detector_MWPC_tMWPC_fDetMessages_fStChannel[kMaxBeam_detector_MWPC_tMWPC_fDetMessages];   //[Beam_detector_MWPC_tMWPC.fDetMessages_]
   Int_t           Beam_detector_MWPC_tMWPC_fDetMessages_fValue[kMaxBeam_detector_MWPC_tMWPC_fDetMessages];   //[Beam_detector_MWPC_tMWPC.fDetMessages_]
 //DetEventStation *Beam_detector_MWPC_MWPC1_;
   UInt_t          Beam_detector_MWPC_MWPC1_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_MWPC_MWPC1_TGo4EventElement_fBits;
   TString         Beam_detector_MWPC_MWPC1_TGo4EventElement_fName;
   TString         Beam_detector_MWPC_MWPC1_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_MWPC_MWPC1_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_MWPC_MWPC1_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_MWPC_MWPC1_fDetMessages_;
   UInt_t          Beam_detector_MWPC_MWPC1_fDetMessages_fUniqueID[kMaxBeam_detector_MWPC_MWPC1_fDetMessages];   //[Beam_detector_MWPC_MWPC1.fDetMessages_]
   UInt_t          Beam_detector_MWPC_MWPC1_fDetMessages_fBits[kMaxBeam_detector_MWPC_MWPC1_fDetMessages];   //[Beam_detector_MWPC_MWPC1.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC1_fDetMessages_fDetector[kMaxBeam_detector_MWPC_MWPC1_fDetMessages];   //[Beam_detector_MWPC_MWPC1.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC1_fDetMessages_fStation[kMaxBeam_detector_MWPC_MWPC1_fDetMessages];   //[Beam_detector_MWPC_MWPC1.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC1_fDetMessages_fStChannel[kMaxBeam_detector_MWPC_MWPC1_fDetMessages];   //[Beam_detector_MWPC_MWPC1.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC1_fDetMessages_fValue[kMaxBeam_detector_MWPC_MWPC1_fDetMessages];   //[Beam_detector_MWPC_MWPC1.fDetMessages_]
 //DetEventStation *Beam_detector_MWPC_MWPC2_;
   UInt_t          Beam_detector_MWPC_MWPC2_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_MWPC_MWPC2_TGo4EventElement_fBits;
   TString         Beam_detector_MWPC_MWPC2_TGo4EventElement_fName;
   TString         Beam_detector_MWPC_MWPC2_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_MWPC_MWPC2_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_MWPC_MWPC2_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_MWPC_MWPC2_fDetMessages_;
   UInt_t          Beam_detector_MWPC_MWPC2_fDetMessages_fUniqueID[kMaxBeam_detector_MWPC_MWPC2_fDetMessages];   //[Beam_detector_MWPC_MWPC2.fDetMessages_]
   UInt_t          Beam_detector_MWPC_MWPC2_fDetMessages_fBits[kMaxBeam_detector_MWPC_MWPC2_fDetMessages];   //[Beam_detector_MWPC_MWPC2.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC2_fDetMessages_fDetector[kMaxBeam_detector_MWPC_MWPC2_fDetMessages];   //[Beam_detector_MWPC_MWPC2.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC2_fDetMessages_fStation[kMaxBeam_detector_MWPC_MWPC2_fDetMessages];   //[Beam_detector_MWPC_MWPC2.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC2_fDetMessages_fStChannel[kMaxBeam_detector_MWPC_MWPC2_fDetMessages];   //[Beam_detector_MWPC_MWPC2.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC2_fDetMessages_fValue[kMaxBeam_detector_MWPC_MWPC2_fDetMessages];   //[Beam_detector_MWPC_MWPC2.fDetMessages_]
 //DetEventStation *Beam_detector_MWPC_MWPC3_;
   UInt_t          Beam_detector_MWPC_MWPC3_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_MWPC_MWPC3_TGo4EventElement_fBits;
   TString         Beam_detector_MWPC_MWPC3_TGo4EventElement_fName;
   TString         Beam_detector_MWPC_MWPC3_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_MWPC_MWPC3_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_MWPC_MWPC3_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_MWPC_MWPC3_fDetMessages_;
   UInt_t          Beam_detector_MWPC_MWPC3_fDetMessages_fUniqueID[kMaxBeam_detector_MWPC_MWPC3_fDetMessages];   //[Beam_detector_MWPC_MWPC3.fDetMessages_]
   UInt_t          Beam_detector_MWPC_MWPC3_fDetMessages_fBits[kMaxBeam_detector_MWPC_MWPC3_fDetMessages];   //[Beam_detector_MWPC_MWPC3.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC3_fDetMessages_fDetector[kMaxBeam_detector_MWPC_MWPC3_fDetMessages];   //[Beam_detector_MWPC_MWPC3.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC3_fDetMessages_fStation[kMaxBeam_detector_MWPC_MWPC3_fDetMessages];   //[Beam_detector_MWPC_MWPC3.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC3_fDetMessages_fStChannel[kMaxBeam_detector_MWPC_MWPC3_fDetMessages];   //[Beam_detector_MWPC_MWPC3.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC3_fDetMessages_fValue[kMaxBeam_detector_MWPC_MWPC3_fDetMessages];   //[Beam_detector_MWPC_MWPC3.fDetMessages_]
 //DetEventStation *Beam_detector_MWPC_MWPC4_;
   UInt_t          Beam_detector_MWPC_MWPC4_TGo4EventElement_fUniqueID;
   UInt_t          Beam_detector_MWPC_MWPC4_TGo4EventElement_fBits;
   TString         Beam_detector_MWPC_MWPC4_TGo4EventElement_fName;
   TString         Beam_detector_MWPC_MWPC4_TGo4EventElement_fTitle;
   Bool_t          Beam_detector_MWPC_MWPC4_TGo4EventElement_fbIsValid;
   Short_t         Beam_detector_MWPC_MWPC4_TGo4EventElement_fIdentifier;
   Int_t           Beam_detector_MWPC_MWPC4_fDetMessages_;
   UInt_t          Beam_detector_MWPC_MWPC4_fDetMessages_fUniqueID[kMaxBeam_detector_MWPC_MWPC4_fDetMessages];   //[Beam_detector_MWPC_MWPC4.fDetMessages_]
   UInt_t          Beam_detector_MWPC_MWPC4_fDetMessages_fBits[kMaxBeam_detector_MWPC_MWPC4_fDetMessages];   //[Beam_detector_MWPC_MWPC4.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC4_fDetMessages_fDetector[kMaxBeam_detector_MWPC_MWPC4_fDetMessages];   //[Beam_detector_MWPC_MWPC4.fDetMessages_]
   Short_t         Beam_detector_MWPC_MWPC4_fDetMessages_fStation[kMaxBeam_detector_MWPC_MWPC4_fDetMessages];   //[Beam_detector_MWPC_MWPC4.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC4_fDetMessages_fStChannel[kMaxBeam_detector_MWPC_MWPC4_fDetMessages];   //[Beam_detector_MWPC_MWPC4.fDetMessages_]
   Int_t           Beam_detector_MWPC_MWPC4_fDetMessages_fValue[kMaxBeam_detector_MWPC_MWPC4_fDetMessages];   //[Beam_detector_MWPC_MWPC4.fDetMessages_]
 //DetEventDetector *Neutron_detector_;
   UInt_t          Neutron_detector_TGo4CompositeEvent_fUniqueID;
   UInt_t          Neutron_detector_TGo4CompositeEvent_fBits;
   TString         Neutron_detector_TGo4CompositeEvent_fName;
   TString         Neutron_detector_TGo4CompositeEvent_fTitle;
   Bool_t          Neutron_detector_TGo4CompositeEvent_fbIsValid;
   Short_t         Neutron_detector_TGo4CompositeEvent_fIdentifier;
   Short_t         Neutron_detector_TGo4CompositeEvent_fNElements;
   Short_t         Neutron_detector_TGo4CompositeEvent_fMaxIndex;
 //DetEventStation *Neutron_detector_neutTDC_;
   UInt_t          Neutron_detector_neutTDC_TGo4EventElement_fUniqueID;
   UInt_t          Neutron_detector_neutTDC_TGo4EventElement_fBits;
   TString         Neutron_detector_neutTDC_TGo4EventElement_fName;
   TString         Neutron_detector_neutTDC_TGo4EventElement_fTitle;
   Bool_t          Neutron_detector_neutTDC_TGo4EventElement_fbIsValid;
   Short_t         Neutron_detector_neutTDC_TGo4EventElement_fIdentifier;
   Int_t           Neutron_detector_neutTDC_fDetMessages_;
   UInt_t          Neutron_detector_neutTDC_fDetMessages_fUniqueID[kMaxNeutron_detector_neutTDC_fDetMessages];   //[Neutron_detector_neutTDC.fDetMessages_]
   UInt_t          Neutron_detector_neutTDC_fDetMessages_fBits[kMaxNeutron_detector_neutTDC_fDetMessages];   //[Neutron_detector_neutTDC.fDetMessages_]
   Short_t         Neutron_detector_neutTDC_fDetMessages_fDetector[kMaxNeutron_detector_neutTDC_fDetMessages];   //[Neutron_detector_neutTDC.fDetMessages_]
   Short_t         Neutron_detector_neutTDC_fDetMessages_fStation[kMaxNeutron_detector_neutTDC_fDetMessages];   //[Neutron_detector_neutTDC.fDetMessages_]
   Int_t           Neutron_detector_neutTDC_fDetMessages_fStChannel[kMaxNeutron_detector_neutTDC_fDetMessages];   //[Neutron_detector_neutTDC.fDetMessages_]
   Int_t           Neutron_detector_neutTDC_fDetMessages_fValue[kMaxNeutron_detector_neutTDC_fDetMessages];   //[Neutron_detector_neutTDC.fDetMessages_]
 //DetEventStation *Neutron_detector_neutAmp_;
   UInt_t          Neutron_detector_neutAmp_TGo4EventElement_fUniqueID;
   UInt_t          Neutron_detector_neutAmp_TGo4EventElement_fBits;
   TString         Neutron_detector_neutAmp_TGo4EventElement_fName;
   TString         Neutron_detector_neutAmp_TGo4EventElement_fTitle;
   Bool_t          Neutron_detector_neutAmp_TGo4EventElement_fbIsValid;
   Short_t         Neutron_detector_neutAmp_TGo4EventElement_fIdentifier;
   Int_t           Neutron_detector_neutAmp_fDetMessages_;
   UInt_t          Neutron_detector_neutAmp_fDetMessages_fUniqueID[kMaxNeutron_detector_neutAmp_fDetMessages];   //[Neutron_detector_neutAmp.fDetMessages_]
   UInt_t          Neutron_detector_neutAmp_fDetMessages_fBits[kMaxNeutron_detector_neutAmp_fDetMessages];   //[Neutron_detector_neutAmp.fDetMessages_]
   Short_t         Neutron_detector_neutAmp_fDetMessages_fDetector[kMaxNeutron_detector_neutAmp_fDetMessages];   //[Neutron_detector_neutAmp.fDetMessages_]
   Short_t         Neutron_detector_neutAmp_fDetMessages_fStation[kMaxNeutron_detector_neutAmp_fDetMessages];   //[Neutron_detector_neutAmp.fDetMessages_]
   Int_t           Neutron_detector_neutAmp_fDetMessages_fStChannel[kMaxNeutron_detector_neutAmp_fDetMessages];   //[Neutron_detector_neutAmp.fDetMessages_]
   Int_t           Neutron_detector_neutAmp_fDetMessages_fValue[kMaxNeutron_detector_neutAmp_fDetMessages];   //[Neutron_detector_neutAmp.fDetMessages_]
 //DetEventStation *Neutron_detector_neutTAC_;
   UInt_t          Neutron_detector_neutTAC_TGo4EventElement_fUniqueID;
   UInt_t          Neutron_detector_neutTAC_TGo4EventElement_fBits;
   TString         Neutron_detector_neutTAC_TGo4EventElement_fName;
   TString         Neutron_detector_neutTAC_TGo4EventElement_fTitle;
   Bool_t          Neutron_detector_neutTAC_TGo4EventElement_fbIsValid;
   Short_t         Neutron_detector_neutTAC_TGo4EventElement_fIdentifier;
   Int_t           Neutron_detector_neutTAC_fDetMessages_;
   UInt_t          Neutron_detector_neutTAC_fDetMessages_fUniqueID[kMaxNeutron_detector_neutTAC_fDetMessages];   //[Neutron_detector_neutTAC.fDetMessages_]
   UInt_t          Neutron_detector_neutTAC_fDetMessages_fBits[kMaxNeutron_detector_neutTAC_fDetMessages];   //[Neutron_detector_neutTAC.fDetMessages_]
   Short_t         Neutron_detector_neutTAC_fDetMessages_fDetector[kMaxNeutron_detector_neutTAC_fDetMessages];   //[Neutron_detector_neutTAC.fDetMessages_]
   Short_t         Neutron_detector_neutTAC_fDetMessages_fStation[kMaxNeutron_detector_neutTAC_fDetMessages];   //[Neutron_detector_neutTAC.fDetMessages_]
   Int_t           Neutron_detector_neutTAC_fDetMessages_fStChannel[kMaxNeutron_detector_neutTAC_fDetMessages];   //[Neutron_detector_neutTAC.fDetMessages_]
   Int_t           Neutron_detector_neutTAC_fDetMessages_fValue[kMaxNeutron_detector_neutTAC_fDetMessages];   //[Neutron_detector_neutTAC.fDetMessages_]

   // List of branches
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fName;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_DetEventFull1_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_DetEventCommon_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_DetEventCommon_TGo4EventElement_fBits;   //!
   TBranch        *b_DetEventCommon_TGo4EventElement_fName;   //!
   TBranch        *b_DetEventCommon_TGo4EventElement_fTitle;   //!
   TBranch        *b_DetEventCommon_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_DetEventCommon_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_DetEventCommon_trigger;   //!
   TBranch        *b_DetEventCommon_scaler;   //!
   TBranch        *b_DetEventCommon_mtime;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fName;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_DAQ_status_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_DAQ_status_mtime_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_DAQ_status_mtime_TGo4EventElement_fBits;   //!
   TBranch        *b_DAQ_status_mtime_TGo4EventElement_fName;   //!
   TBranch        *b_DAQ_status_mtime_TGo4EventElement_fTitle;   //!
   TBranch        *b_DAQ_status_mtime_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_DAQ_status_mtime_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_fUniqueID;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_fBits;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_fDetector;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_fStation;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_fStChannel;   //!
   TBranch        *b_DAQ_status_mtime_fDetMessages_fValue;   //!
   TBranch        *b_DAQ_status_scalers_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_DAQ_status_scalers_TGo4EventElement_fBits;   //!
   TBranch        *b_DAQ_status_scalers_TGo4EventElement_fName;   //!
   TBranch        *b_DAQ_status_scalers_TGo4EventElement_fTitle;   //!
   TBranch        *b_DAQ_status_scalers_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_DAQ_status_scalers_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_fUniqueID;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_fBits;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_fDetector;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_fStation;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_fStChannel;   //!
   TBranch        *b_DAQ_status_scalers_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fName;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_Left_telescope_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_Left_telescope_SQX_L_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_SQX_L_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_SQX_L_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_SQX_L_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_SQX_L_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_SQX_L_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_SQX_L_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_SQY_L_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_SQY_L_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_SQY_L_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_SQY_L_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_SQY_L_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_SQY_L_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_SQY_L_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_CsI_L_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_CsI_L_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_CsI_L_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_CsI_L_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_CsI_L_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_CsI_L_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_CsI_L_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_SQ20_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_SQ20_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_SQ20_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_SQ20_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_SQ20_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_SQ20_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_SQ20_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_tSQ20_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_tSQ20_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_tSQ20_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_tSQ20_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_tSQ20_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_tSQ20_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_tSQ20_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_tSQX_L_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_tSQX_L_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_tSQX_L_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_tSQX_L_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_tSQX_L_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_tSQX_L_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_tSQX_L_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_tSQY_L_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_tSQY_L_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_tSQY_L_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_tSQY_L_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_tSQY_L_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_tSQY_L_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_tSQY_L_fDetMessages_fValue;   //!
   TBranch        *b_Left_telescope_tCsI_L_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Left_telescope_tCsI_L_TGo4EventElement_fBits;   //!
   TBranch        *b_Left_telescope_tCsI_L_TGo4EventElement_fName;   //!
   TBranch        *b_Left_telescope_tCsI_L_TGo4EventElement_fTitle;   //!
   TBranch        *b_Left_telescope_tCsI_L_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Left_telescope_tCsI_L_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_fUniqueID;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_fBits;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_fDetector;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_fStation;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_fStChannel;   //!
   TBranch        *b_Left_telescope_tCsI_L_fDetMessages_fValue;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fName;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_Right_telescope_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_Right_telescope_SQX_R_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Right_telescope_SQX_R_TGo4EventElement_fBits;   //!
   TBranch        *b_Right_telescope_SQX_R_TGo4EventElement_fName;   //!
   TBranch        *b_Right_telescope_SQX_R_TGo4EventElement_fTitle;   //!
   TBranch        *b_Right_telescope_SQX_R_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Right_telescope_SQX_R_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_fUniqueID;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_fBits;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_fDetector;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_fStation;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_fStChannel;   //!
   TBranch        *b_Right_telescope_SQX_R_fDetMessages_fValue;   //!
   TBranch        *b_Right_telescope_SQY_R_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Right_telescope_SQY_R_TGo4EventElement_fBits;   //!
   TBranch        *b_Right_telescope_SQY_R_TGo4EventElement_fName;   //!
   TBranch        *b_Right_telescope_SQY_R_TGo4EventElement_fTitle;   //!
   TBranch        *b_Right_telescope_SQY_R_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Right_telescope_SQY_R_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_fUniqueID;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_fBits;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_fDetector;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_fStation;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_fStChannel;   //!
   TBranch        *b_Right_telescope_SQY_R_fDetMessages_fValue;   //!
   TBranch        *b_Right_telescope_CsI_R_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Right_telescope_CsI_R_TGo4EventElement_fBits;   //!
   TBranch        *b_Right_telescope_CsI_R_TGo4EventElement_fName;   //!
   TBranch        *b_Right_telescope_CsI_R_TGo4EventElement_fTitle;   //!
   TBranch        *b_Right_telescope_CsI_R_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Right_telescope_CsI_R_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_fUniqueID;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_fBits;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_fDetector;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_fStation;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_fStChannel;   //!
   TBranch        *b_Right_telescope_CsI_R_fDetMessages_fValue;   //!
   TBranch        *b_Right_telescope_tSQX_R_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Right_telescope_tSQX_R_TGo4EventElement_fBits;   //!
   TBranch        *b_Right_telescope_tSQX_R_TGo4EventElement_fName;   //!
   TBranch        *b_Right_telescope_tSQX_R_TGo4EventElement_fTitle;   //!
   TBranch        *b_Right_telescope_tSQX_R_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Right_telescope_tSQX_R_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_fUniqueID;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_fBits;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_fDetector;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_fStation;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_fStChannel;   //!
   TBranch        *b_Right_telescope_tSQX_R_fDetMessages_fValue;   //!
   TBranch        *b_Right_telescope_tSQY_R_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Right_telescope_tSQY_R_TGo4EventElement_fBits;   //!
   TBranch        *b_Right_telescope_tSQY_R_TGo4EventElement_fName;   //!
   TBranch        *b_Right_telescope_tSQY_R_TGo4EventElement_fTitle;   //!
   TBranch        *b_Right_telescope_tSQY_R_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Right_telescope_tSQY_R_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_fUniqueID;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_fBits;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_fDetector;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_fStation;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_fStChannel;   //!
   TBranch        *b_Right_telescope_tSQY_R_fDetMessages_fValue;   //!
   TBranch        *b_Right_telescope_tCsI_R_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Right_telescope_tCsI_R_TGo4EventElement_fBits;   //!
   TBranch        *b_Right_telescope_tCsI_R_TGo4EventElement_fName;   //!
   TBranch        *b_Right_telescope_tCsI_R_TGo4EventElement_fTitle;   //!
   TBranch        *b_Right_telescope_tCsI_R_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Right_telescope_tCsI_R_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_fUniqueID;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_fBits;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_fDetector;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_fStation;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_fStChannel;   //!
   TBranch        *b_Right_telescope_tCsI_R_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fName;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_Beam_detector_ToF_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_Beam_detector_ToF_F3_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_F3_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_ToF_F3_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_ToF_F3_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_F3_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_F3_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_ToF_F3_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_ToF_F5_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_F5_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_ToF_F5_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_ToF_F5_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_F5_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_F5_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_ToF_F5_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_ToF_F6_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_F6_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_ToF_F6_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_ToF_F6_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_F6_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_F6_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_ToF_F6_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_ToF_tF3_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_tF3_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_ToF_tF3_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_ToF_tF3_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_tF3_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_tF3_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_ToF_tF3_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_ToF_tF5_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_tF5_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_ToF_tF5_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_ToF_tF5_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_tF5_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_tF5_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_ToF_tF5_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_ToF_tF6_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_tF6_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_ToF_tF6_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_ToF_tF6_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_ToF_tF6_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_ToF_tF6_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_ToF_tF6_fDetMessages_fValue;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fName;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_Ignore_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_Ignore_Ignore_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Ignore_Ignore_TGo4EventElement_fBits;   //!
   TBranch        *b_Ignore_Ignore_TGo4EventElement_fName;   //!
   TBranch        *b_Ignore_Ignore_TGo4EventElement_fTitle;   //!
   TBranch        *b_Ignore_Ignore_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Ignore_Ignore_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_fUniqueID;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_fBits;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_fDetector;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_fStation;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_fStChannel;   //!
   TBranch        *b_Ignore_Ignore_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fName;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_Beam_detector_MWPC_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_MWPC_tMWPC_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC1_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC2_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC3_fDetMessages_fValue;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fName;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fTitle;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_fUniqueID;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_fBits;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_fDetector;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_fStation;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_fStChannel;   //!
   TBranch        *b_Beam_detector_MWPC_MWPC4_fDetMessages_fValue;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fUniqueID;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fBits;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fName;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fTitle;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fbIsValid;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fIdentifier;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fNElements;   //!
   TBranch        *b_Neutron_detector_TGo4CompositeEvent_fMaxIndex;   //!
   TBranch        *b_Neutron_detector_neutTDC_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Neutron_detector_neutTDC_TGo4EventElement_fBits;   //!
   TBranch        *b_Neutron_detector_neutTDC_TGo4EventElement_fName;   //!
   TBranch        *b_Neutron_detector_neutTDC_TGo4EventElement_fTitle;   //!
   TBranch        *b_Neutron_detector_neutTDC_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Neutron_detector_neutTDC_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_fUniqueID;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_fBits;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_fDetector;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_fStation;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_fStChannel;   //!
   TBranch        *b_Neutron_detector_neutTDC_fDetMessages_fValue;   //!
   TBranch        *b_Neutron_detector_neutAmp_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Neutron_detector_neutAmp_TGo4EventElement_fBits;   //!
   TBranch        *b_Neutron_detector_neutAmp_TGo4EventElement_fName;   //!
   TBranch        *b_Neutron_detector_neutAmp_TGo4EventElement_fTitle;   //!
   TBranch        *b_Neutron_detector_neutAmp_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Neutron_detector_neutAmp_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_fUniqueID;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_fBits;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_fDetector;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_fStation;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_fStChannel;   //!
   TBranch        *b_Neutron_detector_neutAmp_fDetMessages_fValue;   //!
   TBranch        *b_Neutron_detector_neutTAC_TGo4EventElement_fUniqueID;   //!
   TBranch        *b_Neutron_detector_neutTAC_TGo4EventElement_fBits;   //!
   TBranch        *b_Neutron_detector_neutTAC_TGo4EventElement_fName;   //!
   TBranch        *b_Neutron_detector_neutTAC_TGo4EventElement_fTitle;   //!
   TBranch        *b_Neutron_detector_neutTAC_TGo4EventElement_fbIsValid;   //!
   TBranch        *b_Neutron_detector_neutTAC_TGo4EventElement_fIdentifier;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_fUniqueID;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_fBits;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_fDetector;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_fStation;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_fStChannel;   //!
   TBranch        *b_Neutron_detector_neutTAC_fDetMessages_fValue;   //!


   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fUniqueID", &DetEventFull1_TGo4CompositeEvent_fUniqueID, &b_DetEventFull1_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fBits", &DetEventFull1_TGo4CompositeEvent_fBits, &b_DetEventFull1_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fName", &DetEventFull1_TGo4CompositeEvent_fName, &b_DetEventFull1_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fTitle", &DetEventFull1_TGo4CompositeEvent_fTitle, &b_DetEventFull1_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fbIsValid", &DetEventFull1_TGo4CompositeEvent_fbIsValid, &b_DetEventFull1_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fIdentifier", &DetEventFull1_TGo4CompositeEvent_fIdentifier, &b_DetEventFull1_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fNElements", &DetEventFull1_TGo4CompositeEvent_fNElements, &b_DetEventFull1_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("DetEventFull1.TGo4CompositeEvent.fMaxIndex", &DetEventFull1_TGo4CompositeEvent_fMaxIndex, &b_DetEventFull1_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("DetEventCommon.TGo4EventElement.fUniqueID", &DetEventCommon_TGo4EventElement_fUniqueID, &b_DetEventCommon_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("DetEventCommon.TGo4EventElement.fBits", &DetEventCommon_TGo4EventElement_fBits, &b_DetEventCommon_TGo4EventElement_fBits);
   fChain->SetBranchAddress("DetEventCommon.TGo4EventElement.fName", &DetEventCommon_TGo4EventElement_fName, &b_DetEventCommon_TGo4EventElement_fName);
   fChain->SetBranchAddress("DetEventCommon.TGo4EventElement.fTitle", &DetEventCommon_TGo4EventElement_fTitle, &b_DetEventCommon_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("DetEventCommon.TGo4EventElement.fbIsValid", &DetEventCommon_TGo4EventElement_fbIsValid, &b_DetEventCommon_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("DetEventCommon.TGo4EventElement.fIdentifier", &DetEventCommon_TGo4EventElement_fIdentifier, &b_DetEventCommon_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("DetEventCommon.trigger", &DetEventCommon_trigger, &b_DetEventCommon_trigger);
   fChain->SetBranchAddress("DetEventCommon.scaler[16]", DetEventCommon_scaler, &b_DetEventCommon_scaler);
   fChain->SetBranchAddress("DetEventCommon.mtime[2]", DetEventCommon_mtime, &b_DetEventCommon_mtime);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fUniqueID", &DAQ_status_TGo4CompositeEvent_fUniqueID, &b_DAQ_status_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fBits", &DAQ_status_TGo4CompositeEvent_fBits, &b_DAQ_status_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fName", &DAQ_status_TGo4CompositeEvent_fName, &b_DAQ_status_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fTitle", &DAQ_status_TGo4CompositeEvent_fTitle, &b_DAQ_status_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fbIsValid", &DAQ_status_TGo4CompositeEvent_fbIsValid, &b_DAQ_status_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fIdentifier", &DAQ_status_TGo4CompositeEvent_fIdentifier, &b_DAQ_status_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fNElements", &DAQ_status_TGo4CompositeEvent_fNElements, &b_DAQ_status_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("DAQ_status.TGo4CompositeEvent.fMaxIndex", &DAQ_status_TGo4CompositeEvent_fMaxIndex, &b_DAQ_status_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("DAQ_status_mtime.TGo4EventElement.fUniqueID", &DAQ_status_mtime_TGo4EventElement_fUniqueID, &b_DAQ_status_mtime_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("DAQ_status_mtime.TGo4EventElement.fBits", &DAQ_status_mtime_TGo4EventElement_fBits, &b_DAQ_status_mtime_TGo4EventElement_fBits);
   fChain->SetBranchAddress("DAQ_status_mtime.TGo4EventElement.fName", &DAQ_status_mtime_TGo4EventElement_fName, &b_DAQ_status_mtime_TGo4EventElement_fName);
   fChain->SetBranchAddress("DAQ_status_mtime.TGo4EventElement.fTitle", &DAQ_status_mtime_TGo4EventElement_fTitle, &b_DAQ_status_mtime_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("DAQ_status_mtime.TGo4EventElement.fbIsValid", &DAQ_status_mtime_TGo4EventElement_fbIsValid, &b_DAQ_status_mtime_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("DAQ_status_mtime.TGo4EventElement.fIdentifier", &DAQ_status_mtime_TGo4EventElement_fIdentifier, &b_DAQ_status_mtime_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages", &DAQ_status_mtime_fDetMessages_, &b_DAQ_status_mtime_fDetMessages_);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages.fUniqueID", &DAQ_status_mtime_fDetMessages_fUniqueID, &b_DAQ_status_mtime_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages.fBits", &DAQ_status_mtime_fDetMessages_fBits, &b_DAQ_status_mtime_fDetMessages_fBits);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages.fDetector", &DAQ_status_mtime_fDetMessages_fDetector, &b_DAQ_status_mtime_fDetMessages_fDetector);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages.fStation", &DAQ_status_mtime_fDetMessages_fStation, &b_DAQ_status_mtime_fDetMessages_fStation);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages.fStChannel", &DAQ_status_mtime_fDetMessages_fStChannel, &b_DAQ_status_mtime_fDetMessages_fStChannel);
   fChain->SetBranchAddress("DAQ_status_mtime.fDetMessages.fValue", &DAQ_status_mtime_fDetMessages_fValue, &b_DAQ_status_mtime_fDetMessages_fValue);
   fChain->SetBranchAddress("DAQ_status_scalers.TGo4EventElement.fUniqueID", &DAQ_status_scalers_TGo4EventElement_fUniqueID, &b_DAQ_status_scalers_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("DAQ_status_scalers.TGo4EventElement.fBits", &DAQ_status_scalers_TGo4EventElement_fBits, &b_DAQ_status_scalers_TGo4EventElement_fBits);
   fChain->SetBranchAddress("DAQ_status_scalers.TGo4EventElement.fName", &DAQ_status_scalers_TGo4EventElement_fName, &b_DAQ_status_scalers_TGo4EventElement_fName);
   fChain->SetBranchAddress("DAQ_status_scalers.TGo4EventElement.fTitle", &DAQ_status_scalers_TGo4EventElement_fTitle, &b_DAQ_status_scalers_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("DAQ_status_scalers.TGo4EventElement.fbIsValid", &DAQ_status_scalers_TGo4EventElement_fbIsValid, &b_DAQ_status_scalers_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("DAQ_status_scalers.TGo4EventElement.fIdentifier", &DAQ_status_scalers_TGo4EventElement_fIdentifier, &b_DAQ_status_scalers_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages", &DAQ_status_scalers_fDetMessages_, &b_DAQ_status_scalers_fDetMessages_);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages.fUniqueID", &DAQ_status_scalers_fDetMessages_fUniqueID, &b_DAQ_status_scalers_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages.fBits", &DAQ_status_scalers_fDetMessages_fBits, &b_DAQ_status_scalers_fDetMessages_fBits);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages.fDetector", &DAQ_status_scalers_fDetMessages_fDetector, &b_DAQ_status_scalers_fDetMessages_fDetector);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages.fStation", &DAQ_status_scalers_fDetMessages_fStation, &b_DAQ_status_scalers_fDetMessages_fStation);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages.fStChannel", &DAQ_status_scalers_fDetMessages_fStChannel, &b_DAQ_status_scalers_fDetMessages_fStChannel);
   fChain->SetBranchAddress("DAQ_status_scalers.fDetMessages.fValue", &DAQ_status_scalers_fDetMessages_fValue, &b_DAQ_status_scalers_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fUniqueID", &Left_telescope_TGo4CompositeEvent_fUniqueID, &b_Left_telescope_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fBits", &Left_telescope_TGo4CompositeEvent_fBits, &b_Left_telescope_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fName", &Left_telescope_TGo4CompositeEvent_fName, &b_Left_telescope_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fTitle", &Left_telescope_TGo4CompositeEvent_fTitle, &b_Left_telescope_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fbIsValid", &Left_telescope_TGo4CompositeEvent_fbIsValid, &b_Left_telescope_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fIdentifier", &Left_telescope_TGo4CompositeEvent_fIdentifier, &b_Left_telescope_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fNElements", &Left_telescope_TGo4CompositeEvent_fNElements, &b_Left_telescope_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("Left_telescope.TGo4CompositeEvent.fMaxIndex", &Left_telescope_TGo4CompositeEvent_fMaxIndex, &b_Left_telescope_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("Left_telescope_SQX_L.TGo4EventElement.fUniqueID", &Left_telescope_SQX_L_TGo4EventElement_fUniqueID, &b_Left_telescope_SQX_L_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_SQX_L.TGo4EventElement.fBits", &Left_telescope_SQX_L_TGo4EventElement_fBits, &b_Left_telescope_SQX_L_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_SQX_L.TGo4EventElement.fName", &Left_telescope_SQX_L_TGo4EventElement_fName, &b_Left_telescope_SQX_L_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_SQX_L.TGo4EventElement.fTitle", &Left_telescope_SQX_L_TGo4EventElement_fTitle, &b_Left_telescope_SQX_L_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_SQX_L.TGo4EventElement.fbIsValid", &Left_telescope_SQX_L_TGo4EventElement_fbIsValid, &b_Left_telescope_SQX_L_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_SQX_L.TGo4EventElement.fIdentifier", &Left_telescope_SQX_L_TGo4EventElement_fIdentifier, &b_Left_telescope_SQX_L_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages", &Left_telescope_SQX_L_fDetMessages_, &b_Left_telescope_SQX_L_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages.fUniqueID", Left_telescope_SQX_L_fDetMessages_fUniqueID, &b_Left_telescope_SQX_L_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages.fBits", Left_telescope_SQX_L_fDetMessages_fBits, &b_Left_telescope_SQX_L_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages.fDetector", Left_telescope_SQX_L_fDetMessages_fDetector, &b_Left_telescope_SQX_L_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages.fStation", Left_telescope_SQX_L_fDetMessages_fStation, &b_Left_telescope_SQX_L_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages.fStChannel", Left_telescope_SQX_L_fDetMessages_fStChannel, &b_Left_telescope_SQX_L_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_SQX_L.fDetMessages.fValue", Left_telescope_SQX_L_fDetMessages_fValue, &b_Left_telescope_SQX_L_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_SQY_L.TGo4EventElement.fUniqueID", &Left_telescope_SQY_L_TGo4EventElement_fUniqueID, &b_Left_telescope_SQY_L_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_SQY_L.TGo4EventElement.fBits", &Left_telescope_SQY_L_TGo4EventElement_fBits, &b_Left_telescope_SQY_L_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_SQY_L.TGo4EventElement.fName", &Left_telescope_SQY_L_TGo4EventElement_fName, &b_Left_telescope_SQY_L_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_SQY_L.TGo4EventElement.fTitle", &Left_telescope_SQY_L_TGo4EventElement_fTitle, &b_Left_telescope_SQY_L_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_SQY_L.TGo4EventElement.fbIsValid", &Left_telescope_SQY_L_TGo4EventElement_fbIsValid, &b_Left_telescope_SQY_L_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_SQY_L.TGo4EventElement.fIdentifier", &Left_telescope_SQY_L_TGo4EventElement_fIdentifier, &b_Left_telescope_SQY_L_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages", &Left_telescope_SQY_L_fDetMessages_, &b_Left_telescope_SQY_L_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages.fUniqueID", Left_telescope_SQY_L_fDetMessages_fUniqueID, &b_Left_telescope_SQY_L_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages.fBits", Left_telescope_SQY_L_fDetMessages_fBits, &b_Left_telescope_SQY_L_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages.fDetector", Left_telescope_SQY_L_fDetMessages_fDetector, &b_Left_telescope_SQY_L_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages.fStation", Left_telescope_SQY_L_fDetMessages_fStation, &b_Left_telescope_SQY_L_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages.fStChannel", Left_telescope_SQY_L_fDetMessages_fStChannel, &b_Left_telescope_SQY_L_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_SQY_L.fDetMessages.fValue", Left_telescope_SQY_L_fDetMessages_fValue, &b_Left_telescope_SQY_L_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_CsI_L.TGo4EventElement.fUniqueID", &Left_telescope_CsI_L_TGo4EventElement_fUniqueID, &b_Left_telescope_CsI_L_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_CsI_L.TGo4EventElement.fBits", &Left_telescope_CsI_L_TGo4EventElement_fBits, &b_Left_telescope_CsI_L_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_CsI_L.TGo4EventElement.fName", &Left_telescope_CsI_L_TGo4EventElement_fName, &b_Left_telescope_CsI_L_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_CsI_L.TGo4EventElement.fTitle", &Left_telescope_CsI_L_TGo4EventElement_fTitle, &b_Left_telescope_CsI_L_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_CsI_L.TGo4EventElement.fbIsValid", &Left_telescope_CsI_L_TGo4EventElement_fbIsValid, &b_Left_telescope_CsI_L_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_CsI_L.TGo4EventElement.fIdentifier", &Left_telescope_CsI_L_TGo4EventElement_fIdentifier, &b_Left_telescope_CsI_L_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages", &Left_telescope_CsI_L_fDetMessages_, &b_Left_telescope_CsI_L_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages.fUniqueID", Left_telescope_CsI_L_fDetMessages_fUniqueID, &b_Left_telescope_CsI_L_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages.fBits", Left_telescope_CsI_L_fDetMessages_fBits, &b_Left_telescope_CsI_L_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages.fDetector", Left_telescope_CsI_L_fDetMessages_fDetector, &b_Left_telescope_CsI_L_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages.fStation", Left_telescope_CsI_L_fDetMessages_fStation, &b_Left_telescope_CsI_L_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages.fStChannel", Left_telescope_CsI_L_fDetMessages_fStChannel, &b_Left_telescope_CsI_L_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_CsI_L.fDetMessages.fValue", Left_telescope_CsI_L_fDetMessages_fValue, &b_Left_telescope_CsI_L_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_SQ20.TGo4EventElement.fUniqueID", &Left_telescope_SQ20_TGo4EventElement_fUniqueID, &b_Left_telescope_SQ20_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_SQ20.TGo4EventElement.fBits", &Left_telescope_SQ20_TGo4EventElement_fBits, &b_Left_telescope_SQ20_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_SQ20.TGo4EventElement.fName", &Left_telescope_SQ20_TGo4EventElement_fName, &b_Left_telescope_SQ20_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_SQ20.TGo4EventElement.fTitle", &Left_telescope_SQ20_TGo4EventElement_fTitle, &b_Left_telescope_SQ20_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_SQ20.TGo4EventElement.fbIsValid", &Left_telescope_SQ20_TGo4EventElement_fbIsValid, &b_Left_telescope_SQ20_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_SQ20.TGo4EventElement.fIdentifier", &Left_telescope_SQ20_TGo4EventElement_fIdentifier, &b_Left_telescope_SQ20_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages", &Left_telescope_SQ20_fDetMessages_, &b_Left_telescope_SQ20_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages.fUniqueID", Left_telescope_SQ20_fDetMessages_fUniqueID, &b_Left_telescope_SQ20_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages.fBits", Left_telescope_SQ20_fDetMessages_fBits, &b_Left_telescope_SQ20_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages.fDetector", Left_telescope_SQ20_fDetMessages_fDetector, &b_Left_telescope_SQ20_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages.fStation", Left_telescope_SQ20_fDetMessages_fStation, &b_Left_telescope_SQ20_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages.fStChannel", Left_telescope_SQ20_fDetMessages_fStChannel, &b_Left_telescope_SQ20_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_SQ20.fDetMessages.fValue", Left_telescope_SQ20_fDetMessages_fValue, &b_Left_telescope_SQ20_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_tSQ20.TGo4EventElement.fUniqueID", &Left_telescope_tSQ20_TGo4EventElement_fUniqueID, &b_Left_telescope_tSQ20_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tSQ20.TGo4EventElement.fBits", &Left_telescope_tSQ20_TGo4EventElement_fBits, &b_Left_telescope_tSQ20_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_tSQ20.TGo4EventElement.fName", &Left_telescope_tSQ20_TGo4EventElement_fName, &b_Left_telescope_tSQ20_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_tSQ20.TGo4EventElement.fTitle", &Left_telescope_tSQ20_TGo4EventElement_fTitle, &b_Left_telescope_tSQ20_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_tSQ20.TGo4EventElement.fbIsValid", &Left_telescope_tSQ20_TGo4EventElement_fbIsValid, &b_Left_telescope_tSQ20_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_tSQ20.TGo4EventElement.fIdentifier", &Left_telescope_tSQ20_TGo4EventElement_fIdentifier, &b_Left_telescope_tSQ20_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages", &Left_telescope_tSQ20_fDetMessages_, &b_Left_telescope_tSQ20_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages.fUniqueID", Left_telescope_tSQ20_fDetMessages_fUniqueID, &b_Left_telescope_tSQ20_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages.fBits", Left_telescope_tSQ20_fDetMessages_fBits, &b_Left_telescope_tSQ20_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages.fDetector", Left_telescope_tSQ20_fDetMessages_fDetector, &b_Left_telescope_tSQ20_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages.fStation", Left_telescope_tSQ20_fDetMessages_fStation, &b_Left_telescope_tSQ20_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages.fStChannel", Left_telescope_tSQ20_fDetMessages_fStChannel, &b_Left_telescope_tSQ20_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_tSQ20.fDetMessages.fValue", Left_telescope_tSQ20_fDetMessages_fValue, &b_Left_telescope_tSQ20_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.TGo4EventElement.fUniqueID", &Left_telescope_tSQX_L_TGo4EventElement_fUniqueID, &b_Left_telescope_tSQX_L_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.TGo4EventElement.fBits", &Left_telescope_tSQX_L_TGo4EventElement_fBits, &b_Left_telescope_tSQX_L_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.TGo4EventElement.fName", &Left_telescope_tSQX_L_TGo4EventElement_fName, &b_Left_telescope_tSQX_L_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.TGo4EventElement.fTitle", &Left_telescope_tSQX_L_TGo4EventElement_fTitle, &b_Left_telescope_tSQX_L_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.TGo4EventElement.fbIsValid", &Left_telescope_tSQX_L_TGo4EventElement_fbIsValid, &b_Left_telescope_tSQX_L_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.TGo4EventElement.fIdentifier", &Left_telescope_tSQX_L_TGo4EventElement_fIdentifier, &b_Left_telescope_tSQX_L_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages", &Left_telescope_tSQX_L_fDetMessages_, &b_Left_telescope_tSQX_L_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages.fUniqueID", Left_telescope_tSQX_L_fDetMessages_fUniqueID, &b_Left_telescope_tSQX_L_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages.fBits", Left_telescope_tSQX_L_fDetMessages_fBits, &b_Left_telescope_tSQX_L_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages.fDetector", Left_telescope_tSQX_L_fDetMessages_fDetector, &b_Left_telescope_tSQX_L_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages.fStation", Left_telescope_tSQX_L_fDetMessages_fStation, &b_Left_telescope_tSQX_L_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages.fStChannel", Left_telescope_tSQX_L_fDetMessages_fStChannel, &b_Left_telescope_tSQX_L_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_tSQX_L.fDetMessages.fValue", Left_telescope_tSQX_L_fDetMessages_fValue, &b_Left_telescope_tSQX_L_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.TGo4EventElement.fUniqueID", &Left_telescope_tSQY_L_TGo4EventElement_fUniqueID, &b_Left_telescope_tSQY_L_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.TGo4EventElement.fBits", &Left_telescope_tSQY_L_TGo4EventElement_fBits, &b_Left_telescope_tSQY_L_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.TGo4EventElement.fName", &Left_telescope_tSQY_L_TGo4EventElement_fName, &b_Left_telescope_tSQY_L_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.TGo4EventElement.fTitle", &Left_telescope_tSQY_L_TGo4EventElement_fTitle, &b_Left_telescope_tSQY_L_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.TGo4EventElement.fbIsValid", &Left_telescope_tSQY_L_TGo4EventElement_fbIsValid, &b_Left_telescope_tSQY_L_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.TGo4EventElement.fIdentifier", &Left_telescope_tSQY_L_TGo4EventElement_fIdentifier, &b_Left_telescope_tSQY_L_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages", &Left_telescope_tSQY_L_fDetMessages_, &b_Left_telescope_tSQY_L_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages.fUniqueID", Left_telescope_tSQY_L_fDetMessages_fUniqueID, &b_Left_telescope_tSQY_L_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages.fBits", Left_telescope_tSQY_L_fDetMessages_fBits, &b_Left_telescope_tSQY_L_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages.fDetector", Left_telescope_tSQY_L_fDetMessages_fDetector, &b_Left_telescope_tSQY_L_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages.fStation", Left_telescope_tSQY_L_fDetMessages_fStation, &b_Left_telescope_tSQY_L_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages.fStChannel", Left_telescope_tSQY_L_fDetMessages_fStChannel, &b_Left_telescope_tSQY_L_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_tSQY_L.fDetMessages.fValue", Left_telescope_tSQY_L_fDetMessages_fValue, &b_Left_telescope_tSQY_L_fDetMessages_fValue);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.TGo4EventElement.fUniqueID", &Left_telescope_tCsI_L_TGo4EventElement_fUniqueID, &b_Left_telescope_tCsI_L_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.TGo4EventElement.fBits", &Left_telescope_tCsI_L_TGo4EventElement_fBits, &b_Left_telescope_tCsI_L_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.TGo4EventElement.fName", &Left_telescope_tCsI_L_TGo4EventElement_fName, &b_Left_telescope_tCsI_L_TGo4EventElement_fName);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.TGo4EventElement.fTitle", &Left_telescope_tCsI_L_TGo4EventElement_fTitle, &b_Left_telescope_tCsI_L_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.TGo4EventElement.fbIsValid", &Left_telescope_tCsI_L_TGo4EventElement_fbIsValid, &b_Left_telescope_tCsI_L_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.TGo4EventElement.fIdentifier", &Left_telescope_tCsI_L_TGo4EventElement_fIdentifier, &b_Left_telescope_tCsI_L_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages", &Left_telescope_tCsI_L_fDetMessages_, &b_Left_telescope_tCsI_L_fDetMessages_);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages.fUniqueID", Left_telescope_tCsI_L_fDetMessages_fUniqueID, &b_Left_telescope_tCsI_L_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages.fBits", Left_telescope_tCsI_L_fDetMessages_fBits, &b_Left_telescope_tCsI_L_fDetMessages_fBits);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages.fDetector", Left_telescope_tCsI_L_fDetMessages_fDetector, &b_Left_telescope_tCsI_L_fDetMessages_fDetector);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages.fStation", Left_telescope_tCsI_L_fDetMessages_fStation, &b_Left_telescope_tCsI_L_fDetMessages_fStation);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages.fStChannel", Left_telescope_tCsI_L_fDetMessages_fStChannel, &b_Left_telescope_tCsI_L_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Left_telescope_tCsI_L.fDetMessages.fValue", Left_telescope_tCsI_L_fDetMessages_fValue, &b_Left_telescope_tCsI_L_fDetMessages_fValue);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fUniqueID", &Right_telescope_TGo4CompositeEvent_fUniqueID, &b_Right_telescope_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fBits", &Right_telescope_TGo4CompositeEvent_fBits, &b_Right_telescope_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fName", &Right_telescope_TGo4CompositeEvent_fName, &b_Right_telescope_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fTitle", &Right_telescope_TGo4CompositeEvent_fTitle, &b_Right_telescope_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fbIsValid", &Right_telescope_TGo4CompositeEvent_fbIsValid, &b_Right_telescope_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fIdentifier", &Right_telescope_TGo4CompositeEvent_fIdentifier, &b_Right_telescope_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fNElements", &Right_telescope_TGo4CompositeEvent_fNElements, &b_Right_telescope_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("Right_telescope.TGo4CompositeEvent.fMaxIndex", &Right_telescope_TGo4CompositeEvent_fMaxIndex, &b_Right_telescope_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("Right_telescope_SQX_R.TGo4EventElement.fUniqueID", &Right_telescope_SQX_R_TGo4EventElement_fUniqueID, &b_Right_telescope_SQX_R_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_SQX_R.TGo4EventElement.fBits", &Right_telescope_SQX_R_TGo4EventElement_fBits, &b_Right_telescope_SQX_R_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Right_telescope_SQX_R.TGo4EventElement.fName", &Right_telescope_SQX_R_TGo4EventElement_fName, &b_Right_telescope_SQX_R_TGo4EventElement_fName);
   fChain->SetBranchAddress("Right_telescope_SQX_R.TGo4EventElement.fTitle", &Right_telescope_SQX_R_TGo4EventElement_fTitle, &b_Right_telescope_SQX_R_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Right_telescope_SQX_R.TGo4EventElement.fbIsValid", &Right_telescope_SQX_R_TGo4EventElement_fbIsValid, &b_Right_telescope_SQX_R_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Right_telescope_SQX_R.TGo4EventElement.fIdentifier", &Right_telescope_SQX_R_TGo4EventElement_fIdentifier, &b_Right_telescope_SQX_R_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages", &Right_telescope_SQX_R_fDetMessages_, &b_Right_telescope_SQX_R_fDetMessages_);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages.fUniqueID", Right_telescope_SQX_R_fDetMessages_fUniqueID, &b_Right_telescope_SQX_R_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages.fBits", Right_telescope_SQX_R_fDetMessages_fBits, &b_Right_telescope_SQX_R_fDetMessages_fBits);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages.fDetector", Right_telescope_SQX_R_fDetMessages_fDetector, &b_Right_telescope_SQX_R_fDetMessages_fDetector);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages.fStation", Right_telescope_SQX_R_fDetMessages_fStation, &b_Right_telescope_SQX_R_fDetMessages_fStation);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages.fStChannel", Right_telescope_SQX_R_fDetMessages_fStChannel, &b_Right_telescope_SQX_R_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Right_telescope_SQX_R.fDetMessages.fValue", Right_telescope_SQX_R_fDetMessages_fValue, &b_Right_telescope_SQX_R_fDetMessages_fValue);
   fChain->SetBranchAddress("Right_telescope_SQY_R.TGo4EventElement.fUniqueID", &Right_telescope_SQY_R_TGo4EventElement_fUniqueID, &b_Right_telescope_SQY_R_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_SQY_R.TGo4EventElement.fBits", &Right_telescope_SQY_R_TGo4EventElement_fBits, &b_Right_telescope_SQY_R_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Right_telescope_SQY_R.TGo4EventElement.fName", &Right_telescope_SQY_R_TGo4EventElement_fName, &b_Right_telescope_SQY_R_TGo4EventElement_fName);
   fChain->SetBranchAddress("Right_telescope_SQY_R.TGo4EventElement.fTitle", &Right_telescope_SQY_R_TGo4EventElement_fTitle, &b_Right_telescope_SQY_R_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Right_telescope_SQY_R.TGo4EventElement.fbIsValid", &Right_telescope_SQY_R_TGo4EventElement_fbIsValid, &b_Right_telescope_SQY_R_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Right_telescope_SQY_R.TGo4EventElement.fIdentifier", &Right_telescope_SQY_R_TGo4EventElement_fIdentifier, &b_Right_telescope_SQY_R_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages", &Right_telescope_SQY_R_fDetMessages_, &b_Right_telescope_SQY_R_fDetMessages_);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages.fUniqueID", Right_telescope_SQY_R_fDetMessages_fUniqueID, &b_Right_telescope_SQY_R_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages.fBits", Right_telescope_SQY_R_fDetMessages_fBits, &b_Right_telescope_SQY_R_fDetMessages_fBits);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages.fDetector", Right_telescope_SQY_R_fDetMessages_fDetector, &b_Right_telescope_SQY_R_fDetMessages_fDetector);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages.fStation", Right_telescope_SQY_R_fDetMessages_fStation, &b_Right_telescope_SQY_R_fDetMessages_fStation);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages.fStChannel", Right_telescope_SQY_R_fDetMessages_fStChannel, &b_Right_telescope_SQY_R_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Right_telescope_SQY_R.fDetMessages.fValue", Right_telescope_SQY_R_fDetMessages_fValue, &b_Right_telescope_SQY_R_fDetMessages_fValue);
   fChain->SetBranchAddress("Right_telescope_CsI_R.TGo4EventElement.fUniqueID", &Right_telescope_CsI_R_TGo4EventElement_fUniqueID, &b_Right_telescope_CsI_R_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_CsI_R.TGo4EventElement.fBits", &Right_telescope_CsI_R_TGo4EventElement_fBits, &b_Right_telescope_CsI_R_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Right_telescope_CsI_R.TGo4EventElement.fName", &Right_telescope_CsI_R_TGo4EventElement_fName, &b_Right_telescope_CsI_R_TGo4EventElement_fName);
   fChain->SetBranchAddress("Right_telescope_CsI_R.TGo4EventElement.fTitle", &Right_telescope_CsI_R_TGo4EventElement_fTitle, &b_Right_telescope_CsI_R_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Right_telescope_CsI_R.TGo4EventElement.fbIsValid", &Right_telescope_CsI_R_TGo4EventElement_fbIsValid, &b_Right_telescope_CsI_R_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Right_telescope_CsI_R.TGo4EventElement.fIdentifier", &Right_telescope_CsI_R_TGo4EventElement_fIdentifier, &b_Right_telescope_CsI_R_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages", &Right_telescope_CsI_R_fDetMessages_, &b_Right_telescope_CsI_R_fDetMessages_);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages.fUniqueID", Right_telescope_CsI_R_fDetMessages_fUniqueID, &b_Right_telescope_CsI_R_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages.fBits", Right_telescope_CsI_R_fDetMessages_fBits, &b_Right_telescope_CsI_R_fDetMessages_fBits);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages.fDetector", Right_telescope_CsI_R_fDetMessages_fDetector, &b_Right_telescope_CsI_R_fDetMessages_fDetector);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages.fStation", Right_telescope_CsI_R_fDetMessages_fStation, &b_Right_telescope_CsI_R_fDetMessages_fStation);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages.fStChannel", Right_telescope_CsI_R_fDetMessages_fStChannel, &b_Right_telescope_CsI_R_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Right_telescope_CsI_R.fDetMessages.fValue", Right_telescope_CsI_R_fDetMessages_fValue, &b_Right_telescope_CsI_R_fDetMessages_fValue);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.TGo4EventElement.fUniqueID", &Right_telescope_tSQX_R_TGo4EventElement_fUniqueID, &b_Right_telescope_tSQX_R_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.TGo4EventElement.fBits", &Right_telescope_tSQX_R_TGo4EventElement_fBits, &b_Right_telescope_tSQX_R_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.TGo4EventElement.fName", &Right_telescope_tSQX_R_TGo4EventElement_fName, &b_Right_telescope_tSQX_R_TGo4EventElement_fName);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.TGo4EventElement.fTitle", &Right_telescope_tSQX_R_TGo4EventElement_fTitle, &b_Right_telescope_tSQX_R_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.TGo4EventElement.fbIsValid", &Right_telescope_tSQX_R_TGo4EventElement_fbIsValid, &b_Right_telescope_tSQX_R_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.TGo4EventElement.fIdentifier", &Right_telescope_tSQX_R_TGo4EventElement_fIdentifier, &b_Right_telescope_tSQX_R_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages", &Right_telescope_tSQX_R_fDetMessages_, &b_Right_telescope_tSQX_R_fDetMessages_);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages.fUniqueID", Right_telescope_tSQX_R_fDetMessages_fUniqueID, &b_Right_telescope_tSQX_R_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages.fBits", Right_telescope_tSQX_R_fDetMessages_fBits, &b_Right_telescope_tSQX_R_fDetMessages_fBits);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages.fDetector", Right_telescope_tSQX_R_fDetMessages_fDetector, &b_Right_telescope_tSQX_R_fDetMessages_fDetector);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages.fStation", Right_telescope_tSQX_R_fDetMessages_fStation, &b_Right_telescope_tSQX_R_fDetMessages_fStation);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages.fStChannel", Right_telescope_tSQX_R_fDetMessages_fStChannel, &b_Right_telescope_tSQX_R_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Right_telescope_tSQX_R.fDetMessages.fValue", Right_telescope_tSQX_R_fDetMessages_fValue, &b_Right_telescope_tSQX_R_fDetMessages_fValue);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.TGo4EventElement.fUniqueID", &Right_telescope_tSQY_R_TGo4EventElement_fUniqueID, &b_Right_telescope_tSQY_R_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.TGo4EventElement.fBits", &Right_telescope_tSQY_R_TGo4EventElement_fBits, &b_Right_telescope_tSQY_R_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.TGo4EventElement.fName", &Right_telescope_tSQY_R_TGo4EventElement_fName, &b_Right_telescope_tSQY_R_TGo4EventElement_fName);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.TGo4EventElement.fTitle", &Right_telescope_tSQY_R_TGo4EventElement_fTitle, &b_Right_telescope_tSQY_R_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.TGo4EventElement.fbIsValid", &Right_telescope_tSQY_R_TGo4EventElement_fbIsValid, &b_Right_telescope_tSQY_R_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.TGo4EventElement.fIdentifier", &Right_telescope_tSQY_R_TGo4EventElement_fIdentifier, &b_Right_telescope_tSQY_R_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages", &Right_telescope_tSQY_R_fDetMessages_, &b_Right_telescope_tSQY_R_fDetMessages_);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages.fUniqueID", Right_telescope_tSQY_R_fDetMessages_fUniqueID, &b_Right_telescope_tSQY_R_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages.fBits", Right_telescope_tSQY_R_fDetMessages_fBits, &b_Right_telescope_tSQY_R_fDetMessages_fBits);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages.fDetector", Right_telescope_tSQY_R_fDetMessages_fDetector, &b_Right_telescope_tSQY_R_fDetMessages_fDetector);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages.fStation", Right_telescope_tSQY_R_fDetMessages_fStation, &b_Right_telescope_tSQY_R_fDetMessages_fStation);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages.fStChannel", Right_telescope_tSQY_R_fDetMessages_fStChannel, &b_Right_telescope_tSQY_R_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Right_telescope_tSQY_R.fDetMessages.fValue", Right_telescope_tSQY_R_fDetMessages_fValue, &b_Right_telescope_tSQY_R_fDetMessages_fValue);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.TGo4EventElement.fUniqueID", &Right_telescope_tCsI_R_TGo4EventElement_fUniqueID, &b_Right_telescope_tCsI_R_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.TGo4EventElement.fBits", &Right_telescope_tCsI_R_TGo4EventElement_fBits, &b_Right_telescope_tCsI_R_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.TGo4EventElement.fName", &Right_telescope_tCsI_R_TGo4EventElement_fName, &b_Right_telescope_tCsI_R_TGo4EventElement_fName);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.TGo4EventElement.fTitle", &Right_telescope_tCsI_R_TGo4EventElement_fTitle, &b_Right_telescope_tCsI_R_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.TGo4EventElement.fbIsValid", &Right_telescope_tCsI_R_TGo4EventElement_fbIsValid, &b_Right_telescope_tCsI_R_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.TGo4EventElement.fIdentifier", &Right_telescope_tCsI_R_TGo4EventElement_fIdentifier, &b_Right_telescope_tCsI_R_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages", &Right_telescope_tCsI_R_fDetMessages_, &b_Right_telescope_tCsI_R_fDetMessages_);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages.fUniqueID", Right_telescope_tCsI_R_fDetMessages_fUniqueID, &b_Right_telescope_tCsI_R_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages.fBits", Right_telescope_tCsI_R_fDetMessages_fBits, &b_Right_telescope_tCsI_R_fDetMessages_fBits);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages.fDetector", Right_telescope_tCsI_R_fDetMessages_fDetector, &b_Right_telescope_tCsI_R_fDetMessages_fDetector);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages.fStation", Right_telescope_tCsI_R_fDetMessages_fStation, &b_Right_telescope_tCsI_R_fDetMessages_fStation);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages.fStChannel", Right_telescope_tCsI_R_fDetMessages_fStChannel, &b_Right_telescope_tCsI_R_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Right_telescope_tCsI_R.fDetMessages.fValue", Right_telescope_tCsI_R_fDetMessages_fValue, &b_Right_telescope_tCsI_R_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fUniqueID", &Beam_detector_ToF_TGo4CompositeEvent_fUniqueID, &b_Beam_detector_ToF_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fBits", &Beam_detector_ToF_TGo4CompositeEvent_fBits, &b_Beam_detector_ToF_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fName", &Beam_detector_ToF_TGo4CompositeEvent_fName, &b_Beam_detector_ToF_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fTitle", &Beam_detector_ToF_TGo4CompositeEvent_fTitle, &b_Beam_detector_ToF_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fbIsValid", &Beam_detector_ToF_TGo4CompositeEvent_fbIsValid, &b_Beam_detector_ToF_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fIdentifier", &Beam_detector_ToF_TGo4CompositeEvent_fIdentifier, &b_Beam_detector_ToF_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fNElements", &Beam_detector_ToF_TGo4CompositeEvent_fNElements, &b_Beam_detector_ToF_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("Beam_detector_ToF.TGo4CompositeEvent.fMaxIndex", &Beam_detector_ToF_TGo4CompositeEvent_fMaxIndex, &b_Beam_detector_ToF_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.TGo4EventElement.fUniqueID", &Beam_detector_ToF_F3_TGo4EventElement_fUniqueID, &b_Beam_detector_ToF_F3_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.TGo4EventElement.fBits", &Beam_detector_ToF_F3_TGo4EventElement_fBits, &b_Beam_detector_ToF_F3_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.TGo4EventElement.fName", &Beam_detector_ToF_F3_TGo4EventElement_fName, &b_Beam_detector_ToF_F3_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.TGo4EventElement.fTitle", &Beam_detector_ToF_F3_TGo4EventElement_fTitle, &b_Beam_detector_ToF_F3_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.TGo4EventElement.fbIsValid", &Beam_detector_ToF_F3_TGo4EventElement_fbIsValid, &b_Beam_detector_ToF_F3_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.TGo4EventElement.fIdentifier", &Beam_detector_ToF_F3_TGo4EventElement_fIdentifier, &b_Beam_detector_ToF_F3_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages", &Beam_detector_ToF_F3_fDetMessages_, &b_Beam_detector_ToF_F3_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages.fUniqueID", Beam_detector_ToF_F3_fDetMessages_fUniqueID, &b_Beam_detector_ToF_F3_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages.fBits", Beam_detector_ToF_F3_fDetMessages_fBits, &b_Beam_detector_ToF_F3_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages.fDetector", Beam_detector_ToF_F3_fDetMessages_fDetector, &b_Beam_detector_ToF_F3_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages.fStation", Beam_detector_ToF_F3_fDetMessages_fStation, &b_Beam_detector_ToF_F3_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages.fStChannel", Beam_detector_ToF_F3_fDetMessages_fStChannel, &b_Beam_detector_ToF_F3_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_ToF_F3.fDetMessages.fValue", Beam_detector_ToF_F3_fDetMessages_fValue, &b_Beam_detector_ToF_F3_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.TGo4EventElement.fUniqueID", &Beam_detector_ToF_F5_TGo4EventElement_fUniqueID, &b_Beam_detector_ToF_F5_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.TGo4EventElement.fBits", &Beam_detector_ToF_F5_TGo4EventElement_fBits, &b_Beam_detector_ToF_F5_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.TGo4EventElement.fName", &Beam_detector_ToF_F5_TGo4EventElement_fName, &b_Beam_detector_ToF_F5_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.TGo4EventElement.fTitle", &Beam_detector_ToF_F5_TGo4EventElement_fTitle, &b_Beam_detector_ToF_F5_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.TGo4EventElement.fbIsValid", &Beam_detector_ToF_F5_TGo4EventElement_fbIsValid, &b_Beam_detector_ToF_F5_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.TGo4EventElement.fIdentifier", &Beam_detector_ToF_F5_TGo4EventElement_fIdentifier, &b_Beam_detector_ToF_F5_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages", &Beam_detector_ToF_F5_fDetMessages_, &b_Beam_detector_ToF_F5_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages.fUniqueID", Beam_detector_ToF_F5_fDetMessages_fUniqueID, &b_Beam_detector_ToF_F5_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages.fBits", Beam_detector_ToF_F5_fDetMessages_fBits, &b_Beam_detector_ToF_F5_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages.fDetector", Beam_detector_ToF_F5_fDetMessages_fDetector, &b_Beam_detector_ToF_F5_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages.fStation", Beam_detector_ToF_F5_fDetMessages_fStation, &b_Beam_detector_ToF_F5_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages.fStChannel", Beam_detector_ToF_F5_fDetMessages_fStChannel, &b_Beam_detector_ToF_F5_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_ToF_F5.fDetMessages.fValue", Beam_detector_ToF_F5_fDetMessages_fValue, &b_Beam_detector_ToF_F5_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.TGo4EventElement.fUniqueID", &Beam_detector_ToF_F6_TGo4EventElement_fUniqueID, &b_Beam_detector_ToF_F6_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.TGo4EventElement.fBits", &Beam_detector_ToF_F6_TGo4EventElement_fBits, &b_Beam_detector_ToF_F6_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.TGo4EventElement.fName", &Beam_detector_ToF_F6_TGo4EventElement_fName, &b_Beam_detector_ToF_F6_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.TGo4EventElement.fTitle", &Beam_detector_ToF_F6_TGo4EventElement_fTitle, &b_Beam_detector_ToF_F6_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.TGo4EventElement.fbIsValid", &Beam_detector_ToF_F6_TGo4EventElement_fbIsValid, &b_Beam_detector_ToF_F6_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.TGo4EventElement.fIdentifier", &Beam_detector_ToF_F6_TGo4EventElement_fIdentifier, &b_Beam_detector_ToF_F6_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages", &Beam_detector_ToF_F6_fDetMessages_, &b_Beam_detector_ToF_F6_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages.fUniqueID", &Beam_detector_ToF_F6_fDetMessages_fUniqueID, &b_Beam_detector_ToF_F6_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages.fBits", &Beam_detector_ToF_F6_fDetMessages_fBits, &b_Beam_detector_ToF_F6_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages.fDetector", &Beam_detector_ToF_F6_fDetMessages_fDetector, &b_Beam_detector_ToF_F6_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages.fStation", &Beam_detector_ToF_F6_fDetMessages_fStation, &b_Beam_detector_ToF_F6_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages.fStChannel", &Beam_detector_ToF_F6_fDetMessages_fStChannel, &b_Beam_detector_ToF_F6_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_ToF_F6.fDetMessages.fValue", &Beam_detector_ToF_F6_fDetMessages_fValue, &b_Beam_detector_ToF_F6_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.TGo4EventElement.fUniqueID", &Beam_detector_ToF_tF3_TGo4EventElement_fUniqueID, &b_Beam_detector_ToF_tF3_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.TGo4EventElement.fBits", &Beam_detector_ToF_tF3_TGo4EventElement_fBits, &b_Beam_detector_ToF_tF3_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.TGo4EventElement.fName", &Beam_detector_ToF_tF3_TGo4EventElement_fName, &b_Beam_detector_ToF_tF3_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.TGo4EventElement.fTitle", &Beam_detector_ToF_tF3_TGo4EventElement_fTitle, &b_Beam_detector_ToF_tF3_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.TGo4EventElement.fbIsValid", &Beam_detector_ToF_tF3_TGo4EventElement_fbIsValid, &b_Beam_detector_ToF_tF3_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.TGo4EventElement.fIdentifier", &Beam_detector_ToF_tF3_TGo4EventElement_fIdentifier, &b_Beam_detector_ToF_tF3_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages", &Beam_detector_ToF_tF3_fDetMessages_, &b_Beam_detector_ToF_tF3_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages.fUniqueID", Beam_detector_ToF_tF3_fDetMessages_fUniqueID, &b_Beam_detector_ToF_tF3_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages.fBits", Beam_detector_ToF_tF3_fDetMessages_fBits, &b_Beam_detector_ToF_tF3_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages.fDetector", Beam_detector_ToF_tF3_fDetMessages_fDetector, &b_Beam_detector_ToF_tF3_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages.fStation", Beam_detector_ToF_tF3_fDetMessages_fStation, &b_Beam_detector_ToF_tF3_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages.fStChannel", Beam_detector_ToF_tF3_fDetMessages_fStChannel, &b_Beam_detector_ToF_tF3_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_ToF_tF3.fDetMessages.fValue", Beam_detector_ToF_tF3_fDetMessages_fValue, &b_Beam_detector_ToF_tF3_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.TGo4EventElement.fUniqueID", &Beam_detector_ToF_tF5_TGo4EventElement_fUniqueID, &b_Beam_detector_ToF_tF5_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.TGo4EventElement.fBits", &Beam_detector_ToF_tF5_TGo4EventElement_fBits, &b_Beam_detector_ToF_tF5_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.TGo4EventElement.fName", &Beam_detector_ToF_tF5_TGo4EventElement_fName, &b_Beam_detector_ToF_tF5_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.TGo4EventElement.fTitle", &Beam_detector_ToF_tF5_TGo4EventElement_fTitle, &b_Beam_detector_ToF_tF5_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.TGo4EventElement.fbIsValid", &Beam_detector_ToF_tF5_TGo4EventElement_fbIsValid, &b_Beam_detector_ToF_tF5_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.TGo4EventElement.fIdentifier", &Beam_detector_ToF_tF5_TGo4EventElement_fIdentifier, &b_Beam_detector_ToF_tF5_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages", &Beam_detector_ToF_tF5_fDetMessages_, &b_Beam_detector_ToF_tF5_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages.fUniqueID", Beam_detector_ToF_tF5_fDetMessages_fUniqueID, &b_Beam_detector_ToF_tF5_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages.fBits", Beam_detector_ToF_tF5_fDetMessages_fBits, &b_Beam_detector_ToF_tF5_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages.fDetector", Beam_detector_ToF_tF5_fDetMessages_fDetector, &b_Beam_detector_ToF_tF5_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages.fStation", Beam_detector_ToF_tF5_fDetMessages_fStation, &b_Beam_detector_ToF_tF5_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages.fStChannel", Beam_detector_ToF_tF5_fDetMessages_fStChannel, &b_Beam_detector_ToF_tF5_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_ToF_tF5.fDetMessages.fValue", Beam_detector_ToF_tF5_fDetMessages_fValue, &b_Beam_detector_ToF_tF5_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.TGo4EventElement.fUniqueID", &Beam_detector_ToF_tF6_TGo4EventElement_fUniqueID, &b_Beam_detector_ToF_tF6_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.TGo4EventElement.fBits", &Beam_detector_ToF_tF6_TGo4EventElement_fBits, &b_Beam_detector_ToF_tF6_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.TGo4EventElement.fName", &Beam_detector_ToF_tF6_TGo4EventElement_fName, &b_Beam_detector_ToF_tF6_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.TGo4EventElement.fTitle", &Beam_detector_ToF_tF6_TGo4EventElement_fTitle, &b_Beam_detector_ToF_tF6_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.TGo4EventElement.fbIsValid", &Beam_detector_ToF_tF6_TGo4EventElement_fbIsValid, &b_Beam_detector_ToF_tF6_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.TGo4EventElement.fIdentifier", &Beam_detector_ToF_tF6_TGo4EventElement_fIdentifier, &b_Beam_detector_ToF_tF6_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages", &Beam_detector_ToF_tF6_fDetMessages_, &b_Beam_detector_ToF_tF6_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages.fUniqueID", &Beam_detector_ToF_tF6_fDetMessages_fUniqueID, &b_Beam_detector_ToF_tF6_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages.fBits", &Beam_detector_ToF_tF6_fDetMessages_fBits, &b_Beam_detector_ToF_tF6_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages.fDetector", &Beam_detector_ToF_tF6_fDetMessages_fDetector, &b_Beam_detector_ToF_tF6_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages.fStation", &Beam_detector_ToF_tF6_fDetMessages_fStation, &b_Beam_detector_ToF_tF6_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages.fStChannel", &Beam_detector_ToF_tF6_fDetMessages_fStChannel, &b_Beam_detector_ToF_tF6_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_ToF_tF6.fDetMessages.fValue", &Beam_detector_ToF_tF6_fDetMessages_fValue, &b_Beam_detector_ToF_tF6_fDetMessages_fValue);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fUniqueID", &Ignore_TGo4CompositeEvent_fUniqueID, &b_Ignore_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fBits", &Ignore_TGo4CompositeEvent_fBits, &b_Ignore_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fName", &Ignore_TGo4CompositeEvent_fName, &b_Ignore_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fTitle", &Ignore_TGo4CompositeEvent_fTitle, &b_Ignore_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fbIsValid", &Ignore_TGo4CompositeEvent_fbIsValid, &b_Ignore_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fIdentifier", &Ignore_TGo4CompositeEvent_fIdentifier, &b_Ignore_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fNElements", &Ignore_TGo4CompositeEvent_fNElements, &b_Ignore_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("Ignore.TGo4CompositeEvent.fMaxIndex", &Ignore_TGo4CompositeEvent_fMaxIndex, &b_Ignore_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("Ignore_Ignore.TGo4EventElement.fUniqueID", &Ignore_Ignore_TGo4EventElement_fUniqueID, &b_Ignore_Ignore_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Ignore_Ignore.TGo4EventElement.fBits", &Ignore_Ignore_TGo4EventElement_fBits, &b_Ignore_Ignore_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Ignore_Ignore.TGo4EventElement.fName", &Ignore_Ignore_TGo4EventElement_fName, &b_Ignore_Ignore_TGo4EventElement_fName);
   fChain->SetBranchAddress("Ignore_Ignore.TGo4EventElement.fTitle", &Ignore_Ignore_TGo4EventElement_fTitle, &b_Ignore_Ignore_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Ignore_Ignore.TGo4EventElement.fbIsValid", &Ignore_Ignore_TGo4EventElement_fbIsValid, &b_Ignore_Ignore_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Ignore_Ignore.TGo4EventElement.fIdentifier", &Ignore_Ignore_TGo4EventElement_fIdentifier, &b_Ignore_Ignore_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages", &Ignore_Ignore_fDetMessages_, &b_Ignore_Ignore_fDetMessages_);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages.fUniqueID", &Ignore_Ignore_fDetMessages_fUniqueID, &b_Ignore_Ignore_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages.fBits", &Ignore_Ignore_fDetMessages_fBits, &b_Ignore_Ignore_fDetMessages_fBits);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages.fDetector", &Ignore_Ignore_fDetMessages_fDetector, &b_Ignore_Ignore_fDetMessages_fDetector);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages.fStation", &Ignore_Ignore_fDetMessages_fStation, &b_Ignore_Ignore_fDetMessages_fStation);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages.fStChannel", &Ignore_Ignore_fDetMessages_fStChannel, &b_Ignore_Ignore_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Ignore_Ignore.fDetMessages.fValue", &Ignore_Ignore_fDetMessages_fValue, &b_Ignore_Ignore_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fUniqueID", &Beam_detector_MWPC_TGo4CompositeEvent_fUniqueID, &b_Beam_detector_MWPC_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fBits", &Beam_detector_MWPC_TGo4CompositeEvent_fBits, &b_Beam_detector_MWPC_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fName", &Beam_detector_MWPC_TGo4CompositeEvent_fName, &b_Beam_detector_MWPC_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fTitle", &Beam_detector_MWPC_TGo4CompositeEvent_fTitle, &b_Beam_detector_MWPC_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fbIsValid", &Beam_detector_MWPC_TGo4CompositeEvent_fbIsValid, &b_Beam_detector_MWPC_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fIdentifier", &Beam_detector_MWPC_TGo4CompositeEvent_fIdentifier, &b_Beam_detector_MWPC_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fNElements", &Beam_detector_MWPC_TGo4CompositeEvent_fNElements, &b_Beam_detector_MWPC_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("Beam_detector_MWPC.TGo4CompositeEvent.fMaxIndex", &Beam_detector_MWPC_TGo4CompositeEvent_fMaxIndex, &b_Beam_detector_MWPC_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.TGo4EventElement.fUniqueID", &Beam_detector_MWPC_tMWPC_TGo4EventElement_fUniqueID, &b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.TGo4EventElement.fBits", &Beam_detector_MWPC_tMWPC_TGo4EventElement_fBits, &b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.TGo4EventElement.fName", &Beam_detector_MWPC_tMWPC_TGo4EventElement_fName, &b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.TGo4EventElement.fTitle", &Beam_detector_MWPC_tMWPC_TGo4EventElement_fTitle, &b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.TGo4EventElement.fbIsValid", &Beam_detector_MWPC_tMWPC_TGo4EventElement_fbIsValid, &b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.TGo4EventElement.fIdentifier", &Beam_detector_MWPC_tMWPC_TGo4EventElement_fIdentifier, &b_Beam_detector_MWPC_tMWPC_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages", &Beam_detector_MWPC_tMWPC_fDetMessages_, &b_Beam_detector_MWPC_tMWPC_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages.fUniqueID", Beam_detector_MWPC_tMWPC_fDetMessages_fUniqueID, &b_Beam_detector_MWPC_tMWPC_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages.fBits", Beam_detector_MWPC_tMWPC_fDetMessages_fBits, &b_Beam_detector_MWPC_tMWPC_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages.fDetector", Beam_detector_MWPC_tMWPC_fDetMessages_fDetector, &b_Beam_detector_MWPC_tMWPC_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages.fStation", Beam_detector_MWPC_tMWPC_fDetMessages_fStation, &b_Beam_detector_MWPC_tMWPC_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages.fStChannel", Beam_detector_MWPC_tMWPC_fDetMessages_fStChannel, &b_Beam_detector_MWPC_tMWPC_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_MWPC_tMWPC.fDetMessages.fValue", Beam_detector_MWPC_tMWPC_fDetMessages_fValue, &b_Beam_detector_MWPC_tMWPC_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.TGo4EventElement.fUniqueID", &Beam_detector_MWPC_MWPC1_TGo4EventElement_fUniqueID, &b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.TGo4EventElement.fBits", &Beam_detector_MWPC_MWPC1_TGo4EventElement_fBits, &b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.TGo4EventElement.fName", &Beam_detector_MWPC_MWPC1_TGo4EventElement_fName, &b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.TGo4EventElement.fTitle", &Beam_detector_MWPC_MWPC1_TGo4EventElement_fTitle, &b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.TGo4EventElement.fbIsValid", &Beam_detector_MWPC_MWPC1_TGo4EventElement_fbIsValid, &b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.TGo4EventElement.fIdentifier", &Beam_detector_MWPC_MWPC1_TGo4EventElement_fIdentifier, &b_Beam_detector_MWPC_MWPC1_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages", &Beam_detector_MWPC_MWPC1_fDetMessages_, &b_Beam_detector_MWPC_MWPC1_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages.fUniqueID", Beam_detector_MWPC_MWPC1_fDetMessages_fUniqueID, &b_Beam_detector_MWPC_MWPC1_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages.fBits", Beam_detector_MWPC_MWPC1_fDetMessages_fBits, &b_Beam_detector_MWPC_MWPC1_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages.fDetector", Beam_detector_MWPC_MWPC1_fDetMessages_fDetector, &b_Beam_detector_MWPC_MWPC1_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages.fStation", Beam_detector_MWPC_MWPC1_fDetMessages_fStation, &b_Beam_detector_MWPC_MWPC1_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages.fStChannel", Beam_detector_MWPC_MWPC1_fDetMessages_fStChannel, &b_Beam_detector_MWPC_MWPC1_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC1.fDetMessages.fValue", Beam_detector_MWPC_MWPC1_fDetMessages_fValue, &b_Beam_detector_MWPC_MWPC1_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.TGo4EventElement.fUniqueID", &Beam_detector_MWPC_MWPC2_TGo4EventElement_fUniqueID, &b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.TGo4EventElement.fBits", &Beam_detector_MWPC_MWPC2_TGo4EventElement_fBits, &b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.TGo4EventElement.fName", &Beam_detector_MWPC_MWPC2_TGo4EventElement_fName, &b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.TGo4EventElement.fTitle", &Beam_detector_MWPC_MWPC2_TGo4EventElement_fTitle, &b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.TGo4EventElement.fbIsValid", &Beam_detector_MWPC_MWPC2_TGo4EventElement_fbIsValid, &b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.TGo4EventElement.fIdentifier", &Beam_detector_MWPC_MWPC2_TGo4EventElement_fIdentifier, &b_Beam_detector_MWPC_MWPC2_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages", &Beam_detector_MWPC_MWPC2_fDetMessages_, &b_Beam_detector_MWPC_MWPC2_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages.fUniqueID", Beam_detector_MWPC_MWPC2_fDetMessages_fUniqueID, &b_Beam_detector_MWPC_MWPC2_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages.fBits", Beam_detector_MWPC_MWPC2_fDetMessages_fBits, &b_Beam_detector_MWPC_MWPC2_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages.fDetector", Beam_detector_MWPC_MWPC2_fDetMessages_fDetector, &b_Beam_detector_MWPC_MWPC2_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages.fStation", Beam_detector_MWPC_MWPC2_fDetMessages_fStation, &b_Beam_detector_MWPC_MWPC2_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages.fStChannel", Beam_detector_MWPC_MWPC2_fDetMessages_fStChannel, &b_Beam_detector_MWPC_MWPC2_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC2.fDetMessages.fValue", Beam_detector_MWPC_MWPC2_fDetMessages_fValue, &b_Beam_detector_MWPC_MWPC2_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.TGo4EventElement.fUniqueID", &Beam_detector_MWPC_MWPC3_TGo4EventElement_fUniqueID, &b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.TGo4EventElement.fBits", &Beam_detector_MWPC_MWPC3_TGo4EventElement_fBits, &b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.TGo4EventElement.fName", &Beam_detector_MWPC_MWPC3_TGo4EventElement_fName, &b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.TGo4EventElement.fTitle", &Beam_detector_MWPC_MWPC3_TGo4EventElement_fTitle, &b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.TGo4EventElement.fbIsValid", &Beam_detector_MWPC_MWPC3_TGo4EventElement_fbIsValid, &b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.TGo4EventElement.fIdentifier", &Beam_detector_MWPC_MWPC3_TGo4EventElement_fIdentifier, &b_Beam_detector_MWPC_MWPC3_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages", &Beam_detector_MWPC_MWPC3_fDetMessages_, &b_Beam_detector_MWPC_MWPC3_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages.fUniqueID", Beam_detector_MWPC_MWPC3_fDetMessages_fUniqueID, &b_Beam_detector_MWPC_MWPC3_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages.fBits", Beam_detector_MWPC_MWPC3_fDetMessages_fBits, &b_Beam_detector_MWPC_MWPC3_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages.fDetector", Beam_detector_MWPC_MWPC3_fDetMessages_fDetector, &b_Beam_detector_MWPC_MWPC3_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages.fStation", Beam_detector_MWPC_MWPC3_fDetMessages_fStation, &b_Beam_detector_MWPC_MWPC3_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages.fStChannel", Beam_detector_MWPC_MWPC3_fDetMessages_fStChannel, &b_Beam_detector_MWPC_MWPC3_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC3.fDetMessages.fValue", Beam_detector_MWPC_MWPC3_fDetMessages_fValue, &b_Beam_detector_MWPC_MWPC3_fDetMessages_fValue);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.TGo4EventElement.fUniqueID", &Beam_detector_MWPC_MWPC4_TGo4EventElement_fUniqueID, &b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.TGo4EventElement.fBits", &Beam_detector_MWPC_MWPC4_TGo4EventElement_fBits, &b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.TGo4EventElement.fName", &Beam_detector_MWPC_MWPC4_TGo4EventElement_fName, &b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fName);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.TGo4EventElement.fTitle", &Beam_detector_MWPC_MWPC4_TGo4EventElement_fTitle, &b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.TGo4EventElement.fbIsValid", &Beam_detector_MWPC_MWPC4_TGo4EventElement_fbIsValid, &b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.TGo4EventElement.fIdentifier", &Beam_detector_MWPC_MWPC4_TGo4EventElement_fIdentifier, &b_Beam_detector_MWPC_MWPC4_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages", &Beam_detector_MWPC_MWPC4_fDetMessages_, &b_Beam_detector_MWPC_MWPC4_fDetMessages_);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages.fUniqueID", Beam_detector_MWPC_MWPC4_fDetMessages_fUniqueID, &b_Beam_detector_MWPC_MWPC4_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages.fBits", Beam_detector_MWPC_MWPC4_fDetMessages_fBits, &b_Beam_detector_MWPC_MWPC4_fDetMessages_fBits);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages.fDetector", Beam_detector_MWPC_MWPC4_fDetMessages_fDetector, &b_Beam_detector_MWPC_MWPC4_fDetMessages_fDetector);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages.fStation", Beam_detector_MWPC_MWPC4_fDetMessages_fStation, &b_Beam_detector_MWPC_MWPC4_fDetMessages_fStation);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages.fStChannel", Beam_detector_MWPC_MWPC4_fDetMessages_fStChannel, &b_Beam_detector_MWPC_MWPC4_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Beam_detector_MWPC_MWPC4.fDetMessages.fValue", Beam_detector_MWPC_MWPC4_fDetMessages_fValue, &b_Beam_detector_MWPC_MWPC4_fDetMessages_fValue);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fUniqueID", &Neutron_detector_TGo4CompositeEvent_fUniqueID, &b_Neutron_detector_TGo4CompositeEvent_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fBits", &Neutron_detector_TGo4CompositeEvent_fBits, &b_Neutron_detector_TGo4CompositeEvent_fBits);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fName", &Neutron_detector_TGo4CompositeEvent_fName, &b_Neutron_detector_TGo4CompositeEvent_fName);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fTitle", &Neutron_detector_TGo4CompositeEvent_fTitle, &b_Neutron_detector_TGo4CompositeEvent_fTitle);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fbIsValid", &Neutron_detector_TGo4CompositeEvent_fbIsValid, &b_Neutron_detector_TGo4CompositeEvent_fbIsValid);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fIdentifier", &Neutron_detector_TGo4CompositeEvent_fIdentifier, &b_Neutron_detector_TGo4CompositeEvent_fIdentifier);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fNElements", &Neutron_detector_TGo4CompositeEvent_fNElements, &b_Neutron_detector_TGo4CompositeEvent_fNElements);
   fChain->SetBranchAddress("Neutron_detector.TGo4CompositeEvent.fMaxIndex", &Neutron_detector_TGo4CompositeEvent_fMaxIndex, &b_Neutron_detector_TGo4CompositeEvent_fMaxIndex);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.TGo4EventElement.fUniqueID", &Neutron_detector_neutTDC_TGo4EventElement_fUniqueID, &b_Neutron_detector_neutTDC_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.TGo4EventElement.fBits", &Neutron_detector_neutTDC_TGo4EventElement_fBits, &b_Neutron_detector_neutTDC_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.TGo4EventElement.fName", &Neutron_detector_neutTDC_TGo4EventElement_fName, &b_Neutron_detector_neutTDC_TGo4EventElement_fName);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.TGo4EventElement.fTitle", &Neutron_detector_neutTDC_TGo4EventElement_fTitle, &b_Neutron_detector_neutTDC_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.TGo4EventElement.fbIsValid", &Neutron_detector_neutTDC_TGo4EventElement_fbIsValid, &b_Neutron_detector_neutTDC_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.TGo4EventElement.fIdentifier", &Neutron_detector_neutTDC_TGo4EventElement_fIdentifier, &b_Neutron_detector_neutTDC_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages", &Neutron_detector_neutTDC_fDetMessages_, &b_Neutron_detector_neutTDC_fDetMessages_);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages.fUniqueID", Neutron_detector_neutTDC_fDetMessages_fUniqueID, &b_Neutron_detector_neutTDC_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages.fBits", Neutron_detector_neutTDC_fDetMessages_fBits, &b_Neutron_detector_neutTDC_fDetMessages_fBits);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages.fDetector", Neutron_detector_neutTDC_fDetMessages_fDetector, &b_Neutron_detector_neutTDC_fDetMessages_fDetector);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages.fStation", Neutron_detector_neutTDC_fDetMessages_fStation, &b_Neutron_detector_neutTDC_fDetMessages_fStation);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages.fStChannel", Neutron_detector_neutTDC_fDetMessages_fStChannel, &b_Neutron_detector_neutTDC_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Neutron_detector_neutTDC.fDetMessages.fValue", Neutron_detector_neutTDC_fDetMessages_fValue, &b_Neutron_detector_neutTDC_fDetMessages_fValue);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.TGo4EventElement.fUniqueID", &Neutron_detector_neutAmp_TGo4EventElement_fUniqueID, &b_Neutron_detector_neutAmp_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.TGo4EventElement.fBits", &Neutron_detector_neutAmp_TGo4EventElement_fBits, &b_Neutron_detector_neutAmp_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.TGo4EventElement.fName", &Neutron_detector_neutAmp_TGo4EventElement_fName, &b_Neutron_detector_neutAmp_TGo4EventElement_fName);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.TGo4EventElement.fTitle", &Neutron_detector_neutAmp_TGo4EventElement_fTitle, &b_Neutron_detector_neutAmp_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.TGo4EventElement.fbIsValid", &Neutron_detector_neutAmp_TGo4EventElement_fbIsValid, &b_Neutron_detector_neutAmp_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.TGo4EventElement.fIdentifier", &Neutron_detector_neutAmp_TGo4EventElement_fIdentifier, &b_Neutron_detector_neutAmp_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages", &Neutron_detector_neutAmp_fDetMessages_, &b_Neutron_detector_neutAmp_fDetMessages_);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages.fUniqueID", Neutron_detector_neutAmp_fDetMessages_fUniqueID, &b_Neutron_detector_neutAmp_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages.fBits", Neutron_detector_neutAmp_fDetMessages_fBits, &b_Neutron_detector_neutAmp_fDetMessages_fBits);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages.fDetector", Neutron_detector_neutAmp_fDetMessages_fDetector, &b_Neutron_detector_neutAmp_fDetMessages_fDetector);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages.fStation", Neutron_detector_neutAmp_fDetMessages_fStation, &b_Neutron_detector_neutAmp_fDetMessages_fStation);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages.fStChannel", Neutron_detector_neutAmp_fDetMessages_fStChannel, &b_Neutron_detector_neutAmp_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Neutron_detector_neutAmp.fDetMessages.fValue", Neutron_detector_neutAmp_fDetMessages_fValue, &b_Neutron_detector_neutAmp_fDetMessages_fValue);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.TGo4EventElement.fUniqueID", &Neutron_detector_neutTAC_TGo4EventElement_fUniqueID, &b_Neutron_detector_neutTAC_TGo4EventElement_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.TGo4EventElement.fBits", &Neutron_detector_neutTAC_TGo4EventElement_fBits, &b_Neutron_detector_neutTAC_TGo4EventElement_fBits);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.TGo4EventElement.fName", &Neutron_detector_neutTAC_TGo4EventElement_fName, &b_Neutron_detector_neutTAC_TGo4EventElement_fName);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.TGo4EventElement.fTitle", &Neutron_detector_neutTAC_TGo4EventElement_fTitle, &b_Neutron_detector_neutTAC_TGo4EventElement_fTitle);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.TGo4EventElement.fbIsValid", &Neutron_detector_neutTAC_TGo4EventElement_fbIsValid, &b_Neutron_detector_neutTAC_TGo4EventElement_fbIsValid);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.TGo4EventElement.fIdentifier", &Neutron_detector_neutTAC_TGo4EventElement_fIdentifier, &b_Neutron_detector_neutTAC_TGo4EventElement_fIdentifier);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages", &Neutron_detector_neutTAC_fDetMessages_, &b_Neutron_detector_neutTAC_fDetMessages_);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages.fUniqueID", Neutron_detector_neutTAC_fDetMessages_fUniqueID, &b_Neutron_detector_neutTAC_fDetMessages_fUniqueID);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages.fBits", Neutron_detector_neutTAC_fDetMessages_fBits, &b_Neutron_detector_neutTAC_fDetMessages_fBits);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages.fDetector", Neutron_detector_neutTAC_fDetMessages_fDetector, &b_Neutron_detector_neutTAC_fDetMessages_fDetector);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages.fStation", Neutron_detector_neutTAC_fDetMessages_fStation, &b_Neutron_detector_neutTAC_fDetMessages_fStation);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages.fStChannel", Neutron_detector_neutTAC_fDetMessages_fStChannel, &b_Neutron_detector_neutTAC_fDetMessages_fStChannel);
   fChain->SetBranchAddress("Neutron_detector_neutTAC.fDetMessages.fValue", Neutron_detector_neutTAC_fDetMessages_fValue, &b_Neutron_detector_neutTAC_fDetMessages_fValue);

    // Reading cal parameters 
  Float_t parXL1[32], parXL2[32],parYL1[16],parYL2[16],parXR1[32], parXR2[32],parYR1[16],parYR2[16],tPx_l1[32],tPx_l2[32],tPy_l1[16],tPy_l2[16],parCsR1[32],parCsR2[32];
  //------------------------------------------------------------------------------ 
 
  // for 1 mm Si detector
  TString line1;
  ifstream myfile1;
  Int_t count=-2;
  myfile1.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQX_R.cal");
  while (! myfile1.eof() ){
    line1.ReadLine(myfile1);
    if(count < 0){
      count++;
      continue;
    }
    if(line1.IsNull()) break;
    sscanf(line1.Data(),"%g %g", parXR1+count,parXR2+count);
    count++;
  }
  cout << endl << " pars for XR strips" << endl;
  for(Int_t i=0;i<32;i++) cout << parXR1[i] << " " << parXR2[i] << endl;  

  ifstream myfile2;
  TString line2;
  count=-2;
  myfile2.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQY_R.cal");
  while (! myfile2.eof() ){
    line2.ReadLine(myfile2);
    if(count < 0){
      count++;
      continue;
    }
    if(line2.IsNull()) break;
    sscanf(line2.Data(),"%g %g", parYR1+count,parYR2+count);
    count++;
  }

  cout << endl << " pars for YR strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parYR1[i] << " " << parYR2[i] << endl;   

  ifstream myfile3;
  TString line3;
  count=-2;
  myfile3.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQX_L.cal");
  while (! myfile3.eof() ){
    line3.ReadLine(myfile3);
    if(count < 0){
      count++;
      continue;
    }
    if(line3.IsNull()) break;
    sscanf(line3.Data(),"%g %g", parXL1+count,parXL2+count);
    count++;
  }

  cout << endl << " pars for XL strips" << endl;
  for(Int_t i=0;i<32;i++) cout << parXL1[i] << " " << parXL2[i] << endl;   

  ifstream myfile4;
  TString line4;
  count=-2;
  myfile4.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/SQY_L.cal");
  while (! myfile4.eof() ){
    line4.ReadLine(myfile4);
    if(count < 0){
      count++;
      continue;
    }
    if(line4.IsNull()) break;
    sscanf(line4.Data(),"%g %g", parYL1+count,parYL2+count);
    count++;
  }

  cout << endl << " pars for YL strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parYL1[i] << " " << parYL2[i] << endl;   

  // get pars for positions of times
  cout << endl << " time parameters " << endl;
  ifstream myfile5;
  TString line5;
  myfile5.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/tParX_L.clb");
  count = -2;
  while (! myfile5.eof() ){
    line5.ReadLine(myfile5);
    if(count < 0){
      count++;
      continue;
    }
    if(line5.IsNull()) break;
    sscanf(line5.Data(),"%g %g", tPx_l1+count,tPx_l2+count);
    count++;
  }
  cout << endl << " pars for X time positions" << endl;
  for(Int_t i=0;i<32;i++) cout << tPx_l1[i] << " " << tPx_l2[i] << endl;      

  ifstream myfile6;
  TString line6;
  myfile6.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/tParY_L.clb");
  count = -2;
  while (! myfile6.eof() ){
    line6.ReadLine(myfile6);
    if(count < 0){
      count++;
      continue;
    }
    if(line6.IsNull()) break;
    sscanf(line6.Data(),"%g %g", tPy_l1+count,tPy_l2+count);
    count++;
  }
  cout << endl << " pars for Y time positions" << endl;
  for(Int_t i=0;i<16;i++) cout << tPy_l1[i] << " " << tPy_l2[i] << endl;      

  ifstream myfile7;
  TString line7;
  count=-2;
  myfile7.open("/home/muzalevsky/work/exp1803/data/siCal/presentPars/csi_r_ec.clb");
  while (! myfile7.eof() ) {
    line7.ReadLine(myfile7);
    if(count < 0){
      count++;
      continue;
    }
    if(line7.IsNull()) break;
    sscanf(line7.Data(),"%g %g", parCsR1+count,parCsR2+count);
    count++;
  }  

  cout << endl << " pars for CsR strips" << endl;
  for(Int_t i=0;i<16;i++) cout << parCsR1[i] << " " << parCsR2[i] << endl; 
  //------------------------------------------------------------------------------ 

  // Creating outfile,outtree
 /* TFile *fw = new TFile("/media/analysis_nas/exp201804/analyze/temp/h5_14.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");
  tw->Branch("CsI_R",&CsI_R,"CsI_R[16]/F");
  tw->Branch("F3",&F3,"F3[4]/F");
  tw->Branch("F5",&F5,"F5[4]/F");
  tw->Branch("tF3",&tF3,"tF3[4]/F");
  tw->Branch("tF5",&tF5,"tF5[4]/F");
  tw->Branch("SQX_R",&SQX_R,"SQX_R[32]/F");
  tw->Branch("SQY_R",&SQY_R,"SQY_R[16]/F");
  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
  tw->Branch("tSQX_R",&tSQX_R,"tSQX_R[32]/F");
  tw->Branch("tSQY_R",&tSQY_R,"tSQY_R[16]/F");
  tw->Branch("tSQX_L",&tSQX_L,"tSQX_L[32]/F");
  tw->Branch("tSQY_L",&tSQY_L,"tSQY_L[16]/F");
  tw->Branch("multY_L",&multY_L,"multY_L/I");
  tw->Branch("multX_L",&multX_L,"multX_L/I");
  tw->Branch("trigger",&trigger,"trigger/I");*/

  //for(Int_t n=10;n<12;n++) {
  //  input_file.Form("/media/analysis_nas/exp201804/rootfiles/h5_14_00%d.root",n);		
  //  f[n] = new TFile(input_file.Data());
  //  if (f[n]->IsZombie()) {
	 //   cerr << "Input file was not opened " << input_file.Data() << endl;
	 //   return 1;
   // }
  //cout <<  input_file.Data() << " filename " << endl;
  //f[n]->GetObject("AnalysisxTree",t);


	//Left_telescope_SQY_L.fDetMessages.fValue
  Int_t nentries1 = fChain->GetEntries();
  cout << nentries1 << " is a number of entries" << endl;
  
return;
/*
  maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
  for (Long64_t jentry=0; jentry<maxE;jentry++) {
	  t->GetEntry(jentry);
    if(jentry%10000000==0) cout << "######## " << jentry << endl;
    // обнуление
    trigger=0;
    for(Int_t i = 0; i<32;i++) {
      thresh_X = 1;
      thresh_Y = 1;
      thresh_CsI = 1;
      timeF5 = 0;
     // multY_L = 0;
     // multX_L = 0;
      multY_R = 0;
      multX_R = 0;
      multCsi_R=0;
      SQX_R[i]=0.;
     // SQX_L[i]=0.;
      tSQX_R[i]=0.;
     // tSQX_L[i]=0.;
      if(i<16) {
        CsI_R[i]=0.;
        SQY_R[i]=0.;
      //  SQY_L[i]=0.;
        tSQY_R[i]=0.;
      //  tSQY_L[i]=0.;
        CsI_R[i] = 0;
      }
      if(i<4){
       // F3[i] = 0.;
       // F5[i] = 0.;
        tF5[i] = 0.;
       // tF3[i] = 0.;
      }
    }

    for(Int_t i=0; i<32; i++) {
      SQX_R[i] = NeEvent_SQX_R[i]*parXR2[i] + parXR1[i];
      //SQX_L[i] = NeEvent_SQX_L[i]*parXL2[i] + parXL1[i];
      if(SQX_R[i]>3) multX_R++; 
      if(SQX_R[i]>20) thresh_X=0; 
      tSQX_R[i] = NeEvent_tSQX_R[i]*0.3;
      //tSQX_L[i] = NeEvent_tSQX_L[i]*tPx_l2[i] + tPx_l1[i];
     // tSQX_L[i] = NeEvent_tSQX_L[i]*0.3;
      if(i<4) {
        //F3[i] = NeEvent_F3[i];
        //F5[i] = NeEvent_F5[i];
        //tF3[i] = NeEvent_tF3[i]*0.125;
        tF5[i] = NeEvent_tF5[i]*0.125;
      }
      if(i<16){
        CsI_R[i] = NeEvent_CsI_R[i]*parCsR2[i]+parCsR1[i];
        if(CsI_R[i]>0) multCsi_R++;
        if(CsI_R[i]>145) thresh_CsI=0;
        SQY_R[i] = NeEvent_SQY_R[i]*parYR2[i] + parYR1[i];
       // SQY_L[i] = NeEvent_SQY_L[i]*parYL2[i] + parYL1[i];
        if(SQY_R[i]>2.3) multY_R++; 
        if(SQY_R[i]>20) thresh_Y=0; 
        tSQY_R[i] = NeEvent_tSQY_R[i]*0.3;
        //tSQY_L[i] = NeEvent_tSQY_L[i]*tPy_l2[i] + tPy_l1[i];
       // tSQY_L[i] = NeEvent_tSQY_L[i]*0.3;
      }
    }
    for(Int_t j =0;j<32;j++){
      if(j<16 && (tF5[2]-tSQX_R[j])>-50 && (tF5[2]-tSQX_R[j])<50) timeF5++;
      if(j>15 && (tF5[2]-tSQX_R[j])>50 && (tF5[2]-tSQX_R[j])<100) timeF5++;
    }
    trigger = NeEvent_trigger;
	  if(multX_R>0 && multY_R>0 && timeF5>0 && multCsi_R>0 && thresh_Y==1 && thresh_X==1 && thresh_CsI==1) {
      tw->Fill();
    }			
  }//entries
  fw->cd();
	tw->Write();
	fw->Close();*/
}
