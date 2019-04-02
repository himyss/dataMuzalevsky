void drawAngles(){
  // gStyle->SetOptStat(0);

  TCutG *mmCut;
  TFile *f1;

  TString cutName;
  cutName.Form("/home/oem/work/macro/he8_1811/graphCut_mm.root");
  f1 = new TFile(cutName.Data());
  mmCut = (TCutG*)f1->Get("CUTG");
  if (!mmCut) {
    cout << " no cut"<< endl;
    return;
  }
  delete f1;


  Bool_t MM,angles,nikolski,kin;
  MM = 1;
  angles = 0;
  nikolski = 0;
  kin = 0;


  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/home/oem/work/data/exp1811/analysed/he8_missing_mass.root");
  TChain *ch2 = new TChain("tree"); //e4
  ch2->Add("/home/oem/work/data/exp1811/analysed/he8_emtpytarget_mm.root");
  // cout << ch1->GetEntries() << " total number of Entries" << endl;

    ch2->SetLineColor(kRed);
    ch2->SetMarkerColor(kRed);
    ch2->SetMarkerStyle(20);


    ch1->SetLineColor(kBlack);
    ch1->SetLineWidth(3.);
    ch1->SetMarkerStyle(20);
  //--------------------------------------------------------------------------------

    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    // c1->Divide(2,2);

    // c1->cd(1);
    // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h2D_1(18,-10,25)","nhe3 && flagLeft && flagCent && nh3 ","");
    // ch2->Draw("1000*(mh7-4*0.939565-2.808920) >> h2D_2(18,-10,25)","nhe3 && flagLeft && flagCent && nh3 ","same");

    // c1->cd(2);
    ch1->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920) >> h2D_3(18,-10,25,40,0,30)","nhe3 && flagLeft && flagCent && nh3","");
    ch2->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920) >> h2D_4(18,-10,25,40,0,30)","nhe3 && flagLeft && flagCent && nh3  ","same");

    // c1->cd(3);
    // ch1->Draw("1000*ehe8:1000*(mh7-4*0.939565-2.808920) >> h2D_5(18,-10,25,40,180,220)","nhe3 && flagLeft && flagCent && nh3  ","");
    // ch2->Draw("1000*ehe8:1000*(mh7-4*0.939565-2.808920) >> h2D_6(18,-10,25,40,180,220)","nhe3 && flagLeft && flagCent && nh3  ","same");

    // c1->cd(4);
    // ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h2D_7(18,-10,25,40,0,120)","nhe3 && flagLeft && flagCent && nh3 ","");
    // ch2->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h2D_8(18,-10,25,40,0,120)","nhe3 && flagLeft && flagCent && nh3 ","same");


  // if (MM) {
    // TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    // c1->Divide(2,2);

    // c1->cd(1);
    // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h2D_1(18,-10,25)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90","");
    // ch2->Draw("1000*(mh7-4*0.939565-2.808920) >> h2D_2(18,-10,25)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90","same");

    // c1->cd(2);
    // ch1->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920) >> h2D_3(18,-10,25,40,0,30)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90","");
    // ch2->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920) >> h2D_4(18,-10,25,40,0,30)","nhe3 && flagLeft && flagCent && nh3  && 1000*eh3>90","same");

    // c1->cd(3);
    // ch1->Draw("1000*ehe8:1000*(mh7-4*0.939565-2.808920) >> h2D_5(18,-10,25,40,180,220)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90 ","");
    // ch2->Draw("1000*ehe8:1000*(mh7-4*0.939565-2.808920) >> h2D_6(18,-10,25,40,180,220)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90 ","same");

    // c1->cd(4);
    // ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h2D_7(18,-10,25,40,0,120)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90 ","");
    // ch2->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h2D_8(18,-10,25,40,0,120)","nhe3 && flagLeft && flagCent && nh3 && 1000*eh3>90 ","same");

    // c1->Print("/home/oem/Desktop/2D_110.png");


    TCanvas *c2 = new TCanvas("c2","",1800,1000);  

    // c2->Divide(2,2);

   // c2->cd(1);
    ch1->Draw("angle_he3_he8:1000*(mh7-4*0.939565-2.808920) >> h2D_angle_1(18,-10,25,50,0,50)","nhe3 && flagLeft && flagCent && nh3","");
    ch2->Draw("angle_he3_he8:1000*(mh7-4*0.939565-2.808920) >> h2D_angle_2(18,-10,25,50,0,50)","nhe3 && flagLeft && flagCent && nh3","same");




    
    // cutName.Form("nhe3 && flagLeft && flagCent && nh3 && %s",mmCut->GetName());
    // // cout << cutName.Data() << endl;

    // // c2->cd(1);
    // // ch1->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h2D_7(18,-10,25,40,0,120)","nhe3 && flagLeft && flagCent && nh3 ","");
    // // ch2->Draw("angle_h3_h7*angle_h3_h7:1000*(mh7-4*0.939565-2.808920) >> h2D_8(18,-10,25,40,0,120)","nhe3 && flagLeft && flagCent && nh3 ","same");
    // // mmCut->Draw("same");

    // // c2->cd(2);
    // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >> h2D_cut1(18,-10,25)",cutName.Data(),"");
    // ch2->Draw("1000*(mh7-4*0.939565-2.808920) >> h2D_cut2(18,-10,25)",cutName.Data(),"same");



    // TCanvas *c2 = new TCanvas("c2","",1800,1000);  

    // ch1->Draw("nX_L.","flagLeft && nh3 && flagCent && nhe3 && angle_he3_he8>16.5 && angle_he3_he8<21","");

    // c1->cd(5);
    // ch1->Draw("1000*ehe3/3.:thetahe3 >> kin_5(40,0,40,15,0,15)","nhe3 && flagLeft && flagCent && nh3","");
    // ch2->Draw("1000*ehe3/3.:thetahe3 >> kin_6(40,0,40,15,0,15)","nhe3 && flagLeft && flagCent && nh3","same");

    // ch2->SetMarkerStyle(20);
    // ch2->SetMarkerColor(kRed);
    // ch2->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920) >> h2D_1(20,-10,25,20,-10,140)","nhe3 && flagLeft && flagCent && nh3","same");
    // // c1->cd(2);
    // // ch2->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_2(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3<20","");
    // // c1->cd(3);
    // // ch3->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_3(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3<20","");


    // // c1->cd(2);
    // // ch1->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920) >> h2D_1(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3>20","");
    // // c1->cd(5);
    // // ch2->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_2(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3>20","");
    // // c1->cd(6);
    // // ch3->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_3(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3>20","");
    // c1->cd(2);
    // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >>mm(20,-10,25)","nhe3 && flagLeft && flagCent && nh3","");
    // ch2->SetLineColor(kRed);
    // ch2->SetLineWidth(3.);
    // ch2->Draw("1000*(mh7-4*0.939565-2.808920) >>mm1(20,-10,25)","nhe3 && flagLeft && flagCent && nh3","same");
    // ch1->SetLineCo*(mh7-4*0.939565-2.808920) >>mm2(15,0,20)","1000*(7.482538 + 1.874319 - mh7- 2.808391)>-30 && nhe3 && flagLeft && flagCent && nh3 && thetahe3<20 && eh3>0.045 && ehe3<0.03","same");


    // ch1->SetLineColor(kBlack);
    // c1->cd(2);
    // ch1->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h4(25,-50,0)","nhe3 && flagLeft && flagCent && nh3 && thetahe3<20 && eh3>0.045 && ehe3<0.03","");

    // c1->cd(5);
    // ch2->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h5(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");  

    // c1->cd(6);
    // ch3->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h6(25,-50,0)","nhe3 && flagLeft && nh3 && eh3>0","");

  // }

if (kin) {
    TCanvas *ckin = new TCanvas("ckin","",1800,1000);  
    ckin->Divide(2,2);

    ckin->cd(1);
    ch1->Draw("thetahe3:thetah3 >> kin_1(15,0,15,20,10,30)","nhe3 && flagLeft && flagCent && nh3","");
    ch2->Draw("thetahe3:thetah3 >> kin_2(15,0,15,20,10,30)","nhe3 && flagLeft && flagCent && nh3","same");

    ckin->cd(2);
    ch1->Draw("1000*ehe3:thetah3 >> kin_3(15,0,15,40,0,40)","nhe3 && flagLeft && flagCent && nh3","");
    ch2->Draw("1000*ehe3:thetah3 >> kin_4(15,0,15,40,0,40)","nhe3 && flagLeft && flagCent && nh3","same");

    ckin->cd(3);
    ch1->Draw("1000*ehe3:thetahe3 >> kin_5(40,0,40,40,0,40)","nhe3 && flagLeft && flagCent && nh3","");
    ch2->Draw("1000*ehe3:thetahe3 >> kin_6(40,0,40,40,0,40)","nhe3 && flagLeft && flagCent && nh3","same");

  // c1->Print("/home/oem/Desktop/pics/d2.pdf");
  // c1->Print("/home/oem/Desktop/pics/d2.pdf[");
  // c1->Print("/home/oem/Desktop/pics/d2.pdf");
  // ckin->Print("/home/oem/Desktop/pics/d2.pdf");
  // ckin->Print("/home/oem/Desktop/pics/d2.pdf]");


 }


if (nikolski) {
    TCanvas *c1 = new TCanvas("c1","",1800,1000);  
    c1->Divide(2,2);

    // c1->cd(1);
    // ch->Draw("angle_h3_h7.>>h1(30,0,15)","flagLeft && flagCent && nh3 && nhe3","", 5390, 0);

    // TF1 *f1 = new TF1();

    ch1->SetMarkerStyle(20);


    // c1->cd(2);
    // ch->Draw("1000*(eh7.-4*0.939565-2.80892)","nhe3 && flagLeft","", 5390, 0);
    ch1->SetLineColor(kBlack);
    ch1->SetLineWidth(3.);


    // c1->cd(1);

    c1->cd(1);
    ch1->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","");
    
    ch2->SetMarkerStyle(20);
    ch2->SetMarkerColor(kRed);
    ch2->Draw("1000*ehe3:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","same");



    c1->cd(2);
    ch1->Draw("angle_he3_he8:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","");
    
    ch2->SetMarkerStyle(20);
    ch2->SetMarkerColor(kRed);
    ch2->Draw("angle_he3_he8:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","same");


    c1->cd(3);
    ch1->Draw("ehe8*1000:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","");
    
    ch2->SetMarkerStyle(20);
    ch2->SetMarkerColor(kRed);
    ch2->Draw("ehe8*1000:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","same");


    c1->cd(4);
    ch1->Draw("eh3*1000:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","");
    
    ch2->SetMarkerStyle(20);
    ch2->SetMarkerColor(kRed);
    ch2->Draw("eh3*1000:1000*(mh7-4*0.939565-2.808920)","nhe3 && flagLeft && flagCent && nh3","same");





    // c1->cd(2);
    // ch2->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_2(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3<20","");
    // c1->cd(3);
    // ch3->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_3(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3<20","");


    // c1->cd(2);
    // ch1->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920) >> h2D_1(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3>20","");
    // c1->cd(5);
    // ch2->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_2(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3>20","");
    // c1->cd(6);
    // // ch3->Draw("angle_h3_h7*angle_h3_h7.:1000*(mh7-4*0.939565-2.808920)>> h2D_3(20,-10,20,20,-10,140)","nhe3 && flagLeft && flagCent && nh3 && eh3>0.06 && ehe3<0.03 && thetahe3>20","");
    // c1->cd(2);
    // ch1->Draw("1000*(mh7-4*0.939565-2.808920) >>mm(20,-10,25)","nhe3 && flagLeft && flagCent && nh3","");
    // ch2->SetLineColor(kRed);
    // ch2->SetLineWidth(3.);
    // ch2->Draw("1000*(mh7-4*0.939565-2.808920) >>mm1(20,-10,25)","nhe3 && flagLeft && flagCent && nh3","same");
    // // ch1->SetLineCo*(mh7-4*0.939565-2.808920) >>mm2(15,0,20)","1000*(7.482538 + 1.874319 - mh7- 2.808391)>-30 && nhe3 && flagLeft && flagCent && nh3 && thetahe3<20 && eh3>0.045 && ehe3<0.03","same");


    // // ch1->SetLineColor(kBlack);
    // // c1->cd(2);
    // // ch1->Draw("1000*(7.482538 + 1.874319 - mh7- 2.808391)>>h4(25,-50,0)","nhe3 && flagLeft && flagCent && nh3 && thetahe3<20 && eh3>0.045 && ehe3<0.03","");

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
    ch1->Draw("ehe3.>>h3_1_123(35,0.,045)","flagLeft && nhe3 ","");

    // c2->cd(2);
    // ch2->Draw("ehe3.>>h3_4(35,0.,0.045)","flagLeft && nhe3","", 5390, 0);

    // c2->cd(3);
    // ch3->Draw("ehe3.>>h3_4_2(35,0.,0.045)","flagLeft && nhe3","", 5390, 0);
    

  }

}