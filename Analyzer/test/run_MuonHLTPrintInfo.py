process = cms.Process("MuonHLT")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/user/k/kplee/work/private/MuonHLT/v20181107_v01_RemoveIOFromL1/output_NoIOFromL1_skimmed.root'),
    secondaryFileNames = cms.untracked.vstring(),
    # lumisToProcess = cms.untracked.VLuminosityBlockRange('258158:1-258158:1786'),
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '101X_dataRun2_Prompt_v9'

process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load('Configuration.Geometry.GeometryRecoDB_cff')

process.MessageLogger = cms.Service( "MessageLogger",
    destinations = cms.untracked.vstring("cerr"),
    cerr = cms.untracked.PSet( threshold = cms.untracked.string('ERROR'), ),
    )


from MuonHLTTool.Analyzer.MuonHLTPrintInfo_cfi import muonHLTPrintInfo
process.muonHLTPrintInfo = muonHLTPrintInfo.clone()
process.printL3Muon = cms.untracked.bool(True)
process.printL2Muon = cms.untracked.bool(True)
process.printL1Muon = cms.untracked.bool(True)

process.printIterL3OI        = cms.untracked.bool(True)
process.printIterL3IOFromL2  = cms.untracked.bool(True)
process.printIterL3FromL2    = cms.untracked.bool(True)
process.printIterL3IOFromL1  = cms.untracked.bool(True)
process.printIterL3MuonNoID  = cms.untracked.bool(True)

process.path = cms.Path(process.muonHLTPrintInfo)
