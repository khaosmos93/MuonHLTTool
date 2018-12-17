#include "MCRateTool.h"

void MCRateTool_ZMuMu_M50to120()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_ZToMuMu_M50to120_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M50to120";
  producer->xSec_ = 1975.0;
  producer->sumWeight_ = 100000.0;

  producer->Run();  
}

