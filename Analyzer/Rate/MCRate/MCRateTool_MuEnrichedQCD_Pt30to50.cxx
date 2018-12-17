#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt30to50()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt30to50/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt30to50";
  producer->xSec_ = 1705381.0;
  producer->sumWeight_ = 24455996.0;

  producer->Run();  
}

