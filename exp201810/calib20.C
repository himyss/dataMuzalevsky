void calib20(){
  
  TString fileName("/media/user/work/data/exp201810/calib/Right_20um/DSDX_Rtrigg.root");
  TFile *f = new TFile(fileName.Data());
  if(!f) {
    cout << "File " << fileName.Data() << " does not exist." << endl;
    return;
  }

  TString treeName("AnalysisxTree");
  TTree *t = (TTree*)f->Get(treeName.Data());
  if(!t) {
    cout << "Tree " << treeName.Data() << " does not exist." << endl;
    return;
  }

//--------------------------------------------------------------------------------
  t->Draw("(DSDY_R[5]*0.02339 - 1.101)>>(150,1,9)","","");
  // t->Draw("NeEvent.DSDY_R[5]>>(400,85,500)","","", 690709, 0);
}