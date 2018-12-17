#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt470to600()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt470to600/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt470to600";
  producer->xSec_ = 56.588336;
  producer->sumWeight_ = 14062334.0;

  producer->Run();  
}

