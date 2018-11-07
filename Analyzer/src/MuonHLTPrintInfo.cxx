#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include <vector>
#include <iostream>

using namespace std;
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
t_iterL3MuonNoID_    ( consumes< std::vector<reco::Muon> >                (iConfig.getUntrackedParameter<edm::InputTag>("iterL3MuonNoID"    )) ),
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

void MuonHLTPrintInfo::analyze(const edm::Event&, const edm::EventSetup&)
{
  cout << iEvent.id().run() << ":" << iEvent.id().luminosityBlock() << ":" << iEvent.id().event() << endl;

  // -- L1 muon
  edm::Handle<l1t::MuonBxCollection> h_L1Muon;
  if( printL1Muon_ && iEvent.getByToken(t_L1Muon_, h_L1Muon) )
    PrintMuonBxCollection("L1Muon", h_L1Muon);

  // -- L2 muon
  edm::Handle<PrintRecoChargedCandidateCollection> h_L2Muon;
  if( printL2Muon_ && iEvent.getByToken(t_L2Muon_, h_L2Muon) )
    PrintRecoChargedCandidateCollection("L2Muon", h_L2Muon);

  // -- L3 muon
  edm::Handle<PrintRecoChargedCandidateCollection> h_L3Muon;
  if( printL3Muon_ && iEvent.getByToken(t_L3Muon_, h_L3Muon) )
    PrintRecoChargedCandidateCollection("L3Muon", h_L3Muon);


  printf("\n");
}

void MuonHLTPrintInfo::PrintMuonBxCollection(std::string type, edm::Handle<l1t::MuonBxCollection>& handle)
{
  printf("[MuonHLTPrintInfo::PrintMuonBxCollection] type = %s\n", type);

  for(int ibx = handle->getFirstBX(); ibx<=handle->getLastBX(); ++ibx)
  {
    if(ibx != 0) continue; // -- only take when ibx == 0 -- //

    int nObject = (int)handle->size();
    printf("# object = %d\n", nObject);
    for(int i_obj=0; i_obj<nObject; i_obj++)
    {
      l1t::MuonRef ref_L1Mu(handle, distance(handle->begin(handle->getFirstBX()), i_obj) );

      printf("  [%02d object] (pt, eta, phi, charge, quality) = (%.3lf, %.3lf, %.3lf, %.3lf, %d)\n",
             i_obj, ref_L1Mu->pt(), ref_L1Mu->eta(), ref_L1Mu->phi(), ref_L1Mu->charge(), ref_L1Mu->hwQual() );
    }
  }
  printf("\n");
}

void MuonHLTPrintInfo::PrintRecoChargedCandidateCollection(std::string type, edm::Handle<RecoChargedCandidateCollection>& handle)
{
  printf("[MuonHLTPrintInfo::PrintRecoChargedCandidateCollection] type = %s\n", type);

  int nObject = (int)handle->size();
  printf("# object = %d\n", nObject);
  for(int i_obj=0; i_obj<nObject; i_obj++)
  {
    reco::RecoChargedCandidateRef ref(handle, i_obj);

    printf("  [%02d object] (pt, eta, phi, charge, trkPt) = (%.3lf, %.3lf, %.3lf, %.3lf, %.3lf)\n",
           i_obj, ref->pt(), ref->eta(), ref->phi(), ref->charge(), ref->track()->pt() );
  }

  printf("\n");
}

DEFINE_FWK_MODULE(MuonHLTPrintInfo);