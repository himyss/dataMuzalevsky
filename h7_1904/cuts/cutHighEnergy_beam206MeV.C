{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("CUTG",13);
   cutg->SetVarX("v3He.Theta()*TMath::RadToDeg()");
   cutg->SetVarY("v3He.E()-2808.391000");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(6);
   cutg->SetLineWidth(3);
   cutg->SetPoint(0,0.0276187,17.3948);
   cutg->SetPoint(1,2.61114,17.4351);
   cutg->SetPoint(2,5.54497,17.8387);
   cutg->SetPoint(3,8.67585,18.4844);
   cutg->SetPoint(4,10.7996,19.1705);
   cutg->SetPoint(5,12.8139,19.8566);
   cutg->SetPoint(6,15.5506,21.3095);
   cutg->SetPoint(7,18.0466,23.4888);
   cutg->SetPoint(8,21.0461,27.2825);
   cutg->SetPoint(9,22.2503,30.39);
   cutg->SetPoint(10,23.1042,32.9326);
   cutg->SetPoint(11,0.640658,32.9729);
   cutg->SetPoint(12,0.0276187,17.3948);
   cutg->Draw("");
}
