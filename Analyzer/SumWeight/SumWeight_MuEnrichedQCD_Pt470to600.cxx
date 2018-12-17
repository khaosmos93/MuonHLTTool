#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt470to600()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt470to600/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt470to600";

  producer->Run();  
}

