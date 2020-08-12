{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("CUTG",19);
   cutg->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutg->SetVarY("(Beam_detector_F5.fData.fValue[0] + Beam_detector_F5.fData.fValue[1] + Beam_detector_F5.fData.fValue[2] + Beam_detector_F5.fData.fValue[3])/4.");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,94.7265,1432.15);
   cutg->SetPoint(1,94.3416,1375.39);
   cutg->SetPoint(2,94.2403,1267.03);
   cutg->SetPoint(3,94.3011,1179.31);
   cutg->SetPoint(4,94.767,1114.81);
   cutg->SetPoint(5,95.6382,1086.43);
   cutg->SetPoint(6,97.421,1052.89);
   cutg->SetPoint(7,98.9607,1045.15);
   cutg->SetPoint(8,99.6495,1065.79);
   cutg->SetPoint(9,100.095,1119.97);
   cutg->SetPoint(10,100.399,1210.27);
   cutg->SetPoint(11,100.298,1393.45);
   cutg->SetPoint(12,100.055,1468.27);
   cutg->SetPoint(13,99.69,1506.97);
   cutg->SetPoint(14,98.3529,1535.35);
   cutg->SetPoint(15,97.1171,1545.67);
   cutg->SetPoint(16,95.9015,1530.19);
   cutg->SetPoint(17,95.1114,1488.91);
   cutg->SetPoint(18,94.7265,1432.15);
   cutg->Draw("");
}
