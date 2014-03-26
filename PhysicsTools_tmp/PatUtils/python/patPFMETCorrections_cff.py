import FWCore.ParameterSet.Config as cms

# load modules for producing Type 1 / Type 1 + 2 corrections for reco::PFMET objects
from JetMETCorrections.Type1MET.pfMETCorrections_cff import *

#--------------------------------------------------------------------------------
# produce "raw" (uncorrected) pat::MET of PF-type
from PhysicsTools.PatAlgos.producersLayer1.metProducer_cfi import patMETs
patPFMet = patMETs.clone(
    metSource = cms.InputTag('pfMet'),
    addMuonCorrections = cms.bool(False),
    genMETSource = cms.InputTag('genMetTrue')
)
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# select collection of pat::Jets entering Type 1 + 2 MET corrections
#
# NOTE: do not compute Type 1 MET corrections for |eta| > 4.7,
#       in order to work around problem with CMSSW_4_2_x JEC factors at high eta,
#       reported in
#         https://hypernews.cern.ch/HyperNews/CMS/get/jes/270.html
#         https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/1259/1.html
#                         
selectedPatJetsForMETtype1p2Corr = cms.EDFilter("PATJetSelector",
    src = cms.InputTag('patJets'),                                    
    cut = cms.string('abs(eta) < 4.7'),
    filter = cms.bool(False)
)

selectedPatJetsForMETtype2Corr = cms.EDFilter("PATJetSelector",
    src = cms.InputTag('patJets'),                                               
    cut = cms.string('abs(eta) > 4.7'),
    filter = cms.bool(False)
)
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce Type 1 + 2 MET corrections for pat::Jets of PF-type
patPFJetMETtype1p2Corr = cms.EDProducer("PATPFJetMETcorrInputProducer",
    src = cms.InputTag('selectedPatJetsForMETtype1p2Corr'),
    offsetCorrLabel = cms.string("L1FastJet"),
    jetCorrLabel = cms.string("L3Absolute"), # NOTE: use "L3Absolute" for MC / "L2L3Residual" for Data
    type1JetPtThreshold = cms.double(10.0),
    skipEM = cms.bool(True),
    skipEMfractionThreshold = cms.double(0.90),
    skipMuons = cms.bool(True),
    skipMuonSelection = cms.string("isGlobalMuon | isStandAloneMuon")
)

patPFJetMETtype2Corr = patPFJetMETtype1p2Corr.clone(
    src = cms.InputTag('selectedPatJetsForMETtype2Corr')
)    
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# use MET corrections to produce Type 1 / Type 1 + 2 corrected PFMET objects
patType1CorrectedPFMet = cms.EDProducer("CorrectedPATMETProducer",
    src = cms.InputTag('patPFMet'),
    applyType1Corrections = cms.bool(True),
    srcType1Corrections = cms.VInputTag(
        cms.InputTag('patPFJetMETtype1p2Corr', 'type1')
    ),
    applyType2Corrections = cms.bool(False)
)   

patType1p2CorrectedPFMet = cms.EDProducer("CorrectedPATMETProducer",
    src = cms.InputTag('patPFMet'),
    applyType1Corrections = cms.bool(True),
    srcType1Corrections = cms.VInputTag(
        cms.InputTag('patPFJetMETtype1p2Corr', 'type1')
    ),
    applyType2Corrections = cms.bool(True),
    srcUnclEnergySums = cms.VInputTag(
        cms.InputTag('patPFJetMETtype1p2Corr', 'type2' ),
        cms.InputTag('patPFJetMETtype2Corr',   'type2' ),                                   
        cms.InputTag('patPFJetMETtype1p2Corr', 'offset'),
        cms.InputTag('pfCandMETcorr')                                    
    ),                              
    type2CorrFormula = cms.string("A"),
    type2CorrParameter = cms.PSet(
        A = cms.double(1.4)
    )
)   
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# define sequence to run all modules
producePatPFMETCorrections = cms.Sequence(
    patPFMet
   * kt6PFNewJets
   * ak5PFJets
   * pfCandsNotInJet
   * selectedPatJetsForMETtype1p2Corr
   * selectedPatJetsForMETtype2Corr 
   * patPFJetMETtype1p2Corr
   * patPFJetMETtype2Corr
   * pfCandMETcorr 
   * patType1CorrectedPFMet
   * patType1p2CorrectedPFMet
)
#--------------------------------------------------------------------------------
