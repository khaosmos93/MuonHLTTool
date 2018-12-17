#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M6000toInf()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M6000toInf_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M6000toInf";

  producer->Run();  
}

