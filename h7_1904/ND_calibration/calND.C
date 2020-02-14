void calND() {
  
  TString hdraw,hcut;

  TChain *ch = new TChain("tree");
  ch->Add("/media/ivan/data/exp1904/analysed/novPars/calibrated/finalCal/h7_ct*");

  ch->SetMarkerStyle(1);

  TCanvas *c1 = new TCanvas("c1","title",1800,900);
  c1->Divide(3,1);

  c1->cd(1);
  Int_t nK=1;
  ch->SetMarkerColor(1);
  hdraw.Form("ND_tac[]:ND_amp[]",nK,nK);
  hcut.Form("ND_tac[] && ND_amp[] && trigger==2",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"");
  c1->Update();    
 
  ch->SetMarkerColor(2);
  hdraw.Form("ND_tac[]:ND_amp[]",nK,nK);
  hcut.Form("ND_tac[]>110 && ND_amp[] && trigger==2",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"same");
  c1->Update();  


  c1->cd(2);
  ch->SetMarkerColor(1);
  hdraw.Form("ND_amp[]:ND_time[]-tF5",nK,nK);
  hcut.Form("ND_tac[] && ND_amp[] && trigger==2",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"");
  c1->Update();    

  ch->SetMarkerColor(2);
  hdraw.Form("ND_amp[]:ND_time[]-tF5",nK,nK);
  hcut.Form("ND_tac[]>110 && ND_amp[] && trigger==2",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"same");
  c1->Update();    

  c1->cd(3);
  ch->SetLineColor(1);
  hdraw.Form("ND_time[]-tF5",nK,nK);
  hcut.Form("ND_tac[] && ND_amp[] && trigger==2",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"");
  c1->Update();    

  ch->SetLineColor(2);
  hdraw.Form("ND_time[]-tF5",nK,nK);
  hcut.Form("ND_tac[]>110 && ND_amp[] && trigger==2",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"same");
  c1->Update();  

  // ch->SetMarkerColor(3);
  // hdraw.Form("ND_amp[%d]:ND_time[%d]-tF5",nK,nK);
  // hcut.Form("ND_tac[%d]<110 && ND_amp[%d] && ND_time[%d]",nK,nK,nK);
  // ch->Draw(hdraw.Data(),hcut.Data(),"same");
  // c1->Update(); 

return;


  // c1->cd();
  // Int_t nK=1;
  // ch->SetMarkerColor(1);
  // hdraw.Form("ND_tac[%d]:ND_amp[%d]",nK,nK);
  // hcut.Form("ND_tac[%d] && ND_amp[%d]",nK,nK);
  // ch->Draw(hdraw.Data(),hcut.Data(),"");
  // c1->Update();    

  // for(nK=2;nK<10;nK++) {
  //   ch->SetMarkerColor(nK);
  //   hdraw.Form("ND_tac[%d]:ND_amp[%d]",nK,nK);
  //   hcut.Form("ND_tac[%d] && ND_amp[%d]",nK,nK);
  //   ch->Draw(hdraw.Data(),hcut.Data(),"same");
  //   c1->Update();    
  // }





return;

  c1->cd(2);

  ch->SetLineColor(1);
  hdraw.Form("ND_tac[%d] >> htemp(100,100,1500)",nK,nK);
  hcut.Form("ND_tac[%d] && ND_amp[%d]>400",nK,nK);
  ch->Draw(hdraw.Data(),hcut.Data(),"");
  c1->Update();

  TH1F *htemp = (TH1F*)gPad->GetPrimitive("htemp");
  cout << htemp->GetMean() << endl;
return;

  // ch->SetLineColor(2);
  // nK = 15;
  // hdraw.Form("ND_tac[%d]",nK,nK);
  // hcut.Form("ND_tac[%d] && ND_amp[%d]>500",nK,nK);
  // ch->Draw(hdraw.Data(),hcut.Data(),"same");
  // c1->Update();

  // ch->SetLineColor(3);
  // nK = 25;
  // hdraw.Form("ND_tac[%d]",nK,nK);
  // hcut.Form("ND_tac[%d] && ND_amp[%d]>500",nK,nK);
  // ch->Draw(hdraw.Data(),hcut.Data(),"same");
  // c1->Update();

  // ch->SetLineColor(4);
  // nK = 30;
  // hdraw.Form("ND_tac[%d]",nK,nK);
  // hcut.Form("ND_tac[%d] && ND_amp[%d]>500",nK,nK);
  // ch->Draw(hdraw.Data(),hcut.Data(),"same");
  // c1->Update();


}