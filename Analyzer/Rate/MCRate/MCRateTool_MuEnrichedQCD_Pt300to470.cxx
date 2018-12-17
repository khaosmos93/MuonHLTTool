#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt300to470()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt300to470/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt300to470";
  producer->xSec_ = 797.35269;
  producer->sumWeight_ = 19369441.0;

  producer->Run();  
}

