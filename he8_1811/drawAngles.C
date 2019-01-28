{
  gStyle->SetOptStat(0);

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
  TCanvas *c1 = new TCanvas("c1","",1800,1000);  
  c1->Divide(3,2);

  // c1->cd(1);
  // ch->Draw("angle_h3_h7.>>h1(30,0,15)","flagLeft && flagCent && nh3 && nhe3","", 5390, 0);

  // c1->cd(2);
  // ch->Draw("1000*(eh7.-4*0.939565-2.80892)","nhe3 && flagLeft","", 5390, 0);

  c1->cd(1);
  ch1->Draw("1000*(mh7.-4*0.939565-2.808920)>>h1(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0","");

  c1->cd(2);
  ch2->Draw("1000*(mh7.-4*0.939565-2.808920)>>h2(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0","");  

  c1->cd(3);
  ch3->Draw("1000*(mh7.-4*0.939565-2.808920)>>h3(20,-5,25)","nhe3 && flagLeft && nh3 && eh3>0","");

  c1->cd(4);
  ch1->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h4(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");

  c1->cd(5);
  ch2->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h5(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");  

  c1->cd(6);
  ch3->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h6(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");



return;
  // c1->cd(2);
  // ch->Draw("angle_h3_h7CM.>>h2(30,0,180)","flagLeft && flagCent && nh3 && nhe3 && ehe3<0.022","", 5390, 0);

  // c1->cd(3);
  // ch->Draw("ehe3.>>h3(25,0.005,0.03)","flagLeft && flagCent && nh3 && nhe3 && ehe3<0.022","", 5390, 0);

  // c1->cd(4);
  // ch->Draw("ehe3.>>h3(35,0.,0.045)","flagLeft && flagCent && nh3 && nhe3","", 5390, 0);

}