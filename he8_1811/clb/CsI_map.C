void CsI_map() {

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  TString cut,hDraw;
  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(4,4);

  c1->cd(1);
  ch->Draw("nCsI","nX_C<8 && nY_C<8 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(2);
  ch->Draw("nCsI","nX_C>7 && nX_C<16 && nY_C<8 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(3);
  ch->Draw("nCsI","nX_C>15 && nX_C<24 && nY_C<8 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(4);
  ch->Draw("nCsI","nX_C>24 && nY_C<8 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");  


  c1->cd(5);
  ch->Draw("nCsI","nX_C<8 && nY_C>7 && nY_C<16 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(6);
  ch->Draw("nCsI","nX_C>7 && nX_C<16 && nY_C>7 && nY_C<16 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(7);
  ch->Draw("nCsI","nX_C>15 && nX_C<24 && nY_C>7 && nY_C<16 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(8);
  ch->Draw("nCsI","nX_C>24 && nY_C>7 && nY_C<16 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");


  c1->cd(9);
  ch->Draw("nCsI","nX_C<8 && nY_C>15 && nY_C<24 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(10);
  ch->Draw("nCsI","nX_C>7 && nX_C<16 && nY_C>15 && nY_C<24 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(11);
  ch->Draw("nCsI","nX_C>15 && nX_C<24 && nY_C>15 && nY_C<24 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(12);
  ch->Draw("nCsI","nX_C>24 && nY_C>15 && nY_C<24 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");


  c1->cd(13);
  ch->Draw("nCsI","nX_C<8 && nY_C>23 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(14);
  ch->Draw("nCsI","nX_C>7 && nX_C<16 && nY_C>23 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(15);
  ch->Draw("nCsI","nX_C>15 && nX_C<24 && nY_C>23 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");

  c1->cd(16);
  ch->Draw("nCsI","nX_C>24 && nY_C>23 && nTarget==1 && timesDSDY_C==1 && timesDSDX_C==1 && aCsI>0","");



}