#include <Include/SimplePlotTools.h>
#define nMaxLumiBlock 5000

// -- https://cmswbm.cern.ch/cmsdb/servlet/ChartHLTTriggerRates?RUNID=325170&PATHID=2122247&LSLENGTH=23.31040958&TRIGGER_PATH=HLT_IsoMu24_v13
TH1D* ProduceRateHist_fromWBM()
{
  vector<Double_t> vec_rate = 
  {
    0, // -- LS=1 does not have rate info.
    76.7468,
    159.4996,
    112.4819,
    162.3738,
    109.1358,
    160.6578,
    163.3605,
    158.5987,
    165.5484,
    163.2318,
    166.1489,
    162.5454,
    160.7007,
    161.1726,
    166.5350,
    160.1859,
    161.8161,
    158.4700,
    165.6342,
    160.8294,
    163.1889,
    155.5957,
    152.4212,
    159.5854,
    163.5321,
    155.2525,
    157.9552,
    161.6016,
    163.1889
  };

  TH1D* h_rate = new TH1D("h_rateFromWBM", "", nMaxLumiBlock, 1, nMaxLumiBlock+1);
  for(Int_t i=0; i<nMaxLumiBlock; i++)
  {
    Int_t i_bin = i+1;
    h_rate->SetBinContent(i_bin, 0);
    h_rate->SetBinError(i_bin, 0);
  }

  Int_t nValue = (Int_t)vec_rate.size();
  for(Int_t i=0; i<nValue; i++)
  {
    Int_t i_bin = i+1;
    h_rate->SetBinContent(i_bin, vec_rate[i]);
  }

  return h_rate;
}

void Validation_CompToWBM()
{
  // -- test using IsoMu24 rate
  TString fileName = "ROOTFile_DataRateTool_SingleMuon_Run325170.root";
  TH1D* h_rate = PlotTool::Get_Hist(fileName, "h_HLT_IsoMu24_vs_LB");

  // -- rate result from WBM
  TH1D* h_WBMRate = ProduceRateHist_fromWBM();

  TString canvasName = "c_rate_IsoMu24_customCode_vs_WBM";
  PlotTool::HistCanvaswRatio *canvas = new PlotTool::HistCanvaswRatio(canvasName, 0, 0);
  canvas->Register( h_WBMRate, "WBM",         kBlack);
  canvas->Register( h_rate,    "Custom code", kBlue);
  canvas->SetTitle("Lumi block number", "Rate [Hz]", "Custom/WBM");

  canvas->SetRangeX(2, 31);
  canvas->SetRangeY(0, 200);
  canvas->SetRangeRatio(0.97, 1.03);
  canvas->SetLegendPosition(0.50, 0.32, 0.95, 0.45);
  canvas->Latex_CMSPre();
  canvas->RegisterLatex(0.16, 0.91, "#font[42]{#scale[0.6]{IsoMu24 rate, Run325170}}");

  canvas->Draw();
}