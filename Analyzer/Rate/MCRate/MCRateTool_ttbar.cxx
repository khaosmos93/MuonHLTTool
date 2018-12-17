#include "MCRateTool.h"

void MCRateTool_ttbar()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_TT_Powheg/*.root");
  
  producer->sampleType_ = "ttbar";
  producer->xSec_ = 831.76;
  producer->sumWeight_ = 9945480.0;

  producer->Run();  
}

