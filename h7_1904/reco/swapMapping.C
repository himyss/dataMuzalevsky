Double_t fThickness1[16][16],fThickness2[16][16],fThickness3[16][16],fThickness4[16][16];
void readThickness();

TH2F *hThick1,*hThick2,*hThick3,*hThick4;
TH2F *hThick1_sim,*hThick2_sim,*hThick3_sim,*hThick4_sim;

void swapMapping() {
	
	readThickness();

	Bool_t swapX = 0;
	Bool_t swapY = 1;

	hThick1_sim = (TH2F*)hThick1->Clone();
	hThick2_sim = (TH2F*)hThick2->Clone();
	hThick3_sim = (TH2F*)hThick3->Clone();
	hThick4_sim = (TH2F*)hThick4->Clone();


	for (Int_t i=0;i<hThick4->GetXaxis()->GetNbins();i++) {
		for (Int_t j=0;j<hThick4->GetYaxis()->GetNbins();j++) {
			if (swapX && !swapY) hThick4_sim->SetBinContent(i+1,j+1,hThick4->GetBinContent(hThick4->GetXaxis()->GetNbins()-i,j+1));
			if (!swapX && swapY) hThick4_sim->SetBinContent(i+1,j+1,hThick4->GetBinContent(i+1,hThick4->GetXaxis()->GetNbins()-j));
			if (swapX && swapY) hThick4_sim->SetBinContent(i+1,j+1,hThick4->GetBinContent(hThick4->GetXaxis()->GetNbins()-i,hThick4->GetXaxis()->GetNbins()-j));
		}
	}

	cout << endl << " new " << endl;
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        cout << hThick4_sim->GetBinContent(i+1,j+1) << " ";
      }
      cout << endl;
    }

    TString outFileName("/home/muzalevskii/work/expertroot/macro/EXP1904_H7/sim_nonuniform/input/thicknessMap_calib_90_all_SSD_1m_4_sim.root");
    TFile *fOut = new TFile(outFileName.Data(),"RECREATE");
    fOut->cd();
    hThick4_sim->Write();
    fOut->Close();

}

void readThickness() {
  cout << "thickness of the first detector " << endl;
  TFile *f1 = new TFile("/home/muzalevskii/work/expertroot/macro/EXP1904_H7/sim_nonuniform/input/thicknessMap_calib_90_all_SSD_1m_1_real.root","READ");
  if (f1->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness1[i][j] = 20.;
        cout << fThickness1[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    hThick1 = (TH2F*)f1->Get("thicknessMap_calib_90_all_SSD_1m_1_realHist");
    // for(Int_t i = 0; i<16; i++) {
    //   for(Int_t j = 0; j<16; j++) {
    //     fThickness1[i][j] = hThick1->GetBinContent(i+1,j+1);
    //     cout << fThickness1[i][j] << " ";
    //   }
    //   cout << endl;
    // }
  }
  // delete f1;

  cout  << endl << "thickness of the SECOND detector " << endl;
  TFile *f2 = new TFile("/home/muzalevskii/work/expertroot/macro/EXP1904_H7/sim_nonuniform/input/thicknessMap_alltel_90_SSD_1m_2_real.root","READ");
  if (f2->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness2[i][j] = 20.;
        cout << fThickness2[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    hThick2 = (TH2F*)f2->Get("thicknessMap_alltel_90_SSD_1m_2_realHist");
    // for(Int_t i = 0; i<16; i++) {
    //   for(Int_t j = 0; j<16; j++) {
    //     fThickness2[i][j] = hThick2->GetBinContent(i+1,j+1);
    //     cout << fThickness2[i][j] << " ";
    //   }
    //   cout << endl;
    // }
  }
  // delete f2;


  cout  << endl << "thickness of the THIRD detector " << endl;
  TFile *f3 = new TFile("/home/muzalevskii/work/expertroot/macro/EXP1904_H7/sim_nonuniform/input/thicknessMap_calib_90_all_SSD_1m_3_switch_new.root","READ");
  if (f3->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness3[i][j] = 20.;
        cout << fThickness3[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    hThick3 = (TH2F*)f3->Get("thicknessMap_calib_90_all_SSD_1m_3_switch_realHist");
    // for(Int_t i = 0; i<16; i++) {
    //   for(Int_t j = 0; j<16; j++) {
    //     fThickness3[i][j] = hThick3->GetBinContent(i+1,j+1);
    //     cout << fThickness3[i][j] << " ";
    //   }
    //   cout << endl;
    // }
  }
  // delete f3;


  cout  << endl << "thickness of the FOURTH detector " << endl;
  TFile *f4 = new TFile("/home/muzalevskii/work/expertroot/macro/EXP1904_H7/sim_nonuniform/input/thicknessMap_calib_90_all_SSD_1m_4_real.root","READ");
  if (f4->IsZombie()) {
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness4[i][j] = 20.;
        cout << fThickness4[i][j] << " ";
      }
      cout << endl;
    }

  }
  else {
    hThick4 = (TH2F*)f4->Get("thicknessMap_calib_90_all_SSD_1m_4_realHist");
    for(Int_t i = 0; i<16; i++) {
      for(Int_t j = 0; j<16; j++) {
        fThickness4[i][j] = hThick4->GetBinContent(i+1,j+1);
        cout << fThickness4[i][j] << " ";
      }
      cout << endl;
    }
  }
  // delete f4;

}


