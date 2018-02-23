void eventDisplay()
{
  FairRunAna *fRun= new FairRunAna();

  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo*  parIo1 = new FairParRootFileIo();
  parIo1->open("/store/ivan/EXP1803/Telescope1/par.root");
  rtdb->setFirstInput(parIo1);
  //rtdb->print();

  fRun->SetInputFile("/store/ivan/EXP1803/Telescope1/sim_digi.root");
  fRun->SetOutputFile("/store/ivan/EXP1803/Telescope1/EventDisplay.root");

  FairEventManager *fMan= new FairEventManager();
  FairMCTracks *Track =  new FairMCTracks ("Monte-Carlo Tracks");

  fMan->AddTask(Track);

  fMan->Init();
}
