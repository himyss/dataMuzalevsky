TCutG *ssd20_1_0_cut;
TCutG *ssd20_2_0_cut;
TCutG *ssd20_3_0_cut;
TCutG *ssd20_4_0_cut;

TCutG *ssd1_1_0_cut;
TCutG *ssd1_2_0_cut;
TCutG *ssd1_3_0_cut;
TCutG *ssd1_4_0_cut;

TCutG *ssdv_1_0_cut;
TCutG *ssdv_2_0_cut;
TCutG *ssdv_3_0_cut;
TCutG *ssdv_4_0_cut;

TCutG *dssd_x_cut[32];

TCutG *CsI_cut[16];

// 20um amp-time cuts
void create_ssd20_1(){
   ssd20_1_0_cut = new TCutG("ssd20_1_0_cut",5);
   ssd20_1_0_cut->SetPoint(0,-5,0);
   ssd20_1_0_cut->SetPoint(1,40,0);
   ssd20_1_0_cut->SetPoint(2,40,100);
   ssd20_1_0_cut->SetPoint(3,40,0);
   ssd20_1_0_cut->SetPoint(4,-5,0);
}

void create_ssd20_2(){
   ssd20_2_0_cut = new TCutG("ssd20_2_0_cut",5);
   ssd20_2_0_cut->SetPoint(0,-5,0);
   ssd20_2_0_cut->SetPoint(1,40,0);
   ssd20_2_0_cut->SetPoint(2,40,100);
   ssd20_2_0_cut->SetPoint(3,40,0);
   ssd20_2_0_cut->SetPoint(4,-5,0);
}

void create_ssd20_3(){
   ssd20_3_0_cut = new TCutG("ssd20_3_0_cut",5);
   ssd20_3_0_cut->SetPoint(0,0,0);
   ssd20_3_0_cut->SetPoint(1,40,0);
   ssd20_3_0_cut->SetPoint(2,40,100);
   ssd20_3_0_cut->SetPoint(3,40,0);
   ssd20_3_0_cut->SetPoint(4,0,0);
}

void create_ssd20_4(){
   ssd20_4_0_cut = new TCutG("ssd20_4_0_cut",5);
   ssd20_4_0_cut->SetPoint(0,0,0);
   ssd20_4_0_cut->SetPoint(1,45,0);
   ssd20_4_0_cut->SetPoint(2,45,100);
   ssd20_4_0_cut->SetPoint(3,45,0);
   ssd20_4_0_cut->SetPoint(4,0,0);
}

// 1-mm amp-time cuts
void create_ssd1_1(){
   ssd1_1_0_cut = new TCutG("ssd1_1_0_cut",5);
   ssd1_1_0_cut->SetPoint(0,0,0);
   ssd1_1_0_cut->SetPoint(1,60,0);
   ssd1_1_0_cut->SetPoint(2,60,100);
   ssd1_1_0_cut->SetPoint(3,60,0);
   ssd1_1_0_cut->SetPoint(4,0,0);
}
void create_ssd1_2(){
   ssd1_2_0_cut = new TCutG("ssd1_2_0_cut",5);
   ssd1_2_0_cut->SetPoint(0,0,0);
   ssd1_2_0_cut->SetPoint(1,60,0);
   ssd1_2_0_cut->SetPoint(2,60,100);
   ssd1_2_0_cut->SetPoint(3,60,0);
   ssd1_2_0_cut->SetPoint(4,0,0);
}
void create_ssd1_3(){
   ssd1_3_0_cut = new TCutG("ssd1_3_0_cut",5);
   ssd1_3_0_cut->SetPoint(0,0,0);
   ssd1_3_0_cut->SetPoint(1,60,0);
   ssd1_3_0_cut->SetPoint(2,60,100);
   ssd1_3_0_cut->SetPoint(3,60,0);
   ssd1_3_0_cut->SetPoint(4,0,0);
}
void create_ssd1_4(){
   ssd1_4_0_cut = new TCutG("ssd1_4_0_cut",5);
   ssd1_4_0_cut->SetPoint(0,-100,0);
   ssd1_4_0_cut->SetPoint(1,200,0);
   ssd1_4_0_cut->SetPoint(2,200,100);
   ssd1_4_0_cut->SetPoint(3,200,0);
   ssd1_4_0_cut->SetPoint(4,-100,0);
}

// veto amp-time cuts
void create_ssdv_1(){
   ssdv_1_0_cut = new TCutG("ssdv_1_0_cut",5);
   ssdv_1_0_cut->SetPoint(0,0,0);
   ssdv_1_0_cut->SetPoint(1,60,0);
   ssdv_1_0_cut->SetPoint(2,60,100);
   ssdv_1_0_cut->SetPoint(3,60,0);
   ssdv_1_0_cut->SetPoint(4,0,0);
}
void create_ssdv_2(){
   ssdv_2_0_cut = new TCutG("ssdv_2_0_cut",5);
   ssdv_2_0_cut->SetPoint(0,0,0);
   ssdv_2_0_cut->SetPoint(1,60,0);
   ssdv_2_0_cut->SetPoint(2,60,100);
   ssdv_2_0_cut->SetPoint(3,60,0);
   ssdv_2_0_cut->SetPoint(4,0,0);
}
void create_ssdv_3(){
   ssdv_3_0_cut = new TCutG("ssdv_3_0_cut",5);
   ssdv_3_0_cut->SetPoint(0,0,0);
   ssdv_3_0_cut->SetPoint(1,60,0);
   ssdv_3_0_cut->SetPoint(2,60,100);
   ssdv_3_0_cut->SetPoint(3,60,0);
   ssdv_3_0_cut->SetPoint(4,0,0);
}
void create_ssdv_4(){
   ssdv_4_0_cut = new TCutG("ssdv_4_0_cut",5);
   ssdv_4_0_cut->SetPoint(0,0,0);
   ssdv_4_0_cut->SetPoint(1,60,0);
   ssdv_4_0_cut->SetPoint(2,60,100);
   ssdv_4_0_cut->SetPoint(3,60,0);
   ssdv_4_0_cut->SetPoint(4,0,0);
}

// DSSD_X 
void create_dssd_x(){

   dssd_x_cut[0] = new TCutG("dssd_x_0_cut",11);
   dssd_x_cut[0]->SetVarX("tDSD_X[0]-tF5 ");
   dssd_x_cut[0]->SetVarY("DSD_X[0]");
   dssd_x_cut[0]->SetTitle("Graph");
   dssd_x_cut[0]->SetFillColor(1);
   dssd_x_cut[0]->SetPoint(0,-175.162,102.749);
   dssd_x_cut[0]->SetPoint(1,-172.596,36.3403);
   dssd_x_cut[0]->SetPoint(2,-170.435,12.7851);
   dssd_x_cut[0]->SetPoint(3,-166.653,4.83875);
   dssd_x_cut[0]->SetPoint(4,-159.225,2.42647);
   dssd_x_cut[0]->SetPoint(5,-151.526,1.43318);
   dssd_x_cut[0]->SetPoint(6,-142.207,1.14938);
   dssd_x_cut[0]->SetPoint(7,-129.646,1.71698);
   dssd_x_cut[0]->SetPoint(8,-119.516,1.43318);
   dssd_x_cut[0]->SetPoint(9,-144.368,102.465);
   dssd_x_cut[0]->SetPoint(10,-175.162,102.749);

   dssd_x_cut[1] = new TCutG("dssd_x_1_cut",15);
   dssd_x_cut[1]->SetVarX("tDSD_X[1]-tF5 ");
   dssd_x_cut[1]->SetVarY("DSD_X[1]");
   dssd_x_cut[1]->SetTitle("Graph");
   dssd_x_cut[1]->SetFillColor(1);
   dssd_x_cut[1]->SetPoint(0,-172.191,84.3782);
   dssd_x_cut[1]->SetPoint(1,-169.76,56.1275);
   dssd_x_cut[1]->SetPoint(2,-168.679,33.2946);
   dssd_x_cut[1]->SetPoint(3,-166.653,14.5898);
   dssd_x_cut[1]->SetPoint(4,-163.277,6.33385);
   dssd_x_cut[1]->SetPoint(5,-159.495,4.01187);
   dssd_x_cut[1]->SetPoint(6,-156.253,2.97988);
   dssd_x_cut[1]->SetPoint(7,-149.77,1.94788);
   dssd_x_cut[1]->SetPoint(8,-137.48,1.94788);
   dssd_x_cut[1]->SetPoint(9,-106.956,1.30289);
   dssd_x_cut[1]->SetPoint(10,-101.148,1.56089);
   dssd_x_cut[1]->SetPoint(11,-147.88,99.3421);
   dssd_x_cut[1]->SetPoint(12,-175.297,99.2131);
   dssd_x_cut[1]->SetPoint(13,-173.676,92.3762);
   dssd_x_cut[1]->SetPoint(14,-172.191,84.3782);

   dssd_x_cut[2] = new TCutG("dssd_x_2_cut",14);
   dssd_x_cut[2]->SetVarX("tDSD_X[2]-tF5 ");
   dssd_x_cut[2]->SetVarY("DSD_X[2]");
   dssd_x_cut[2]->SetTitle("Graph");
   dssd_x_cut[2]->SetFillColor(1);
   dssd_x_cut[2]->SetPoint(0,-176.243,99.4853);
   dssd_x_cut[2]->SetPoint(1,-173.811,50.5302);
   dssd_x_cut[2]->SetPoint(2,-171.38,28.8197);
   dssd_x_cut[2]->SetPoint(3,-169.489,13.9203);
   dssd_x_cut[2]->SetPoint(4,-168.139,8.10242);
   dssd_x_cut[2]->SetPoint(5,-163.952,4.69685);
   dssd_x_cut[2]->SetPoint(6,-158.82,2.71027);
   dssd_x_cut[2]->SetPoint(7,-152.472,1.71698);
   dssd_x_cut[2]->SetPoint(8,-141.667,1.57508);
   dssd_x_cut[2]->SetPoint(9,-129.511,1.57508);
   dssd_x_cut[2]->SetPoint(10,-118.571,1.71698);
   dssd_x_cut[2]->SetPoint(11,-142.612,101.614);
   dssd_x_cut[2]->SetPoint(12,-174.757,101.188);
   dssd_x_cut[2]->SetPoint(13,-176.243,99.4853);

   dssd_x_cut[3] = new TCutG("dssd_x_3_cut",12);
   dssd_x_cut[3]->SetVarX("tDSD_X[3]-tF5 ");
   dssd_x_cut[3]->SetVarY("DSD_X[3]");
   dssd_x_cut[3]->SetTitle("Graph");
   dssd_x_cut[3]->SetFillColor(1);
   dssd_x_cut[3]->SetPoint(0,-177.323,99.911);
   dssd_x_cut[3]->SetPoint(1,-173.676,42.3001);
   dssd_x_cut[3]->SetPoint(2,-172.191,19.88);
   dssd_x_cut[3]->SetPoint(3,-170.165,10.6566);
   dssd_x_cut[3]->SetPoint(4,-167.193,6.68344);
   dssd_x_cut[3]->SetPoint(5,-164.762,4.12926);
   dssd_x_cut[3]->SetPoint(6,-158.279,2.28457);
   dssd_x_cut[3]->SetPoint(7,-149.5,1.85887);
   dssd_x_cut[3]->SetPoint(8,-132.618,1.57508);
   dssd_x_cut[3]->SetPoint(9,-116.41,1.14938);
   dssd_x_cut[3]->SetPoint(10,-142.477,101.756);
   dssd_x_cut[3]->SetPoint(11,-177.323,99.911);

   dssd_x_cut[4] = new TCutG("dssd_x_4_cut",12);
   dssd_x_cut[4]->SetVarX("tDSD_X[4]-tF5 ");
   dssd_x_cut[4]->SetVarY("DSD_X[4]");
   dssd_x_cut[4]->SetTitle("Graph");
   dssd_x_cut[4]->SetFillColor(1);
   dssd_x_cut[4]->SetPoint(0,-173.947,101.472);
   dssd_x_cut[4]->SetPoint(1,-169.76,31.5157);
   dssd_x_cut[4]->SetPoint(2,-166.518,15.3393);
   dssd_x_cut[4]->SetPoint(3,-163.277,7.67673);
   dssd_x_cut[4]->SetPoint(4,-159.36,4.27116);
   dssd_x_cut[4]->SetPoint(5,-154.092,2.14267);
   dssd_x_cut[4]->SetPoint(6,-147.609,1.43318);
   dssd_x_cut[4]->SetPoint(7,-137.885,1.71698);
   dssd_x_cut[4]->SetPoint(8,-120.732,1.29128);
   dssd_x_cut[4]->SetPoint(9,-114.519,1.85887);
   dssd_x_cut[4]->SetPoint(10,-146.664,103.884);
   dssd_x_cut[4]->SetPoint(11,-173.947,101.472);

   dssd_x_cut[5] = new TCutG("dssd_x_5_cut",13);
   dssd_x_cut[5]->SetVarX("tDSD_X[5]-tF5 ");
   dssd_x_cut[5]->SetVarY("DSD_X[5]");
   dssd_x_cut[5]->SetTitle("Graph");
   dssd_x_cut[5]->SetFillColor(1);
   dssd_x_cut[5]->SetPoint(0,-178.404,99.911);
   dssd_x_cut[5]->SetPoint(1,-174.082,34.2118);
   dssd_x_cut[5]->SetPoint(2,-171.515,17.0421);
   dssd_x_cut[5]->SetPoint(3,-168.949,9.52141);
   dssd_x_cut[5]->SetPoint(4,-166.248,7.25103);
   dssd_x_cut[5]->SetPoint(5,-163.277,4.27116);
   dssd_x_cut[5]->SetPoint(6,-158.684,2.56837);
   dssd_x_cut[5]->SetPoint(7,-154.092,1.85887);
   dssd_x_cut[5]->SetPoint(8,-141.532,1.71698);
   dssd_x_cut[5]->SetPoint(9,-128.296,1.43318);
   dssd_x_cut[5]->SetPoint(10,-119.922,1.57508);
   dssd_x_cut[5]->SetPoint(11,-150.446,101.472);
   dssd_x_cut[5]->SetPoint(12,-178.404,99.911);

   dssd_x_cut[6] = new TCutG("dssd_x_6_cut",15);
   dssd_x_cut[6]->SetVarX("tDSD_X[6]-tF5 ");
   dssd_x_cut[6]->SetVarY("DSD_X[6]");
   dssd_x_cut[6]->SetTitle("Graph");
   dssd_x_cut[6]->SetFillColor(1);
   dssd_x_cut[6]->SetPoint(0,-179.349,100.762);
   dssd_x_cut[6]->SetPoint(1,-175.837,44.0028);
   dssd_x_cut[6]->SetPoint(2,-174.217,32.0833);
   dssd_x_cut[6]->SetPoint(3,-172.461,16.4745);
   dssd_x_cut[6]->SetPoint(4,-171.65,11.2242);
   dssd_x_cut[6]->SetPoint(5,-168.949,5.69014);
   dssd_x_cut[6]->SetPoint(6,-164.222,3.13596);
   dssd_x_cut[6]->SetPoint(7,-160.035,2.42647);
   dssd_x_cut[6]->SetPoint(8,-152.066,2.14267);
   dssd_x_cut[6]->SetPoint(9,-144.503,1.57508);
   dssd_x_cut[6]->SetPoint(10,-135.994,1.57508);
   dssd_x_cut[6]->SetPoint(11,-119.652,1.57508);
   dssd_x_cut[6]->SetPoint(12,-149.77,102.181);
   dssd_x_cut[6]->SetPoint(13,-175.162,101.898);
   dssd_x_cut[6]->SetPoint(14,-179.349,100.762);

   dssd_x_cut[7] = new TCutG("dssd_x_7_cut",15);
   dssd_x_cut[7]->SetVarX("tDSD_X[7]-tF5 ");
   dssd_x_cut[7]->SetVarY("DSD_X[7]");
   dssd_x_cut[7]->SetTitle("Graph");
   dssd_x_cut[7]->SetFillColor(1);
   dssd_x_cut[7]->SetPoint(0,-180.429,101.046);
   dssd_x_cut[7]->SetPoint(1,-178.269,60.1793);
   dssd_x_cut[7]->SetPoint(2,-174.217,28.2521);
   dssd_x_cut[7]->SetPoint(3,-172.326,14.4879);
   dssd_x_cut[7]->SetPoint(4,-170.3,9.52141);
   dssd_x_cut[7]->SetPoint(5,-167.058,5.26445);
   dssd_x_cut[7]->SetPoint(6,-164.627,3.70356);
   dssd_x_cut[7]->SetPoint(7,-161.926,2.28457);
   dssd_x_cut[7]->SetPoint(8,-156.253,2.14267);
   dssd_x_cut[7]->SetPoint(9,-138.695,1.71698);
   dssd_x_cut[7]->SetPoint(10,-128.971,2.28457);
   dssd_x_cut[7]->SetPoint(11,-125.054,8.24432);
   dssd_x_cut[7]->SetPoint(12,-133.968,53.5101);
   dssd_x_cut[7]->SetPoint(13,-154.363,102.749);
   dssd_x_cut[7]->SetPoint(14,-180.429,101.046);

   dssd_x_cut[8] = new TCutG("dssd_x_8_cut",12);
   dssd_x_cut[8]->SetVarX("tDSD_X[8]-tF5 ");
   dssd_x_cut[8]->SetVarY("DSD_X[8]");
   dssd_x_cut[8]->SetTitle("Graph");
   dssd_x_cut[8]->SetFillColor(1);
   dssd_x_cut[8]->SetPoint(0,-175.702,100.904);
   dssd_x_cut[8]->SetPoint(1,-174.082,58.3346);
   dssd_x_cut[8]->SetPoint(2,-171.245,29.9548);
   dssd_x_cut[8]->SetPoint(3,-168.949,15.3393);
   dssd_x_cut[8]->SetPoint(4,-167.193,9.66331);
   dssd_x_cut[8]->SetPoint(5,-163.142,4.41305);
   dssd_x_cut[8]->SetPoint(6,-157.064,2.28457);
   dssd_x_cut[8]->SetPoint(7,-145.043,1.85887);
   dssd_x_cut[8]->SetPoint(8,-132.482,1.85887);
   dssd_x_cut[8]->SetPoint(9,-141.397,79.3357);
   dssd_x_cut[8]->SetPoint(10,-153.687,101.188);
   dssd_x_cut[8]->SetPoint(11,-175.702,100.904);

   dssd_x_cut[9] = new TCutG("dssd_x_9_cut",12);
   dssd_x_cut[9]->SetVarX("tDSD_X[9]-tF5 ");
   dssd_x_cut[9]->SetVarY("DSD_X[9]");
   dssd_x_cut[9]->SetTitle("Graph");
   dssd_x_cut[9]->SetFillColor(1);
   dssd_x_cut[9]->SetPoint(0,-181.24,101.188);
   dssd_x_cut[9]->SetPoint(1,-179.079,53.652);
   dssd_x_cut[9]->SetPoint(2,-177.053,29.2454);
   dssd_x_cut[9]->SetPoint(3,-173.136,11.3661);
   dssd_x_cut[9]->SetPoint(4,-168.679,4.69685);
   dssd_x_cut[9]->SetPoint(5,-165.167,2.99407);
   dssd_x_cut[9]->SetPoint(6,-157.874,1.85887);
   dssd_x_cut[9]->SetPoint(7,-140.046,2.14267);
   dssd_x_cut[9]->SetPoint(8,-137.345,2.28457);
   dssd_x_cut[9]->SetPoint(9,-152.472,102.465);
   dssd_x_cut[9]->SetPoint(10,-175.972,103.175);
   dssd_x_cut[9]->SetPoint(11,-181.24,101.188);

   dssd_x_cut[10] = new TCutG("dssd_x_10_cut",10);
   dssd_x_cut[10]->SetVarX("tDSD_X[10]-tF5 ");
   dssd_x_cut[10]->SetVarY("DSD_X[10]");
   dssd_x_cut[10]->SetTitle("Graph");
   dssd_x_cut[10]->SetFillColor(1);
   dssd_x_cut[10]->SetPoint(0,-169.489,101.33);
   dssd_x_cut[10]->SetPoint(1,-165.032,41.8744);
   dssd_x_cut[10]->SetPoint(2,-162.736,16.7583);
   dssd_x_cut[10]->SetPoint(3,-159.225,6.68344);
   dssd_x_cut[10]->SetPoint(4,-152.472,3.27786);
   dssd_x_cut[10]->SetPoint(5,-144.638,2.56837);
   dssd_x_cut[10]->SetPoint(6,-130.592,2.56837);
   dssd_x_cut[10]->SetPoint(7,-143.963,103.6);
   dssd_x_cut[10]->SetPoint(8,-167.058,102.749);
   dssd_x_cut[10]->SetPoint(9,-169.489,101.33);

   dssd_x_cut[11] = new TCutG("dssd_x_11_cut",11);
   dssd_x_cut[11]->SetVarX("tDSD_X[11]-tF5 ");
   dssd_x_cut[11]->SetVarY("DSD_X[11]");
   dssd_x_cut[11]->SetTitle("Graph");
   dssd_x_cut[11]->SetFillColor(1);
   dssd_x_cut[11]->SetPoint(0,-177.728,100.195);
   dssd_x_cut[11]->SetPoint(1,-175.162,51.9492);
   dssd_x_cut[11]->SetPoint(2,-172.191,20.1638);
   dssd_x_cut[11]->SetPoint(3,-170.84,13.6365);
   dssd_x_cut[11]->SetPoint(4,-168.004,8.67002);
   dssd_x_cut[11]->SetPoint(5,-163.952,4.12926);
   dssd_x_cut[11]->SetPoint(6,-159.225,3.13596);
   dssd_x_cut[11]->SetPoint(7,-150.446,2.99407);
   dssd_x_cut[11]->SetPoint(8,-143.558,3.13596);
   dssd_x_cut[11]->SetPoint(9,-151.391,101.33);
   dssd_x_cut[11]->SetPoint(10,-177.728,100.195);

   dssd_x_cut[12] = new TCutG("dssd_x_12_cut",12);
   dssd_x_cut[12]->SetVarX("tDSD_X[12]-tF5 ");
   dssd_x_cut[12]->SetVarY("DSD_X[12]");
   dssd_x_cut[12]->SetTitle("Graph");
   dssd_x_cut[12]->SetFillColor(1);
   dssd_x_cut[12]->SetPoint(0,-176.783,100.337);
   dssd_x_cut[12]->SetPoint(1,-174.757,47.2665);
   dssd_x_cut[12]->SetPoint(2,-172.866,22.0085);
   dssd_x_cut[12]->SetPoint(3,-169.354,12.0756);
   dssd_x_cut[12]->SetPoint(4,-167.328,6.39964);
   dssd_x_cut[12]->SetPoint(5,-162.601,3.70356);
   dssd_x_cut[12]->SetPoint(6,-160.17,3.27786);
   dssd_x_cut[12]->SetPoint(7,-148.825,2.99407);
   dssd_x_cut[12]->SetPoint(8,-145.719,3.13596);
   dssd_x_cut[12]->SetPoint(9,-157.334,101.898);
   dssd_x_cut[12]->SetPoint(10,-171.786,100.762);
   dssd_x_cut[12]->SetPoint(11,-176.783,100.337);

   dssd_x_cut[13] = new TCutG("dssd_x_13_cut",11);
   dssd_x_cut[13]->SetVarX("tDSD_X[13]-tF5 ");
   dssd_x_cut[13]->SetVarY("DSD_X[13]");
   dssd_x_cut[13]->SetTitle("Graph");
   dssd_x_cut[13]->SetFillColor(1);
   dssd_x_cut[13]->SetPoint(0,-178.133,99.4853);
   dssd_x_cut[13]->SetPoint(1,-175.027,57.3413);
   dssd_x_cut[13]->SetPoint(2,-173.406,30.3805);
   dssd_x_cut[13]->SetPoint(3,-171.65,13.2108);
   dssd_x_cut[13]->SetPoint(4,-169.625,8.67002);
   dssd_x_cut[13]->SetPoint(5,-163.952,5.40635);
   dssd_x_cut[13]->SetPoint(6,-158.414,3.27786);
   dssd_x_cut[13]->SetPoint(7,-150.311,2.99407);
   dssd_x_cut[13]->SetPoint(8,-143.558,2.99407);
   dssd_x_cut[13]->SetPoint(9,-152.337,99.0596);
   dssd_x_cut[13]->SetPoint(10,-178.133,99.4853);

   dssd_x_cut[14] = new TCutG("dssd_x_14_cut",10);
   dssd_x_cut[14]->SetVarX("tDSD_X[14]-tF5 ");
   dssd_x_cut[14]->SetVarY("DSD_X[14]");
   dssd_x_cut[14]->SetTitle("Graph");
   dssd_x_cut[14]->SetFillColor(1);
   dssd_x_cut[14]->SetPoint(0,-182.455,101.188);
   dssd_x_cut[14]->SetPoint(1,-180.159,55.4966);
   dssd_x_cut[14]->SetPoint(2,-178.674,21.4409);
   dssd_x_cut[14]->SetPoint(3,-175.567,11.7918);
   dssd_x_cut[14]->SetPoint(4,-173.136,6.68344);
   dssd_x_cut[14]->SetPoint(5,-164.897,3.41976);
   dssd_x_cut[14]->SetPoint(6,-157.874,3.13596);
   dssd_x_cut[14]->SetPoint(7,-149.905,2.99407);
   dssd_x_cut[14]->SetPoint(8,-155.038,102.039);
   dssd_x_cut[14]->SetPoint(9,-182.455,101.188);

   dssd_x_cut[15] = new TCutG("dssd_x_15_cut",11);
   dssd_x_cut[15]->SetVarX("tDSD_X[15]-tF5 ");
   dssd_x_cut[15]->SetVarY("DSD_X[15]");
   dssd_x_cut[15]->SetTitle("Graph");
   dssd_x_cut[15]->SetFillColor(1);
   dssd_x_cut[15]->SetPoint(0,-181.78,99.7691);
   dssd_x_cut[15]->SetPoint(1,-178.133,53.652);
   dssd_x_cut[15]->SetPoint(2,-176.783,33.2185);
   dssd_x_cut[15]->SetPoint(3,-175.162,19.88);
   dssd_x_cut[15]->SetPoint(4,-172.191,11.2242);
   dssd_x_cut[15]->SetPoint(5,-166.518,5.97394);
   dssd_x_cut[15]->SetPoint(6,-160.575,3.56166);
   dssd_x_cut[15]->SetPoint(7,-151.121,3.27786);
   dssd_x_cut[15]->SetPoint(8,-143.422,3.13596);
   dssd_x_cut[15]->SetPoint(9,-158.144,100.62);
   dssd_x_cut[15]->SetPoint(10,-181.78,99.7691);

   dssd_x_cut[16] = new TCutG("dssd_x_16_cut",7);
   dssd_x_cut[16]->SetVarX("tDSD_X[16]-tF5 ");
   dssd_x_cut[16]->SetVarY("DSD_X[16]");
   dssd_x_cut[16]->SetTitle("Graph");
   dssd_x_cut[16]->SetFillColor(1);
   dssd_x_cut[16]->SetPoint(0,-173.627,100.923);
   dssd_x_cut[16]->SetPoint(1,-172.776,48.0979);
   dssd_x_cut[16]->SetPoint(2,-169.94,12.0685);
   dssd_x_cut[16]->SetPoint(3,-163.133,3.12887);
   dssd_x_cut[16]->SetPoint(4,-145.028,3.26432);
   dssd_x_cut[16]->SetPoint(5,-164.976,102.007);
   dssd_x_cut[16]->SetPoint(6,-173.627,100.923);

   dssd_x_cut[17] = new TCutG("dssd_x_17_cut",7);
   dssd_x_cut[17]->SetVarX("tDSD_X[17]-tF5 ");
   dssd_x_cut[17]->SetVarY("DSD_X[17]");
   dssd_x_cut[17]->SetTitle("Graph");
   dssd_x_cut[17]->SetFillColor(1);
   dssd_x_cut[17]->SetPoint(0,-171.736,102.413);
   dssd_x_cut[17]->SetPoint(1,-170.365,44.5762);
   dssd_x_cut[17]->SetPoint(2,-166.111,12.6103);
   dssd_x_cut[17]->SetPoint(3,-159.729,3.39977);
   dssd_x_cut[17]->SetPoint(4,-142.191,3.12887);
   dssd_x_cut[17]->SetPoint(5,-159.824,103.632);
   dssd_x_cut[17]->SetPoint(6,-171.736,102.413);

   dssd_x_cut[18] = new TCutG("dssd_x_18_cut",8);
   dssd_x_cut[18]->SetVarX("tDSD_X[18]-tF5 ");
   dssd_x_cut[18]->SetVarY("DSD_X[18]");
   dssd_x_cut[18]->SetTitle("Graph");
   dssd_x_cut[18]->SetFillColor(1);
   dssd_x_cut[18]->SetPoint(0,-175.14,94.6923);
   dssd_x_cut[18]->SetPoint(1,-175.045,54.1931);
   dssd_x_cut[18]->SetPoint(2,-173.722,33.6049);
   dssd_x_cut[18]->SetPoint(3,-167.86,3.26432);
   dssd_x_cut[18]->SetPoint(4,-144.082,3.12887);
   dssd_x_cut[18]->SetPoint(5,-161.195,100.923);
   dssd_x_cut[18]->SetPoint(6,-174.856,101.194);
   dssd_x_cut[18]->SetPoint(7,-175.14,94.6923);

   dssd_x_cut[19] = new TCutG("dssd_x_19_cut",8);
   dssd_x_cut[19]->SetVarX("tDSD_X[19]-tF5 ");
   dssd_x_cut[19]->SetVarY("DSD_X[19]");
   dssd_x_cut[19]->SetTitle("Graph");
   dssd_x_cut[19]->SetFillColor(1);
   dssd_x_cut[19]->SetPoint(0,-170.224,98.4849);
   dssd_x_cut[19]->SetPoint(1,-169.656,57.7148);
   dssd_x_cut[19]->SetPoint(2,-164.267,12.0685);
   dssd_x_cut[19]->SetPoint(3,-159.351,3.26432);
   dssd_x_cut[19]->SetPoint(4,-140.395,2.58707);
   dssd_x_cut[19]->SetPoint(5,-154.009,99.0267);
   dssd_x_cut[19]->SetPoint(6,-169.042,99.4331);
   dssd_x_cut[19]->SetPoint(7,-170.224,98.4849);

   dssd_x_cut[20] = new TCutG("dssd_x_20_cut",8);
   dssd_x_cut[20]->SetVarX("tDSD_X[20]-tF5 ");
   dssd_x_cut[20]->SetVarY("DSD_X[20]");
   dssd_x_cut[20]->SetTitle("Graph");
   dssd_x_cut[20]->SetFillColor(1);
   dssd_x_cut[20]->SetPoint(0,-173.58,96.1823);
   dssd_x_cut[20]->SetPoint(1,-173.013,47.1498);
   dssd_x_cut[20]->SetPoint(2,-167.245,9.08862);
   dssd_x_cut[20]->SetPoint(3,-162.849,3.12887);
   dssd_x_cut[20]->SetPoint(4,-142.522,2.18073);
   dssd_x_cut[20]->SetPoint(5,-160.155,102.684);
   dssd_x_cut[20]->SetPoint(6,-173.391,102.548);
   dssd_x_cut[20]->SetPoint(7,-173.58,96.1823);

   dssd_x_cut[21] = new TCutG("dssd_x_21_cut",8);
   dssd_x_cut[21]->SetVarX("tDSD_X[21]-tF5 ");
   dssd_x_cut[21]->SetVarY("DSD_X[21]");
   dssd_x_cut[21]->SetTitle("Graph");
   dssd_x_cut[21]->SetFillColor(1);
   dssd_x_cut[21]->SetPoint(0,-175.093,99.9748);
   dssd_x_cut[21]->SetPoint(1,-172.303,49.1815);
   dssd_x_cut[21]->SetPoint(2,-168.522,13.0166);
   dssd_x_cut[21]->SetPoint(3,-162.566,2.85797);
   dssd_x_cut[21]->SetPoint(4,-138.977,1.63893);
   dssd_x_cut[21]->SetPoint(5,-157.602,103.09);
   dssd_x_cut[21]->SetPoint(6,-174.809,101.871);
   dssd_x_cut[21]->SetPoint(7,-175.093,99.9748);

   dssd_x_cut[22] = new TCutG("dssd_x_22_cut",8);
   dssd_x_cut[22]->SetVarX("tDSD_X[22]-tF5 ");
   dssd_x_cut[22]->SetVarY("DSD_X[22]");
   dssd_x_cut[22]->SetTitle("Graph");
   dssd_x_cut[22]->SetFillColor(1);
   dssd_x_cut[22]->SetPoint(0,-175.471,100.652);
   dssd_x_cut[22]->SetPoint(1,-171.264,26.9679);
   dssd_x_cut[22]->SetPoint(2,-168.333,10.1722);
   dssd_x_cut[22]->SetPoint(3,-162.235,2.45162);
   dssd_x_cut[22]->SetPoint(4,-136.991,1.50348);
   dssd_x_cut[22]->SetPoint(5,-159.304,101.736);
   dssd_x_cut[22]->SetPoint(6,-174.762,101.058);
   dssd_x_cut[22]->SetPoint(7,-175.471,100.652);

   dssd_x_cut[23] = new TCutG("dssd_x_23_cut",7);
   dssd_x_cut[23]->SetVarX("tDSD_X[23]-tF5 ");
   dssd_x_cut[23]->SetVarY("DSD_X[23]");
   dssd_x_cut[23]->SetTitle("Graph");
   dssd_x_cut[23]->SetFillColor(1);
   dssd_x_cut[23]->SetPoint(0,-169.656,85.4818);
   dssd_x_cut[23]->SetPoint(1,-163.275,9.22407);
   dssd_x_cut[23]->SetPoint(2,-157.035,3.26432);
   dssd_x_cut[23]->SetPoint(3,-131.366,1.77438);
   dssd_x_cut[23]->SetPoint(4,-151.598,101.329);
   dssd_x_cut[23]->SetPoint(5,-170.602,101.6);
   dssd_x_cut[23]->SetPoint(6,-169.656,85.4818);

   dssd_x_cut[24] = new TCutG("dssd_x_24_cut",8);
   dssd_x_cut[24]->SetVarX("tDSD_X[24]-tF5 ");
   dssd_x_cut[24]->SetVarY("DSD_X[24]");
   dssd_x_cut[24]->SetTitle("Graph");
   dssd_x_cut[24]->SetFillColor(1);
   dssd_x_cut[24]->SetPoint(0,-167.009,95.505);
   dssd_x_cut[24]->SetPoint(1,-162.991,23.988);
   dssd_x_cut[24]->SetPoint(2,-159.209,6.10875);
   dssd_x_cut[24]->SetPoint(3,-154.86,2.72252);
   dssd_x_cut[24]->SetPoint(4,-131.177,1.77438);
   dssd_x_cut[24]->SetPoint(5,-151.126,101.329);
   dssd_x_cut[24]->SetPoint(6,-166.915,101.6);
   dssd_x_cut[24]->SetPoint(7,-167.009,95.505);

   dssd_x_cut[25] = new TCutG("dssd_x_25_cut",9);
   dssd_x_cut[25]->SetVarX("tDSD_X[25]-tF5 ");
   dssd_x_cut[25]->SetVarY("DSD_X[25]");
   dssd_x_cut[25]->SetTitle("Graph");
   dssd_x_cut[25]->SetFillColor(1);
   dssd_x_cut[25]->SetPoint(0,-169.278,99.1622);
   dssd_x_cut[25]->SetPoint(1,-165.496,23.988);
   dssd_x_cut[25]->SetPoint(2,-159.304,4.75426);
   dssd_x_cut[25]->SetPoint(3,-158.027,3.80611);
   dssd_x_cut[25]->SetPoint(4,-154.907,2.72252);
   dssd_x_cut[25]->SetPoint(5,-139.591,1.77438);
   dssd_x_cut[25]->SetPoint(6,-153.915,101.329);
   dssd_x_cut[25]->SetPoint(7,-169.136,101.6);
   dssd_x_cut[25]->SetPoint(8,-169.278,99.1622);

   dssd_x_cut[26] = new TCutG("dssd_x_26_cut",9);
   dssd_x_cut[26]->SetVarX("tDSD_X[26]-tF5 ");
   dssd_x_cut[26]->SetVarY("DSD_X[26]");
   dssd_x_cut[26]->SetTitle("Graph");
   dssd_x_cut[26]->SetFillColor(1);
   dssd_x_cut[26]->SetPoint(0,-170.413,99.1622);
   dssd_x_cut[26]->SetPoint(1,-168.191,43.3572);
   dssd_x_cut[26]->SetPoint(2,-165.733,18.7055);
   dssd_x_cut[26]->SetPoint(3,-162.518,9.63042);
   dssd_x_cut[26]->SetPoint(4,-158.406,4.07701);
   dssd_x_cut[26]->SetPoint(5,-154.387,2.18073);
   dssd_x_cut[26]->SetPoint(6,-137.086,1.77438);
   dssd_x_cut[26]->SetPoint(7,-157.035,100.246);
   dssd_x_cut[26]->SetPoint(8,-170.413,99.1622);

   dssd_x_cut[27] = new TCutG("dssd_x_27_cut",9);
   dssd_x_cut[27]->SetVarX("tDSD_X[27]-tF5 ");
   dssd_x_cut[27]->SetVarY("DSD_X[27]");
   dssd_x_cut[27]->SetTitle("Graph");
   dssd_x_cut[27]->SetFillColor(1);
   dssd_x_cut[27]->SetPoint(0,-167.009,99.8394);
   dssd_x_cut[27]->SetPoint(1,-163.653,42.8154);
   dssd_x_cut[27]->SetPoint(2,-160.864,14.2357);
   dssd_x_cut[27]->SetPoint(3,-156.893,5.1606);
   dssd_x_cut[27]->SetPoint(4,-152.355,2.45162);
   dssd_x_cut[27]->SetPoint(5,-135.621,1.90983);
   dssd_x_cut[27]->SetPoint(6,-153.868,101.6);
   dssd_x_cut[27]->SetPoint(7,-165.685,101.465);
   dssd_x_cut[27]->SetPoint(8,-167.009,99.8394);

   dssd_x_cut[28] = new TCutG("dssd_x_28_cut",8);
   dssd_x_cut[28]->SetVarX("tDSD_X[28]-tF5 ");
   dssd_x_cut[28]->SetVarY("DSD_X[28]");
   dssd_x_cut[28]->SetTitle("Graph");
   dssd_x_cut[28]->SetFillColor(1);
   dssd_x_cut[28]->SetPoint(0,-175.282,100.246);
   dssd_x_cut[28]->SetPoint(1,-171.5,23.3108);
   dssd_x_cut[28]->SetPoint(2,-168.758,10.8495);
   dssd_x_cut[28]->SetPoint(3,-164.787,3.80611);
   dssd_x_cut[28]->SetPoint(4,-158.973,2.18073);
   dssd_x_cut[28]->SetPoint(5,-141.104,1.36803);
   dssd_x_cut[28]->SetPoint(6,-159.304,100.923);
   dssd_x_cut[28]->SetPoint(7,-175.282,100.246);

   dssd_x_cut[29] = new TCutG("dssd_x_29_cut",9);
   dssd_x_cut[29]->SetVarX("tDSD_X[29]-tF5 ");
   dssd_x_cut[29]->SetVarY("DSD_X[29]");
   dssd_x_cut[29]->SetTitle("Graph");
   dssd_x_cut[29]->SetFillColor(1);
   dssd_x_cut[29]->SetPoint(0,-178.26,101.194);
   dssd_x_cut[29]->SetPoint(1,-175.754,46.0662);
   dssd_x_cut[29]->SetPoint(2,-173.154,16.5383);
   dssd_x_cut[29]->SetPoint(3,-169.798,7.46323);
   dssd_x_cut[29]->SetPoint(4,-165.355,3.26432);
   dssd_x_cut[29]->SetPoint(5,-161.336,2.45162);
   dssd_x_cut[29]->SetPoint(6,-149.991,2.04528);
   dssd_x_cut[29]->SetPoint(7,-165.496,102.548);
   dssd_x_cut[29]->SetPoint(8,-178.26,101.194);

   dssd_x_cut[30] = new TCutG("dssd_x_30_cut",9);
   dssd_x_cut[30]->SetVarX("tDSD_X[30]-tF5 ");
   dssd_x_cut[30]->SetVarY("DSD_X[30]");
   dssd_x_cut[30]->SetTitle("Graph");
   dssd_x_cut[30]->SetFillColor(1);
   dssd_x_cut[30]->SetPoint(0,-169.278,99.4331);
   dssd_x_cut[30]->SetPoint(1,-166.064,39.7001);
   dssd_x_cut[30]->SetPoint(2,-163.747,16.6738);
   dssd_x_cut[30]->SetPoint(3,-160.769,7.86958);
   dssd_x_cut[30]->SetPoint(4,-154.86,3.53522);
   dssd_x_cut[30]->SetPoint(5,-146.304,1.90983);
   dssd_x_cut[30]->SetPoint(6,-137.559,1.77438);
   dssd_x_cut[30]->SetPoint(7,-151.315,101.465);
   dssd_x_cut[30]->SetPoint(8,-169.278,99.4331);

   dssd_x_cut[31] = new TCutG("dssd_x_31_cut",9);
   dssd_x_cut[31]->SetVarX("tDSD_X[31]-tF5 ");
   dssd_x_cut[31]->SetVarY("DSD_X[31]");
   dssd_x_cut[31]->SetTitle("Graph");
   dssd_x_cut[31]->SetFillColor(1);
   dssd_x_cut[31]->SetPoint(0,-174.573,99.9748);
   dssd_x_cut[31]->SetPoint(1,-170.885,31.3022);
   dssd_x_cut[31]->SetPoint(2,-168.853,17.351);
   dssd_x_cut[31]->SetPoint(3,-166.253,9.76587);
   dssd_x_cut[31]->SetPoint(4,-163.7,4.75426);
   dssd_x_cut[31]->SetPoint(5,-159.209,2.58707);
   dssd_x_cut[31]->SetPoint(6,-143.515,1.90983);
   dssd_x_cut[31]->SetPoint(7,-154.907,101.465);
   dssd_x_cut[31]->SetPoint(8,-174.573,99.9748);

}

void create_CsI(){

   CsI_cut[0] = new TCutG("csi_0_cut",14);
   CsI_cut[0]->SetVarX("trCsI[0]-tF5 ");
   CsI_cut[0]->SetVarY("arCsI[0]");
   CsI_cut[0]->SetTitle("Graph");
   CsI_cut[0]->SetFillColor(1);
   CsI_cut[0]->SetPoint(0,311.777,4057.66);
   CsI_cut[0]->SetPoint(1,316.099,2400.03);
   CsI_cut[0]->SetPoint(2,327.445,1174.54);
   CsI_cut[0]->SetPoint(3,340.951,548.891);
   CsI_cut[0]->SetPoint(4,368.504,284.443);
   CsI_cut[0]->SetPoint(5,394.435,232.843);
   CsI_cut[0]->SetPoint(6,501.945,239.293);
   CsI_cut[0]->SetPoint(7,500.324,387.642);
   CsI_cut[0]->SetPoint(8,420.908,523.091);
   CsI_cut[0]->SetPoint(9,376.607,742.389);
   CsI_cut[0]->SetPoint(10,359.86,1051.99);
   CsI_cut[0]->SetPoint(11,342.031,2096.88);
   CsI_cut[0]->SetPoint(12,326.364,4044.76);
   CsI_cut[0]->SetPoint(13,311.777,4057.66);

   CsI_cut[1] = new TCutG("csi_1_cut",18);
   CsI_cut[1]->SetVarX("trCsI[1]-tF5 ");
   CsI_cut[1]->SetVarY("arCsI[1]");
   CsI_cut[1]->SetTitle("Graph");
   CsI_cut[1]->SetFillColor(1);
   CsI_cut[1]->SetPoint(0,317.72,4050.42);
   CsI_cut[1]->SetPoint(1,319.341,2736.17);
   CsI_cut[1]->SetPoint(2,323.123,2133.81);
   CsI_cut[1]->SetPoint(3,329.606,1378.12);
   CsI_cut[1]->SetPoint(4,333.928,912.664);
   CsI_cut[1]->SetPoint(5,349.055,545.772);
   CsI_cut[1]->SetPoint(6,376.067,326.732);
   CsI_cut[1]->SetPoint(7,385.251,282.924);
   CsI_cut[1]->SetPoint(8,507.347,288.4);
   CsI_cut[1]->SetPoint(9,505.186,463.632);
   CsI_cut[1]->SetPoint(10,414.425,622.436);
   CsI_cut[1]->SetPoint(11,384.171,792.192);
   CsI_cut[1]->SetPoint(12,373.366,1000.28);
   CsI_cut[1]->SetPoint(13,362.021,1378.12);
   CsI_cut[1]->SetPoint(14,351.216,1860.01);
   CsI_cut[1]->SetPoint(15,343.652,2369.28);
   CsI_cut[1]->SetPoint(16,330.146,4039.46);
   CsI_cut[1]->SetPoint(17,317.72,4050.42);

   CsI_cut[2] = new TCutG("csi_2_cut",14);
   CsI_cut[2]->SetVarX("trCsI[2]-tF5 ");
   CsI_cut[2]->SetVarY("arCsI[2]");
   CsI_cut[2]->SetTitle("Graph");
   CsI_cut[2]->SetFillColor(1);
   CsI_cut[2]->SetPoint(0,320.421,3444.92);
   CsI_cut[2]->SetPoint(1,329.065,1567.98);
   CsI_cut[2]->SetPoint(2,339.87,1064.89);
   CsI_cut[2]->SetPoint(3,352.836,664.99);
   CsI_cut[2]->SetPoint(4,366.883,458.591);
   CsI_cut[2]->SetPoint(5,395.516,323.142);
   CsI_cut[2]->SetPoint(6,432.253,265.093);
   CsI_cut[2]->SetPoint(7,501.945,239.293);
   CsI_cut[2]->SetPoint(8,500.324,406.992);
   CsI_cut[2]->SetPoint(9,430.632,561.79);
   CsI_cut[2]->SetPoint(10,390.113,845.588);
   CsI_cut[2]->SetPoint(11,361.48,1464.78);
   CsI_cut[2]->SetPoint(12,333.387,3419.12);
   CsI_cut[2]->SetPoint(13,320.421,3444.92);

   CsI_cut[3] = new TCutG("csi_3_cut",15);
   CsI_cut[3]->SetVarX("trCsI[3]-tF5 ");
   CsI_cut[3]->SetVarY("arCsI[3]");
   CsI_cut[3]->SetTitle("Graph");
   CsI_cut[3]->SetFillColor(1);
   CsI_cut[3]->SetPoint(0,315.559,4070.56);
   CsI_cut[3]->SetPoint(1,322.042,1735.68);
   CsI_cut[3]->SetPoint(2,329.065,1135.84);
   CsI_cut[3]->SetPoint(3,339.87,568.24);
   CsI_cut[3]->SetPoint(4,366.343,316.692);
   CsI_cut[3]->SetPoint(5,386.872,232.843);
   CsI_cut[3]->SetPoint(6,500.864,239.293);
   CsI_cut[3]->SetPoint(7,498.163,413.442);
   CsI_cut[3]->SetPoint(8,407.401,516.641);
   CsI_cut[3]->SetPoint(9,373.366,768.189);
   CsI_cut[3]->SetPoint(10,358.779,1155.19);
   CsI_cut[3]->SetPoint(11,346.894,1742.13);
   CsI_cut[3]->SetPoint(12,337.169,2967.62);
   CsI_cut[3]->SetPoint(13,329.606,4077.01);
   CsI_cut[3]->SetPoint(14,315.559,4070.56);

   CsI_cut[4] = new TCutG("csi_4_cut",17);
   CsI_cut[4]->SetVarX("trCsI[4]-tF5 ");
   CsI_cut[4]->SetVarY("arCsI[4]");
   CsI_cut[4]->SetTitle("Graph");
   CsI_cut[4]->SetFillColor(1);
   CsI_cut[4]->SetPoint(0,304.754,4089.91);
   CsI_cut[4]->SetPoint(1,308.536,2322.63);
   CsI_cut[4]->SetPoint(2,318.26,1303.53);
   CsI_cut[4]->SetPoint(3,323.663,735.939);
   CsI_cut[4]->SetPoint(4,339.33,510.191);
   CsI_cut[4]->SetPoint(5,381.469,245.743);
   CsI_cut[4]->SetPoint(6,413.344,245.743);
   CsI_cut[4]->SetPoint(7,484.657,252.193);
   CsI_cut[4]->SetPoint(8,483.576,323.142);
   CsI_cut[4]->SetPoint(9,391.194,587.59);
   CsI_cut[4]->SetPoint(10,366.343,813.338);
   CsI_cut[4]->SetPoint(11,353.917,1155.19);
   CsI_cut[4]->SetPoint(12,345.813,1561.53);
   CsI_cut[4]->SetPoint(13,332.847,2999.87);
   CsI_cut[4]->SetPoint(14,324.743,4122.16);
   CsI_cut[4]->SetPoint(15,306.915,4141.51);
   CsI_cut[4]->SetPoint(16,304.754,4089.91);

   CsI_cut[5] = new TCutG("csi_5_cut",14);
   CsI_cut[5]->SetVarX("trCsI[5]-tF5 ");
   CsI_cut[5]->SetVarY("arCsI[5]");
   CsI_cut[5]->SetTitle("Graph");
   CsI_cut[5]->SetFillColor(1);
   CsI_cut[5]->SetPoint(0,298.811,4096.36);
   CsI_cut[5]->SetPoint(1,304.214,2193.63);
   CsI_cut[5]->SetPoint(2,313.938,1090.69);
   CsI_cut[5]->SetPoint(3,322.582,652.09);
   CsI_cut[5]->SetPoint(4,342.572,265.093);
   CsI_cut[5]->SetPoint(5,367.963,232.843);
   CsI_cut[5]->SetPoint(6,465.748,252.193);
   CsI_cut[5]->SetPoint(7,461.426,477.941);
   CsI_cut[5]->SetPoint(8,358.239,755.289);
   CsI_cut[5]->SetPoint(9,339.33,1045.54);
   CsI_cut[5]->SetPoint(10,330.686,1735.68);
   CsI_cut[5]->SetPoint(11,316.64,3896.41);
   CsI_cut[5]->SetPoint(12,315.559,4147.96);
   CsI_cut[5]->SetPoint(13,298.811,4096.36);

   CsI_cut[6] = new TCutG("csi_6_cut",15);
   CsI_cut[6]->SetVarX("trCsI[6]-tF5 ");
   CsI_cut[6]->SetVarY("arCsI[6]");
   CsI_cut[6]->SetTitle("Graph");
   CsI_cut[6]->SetFillColor(1);
   CsI_cut[6]->SetPoint(0,323.123,4044.76);
   CsI_cut[6]->SetPoint(1,325.284,2329.08);
   CsI_cut[6]->SetPoint(2,332.307,1619.58);
   CsI_cut[6]->SetPoint(3,348.514,677.89);
   CsI_cut[6]->SetPoint(4,374.446,303.793);
   CsI_cut[6]->SetPoint(5,406.861,245.743);
   CsI_cut[6]->SetPoint(6,498.703,258.643);
   CsI_cut[6]->SetPoint(7,497.083,574.69);
   CsI_cut[6]->SetPoint(8,389.573,800.439);
   CsI_cut[6]->SetPoint(9,371.745,1064.89);
   CsI_cut[6]->SetPoint(10,352.296,1632.48);
   CsI_cut[6]->SetPoint(11,345.273,2651.57);
   CsI_cut[6]->SetPoint(12,342.031,4077.01);
   CsI_cut[6]->SetPoint(13,325.824,4064.11);
   CsI_cut[6]->SetPoint(14,323.123,4044.76);

   CsI_cut[7] = new TCutG("csi_7_cut",14);
   CsI_cut[7]->SetVarX("trCsI[7]-tF5 ");
   CsI_cut[7]->SetVarY("arCsI[7]");
   CsI_cut[7]->SetTitle("Graph");
   CsI_cut[7]->SetFillColor(1);
   CsI_cut[7]->SetPoint(0,309.076,4070.56);
   CsI_cut[7]->SetPoint(1,312.318,2180.73);
   CsI_cut[7]->SetPoint(2,318.801,1303.53);
   CsI_cut[7]->SetPoint(3,330.686,606.94);
   CsI_cut[7]->SetPoint(4,360.94,284.443);
   CsI_cut[7]->SetPoint(5,388.493,239.293);
   CsI_cut[7]->SetPoint(6,484.117,245.743);
   CsI_cut[7]->SetPoint(7,483.576,355.392);
   CsI_cut[7]->SetPoint(8,394.976,555.341);
   CsI_cut[7]->SetPoint(9,358.239,961.687);
   CsI_cut[7]->SetPoint(10,340.951,1529.28);
   CsI_cut[7]->SetPoint(11,329.606,2445.18);
   CsI_cut[7]->SetPoint(12,322.042,4096.36);
   CsI_cut[7]->SetPoint(13,309.076,4070.56);

   CsI_cut[8] = new TCutG("csi_8_cut",15);
   CsI_cut[8]->SetVarX("trCsI[8]-tF5 ");
   CsI_cut[8]->SetVarY("arCsI[8]");
   CsI_cut[8]->SetTitle("Graph");
   CsI_cut[8]->SetFillColor(1);
   CsI_cut[8]->SetPoint(0,299.892,4102.81);
   CsI_cut[8]->SetPoint(1,302.593,2425.83);
   CsI_cut[8]->SetPoint(2,309.616,1464.78);
   CsI_cut[8]->SetPoint(3,318.801,748.839);
   CsI_cut[8]->SetPoint(4,331.226,394.092);
   CsI_cut[8]->SetPoint(5,347.434,245.743);
   CsI_cut[8]->SetPoint(6,418.206,239.293);
   CsI_cut[8]->SetPoint(7,488.979,232.843);
   CsI_cut[8]->SetPoint(8,488.979,374.742);
   CsI_cut[8]->SetPoint(9,377.147,587.59);
   CsI_cut[8]->SetPoint(10,352.836,884.288);
   CsI_cut[8]->SetPoint(11,330.146,1677.63);
   CsI_cut[8]->SetPoint(12,320.421,2554.82);
   CsI_cut[8]->SetPoint(13,312.318,4102.81);
   CsI_cut[8]->SetPoint(14,299.892,4102.81);

   CsI_cut[9] = new TCutG("csi_9_cut",14);
   CsI_cut[9]->SetVarX("trCsI[9]-tF5 ");
   CsI_cut[9]->SetVarY("arCsI[9]");
   CsI_cut[9]->SetTitle("Graph");
   CsI_cut[9]->SetFillColor(1);
   CsI_cut[9]->SetPoint(0,312.318,4077.01);
   CsI_cut[9]->SetPoint(1,320.962,2142.03);
   CsI_cut[9]->SetPoint(2,336.089,1097.14);
   CsI_cut[9]->SetPoint(3,356.618,561.79);
   CsI_cut[9]->SetPoint(4,409.022,245.743);
   CsI_cut[9]->SetPoint(5,521.394,252.193);
   CsI_cut[9]->SetPoint(6,517.612,503.741);
   CsI_cut[9]->SetPoint(7,434.414,619.84);
   CsI_cut[9]->SetPoint(8,391.194,897.188);
   CsI_cut[9]->SetPoint(9,370.665,1303.53);
   CsI_cut[9]->SetPoint(10,357.699,1909.83);
   CsI_cut[9]->SetPoint(11,346.894,2974.07);
   CsI_cut[9]->SetPoint(12,338.25,4147.96);
   CsI_cut[9]->SetPoint(13,312.318,4077.01);

   CsI_cut[10] = new TCutG("csi_10_cut",16);
   CsI_cut[10]->SetVarX("trCsI[10]-tF5 ");
   CsI_cut[10]->SetVarY("arCsI[10]");
   CsI_cut[10]->SetTitle("Graph");
   CsI_cut[10]->SetFillColor(1);
   CsI_cut[10]->SetPoint(0,301.513,4057.66);
   CsI_cut[10]->SetPoint(1,299.892,2206.53);
   CsI_cut[10]->SetPoint(2,308.536,1297.08);
   CsI_cut[10]->SetPoint(3,318.26,645.64);
   CsI_cut[10]->SetPoint(4,340.411,258.643);
   CsI_cut[10]->SetPoint(5,392.274,245.743);
   CsI_cut[10]->SetPoint(6,459.806,252.193);
   CsI_cut[10]->SetPoint(7,462.507,452.141);
   CsI_cut[10]->SetPoint(8,380.389,606.94);
   CsI_cut[10]->SetPoint(9,350.675,877.838);
   CsI_cut[10]->SetPoint(10,334.468,1426.08);
   CsI_cut[10]->SetPoint(11,325.824,2064.63);
   CsI_cut[10]->SetPoint(12,320.421,3006.32);
   CsI_cut[10]->SetPoint(13,318.801,4128.61);
   CsI_cut[10]->SetPoint(14,302.053,4115.71);
   CsI_cut[10]->SetPoint(15,301.513,4057.66);

   CsI_cut[11] = new TCutG("csi_11_cut",20);
   CsI_cut[11]->SetVarX("tCsI-tF5");
   CsI_cut[11]->SetVarY("aCsI");
   CsI_cut[11]->SetTitle("Graph");
   CsI_cut[11]->SetFillColor(1);
   CsI_cut[11]->SetPoint(0,309.299,3186.3);
   CsI_cut[11]->SetPoint(1,310.717,2081.04);
   CsI_cut[11]->SetPoint(2,315.985,1365.87);
   CsI_cut[11]->SetPoint(3,324.494,813.235);
   CsI_cut[11]->SetPoint(4,333.408,509.83);
   CsI_cut[11]->SetPoint(5,349.615,282.276);
   CsI_cut[11]->SetPoint(6,400.061,114.319);
   CsI_cut[11]->SetPoint(7,444.631,114.319);
   CsI_cut[11]->SetPoint(8,463.472,70.9752);
   CsI_cut[11]->SetPoint(9,466.106,190.17);
   CsI_cut[11]->SetPoint(10,463.27,233.514);
   CsI_cut[11]->SetPoint(11,405.328,352.709);
   CsI_cut[11]->SetPoint(12,366.835,558.591);
   CsI_cut[11]->SetPoint(13,346.981,834.907);
   CsI_cut[11]->SetPoint(14,333.408,1371.28);
   CsI_cut[11]->SetPoint(15,323.278,2118.96);
   CsI_cut[11]->SetPoint(16,318.618,2427.79);
   CsI_cut[11]->SetPoint(17,315.579,2947.91);
   CsI_cut[11]->SetPoint(18,314.161,3240.48);
   CsI_cut[11]->SetPoint(19,309.299,3186.3);

   CsI_cut[12] = new TCutG("csi_12_cut",20);
   CsI_cut[12]->SetVarX("tCsI-tF5");
   CsI_cut[12]->SetVarY("aCsI");
   CsI_cut[12]->SetTitle("Graph");
   CsI_cut[12]->SetFillColor(1);
   CsI_cut[12]->SetPoint(0,305.045,3749.77);
   CsI_cut[12]->SetPoint(1,308.286,2400.7);
   CsI_cut[12]->SetPoint(2,313.553,1631.35);
   CsI_cut[12]->SetPoint(3,324.696,867.415);
   CsI_cut[12]->SetPoint(4,336.244,553.173);
   CsI_cut[12]->SetPoint(5,369.874,260.604);
   CsI_cut[12]->SetPoint(6,427.006,130.573);
   CsI_cut[12]->SetPoint(7,464.08,114.319);
   CsI_cut[12]->SetPoint(8,470.158,314.783);
   CsI_cut[12]->SetPoint(9,461.244,390.635);
   CsI_cut[12]->SetPoint(10,416.471,504.412);
   CsI_cut[12]->SetPoint(11,376.56,699.458);
   CsI_cut[12]->SetPoint(12,358.124,981.192);
   CsI_cut[12]->SetPoint(13,339.688,1409.21);
   CsI_cut[12]->SetPoint(14,322.873,2167.72);
   CsI_cut[12]->SetPoint(15,315.174,3018.34);
   CsI_cut[12]->SetPoint(16,312.135,3798.53);
   CsI_cut[12]->SetPoint(17,306.26,3912.31);
   CsI_cut[12]->SetPoint(18,306.26,3912.31);
   CsI_cut[12]->SetPoint(19,305.045,3749.77);

   CsI_cut[13] = new TCutG("csi_13_cut",21);
   CsI_cut[13]->SetVarX("tCsI-tF5");
   CsI_cut[13]->SetVarY("aCsI");
   CsI_cut[13]->SetTitle("Graph");
   CsI_cut[13]->SetFillColor(1);
   CsI_cut[13]->SetPoint(0,305.247,4064.01);
   CsI_cut[13]->SetPoint(1,309.907,2801.63);
   CsI_cut[13]->SetPoint(2,315.377,1885.99);
   CsI_cut[13]->SetPoint(3,323.278,1235.84);
   CsI_cut[13]->SetPoint(4,331.382,791.563);
   CsI_cut[13]->SetPoint(5,339.891,618.189);
   CsI_cut[13]->SetPoint(6,367.443,303.947);
   CsI_cut[13]->SetPoint(7,418.902,157.663);
   CsI_cut[13]->SetPoint(8,455.571,157.663);
   CsI_cut[13]->SetPoint(9,454.356,352.709);
   CsI_cut[13]->SetPoint(10,420.32,450.232);
   CsI_cut[13]->SetPoint(11,393.78,542.337);
   CsI_cut[13]->SetPoint(12,369.874,764.474);
   CsI_cut[13]->SetPoint(13,354.882,1073.3);
   CsI_cut[13]->SetPoint(14,340.498,1625.93);
   CsI_cut[13]->SetPoint(15,328.14,2563.24);
   CsI_cut[13]->SetPoint(16,322.265,3484.29);
   CsI_cut[13]->SetPoint(17,317.808,4015.25);
   CsI_cut[13]->SetPoint(18,313.148,4129.02);
   CsI_cut[13]->SetPoint(19,307.273,4123.61);
   CsI_cut[13]->SetPoint(20,305.247,4064.01);

   CsI_cut[14] = new TCutG("csi_14_cut",20);
   CsI_cut[14]->SetVarX("tCsI-tF5");
   CsI_cut[14]->SetVarY("aCsI");
   CsI_cut[14]->SetTitle("Graph");
   CsI_cut[14]->SetFillColor(1);
   CsI_cut[14]->SetPoint(0,323.278,1972.68);
   CsI_cut[14]->SetPoint(1,332.192,1690.94);
   CsI_cut[14]->SetPoint(2,342.524,1528.41);
   CsI_cut[14]->SetPoint(3,354.275,1279.18);
   CsI_cut[14]->SetPoint(4,366.835,921.594);
   CsI_cut[14]->SetPoint(5,377.978,645.279);
   CsI_cut[14]->SetPoint(6,446.86,287.693);
   CsI_cut[14]->SetPoint(7,485.555,238.932);
   CsI_cut[14]->SetPoint(8,496.495,217.26);
   CsI_cut[14]->SetPoint(9,502.978,358.127);
   CsI_cut[14]->SetPoint(10,503.383,509.83);
   CsI_cut[14]->SetPoint(11,498.116,585.681);
   CsI_cut[14]->SetPoint(12,446.657,759.056);
   CsI_cut[14]->SetPoint(13,412.014,1057.04);
   CsI_cut[14]->SetPoint(14,392.565,1414.63);
   CsI_cut[14]->SetPoint(15,381.625,1766.8);
   CsI_cut[14]->SetPoint(16,352.046,2048.53);
   CsI_cut[14]->SetPoint(17,336.041,2102.71);
   CsI_cut[14]->SetPoint(18,324.696,2021.44);
   CsI_cut[14]->SetPoint(19,323.278,1972.68);

   CsI_cut[15] = new TCutG("csi_15_cut",16);
   CsI_cut[15]->SetVarX("tCsI-tF5");
   CsI_cut[15]->SetVarY("aCsI");
   CsI_cut[15]->SetTitle("Graph");
   CsI_cut[15]->SetFillColor(1);
   CsI_cut[15]->SetPoint(0,295.357,4047.76);
   CsI_cut[15]->SetPoint(1,300.557,2276.08);
   CsI_cut[15]->SetPoint(2,311.666,1187.07);
   CsI_cut[15]->SetPoint(3,326.557,656.115);
   CsI_cut[15]->SetPoint(4,355.392,303.947);
   CsI_cut[15]->SetPoint(5,434.1,184.752);
   CsI_cut[15]->SetPoint(6,487.281,173.916);
   CsI_cut[15]->SetPoint(7,486.808,341.873);
   CsI_cut[15]->SetPoint(8,401.719,498.994);
   CsI_cut[15]->SetPoint(9,362.247,769.892);
   CsI_cut[15]->SetPoint(10,340.029,1100.39);
   CsI_cut[15]->SetPoint(11,323.011,1972.68);
   CsI_cut[15]->SetPoint(12,312.611,2774.54);
   CsI_cut[15]->SetPoint(13,307.175,3430.11);
   CsI_cut[15]->SetPoint(14,302.212,4069.43);
   CsI_cut[15]->SetPoint(15,295.357,4047.76);

}


void create_cuts(){

  create_ssd20_1();
  create_ssd20_2();
  create_ssd20_3();
  create_ssd20_4();

  create_ssd1_1();
  create_ssd1_2();
  create_ssd1_3();
  create_ssd1_4();

  create_ssdv_1();
  create_ssdv_2();
  create_ssdv_3();
  create_ssdv_4();

  create_dssd_x();
  create_CsI();

}
