#if !defined(__CLING__)

#include "TCutG.h"

#endif

TCutG *cutF5_b12;

void create_Cut_F5_b12() { 
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08

   cutF5_b12 = new TCutG("F5_b12",8);
   cutF5_b12->SetVarX("BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime ");
   cutF5_b12->SetVarY("BeamDetToFDigi2.fEdep/4.");
   cutF5_b12->SetTitle("Graph");
   cutF5_b12->SetFillColor(1);
   cutF5_b12->SetPoint(0,64.9487,2427.05);
   cutF5_b12->SetPoint(1,62.3555,2072.95);
   cutF5_b12->SetPoint(2,62.1934,1742.07);
   cutF5_b12->SetPoint(3,63.0578,1492.45);
   cutF5_b12->SetPoint(4,66.3533,1335.72);
   cutF5_b12->SetPoint(5,66.7315,2020.7);
   cutF5_b12->SetPoint(6,65.9751,2485.1);
   cutF5_b12->SetPoint(7,64.9487,2427.05);
   // cutg->Draw("");
}

void b12_beamCut(){
   cout << "12B beamCut run" << endl;
   create_Cut_F5_b12();
}

