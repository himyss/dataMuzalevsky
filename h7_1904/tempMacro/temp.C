void readCuts(){

  TChain *ch = new TChain("er");
  ch->Add("/home/oem/work/data/exp1811/digi/clb/dsd_20_l_03*");
}
