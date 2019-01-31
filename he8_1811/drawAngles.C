{

  Bool_t MM,angles;
  MM = 1;
  angles = 2;

  // gStyle->SetOptStat(0);

  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/user/work/data/Analysed1811/selected/he8_missing_mass1.root");
  cout << ch1->GetEntries() << " total number of Entries" << endl;


  TChain *ch2 = new TChain("tree");//e24
  ch2->Add("/media/user/work/data/Analysed1811/selected/he8_missing_mass2.root");
  cout << ch2->GetEntries() << " total number of Entries" << endl;

  TChain *ch3 = new TChain("tree");//ecal
  ch3->Add("/media/user/work/data/Analysed1811/selected/he8_missing_mass3.root");
  cout << ch3->GetEntries() << " total number of Entries" << endl;

  //--------------------------------------------------------------------------------
  if (MM) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    // c1->Divide(2,1);

    // c1->cd(1);
    // ch->Draw("angle_h3_h7.>>h1(30,0,15)","flagLeft && flagCent && nh3 && nhe3","", 5390, 0);

    TF1 *f1 = new TF1();

    // c1->cd(2);
    // ch->Draw("1000*(eh7.-4*0.939565-2.80892)","nhe3 && flagLeft","", 5390, 0);
    ch1->SetLineColor(kBlack);
    ch1->SetLineWidth(3.);
    // c1->cd(1);
    ch1->Draw("1000*(mh7.-4*0.939565-2.808920)>>h1(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0","");
return;
    // ch1->SetLineColor(kRed);
    // ch1->Draw("1000*(mh7.-4*0.939565-2.808920)>>h1_1(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)>-35 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)<-30","same");  

    // ch1->SetLineColor(kBlue);
    // ch1->Draw("1000*(mh7.-4*0.939565-2.808920)>>h1_2(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)>-30 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)<-25","same");  
    // ch1->SetLineColor(kBlack);

    // ch2->SetLineColor(kBlack);
    // ch2->SetLineWidth(3.);
    // c1->cd(2);
    // ch2->Draw("1000*(mh7.-4*0.939565-2.808920)>>h2(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0","");  

    // ch2->SetLineColor(kRed);
    // ch2->Draw("1000*(mh7.-4*0.939565-2.808920)>>h2_1(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)>-35 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)<-30","same");  

    // ch2->SetLineColor(kBlue);
    // ch2->Draw("1000*(mh7.-4*0.939565-2.808920)>>h2_2(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)>-30 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)<-25","same");  
    // ch2->SetLineColor(kBlack);

    // ch3->SetLineColor(kBlack);
    // ch3->SetLineWidth(3.);
    // c1->cd(3);
    // ch3->Draw("1000*(mh7.-4*0.939565-2.808920)>>h3(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0","");

    // ch3->SetLineColor(kRed);
    // ch3->Draw("1000*(mh7.-4*0.939565-2.808920)>>h3_1(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)>-35 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)<-30","same");  

    // ch3->SetLineColor(kBlue);
    // ch3->Draw("1000*(mh7.-4*0.939565-2.808920)>>h3_2(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)>-30 && 1000*(7.482538 + 1.874319 - mh7- 2.808391)<-25","same");  
    // ch3->SetLineColor(kBlack);


    c1->cd(2);
    ch1->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h4(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");

    // c1->cd(5);
    // ch2->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h5(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");  

    // c1->cd(6);
    // ch3->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h6(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");

  }

  if (angles) {
    TCanvas *c2 = new TCanvas("c2","",1800,1000);  
    c2->Divide(2,2);

    // c2->cd(1);
    // ch1->Draw("angle_h3_h7.>>h2_1(30,0,15)","flagLeft && flagCent && nh3 && nhe3 && eh3>0.06 ","", 5390, 0);

    // c2->cd(2);
    // ch1->Draw("angle_h3_h7CMreaction.>>h2_2(40,0,180)","flagLeft && flagCent && nh3 && nhe3 && eh3>0.06 ","", 5390, 0);

    // c2->cd(3);
    // ch1->Draw("angle_h3_h7CM.>>h2_3(40,0,5)","flagLeft && flagCent && nh3 && nhe3 && eh3>0.06 ","", 5390, 0);

    c2->cd(1);
    ch1->Draw("ehe3.>>h3_1_123(35,0.,045)","flagLeft && nhe3 ","", 5390, 0);

    c2->cd(2);
    ch2->Draw("ehe3.>>h3_4(35,0.,0.045)","flagLeft && nhe3","", 5390, 0);

    c2->cd(3);
    ch3->Draw("ehe3.>>h3_4_2(35,0.,0.045)","flagLeft && nhe3","", 5390, 0);
    

  }

}