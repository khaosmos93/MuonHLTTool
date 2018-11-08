import FWCore.ParameterSet.Config as cms

muonHLTPrintInfo = cms.EDAnalyzer("MuonHLTPrintInfo",
    triggerResults = cms.untracked.InputTag("TriggerResults::MYHLT"),
    triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD::MYHLT"),

    L3Muon = cms.untracked.InputTag("hltIterL3MuonCandidates"),
    L2Muon = cms.untracked.InputTag("hltL2MuonCandidates"),
    L1Muon = cms.untracked.InputTag("hltGtStage2Digis", "Muon"),

    iterL3OI        = cms.untracked.InputTag("hltL3MuonsIterL3OI", "", "MYHLT"),
    iterL3IOFromL2  = cms.untracked.InputTag("hltL3MuonsIterL3IO", "", "MYHLT"),
    iterL3FromL2    = cms.untracked.InputTag("hltIterL3MuonsFromL2LinksCombination", "", "MYHLT"),
    iterL3IOFromL1  = cms.untracked.InputTag("hltIter3IterL3FromL1MuonMerged", "", "MYHLT"),
    iterL3MuonNoID  = cms.untracked.InputTag("hltIterL3MuonsNoID", "", "MYHLT"),

    # -- flag to print
    printL3Muon = cms.untracked.bool(False),
    printL2Muon = cms.untracked.bool(False),
    printL1Muon = cms.untracked.bool(False),

    printIterL3OI        = cms.untracked.bool(False),
    printIterL3IOFromL2  = cms.untracked.bool(False),
    printIterL3FromL2    = cms.untracked.bool(False),
    printIterL3IOFromL1  = cms.untracked.bool(False),
    printIterL3MuonNoID  = cms.untracked.bool(False),
)
