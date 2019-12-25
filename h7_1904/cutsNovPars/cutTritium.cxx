void cutTritium() {

   cal[0] = new TCutG("Tritium",23);
   cal[0]->SetVarX("fCsI");
   cal[0]->SetVarY("fCTX");
   cal[0]->SetTitle("Graph");
   cal[0]->SetFillStyle(1000);
   cal[0]->SetPoint(0,1.55176,21.6568);
   cal[0]->SetPoint(1,2.10314,19.7624);
   cal[0]->SetPoint(2,8.01084,16.5637);
   cal[0]->SetPoint(3,18.881,12.3712);
   cal[0]->SetPoint(4,29.5936,9.63829);
   cal[0]->SetPoint(5,40.8577,7.93024);
   cal[0]->SetPoint(6,50.6251,6.84329);
   cal[0]->SetPoint(7,59.9986,5.94268);
   cal[0]->SetPoint(8,70.79,5.19735);
   cal[0]->SetPoint(9,84.1808,4.54519);
   cal[0]->SetPoint(10,102.298,3.92407);
   cal[0]->SetPoint(11,101.825,5.53896);
   cal[0]->SetPoint(12,84.0233,6.03585);
   cal[0]->SetPoint(13,62.9919,7.34018);
   cal[0]->SetPoint(14,47.7106,8.73768);
   cal[0]->SetPoint(15,36.8404,10.2594);
   cal[0]->SetPoint(16,28.806,11.688);
   cal[0]->SetPoint(17,21.2441,13.6755);
   cal[0]->SetPoint(18,12.3432,17.2158);
   cal[0]->SetPoint(19,4.62376,21.0046);
   cal[0]->SetPoint(20,2.65453,21.8431);
   cal[0]->SetPoint(21,1.39422,21.7189);
   cal[0]->SetPoint(22,1.55176,21.6568); 
}
