{
  
  Float_t angle1,angle2;
  // cout << sin(30*TMath::DegToRad()) << endl;
  Float_t x = 25.;


  angle1 = (8.5*sin(17.*TMath::DegToRad()) - 180.)/(sqrt( (x+8.5*cos(17.*TMath::DegToRad()))*(x+8.5*cos(17.*TMath::DegToRad())) + (180-8.5*sin(17.*TMath::DegToRad()))*(180-8.5*sin(17.*TMath::DegToRad())) ));

  angle2 = -(8.5*sin(17.*TMath::DegToRad()) + 180.)/(sqrt( (x-8.5*cos(17.*TMath::DegToRad()))*(x-8.5*cos(17.*TMath::DegToRad())) + (180+8.5*sin(17.*TMath::DegToRad()))*(180+8.5*sin(17.*TMath::DegToRad())) ));


  cout << angle1*TMath::RadToDeg()  << " " << angle2*TMath::RadToDeg() << endl;




}

