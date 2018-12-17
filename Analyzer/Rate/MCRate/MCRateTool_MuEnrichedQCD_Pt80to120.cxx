#include "MCRateTool.h"

void MCRateTool_MuEnrichedQCD_Pt80to120()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt80to120/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt80to120";
  producer->xSec_ = 106889.4;
  producer->sumWeight_ = 13853173.0;

  producer->Run();  
}

