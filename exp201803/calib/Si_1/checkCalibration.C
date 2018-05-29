void checkCalibration() {
  Int_t par1,par2;
  par1=1; par2=0;  

  if(par1) {
      TFile *f = new TFile("~muzalevsky/work/exp1803/data/siCal/SQY_L_full_calibrated_spectra.root");
  const Int_t nhists = 16;
  TH1F *h[nhists],*hsumm;
  hsumm = new TH1F("hsumm","summ X spec",4095,0,10);
  TString hname,cName;
  TTree *t = (TTree*)f->Get("AnalysisxTree");
  for(Int_t i=0;i<nhists;i++) {
    hname.Form("HistSQY_L[%d]Efull",i);
    h[i] = (TH1F*)f->Get(hname.Data());
    //cout  << h[i]->GetXaxis()->GetXmax()<< " " << i<< endl;
  }
  TCanvas *c1 = new TCanvas("c1"," summ Xspec",1000,1000);
  Float_t content;
  for(Int_t i=0;i<4095;i++) {
    content = 0.;
    for(Int_t j=0;j<nhists;j++) {
      if(j==0) continue;
      content += h[j]->GetBinContent(i);    
    }
    hsumm->SetBinContent(i,content);
  }

  TF1* g1 = new TF1("g1", "gaus", 4.4, 4.6);
  g1->SetParLimits(0,1.,150.);
  g1->SetParLimits(1,4.,5.);
  g1->SetParLimits(2,0.1,3.);

  TF1* g2 = new TF1("g2", "gaus", 5.12, 5.35);
  g2->SetParLimits(0,1.,150.);
  g2->SetParLimits(1,5.12,5.35);
  g2->SetParLimits(2,0.1,3.);

  TF1* g3 = new TF1("g3", "gaus", 5.65, 5.95);
  g3->SetParLimits(0,1.,150.);
  g3->SetParLimits(1,5.65,5.95);
  g3->SetParLimits(2,0.1,3.);

  TF1* g4 = new TF1("g4", "gaus", 7.25, 7.65);
  g4->SetParLimits(0,1.,150.);
  g4->SetParLimits(1,7.25,7.65);
  g4->SetParLimits(2,0.1,3.);

  c1->cd();
  hsumm->Draw();
  hsumm->Fit("g1","R+");
  hsumm->Fit("g2","R+");
  hsumm->Fit("g3","R+");
  hsumm->Fit("g4","R+");
  hsumm->GetXaxis()->SetRangeUser(0.85,9.);
  /*TCanvas *c[4];
  for(Int_t i=0;i<4;i++){
    cName.Form("c%d",i+1);
    c[i] = new TCanvas(cName.Data(),"calibrated spectra",1000,1000);
    c[i]->Divide(2,2);
  }

	ofstream outcalfile;
	outcalfile.open("/home/muzalevsky/work/exp1803/data/dataCal/check_cali.txt");
	if (!outcalfile.is_open()) {
		cout <<"Output file was not opened" << endl;
		return;
	}

  Int_t count=-1;
  Int_t nPad;
  for(Int_t i=0;i<nhists;i++) {
    count = i/4;
    nPad = (i%4)+1;
    c[count]->cd(nPad);

    h[i]->Draw();
    h[i]->Rebin(8);
    h[i]->Fit("g1","R+");
    h[i]->Fit("g2","R+");
    h[i]->Fit("g3","R+");
    h[i]->Fit("g4","R+");
    h[i]->GetXaxis()->SetRangeUser(4.,8.);
    c[count]->Update();
    outcalfile << g1->GetParameter(1) << "\t" << g2->GetParameter(1) << "\t" << g3->GetParameter(1) << "\t" << g4->GetParameter(1) << endl; 
  }
*/
  } // if(par1)
///////////////////////////////////
  if(par2) {
	  TTree* 		t;
	  UShort_t    NeEvent_SQ20[16];
	  UShort_t    NeEvent_SQX_L[32];
	  UShort_t    NeEvent_SQY_L[16];
	  TBranch    *b_NeEvent_SQ20;
	  TBranch    *b_NeEvent_SQX_L;
	  TBranch    *b_NeEvent_SQY_L;

	  Float_t parSQX1[32], parSQX2[32],parSQY1[16],parSQY2[16],parSQ201[16],parSQ202[16];
    // Reading cal parameters 
  //------------------------------------------------------------------------------ 
   // for 1 mm Si detector
    TString line1;
    ifstream myfile1;
    Int_t count=-2;
    myfile1.open("/home/muzalevsky/work/exp1803/data/dataCal/SQX_L.cal");
    while (! myfile1.eof() ){
		  line1.ReadLine(myfile1);
      if(count < 0){
        count++;
        continue;
      }
		  if(line1.IsNull()) break;
      sscanf(line1.Data(),"%g %g", parSQX1+count,parSQX2+count);
      count++;
    }
    parSQX1[6]=0.;parSQX2[6]=0.;
   // for(Int_t i=0;i<32;i++) cout << parSQX1[i] << " " << parSQX2[i] << endl;  

    ifstream myfile2;
    TString line2;
    count=-2;
    myfile2.open("/home/muzalevsky/work/exp1803/data/dataCal/SQY_L.cal");
    while (! myfile2.eof() ){
		  line2.ReadLine(myfile2);
      if(count < 0){
        count++;
        continue;
      }
		  if(line2.IsNull()) break;
      sscanf(line2.Data(),"%g %g", parSQY1+count,parSQY2+count);
      count++;
    }
    parSQY1[0]=0.;parSQY2[0]=0.;
    //for(Int_t i=0;i<16;i++) cout << parSQY1[i] << " " << parSQY2[i] << endl;   

   // for 20 mkm Si detector
    ifstream myfile3;
    TString line3;
    count=-2;
    myfile3.open("/home/muzalevsky/work/exp1803/data/dataCal/SQ20.cal");
    while (! myfile3.eof() ){
		  line3.ReadLine(myfile3);
      if(count < 0){
        count++;
        continue;
      }
		  if(line3.IsNull()) break;
      sscanf(line3.Data(),"%g %g", parSQ201+count,parSQ202+count);
      count++;
    }
    parSQ201[14]=0.;parSQ202[14]=0.;
    parSQ201[15]=0.;parSQ202[15]=0.;
    //for(Int_t i=0;i<16;i++) cout << parSQ201[i] << " " << parSQ202[i] << endl;   

    // Creating outfile,outtree
  //------------------------------------------------------------------------------ 
	  TFile *f[100];  
	  TString input_file;
	  Float_t SQX_L[32],SQY_L[16],SQ20[16],clasterX,clasterY,summX,summY;
    Int_t n =10,maxE;
    Long64_t nentries;

	  TFile *fw = new TFile("/home/muzalevsky/work/exp1803/data/exp1804/h5_14/outCal.root", "RECREATE");
	  TTree *tw = new TTree("tree", "merged data in energies");
	  tw->Branch("SQX_L",&SQX_L,"SQX_L[32]/F");
	  tw->Branch("SQY_L",&SQY_L,"SQY_L[16]/F");
	  tw->Branch("SQ20",&SQ20,"SQ20[16]/F");
	  tw->Branch("summX",&summX,"summX/F");
	  tw->Branch("summY",&summY,"summY/F");

    // Reading input filesm, filling out tree
  //----------------------------------------------------------------------------------
    //for(Int_t n=10;n<20;n++){
      input_file.Form("/media/analysis_nas/exp201804/rootfiles/h5_14_00%d.root",n);		
	    //f[n] = new TFile(input_file.Data());
      f[n] = new TFile("/media/analysis_nas/exp201804/calib/si_1000_LR_02_0001.root");
	    if (f[n]->IsZombie()) {
		    cerr << "Input file was not opened " << input_file.Data() << endl;
		    return 1;
	    }

	    f[n]->GetObject("AnalysisxTree",t);
	    t->SetMakeClass(1);
	    t->SetBranchAddress("NeEvent.SQX_L[32]", NeEvent_SQX_L, &b_NeEvent_SQX_L);
	    t->SetBranchAddress("NeEvent.SQY_L[16]", NeEvent_SQY_L, &b_NeEvent_SQY_L);
      t->SetBranchAddress("NeEvent.SQ20[16]", NeEvent_SQ20, &b_NeEvent_SQ20);
	    nentries = t->GetEntries();

      maxE = nentries;
      cout<<">>> filling TREE up to "<<maxE<< " event"<<endl;
	    for (Long64_t jentry=0; jentry<maxE;jentry++) {
		    t->GetEntry(jentry);
        summX=0.;
        summY=0.;
		    for(Int_t i=0; i<32; i++){
          SQX_L[i]=-1.;// обнуление
          if(i<16) {
            SQ20[i]=-1.;
            SQY_L[i] = -1.;
          }

          SQX_L[i] = NeEvent_SQX_L[i]*parSQX2[i] + parSQX1[i];
          summX += SQX_L[i];
          if(i<16){
            //if(NeEvent_SQ20[i]>150.) { //cut the pedestal, calculating
            SQ20[i] = NeEvent_SQ20[i]*parSQ202[i] + parSQ201[i];
            SQY_L[i] = NeEvent_SQY_L[i]*parSQY2[i] + parSQY1[i];
            summY += SQY_L[i];
            //}
          }
	      } // i<32

       /* // fill clasters
        if(SQX_L[15]>1.1 && SQX_L[14]<1 && SQX_L[16]<1){ //cut the pedestal, calculating
          clasterX = SQX_L[14] + SQX_L[15] + SQX_L[16];  
        }
        if(SQY_L[7]>0.85 && SQY_L[6]<0.85 && SQY_L[8]<0.85){ 
          clasterY = SQY_L[6] + SQY_L[7] + SQY_L[8];  
        }*/

		    tw->Fill();			
	    }//entries
    //}// nfiles

  // writing outfile
  //----------------------------------------------------------------------------------
    fw->cd();
	  tw->Write();
	  fw->Close();
  } //if par2

  return;
}
