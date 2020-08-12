#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"

void calculateBeam();
void zeroVars();

//outtree vars
Int_t trigger; 

Float_t tF5,F5,tF3,F3;

Float_t tMWPC;
Float_t wirex1,wirex2,wirey1,wirey2;

// reconstructed
Float_t fXt,fYt;
Float_t x1c, y1c, x2c, y2c;

TLorentzVector he8;

void selection(TString InFile, TString OutFile) {

  TChain *ch = new TChain("tree");
  // TString inPutFileName;
  // inPutFileName.Form("/mnt/data/exp1904/analysed/cal/h7/h7_ct_%d_cal.root",nFile);
  // inPutFileName.Form("/mnt/data/exp1904/ERanalysis/tests/reco/test_convert.root",nFile);
  ch->Add(InFile.Data());


  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  ch->SetBranchAddress("trigger",&trigger);

  ch->SetBranchAddress("F5.",&F5);
  ch->SetBranchAddress("tF5.",&tF5);
  ch->SetBranchAddress("F3.",&F3);
  ch->SetBranchAddress("tF3.",&tF3);

  ch->SetBranchAddress("tMWPC.",&tMWPC);
  ch->SetBranchAddress("wirex1.",&wirex1);
  ch->SetBranchAddress("wirex2.",&wirex2);
  ch->SetBranchAddress("wirey1.",&wirey1);
  ch->SetBranchAddress("wirey2.",&wirey2);

  ch->SetBranchAddress("x1c.",&x1c); // position in MWPC in mm
  ch->SetBranchAddress("y1c.",&y1c);
  ch->SetBranchAddress("x2c.",&x2c);
  ch->SetBranchAddress("y2c.",&y2c); 
  ch->SetBranchAddress("fXt.",&fXt); // beam profile at the target plane
  ch->SetBranchAddress("fYt.",&fYt);

  // TString outPutFileName;
  // outPutFileName.Form("/media/ivan/data/exp1904/analysed/novPars/beamDiagnostics/selected/h7_ct_%d_cut_newPars.root",nFile);
  // outPutFileName.Form("/mnt/data/exp1904/analysed/selected/h7/h7_ct_%d_cut.root",nFile);
  // outPutFileName.Form("temp1.root");
  // outPutFileName.Form("/mnt/data/exp1904/ERanalysis/tests/selected/selected.root",nFile);

  TFile *fw = new TFile(OutFile.Data(), "RECREATE");
  // TFile *fw = new TFile("test.root", "RECREATE");
  TTree *tw = new TTree("tree", "data");

  tw->Branch("trigger.",&trigger,"trigger/I");

  tw->Branch("F5.",&F5,"F5/F");
  tw->Branch("tF5.",&tF5,"tF5/F");
  tw->Branch("F3.",&F3,"F3/F");
  tw->Branch("tF3.",&tF3,"tF3/F");

  tw->Branch("tMWPC.",&tMWPC,"tMWPC/F");
  tw->Branch("wirex1.",&wirex1,"wirex1/F");
  tw->Branch("wirex2.",&wirex2,"wirex2/F");
  tw->Branch("wirey1.",&wirey1,"wirey1/F");
  tw->Branch("wirey2.",&wirey2,"wirey2/F");
 
  tw->Branch("x1c.",&x1c,"x1c/F");
  tw->Branch("y1c.",&y1c,"y1c/F");
  tw->Branch("x2c.",&x2c,"x2c/F");
  tw->Branch("y2c.",&y2c,"y2c/F"); 
  tw->Branch("fXt.",&fXt,"fXt/F");
  tw->Branch("fYt.",&fYt,"fYt/F"); 

  tw->Branch("he8","TLorentzVector",&he8);

  for(Int_t nentry=0;nentry<ch->GetEntries();nentry++) { 
  // for(Int_t nentry=0;nentry<10;nentry++) {     
    if(nentry%1000000==0) cout << "#ENTRY " << nentry << "#" << endl;

    ch->GetEntry(nentry);


    zeroVars();

    calculateBeam();

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;
}

void zeroVars() {

  he8.SetXYZT(0,0,0,0);

}

void calculateBeam() {

  TVector3 dir;
  dir.SetXYZ(fXt-x1c,fYt-y1c,815.);
  // dir.SetXYZ(x2c-x1c,y2c-y1c,545.);  
  Double_t phi = dir.Phi();
  Double_t theta = dir.Theta();

  Double_t len = dir.Mag();

  Double_t mass = 8.406868788;

  Double_t velocity = 12320./(tF5-tF3 + 68.475);
  Double_t beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  Double_t kinEnergy = mass*((1/beta) - 1);

  // cout << tF5-tF3 + 68.475 << " " << 1000*kinEnergy << endl;;

  // velocity = 12320./(tF5-tF3 + 68.475);
  // beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  // kinEnergy = mass*((1/beta) - 1);

  // cout << 1000*kinEnergy << " ";

  // velocity = 12320./(tF5-tF3 + 68.475+1);
  // beta = sqrt(1 - (velocity*velocity/(299.792458*299.792458) ) );
  // kinEnergy = mass*((1/beta) - 1);

  // cout << 1000*kinEnergy << endl;

  Double_t momentum = sqrt(kinEnergy*kinEnergy + 2*kinEnergy*mass);

  momentum = TMath::Abs(momentum);

  he8.SetXYZM(momentum*TMath::Sin(theta)*TMath::Cos(phi), momentum*TMath::Sin(theta)*TMath::Sin(phi), momentum*TMath::Cos(theta) ,mass);

  return;
}