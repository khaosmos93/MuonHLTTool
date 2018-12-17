#include "MCRateTool.h"

void MCRateTool_ZMuMu_M4500to6000()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M4500to6000_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M4500to6000";
  producer->xSec_ = 4.56e-07;
  producer->sumWeight_ = 100000.0;

  producer->Run();  
}

