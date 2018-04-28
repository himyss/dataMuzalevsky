#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
//#include "/media/users_NAS/Muzalevsky/exp1803/go4/TNeEvent.h"

using namespace std;

void mergeFiles(){ 

	TTree* 		t;
	UShort_t    NeEvent_SQ20[16];
	UShort_t    NeEvent_SQX_L[32];
	TBranch    *b_NeEvent_SQ20;
	TBranch    *b_NeEvent_SQX_L;

	Float_t parSQ1[32], parSQ2[32],par201[16],par202[16];
  // Reading cal parameters 
//------------------------------------------------------------------------------ 
 // for 1 mm Si detector
  TString line1;
  ifstream myfile1;
  Int_t count=0;
  myfile1.open("/media/users_NAS/Muzalevsky/exp1804/SQX_L.cal");
  while (! myfile1.eof() ){
		line1.ReadLine(myfile1);
		if(line1.IsNull()) break;
    sscanf(line1.Data(),"%g %g", parSQ1+count,parSQ2+count);
        count++;
  }
  cout << " pars for 1mm " << endl;
  for(Int_t i=0;i<32;i++){
    cout << parSQ1[i] << " " << parSQ2[i] << endl;   
  }
 // for 20 mkm Si detector
  ifstream myfile2;
  TString line2;
  count=0;
  myfile2.open("/media/users_NAS/Muzalevsky/exp1804/SQ20.cal");
  while (! myfile2.eof() ){
		line2.ReadLine(myfile2);
		if(line2.IsNull()) break;
    sscanf(line2.Data(),"%g %g", par201+count,par202+count);
    count++;
  }
  par201[14]=0.;par202[14]=0.;
  par201[15]=0.;par202[15]=0.;
  cout << " pars for 20 mkm " << endl;
  for(Int_t i=0;i<16;i++){
    cout << par201[i] << " " << par202[i] << endl;   
  }
  // Creating outfile,outtree
//------------------------------------------------------------------------------ 
	TFile *f[100];  
	TString input_file;
	Float_t SQX_L[32],SQ20[16];
  Int_t n =10,maxE;
  Long64_t nentries;

	TFile *fw = new TFile("data/out.root", "RECREATE");
	TTree *tw = new TTree("tree", "merged data in energies");
	tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
	tw->Branch("SQ20",&SQ20,"SQ20[16]/F");

  // Reading input filesm, filling out tree
//----------------------------------------------------------------------------------
  for(Int_t n=10;n<20;n++){
    input_file.Form("/media/users_NAS/Muzalevsky/exp1804/rootfiles/h5_14_00%d.root",n);		
	  f[n] = new TFile(input_file.Data());
	  if (/*f == 0 || */f[n]->IsZombie()) {
		  cerr << "Input file was not opened " << input_file.Data() << endl;
		  return 1;
	  }

	  f[n]->GetObject("AnalysisxTree",t);
	  t->SetMakeClass(1);
	  t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
    t->SetBranchAddress("NeEvent.SQ20[16]", NeEvent_SQ20, &b_NeEvent_SQ20);
	  nentries = t->GetEntries();

    maxE = nentries;
    cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
	  for (Long64_t jentry=0; jentry<maxE;jentry++) {
		  t->GetEntry(jentry);
		  for(Int_t i=0; i<32; i++){

        SQX_L[i]=-1.;// обнуление
        if(i<16) {
          SQ20[i]=-1.;
        }

        if(NeEvent_SQX_L[i]>20){ //cut the pedestal, calculating
          SQX_L[i] = NeEvent_SQX_L[i]*parSQ2[i] + parSQ1[i];
        }
   
        if(i<14){
          if(NeEvent_SQ20[i]>150.) { //cut the pedestal, calculating
            SQ20[i] = NeEvent_SQ20[i]*par202[i] + par201[i];
          }
        }

	    } // i<32
		  tw->Fill();			
	  }//entries
  }// nfiles

// writing outfile
//----------------------------------------------------------------------------------
  fw->cd();
	tw->Write();
	fw->Close();

  return;
}
