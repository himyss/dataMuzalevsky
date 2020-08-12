{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("CUTG",19);
   cutg->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutg->SetVarY("(Beam_detector_F3.fData.fValue[0] + Beam_detector_F3.fData.fValue[1] + Beam_detector_F3.fData.fValue[2] + Beam_detector_F3.fData.fValue[3])/4.");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,95.0304,1457.95);
   cutg->SetPoint(1,94.5442,1372.81);
   cutg->SetPoint(2,94.2808,1246.39);
   cutg->SetPoint(3,94.4226,1145.77);
   cutg->SetPoint(4,95.0101,1083.85);
   cutg->SetPoint(5,96.0231,1032.25);
   cutg->SetPoint(6,97.4818,1001.29);
   cutg->SetPoint(7,99.1633,1009.03);
   cutg->SetPoint(8,99.6698,1042.57);
   cutg->SetPoint(9,100.075,1130.29);
   cutg->SetPoint(10,100.298,1243.81);
   cutg->SetPoint(11,100.257,1347.01);
   cutg->SetPoint(12,100.095,1468.27);
   cutg->SetPoint(13,99.8521,1525.03);
   cutg->SetPoint(14,99.2848,1561.15);
   cutg->SetPoint(15,98.1706,1563.73);
   cutg->SetPoint(16,96.7524,1553.41);
   cutg->SetPoint(17,95.5976,1509.55);
   cutg->SetPoint(18,95.0304,1457.95);
   cutg->Draw("");
}
