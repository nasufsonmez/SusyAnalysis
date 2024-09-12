#ifndef MCProcessor_h
#define MCProcessor_h


/*  \class PrepareData
*
*  Class which does the cleaning, isolation, final cuts and matching 
*  of MrParticle objects
*
*  Authors: Luc Pape & Filip Moortgat      Date: October 2006
*                                          Updated: 
*
*/


#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "AnalysisExamples/SusyAnalysis/interface/MrParticle.h" 
#include "AnalysisExamples/SusyAnalysis/interface/MrEvent.h" 

class MCProcessor {

public:

// Constructors:
MCProcessor(MrEvent *);
//MCProcessor(MrEvent *, const edm::ParameterSet&);
MCProcessor(MrEvent *, Config_t *);

// Destructor:
virtual ~MCProcessor(){};

// Methods:
virtual bool MCDriver(void);
math::XYZVector PmissMC(void) {return metMCvector;}
void SetDebug(int debug)  {DEBUGLVL  = debug; } 
virtual int NumMCElecTrue(void){return nMCElecTrue;}
virtual int NumMCMuonTrue(void){return nMCMuonTrue;}
virtual int NumMCTauTrue(void){return nMCTauTrue;}
virtual int NumMCPhotTrue(void){return nMCPhotTrue;}
virtual int NumMCJetTrue(void){return nMCJetTrue;}

private:
     
   // names of parameter sets  
  //edm::ParameterSet& iConfig;
  Config_t * myConfig;
  edm::ParameterSet acceptance_cuts;
  edm::ParameterSet mcproc_params;

  MrEvent * myEventData;
  std::vector<MrParticle*> & MCData;
  
  
  // Define all pointers to objects
     

  int DEBUGLVL;

  // Define the acceptance cuts
  float ana_elecEtaMax;
  float ana_muonEtaMax;
  float ana_tauEtaMax;
  float ana_photonEtaMax;
  float ana_jetEtaMax;
  float ana_elecPtMin2;
  float ana_muonPtMin2;
  float ana_tauPtMin2;
  float ana_photonPtMin2;
  float ana_jetPtMin2;

  // Define the MC parameters
  int mc_numEvtPrnt;
  float mc_PhotCalFac;
  float mc_JetCalFac;
  float mc_JetDeltaRIC;
  
  // Define the counters per event
  
  int nMCElecTrue;
  int nMCMuonTrue;
  int nMCTauTrue;
  int nMCPhotTrue;
  int nMCJetTrue;
  
  // Define MET vectors 
  math::XYZVector metMCvector;

  // Define the private methods included
  virtual void PrintMCInfo(int);
  virtual void MakeMCStatusInfo(void);
  virtual math::XYZVector MetFromMC(void);
  virtual float DeltaPhi(float, float);
  virtual float GetDeltaR(float, float, float, float);

};

#endif

