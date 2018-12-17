#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M3500to4500()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M3500to4500_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M3500to4500";

  producer->Run();  
}

