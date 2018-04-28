#include <string.h>
#include <iostream.h>
#include <fstream.h>

using namespace std;

void tests20(){ 
				

	TFile *f1 = new TFile("/media/users_NAS/Muzalevsky/exp1803/calSi/si_20_03.root");
	TTree *t1 = (TTree*)f1->Get("AnalysisxTree");

	t1->AddFriend("cal_1mm", "/home/muzalevsky/AculUti/macroexp18/cal_1mm.root");

  TCanvas *c1 = new TCanvas("c5", "coincidence");
	c1->Divide(2,2);
	c1->cd(1);
  t1->Draw("NeEvent.SQ20[5]","NeEvent.SQ20[5]>600 && NeEvent.SQ20[5]<700","");
  c1->cd(2);
	//t1->Draw("NeEvent.SQX_L[]","NeEvent.SQ20[5]>635 && NeEvent.SQ20[5]<660 && NeEvent.SQX_L[]>30","");
  t1->Draw("NeEvent.SQX_L[]","NeEvent.SQ20[5]>635 && NeEvent.SQ20[5]<660 && NeEvent.SQX_L[]>30","");

}
