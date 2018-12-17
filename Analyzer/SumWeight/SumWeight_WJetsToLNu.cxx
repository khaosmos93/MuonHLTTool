#include "CalcSumWeight.h"

void SumWeight_WJetsToLNu()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_WJetsToLNu_Madgraph/*.root");
  
  producer->sampleType_ = "WJetsToLNu";

  producer->Run();  
}

