{
  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_10_new_selected.root");
    // ch->Add("/media/user/work/data/Analysed1811/selected/he8_10_selected.root");
  cout << ch->GetEntries() << endl;
  //--------------------------------------------------------------------------------
  gStyle->SetOptStat(0);
  // TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  // c1->Divide(2,2);


  // TString hcut;
  // for(Int_t i=0;i<16;i++) {
  //   c1->cd(i+1);
  //   hcut.Form("nX_L==%d",i);
  //   ch->Draw("X_L:tX_L-tF5",hcut.Data(),"");
  //   c1->Update();

  // }

  // for(Int_t i=0;i<16;i++) {
  //   c1->cd(i+1);
  //   hcut.Form("nY_L==%d",i);
  //   ch->Draw("Y_L:tY_L-tF5",hcut.Data(),"");
  //   c1->Update();

  // }
 
  // c1->cd(1);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L<8 && nX_L<8","");
  // c1->Update();

  // c1->cd(2);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>7 &&  nX_L<8","");
  // c1->Update();

  // c1->cd(3);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L<8 && nX_L>7","");
  // c1->Update();  

  // c1->cd(4);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>7 &&  nX_L>7","");
  // c1->Update(); 


  // TCanvas *c2 = new TCanvas("c2","",1800,1000);  
  // c2->Divide(2,2);

  // c2->cd(1);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>7 && nY_L<12 && nX_L>7 && nX_L<12","");
  // c2->Update();

  // c2->cd(2);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>7 && nY_L<12 && nX_L>11","");
  // c2->Update();

  // c2->cd(3);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>11 && nY_L<16 && nX_L>7 && nX_L<12","");
  // c2->Update();

  // c2->cd(4);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>11 && nY_L<16 && nX_L>11","");
  // c2->Update();

  // TCanvas *c3 = new TCanvas("c3","",1800,1000);  
  // c3->Divide(2,2);

  // c3->cd(1);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>7 && nY_L<10 && nX_L>11 && nX_L<14","");
  // c3->Update();

  // c3->cd(2);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>7 && nY_L<10 && nX_L>13 && nX_L<16","");
  // c3->Update();

  // c3->cd(3);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>9 && nY_L<12 && nX_L>11 && nX_L<14","");
  // c3->Update();

  // c3->cd(4);
  // ch->Draw("X_L:Y_L","X_L>0 && Y_L>0 && nY_L>9 && nY_L<12 && nX_L>13 && nX_L<16","");
  // c3->Update();
  TF1 *g = new TF1("g","x",0,90);
  g->SetLineColor(kRed);
  g->SetLineWidth(2);


  TCanvas *c4 = new TCanvas("c4","",1800,1000);  
  c4->Divide(2,2);

  c4->cd(1);
  ch->Draw("X_L:Y_L>>h1(300,0,90,300,0,90)","X_L>0 && Y_L>0 && nY_L==8 && nX_L==14","col");
  // g->Draw("same");
  c4->Update();

  c4->cd(2);
  ch->Draw("X_L:Y_L>>h2(300,0,90,300,0,90)","X_L>0 && Y_L>0 && nY_L==9 && nX_L==14","col");
  // g->Draw("same");
  c4->Update();

  c4->cd(3);
  ch->Draw("X_L:Y_L>>h3(300,0,90,300,0,90)","X_L>0 && Y_L>0 && nY_L==8 && nX_L==15","col");
  // g->Draw("same");
  c4->Update();

  c4->cd(4);
  ch->Draw("X_L:Y_L>>h4(300,0,90,300,0,90)","X_L>0 && Y_L>0 && nY_L==9 && nX_L==15","col");
  // g->Draw("same");
  c4->Update();


}