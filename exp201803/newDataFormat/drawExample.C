void drawExample() { 

   TFile *f = new TFile("/media/user/work/data/exp1804/analysis/digi.root");
   TTree *t = (TTree*)f->Get("er");
   if(t!=NULL) {
      cout << "tree " << t->GetName() << " with " << t->GetEntries() << " was found" << endl;
   }

   TClonesArray *SQ20_array = new TClonesArray("ERQTelescopeSiDigi");
   TClonesArray *SQX_L_array = new TClonesArray("ERQTelescopeSiDigi");
   TClonesArray *SQY_L_array = new TClonesArray("ERQTelescopeSiDigi");
   TClonesArray *CsI_L_array = new TClonesArray("ERQTelescopeCsIDigi");

   TClonesArray *SQX_R_array = new TClonesArray("ERQTelescopeSiDigi");
   TClonesArray *SQY_R_array = new TClonesArray("ERQTelescopeSiDigi");
   TClonesArray *CsI_R_array = new TClonesArray("ERQTelescopeCsIDigi");

   TClonesArray *ToF1_array = new TClonesArray("ERBeamDetTOFDigi");
   TClonesArray *ToF2_array = new TClonesArray("ERBeamDetTOFDigi");

   TClonesArray *MWPCX1_array = new TClonesArray("ERBeamDetMWPCDigi");
   TClonesArray *MWPCY1_array = new TClonesArray("ERBeamDetMWPCDigi");
   TClonesArray *MWPCX2_array = new TClonesArray("ERBeamDetMWPCDigi");
   TClonesArray *MWPCY2_array = new TClonesArray("ERBeamDetMWPCDigi");

   ERBeamTimeEventHeader *trigger_b = new ERBeamTimeEventHeader();

//    TBranch *b = t->GetBranch("EventHeader");
//    // b->Print();
//    cout << b->GetClassName() << endl;
//    // b->SetAddress(&SQ20_array);
// return;
   t->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SQ300_X_0",&SQ20_array);
   t->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_SQ_L_XY_0_X",&SQX_L_array);
   t->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_DoubleSi_SQ_L_XY_0_Y",&SQY_L_array);
   t->SetBranchAddress("ERQTelescopeCsIDigi_Left_telescope_CsI_L_0",&CsI_L_array);

   t->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_DoubleSi_SQ_R_XY_1_X",&SQX_R_array);
   t->SetBranchAddress("ERQTelescopeSiDigi_Right_telescope_DoubleSi_SQ_R_XY_1_Y",&SQY_R_array);
   t->SetBranchAddress("ERQTelescopeCsIDigi_Right_telescope_CsI_R_0",&CsI_R_array);

   t->SetBranchAddress("BeamDetToFDigi1",&ToF1_array);
   t->SetBranchAddress("BeamDetToFDigi2",&ToF2_array);

   t->SetBranchAddress("BeamDetMWPCDigiX1",&MWPCX1_array);
   t->SetBranchAddress("BeamDetMWPCDigiY1",&MWPCY1_array);
   t->SetBranchAddress("BeamDetMWPCDigiX2",&MWPCX2_array);
   t->SetBranchAddress("BeamDetMWPCDigiY2",&MWPCY2_array);

   t->SetBranchAddress("EventHeader.",&trigger_b);

   for(Int_t nentry = 1; nentry<10;nentry++){
      t->GetEntry(nentry);
      // if(SQ20_array->GetEntries()) cout << SQ20_array->GetEntries() << endl;
      // if(SQX_L_array->GetEntries()) cout << SQX_L_array->GetEntries() << endl;
      // if(ToF1_array->GetEntries()) cout << ToF1_array->GetEntries() << endl;  
      cout << "##EVENT " << nentry << "##" <<endl;

      ERQTelescopeSiDigi **SQ20_Digi = new ERQTelescopeSiDigi*[SQ20_array->GetEntries()];
      for(Int_t i=0;i<SQ20_array->GetEntries();i++){
         SQ20_Digi[i] = (ERQTelescopeSiDigi*)SQ20_array->At(i);
         // cout << i << " " << SQ20_Digi[i]->GetEdep() << " " << SQ20_Digi[i]->GetTime() << endl;
      }
      ERQTelescopeSiDigi **SQX_L_Digi = new ERQTelescopeSiDigi*[SQX_L_array->GetEntries()];
      for(Int_t i=0;i<SQX_L_array->GetEntries();i++){
         SQX_L_Digi[i] = (ERQTelescopeSiDigi*)SQX_L_array->At(i);
         // cout << i << " " << SQX_L_Digi[i]->GetEdep() << " " << SQX_L_Digi[i]->GetTime() << endl;
      }
      ERQTelescopeSiDigi **SQY_L_Digi = new ERQTelescopeSiDigi*[SQY_L_array->GetEntries()];
      for(Int_t i=0;i<SQY_L_array->GetEntries();i++){
         SQY_L_Digi[i] = (ERQTelescopeSiDigi*)SQY_L_array->At(i);
         // cout << i << " " << SQY_L_Digi[i]->GetEdep() << " " << SQY_L_Digi[i]->GetTime() << endl;
      }

      ERQTelescopeSiDigi **SQY_R_Digi = new ERQTelescopeSiDigi*[SQY_R_array->GetEntries()];
      for(Int_t i=0;i<SQY_R_array->GetEntries();i++){
         SQY_R_Digi[i] = (ERQTelescopeSiDigi*)SQY_R_array->At(i);
         // cout << i << " " << SQY_R_Digi[i]->GetEdep() << " " << SQY_R_Digi[i]->GetTime() << endl;
      }
      ERQTelescopeSiDigi **SQX_R_Digi = new ERQTelescopeSiDigi*[SQX_R_array->GetEntries()];
      for(Int_t i=0;i<SQX_R_array->GetEntries();i++){
         SQX_R_Digi[i] = (ERQTelescopeSiDigi*)SQX_R_array->At(i);
         // cout << i << " " << SQX_R_Digi[i]->GetEdep() << " " << SQX_R_Digi[i]->GetTime() << endl;
      }
      ERQTelescopeCsIDigi **CsI_R_Digi = new ERQTelescopeCsIDigi*[CsI_R_array->GetEntries()];
      for(Int_t i=0;i<CsI_R_array->GetEntries();i++){
         CsI_R_Digi[i] = (ERQTelescopeCsIDigi*)CsI_R_array->At(i);
         // cout << i << " " << CsI_R_Digi[i]->GetEdep() << " " << CsI_R_Digi[i]->GetTime() << endl;
      }

      ERBeamDetTOFDigi **ToF1_Digi = new ERBeamDetTOFDigi*[ToF1_array->GetEntries()];
      for(Int_t i=0;i<ToF1_array->GetEntries();i++){
         ToF1_Digi[i] = (ERBeamDetTOFDigi*)ToF1_array->At(i);
         // cout << i << " " << ToF1_Digi[i]->GetEdep() << " " << ToF1_Digi[i]->GetTime() << endl;
      }
      ERBeamDetTOFDigi **ToF2_Digi = new ERBeamDetTOFDigi*[ToF2_array->GetEntries()];
      for(Int_t i=0;i<ToF2_array->GetEntries();i++){
         ToF2_Digi[i] = (ERBeamDetTOFDigi*)ToF2_array->At(i);
         // cout << i << " " << ToF2_Digi[i]->GetEdep() << " " << ToF2_Digi[i]->GetTime() << endl;
      }

      ERBeamDetMWPCDigi **MWPCX1_Digi = new ERBeamDetMWPCDigi*[MWPCX1_array->GetEntries()];
      for(Int_t i=0;i<MWPCX1_array->GetEntries();i++){
         MWPCX1_Digi[i] = (ERBeamDetMWPCDigi*)MWPCX1_array->At(i);
         // cout << i << " " << MWPCX1_Digi[i]->GetEdep() << " " << MWPCX1_Digi[i]->GetTime() << endl;
      }
      ERBeamDetMWPCDigi **MWPCY1_Digi = new ERBeamDetMWPCDigi*[MWPCY1_array->GetEntries()];
      for(Int_t i=0;i<MWPCY1_array->GetEntries();i++){
         MWPCY1_Digi[i] = (ERBeamDetMWPCDigi*)MWPCY1_array->At(i);
         // cout << i << " " << MWPCY1_Digi[i]->GetEdep() << " " << MWPCY1_Digi[i]->GetTime() << endl;
      }
      ERBeamDetMWPCDigi **MWPCX2_Digi = new ERBeamDetMWPCDigi*[MWPCX2_array->GetEntries()];
      for(Int_t i=0;i<MWPCX2_array->GetEntries();i++){
         MWPCX2_Digi[i] = (ERBeamDetMWPCDigi*)MWPCX2_array->At(i);
         // cout << i << " " << MWPCX2_Digi[i]->GetEdep() << " " << MWPCX2_Digi[i]->GetTime() << endl;
      }
      ERBeamDetMWPCDigi **MWPCY2_Digi = new ERBeamDetMWPCDigi*[MWPCY2_array->GetEntries()];
      for(Int_t i=0;i<MWPCY2_array->GetEntries();i++){
         MWPCY2_Digi[i] = (ERBeamDetMWPCDigi*)MWPCY2_array->At(i);
         cout << i << " " << MWPCY2_Digi[i]->GetEdep() << " " << MWPCY2_Digi[i]->GetTime() << endl;
      }

      // cout << trigger_b->GetTrigger() << endl;

   }

// Int_t CheckBranchAddressType(TBranch* branch, TClass* ptrClass, EDataType datatype, Bool_t ptr)
   // cout << t->CheckBranchAddressType("","");
   // t->SetBranchAddress("ERQTelescopeSiDigi_Left_telescope_SingleSi_SQ300_X_0",SQ20_array);


   // cout << endl << " entry!!! " << SQ20_array->GetEntries() << endl;


}
