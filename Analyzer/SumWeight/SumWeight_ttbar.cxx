#include "CalcSumWeight.h"

void SumWeight_ttbar()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_TT_Powheg/*.root");
  
  producer->sampleType_ = "ttbar";

  producer->Run();  
}

