#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TLorentzVector.h>
#include <TStopwatch.h>
#include <TTimeStamp.h>
#include <TString.h>
#include <TLegend.h>
#include <THStack.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TAttMarker.h>
#include <TF1.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TApplication.h>
#include <vector>
#include <TMath.h>
#include <TSystem.h>

#include <Include/NtupleHandle.h>
#include <Include/Object.h>

using namespace MuonHLT;

#define nMaxLumiBlock (5000)
#define LumiBlockTime (23.31)

vector<Int_t> vec_Prescale_Run283884 = { (4*107) };  // HLT_L1FatEvents_partX * 107
vector<Double_t> vec_LS_Run283884 =    { 1, 99999};

vector<Int_t> vec_Prescale_Run325057 = { 0, 1100, 0 };
vector<Double_t> vec_LS_Run325057 =    { 1, 22, 181, 99999};

Int_t Find_PrescaleValue( Int_t RunNum, Int_t LumiBlockNum )
{
  vector<Int_t> vec_Prescale;
  vector<Double_t> vec_LS;
  if( RunNum == 283884 )
  {
    vec_Prescale = vec_Prescale_Run283884;
    vec_LS = vec_LS_Run283884;
  }
  else if( RunNum == 325057 )
  {
    vec_Prescale = vec_Prescale_Run325057;
    vec_LS = vec_LS_Run325057;
  }

  // -- find pre-scale value -- //
  Double_t Prescale = 0;

  Int_t nBin = (Int_t)vec_Prescale.size();
  for(Int_t i=0; i<nBin; i++)
  {
    Double_t LowerEdge = vec_LS[i];
    Double_t UpperEdge = vec_LS[i+1];

    if( LumiBlockNum >= LowerEdge && LumiBlockNum < UpperEdge )
    {
      Prescale = vec_Prescale[i];
      break;
    }
  }

  // printf("[Run = %d, LS = %d] -> Prescale = %.0lf\n", RunNum, LumiBlockNum, Prescale);

  return Prescale;
}



class LumiBlockInfo
{
public:
  Int_t LumiBlockNum;

  Double_t nEvent;
  Double_t nEvent_UnPS;

  Double_t Sum_InstLumi;
  Double_t Mean_InstLumi;
  Double_t Sum_nVertices;
  Double_t Mean_nVertices;

  Double_t nFiredEvent;
  Double_t nFiredEvent_UnPS;
  Double_t nFiredEvent_UnPS_Scaled2e34;

  Double_t Rate;
  Double_t Rate_UnPS;
  Double_t Rate_UnPS_Scaled2e34;

  ///
  Double_t nMyFiredEvent;
  Double_t nMyFiredEvent_UnPS;
  Double_t nMyFiredEvent_UnPS_Scaled2e34;

  Double_t MyRate;
  Double_t MyRate_UnPS;
  Double_t MyRate_UnPS_Scaled2e34;

  LumiBlockInfo( Int_t _Num )
  {
    this->LumiBlockNum = _Num;
    this->Init();
  }

  void Fill( NtupleHandle *ntuple, vector<TString> TriggerTag )
  {
    Double_t Prescale = Find_PrescaleValue( ntuple->runNum, ntuple->lumiBlockNum );

    this->nEvent += 1;
    this->nEvent_UnPS += Prescale;

    this->Sum_InstLumi = Sum_InstLumi + ntuple->instLumi;
    this->Sum_nVertices = Sum_nVertices + ntuple->nVertex;

    Bool_t isFiredTrigger = kFALSE;
    if(TriggerTag[0].Contains("_")) {
      for(Int_t i=0; i<ntuple->vec_firedTrigger->size(); ++i) {
        std::string FiredPath = ntuple->vec_firedTrigger->at(i);
        for(Int_t j=0; j<TriggerTag.size(); ++j) {
          if( FiredPath.find(TriggerTag[j].Data()) != std::string::npos ) {
            isFiredTrigger = kTRUE;
            break;
          }
        }
        if(isFiredTrigger)  break;
      }
    }
    else {
      for(Int_t i=0; i<ntuple->vec_filterName->size(); ++i) {
        std::string FiredPath = ntuple->vec_filterName->at(i);
        for(Int_t j=0; j<TriggerTag.size(); ++j) {
          if( FiredPath.find(TriggerTag[j].Data()) != std::string::npos ) {
            isFiredTrigger = kTRUE;
            break;
          }
        }
        if(isFiredTrigger)  break;
      }
    }

    if( isFiredTrigger )
    {
      this->nFiredEvent += 1;
      this->nFiredEvent_UnPS += Prescale;
    }

    ///
    Bool_t isMyFiredTrigger = kFALSE;
    if(TriggerTag[0].Contains("_")) {
      for(Int_t i=0; i<ntuple->vec_myFiredTrigger->size(); ++i) {
        std::string MyFiredPath = ntuple->vec_myFiredTrigger->at(i);
        for(Int_t j=0; j<TriggerTag.size(); ++j) {
          if( MyFiredPath.find(TriggerTag[j].Data()) != std::string::npos ) {
            isMyFiredTrigger = kTRUE;
            break;
          }
        }
        if(isMyFiredTrigger)  break;
      }
    }
    else {
      for(Int_t i=0; i<ntuple->vec_myFilterName->size(); ++i) {
        std::string MyFiredPath = ntuple->vec_myFilterName->at(i);
        for(Int_t j=0; j<TriggerTag.size(); ++j) {
          if( MyFiredPath.find(TriggerTag[j].Data()) != std::string::npos ) {
            isMyFiredTrigger = kTRUE;
            break;
          }
        }
        if(isMyFiredTrigger)  break;
      }
    }

    if( isMyFiredTrigger )
    {
      this->nMyFiredEvent += 1;
      this->nMyFiredEvent_UnPS += Prescale;
    }
  }

  void Calc_Rate()
  {
    if( this->nEvent == 0 )
    {
      this->Mean_InstLumi = 0;
      this->Mean_nVertices = 0;

      this->Rate = 0;
      this->Rate_UnPS = 0;
      this->Rate_UnPS_Scaled2e34 = 0;

      ///
      this->MyRate = 0;
      this->MyRate_UnPS = 0;
      this->MyRate_UnPS_Scaled2e34 = 0;
    }
    else
    {
      // -- divided by total # events, not only # fired events! -- //
      this->Mean_InstLumi = this->Sum_InstLumi / this->nEvent;
      this->Mean_nVertices = this->Sum_nVertices / this->nEvent;

      // -- normalized to the # datasets included: HLTPhysicsN datasets -- //
      this->nEvent = this->nEvent / (Double_t)nDataset;
      this->nEvent_UnPS = this->nEvent_UnPS / (Double_t)nDataset;


      Double_t SF_Lumi = 20000.0 / this->Mean_InstLumi;

      this->nFiredEvent = this->nFiredEvent / (Double_t)nDataset;
      this->nFiredEvent_UnPS = this->nFiredEvent_UnPS / (Double_t)nDataset;
      this->nFiredEvent_UnPS_Scaled2e34 = this->nFiredEvent_UnPS_Scaled2e34 / (Double_t)nDataset;

      this->Rate = this->nFiredEvent / LumiBlockTime; // -- unit: Hz -- //
      this->Rate_UnPS = this->nFiredEvent_UnPS / LumiBlockTime;

      this->nFiredEvent_UnPS_Scaled2e34 = this->nFiredEvent_UnPS * SF_Lumi;
      this->Rate_UnPS_Scaled2e34 = this->nFiredEvent_UnPS_Scaled2e34 / LumiBlockTime;

      ///
      this->nMyFiredEvent = this->nMyFiredEvent / (Double_t)nDataset;
      this->nMyFiredEvent_UnPS = this->nMyFiredEvent_UnPS / (Double_t)nDataset;
      this->nMyFiredEvent_UnPS_Scaled2e34 = this->nMyFiredEvent_UnPS_Scaled2e34 / (Double_t)nDataset;

      this->MyRate = this->nMyFiredEvent / LumiBlockTime; // -- unit: Hz -- //
      this->MyRate_UnPS = this->nMyFiredEvent_UnPS / LumiBlockTime;

      this->nMyFiredEvent_UnPS_Scaled2e34 = this->nMyFiredEvent_UnPS * SF_Lumi;
      this->MyRate_UnPS_Scaled2e34 = this->nMyFiredEvent_UnPS_Scaled2e34 / LumiBlockTime;
    }

  }

private:

  void Init()
  {
    this->nEvent = 0;
    this->nEvent_UnPS = 0;

    this->Sum_InstLumi = 0;
    this->Mean_InstLumi = 0;
    this->Sum_nVertices = 0;
    this->Mean_nVertices = 0;


    this->nFiredEvent = 0;
    this->nFiredEvent_UnPS = 0;
    this->nFiredEvent_UnPS_Scaled2e34 = 0;

    this->Rate = 0;
    this->Rate_UnPS = 0;
    this->Rate_UnPS_Scaled2e34 = 0;

    ///
    this->nMyFiredEvent = 0;
    this->nMyFiredEvent_UnPS = 0;
    this->nMyFiredEvent_UnPS_Scaled2e34 = 0;

    this->MyRate = 0;
    this->MyRate_UnPS = 0;
    this->MyRate_UnPS_Scaled2e34 = 0;
  }
};

class RunInfos
{
public:
  Int_t RunNum;
  vector< LumiBlockInfo* > vec_LumiBlockInfo;

  RunInfos( Int_t _RunNum )
  {
    this->Init();
    this->RunNum = _RunNum;
  }

  void Fill( NtupleHandle *ntuple, vector<TString> TriggerTag )
  {
    Int_t LumiBlockNum = ntuple->lumiBlockNum;
    vec_LumiBlockInfo[LumiBlockNum]->Fill( ntuple, TriggerTag );
  }

  void CalcRate_EachLumiBlock()
  {
    for( auto& Info : this->vec_LumiBlockInfo )
      Info->Calc_Rate();
  }

private:

  void Init()
  {
    this->RunNum = 0;
    // -- 0-th content: dummy (to have consistent between vector index and exact lumi-block number) -- //
    for(Int_t i=0; i<nMaxLumiBlock+1; i++)
    {
      LumiBlockInfo* Info = new LumiBlockInfo( i );
      vec_LumiBlockInfo.push_back( Info );
    }
  }
};

class RunHistContainer
{
public:
  TString Tag;  // Run number Tag

  Int_t nLumiBlock;

  Double_t nFiredEvent;
  Double_t nFiredEvent_UnPS;
  Double_t nFiredEvent_UnPS_Scaled2e34;

  Double_t TotalRate;
  Double_t TotalRate_UnPS;
  Double_t TotalRate_UnPS_Scaled2e34;

  ///
  Double_t nMyFiredEvent;
  Double_t nMyFiredEvent_UnPS;
  Double_t nMyFiredEvent_UnPS_Scaled2e34;

  Double_t MyTotalRate;
  Double_t MyTotalRate_UnPS;
  Double_t MyTotalRate_UnPS_Scaled2e34;


  vector<TH1D*> vec_Hist;

  TH1D* h_LumiBlock_vs_nEvent;
  TH1D* h_LumiBlock_vs_nEvent_UnPS;

  TH1D* h_LumiBlock_vs_InstLumiMean;
  TH1D* h_LumiBlock_vs_nVerticesMean;


  TH1D* h_LumiBlock_vs_nFiredEvent;
  TH1D* h_LumiBlock_vs_nFiredEvent_UnPS;
  TH1D* h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34;

  TH1D* h_LumiBlock_vs_Rate;
  TH1D* h_LumiBlock_vs_Rate_UnPS;
  TH1D* h_LumiBlock_vs_Rate_UnPS_Scaled2e34;

  ///
  TH1D* h_LumiBlock_vs_nMyFiredEvent;
  TH1D* h_LumiBlock_vs_nMyFiredEvent_UnPS;
  TH1D* h_LumiBlock_vs_nMyFiredEvent_UnPS_Scaled2e34;

  TH1D* h_LumiBlock_vs_MyRate;
  TH1D* h_LumiBlock_vs_MyRate_UnPS;
  TH1D* h_LumiBlock_vs_MyRate_UnPS_Scaled2e34;


  // -- just 1 bin -- //
  TH1D* h_TotalRate;
  TH1D* h_TotalRate_UnPS;
  TH1D* h_TotalRate_UnPS_Scaled2e34;

  ///
  TH1D* h_MyTotalRate;
  TH1D* h_MyTotalRate_UnPS;
  TH1D* h_MyTotalRate_UnPS_Scaled2e34;


  vector<TGraph*> vec_Graph;

  TGraph* G_Lumi_Rate;
  TGraph* G_Lumi_Rate_UnPS;
  TGraph* G_Lumi_Rate_UnPS_Scaled2e34;

  TGraph* G_nVertices_Rate;
  TGraph* G_nVertices_Rate_UnPS;
  TGraph* G_nVertices_Rate_UnPS_Scaled2e34;

  ///
  TGraph* G_Lumi_MyRate;
  TGraph* G_Lumi_MyRate_UnPS;
  TGraph* G_Lumi_MyRate_UnPS_Scaled2e34;

  TGraph* G_nVertices_MyRate;
  TGraph* G_nVertices_MyRate_UnPS;
  TGraph* G_nVertices_MyRate_UnPS_Scaled2e34;


  RunHistContainer( TString _Tag )
  {
    this->Tag = _Tag;
    this->Init();
  }

  void Fill( LumiBlockInfo* Info )
  {
    Int_t LumiBlockNum = Info->LumiBlockNum; // -- same with bin number -- //

    this->h_LumiBlock_vs_nEvent->SetBinContent(LumiBlockNum, Info->nEvent );
    this->h_LumiBlock_vs_nEvent->SetBinError(LumiBlockNum, 0);  //sqrt(Info->nEvent) );

    this->h_LumiBlock_vs_nEvent_UnPS->SetBinContent(LumiBlockNum, Info->nEvent_UnPS );
    this->h_LumiBlock_vs_nEvent_UnPS->SetBinError(LumiBlockNum, 0);  //sqrt(Info->nEvent_UnPS) );

    this->h_LumiBlock_vs_InstLumiMean->SetBinContent(LumiBlockNum, Info->Mean_InstLumi );
    this->h_LumiBlock_vs_InstLumiMean->SetBinError(LumiBlockNum, 0 );

    this->h_LumiBlock_vs_nVerticesMean->SetBinContent(LumiBlockNum, Info->Mean_nVertices );
    this->h_LumiBlock_vs_nVerticesMean->SetBinError(LumiBlockNum, 0 );


    this->h_LumiBlock_vs_nFiredEvent->SetBinContent(LumiBlockNum, Info->nFiredEvent );
    this->h_LumiBlock_vs_nFiredEvent->SetBinError(LumiBlockNum, 0);  //sqrt(Info->nFiredEvent) );

    this->h_LumiBlock_vs_nFiredEvent_UnPS->SetBinContent(LumiBlockNum, Info->nFiredEvent_UnPS );
    this->h_LumiBlock_vs_nFiredEvent_UnPS->SetBinError(LumiBlockNum, 0);

    this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34->SetBinContent(LumiBlockNum, Info->nFiredEvent_UnPS_Scaled2e34 );
    this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34->SetBinError(LumiBlockNum, 0);

    this->h_LumiBlock_vs_Rate->SetBinContent(LumiBlockNum, Info->Rate );
    this->h_LumiBlock_vs_Rate->SetBinError(LumiBlockNum, 0);  //Info->Rate * (1.0 / sqrt(Info->nFiredEvent)) );

    this->h_LumiBlock_vs_Rate_UnPS->SetBinContent(LumiBlockNum, Info->Rate_UnPS );
    this->h_LumiBlock_vs_Rate_UnPS->SetBinError(LumiBlockNum, 0);

    this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34->SetBinContent(LumiBlockNum, Info->Rate_UnPS_Scaled2e34 );
    this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34->SetBinError(LumiBlockNum, 0);

    ///
    this->h_LumiBlock_vs_nMyFiredEvent->SetBinContent(LumiBlockNum, Info->nMyFiredEvent );
    this->h_LumiBlock_vs_nMyFiredEvent->SetBinError(LumiBlockNum, 0);  //sqrt(Info->nMyFiredEvent) );

    this->h_LumiBlock_vs_nMyFiredEvent_UnPS->SetBinContent(LumiBlockNum, Info->nMyFiredEvent_UnPS );
    this->h_LumiBlock_vs_nMyFiredEvent_UnPS->SetBinError(LumiBlockNum, 0);

    this->h_LumiBlock_vs_nMyFiredEvent_UnPS_Scaled2e34->SetBinContent(LumiBlockNum, Info->nMyFiredEvent_UnPS_Scaled2e34 );
    this->h_LumiBlock_vs_nMyFiredEvent_UnPS_Scaled2e34->SetBinError(LumiBlockNum, 0);

    this->h_LumiBlock_vs_MyRate->SetBinContent(LumiBlockNum, Info->MyRate );
    this->h_LumiBlock_vs_MyRate->SetBinError(LumiBlockNum, 0);  //Info->MyRate * (1.0 / sqrt(Info->nMyFiredEvent)) );

    this->h_LumiBlock_vs_MyRate_UnPS->SetBinContent(LumiBlockNum, Info->MyRate_UnPS );
    this->h_LumiBlock_vs_MyRate_UnPS->SetBinError(LumiBlockNum, 0);

    this->h_LumiBlock_vs_MyRate_UnPS_Scaled2e34->SetBinContent(LumiBlockNum, Info->MyRate_UnPS_Scaled2e34 );
    this->h_LumiBlock_vs_MyRate_UnPS_Scaled2e34->SetBinError(LumiBlockNum, 0);

    // -- SetPoint for graphs -- //
    this->G_Lumi_Rate->SetPoint( nLumiBlock, Info->Mean_InstLumi, Info->Rate );
    this->G_Lumi_Rate_UnPS->SetPoint( nLumiBlock, Info->Mean_InstLumi, Info->Rate_UnPS );
    this->G_Lumi_Rate_UnPS_Scaled2e34->SetPoint( nLumiBlock, Info->Mean_InstLumi, Info->Rate_UnPS_Scaled2e34 );

    this->G_nVertices_Rate->SetPoint( nLumiBlock, Info->Mean_nVertices, Info->Rate );
    this->G_nVertices_Rate_UnPS->SetPoint( nLumiBlock, Info->Mean_nVertices, Info->Rate_UnPS );
    this->G_nVertices_Rate_UnPS_Scaled2e34->SetPoint( nLumiBlock, Info->Mean_nVertices, Info->Rate_UnPS_Scaled2e34 );

    ///
    this->G_Lumi_MyRate->SetPoint( nLumiBlock, Info->Mean_InstLumi, Info->MyRate );
    this->G_Lumi_MyRate_UnPS->SetPoint( nLumiBlock, Info->Mean_InstLumi, Info->MyRate_UnPS );
    this->G_Lumi_MyRate_UnPS_Scaled2e34->SetPoint( nLumiBlock, Info->Mean_InstLumi, Info->MyRate_UnPS_Scaled2e34 );

    this->G_nVertices_MyRate->SetPoint( nLumiBlock, Info->Mean_nVertices, Info->MyRate );
    this->G_nVertices_MyRate_UnPS->SetPoint( nLumiBlock, Info->Mean_nVertices, Info->MyRate_UnPS );
    this->G_nVertices_MyRate_UnPS_Scaled2e34->SetPoint( nLumiBlock, Info->Mean_nVertices, Info->MyRate_UnPS_Scaled2e34 );


    this->nFiredEvent += Info->nFiredEvent;
    this->nFiredEvent_UnPS += Info->nFiredEvent_UnPS;
    this->nFiredEvent_UnPS_Scaled2e34 += Info->nFiredEvent_UnPS_Scaled2e34;

    ///
    this->nMyFiredEvent += Info->nMyFiredEvent;
    this->nMyFiredEvent_UnPS += Info->nMyFiredEvent_UnPS;
    this->nMyFiredEvent_UnPS_Scaled2e34 += Info->nMyFiredEvent_UnPS_Scaled2e34;

    this->nLumiBlock += 1;

  }

  void Save( TFile *f_output )
  {
    // -- fill histogram for total rate -- //
    if( this->nLumiBlock == 0 )
    {
      this->TotalRate = 0;
      this->TotalRate_UnPS = 0;
      this->TotalRate_UnPS_Scaled2e34 = 0;

      ///
      this->MyTotalRate = 0;
      this->MyTotalRate_UnPS = 0;
      this->MyTotalRate_UnPS_Scaled2e34 = 0;
    }
    else
    {
      this->TotalRate = this->nFiredEvent / (this->nLumiBlock * LumiBlockTime);
      this->TotalRate_UnPS = this->nFiredEvent_UnPS / (this->nLumiBlock * LumiBlockTime);
      this->TotalRate_UnPS_Scaled2e34 = this->nFiredEvent_UnPS_Scaled2e34 / (this->nLumiBlock * LumiBlockTime);

      ///
      this->MyTotalRate = this->nMyFiredEvent / (this->nLumiBlock * LumiBlockTime);
      this->MyTotalRate_UnPS = this->nMyFiredEvent_UnPS / (this->nLumiBlock * LumiBlockTime);
      this->MyTotalRate_UnPS_Scaled2e34 = this->nMyFiredEvent_UnPS_Scaled2e34 / (this->nLumiBlock * LumiBlockTime);
    }

    this->h_TotalRate->SetBinContent(1, this->TotalRate);
    this->h_TotalRate->SetBinError(1, 0);

    this->h_TotalRate_UnPS->SetBinContent(1, this->TotalRate_UnPS);
    this->h_TotalRate_UnPS->SetBinError(1, 0);

    this->h_TotalRate_UnPS_Scaled2e34->SetBinContent(1, this->TotalRate_UnPS_Scaled2e34);
    this->h_TotalRate_UnPS_Scaled2e34->SetBinError(1, 0);

    ///
    this->h_MyTotalRate->SetBinContent(1, this->MyTotalRate);
    this->h_MyTotalRate->SetBinError(1, 0);

    this->h_MyTotalRate_UnPS->SetBinContent(1, this->MyTotalRate_UnPS);
    this->h_MyTotalRate_UnPS->SetBinError(1, 0);

    this->h_MyTotalRate_UnPS_Scaled2e34->SetBinContent(1, this->MyTotalRate_UnPS_Scaled2e34);
    this->h_MyTotalRate_UnPS_Scaled2e34->SetBinError(1, 0);

    // -- Write to output -- //
    f_output->cd();

    for( const auto& h : this->vec_Hist ) {
      h->Write();
      delete h;
    }

    for( const auto& g : this->vec_Graph ) {
      g->Write();
      delete g;
    }

  }

private:
  void Init()
  {
    this->nLumiBlock = 0;

    this->nFiredEvent = 0;
    this->nFiredEvent_UnPS = 0;
    this->nFiredEvent_UnPS_Scaled2e34 = 0;
    this->TotalRate = 0;
    this->TotalRate_UnPS = 0;
    this->TotalRate_UnPS_Scaled2e34 = 0;

    ///
    this->nMyFiredEvent = 0;
    this->nMyFiredEvent_UnPS = 0;
    this->nMyFiredEvent_UnPS_Scaled2e34 = 0;
    this->MyTotalRate = 0;
    this->MyTotalRate_UnPS = 0;
    this->MyTotalRate_UnPS_Scaled2e34 = 0;


    this->h_LumiBlock_vs_nEvent = new TH1D("h_LumiBlock_vs_nEvent_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nEvent );

    this->h_LumiBlock_vs_nEvent_UnPS = new TH1D("h_LumiBlock_vs_nEvent_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nEvent_UnPS );

    this->h_LumiBlock_vs_InstLumiMean = new TH1D("h_LumiBlock_vs_InstLumiMean_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_InstLumiMean );

    this->h_LumiBlock_vs_nVerticesMean = new TH1D("h_LumiBlock_vs_nVerticesMean_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nVerticesMean );


    this->h_LumiBlock_vs_nFiredEvent = new TH1D("h_LumiBlock_vs_nFiredEvent_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nFiredEvent );

    this->h_LumiBlock_vs_nFiredEvent_UnPS = new TH1D("h_LumiBlock_vs_nFiredEvent_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nFiredEvent_UnPS );

    this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34 = new TH1D("h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nFiredEvent_UnPS_Scaled2e34 );

    this->h_LumiBlock_vs_Rate = new TH1D("h_LumiBlock_vs_Rate_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_Rate );

    this->h_LumiBlock_vs_Rate_UnPS = new TH1D("h_LumiBlock_vs_Rate_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_Rate_UnPS );

    this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34 = new TH1D("h_LumiBlock_vs_Rate_UnPS_Scaled2e34_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_Rate_UnPS_Scaled2e34 );

    ///
    this->h_LumiBlock_vs_nMyFiredEvent = new TH1D("h_LumiBlock_vs_nMyFiredEvent_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nMyFiredEvent );

    this->h_LumiBlock_vs_nMyFiredEvent_UnPS = new TH1D("h_LumiBlock_vs_nMyFiredEvent_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nMyFiredEvent_UnPS );

    this->h_LumiBlock_vs_nMyFiredEvent_UnPS_Scaled2e34 = new TH1D("h_LumiBlock_vs_nMyFiredEvent_UnPS_Scaled2e34_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_nMyFiredEvent_UnPS_Scaled2e34 );

    this->h_LumiBlock_vs_MyRate = new TH1D("h_LumiBlock_vs_MyRate_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_MyRate );

    this->h_LumiBlock_vs_MyRate_UnPS = new TH1D("h_LumiBlock_vs_MyRate_UnPS_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_MyRate_UnPS );

    this->h_LumiBlock_vs_MyRate_UnPS_Scaled2e34 = new TH1D("h_LumiBlock_vs_MyRate_UnPS_Scaled2e34_"+this->Tag, "", nMaxLumiBlock, 1, nMaxLumiBlock+1 ); // -- starts at 1 -- //
    this->vec_Hist.push_back( this->h_LumiBlock_vs_MyRate_UnPS_Scaled2e34 );


    this->h_TotalRate = new TH1D("h_TotalRate_"+this->Tag, "", 1, 0, 1);
    this->vec_Hist.push_back( this->h_TotalRate );

    this->h_TotalRate_UnPS = new TH1D("h_TotalRate_UnPS_"+this->Tag, "", 1, 0, 1);
    this->vec_Hist.push_back( this->h_TotalRate_UnPS );

    this->h_TotalRate_UnPS_Scaled2e34 = new TH1D("h_TotalRate_UnPS_Scaled2e34_"+this->Tag, "", 1, 0, 1);
    this->vec_Hist.push_back( this->h_TotalRate_UnPS_Scaled2e34 );

    ///
    this->h_MyTotalRate = new TH1D("h_MyTotalRate_"+this->Tag, "", 1, 0, 1);
    this->vec_Hist.push_back( this->h_MyTotalRate );

    this->h_MyTotalRate_UnPS = new TH1D("h_MyTotalRate_UnPS_"+this->Tag, "", 1, 0, 1);
    this->vec_Hist.push_back( this->h_MyTotalRate_UnPS );

    this->h_MyTotalRate_UnPS_Scaled2e34 = new TH1D("h_MyTotalRate_UnPS_Scaled2e34_"+this->Tag, "", 1, 0, 1);
    this->vec_Hist.push_back( this->h_MyTotalRate_UnPS_Scaled2e34 );


    this->G_Lumi_Rate = new TGraph();  (this->G_Lumi_Rate)->SetName("G_Lumi_Rate_"+this->Tag);
    this->vec_Graph.push_back( this->G_Lumi_Rate );

    this->G_Lumi_Rate_UnPS = new TGraph();  (this->G_Lumi_Rate_UnPS)->SetName("G_Lumi_Rate_UnPS_"+this->Tag);
    this->vec_Graph.push_back( this->G_Lumi_Rate_UnPS );

    this->G_Lumi_Rate_UnPS_Scaled2e34 = new TGraph();  (this->G_Lumi_Rate_UnPS_Scaled2e34)->SetName("G_Lumi_Rate_UnPS_Scaled2e34_"+this->Tag);
    this->vec_Graph.push_back( this->G_Lumi_Rate_UnPS_Scaled2e34 );

    this->G_nVertices_Rate = new TGraph();  (this->G_nVertices_Rate)->SetName("G_nVertices_Rate_"+this->Tag);
    this->vec_Graph.push_back( this->G_nVertices_Rate );

    this->G_nVertices_Rate_UnPS = new TGraph();  (this->G_nVertices_Rate_UnPS)->SetName("G_nVertices_Rate_UnPS_"+this->Tag);
    this->vec_Graph.push_back( this->G_nVertices_Rate_UnPS );

    this->G_nVertices_Rate_UnPS_Scaled2e34 = new TGraph();  (this->G_nVertices_Rate_UnPS_Scaled2e34)->SetName("G_nVertices_Rate_UnPS_Scaled2e34_"+this->Tag);
    this->vec_Graph.push_back( this->G_nVertices_Rate_UnPS_Scaled2e34 );

    ///
    this->G_Lumi_MyRate = new TGraph();  (this->G_Lumi_MyRate)->SetName("G_Lumi_MyRate_"+this->Tag);
    this->vec_Graph.push_back( this->G_Lumi_MyRate );

    this->G_Lumi_MyRate_UnPS = new TGraph();  (this->G_Lumi_MyRate_UnPS)->SetName("G_Lumi_MyRate_UnPS_"+this->Tag);
    this->vec_Graph.push_back( this->G_Lumi_MyRate_UnPS );

    this->G_Lumi_MyRate_UnPS_Scaled2e34 = new TGraph();  (this->G_Lumi_MyRate_UnPS_Scaled2e34)->SetName("G_Lumi_MyRate_UnPS_Scaled2e34_"+this->Tag);
    this->vec_Graph.push_back( this->G_Lumi_MyRate_UnPS_Scaled2e34 );

    this->G_nVertices_MyRate = new TGraph();  (this->G_nVertices_MyRate)->SetName("G_nVertices_MyRate_"+this->Tag);
    this->vec_Graph.push_back( this->G_nVertices_MyRate );

    this->G_nVertices_MyRate_UnPS = new TGraph();  (this->G_nVertices_MyRate_UnPS)->SetName("G_nVertices_MyRate_UnPS_"+this->Tag);
    this->vec_Graph.push_back( this->G_nVertices_MyRate_UnPS );

    this->G_nVertices_MyRate_UnPS_Scaled2e34 = new TGraph();  (this->G_nVertices_MyRate_UnPS_Scaled2e34)->SetName("G_nVertices_MyRate_UnPS_Scaled2e34_"+this->Tag);
    this->vec_Graph.push_back( this->G_nVertices_MyRate_UnPS_Scaled2e34 );

  }
};


class TriggerRateTool
{
public:
  Int_t maxEvents;
  vector<TString> vec_DataPath;
  vector<Int_t> vec_RunNumList;
  vector< RunHistContainer* > vec_RunHist;
  vector<TString> TriggerTag; // ex) "HLT_IsoMu27_v"

  Bool_t debug;

  TFile *f_output;

  TriggerRateTool()
  {
    this->maxEvents = -1;
    this->debug = kFALSE;
    this->TriggerTag = {""};
    this->f_output = NULL;
  }

  void Set_MaxEvents( Int_t _maxEvents )
  {
    this->maxEvents = _maxEvents;
  }

  void Set_DataList( vector<TString> _vec )
  {
    this->vec_DataPath = _vec;
  }

  void Set_RunNumList( vector<Int_t> _vec )
  {
    this->vec_RunNumList = _vec;

    // -- histogram for each run -- //
    cout << "Run list" << endl;
    Int_t nRun = (Int_t)this->vec_RunNumList.size();
    for(Int_t i=0; i<nRun; i++)
    {
      Int_t RunNum = vec_RunNumList[i];
      cout << RunNum << endl;

      TString Tag = TString::Format("Run%d", RunNum);
      RunHistContainer* Hist = new RunHistContainer( Tag );
      this->vec_RunHist.push_back( Hist );
    }
  }

  void Set_Trigger( vector<TString> _TriggerTag )
  {
    this->TriggerTag = _TriggerTag;
  }

  void Set_Output( TFile *_f_output )
  {
    this->f_output = _f_output;
  }

  void Analyze()
  {
    if(
      this->TriggerTag.size() == 0 ||
      this->f_output == NULL ||
      this->vec_DataPath.size() == 0 ||
      this->vec_RunNumList.size() == 0 )
      {
        cout << "Setup is not done accordingly!" << endl;
        return;
      }

    TChain *chain = new TChain("ntupler/ntuple");
    for( const auto& DataPath : this->vec_DataPath )
    {
      cout << "Adding...   " << DataPath << endl;
      chain->Add( DataPath );
    }

    NtupleHandle *ntuple = new NtupleHandle( chain );
    ntuple->TurnOnBranches_Event();
    ntuple->TurnOnBranches_Muon();
    ntuple->TurnOnBranches_Trigger();

    // -- initialize RunInfos -- //
    vector< RunInfos* > vec_RunInfo;
    Int_t nRun = (Int_t)this->vec_RunNumList.size();
    for(Int_t i=0; i<nRun; i++)
    {
      RunInfos* Info = new RunInfos( vec_RunNumList[i] );
      vec_RunInfo.push_back( Info );
    }

    Int_t nEvent = chain->GetEntries();
    cout << "[Total event: " << nEvent << "]" << endl;
    if(this->maxEvents > 0) {
      nEvent = this->maxEvents;
      cout << "\t --> Testing with Total event: " << nEvent << endl;
    }

    for(Int_t i_ev=0; i_ev<nEvent; i_ev++)
    {
      if(!debug)  loadBar(i_ev+1, nEvent, 100, 100);

      ntuple->GetEvent( i_ev );
      if( debug ) printf("[%d event]\n", i_ev);
      if( debug ) printf("(run, lumi, event) = (%d, %d, %llu)\n", ntuple->runNum, ntuple->lumiBlockNum, ntuple->eventNum );

      for(Int_t i=0; i<nRun; i++)
      {
        if( this->vec_RunNumList[i] == ntuple->runNum )
        {
          if( debug ) cout << "Find corresponding run number: " << this->vec_RunNumList[i] << endl;
          vec_RunInfo[i]->Fill( ntuple, TriggerTag );
          break;
        }
      }
      if( debug ) cout << endl;

    } // -- end of event iteration -- //
    if( debug ) cout << "\tend of event iteration" << endl;

    // -- fill histograms -- //
    for(Int_t i=0; i<nRun; i++)
    {
      vec_RunInfo[i]->CalcRate_EachLumiBlock();

      for( auto& LumiBlockInfo : vec_RunInfo[i]->vec_LumiBlockInfo )
      {
        // -- only for meaningful lumi-block -- //
        if( LumiBlockInfo->nEvent > 0 )
        {

          printf("[Run=%d, LumiBlock=%d] (nEvent, nFiredEvent, Rate, Rate_UnPS, Rate_UnPS_Scaled2e34) =         (%.1lf, %.1lf, %lf, %lf, %lf)\n",
            vec_RunInfo[i]->RunNum, LumiBlockInfo->LumiBlockNum, LumiBlockInfo->nEvent, LumiBlockInfo->nFiredEvent, LumiBlockInfo->Rate, LumiBlockInfo->Rate_UnPS, LumiBlockInfo->Rate_UnPS_Scaled2e34);

          printf("[Run=%d, LumiBlock=%d] (nEvent, nMyFiredEvent, MyRate, MyRate_UnPS, MyRate_UnPS_Scaled2e34) = (%.1lf, %.1lf, %lf, %lf, %lf)\n",
            vec_RunInfo[i]->RunNum, LumiBlockInfo->LumiBlockNum, LumiBlockInfo->nEvent, LumiBlockInfo->nMyFiredEvent, LumiBlockInfo->MyRate, LumiBlockInfo->MyRate_UnPS, LumiBlockInfo->MyRate_UnPS_Scaled2e34);

          // -- fill histogram for each run -- //
          vec_RunHist[i]->Fill( LumiBlockInfo );
        }
      } // -- iteration over all lumi-block in a run -- //

    } // -- iteration over all runs -- //

    this->f_output->cd();
    for(const auto& RunHist : vec_RunHist )
      RunHist->Save( f_output );

    // -- total run rates are calculated after save! -- //
    for( const auto& RunHist : vec_RunHist )
    {
      Double_t RunFiredTotal = (RunHist->nFiredEvent)*nDataset;
      Double_t RunFiredAverage = RunHist->nFiredEvent;
      Double_t RunRelUncert = 1./sqrt(RunFiredTotal);
      Double_t RunRate = RunHist->TotalRate;
      Double_t RunRate_UnPS = RunHist->TotalRate_UnPS;
      Double_t RunRate_UnPS_Scaled2e34 = RunHist->TotalRate_UnPS_Scaled2e34;

      Double_t RunMyFiredTotal = (RunHist->nMyFiredEvent)*nDataset;
      Double_t RunMyFiredAverage = RunHist->nMyFiredEvent;
      Double_t RunMyRelUncert = 1./sqrt(RunMyFiredTotal);
      Double_t RunMyRate = RunHist->MyTotalRate;
      Double_t RunMyRate_UnPS = RunHist->MyTotalRate_UnPS;
      Double_t RunMyRate_UnPS_Scaled2e34 = RunHist->MyTotalRate_UnPS_Scaled2e34;

      cout << endl;
      cout << "HLT ["<< RunHist->Tag <<"]:" << endl;
      printf("# datasets:               %d\n",  nDataset );
      printf("# fired events (total):   %.2lf\n", RunFiredTotal );
      printf("# fired events (average): %.2lf\n", RunFiredAverage );
      printf("Rel. unc.:                %.5lf\n", RunRelUncert );
      printf("Rate:                     %.3lf +/- %.5lf\n", RunRate, RunRate*RunRelUncert );
      printf("Rate_UnPS:                %.3lf +/- %.5lf\n", RunRate_UnPS, RunRate_UnPS*RunRelUncert );
      printf("UnPS_Scaled2e34:          %.3lf +/- %.5lf\n", RunRate_UnPS_Scaled2e34, RunRate_UnPS_Scaled2e34*RunRelUncert );

      cout << endl;
      cout << "MYHLT ["<< RunHist->Tag <<"]:" << endl;
      printf("# datasets:               %d\n",  nDataset );
      printf("# fired events (total):   %.2lf\n", RunMyFiredTotal );
      printf("# fired events (average): %.2lf\n", RunMyFiredAverage );
      printf("Rel. unc.:                %.5lf\n", RunMyRelUncert );
      printf("Rate:                     %.3lf +/- %.5lf\n", RunMyRate, RunMyRate*RunMyRelUncert );
      printf("Rate_UnPS:                %.3lf +/- %.5lf\n", RunMyRate_UnPS, RunMyRate_UnPS*RunMyRelUncert );
      printf("UnPS_Scaled2e34:          %.3lf +/- %.5lf\n", RunMyRate_UnPS_Scaled2e34, RunMyRate_UnPS_Scaled2e34*RunMyRelUncert );

      cout << endl;
      cout << endl;
      // printf("  HLT [%s] (# fired events, run rate, un-prescaled run rate, un-prescaled run rate scaled w.r.t 2e34) = (%.1lf, %lf, %lf, %lf)\n",
      //   RunHist->Tag.Data(), RunHist->nFiredEvent, RunRate, RunRate_UnPS, RunRate_UnPS_Scaled2e34);
      // printf("MYHLT [%s] (# fired events, run rate, un-prescaled run rate, un-prescaled run rate scaled w.r.t 2e34) = (%.1lf, %lf, %lf, %lf)\n",
      //   RunHist->Tag.Data(), RunHist->nMyFiredEvent, RunMyRate, RunMyRate_UnPS, RunMyRate_UnPS_Scaled2e34);
    }

    cout << "finished" << endl;
  }

private:

  void Init()
  {

  }

  static inline void loadBar(int x, int n, int r, int w)
  {
      // Only update r times.
      if( x == n )
        cout << endl;

      if ( x % (n/r +1) != 0 ) return;


      // Calculuate the ratio of complete-to-incomplete.
      float ratio = x/(float)n;
      int   c     = ratio * w;

      // Show the percentage complete.
      printf("%3d%% [", (int)(ratio*100) );

      // Show the load bar.
      for (int x=0; x<c; x++) cout << "=";

      for (int x=c; x<w; x++) cout << " ";

      // ANSI Control codes to go back to the
      // previous line and clear it.
    cout << "]\r" << flush;
  }
};

