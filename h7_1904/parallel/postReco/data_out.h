// BEAM
//------------------------------------------------------------------------------------------------
Float_t fXt,fYt;
TLorentzVector lv_he8;
//------------------------------------------------------------------------------------------------
// CT
TLorentzVector lv_CT;
TLorentzVector lv_h3;

Int_t flagCent;
Int_t nh3,nh2;

Float_t X_C,tX_C,Y_C,tY_C;
Int_t nX_C,nY_C; 

Float_t aCsI;
Int_t nCsI;
//------------------------------------------------------------------------------------------------
// Side telescopes

TLorentzVector lv_side;
TLorentzVector lv_he3,lv_he4;

Int_t flag1,flag2,flag3,flag4;
Int_t nhe3_1,nhe3_2,nhe3_3,nhe3_4;
Int_t nhe4_1,nhe4_2,nhe4_3,nhe4_4;

Float_t a20_1,a20_1_un;
Int_t n20_1;

Float_t a1_1, a1_1_un;
Int_t n1_1;

Float_t av_1, av_1_un;
Int_t nv_1;

Float_t a20_2,a20_2_un;
Int_t n20_2;

Float_t a1_2, a1_2_un;
Int_t n1_2;

Float_t av_2, av_2_un;
Int_t nv_2;

Float_t a20_3,a20_3_un;
Int_t n20_3;

Float_t a1_3, a1_3_un;
Int_t n1_3;

Float_t av_3, av_3_un;
Int_t nv_3;

Float_t a20_4,a20_4_un;
Int_t n20_4;

Float_t a1_4, a1_4_un;
Int_t n1_4;

Float_t av_4, av_4_un;
Int_t nv_4;

Int_t multv_1,multv_2,multv_3,multv_4;
//------------------------------------------------------------------------------------------------
// Neutron
Float_t ND_time[32],ND_amp[32],ND_tac[32];

Int_t neutron,gammma;
//------------------------------------------------------------------------------------------------
// out TLorentzVector's
TLorentzVector lv_h7,lv_h6;
TLorentzVector lv_h3_CMH7,lv_h3_CMH6;
TLorentzVector lv_h7_CMR, lv_h6_CMR;

//------------------------------------------------------------------------------------------------

//Float_t targetTime,diafTime;

// out TLorentzVector's
// TLorentzVector lv_h7,lv_he3;
// TLorentzVector lv_h3_CMH7,lv_h7_CMR,lv_he8_CMR;

// TLorentzVector lv_he4,lv_h6;
// TLorentzVector lv_h3_CMH6,lv_h6_CMR,lv_he4_CMH6,lv_he8_CMH6;
// TLorentzVector lv_h3_CMH6_rot,lv_h3_CMH7_rot;

// TLorentzVector lv_he7,lv_he7_CMR,lv_he4_CMHe7,lv_neutron_CMHe7,lv_neutron_CMHe5,lv_neutron_CMH5,lv_neutron_CMR;

// TLorentzVector lv_neutron,lv_neutron_CMH6;

// TLorentzVector lv_h6qFrame, lv_h3qFrame;

// TLorentzVector lv_he5,lv_he5_CMR,lv_he4_rot,lv_he5_rot,lv_he4_CMHe5_rot;
// TLorentzVector lv_h5, lv_h3_CMH5, lv_h3qFrame_5h,lv_h3_CMH5_rot;

// TLorentzVector lv_h4, lv_he6_side, lv_neutron_CMHe6, lv_h4_CMR, lv_he4_CMHe6;
// //------------------------------------------------------------------------------------------------
// // Neutron
// // Float_t aND,tacND,tND,tND_cal,ND_time_cal[32],ND_energy[32],eNeutron;
// // Int_t neutron,gammma;

// //------------------------------------------------------------------------------------------------
// // h7
// Float_t angle_he3_h7,angle_h3_h7,angle_he3_he8,angle_h7_he8;

// //h6
// Float_t angle_he4_h6,angle_he4_he8,angle_h3_he8,angle_h3_he8_CMH6;
// Float_t angle_h3_h6;
// Float_t angle_h3_beam_CMH6,angle_h3_q_CMH6;
// Float_t angle_h7_beam_CMR, angle_h6_beam_CMR;
