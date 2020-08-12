{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("CUTG",19);
   cutg->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutg->SetVarY("(Beam_detector_F3.fData.fValue[0] + Beam_detector_F3.fData.fValue[1] + Beam_detector_F3.fData.fValue[2] + Beam_detector_F3.fData.fValue[3])/4.");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,93.7541,1411.51);
   cutg->SetPoint(1,93.4299,1251.55);
   cutg->SetPoint(2,93.5109,1122.55);
   cutg->SetPoint(3,93.8756,1042.57);
   cutg->SetPoint(4,94.4631,1003.87);
   cutg->SetPoint(5,95.9623,985.81);
   cutg->SetPoint(6,97.421,975.49);
   cutg->SetPoint(7,98.8189,983.23);
   cutg->SetPoint(8,99.2848,1042.57);
   cutg->SetPoint(9,99.6293,1117.39);
   cutg->SetPoint(10,99.69,1248.97);
   cutg->SetPoint(11,99.8116,1421.83);
   cutg->SetPoint(12,99.3861,1586.95);
   cutg->SetPoint(13,98.7176,1677.24);
   cutg->SetPoint(14,97.3602,1659.18);
   cutg->SetPoint(15,96.2459,1615.33);
   cutg->SetPoint(16,94.6049,1540.51);
   cutg->SetPoint(17,93.8148,1468.27);
   cutg->SetPoint(18,93.7541,1411.51);
   cutg->Draw("");
}
