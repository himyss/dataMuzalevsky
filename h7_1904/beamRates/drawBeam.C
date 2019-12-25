#include "/home/ivan/work/macro/he8_1904/beamRates/be10Cut.C"

void drawBeam() {
  
  be10Cut();

  gStyle->SetOptStat(0);

  TChain *ch = new TChain("stepRepackingxTree");
  ch->Add("/media/ivan/data/exp1904/be10/raw/be10_ct_05_1.lml.root");
  cout << ch->GetEntries() << endl;

  ch->SetMarkerStyle(7);

  TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  c1->Divide(2,1);

  c1->cd(1);

  TString F3,F5,ToF;

  F3 = "(Beam_detector_F3.fData.fValue[0] + "; 
  F3 = F3 + "Beam_detector_F3.fData.fValue[1] + ";
  F3 = F3 + "Beam_detector_F3.fData.fValue[2] + ";
  F3 = F3 + "Beam_detector_F3.fData.fValue[3])/4.";

  cout << F3 << endl;

  ToF = "0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + "; 
  ToF = ToF + "Beam_detector_tF5.fData.fValue[1] + ";
  ToF = ToF + "Beam_detector_tF5.fData.fValue[2] + ";
  ToF = ToF + "Beam_detector_tF5.fData.fValue[3] - ";

  ToF = ToF + "Beam_detector_tF3.fData.fValue[0] - "; 
  ToF = ToF + "Beam_detector_tF3.fData.fValue[1] - ";
  ToF = ToF + "Beam_detector_tF3.fData.fValue[2] - ";
  ToF = ToF + "Beam_detector_tF3.fData.fValue[3])";

  cout << ToF << endl;

  TString hdraw,hcut;

  ch->SetMarkerColor(kBlack);
  hdraw  = F3 + TString(":") + ToF + ">>f3(500,20,150,3000,0,3000)";
  hcut.Form("DetEventCommon.trigger==1");
  ch->Draw(hdraw.Data(),hcut.Data(),"");

  ch->SetMarkerColor(kRed);
  hdraw  = F3 + TString(":") + ToF + ">>f3_cut(500,20,150,3000,0,3000)";
  hcut.Append(" && " + (TString)cutF3->GetName());
  ch->Draw(hdraw.Data(),hcut.Data(),"same");

  c1->Update();

  c1->cd(2);

  F5 = "(Beam_detector_F5.fData.fValue[0] + "; 
  F5 = F5 + "Beam_detector_F5.fData.fValue[1] + ";
  F5 = F5 + "Beam_detector_F5.fData.fValue[2] + ";
  F5 = F5 + "Beam_detector_F5.fData.fValue[3])/4.";

  cout << F5 << endl;

  cout << ToF << endl;

  ch->SetMarkerColor(kBlack);
  hdraw  = F5 + TString(":") + ToF + ">>f5(500,20,150,3000,0,3000)";
  hcut.Form("DetEventCommon.trigger==1");
  ch->Draw(hdraw.Data(),hcut.Data(),"");

  ch->SetMarkerColor(kRed);
  hdraw  = F5 + TString(":") + ToF + ">>f5_cut(500,20,150,3000,0,3000)";
  hcut.Append(" && " + (TString)cutF5->GetName());
  ch->Draw(hdraw.Data(),hcut.Data(),"same");

  c1->Update();

}