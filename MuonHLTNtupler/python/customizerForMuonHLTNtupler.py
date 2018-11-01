# -- custoimzer for ntupler that can be added to the HLT configuration for re-running HLT
# -- add "--customize" option in hltGetConfiguration:
# -- ex> --customise MuonHLTTool/MuonHLTNtupler/customizerForMuonHLTNtupler.customizerFuncForMuonHLTNtupler

import FWCore.ParameterSet.Config as cms

def customizerFuncForMuonHLTNtupler(process, newProcessName = "MYHLT"):
    if hasattr(process, "DQMOutput"):
        del process.DQMOutput

    from MuonHLTTool.MuonHLTNtupler.ntupler_cfi import ntuplerBase

    process.ntupler = ntuplerBase.clone()

    # -- objects in the dataset
    process.ntupler.triggerResults    = cms.untracked.InputTag("TriggerResults", "", "HLT")
    process.ntupler.triggerEvent      = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "HLT")
    process.ntupler.offlineLumiScaler = cms.untracked.InputTag("scalersRawToDigi")
    process.ntupler.offlineMuon       = cms.untracked.InputTag("muons")

    # -- rerun object
    process.ntupler.lumiScaler       = cms.untracked.InputTag("hltScalersRawToDigi",     "",     newProcessName)
    process.ntupler.L1Muon           = cms.untracked.InputTag("hltGtStage2Digis",        "Muon", newProcessName)
    process.ntupler.L2Muon           = cms.untracked.InputTag("hltL2MuonCandidates",     "",     newProcessName)
    process.ntupler.L3Muon           = cms.untracked.InputTag("hltIterL3MuonCandidates", "",     newProcessName)
    process.ntupler.iterL3MuonNoID   = cms.untracked.InputTag("hltIterL3MuonsNoID",      "",     newProcessName)
    process.ntupler.myTriggerResults = cms.untracked.InputTag("TriggerResults",          "",     newProcessName)
    process.ntupler.myTriggerEvent   = cms.untracked.InputTag("hltTriggerSummaryAOD",    "",     newProcessName)


    process.TFileService = cms.Service("TFileService",
      fileName = cms.string("ntuple.root"),
      closeFileFast = cms.untracked.bool(False),
      )

    process.mypath = cms.EndPath(process.ntupler)

    return process

