#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt170to300()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt170to300/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt170to300";
  producer->xSec_ = 8292.982;
  producer->sumWeight_ = 8279252.0;

  producer->Run();  
}

