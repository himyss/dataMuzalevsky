void calibrateCsI() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/h7_*_timescut.root");
  // ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/h7_5_timescut.root");
  // ch->Add("/media/ivan/data/exp1904/analysed/novPars/selected/h7_4_timescut.root");
  cout << ch->GetEntries() << endl;

  TString hdraw,cut,gName;

  TF1 *f1 = new TF1("f1", "[0]*x+[1]",300,2500);   
  // hSpectrum->Fit("f1");       //prvotni fitovani

  TGraph *g[16];
  Float_t par1[16],par2[16];

  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4,4);
  for(Int_t i=0;i<16;i++) {

    c1->cd(i+1);

    ch->SetMarkerColor(kBlack);      
    hdraw.Form("aCsI_reco-X_C:arCsI[%d]",i);
    cut.Form("nh3 && nCsI_track==%d",i);
    // gName.Form("graph%d",i);
    ch->Draw(hdraw.Data(),cut.Data(),"");
    g[i] = (TGraph*)gPad->GetPrimitive("Graph");
    g[i]->Fit(f1,"R");
    par1[i] = f1->GetParameter(0);
    par2[i] = f1->GetParameter(1);
    cout << par1[i] << " " << par2[i] << endl;
    c1->Update();
    // break;
  }

  c1->Print("CsI_linFit.png");

  ofstream outfile("CsI.cal");
  if ( !outfile.is_open() ) {
    printf(" File CsI.cal was not open.");
    return;
  } 
  
  for (Int_t i = 0; i < 16; i++) {
    outfile << par2[i] << "\t" << par1[i] << endl;
  }
  outfile.close();
  return;
}