void getToF() {
 

	// Double_t l1 = 12320; // mm

	Double_t l1 = 4758; // mm
	// Double_t l1 = 320; // mm
	Double_t mass = 8.406868788;
	Double_t e1 = 0.265 - 0.007; // GeV
	// Double_t e1 = 0.265; // GeV

	Double_t a = 1 - ( 1/( 1 + (e1/mass) ) )*( 1/( 1 + (e1/mass) ) );
	Double_t tof1 = l1/299.792458*pow(a,-0.5);

	cout << tof1 << " " << 1000*e1 << endl;


	Double_t l2 = 12320 - l1; // mm
	Double_t e2 = 0.265; // GeV

	a = 1 - ( 1/( 1 + (e2/mass) ) )*( 1/( 1 + (e2/mass) ) );
	Double_t tof2 = l2/299.792458*pow(a,-0.5);

	cout << tof2 << " " << 1000*e2 << endl;

	cout << tof1 + tof2 << endl;

}