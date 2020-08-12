TString MakeConditionBeamID();
TString MakeConditionMWPCtime();

#include "/home/muzalevskii/work/macro/exp2001/beamCut.C"

void digibuilder(TString InFile, TString OutFile) {

  beamCut();

  TString inputdir = gSystem->Getenv("VMCWORKDIR");

  inputdir = "/home/muzalevskii/work/macro/h7_1904/parameters/";

  TString confFile = "/home/muzalevskii/work/macro/exp2001/digi/setupEXP2001.xml";

  TChain *ch = new TChain("stepRepackingxTree");
  ch->Add(InFile.Data());
  Int_t nEvents = ch->GetEntries();
  delete ch;
  cout << nEvents << " will be processed" << endl;
  std::cout << ">>> input file is " << InFile  << std::endl;
  std::cout << ">>> output file is " << OutFile << std::endl;

  // --- Source task
  ERDigibuilder* builder = new ERDigibuilder();
  builder->SetConfigurationFile(confFile);

  // UserCuts
  TString cut("");
  cut+=("DetEventCommon.trigger==1 && ");
  cut+=("Beam_detector_MWPC1.@fData.GetEntries()>0 && ");
  cut+=("Beam_detector_MWPC2.@fData.GetEntries()>0 && ");
  cut+=("Beam_detector_MWPC3.@fData.GetEntries()>0 && ");
  cut+=("Beam_detector_MWPC4.@fData.GetEntries()>0 && ");

  cut+=("Beam_detector_tMWPC.@fData.GetEntries()>0 && ");

  cut+=("Beam_detector_tF3.@fData.GetEntries()==4 && ");  
  cut+=("Beam_detector_tF5.@fData.GetEntries()==4 && ");   
  cut+=("Beam_detector_F3.@fData.GetEntries()==4 && ");
  cut+=("Beam_detector_F5.@fData.GetEntries()==4");

  cut.Append(" && " + (TString)cutF5_cal->GetName() + " && ");
  cut.Append((TString)cutF3_cal->GetName());
  cut.Append(" && " + MakeConditionMWPCtime());  


  cout << " Its my cut " << endl;
  cout << cut.Data() << endl;
  builder->SetUserCut(cut.Data(),kFALSE);

  builder->AddFile(InFile);

  ERBeamDetUnpack* beamDetUnpack = new ERBeamDetUnpack("Beam_detector");
  beamDetUnpack->SetToFCalibration(0.0625, 0., 0.0625, 0.); //aF3, bF3, aF5, bF5
  beamDetUnpack->SetMWPCCalibration(0.0625,0.);
  
  
  builder->AddUnpack(beamDetUnpack);

  // --- Run
  FairRunOnline *run = new FairRunOnline(builder);
  run->SetOutputFile(OutFile);

  ERBeamTimeEventHeader* header = new ERBeamTimeEventHeader();
  run->SetEventHeader(header);

  // -----   Logger settings --------------------------------------------
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");

  // --- Start run
  TStopwatch timer;
  timer.Start();
  std::cout << ">>> Starting run..." << std::endl;
  run->Init();
  run->Run(0,nEvents);

  timer.Stop();
  
  // --- End-of-run info
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  std::cout << std::endl << std::endl;
  std::cout << ">>> Macro finished successfully." << std::endl;
  std::cout << ">>> Output file is " << OutFile << std::endl;
  std::cout << ">>> Real time " << rtime << " s, CPU time "
            << ctime << " s" << std::endl;
}


TString MakeConditionMWPCtime() {

  ////////////////////////////////////////////
  //time in MWPC
  ////////////////////////////////////////////

  TString timeF5 = "0.0625*0.25*(Beam_detector_tF5.fData.fValue[0]"
                "+Beam_detector_tF5.fData.fValue[1]"
                "+Beam_detector_tF5.fData.fValue[2]"
                "+Beam_detector_tF5.fData.fValue[3])";

  TString tMWPCX1 = "0.0625*Beam_detector_tMWPC.fData.fValue[0]";
  TString tMWPCY1 = "0.0625*Beam_detector_tMWPC.fData.fValue[1]";
  TString tMWPCX2 = "0.0625*Beam_detector_tMWPC.fData.fValue[2]";
  TString tMWPCY2 = "0.0625*Beam_detector_tMWPC.fData.fValue[3]";

  TString condition = "( ("+tMWPCX1+"-"+timeF5+")>55. && ("+tMWPCX1+"-"+timeF5+")<85."
          +" && ("+tMWPCY1+"-"+timeF5+")>55. && ("+tMWPCY1+"-"+timeF5+")<85."
          +" && ("+tMWPCX2+"-"+timeF5+")>55. && ("+tMWPCX2+"-"+timeF5+")<85."
          +" && ("+tMWPCY2+"-"+timeF5+")>55. && ("+tMWPCY2+"-"+timeF5+")<85.)";

  return condition;
}