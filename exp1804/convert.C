#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
//#include "/media/users_NAS/Muzalevsky/exp1803/go4/TNeEvent.h"

using namespace std;

void convert(){ 
				
	Int_t 	max_channel = 300;

	TTree* 		t;
	UShort_t    NeEvent_SQ20[16];
	UShort_t    NeEvent_SQX_L[32];
	TBranch    *b_NeEvent_SQ20;
	TBranch    *b_NeEvent_SQX_L;

  //TNeEvent *revent = new TNeEvent();

	Float_t parSQ1[32], parSQ2[32],par201[16],par202[16];
  TString line1;
  ifstream myfile1;
  Int_t count=0;
  myfile1.open("/media/users_NAS/Muzalevsky/exp1804/SQX_L.cal");
  while (! myfile1.eof() ){
		line1.ReadLine(myfile1);
    //cout << line1.Data() << endl;
   // if(count<3) continue;
		if(line1.IsNull()) break;
    sscanf(line1.Data(),"%g %g", parSQ1+count,parSQ2+count);
        count++;
  }
  cout << " pars for 1mm " << endl;
  for(Int_t i=0;i<32;i++){
    cout << parSQ1[i] << " " << parSQ2[i] << endl;   
  }


  ifstream myfile2;
  TString line2;
  count=0;
  myfile2.open("/media/users_NAS/Muzalevsky/exp1804/SQ20.cal");
  while (! myfile2.eof() ){
		line2.ReadLine(myfile2);
   // cout << line2.Data() << endl;
   // if(count<3) continue;
		if(line2.IsNull()) break;
    sscanf(line2.Data(),"%g %g", par201+count,par202+count);
    count++;
  }
  cout << " pars for 20 mkm " << endl;
  for(Int_t i=0;i<16;i++){
    cout << par201[i] << " " << par202[i] << endl;   
  }

/*

ifstream myfile1,myfile2; //	i=0; 1000V_5.2mv_nosource%dWfm_Ch1.txt
	for(Int_t i=0; i<nfiles; i++) {	if(i%1000==0){ cout<<i<<endl;}
		filename1.Form("/home/muzalevsky/workspace/NeuRad_tests/data/rawDataTektronix/muzalevsky/1000V_trigg5mv_nosurce/1000V_5.2mv_nosource%dWfm_Ch1.txt",i+1);
		myfile1.open(filename1.Data());
		if (myfile1.is_open()) {
			filename2.Form("/home/muzalevsky/workspace/NeuRad_tests/data/rawDataTektronix/muzalevsky/1000V_trigg5mv_nosurce/1000V_5.2mv_nosource%dWfm_Ch2.txt",i+1);
			myfile2.open(filename2.Data()); 
			if (myfile2.is_open()) {

*/
  TFile *f;
  ifstream myfile;
  TString filename;
  Int_t i =10,maxE;

	TFile *fw = new TFile("out.root", "RECREATE"); // outputfile
	TTree *tw = new TTree("tree", "out tree in energies");
	Float_t SQX_L[32],SQ20[16];
	tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
	tw->Branch("SQ20",&SQ20,"SQ20[16]/F");

  //for(Int_t i=10; i<99; i++) {
 /*   filename.Form("/media/users_NAS/Muzalevsky/exp1804/rootfiles/h5_14_00%d.root",i);
    f = new TFile(filename.Data(),"READ");
    if (f->IsZombie()) {
      cerr << "cannot open file " << filename.Data() << endl;
    }
    
    f->GetObject("AnalysisxTree",t);
	  t->SetMakeClass(1);
	  t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
    t->SetBranchAddress("NeEvent.SQ20[16]", NeEvent_SQ20, &b_NeEvent_SQ20);
	  Long64_t nentries1 = t->GetEntries();
    cout << nentries1 << endl;*/

  //} number of files
//return;

	f = new TFile("/media/users_NAS/Muzalevsky/exp1804/rootfiles/h5_14_0010.root","READ");
	f->GetObject("AnalysisxTree",t);
	t->SetMakeClass(1);
	t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
  t->SetBranchAddress("NeEvent.SQ20[16]", NeEvent_SQ20, &b_NeEvent_SQ20);
	const Long64_t nentries1 = t->GetEntries();
  cout << nentries1 << endl;
	//Float_t SQX_L[32],SQ20[16];

  maxE = nentries1;
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
	
	tw->Write();
	fw->Close();

}
