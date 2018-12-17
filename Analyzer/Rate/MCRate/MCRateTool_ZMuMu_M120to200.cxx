#include "MCRateTool.h"

void MCRateTool_ZMuMu_M120to200()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M120to200_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M120to200";
  producer->xSec_ = 19.32;
  producer->sumWeight_ = 100000.0;

  producer->Run();  
}

