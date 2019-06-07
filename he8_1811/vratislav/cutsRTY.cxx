#if !defined(__CLING__)

#include "TCutG.h"


#endif

TCutG *cRTY[16];

void cutRTY0() {
	cRTY[0] = new TCutG("cutRTY_0",17);
	cRTY[0]->SetVarX(" Y strip==0");
	cRTY[0]->SetVarY("dE-tau");
	cRTY[0]->SetTitle("Graph");
	cRTY[0]->SetFillStyle(1000);
	cRTY[0]->SetPoint(0,-66.0467,89.9828);
	cRTY[0]->SetPoint(1,-55.6549,10.7774);
	cRTY[0]->SetPoint(2,-30.5926,4.41384);
	cRTY[0]->SetPoint(3,1.80514,1.84136);
	cRTY[0]->SetPoint(4,57.4314,1.02899);
	cRTY[0]->SetPoint(5,100.832,1.02899);
	cRTY[0]->SetPoint(6,99.6095,6.17396);
	cRTY[0]->SetPoint(7,48.8735,7.12172);
	cRTY[0]->SetPoint(8,9.14047,11.1835);
	cRTY[0]->SetPoint(9,-8.58658,17.547);
	cRTY[0]->SetPoint(10,-21.4234,24.8583);
	cRTY[0]->SetPoint(11,-26.9249,34.7421);
	cRTY[0]->SetPoint(12,-33.0377,45.3028);
	cRTY[0]->SetPoint(13,-36.7053,65.6119);
	cRTY[0]->SetPoint(14,-47.0971,93.503);
	cRTY[0]->SetPoint(15,-60.5452,93.7738);
	cRTY[0]->SetPoint(16,-66.0467,89.9828);
}

void cutRTY1() {
	cRTY[1] = new TCutG("cutRTY_1",12);
	cRTY[1]->SetVarX(" Y strip==1");
	cRTY[1]->SetVarY("dE-tau");
	cRTY[1]->SetTitle("Graph");
	cRTY[1]->SetFillStyle(1000);
	cRTY[1]->SetPoint(0,-66.107,93.8255);
	cRTY[1]->SetPoint(1,-56.1352,11.5224);
	cRTY[1]->SetPoint(2,-45.257,5.24508);
	cRTY[1]->SetPoint(3,-13.5288,2.03665);
	cRTY[1]->SetPoint(4,33.6103,0.502187);
	cRTY[1]->SetPoint(5,62.6189,1.06017);
	cRTY[1]->SetPoint(6,15.4799,8.03501);
	cRTY[1]->SetPoint(7,-0.837497,13.4754);
	cRTY[1]->SetPoint(8,-19.8744,24.3561);
	cRTY[1]->SetPoint(9,-34.3787,61.4623);
	cRTY[1]->SetPoint(10,-43.444,96.6154);
	cRTY[1]->SetPoint(11,-66.107,93.8255);
}

void cutRTY2() {
	cRTY[2] = new TCutG("cutRTY_2",12);
	cRTY[2]->SetVarX(" Y strip==2");
	cRTY[2]->SetVarY("dE-tau");
	cRTY[2]->SetTitle("Graph");
	cRTY[2]->SetFillStyle(1000);
	cRTY[2]->SetPoint(0,-74.5135,91.7123);
	cRTY[2]->SetPoint(1,-60.5414,10.6127);
	cRTY[2]->SetPoint(2,-45.6961,5.27899);
	cRTY[2]->SetPoint(3,-22.1183,2.27024);
	cRTY[2]->SetPoint(4,24.1642,1.03939);
	cRTY[2]->SetPoint(5,61.7141,1.31291);
	cRTY[2]->SetPoint(6,34.6432,5.9628);
	cRTY[2]->SetPoint(7,-2.90669,9.10831);
	cRTY[2]->SetPoint(8,-16.8787,16.2199);
	cRTY[2]->SetPoint(9,-32.5973,46.3074);
	cRTY[2]->SetPoint(10,-45.6961,92.8063);
	cRTY[2]->SetPoint(11,-74.5135,91.7123);
}

void cutRTY3() {
	cRTY[3] = new TCutG("cutRTY_3",12);
	cRTY[3]->SetVarX(" Y strip==3");
	cRTY[3]->SetVarY("dE-tau");
	cRTY[3]->SetTitle("Graph");
	cRTY[3]->SetFillStyle(1000);
	cRTY[3]->SetPoint(0,-65.0175,90.3011);
	cRTY[3]->SetPoint(1,-53.582,10.0153);
	cRTY[3]->SetPoint(2,-41.107,4.70829);
	cRTY[3]->SetPoint(3,-14.0777,1.98673);
	cRTY[3]->SetPoint(4,46.2184,0.625957);
	cRTY[3]->SetPoint(5,103.396,1.03419);
	cRTY[3]->SetPoint(6,54.5351,5.2526);
	cRTY[3]->SetPoint(7,9.83283,7.15769);
	cRTY[3]->SetPoint(8,-14.0777,15.1863);
	cRTY[3]->SetPoint(9,-33.8298,93.0227);
	cRTY[3]->SetPoint(10,-59.8195,93.7031);
	cRTY[3]->SetPoint(11,-65.0175,90.3011);
}

void cutRTY4() {
	cRTY[4] = new TCutG("cutRTY_4",13);
	cRTY[4]->SetVarX(" Y strip==4");
	cRTY[4]->SetVarY("dE-tau");
	cRTY[4]->SetTitle("Graph");
	cRTY[4]->SetFillStyle(1000);
	cRTY[4]->SetPoint(0,-64.4486,91.2537);
	cRTY[4]->SetPoint(1,-55.3917,9.74316);
	cRTY[4]->SetPoint(2,-40.2969,5.2526);
	cRTY[4]->SetPoint(3,-4.06937,1.85066);
	cRTY[4]->SetPoint(4,84.4869,1.03419);
	cRTY[4]->SetPoint(5,101.594,0.762034);
	cRTY[4]->SetPoint(6,100.588,4.43613);
	cRTY[4]->SetPoint(7,54.2972,5.52475);
	cRTY[4]->SetPoint(8,21.0887,7.702);
	cRTY[4]->SetPoint(9,-9.10097,13.5533);
	cRTY[4]->SetPoint(10,-25.2021,25.6643);
	cRTY[4]->SetPoint(11,-31.24,93.9752);
	cRTY[4]->SetPoint(12,-64.4486,91.2537);
}

void cutRTY5() {
	cRTY[5] = new TCutG("cutRTY_5",15);
	cRTY[5]->SetVarX(" Y strip==5");
	cRTY[5]->SetVarY("dE-tau");
	cRTY[5]->SetTitle("Graph");
	cRTY[5]->SetFillStyle(1000);
	cRTY[5]->SetPoint(0,-65.7119,90.7094);
	cRTY[5]->SetPoint(1,-58.493,19.5408);
	cRTY[5]->SetPoint(2,-53.3367,8.38238);
	cRTY[5]->SetPoint(3,-18.2735,1.85066);
	cRTY[5]->SetPoint(4,63.1969,1.30635);
	cRTY[5]->SetPoint(5,114.76,0.489879);
	cRTY[5]->SetPoint(6,110.635,3.89182);
	cRTY[5]->SetPoint(7,68.3533,4.30005);
	cRTY[5]->SetPoint(8,19.8836,6.20514);
	cRTY[5]->SetPoint(9,-11.0546,11.7843);
	cRTY[5]->SetPoint(10,-25.4924,21.9902);
	cRTY[5]->SetPoint(11,-32.7113,57.0982);
	cRTY[5]->SetPoint(12,-34.7738,88.6682);
	cRTY[5]->SetPoint(13,-41.9927,93.9752);
	cRTY[5]->SetPoint(14,-65.7119,90.7094);
}

void cutRTY6() {
	cRTY[6] = new TCutG("cutRTY_6",12);
	cRTY[6]->SetVarX(" Y strip==6");
	cRTY[6]->SetVarY("dE-tau");
	cRTY[6]->SetTitle("Graph");
	cRTY[6]->SetFillStyle(1000);
	cRTY[6]->SetPoint(0,-77.1881,90.3366);
	cRTY[6]->SetPoint(1,-63.1163,8.83698);
	cRTY[6]->SetPoint(2,-25.5913,2.23619);
	cRTY[6]->SetPoint(3,31.8688,0.619666);
	cRTY[6]->SetPoint(4,145.616,1.15851);
	cRTY[6]->SetPoint(5,131.544,3.718);
	cRTY[6]->SetPoint(6,42.4227,4.25684);
	cRTY[6]->SetPoint(7,4.8977,7.22046);
	cRTY[6]->SetPoint(8,-17.3827,12.6089);
	cRTY[6]->SetPoint(9,-27.9366,26.0799);
	cRTY[6]->SetPoint(10,-42.0085,92.3572);
	cRTY[6]->SetPoint(11,-77.1881,90.3366);
}

void cutRTY7() {
	cRTY[7] = new TCutG("cutRTY_7",14);
	cRTY[7]->SetVarX(" Y strip==7");
	cRTY[7]->SetVarY("dE-tau");
	cRTY[7]->SetTitle("Graph");
	cRTY[7]->SetFillStyle(1000);
	cRTY[7]->SetPoint(0,-60.01,88.6956);
	cRTY[7]->SetPoint(1,-56.018,15.7333);
	cRTY[7]->SetPoint(2,-45.6387,7.90645);
	cRTY[7]->SetPoint(3,-15.2994,2.20213);
	cRTY[7]->SetPoint(4,14.2415,1.40618);
	cRTY[7]->SetPoint(5,72.5249,1.40618);
	cRTY[7]->SetPoint(6,91.6866,1.6715);
	cRTY[7]->SetPoint(7,35.7984,7.90645);
	cRTY[7]->SetPoint(8,7.85429,11.4882);
	cRTY[7]->SetPoint(9,-3.32336,21.305);
	cRTY[7]->SetPoint(10,-19.2914,39.3466);
	cRTY[7]->SetPoint(11,-36.0579,91.2161);
	cRTY[7]->SetPoint(12,-53.6228,91.6141);
	cRTY[7]->SetPoint(13,-60.01,88.6956);
}

void cutRTY8() {
	cRTY[8] = new TCutG("cutRTY_8",14);
	cRTY[8]->SetVarX(" Y strip==8");
	cRTY[8]->SetVarY("dE-tau");
	cRTY[8]->SetTitle("Graph");
	cRTY[8]->SetFillStyle(1000);
	cRTY[8]->SetPoint(0,-70.7036,91.3898);
	cRTY[8]->SetPoint(1,-65.7967,28.658);
	cRTY[8]->SetPoint(2,-57.9458,8.79062);
	cRTY[8]->SetPoint(3,-39.2997,4.0279);
	cRTY[8]->SetPoint(4,3.88057,0.625957);
	cRTY[8]->SetPoint(5,125.571,1.17027);
	cRTY[8]->SetPoint(6,128.515,4.16398);
	cRTY[8]->SetPoint(7,57.856,4.57221);
	cRTY[8]->SetPoint(8,20.5639,6.61337);
	cRTY[8]->SetPoint(9,-13.7841,12.0565);
	cRTY[8]->SetPoint(10,-22.6164,22.3984);
	cRTY[8]->SetPoint(11,-32.4301,61.8609);
	cRTY[8]->SetPoint(12,-43.2252,93.2949);
	cRTY[8]->SetPoint(13,-70.7036,91.3898);
}

void cutRTY9() {
	cRTY[9] = new TCutG("cutRTY_9",13);
	cRTY[9]->SetVarX(" Y strip==9");
	cRTY[9]->SetVarY("dE-tau");
	cRTY[9]->SetTitle("Graph");
	cRTY[9]->SetFillStyle(1000);
	cRTY[9]->SetPoint(0,-67.2048,92.2593);
	cRTY[9]->SetPoint(1,-60.277,22.1007);
	cRTY[9]->SetPoint(2,-47.411,5.68928);
	cRTY[9]->SetPoint(3,-5.84415,1.03939);
	cRTY[9]->SetPoint(4,85.2071,1.17615);
	cRTY[9]->SetPoint(5,141.619,1.31291);
	cRTY[9]->SetPoint(6,132.712,4.59519);
	cRTY[9]->SetPoint(7,35.7227,5.27899);
	cRTY[9]->SetPoint(8,1.08366,9.5186);
	cRTY[9]->SetPoint(9,-15.741,18.5449);
	cRTY[9]->SetPoint(10,-21.6791,40.0164);
	cRTY[9]->SetPoint(11,-40.4832,94.174);
	cRTY[9]->SetPoint(12,-67.2048,92.2593);
}

void cutRTY10() {
	cRTY[10] = new TCutG("cutRTY_10",13);
	cRTY[10]->SetVarX(" Y strip==10");
	cRTY[10]->SetVarY("dE-tau");
	cRTY[10]->SetTitle("Graph");
	cRTY[10]->SetFillStyle(1000);
	cRTY[10]->SetPoint(0,-67.1994,90.5481);
	cRTY[10]->SetPoint(1,-57.8472,8.52407);
	cRTY[10]->SetPoint(2,-38.4236,4.1012);
	cRTY[10]->SetPoint(3,-13.2448,1.15263);
	cRTY[10]->SetPoint(4,67.3274,0.750546);
	cRTY[10]->SetPoint(5,104.017,0.750546);
	cRTY[10]->SetPoint(6,105.455,5.17341);
	cRTY[10]->SetPoint(7,53.6589,5.97757);
	cRTY[10]->SetPoint(8,16.2504,8.79212);
	cRTY[10]->SetPoint(9,-6.77021,14.0191);
	cRTY[10]->SetPoint(10,-23.3163,22.7309);
	cRTY[10]->SetPoint(11,-41.3012,92.0224);
	cRTY[10]->SetPoint(12,-67.1994,90.5481);
}

void cutRTY11() {
	cRTY[11] = new TCutG("cutRTY_11",13);
	cRTY[11]->SetVarX(" Y strip==11");
	cRTY[11]->SetVarY("dE-tau");
	cRTY[11]->SetTitle("Graph");
	cRTY[11]->SetFillStyle(1000);
	cRTY[11]->SetPoint(0,-57.2193,92.1225);
	cRTY[11]->SetPoint(1,-50.8196,17.0405);
	cRTY[11]->SetPoint(2,-38.7313,6.23632);
	cRTY[11]->SetPoint(3,-8.15494,2.13348);
	cRTY[11]->SetPoint(4,59.3975,1.44967);
	cRTY[11]->SetPoint(5,75.7522,1.44967);
	cRTY[11]->SetPoint(6,58.6864,5.41575);
	cRTY[11]->SetPoint(7,16.7328,10.8862);
	cRTY[11]->SetPoint(8,-10.2882,17.9978);
	cRTY[11]->SetPoint(9,-15.2657,25.5197);
	cRTY[11]->SetPoint(10,-33.0427,66.4114);
	cRTY[11]->SetPoint(11,-36.5981,94.0372);
	cRTY[11]->SetPoint(12,-57.2193,92.1225);
}

void cutRTY12() {
	cRTY[12] = new TCutG("cutRTY_12",13);
	cRTY[12]->SetVarX(" Y strip==12");
	cRTY[12]->SetVarY("dE-tau");
	cRTY[12]->SetTitle("Graph");
	cRTY[12]->SetFillStyle(1000);
	cRTY[12]->SetPoint(0,-64.5384,92.0769);
	cRTY[12]->SetPoint(1,-53.4938,6.8512);
	cRTY[12]->SetPoint(2,-11.3864,0.911651);
	cRTY[12]->SetPoint(3,61.7839,1.18791);
	cRTY[12]->SetPoint(4,130.813,1.46417);
	cRTY[12]->SetPoint(5,128.742,4.08862);
	cRTY[12]->SetPoint(6,63.1645,6.29869);
	cRTY[12]->SetPoint(7,21.0571,9.61378);
	cRTY[12]->SetPoint(8,-14.8378,18.3159);
	cRTY[12]->SetPoint(9,-27.9533,33.6482);
	cRTY[12]->SetPoint(10,-44.5201,94.2869);
	cRTY[12]->SetPoint(11,-54.1841,94.8394);
	cRTY[12]->SetPoint(12,-64.5384,92.0769);
}

void cutRTY13() {
	cRTY[13] = new TCutG("cutRTY_13",17);
	cRTY[13]->SetVarX(" Y strip==13");
	cRTY[13]->SetVarY("dE-tau");
	cRTY[13]->SetTitle("Graph");
	cRTY[13]->SetFillStyle(1000);
	cRTY[13]->SetPoint(0,-63.3184,91.7123);
	cRTY[13]->SetPoint(1,-54.6357,15.9464);
	cRTY[13]->SetPoint(2,-49.3297,8.97155);
	cRTY[13]->SetPoint(3,-37.7528,4.73195);
	cRTY[13]->SetPoint(4,-8.81071,1.85996);
	cRTY[13]->SetPoint(5,80.4275,1.31291);
	cRTY[13]->SetPoint(6,106.958,1.17615);
	cRTY[13]->SetPoint(7,107.44,7.05689);
	cRTY[13]->SetPoint(8,72.7096,6.09956);
	cRTY[13]->SetPoint(9,28.3317,8.42451);
	cRTY[13]->SetPoint(10,-3.50466,11.8435);
	cRTY[13]->SetPoint(11,-27.1407,20.5963);
	cRTY[13]->SetPoint(12,-37.2705,41.5208);
	cRTY[13]->SetPoint(13,-42.0941,79.1302);
	cRTY[13]->SetPoint(14,-44.9884,94.9945);
	cRTY[13]->SetPoint(15,-57.0476,94.9945);
	cRTY[13]->SetPoint(16,-63.3184,91.7123);
}

void cutRTY14() {
	cRTY[14] = new TCutG("cutRTY_14",16);
	cRTY[14]->SetVarX(" Y strip==14");
	cRTY[14]->SetVarY("dE-tau");
	cRTY[14]->SetTitle("Graph");
	cRTY[14]->SetFillStyle(1000);
	cRTY[14]->SetPoint(0,-57.8418,92.9431);
	cRTY[14]->SetPoint(1,-52.752,16.3567);
	cRTY[14]->SetPoint(2,-43.8448,7.46718);
	cRTY[14]->SetPoint(3,-22.2131,3.50109);
	cRTY[14]->SetPoint(4,21.4745,1.17615);
	cRTY[14]->SetPoint(5,101.215,0.765864);
	cRTY[14]->SetPoint(6,101.215,6.23632);
	cRTY[14]->SetPoint(7,59.6482,6.50985);
	cRTY[14]->SetPoint(8,27.4127,9.24508);
	cRTY[14]->SetPoint(9,1.11527,13.6214);
	cRTY[14]->SetPoint(10,-22.2131,23.058);
	cRTY[14]->SetPoint(11,-33.6652,36.7341);
	cRTY[14]->SetPoint(12,-37.9067,52.4617);
	cRTY[14]->SetPoint(13,-43.4207,76.2582);
	cRTY[14]->SetPoint(14,-46.3897,94.8578);
	cRTY[14]->SetPoint(15,-57.8418,92.9431);
}

void cutRTY15() {
	cRTY[15] = new TCutG("cutRTY_15",17);
	cRTY[15]->SetVarX(" Y strip==15");
	cRTY[15]->SetVarY("dE-tau");
	cRTY[15]->SetTitle("Graph");
	cRTY[15]->SetFillStyle(1000);
	cRTY[15]->SetPoint(0,-50.6674,64.4707);
	cRTY[15]->SetPoint(1,-50.2474,26.9229);
	cRTY[15]->SetPoint(2,-40.5876,7.27708);
	cRTY[15]->SetPoint(3,-21.6879,3.55717);
	cRTY[15]->SetPoint(4,24.5114,1.9297);
	cRTY[15]->SetPoint(5,71.9706,1.81346);
	cRTY[15]->SetPoint(6,101.79,1.9297);
	cRTY[15]->SetPoint(7,100.95,7.62582);
	cRTY[15]->SetPoint(8,44.2511,8.3233);
	cRTY[15]->SetPoint(9,1.41176,10.8807);
	cRTY[15]->SetPoint(10,-15.388,13.5544);
	cRTY[15]->SetPoint(11,-26.7278,19.483);
	cRTY[15]->SetPoint(12,-35.1277,31.224);
	cRTY[15]->SetPoint(13,-36.8076,43.7787);
	cRTY[15]->SetPoint(14,-38.9076,67.0282);
	cRTY[15]->SetPoint(15,-47.7275,67.6094);
	cRTY[15]->SetPoint(16,-50.6674,64.4707);
}


void cutsRTY() {

	cutRTY0();
	cutRTY1();
	cutRTY2();
	cutRTY3();
	cutRTY4();
	cutRTY5();
	cutRTY6();
	cutRTY7();
	cutRTY8();
	cutRTY9();
	cutRTY10();
	cutRTY11();
	cutRTY12();
	cutRTY13();
	cutRTY14();
	cutRTY15();

	TString var;
	//second layer
	TString RTY = "ERQTelescopeSiDigi_Right_telescope_SingleSi_SSDY_R_Y_0";

	for (Int_t i = 0; i < 16; i++) {
//		if (i==9) continue;
		//		cutName.Form("cutCsI_%d", i);
		//		cCsI[i] = (TCutG*)fCuts->Get(cutName);
		cRTY[i]->SetLineColor(kRed);
		cRTY[i]->SetLineWidth(1);

		//repair cuts variable
		var.Form("%s.fEdep*1000", RTY.Data());
		cRTY[i]->SetVarY(var);
		var.Form("%s.fTime - BeamDetToFDigi2.fTime/2.", RTY.Data());
		cRTY[i]->SetVarX(var);

	}
}
