#include "MCRateTool.h"

void MCRateTool_ZMuMu_M1400to2300()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M1400to2300_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M1400to2300";
  producer->xSec_ = 0.00139;
  producer->sumWeight_ = 95000.0;

  producer->Run();  
}

