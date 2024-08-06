//
// Created by Giorgio Pintaudi on 2020/10/01.
//

#include "B2MichelElectron.hh"

// BOOST includes
#include <boost/log/trivial.hpp>

// ROOT includes
#include <TClonesArray.h>

// Geant4 includes
#include <G4ios.hh>

// Project includes
#include "B2Enum.hh"
#include "B2Pdg.hh"
#include "B2VertexSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2EventSummary.hh"
#include "B2Converters.hh"
#include "B2Dimension.hh"

bool B2MichelElectron::IsMichelElectronCandidate(const B2TrackSummary &track_summary) {
  return track_summary.GetTrackType() == B2TrackType::kSecondaryTrack &&
         (track_summary.GetSecondaryTrackType() == B2SecondaryTrackType::kMichelElectron ||
          track_summary.GetSecondaryTrackType() == B2SecondaryTrackType::kMichelElectronCandidateThatFailed) &&
         B2Pdg::IsElectronOrPositron(track_summary.GetParticlePdg());
}

bool B2MichelElectron::IsMuonDecayNeutrinoCandidate(const B2TrackSummary &track_summary) {
  return track_summary.GetTrackType() == B2TrackType::kSecondaryTrack &&
         track_summary.GetSecondaryTrackType() == B2SecondaryTrackType::kMuonDecayNeutrino &&
         B2Pdg::IsNeutrinoOrAntiNeutrino(track_summary.GetParticlePdg());
}

bool B2MichelElectron::IsInvariantMassConserved(const B2TrackSummary &muon,
                                                const B2TrackSummary &michel_electron,
                                                const B2TrackSummary &muon_neutrino,
                                                const B2TrackSummary &electron_neutrino) {
  double i_inv_mass = muon.GetMass().GetValue();
  double f_inv_mass = std::sqrt(std::pow(michel_electron.GetTotalEnergy().GetValue() +
                                         muon_neutrino.GetTotalEnergy().GetValue() +
                                         electron_neutrino.GetTotalEnergy().GetValue(), 2) -
                                (michel_electron.GetInitialMomentum().GetValue() +
                                 muon_neutrino.GetInitialMomentum().GetValue() +
                                 electron_neutrino.GetInitialMomentum().GetValue()).Mag2());
  return (std::fabs(2 * (f_inv_mass - i_inv_mass) / (f_inv_mass + i_inv_mass)) < invariant_mass_cut_ / 100.);
}


B2TrackSummary *B2MichelElectron::SearchMuonDecayNeutrino(PDG_t pdg_id) {
  if (!B2Pdg::IsNeutrinoOrAntiNeutrino(pdg_id))
    throw std::invalid_argument("SearchMuonDecayNeutrino : particle to search must be a neutrino");
  auto it = spill_summary_.get().BeginTrueTrack();
  while (auto *track_summary = it.Next()) {
    if (IsMuonDecayNeutrinoCandidate(*track_summary) && track_summary->GetParticlePdg() == pdg_id) {
      return track_summary;
    }
  }
  return nullptr;
}

std::vector<B2TrackSummary *> B2MichelElectron::CollectMichelElectronCandidates() {
  std::vector<B2TrackSummary *> candidates;
  auto it = spill_summary_.get().BeginTrueTrack();
  while (auto *track_summary = it.Next()) {
    if (IsMichelElectronCandidate(*track_summary)) {
      candidates.push_back(track_summary);
    }
  }
  return candidates;
}

void B2MichelElectron::RemoveFailedMichelElectronCandidates(const std::vector<B2TrackSummary *> &candidates) {
  auto it = spill_summary_.get().BeginTrueTrack();
  while (auto *track_summary = it.Next()) {
    if (IsMichelElectronCandidate(*track_summary) || IsMuonDecayNeutrinoCandidate(*track_summary)) {
      if (remove_michel_electrons_candidates_) {
        BOOST_LOG_TRIVIAL(trace) << "Removing Michel electron candidate or decay neutrino : " << *track_summary;
        spill_summary_.get().RemoveTrueTrack(track_summary, kTRUE);
      } else {
        if (track_summary->GetSecondaryTrackType() == B2SecondaryTrackType::kMichelElectron) {
          track_summary->SetSecondaryTrackType(B2SecondaryTrackType::kMichelElectronCandidateThatFailed);
          BOOST_LOG_TRIVIAL(trace) << "Flagging Michel electron candidate as failed : " << *track_summary;
        }
      }
    }
  }
}

bool B2MichelElectron::CheckMichelElectronCandidates(const std::vector<B2TrackSummary *> &candidates) {
  static int total_calls = 0;
  static int no_candidates = 0;
  static int no_muon_neutrino = 0;
  static int no_electron_neutrino = 0;
  static int wrong_inv_mass = 0;
  static int found_calls = 0;

  ++total_calls;

  bool michel_electron_found = false;

  if (candidates.empty()) {

    BOOST_LOG_TRIVIAL(trace) << "Reason for Michel electron search failure : no candidates ("
                             << ++no_candidates << "/" << total_calls << ")";

  } else {

    B2TrackSummary *real_michel_electron;
    B2TrackSummary *muon;
    B2TrackSummary *muon_neutrino;
    B2TrackSummary *electron_neutrino;

    for (const auto michel_electron: candidates) {

      // There must be a muon neutrino if the primary particle is a muon or a muon anti-neutrino if the primary
      // particle is an anti-muon
      muon = &michel_electron->GetParentTrack();
      muon_neutrino = SearchMuonDecayNeutrino(muon->GetParticlePdg() == PDG_t::kMuonMinus ?
                                              PDG_t::kNuMu : PDG_t::kNuMuBar);
      if (muon_neutrino == nullptr) {
        BOOST_LOG_TRIVIAL(trace) << "Reason for Michel electron search failure : no muon neutrino ("
                                 << ++no_muon_neutrino << "/" << total_calls << ")";
      } else {

        // There must be an electron anti0neutrino if the primary particle is a muon or an electron neutrino if the
        // primary particle is an anti-muon
        electron_neutrino = SearchMuonDecayNeutrino(muon->GetParticlePdg() == PDG_t::kMuonMinus ?
                                                    PDG_t::kNuEBar : PDG_t::kNuE);
        if (electron_neutrino == nullptr) {
          BOOST_LOG_TRIVIAL(trace) << "Reason for Michel electron search failure : no electron neutrino ("
                                   << ++no_electron_neutrino << "/" << total_calls << ")";
        } else {

          // Check for invariant mass conservation
          if (IsInvariantMassConserved(*muon, *michel_electron, *muon_neutrino, *electron_neutrino)) {
            real_michel_electron = michel_electron;
            michel_electron_found = true;
          } else {
            BOOST_LOG_TRIVIAL(trace) << "Reason for Michel electron search failure : wrong invariant mass ("
                                     << ++wrong_inv_mass << "/" << total_calls << ")";
          }
        }
      }

      if (michel_electron_found)
        break;
    }

    // Create a vertex for the Michel electron decay
    if (michel_electron_found) {
      BOOST_LOG_TRIVIAL(trace) << "Found Michel electron (" << ++found_calls << "/" << total_calls << ")";
      AddMichelVertex(muon, muon_neutrino, electron_neutrino, real_michel_electron);
    }
  }

  return michel_electron_found;
}

void B2MichelElectron::AddMichelVertex(B2TrackSummary *muon, B2TrackSummary *muon_neutrino,
                                       B2TrackSummary *electron_neutrino, B2TrackSummary *michel_electron) {
  auto &vertex = spill_summary_.get().AddTrueVertex();
  vertex.SetIncomingTrack(muon);
  vertex.SetIncomingParticlePdg(muon->GetParticlePdg());
  vertex.AddOutgoingTrack(michel_electron);
  vertex.AddOutgoingTrack(muon_neutrino);
  vertex.AddOutgoingTrack(electron_neutrino);
  vertex.SetAbsolutePosition(muon->GetFinalPosition());
  vertex.SetTotalEnergy(momentum_mass_to_total_energy(muon->GetFinalAbsoluteMomentum().GetValue(),
                                                      muon->GetMass().GetValue()));
  vertex.SetMomentum(muon->GetFinalMomentum());
  vertex.SetInteractionType(B2InteractionMode::MODE_MICHEL_ELECTRON);
  // In case of multiple events per spill, the B2EventSummary::SearchClosestHit needs to be called
  auto *closest_hit = spill_summary_.get().SearchClosestHit(vertex.GetAbsolutePosition().GetValue(),
                                                            closest_distance_cut_);
  if (closest_hit) {
    vertex.SetClosestHit(closest_hit);
    vertex.SetDetector(closest_hit->GetDetectorId());
    if (closest_hit->GetDetectorId() >= 0 && closest_hit->GetDetectorId() < B2Detector::kNumDetectors) {
      TVector3 pos(vertex.GetAbsolutePosition().GetValue());
      pos.SetX(pos.X() - POSITION_OFFSET_X.at((B2Detector) closest_hit->GetDetectorId()));
      pos.SetY(pos.Y() - POSITION_OFFSET_Y.at((B2Detector) closest_hit->GetDetectorId()));
      pos.SetZ(pos.Z() - POSITION_OFFSET_Z.at((B2Detector) closest_hit->GetDetectorId()));
      vertex.SetRelativePosition(pos);
    }
  }
  michel_electron->SetParentVertex(vertex);
  muon_neutrino->SetParentVertex(vertex);
  electron_neutrino->SetParentVertex(vertex);
  BOOST_LOG_TRIVIAL(trace) << "Michel vertex summary : \n" << vertex;
}

bool B2MichelElectron::SearchMichelElectronCandidates() {
  // Search for Michel electron candidates
  const auto candidates = CollectMichelElectronCandidates();

  // Check if each candidate is indeed a Michel electron. It is assumed that there
  // can be only a single Michel electron per event since there is a single muon per event
  bool found_michel_electron = CheckMichelElectronCandidates(candidates);

  // Michel electron not found. If the process_secondary_tracks_ flag is enabled, the Michel electron candidates are
  // flagged as failed, if the flag is disabled they are removed together with all the secondary neutrinos.
  if (!found_michel_electron) {
    RemoveFailedMichelElectronCandidates(candidates);
  }

  // Return true if a Michel electron was found, otherwise false
  return found_michel_electron;
}