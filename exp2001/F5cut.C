{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutg = new TCutG("CUTG",15);
   cutg->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutg->SetVarY("(Beam_detector_F5.fData.fValue[0] + Beam_detector_F5.fData.fValue[1] + Beam_detector_F5.fData.fValue[2] + Beam_detector_F5.fData.fValue[3])/4.");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,94.5989,1610.29);
   cutg->SetPoint(1,93.4238,1470.98);
   cutg->SetPoint(2,93.3428,1207.82);
   cutg->SetPoint(3,93.6669,1083.98);
   cutg->SetPoint(4,94.2747,1033.67);
   cutg->SetPoint(5,95.4092,1002.71);
   cutg->SetPoint(6,98.9344,994.969);
   cutg->SetPoint(7,99.5421,1029.8);
   cutg->SetPoint(8,99.9068,1176.86);
   cutg->SetPoint(9,99.7853,1490.33);
   cutg->SetPoint(10,99.0964,1614.16);
   cutg->SetPoint(11,98.0429,1664.47);
   cutg->SetPoint(12,96.1386,1668.34);
   cutg->SetPoint(13,95.0446,1645.12);
   cutg->SetPoint(14,94.5989,1610.29);
   cutg->Draw("");
}
