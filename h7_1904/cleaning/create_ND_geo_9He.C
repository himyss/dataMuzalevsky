void create_ND_geo_9He()
{
  TString erPath = gSystem->Getenv("VMCWORKDIR");

  // Output paths
  TString outGeoFilenameRoot = "/home/muzalevskii/work/macro/h7_1904/cleaning/ND10Li.geo.root";
  TString outGeoFilenameGdml = "/home/muzalevskii/work/macro/h7_1904/cleaning/geometry/ND10Li.gdml";

  // Input paths
  TString medFile = erPath + "/geometry/media.geo";

  // Materials and media
  FairGeoLoader* geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  geoFace->setMediaFile(medFile);
  geoFace->readMedia();
  FairGeoMedia* geoMedia = geoFace->getMedia();
  FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

  // Geometry manager
  TGeoManager* geoM = (TGeoManager*)gROOT->FindObject("FAIRGeom");

  TString mediumName;

  mediumName = "Stilbene";
  FairGeoMedium* mStilbene = geoMedia->getMedium(mediumName);
  if (!mStilbene) Fatal("create_ND_geo", "FairMedium %s not found", mediumName.Data());
  geoBuild->createMedium(mStilbene);
  TGeoMedium* pStilbene = geoM->GetMedium(mediumName);
  if (!pStilbene) Fatal("create_ND_geo", "Medium %s not found", mediumName.Data());

  mediumName = "Steel";
  FairGeoMedium* mSteel = geoMedia->getMedium(mediumName);
  if (!mSteel) Fatal("create_ND_geo", "FairMedium %s not found", mediumName.Data());
  geoBuild->createMedium(mSteel);
  TGeoMedium* pSteel = geoM->GetMedium(mediumName);
  if (!pSteel) Fatal("create_ND_geo", "Medium %s not found", mediumName.Data());

  mediumName = "aluminium";
  FairGeoMedium* maluminium = geoMedia->getMedium(mediumName);
  if (!maluminium) Fatal("create_ND_geo", "FairMedium %s not found", mediumName.Data());
  geoBuild->createMedium(maluminium);
  TGeoMedium* paluminium = geoM->GetMedium(mediumName);
  if (!paluminium) Fatal("create_ND_geo", "Medium %s not found", mediumName.Data());

  // General dimensions
  Double_t R_min_Crystal = 0.0; // cm
  Double_t R_max_Crystal = 4.0; // cm
  Double_t HeightZ_Crystal = 5.0; // cm
  Double_t R_min_Shell = 0.0; // cm
  Double_t R_max_Shell = 4.2; // cm
  Double_t HeightZ_Shell = 5.2; // cm
  Double_t R_min_Housing = 0.0; // cm
  Double_t R_max_Housing = 4.8; // cm
  Double_t HeightZ_Housing = 5.4; // cm

  // Shapes
  TGeoTube* crystalSh = new TGeoTube("crystalSh", R_min_Crystal, R_max_Crystal, HeightZ_Crystal/2.);
  TGeoTube* shellSh = new TGeoTube("shellSh", R_min_Shell, R_max_Shell, HeightZ_Shell/2.);
  TGeoTube* housingSh = new TGeoTube("housingSh", R_min_Housing, R_max_Housing, HeightZ_Housing/2.);

  // Volumes
  TGeoVolume* crystalVol = new TGeoVolume("crystalVol", crystalSh, pStilbene);
  crystalVol->SetLineColor(kBlack);
  crystalVol->SetTransparency(10);

  TGeoVolume* shellVol = new TGeoVolume("shellVol", shellSh, paluminium);
  shellVol->SetLineColor(kRed);
  //shellVol->SetTransparency(40);

  TGeoVolume* housingVol = new TGeoVolume("housingVol", housingSh, pSteel);
  housingVol->SetLineColor(kGray);
  housingVol->SetTransparency(60);

  TGeoVolume* moduleVol = new TGeoVolumeAssembly("moduleVol");
  moduleVol->SetLineColor(kOrange);
  moduleVol->SetTransparency(70);
  // Matrices
  TGeoRotation* rotNoRot = new TGeoRotation("rotNoRot", 0., 0., 0.);
  rotNoRot->RegisterYourself();

  // Structure
  // Crystal in shell
  shellVol->AddNode(crystalVol, 1, new TGeoCombiTrans("mCrystalInShell", 0., 0., (HeightZ_Shell-HeightZ_Crystal)/2., rotNoRot));

  // Shell in housing
  housingVol->AddNode(shellVol, 1, new TGeoCombiTrans("mCrystalInShell", 0., 0., (HeightZ_Shell-HeightZ_Crystal)/2., rotNoRot));
  // housing in Module
  moduleVol->AddNode(housingVol, 1, new TGeoCombiTrans("mCrystalInShell", 0., 0., (HeightZ_Shell-HeightZ_Crystal)/2., rotNoRot));

  // Module in ND
  // This is the one but last level in the hierarchy
  // This volume-assembly is the only volume to be inserted into TOP
  TGeoVolumeAssembly* subdetectorVolAss = new TGeoVolumeAssembly("neutrondet2ch");

  Float_t z = 20.;

  Float_t ya = 13.5;
  Float_t yb = 27.;

  Float_t x0 = 57.735;
  Float_t x1 = 45.45;
  Float_t x2 = 32.55;
  Float_t x3 = 15.755;

  Float_t x8 = 57.31;
  Float_t x9 = 46.05;
  Float_t x10 = 34.38;
  Float_t x11 = 21.89;
  Float_t x12 = 10.44;

  Float_t x19 = 46.665;
  Float_t x20 = 33.15;
  Float_t x21 = 22.095;
  Float_t x22 = 9.21;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  subdetectorVolAss->AddNode(moduleVol, 0, new TGeoCombiTrans("moduleInNeutrondet2ch", x0, yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 1, new TGeoCombiTrans("moduleInNeutrondet2ch", x1, yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 2, new TGeoCombiTrans("moduleInNeutrondet2ch", x2, yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 3, new TGeoCombiTrans("moduleInNeutrondet2ch", x3, yb, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 47, new TGeoCombiTrans("moduleInNeutrondet2ch", 0., yb, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 4, new TGeoCombiTrans("moduleInNeutrondet2ch", -x3, yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 5, new TGeoCombiTrans("moduleInNeutrondet2ch", -x2, yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 6, new TGeoCombiTrans("moduleInNeutrondet2ch", -x1, yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 7, new TGeoCombiTrans("moduleInNeutrondet2ch", -x0, yb, z, rotNoRot));
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  subdetectorVolAss->AddNode(moduleVol, 8, new TGeoCombiTrans("moduleInNeutrondet2ch", x8, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 9, new TGeoCombiTrans("moduleInNeutrondet2ch", x9, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 10, new TGeoCombiTrans("moduleInNeutrondet2ch", x10, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 11, new TGeoCombiTrans("moduleInNeutrondet2ch", x11, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 12, new TGeoCombiTrans("moduleInNeutrondet2ch", x12, ya, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 13, new TGeoCombiTrans("moduleInNeutrondet2ch", 0., ya, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 14, new TGeoCombiTrans("moduleInNeutrondet2ch", -x12, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 15, new TGeoCombiTrans("moduleInNeutrondet2ch", -x11, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 16, new TGeoCombiTrans("moduleInNeutrondet2ch", -x10, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 17, new TGeoCombiTrans("moduleInNeutrondet2ch", -x9, ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 18, new TGeoCombiTrans("moduleInNeutrondet2ch", -x8, ya, z, rotNoRot));
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  subdetectorVolAss->AddNode(moduleVol, 19, new TGeoCombiTrans("moduleInNeutrondet2ch", x19, 0., z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 20, new TGeoCombiTrans("moduleInNeutrondet2ch", x20, 0., z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 21, new TGeoCombiTrans("moduleInNeutrondet2ch", x21, 0., z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 22, new TGeoCombiTrans("moduleInNeutrondet2ch", x22, 0., z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 23, new TGeoCombiTrans("moduleInNeutrondet2ch", -x22, 0., z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 24, new TGeoCombiTrans("moduleInNeutrondet2ch", -x21, 0., z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 25, new TGeoCombiTrans("moduleInNeutrondet2ch", -x20, 0., z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 26, new TGeoCombiTrans("moduleInNeutrondet2ch", -x19, 0., z, rotNoRot));
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  subdetectorVolAss->AddNode(moduleVol, 27, new TGeoCombiTrans("moduleInNeutrondet2ch", x8, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 28, new TGeoCombiTrans("moduleInNeutrondet2ch", x9, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 29, new TGeoCombiTrans("moduleInNeutrondet2ch", x10, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 30, new TGeoCombiTrans("moduleInNeutrondet2ch", x11, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 31, new TGeoCombiTrans("moduleInNeutrondet2ch", x12, -ya, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 32, new TGeoCombiTrans("moduleInNeutrondet2ch", 0., -ya, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 33, new TGeoCombiTrans("moduleInNeutrondet2ch", -x12, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 34, new TGeoCombiTrans("moduleInNeutrondet2ch", -x11, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 35, new TGeoCombiTrans("moduleInNeutrondet2ch", -x10, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 36, new TGeoCombiTrans("moduleInNeutrondet2ch", -x9, -ya, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 37, new TGeoCombiTrans("moduleInNeutrondet2ch", -x8, -ya, z, rotNoRot));
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  subdetectorVolAss->AddNode(moduleVol, 38, new TGeoCombiTrans("moduleInNeutrondet2ch", x0, -yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 39, new TGeoCombiTrans("moduleInNeutrondet2ch", x1, -yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 40, new TGeoCombiTrans("moduleInNeutrondet2ch", x2, -yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 41, new TGeoCombiTrans("moduleInNeutrondet2ch", x3, -yb, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 42, new TGeoCombiTrans("moduleInNeutrondet2ch", 0., -yb, z, rotNoRot));
  
  subdetectorVolAss->AddNode(moduleVol, 43, new TGeoCombiTrans("moduleInNeutrondet2ch", -x3, -yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 44, new TGeoCombiTrans("moduleInNeutrondet2ch", -x2, -yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 45, new TGeoCombiTrans("moduleInNeutrondet2ch", -x1, -yb, z, rotNoRot));
  subdetectorVolAss->AddNode(moduleVol, 46, new TGeoCombiTrans("moduleInNeutrondet2ch", -x0, -yb, z, rotNoRot));
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // World ------------------------------------
  TGeoVolumeAssembly* topVolAss = new TGeoVolumeAssembly("TOP");
  topVolAss->AddNode(subdetectorVolAss, 1);

  // Finalize
  geoM->SetTopVolume(topVolAss);
  geoM->CloseGeometry();
  geoM->CheckOverlaps();
  geoM->PrintOverlaps();
  //geoM->CheckGeometry();
  //geoM->CheckGeometryFull();
  //geoM->Test();

  // Export
  //geoM->Export(outGeoFilenameGdml);
  TFile* outGeoFileRoot = new TFile(outGeoFilenameRoot, "RECREATE");
  geoM->GetTopVolume()->Write();
  outGeoFileRoot->Close();

  // Draw
  TBrowser* bro = new TBrowser("bro", "bro");
  geoM->GetTopVolume()->Draw("ogl");
}
