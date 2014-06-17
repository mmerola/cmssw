import FWCore.ParameterSet.Config as cms

process = cms.Process('TOPDQM')

## imports of standard configurations
process.load('DQMOffline.Configuration.DQMOffline_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

## --------------------------------------------------------------------
## Frontier Conditions: (adjust accordingly!!!)
##
## For CMSSW_3_8_X MC use             ---> 'START38_V12::All'
## For Data (38X re-processing) use   ---> 'GR_R_38X_V13::All'
## For Data (38X prompt reco) use     ---> 'GR10_P_V10::All'
##
## For more details have a look at: WGuideFrontierConditions
## --------------------------------------------------------------------
##process.GlobalTag.globaltag = 'GR_R_42_V14::All' 
process.GlobalTag.globaltag = 'POSTLS171_V1::All'

#dbs search --query 'find file where site=srm-eoscms.cern.ch and dataset=/RelValTTbar/CMSSW_7_0_0_pre3-PRE_ST62_V8-v1/GEN-SIM-RECO'
#dbs search --query 'find dataset where dataset=/RelValTTbar/CMSSW_7_0_0_pre6*/GEN-SIM-RECO'

## input file(s) for testing
process.source = cms.Source("PoolSource",
    #fileNames = cms.untracked.vstring("file:input.root',")
    fileNames = cms.untracked.vstring(
    #"/store/relval/CMSSW_6_2_0_pre1-START61_V8/RelValTTbarLepton/GEN-SIM-RECO/v1/00000/C6CC53CC-6E6D-E211-8EAB-003048D3756A.root',"
    
    #/RelValTTbar/CMSSW_7_0_0_pre6-PRE_ST62_V8-v1/GEN-SIM-RECO
#        '/store/relval/CMSSW_7_0_0_pre13/RelValTTbar_13/GEN-SIM-RECO/PU25ns_POSTLS170_V3-v1/00000/1E407758-2F90-E311-AF63-0025905A6118.root',
#     '/store/relval/CMSSW_7_1_0_pre4/RelValTTbarLepton_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/48ED95A2-66AA-E311-9865-02163E00E5AE.root',
#     '/store/relval/CMSSW_7_1_0_pre4/RelValTTbar_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/10C41776-E0AA-E311-BD4D-02163E00E914.root',
#     '/store/relval/CMSSW_7_1_0_pre4/RelValTTbar_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/12627EB2-6BAA-E311-95E6-02163E00EB1C.root',
#     '/store/relval/CMSSW_7_1_0_pre4/RelValTTbar_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/8C0E1D82-95AA-E311-8788-02163E00E7C5.root',
#     '/store/relval/CMSSW_7_1_0_pre4/RelValTTbar_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/941B48A3-84AA-E311-8B59-02163E00CFDF.root', 
 
   '/store/relval/CMSSW_7_1_0_pre4/RelValTTbarLepton_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/48ED95A2-66AA-E311-9865-02163E00E5AE.root',
   '/store/relval/CMSSW_7_1_0_pre4/RelValTTbarLepton_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/6493F7B6-5BAA-E311-BAF4-02163E00E7AF.root',
   '/store/relval/CMSSW_7_1_0_pre4/RelValTTbarLepton_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/94843F2F-6BAA-E311-B4EF-02163E00EA7F.root',
   '/store/relval/CMSSW_7_1_0_pre4/RelValTTbarLepton_13/GEN-SIM-RECO/POSTLS171_V1-v2/00000/9E3D1FFE-71AA-E311-A2F1-0025904B5B28.root',

    #'/store/relval/CMSSW_7_0_0_pre6/RelValTTbar/GEN-SIM-RECO/PRE_ST62_V8-v1/00000/B627D32C-0B3C-E311-BBE6-0026189438E6.root',
    #'/store/relval/CMSSW_7_0_0_pre6/RelValTTbar/GEN-SIM-RECO/PRE_ST62_V8-v1/00000/72477A84-F93B-E311-BF63-003048FFD720.root',
    #'/store/relval/CMSSW_7_0_0_pre6/RelValTTbar/GEN-SIM-RECO/PRE_ST62_V8-v1/00000/12A06D7A-F93B-E311-AA64-003048678BEA.root'
    )
)

## number of events
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)

## apply VBTF electronID (needed for the current implementation
## of topSingleElectronDQMLoose and topSingleElectronDQMMedium)
#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("DQM.Physics.topElectronID_cff")
process.load('Configuration/StandardSequences/Reconstruction_cff')


### output ###
process.output = cms.OutputModule("PoolOutputModule",
  fileName       = cms.untracked.string('topDQM_production.root'),
  outputCommands = cms.untracked.vstring(
    'drop *_*_*_*',
    'keep *_*_*_TOPDQM',
    'drop *_TriggerResults_*_TOPDQM',
    'drop *_simpleEleId70cIso_*_TOPDQM',
  ),
  splitLevel     = cms.untracked.int32(0),
  dataset = cms.untracked.PSet(
    dataTier   = cms.untracked.string(''),
    filterName = cms.untracked.string('')
  )
)

## load jet corrections
process.load("JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff")
process.prefer("ak5PFL2L3")

## check the event content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

## load the electron MVA ID
process.load("EgammaAnalysis.ElectronTools.electronIdMVAProducer_cfi")
process.mvaTrigV0.electronTag = cms.InputTag("gedGsfElectrons")
process.mvaNonTrigV0.electronTag = cms.InputTag("gedGsfElectrons")
#process.mvaTrigV0.electronTag = cms.InputTag("pfIsolatedElectronsEI")
#process.mvaNonTrigV0.electronTag = cms.InputTag("pfIsolatedElectronsEI")


## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TopSingleLeptonDQM'   )
process.MessageLogger.cerr.TopSingleLeptonDQM    = cms.untracked.PSet(limit = cms.untracked.int32(1))
process.MessageLogger.categories.append('TopDiLeptonOfflineDQM')
process.MessageLogger.cerr.TopDiLeptonOfflineDQM = cms.untracked.PSet(limit = cms.untracked.int32(1))
process.MessageLogger.categories.append('SingleTopTChannelLeptonDQM'   )
process.MessageLogger.cerr.SingleTopTChannelLeptonDQM    = cms.untracked.PSet(limit = cms.untracked.int32(1))
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MEtoEDMConverter.deleteAfterCopy = cms.untracked.bool(False)  ## line added to avoid crash when changing run number


## path definitions
process.p      = cms.Path(
    #process.simpleEleId70cIso          *
#    process.mvaTrigV0                     +
#    process.mvaNonTrigV0               +
    process.DiMuonDQM                  +
    process.DiElectronDQM              +
    process.ElecMuonDQM                +
#    process.topSingleMuonLooseDQM      +
    process.topSingleMuonMediumDQM     +
#    process.topSingleElectronLooseDQM  +
    process.topSingleElectronMediumDQM +
    process.singleTopMuonMediumDQM     +
    process.singleTopElectronMediumDQM
)

process.endjob = cms.Path(
    process.endOfProcess
)
process.fanout = cms.EndPath(
    process.output
)

## schedule definition
process.schedule = cms.Schedule(
    process.p,
    process.endjob,
    process.fanout
)
