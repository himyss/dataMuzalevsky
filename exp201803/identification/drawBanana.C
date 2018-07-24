void drawBanana(){

  TChain *ch = new TChain("tree");
  ch->Add("/home/muzalevsky/work/exp1803/data/exp1804/h5_14_id1_test.root");

  TCanvas *c1 = new TCanvas("c1","");
  c1->Divide(2,2);
  //TH2F *h = new TH2F("h","dE-E",500,0,4000,500,0,50);
  TString hDraw,hCut;

  for(Int_t i=0;i<4;i++){
    c1->cd(i+1);
    hDraw.Form("SQX_R:CsI_R[%d]>>h%d(500,0,5000,500,0,45)",i+4,i);
    hCut.Form("SQX_R[]>1 && CsI_R[%d]>100 && tCsI_R[%d]>740 && tCsI_R[%d]<840",i+4,i+4,i+4);
    ch->Draw(hDraw.Data(),hCut.Data(),"");
    //gPad->SetLogz();
  }

 // ch->Draw("SQX_R[8]:CsI_R[5] >> h1(500,0,4000,500,0,50)","SQX_R[8]>1 && CsI_R[5]>100","");
  /*ch->SetMarkerColor(2);  
  ch->Draw("SQX_R[9]:CsI_R[5]","SQX_R[9]>1 && CsI_R[5]>100","same");
  ch->SetMarkerColor(3);  
  ch->Draw("SQX_R[10]:CsI_R[5]","SQX_R[10]>1 && CsI_R[5]>100","same");
  ch->SetMarkerColor(4);  
  ch->Draw("SQX_R[11]:CsI_R[5]","SQX_R[11]>1 && CsI_R[5]>100","same");
  ch->SetMarkerColor(5);  
  ch->Draw("SQX_R[12]:CsI_R[5]","SQX_R[12]>1 && CsI_R[5]>100","same");
  ch->SetMarkerColor(6);  
  ch->Draw("SQX_R[13]:CsI_R[5]","SQX_R[13]>1 && CsI_R[5]>100","same");
  ch->SetMarkerColor(7);  
  ch->Draw("SQX_R[14]:CsI_R[5]","SQX_R[14]>1 && CsI_R[5]>100","same");
  ch->SetMarkerColor(8);  
  ch->Draw("SQX_R[15]:CsI_R[5]","SQX_R[15]>1 && CsI_R[5]>100","same");*/
 

 /* ch->Draw("SQX_R[20]:CsI_R[6]","SQX_R[28]>1 && CsI_R[6]>100","");
  ch->SetMarkerColor(2);  
  ch->Draw("SQX_R[21]:CsI_R[6]","SQX_R[29]>1 && CsI_R[6]>100","same");
  ch->SetMarkerColor(3);  
  ch->Draw("SQX_R[22]:CsI_R[6]","SQX_R[30]>1 && CsI_R[6]>100","same");
  ch->SetMarkerColor(4);  
  ch->Draw("SQX_R[23]:CsI_R[6]","SQX_R[31]>1 && CsI_R[6]>100","same");*/

}
