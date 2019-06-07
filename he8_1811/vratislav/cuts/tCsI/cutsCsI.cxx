#if !defined(__CLING__)

#include "TCutG.h"


#endif

TCutG *cCsI[16];

void cut0() {

  TCutG *cCsI[0] = new TCutG("CUTG",25);
	cCsI[0]->SetVarX(" crystal==0");
	cCsI[0]->SetVarY("dE-tau");
	cCsI[0]->SetTitle("Graph");
	cCsI[0]->SetFillStyle(1000);
	cCsI[0]->SetPoint(0,-310.96,2457.17);
	cCsI[0]->SetPoint(1,-313.999,2580.76);
	cCsI[0]->SetPoint(2,-278.545,2624.18);
	cCsI[0]->SetPoint(3,-258.286,2243.4);
	cCsI[0]->SetPoint(4,-206.625,1391.65);
	cCsI[0]->SetPoint(5,-194.469,1057.63);
	cCsI[0]->SetPoint(6,-177.249,947.405);
	cCsI[0]->SetPoint(7,-146.86,793.756);
	cCsI[0]->SetPoint(8,-117.484,660.149);
	cCsI[0]->SetPoint(9,-62.7836,543.243);
	cCsI[0]->SetPoint(10,-3.01864,516.521);
	cCsI[0]->SetPoint(11,30.4092,523.201);
	cCsI[0]->SetPoint(12,96.252,526.542);
	cCsI[0]->SetPoint(13,150.952,506.501);
	cCsI[0]->SetPoint(14,213.756,466.418);
	cCsI[0]->SetPoint(15,233.002,339.491);
	cCsI[0]->SetPoint(16,227.938,239.286);
	cCsI[0]->SetPoint(17,-29.3558,339.491);
	cCsI[0]->SetPoint(18,-133.691,463.078);
	cCsI[0]->SetPoint(19,-192.443,636.768);
	cCsI[0]->SetPoint(20,-217.767,803.777);
	cCsI[0]->SetPoint(21,-258.286,1214.62);
	cCsI[0]->SetPoint(22,-268.416,1642.16);
	cCsI[0]->SetPoint(23,-282.597,1992.88);
	cCsI[0]->SetPoint(24,-310.96,2457.17);

}

void cut1() {
  TCutG *cCsI[1] = new TCutG("CUTG",20);
	cCsI[1]->SetVarX(" crystal==1");
	cCsI[1]->SetVarY("dE-tau");
	cCsI[1]->SetTitle("Graph");
	cCsI[1]->SetFillStyle(1000);
	cCsI[1]->SetPoint(0,-244.449,1211.2);
	cCsI[1]->SetPoint(1,-253.762,1509.25);
	cCsI[1]->SetPoint(2,-233.066,1540.08);
	cCsI[1]->SetPoint(3,-206.162,1447.58);
	cCsI[1]->SetPoint(4,-186.501,1072.46);
	cCsI[1]->SetPoint(5,-156.493,897.739);
	cCsI[1]->SetPoint(6,-103.719,728.16);
	cCsI[1]->SetPoint(7,-48.8755,584.275);
	cCsI[1]->SetPoint(8,28.733,538.027);
	cCsI[1]->SetPoint(9,122.898,486.639);
	cCsI[1]->SetPoint(10,184.985,491.778);
	cCsI[1]->SetPoint(11,190.159,373.587);
	cCsI[1]->SetPoint(12,182.915,332.477);
	cCsI[1]->SetPoint(13,132.211,270.812);
	cCsI[1]->SetPoint(14,3.89825,327.338);
	cCsI[1]->SetPoint(15,-110.962,476.362);
	cCsI[1]->SetPoint(16,-187.536,676.773);
	cCsI[1]->SetPoint(17,-238.24,959.404);
	cCsI[1]->SetPoint(18,-251.692,1200.92);
	cCsI[1]->SetPoint(19,-244.449,1211.2);
}

void cut2() {
	cCsI[2] = new TCutG("cutCsI_2",16);
	cCsI[2]->SetVarX(" crystal==2");
	cCsI[2]->SetVarY("dE-tau");
	cCsI[2]->SetTitle("Graph");
	cCsI[2]->SetFillStyle(1000);
	cCsI[2]->SetPoint(0,-226.73,883.273);
	cCsI[2]->SetPoint(1,-263.978,1498.38);
	cCsI[2]->SetPoint(2,-278.464,2005.58);
	cCsI[2]->SetPoint(3,-254.666,2091.91);
	cCsI[2]->SetPoint(4,-221.556,1498.38);
	cCsI[2]->SetPoint(5,-180.169,1109.89);
	cCsI[2]->SetPoint(6,-138.781,872.482);
	cCsI[2]->SetPoint(7,-103.602,780.755);
	cCsI[2]->SetPoint(8,-31.1739,667.446);
	cCsI[2]->SetPoint(9,68.156,510.971);
	cCsI[2]->SetPoint(10,89.8844,440.827);
	cCsI[2]->SetPoint(11,96.0926,354.496);
	cCsI[2]->SetPoint(12,27.8032,327.518);
	cCsI[2]->SetPoint(13,-95.3245,392.266);
	cCsI[2]->SetPoint(14,-203.967,716.007);
	cCsI[2]->SetPoint(15,-226.73,883.273);
}

void cut3() {
	cCsI[3] = new TCutG("cutCsI_3",17);
	cCsI[3]->SetVarX(" crystal==3");
	cCsI[3]->SetVarY("dE-tau");
	cCsI[3]->SetTitle("Graph");
	cCsI[3]->SetFillStyle(1000);
	cCsI[3]->SetPoint(0,-269.436,1457.86);
	cCsI[3]->SetPoint(1,-286.579,2182.43);
	cCsI[3]->SetPoint(2,-272.293,2341.73);
	cCsI[3]->SetPoint(3,-238.959,1668.55);
	cCsI[3]->SetPoint(4,-208.483,1180.37);
	cCsI[3]->SetPoint(5,-170.388,892.6);
	cCsI[3]->SetPoint(6,-113.244,707.605);
	cCsI[3]->SetPoint(7,-30.3868,589.414);
	cCsI[3]->SetPoint(8,109.614,460.946);
	cCsI[3]->SetPoint(9,181.043,368.448);
	cCsI[3]->SetPoint(10,185.805,301.644);
	cCsI[3]->SetPoint(11,45.8041,301.644);
	cCsI[3]->SetPoint(12,-116.102,404.419);
	cCsI[3]->SetPoint(13,-208.483,702.467);
	cCsI[3]->SetPoint(14,-254.197,1154.68);
	cCsI[3]->SetPoint(15,-261.817,1313.98);
	cCsI[3]->SetPoint(16,-269.436,1457.86);
}

void cut4() {

	cCsI[4] = new TCutG("cutCsI_4",17);
	cCsI[4]->SetVarX(" crystal==4");
	cCsI[4]->SetVarY("dE-tau");
	cCsI[4]->SetTitle("Graph");
	cCsI[4]->SetFillStyle(1000);
	cCsI[4]->SetPoint(0,-255.729,1235.75);
	cCsI[4]->SetPoint(1,-279.088,1895.51);
	cCsI[4]->SetPoint(2,-281.09,2159.41);
	cCsI[4]->SetPoint(3,-273.081,2210.9);
	cCsI[4]->SetPoint(4,-251.724,2204.47);
	cCsI[4]->SetPoint(5,-229.7,1589.77);
	cCsI[4]->SetPoint(6,-166.963,910.698);
	cCsI[4]->SetPoint(7,-98.8877,646.795);
	cCsI[4]->SetPoint(8,-14.7942,521.28);
	cCsI[4]->SetPoint(9,94.6607,460.131);
	cCsI[4]->SetPoint(10,134.705,427.948);
	cCsI[4]->SetPoint(11,151.39,263.813);
	cCsI[4]->SetPoint(12,-4.11569,302.433);
	cCsI[4]->SetPoint(13,-146.274,479.441);
	cCsI[4]->SetPoint(14,-226.363,846.331);
	cCsI[4]->SetPoint(15,-249.055,1123.11);
	cCsI[4]->SetPoint(16,-255.729,1235.75);

}

void cut5() {
	cCsI[5] = new TCutG("cutCsI_5",21);
	cCsI[5]->SetVarX(" crystal==5");
	cCsI[5]->SetVarY("dE-tau");
	cCsI[5]->SetTitle("Graph");
	cCsI[5]->SetFillStyle(1000);
	cCsI[5]->SetPoint(0,-283.517,1841.62);
	cCsI[5]->SetPoint(1,-288.05,2049.65);
	cCsI[5]->SetPoint(2,-283.517,2055.12);
	cCsI[5]->SetPoint(3,-268.408,2044.18);
	cCsI[5]->SetPoint(4,-250.277,1737.61);
	cCsI[5]->SetPoint(5,-225.348,1288.71);
	cCsI[5]->SetPoint(6,-201.929,1080.68);
	cCsI[5]->SetPoint(7,-169.445,828.862);
	cCsI[5]->SetPoint(8,-122.608,675.579);
	cCsI[5]->SetPoint(9,-49.3295,538.719);
	cCsI[5]->SetPoint(10,40.5682,478.501);
	cCsI[5]->SetPoint(11,63.2315,418.283);
	cCsI[5]->SetPoint(12,59.4543,352.59);
	cCsI[5]->SetPoint(13,10.3505,325.218);
	cCsI[5]->SetPoint(14,-112.787,412.808);
	cCsI[5]->SetPoint(15,-183.043,566.091);
	cCsI[5]->SetPoint(16,-212.505,752.22);
	cCsI[5]->SetPoint(17,-243.478,949.298);
	cCsI[5]->SetPoint(18,-258.587,1228.49);
	cCsI[5]->SetPoint(19,-281.251,1737.61);
	cCsI[5]->SetPoint(20,-283.517,1841.62);
}

void cut6() {
	cCsI[6] = new TCutG("cutCsI_6",18);
	cCsI[6]->SetVarX(" crystal==6");
	cCsI[6]->SetVarY("dE-tau");
	cCsI[6]->SetTitle("Graph");
	cCsI[6]->SetFillStyle(1000);
	cCsI[6]->SetPoint(0,-280.505,2138.94);
	cCsI[6]->SetPoint(1,-282.222,2404.23);
	cCsI[6]->SetPoint(2,-267.633,2449.19);
	cCsI[6]->SetPoint(3,-245.321,1968.08);
	cCsI[6]->SetPoint(4,-207.562,1271.13);
	cCsI[6]->SetPoint(5,-163.797,843.975);
	cCsI[6]->SetPoint(6,-121.747,673.111);
	cCsI[6]->SetPoint(7,-47.0877,547.212);
	cCsI[6]->SetPoint(8,76.4863,416.817);
	cCsI[6]->SetPoint(9,141.706,385.342);
	cCsI[6]->SetPoint(10,142.564,313.399);
	cCsI[6]->SetPoint(11,97.0819,290.917);
	cCsI[6]->SetPoint(12,-47.9459,326.888);
	cCsI[6]->SetPoint(13,-159.506,488.759);
	cCsI[6]->SetPoint(14,-211.853,740.558);
	cCsI[6]->SetPoint(15,-259.91,1392.54);
	cCsI[6]->SetPoint(16,-277.931,1905.13);
	cCsI[6]->SetPoint(17,-280.505,2138.94);
}

void cut7() {
	cCsI[7] = new TCutG("cutCsI_7",23);
	cCsI[7]->SetVarX(" crystal==7");
	cCsI[7]->SetVarY("dE-tau");
	cCsI[7]->SetTitle("Graph");
	cCsI[7]->SetFillStyle(1000);
	cCsI[7]->SetPoint(0,-286.312,2192.7);
	cCsI[7]->SetPoint(1,-294.655,2840.19);
	cCsI[7]->SetPoint(2,-301.481,3292.39);
	cCsI[7]->SetPoint(3,-299.964,3446.56);
	cCsI[7]->SetPoint(4,-287.45,3549.33);
	cCsI[7]->SetPoint(5,-267.731,2331.45);
	cCsI[7]->SetPoint(6,-252.183,1797.02);
	cCsI[7]->SetPoint(7,-236.635,1473.28);
	cCsI[7]->SetPoint(8,-217.295,1164.95);
	cCsI[7]->SetPoint(9,-185.82,887.461);
	cCsI[7]->SetPoint(10,-107.323,604.83);
	cCsI[7]->SetPoint(11,-38.685,507.194);
	cCsI[7]->SetPoint(12,16.6803,502.055);
	cCsI[7]->SetPoint(13,47.776,435.252);
	cCsI[7]->SetPoint(14,54.6018,296.506);
	cCsI[7]->SetPoint(15,12.8882,322.199);
	cCsI[7]->SetPoint(16,-113.77,378.726);
	cCsI[7]->SetPoint(17,-173.306,507.194);
	cCsI[7]->SetPoint(18,-211.607,681.912);
	cCsI[7]->SetPoint(19,-248.77,1108.43);
	cCsI[7]->SetPoint(20,-273.419,1601.75);
	cCsI[7]->SetPoint(21,-282.141,1976.88);
	cCsI[7]->SetPoint(22,-286.312,2192.7);
}

void cut8() {

	cCsI[8] = new TCutG("cutCsI_8",20);
	cCsI[8]->SetVarX("crystal==8");
	cCsI[8]->SetVarY("dE-tau");
	cCsI[8]->SetTitle("Graph");
	cCsI[8]->SetFillStyle(1000);
	cCsI[8]->SetPoint(0,-258.789,1350.51);
	cCsI[8]->SetPoint(1,-265.677,1610.02);
	cCsI[8]->SetPoint(2,-262.233,1658.84);
	cCsI[8]->SetPoint(3,-243.865,1638.28);
	cCsI[8]->SetPoint(4,-214.59,1114.13);
	cCsI[8]->SetPoint(5,-177.279,816.084);
	cCsI[8]->SetPoint(6,-142.264,656.783);
	cCsI[8]->SetPoint(7,-105.527,571.994);
	cCsI[8]->SetPoint(8,1.23919,448.664);
	cCsI[8]->SetPoint(9,167.703,384.43);
	cCsI[8]->SetPoint(10,178.61,356.166);
	cCsI[8]->SetPoint(11,173.443,266.238);
	cCsI[8]->SetPoint(12,81.0271,281.655);
	cCsI[8]->SetPoint(13,12.7195,294.502);
	cCsI[8]->SetPoint(14,-61.3283,348.458);
	cCsI[8]->SetPoint(15,-148.004,487.205);
	cCsI[8]->SetPoint(16,-203.684,703.032);
	cCsI[8]->SetPoint(17,-234.107,929.137);
	cCsI[8]->SetPoint(18,-255.919,1276);
	cCsI[8]->SetPoint(19,-258.789,1350.51);

}

void cut10() {
	cCsI[10] = new TCutG("cutCsI_10",22);
	cCsI[10]->SetVarX(" crystal==10");
	cCsI[10]->SetVarY("dE-tau");
	cCsI[10]->SetTitle("Graph");
	cCsI[10]->SetFillStyle(1000);
	cCsI[10]->SetPoint(0,-276.303,1713.69);
	cCsI[10]->SetPoint(1,-283.327,1998.9);
	cCsI[10]->SetPoint(2,-274.548,2064.41);
	cCsI[10]->SetPoint(3,-259.623,2099.1);
	cCsI[10]->SetPoint(4,-244.699,2045.14);
	cCsI[10]->SetPoint(5,-235.042,1601.93);
	cCsI[10]->SetPoint(6,-217.484,1216.52);
	cCsI[10]->SetPoint(7,-189.391,969.861);
	cCsI[10]->SetPoint(8,-154.275,838.823);
	cCsI[10]->SetPoint(9,-102.478,622.996);
	cCsI[10]->SetPoint(10,-4.15316,511.228);
	cCsI[10]->SetPoint(11,101.195,422.585);
	cCsI[10]->SetPoint(12,151.236,357.066);
	cCsI[10]->SetPoint(13,146.846,268.422);
	cCsI[10]->SetPoint(14,39.742,283.839);
	cCsI[10]->SetPoint(15,-93.6994,357.066);
	cCsI[10]->SetPoint(16,-185.001,538.207);
	cCsI[10]->SetPoint(17,-228.019,811.845);
	cCsI[10]->SetPoint(18,-257.867,1228.08);
	cCsI[10]->SetPoint(19,-271.914,1413.08);
	cCsI[10]->SetPoint(20,-275.425,1655.88);
	cCsI[10]->SetPoint(21,-276.303,1713.69);
}

void cut11() {
	cCsI[11] = new TCutG("cutCsI_11",20);
	cCsI[11]->SetVarX(" crystal==11");
	cCsI[11]->SetVarY("dE-tau");
	cCsI[11]->SetTitle("Graph");
	cCsI[11]->SetFillStyle(1000);
	cCsI[11]->SetPoint(0,-288.323,2307.49);
	cCsI[11]->SetPoint(1,-289.133,2472.83);
	cCsI[11]->SetPoint(2,-279.814,2540.66);
	cCsI[11]->SetPoint(3,-256.718,1959.85);
	cCsI[11]->SetPoint(4,-229.571,1298.5);
	cCsI[11]->SetPoint(5,-197.966,925.424);
	cCsI[11]->SetPoint(6,-153.395,772.803);
	cCsI[11]->SetPoint(7,-99.5057,594.746);
	cCsI[11]->SetPoint(8,-82.4878,628.661);
	cCsI[11]->SetPoint(9,3.41167,492.998);
	cCsI[11]->SetPoint(10,61.3533,365.814);
	cCsI[11]->SetPoint(11,45.1459,276.786);
	cCsI[11]->SetPoint(12,-56.5559,344.617);
	cCsI[11]->SetPoint(13,-142.455,416.688);
	cCsI[11]->SetPoint(14,-191.078,573.548);
	cCsI[11]->SetPoint(15,-236.053,887.269);
	cCsI[11]->SetPoint(16,-260.77,1285.78);
	cCsI[11]->SetPoint(17,-280.624,1879.3);
	cCsI[11]->SetPoint(18,-289.133,2184.55);
	cCsI[11]->SetPoint(19,-288.323,2307.49);
}

void cut12() {

	cCsI[12] = new TCutG("cutCsI_12",23);
	cCsI[12]->SetVarX("crystal==12");
	cCsI[12]->SetVarY("dE-tau");
	cCsI[12]->SetTitle("Graph");
	cCsI[12]->SetFillStyle(1000);
	cCsI[12]->SetPoint(0,-274.826,1876.31);
	cCsI[12]->SetPoint(1,-285.55,2315.67);
	cCsI[12]->SetPoint(2,-284.656,2412.8);
	cCsI[12]->SetPoint(3,-276.613,2477.54);
	cCsI[12]->SetPoint(4,-265.443,2435.92);
	cCsI[12]->SetPoint(5,-247.123,1839.31);
	cCsI[12]->SetPoint(6,-226.569,1436.95);
	cCsI[12]->SetPoint(7,-200.206,1071.58);
	cCsI[12]->SetPoint(8,-173.396,835.714);
	cCsI[12]->SetPoint(9,-141.225,733.967);
	cCsI[12]->SetPoint(10,-78.2223,581.346);
	cCsI[12]->SetPoint(11,26.3352,525.848);
	cCsI[12]->SetPoint(12,117.935,465.725);
	cCsI[12]->SetPoint(13,147.425,442.6);
	cCsI[12]->SetPoint(14,165.298,303.854);
	cCsI[12]->SetPoint(15,151.893,225.231);
	cCsI[12]->SetPoint(16,-16.1134,299.229);
	cCsI[12]->SetPoint(17,-129.161,442.6);
	cCsI[12]->SetPoint(18,-209.589,733.967);
	cCsI[12]->SetPoint(19,-229.697,951.336);
	cCsI[12]->SetPoint(20,-255.612,1288.95);
	cCsI[12]->SetPoint(21,-272.145,1816.19);
	cCsI[12]->SetPoint(22,-274.826,1876.31);

}

void cut13() {
	cCsI[13] = new TCutG("cutCsI_13",23);
	cCsI[13]->SetVarX(" crystal==13");
	cCsI[13]->SetVarY("dE-tau");
	cCsI[13]->SetTitle("Graph");
	cCsI[13]->SetFillStyle(1000);
	cCsI[13]->SetPoint(0,-259.955,1391.06);
	cCsI[13]->SetPoint(1,-272.879,1673.69);
	cCsI[13]->SetPoint(2,-281.017,2023.12);
	cCsI[13]->SetPoint(3,-274.315,2167.01);
	cCsI[13]->SetPoint(4,-256.605,2151.59);
	cCsI[13]->SetPoint(5,-232.671,1478.42);
	cCsI[13]->SetPoint(6,-216.875,1200.92);
	cCsI[13]->SetPoint(7,-192.942,995.375);
	cCsI[13]->SetPoint(8,-160.392,861.768);
	cCsI[13]->SetPoint(9,-115.876,712.744);
	cCsI[13]->SetPoint(10,-34.5021,599.692);
	cCsI[13]->SetPoint(11,64.5824,543.165);
	cCsI[13]->SetPoint(12,167.018,440.391);
	cCsI[13]->SetPoint(13,170.368,368.448);
	cCsI[13]->SetPoint(14,110.056,317.061);
	cCsI[13]->SetPoint(15,-4.82462,358.171);
	cCsI[13]->SetPoint(16,-90.0277,404.419);
	cCsI[13]->SetPoint(17,-155.127,527.749);
	cCsI[13]->SetPoint(18,-204.43,707.605);
	cCsI[13]->SetPoint(19,-224.055,815.519);
	cCsI[13]->SetPoint(20,-245.595,1118.71);
	cCsI[13]->SetPoint(21,-252.297,1216.34);
	cCsI[13]->SetPoint(22,-259.955,1391.06);
}

void cut14() {

	cCsI[14] = new TCutG("cutCsI_14",22);
	cCsI[14]->SetVarX("crystal==14");
	cCsI[14]->SetVarY("dE-tau");
	cCsI[14]->SetTitle("Graph");
	cCsI[14]->SetFillStyle(1000);
	cCsI[14]->SetPoint(0,-265.012,1570.91);
	cCsI[14]->SetPoint(1,-277.3,1971.74);
	cCsI[14]->SetPoint(2,-275.605,2295.48);
	cCsI[14]->SetPoint(3,-265.436,2336.59);
	cCsI[14]->SetPoint(4,-247.638,1755.91);
	cCsI[14]->SetPoint(5,-227.723,1334.53);
	cCsI[14]->SetPoint(6,-202.298,1062.18);
	cCsI[14]->SetPoint(7,-181.111,887.461);
	cCsI[14]->SetPoint(8,-146.364,723.022);
	cCsI[14]->SetPoint(9,-98.058,630.524);
	cCsI[14]->SetPoint(10,-12.8862,527.749);
	cCsI[14]->SetPoint(11,49.4037,517.472);
	cCsI[14]->SetPoint(12,148.983,517.472);
	cCsI[14]->SetPoint(13,151.101,347.893);
	cCsI[14]->SetPoint(14,33.3015,317.061);
	cCsI[14]->SetPoint(15,-87.0408,378.726);
	cCsI[14]->SetPoint(16,-168.399,548.304);
	cCsI[14]->SetPoint(17,-212.044,728.16);
	cCsI[14]->SetPoint(18,-242.13,1015.93);
	cCsI[14]->SetPoint(19,-254.842,1288.28);
	cCsI[14]->SetPoint(20,-262.469,1514.39);
	cCsI[14]->SetPoint(21,-265.012,1570.91);
}

void cut15() {
	cCsI[15] = new TCutG("cutCsI_15",21);
	cCsI[15]->SetVarX(" crystal==15");
	cCsI[15]->SetVarY("dE-tau");
	cCsI[15]->SetTitle("Graph");
	cCsI[15]->SetFillStyle(1000);
	cCsI[15]->SetPoint(0,-270.044,1615.57);
	cCsI[15]->SetPoint(1,-282.83,2045.68);
	cCsI[15]->SetPoint(2,-284.251,2147.43);
	cCsI[15]->SetPoint(3,-278.568,2189.05);
	cCsI[15]->SetPoint(4,-268.15,2184.43);
	cCsI[15]->SetPoint(5,-233.106,1439.83);
	cCsI[15]->SetPoint(6,-209.428,1106.83);
	cCsI[15]->SetPoint(7,-181.961,921.84);
	cCsI[15]->SetPoint(8,-137.447,741.47);
	cCsI[15]->SetPoint(9,-78.2514,635.098);
	cCsI[15]->SetPoint(10,38.2448,505.601);
	cCsI[15]->SetPoint(11,128.695,505.601);
	cCsI[15]->SetPoint(12,181.26,445.478);
	cCsI[15]->SetPoint(13,180.787,302.107);
	cCsI[15]->SetPoint(14,171.789,241.984);
	cCsI[15]->SetPoint(15,-21.8975,283.607);
	cCsI[15]->SetPoint(16,-134.605,473.227);
	cCsI[15]->SetPoint(17,-180.541,584.224);
	cCsI[15]->SetPoint(18,-223.161,810.843);
	cCsI[15]->SetPoint(19,-255.363,1296.45);
	cCsI[15]->SetPoint(20,-270.044,1615.57);
}

void cutsCsI() {

	cut0();
	cut1();
	cut2();
	cut3();
	cut4();
	cut5();
	cut6();
	cut7();
	cut8();
	cut10();
	cut11();
	cut12();
	cut13();
	cut14();
	cut15();

	TString var;
	//CsI layer
	TString CTCsI = "ERQTelescopeCsIDigi_Central_telescope_CsI_0";

	for (Int_t i = 0; i < 16; i++) {
		if (i==9) continue;
		//		cutName.Form("cutCsI_%d", i);
		//		cCsI[i] = (TCutG*)fCuts->Get(cutName);
		cCsI[i]->SetLineColor(kRed);
		cCsI[i]->SetLineWidth(1);

		//repair cuts variable
		//		var.Form("%s.fEdep", CTCsI.Data());
		var.Form("Max$(%s.fEdep)", CTCsI.Data());
		cCsI[i]->SetVarY(var);
		var.Form("%s.fTime - BeamDetToFDigi2.fTime/2.", CTCsI.Data());
		cCsI[i]->SetVarX(var);

	}
}
