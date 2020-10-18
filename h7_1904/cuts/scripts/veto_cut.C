TCutG *cutVeto1,*cutVeto3;

void createVetoCuts() {

   cutVeto1 = new TCutG("cutVeto1",8);
   cutVeto1->SetVarX("a1_1+a20_1_un");
   cutVeto1->SetVarY("a20_1");
   cutVeto1->SetTitle("Graph");
   cutVeto1->SetFillColor(1);
   cutVeto1->SetPoint(0,13.7041,0.551729);
   cutVeto1->SetPoint(1,13.6568,0.118292);
   cutVeto1->SetPoint(2,16.824,0.109262);
   cutVeto1->SetPoint(3,22.5439,0.190531);
   cutVeto1->SetPoint(4,26.042,0.244711);
   cutVeto1->SetPoint(5,25.0966,0.651058);
   cutVeto1->SetPoint(6,14.2241,0.614938);
   cutVeto1->SetPoint(7,13.7041,0.551729);

   cutVeto3 = new TCutG("cutVeto3",9);
   cutVeto3->SetVarX("a1_3+a20_3_un");
   cutVeto3->SetVarY("a20_3");
   cutVeto3->SetTitle("Graph");
   cutVeto3->SetFillColor(1);
   cutVeto3->SetPoint(0,15.5949,0.434339);
   cutVeto3->SetPoint(1,14.8386,0.30792);
   cutVeto3->SetPoint(2,15.1695,0.208591);
   cutVeto3->SetPoint(3,16.6349,0.163442);
   cutVeto3->SetPoint(4,29.1619,0.298891);
   cutVeto3->SetPoint(5,28.4056,0.560758);
   cutVeto3->SetPoint(6,17.5331,0.497549);
   cutVeto3->SetPoint(7,15.0277,0.42531);
   cutVeto3->SetPoint(8,15.5949,0.434339);

}

void veto_cut(){

   createVetoCuts();

}
