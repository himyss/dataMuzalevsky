#if !defined(__CLING__)

#include "TCutG.h"


#endif

TCutG *cCsI[16];

void cut0() {

	cCsI[0] = new TCutG("cutCsI_0",19);
	cCsI[0]->SetVarX(" crystal==0");
	cCsI[0]->SetVarY("dE-tau");
	cCsI[0]->SetTitle("Graph");
	cCsI[0]->SetFillStyle(1000);
	cCsI[0]->SetPoint(0,-281.233,1388.25);
	cCsI[0]->SetPoint(1,-262.313,945.555);
	cCsI[0]->SetPoint(2,-232.04,610.695);
	cCsI[0]->SetPoint(3,-195.28,446.102);
	cCsI[0]->SetPoint(4,-147.168,349.617);
	cCsI[0]->SetPoint(5,-105.543,315.563);
	cCsI[0]->SetPoint(6,-33.1046,287.185);
	cCsI[0]->SetPoint(7,23.1163,270.159);
	cCsI[0]->SetPoint(8,17.7104,497.183);
	cCsI[0]->SetPoint(9,-32.0235,474.48);
	cCsI[0]->SetPoint(10,-87.1632,525.561);
	cCsI[0]->SetPoint(11,-136.356,673.126);
	cCsI[0]->SetPoint(12,-172.576,797.99);
	cCsI[0]->SetPoint(13,-202.308,985.284);
	cCsI[0]->SetPoint(14,-227.175,1286.09);
	cCsI[0]->SetPoint(15,-243.933,1547.17);
	cCsI[0]->SetPoint(16,-263.935,1552.84);
	cCsI[0]->SetPoint(17,-279.071,1513.12);
	cCsI[0]->SetPoint(18,-281.233,1388.25);

}

void cut1() {
	cCsI[1] = new TCutG("cutCsI_1",14);
	cCsI[1]->SetVarX(" crystal==1");
	cCsI[1]->SetVarY("dE-tau");
	cCsI[1]->SetTitle("Graph");
	cCsI[1]->SetFillStyle(1000);
	cCsI[1]->SetPoint(0,-267.754,1247.44);
	cCsI[1]->SetPoint(1,-239.75,821.154);
	cCsI[1]->SetPoint(2,-163,338.782);
	cCsI[1]->SetPoint(3,-33.3541,249.038);
	cCsI[1]->SetPoint(4,127.407,226.603);
	cCsI[1]->SetPoint(5,214.529,282.692);
	cCsI[1]->SetPoint(6,207.269,529.487);
	cCsI[1]->SetPoint(7,82.8087,551.923);
	cCsI[1]->SetPoint(8,-67.5806,652.885);
	cCsI[1]->SetPoint(9,-149.517,843.59);
	cCsI[1]->SetPoint(10,-208.635,1202.56);
	cCsI[1]->SetPoint(11,-234.564,1539.1);
	cCsI[1]->SetPoint(12,-253.233,1438.14);
	cCsI[1]->SetPoint(13,-267.754,1247.44);
}

void cut2() {
	cCsI[2] = new TCutG("cutCsI_2",13);
	cCsI[2]->SetVarX(" crystal==2");
	cCsI[2]->SetVarY("dE-tau");
	cCsI[2]->SetTitle("Graph");
	cCsI[2]->SetFillStyle(1000);
	cCsI[2]->SetPoint(0,-284.611,1505.45);
	cCsI[2]->SetPoint(1,-252.547,776.282);
	cCsI[2]->SetPoint(2,-175.594,350);
	cCsI[2]->SetPoint(3,-14.2059,237.82);
	cCsI[2]->SetPoint(4,62.7473,271.474);
	cCsI[2]->SetPoint(5,68.0913,551.923);
	cCsI[2]->SetPoint(6,-10.9995,596.795);
	cCsI[2]->SetPoint(7,-111.466,686.538);
	cCsI[2]->SetPoint(8,-173.456,955.769);
	cCsI[2]->SetPoint(9,-209.795,1247.44);
	cCsI[2]->SetPoint(10,-232.24,1595.19);
	cCsI[2]->SetPoint(11,-261.097,1808.33);
	cCsI[2]->SetPoint(12,-284.611,1505.45);
}

void cut3() {
	cCsI[3] = new TCutG("cutCsI_3",16);
	cCsI[3]->SetVarX(" crystal==3");
	cCsI[3]->SetVarY("dE-tau");
	cCsI[3]->SetTitle("Graph");
	cCsI[3]->SetFillStyle(1000);
	cCsI[3]->SetPoint(0,-261.512,990.769);
	cCsI[3]->SetPoint(1,-227.055,577.949);
	cCsI[3]->SetPoint(2,-148.571,319.936);
	cCsI[3]->SetPoint(3,-35.6298,268.333);
	cCsI[3]->SetPoint(4,135.696,251.132);
	cCsI[3]->SetPoint(5,211.309,268.333);
	cCsI[3]->SetPoint(6,205.566,483.344);
	cCsI[3]->SetPoint(7,109.854,526.346);
	cCsI[3]->SetPoint(8,-20.3157,560.748);
	cCsI[3]->SetPoint(9,-113.157,638.152);
	cCsI[3]->SetPoint(10,-141.871,706.955);
	cCsI[3]->SetPoint(11,-183.027,887.564);
	cCsI[3]->SetPoint(12,-212.698,1111.18);
	cCsI[3]->SetPoint(13,-239.498,1308.99);
	cCsI[3]->SetPoint(14,-256.726,1119.78);
	cCsI[3]->SetPoint(15,-261.512,990.769);
}

void cut4() {

	cCsI[4] = new TCutG("cutCsI_4",20);
	cCsI[4]->SetVarX(" crystal==4");
	cCsI[4]->SetVarY("dE-tau");
	cCsI[4]->SetTitle("Graph");
	cCsI[4]->SetFillStyle(1000);
	cCsI[4]->SetPoint(0,-277.664,1264.71);
	cCsI[4]->SetPoint(1,-257.538,927.128);
	cCsI[4]->SetPoint(2,-232.883,633.022);
	cCsI[4]->SetPoint(3,-191.624,466.789);
	cCsI[4]->SetPoint(4,-132.754,344.032);
	cCsI[4]->SetPoint(5,-58.7895,300.555);
	cCsI[4]->SetPoint(6,72.5353,297.998);
	cCsI[4]->SetPoint(7,151.532,310.785);
	cCsI[4]->SetPoint(8,151.028,423.312);
	cCsI[4]->SetPoint(9,65.9943,438.657);
	cCsI[4]->SetPoint(10,-65.3306,510.265);
	cCsI[4]->SetPoint(11,-123.194,597.218);
	cCsI[4]->SetPoint(12,-154.893,681.614);
	cCsI[4]->SetPoint(13,-179.548,814.601);
	cCsI[4]->SetPoint(14,-201.184,991.064);
	cCsI[4]->SetPoint(15,-216.279,1113.82);
	cCsI[4]->SetPoint(16,-235.902,1300.51);
	cCsI[4]->SetPoint(17,-245.965,1448.85);
	cCsI[4]->SetPoint(18,-272.129,1459.08);
	cCsI[4]->SetPoint(19,-277.664,1264.71);

}

void cut5() {
	cCsI[5] = new TCutG("cutCsI_5",17);
	cCsI[5]->SetVarX(" crystal==5");
	cCsI[5]->SetVarY("dE-tau");
	cCsI[5]->SetTitle("Graph");
	cCsI[5]->SetFillStyle(1000);
	cCsI[5]->SetPoint(0,-293.016,1520.21);
	cCsI[5]->SetPoint(1,-267.658,933.248);
	cCsI[5]->SetPoint(2,-213.771,432.179);
	cCsI[5]->SetPoint(3,-136.64,331.966);
	cCsI[5]->SetPoint(4,22.9047,274.701);
	cCsI[5]->SetPoint(5,217.317,281.859);
	cCsI[5]->SetPoint(6,210.978,482.286);
	cCsI[5]->SetPoint(7,138.073,503.761);
	cCsI[5]->SetPoint(8,8.11247,546.709);
	cCsI[5]->SetPoint(9,-82.7543,603.974);
	cCsI[5]->SetPoint(10,-133.471,675.556);
	cCsI[5]->SetPoint(11,-178.904,818.718);
	cCsI[5]->SetPoint(12,-208.489,1076.41);
	cCsI[5]->SetPoint(13,-235.96,1362.74);
	cCsI[5]->SetPoint(14,-264.488,1692.01);
	cCsI[5]->SetPoint(15,-282.45,1634.74);
	cCsI[5]->SetPoint(16,-293.016,1520.21);
}

void cut6() {
	cCsI[6] = new TCutG("cutCsI_6",15);
	cCsI[6]->SetVarX(" crystal==6");
	cCsI[6]->SetVarY("dE-tau");
	cCsI[6]->SetTitle("Graph");
	cCsI[6]->SetFillStyle(1000);
	cCsI[6]->SetPoint(0,-274.466,1194.71);
	cCsI[6]->SetPoint(1,-236.939,660.256);
	cCsI[6]->SetPoint(2,-188.041,389.957);
	cCsI[6]->SetPoint(3,-90.2436,260.951);
	cCsI[6]->SetPoint(4,25.7486,273.237);
	cCsI[6]->SetPoint(5,172.444,267.094);
	cCsI[6]->SetPoint(6,165.621,420.673);
	cCsI[6]->SetPoint(7,98.5279,451.389);
	cCsI[6]->SetPoint(8,9.82808,518.964);
	cCsI[6]->SetPoint(9,-69.7744,574.252);
	cCsI[6]->SetPoint(10,-138.005,715.545);
	cCsI[6]->SetPoint(11,-191.452,979.701);
	cCsI[6]->SetPoint(12,-213.059,1207);
	cCsI[6]->SetPoint(13,-250.586,1299.15);
	cCsI[6]->SetPoint(14,-274.466,1194.71);
}

void cut7() {
	cCsI[7] = new TCutG("cutCsI_7",20);
	cCsI[7]->SetVarX(" crystal==7");
	cCsI[7]->SetVarY("dE-tau");
	cCsI[7]->SetTitle("Graph");
	cCsI[7]->SetFillStyle(1000);
	cCsI[7]->SetPoint(0,-300.394,1891.54);
	cCsI[7]->SetPoint(1,-282.772,1307.4);
	cCsI[7]->SetPoint(2,-247.529,658.365);
	cCsI[7]->SetPoint(3,-193.562,413.173);
	cCsI[7]->SetPoint(4,-126.379,276.154);
	cCsI[7]->SetPoint(5,-11.8374,276.154);
	cCsI[7]->SetPoint(6,131.34,247.308);
	cCsI[7]->SetPoint(7,201.827,312.212);
	cCsI[7]->SetPoint(8,177.597,456.442);
	cCsI[7]->SetPoint(9,79.5756,492.5);
	cCsI[7]->SetPoint(10,-3.0265,528.558);
	cCsI[7]->SetPoint(11,-91.1354,643.942);
	cCsI[7]->SetPoint(12,-167.129,795.385);
	cCsI[7]->SetPoint(13,-203.474,1062.21);
	cCsI[7]->SetPoint(14,-233.211,1430);
	cCsI[7]->SetPoint(15,-250.833,1920.38);
	cCsI[7]->SetPoint(16,-267.353,2345.87);
	cCsI[7]->SetPoint(17,-290.482,2468.46);
	cCsI[7]->SetPoint(18,-297.09,2223.27);
	cCsI[7]->SetPoint(19,-300.394,1891.54);
}

void cut8() {

	cCsI[8] = new TCutG("cutCsI_8",20);
	cCsI[8]->SetVarX("crystal==8");
	cCsI[8]->SetVarY("dE-tau");
	cCsI[8]->SetTitle("Graph");
	cCsI[8]->SetFillStyle(1000);
	cCsI[8]->SetPoint(0,-263.981,1088.92);
	cCsI[8]->SetPoint(1,-242.287,794.759);
	cCsI[8]->SetPoint(2,-218.285,599.368);
	cCsI[8]->SetPoint(3,-171.665,440.479);
	cCsI[8]->SetPoint(4,-119.507,341.71);
	cCsI[8]->SetPoint(5,-40.116,288.031);
	cCsI[8]->SetPoint(6,38.8136,270.853);
	cCsI[8]->SetPoint(7,120.974,279.442);
	cCsI[8]->SetPoint(8,151.9,283.736);
	cCsI[8]->SetPoint(9,144.976,386.8);
	cCsI[8]->SetPoint(10,75.7398,393.241);
	cCsI[8]->SetPoint(11,-7.80564,429.743);
	cCsI[8]->SetPoint(12,-77.5037,496.305);
	cCsI[8]->SetPoint(13,-123.2,584.338);
	cCsI[8]->SetPoint(14,-159.203,691.696);
	cCsI[8]->SetPoint(15,-191.052,848.438);
	cCsI[8]->SetPoint(16,-215.054,1018.06);
	cCsI[8]->SetPoint(17,-229.824,1153.33);
	cCsI[8]->SetPoint(18,-251.98,1187.69);
	cCsI[8]->SetPoint(19,-263.981,1088.92);

}

void cut10() {
	cCsI[10] = new TCutG("cutCsI_10",20);
	cCsI[10]->SetVarX(" crystal==10");
	cCsI[10]->SetVarY("dE-tau");
	cCsI[10]->SetTitle("Graph");
	cCsI[10]->SetFillStyle(1000);
	cCsI[10]->SetPoint(0,-286.408,1327.4);
	cCsI[10]->SetPoint(1,-264.148,893.75);
	cCsI[10]->SetPoint(2,-242.899,655.769);
	cCsI[10]->SetPoint(3,-200.403,428.365);
	cCsI[10]->SetPoint(4,-116.422,259.135);
	cCsI[10]->SetPoint(5,-26.37,243.269);
	cCsI[10]->SetPoint(6,120.344,253.846);
	cCsI[10]->SetPoint(7,156.769,296.154);
	cCsI[10]->SetPoint(8,149.687,401.923);
	cCsI[10]->SetPoint(9,103.143,444.231);
	cCsI[10]->SetPoint(10,15.1146,428.365);
	cCsI[10]->SetPoint(11,-64.8191,523.558);
	cCsI[10]->SetPoint(12,-106.304,565.865);
	cCsI[10]->SetPoint(13,-145.765,687.5);
	cCsI[10]->SetPoint(14,-187.249,840.865);
	cCsI[10]->SetPoint(15,-214.568,1052.4);
	cCsI[10]->SetPoint(16,-235.817,1311.54);
	cCsI[10]->SetPoint(17,-243.911,1528.37);
	cCsI[10]->SetPoint(18,-277.301,1496.63);
	cCsI[10]->SetPoint(19,-286.408,1327.4);
}

void cut11() {
	cCsI[11] = new TCutG("cutCsI_11",24);
	cCsI[11]->SetVarX(" crystal==11");
	cCsI[11]->SetVarY("dE-tau");
	cCsI[11]->SetTitle("Graph");
	cCsI[11]->SetFillStyle(1000);
	cCsI[11]->SetPoint(0,-293.456,1640.56);
	cCsI[11]->SetPoint(1,-282.98,1233.72);
	cCsI[11]->SetPoint(2,-259.932,839.594);
	cCsI[11]->SetPoint(3,-228.503,572.607);
	cCsI[11]->SetPoint(4,-169.835,388.259);
	cCsI[11]->SetPoint(5,-82.8814,311.976);
	cCsI[11]->SetPoint(6,36.5491,286.549);
	cCsI[11]->SetPoint(7,141.313,280.192);
	cCsI[11]->SetPoint(8,157.027,267.479);
	cCsI[11]->SetPoint(9,155.98,515.395);
	cCsI[11]->SetPoint(10,82.6451,470.897);
	cCsI[11]->SetPoint(11,9.31053,470.897);
	cCsI[11]->SetPoint(12,-53.5476,502.682);
	cCsI[11]->SetPoint(13,-93.3578,547.179);
	cCsI[11]->SetPoint(14,-133.168,617.105);
	cCsI[11]->SetPoint(15,-176.121,788.739);
	cCsI[11]->SetPoint(16,-210.693,966.731);
	cCsI[11]->SetPoint(17,-231.646,1195.58);
	cCsI[11]->SetPoint(18,-244.217,1494.35);
	cCsI[11]->SetPoint(19,-256.789,1837.62);
	cCsI[11]->SetPoint(20,-264.122,2009.25);
	cCsI[11]->SetPoint(21,-290.313,1990.18);
	cCsI[11]->SetPoint(22,-296.599,1786.76);
	cCsI[11]->SetPoint(23,-293.456,1640.56);
}

void cut12() {

	cCsI[12] = new TCutG("cutCsI_12",20);
	cCsI[12]->SetVarX("crystal==12");
	cCsI[12]->SetVarY("dE-tau");
	cCsI[12]->SetTitle("Graph");
	cCsI[12]->SetFillStyle(1000);
	cCsI[12]->SetPoint(0,-294.207,2001.22);
	cCsI[12]->SetPoint(1,-282.315,1450.68);
	cCsI[12]->SetPoint(2,-264.475,939.88);
	cCsI[12]->SetPoint(3,-233.121,593.668);
	cCsI[12]->SetPoint(4,-187.171,412.049);
	cCsI[12]->SetPoint(5,-126.085,332.59);
	cCsI[12]->SetPoint(6,-43.9163,281.51);
	cCsI[12]->SetPoint(7,70.6878,258.807);
	cCsI[12]->SetPoint(8,69.066,497.183);
	cCsI[12]->SetPoint(9,-7.6971,497.183);
	cCsI[12]->SetPoint(10,-96.3531,576.641);
	cCsI[12]->SetPoint(11,-147.168,695.829);
	cCsI[12]->SetPoint(12,-183.387,837.719);
	cCsI[12]->SetPoint(13,-213.66,1104.47);
	cCsI[12]->SetPoint(14,-239.068,1416.63);
	cCsI[12]->SetPoint(15,-255.285,1774.19);
	cCsI[12]->SetPoint(16,-266.638,2114.73);
	cCsI[12]->SetPoint(17,-282.855,2330.4);
	cCsI[12]->SetPoint(18,-298.532,2194.19);
	cCsI[12]->SetPoint(19,-294.207,2001.22);


}

void cut13() {
	cCsI[13] = new TCutG("cutCsI_13",18);
	cCsI[13]->SetVarX(" crystal==13");
	cCsI[13]->SetVarY("dE-tau");
	cCsI[13]->SetTitle("Graph");
	cCsI[13]->SetFillStyle(1000);
	cCsI[13]->SetPoint(0,-290.415,1509.7);
	cCsI[13]->SetPoint(1,-262.257,988.729);
	cCsI[13]->SetPoint(2,-221.585,578.606);
	cCsI[13]->SetPoint(3,-144.413,312.58);
	cCsI[13]->SetPoint(4,-36.9975,301.496);
	cCsI[13]->SetPoint(5,116.304,257.158);
	cCsI[13]->SetPoint(6,200.777,268.242);
	cCsI[13]->SetPoint(7,203.905,501.015);
	cCsI[13]->SetPoint(8,129.862,501.015);
	cCsI[13]->SetPoint(9,28.7033,567.521);
	cCsI[13]->SetPoint(10,-22.3973,622.943);
	cCsI[13]->SetPoint(11,-87.0552,634.028);
	cCsI[13]->SetPoint(12,-140.241,767.041);
	cCsI[13]->SetPoint(13,-196.556,988.729);
	cCsI[13]->SetPoint(14,-227.842,1310.18);
	cCsI[13]->SetPoint(15,-245.571,1675.96);
	cCsI[13]->SetPoint(16,-272.686,1687.05);
	cCsI[13]->SetPoint(17,-290.415,1509.7);
}

void cut14() {

	cCsI[14] = new TCutG("cutCsI_14",20);
	cCsI[14]->SetVarX("crystal==14");
	cCsI[14]->SetVarY("dE-tau");
	cCsI[14]->SetTitle("Graph");
	cCsI[14]->SetFillStyle(1000);
	cCsI[14]->SetPoint(0,-286.367,1592.57);
	cCsI[14]->SetPoint(1,-271.464,1155.55);
	cCsI[14]->SetPoint(2,-242.189,752.585);
	cCsI[14]->SetPoint(3,-213.446,508.534);
	cCsI[14]->SetPoint(4,-158.623,372.319);
	cCsI[14]->SetPoint(5,-113.38,349.617);
	cCsI[14]->SetPoint(6,-53.7658,321.239);
	cCsI[14]->SetPoint(7,-20.2329,309.888);
	cCsI[14]->SetPoint(8,73.9787,270.159);
	cCsI[14]->SetPoint(9,73.4464,485.831);
	cCsI[14]->SetPoint(10,5.8483,474.48);
	cCsI[14]->SetPoint(11,-56.9594,531.236);
	cCsI[14]->SetPoint(12,-120.832,616.37);
	cCsI[14]->SetPoint(13,-166.075,763.936);
	cCsI[14]->SetPoint(14,-199.075,985.284);
	cCsI[14]->SetPoint(15,-227.285,1291.77);
	cCsI[14]->SetPoint(16,-246.447,1615.28);
	cCsI[14]->SetPoint(17,-265.077,1853.65);
	cCsI[14]->SetPoint(18,-280.512,1796.9);
	cCsI[14]->SetPoint(19,-286.367,1592.57);
}

void cut15() {
	cCsI[15] = new TCutG("cutCsI_15",17);
	cCsI[15]->SetVarX(" crystal==15");
	cCsI[15]->SetVarY("dE-tau");
	cCsI[15]->SetTitle("Graph");
	cCsI[15]->SetFillStyle(1000);
	cCsI[15]->SetPoint(0,-279.148,1307.6);
	cCsI[15]->SetPoint(1,-253.852,866.25);
	cCsI[15]->SetPoint(2,-207.308,514.808);
	cCsI[15]->SetPoint(3,-132.434,310.481);
	cCsI[15]->SetPoint(4,-8.99176,261.442);
	cCsI[15]->SetPoint(5,155.935,285.962);
	cCsI[15]->SetPoint(6,156.947,482.115);
	cCsI[15]->SetPoint(7,81.0602,457.596);
	cCsI[15]->SetPoint(8,10.2328,514.808);
	cCsI[15]->SetPoint(9,-62.6182,555.673);
	cCsI[15]->SetPoint(10,-124.339,645.577);
	cCsI[15]->SetPoint(11,-171.895,784.519);
	cCsI[15]->SetPoint(12,-210.344,1037.88);
	cCsI[15]->SetPoint(13,-226.533,1242.21);
	cCsI[15]->SetPoint(14,-236.651,1454.71);
	cCsI[15]->SetPoint(15,-267.006,1495.58);
	cCsI[15]->SetPoint(16,-279.148,1307.6);
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
