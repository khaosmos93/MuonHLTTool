#include <Include/MuonHLTTool.h>
#include <TString.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStopwatch.h>
#include <iostream>

class SumWeightProducer
{
public:
  TString sampleType_;
  vector<TString> vec_ntuplePath_;

  SumWeightProducer()
  {
    sampleType_ = "undefined";
  }

  void AddNtuplePath(TString ntuplePath)
  {
    vec_ntuplePath_.push_back( ntuplePath );
  }

  void Run()
  {
    StartTimer();

    TChain *chain = new TChain("ntupler/ntuple");
    for(const auto& ntuplePath : vec_ntuplePath_ )
      chain->Add( ntuplePath );

    MuonHLT::NtupleHandle *ntuple = new MuonHLT::NtupleHandle(chain);

    // -- histogram initialization
    TH1D* h_sumWeight = new TH1D("h_sumWeight", "", 1, 0, 1);
    Double_t sumWeight = 0;

    Int_t nEvent = chain->GetEntries();
    for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
    {
      MuonHLT::loadBar(i_ev+1, nEvent, 100, 100);

      ntuple->GetEvent(i_ev);

      Double_t genWeight;
      ntuple->genEventWeight < 0 ? genWeight = -1 : genWeight = 1;
      sumWeight = sumWeight + genWeight;
    }

    h_sumWeight->SetBinContent(1, sumWeight);
    h_sumWeight->SetBinError(1, 0);

    TString outputName = TString::Format("ROOTFile_SumWeight_%s.root", sampleType_.Data());
    TFile *f_output = TFile::Open(outputName, "RECREATE");
    h_sumWeight->Write();
    f_output->Close();

    PrintRunTime();
  }

private:
  TStopwatch timer_;

  void StartTimer()
  {
    timer_.Start();
  }

  void PrintRunTime()
  {
    Double_t cpuTime = timer_.CpuTime();
    Double_t realTime = timer_.RealTime();

    std::cout << "************************************************" << std::endl;
    std::cout << "Total real time: " << realTime << " (seconds)" << std::endl;
    std::cout << "Total CPU time:  " << cpuTime << " (seconds)" << std::endl;
    std::cout << "  CPU time / real time = " << cpuTime / realTime << std::endl;
    std::cout << "************************************************" << std::endl;
  }
};

void Test()
{
  SumWeightProducer* producer = new SumWeightProducer();

  TString ntuplePath = "/Users/KyeongPil_Lee/ServiceWorks/ExampleROOTFile/MuonHLTNtuple_ZMuMu_M50to120.root";
  producer->AddNtuplePath(ntuplePath);
  producer->sampleType_ = "ZMuMu_M50to120";

  producer->Run();  
}