#include "MCRateTool.h"

void MCRateTool_ZMuMu_M800to1400()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M800to1400_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M800to1400";
  producer->xSec_ = 0.01678;
  producer->sumWeight_ = 11938.0;

  producer->Run();  
}

