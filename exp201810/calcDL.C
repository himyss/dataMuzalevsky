#include "/media/user/work/software/AculUti/TELoss/TELoss.h"
void calcDL(){ 

  TELoss fAlphaSi;
  Info("AculCalibration::SetELosses", "Combination of aplha particle with silicon material only.");
  fAlphaSi.SetEL(1, 2.321); // density in g/cm3
  fAlphaSi.AddEL(14., 28.086, 1);  //Z, mass
//  mSi.SetZP(1., 1.);    //protons
  fAlphaSi.SetZP(2., 4.);   //alphas, Z, A
  fAlphaSi.SetEtab(100000, 200.); // ?, MeV calculate ranges
  fAlphaSi.SetDeltaEtab(300);

  cout << fAlphaSi.GetE(7.6869, 26.) << endl;
}