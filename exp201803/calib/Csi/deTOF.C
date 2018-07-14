void deTOF(){

  TChain *ch = new TChain("AnalysisxTree");
  ch->Add("/media/analysis_nas/exp201803/rootfiles/csi02_*");
  ch->Add("/media/analysis_nas/exp201803/rootfiles/csi03_*");
  ch->Add("/media/analysis_nas/exp201803/rootfiles/csi04_*");
  cout << ch->GetEntries() << endl;

  Int_t can1,can2,can3,can4;
  //can1=1;
  //can2=1;
  //can3=1;
  if(can1){  
    TCanvas *c1 = new TCanvas("c1","dE-ToF",1800,1000);
    c1->Divide(2,2);
    c1->cd(1);
    //c1_1->SetLogz();
    ch->Draw("NeEvent.F5[]+NeEvent.F3[]:(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165>>h1(300,100,180,1000,0,4000)","trigger==1 && (NeEvent.SQX_R[18]*0.02003-1.286)>1","col");
    c1->GetPad(1)->SetLogz();
    c1->Update();

    c1->cd(2);
    ch->Draw("NeEvent.F5[]+NeEvent.F3[]:(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165>>h2(100,150,175,100,200,800)","trigger==1 && (NeEvent.SQX_R[18]*0.02003-1.286)>1","col");
    c1->GetPad(2)->SetLogz();
    c1->Update();



    //ch->Draw("NeEvent.F5[]+NeEvent.F3[]:NeEvent.tF5[]-NeEvent.tF3[]>>h(1000,0,1000,1000,0,4000)","","col",10000,0); 
   // NeEvent.tF5[]-NeEvent.tF3[] ()
   // NeEvent.F5[]+NeEvent.F3[] 
    c1->cd(3);

    ch->Draw("NeEvent.SQX_R[18]*0.02003-1.286:NeEvent.CsI_R[6]>>h3(2000,0,7000,500,0,40)","trigger==1 && (NeEvent.SQX_R[18]*0.02003-1.286)>1","col");
    c1->GetPad(3)->SetLogz();
    c1->Update();

    c1->cd(4);
    TString trCut("trigger==1 && (NeEvent.SQX_R[18]*0.02003-1.286)>1 && (NeEvent.F5[]+NeEvent.F3[])>200 && (NeEvent.F5[]+NeEvent.F3[])<750 && ((NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165)>150 && ((NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165)<175");
    ch->Draw("NeEvent.SQX_R[18]*0.02003-1.286:NeEvent.CsI_R[6]>>h4(2000,0,7000,500,0,40)",trCut.Data(),"col");
    c1->GetPad(4)->SetLogz();
    c1->Update();
  }

  if(can2){
    TCanvas *c2 = new TCanvas("c2","dE-ToF",1800,1000);
    c2->Divide(2,2);
    c2->cd(1);
    //c1_1->SetLogz();
    ch->Draw("NeEvent.F5[]+NeEvent.F3[]:(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165>>h5(300,100,180,1000,0,4000)","trigger==1 && (NeEvent.SQX_R[12]*0.02346-1.694)>1","col");
    c2->GetPad(1)->SetLogz();
    c2->Update();

    c2->cd(2);
    ch->Draw("NeEvent.F5[]+NeEvent.F3[]:(NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165>>h6(100,150,175,100,200,800)","trigger==1 && (NeEvent.SQX_R[12]*0.02346-1.694)>1","col");
    c2->GetPad(2)->SetLogz();
    c2->Update();



    //ch->Draw("NeEvent.F5[]+NeEvent.F3[]:NeEvent.tF5[]-NeEvent.tF3[]>>h(1000,0,1000,1000,0,4000)","","col",10000,0); 
   // NeEvent.tF5[]-NeEvent.tF3[] ()
   // NeEvent.F5[]+NeEvent.F3[] 
    c2->cd(3);

    ch->Draw("NeEvent.SQX_R[12]*0.02346-1.694:NeEvent.CsI_R[9]>>h7(2000,0,7000,500,0,40)","trigger==1 && (NeEvent.SQX_R[12]*0.02346-1.694)>1","col");
    c2->GetPad(3)->SetLogz();
    c2->Update();

    c2->cd(4);
    TString trCut("trigger==1 && (NeEvent.SQX_R[12]*0.02346-1.694)>1 && (NeEvent.F5[]+NeEvent.F3[])>200 && (NeEvent.F5[]+NeEvent.F3[])<750 && ((NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165)>150 && ((NeEvent.tF5[]-NeEvent.tF3[])*0.125+89.165)<175");
    ch->Draw("NeEvent.SQX_R[12]*0.02346-1.694:NeEvent.CsI_R[9]>>h8(500,0,2000,100,0,5)",trCut.Data(),"col");
    c2->GetPad(4)->SetLogz();
    c2->Update();
  }    

  if(can3) { 
    ch->Draw("NeEvent.SQX_R[12]:NeEvent.tSQX_R[12]>>(1000,1000,2000,1000,0,4000)","","");

  }

  
  if(can4) {
    TCanvas *c4 = new TCanvas("c4","cuts",1800,1000);
    c4->cd();
    
  }

 
}
