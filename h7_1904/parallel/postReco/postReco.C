void zeroVars();

void centID();
void sideID_1();
void sideID_2();
void sideID_3();
void sideID_4();

void neutronID(TClonesArray *v_track, TClonesArray *v_par);
void reco7H();
void reco6H();

#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_cuts.C"
#include "/home/muzalevskii/work/macro/h7_1904/cuts/scripts/create_IDs.C"
#include "/home/muzalevskii/work/macro/h7_1904/parallel/postReco/myCuts.C"

#include "/home/muzalevskii/work/macro/h7_1904/parallel/postReco/data_in.h"
#include "/home/muzalevskii/work/macro/h7_1904/parallel/postReco/data_out.h"

void postReco(Int_t nRun = 0) {
  
  create_IDs();

  TString inputRecoFile; 
  inputRecoFile.Form("/mnt/data/exp1904/ERanalysis/reco/h7/h7_ct_%d*.reco.root",nRun);
  
  TChain *chReco = new TChain("er");
  chReco->Add(inputRecoFile.Data());
  cout << chReco->GetEntries() << endl;

  TString inputCleanedFile;
  inputCleanedFile.Form("/mnt/data/exp1904/digi/h7/h7_ct_%d*.digi.root",nRun);
  TChain *chCleaned = new TChain("er");
  chCleaned->Add(inputCleanedFile.Data());
  cout << chCleaned->GetEntries() << endl;

  chReco->AddFriend(chCleaned);
  
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

  TClonesArray *v_track_nd = new TClonesArray("ERNDTrack");
  TClonesArray* v_par_nd = new TClonesArray("ERNDParticle");


  TClonesArray *v_SSD_V_1 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD20_1 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD_1 = new TClonesArray("ERDigi");

  TClonesArray *v_SSD_V_2 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD20_2 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD_2 = new TClonesArray("ERDigi");

  TClonesArray *v_SSD_V_3 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD20_3 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD_3 = new TClonesArray("ERDigi");

  TClonesArray *v_SSD_V_4 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD20_4 = new TClonesArray("ERDigi");
  TClonesArray *v_SSD_4 = new TClonesArray("ERDigi");

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

  // neutrons
  chReco->SetBranchAddress("NDTrack",&v_track_nd);
  chReco->SetBranchAddress("NDParticle",&v_par_nd);

  // digi
  chReco->SetBranchAddress("TelescopeDigi_Telescope_1_SingleSi_SSD20_1_X",&v_SSD20_1);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_1_SingleSi_SSD_1_Y",&v_SSD_1);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_1_SingleSi_SSD_V_1_Y",&v_SSD_V_1);  
 
  chReco->SetBranchAddress("TelescopeDigi_Telescope_2_SingleSi_SSD20_2_Y",&v_SSD20_2);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_2_SingleSi_SSD_2_X",&v_SSD_2);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_2_SingleSi_SSD_V_2_X",&v_SSD_V_2);  

  chReco->SetBranchAddress("TelescopeDigi_Telescope_3_SingleSi_SSD20_3_X",&v_SSD20_3);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_3_SingleSi_SSD_3_Y",&v_SSD_3);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_3_SingleSi_SSD_V_3_Y",&v_SSD_V_3);  

  chReco->SetBranchAddress("TelescopeDigi_Telescope_4_SingleSi_SSD20_4_Y",&v_SSD20_4);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_4_SingleSi_SSD_4_X",&v_SSD_4);
  chReco->SetBranchAddress("TelescopeDigi_Telescope_4_SingleSi_SSD_V_4_X",&v_SSD_V_4);  

//------------------------------------------------------------------------------------------------
  TString outPutFileName;
  outPutFileName.Form("/mnt/data/exp1904/ERanalysis/postReco/h7/h7_ct_%d_mm.root",nRun);

  TFile *fw = new TFile(outPutFileName.Data(), "RECREATE");
  TTree *tw = new TTree("tree", "data");
 
  tw->Branch("aCsI.",&aCsI,"aCsI/F");
  tw->Branch("nCsI.",&nCsI,"nCsI/I");

  tw->Branch("X_C.",&X_C,"X_C/F");
  tw->Branch("nX_C.",&nX_C,"nX_C/I");
  tw->Branch("Y_C.",&Y_C,"Y_C/F");
  tw->Branch("nY_C.",&nY_C,"nY_C/I");
 
  tw->Branch("fXt.",&fXt,"fXt/F");
  tw->Branch("fYt.",&fYt,"fYt/F"); 

  tw->Branch("a20_1.",&a20_1,"a20_1/F");
  tw->Branch("a20_1_un.",&a20_1_un,"a20_1_un/F");
  tw->Branch("n20_1.",&n20_1,"n20_1/I");

  tw->Branch("a1_1_un.",&a1_1_un,"a1_1_un/F");
  tw->Branch("a1_1.",&a1_1,"a1_1/F");
  tw->Branch("n1_1.",&n1_1,"n1_1/I");

  tw->Branch("a20_2.",&a20_2,"a20_2/F");
  tw->Branch("a20_2_un.",&a20_2_un,"a20_2_un/F");
  tw->Branch("n20_2.",&n20_2,"n20_2/I");

  tw->Branch("a1_2_un.",&a1_2_un,"a1_2_un/F");
  tw->Branch("a1_2.",&a1_2,"a1_2/F");
  tw->Branch("n1_2.",&n1_2,"n1_2/I");

  tw->Branch("a20_3.",&a20_3,"a20_3/F");
  tw->Branch("a20_3_un.",&a20_3_un,"a20_3_un/F");
  tw->Branch("n20_3.",&n20_3,"n20_3/I");

  tw->Branch("a1_3_un.",&a1_3_un,"a1_3_un/F");
  tw->Branch("a1_3.",&a1_3,"a1_3/F");
  tw->Branch("n1_3.",&n1_3,"n1_3/I");

  tw->Branch("a20_4.",&a20_4,"a20_4/F");
  tw->Branch("a20_4_un.",&a20_4_un,"a20_4_un/F");
  tw->Branch("n20_4.",&n20_4,"n20_4/I");

  tw->Branch("a1_4_un.",&a1_4_un,"a1_4_un/F");
  tw->Branch("a1_4.",&a1_4,"a1_4/F");
  tw->Branch("n1_4.",&n1_4,"n1_4/I");

  tw->Branch("SSD_V1",&SSD_V1,"SSD_V1[16]/F");
  tw->Branch("tSSD_V1",&tSSD_V1,"tSSD_V1[16]/F");
  tw->Branch("SSD_V2",&SSD_V2,"SSD_V2[16]/F");
  tw->Branch("tSSD_V2",&tSSD_V2,"tSSD_V2[16]/F");
  tw->Branch("SSD_V3",&SSD_V3,"SSD_V3[16]/F");
  tw->Branch("tSSD_V3",&tSSD_V3,"tSSD_V3[16]/F");
  tw->Branch("SSD_V4",&SSD_V4,"SSD_V4[16]/F");
  tw->Branch("tSSD_V4",&tSSD_V4,"tSSD_V4[16]/F");

  tw->Branch("multv_1.",&multv_1,"multv_1/I");
  tw->Branch("multv_2.",&multv_2,"multv_2/I");
  tw->Branch("multv_3.",&multv_3,"multv_3/I");
  tw->Branch("multv_4.",&multv_4,"multv_4/I");

  tw->Branch("flag1.",&flag1,"flag1/I");
  tw->Branch("flag2.",&flag2,"flag2/I");
  tw->Branch("flag3.",&flag3,"flag3/I");
  tw->Branch("flag4.",&flag4,"flag4/I");
  tw->Branch("flagCent.",&flagCent,"flagCent/I");
  tw->Branch("neutron.",&neutron,"neutron/I");
  tw->Branch("gammma.",&gammma,"gammma/I");

  tw->Branch("ND_amp",&ND_amp,"ND_amp[32]/F");
  tw->Branch("ND_time",&ND_time,"ND_time[32]/F");
  tw->Branch("ND_tac",&ND_tac,"ND_tac[32]/F");

  tw->Branch("nh3.",&nh3,"nh3/I");
  tw->Branch("nhe3_1.",&nhe3_1,"nhe3_1/I");
  tw->Branch("nhe3_2.",&nhe3_2,"nhe3_2/I");
  tw->Branch("nhe3_3.",&nhe3_3,"nhe3_3/I");
  tw->Branch("nhe3_4.",&nhe3_4,"nhe3_4/I");

  tw->Branch("nhe4_1.",&nhe4_1,"nhe4_1/I");
  tw->Branch("nhe4_2.",&nhe4_2,"nhe4_2/I");
  tw->Branch("nhe4_3.",&nhe4_3,"nhe4_3/I");
  tw->Branch("nhe4_4.",&nhe4_4,"nhe4_4/I"); 

// Lorentz Vectors

  tw->Branch("lv_he8","TLorentzVector",&lv_he8);
  
  tw->Branch("lv_h7","TLorentzVector",&lv_h7);
  tw->Branch("lv_he3","TLorentzVector",&lv_he3);
  tw->Branch("lv_h3","TLorentzVector",&lv_h3);
  tw->Branch("lv_h3_CMH7","TLorentzVector",&lv_h3_CMH7);
  tw->Branch("lv_h7_CMR","TLorentzVector",&lv_h7_CMR);

  tw->Branch("lv_he4","TLorentzVector",&lv_he4);
  tw->Branch("lv_h3_CMH6","TLorentzVector",&lv_h3_CMH6);
  tw->Branch("lv_h6","TLorentzVector",&lv_h6);
  tw->Branch("lv_h6_CMR","TLorentzVector",&lv_h6_CMR);

// arrays 
  tw->Branch("ND_time",&ND_time,"ND_time[32]/F");
  tw->Branch("ND_amp",&ND_amp,"ND_amp[32]/F");
  tw->Branch("ND_tac",&ND_tac,"ND_tac[32]/F");

//------------------------------------------------------------------------------------------------

  lv_d2.SetXYZT(0.,0.,0.,1875.612);

  // for (Int_t nentry=0;nentry<chReco->GetEntries();nentry++) {
  for (Int_t nentry=0;nentry<1000;nentry++) {

    zeroVars();

    chReco->GetEntry(nentry);

    if (v_track_beam->GetEntries()==0 || v_par_beam->GetEntries()==0) continue;

    //------------------------------------------------------------------------------------------------
    lv_he8 = ((ERBeamDetParticle*)v_par_beam->At(0))->GetLVTarget();
    fXt = ((ERBeamDetTrack*)v_track_beam->At(0))->GetTargetX();
    fYt = ((ERBeamDetTrack*)v_track_beam->At(0))->GetTargetY();
    if ( ((fXt  -0.0467)*(fXt-0.0467) + (fYt-0.0026)*(fYt-0.0026))>1 ) continue;
    lv_R = lv_he8 + lv_d2;
    //------------------------------------------------------------------------------------------------
    if (v_track_cent->GetEntries()==1 && v_par_cent->GetEntries()==1) {
      // lv_h3 = ((ERTelescopeParticle*)v_par_beam->At(0))->GetLVInteraction();
      X_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetXEdep();
      Y_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetYEdep();

      nX_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetXChannel(); 
      nY_C = ((ERTelescopeTrack*)v_track_cent->At(0))->GetYChannel(); 
      
      aCsI = ((ERTelescopeParticle*)v_par_cent->At(0))->GetCorrectedEdepInThickStation();
      nCsI = ((ERTelescopeParticle*)v_par_cent->At(0))->ChannelOfThickStation();

      if (nCsI>-1 && nCsI<16 && nX_C>-1 && nX_C<32 && nY_C>-1 && nY_C<32) flagCent=1;
      else flagCent=0;

      if (flagCent) centID();
      if (nh3) lv_h3 = ((ERTelescopeParticle*)v_par_cent->At(0))->GetLVInteraction();
    }
    //------------------------------------------------------------------------------------------------
    for(Int_t i=0;i<v_SSD_V_1->GetEntries();i++) {
      Int_t numCh_tmp = ((ERDigi*)v_SSD_V_1->At(i))->Channel();
      SSD_V1[numCh_tmp] = ((ERDigi*)v_SSD_V_1->At(i))->Edep();
      tSSD_V1[numCh_tmp] = ((ERDigi*)v_SSD_V_1->At(i))->Time();
      if (SSD_V1[numCh_tmp]>0 && tSSD_V1[numCh_tmp]>0) multv_1++;
    }

    if (v_track_t1->GetEntries()==1 && v_par_he3_t1->GetEntries()==1) {

      a20_1 = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->GetCorrectedEdepInThinStation();
      a1_1 = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->GetCorrectedEdepInThickStation();
      a20_1_un = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->GetEdepInThinStation();
      a1_1_un = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->GetEdepInThickStation();

      n20_1 = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->ChannelOfThinStation();
      n1_1 = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->ChannelOfThickStation();

      if (n20_1>-1 && n20_1<16 && n1_1>-1 && n1_1<16) flag1=1;
      else flag1=0;

      Double_t vertex1 = ((ERTelescopeTrack*)v_track_t1->At(0))->GetXStationLocalVertex().Y();
      if (vertex1 >= 2.5 - 5./16) flag1 = 0; 

      if (flag1) sideID_1();
      if (nhe3_1) lv_he3 = ((ERTelescopeParticle*)v_par_he3_t1->At(0))->GetLVInteraction();
      if (nhe4_1) lv_he4 = ((ERTelescopeParticle*)v_par_he4_t1->At(0))->GetLVInteraction();
    }

    for(Int_t i=0;i<v_SSD_V_2->GetEntries();i++) {
      Int_t numCh_tmp = ((ERDigi*)v_SSD_V_2->At(i))->Channel();
      SSD_V2[numCh_tmp] = ((ERDigi*)v_SSD_V_2->At(i))->Edep();
      tSSD_V2[numCh_tmp] = ((ERDigi*)v_SSD_V_2->At(i))->Time();
      if (SSD_V2[numCh_tmp]>0 && tSSD_V2[numCh_tmp]>0) multv_2++;
    }
    if (v_track_t2->GetEntries()==1 && v_par_he3_t2->GetEntries()==1) {

      a20_2 = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->GetCorrectedEdepInThinStation();
      a1_2 = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->GetCorrectedEdepInThickStation();
      a20_2_un = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->GetEdepInThinStation();
      a1_2_un = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->GetEdepInThickStation();

      n20_2 = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->ChannelOfThinStation();
      n1_2 = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->ChannelOfThickStation();

      if (n20_2>-1 && n20_2<16 && n1_2>-1 && n1_2<16) flag2=1;
      else flag2=0;

      Double_t vertex2 = ((ERTelescopeTrack*)v_track_t2->At(0))->GetYStationLocalVertex().Y();
      if (vertex2 >= 2.5 - 5./16) flag2 = 0; 

      if (flag2) sideID_2();
      if (nhe3_2) lv_he3 = ((ERTelescopeParticle*)v_par_he3_t2->At(0))->GetLVInteraction();
      if (nhe4_2) lv_he4 = ((ERTelescopeParticle*)v_par_he4_t2->At(0))->GetLVInteraction();
    }

    for(Int_t i=0;i<v_SSD_V_3->GetEntries();i++) {
      Int_t numCh_tmp = ((ERDigi*)v_SSD_V_3->At(i))->Channel();
      SSD_V3[numCh_tmp] = ((ERDigi*)v_SSD_V_3->At(i))->Edep();
      tSSD_V3[numCh_tmp] = ((ERDigi*)v_SSD_V_3->At(i))->Time();
      if (SSD_V3[numCh_tmp]>0 && tSSD_V3[numCh_tmp]>0) multv_3++;
    }
    if (v_track_t3->GetEntries()==1 && v_par_he3_t3->GetEntries()==1) {

      a20_3 = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->GetCorrectedEdepInThinStation();
      a1_3 = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->GetCorrectedEdepInThickStation();
      a20_3_un = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->GetEdepInThinStation();
      a1_3_un = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->GetEdepInThickStation();

      n20_3 = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->ChannelOfThinStation();
      n1_3 = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->ChannelOfThickStation();

      if (n20_3>-1 && n20_3<16 && n1_3>-1 && n1_3<16) flag3=1;
      else flag3=0;

      Double_t vertex3 = ((ERTelescopeTrack*)v_track_t3->At(0))->GetXStationLocalVertex().Y();
      if (vertex3 <= -2.5 + 5./16) flag3 = 0; 


      if (flag3) sideID_3();
      if (nhe3_3) lv_he3 = ((ERTelescopeParticle*)v_par_he3_t3->At(0))->GetLVInteraction();
      if (nhe4_3) lv_he4 = ((ERTelescopeParticle*)v_par_he4_t3->At(0))->GetLVInteraction();
    }    

    for(Int_t i=0;i<v_SSD_V_4->GetEntries();i++) {
      Int_t numCh_tmp = ((ERDigi*)v_SSD_V_4->At(i))->Channel();
      SSD_V4[numCh_tmp] = ((ERDigi*)v_SSD_V_4->At(i))->Edep();
      tSSD_V4[numCh_tmp] = ((ERDigi*)v_SSD_V_4->At(i))->Time();
      if (SSD_V4[numCh_tmp]>0 && tSSD_V4[numCh_tmp]>0) multv_4++;
    }    
    if (v_track_t4->GetEntries()==1 && v_par_he3_t4->GetEntries()==1) {

      a20_4 = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->GetCorrectedEdepInThinStation();
      a1_4 = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->GetCorrectedEdepInThickStation();
      a20_4_un = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->GetEdepInThinStation();
      a1_4_un = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->GetEdepInThickStation();

      n20_4 = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->ChannelOfThinStation();
      n1_4 = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->ChannelOfThickStation();

      if (n20_4>-1 && n20_4<16 && n1_4>-1 && n1_4<16) flag4=1;
      else flag4=0;

      Double_t vertex4 = ((ERTelescopeTrack*)v_track_t4->At(0))->GetYStationLocalVertex().Y();
      if (vertex4 <= -2.5 + 5./16) flag4 = 0;

      if (flag4) sideID_4();
      if (nhe3_4) lv_he3 = ((ERTelescopeParticle*)v_par_he3_t4->At(0))->GetLVInteraction();
      if (nhe4_4) lv_he4 = ((ERTelescopeParticle*)v_par_he4_t4->At(0))->GetLVInteraction();
    }    
    //------------------------------------------------------------------------------------------------
    if (v_track_nd->GetEntries()>0 && v_par_nd->GetEntries()>0) {
      for (Int_t i=0;i<v_track_nd->GetEntries();i++) {
        ND_time[i] = ((ERNDTrack*)v_track_nd->At(i))->Time();
        ND_amp[i] = ((ERNDTrack*)v_track_nd->At(i))->Edep();
        ND_tac[i] = ((ERNDTrack*)v_track_nd->At(i))->TAC();
      }
      neutronID(v_track_nd,v_par_nd);
    }
    //------------------------------------------------------------------------------------------------

    if (nh3 && ( nhe3_1 || nhe3_2 || nhe3_3 || nhe3_4) ) { // reco 7H
      reco7H();
    }

    if (nh3 && ( nhe4_1 || nhe4_2 || nhe4_3 || nhe4_4) ) { // reco 7H
      reco6H();
    }

    tw->Fill();
  }
  fw->cd();
  tw->Write();
  fw->Close();

  return;

}

void centID() {

  std::map<ushort, ushort> csiMapping = {
      {0, 15},
      {1, 11},
      {2, 7},
      {3, 3},
      {4, 14},
      {5, 10},
      {6, 6},
      {7, 2},
      {8, 13},
      {9, 9},
      {10, 5},
      {11, 1},
      {12, 12},
      {13, 8},
      {14, 4},
      {15, 0}
  };

  const ushort numCh_tmp = csiMapping[nCsI];

  if(cut3h[numCh_tmp]->IsInside(aCsI, X_C)) {
    nh3 = 1;
    return;
  }
  else {
    nh3 = 0;
    return;
  }
}

void sideID_1() {

    std::map<ushort, ushort> inverse16Mapping = {
        {0, 15},
        {1, 14},
        {2, 13},
        {3, 12},
        {4, 11},
        {5, 10},
        {6, 9},
        {7, 8},
        {8, 7},
        {9, 6},
        {10, 5},
        {11, 4},
        {12, 3},
        {13, 2},
        {14, 1},
        {15, 0}
    };

  const ushort numCh_tmp = inverse16Mapping[n20_1];
  if(cuthe3_1[numCh_tmp]->IsInside(a1_1+a20_1_un, a20_1)) {
    nhe3_1 = 1;
    return;
  }
  if(cuthe4_1[numCh_tmp]->IsInside(a1_1+a20_1_un, a20_1)) {
    nhe4_1 = 1;
    return;
  }

}

void sideID_2() {

  std::map<ushort, ushort> inverse16Mapping = {
      {0, 15},
      {1, 14},
      {2, 13},
      {3, 12},
      {4, 11},
      {5, 10},
      {6, 9},
      {7, 8},
      {8, 7},
      {9, 6},
      {10, 5},
      {11, 4},
      {12, 3},
      {13, 2},
      {14, 1},
      {15, 0}
  };

  const ushort numCh_tmp = inverse16Mapping[n20_2];
  if(cuthe3_2[numCh_tmp]->IsInside(a1_2+a20_2_un, a20_2)) {
    nhe3_2 = 1;
    return;
  }
  if(cuthe4_2[numCh_tmp]->IsInside(a1_2+a20_2_un, a20_2)) {
    nhe4_2 = 1;
    return;
  }
}

void sideID_3() {
  if(cuthe3_3[n20_3]->IsInside(a1_3+a20_3_un, a20_3)) {
    nhe3_3 = 1;
    return;
  }
  else {
    nhe3_3 = 0;
    return;
  }
}

void sideID_4() {

  if (flag4) {
    if(cuthe3_4[n20_4]->IsInside(a1_4+a20_4_un, a20_4)) {
      nhe3_4 = 1;
      return;
    }
    else {
      nhe3_4 = 0;
      return;
    }
  }
}

void neutronID(TClonesArray *v_track, TClonesArray *v_par) {

  for (Int_t i=0;i<v_track->GetEntries();i++) {
    if(cutNeutron->IsInside(ND_amp[i], ND_tac[i])) {
      neutron++;
    } 
    if(cutGamma->IsInside(ND_amp[i], ND_tac[i])) {
      gammma++;
    }         
  }

}

void reco7H() {

  lv_h7 = lv_he8 + lv_d2 + (-lv_he3);

  lv_h7_CMR = lv_h7;
  TVector3 bVect_R = lv_R.BoostVector();
  lv_h7_CMR.Boost(-bVect_R);

  TVector3 bVect_7H = lv_h7.BoostVector();

  lv_h3_CMH7 = lv_h3;
  lv_h3_CMH7.Boost(-bVect_7H);

  // angle_he3_h7 = lv_h7.Angle(lv_he3.Vect())*TMath::RadToDeg();

  // energy = centE/1000.;
  // mass = 2.80892; //GeV
  // momentum = sqrt(energy*energy + 2*energy*mass);

  // lv_h3.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);
  // angle_h3_h7 = lv_h7.Angle(lv_h3.Vect())*TMath::RadToDeg();



  // angle_he3_he8 = lv_he8.Angle(lv_he3.Vect())*TMath::RadToDeg();
  // angle_h7_he8 = lv_he8.Angle(lv_h7.Vect())*TMath::RadToDeg();
  
  // angle_h7_beam_CMR = lv_he8_CMR.Angle(lv_h7_CMR.Vect())*TMath::RadToDeg();  

}

void reco6H() {

  lv_h6 = lv_he8 + lv_d2 + (-lv_he4);

  lv_h6_CMR = lv_h6;
  TVector3 bVect_R = lv_R.BoostVector();  
  lv_h6_CMR.Boost(-bVect_R);

  TVector3 bVect_6H = lv_h6.BoostVector();
  lv_h3_CMH6 = lv_h3;
  lv_h3_CMH6.Boost(-bVect_6H);

  // angle_he4_h6 = lv_h6.Angle(lv_he4.Vect())*TMath::RadToDeg();

  // energy = centE/1000.;
  // mass = 2.80892; //GeV
  // momentum = sqrt(energy*energy + 2*energy*mass);

  // lv_h3.SetXYZM(momentum*TMath::Sin(th_h3)*TMath::Cos(phi_h3), momentum*TMath::Sin(th_h3)*TMath::Sin(phi_h3), momentum*TMath::Cos(th_h3) ,mass);
  // angle_h3_h6 = lv_h6.Angle(lv_h3.Vect())*TMath::RadToDeg();



  // lv_he4_CMH6 = lv_he4;
  // lv_he4_CMH6.Boost(-bVect_6H);

  // lv_he8_CMH6 = lv_he8;
  // lv_he8_CMH6.Boost(-bVect_6H);  

  // angle_he4_he8 = lv_he8.Angle(lv_he4.Vect())*TMath::RadToDeg();
  // angle_h3_he8 = lv_he8.Angle(lv_h3.Vect())*TMath::RadToDeg();
  // angle_h3_he8_CMH6 = lv_he8_CMH6.Angle(lv_h3_CMH6.Vect())*TMath::RadToDeg();

  // lv_neutron_CMH6 = lv_neutron;
  // lv_neutron_CMH6.Boost(-bVect_6H);

  // angle_h6_beam_CMR = lv_he8_CMR.Angle(lv_h6_CMR.Vect())*TMath::RadToDeg();

}

void zeroVars() {

  flagCent = 0;
  flag1 = 0;
  flag2 = 0;
  flag3 = 0;
  flag4 = 0;

  nh3 = 0;
  nh2 = 0;
  nhe3_1 = 0;
  nhe3_2 = 0;
  nhe3_3 = 0;
  nhe3_4 = 0;
  nhe4_1 = 0;
  nhe4_2 = 0;
  nhe4_3 = 0;
  nhe4_4 = 0;
  neutron = 0;
  gammma = 0;

  fXt = -1000;
  fYt = -1000;

  lv_he8.SetXYZM(0,0,0,0);
  lv_CT.SetXYZM(0,0,0,0);
  lv_h3.SetXYZM(0,0,0,0);
  lv_side.SetXYZM(0,0,0,0);
  lv_he3.SetXYZM(0,0,0,0);
  lv_he4.SetXYZM(0,0,0,0);
  lv_h7.SetXYZM(0,0,0,0);
  lv_h6.SetXYZM(0,0,0,0);
  lv_h3_CMH7.SetXYZM(0,0,0,0);
  lv_h3_CMH6.SetXYZM(0,0,0,0);
  lv_h7_CMR.SetXYZM(0,0,0,0);
  lv_h6_CMR.SetXYZM(0,0,0,0);

  X_C = 0;
  Y_C = 0;
  nX_C = -1;
  nY_C = -1;
  aCsI = 0;
  nCsI = -1;

  a20_1 = 0;
  a20_1_un = 0;
  n20_1 = -1;

  a1_1 = 0;
  a1_1_un = 0;
  n1_1 = -1;

  a20_2 = 0;
  a20_2_un = 0;
  n20_2 = -1;

  a1_2 = 0;
  a1_2_un = 0;
  n1_2 = -1;

  a20_3 = 0;
  a20_3_un = 0;
  n20_3 = -1;

  a1_3 = 0;
  a1_3_un = 0;
  n1_3 = -1;

  a20_4 = 0;
  a20_4_un = 0;
  n20_4 = -1;

  a1_4 = 0;
  a1_4_un = 0;
  n1_4 = -1;

  for (Int_t i=0;i<32;i++) {
    ND_time[i] = 0;
    ND_amp[i] = 0;
    ND_tac[i] = 0;
  }


  for (Int_t i=0;i<16;i++) {
    SSD_V1[i] = 0;
    tSSD_V1[i] = 0;
    SSD_V2[i] = 0;
    tSSD_V2[i] = 0;
    SSD_V3[i] = 0;
    tSSD_V3[i] = 0;
    SSD_V4[i] = 0;
    tSSD_V4[i] = 0;        
  }

  multv_1 = 0;
  multv_2 = 0;
  multv_3 = 0;
  multv_4 = 0;

}