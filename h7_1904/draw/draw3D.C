void draw3D(){


  TH3F *target = new TH3F("target","target plane",20,-9.5,10.5,20,-9,11,1,-0.3,0.3);
  target->FillRandom("gaus");
  target->Draw("col");


  // TH3F *t1 = new TH3F("t1","t1 plane",20,-9,5,10.5,20,-9,11,1,-0.3,0.3);
  // t1->FillRandom();

}