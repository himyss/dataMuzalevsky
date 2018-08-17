void drawBanana(){

  TF1 *f = new TF1("f","50/(x)",10,200);
  // TF1 *fa1 = new TF1("fa1","sin(x)/x",0,10);

  TChain *ch = new TChain("tree");
  ch->Add("/media/user/work/data/analysisexp1804/tmp.root");

  TCanvas *c1 = new TCanvas("c1","de-E plots");
  // c1->Divide(2,1);
  //TH2F *h = new TH2F("h","dE-E",500,0,4000,500,0,50);
  TString hDraw,hCut,hName;

  TH2F *hSum,*htemp;
  hSum = new TH2F("hSum","summ dE-E",200,1,200,200,1,45);

  // c1->cd(1);  
  for(Int_t i=0;i<1;i++){
    // c1->cd(i+1);
    hDraw.Form("SQX_R:(CsI_R[%d]+SQX_R)>>h(200,1,200,200,1,45)",i);
    hCut.Form("CsI_R[%d]>1 && tCsI_R[%d]>740 && tCsI_R[%d]<840 && trigger==3 && (SQX_R>60./CsI_R[%d])",i,i,i,i);
    ch->Draw(hDraw.Data(),hCut.Data(),"col");

    htemp = (TH2F*)gPad->GetPrimitive("h");
    // cout << htemp->GetEntries() << endl;
    hSum->Add(htemp);
    //if(i!=0) ch->Draw(hDraw.Data(),hCut.Data(),"same");
    c1->Update();
    cout <<  i << endl;
    //gPad->SetLogz();

  }
  c1->cd(2);
  // hSum->Draw("col");
  // f->Draw("same");
  // f->SetLineWidth(2);
  // f->SetLineColor(4);
  c1->Update();


  TFile *fw = new TFile("left_tele/bananaR.root", "RECREATE");
  fw->cd();
  hSum->Write();
  fw->Close();

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
