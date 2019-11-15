#if !defined(__CLING__)

#include "TCutG.h"

#endif

TCutG *cutF5_li;

void create_Cut_F5_li() { 
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08

   cutF5_li = new TCutG("F5_li9",10);
   cutF5_li->SetVarX("BeamDetToFDigi2.fTime-BeamDetToFDigi1.fTime ");
   cutF5_li->SetVarY("BeamDetToFDigi2.fEdep/4.");
   cutF5_li->SetTitle("Graph");
   cutF5_li->SetFillColor(1);
   cutF5_li->SetPoint(0,92.6634,1486.65);
   cutF5_li->SetPoint(1,95.5808,1579.53);
   cutF5_li->SetPoint(2,97.0394,1550.5);
   cutF5_li->SetPoint(3,97.5797,1080.3);
   cutF5_li->SetPoint(4,97.2015,952.593);
   cutF5_li->SetPoint(5,95.4727,917.763);
   cutF5_li->SetPoint(6,92.7175,946.788);
   cutF5_li->SetPoint(7,92.2312,1184.79);
   cutF5_li->SetPoint(8,92.5014,1451.82);
   cutF5_li->SetPoint(9,92.6634,1486.65);
   // cutg->Draw("");
}

void li9_beamCut(){
   cout << "9Li beamCut run" << endl;
   create_Cut_F5_li();
}

