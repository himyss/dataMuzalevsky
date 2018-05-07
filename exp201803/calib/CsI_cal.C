#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
//#include "/media/users_NAS/Muzalevsky/exp1803/go4/TNeEvent.h"

using namespace std;

//---------------------------------------------------------
Double_t fitf(Double_t *x,Double_t *par) {  // creating fit function
  Int_t A,Z;
  A = 4; Z = 2;
  Double_t fitval = par[4] + par[0]*( x[0]*(1 - (par[1]*A*Z*Z/x[0])*TMath::Log(1 + (1/(par[1]*A*Z*Z/x[0])) ) ) + par[3]*par[1]*A*Z*Z*TMath::Log( (x[0]+par[1]*A*Z*Z)/(A*par[2]+par[1]*A*Z*Z) ) );
  return fitval;
}
//---------------------------------------------------------

void CsI_cal() { 
		
//--------------------------------------------------------- reading intup: 4 peak channels	
	Float_t ch1[16],ch2[16],ch3[16],ch4[16];
  TString line1;
  ifstream myfile1;
  Int_t count=0;
  myfile1.open("/home/muzalevsky/work/dataMuzalevsky/exp201803/data/CsI_L_E.txt");
  while (! myfile1.eof() ){
		line1.ReadLine(myfile1);
    //cout << line1.Data() << endl;
   // if(count<3) continue;
		if(line1.IsNull()) break;
    sscanf(line1.Data(),"%g %g %g %g", ch1+count,ch2+count,ch3+count,ch4+count);
    count++;
  }
  cout << " peak channels " << endl;
  for(Int_t i=0;i<16;i++){
    cout << ch1[i] << " " << ch2[i] << " " << ch3[i] << " " << ch4[i] << endl;   
  }
//---------------------------------------------------------
  TCanvas *c1 = new TCanvas();
  c1->Divide(2,1);
  c1->cd(1); 
  TGraph *g,*g1;
  Float_t y[4],x[4];
  y[0] = ch1[0]; y[1] = ch2[0];y[2] = ch3[0];y[3] = ch4[0];
  x[0] = 4.7843;x[1] = 5.48948; x[2] = 6.0024; x[3] = 7.6869;    
  g = new TGraph(4,x,y);
  g->SetMarkerSize(5);
  //TGraph(Int_t n, const Int_t* x, const Int_t* y)
  g->Draw("AL*");
  
  TF1 *func = new TF1("fit",fitf,0.,200.,5); // функция фитирования
  func->SetParLimits(0,10.,60);
  func->SetParLimits(1,0.001,2.);
  func->SetParLimits(2,0.001,6.);
  func->SetParLimits(3,0.1,10.);
  func->SetParLimits(4,-100.,100.);  
  g->Fit("fit"); 

  c1->cd(2);
  g1 = new TGraph(4,x,y);
  g1->SetMarkerSize(5);
  g1->Draw("AL*");
  TF1 *linfit = new TF1("linfit","x*[0]+[1]",0.,200.); // функция фитирования
  g1->Fit("linfit");

  TCanvas *c2 = new TCanvas();
  c2->cd();
  linfit->SetLineColor(1);
  linfit->Draw();
  func->SetLineColor(3);
  func->Draw("same");
 // func->Draw();
 /* func->SetParameter(0,19.5);
  func->SetParameter(1,0.71);
  func->SetParameter(2,3.8);
  func->SetParameter(3,0.26);*/

  //func->Draw();

/*

*/

/*
	string 	input_file_name_cs = "/media/analysis_nas/exp201803/rootfiles/csi_l_0002.root";		

	TTree* 		t;
	UShort_t    NeEvent_CsI_L[16];
	TBranch    *b_NeEvent_CsI_L;

	f = new TFile(input_file_name_cs.c_str());
	f->GetObject("AnalysisxTree",t);
	t->SetMakeClass(1);
	t->SetBranchAddress("NeEvent.CsI_L[16]", NeEvent_CsI_L, &b_NeEvent_CsI_L);
	const Long64_t nentries1 = t->GetEntries();
  cout << nentries1 << endl;
	Float_t CsI_L[16],Eloss[16];
  Int_t count=0;

  Double_t r1[16],r2[16],r3[16],r4[16],r5[16],r6[16];

	TFile *fw = new TFile("cal_CsI.root", "RECREATE");
	TTree *tw = new TTree("tree", "CsI_L data");
	tw->Branch("CsI_L",&CsI_L,"CsI_L[16]/F");
	tw->Branch("Eloss",&Eloss,"Eloss[16]/F");
  
  Int_t maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
	for (Long64_t jentry=0; jentry<maxE;jentry++) {
		t->GetEntry(jentry);
		for(Int_t i=0; i<16; i++){

      CsI_L[i]=-1.;// обнуление
      Eloss[i] = -1.;
      CsI_L[i] = NeEvent_CsI_L[i];
      if(CsI_L[i]>165 && CsI_L[i]<190) {
        Eloss[i] = 4.7843;
        count++;
      }
      if(CsI_L[i]>190 && CsI_L[i]<213) {
        Eloss[i] = 5.48948;
        count++;
      }
      if(CsI_L[i]>213 && CsI_L[i]<235) {
        Eloss[i] = 6.0024;
        count++;
      }
      if(CsI_L[i]>270 && CsI_L[i]<302) {
        Eloss[i] = 7.6869;
        count++;
      }

	  } // i<16
		tw->Fill();			
	}//entries
	cout << count << " the number of good events" << endl;
	//htest->Draw();
	tw->Write();
	fw->Close();
*/
}
