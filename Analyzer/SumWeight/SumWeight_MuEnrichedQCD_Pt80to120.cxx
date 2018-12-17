#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt80to120()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_MuEnrichedQCD_Pt80to120/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt80to120";

  producer->Run();  
}

