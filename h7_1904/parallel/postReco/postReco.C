#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/ivan/work/macro/h7_1904/cuts/scripts/create_IDs.C"
#include "/home/ivan/work/macro/h7_1904/cuts/scripts/er_cuts.C"

#include "/home/ivan/work/macro/h7_1904/parallel/reco/recoInput.h"
#include "/home/ivan/work/macro/h7_1904/parallel/reco/recoOutput.h"

void postReco() {
  
  create_IDs();

  cout << create_he3_cut(1) << endl;

return;

  TString inputRecoFile("/media/ivan/data/exp1904/ERanalysis/reco/h7_ct_00_0001.reco.root");
  TChain *chReco = new TChain("er");
  chReco->Add(inputRecoFile.Data());

  TString inputCleanedFile("/media/ivan/data/exp1904/ERanalysis/cleaned/h7_ct_00_0001.cleaned.root");
  TChain *chCleaned = new TChain("er");
  chCleaned->Add(inputCleanedFile.Data());

  chReco->AddFriend(chCleaned);
  cout << chReco->GetEntries() << endl;

  TClonesArray *v_track_beam = new TClonesArray("ERBeamDetTrack");
  TClonesArray* v_par_beam = new TClonesArray("ERBeamDetParticle");

  TClonesArray *v_track_cent = new TClonesArray("ERTelescopeTrack");
  TClonesArray* v_par_cent = new TClonesArray("ERTelescopeParticle"); 

  TClonesArray *v_track_t1 = new TClonesArray("ERTelescopeTrack");
  TClonesArray* v_par_he3_t1 = new TClonesArray("ERTelescopeParticle"); 
  TClonesArray* v_par_he4_t1 = new TClonesArray("ERTelescopeParticle"); 

  TClonesArray *v_track_t2 = new TClonesArray("ERTelescopeTrack");
  TClonesArray* v_par_he3_t2 = new TClonesArray("ERTelescopeParticle");
  TClonesArray* v_par_he4_t2 = new TClonesArray("ERTelescopeParticle"); 

  TClonesArray *v_track_t3 = new TClonesArray("ERTelescopeTrack");
  TClonesArray* v_par_he3_t3 = new TClonesArray("ERTelescopeParticle");
  TClonesArray* v_par_he4_t3 = new TClonesArray("ERTelescopeParticle"); 

  TClonesArray *v_track_t4 = new TClonesArray("ERTelescopeTrack");
  TClonesArray* v_par_he3_t4 = new TClonesArray("ERTelescopeParticle");
  TClonesArray* v_par_he4_t4 = new TClonesArray("ERTelescopeParticle"); 

  chReco->SetBranchAddress("BeamDetTrack",&v_track_beam);
  chReco->SetBranchAddress("BeamDetParticle.",&v_par_beam);

  // PARTICLE = tritons
  chReco->SetBranchAddress("TelescopeTrack_Central_telescope_DoubleSi_DSD_XY",&v_track_cent);
  chReco->SetBranchAddress("TelescopeParticle_Central_telescope_DoubleSi_DSD_XY_1000010030",&v_par_cent);

  // PARTICLE = 3,4He
  chReco->SetBranchAddress("TelescopeTrack_Telescope_1_SingleSi_SSD20_1_XTelescope_1_SingleSi_SSD_1_Y",&v_track_t1);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_1_SingleSi_SSD20_1_XTelescope_1_SingleSi_SSD_1_Y_1000020030",&v_par_he3_t1);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_1_SingleSi_SSD20_1_XTelescope_1_SingleSi_SSD_1_Y_1000020040",&v_par_he4_t1);

  chReco->SetBranchAddress("TelescopeTrack_Telescope_2_SingleSi_SSD_2_XTelescope_2_SingleSi_SSD20_2_Y",&v_track_t2);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_2_SingleSi_SSD_2_XTelescope_2_SingleSi_SSD20_2_Y_1000020030",&v_par_he3_t2);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_2_SingleSi_SSD_2_XTelescope_2_SingleSi_SSD20_2_Y_1000020040",&v_par_he4_t2);

  chReco->SetBranchAddress("TelescopeTrack_Telescope_3_SingleSi_SSD20_3_XTelescope_3_SingleSi_SSD_3_Y",&v_track_t3);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_3_SingleSi_SSD20_3_XTelescope_3_SingleSi_SSD_3_Y_1000020030",&v_par_he3_t3);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_3_SingleSi_SSD20_3_XTelescope_3_SingleSi_SSD_3_Y_1000020040",&v_par_he4_t3);

  chReco->SetBranchAddress("TelescopeTrack_Telescope_4_SingleSi_SSD_4_XTelescope_4_SingleSi_SSD20_4_Y",&v_track_t4);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_4_SingleSi_SSD_4_XTelescope_4_SingleSi_SSD20_4_Y_1000020030",&v_par_he3_t4);
  chReco->SetBranchAddress("TelescopeParticle_Telescope_4_SingleSi_SSD_4_XTelescope_4_SingleSi_SSD20_4_Y_1000020040",&v_par_he4_t4);


  for (Int_t nentry=0;nentry<1000;nentry++) {

    chReco->GetEntry(nentry);

    //------------------------------------------------------------------------------------------------
    if (v_track_beam->GetEntries()==1 && v_par_beam->GetEntries()==1) {
      lv_he8 = ((ERBeamDetParticle*)v_par_beam->At(0))->GetLVTarget();
      fXt = ((ERBeamDetTrack*)v_track_beam->At(0))->GetTargetX();
      fYt = ((ERBeamDetTrack*)v_track_beam->At(0))->GetTargetY();
      // cout << lv_he8.T() - lv_he8.Mag() << endl;
    }
    //------------------------------------------------------------------------------------------------

    //------------------------------------------------------------------------------------------------
    if (v_track_cent->GetEntries()==1 && v_par_cent->GetEntries()==1) {
      lv_h3 = ((ERTelescopeParticle*)v_par_beam->At(0))->GetLVInteraction();
      X_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetXEdep();
      Y_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetYEdep();

      nX_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetXChannel(); 
      nY_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetYChannel(); 
      
      aCsI = ((ERTelescopeParticle*)v_par_cent->At(0))->GetCorrectedEdepInThickStation();
      nCsI = ((ERTelescopeParticle*)v_par_cent->At(0))->ChannelOfThickStation();

      // if ()


    }
    //------------------------------------------------------------------------------------------------


  }

  return;

}