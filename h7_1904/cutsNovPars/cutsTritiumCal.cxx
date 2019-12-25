#if !defined(__CLING__)
#include "TCutG.h"
#endif

TCutG *cTritium[16];

void cutTritium0() {

   cTritium[0] = new TCutG("cT_0",18);
   cTritium[0]->SetVarX(" CsI==0");
   cTritium[0]->SetVarY("dE-E");
   cTritium[0]->SetTitle("Graph");
   cTritium[0]->SetFillStyle(1000);
   cTritium[0]->SetPoint(0,2.97275,21.5735);
   cTritium[0]->SetPoint(1,2.97275,19.2949);
   cTritium[0]->SetPoint(2,10.6701,15.1397);
   cTritium[0]->SetPoint(3,24.4721,10.6494);
   cTritium[0]->SetPoint(4,40.9284,7.63351);
   cTritium[0]->SetPoint(5,57.6502,5.891);
   cTritium[0]->SetPoint(6,85.5198,4.1485);
   cTritium[0]->SetPoint(7,112.858,3.27725);
   cTritium[0]->SetPoint(8,112.858,4.81869);
   cTritium[0]->SetPoint(9,84.9889,5.82398);
   cTritium[0]->SetPoint(10,63.2241,7.16437);
   cTritium[0]->SetPoint(11,46.2369,8.97389);
   cTritium[0]->SetPoint(12,32.4349,11.5206);
   cTritium[0]->SetPoint(13,22.6142,14.3354);
   cTritium[0]->SetPoint(14,12.528,18.7587);
   cTritium[0]->SetPoint(15,4.5653,21.8416);
   cTritium[0]->SetPoint(16,2.70733,21.5735);
   cTritium[0]->SetPoint(17,2.97275,21.5735);

}

void cutTritium1() {

   cTritium[1] = new TCutG("cT_1",17);
   cTritium[1]->SetVarX(" CsI==1");
   cTritium[1]->SetVarY("dE-E");
   cTritium[1]->SetTitle("Graph");
   cTritium[1]->SetFillStyle(1000);
   cTritium[1]->SetPoint(0,4.17102,20.957);
   cTritium[1]->SetPoint(1,4.44543,18.2578);
   cTritium[1]->SetPoint(2,12.4033,14.1342);
   cTritium[1]->SetPoint(3,24.2029,10.3854);
   cTritium[1]->SetPoint(4,37.9233,7.53626);
   cTritium[1]->SetPoint(5,51.9182,6.03674);
   cTritium[1]->SetPoint(6,70.0292,4.68717);
   cTritium[1]->SetPoint(7,114.758,3.18765);
   cTritium[1]->SetPoint(8,114.758,4.98708);
   cTritium[1]->SetPoint(9,79.9079,5.73684);
   cTritium[1]->SetPoint(10,55.4855,7.68622);
   cTritium[1]->SetPoint(11,42.5883,9.11076);
   cTritium[1]->SetPoint(12,32.4351,11.0601);
   cTritium[1]->SetPoint(13,23.3796,13.6843);
   cTritium[1]->SetPoint(14,14.0497,17.3581);
   cTritium[1]->SetPoint(15,4.44543,21.1069);
   cTritium[1]->SetPoint(16,4.17102,20.957);
}

void cutTritium2() {

   cTritium[2] = new TCutG("cT_2",16);
   cTritium[2]->SetVarX(" CsI==2");
   cTritium[2]->SetVarY("dE-E");
   cTritium[2]->SetTitle("Graph");
   cTritium[2]->SetFillStyle(1000);
   cTritium[2]->SetPoint(0,5.95104,19.8476);
   cTritium[2]->SetPoint(1,5.95104,16.7525);
   cTritium[2]->SetPoint(2,21.8598,11.2417);
   cTritium[2]->SetPoint(3,35.7062,8.22207);
   cTritium[2]->SetPoint(4,51.615,6.4103);
   cTritium[2]->SetPoint(5,67.5237,5.05148);
   cTritium[2]->SetPoint(6,103.466,3.16422);
   cTritium[2]->SetPoint(7,103.171,5.05148);
   cTritium[2]->SetPoint(8,75.7727,6.4103);
   cTritium[2]->SetPoint(9,54.561,8.07109);
   cTritium[2]->SetPoint(10,42.1876,9.5054);
   cTritium[2]->SetPoint(11,32.171,11.6191);
   cTritium[2]->SetPoint(12,23.3328,13.7329);
   cTritium[2]->SetPoint(13,15.3784,16.7525);
   cTritium[2]->SetPoint(14,5.95104,19.9985);
   cTritium[2]->SetPoint(15,5.95104,19.8476);

}

void cutTritium3() {

   cTritium[3] = new TCutG("cT_3",18);
   cTritium[3]->SetVarX(" CsI==3");
   cTritium[3]->SetVarY("dE-E");
   cTritium[3]->SetTitle("Graph");
   cTritium[3]->SetFillStyle(1000);
   cTritium[3]->SetPoint(0,0.373045,22.6114);
   cTritium[3]->SetPoint(1,0.99479,19.6266);
   cTritium[3]->SetPoint(2,10.321,15.4479);
   cTritium[3]->SetPoint(3,23.0667,11.0702);
   cTritium[3]->SetPoint(4,38.6103,8.21811);
   cTritium[3]->SetPoint(5,57.5735,6.09559);
   cTritium[3]->SetPoint(6,83.9977,4.43738);
   cTritium[3]->SetPoint(7,139.955,2.84549);
   cTritium[3]->SetPoint(8,139.644,4.50371);
   cTritium[3]->SetPoint(9,97.9869,5.49864);
   cTritium[3]->SetPoint(10,65.3453,7.35584);
   cTritium[3]->SetPoint(11,47.0039,9.21304);
   cTritium[3]->SetPoint(12,34.8799,11.0702);
   cTritium[3]->SetPoint(13,25.5537,13.4581);
   cTritium[3]->SetPoint(14,16.2275,16.1775);
   cTritium[3]->SetPoint(15,7.83398,20.3562);
   cTritium[3]->SetPoint(16,0.683917,22.6777);
   cTritium[3]->SetPoint(17,0.373045,22.6114);

}

void cutTritium4() {

   cTritium[4] = new TCutG("cT_4",18);
   cTritium[4]->SetVarX(" CsI==4");
   cTritium[4]->SetVarY("dE-E");
   cTritium[4]->SetTitle("Graph");
   cTritium[4]->SetFillStyle(1000);
   cTritium[4]->SetPoint(0,1.79245,22.0161);
   cTritium[4]->SetPoint(1,2.37066,19.2633);
   cTritium[4]->SetPoint(2,14.8022,13.3547);
   cTritium[4]->SetPoint(3,29.5465,9.32613);
   cTritium[4]->SetPoint(4,48.0492,6.90899);
   cTritium[4]->SetPoint(5,70.0211,4.89471);
   cTritium[4]->SetPoint(6,103.557,3.35042);
   cTritium[4]->SetPoint(7,123.795,3.21614);
   cTritium[4]->SetPoint(8,122.349,5.16328);
   cTritium[4]->SetPoint(9,91.4149,5.63328);
   cTritium[4]->SetPoint(10,70.0211,6.64042);
   cTritium[4]->SetPoint(11,54.4095,8.25185);
   cTritium[4]->SetPoint(12,36.1959,10.7361);
   cTritium[4]->SetPoint(13,26.0772,13.489);
   cTritium[4]->SetPoint(14,17.115,16.779);
   cTritium[4]->SetPoint(15,3.23797,22.2175);
   cTritium[4]->SetPoint(16,1.79245,22.0833);
   cTritium[4]->SetPoint(17,1.79245,22.0161);
}

void cutTritium5() {

   cTritium[5] = new TCutG("cT_5",15);
   cTritium[5]->SetVarX("CsI==5");
   cTritium[5]->SetVarY("dE-E");
   cTritium[5]->SetTitle("Graph");
   cTritium[5]->SetFillStyle(1000);
   cTritium[5]->SetPoint(0,3.54981,20.6522);
   cTritium[5]->SetPoint(1,3.54981,18.6448);
   cTritium[5]->SetPoint(2,12.4243,14.3432);
   cTritium[5]->SetPoint(3,25.0138,10.3284);
   cTritium[5]->SetPoint(4,42.5564,7.46067);
   cTritium[5]->SetPoint(5,62.5757,5.51063);
   cTritium[5]->SetPoint(6,100.138,4.01941);
   cTritium[5]->SetPoint(7,99.1057,5.62533);
   cTritium[5]->SetPoint(8,76.1971,6.543);
   cTritium[5]->SetPoint(9,56.1778,7.86215);
   cTritium[5]->SetPoint(10,38.4288,10.099);
   cTritium[5]->SetPoint(11,28.3159,12.2784);
   cTritium[5]->SetPoint(12,17.3776,15.605);
   cTritium[5]->SetPoint(13,3.75619,20.7095);
   cTritium[5]->SetPoint(14,3.54981,20.6522);
}


void cutTritium6() {

   cTritium[6] = new TCutG("cT_6",17);
   cTritium[6]->SetVarX(" CsI==6");
   cTritium[6]->SetVarY("dE-E");
   cTritium[6]->SetTitle("Graph");
   cTritium[6]->SetFillStyle(1000);
   cTritium[6]->SetPoint(0,5.93719,20.1312);
   cTritium[6]->SetPoint(1,6.67018,17.1776);
   cTritium[6]->SetPoint(2,18.0315,12.0089);
   cTritium[6]->SetPoint(3,31.5917,8.38408);
   cTritium[6]->SetPoint(4,46.9845,5.96753);
   cTritium[6]->SetPoint(5,67.5081,4.625);
   cTritium[6]->SetPoint(6,89.4977,3.55098);
   cTritium[6]->SetPoint(7,110.754,3.21535);
   cTritium[6]->SetPoint(8,109.655,4.69213);
   cTritium[6]->SetPoint(9,85.0998,5.22914);
   cTritium[6]->SetPoint(10,60.1782,6.50454);
   cTritium[6]->SetPoint(11,45.885,8.1827);
   cTritium[6]->SetPoint(12,32.6912,10.7335);
   cTritium[6]->SetPoint(13,23.5289,13.9556);
   cTritium[6]->SetPoint(14,9.23564,20.3997);
   cTritium[6]->SetPoint(15,5.93719,20.1312);
   cTritium[6]->SetPoint(16,5.93719,20.1312);
}

void cutTritium7() {

   cTritium[7] = new TCutG("cT_7",16);
   cTritium[7]->SetVarX(" CsI==7");
   cTritium[7]->SetVarY("dE-E");
   cTritium[7]->SetTitle("Graph");
   cTritium[7]->SetFillStyle(1000);
   cTritium[7]->SetPoint(0,3.13261,20.7717);
   cTritium[7]->SetPoint(1,3.13261,18.1661);
   cTritium[7]->SetPoint(2,14.6002,13.6229);
   cTritium[7]->SetPoint(3,29.1445,9.48056);
   cTritium[7]->SetPoint(4,42.8496,7.47621);
   cTritium[7]->SetPoint(5,65.7848,5.20462);
   cTritium[7]->SetPoint(6,103.824,3.46752);
   cTritium[7]->SetPoint(7,103.824,5.20462);
   cTritium[7]->SetPoint(8,78.6509,6.20679);
   cTritium[7]->SetPoint(9,54.5969,8.01071);
   cTritium[7]->SetPoint(10,43.1293,9.61419);
   cTritium[7]->SetPoint(11,31.6617,11.7522);
   cTritium[7]->SetPoint(12,20.1941,15.0259);
   cTritium[7]->SetPoint(13,6.76867,21.1058);
   cTritium[7]->SetPoint(14,3.13261,20.8385);
   cTritium[7]->SetPoint(15,3.13261,20.7717);
}

void cutTritium8() {

   cTritium[8] = new TCutG("cT_8",19);
   cTritium[8]->SetVarX(" CsI==8");
   cTritium[8]->SetVarY("dE-E");
   cTritium[8]->SetTitle("Graph");
   cTritium[8]->SetFillStyle(1000);
   cTritium[8]->SetPoint(0,0.781006,22.5577);
   cTritium[8]->SetPoint(1,1.49101,19.2768);
   cTritium[8]->SetPoint(2,8.59109,15.996);
   cTritium[8]->SetPoint(3,19.2412,11.9116);
   cTritium[8]->SetPoint(4,32.3763,9.09942);
   cTritium[8]->SetPoint(5,46.2215,7.02376);
   cTritium[8]->SetPoint(6,60.7766,5.75158);
   cTritium[8]->SetPoint(7,77.4618,4.68028);
   cTritium[8]->SetPoint(8,119.707,3.14027);
   cTritium[8]->SetPoint(9,118.642,5.14897);
   cTritium[8]->SetPoint(10,93.0819,5.68463);
   cTritium[8]->SetPoint(11,67.5217,6.82289);
   cTritium[8]->SetPoint(12,51.9015,8.49681);
   cTritium[8]->SetPoint(13,38.0564,10.5725);
   cTritium[8]->SetPoint(14,28.4713,12.5142);
   cTritium[8]->SetPoint(15,13.9161,18.0716);
   cTritium[8]->SetPoint(16,3.62104,22.6247);
   cTritium[8]->SetPoint(17,0.781006,22.5577);
   cTritium[8]->SetPoint(18,0.781006,22.5577);
}

void cutTritium9() {

   cTritium[9] = new TCutG("cT_9",19);
   cTritium[9]->SetVarX(" CsI==9");
   cTritium[9]->SetVarY("dE-E");
   cTritium[9]->SetTitle("Graph");
   cTritium[9]->SetFillStyle(1000);
   cTritium[9]->SetPoint(0,3.4173,20.2073);
   cTritium[9]->SetPoint(1,5.50102,16.7823);
   cTritium[9]->SetPoint(2,14.6694,13.134);
   cTritium[9]->SetPoint(3,30.0889,8.96449);
   cTritium[9]->SetPoint(4,44.675,6.65636);
   cTritium[9]->SetPoint(5,65.0955,5.01834);
   cTritium[9]->SetPoint(6,94.6843,3.67814);
   cTritium[9]->SetPoint(7,132.191,2.85912);
   cTritium[9]->SetPoint(8,131.775,4.79497);
   cTritium[9]->SetPoint(9,101.769,5.39062);
   cTritium[9]->SetPoint(10,75.5141,6.35854);
   cTritium[9]->SetPoint(11,53.8434,8.07102);
   cTritium[9]->SetPoint(12,40.0908,10.0069);
   cTritium[9]->SetPoint(13,28.422,12.4639);
   cTritium[9]->SetPoint(14,18.8368,15.8144);
   cTritium[9]->SetPoint(15,10.502,19.016);
   cTritium[9]->SetPoint(16,7.58474,20.3562);
   cTritium[9]->SetPoint(17,3.4173,20.3562);
   cTritium[9]->SetPoint(18,3.4173,20.2073);
}

void cutTritium10() {

   cTritium[10] = new TCutG("cT_10",18);
   cTritium[10]->SetVarX(" CsI==10");
   cTritium[10]->SetVarY("dE-E");
   cTritium[10]->SetTitle("Graph");
   cTritium[10]->SetFillStyle(1000);
   cTritium[10]->SetPoint(0,4.12348,21.0076);
   cTritium[10]->SetPoint(1,4.62634,17.9192);
   cTritium[10]->SetPoint(2,17.1979,13.1524);
   cTritium[10]->SetPoint(3,31.781,9.32551);
   cTritium[10]->SetPoint(4,47.3697,7.17708);
   cTritium[10]->SetPoint(5,65.9757,5.56576);
   cTritium[10]->SetPoint(6,88.6046,4.223);
   cTritium[10]->SetPoint(7,122.799,3.21592);
   cTritium[10]->SetPoint(8,122.799,5.23007);
   cTritium[10]->SetPoint(9,86.5931,5.96859);
   cTritium[10]->SetPoint(10,63.4614,7.71419);
   cTritium[10]->SetPoint(11,45.3583,9.59406);
   cTritium[10]->SetPoint(12,33.7924,12.0782);
   cTritium[10]->SetPoint(13,24.238,14.9651);
   cTritium[10]->SetPoint(14,15.1865,17.9192);
   cTritium[10]->SetPoint(15,8.64925,21.209);
   cTritium[10]->SetPoint(16,4.12348,21.0076);
   cTritium[10]->SetPoint(17,4.12348,21.0076);
}

void cutTritium11() {

   cTritium[11] = new TCutG("cT_11",17);
   cTritium[11]->SetVarX(" CsI==11");
   cTritium[11]->SetVarY("dE-E");
   cTritium[11]->SetTitle("Graph");
   cTritium[11]->SetFillStyle(1000);
   cTritium[11]->SetPoint(0,2.91957,21.535);
   cTritium[11]->SetPoint(1,3.8716,17.7886);
   cTritium[11]->SetPoint(2,16.5654,13.2394);
   cTritium[11]->SetPoint(3,26.403,9.89446);
   cTritium[11]->SetPoint(4,44.1743,7.21848);
   cTritium[11]->SetPoint(5,68.6098,5.27838);
   cTritium[11]->SetPoint(6,103.2,3.53899);
   cTritium[11]->SetPoint(7,103.518,5.41218);
   cTritium[11]->SetPoint(8,71.7833,7.01778);
   cTritium[11]->SetPoint(9,53.6946,8.28887);
   cTritium[11]->SetPoint(10,40.0488,10.4297);
   cTritium[11]->SetPoint(11,28.9418,12.7042);
   cTritium[11]->SetPoint(12,15.9307,17.0527);
   cTritium[11]->SetPoint(13,8.94911,19.7287);
   cTritium[11]->SetPoint(14,5.45832,21.7357);
   cTritium[11]->SetPoint(15,2.91957,21.6019);
   cTritium[11]->SetPoint(16,2.91957,21.535);
}

void cutTritium12() {

   cTritium[12] = new TCutG("cT_12",18);
   cTritium[12]->SetVarX(" CsI==12");
   cTritium[12]->SetVarY("dE-E");
   cTritium[12]->SetTitle("Graph");
   cTritium[12]->SetFillStyle(1000);
   cTritium[12]->SetPoint(0,1.76758,21.3901);
   cTritium[12]->SetPoint(1,2.33776,18.6572);
   cTritium[12]->SetPoint(2,11.4607,14.7911);
   cTritium[12]->SetPoint(3,23.7197,10.9917);
   cTritium[12]->SetPoint(4,35.4086,8.45872);
   cTritium[12]->SetPoint(5,49.9483,6.79231);
   cTritium[12]->SetPoint(6,71.6154,4.99258);
   cTritium[12]->SetPoint(7,104.971,3.52613);
   cTritium[12]->SetPoint(8,104.686,5.45917);
   cTritium[12]->SetPoint(9,80.4533,6.39237);
   cTritium[12]->SetPoint(10,55.3651,8.32541);
   cTritium[12]->SetPoint(11,40.5402,10.1918);
   cTritium[12]->SetPoint(12,28.8514,12.3248);
   cTritium[12]->SetPoint(13,18.5881,16.1909);
   cTritium[12]->SetPoint(14,7.75453,20.3236);
   cTritium[12]->SetPoint(15,4.9036,21.6567);
   cTritium[12]->SetPoint(16,1.76758,21.3901);
   cTritium[12]->SetPoint(17,1.76758,21.3901);
}

void cutTritium13() {

   cTritium[13] = new TCutG("cT_13",18);
   cTritium[13]->SetVarX(" CsI==13");
   cTritium[13]->SetVarY("dE-E");
   cTritium[13]->SetTitle("Graph");
   cTritium[13]->SetFillStyle(1000);
   cTritium[13]->SetPoint(0,1.06965,21.9661);
   cTritium[13]->SetPoint(1,1.73818,19.0507);
   cTritium[13]->SetPoint(2,9.09203,15.3131);
   cTritium[13]->SetPoint(3,21.1256,11.5007);
   cTritium[13]->SetPoint(4,32.1564,9.10857);
   cTritium[13]->SetPoint(5,47.1983,7.01548);
   cTritium[13]->SetPoint(6,59.9004,5.81944);
   cTritium[13]->SetPoint(7,81.2934,4.54863);
   cTritium[13]->SetPoint(8,119.734,3.05357);
   cTritium[13]->SetPoint(9,120.068,5.07191);
   cTritium[13]->SetPoint(10,84.6361,6.1932);
   cTritium[13]->SetPoint(11,54.8864,8.21153);
   cTritium[13]->SetPoint(12,38.8417,10.3046);
   cTritium[13]->SetPoint(13,23.7997,13.9675);
   cTritium[13]->SetPoint(14,13.1032,17.8547);
   cTritium[13]->SetPoint(15,6.08364,21.5923);
   cTritium[13]->SetPoint(16,0.735383,21.9661);
   cTritium[13]->SetPoint(17,1.06965,21.9661);
}

void cutTritium14() {

   cTritium[14] = new TCutG("cT_14",14);
   cTritium[14]->SetVarX(" CsI==14");
   cTritium[14]->SetVarY("dE-E");
   cTritium[14]->SetTitle("Graph");
   cTritium[14]->SetFillStyle(1000);
   cTritium[14]->SetPoint(0,6.23079,19.9);
   cTritium[14]->SetPoint(1,6.90511,16.918);
   cTritium[14]->SetPoint(2,18.2338,12.5195);
   cTritium[14]->SetPoint(3,29.1579,9.6866);
   cTritium[14]->SetPoint(4,42.3747,7.59919);
   cTritium[14]->SetPoint(5,58.6935,5.95909);
   cTritium[14]->SetPoint(6,58.9632,8.04649);
   cTritium[14]->SetPoint(7,45.6115,9.2393);
   cTritium[14]->SetPoint(8,34.6874,10.954);
   cTritium[14]->SetPoint(9,23.3587,13.5632);
   cTritium[14]->SetPoint(10,14.8622,16.6198);
   cTritium[14]->SetPoint(11,6.23079,19.9745);
   cTritium[14]->SetPoint(12,6.23079,19.9745);
   cTritium[14]->SetPoint(13,6.23079,19.9);

}

void cutTritium15() {

   cTritium[15] = new TCutG("cT_15",18);
   cTritium[15]->SetVarX(" CsI==15");
   cTritium[15]->SetVarY("dE-E");
   cTritium[15]->SetTitle("Graph");
   cTritium[15]->SetFillStyle(1000);
   cTritium[15]->SetPoint(0,2.54896,21.4505);
   cTritium[15]->SetPoint(1,2.54896,18.9925);
   cTritium[15]->SetPoint(2,11.1379,15.0067);
   cTritium[15]->SetPoint(3,22.2203,11.2866);
   cTritium[15]->SetPoint(4,32.4716,9.02794);
   cTritium[15]->SetPoint(5,45.4935,7.30074);
   cTritium[15]->SetPoint(6,63.7795,5.50711);
   cTritium[15]->SetPoint(7,90.3774,3.9792);
   cTritium[15]->SetPoint(8,108.94,3.38132);
   cTritium[15]->SetPoint(9,108.386,5.37425);
   cTritium[15]->SetPoint(10,75.139,6.70286);
   cTritium[15]->SetPoint(11,51.3117,8.69578);
   cTritium[15]->SetPoint(12,37.1816,10.5558);
   cTritium[15]->SetPoint(13,24.7139,13.9438);
   cTritium[15]->SetPoint(14,14.1855,17.6639);
   cTritium[15]->SetPoint(15,6.70488,21.0519);
   cTritium[15]->SetPoint(16,2.2719,21.5169);
   cTritium[15]->SetPoint(17,2.54896,21.4505);
}

void cutsTritiumCal() {

   cutTritium0();
   cutTritium1();
   cutTritium2();
   cutTritium3();
   cutTritium4();
   cutTritium5();
   cutTritium6();
   cutTritium7();
   cutTritium8();
   cutTritium9();
   cutTritium10();
   cutTritium11();
   cutTritium12();
   cutTritium13();
   cutTritium14();
   cutTritium15();

   TString var;

   for (Int_t i = 0; i < 16; i++) {
      
      cTritium[i]->SetLineColor(kRed);
      cTritium[i]->SetLineWidth(1);
      var.Form("fCsI");
      cTritium[i]->SetVarX(var);
      var.Form("fCTX");
      cTritium[i]->SetVarY(var);

   }
}
