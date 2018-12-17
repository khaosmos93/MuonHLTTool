#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M800to1400()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M800to1400_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M800to1400";

  producer->Run();  
}

