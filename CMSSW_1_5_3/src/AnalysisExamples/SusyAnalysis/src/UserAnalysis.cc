#include "AnalysisExamples/SusyAnalysis/interface/UserAnalysis.h"

using namespace std;
using std::vector;
using std::cout;
using std::endl;


// Constructor:

UserAnalysis::UserAnalysis(Config_t * theConfig) : 
myConfig(theConfig), EventData(0)
{
// get parameters for UserAnalysis
  useranalysis_params = (*myConfig).useranalysis_params;
// load the parameters
  user_metMin = useranalysis_params.getParameter<double>("user_metMin") ;
  
  cout << endl;
  cout << "UserAnalysis parameters:" << endl;
  cout << " user_metMin = " << user_metMin << endl;

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
ins.open("istatistik.txt",ios::out);
in.open("susyout.txt",ios::out);
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
  signal=0.;
  numatch=0.;
  iMatch=-1;
  Tsignal=0;
  GQ=0;
  QQ=0;
  Num_Event=0;
  Ngenevent=0;
  Ngenevent1=0;
  Ngenevent2=0;
  Ngluino=0;
  Ngsq=0;
  Nsqsq=0;
  NXX=0;
  Nll=0;
  NsqX=0;
  NgX=0;
  Ngsq=0;
  Nsqsb=0;
  Ngsb=0;
  Nsbsb=0;
  Nstst=0;
    kok1=0;
    kok2=0;
    kok3=0;
    kok4=0;
    kok5=0;
    kok6=0;
    kok7=0;
    kok8=0;
    kok9=0;
    kok10=0;
    kok11=0;
    kok12=0;
    kok13=0;
    kok14=0;
    kok15=0;
    kok16=0;
    fsa=0;
    fsb=0;
    fsc=0;
    
    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// initialize histograms
// book histograms for multiplicities of leptons and jets
   hRLeptonMult = new TH2F( "RLeptonMult", "Multiplicity of leptons (Particle.Type->1)", 2000,0,2000,30,0,30);
   hRElectronMult = new TH2F( "RElectronMult", "Multiplicity of electrons (Particle.Type->2) ", 2000,0,2000,30,0,30);
   hRMuonMult = new TH2F( "RMuonMult", "Multiplicity of muons, (Particle.Type->3)", 2000,0,2000,30,0,30);
   hRPhotonMult = new TH2F( "RPhotonMult", "Multiplicity of photons, (Particle.Type->4)", 2000,0,2000,30,0,30);
   hRBJetMult = new TH2F( "RBJetMult", "Multiplicity of b-jets, (Particle.Type->5)", 2000,0,2000,30,0,30);
   hJetMult = new TH2F( "JetMult", "Jet Multiplicity ", 2000,0,2000,30,0,30);
   hJetEnergy = new TH1D( "JetEnergy", "E spectrum of jets ", 50, 0.0, 1000.0);
   hPtEnergy = new TH1D( "PtEnergy", "Pt spectrum of jets ", 50, 0.0, 1000.0);   
   hNRtJets = new TH2F( "RtJets", "Multiplicity of jets, (Particle.Type->7)", 2000,0,2000,30,0,30);
   hMissEnergy = new TH1F( "MissEnergy", "Missing Enegy of ~X_1_0", 2000,0,2000);


// book histograms for PT of the leptons and the 3 leading jets
   hPtElec = new TH1D( "PtElec", "Pt spectrum of electrons", 50, 0.0, 1000.0);
   hPtMuon = new TH1D( "PtMuon", "Pt spectrum of muons", 50, 0.0, 1000.0);
   hPtJet1 = new TH1D( "PtJet1", "Pt spectrum of 1st jet", 50, 0.0, 1000.0);
   hPtJet2 = new TH1D( "PtJet2", "Pt spectrum of 2nd jet", 50, 0.0, 1000.0);
   hPtJet3 = new TH1D( "PtJet3", "Pt spectrum of 3rd jet", 50, 0.0, 1000.0);
   hChi10Mass = new TH1D("Chi10Mass","Mass of Chi10",100,75 ,125);
   hChi10InvMass = new TH1D("Chi10InvMass","E^2-p^2 of Chi10",100,75 ,125);
   hGluinoMass = new TH1D("GluinoMass","Mass of Gluino",100,150,1000);
   hGluinoInvMass = new TH1D("GluinoInvMass","E^2-p^2 of Gluino",100,150,1000);
   hSquarkMass = new TH1D("SquarkMass","Mass of Squark" ,100,100,1000);
   hSquarkInvMass = new TH1D("SquarkInvMass","E^2-p^2 of Squark" ,100,100,1000);
   hqMassfromsq = new TH1D("hqfromsq","Mass of quark from Squark decay" ,100,0,500);

   hLjetPt = new TH1D("Ljetpt", "L Jet  Pt   ", 100, 50, 800);
   hLGenjetPt = new TH1D("LGenjetpt", "L GenJet Pt", 100, 50, 800);
   JetGen = new TH2D("Num of GenJet","Nu of Gen jet vs Event",2000,0,2000,30,0,30);

//book histograms
   hSignal= new TH1F( "Signal", "reco vs mc", 10, 0.0, 10.0);
   hSignal1= new TH1F( "Signal1", "reco vs mc", 10, 0.0, 10.0);
   hGenJetMult = new TH1D( "GenJetMult", "Multiplicity of Gen jets", 30, 0.0, 30.0);
  
// book histograms for MET, ETSum and HT
   hMissingETmc = new TH1D( "MissingETmc", "Missing transverse energyfrom MC", 100, 0.0, 1000.0);
   hMissingET = new TH1D( "MissingET", "Missing transverse energy", 100, 0.0, 1000.0);
   hEtSum = new TH1D( "ETsum", "Transverse energy sum", 100, 0.0, 2000.0);
   hHT = new TH1D( "HT", "Transverse energy sum", 100, 0.0, 2000.0);
   hHemiMass = new TH1D( "HemiMass", "Hemisphere mass", 100, 0.0, 1000.0);

// book histograms for ET distribution of jets correctly and wrongly assigned to hemispheres
   hJetGoodEt = new TH1D( "JetGoodEt", "Et spectrum of Jets correctly ID'ed", 80, 0.0, 800.0);
   hJetWrongEt = new TH1D( "JetWrongEt", "Et spectrum of Jets wrongly ID'ed", 80, 0.0, 800.0);
   hNEvent = new TH1D( "NEvent", "Number of Events", 80, 0, 10);
   hNSMq = new TH1D("NSMq", "Number of SMq", 80, 0, 10);
   hNGluino = new TH1D("NGluino", "Number of gluinos", 80, 0, 10);   
// Initialize user counters
  nTotEvtSelUser = 0;

}

// Called from Destructor:
void UserAnalysis::endAnalysis() {
// Print the user statistics here
 in << endl;
 in << "User statistics:" << endl;
 in << "Number of User selected events = " << nTotEvtSelUser << endl;
 
 	ins<<"//counter for q->~q_L+~q_L"<<"\t"<<(float)kok1/Num_Event<<endl;
	ins<<"//counter for g->~q_L+~q_L"<<"\t"<<(float)kok2/Num_Event<<endl;
	ins<<"//counter for q->~q_R+~q_R"<<"\t"<<(float)kok3/Num_Event<<endl;
	ins<<"//counter for g->~q_R+~q_R"<<"\t"<<(float)kok4/Num_Event<<endl;
	ins<<"//counter for q->~q_L+~g"<<"\t"<<(float)kok5/Num_Event<<endl;
	ins<<"//counter for g->~q_L+~g"<<"\t"<<(float)kok6/Num_Event<<endl;
	ins<<"//counter for q->~q_R+~g"<<"\t"<<(float)kok7/Num_Event<<endl;
	ins<<"//counter for g->~q_R+~g"<<"\t"<<(float)kok8/Num_Event<<endl;
	ins<<"//counter for q->~g+~g"<<"\t"<<"\t"<<(float)kok9/Num_Event<<endl;
	ins<<"//counter for g->~g+~g"<<"\t"<<"\t"<<(float)kok10/Num_Event<<endl;
	ins<<"//counter for q->~q_L+~q_R"<<"\t"<<(float)kok11/Num_Event<<endl;
	ins<<"//counter for g->~q_L+~q_R"<<"\t"<<(float)kok12/Num_Event<<endl;
	ins<<"//counter for q->~q_L+~X_i^0"<<"\t"<<(float)kok13/Num_Event<<endl;
	ins<<"//counter for g->~q_L+~X_i^0"<<"\t"<<(float)kok14/Num_Event<<endl;
	ins<<"//counter for q->~q_R+~X_i^0"<<"\t"<<(float)kok15/Num_Event<<endl;
	ins<<"//counter for g->~q_R+~X_i^0"<<"\t"<<(float)kok16/Num_Event<<endl;  
	ins<<"---------------------Toplam:"<<"\t"<<(float)(kok1+kok2+kok3+kok4+kok5+kok6+kok7+kok8+kok9+kok10+kok11+kok12+kok13+kok14+kok15+kok16)/(float)Num_Event<<endl;
	ins<<"//counter for  jet + MET final states  "<<"\t" <<endl;	
	ins<<"//counter for ~q~q->2 jet + MET"<<"\t"<<fsa<<endl;
	ins<<"//counter for ~q~g->3 jet + MET"<<"\t"<<fsb<<endl;
	ins<<"//counter for ~g~g->4 jet + MET"<<"\t"<<fsc<<endl;
 return;
}    
     
//------------------------------------------------------------------------------
// Methods:
//------------------------------------------------------------------------------
// this method checks whether the L1 trigger is accepted
bool UserAnalysis::L1Driver(MrEvent* EventData)
{    
// this module is dummy and accepts the OR of all L1 trigger bits
// note that, if the L1 trigger bit vector does not exist, the event is accepted
// (behaviour can be changed below)
  
  unsigned int fired(0);
  bool acceptedL1 = false;

  std::vector<int> bits = EventData->l1Bits();
  //  cout << "TriggerProcessor: bits = ";
  if (bits.size() > 0){
    for(unsigned int i=0; i<bits.size(); i++) {
      //    cout << bits[i];
      if(bits[i]) fired++;
    }
  }
  //  cout << endl;

  if(fired > 0) acceptedL1 = true;
  //cout << "TriggerProcessor: acceptedL1 = " << (int) acceptedL1 << endl;
  EventData->setTriggeredL1(acceptedL1);

  return acceptedL1;

}

//------------------------------------------------------------------------------
// this method checks whether the HLT is accepted
bool UserAnalysis::HLTDriver(MrEvent* EventData)
{
   
  // this module is dummy and accepts the OR of all HLT trigger bits
  // note that, if the HLT trigger bit vector does not exist, the event is accepted
  // (behaviour can be changed below)


  unsigned int fired(0);
  bool acceptedHLT = false;
  
  std::vector<int> bits = EventData->hltBits();
  //  cout << "TriggerProcessor: bits = ";
  if (bits.size() > 0){
    for(unsigned int i=0; i<bits.size(); i++) {
      //    cout << bits[i];
      if(bits[i]) fired++;
    }
  }
  //  cout << endl;

  if(fired > 0) acceptedHLT = true;
  //cout << "TriggerProcessor: acceptedHLT = " << (int) acceptedHLT << endl;
  EventData->setTriggeredHLT(acceptedHLT);
  return acceptedHLT;

}
  
//------------------------------------------------------------------------------
// this method is called for every event
void UserAnalysis::doAnalysis(MrEvent* theEventData)
{
  EventData = theEventData;

  std::vector<MrParticle*> & MCData = *(EventData->mcData());

Num_Event++;
//getting MC information from MCData,
///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	in << "Event: " << Num_Event << endl;
	in << "----------------" << "Genereted level ----------------------------" << endl;
	
int say_0=0,say_1=0,say_2=0,say_3=0,say_4=0,say_5=0,say_6=0;
// 	int kok1 = 0; //counter for q->~q_L+~q_L
// 	int kok2 = 0; //counter for g->~q_L+~q_L 
	for(int i = 0; i < (int) MCData.size(); i++) {
if ( abs(MCData[i]->pid()) > 1000000 && abs(MCData[i]->pid()) < 1000007 && abs(MCData[i+1]->pid()) 
     > 1000000 && abs(MCData[i+1]->pid()) < 1000007 ){
    if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
      if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 7) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok1; } 
         if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){ ++kok2; }
		for(int j = i+2; j < (int) MCData.size(); j++) {	
			if ( abs(MCData[j]->pid())==1000022&&(MCData[j]->motherIndex()==i
			     ||MCData[j]->motherIndex()==i+1)) {
			       say_0++;
			       if(say_0==2)fsa++;
			       }
	         }
	}
  } 
  
if ( abs(MCData[i]->pid()) > 2000000 && abs(MCData[i]->pid()) < 2000005 &&
     abs(MCData[i+1]->pid()) > 2000000 && abs(MCData[i+1]->pid()) < 2000005 ){
  if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
     if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 7) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok3; } 
       if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok4; }

             for(int j = i+2; j < (int) MCData.size(); j++) {	
			if ( abs(MCData[j]->pid())==1000022 &&(MCData[j]->motherIndex()==i
			     ||MCData[j]->motherIndex()==i+1)) {
			       say_0++;
			       if(say_0==2)fsa++;
			       }
	         }  
   }
} 

if ( (abs(MCData[i]->pid()) == 1000021 && abs(MCData[i+1]->pid()) > 1000000 && abs(MCData[i+1]->pid()) < 1000005) ||
	(abs(MCData[i]->pid()) < 1000005) && abs(MCData[i]->pid()) > 1000000 && abs(MCData[i+1]->pid()) == 1000021){
 if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){ 
   if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 5) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok5; } 
     if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok6; }
         for(int j = i+2; j < (int) MCData.size(); j++) {	
		if ( abs(MCData[j]->pid())==1000022 &&((abs(MCData[MCData[j]->motherIndex()]->pid())>1000000
		    && abs(MCData[MCData[j]->motherIndex()]->pid())<1000005)||(abs(MCData[MCData[j]->motherIndex()]->pid())>2000000
		    && abs(MCData[MCData[j]->motherIndex()]->pid())<2000005)||abs(MCData[MCData[j]->motherIndex()]->pid())==1000021)
		    &&(MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->motherIndex()==i ||
		     MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->motherIndex()==i+1)) {
			       say_1++;
		         
		 }
		/*  else if(abs(MCData[j]->pid())==1000022 &&(MCData[MCData[j]->motherIndex()]->pid()==i||
		  MCData[MCData[j]->motherIndex()]->pid()==i+1))say_1++;*/
		 
		 if(say_1==2)fsb++;
		 
	
	   }
  
   
   }
} 

if ( (abs(MCData[i]->pid()) == 1000021 && abs(MCData[i+1]->pid()) > 2000000 && abs(MCData[i+1]->pid()) < 2000005) ||
    (abs(MCData[i]->pid()) < 2000005 && abs(MCData[i]->pid()) > 2000000 && abs(MCData[i+1]->pid()) == 1000021) ){
  if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
    if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 7) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok7;} 
     if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok8; }
 		 
       
        for(int j = i+2; j < (int) MCData.size(); j++) {	
		if ( abs(MCData[j]->pid())==1000022 &&((abs(MCData[MCData[j]->motherIndex()]->pid())>1000000
		    && abs(MCData[MCData[j]->motherIndex()]->pid())<1000005)||(abs(MCData[MCData[j]->motherIndex()]->pid())>2000000
		    && abs(MCData[MCData[j]->motherIndex()]->pid())<2000005)||abs(MCData[MCData[j]->motherIndex()]->pid())==1000021)
		    && (MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->motherIndex()==i ||
		       MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->motherIndex()==i+1)) {
			       say_1++;
		         
		 }
		/*  else if(abs(MCData[j]->pid())==1000022 &&(MCData[MCData[j]->motherIndex()]->pid()==i||
		  MCData[MCData[j]->motherIndex()]->pid()==i+1))say_1++;*/
		 
		 if(say_1==2)fsb++;
		 

	   }
   
   
   
  }
} 

if ( abs(MCData[i]->pid()) == 1000021 && abs(MCData[i+1]->pid()) == 1000021 ){
   if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
      if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 5) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok9; } 
      if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok10; }
      
          for(int j = i+2; j < (int) MCData.size(); j++) {	
		if ( abs(MCData[j]->pid())==1000022 ){
		   if((abs(MCData[MCData[j]->motherIndex()]->pid())>1000000
		    && abs(MCData[MCData[j]->motherIndex()]->pid())<1000005)||(abs(MCData[MCData[j]->motherIndex()]->pid())>2000000
		    && abs(MCData[MCData[j]->motherIndex()]->pid())<2000005)) {
		    cout<<"bulduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuum"<<
		     /* if( MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->motherIndex()==i ||
		         MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->motherIndex()==i+1) */ 
			 say_2++;
		   }      
		 } 
		 
		 if(say_2==2)fsc++;
		 

	   }
      
      
   }
} 

if ( (abs(MCData[i]->pid()) > 1000000 && abs(MCData[i]->pid()) < 1000005 && 
      abs(MCData[i+1]->pid()) > 2000000 && abs(MCData[i+1]->pid()) < 2000005)||
     (abs(MCData[i]->pid()) < 2000005) && abs(MCData[i]->pid()) > 2000000 && 
      abs(MCData[i+1]->pid()) > 1000000 && abs(MCData[i+1]->pid()) < 1000005){
     
  if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
    if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 7) && 
        (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok11; } 
      if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok12; }
      
  }
} 
if ( (abs(MCData[i]->pid()) > 1000000 && abs(MCData[i]->pid()) < 1000007 && (abs(MCData[i+1]->pid()) == 1000022 || abs(MCData[i+1]->pid()) == 1000023 || abs(MCData[i+1]->pid()) == 1000025 || abs(MCData[i+1]->pid()) == 1000035) ) ||
	(abs(MCData[i]->pid()) == 1000022 || abs(MCData[i]->pid()) == 1000023 || abs(MCData[i]->pid()) == 1000025 || abs(MCData[i]->pid()) == 1000035) && abs(MCData[i+1]->pid()) > 1000000 && abs(MCData[i+1]->pid()) < 1000007){
if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 7) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok13; } 
if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok14;}
			}
		}
 
if ( (abs(MCData[i]->pid()) > 2000000 && abs(MCData[i]->pid()) < 2000007 && (abs(MCData[i+1]->pid()) == 1000022 ||
     abs(MCData[i+1]->pid()) == 1000023 || abs(MCData[i+1]->pid()) == 1000025 ||abs(MCData[i+1]->pid()) == 1000035) ) ||
     ((abs(MCData[i]->pid()) == 1000022 || abs(MCData[i]->pid()) == 1000023 || abs(MCData[i]->pid()) == 1000025 || 
     abs(MCData[i]->pid()) == 1000035) && abs(MCData[i+1]->pid()) > 2000000 && abs(MCData[i+1]->pid()) < 2000007)){
if ( MCData[i]->motherIndex() == MCData[i+1]->motherIndex() ){
if ((abs(MCData[MCData[i]->motherIndex()]->pid()) < 7) && (abs(MCData[MCData[i]->motherIndex()]->pid()) > 0)){ ++kok15; } 
if ( abs(MCData[MCData[i]->motherIndex()]->pid()) == 21 ){++kok16;}
			}
		}
	}

	
	in <<"kok1:"<<kok1<<"\t"<<"-kok2:"<<kok2<<"\t"<<"-kok3:"<<kok3<<"\t"<<" -kok4:"<<kok4 <<"\t"<<"-kok5:"<<kok5<<"\t"<<"-kok6:"<<kok6<<"\t";
	in <<"-tok7:"<<kok7<<"\t"<<"-kok8:"<<kok8<<"\t"<< "-kok9:"<<kok9<<"\t"<<"-kok10:"<<kok10<<"\t"<< "-kok11:"<<kok11<<"\t"<<"-kok12:"<<kok12<<"\t";
	in <<"-kok13:"<<kok13<<"\t"<< "-kok14:"<<kok14<<"\t"<<"-kok15:"<<kok15<<"\t"<<"-kok16:"<<kok16<<endl;
	in << endl;


 

//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxx Ferhat MC Statistics xxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//~g~g events counter


	std::vector<MrParticle*> & RecoData = *(EventData->recoData());
	in << "RecoData:" << (int) RecoData.size() << endl;
	vector<int> indxMC;
	vector<int> indxRC;
	vector<int> iMatchindx;
	vector<int>::iterator match;
	vector<int>::iterator iter;
	vector<int> MCsq;
	vector<int>::iterator MCiter;
	nEventsAfterCuts = 0;
	vector<int> GenjetIndex2;
	vector<int> GenjetIndex3;
//	Multiplicity of Partilces in the RecoData
    int NRElectrons =0;
    int NRMuons =0;
    int NRPhotons =0;
    int NRBJets=0;
    int NRecJets=0;
    int NRtJets=0;
   // int njets=0;

int say0=0;
int Tsay=0;
//~g~q events counters
int say1=0;
int Tsay1=0;
//~X counter
int say2=0;
//~b counter
int say3=0;
//~t counter
int say4=0;
//~l counter
int say5=0;
for(int i=0;i<(int) MCData.size();i++){

 if(abs(MCData[i]->pid())==1000021){
  say0++;
   for(int j=i+1;j<(int) MCData.size();j++){
     if (((abs(MCData[j]->pid()) >= 1000001 && abs(MCData[j]->pid()) < 1000005) ||(abs(MCData[j]->pid()) >= 2000001 && abs(MCData[j]->pid()) < 2000005) )&&MCData[j]->motherIndex()==i){
	 ins<<"~g->~q:   "<<abs(MCData[MCData[j]->motherIndex()]->pid())<<"--->"<<MCData[j]->pid() << endl;
	 MCsq.push_back(j);
		}
	}
}
// For the events that qluon decays to squark.
    else if( ((abs(MCData[i]->pid())>=1000001 && abs(MCData[i]->pid())<1000005)||(abs(MCData[i]->pid())>=2000001 && 
    abs(MCData[i]->pid())<2000005))&&abs(MCData[MCData[i]->motherIndex()]->pid())< 22){
    say1++;
        for(int j=i+1;j<(int) MCData.size();j++){
    	    if ( abs(MCData[j]->pid()) == 1000022 && MCData[j]->motherIndex()==i){
	     ins<<"sonuuuc"<<abs(MCData[MCData[j]->motherIndex()]->pid())<<"--->"<<MCData[j]->pid()<<endl;
	     Tsay1++;
		}
	} 
}

    else if(((abs(MCData[i]->pid())>=1000022 && abs(MCData[i]->pid())<1000026)
    	   ||abs(MCData[i]->pid())==1000035||abs(MCData[i]->pid())==1000037)&&
	   abs(MCData[MCData[i]->motherIndex()]->pid())< 22){
	   say2++;
	   }

    else if((abs(MCData[i]->pid())==1000005||abs(MCData[i]->pid())==2000005)&&
	   abs(MCData[MCData[i]->motherIndex()]->pid())< 22){
    say3++;
    }
    
    else if((abs(MCData[i]->pid())==1000006||abs(MCData[i]->pid())==2000006)&&
	   abs(MCData[MCData[i]->motherIndex()]->pid())< 22){
    say4++;
    }
    
    else if((abs(MCData[i]->pid())==1000011||abs(MCData[i]->pid())==2000011||
             abs(MCData[i]->pid())==1000013||abs(MCData[i]->pid())==2000013||
             abs(MCData[i]->pid())==1000015||abs(MCData[i]->pid())==2000015||
             abs(MCData[i]->pid())==1000012||abs(MCData[i]->pid())==2000012||
             abs(MCData[i]->pid())==1000014||abs(MCData[i]->pid())==2000014||
             abs(MCData[i]->pid())==1000016||abs(MCData[i]->pid())==2000016)&&
	     abs(MCData[MCData[i]->motherIndex()]->pid())< 22){
             say5++;
    }
}

for( MCiter=MCsq.begin(); MCiter!= MCsq.end(); MCiter++){
  if(abs(MCData[MCData[*MCiter]->motherIndex()]->pid()) == 1000021){
    for(int k=*MCiter+1;k<(int) MCData.size();k++){
      if (abs(MCData[k]->pid()) == 1000022 && MCData[k]->motherIndex()==*MCiter){
      Tsay++;
      ins<<"bulduuuuum\t"<<Tsay<<"motherindex"<< MCData[k]->motherIndex()<<"pid"<<MCData[MCData[k]->motherIndex()]->pid()<<endl;
      ins<<"bulduuuuum\t"<<Tsay<<endl;
			}	
		}
	}
}
 
if(say0==2){Ngluino++;			//~g~g 
 if(Tsay==2) Ngenevent++; }		//~g~g->q~q q~q->qqqq 2chi_10
if(say0==1 && say1==1){ Ngsq++;		//~q~g
  if(Tsay==1&&Tsay1==1)Ngenevent1++;}	//~q~g->qchi_10 ~qq->qqq 2chi_10
if(say1==2){ Nsqsq++;			//~q~q
if(Tsay1==2)Ngenevent2++; }		//~q~q->qchi_10 qchi_10
if(say0==1&&say2==1){ NgX++; }		//~g~X
if(say1==1&&say2==1){ NsqX++; }		//~q~X
if(say2==2){ NXX++; }			//~X~X
if(say3==2){ Nsbsb++; }			//~b~b
if(say0==1&&say3==1){ Ngsb++; }		//~g~b
if(say1==1&& say3==1){ Nsqsb++; }	//~q~b
if(say4==2){ Nstst++; }			//~t~t
if(say5==2){ Nll++; }			//~l~l
 ins<<"~g ~g->\t"<<Ngluino<<endl; 
 ins<<"~g ~q->\t"<<Ngsq<<endl;  
 ins<<"~q ~q->\t"<<Nsqsq<<endl;
 ins<<"~X ~g->\t"<<NgX<<endl; 
 ins<<"~X ~q->\t"<<NsqX<<endl;  
 ins<<"~X ~X->\t"<<NXX<<endl;
 ins<<"~b ~b->\t"<<Nsbsb<<endl; 
 ins<<"~g ~b->\t"<<Ngsb<<endl;  
 ins<<"~t ~t->\t"<<Nstst<<endl;  
 ins<<"~l ~l->\t"<<Nll<<endl;  
 ins<<"final states"<<endl;
 ins<<"~g ~g->~q q ~q q ->4q chi_10\t"<<Ngenevent<<endl;
 ins<<"~g ~q->q chi_10 q ~q->3q chi_10\t"<<Ngenevent1<<endl;
 ins<<"~g ~q->q chi_10 q chi_10\t"<<Ngenevent2<<endl;
 ins<<"Event\t"<<Num_Event<<endl;
 ins<<"~g ~g->\t"<<Ngluino<<endl; 
 ins<<"~g ~q->\t"<<Ngsq<<endl;  
 ins<<"~q ~q->\t"<<Nsqsq<<endl;
 ins<<"~X ~g->\t"<<NgX<<endl; 
 ins<<"~X ~q->\t"<<NsqX<<endl;  
 ins<<"~X ~X->\t"<<NXX<<endl;
 ins<<"~b ~b->\t"<<Nsbsb<<endl; 
 ins<<"~g ~b->\t"<<Ngsb<<endl;  
 ins<<"~t ~t->\t"<<Nstst<<endl;  
 ins<<"~l ~l->\t"<<Nll<<endl;
 ins<<"final states"<<endl;
 ins<<"~g ~g->~q q ~q q ->4q chi_10\t"<<Ngenevent<<endl;
 ins<<"~g ~q->q chi_10 q ~q->3q chi_10\t"<<Ngenevent1<<endl;
 ins<<"~g ~q->q chi_10 q chi_10\t"<<Ngenevent2<<endl;
 ins<<"Event=\t"<<Num_Event<<endl;
 
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxxx END of Ferhat MC Statistics xxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//}  
  
 
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxx RECO Data Statistics xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



      for (int i = 0; i < (int) RecoData.size(); i++){
      if (RecoData[i]->particleType() == 10) { NRElectrons++; }
      if (RecoData[i]->particleType() == 20) { NRMuons++; }
      if (RecoData[i]->particleType() == 40) { NRPhotons++; }
      if (RecoData[i]->particleType() == 50) { NRBJets++; }
      if (RecoData[i]->particleType() == 60) { NRecJets++; }
      if (RecoData[i]->particleType() == 70) { NRtJets++; }
      //if ((RecoData[i]->particleType()==50)||(RecoData[i]->particleType()==60)||(RecoData[i]->particleType()==70)) { njets++;}
//       in << "RecoData[" << i << "]->particleType: " << RecoData[i]->particleType() << endl;
    }
	//in << "njets according to :" << njets << endl;
	//in << "iJet" << "\t" << "ptjet" << "\t" << "jetIndx" << "\t" << "etajet" << endl;
	int nJets = EventData->numJets();
	for (int iJet = 1; iJet <= nJets; iJet++){
	double ptjet = EventData->ptJet(iJet);
	int jetindex = EventData->indexRecoJet(iJet);
// 	double EJet = EventData->emEnergyFraction(iJet);
// 	double EJet = EventData->energyFractionHadronic(iJet);	
	float etajet = RecoData[jetindex]->eta();
	hPtEnergy->Fill(ptjet);
	ins << iJet << "\t" << setprecision(4) << ptjet << "\t" << jetindex << "\t" << etajet << endl;
	}
	hJetMult->Fill(Num_Event,nJets);
	//hJetEnergy->Fill(Enjet);   
	hRLeptonMult->Fill(Num_Event,NRElectrons+NRMuons);
	hRElectronMult->Fill(Num_Event,NRElectrons);
 	hRMuonMult->Fill(Num_Event,NRMuons);
	hRPhotonMult->Fill(Num_Event,NRPhotons);
	hRBJetMult->Fill(Num_Event,NRBJets);
	//hRJetMult->Fill(Num_Event,NRecJets);
	hNRtJets->Fill(Num_Event,NRtJets);


/*
int genN2jet = 0;
int genN3jet = 0;
// // float LGenjet = 0.;
    for(int j = 2 ; j < (int) MCData.size(); j++){
      if((abs(MCData[j]->pid()) > 0) && (abs(MCData[j]->pid()) < 7) && ( MCData[j]->status() == 2 ) ){  
// 	if (LGenjet < MCData[j]->pt()) LGenjet = MCData[j]->pt();
// 		genN2jet++;
		GenjetIndex2.push_back(j);
             }
      if((abs(MCData[j]->pid()) > 0) && (abs(MCData[j]->pid()) < 7) && ( MCData[j]->status() == 3 ) ){ 
// 	if (LGenjet < MCData[j]->pt()) LGenjet = MCData[j]->pt();
// 		genN3jet++;
		GenjetIndex3.push_back(j);
		}	     
	}     


      //do not count as jet too near in DeltaR
       if (GenjetIndex2.size() > 1){
       for(int i=0; i < (int) GenjetIndex2.size(); i++){
         if (GenjetIndex2.size() >= 0){
           float eta1 = MCData[GenjetIndex2[i]]->eta();
           float phi1 = MCData[GenjetIndex2[i]]->phi();
           for(int j=i+1; j<(int) GenjetIndex2.size(); j++){
	     if (GenjetIndex2[j] >= 0){
               float eta2 = MCData[GenjetIndex2[j]]->eta();
               float phi2 = MCData[GenjetIndex2[j]]->phi();
               float deltaR = GetDeltaR(eta1, eta2, phi1, phi2);
               if (deltaR < 0.5){ genN2jet--; }
             }
	   }
         }
       }
     }

       if (GenjetIndex3.size() > 1){
       for(int i=0; i < (int) GenjetIndex3.size(); i++){
         if (GenjetIndex3.size() >= 0){
           float eta1 = MCData[GenjetIndex3[i]]->eta();
           float phi1 = MCData[GenjetIndex3[i]]->phi();
           for(int j=i+1; j<(int) GenjetIndex3.size(); j++){
	     if (GenjetIndex3[j] >= 0){
               float eta2 = MCData[GenjetIndex3[j]]->eta();
               float phi2 = MCData[GenjetIndex3[j]]->phi();
               float deltaR = GetDeltaR(eta1, eta2, phi1, phi2);
               if (deltaR < 0.5){ genN3jet--; }
             }
	   }
         }
       }
     }
     
in << "MC Sayımı" <<"\t" << "xxxxxxx" << "\t"<< "\t" << "DeltaRDüzeltme" << endl;
in << "GenjetIndex2.size(): " << GenjetIndex2.size()  << "|" << "genN2jet: " << genN2jet << "|" << "genN2jet: " << genN2jet <<endl;
in << "GenjetIndex3.size(): " << GenjetIndex3.size()  << "|" << "genN3jet: " << genN3jet << "|" << "genN3jet: " << genN2jet <<endl;
*/

//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxx END of RECO Data Statistics xxxxxxxxxxxxxxxxxxxxxxxxxxx
//		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx






//xxxxMatching reco and MC particles that comes from ~g~g->~q~q->chi_10 + 4q
//burda yapmaya calisilan kanallar icin mc ile reconstruct parcaciklari eslemek ve eslenen olay sayisini
//  iMatch=-1;
// indx=-1;
signal=0;
Tsignal=0;
//if(say==2
//  &&Tsay == 2
	//){
  ins<< "####################" <<endl;
  ins<< "RECo match MC Truth" <<endl;
 // in<< "nbr of jet->" <<NJets<<endl;
  ins<< "nbr of jet->" <<NRecJets<<endl;
  ins<< "################" <<endl;
  ins<< "event olusan parcaciklar" <<endl;
  ins<< "nbr of Bjet->" <<NRBJets<<endl;
  ins<< "nbr of leptons->" <<NRElectrons+NRMuons<<endl;
  ins<< "nbr of jet->" <<NRecJets<<endl;
  ins<< "################" <<endl; 

      if(NRElectrons+NRMuons==0 && NRBJets==0 /*&& NRtJets==0 */&& NRecJets>=2){
      ins<<"candidate!!"<<endl;
      ins<<"candidate!!"<<endl;
      GQ++;
      ins<<"RECo data size=>"<<(int) RecoData.size()<<endl;

  for(int i = 0; i < (int) RecoData.size() ;i++){
   ins<<"RECo match MC=>"<<RecoData[i]->partonIndex()<<endl;
  if(RecoData[i]->partonIndex()<0)continue;
  ins<<"RECo match MC=>"<<MCData[RecoData[i]->partonIndex()]->pid()<<endl;
  ins<<"RECo match MC=>"<<MCData[RecoData[i]->partonIndex()]->pid()<<endl;
  ins<<"REComatch MC =>"<<RecoData[i]->partonIndex()<<endl;
    if(RecoData[i]->partonIndex()>0){
	for(int j = RecoData[i]->partonIndex(); j >0  ;j--){
  		if(MCData[RecoData[i]->partonIndex()]->motherIndex()==j){
                   if(abs(MCData[j]->pid())>= 1 && abs(MCData[j]->pid()) <5||abs(MCData[j]->pid())==21){
		      if((abs(MCData[MCData[j]->motherIndex()]->pid())> 1000000&&
		         abs(MCData[MCData[j]->motherIndex()]->pid())< 1000005)||(abs(MCData[MCData[j]->motherIndex()]->pid())> 2000000
		         && abs(MCData[MCData[j]->motherIndex()]->pid())< 2000005)){
		      
		        if(abs(MCData[MCData[MCData[j]->motherIndex()]->motherIndex()]->pid())==1000021){
		          signal++;
		          ins<<"Signal=>"<<signal<<endl;
		         indxMC.push_back(MCData[j]->motherIndex());
		       } 
		      
		   }
		   
		 }
	       }
	     }
	   }
	 } 
	
   for(iter = indxMC.begin(); iter != indxMC.end(); iter++){
   	for(int j = *iter+1; j <(int) MCData.size() ;j++){
	  if(abs(MCData[j]->pid())==1000022&&MCData[j]->motherIndex()==*iter){
	  Tsignal++; 
	  if(Tsignal==2){QQ++;}
	  ins<<"->"<<Tsignal<<endl;
	  ins<<"->"<<Tsignal<<endl;
	     }
	   }
	 }
       }
  //   } 
//}

  ins<<"reconstructed/~g~g->~q q ~q q ->4q chi_10->"<<GQ<<endl;
  ins<<"reconstructedand matched with MC/~g ~g->~q q ~q q ->4q chi_10->"<<QQ<<endl;


PtSumJets=0.0;
EtSumJet=0.0;
 if(Tsignal==2){
  hSignal->Fill(5);
  for(int i = 0; i < (int) RecoData.size() ;i++){
   if(RecoData[i]->particleType() ==50){indxRC.push_back(i);}
  }
// int nJets = EventData->numJets();
 ins<<"----------------------"<<endl;
 ins<<"----------------------"<<endl;
 ins<<"nbr of jets"<<nJets<<endl; 
 for(match = indxRC.begin(); match != indxRC.end(); match++){
  PtSumJets+=RecoData[*match]->pt();
 EtSumJet+=RecoData[*match]->energy();
 }
 EtSumJet=EtSumJet+ EventData->metCaloMod();
 ins<<"EtSumJet"<<EtSumJet<<endl; 
 ins<<"----------------------"<<endl;
 ins<<"----------------------"<<endl;
 
} 

// This produces some simple plots as examples
// Put your event selection here *****************
// Overall condition on MET (to illustrate usage of parameters)
    float metchk = EventData->metRecoilMod();
    if (metchk < user_metMin){return;}
    
    // count number of selected events for final statistics
    nTotEvtSelUser++;

 

    // plot the pT of the leptons and the 3 leading jets
    for(int i = 0; i < (int) RecoData.size() ;i++){
      if (RecoData[i]->particleType() == 10){
        hPtElec->Fill(RecoData[i]->pt());
      }
      if (RecoData[i]->particleType() == 20){
        hPtMuon->Fill(RecoData[i]->pt());
      }
    }
//    int nJets = EventData->numJets();
    if (nJets > 3){nJets = 3;}
    for (int iJet = 1; iJet <= nJets; iJet++){
      float ptjet = EventData->ptJet(iJet);
      if (iJet == 1){hPtJet1->Fill(ptjet);}
      if (iJet == 2){hPtJet2->Fill(ptjet);}
      if (iJet == 3){hPtJet3->Fill(ptjet);}
    }
    
    if (nJets > 0){
      // make plots of Missing energy from MC and recoil
      float metmc = EventData->metMCMod();
      hMissingETmc->Fill(metmc);
      float metrec = EventData->metRecoilMod();
      hMissingET->Fill(metrec);
  
      // make a plot of ETsum and HT (using the MET from recoil)
      float etSum = EventData->etSumRecoil();
      float ht = EventData->htRecoil();
      hEtSum->Fill(etSum);
      hHT->Fill(ht);
  
      // make a plot of the largest hemisphere mass
      float mass1 = EventData->hemiMass1();
      float mass2 = EventData->hemiMass2();
      float mass = mass1 > mass2 ? mass1 : mass2;
      hHemiMass->Fill(mass);
    }
    
//    in << " Now look at hemispheres, njets = " << nJets << endl;
    // pT distribution of the 2 leading jets correctly and wrongly assigned to hemispheres
    // example of access to the hemisphere information
    if (nJets >= 2) {
      int firstsusymother[2] = {-1, -1};
//    in << " pointer to EventData " << EventData << endl;
      firstsusymother[0] = EventData->indexMatchedSusyMother1();
      firstsusymother[1] = EventData->indexMatchedSusyMother2();
//    in << " firstsusymother done " << endl;
      int indjet1 = EventData->indexRecoJet(1);
      int indjet2 = EventData->indexRecoJet(2);
//    in << " indjet done " << indjet1 << " " << indjet2 << endl;
      int hemijet1 = RecoData[indjet1]->hemisphere();
      int hemijet2 = RecoData[indjet2]->hemisphere();
//    in << " hemijet done " << endl;
      int susymotherjet1 = FindTopSusyMother(RecoData[indjet1]->partonIndex());
      int susymotherjet2 = FindTopSusyMother(RecoData[indjet2]->partonIndex());
//    in << " susymotherjet done " << endl;
      if (hemijet1 > 0) {
        float ptjet1 = EventData->ptJet(1);
        if (susymotherjet1 > 0 && susymotherjet1 == firstsusymother[hemijet1-1]) {
          hJetGoodEt->Fill(ptjet1);
        }
        else{
          hJetWrongEt->Fill(ptjet1);
        }
      }
      if (hemijet2 > 0) {
        float ptjet2 = EventData->ptJet(2);
        if (susymotherjet2 > 0 && susymotherjet2 == firstsusymother[hemijet2-1]) {
           hJetGoodEt->Fill(ptjet2);
        }
        else{
           hJetWrongEt->Fill(ptjet2);
        }
      }
    } 

  return;
}

//------------------------------------------------------------------------------

int UserAnalysis::FindProducedSusyParticles(int firstsusy[])
{ // finds the produced susy particles
  // and returns their index IN MCData into an array
  std::vector<MrParticle*> & MCData = *(EventData->mcData());

  int nfound = 0;
  for (int j = 0; j < (int) MCData.size(); j++){
    if (abs(MCData[j]->pid()) > 1000000 &&
        abs(MCData[MCData[j]->motherIndex()]->pid()) < 1000000){
      firstsusy[nfound] = j;
      nfound++;
    }
  }

  return nfound;

}

//------------------------------------------------------------------------------

int UserAnalysis::FindTopSusyMother(int current)
{ // goes up to highest susy particle
  // current = index of current object in the MCData vector
  //using MrParticle class;
  std::vector<MrParticle*> & MCData = *(EventData->mcData());

 if(current <2) return -1;
 int mother = MCData[current]->motherIndex();
 if(mother <2){
   return -1;
 } else if (abs(MCData[mother]->pid()) < 22 && abs(MCData[current]->pid()) > 1000000) {
    return current; 
 } else {
    return FindTopSusyMother(mother);
 }

}

//------------------------------------------------------------------------------
int UserAnalysis::FindLowSusyMother(int current)
{ // goes up to the first squark (including stop) or gluino on the path
  // current = index of current object in the MCData vector
  //using MrParticle class;
 std::vector<MrParticle*> & MCData = *(EventData->mcData());

 if(current <2) return -1;
 int mother = MCData[current]->motherIndex();
 if(mother <2){
   return -1;
 } else if ( (abs(MCData[current]->pid()) >= 1000001 && abs(MCData[current]->pid()) <= 1000006) || 
      (abs(MCData[current]->pid()) >= 2000001 && abs(MCData[current]->pid()) <= 2000006) ||
        abs(MCData[current]->pid()) == 1000021 ) {
    return current; 
 } else {
    return FindLowSusyMother(mother);
 }
}

//------------------------------------------------------------------------------
int UserAnalysis::FirstSMParton(int current)
{ // goes up to the first quark produced in squark or gluino decay
  // current = index of current object in the MCData vector
  //using MrParticle class;
  std::vector<MrParticle*> & MCData = *(EventData->mcData());


 if(current <2) return -1;
 int mother = MCData[current]->motherIndex();
 if(mother <2){
   return -1;
 } else if ( (abs(MCData[mother]->pid()) >= 1000001 && abs(MCData[mother]->pid()) <= 1000006) || 
      (abs(MCData[mother]->pid()) >= 2000001 && abs(MCData[mother]->pid()) <= 2000006) ||
        abs(MCData[mother]->pid()) == 1000021 ) {
   if(abs(MCData[current]->pid()) >= 1 && abs(MCData[current]->pid()) <= 6 ){
    return current; 
    } else {return -1;}
 } else {
    return FirstSMParton(mother);
 }
}

//------------------------------------------------------------------------------
bool UserAnalysis::ComesFromSquark(int imc)
{
 // returns true if the LowSusyMother is a squark
 // imc = index of current object in the MCData vector
 //using MrParticle class;
  std::vector<MrParticle*> & MCData = *(EventData->mcData());


 int mother = FindLowSusyMother(imc);
 if (mother<2) {return false;}
 if ((abs(MCData[mother]->pid()) >= 1000001 && abs(MCData[mother]->pid()) <= 1000006) || 
     (abs(MCData[mother]->pid()) >= 2000001 && abs(MCData[mother]->pid()) <= 2000006) ) {
   return true;
  } else { return false;}
}

//------------------------------------------------------------------------------
bool UserAnalysis::ComesFromGluino(int imc)
{
 // returns true if the LowSusyMother is a gluino
 // imc = index of current object in the MCData vector
 //using MrParticle class;
 std::vector<MrParticle*> & MCData = *(EventData->mcData());

 int mother = FindLowSusyMother(imc);
 if (mother<2) {return false;}
 if (abs(MCData[mother]->pid()) == 1000021)  {
  return true;
 } else { return false;}
}

//------------------------------------------------------------------------------
int UserAnalysis::FindNearestJet(int ichk)
{
// Looks for the nearest jet in deltaR to a given object
// and returns its RecoData index 
// returns -1 if no nearest jet

  std::vector<MrParticle*> & RecoData = *(EventData->recoData());

  int iJetMin = -1;
  if (ichk < 0){return iJetMin;}
  
  float deltaRmin = 999.;
  for(int i = 0; i < (int) RecoData.size(); i++){
   if(RecoData[i]->particleType() >= 50
      && RecoData[i]->particleType() <= 79){
    float deltaR = GetDeltaR(RecoData[ichk]->eta(), RecoData[i]->eta(), 
                             RecoData[ichk]->phi(), RecoData[i]->phi());
    if (deltaR < deltaRmin && i != ichk){
      deltaRmin = deltaR;
      iJetMin = i;
    }
   }
  }
  
  return iJetMin;

}

//------------------------------------------------------------------------------
float UserAnalysis::GetPtwrtJet(int ichk, int iJet)
{
// Computes the Pt of object ichk wrt the direction of object iJet
    std::vector<MrParticle*> & RecoData = *(EventData->recoData());
  
    if (ichk < 0 || iJet < 0){return -1.;}
    
    float plwrtJet = (RecoData[ichk]->px()*RecoData[iJet]->px() +
                      RecoData[ichk]->py()*RecoData[iJet]->py() +
                      RecoData[ichk]->pz()*RecoData[iJet]->pz() )
                    / RecoData[iJet]->p();
//    in << " plwrtJet = " << plwrtJet
//         << " cosTheta = " << plwrtJet/RecoData[ichk]->p() << endl;
    float ptwrtJet = sqrt(RecoData[ichk]->p()*RecoData[ichk]->p() -
                          plwrtJet*plwrtJet);
//    in << " ptwrtJet = " << ptwrtJet << endl;

 return ptwrtJet;

}

//------------------------------------------------------------------------------
void UserAnalysis::AddToJet(int ichk)
{
// adds an object to its nearest jet
std::vector<MrParticle*> & RecoData = *(EventData->recoData());
int iJet = FindNearestJet(ichk);
  
  if (ichk >= 0 && iJet >= 0) {
   RecoData[iJet]->setPx(RecoData[iJet]->px() + RecoData[ichk]->px());
   RecoData[iJet]->setPy(RecoData[iJet]->py() + RecoData[ichk]->py());
   RecoData[iJet]->setPz(RecoData[iJet]->pz() + RecoData[ichk]->pz());
   RecoData[iJet]->setEnergy(RecoData[iJet]->energy() + RecoData[ichk]->energy());
   // ??? or do we want to keep the jets massless?
   //RecoData[iJet]->setEnergy(RecoData[iJet]->p() );
	}
  return;
}

//------------------------------------------------------------------------------
float UserAnalysis::DeltaPhi(float v1, float v2)
{
// Computes the correctly normalized phi difference
// v1, v2 = phi of object 1 and 2
float diff = fabs(v2 - v1);
float corr = 2*acos(-1.) - diff;
if (diff < acos(-1.)){ return diff;} else { return corr;} 
}

//------------------------------------------------------------------------------
float UserAnalysis::GetDeltaR(float eta1, float eta2, float phi1, float phi2)
{ // Computes the DeltaR of two objects from their eta and phi values

 return sqrt( (eta1-eta2)*(eta1-eta2) 
            + DeltaPhi(phi1, phi2)*DeltaPhi(phi1, phi2) );

}


