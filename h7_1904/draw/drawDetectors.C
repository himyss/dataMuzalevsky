{
  
  TChain *ch = new TChain("tree");
  // ch->Add("/media/user/work/data/Analysed1811/siParTests/analysed/he8_full_cut.root");
  ch->Add("/media/ivan/data/exp1904/analysed/oldPars/select.root");
  // ch->Add("/media/user/work/data/Analysed1811/selected/he8_full_cut_emptyTarget.root");
  cout << ch->GetEntries() << endl;

  TCanvas *c1 = new TCanvas("c1","",1000,1000); 
  ch->SetMarkerStyle(20);

  ch->SetMarkerColor(kBlack);
  ch->Draw("y1t:x1t >> h1(48,-75,75,48,-75,75)","flag1","");
  c1->Update();

  ch->SetMarkerColor(kRed);
  ch->Draw("y2t:x2t >> h2(48,-75,75,48,-75,75)","flag2","same");
  c1->Update();

  ch->SetMarkerColor(kGreen);
  ch->Draw("y3t:x3t >> h3((48,-75,75,48,-75,75)","flag3","same");
  c1->Update();

  ch->SetMarkerColor(kBlue);
  ch->Draw("y4t:x4t >> h4(48,-75,75,48,-75,75)","flag4","same");
  c1->Update();

  TCanvas *c2 = new TCanvas("c2","",1000,1000);
  c2->Divide(2,2);

  c2->cd(2);
  ch->Draw("n1_1:n20_1","flag1","");
  
  c2->cd(4);
  ch->Draw("n20_2:n1_2","flag2","");

  c2->cd(3);
  ch->Draw("n1_3:n20_3","flag3","");

  c2->cd(1);
  ch->Draw("n20_4:n1_4","flag4","");
}