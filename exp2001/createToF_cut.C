#include "/home/muzalevskii/work/macro/exp2001/beamCut.C"

void createToF_cut(){
	
	gStyle->SetOptStat(0);

  	beamCut();

  	TCanvas *c1 = new TCanvas("c1","title",1800,1000);
  	c1->Divide(2,2);

	TChain *ch = new TChain("stepRepackingxTree");
	ch->Add("/mnt/data/exp2001/data/raw/run40*");

	TChain *chCal = new TChain("stepRepackingxTree");
	chCal->Add("/mnt/data/exp2001/data/raw/crun09*");

	TString hdraw,hcut;
	TString htemp;

	hdraw = "(Beam_detector_F3.fData.fValue[0] + Beam_detector_F3.fData.fValue[1] + Beam_detector_F3.fData.fValue[2] + Beam_detector_F3.fData.fValue[3])/4.";
	hdraw += ":0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])";
	
	htemp = hdraw + ">>h1(300,80,110,2000,0,2000)";

	hcut = "DetEventCommon.trigger==1";

	c1->cd(1);
	chCal->Draw(htemp.Data(),hcut.Data(),"col");
	cutF3->Draw("same");

	htemp = hdraw + ">>h2(300,80,110,2000,0,2000)";

	c1->cd(2);
	ch->Draw(htemp.Data(),hcut.Data(),"col");
	cutF3->Draw("same");


	hdraw = "(Beam_detector_F5.fData.fValue[0] + Beam_detector_F5.fData.fValue[1] + Beam_detector_F5.fData.fValue[2] + Beam_detector_F5.fData.fValue[3])/4.";
	hdraw += ":0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])";
	
	htemp = hdraw + ">>h3(300,80,110,2000,0,2000)";

	hcut = "DetEventCommon.trigger==1";

	c1->cd(3);
	chCal->Draw(htemp.Data(),hcut.Data(),"col");
	cutF5->Draw("same");

	htemp = hdraw + ">>h4(300,80,110,2000,0,2000)";

	c1->cd(4);
	ch->Draw(htemp.Data(),hcut.Data(),"col");
	cutF5->Draw("same");


}