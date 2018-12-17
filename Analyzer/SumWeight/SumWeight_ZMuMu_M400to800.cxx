#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M400to800()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M400to800_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M400to800";

  producer->Run();  
}

