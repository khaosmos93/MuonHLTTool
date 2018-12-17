#include "MCRateTool.h"

void MCRateTool_ZMuMu_M3500to4500()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M3500to4500_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M3500to4500";
  producer->xSec_ = 4.135e-06;
  producer->sumWeight_ = 100000.0;

  producer->Run();  
}

