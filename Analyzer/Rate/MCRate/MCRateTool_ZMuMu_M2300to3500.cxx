#include "MCRateTool.h"

void MCRateTool_ZMuMu_M2300to3500()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M2300to3500_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M2300to3500";
  producer->xSec_ = 8.948e-05;
  producer->sumWeight_ = 100000.0;

  producer->Run();  
}

