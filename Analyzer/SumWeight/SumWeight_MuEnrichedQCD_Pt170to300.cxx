#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt170to300()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt170to300/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt170to300";

  producer->Run();  
}

