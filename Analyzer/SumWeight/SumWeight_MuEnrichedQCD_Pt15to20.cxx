#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt15to20()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt15to20/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt15to20";

  producer->Run();  
}

