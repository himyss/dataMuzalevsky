void fillCut1() {
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   cutg1 = new TCutG("cutg1_mm",13);
   cutg1->SetVarX("1000*(mh7_in-8.406868788) ");
   cutg1->SetVarY("e_1_in");
   cutg1->SetTitle("Graph");
   cutg1->SetFillColor(1);
   cutg1->SetPoint(0,-1.05011,11.1196);
   cutg1->SetPoint(1,-1.50932,10.0515);
   cutg1->SetPoint(2,-1.61737,9.05302);
   cutg1->SetPoint(3,-1.48231,8.01974);
   cutg1->SetPoint(4,-1.02985,7.82237);
   cutg1->SetPoint(5,-0.145192,7.93847);
   cutg1->SetPoint(6,1.48906,8.77438);
   cutg1->SetPoint(7,1.69841,9.83088);
   cutg1->SetPoint(8,1.6849,11.0848);
   cutg1->SetPoint(9,1.61062,11.793);
   cutg1->SetPoint(10,1.28647,12.0252);
   cutg1->SetPoint(11,-0.192464,11.5259);
   cutg1->SetPoint(12,-1.05011,11.1196);

   cutg2 = new TCutG("cutg2_mm",14);
   cutg2->SetVarX("1000*(mh7_in-8.406868788) ");
   cutg2->SetVarY("e_2_in");
   cutg2->SetTitle("Graph");
   cutg2->SetFillColor(1);
   cutg2->SetPoint(0,-1.52958,10.0631);
   cutg2->SetPoint(1,-1.74568,9.44776);
   cutg2->SetPoint(2,-1.70516,8.75116);
   cutg2->SetPoint(3,-1.50932,8.21711);
   cutg2->SetPoint(4,-1.27296,7.89203);
   cutg2->SetPoint(5,-0.104673,7.84559);
   cutg2->SetPoint(6,1.71191,9.33166);
   cutg2->SetPoint(7,1.98879,9.88893);
   cutg2->SetPoint(8,1.98204,10.6436);
   cutg2->SetPoint(9,1.74568,11.2241);
   cutg2->SetPoint(10,1.27296,11.7233);
   cutg2->SetPoint(11,0.719206,11.7233);
   cutg2->SetPoint(12,-0.151945,11.1428);
   cutg2->SetPoint(13,-1.52958,10.0631);

   cutg3 = new TCutG("cutg3_mm",14);
   cutg3->SetVarX("1000*(mh7_in-8.406868788) ");
   cutg3->SetVarY("e_3_in");
   cutg3->SetTitle("Graph");
   cutg3->SetFillColor(1);
   cutg3->SetPoint(0,0.935305,11.7117);
   cutg3->SetPoint(1,1.42153,10.7481);
   cutg3->SetPoint(2,1.45529,9.95859);
   cutg3->SetPoint(3,1.27971,8.90209);
   cutg3->SetPoint(4,0.570638,8.14745);
   cutg3->SetPoint(5,-0.516613,7.59017);
   cutg3->SetPoint(6,-1.61737,8.05457);
   cutg3->SetPoint(7,-1.69165,8.65828);
   cutg3->SetPoint(8,-1.63088,9.36649);
   cutg3->SetPoint(9,-1.41478,10.0631);
   cutg3->SetPoint(10,-1.09738,10.8758);
   cutg3->SetPoint(11,-0.631415,11.5608);
   cutg3->SetPoint(12,0.354538,11.8858);
   cutg3->SetPoint(13,0.935305,11.7117);


   cutg4 = new TCutG("cutg4_mm",12);
   cutg4->SetVarX("1000*(mh7_in-8.406868788) ");
   cutg4->SetVarY("e_4_in");
   cutg4->SetTitle("Graph");
   cutg4->SetFillColor(1);
   cutg4->SetPoint(0,-0.522076,11.4098);
   cutg4->SetPoint(1,-1.29773,9.57546);
   cutg4->SetPoint(2,-1.14111,8.12423);
   cutg4->SetPoint(3,-0.745823,7.61339);
   cutg4->SetPoint(4,0.880072,8.07779);
   cutg4->SetPoint(5,1.72285,8.76277);
   cutg4->SetPoint(6,1.97643,9.44776);
   cutg4->SetPoint(7,1.92422,10.957);
   cutg4->SetPoint(8,1.6259,11.3518);
   cutg4->SetPoint(9,0.5892,11.7813);
   cutg4->SetPoint(10,-0.0372912,11.642);
   cutg4->SetPoint(11,-0.522076,11.4098);

}


void mmCuts() {
   fillCut1();

   cutg1->SetLineColor(kRed);
   cutg2->SetLineColor(kRed);
   cutg3->SetLineColor(kRed);
   cutg4->SetLineColor(kRed);

   cutg1->SetLineWidth(2);
   cutg2->SetLineWidth(2);
   cutg3->SetLineWidth(2);
   cutg4->SetLineWidth(2);

}


