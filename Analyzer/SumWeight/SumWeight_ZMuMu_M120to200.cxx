#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M120to200()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M120to200_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M120to200";

  producer->Run();  
}

