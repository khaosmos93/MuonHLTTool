#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt30to50()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt30to50/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt30to50";

  producer->Run();  
}

