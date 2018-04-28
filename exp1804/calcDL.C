void calcDL(){

	gSystem->Load("/home/muzalevsky/AculUti/libAculData.so");
	gSystem->Load("/home/muzalevsky/AculUti/libTELoss.so");

  TELoss AlphaSi;
	AlphaSi.SetEL(1, 2.321); // density in g/cm3
	AlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//	mSi.SetZP(1., 1.);		//protons
	AlphaSi.SetZP(2., 4.);		//alphas, Z, A
	AlphaSi.SetEtab(100000, 200.);	// ?, MeV calculate ranges
	AlphaSi.SetDeltaEtab(300);

  Double_t dl[4];

 /* cout << AlphaSi.GetR(4.7843, 4.7843 - 0.1155137813) << endl;
  cout << AlphaSi.GetR(5.48948, 5.48948 - 0.106348875) << endl;
  cout << AlphaSi.GetR(6.0024, 6.0024 - 0.099938125) << endl;
  cout << AlphaSi.GetR(7.6869, 7.6869 - 0.08698671875) << endl;*/



  dl[0] = AlphaSi.GetR(4.7795, 4.7795 - 0.1155137813);
  dl[1] = AlphaSi.GetR(5.49196875, 5.49196875 - 0.106348875);
  dl[2] = AlphaSi.GetR(6.0075625, 6.0075625 - 0.099938125);
  dl[3] = AlphaSi.GetR(7.6841875, 7.6841875 - 0.08698671875);

  Double_t d = (dl[0]+dl[1]+dl[2]+dl[3])/4.;
  
  Double_t dead;
  dead = d/( (1/cos(TMath::DegToRad()*44)) - 1);
  cout << "dead layer = " << dead << endl;
}
