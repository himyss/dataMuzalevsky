{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("CUTG",11);
   cutg->SetVarX("v3He.Theta()*TMath::RadToDeg()");
   cutg->SetVarY("v3He.E()-2808.391000");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(3);
   cutg->SetPoint(0,0.14778,19.0489);
   cutg->SetPoint(1,3.21615,19.2328);
   cutg->SetPoint(2,7.62989,20.1826);
   cutg->SetPoint(3,11.3828,21.5307);
   cutg->SetPoint(4,14.2387,23.4609);
   cutg->SetPoint(5,16.5046,25.912);
   cutg->SetPoint(6,18.204,28.7307);
   cutg->SetPoint(7,18.3928,29.3128);
   cutg->SetPoint(8,0.737852,29.1903);
   cutg->SetPoint(9,0.690646,24.6252);
   cutg->SetPoint(10,0.14778,19.0489);
   cutg->Draw("");
}
