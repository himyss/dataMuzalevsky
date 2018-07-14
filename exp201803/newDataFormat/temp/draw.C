{
  
  TChain *t = new TChain("stepMonitoringxTree");
	t->Add("/media/analysis_nas/exp201804/rootfilesEgor/h5_14_00*");
  t->MakeClass("temp")
}
