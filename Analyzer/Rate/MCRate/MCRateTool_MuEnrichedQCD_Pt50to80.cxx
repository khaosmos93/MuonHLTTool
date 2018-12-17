#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt50to80()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt50to80/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt50to80";
  producer->xSec_ = 393820.0;
  producer->sumWeight_ = 17127235.0;

  producer->Run();  
}

