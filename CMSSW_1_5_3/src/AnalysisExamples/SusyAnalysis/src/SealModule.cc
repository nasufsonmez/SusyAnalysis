#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/InputSourceMacros.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "AnalysisExamples/SusyAnalysis/interface/SusyAnalyzer.h"

DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE(SusyAnalyzer);
