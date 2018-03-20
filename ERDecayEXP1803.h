/********************************************************************************
 *              Copyright (C) Joint Institute for Nuclear Research              *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef ERDecayEXP1803_H
#define ERDecayEXP1803_H

#include "TGraph.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TGenPhaseSpace.h"

#include "FairIon.h"

#include "ERDecay.h"

class ERDecayEXP1803 : public ERDecay{

public:
  ERDecayEXP1803();
  ~ERDecayEXP1803();

  /*Modifiers*/
  void SetMinStep(Double_t minStep) {fMinStep = minStep;}
  void SetTargetVolumeName(TString volumeName) {fVolumeName = volumeName;}
  void SetTargetThickness(Double_t targetThickness) {fTargetThickness = targetThickness;}
  void SetH5Mass(Double_t mass) {f5HMass = mass; fIs5HUserMassSet = true;}
  void SetH5Exitation(Double_t excMean, Double_t fwhm, Double_t distibWeight);

  void phasegen2(Double_t Ecm, Double_t h5Mass);
  void ReadADInput(TString ADfile);
  static Double_t ADEvaluate(Double_t *x, Double_t *p);

public:
  Bool_t Init();
  Bool_t Stepping();

  void BeginEvent();
  void FinishEvent();

private:
  TRandom3       *fRnd;
  
  TParticlePDG   *f6He;
  TParticlePDG   *f2H;
  TParticlePDG   *f3He;
  TParticlePDG   *f5H;
  TParticlePDG   *f3H;
  TParticlePDG   *fn;

  TLorentzVector *flv3He; //!
  TLorentzVector *flv5H; //!

  FairIon        *fIon3He;
  FairIon* fUnstableIon5H;

  TGenPhaseSpace  *fReactionPhaseSpace;
  TGenPhaseSpace  *fDecayPhaseSpace;
  TString          fVolumeName;
  Double_t         fTargetReactZ;
  Double_t         fMinStep;
  Double_t         fTargetThickness;
  Bool_t           fDecayFinish;
  std::vector<Double_t> f5HExcitationMean;
  std::vector<Double_t> f5HExcitationSigma; 
  std::vector<Double_t> f5HExcitationWeight;

  Double_t        f5HMass;
  Bool_t          fIs5HUserMassSet;
  Bool_t          fIs5HExcitationSet;

  TF1 *fADFunction;  // function describing AD of binary reaction
  static TGraph *fADInput; //   distribution (AD) graph containing AD input

  ClassDef(ERDecayEXP1803,1)
};

#endif