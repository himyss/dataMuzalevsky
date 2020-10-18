{
//========= Macro generated from object: cut3h_15/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("cut3h_15",24);
   cutg->SetVarX("aCsI");
   cutg->SetVarY("X_C.");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   cutg->SetLineColor(ci);
   cutg->SetPoint(0,7.11448,16.5836);
   cutg->SetPoint(1,-0.526864,20.7554);
   cutg->SetPoint(2,2.36899,21.2508);
   cutg->SetPoint(3,6.2869,20.1362);
   cutg->SetPoint(4,13.9524,16.5139);
   cutg->SetPoint(5,26.3875,12.613);
   cutg->SetPoint(6,34.9047,10.7864);
   cutg->SetPoint(7,48.8729,8.68111);
   cutg->SetPoint(8,69.1439,6.88545);
   cutg->SetPoint(9,84.3045,5.89474);
   cutg->SetPoint(10,118.203,4.50155);
   cutg->SetPoint(11,142.222,3.91331);
   cutg->SetPoint(12,142.222,3.29412);
   cutg->SetPoint(13,139.496,3.01548);
   cutg->SetPoint(14,125.017,3.32508);
   cutg->SetPoint(15,106.109,3.78947);
   cutg->SetPoint(16,87.2004,4.37771);
   cutg->SetPoint(17,62.0009,5.84187);
   cutg->SetPoint(18,46.5641,7.19729);
   cutg->SetPoint(19,36.7785,8.4644);
   cutg->SetPoint(20,27.2681,10.1792);
   cutg->SetPoint(21,20.2358,12.009);
   cutg->SetPoint(22,13.375,14.2116);
   cutg->SetPoint(23,7.11448,16.5836);
   cutg->Draw("");
}
