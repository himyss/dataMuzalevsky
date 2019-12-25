{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.10/08
   
   TCutG *cutF5 = new TCutG("F5_Beam",17);
   cutF5->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutF5->SetVarY("Beam_detector_F5.fData.fValue[0] + Beam_detector_F5.fData.fValue[1] + Beam_detector_F5.fData.fValue[2] + Beam_detector_F5.fData.fValue[3]");
   cutF5->SetTitle("F5_Beam_title");
   cutF5->SetFillColor(1);
   cutF5->SetPoint(0,103.348,819.092);
   cutF5->SetPoint(1,103.524,923.323);
   cutF5->SetPoint(2,106.063,971.827);
   cutF5->SetPoint(3,109.602,998.658);
   cutF5->SetPoint(4,112.64,1007.95);
   cutF5->SetPoint(5,115.423,990.402);
   cutF5->SetPoint(6,116.125,875.851);
   cutF5->SetPoint(7,116.112,681.837);
   cutF5->SetPoint(8,115.747,634.365);
   cutF5->SetPoint(9,112.073,601.342);
   cutF5->SetPoint(10,108.953,596.182);
   cutF5->SetPoint(11,106.198,585.862);
   cutF5->SetPoint(12,104.348,583.798);
   cutF5->SetPoint(13,103.416,595.15);
   cutF5->SetPoint(14,103.186,669.453);
   cutF5->SetPoint(15,103.132,739.628);
   cutF5->SetPoint(16,103.348,819.092);
   // cutF5->Draw("");
}
