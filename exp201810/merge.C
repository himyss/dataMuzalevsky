void merge(){
  TChain *f = new TChain("AnalysisxTree");
  f->Add("/media/user/work/data/exp201810/calib/Right_20um/dsd_20_r_02_000*");
  f->Merge("/media/user/work/data/exp201810/calib/Right_20um/DSDX_Rtrigg.root");

}