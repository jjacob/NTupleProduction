from WMCore.Configuration import Configuration
from BristolAnalysis.NTupleTools.BLT_unfold import input_files
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'TTJets_central_7TeV_madgraph_BLTUnfold_NoSkim'
config.General.transferLogs = True
config.section_('JobType')
config.JobType.psetName = 'BristolAnalysis/NTupleTools/test/unfoldingBLT_cfg.py'
config.JobType.pluginName = 'Analysis'
config.JobType.inputFiles = input_files

config.JobType.pyCfgParams = ['useData=0', 'dataType=TTJets', 'isTTbarMC=1', 'skim=NoSkim', 'CMSSW=53X', 'centreOfMassEnergy=7', 'storePDFWeights=1', 'applyType0METcorrection=1', 'applySysShiftCorrection=1']
config.section_('Data')
config.Data.inputDataset = '/TTJets_MSDecays_central_TuneZ2_7TeV-madgraph-tauola/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM'
config.Data.unitsPerJob = 3
config.Data.splitting = 'FileBased'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_UK_SGrid_Bristol'
