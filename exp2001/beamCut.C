#if !defined(__CLING__)

#include "TCutG.h"

#endif

TCutG *cutF3,*cutF5;

TCutG *cutF3_cal,*cutF5_cal;

void create_Cut_F3() { 
   cutF3 = new TCutG("F3_Beam",19);
   cutF3->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutF3->SetVarY("(Beam_detector_F3.fData.fValue[0] + Beam_detector_F3.fData.fValue[1] + Beam_detector_F3.fData.fValue[2] + Beam_detector_F3.fData.fValue[3])/4.");
   cutF3->SetTitle("Graph");
   cutF3->SetFillColor(1);
   cutF3->SetPoint(0,93.7541,1411.51);
   cutF3->SetPoint(1,93.4299,1251.55);
   cutF3->SetPoint(2,93.5109,1122.55);
   cutF3->SetPoint(3,93.8756,1042.57);
   cutF3->SetPoint(4,94.4631,1003.87);
   cutF3->SetPoint(5,95.9623,985.81);
   cutF3->SetPoint(6,97.421,975.49);
   cutF3->SetPoint(7,98.8189,983.23);
   cutF3->SetPoint(8,99.2848,1042.57);
   cutF3->SetPoint(9,99.6293,1117.39);
   cutF3->SetPoint(10,99.69,1248.97);
   cutF3->SetPoint(11,99.8116,1421.83);
   cutF3->SetPoint(12,99.3861,1586.95);
   cutF3->SetPoint(13,98.7176,1677.24);
   cutF3->SetPoint(14,97.3602,1659.18);
   cutF3->SetPoint(15,96.2459,1615.33);
   cutF3->SetPoint(16,94.6049,1540.51);
   cutF3->SetPoint(17,93.8148,1468.27);
   cutF3->SetPoint(18,93.7541,1411.51);

   cutF3->SetLineColor(kRed);
   // cutF3->Draw("");
}

void create_Cut_F5() { 
   cout << "create_Cut_F5 RUN " << endl;
   cutF5 = new TCutG("F5_Beam",15);
   cutF5->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutF5->SetVarY("(Beam_detector_F5.fData.fValue[0] + Beam_detector_F5.fData.fValue[1] + Beam_detector_F5.fData.fValue[2] + Beam_detector_F5.fData.fValue[3])/4.");
   cutF5->SetTitle("F5_Beam_title");
   cutF5->SetFillColor(1);
   cutF5->SetPoint(0,94.5989,1610.29);
   cutF5->SetPoint(1,93.4238,1470.98);
   cutF5->SetPoint(2,93.3428,1207.82);
   cutF5->SetPoint(3,93.6669,1083.98);
   cutF5->SetPoint(4,94.2747,1033.67);
   cutF5->SetPoint(5,95.4092,1002.71);
   cutF5->SetPoint(6,98.9344,994.969);
   cutF5->SetPoint(7,99.5421,1029.8);
   cutF5->SetPoint(8,99.9068,1176.86);
   cutF5->SetPoint(9,99.7853,1490.33);
   cutF5->SetPoint(10,99.0964,1614.16);
   cutF5->SetPoint(11,98.0429,1664.47);
   cutF5->SetPoint(12,96.1386,1668.34);
   cutF5->SetPoint(13,95.0446,1645.12);
   cutF5->SetPoint(14,94.5989,1610.29);

   cutF5->SetLineColor(kRed);
   // cutF5->Draw("");
}

void create_cal_Cut_F3() { 
   cutF3_cal = new TCutG("F3_cal_Beam",19);
   cutF3_cal->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutF3_cal->SetVarY("(Beam_detector_F3.fData.fValue[0] + Beam_detector_F3.fData.fValue[1] + Beam_detector_F3.fData.fValue[2] + Beam_detector_F3.fData.fValue[3])/4.");
   cutF3_cal->SetTitle("Graph");
   cutF3_cal->SetFillColor(1);
   cutF3_cal->SetPoint(0,95.0304,1457.95);
   cutF3_cal->SetPoint(1,94.5442,1372.81);
   cutF3_cal->SetPoint(2,94.2808,1246.39);
   cutF3_cal->SetPoint(3,94.4226,1145.77);
   cutF3_cal->SetPoint(4,95.0101,1083.85);
   cutF3_cal->SetPoint(5,96.0231,1032.25);
   cutF3_cal->SetPoint(6,97.4818,1001.29);
   cutF3_cal->SetPoint(7,99.1633,1009.03);
   cutF3_cal->SetPoint(8,99.6698,1042.57);
   cutF3_cal->SetPoint(9,100.075,1130.29);
   cutF3_cal->SetPoint(10,100.298,1243.81);
   cutF3_cal->SetPoint(11,100.257,1347.01);
   cutF3_cal->SetPoint(12,100.095,1468.27);
   cutF3_cal->SetPoint(13,99.8521,1525.03);
   cutF3_cal->SetPoint(14,99.2848,1561.15);
   cutF3_cal->SetPoint(15,98.1706,1563.73);
   cutF3_cal->SetPoint(16,96.7524,1553.41);
   cutF3_cal->SetPoint(17,95.5976,1509.55);
   cutF3_cal->SetPoint(18,95.0304,1457.95);

   cutF3_cal->SetLineColor(kRed);
   // cutF3->Draw("");
}

void create_cal_Cut_F5() { 
   cout << "create_Cut_F5 RUN " << endl;
   cutF5_cal = new TCutG("F5_cal_Beam",15);
   cutF5_cal->SetVarX("0.0625*0.25*(Beam_detector_tF5.fData.fValue[0] + Beam_detector_tF5.fData.fValue[1] + Beam_detector_tF5.fData.fValue[2] + Beam_detector_tF5.fData.fValue[3] - Beam_detector_tF3.fData.fValue[0] - Beam_detector_tF3.fData.fValue[1] - Beam_detector_tF3.fData.fValue[2] - Beam_detector_tF3.fData.fValue[3])");
   cutF5_cal->SetVarY("(Beam_detector_F5.fData.fValue[0] + Beam_detector_F5.fData.fValue[1] + Beam_detector_F5.fData.fValue[2] + Beam_detector_F5.fData.fValue[3])/4.");
   cutF5_cal->SetTitle("F5_Beam_title");
   cutF5_cal->SetFillColor(1);
   cutF5_cal->SetPoint(0,94.7265,1432.15);
   cutF5_cal->SetPoint(1,94.3416,1375.39);
   cutF5_cal->SetPoint(2,94.2403,1267.03);
   cutF5_cal->SetPoint(3,94.3011,1179.31);
   cutF5_cal->SetPoint(4,94.767,1114.81);
   cutF5_cal->SetPoint(5,95.6382,1086.43);
   cutF5_cal->SetPoint(6,97.421,1052.89);
   cutF5_cal->SetPoint(7,98.9607,1045.15);
   cutF5_cal->SetPoint(8,99.6495,1065.79);
   cutF5_cal->SetPoint(9,100.095,1119.97);
   cutF5_cal->SetPoint(10,100.399,1210.27);
   cutF5_cal->SetPoint(11,100.298,1393.45);
   cutF5_cal->SetPoint(12,100.055,1468.27);
   cutF5_cal->SetPoint(13,99.69,1506.97);
   cutF5_cal->SetPoint(14,98.3529,1535.35);
   cutF5_cal->SetPoint(15,97.1171,1545.67);
   cutF5_cal->SetPoint(16,95.9015,1530.19);
   cutF5_cal->SetPoint(17,95.1114,1488.91);
   cutF5_cal->SetPoint(18,94.7265,1432.15);

   cutF5_cal->SetLineColor(kRed);
   // cutF5->Draw("");
}

void beamCut() {
   cout << "beamCut run" << endl;
   create_Cut_F3();
   create_Cut_F5();

   create_cal_Cut_F3();
   create_cal_Cut_F5();

}
