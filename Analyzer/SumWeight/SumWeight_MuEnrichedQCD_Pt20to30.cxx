#include "CalcSumWeight.h"

void SumWeight_MuEnrichedQCD_Pt20to30()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181121_RAWOnly_92X_MuEnrichedQCD_Pt20to30/*.root");
  
  producer->sampleType_ = "MuEnrichedQCD_Pt20to30";

  producer->Run();  
}

