import FWCore.ParameterSet.Config as cms

process = cms.Process("MuonHLT")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/user/k/kplee/work/private/MuonHLT/v20181107_v01_RemoveIOFromL1/CMSSW_10_3_1/src/output_NoIOFromL1.root'),
    secondaryFileNames = cms.untracked.vstring(),
    # lumisToProcess = cms.untracked.VLuminosityBlockRange('258158:1-258158:1786'),
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
# process.GlobalTag.globaltag = '101X_dataRun2_Prompt_v9'
process.GlobalTag.globaltag = "103X_upgrade2018_realistic_HI_v6" # -- HI

process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.Geometry.GeometryRecoDB_cff')

process.MessageLogger = cms.Service( "MessageLogger",
    destinations = cms.untracked.vstring("cerr"),
    cerr = cms.untracked.PSet( threshold = cms.untracked.string('ERROR'), ),
    )


from MuonHLTTool.Analyzer.MuonHLTPrintInfo_cfi import muonHLTPrintInfo
process.muonHLTPrintInfo = muonHLTPrintInfo.clone()

process.muonHLTPrintInfo.triggerResults = cms.untracked.InputTag("TriggerResults::MyHLT")
process.muonHLTPrintInfo.triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD::MyHLT")

process.muonHLTPrintInfo.L3Muon = cms.untracked.InputTag("hltIterL3MuonCandidatesPPOnAA")
process.muonHLTPrintInfo.L2Muon = cms.untracked.InputTag("hltL2MuonCandidatesPPOnAA")
process.muonHLTPrintInfo.L1Muon = cms.untracked.InputTag("hltGtStage2Digis", "Muon")

process.muonHLTPrintInfo.iterL3OI        = cms.untracked.InputTag("hltL3MuonsIterL3OIPPOnAA", "", "MyHLT")
process.muonHLTPrintInfo.iterL3IOFromL2  = cms.untracked.InputTag("hltL3MuonsIterL3IOPPOnAA", "", "MyHLT")
process.muonHLTPrintInfo.iterL3FromL2    = cms.untracked.InputTag("hltIterL3MuonsFromL2LinksCombinationPPOnAA", "", "MyHLT")
process.muonHLTPrintInfo.L1MuonsPt0      = cms.untracked.InputTag("hltL1MuonsPt0PPOnAA::MyHLT")
process.muonHLTPrintInfo.iterL3IOFromL1  = cms.untracked.InputTag("hltIter3IterL3FromL1MuonMergedPPOnAA", "", "MyHLT")
process.muonHLTPrintInfo.iterL3MuonNoID  = cms.untracked.InputTag("hltIterL3MuonsNoIDPPOnAA", "", "MyHLT")

process.muonHLTPrintInfo.printL3Muon = cms.untracked.bool(True)
process.muonHLTPrintInfo.printL2Muon = cms.untracked.bool(True)
process.muonHLTPrintInfo.printL1Muon = cms.untracked.bool(True)

process.muonHLTPrintInfo.printIterL3OI        = cms.untracked.bool(True)
process.muonHLTPrintInfo.printIterL3IOFromL2  = cms.untracked.bool(True)
process.muonHLTPrintInfo.printIterL3FromL2    = cms.untracked.bool(True)
process.muonHLTPrintInfo.printL1MuonsPt0      = cms.untracked.bool(True)
process.muonHLTPrintInfo.printIterL3IOFromL1  = cms.untracked.bool(True)
process.muonHLTPrintInfo.printIterL3MuonNoID  = cms.untracked.bool(True)

process.muonHLTPrintInfo.printTriggerObjects = cms.untracked.bool(True)
process.muonHLTPrintInfo.triggerObjects = cms.untracked.vstring(
    "hltL1fL1sL1DoubleMuOpenL1Filtered0::MyHLT",
    "hltL1fForIterL3L1fL1sL1DoubleMuOpenL1Filtered0::MyHLT", 
    "hltL3fL1DoubleMuOpenL3Filtered0::MyHLT")

process.path = cms.Path(process.muonHLTPrintInfo)