#include <string.h>
#include <iostream.h>
#include <fstream.h>

using namespace std;

void SQXL_calib(){ 
				
	string 	input_file_name_cs = "/media/users_NAS/Muzalevsky/si_1000_LR_02_0001.root";		
	Int_t 	max_channel = 300;

	TTree* 		t;
	UShort_t    NeEvent_SQ20[16];
	UShort_t    NeEvent_SQX_L[32];
	TBranch    *b_NeEvent_SQ20;
	TBranch    *b_NeEvent_SQX_L;

	Float_t parSQ1[32], parSQ2[32];
  TString line1;
  ifstream myfile1;
  Int_t count=0;
  myfile1.open("/home/muzalevsky/AculUtils/macro/sqx_l_ec.clb");
  while (! myfile1.eof() ){
    count++;
		line1.ReadLine(myfile1);
    if(count<3) continue;
		if(line1.IsNull()) break;
    sscanf(line1.Data(),"%g %g", parSQ1+count-3,parSQ2+count-3);
    //cout << parSQ1[count-3] << " " << parSQ2[count-3] << endl;
  }

	f = new TFile(input_file_name_cs.c_str());
	f->GetObject("AnalysisxTree",t);
	t->SetMakeClass(1);
	//TTree *t = (TTree*)f->Get("AnalysisxTree");
	t->SetBranchAddress("NeEvent.SQ20[16]", NeEvent_SQ20, &b_NeEvent_SQ20);
	t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
	const Long64_t nentries1 = t->GetEntries();
  cout << nentries1 << endl;

	//cout<<">>> Making histograms"<<endl;
	TH1I* hist20[16];
	TString histName;
	TH1I *htest = new TH1I("htest", "htest", 300, 0, 1000);
	Int_t raw20[16];	
	Float_t SQX_L[32];

	for(Int_t i=0; i<16;i++){
      		histName.Form("hist20_%d", i);
		hist20[i] = new TH1I(histName.Data(), histName.Data(), max_channel, 0, 1000);
	}
	
	TFile *fw = new TFile("raw.root", "RECREATE");
	TTree *tw = new TTree("raw", "raw hists");
	//tw->Branch("htest","TH1I",&htest,32000,0);
	//tw->Branch("raw20",&raw20,"raw20/I");
	tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");

	/*for(Int_t i=0; i<16;i++){
      		histName.Form("hist20_%d", i);
		cout << histName.Data() << endl;
		tw->Branch(histName.Data(),"TH1I",hist20[i],32000,0);
	}*/
  Int_t maxE = 50000;
  cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
	//for (Long64_t jentry=0; jentry<nentries1;jentry++) {
	for (Long64_t jentry=0; jentry<maxE;jentry++) {
		t->GetEntry(jentry);
		for(Int_t i=0; i<32; i++){
			//hist20[i]->Fill(NeEvent_SQ20[i]);
			//htest->Fill(NeEvent_SQ20[0]);
			//raw20[i] = NeEvent_SQ20[i];
			SQX_L[i] = NeEvent_SQX_L[i];
		}
		tw->Fill();			
	}
	
	//htest->Draw();
	tw->Write();
	fw->Close();
/*
  TH1F *hpx    = new TH1F("hpx","This is the px distribution",100,-4,4);
   TH2F *hpxpy  = new TH2F("hpxpy","py vs px",40,-4,4,40,-4,4);
   TProfile *hprof  = new TProfile("hprof","Profile of pz versus px",100,-4,4,0,20);
   T->Branch("hpx","TH1F",&hpx,32000,0);
   T->Branch("hpxpy","TH2F",&hpxpy,32000,0)
*/
	//hist20[0]->Draw();
}
