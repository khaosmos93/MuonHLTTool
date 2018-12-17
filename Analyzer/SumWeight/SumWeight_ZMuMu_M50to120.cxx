#include "CalcSumWeight.h"

void SumWeight_ZMuMu_M50to120()
{
  SumWeightProducer* producer = new SumWeightProducer();

  producer->AddNtuplePath("/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181101_RAWOnly_92X_ZToMuMu_M50to120_Powheg/*.root");
  
  producer->sampleType_ = "ZMuMu_M50to120";

  producer->Run();  
}

