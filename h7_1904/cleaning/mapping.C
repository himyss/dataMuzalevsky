void mapping(TString inFile,TString outFile) {
  // create_cuts();  
  // inFile  = "/mnt/data/exp1904/digi/h7_final/h7_ct_00_0001.digi.root";
  TFile *f_in = new TFile(inFile.Data());
  if (f_in->IsZombie()) {
    cerr << "File " << inFile.Data() << " does not exist" << endl;
    exit(1);
  }
  TTree *in_tree = (TTree*)f_in->Get("er");
  if (in_tree->IsZombie()) {
    cerr << "Tree er in file" << inFile.Data() << " does not exist" << endl;
    exit(1);   
  }
  Int_t nEvents = in_tree->GetEntries();

  // outFile = "/mnt/data/exp1904/cleaned/h7_final/h7_ct_00_0001.clean.root";
  TString parFile = "/home/muzalevskii/work/expertroot/macro/EXP1904_H7/sim/par.root";
  TString parFolder = "/home/muzalevskii/work/macro/h7_1904/cleaning/pars/";
  // ------------------------------------------------------------------------
  TStopwatch timer;
  timer.Start();  
  // ------------------------------------------------------------------------
  ERRunAna *run = ERRunAna::Instance();
  run->HoldEventsCount(); //forbid different entry number in the input and output file
  run->WithoutGeant(); //do not init Geant
  run->SetUserCut("");
  run->SetInputFile(inFile);
  run->SetOutputFile(outFile);
  ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();
  run->SetEventHeader(header);  
  // ------------------------------------------------------------------------
  ERDigiCleaner* cleaner = new ERDigiCleaner();

  cleaner->SetLonelyMWPCClusterCondition();
  // "" - do not recalibrate

  // SSD20_1 
  // cleaner->Recalibrate("Telescope_1", "SSD20_1", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                      parFolder + "empty16.cal" previous amp calibration ,
  //                      parFolder + "SSD_20u_1_cal.cal" /*new amp calibration*/
  //                      // &raw2simChannelsMapping - like in digibuiler
  //                      );

  // SSD_1 
  //cleaner->Recalibrate("Telescope_1", "SSD_1", "" /*previous time calibration*/, ""/*new time calibration*/,
   //                    parFolder + "empty16.cal" /*previous amp calibration*/ ,
   //                    parFolder + "SSD_1m_1_cal.cal" /*new amp calibration*/
   //                    // &raw2simChannelsMapping - like in digibuiler
    //                   );

  // SSDV_1 
  //cleaner->Recalibrate("Telescope_1", "SSD_V_1", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_1m_1_v_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
  //                     );

  //----------------------------------------------------------------------------------------------------------
  // SSD20_2 
  //cleaner->Recalibrate("Telescope_2", "SSD20_2", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_20u_2_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
  //                     );


  // SSD_2 
  //cleaner->Recalibrate("Telescope_2", "SSD_2", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_1m_2_cal.cal" /*new amp calibration*/
   //                    // &raw2simChannelsMapping - like in digibuiler
  //                     );

  // SSDV_2
  //cleaner->Recalibrate("Telescope_2", "SSD_V_2", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_1m_2_v_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
  //                     );

  //-----------------------------------------------------------------------------------------------------------
  // SSD20_3 
  //cleaner->Recalibrate("Telescope_3", "SSD20_3", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
   //                    parFolder + "SSD_20u_3_cal.cal" /*new amp calibration*/
   //                    // &raw2simChannelsMapping - like in digibuiler
   //                    );


  // SSD_3 
  //cleaner->Recalibrate("Telescope_3", "SSD_3", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_1m_3_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
   //                    );


  // SSDV_3
  //cleaner->Recalibrate("Telescope_3", "SSD_V_3", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_1m_3_v_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
   //                    );

  //-----------------------------------------------------------------------------------------------------------
  // SSD20_4
  //cleaner->Recalibrate("Telescope_4", "SSD20_4", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_20u_4_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
  //                     );

  // SSD_4 
  //cleaner->Recalibrate("Telescope_4", "SSD_4", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
   //                    parFolder + "SSD_1m_4_cal.cal" /*new amp calibration*/
   //                    // &raw2simChannelsMapping - like in digibuiler
   //                    );

  // SSDV_4
  //cleaner->Recalibrate("Telescope_4", "SSD_V_4", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty16.cal" /*previous amp calibration*/ ,
  //                     parFolder + "SSD_1m_4_v_cal.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
  //                     );

  //-------------------------------------------------------------------------------------------------------------------
  // DSSD_X
  //cleaner->Recalibrate("Central_telescope", "DSD_XY_0_X", "" /*previous time calibration*/, ""/*new time calibration*/,
  //                     parFolder + "empty32.cal" /*previous amp calibration*/ ,
  //                    parFolder + "DSSD_X.cal" /*new amp calibration*/
  //                     // &raw2simChannelsMapping - like in digibuiler
  //                     );

  // DSSD_Y
  //cleaner->Recalibrate("Central_telescope", "DSD_XY_0_Y", "" /*previous time calibration*/, ""/*new time calibration*/,
   //                    parFolder + "empty32.cal" /*previous amp calibration*/ ,
  //                     parFolder + "DSSD_Y.cal" /*new amp calibration*/
   //                    // &raw2simChannelsMapping - like in digibuiler
   //                    );

  //---------------------------------------------------------------------------------------------------------------------
  // CsI

  std::map<Int_t, Int_t> csiMapping = {
    {0,    15},
    {1,    11},
    {2,    7},
    {3,    3},
    {4,    14},
    {5,    10},
    {6,    6},
    {7,    2},
    {8,    13},
    {9,    9},
    {10,   5},
    {11,   1},
    {12,   12},
    {13,   8},
    {14,   4},
    {15,   0} 
  };

  cleaner->Recalibrate("Central_telescope", "CsI", "" /*previous time calibration*/, ""/*new time calibration*/,
                       "" /*previous amp calibration*/ ,
                       "", /*new amp calibration*/
                       &csiMapping //- like in digibuiler
                       );

  run->AddTask(cleaner);
  // ------------------------------------------------------------------------
  FairRuntimeDb* rtdb = run->GetRuntimeDb();
  FairParRootFileIo*  parIO = new FairParRootFileIo();
  parIO->open(parFile.Data(), "UPDATE");
  rtdb->setFirstInput(parIO);
  // ------------------------------------------------------------------------
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  run->Init();
  run->Run(0, nEvents);
  // ------------------------------------------------------------------------
  rtdb->setOutput(parIO);
  rtdb->saveOutput();
  // ------------------------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t Central_telescopeime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file writen:  "    << outFile << endl;    
  cout << "Real time " << rtime << " s, CPU time " << Central_telescopeime << " s" << endl;
  cout << endl;
}