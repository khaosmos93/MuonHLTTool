#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M2300to3500()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M2300to3500_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M2300to3500";

  producer->Run();  
}

