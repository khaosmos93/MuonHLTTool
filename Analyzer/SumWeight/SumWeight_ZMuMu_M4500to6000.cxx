#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M4500to6000()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M4500to6000_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M4500to6000";

  producer->Run();  
}

