#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt120to170()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt120to170/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt120to170";
  producer->xSec_ = 23773.61;
  producer->sumWeight_ = 8815947.0;

  producer->Run();  
}

