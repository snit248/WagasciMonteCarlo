#include "B2TrackingAction.hh"

// BOOST includes
#include <boost/log/trivial.hpp>

// Geant4 include
#include <G4TrackingManager.hh>
#include <G4Track.hh>
#include <G4VProcess.hh>

// project include
#include "B2TrackSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2EventSummary.hh"
#include "B2VertexSummary.hh"
#include "B2Converters.hh"
#include "B2Pdg.hh"
#include "B2SpillSummary.hh"

//////////////////////////////////////////////////////////////////////
B2TrackingAction::B2TrackingAction(B2RunAction *rac, const B2Settings &settings)
    : run_action_(rac),
      process_michel_electrons_(boost::any_cast<bool>(settings.At(B2Settings::MichelElectrons))),
      process_secondary_tracks_(boost::any_cast<bool>(settings.At(B2Settings::SecondaryTracks))) {}

//////////////////////////////////////////////////////////////////////
bool B2TrackingAction::IsMichelElectronCandidate(const G4Track *track, const B2SpillSummary &spill_summary) const {
  Int_t muon_id = B2_NON_INITIALIZED_VALUE;
  G4ThreeVector decay_point;
  auto it = spill_summary.BeginTrueTrack();
  while (const auto *i = it.Next()) {
    if (B2Pdg::IsMuonPlusOrMinus(i->GetParticlePdg()) && i->GetTrackType() == B2TrackType::kPrimaryTrack) {
      muon_id = (Int_t) i->GetTrackId();
      decay_point = root_v_to_geant_v(i->GetFinalPosition().GetValue());
    }
  }
  auto parent_id = track->GetParentID();
  return B2Pdg::IsElectronOrPositron(track->GetDefinition()->GetPDGEncoding()) &&
         muon_id != B2_NON_INITIALIZED_VALUE && parent_id == muon_id &&
         track->GetPosition().isNear(decay_point, michel_electron_decay_point_tolerance_) &&
         track->GetMomentum().mag() > michel_electron_momentum_cut_;
}

//////////////////////////////////////////////////////////////////////
bool B2TrackingAction::IsMuonDecayNeutrino(const G4Track *track, const B2SpillSummary &spill_summary) const {
  Int_t muon_id = B2_NON_INITIALIZED_VALUE;
  G4ThreeVector decay_point;
  auto it = spill_summary.BeginTrueTrack();
  while (const auto *i = it.Next()) {
    if (B2Pdg::IsMuonPlusOrMinus(i->GetParticlePdg()) && i->GetTrackType() == B2TrackType::kPrimaryTrack) {
      muon_id = (Int_t) i->GetTrackId();
      decay_point = root_v_to_geant_v(i->GetFinalPosition().GetValue());
    }
  }
  auto parent_id = track->GetParentID();
  return B2Pdg::IsNeutrinoOrAntiNeutrino(track->GetDefinition()->GetPDGEncoding()) &&
         muon_id != B2_NON_INITIALIZED_VALUE && parent_id == muon_id &&
         track->GetPosition().isNear(decay_point, michel_electron_decay_point_tolerance_);
}

//////////////////////////////////////////////////////////////////////
void B2TrackingAction::PreUserTrackingAction(const G4Track *track) {
  BOOST_LOG_TRIVIAL(trace) << "----- PreUserTrackingAction -----";

  auto &spill_summary = run_action_->GetSpillSummary();
  auto track_id = track->GetTrackID();
  auto parent_id = track->GetParentID();

  // Do not re-process tracks already processed
  if (!spill_summary.HasTrueTrack(track_id)) {

    // check if a track is consistent with the final state of a muon decaying into an electron
    const bool is_michel_like_interaction = process_michel_electrons_ &&
                                            (IsMichelElectronCandidate(track, spill_summary) ||
                                             IsMuonDecayNeutrino(track, spill_summary));

    // In case the user does not wants secondary tracks (with the exclusion of Michel electrons), do not process
    // secondary tracks
    if (!is_michel_like_interaction && !process_secondary_tracks_ && parent_id != 0)
      return;

    auto &track_summary = spill_summary.AddTrueTrack();
    track_summary.SetTrackId(track_id);
    track_summary.SetParentTrackId(parent_id);

    if (parent_id == 0) {
      auto *event_summary = (B2EventSummary *) spill_summary.GetTrueEvents().First();
      track_summary.SetParentVertex(event_summary->GetPrimaryVertex());
      track_summary.SetTrackType(B2TrackType::kPrimaryTrack);
      BOOST_LOG_TRIVIAL(trace) << "Added primary particle track with Geant4 ID " << track_id;
    } else {
      track_summary.SetTrackType(B2TrackType::kSecondaryTrack);
      BOOST_LOG_TRIVIAL(trace) << "Added secondary track with Geant4 ID " << track_id;

      if (is_michel_like_interaction && B2Pdg::IsNeutrinoOrAntiNeutrino(track->GetDefinition()->GetPDGEncoding())) {
        track_summary.SetSecondaryTrackType(B2SecondaryTrackType::kMuonDecayNeutrino);
        BOOST_LOG_TRIVIAL(trace) << "Added neutrino track from muon decay with Geant4 ID " << track_id;
      } else if (is_michel_like_interaction && B2Pdg::IsElectronOrPositron(track->GetDefinition()->GetPDGEncoding())) {
        track_summary.SetSecondaryTrackType(B2SecondaryTrackType::kMichelElectron);
        BOOST_LOG_TRIVIAL(trace) << "Added Michel electron track with Geant4 ID " << track_id;
      }
    }
    track_summary.SetParticlePdg(static_cast<PDG_t>(track->GetDefinition()->GetPDGEncoding()));
    track_summary.SetInitialMomentum(geant_v_to_root_v(track->GetMomentum()));
    track_summary.SetInitialAbsoluteMomentum(track->GetMomentum().mag());
    track_summary.SetInitialDirection(geant_v_to_root_v(track->GetMomentumDirection()));
    track_summary.SetInitialPosition(geant_v_to_root_v(track->GetPosition()));
    track_summary.SetTotalEnergy(track->GetTotalEnergy());
    track_summary.SetKineticEnergy(track->GetKineticEnergy());
    track_summary.SetMass(track->GetDefinition()->GetPDGMass());
    track_summary.SetViewAngle(direction_to_view_angle(track->GetMomentumDirection()));
    track_summary.SetAngle(direction_to_angle(track->GetMomentumDirection()));
    track_summary.SetDimensionality(B2Dimensionality::kTridimensional);
  } else {
    BOOST_LOG_TRIVIAL(warning) << "Track with Geant4 ID " << track_id << " already present";
  }
}

///////////////////////////////////////////////////////////////////////
void B2TrackingAction::PostUserTrackingAction(const G4Track *track) {
  BOOST_LOG_TRIVIAL(trace) << "----- PostUserTrackingAction -----";

  B2SpillSummary &spill_summary = run_action_->GetSpillSummary();
  auto track_id = track->GetTrackID();
  if (spill_summary.HasTrueTrack(track_id)) {
    auto &track_summary = spill_summary.GetTrueTrack(track_id);
    track_summary.SetParticlePdg(static_cast<PDG_t>(track->GetDefinition()->GetPDGEncoding()));
    track_summary.SetLength(track->GetTrackLength());
    track_summary.SetFinalMomentum(geant_v_to_root_v(track->GetMomentum()));
    track_summary.SetFinalAbsoluteMomentum(track->GetMomentum().mag());
    track_summary.SetFinalDirection(geant_v_to_root_v(track->GetMomentumDirection()));
    track_summary.SetFinalPosition(geant_v_to_root_v(track->GetPosition()));

    if (!track_summary.HasCluster(track_id)) {
      auto &cluster_summary = spill_summary.AddTrueCluster();
      cluster_summary.SetDimensionality(B2Dimensionality::kTridimensional);
      cluster_summary.SetClusterId(track_id);
      cluster_summary.SetParentTrackId(track_id);
      cluster_summary.SetParentTrack(track_summary);
      track_summary.AddCluster(cluster_summary, kFALSE);
      BOOST_LOG_TRIVIAL(trace) << "Added cluster with Geant4 ID " << track_id;
    }

    auto &cluster_summary = spill_summary.GetTrueCluster(track_id);
    cluster_summary.SetLength(track_summary.GetLength());
    cluster_summary.SetViewAngle(track_summary.GetViewAngle());
    cluster_summary.SetAngle(track_summary.GetAngle());

    if (!spill_summary.GetTrueEvents().IsEmpty()) {
      auto *event_summary = (B2EventSummary *) spill_summary.GetTrueEvents().First();
      track_summary.SetParentEvent(event_summary);
      cluster_summary.SetParentEvent(event_summary);
      if (track_summary.GetTrackType() == B2TrackType::kPrimaryTrack)
        event_summary->GetPrimaryVertex().AddOutgoingTrack(track_summary);
    } else {
      BOOST_LOG_TRIVIAL(warning) << "No events found for spill with ID "
                                 << spill_summary.GetBeamSummary().GetWagasciSpillNumber();
    }

    BOOST_LOG_TRIVIAL(trace) << "Cluster information";
    BOOST_LOG_TRIVIAL(trace) << cluster_summary;
    BOOST_LOG_TRIVIAL(trace) << "Track information";
    BOOST_LOG_TRIVIAL(trace) << track_summary;
  }
}
