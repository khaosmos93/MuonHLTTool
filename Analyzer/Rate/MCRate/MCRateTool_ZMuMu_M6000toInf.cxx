#include "MCRateTool.h"

void MCRateTool_ZMuMu_M6000toInf()
{
  MCRateTool* producer = new MCRateTool();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M6000toInf_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M6000toInf";
  producer->xSec_ = 2.06e-08;
  producer->sumWeight_ = 98014.0;

  producer->Run();  
}

