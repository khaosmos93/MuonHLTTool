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

config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'

version = '_v20181213_RAWOnly_'

# 'MultiCRAB' part
if __name__ == '__main__':
    
    from CRABAPI.RawCommand import crabCommand

    # -- one of the run in the last fill of Run 2 (~270 /pb)
    config.General.requestName = 'MuonHLTNtuple'+version+'SingleMuon_Run2018D_Run325170'
    config.Data.inputDataset = '/SingleMuon/Run2018D-v1/RAW'
    config.Data.runRange = '325170-325170'
    crabCommand('submit', config = config)

