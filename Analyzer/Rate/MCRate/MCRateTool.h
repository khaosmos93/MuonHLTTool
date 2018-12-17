#include <TString.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStopwatch.h>

#include <iostream>
#include <vector>

#include <Include/MuonHLTTool.h>

class HistContainer
{
public:
  Int_t nPath_;
  vector<TString> vec_pathName_;
  vector<TH1D*>   vec_hist_;

  HistContainer()
  {
    Init();
  }

  void Fill(MuonHLT::NtupleHandle *ntuple, Double_t weight)
  {
    for(const auto& myFiredTrigger: *ntuple->vec_myFiredTrigger )
    {
      TString tstr_myFiredTrigger = myFiredTrigger;
      // -- serach whether a path is fired
      for(Int_t i_path=0; i_path<nPath_; i_path++)
      {
        TString pathName = vec_pathName_[i_path];

        // -- if it is found: fill the hist
        if( tstr_myFiredTrigger.Contains(pathName+"_v") )
          vec_hist_[i_path]->Fill( 0.5, weight ); // -- fill 0 < x < 1 bin with weights: counts
      }
    }
  }

  void Write(TFile *f_output)
  {
    f_output->cd();
    for(const auto& hist : vec_hist_ )
      hist->Write();
  }

private:
  void Init()
  {
    nPath_ = 0;
    vec_pathName_.clear();
    vec_hist_.clear();

    Register( "HLT_IsoMu20" );
    Register( "HLT_IsoMu24" );
    Register( "HLT_IsoMu27" );
    Register( "HLT_IsoMu30" );
    Register( "HLT_Mu12" );
    Register( "HLT_Mu15" );
    Register( "HLT_Mu20" );
    Register( "HLT_Mu27" );
    Register( "HLT_Mu50" );
    Register( "HLT_Mu55" );
    Register( "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8" );

    nPath_ = (Int_t)vec_pathName_.size();
  }

  void Register(TString pathName)
  {
    TString histName = "h_"+pathName;
    TH1D* h_temp = new TH1D(histName, "", 1, 0, 1);
    h_temp->Sumw2();

    // -- always same order
    vec_pathName_.push_back( pathName );
    vec_hist_.push_back( h_temp );
  }
};

class MCRateTool
{
public:
  TString sampleType_;
  vector<TString> vec_ntuplePath_;
  Double_t xSec_;
  Double_t sumWeight_;

  Double_t instLumi_;

  MCRateTool()
  {
    Init();
  }

  void AddNtuplePath(TString ntuplePath)
  {
    vec_ntuplePath_.push_back( ntuplePath );
  }

  void Run()
  {
    if( !IsReady() ) return;

    StartTimer();

    printf("[MCRateTool::Run] Target inst. lumi for rate estimation: %.1e (pb-1 * s-1)\n", instLumi_);

    TChain *chain = new TChain("ntupler/ntuple");
    for(const auto& ntuplePath : vec_ntuplePath_ )
      chain->Add( ntuplePath );

    MuonHLT::NtupleHandle *ntuple = new MuonHLT::NtupleHandle(chain);
    // ntuple->TurnOnBranches_HLTMuon();

    HistContainer* histContainer = new HistContainer();

    Int_t nEvent = chain->GetEntries();
    for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
    {
      MuonHLT::loadBar(i_ev+1, nEvent, 100, 100);

      chain->GetEvent(i_ev);

      Double_t normFactor = (xSec_ * instLumi_) / sumWeight_;

      histContainer->Fill( ntuple, normFactor );
    }

    TFile *f_output = TFile::Open("ROOTFile_MCRateTool_"+sampleType_+".root", "RECREATE");
    histContainer->Write(f_output);
    f_output->Close();

    PrintRunTime();
  }

private:
  TStopwatch timer_;

  void Init()
  {
    sampleType_ = "";
    vec_ntuplePath_.clear();
    xSec_ = -999;
    sumWeight_ = -999;

    instLumi_ = 0.02; // -- pb-1 * s-1 = 2.0e34 cm-2*s-1
  }

  Bool_t IsReady()
  {
    Bool_t isReady = kTRUE;
    if( sampleType_ == "" )
    {
      cout << "sampleType is not set" << endl;
      isReady = kFALSE;

    }
    if( vec_ntuplePath_.size() == 0 )
    {
      cout << "No ntuples are provided" << endl;
      isReady = kFALSE;
    }

    if( xSec_ == -999 )
    {
      cout << "Cross section is not set" << endl;
      isReady = kFALSE;
    }

    if( sumWeight_ == -999 )
    {
      cout << "sum(weight) is not set" << endl;
      isReady = kFALSE;
    }

    return isReady;
  }

  void StartTimer()
  {
    timer_.Start();
  }

  void PrintRunTime()
  {
    Double_t cpuTime = timer_.CpuTime();
    Double_t realTime = timer_.RealTime();

    cout << "************************************************" << endl;
    cout << "Total real time: " << realTime << " (seconds)" << endl;
    cout << "Total CPU time:  " << cpuTime << " (seconds)" << endl;
    cout << "  CPU time / real time = " << cpuTime / realTime << endl;
    cout << "************************************************" << endl;
  }
};

void Test()
{
  MCRateTool* mcRateTool = new MCRateTool();

  TString ntuplePath = "/Users/KyeongPil_Lee/ServiceWorks/ExampleROOTFile/MuonHLTNtuple_ZMuMu_M50to120.root";
  mcRateTool->AddNtuplePath(ntuplePath);

  mcRateTool->sampleType_ = "ZMuMu_M50to120";
  mcRateTool->xSec_ = 2000.0;
  mcRateTool->sumWeight_ = 6000.0;
  mcRateTool->Run();
}