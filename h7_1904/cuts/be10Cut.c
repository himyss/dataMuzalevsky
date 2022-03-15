#if !defined(__CLING__)

#include "TCutG.h"

#endif

TCutG *cutF3,*cutF5;

void create_Cut_F3() { 
   cutF3 = new TCutG("F3_Beam",34);
   cutF3->SetVarX("0.0625*0.25*(tF5[0] + tF5[1] + tF5[2] + tF5[3] - tF3[0] - tF3[1] - tF3[2] - tF3[3])");
   cutF3->SetVarY("(F3[0] + F3[1] + F3[2] + F3[3])/4.");
   cutF3->SetTitle("F3_ToF_title");
   cutF3->SetFillColor(1);
   cutF3->SetPoint(0,66.7878,1629.24);
   cutF3->SetPoint(1,66.7244,1529.5);
   cutF3->SetPoint(2,66.6611,1449.23);
   cutF3->SetPoint(3,66.6611,1342.2);
   cutF3->SetPoint(4,66.64,1243.68);
   cutF3->SetPoint(5,66.7878,1167.05);
   cutF3->SetPoint(6,66.83,1134.21);
   cutF3->SetPoint(7,67.1254,1108.67);
   cutF3->SetPoint(8,67.9062,1092.86);
   cutF3->SetPoint(9,68.7504,1083.13);
   cutF3->SetPoint(10,69.7211,1080.7);
   cutF3->SetPoint(11,70.5231,1090.43);
   cutF3->SetPoint(12,70.924,1107.46);
   cutF3->SetPoint(13,71.0084,1128.13);
   cutF3->SetPoint(14,71.114,1188.95);
   cutF3->SetPoint(15,71.1351,1257.06);
   cutF3->SetPoint(16,71.2195,1376.25);
   cutF3->SetPoint(17,71.2195,1471.12);
   cutF3->SetPoint(18,71.1984,1579.37);
   cutF3->SetPoint(19,71.0929,1634.1);
   cutF3->SetPoint(20,71.114,1703.43);
   cutF3->SetPoint(21,70.8818,1732.62);
   cutF3->SetPoint(22,70.4598,1784.92);
   cutF3->SetPoint(23,70.4176,1805.6);
   cutF3->SetPoint(24,70.1432,1825.06);
   cutF3->SetPoint(25,69.6789,1821.41);
   cutF3->SetPoint(26,69.1936,1814.11);
   cutF3->SetPoint(27,68.4127,1794.65);
   cutF3->SetPoint(28,67.7374,1765.46);
   cutF3->SetPoint(29,67.2942,1733.84);
   cutF3->SetPoint(30,66.9988,1709.51);
   cutF3->SetPoint(31,66.8722,1673.02);
   cutF3->SetPoint(32,66.8089,1645.05);
   cutF3->SetPoint(33,66.7878,1629.24);
   // cutF3->Draw("");
}

void create_Cut_F5() { 
   cout << "create_Cut_F5 RUN " << endl;
   cutF5 = new TCutG("F5_Beam",27);
   cutF5->SetVarX("0.0625*0.25*(tF5[0] + tF5[1] + tF5[2] + tF5[3] - tF3[0] - tF3[1] - tF3[2] - tF3[3])");
   cutF5->SetVarY("(F5[0] + F5[1] + F5[2] + F5[3])/4");
   cutF5->SetTitle("F5_Beam_title");
   cutF5->SetFillColor(1);
   cutF5->SetPoint(0,66.7456,1679.77);
   cutF5->SetPoint(1,66.7033,1513.91);
   cutF5->SetPoint(2,66.6822,1344.9);
   cutF5->SetPoint(3,66.7456,1226.43);
   cutF5->SetPoint(4,67.0621,1166.41);
   cutF5->SetPoint(5,67.5686,1136.39);
   cutF5->SetPoint(6,68.4549,1122.18);
   cutF5->SetPoint(7,69.4257,1119.02);
   cutF5->SetPoint(8,70.2276,1130.08);
   cutF5->SetPoint(9,70.8607,1167.99);
   cutF5->SetPoint(10,71.114,1209.05);
   cutF5->SetPoint(11,71.2195,1276.98);
   cutF5->SetPoint(12,71.2195,1384.39);
   cutF5->SetPoint(13,71.2406,1502.86);
   cutF5->SetPoint(14,71.2195,1613.43);
   cutF5->SetPoint(15,71.1562,1724);
   cutF5->SetPoint(16,71.0507,1785.6);
   cutF5->SetPoint(17,71.0296,1829.83);
   cutF5->SetPoint(18,70.5442,1878.8);
   cutF5->SetPoint(19,69.7633,1913.55);
   cutF5->SetPoint(20,69.2569,1904.07);
   cutF5->SetPoint(21,68.6238,1872.48);
   cutF5->SetPoint(22,67.8851,1834.57);
   cutF5->SetPoint(23,67.2942,1793.5);
   cutF5->SetPoint(24,66.8511,1768.23);
   cutF5->SetPoint(25,66.7878,1706.62);
   cutF5->SetPoint(26,66.7456,1679.77);
   // cutF5->Draw("");
}

void be10Cut() {
   cout << "beamCut run" << endl;
   create_Cut_F3();
   create_Cut_F5();
}
