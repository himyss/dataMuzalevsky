void setTables();
void zeroVars();
void checkToF();
void cutMWPC();

void MWPCprojection();
Float_t GetPosition(Float_t wire, Float_t wireStep,Float_t planeOffset);

void CsIselect();
void CsIselect_arr();
void DSD_Cselect();
void SSD20_Lselect();
void X_Lselect();
void Y_Lselect();

void fillSi();
void fillCsI();

void readThickness();
void readCsImap();

void triton();
void triton_arr();
void checkHe3();

void CsIcut();
void tempTEloss() {

  TELoss* f3HSi = new TELoss();
  f3HSi->SetEL(1, 2.321); // density in g/cm3
  f3HSi->AddEL(14., 28.086, 1);  //Z, mass
  f3HSi->SetZP(1., 3.);   //alphas, Z, A
  f3HSi->SetEtab(100000, 200.); // ?, MeV calculate ranges
  f3HSi->SetDeltaEtab(1500);


  Float_t a =  f3HSi->GetE0dE(4.0283, 1500.);
  cout << a << endl;
    
  return;
}
