#include "Validation/RecoMuon/src/RecoMuonValidatorPF.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByChi2.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"

#include "SimMuon/MCTruth/interface/MuonAssociatorByHits.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"

// for selection cut
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

#include "TMath.h"

using namespace std;
using namespace edm;
using namespace reco;

typedef TrajectoryStateOnSurface TSOS;
typedef FreeTrajectoryState FTS;

//
//struct for histogram dimensions
//
struct HistoDimensions {
  //p
  unsigned int nBinP;
  double minP, maxP;
  //pt
  unsigned int nBinPt;
  double minPt, maxPt;
  //if abs eta
  bool doAbsEta;
  //eta
  unsigned int nBinEta;
  double minEta, maxEta;
  //phi
  unsigned int nBinPhi;
  double minPhi, maxPhi;
  //dxy
  unsigned int nBinDxy;
  double minDxy, maxDxy;
  //dz
  unsigned int nBinDz; 
  double minDz, maxDz;
  //pulls
  unsigned int nBinPull;
  double wPull;
  //resolustions
  unsigned int nBinErr;
  double minErrP, maxErrP;
  double minErrPt, maxErrPt;
  double minErrQPt, maxErrQPt;
  double minErrEta, maxErrEta;
  double minErrPhi, maxErrPhi;
  double minErrDxy, maxErrDxy;
  double minErrDz, maxErrDz;
  //track multiplicities
  unsigned int nTrks, nAssoc;
  unsigned int nDof;
};

//
//Struct containing all histograms definitions
//
struct RecoMuonValidatorPF::MuonME {
  typedef MonitorElement* MEP;

//general kinematics
  MEP hSimP_, hSimPt_, hSimEta_, hSimPhi_, hSimDxy_, hSimDz_;
//only for efficiencies
  MEP hP_, hPt_, hEta_, hPhi_;
  MEP hNSim_, hNMuon_;

//misc vars
  MEP hNTrks_, hNTrksEta_,  hNTrksPt_;
  MEP hMisQPt_, hMisQEta_;

//resolutions
  MEP hErrP_, hErrPt_, hErrEta_, hErrPhi_;
  MEP hErrPBarrel_, hErrPOverlap_, hErrPEndcap_;
  MEP hErrPtBarrel_, hErrPtOverlap_, hErrPtEndcap_;
  MEP hErrDxy_, hErrDz_;

  MEP hErrP_vs_Eta_, hErrPt_vs_Eta_, hErrQPt_vs_Eta_;
  MEP hErrP_vs_P_, hErrPt_vs_Pt_, hErrQPt_vs_Pt_, hErrEta_vs_Eta_;

//PF-RECO event-by-event comparisons
  MEP hErrPt_PF_;
  MEP hErrQPt_PF_;
  MEP hdPt_vs_Eta_;
  MEP hdPt_vs_Pt_;
  MEP hPFMomPicked, hPFDirectionPicked, hPFMomAssCorrectness;
  MEP hPt_vs_PFMomPicked, hPt_vs_PFDirectionPicked, hPt_vs_PFMomAssCorrectness;

//hit pattern
  MEP hNSimHits_;
  MEP hNSimToReco_, hNRecoToSim_;

  MEP hNHits_, hNLostHits_, hNTrackerHits_, hNMuonHits_;
  MEP hNHits_vs_Pt_, hNHits_vs_Eta_;
  MEP hNLostHits_vs_Pt_, hNLostHits_vs_Eta_;
  MEP hNTrackerHits_vs_Pt_, hNTrackerHits_vs_Eta_;
  MEP hNMuonHits_vs_Pt_, hNMuonHits_vs_Eta_;

//pulls
  MEP hPullPt_, hPullEta_, hPullPhi_, hPullQPt_, hPullDxy_, hPullDz_;
  MEP hPullPt_vs_Eta_, hPullPt_vs_Pt_, hPullEta_vs_Eta_, hPullPhi_vs_Eta_, hPullEta_vs_Pt_;

//chi2, ndof
  MEP hNDof_, hChi2_, hChi2Norm_, hChi2Prob_;
  MEP hNDof_vs_Eta_, hChi2_vs_Eta_, hChi2Norm_vs_Eta_, hChi2Prob_vs_Eta_;

  bool doAbsEta_;

//
//books histograms
//
  void bookHistograms(DQMStore* dqm, const string& dirName, const HistoDimensions& hDim)
  {
    dqm->cd();
    dqm->setCurrentFolder(dirName.c_str());

    doAbsEta_ = hDim.doAbsEta;

    //histograms for efficiency plots
    hP_   = dqm->book1D("P"  , "p of recoTracks"    , hDim.nBinP  , hDim.minP  , hDim.maxP  );
    hPt_  = dqm->book1D("Pt" , "p_{T} of recoTracks", hDim.nBinPt , hDim.minPt , hDim.maxPt );
    hEta_ = dqm->book1D("Eta", "#eta of recoTracks" , hDim.nBinEta, hDim.minEta, hDim.maxEta);
    hPhi_ = dqm->book1D("Phi", "#phi of recoTracks" , hDim.nBinPhi, hDim.minPhi, hDim.maxPhi);

    hSimP_   = dqm->book1D("SimP"  , "p of simTracks"    , hDim.nBinP  , hDim.minP  , hDim.maxP  );
    hSimPt_  = dqm->book1D("SimPt" , "p_{T} of simTracks", hDim.nBinPt , hDim.minPt , hDim.maxPt );
    hSimEta_ = dqm->book1D("SimEta", "#eta of simTracks" , hDim.nBinEta, hDim.minEta, hDim.maxEta);
    hSimPhi_ = dqm->book1D("SimPhi", "#phi of simTracks" , hDim.nBinPhi, hDim.minPhi, hDim.maxPhi);
    hSimDxy_ = dqm->book1D("SimDxy", "Dxy of simTracks" , hDim.nBinDxy, hDim.minDxy, hDim.maxDxy);
    hSimDz_ = dqm->book1D("Dz", "Dz of simTracks" , hDim.nBinDz, hDim.minDz, hDim.maxDz);

    //track multiplicities
    hNSim_  = dqm->book1D("NSim" , "Number of particles per event", hDim.nTrks+1, -0.5, hDim.nTrks+0.5);
    hNMuon_ = dqm->book1D("NMuon", "Number of muons per event"    , hDim.nTrks+1, -0.5, hDim.nTrks+0.5);

    // - Misc. variables
    hNTrks_ = dqm->book1D("NTrks", "Number of reco tracks per event", hDim.nTrks+1, -0.5, hDim.nTrks+0.5);
    hNTrksEta_ = dqm->book1D("NTrksEta", "Number of reco tracks vs #eta", hDim.nBinEta, hDim.minEta, hDim.maxEta);
    hNTrksPt_ = dqm->book1D("NTrksPt", "Number of reco tracks vs p_{T}", hDim.nBinPt, hDim.minPt, hDim.maxPt);

    hMisQPt_  = dqm->book1D("MisQPt" , "Charge mis-id vs Pt" , hDim.nBinPt , hDim.minPt , hDim.maxPt );
    hMisQEta_ = dqm->book1D("MisQEta", "Charge mis-id vs Eta", hDim.nBinEta, hDim.minEta, hDim.maxEta);

    // - Resolutions
    hErrP_   = dqm->book1D("ErrP"  , "#Delta(p)/p"        , hDim.nBinErr, hDim.minErrP  , hDim.maxErrP  );
    hErrPBarrel_   = dqm->book1D("ErrP_barrel"  , "#Delta(p)/p"        , hDim.nBinErr, hDim.minErrP  , hDim.maxErrP  );
    hErrPOverlap_   = dqm->book1D("ErrP_overlap"  , "#Delta(p)/p"        , hDim.nBinErr, hDim.minErrP  , hDim.maxErrP  );
    hErrPEndcap_   = dqm->book1D("ErrP_endcap"  , "#Delta(p)/p"        , hDim.nBinErr, hDim.minErrP  , hDim.maxErrP  );
    hErrPt_  = dqm->book1D("ErrPt" , "#Delta(p_{T})/p_{T}", hDim.nBinErr, hDim.minErrPt , hDim.maxErrPt );
    hErrPtBarrel_  = dqm->book1D("ErrPt_barrel" , "#Delta(p_{T})/p_{T}", hDim.nBinErr, hDim.minErrPt , hDim.maxErrPt );
    hErrPtOverlap_  = dqm->book1D("ErrPt_overlap" , "#Delta(p_{T})/p_{T}", hDim.nBinErr, hDim.minErrPt , hDim.maxErrPt );
    hErrPtEndcap_  = dqm->book1D("ErrPt_endcap" , "#Delta(p_{T})/p_{T}", hDim.nBinErr, hDim.minErrPt , hDim.maxErrPt );
    hErrEta_ = dqm->book1D("ErrEta", "#sigma(#eta))"      , hDim.nBinErr, hDim.minErrEta, hDim.maxErrEta);
    hErrPhi_ = dqm->book1D("ErrPhi", "#sigma(#phi)"       , hDim.nBinErr, hDim.minErrPhi, hDim.maxErrPhi);
    hErrDxy_ = dqm->book1D("ErrDxy", "#sigma(d_{xy})"     , hDim.nBinErr, hDim.minErrDxy, hDim.maxErrDxy);
    hErrDz_  = dqm->book1D("ErrDz" , "#sigma(d_{z})"      , hDim.nBinErr, hDim.minErrDz , hDim.maxErrDz );

    //PF-RECO comparisons
    hErrPt_PF_  = dqm->book1D("ErrPt_PF" , "#Delta(p_{T})|_{PF}/p_{T}", hDim.nBinErr, hDim.minErrPt, hDim.maxErrPt );
    hErrQPt_PF_  = dqm->book1D("ErrQPt_PF" , "#Delta(q/p_{T})|_{PF}/(q/p_{T})", hDim.nBinErr, hDim.minErrQPt, hDim.maxErrQPt);

    hPFMomPicked  = dqm->book1D("hPFMomPicked", "Momentum picked by PF",4,0.5,4.5);
    hPFDirectionPicked  = dqm->book1D("hPFDirectionPicked", "Direction picked by PF",4,0.5,4.5);
    hPFMomAssCorrectness  = dqm->book1D("hPFMomAssCorrectness", "Corrected momentum assignement PF/RECO",2,0.5,2.5);

    hdPt_vs_Pt_  = dqm->book2D("dPt_vs_Pt", "#Delta(p_{T}) vs p_{T}", hDim.nBinPt, 0., 500., 100, 0., 5.);
    hdPt_vs_Eta_  = dqm->book2D("dPt_vs_Eta", "#Delta(p_{T}) vs #eta", hDim.nBinEta, hDim.minEta, hDim.maxEta, 100, 0., 5.);
    
    hPt_vs_PFMomPicked  = dqm->book2D("hPt_vs_PFMomPicked", "Momentum picked by PF vs recoPt", hDim.nBinPt,0.,500.,4,0.5,4.5);
    hPt_vs_PFDirectionPicked  = dqm->book2D("hPt_vs_PFDirectionPicked", "Direction picked by PF vs recoPt",100,0.,500.,4,0.5,4.5);
    hPt_vs_PFMomAssCorrectness  = dqm->book2D("hPt_vs_PFMomAssCorrectness", "Corrected momentum assignement PF/RECO", hDim.nBinPt,0.,500.,2,0.5,2.5);

    // -- Resolutions vs Eta
    hErrP_vs_Eta_   = dqm->book2D("ErrP_vs_Eta", "#Delta(p)/p vs #eta",
                                  hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, hDim.minErrP, hDim.maxErrP);
    hErrPt_vs_Eta_  = dqm->book2D("ErrPt_vs_Eta", "#Delta(p_{T})/p_{T} vs #eta",
                                  hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, hDim.minErrPt, hDim.maxErrPt);
    hErrQPt_vs_Eta_ = dqm->book2D("ErrQPt_vs_Eta", "#Delta(q/p_{T})/(q/p_{T}) vs #eta",
                                  hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, hDim.minErrQPt, hDim.maxErrQPt);
    hErrEta_vs_Eta_ = dqm->book2D("ErrEta_vs_Eta", "#sigma(#eta) vs #eta",
                                  hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, hDim.minErrEta, hDim.maxErrEta);

    // -- Resolutions vs momentum
    hErrP_vs_P_    = dqm->book2D("ErrP_vs_P", "#Delta(p)/p vs p",
                                 hDim.nBinP, hDim.minP, hDim.maxP, hDim.nBinErr, hDim.minErrP, hDim.maxErrP);
    hErrPt_vs_Pt_  = dqm->book2D("ErrPt_vs_Pt", "#Delta(p_{T})/p_{T} vs p_{T}",
                                 hDim.nBinPt, hDim.minPt, hDim.maxPt, hDim.nBinErr, hDim.minErrPt, hDim.maxErrPt);
    hErrQPt_vs_Pt_ = dqm->book2D("ErrQPt_vs_Pt", "#Delta(q/p_{T})/(q/p_{T}) vs p_{T}",
                                 hDim.nBinPt, hDim.minPt, hDim.maxPt, hDim.nBinErr, hDim.minErrQPt, hDim.maxErrQPt);

    // - Pulls
    hPullPt_  = dqm->book1D("PullPt" , "Pull(#p_{T})" , hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullEta_ = dqm->book1D("PullEta", "Pull(#eta)"   , hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullPhi_ = dqm->book1D("PullPhi", "Pull(#phi)"   , hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullQPt_ = dqm->book1D("PullQPt", "Pull(q/p_{T})", hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullDxy_ = dqm->book1D("PullDxy", "Pull(D_{xy})" , hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullDz_  = dqm->book1D("PullDz" , "Pull(D_{z})"  , hDim.nBinPull, -hDim.wPull, hDim.wPull);

    // -- Pulls vs Eta
    hPullPt_vs_Eta_  = dqm->book2D("PullPt_vs_Eta", "Pull(p_{T}) vs #eta",
                                   hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullEta_vs_Eta_ = dqm->book2D("PullEta_vs_Eta", "Pull(#eta) vs #eta",
                                   hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullPhi_vs_Eta_ = dqm->book2D("PullPhi_vs_Eta", "Pull(#phi) vs #eta",
                                   hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinPull, -hDim.wPull, hDim.wPull);

    // -- Pulls vs Pt
    hPullPt_vs_Pt_ = dqm->book2D("PullPt_vs_Pt", "Pull(p_{T}) vs p_{T}",
                                 hDim.nBinPt, hDim.minPt, hDim.maxPt, hDim.nBinPull, -hDim.wPull, hDim.wPull);
    hPullEta_vs_Pt_ = dqm->book2D("PullEta_vs_Pt", "Pull(#eta) vs p_{T}",
                                  hDim.nBinPt, hDim.minPt, hDim.maxPt, hDim.nBinPull, -hDim.wPull, hDim.wPull);

    // -- Number of Hits
    const int nHits = 100;
    hNHits_ = dqm->book1D("NHits", "Number of hits", nHits+1, -0.5, nHits+0.5);
    hNHits_vs_Pt_  = dqm->book2D("NHits_vs_Pt", "Number of hits vs p_{T}",
                                 hDim.nBinPt, hDim.minPt, hDim.maxPt, nHits/4+1, -0.25, nHits+0.25);
    hNHits_vs_Eta_ = dqm->book2D("NHits_vs_Eta", "Number of hits vs #eta",
                                 hDim.nBinEta, hDim.minEta, hDim.maxEta, nHits/4+1, -0.25, nHits+0.25);
    hNSimHits_ = dqm->book1D("NSimHits", "Number of simHits", nHits+1, -0.5, nHits+0.5);

    const int nLostHits = 5;
    hNLostHits_ = dqm->book1D("NLostHits", "Number of Lost hits", nLostHits+1, -0.5, nLostHits+0.5);
    hNLostHits_vs_Pt_  = dqm->book2D("NLostHits_vs_Pt", "Number of lost Hits vs p_{T}",
                                     hDim.nBinPt, hDim.minPt, hDim.maxPt, nLostHits+1, -0.5, nLostHits+0.5);
    hNLostHits_vs_Eta_ = dqm->book2D("NLostHits_vs_Eta", "Number of lost Hits vs #eta",
                                     hDim.nBinEta, hDim.minEta, hDim.maxEta, nLostHits+1, -0.5, nLostHits+0.5);

    const int nTrackerHits = 40;
    hNTrackerHits_ = dqm->book1D("NTrackerHits", "Number of valid tracker hits", nTrackerHits+1, -0.5, nTrackerHits+0.5);
    hNTrackerHits_vs_Pt_ = dqm->book2D("NTrackerHits_vs_Pt", "Number of valid traker hits vs p_{T}",
                                       hDim.nBinPt, hDim.minPt, hDim.maxPt, nTrackerHits/4+1, -0.25, nTrackerHits+0.25);
    hNTrackerHits_vs_Eta_ = dqm->book2D("NTrackerHits_vs_Eta", "Number of valid tracker hits vs #eta",
                                        hDim.nBinEta, hDim.minEta, hDim.maxEta, nTrackerHits/4+1, -0.25, nTrackerHits+0.25);

    const int nMuonHits = 60;
    hNMuonHits_ = dqm->book1D("NMuonHits", "Number of valid muon hits", nMuonHits+1, -0.5, nMuonHits+0.5);
    hNMuonHits_vs_Pt_  = dqm->book2D("NMuonHits_vs_Pt", "Number of valid muon hits vs p_{T}",
                                     hDim.nBinPt, hDim.minPt, hDim.maxPt, nMuonHits/4+1, -0.25, nMuonHits+0.25);
    hNMuonHits_vs_Eta_ = dqm->book2D("NMuonHits_vs_Eta", "Number of valid muon hits vs #eta",
                                     hDim.nBinEta, hDim.minEta, hDim.maxEta, nMuonHits/4+1, -0.25, nMuonHits+0.25);

    hNDof_ = dqm->book1D("NDof", "Number of DoF", hDim.nDof+1, -0.5, hDim.nDof+0.5);
    hChi2_ = dqm->book1D("Chi2", "#Chi^{2}", hDim.nBinErr, 0., 200.);
    hChi2Norm_ = dqm->book1D("Chi2Norm", "Normalized #Chi^{2}", hDim.nBinErr, 0., 50.);
    hChi2Prob_ = dqm->book1D("Chi2Prob", "Prob(#Chi^{2})", hDim.nBinErr, 0., 1.);

    hNDof_vs_Eta_ = dqm->book2D("NDof_vs_Eta", "Number of DoF vs #eta",
                                hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nDof+1, -0.5, hDim.nDof+0.5);
    hChi2_vs_Eta_ = dqm->book2D("Chi2_vs_Eta", "#Chi^{2} vs #eta",
                                hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, 0., 200.);
    hChi2Norm_vs_Eta_ = dqm->book2D("Chi2Norm_vs_Eta", "Normalized #Chi^{2} vs #eta",
                                    hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, 0., 50.);
    hChi2Prob_vs_Eta_ = dqm->book2D("Chi2Prob_vs_Eta", "Prob(#Chi^{2}) vs #eta",
                                    hDim.nBinEta, hDim.minEta, hDim.maxEta, hDim.nBinErr, 0., 1.);

    hNSimToReco_ = dqm->book1D("NSimToReco", "Number of associated reco tracks", hDim.nAssoc+1, -0.5, hDim.nAssoc+0.5);
    hNRecoToSim_ = dqm->book1D("NRecoToSim", "Number of associated sim TP's", hDim.nAssoc+1, -0.5, hDim.nAssoc+0.5);

  };

//
//Fill hists booked, simRef and muonRef are associated by hits
//
  void fill(const TrackingParticle* simRef, const Muon* muonRef)
  {

    const double simP   = simRef->p();
    const double simPt  = simRef->pt();
    const double simEta = doAbsEta_ ? fabs(simRef->eta()) : simRef->eta();
    const double simPhi = simRef->phi();
    const double simQ   = simRef->charge();
    const double simQPt = simQ/simPt;

    GlobalPoint  simVtx(simRef->vertex().x(), simRef->vertex().y(), simRef->vertex().z());
    GlobalVector simMom(simRef->momentum().x(), simRef->momentum().y(), simRef->momentum().z());
    const double simDxy = -simVtx.x()*sin(simPhi)+simVtx.y()*cos(simPhi);
    const double simDz  = simVtx.z() - (simVtx.x()*simMom.x()+simVtx.y()*simMom.y())*simMom.z()/simMom.perp2();

//    const unsigned int nSimHits = simRef->pSimHit_end() - simRef->pSimHit_begin();

/*
    // Histograms for efficiency plots
    hSimP_  ->Fill(simP  );
    hSimPt_ ->Fill(simPt );
    hSimEta_->Fill(simEta);
    hSimPhi_->Fill(simPhi);
    hSimDxy_->Fill(simDxy);
    hSimDz_->Fill(simDz);
    hNSimHits_->Fill(nSimHits);
*/

    const double recoQ   = muonRef->charge();
    if ( simQ*recoQ < 0 ) {
      hMisQPt_ ->Fill(simPt );
      hMisQEta_->Fill(simEta);
    }

    //    const double recoP   = muonRef->p(); 
    const double recoPt  = muonRef->pt();
    const double recoEta = muonRef->eta();
    //    const double recoPhi = muonRef->phi();
    const double recoQPt = recoQ/recoPt;

    const double recoPFP = muonRef->pfP4().P();
    const double recoPFPt = muonRef->pfP4().Pt();
    const double recoPFEta = muonRef->pfP4().Eta(); 
    const double recoPFPhi = muonRef->pfP4().Phi();
    const double recoQPFPt = recoQ/recoPFPt;
    
    //matching parameters
    double MatchPFRECOMomMagn = 0.00001;
    double MatchPFRECOMomDir = 0.000000000000001;

    if (muonRef->isPFMuon()) { //in principle it will be use for PF muons only...

      hErrPt_PF_->Fill((recoPt-recoPFPt)/recoPt);
      hErrQPt_PF_->Fill((recoQPt-recoQPFPt)/recoQPt);
      hdPt_vs_Eta_->Fill(recoEta,fabs(recoPt-recoPFPt));
      hdPt_vs_Pt_->Fill(recoPt,fabs(recoPt-recoPFPt));

      if (fabs(recoPFPt - recoPt) > MatchPFRECOMomMagn) {

	// global
	if (muonRef->isGlobalMuon()) {
	  //split into categories by direction
	  //has direction of global track
	  if (fabs((muonRef->pfP4().Px()*muonRef->globalTrack()->px()+muonRef->pfP4().Py()*muonRef->globalTrack()->py()+muonRef->pfP4().Pz()*muonRef->globalTrack()->pz())/muonRef->globalTrack()->p()/recoPFP - 1.) < MatchPFRECOMomDir) {
	    //has momentum of global track
	    if (fabs(recoPFPt - muonRef->globalTrack()->pt()) < MatchPFRECOMomMagn) {
	      hPFMomPicked->Fill(1.);
	      hPt_vs_PFMomPicked->Fill(recoPt,1.);
	      //correctness
	      int theCorrectPFAss = (fabs(recoPFPt-simPt) < fabs(recoPt - simPt))? 1 : 2;
	      hPFMomAssCorrectness->Fill(theCorrectPFAss);
	      hPt_vs_PFMomAssCorrectness->Fill(recoPt,theCorrectPFAss);
	    } else {
	      //just the direction
	      hPFDirectionPicked->Fill(1.);
	      hPFMomPicked->Fill(4.);
	      hPt_vs_PFMomPicked->Fill(recoPt,4.);
	    }
	  }
	  //has direction of inner track
	  //must be also tracker muon
	  if (muonRef->isTrackerMuon()) {
	    if (fabs((muonRef->pfP4().x()*muonRef->innerTrack()->px()+muonRef->pfP4().y()*muonRef->innerTrack()->py()+muonRef->pfP4().z()*muonRef->innerTrack()->pz())/muonRef->innerTrack()->p()/recoPFP - 1.) < MatchPFRECOMomDir) {
	      //has momentum of inner track
	      if (fabs(recoPFPt - muonRef->innerTrack()->pt()) < MatchPFRECOMomMagn) {
		hPFMomPicked->Fill(2.);
		hPt_vs_PFMomPicked->Fill(recoPt,2.);
		//correctness
		int theCorrectPFAss = (fabs(recoPFPt-simPt) < fabs(recoPt - simPt))? 1 : 2;
		hPFMomAssCorrectness->Fill(theCorrectPFAss);
		hPt_vs_PFMomAssCorrectness->Fill(recoPt,theCorrectPFAss);
	      } else {
		//just the direction
		hPFDirectionPicked->Fill(2.);
		hPFMomPicked->Fill(4.);
		hPt_vs_PFMomPicked->Fill(recoPt,4.);
	      }
	    }//has direction of inner track
	  } //has direction outer track
	}//is global muon
	 //is tracker not global muon
	else if (muonRef->isTrackerMuon()) {
	  if (fabs((muonRef->pfP4().Px()*muonRef->innerTrack()->px()+muonRef->pfP4().Py()*muonRef->innerTrack()->py()+muonRef->pfP4().Pz()*muonRef->innerTrack()->pz())/muonRef->innerTrack()->p()/recoPFP- 1.) < MatchPFRECOMomDir) {
	    //has momentum of inner track
	    if (fabs(recoPFPt - muonRef->innerTrack()->pt()) < MatchPFRECOMomMagn) {
	      hPFMomPicked->Fill(2.);
	      hPt_vs_PFMomPicked->Fill(recoPt,2.);
	      //correctness
	      int theCorrectPFAss = (fabs(recoPFPt-simPt) < fabs(recoPt - simPt))? 1 : 2;
	      hPFMomAssCorrectness->Fill(theCorrectPFAss);
	      hPt_vs_PFMomAssCorrectness->Fill(recoPt,theCorrectPFAss);
	    } else {
	      //just the direction
	      hPFDirectionPicked->Fill(2.);
	      hPFMomPicked->Fill(4.);
	      hPt_vs_PFMomPicked->Fill(recoPt,4.);
	    }
	  }//has direction of inner track
	}
	//is also a standalone 
	if (muonRef->isStandAloneMuon()) {
	  //has direction of outer track
	  if (fabs((muonRef->pfP4().Px()*muonRef->outerTrack()->px()+muonRef->pfP4().Py()*muonRef->outerTrack()->py()+muonRef->pfP4().Pz()*muonRef->outerTrack()->pz())/muonRef->outerTrack()->p()/recoPFP - 1.) < MatchPFRECOMomDir) {
	    //has momentum of inner track
	    if (fabs(recoPFPt - muonRef->outerTrack()->pt()) < MatchPFRECOMomMagn) {
	      hPFMomPicked->Fill(3.);
	      hPt_vs_PFMomPicked->Fill(recoPt,3.);
	      //correctness
	      int theCorrectPFAss = (fabs(recoPFPt-simPt) < fabs(recoPt - simPt))? 1 : 2;
	      hPFMomAssCorrectness->Fill(theCorrectPFAss);
	      hPt_vs_PFMomAssCorrectness->Fill(recoPt,theCorrectPFAss);
	    } else {
	      //just the direction
	      hPFDirectionPicked->Fill(3.);
	      hPFMomPicked->Fill(4.);
	      hPt_vs_PFMomPicked->Fill(recoPt,4.);
	    }
	  }//has direction of outer track
	}
      }//end is tracker
      else if (muonRef->isStandAloneMuon()) {
	//has direction of outer track
	if (fabs((muonRef->pfP4().Px()*muonRef->outerTrack()->px()+muonRef->pfP4().Py()*muonRef->outerTrack()->py()+muonRef->pfP4().Pz()*muonRef->outerTrack()->pz())/muonRef->outerTrack()->p()/recoPFP - 1.) < MatchPFRECOMomDir) {
	  //has momentum of inner track
	  if (fabs(recoPFPt - muonRef->outerTrack()->pt()) < MatchPFRECOMomMagn) {
	    hPFMomPicked->Fill(3.);
	    hPt_vs_PFMomPicked->Fill(recoPt,3.);
	    //correctness
	    int theCorrectPFAss = (fabs(recoPFPt-simPt) < fabs(recoPt - simPt))? 1 : 2;
	    hPFMomAssCorrectness->Fill(theCorrectPFAss);
	    hPt_vs_PFMomAssCorrectness->Fill(recoPt,theCorrectPFAss);
	  } else {
	    //just the direction
	    hPFDirectionPicked->Fill(3.);
	    hPFMomPicked->Fill(4.);
	    hPt_vs_PFMomPicked->Fill(recoPt,4.);
	  }
	}//has direction of outer track
      } //end standalone
    } //end different momentum assignment 
    
    
    //pulls
    const double errP   = (recoPFP-simP)/simP;
    const double errPt  = (recoPFPt-simPt)/simPt;
    const double errEta = (recoPFEta-simEta)/simEta;
    const double errPhi = (recoPFPhi-simPhi)/simPhi;
    const double errQPt = (recoQPFPt-simQPt)/simQPt;

    hP_  ->Fill(simP);
    hPt_ ->Fill(simPt );
    hEta_->Fill(simEta);   
    hPhi_->Fill(simPhi);

    hErrP_  ->Fill(errP  );
    hErrPt_ ->Fill(errPt );
    hErrEta_->Fill(errEta);
    hErrPhi_->Fill(errPhi);

    if(fabs(simEta) > 0. && fabs(simEta) < 0.8) {
      hErrPBarrel_->Fill(errP);
      hErrPtBarrel_->Fill(errPt);
    } else if (fabs(simEta) > 0.8 && fabs(simEta) < 1.2) {
      hErrPOverlap_->Fill(errP);
      hErrPtOverlap_->Fill(errPt);
    } else if (fabs(simEta) > 1.2 ){
      hErrPEndcap_->Fill(errP);
      hErrPtEndcap_->Fill(errPt);
    }

    hErrP_vs_Eta_  ->Fill(simEta, errP  );
    hErrPt_vs_Eta_ ->Fill(simEta, errPt );
    hErrQPt_vs_Eta_->Fill(simEta, errQPt);

    hErrP_vs_P_   ->Fill(simP  , errP  );
    hErrPt_vs_Pt_ ->Fill(simPt , errPt );
    hErrQPt_vs_Pt_->Fill(simPt , errQPt);

    hErrEta_vs_Eta_->Fill(simEta, errEta);

    //access from track (same for PF and non PF)
    reco::TrackRef recoRef = muonRef->track();
    if (recoRef.isNonnull()) {

    // Number of reco-hits
    const int nRecoHits = recoRef->numberOfValidHits();
    const int nLostHits = recoRef->numberOfLostHits();

    hNHits_->Fill(nRecoHits);
    hNHits_vs_Pt_ ->Fill(simPt , nRecoHits);
    hNHits_vs_Eta_->Fill(simEta, nRecoHits);

    hNLostHits_->Fill(nLostHits);
    hNLostHits_vs_Pt_ ->Fill(simPt , nLostHits);
    hNLostHits_vs_Eta_->Fill(simEta, nLostHits);

    const double recoNDof = recoRef->ndof();
    const double recoChi2 = recoRef->chi2();
    const double recoChi2Norm = recoRef->normalizedChi2();
    const double recoChi2Prob = TMath::Prob(recoRef->chi2(), static_cast<int>(recoRef->ndof()));

    hNDof_->Fill(recoNDof);
    hChi2_->Fill(recoChi2);
    hChi2Norm_->Fill(recoChi2Norm);
    hChi2Prob_->Fill(recoChi2Prob);

    hNDof_vs_Eta_->Fill(simEta, recoNDof);
    hChi2_vs_Eta_->Fill(simEta, recoChi2);
    hChi2Norm_vs_Eta_->Fill(simEta, recoChi2Norm);
    hChi2Prob_vs_Eta_->Fill(simEta, recoChi2Prob);

    const double recoDxy = recoRef->dxy();
    const double recoDz  = recoRef->dz();

    const double errDxy = (recoDxy-simDxy)/simDxy;
    const double errDz  = (recoDz-simDz)/simDz;
    hErrDxy_->Fill(errDxy);
    hErrDz_ ->Fill(errDz );

    const double pullPt  = (recoPFPt-simPt)/recoRef->ptError();
    const double pullQPt = (recoQPFPt-simQPt)/recoRef->qoverpError();
    const double pullEta = (recoPFEta-simEta)/recoRef->etaError();
    const double pullPhi = (recoPFPhi-simPhi)/recoRef->phiError();
    const double pullDxy = (recoDxy-simDxy)/recoRef->dxyError();
    const double pullDz  = (recoDz-simDz)/recoRef->dzError();

    hPullPt_ ->Fill(pullPt );
    hPullEta_->Fill(pullEta);
    hPullPhi_->Fill(pullPhi);
    hPullQPt_->Fill(pullQPt);
    hPullDxy_->Fill(pullDxy);
    hPullDz_ ->Fill(pullDz );

    hPullPt_vs_Eta_->Fill(simEta, pullPt);
    hPullPt_vs_Pt_ ->Fill(simPt, pullPt);

    hPullEta_vs_Eta_->Fill(simEta, pullEta);
    hPullPhi_vs_Eta_->Fill(simEta, pullPhi);

    hPullEta_vs_Pt_->Fill(simPt, pullEta);
    }
  };
};

//
//struct defininiong histograms
//
struct RecoMuonValidatorPF::CommonME {
  typedef MonitorElement* MEP;

//diffs
  MEP hTrkToGlbDiffNTrackerHits_, hStaToGlbDiffNMuonHits_;
  MEP hTrkToGlbDiffNTrackerHitsEta_, hStaToGlbDiffNMuonHitsEta_;
  MEP hTrkToGlbDiffNTrackerHitsPt_, hStaToGlbDiffNMuonHitsPt_;

//global muon hit pattern
  MEP hNInvalidHitsGTHitPattern_, hNInvalidHitsITHitPattern_, hNInvalidHitsOTHitPattern_;
  MEP hNDeltaInvalidHitsHitPattern_;

//muon based momentum assignment
  MEP hMuonP_, hMuonPt_, hMuonEta_, hMuonPhi_;
//track based kinematics
  MEP hMuonTrackP_, hMuonTrackPt_, hMuonTrackEta_, hMuonTrackPhi_, hMuonTrackDxy_, hMuonTrackDz_;
//histograms for fractions
  MEP hMuonAllP_, hMuonAllPt_, hMuonAllEta_, hMuonAllPhi_;
};

//
//Constructor
//
RecoMuonValidatorPF::RecoMuonValidatorPF(const ParameterSet& pset):
  selector_(pset.getParameter<std::string>("selection"))
{
  verbose_ = pset.getUntrackedParameter<unsigned int>("verbose", 0);
 
  outputFileName_ = pset.getUntrackedParameter<string>("outputFileName", "");

  // Set histogram dimensions from config
  HistoDimensions hDim;

  hDim.nBinP = pset.getUntrackedParameter<unsigned int>("nBinP");
  hDim.minP = pset.getUntrackedParameter<double>("minP");
  hDim.maxP = pset.getUntrackedParameter<double>("maxP");

  hDim.nBinPt = pset.getUntrackedParameter<unsigned int>("nBinPt");
  hDim.minPt = pset.getUntrackedParameter<double>("minPt");
  hDim.maxPt = pset.getUntrackedParameter<double>("maxPt");

  doAbsEta_ = pset.getUntrackedParameter<bool>("doAbsEta");
  hDim.doAbsEta = doAbsEta_;
  hDim.nBinEta  = pset.getUntrackedParameter<unsigned int>("nBinEta");
  hDim.minEta = pset.getUntrackedParameter<double>("minEta");
  hDim.maxEta = pset.getUntrackedParameter<double>("maxEta");

  hDim.nBinDxy  = pset.getUntrackedParameter<unsigned int>("nBinDxy");
  hDim.minDxy = pset.getUntrackedParameter<double>("minDxy");
  hDim.maxDxy = pset.getUntrackedParameter<double>("maxDxy");

  hDim.nBinDz  = pset.getUntrackedParameter<unsigned int>("nBinDz");
  hDim.minDz = pset.getUntrackedParameter<double>("minDz");
  hDim.maxDz = pset.getUntrackedParameter<double>("maxDz");

  hDim.nBinPhi  = pset.getUntrackedParameter<unsigned int>("nBinPhi");
  hDim.minPhi = pset.getUntrackedParameter<double>("minPhi", -TMath::Pi());
  hDim.maxPhi = pset.getUntrackedParameter<double>("maxPhi",  TMath::Pi());

  hDim.nBinErr  = pset.getUntrackedParameter<unsigned int>("nBinErr");
  hDim.nBinPull = pset.getUntrackedParameter<unsigned int>("nBinPull");

  hDim.wPull = pset.getUntrackedParameter<double>("wPull");

  hDim.minErrP = pset.getUntrackedParameter<double>("minErrP");
  hDim.maxErrP = pset.getUntrackedParameter<double>("maxErrP");

  hDim.minErrPt = pset.getUntrackedParameter<double>("minErrPt");
  hDim.maxErrPt = pset.getUntrackedParameter<double>("maxErrPt");

  hDim.minErrQPt = pset.getUntrackedParameter<double>("minErrQPt");
  hDim.maxErrQPt = pset.getUntrackedParameter<double>("maxErrQPt");

  hDim.minErrEta = pset.getUntrackedParameter<double>("minErrEta");
  hDim.maxErrEta = pset.getUntrackedParameter<double>("maxErrEta");

  hDim.minErrPhi = pset.getUntrackedParameter<double>("minErrPhi");
  hDim.maxErrPhi = pset.getUntrackedParameter<double>("maxErrPhi");

  hDim.minErrDxy = pset.getUntrackedParameter<double>("minErrDxy");
  hDim.maxErrDxy = pset.getUntrackedParameter<double>("maxErrDxy");

  hDim.minErrDz  = pset.getUntrackedParameter<double>("minErrDz" );
  hDim.maxErrDz  = pset.getUntrackedParameter<double>("maxErrDz" );

  hDim.nTrks = pset.getUntrackedParameter<unsigned int>("nTrks");
  hDim.nAssoc = pset.getUntrackedParameter<unsigned int>("nAssoc");
  hDim.nDof = pset.getUntrackedParameter<unsigned int>("nDof", 55);

  // Labels for simulation and reconstruction tracks
  simLabel_  = pset.getParameter<InputTag>("simLabel" );
  muonLabel_ = pset.getParameter<InputTag>("muonLabel");

  // Labels for sim-reco association
  doAssoc_ = pset.getUntrackedParameter<bool>("doAssoc", true);
  muAssocLabel_ = pset.getParameter<InputTag>("muAssocLabel");

  //type of track
  std::string trackType = pset.getParameter< std::string >("trackType");
  if (trackType == "inner") trackType_ = MuonAssociatorByHits::InnerTk;
  else if (trackType == "outer") trackType_ = MuonAssociatorByHits::OuterTk;
  else if (trackType == "global") trackType_ = MuonAssociatorByHits::GlobalTk;
  else if (trackType == "segments") trackType_ = MuonAssociatorByHits::Segments;
  else throw cms::Exception("Configuration") << "Track type '" << trackType << "' not supported.\n";

//  seedPropagatorName_ = pset.getParameter<string>("SeedPropagator");

  ParameterSet tpset = pset.getParameter<ParameterSet>("tpSelector");
  tpSelector_ = TrackingParticleSelector(tpset.getParameter<double>("ptMin"),
                                         tpset.getParameter<double>("minRapidity"),
                                         tpset.getParameter<double>("maxRapidity"),
                                         tpset.getParameter<double>("tip"),
                                         tpset.getParameter<double>("lip"),
                                         tpset.getParameter<int>("minHit"),
                                         tpset.getParameter<bool>("signalOnly"),
                                         tpset.getParameter<bool>("chargedOnly"),
                                         tpset.getParameter<bool>("stableOnly"),
                                         tpset.getParameter<std::vector<int> >("pdgId"));

  // the service parameters
  ParameterSet serviceParameters 
    = pset.getParameter<ParameterSet>("ServiceParameters");
  theMuonService = new MuonServiceProxy(serviceParameters);

  // retrieve the instance of DQMService
  theDQM = 0;
  theDQM = Service<DQMStore>().operator->();

  if ( ! theDQM ) {
    LogError("RecoMuonValidatorPF") << "DQMService not initialized\n";
    return;
  }

  subDir_ = pset.getUntrackedParameter<string>("subDir");
  if ( subDir_.empty() ) subDir_ = "RecoMuonV";
  if ( subDir_[subDir_.size()-1] == '/' ) subDir_.erase(subDir_.size()-1);

  // book histograms
  theDQM->cd();

  theDQM->setCurrentFolder(subDir_);

  commonME_ = new CommonME;
  muonME_  = new MuonME;

  //commonME
  const int nHits = 100;

  // - diffs
  commonME_->hTrkToGlbDiffNTrackerHits_ = theDQM->book1D("TrkGlbDiffNTrackerHits", "Difference of number of tracker hits (tkMuon - globalMuon)", 2*nHits+1, -nHits-0.5, nHits+0.5);
  commonME_->hStaToGlbDiffNMuonHits_ = theDQM->book1D("StaGlbDiffNMuonHits", "Difference of number of muon hits (staMuon - globalMuon)", 2*nHits+1, -nHits-0.5, nHits+0.5);

  commonME_->hTrkToGlbDiffNTrackerHitsEta_ = theDQM->book2D("TrkGlbDiffNTrackerHitsEta", "Difference of number of tracker hits (tkMuon - globalMuon)",   hDim.nBinEta, hDim.minEta, hDim.maxEta, 2*nHits+1, -nHits-0.5, nHits+0.5);
  commonME_->hStaToGlbDiffNMuonHitsEta_ = theDQM->book2D("StaGlbDiffNMuonHitsEta", "Difference of number of muon hits (staMuon - globalMuon)",   hDim.nBinEta, hDim.minEta, hDim.maxEta, 2*nHits+1, -nHits-0.5, nHits+0.5);

  commonME_->hTrkToGlbDiffNTrackerHitsPt_ = theDQM->book2D("TrkGlbDiffNTrackerHitsPt", "Difference of number of tracker hits (tkMuon - globalMuon)",  hDim.nBinPt, hDim.minPt, hDim.maxPt, 2*nHits+1, -nHits-0.5, nHits+0.5);
  commonME_->hStaToGlbDiffNMuonHitsPt_ = theDQM->book2D("StaGlbDiffNMuonHitsPt", "Difference of number of muon hits (staMuon - globalMuon)",  hDim.nBinPt, hDim.minPt, hDim.maxPt, 2*nHits+1, -nHits-0.5, nHits+0.5);

 // -global muon hit pattern
  commonME_->hNInvalidHitsGTHitPattern_ = theDQM->book1D("NInvalidHitsGTHitPattern", "Number of invalid hits on a global track", nHits+1, -0.5, nHits+0.5);
  commonME_->hNInvalidHitsITHitPattern_ = theDQM->book1D("NInvalidHitsITHitPattern", "Number of invalid hits on an inner track", nHits+1, -0.5, nHits+0.5);
  commonME_->hNInvalidHitsOTHitPattern_ = theDQM->book1D("NInvalidHitsOTHitPattern", "Number of invalid hits on an outer track", nHits+1, -0.5, nHits+0.5);
  commonME_->hNDeltaInvalidHitsHitPattern_ = theDQM->book1D("hNDeltaInvalidHitsHitPattern", "The discrepancy for Number of invalid hits on an global track and inner and outer tracks", 2.*nHits+1, -nHits-0.5, nHits+0.5);

   //muon based kinematics
  commonME_->hMuonP_   = theDQM->book1D("PMuon"  , "p of muon"    , hDim.nBinP  , hDim.minP  , hDim.maxP  );
  commonME_->hMuonPt_  = theDQM->book1D("PtMuon" , "p_{T} of muon", hDim.nBinPt , hDim.minPt , hDim.maxPt );
  commonME_->hMuonEta_ = theDQM->book1D("EtaMuon", "#eta of muon" , hDim.nBinEta, hDim.minEta, hDim.maxEta);
  commonME_->hMuonPhi_ = theDQM->book1D("PhiMuon", "#phi of muon" , hDim.nBinPhi, hDim.minPhi, hDim.maxPhi);
   //track based kinematics
  commonME_->hMuonTrackP_   = theDQM->book1D("PMuonTrack"  , "p of reco muon track"    , hDim.nBinP  , hDim.minP  , hDim.maxP  );
  commonME_->hMuonTrackPt_  = theDQM->book1D("PtMuonTrack" , "p_{T} of reco muon track", hDim.nBinPt , hDim.minPt , hDim.maxPt );
  commonME_->hMuonTrackEta_ = theDQM->book1D("EtaMuonTrack", "#eta of reco muon track" , hDim.nBinEta, hDim.minEta, hDim.maxEta);
  commonME_->hMuonTrackPhi_ = theDQM->book1D("PhiMuonTrack", "#phi of reco muon track" , hDim.nBinPhi, hDim.minPhi, hDim.maxPhi);
  commonME_->hMuonTrackDxy_ = theDQM->book1D("DxyMuonTrack", "Dxy of reco muon track" , hDim.nBinDxy, hDim.minDxy, hDim.maxDxy);
  commonME_->hMuonTrackDz_ = theDQM->book1D("DzMuonTrack", "Dz of reco muon track" , hDim.nBinDz, hDim.minDz, hDim.maxDz);

  //histograms for fractions
  commonME_->hMuonAllP_   = theDQM->book1D("PMuonAll"  , "p of muons of all types"    , hDim.nBinP  , hDim.minP  , hDim.maxP  );
  commonME_->hMuonAllPt_  = theDQM->book1D("PtMuonAll" , "p_{T} of muon of all types", hDim.nBinPt , hDim.minPt , hDim.maxPt );
  commonME_->hMuonAllEta_ = theDQM->book1D("EtaMuonAll", "#eta of muon of all types" , hDim.nBinEta, hDim.minEta, hDim.maxEta);
  commonME_->hMuonAllPhi_ = theDQM->book1D("PhiMuonAll", "#phi of muon of all types" , hDim.nBinPhi, hDim.minPhi, hDim.maxPhi);

  muonME_->bookHistograms(theDQM, subDir_, hDim);

  if ( verbose_ > 0 ) theDQM->showDirStructure();
}

//
//Destructor
//
RecoMuonValidatorPF::~RecoMuonValidatorPF()
{
  if ( theMuonService ) delete theMuonService;
}

//
//Begin run
//
void RecoMuonValidatorPF::beginRun(const edm::Run& , const EventSetup& eventSetup)
{
  if ( theMuonService ) theMuonService->update(eventSetup);

  if ( doAssoc_ ) {
    edm::ESHandle<TrackAssociatorBase> associatorBase;
    eventSetup.get<TrackAssociatorRecord>().get(muAssocLabel_.label(), associatorBase);
    assoByHits = dynamic_cast<const MuonAssociatorByHits *>(associatorBase.product());
    if (assoByHits == 0) throw cms::Exception("Configuration") << "The Track Associator with label '" << muAssocLabel_.label() << "' is not a MuonAssociatorByHits.\n";
    }

}

//
//End run
//
void RecoMuonValidatorPF::endRun()
{
  if ( theDQM && ! outputFileName_.empty() ) theDQM->save(outputFileName_);
}

//
//Analyze
//
void RecoMuonValidatorPF::analyze(const Event& event, const EventSetup& eventSetup)
{
  if ( ! theDQM ) {
    LogError("RecoMuonValidatorPF") << "DQMService not initialized\n";
    return;
  }

  // Get TrackingParticles
  Handle<TrackingParticleCollection> simHandle;
  event.getByLabel(simLabel_, simHandle);
  const TrackingParticleCollection simColl = *(simHandle.product());

  // Get Muons
  Handle<View<Muon> > muonHandle;
  event.getByLabel(muonLabel_, muonHandle);
  View<Muon> muonColl = *(muonHandle.product());

  const TrackingParticleCollection::size_type nSim = simColl.size();

  edm::RefToBaseVector<reco::Muon> Muons;
  Muons = muonHandle->refVector();

  edm::RefVector<TrackingParticleCollection> allTPs;
  for (size_t i = 0; i < nSim; ++i) {
      allTPs.push_back(TrackingParticleRef(simHandle,i));
  }

  muonME_->hNSim_->Fill(nSim);
  muonME_->hNMuon_->Fill(muonColl.size());

  MuonAssociatorByHits::MuonToSimCollection muonToSimColl;
  MuonAssociatorByHits::SimToMuonCollection simToMuonColl;

  if ( doAssoc_ ) {
  assoByHits->associateMuons(muonToSimColl, simToMuonColl, Muons, trackType_, allTPs, &event, &eventSetup);
  } else {
/*
    // SimToMuon associations
    Handle<reco::RecoToSimCollection> simToTrkMuHandle;
    event.getByLabel(trkMuAssocLabel_, simToTrkMuHandle);
    trkSimRecColl = *(simToTrkMuHandle.product());

    Handle<reco::RecoToSimCollection> simToStaMuHandle;
    event.getByLabel(staMuAssocLabel_, simToStaMuHandle);
    staSimRecColl = *(simToStaMuHandle.product());

    Handle<reco::RecoToSimCollection> simToGlbMuHandle;
    event.getByLabel(glbMuAssocLabel_, simToGlbMuHandle);
    glbSimRecColl = *(simToGlbMuHandle.product());

    // MuonToSim associations
    Handle<reco::SimToRecoCollection> trkMuToSimHandle;
    event.getByLabel(trkMuAssocLabel_, trkMuToSimHandle);
    trkRecSimColl = *(trkMuToSimHandle.product());

    Handle<reco::SimToRecoCollection> staMuToSimHandle;
    event.getByLabel(staMuAssocLabel_, staMuToSimHandle);
    staRecSimColl = *(staMuToSimHandle.product());

    Handle<reco::SimToRecoCollection> glbMuToSimHandle;
    event.getByLabel(glbMuAssocLabel_, glbMuToSimHandle);
    glbRecSimColl = *(glbMuToSimHandle.product());
*/
  }

    int glbNTrackerHits = 0; int trkNTrackerHits = 0; int staNTrackerHits = 0;
    int glbNMuonHits = 0; int trkNMuonHits = 0; int staNMuonHits = 0;
    int NTrackerHits = 0; int NMuonHits = 0;

  // Analyzer reco::Muon  
  for(View<Muon>::const_iterator iMuon = muonColl.begin();
      iMuon != muonColl.end(); ++iMuon) {

       //histograms for 
      commonME_->hMuonAllP_->Fill(iMuon->pfP4().P());
      commonME_->hMuonAllPt_->Fill(iMuon->pfP4().Pt());
      commonME_->hMuonAllEta_->Fill(iMuon->pfP4().Eta());
      commonME_->hMuonAllPhi_->Fill(iMuon->pfP4().Phi());

     //everything else uses track
     if (!selector_(*iMuon)) continue; 

     TrackRef Track = iMuon->track();

     if (Track.isNonnull()) {
     commonME_->hMuonTrackP_->Fill(Track->p());
     commonME_->hMuonTrackPt_->Fill(Track->pt());
     commonME_->hMuonTrackEta_->Fill(Track->eta());
     commonME_->hMuonTrackPhi_->Fill(Track->phi());

          //ip histograms
     commonME_->hMuonTrackDxy_->Fill(Track->dxy());
     commonME_->hMuonTrackDz_->Fill(Track->dz());
    }

    if (iMuon->isGlobalMuon()) {
          Track = iMuon->combinedMuon();
          glbNTrackerHits = countTrackerHits(*Track);
          glbNMuonHits = countMuonHits(*Track);
    } else if (iMuon->isTrackerMuon()) {
          Track = iMuon->track();
          trkNTrackerHits = countTrackerHits(*Track);
          trkNMuonHits = countMuonHits(*Track);
    } else {
          Track = iMuon->standAloneMuon();
          staNTrackerHits = countTrackerHits(*Track);
          staNMuonHits = countMuonHits(*Track);
    } 

    NTrackerHits = countTrackerHits(*Track);
    NMuonHits = countMuonHits(*Track);

//list of histos for each type

//      muonME_->hNTrks_->Fill();
          muonME_->hNTrksEta_->Fill(Track->eta());
          muonME_->hNTrksPt_->Fill(Track->pt());

          commonME_->hMuonP_->Fill(iMuon->p());
          commonME_->hMuonPt_->Fill(iMuon->pt());
          commonME_->hMuonEta_->Fill(iMuon->eta());
          commonME_->hMuonPhi_->Fill(iMuon->phi());

      if (iMuon->isGlobalMuon()) {
          double gtHitPat = iMuon->globalTrack()->hitPattern().numberOfHits() - iMuon->globalTrack()->hitPattern().numberOfValidHits();
          double itHitPat = iMuon->innerTrack()->hitPattern().numberOfHits() - iMuon->innerTrack()->hitPattern().numberOfValidHits();
          double otHitPat = iMuon->outerTrack()->hitPattern().numberOfHits() - iMuon->outerTrack()->hitPattern().numberOfValidHits();
      
          commonME_->hNInvalidHitsGTHitPattern_->Fill(gtHitPat);
          commonME_->hNInvalidHitsITHitPattern_->Fill(itHitPat);
          commonME_->hNInvalidHitsOTHitPattern_->Fill(otHitPat);
          commonME_->hNDeltaInvalidHitsHitPattern_->Fill(gtHitPat - itHitPat - otHitPat);
     }

          muonME_->hNTrackerHits_->Fill(NTrackerHits);
          muonME_->hNTrackerHits_vs_Pt_->Fill(Track->pt(), NTrackerHits);
          muonME_->hNTrackerHits_vs_Eta_->Fill(Track->eta(), NTrackerHits);

          muonME_->hNMuonHits_->Fill(NMuonHits);
          muonME_->hNMuonHits_vs_Pt_->Fill(Track->pt(), NMuonHits);
          muonME_->hNMuonHits_vs_Eta_->Fill(Track->eta(), NMuonHits);

         //must be global and standalone
         if (iMuon->isGlobalMuon() && iMuon->isStandAloneMuon()) { 
           commonME_->hStaToGlbDiffNMuonHitsEta_->Fill(Track->eta(),staNMuonHits-glbNMuonHits);
           commonME_->hStaToGlbDiffNMuonHitsPt_->Fill(Track->pt(),staNMuonHits-glbNMuonHits);
           commonME_->hStaToGlbDiffNMuonHits_->Fill(staNMuonHits-glbNMuonHits);
         }

         //must be global and tracker
         if (iMuon->isGlobalMuon() && iMuon->isTrackerMuon()) {
           commonME_->hTrkToGlbDiffNTrackerHitsEta_->Fill(Track->eta(),trkNTrackerHits-glbNTrackerHits);
           commonME_->hTrkToGlbDiffNTrackerHitsPt_->Fill(Track->pt(),trkNTrackerHits-glbNTrackerHits);
           commonME_->hTrkToGlbDiffNTrackerHits_->Fill(trkNTrackerHits-glbNTrackerHits);
        }

    }//end of reco muon loop

  // Associate by hits
  for(TrackingParticleCollection::size_type i=0; i<nSim; i++) {
    TrackingParticleRef simRef(simHandle, i);
    const TrackingParticle* simTP = simRef.get();
    if ( ! tpSelector_(*simTP) ) continue;

      //denominators for efficiency plots
      const double simP   = simRef->p();
      const double simPt  = simRef->pt();
      const double simEta = doAbsEta_ ? fabs(simRef->eta()) : simRef->eta();
      const double simPhi = simRef->phi();

      GlobalPoint  simVtx(simRef->vertex().x(), simRef->vertex().y(), simRef->vertex().z());
      GlobalVector simMom(simRef->momentum().x(), simRef->momentum().y(), simRef->momentum().z());
      const double simDxy = -simVtx.x()*sin(simPhi)+simVtx.y()*cos(simPhi);
      const double simDz  = simVtx.z() - (simVtx.x()*simMom.x()+simVtx.y()*simMom.y())*simMom.z()/simMom.perp2();
      
      const unsigned int nSimHits = simRef->pSimHit_end() - simRef->pSimHit_begin();

      muonME_->hSimP_  ->Fill(simP  );
      muonME_->hSimPt_ ->Fill(simPt );
      muonME_->hSimEta_->Fill(simEta);
      muonME_->hSimPhi_->Fill(simPhi);
      muonME_->hSimDxy_->Fill(simDxy);
      muonME_->hSimDz_->Fill(simDz);
      muonME_->hNSimHits_->Fill(nSimHits);

    // Get sim-reco association for a simRef
    vector<pair<RefToBase<Muon>, double> > MuRefV;
    if ( simToMuonColl.find(simRef) != simToMuonColl.end() ) {
      MuRefV = simToMuonColl[simRef];

      if ( !MuRefV.empty()) {
        muonME_->hNSimToReco_->Fill(MuRefV.size());
        const Muon* Mu = MuRefV.begin()->first.get();
        if (!selector_(*Mu)) continue;

        muonME_->fill(&*simTP, Mu); 
      }
    }
  }
}

int
RecoMuonValidatorPF::countMuonHits(const reco::Track& track) const {
  TransientTrackingRecHit::ConstRecHitContainer result;
  
  int count = 0;

  for (trackingRecHit_iterator hit = track.recHitsBegin(); hit != track.recHitsEnd(); ++hit) {
    if((*hit)->isValid()) {
      DetId recoid = (*hit)->geographicalId();
      if ( recoid.det() == DetId::Muon ) count++;
    }
  }
  return count;
}

int
RecoMuonValidatorPF::countTrackerHits(const reco::Track& track) const {
  TransientTrackingRecHit::ConstRecHitContainer result;
  
  int count = 0;

  for (trackingRecHit_iterator hit = track.recHitsBegin(); hit != track.recHitsEnd(); ++hit) {
    if((*hit)->isValid()) {
      DetId recoid = (*hit)->geographicalId();
      if ( recoid.det() == DetId::Tracker ) count++;
    }
  }
  return count;
}
/* vim:set ts=2 sts=2 sw=2 expandtab: */