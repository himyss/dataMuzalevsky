#if !defined(__CLING__)

#include "TCutG.h"


#endif

TCutG *cLTY[16];

void cutLTY0() {
	cLTY[0] = new TCutG("cutLTY_0",17);
	cLTY[0]->SetVarX(" Y strip==0");
	cLTY[0]->SetVarY("dE-tau");
	cLTY[0]->SetTitle("Graph");
	cLTY[0]->SetFillStyle(1000);
	cLTY[0]->SetPoint(0,-66.0467,89.9828);
	cLTY[0]->SetPoint(1,-55.6549,10.7774);
	cLTY[0]->SetPoint(2,-30.5926,4.41384);
	cLTY[0]->SetPoint(3,1.80514,1.84136);
	cLTY[0]->SetPoint(4,57.4314,1.02899);
	cLTY[0]->SetPoint(5,100.832,1.02899);
	cLTY[0]->SetPoint(6,99.6095,6.17396);
	cLTY[0]->SetPoint(7,48.8735,7.12172);
	cLTY[0]->SetPoint(8,9.14047,11.1835);
	cLTY[0]->SetPoint(9,-8.58658,17.547);
	cLTY[0]->SetPoint(10,-21.4234,24.8583);
	cLTY[0]->SetPoint(11,-26.9249,34.7421);
	cLTY[0]->SetPoint(12,-33.0377,45.3028);
	cLTY[0]->SetPoint(13,-36.7053,65.6119);
	cLTY[0]->SetPoint(14,-47.0971,93.503);
	cLTY[0]->SetPoint(15,-60.5452,93.7738);
	cLTY[0]->SetPoint(16,-66.0467,89.9828);
}

void cutLTY1() {
	cLTY[1] = new TCutG("cutLTY_1",12);
	cLTY[1]->SetVarX(" Y strip==1");
	cLTY[1]->SetVarY("dE-tau");
	cLTY[1]->SetTitle("Graph");
	cLTY[1]->SetFillStyle(1000);
	cLTY[1]->SetPoint(0,-66.107,93.8255);
	cLTY[1]->SetPoint(1,-56.1352,11.5224);
	cLTY[1]->SetPoint(2,-45.257,5.24508);
	cLTY[1]->SetPoint(3,-13.5288,2.03665);
	cLTY[1]->SetPoint(4,154.58,1.15385);
	cLTY[1]->SetPoint(5,221.437,3.39744);
	cLTY[1]->SetPoint(6,9.16429,8.36538);
	cLTY[1]->SetPoint(7,-0.837497,13.4754);
	cLTY[1]->SetPoint(8,-19.8744,24.3561);
	cLTY[1]->SetPoint(9,-34.3787,61.4623);
	cLTY[1]->SetPoint(10,-43.444,96.6154);
	cLTY[1]->SetPoint(11,-66.107,93.8255);
}

void cutLTY2() {
	cLTY[2] = new TCutG("cutLTY_2",12);
	cLTY[2]->SetVarX(" Y strip==2");
	cLTY[2]->SetVarY("dE-tau");
	cLTY[2]->SetTitle("Graph");
	cLTY[2]->SetFillStyle(1000);
	cLTY[2]->SetPoint(0,-64.4984,91.147);
	cLTY[2]->SetPoint(1,-50.6471,10.209);
	cLTY[2]->SetPoint(2,-13.355,3.65357);
	cLTY[2]->SetPoint(3,68.6874,1.51212);
	cLTY[2]->SetPoint(4,136.879,1.42472);
	cLTY[2]->SetPoint(5,124.625,4.0469);
	cLTY[2]->SetPoint(6,36.7228,6.49427);
	cLTY[2]->SetPoint(7,6.8892,8.67942);
	cLTY[2]->SetPoint(8,-6.96213,15.803);
	cLTY[2]->SetPoint(9,-22.9444,45.7396);
	cLTY[2]->SetPoint(10,-35.7303,92.2396);
	cLTY[2]->SetPoint(11,-64.4984,91.147);
}

void cutLTY3() {
	cLTY[3] = new TCutG("cutLTY_3",12);
	cLTY[3]->SetVarX(" Y strip==3");
	cLTY[3]->SetVarY("dE-tau");
	cLTY[3]->SetTitle("Graph");
	cLTY[3]->SetFillStyle(1000);
	cLTY[3]->SetPoint(0,-65.0175,90.3011);
	cLTY[3]->SetPoint(1,-53.582,10.0153);
	cLTY[3]->SetPoint(2,-41.107,4.70829);
	cLTY[3]->SetPoint(3,-14.0777,1.98673);
	cLTY[3]->SetPoint(4,46.2184,0.625957);
	cLTY[3]->SetPoint(5,103.396,1.03419);
	cLTY[3]->SetPoint(6,54.5351,5.2526);
	cLTY[3]->SetPoint(7,9.83283,7.15769);
	cLTY[3]->SetPoint(8,-14.0777,15.1863);
	cLTY[3]->SetPoint(9,-33.8298,93.0227);
	cLTY[3]->SetPoint(10,-59.8195,93.7031);
	cLTY[3]->SetPoint(11,-65.0175,90.3011);
}

void cutLTY4() {
	cLTY[4] = new TCutG("cutLTY_4",13);
	cLTY[4]->SetVarX(" Y strip==4");
	cLTY[4]->SetVarY("dE-tau");
	cLTY[4]->SetTitle("Graph");
	cLTY[4]->SetFillStyle(1000);
	cLTY[4]->SetPoint(0,-64.4486,91.2537);
	cLTY[4]->SetPoint(1,-55.3917,9.74316);
	cLTY[4]->SetPoint(2,-40.2969,5.2526);
	cLTY[4]->SetPoint(3,-4.06937,1.85066);
	cLTY[4]->SetPoint(4,84.4869,1.03419);
	cLTY[4]->SetPoint(5,101.594,0.762034);
	cLTY[4]->SetPoint(6,100.588,4.43613);
	cLTY[4]->SetPoint(7,54.2972,5.52475);
	cLTY[4]->SetPoint(8,21.0887,7.702);
	cLTY[4]->SetPoint(9,-9.10097,13.5533);
	cLTY[4]->SetPoint(10,-25.2021,25.6643);
	cLTY[4]->SetPoint(11,-31.24,93.9752);
	cLTY[4]->SetPoint(12,-64.4486,91.2537);
}

void cutLTY5() {
	cLTY[5] = new TCutG("cutLTY_5",15);
	cLTY[5]->SetVarX(" Y strip==5");
	cLTY[5]->SetVarY("dE-tau");
	cLTY[5]->SetTitle("Graph");
	cLTY[5]->SetFillStyle(1000);
	cLTY[5]->SetPoint(0,-62.4902,91.1711);
	cLTY[5]->SetPoint(1,-55.3426,20.0238);
	cLTY[5]->SetPoint(2,-50.3942,8.90543);
	cLTY[5]->SetPoint(3,-15.2058,2.38405);
	cLTY[5]->SetPoint(4,66.1673,1.79605);
	cLTY[5]->SetPoint(5,117.85,0.994243);
	cLTY[5]->SetPoint(6,113.452,4.4153);
	cLTY[5]->SetPoint(7,71.1157,4.78947);
	cLTY[5]->SetPoint(8,22.7316,6.71382);
	cLTY[5]->SetPoint(9,-8.05818,12.273);
	cLTY[5]->SetPoint(10,-22.3535,22.4827);
	cLTY[5]->SetPoint(11,-29.5011,57.5485);
	cLTY[5]->SetPoint(12,-31.7004,89.1398);
	cLTY[5]->SetPoint(13,-38.848,94.4317);
	cLTY[5]->SetPoint(14,-62.4902,91.1711);
}

void cutLTY6() {
	cLTY[6] = new TCutG("cutLTY_6",12);
	cLTY[6]->SetVarX(" Y strip==6");
	cLTY[6]->SetVarY("dE-tau");
	cLTY[6]->SetTitle("Graph");
	cLTY[6]->SetFillStyle(1000);
	cLTY[6]->SetPoint(0,-65.3728,91.0782);
	cLTY[6]->SetPoint(1,-51.6239,9.66494);
	cLTY[6]->SetPoint(2,-14.127,3.04723);
	cLTY[6]->SetPoint(3,43.3683,1.43127);
	cLTY[6]->SetPoint(4,157.109,1.96992);
	cLTY[6]->SetPoint(5,143.36,4.50928);
	cLTY[6]->SetPoint(6,53.9924,5.04793);
	cLTY[6]->SetPoint(7,16.4955,8.04899);
	cLTY[6]->SetPoint(8,-6.00268,13.4355);
	cLTY[6]->SetPoint(9,-16.6268,26.9018);
	cLTY[6]->SetPoint(10,-30.3757,93.0789);
	cLTY[6]->SetPoint(11,-65.3728,91.0782);
}

void cutLTY7() {
	cLTY[7] = new TCutG("cutLTY_7",14);
	cLTY[7]->SetVarX(" Y strip==7");
	cLTY[7]->SetVarY("dE-tau");
	cLTY[7]->SetTitle("Graph");
	cLTY[7]->SetFillStyle(1000);
	cLTY[7]->SetPoint(0,-60.01,88.6956);
	cLTY[7]->SetPoint(1,-56.018,15.7333);
	cLTY[7]->SetPoint(2,-32.502,4.24248);
	cLTY[7]->SetPoint(3,4.03868,2.50376);
	cLTY[7]->SetPoint(4,146.547,1.6344);
	cLTY[7]->SetPoint(5,140.701,3.85127);
	cLTY[7]->SetPoint(6,45.6951,7.19831);
	cLTY[7]->SetPoint(7,35.7984,7.90645);
	cLTY[7]->SetPoint(8,7.85429,11.4882);
	cLTY[7]->SetPoint(9,-3.32336,21.305);
	cLTY[7]->SetPoint(10,-19.2914,39.3466);
	cLTY[7]->SetPoint(11,-36.0579,91.2161);
	cLTY[7]->SetPoint(12,-53.6228,91.6141);
	cLTY[7]->SetPoint(13,-60.01,88.6956);
}

void cutLTY8() {
	cLTY[8] = new TCutG("cutLTY_8",14);
	cLTY[8]->SetVarX(" Y strip==8");
	cLTY[8]->SetVarY("dE-tau");
	cLTY[8]->SetTitle("Graph");
	cLTY[8]->SetFillStyle(1000);
	cLTY[8]->SetPoint(0,-70.7036,91.3898);
	cLTY[8]->SetPoint(1,-65.7967,28.658);
	cLTY[8]->SetPoint(2,-57.9458,8.79062);
	cLTY[8]->SetPoint(3,-29.6828,4.8312);
	cLTY[8]->SetPoint(4,12.8547,2.27951);
	cLTY[8]->SetPoint(5,125.571,1.17027);
	cLTY[8]->SetPoint(6,128.515,4.16398);
	cLTY[8]->SetPoint(7,57.856,4.57221);
	cLTY[8]->SetPoint(8,20.5639,6.61337);
	cLTY[8]->SetPoint(9,-13.7841,12.0565);
	cLTY[8]->SetPoint(10,-22.6164,22.3984);
	cLTY[8]->SetPoint(11,-32.4301,61.8609);
	cLTY[8]->SetPoint(12,-43.2252,93.2949);
	cLTY[8]->SetPoint(13,-70.7036,91.3898);
}

void cutLTY9() {
	cLTY[9] = new TCutG("cutLTY_9",13);
	cLTY[9]->SetVarX(" Y strip==9");
	cLTY[9]->SetVarY("dE-tau");
	cLTY[9]->SetTitle("Graph");
	cLTY[9]->SetFillStyle(1000);
	cLTY[9]->SetPoint(0,-67.2048,92.2593);
	cLTY[9]->SetPoint(1,-60.277,22.1007);
	cLTY[9]->SetPoint(2,-47.411,5.68928);
	cLTY[9]->SetPoint(3,-5.84415,1.03939);
	cLTY[9]->SetPoint(4,85.2071,1.17615);
	cLTY[9]->SetPoint(5,141.619,1.31291);
	cLTY[9]->SetPoint(6,132.712,4.59519);
	cLTY[9]->SetPoint(7,35.7227,5.27899);
	cLTY[9]->SetPoint(8,1.08366,9.5186);
	cLTY[9]->SetPoint(9,-15.741,18.5449);
	cLTY[9]->SetPoint(10,-21.6791,40.0164);
	cLTY[9]->SetPoint(11,-40.4832,94.174);
	cLTY[9]->SetPoint(12,-67.2048,92.2593);
}

void cutLTY10() {
	cLTY[10] = new TCutG("cutLTY_10",13);
	cLTY[10]->SetVarX(" Y strip==10");
	cLTY[10]->SetVarY("dE-tau");
	cLTY[10]->SetTitle("Graph");
	cLTY[10]->SetFillStyle(1000);
	cLTY[10]->SetPoint(0,-67.1994,90.5481);
	cLTY[10]->SetPoint(1,-57.8472,8.52407);
	cLTY[10]->SetPoint(2,-38.4236,4.1012);
	cLTY[10]->SetPoint(3,-13.2448,1.15263);
	cLTY[10]->SetPoint(4,67.3274,0.750546);
	cLTY[10]->SetPoint(5,104.017,0.750546);
	cLTY[10]->SetPoint(6,105.455,5.17341);
	cLTY[10]->SetPoint(7,53.6589,5.97757);
	cLTY[10]->SetPoint(8,16.2504,8.79212);
	cLTY[10]->SetPoint(9,-6.77021,14.0191);
	cLTY[10]->SetPoint(10,-23.3163,22.7309);
	cLTY[10]->SetPoint(11,-41.3012,92.0224);
	cLTY[10]->SetPoint(12,-67.1994,90.5481);
}

void cutLTY11() {
	cLTY[11] = new TCutG("cutLTY_11",13);
	cLTY[11]->SetVarX(" Y strip==11");
	cLTY[11]->SetVarY("dE-tau");
	cLTY[11]->SetTitle("Graph");
	cLTY[11]->SetFillStyle(1000);
	cLTY[11]->SetPoint(0,-57.2193,92.1225);
	cLTY[11]->SetPoint(1,-50.8196,17.0405);
	cLTY[11]->SetPoint(2,-38.7313,6.23632);
	cLTY[11]->SetPoint(3,-8.15494,2.13348);
	cLTY[11]->SetPoint(4,59.3975,1.44967);
	cLTY[11]->SetPoint(5,100.668,1.88496);
	cLTY[11]->SetPoint(6,99.2544,4.13308);
	cLTY[11]->SetPoint(7,17.2529,8.58609);
	cLTY[11]->SetPoint(8,-10.2882,17.9978);
	cLTY[11]->SetPoint(9,-15.2657,25.5197);
	cLTY[11]->SetPoint(10,-33.0427,66.4114);
	cLTY[11]->SetPoint(11,-36.5981,94.0372);
	cLTY[11]->SetPoint(12,-57.2193,92.1225);
}

void cutLTY12() {
	cLTY[12] = new TCutG("cutLTY_12",13);
	cLTY[12]->SetVarX(" Y strip==12");
	cLTY[12]->SetVarY("dE-tau");
	cLTY[12]->SetTitle("Graph");
	cLTY[12]->SetFillStyle(1000);
	cLTY[12]->SetPoint(0,-64.5384,92.0769);
	cLTY[12]->SetPoint(1,-53.4938,6.8512);
	cLTY[12]->SetPoint(2,-11.3864,0.911651);
	cLTY[12]->SetPoint(3,61.7839,1.18791);
	cLTY[12]->SetPoint(4,130.813,1.46417);
	cLTY[12]->SetPoint(5,128.742,4.08862);
	cLTY[12]->SetPoint(6,63.1645,6.29869);
	cLTY[12]->SetPoint(7,21.0571,9.61378);
	cLTY[12]->SetPoint(8,-14.8378,18.3159);
	cLTY[12]->SetPoint(9,-27.9533,33.6482);
	cLTY[12]->SetPoint(10,-44.5201,94.2869);
	cLTY[12]->SetPoint(11,-54.1841,94.8394);
	cLTY[12]->SetPoint(12,-64.5384,92.0769);
}

void cutLTY13() {
	cLTY[13] = new TCutG("cutLTY_13",17);
	cLTY[13]->SetVarX(" Y strip==13");
	cLTY[13]->SetVarY("dE-tau");
	cLTY[13]->SetTitle("Graph");
	cLTY[13]->SetFillStyle(1000);
	cLTY[13]->SetPoint(0,-63.3184,91.7123);
	cLTY[13]->SetPoint(1,-54.6357,15.9464);
	cLTY[13]->SetPoint(2,-49.3297,8.97155);
	cLTY[13]->SetPoint(3,-37.7528,4.73195);
	cLTY[13]->SetPoint(4,-8.81071,1.85996);
	cLTY[13]->SetPoint(5,80.4275,1.31291);
	cLTY[13]->SetPoint(6,106.958,1.17615);
	cLTY[13]->SetPoint(7,114.606,4.57895);
	cLTY[13]->SetPoint(8,72.7096,6.09956);
	cLTY[13]->SetPoint(9,28.3317,8.42451);
	cLTY[13]->SetPoint(10,-3.50466,11.8435);
	cLTY[13]->SetPoint(11,-27.1407,20.5963);
	cLTY[13]->SetPoint(12,-37.2705,41.5208);
	cLTY[13]->SetPoint(13,-42.0941,79.1302);
	cLTY[13]->SetPoint(14,-44.9884,94.9945);
	cLTY[13]->SetPoint(15,-57.0476,94.9945);
	cLTY[13]->SetPoint(16,-63.3184,91.7123);
}

void cutLTY14() {
	cLTY[14] = new TCutG("cutLTY_14",16);
	cLTY[14]->SetVarX(" Y strip==14");
	cLTY[14]->SetVarY("dE-tau");
	cLTY[14]->SetTitle("Graph");
	cLTY[14]->SetFillStyle(1000);
	cLTY[14]->SetPoint(0,-57.8418,92.9431);
	cLTY[14]->SetPoint(1,-52.752,16.3567);
	cLTY[14]->SetPoint(2,-43.8448,7.46718);
	cLTY[14]->SetPoint(3,-22.2131,3.50109);
	cLTY[14]->SetPoint(4,21.4745,1.17615);
	cLTY[14]->SetPoint(5,101.215,0.765864);
	cLTY[14]->SetPoint(6,101.215,6.23632);
	cLTY[14]->SetPoint(7,59.6482,6.50985);
	cLTY[14]->SetPoint(8,27.4127,9.24508);
	cLTY[14]->SetPoint(9,1.11527,13.6214);
	cLTY[14]->SetPoint(10,-22.2131,23.058);
	cLTY[14]->SetPoint(11,-33.6652,36.7341);
	cLTY[14]->SetPoint(12,-37.9067,52.4617);
	cLTY[14]->SetPoint(13,-43.4207,76.2582);
	cLTY[14]->SetPoint(14,-46.3897,94.8578);
	cLTY[14]->SetPoint(15,-57.8418,92.9431);
}

void cutLTY15() {
	cLTY[15] = new TCutG("cutLTY_15",17);
	cLTY[15]->SetVarX(" Y strip==15");
	cLTY[15]->SetVarY("dE-tau");
	cLTY[15]->SetTitle("Graph");
	cLTY[15]->SetFillStyle(1000);
	cLTY[15]->SetPoint(0,-50.6674,64.4707);
	cLTY[15]->SetPoint(1,-50.2474,26.9229);
	cLTY[15]->SetPoint(2,-40.5876,7.27708);
	cLTY[15]->SetPoint(3,-21.6879,3.55717);
	cLTY[15]->SetPoint(4,24.5114,1.9297);
	cLTY[15]->SetPoint(5,71.9706,1.81346);
	cLTY[15]->SetPoint(6,101.79,1.9297);
	cLTY[15]->SetPoint(7,98.3165,4.92476);
	cLTY[15]->SetPoint(8,41.1217,6.73867);
	cLTY[15]->SetPoint(9,1.41176,10.8807);
	cLTY[15]->SetPoint(10,-15.388,13.5544);
	cLTY[15]->SetPoint(11,-26.7278,19.483);
	cLTY[15]->SetPoint(12,-35.1277,31.224);
	cLTY[15]->SetPoint(13,-36.8076,43.7787);
	cLTY[15]->SetPoint(14,-38.9076,67.0282);
	cLTY[15]->SetPoint(15,-47.7275,67.6094);
	cLTY[15]->SetPoint(16,-50.6674,64.4707);
}


void cutsLTY() {

	cutLTY0();
	cutLTY1();
	cutLTY2();
	cutLTY3();
	cutLTY4();
	cutLTY5();
	cutLTY6();
	cutLTY7();
	cutLTY8();
	cutLTY9();
	cutLTY10();
	cutLTY11();
	cutLTY12();
	cutLTY13();
	cutLTY14();
	cutLTY15();

	TString var;
	//second layer
	TString LTY = "ERQTelescopeSiDigi_Left_telescope_DoubleSi_DSD_L_XY_0_Y";

	for (Int_t i = 0; i < 16; i++) {
		//		if (i==9) continue;
		//		cutName.Form("cutCsI_%d", i);
		//		cCsI[i] = (TCutG*)fCuts->Get(cutName);
		cLTY[i]->SetLineColor(kRed);
		cLTY[i]->SetLineWidth(1);

		//repair cuts variable
		var.Form("%s.fEdep*1000", LTY.Data());
		cLTY[i]->SetVarY(var);
		var.Form("%s.fTime - BeamDetToFDigi2.fTime/2.", LTY.Data());
		cLTY[i]->SetVarX(var);

	}
}
