#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M200to400()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M200to400_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M200to400";

  producer->Run();  
}

