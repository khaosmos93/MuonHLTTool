#include "DataRateTool.h"

void DataRateTool_SingleMuon_Run325170()
{
  DataRateTool* producer = new DataRateTool();

  TString ntuplePath = "/scratch/kplee/MuonHLTNtuple/crab_MuonHLTNtuple_v20181214_RAWOnly_v2_SingleMuon_Run2018D_Run325170/*.root";
  producer->AddNtuplePath(ntuplePath);

  producer->sampleType_ = "SingleMuon_Run325170";
  producer->runNum_ = 325170;

  producer->Run();
}