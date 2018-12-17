#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt50to80()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt50to80/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt50to80";

  producer->Run();  
}

