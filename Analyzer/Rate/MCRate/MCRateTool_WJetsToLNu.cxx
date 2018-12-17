#include "MCRateTool.h"

void MCRateTool_WJetsToLNu()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_WJetsToLNu_Madgraph/*.root");
  
  producer->sampleType_ = "WJetsToLNu";
  producer->xSec_ = 61526.7;
  producer->sumWeight_ = 1053937.0;

  producer->Run();  
}

