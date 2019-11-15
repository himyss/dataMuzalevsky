void profile(){
  
  TChain *ch1 = new TChain("tree"); //e4
  ch1->Add("/media/ivan/data/exp1906/be10/analysed/beamDiagnostics/be10_mm.root");


  TCanvas *c1 = new TCanvas("c1","",1800,1000);
  // c1->Divide(2,2);

  // c1->cd(1);
  // ch1->Draw("fXt >> h1(97,-30,30)","","");
  // c1->Update();

  // c1->cd(2);
  ch1->Draw("phihe8 >> h2(60,-180,180)","","");
  c1->Update();
  
  // c1->cd(3);
  // ch1->Draw("thetahe8.>>hangle(58,0,5)","","");
  // c1->Update();

  TH1F *hTheta = (TH1F*)c1->GetPrimitive("h2");
  // cout << hTheta->GetEntries() << endl;
  // return;

  ofstream thetaFile;
  thetaFile.open("targetPhi.txt");

  for(Int_t i= 1;i<hTheta->GetNbinsX()+1;i++) {
    thetaFile
    << hTheta->GetBinCenter(i) << "\t"
    << hTheta->GetBinContent(i) << "\t\t" 
    << endl;    
  }
  // thetaFile.close();
  
return;
  // c1->cd(4);
  // ch1->Draw("phihe8 >> hphi(1000,-180,180)","","col");
  // c1->Update();


  // TCanvas *c1 = new TCanvas("c1","",1800,1000);
  // c1->Divide(2,2);

  // c1->cd(1);
  // ch1->Draw("fXt >> h1(110,-30,30)","","");
  // c1->Update();

  // c1->cd(2);
  // ch1->Draw("fYt>> h2(110,-30,30)","","");
  // c1->Update();
  
  // c1->cd(3);
  // ch1->Draw("thetahe8. >> h3 (50,0,5)","","");
  // c1->Update();

  // c1->cd(4);
  // ch1->Draw("fYt-1:fXt-0.5 >> h4(62,-20,20,62,-20,20)","nCsI>-1 && nX_C>-1 && nY_C>-1","col");
  // c1->Update();


  // TCanvas *c1 = new TCanvas("c1","",1000,1000);

  // ch1->Draw("fYt:fXt >> h1(95,-30,30,95,-30,30)","nCsI>-1 && nX_C>-1 && nY_C>-1","col");
  // c1->Update();

  // ch1->SetMarkerColor(kRed);
  // ch1->SetMarkerStyle(7);
  // ch1->Draw("fYt+2:fXt >> h2(95,-30,30,95,-30,30)","nCsI>-1 && nX_C>-1 && nY_C>-1 && fYt*fYt+fXt*fXt<12*12","same");
  // c1->Update();


  // TLine *l1 = new TLine(-40, 2,40, 2);
  // l1->SetLineColor(kRed);
  // l1->Draw("same");

  // TLine *l2 = new TLine(0, -40,0, 40);
  // l2->SetLineColor(kRed);
  // l2->Draw("same");

  // Float_t x1,y1,r1;
  // x1 = 0.;
  // y1 = 0.;
  // r1 = 20.;
  // TEllipse *el = new TEllipse(x1,y1,r1);
  // el->SetLineColor(kRed);
  // el->Draw("same");
// thetahe8.
  return;
}