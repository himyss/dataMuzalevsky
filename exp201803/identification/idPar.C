void idPar(){

  TELoss fAlphaSi;
  fAlphaSi.SetEL(1, 2.321); // density in g/cm3
	fAlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//	mSi.SetZP(1., 1.);		//protons
	fAlphaSi.SetZP(2., 4.);		//alphas, Z, A
	fAlphaSi.SetEtab(100000, 200.);	// ?, MeV calculate ranges
	fAlphaSi.SetDeltaEtab(300);


  TString cut[16];
  TString cut_0[16];
  TString cut1("");
  TString cut2("");
  TString cut3("");
  TString cut4("");
  
  
  TString hDraw,hname,hcut;

  TH1F *h0,*h1,*h2,*h[300];


  TChain *ch = new TChain("AnalysisxTree");
	ch->Add("/media/analysis_nas/exp201804/rootfiles/h5_14_00*.root");

 
  TCanvas *c1 = new TCanvas("c1","raw data",1800,1000);
  c1->Divide(2,2);
  c1->cd(1);
  ch->Draw("NeEvent.SQY_R[]>>(300,150,2500)","","");
  c1->cd(2); 
  ch->Draw("NeEvent.CsI_R[]>>(1000,100,5000)","","");
  c1->cd(3);
  ch->Draw("NeEvent.SQY_R[]:NeEvent.CsI_R[]>>(1000,100,5000,300,150,2500)","","");  
 

  return;  
}
