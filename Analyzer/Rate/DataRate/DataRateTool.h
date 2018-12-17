#include <TString.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TStopwatch.h>

#include <iostream>
#include <vector>

#include <Include/MuonHLTTool.h>

#define nMaxLumiBlock 5000
#define LumiBlockTime 23.31

class LumiRateTool
{
public:
  Int_t lumiBlockNum_;

  Int_t nFiredEvent_; // -- pure # events
  Double_t nFiredEventScaled_; // -- scaled to the target lumi.

  Double_t rate_;
  Double_t rateScaled_;

  LumiRateTool(Int_t lumiBlockNum)
  {
    Init();

    lumiBlockNum_ = lumiBlockNum;
  }

  void Fill( Double_t lumiScale )
  {
    nFiredEvent_ += 1;
    nFiredEventScaled_ += lumiScale;
  }

  void CalcRate()
  {
    rate_       = nFiredEvent_       / LumiBlockTime;
    rateScaled_ = nFiredEventScaled_ / LumiBlockTime;
  }

private:
  void Init()
  {
    lumiBlockNum_ = -999;
    nFiredEvent_       = 0;
    nFiredEventScaled_ = 0;
    rate_       = -999;
    rateScaled_ = -999;
  }

};

class RunRateTool
{
public:
  Int_t runNum_;
  TString pathName_;

  vector<LumiRateTool> vec_lumiRateTool_;

  RunRateTool(Int_t runNum, TString pathName)
  {
    Init();

    runNum_   = runNum;
    pathName_ = pathName;
  }

  void Fill( Int_t LBNum, Double_t lumiScale )
  {
    vec_lumiRateTool_[LBNum-1].Fill( lumiScale );
  }

  void CalcRate()
  {
    for(auto& lumiRateTool : vec_lumiRateTool_ )
      lumiRateTool.CalcRate();
  }

private:
  void Init()
  {
    vec_lumiRateTool_.clear();

    for(Int_t i=0; i<nMaxLumiBlock; i++)
    {
      Int_t i_LBNum = i+1; // -- lumi block number: starting from 1, not 0
      LumiRateTool tool(i_LBNum);
      vec_lumiRateTool_.push_back( tool );
    }
  }

};

class HistContainer
{
public:
  Int_t runNum_;
  Double_t targetLumi_;

  Int_t nPath_;
  vector<TString>     vec_pathName_;
  vector<RunRateTool> vec_runRateTool_;
  vector<TH1D*>       vec_hist_rate_;
  vector<TH1D*>       vec_hist_rate_vs_LB_;
  vector<TH1D*>       vec_hist_rateScaled_;
  vector<TH1D*>       vec_hist_rateScaled_vs_LB_;

  HistContainer(Int_t runNum, Double_t targetLumi)
  {
    runNum_ = runNum;
    targetLumi_ = targetLumi;

    Init();
  }

  void Fill(MuonHLT::NtupleHandle *ntuple)
  {
    for(const auto& myFiredTrigger: *ntuple->vec_myFiredTrigger )
    {
      TString tstr_myFiredTrigger = myFiredTrigger;
      // -- serach whether a path is fired
      for(Int_t i_path=0; i_path<nPath_; i_path++)
      {
        TString pathName = vec_pathName_[i_path];

        // -- if it is found: fill the RunRateTool
        if( tstr_myFiredTrigger.Contains(pathName+"_v") )
        {
          Double_t lumiScale = -999;

          Double_t instLumi = ntuple->instLumi;
          if( instLumi == 0 )
            lumiScale = 0;
          else
            lumiScale = targetLumi_ / instLumi; // -- linear extrapolation

          vec_runRateTool_[i_path].Fill( ntuple->lumiBlockNum, lumiScale );
        }
      }
    }
  }

  void FillHist()
  {
    for(Int_t i_path=0; i_path<nPath_; i_path++)
    {
      vec_runRateTool_[i_path].CalcRate();

      Int_t nEffLB = 0; // -- LB with # fired event != 0
      Double_t rateSum = 0;
      Double_t rateScaledSum = 0;

      // -- iteration over all lumi block
      for(Int_t i=0; i<nMaxLumiBlock; i++)
      {
        Int_t i_LBNumBin = i+1;

        LumiRateTool lumiRateTool = vec_runRateTool_[i_path].vec_lumiRateTool_[i];

        Double_t rate       = lumiRateTool.rate_;
        Double_t rateScaled = lumiRateTool.rateScaled_;

        vec_hist_rate_vs_LB_[i_path]->SetBinContent( i_LBNumBin, rate );
        vec_hist_rateScaled_vs_LB_[i_path]->SetBinContent( i_LBNumBin, rateScaled );

        vec_hist_rate_vs_LB_[i_path]->SetBinError( i_LBNumBin, 0 );
        vec_hist_rateScaled_vs_LB_[i_path]->SetBinError( i_LBNumBin, 0 );

        if( lumiRateTool.nFiredEvent_ > 0 )
        {
          nEffLB += 1;
          rateSum       += rate;
          rateScaledSum += rateScaled;
        }
      }

      Double_t totalRate       = rateSum / nEffLB;
      Double_t totalRateScaled = rateScaledSum / nEffLB;

      vec_hist_rate_[i_path]->SetBinContent(1, totalRate);
      vec_hist_rateScaled_[i_path]->SetBinContent(1, totalRateScaled);

      vec_hist_rate_[i_path]->SetBinError(1, 0);
      vec_hist_rateScaled_[i_path]->SetBinError(1, 0);
    }
  }

  void Write(TFile *f_output)
  {
    f_output->cd();
    for(Int_t i_path=0; i_path<nPath_; i_path++)
    {
      vec_hist_rate_[i_path]->Write();
      vec_hist_rate_vs_LB_[i_path]->Write();
      vec_hist_rateScaled_[i_path]->Write();
      vec_hist_rateScaled_vs_LB_[i_path]->Write();
    }
  }

private:
  void Init()
  {
    nPath_ = 0;
    vec_pathName_.clear();
    vec_hist_rate_.clear();
    vec_hist_rate_vs_LB_.clear();
    vec_hist_rateScaled_.clear();
    vec_hist_rateScaled_vs_LB_.clear();

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
    RunRateTool tool(runNum_, pathName);

    TH1D* h_rate       = new TH1D(histName         , "", 1, 0, 1);
    TH1D* h_rate_vs_LB = new TH1D(histName+"_vs_LB", "", nMaxLumiBlock, 1, nMaxLumiBlock+1);

    TH1D* h_rateScaled       = new TH1D(histName+"_scaled",       "", 1, 0, 1);
    TH1D* h_rateScaled_vs_LB = new TH1D(histName+"_scaled_vs_LB", "", nMaxLumiBlock, 1, nMaxLumiBlock+1);


    // -- always same order
    vec_pathName_.push_back( pathName );
    vec_runRateTool_.push_back( tool );
    vec_hist_rate_.push_back( h_rate );
    vec_hist_rate_vs_LB_.push_back( h_rate_vs_LB );
    vec_hist_rateScaled_.push_back( h_rateScaled );
    vec_hist_rateScaled_vs_LB_.push_back( h_rateScaled_vs_LB );
  }

};



class DataRateTool
{
public:
  TString sampleType_;
  Int_t runNum_;
  Double_t targetLumi_;
  vector<TString> vec_ntuplePath_;

  DataRateTool()
  {
    Init();
  }

  void AddNtuplePath(TString ntuplePath)
  {
    vec_ntuplePath_.push_back( ntuplePath );
  }

  void Run()
  {
    StartTimer();

    printf("[DataRateTool::Run] Target inst. lumi for rate estimation: %lf (* 10^{30} cm-2 * s-1)\n", targetLumi_);

    TChain *chain = new TChain("ntupler/ntuple");
    for(const auto& ntuplePath : vec_ntuplePath_ )
      chain->Add( ntuplePath );

    MuonHLT::NtupleHandle *ntuple = new MuonHLT::NtupleHandle(chain);
    // ntuple->TurnOnBranches_HLTMuon();

    HistContainer* histContainer = new HistContainer(runNum_, targetLumi_);

    Int_t nEvent = chain->GetEntries();
    for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
    {
      MuonHLT::loadBar(i_ev+1, nEvent, 100, 100);

      chain->GetEvent(i_ev);
      histContainer->Fill( ntuple );
    }

    histContainer->FillHist();

    TFile *f_output = TFile::Open("ROOTFile_DataRateTool_"+sampleType_+".root", "RECREATE");
    histContainer->Write(f_output);
    f_output->Close();

    PrintRunTime();
  }

private:
  TStopwatch timer_;

  void Init()
  {
    sampleType_ = "";
    targetLumi_ = 20000.0; // -- 2.0e34
    vec_ntuplePath_.clear();
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
  DataRateTool* producer = new DataRateTool();

  TString ntuplePath = "/Users/KyeongPil_Lee/ServiceWorks/ExampleROOTFile/MuonHLTNtuple_SingleMuon_Run2018D_Run325170.root";
  producer->AddNtuplePath(ntuplePath);

  producer->sampleType_ = "SingleMuon_Run325170";
  producer->runNum_ = 325170;

  producer->Run();
}