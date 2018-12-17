#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt20to30()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt20to30/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt20to30";
  producer->xSec_ = 3987854.9;
  producer->sumWeight_ = 25190348.0;

  producer->Run();  
}

