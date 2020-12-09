TCutG *cut9Li;
TCutG *cut10Be;
TCutG *cut11Be;
TCutG *cut12B;
TCutG *cut13B;


void create_9li_Cut(){
   
   cut9Li = new TCutG("cut9Li",9);
   cut9Li->SetVarX("tF5-tF3 ");
   cut9Li->SetVarY("F5+F3");
   cut9Li->SetTitle("Graph");
   cut9Li->SetFillColor(1);
   cut9Li->SetPoint(0,92.0151,10104.5);
   cut9Li->SetPoint(1,92.2312,8208.2);
   cut9Li->SetPoint(2,93.4738,7859.91);
   cut9Li->SetPoint(3,96.8233,8130.8);
   cut9Li->SetPoint(4,97.1475,8982.2);
   cut9Li->SetPoint(5,96.7693,10568.9);
   cut9Li->SetPoint(6,94.3922,10723.7);
   cut9Li->SetPoint(7,92.4473,10375.4);
   cut9Li->SetPoint(8,92.0151,10104.5);

   cut9Li->SetLineColor(kRed);
}

void create_10be_cut(){
   cut10Be = new TCutG("cut10Be",10);
   cut10Be->SetVarX("tF5-tF3 ");
   cut10Be->SetVarY("F5+F3");
   cut10Be->SetTitle("Graph");
   cut10Be->SetFillColor(1);
   cut10Be->SetPoint(0,66.4614,13239.2);
   cut10Be->SetPoint(1,66.2993,9949.69);
   cut10Be->SetPoint(2,66.9476,9717.49);
   cut10Be->SetPoint(3,68.3522,9872.29);
   cut10Be->SetPoint(4,69.1626,10143.2);
   cut10Be->SetPoint(5,69.8649,11033.3);
   cut10Be->SetPoint(6,69.8109,12581.3);
   cut10Be->SetPoint(7,68.9465,13161.8);
   cut10Be->SetPoint(8,67.0556,13200.5);
   cut10Be->SetPoint(9,66.4614,13239.2);

   cut10Be->SetLineColor(kRed);
}

void create_11be_cut(){
   cut11Be = new TCutG("cut11Be",10);
   cut11Be->SetVarX("tF5-tF3 ");
   cut11Be->SetVarY("F5+F3");
   cut11Be->SetTitle("Graph");
   cut11Be->SetFillColor(1);
   cut11Be->SetPoint(0,80.3458,13703.6);
   cut11Be->SetPoint(1,79.8595,12503.9);
   cut11Be->SetPoint(2,79.7515,11110.7);
   cut11Be->SetPoint(3,80.5619,10723.7);
   cut11Be->SetPoint(4,82.5608,10723.7);
   cut11Be->SetPoint(5,83.8574,11149.4);
   cut11Be->SetPoint(6,84.1815,12968.3);
   cut11Be->SetPoint(7,83.6413,13781);
   cut11Be->SetPoint(8,81.5343,13935.8);
   cut11Be->SetPoint(9,80.3458,13703.6);

   cut11Be->SetLineColor(kRed);
}

void create_12b_cut(){
   cut12B = new TCutG("cut12B",10);
   cut12B->SetVarX("tF5-tF3 ");
   cut12B->SetVarY("F5+F3");
   cut12B->SetTitle("Graph");
   cut12B->SetFillColor(1);
   cut12B->SetPoint(0,63.0578,16180.3);
   cut12B->SetPoint(1,62.4635,15754.6);
   cut12B->SetPoint(2,62.3555,13974.5);
   cut12B->SetPoint(3,63.1659,12890.9);
   cut12B->SetPoint(4,64.9487,12387.8);
   cut12B->SetPoint(5,65.705,12852.2);
   cut12B->SetPoint(6,65.651,16296.4);
   cut12B->SetPoint(7,65.0567,16915.6);
   cut12B->SetPoint(8,63.9762,16606);
   cut12B->SetPoint(9,63.0578,16180.3);

   cut12B->SetLineColor(kRed);
}

void create_13b_cut(){
   cut13B = new TCutG("cut13B",12);
   cut13B->SetVarX("tF5-tF3");
   cut13B->SetVarY("F5+F3");
   cut13B->SetTitle("Graph");
   cut13B->SetFillColor(1);
   cut13B->SetPoint(0,72.7333,16915.6);
   cut13B->SetPoint(1,72.8572,13935.8);
   cut13B->SetPoint(2,73.4765,13664.9);
   cut13B->SetPoint(3,75.0867,14206.7);
   cut13B->SetPoint(4,75.8299,15251.5);
   cut13B->SetPoint(5,75.768,16412.5);
   cut13B->SetPoint(6,75.4583,17147.8);
   cut13B->SetPoint(7,74.7151,17380);
   cut13B->SetPoint(8,73.6004,17573.5);
   cut13B->SetPoint(9,72.9811,17496.1);
   cut13B->SetPoint(10,72.7953,17380);
   cut13B->SetPoint(11,72.7333,16915.6);

   cut13B->SetLineColor(kRed);

}



void create_dE_ToF(){

   create_9li_Cut();
   create_10be_cut();
   create_11be_cut();
   create_12b_cut();
   create_13b_cut();

}
