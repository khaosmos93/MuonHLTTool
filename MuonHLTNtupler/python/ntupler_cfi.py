import FWCore.ParameterSet.Config as cms

ntuplerBase = cms.EDAnalyzer("MuonHLTNtupler",
	# -- information stored in edm file
	triggerResults    = cms.untracked.InputTag("TriggerResults::HLT"),
	triggerEvent      = cms.untracked.InputTag("hltTriggerSummaryAOD::HLT"),
	offlineLumiScaler = cms.untracked.InputTag("scalersRawToDigi"),
	offlineVertex     = cms.untracked.InputTag("offlinePrimaryVertices"),
	offlineMuon       = cms.untracked.InputTag("muons"),

	# -- newly created objects by HLT rerun
	# -- new process name = "MYHLT"
	myTriggerResults = cms.untracked.InputTag("TriggerResults",       "", "MYHLT"),
	myTriggerEvent   = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "MYHLT"),
	lumiScaler       = cms.untracked.InputTag("hltScalersRawToDigi",  "", "MYHLT"),

	L1Muon = cms.untracked.InputTag("hltGmtStage2Digis",       "Muon", "MYHLT"), # -- if L1 emulator is used
	# L1Muon = cms.untracked.InputTag("gmtStage2Digis",          "Muon", "RECO"), # -- if L1 is not emulated
	L2Muon = cms.untracked.InputTag("hltL2MuonCandidates",     "",     "MYHLT"),
	L3Muon = cms.untracked.InputTag("hltIterL3MuonCandidates", "",     "MYHLT"),
	TkMuon = cms.untracked.InputTag("hltHighPtTkMuonCands",    "",     "MYHLT"),

	iterL3OI        = cms.untracked.InputTag("hltL3MuonsIterL3OI",                   "", "MYHLT"),
	iterL3IOFromL2  = cms.untracked.InputTag("hltL3MuonsIterL3IO",                   "", "MYHLT"),
	iterL3FromL2    = cms.untracked.InputTag("hltIterL3MuonsFromL2LinksCombination", "", "MYHLT"),
	iterL3IOFromL1  = cms.untracked.InputTag("hltIter3IterL3FromL1MuonMerged",       "", "MYHLT"),
	iterL3MuonNoID  = cms.untracked.InputTag("hltIterL3MuonsNoID",                   "", "MYHLT"),

	# -- generator information
	PUSummaryInfo = cms.untracked.InputTag("addPileupInfo"),
	genEventInfo = cms.untracked.InputTag("generator"),
	genParticle = cms.untracked.InputTag("genParticles"),

	# -- miniAOD information
	isMiniAOD             = cms.bool(False),
	triggerObject_miniAOD = cms.untracked.InputTag("notUsed"), # -- only used when isMiniAOD == True

	# isMiniAOD             = cms.untracked.bool(True),
	# triggerObject_miniAOD = cms.untracked.InputTag("slimmedPatTrigger")
)
