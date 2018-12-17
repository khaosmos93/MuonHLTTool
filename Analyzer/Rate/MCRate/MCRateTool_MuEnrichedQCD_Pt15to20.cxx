#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt15to20()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt15to20/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt15to20";
  producer->xSec_ = 3336011.0;
  producer->sumWeight_ = 5101373.0;

  producer->Run();  
}

