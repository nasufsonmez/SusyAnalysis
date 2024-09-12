#ifndef UserAnalysis_h
#define UserAnalysis_h


/*  \class UserAnalysis
*
*  Class where the user analysis code goes -- (now it contains just an example)
*
*  Authors: Luc Pape & Filip Moortgat      Date: December 2006
*                                          Updated: March 2007
*
*/


#include "AnalysisExamples/SusyAnalysis/interface/MrEvent.h" 
#include "AnalysisExamples/SusyAnalysis/interface/MrParticle.h" 
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TH1.h"
#include "TH2.h"
 
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

class UserAnalysis {

public:

// Constructor:
UserAnalysis(Config_t *);

// Destructor:
virtual ~UserAnalysis(){
  endAnalysis();
};

// Methods:

virtual bool L1Driver(MrEvent*);
virtual bool HLTDriver(MrEvent*);
virtual void doAnalysis(MrEvent*);
void endAnalysis();
void setNtotEvtProc(int n){ntotEvtProc = n;};

private:
 
 
  // names of parameter sets  
  Config_t * myConfig;
  edm::ParameterSet useranalysis_params;
  
  // Define the parameters
  float user_metMin;
 
 
  // names of histograms
     TH2F*       hRLeptonMult;
     TH2F*       hRElectronMult;
     TH2F*       hRMuonMult;
     TH2F*       hRPhotonMult;
     TH2F*       hRBJetMult;
     TH2F*       hJetMult;
     TH1D*       hJetEnergy;
     TH1D*       hPtEnergy;   
     TH2F*       hNRtJets;
     TH1F*       hMissEnergy;
     TH1D*       hPtElec;
     TH1D*       hPtMuon;
     TH1D*       hPtJet1;
     TH1D*       hPtJet2;
     TH1D*       hPtJet3;
     TH1D*       hMissingETmc;
     TH1D*       hMissingET;
     TH1D*       hEtSum;
     TH1D*       hHT;
     TH1D*       hHemiMass;
     TH1D*       hJetGoodEt;
     TH1D*       hJetWrongEt;
     TH1D*       hNSMq;
     TH1D*       hNGluino;
     
//F.O
     TH1D*       hDiElectronMass;
     TH1D*       hDiMuonMass;
     TH1D*       hDiElectronMcMass;
     TH1D*       hDiMuonMcMass;
     TH1D*       hDiJeTMcMass;
     TH1D*       hChi10Mass;
     TH1D*       hChi10InvMass;
     TH1D*       hGluinoMass;
     TH1D*       hGluinoInvMass;
     TH1D*       hSquarkMass;
     TH1D*       hqMassfromsq;
     TH1D*	 hSquarkInvMass;  


     //Histos for Analysis
     TH1D*      hMetMc;
     TH1D*      hMetCalo;
     TH1D*      hMetRecoil;
     TH1D*      hElecPt;
     TH1D*      hMuonPt;
     TH1D*      hJet1Pt;
     TH1D*      hJet2Pt;
     TH1D*      hJet3Pt;
     TH1D*      hJet4Pt;

     TH2D*      JetGen;
     TH1D*      hGenJetMult;
     TH1D*      hLjetPt;   
     TH1D*	hLGenjetPt;
     TH1F*      hSignal;
     TH1F*      hSignal1;
     TH1D*      hNEvent;

  MrEvent * EventData;
  //std::vector<MrParticle*> & RecoData;
  //std::vector<MrParticle*> & MCData;

// number of User selected events for final statistics
  int nTotEvtSelUser;

// Some (possibly) useful functions:
// Based on MCData
virtual int FindProducedSusyParticles(int *);
virtual int FindTopSusyMother(int);
virtual int FindLowSusyMother(int);
virtual int FirstSMParton(int);
virtual bool ComesFromSquark(int);
virtual bool ComesFromGluino(int);
// Based on RecoData
virtual int FindNearestJet(int);
virtual float GetPtwrtJet(int, int);
virtual void AddToJet(int);
// Just kinematics
virtual float DeltaPhi(float, float);
virtual float GetDeltaR(float, float, float, float);

// Define user counters


  int ntotEvtProc;
//F.O 
     int EvCounter;
     int Ngenevent;
     int Ngenevent1;
     int Ngenevent2;
     int Ngluino;
     int Ngsq;
     int Nsqsq;
     int NXX;
     int Nll;
     int NsqX;
     int NgX;
     int Nsqsb;
     int Ngsb;
     int Nsbsb;
     int Nstst;
     int kok1;
     int kok2;
     int kok3;
     int kok4;
     int kok5;
     int kok6;
     int kok7;
     int kok8;
     int kok9;
     int kok10;
     int kok11;
     int kok12;
     int kok13;
     int kok14;
     int kok15;
     int kok16;
     int fsa;
     int fsb;
     int fsc;
            
     int nEventsAfterCuts;
     float signal ;
     float Tsignal ;
     float numatch ;
     int iMatch  ;
     int smom1;
     int smom2;
     int indx;
     int GQ;
     int QQ;
     int Num_Event;
     float mo_jetDRmax;
     float mo_jetDPbyPma;
     float mo_cjetDRmax;
     float mo_jetDPbyPmax;
     float PtSumJets;
     float EtSumJet;
     
//
ofstream in;
ofstream ins;
};

#endif

