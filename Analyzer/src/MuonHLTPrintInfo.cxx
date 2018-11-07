#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateIsolation.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Scalers/interface/LumiScalers.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTEventAnalyzerAOD.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace reco;
using namespace edm;

class MuonHLTPrintInfo : public edm::EDAnalyzer {
public:
  MuonHLTPrintInfo(const edm::ParameterSet&);
  void analyze(const edm::Event&, const edm::EventSetup&);

private:
  edm::EDGetTokenT< edm::TriggerResults >                    t_triggerResults_;
  edm::EDGetTokenT< trigger::TriggerEvent >                  t_triggerEvent_;

  edm::EDGetTokenT< reco::RecoChargedCandidateCollection >   t_L3Muon_;
  edm::EDGetTokenT< reco::RecoChargedCandidateCollection >   t_L2Muon_;
  edm::EDGetTokenT< l1t::MuonBxCollection >                  t_L1Muon_;

  edm::EDGetTokenT< std::vector<reco::MuonTrackLinks> >      t_iterL3OI_;
  edm::EDGetTokenT< std::vector<reco::MuonTrackLinks> >      t_iterL3IOFromL2_;
  edm::EDGetTokenT< std::vector<reco::MuonTrackLinks> >      t_iterL3FromL2_;
  edm::EDGetTokenT< std::vector<reco::Track> >               t_iterL3IOFromL1_;
  edm::EDGetTokenT< std::vector<reco::Muon> >                t_iterL3MuonNoID_;

  bool printL3Muon_;
  bool printL2Muon_;
  bool printL1Muon_;

  bool printIterL3OI_;
  bool printIterL3IOFromL2_;
  bool printIterL3FromL2_;
  bool printIterL3IOFromL1_;
  bool printIterL3MuonNoID_;

  void PrintMuonBxCollection(std::string type, edm::Handle<l1t::MuonBxCollection>& handle);
  void PrintRecoChargedCandidateCollection(std::string type, edm::Handle<RecoChargedCandidateCollection>& handle);
};

MuonHLTPrintInfo::MuonHLTPrintInfo(const edm::ParameterSet& iConfig):
t_triggerResults_    ( consumes< edm::TriggerResults >                    (iConfig.getUntrackedParameter<edm::InputTag>("triggerResults"    )) ),
t_triggerEvent_      ( consumes< trigger::TriggerEvent >                  (iConfig.getUntrackedParameter<edm::InputTag>("triggerEvent"      )) ),
t_L3Muon_            ( consumes< reco::RecoChargedCandidateCollection >   (iConfig.getUntrackedParameter<edm::InputTag>("L3Muon"            )) ),
t_L2Muon_            ( consumes< reco::RecoChargedCandidateCollection >   (iConfig.getUntrackedParameter<edm::InputTag>("L2Muon"            )) ),
t_L1Muon_            ( consumes< l1t::MuonBxCollection  >                 (iConfig.getUntrackedParameter<edm::InputTag>("L1Muon"            )) ),
t_iterL3OI_          ( consumes< std::vector<reco::MuonTrackLinks> >      (iConfig.getUntrackedParameter<edm::InputTag>("iterL3OI"          )) ),
t_iterL3IOFromL2_    ( consumes< std::vector<reco::MuonTrackLinks> >      (iConfig.getUntrackedParameter<edm::InputTag>("iterL3IOFromL2"    )) ),
t_iterL3FromL2_      ( consumes< std::vector<reco::MuonTrackLinks> >      (iConfig.getUntrackedParameter<edm::InputTag>("iterL3FromL2"      )) ),
t_iterL3IOFromL1_    ( consumes< std::vector<reco::Track> >               (iConfig.getUntrackedParameter<edm::InputTag>("iterL3IOFromL1"    )) ),
t_iterL3MuonNoID_    ( consumes< std::vector<reco::Muon> >                (iConfig.getUntrackedParameter<edm::InputTag>("iterL3MuonNoID"    )) )
{
  printL3Muon_ = iConfig.getUntrackedParameter<bool>("printL3Muon");
  printL2Muon_ = iConfig.getUntrackedParameter<bool>("printL2Muon");
  printL1Muon_ = iConfig.getUntrackedParameter<bool>("printL1Muon");

  printIterL3OI_        = iConfig.getUntrackedParameter<bool>("printIterL3OI");
  printIterL3IOFromL2_  = iConfig.getUntrackedParameter<bool>("printIterL3IOFromL2");
  printIterL3FromL2_    = iConfig.getUntrackedParameter<bool>("printIterL3FromL2");
  printIterL3IOFromL1_  = iConfig.getUntrackedParameter<bool>("printIterL3IOFromL1");
  printIterL3MuonNoID_  = iConfig.getUntrackedParameter<bool>("printIterL3MuonNoID");
}

void MuonHLTPrintInfo::analyze(const edm::Event& iEvent, const edm::EventSetup& iEventSetup)
{
  cout << iEvent.id().run() << ":" << iEvent.id().luminosityBlock() << ":" << iEvent.id().event() << endl;

  // -- L1 muon
  edm::Handle<l1t::MuonBxCollection> h_L1Muon;
  if( printL1Muon_ && iEvent.getByToken(t_L1Muon_, h_L1Muon) )
    PrintMuonBxCollection("L1Muon", h_L1Muon);

  // -- L2 muon
  edm::Handle<reco::RecoChargedCandidateCollection> h_L2Muon;
  if( printL2Muon_ && iEvent.getByToken(t_L2Muon_, h_L2Muon) )
    PrintRecoChargedCandidateCollection("L2Muon", h_L2Muon);

  // -- L3 muon
  edm::Handle<reco::RecoChargedCandidateCollection> h_L3Muon;
  if( printL3Muon_ && iEvent.getByToken(t_L3Muon_, h_L3Muon) )
    PrintRecoChargedCandidateCollection("L3Muon", h_L3Muon);


  printf("\n");
}

void MuonHLTPrintInfo::PrintMuonBxCollection(std::string type, edm::Handle<l1t::MuonBxCollection>& handle)
{
  cout << "[MuonHLTPrintInfo::PrintMuonBxCollection] type = " << type << endl;

  for(int ibx = handle->getFirstBX(); ibx<=handle->getLastBX(); ++ibx)
  {
    if(ibx != 0) continue; // -- only take when ibx == 0 -- //

    int nObject = 0;
    for(auto it=handle->begin(ibx); it!=handle->end(ibx); it++)
    {
      l1t::MuonRef ref_L1Mu( handle, distance(handle->begin(handle->getFirstBX()) , it) );
      cout << "  [" << nObject << " object] (pt, eta, phi, charge, quality) = ("
           << ref_L1Mu->pt() << ", "
           << ref_L1Mu->eta() << ", "
           << ref_L1Mu->phi() << ", "
           << ref_L1Mu->charge() << ", "
           << ref_L1Mu->hwQual() << ")" << endl;
      nObject++;
    }
    cout << "-> total # object: " << nObject << endl;
  }
  cout << endl;
}

void MuonHLTPrintInfo::PrintRecoChargedCandidateCollection(std::string type, edm::Handle<RecoChargedCandidateCollection>& handle)
{
  cout << "[MuonHLTPrintInfo::PrintRecoChargedCandidateCollection] type = " << type << endl;

  int nObject = (int)handle->size();
  printf("# object = %d\n", nObject);
  for(int i_obj=0; i_obj<nObject; i_obj++)
  {
    reco::RecoChargedCandidateRef ref(handle, i_obj);

    cout << "  [" << i_obj << " object] (pt, eta, phi, charge) = ("
         << ref->pt() << ", "
         << ref->eta() << ", "
         << ref->phi() << ", "
         << ref->charge() << ")" << endl;
  }

  cout << endl;
}

DEFINE_FWK_MODULE(MuonHLTPrintInfo);