#include "MCRateTool.h"

void MCRateTool_ZMuMu_M400to800()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M400to800_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M400to800";
  producer->xSec_ = 0.241;
  producer->sumWeight_ = 98000.0;

  producer->Run();  
}

