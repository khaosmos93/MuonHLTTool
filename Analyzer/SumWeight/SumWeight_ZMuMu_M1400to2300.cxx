#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M1400to2300()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_ZToMuMu_M1400to2300_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M1400to2300";

  producer->Run();  
}

