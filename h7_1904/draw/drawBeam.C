void drawBeam() {

  gStyle->SetOptStat(0);

  TChain *ch = new TChain("tree"); //e4
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/beamDiagnostics/beamHe8_*");


  TCanvas *c1 = new TCanvas("c1","",1800,1000); 
  c1->Divide(2,3);

  c1->cd(1);
  ch->Draw("fYt:fXt >> targetprofile(39,-12,12,39,-12,12)","","lego2");
  c1->Update();

  c1->cd(2);
  ch->Draw("yCt:xCt >> centralProfile(32,-32,32,32,-32,32)","","col");
  c1->Update();

  c1->cd(3);
  ch->Draw("py/pBeam:px/pBeam >>(43,-0.05,0.05,43,-0.05,0.05) ","","col");
  c1->Update();

  c1->cd(4);
  ch->Draw("(pBeam-pz)/pBeam >> dispertion(50,0,0.001)","","");
  c1->Update();

  c1->cd(5);
  ch->Draw("thetahe8*TMath::RadToDeg() >> thetaBeam(30,0,3)","","");
  c1->Update(); 

  c1->cd(6);
  ch->Draw("phihe8*TMath::RadToDeg() >> phiBeam(40,-180,180)","","");
  c1->Update(); 

}