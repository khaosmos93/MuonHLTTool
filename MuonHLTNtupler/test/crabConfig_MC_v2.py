from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.workArea = 'CRABDir'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'HLTCfgMC_Mu_ntupler.py'
config.JobType.numCores = 4
# config.JobType.maxMemoryMB = 2500
# config.JobType.maxJobRuntimeMin = 2000

config.Data.inputDataset = ''
# config.Data.useParent = True

config.Data.inputDBS = 'global'

# config.Data.splitting = 'Automatic' # -- it is not preferred: test job is frequently failed due to memory
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 3

config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Site.storageSite = 'T2_KR_KNU'

version = '_v20181121_RAWOnly_'

# 'MultiCRAB' part
if __name__ == '__main__':
    
    from CRABAPI.RawCommand import crabCommand

    # # -- W
    config.General.requestName = 'MuonHLTNtuple'+version+'92X_WJetsToLNu_Madgraph'
    config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_SUS01_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    # # -- Z
    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M50to120_Powheg'
    # config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_50_120/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M120to200_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_120_200/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M200to400_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_200_400/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M400to800_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_400_800/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M800to1400_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_800_1400/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M1400to2300_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_1400_2300/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M2300to3500_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_2300_3500/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M3500to4500_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_3500_4500/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M4500to6000_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_4500_6000/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_ZToMuMu_M6000toInf_Powheg'
    config.Data.inputDataset = '/ZToMuMu_NNPDF30_13TeV-powheg_M_6000_Inf/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    # # -- ttbar
    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_TT_Powheg'
    # config.Data.inputDataset = '/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

    # # -- QCD, mu-enriched
    config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt15to20'
    config.Data.inputDataset = '/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt20to30'
    config.Data.inputDataset = '/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt30to50'
    config.Data.inputDataset = '/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt50to80'
    # config.Data.inputDataset = '/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt80to120'
    # config.Data.inputDataset = '/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

    config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt120to170'
    config.Data.inputDataset = '/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/GEN-SIM-RAW'
    crabCommand('submit', config = config)

    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt170to300'
    # config.Data.inputDataset = '/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt300to470'
    # config.Data.inputDataset = '/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

    # config.General.requestName = 'MuonHLTNtuple'+version+'92X_MuEnrichedQCD_Pt470to600'
    # config.Data.inputDataset = '/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/RunIISummer17DRStdmix-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/GEN-SIM-RAW'
    # crabCommand('submit', config = config)

