#include "MCRateTool.h"

void MCRateTool_ZMuMu_M200to400()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M200to400_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M200to400";
  producer->xSec_ = 2.731;
  producer->sumWeight_ = 100000.0;

  producer->Run();  
}

