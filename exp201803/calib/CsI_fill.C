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

void CsI_fill() { 
		
	string 	input_file_name_cs = "/media/analysis_nas/exp201803/rootfiles/csi05_0002.root";		

	TTree* 		t;
	UShort_t    NeEvent_CsI_L[16],NeEvent_F3[4],NeEvent_tF3[4],NeEvent_F5[4],NeEvent_tF5[4];
	TBranch    *b_NeEvent_CsI_L,*b_NeEvent_F3,*b_NeEvent_F5,*b_NeEvent_tF3,*b_NeEvent_tF5;


	f = new TFile(input_file_name_cs.c_str());
	f->GetObject("AnalysisxTree",t);
	t->SetMakeClass(1);
	t->SetBranchAddress("NeEvent.CsI_L[16]", NeEvent_CsI_L, &b_NeEvent_CsI_L);
	t->SetBranchAddress("NeEvent.F3[4]", NeEvent_F3, &b_NeEvent_F3);
	t->SetBranchAddress("NeEvent.tF3[4]", NeEvent_tF3, &b_NeEvent_tF3);
	t->SetBranchAddress("NeEvent.F5[4]", NeEvent_F5, &b_NeEvent_F5);
	t->SetBranchAddress("NeEvent.tF5[4]", NeEvent_tF5, &b_NeEvent_tF5);

	const Long64_t nentries1 = t->GetEntries();
  cout << nentries1 << endl;
	Float_t CsI_L[16],F3[4],tF3[4],F5[4],tF5[4];
  Int_t flag=1;
  //Double_t r1[16],r2[16],r3[16],r4[16],r5[16],r6[16];

	TFile *fw = new TFile("cal_CsI.root", "RECREATE");
	TTree *tw = new TTree("tree", "CsI_L data");
	tw->Branch("CsI_L",&CsI_L,"CsI_L[16]/F");
	tw->Branch("F3",&F3,"F3[4]/F");
	tw->Branch("F5",&F5,"F5[4]/F");
	tw->Branch("tF3",&tF3,"tF3[4]/F");
	tw->Branch("tF5",&tF5,"tF5[4]/F");

  
  Int_t maxE = nentries1;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
	for (Long64_t jentry=0; jentry<maxE;jentry++) {
		t->GetEntry(jentry);
    flag = -1;
  
    // обнуление
    for(Int_t i = 0; i<16;i++) {
      CsI_L[i]=-1.;
    }
    for(Int_t i = 0; i<4;i++) {
      F3[i] = -1.;
      F5[i] = -1.;
      tF5[i] = -1.;
      tF3[i] = -1.;
    }

     // selecting nice events
    if( (NeEvent_F5[0]+NeEvent_F3[0]>400) && (NeEvent_F5[0]+NeEvent_F3[0]<750) && (NeEvent_tF5[0]-NeEvent_tF3[0]>640) && (NeEvent_tF5[0]-NeEvent_tF3[0]<750) && 
        (NeEvent_F5[1]+NeEvent_F3[1]>400) && (NeEvent_F5[1]+NeEvent_F3[1]<750) && (NeEvent_tF5[1]-NeEvent_tF3[1]>640) && (NeEvent_tF5[1]-NeEvent_tF3[1]<750) && 
        (NeEvent_F5[2]+NeEvent_F3[2]>400) && (NeEvent_F5[2]+NeEvent_F3[2]<750) && (NeEvent_tF5[2]-NeEvent_tF3[2]>640) && (NeEvent_tF5[2]-NeEvent_tF3[2]<750) && 
        (NeEvent_F5[3]+NeEvent_F3[3]>400) && (NeEvent_F5[3]+NeEvent_F3[3]<750) && (NeEvent_tF5[3]-NeEvent_tF3[3]>640) && (NeEvent_tF5[3]-NeEvent_tF3[3]<750) ) {
      flag = 1;
    }

    if(flag==1) {
      for(Int_t i=0; i<16; i++) {
        CsI_L[i] = NeEvent_CsI_L[i];
      }  
      for(Int_t i=0; i<4; i++) {
        F3[i] = NeEvent_F3[i];
        F5[i] = NeEvent_F5[i];
        tF3[i] = NeEvent_tF3[i];
        tF5[i] = NeEvent_tF5[i];
      }
    }

		if(flag==1) tw->Fill();			
	}//entries
	tw->Write();
	fw->Close();
}
