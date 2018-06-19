void drawCal(){


  TString cut;
  TString cut_0[16];
  TString cut1("");
  TString cut2("");
  TString cut3("");
  TString cut4("");
  
  TString hDraw,hDraw1,hdraw2,hdraw3,hname,hcut,cuttemp;
  TString d1,d2,d3,d4;

  TH1F *h0,*h1,*h2,*h[300];



  TChain *ch = new TChain("tree");
	ch->Add("/home/muzalevsky/work/exp1803/data/exp1804/h5_14_identificationH3_2.root");

 // TChain *ch = new TChain("AnalysisxTree");
	//ch->Add("/media/analysis_nas/exp201804/rootfiles/h5_14_00*.root");
 
  TCanvas *c1 = new TCanvas("c1","raw data",1800,1000);
  c1->Divide(2,2);

 // c1->cd(1);
  //ch->Draw("(0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[])>>(200,0,80)","NeEvent.SQX_R[]>3 && NeEvent.SQX_R[]<20 && (0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[])>0 && (0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[])<80",""); 
  //ch->Draw("tF5[]-tSQX_R[]:SQX_R[]>>(200,3,80,200,0,200)","",""); 
 // ch->Draw("tF5[]-tSQX_R[]:SQX_R[]>>(200,3,80,200,0,200)","",""); 

  c1->cd(1);
  ch->Draw("SQX_R[]>>h1(500,3,20)","","");
  c1->Update();

  c1->cd(2); 
  ch->Draw("CsI_R[]>>(300,0,150)","CsI_R[]>0","");
  //ch->Draw(hDraw1.Data(),"(0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12])>0 && (0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12])<80","");
  //ch->Draw("CsI_R[]>>(900,100,1000)","CsI_R[]>0 && SQX_R[]>3 && SQX_R[]<20 && (tSQX_R[]-tF5[])>0 && (tSQX_R[]-tF5[])<80",""); 
  c1->Update();



  c1->cd(3);
  ch->Draw("SQX_R[12]:CsI_R[5]","CsI_R[5]>0",""); 
 // ch->Draw(hdraw3.Data(),hcut.Data(),"");  
  c1->Update();

  //c1->cd(4);
  //ch->Draw("SQX_R[]:CsI_R[]","CsI_R[]>0","same"); 
 // ch->Draw(hdraw3.Data(),hcut.Data(),"");  
  c1->Update();

return;
/*

  d1.Form("(NeEvent.SQX_R[31]*%g+%g):NeEvent.CsI_R[1]>>h5(1000,100,5000,200,3,20)",parXR2[12],parXR1[12]);
  ch->Draw(d1.Data(),hcut.Data(),"same");  
  c1->Update();

  d2.Form("(NeEvent.SQX_R[31]*%g+%g):NeEvent.CsI_R[9]>>h5(1000,100,5000,200,3,20)",parXR2[12],parXR1[12]);
  ch->Draw(d2.Data(),hcut.Data(),"same");  
  c1->Update();

  d3.Form("(NeEvent.SQX_R[31]*%g+%g):NeEvent.CsI_R[13]>>h5(1000,100,5000,200,3,20)",parXR2[12],parXR1[12]);
  ch->Draw(d3.Data(),hcut.Data(),"same");  
  c1->Update();

  c1->cd(4);
  ch->Draw("NeEvent.SQX_R[31]:NeEvent.CsI_R[5]>>h4(1000,100,5000,1000,200,2500)",hcut.Data(),""); 
  c1->Update();

  //TCanvas *c2 = new TCanvas("c2","raw data",1800,1000);
 // gPad->SetLogz();
 // cuttemp.Form("(0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12])>0 && (0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12])<80 && (NeEvent.SQX_R[12]*%g+%g)>3",parXR2[12],parXR1[12]);
  //ch->Draw("NeEvent.SQX_R[12]:0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12]","","");

  //cuttemp.Form("(0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12])>0 && (0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12])<80 && (NeEvent.SQX_R[12]*%g+%g)>3",parXR2[12],parXR1[12]);
 // ch->Draw("NeEvent.SQX_R[12]:0.125*NeEvent.tF5[]-0.3*NeEvent.tSQX_R[12]",cuttemp.Data(),"");

 // cuttemp.Form("(tF5[]-tSQX_R[12])>0 && (tF5[]-tSQX_R[12])<80 && (SQX_R[12])>3");
//  ch->Draw("SQX_R[12]:tF5[]-tSQX_R[12]","(tF5[]-tSQX_R[12])>0 && (tF5[]-tSQX_R[12])<80 && (SQX_R[12])>3","");
  //ch->Draw("SQX_R[12]:tF5[1]-tSQX_R[12]","(tF5[1]-tSQX_R[12])>0 && (tF5[1]-tSQX_R[12])<80 && SQX_R[12]>3","");
  //ch->Draw("SQX_R[12]:(tSQX_R[12]-tF5[])","","");
*/
  return;  
}
