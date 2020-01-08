#include "/home/ivan/Desktop/be10Cut.C"
#include "/home/ivan/work/macro/be10/beam/li9_beamCut.C"
#include "/home/ivan/work/macro/be10/beam/b12_beamCut.C"


void drawToF(){
  be10Cut();
  li9_beamCut();
  b12_beamCut();

  gStyle->SetOptStat(0);

  TChain *ch1 = new TChain("er"); //e4
  ch1->Add("/media/ivan/data/exp1906/be10/digi/all/firstVol/be10_ct_05*");

  ch1->SetMarkerStyle(20);

  TCanvas *c1 = new TCanvas("c1","dE-ToF ID plot",1800,1000);
  // c1->Divide(2,1);

  // c1->cd(1);
  cout << ch1->Draw("BeamDetToFDigi2.fEdep/4.:BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime >> f5(1000,30,110,4500,0,4500)","","col",5000000,0) << " F5 all" << endl;
  // cutF5_b12->Draw("same");
  cout << ch1->Draw("BeamDetToFDigi2.fEdep/4.:BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime >> f5_cut(1000,30,110,4500,0,4500)",cutF5_b12->GetName(),"same",5000000,0) << " F5 cut" << endl;
// // return;

//   // cutF5->SetLineColor(kRed);
//   // cutF5->SetLineWidth(2);
//   // cutF5->Draw("same");
//   // ch1->Draw("BeamDetToFDigi2.fEdep:BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime >> f5_cut(1000,30,110,17000,0,17000)","","",500000,0);
//   c1->cd(2);
//   cout << ch1->Draw("BeamDetToFDigi1.fEdep/4:BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime >> f3(1000,30,110,4500,0,4500)","","col",5000000,0) << " F3 all" << endl;

//   cout << ch1->Draw("BeamDetToFDigi2.fEdep/4.:BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime >> f3_cut(1000,30,110,4500,0,4500)",cutF3->GetName(),"same",5000000,0) << " F3 cut" << endl;
// // return;


  // cutF3->SetLineColor(kRed);
  // cutF3->SetLineWidth(2);
  // cutF3->Draw("same");
return;


}