import FWCore.ParameterSet.Config as cms


#muon skim part
looseMuons = cms.EDFilter("PATMuonSelector",
  src = cms.InputTag("selectedPatMuons"),
  cut = cms.string('pt > 10 & abs(eta) < 2.1 & isGlobalMuon'),
  filter = cms.bool(False)                                
)

#electron skim part
looseElectrons = cms.EDFilter("PATElectronSelector",
  src = cms.InputTag("selectedPatElectrons"),
  cut = cms.string('pt >  20 & abs(eta) < 2.4'),
)

#electrons for z veto part
zVetoElectrons = cms.EDFilter("PATElectronSelector",
  src = cms.InputTag("selectedPatElectrons"),
  cut = cms.string('pt >  20 & abs(eta) < 2.4'),
)

preselectedJets = cms.EDFilter("PATJetSelector",
  src = cms.InputTag("selectedPatJets"),
  cut = cms.string('pt >  30 & abs(eta) < 5.0'),
  filter = cms.bool(False)                                
)

#UnclusteredMET
UnclusteredMETPF = cms.EDProducer("SingleTopUnclusteredMETProducer",
                                  metSource = cms.InputTag("patMETs"),
                                  jetsSource = cms.InputTag("selectedPatJets"),
                                  electronsSource = cms.InputTag("selectedPatElectrons"),
                                  muonsSource = cms.InputTag("selectedPatMuons"),
                                  )

UnclusteredType1METPF = cms.EDProducer("SingleTopUnclusteredMETProducer",
                                                                         metSource = cms.InputTag("patType1CorrectedPFMet"),
                                                                         jetsSource = cms.InputTag("selectedPatJets"),
                                                                         electronsSource = cms.InputTag("patElectrons"),
                                                                         muonsSource = cms.InputTag("patMuons"),
                                                                         )

#genJets:
genJetsPF = cms.EDProducer("SingleTopGenJetPtEtaProducer",
                                                    jetsSource = cms.InputTag("topJetsPF"),
                                                    )



#PDF Info
NVertices = cms.EDProducer("SingleTopPileUpProducer")

#n gen particles Info
NGenParticles = cms.EDProducer("SingleTopNGenParticlesProducer")

#PDF Info
PDFInfo = cms.EDProducer("PDFInfoDumper",
                         )

topJetsPF = cms.EDFilter("PATJetSelector",
                         preselection = cms.string(''),
                         src = cms.InputTag("selectedPatJets"),
                         cut = cms.string('pt >  20 & abs(eta) < 5.'),
                         checkOverlaps = cms.PSet(),
                           )

tightMuons = cms.EDFilter("PATMuonSelector",
                        preselection = cms.string(''),
                        src = cms.InputTag("selectedPatMuons"),
                        cut = cms.string(''),
                        checkOverlaps = cms.PSet(),
                        )

tightElectrons = cms.EDFilter("PATElectronSelector",
                        preselection = cms.string(''),
                        src = cms.InputTag("selectedPatElectrons"),
                        cut = cms.string(''),
                        checkOverlaps = cms.PSet(),
                         )

tightElectronsZeroIso = cms.EDFilter("PATElectronSelector",
                       preselection = cms.string(''),
                       src = cms.InputTag("patElectronsZeroIso"),
                       cut = cms.string(''),
                       checkOverlaps = cms.PSet(),
                                     )

tightMuonsZeroIso = cms.EDFilter("PATMuonSelector",
                                 preselection = cms.string(''),
                                 src = cms.InputTag("patMuonsZeroIso"),
                                 cut = cms.string(''),
                                 checkOverlaps = cms.PSet(),
                                 )

#Met skim part
preselectedMETs = cms.EDFilter("PATMETSelector",
  src = cms.InputTag("patMETs"),
  cut = cms.string('pt >   0'),
  filter = cms.bool(False)                                
)


#Part of MC Truth particles production
MCTruthParticles = cms.EDProducer("SingleTopTChannelMCProducer",
                                          genParticlesSource = cms.InputTag("genParticles")
                                          )

##################Trigger matching part


PatJetTriggerMatchHLTIsoMuBTagIP = cms.EDProducer(
    "PATTriggerMatcherDRDPtLessByR"                 # match by DeltaR only, best match by DeltaR
    , src     = cms.InputTag( "selectedPatJets" )
    , matched = cms.InputTag( "patTrigger" )          # default producer label as defined in PhysicsTools/PatAlgos/python/triggerLayer1/triggerProducer_cfi.py
    #    , matchedCuts = cms.string( 'path("HLT_IsoMu17_eta2p1_CentralJet30_v*") ' )
    , matchedCuts = cms.string( 'path( "HLT_IsoMu17_CentralJet30_BTagIP_v*" ) || path( "HLT_IsoMu17_eta2p1_CentralJet30_BTagIP_v*" ) ' )
    #    , matchedCuts = cms.string(' path( "HLT_IsoMu17_eta2p1_CentralJet30_BTagIP_v*") ')
    , maxDPtRel = cms.double( 0.5 )
    , maxDeltaR = cms.double( 0.5 )
    , resolveAmbiguities    = cms.bool( True )        # only one match per trigger object
    , resolveByMatchQuality = cms.bool( True )        # take best match found per reco object: by DeltaR here (s. above)
    )


PatJetTriggerMatchHLTIsoEleBTagIP = cms.EDProducer(
    "PATTriggerMatcherDRDPtLessByR"                 # match by DeltaR only, best match by DeltaR
    , src     = cms.InputTag( "selectedPatJets" )
    , matched = cms.InputTag( "patTrigger" )          # default producer label as defined in PhysicsTools/PatAlgos/python/triggerLayer1/triggerProducer_cfi.py
    , matchedCuts = cms.string( 'path( "HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralJet30_BTagIP_v*" )' )
    , maxDPtRel = cms.double( 0.5 )
    , maxDeltaR = cms.double( 0.5 )
    , resolveAmbiguities    = cms.bool( True )        # only one match per trigger object
    , resolveByMatchQuality = cms.bool( True )        # take best match found per reco object: by DeltaR here (s. above)
    )


triggerMatchingSequence = cms.Sequence(
    PatJetTriggerMatchHLTIsoMuBTagIP # +#    somePatMuonTriggerMatchHLTEle27WP80
    )
