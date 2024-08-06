//
// Created by Giorgio Pintaudi on 2020/10/01.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2MICHELELECTRON_HH
#define WAGASCIBABYMINDMONTECARLO_B2MICHELELECTRON_HH

// system includes
#include <vector>

// Geant4 includes
#include <G4UserEventAction.hh>
#include <G4Event.hh>

// project includes
#include "B2RunAction.hh"
#include "B2HitSummary.hh"
#include "B2Dimension.hh"
#include "B2ScintillatorHit.hh"
#include "B2Pdg.hh"

class B2MichelElectron {

private:

  ///> maximum closest distance between an hit and the associated vertex
  constexpr static const double closest_distance_cut_ = 10 * cm;

  ///> decay of a muon into a michel electron must conserve the invariant
  /// mass up to this percentage.
  constexpr static const double invariant_mass_cut_ = 5.; // %

  ///> Reference to B2SpillSummary
  std::reference_wrapper<B2SpillSummary> spill_summary_;

  ///> Flag to remove or not invalid Michel eletrons
  const bool remove_michel_electrons_candidates_;

  /**
   * Search for neutrinos from muon decay
   * @param pdg_id neutrino type
   * @return neutrino track
   */
  B2TrackSummary *SearchMuonDecayNeutrino(PDG_t pdg_id);

  /**
   * Collect Michel electron candidates into a vector
   * @return list of Michel electron track candidates
   */
  std::vector<B2TrackSummary *> CollectMichelElectronCandidates();

  /**
   * Remove all Michel electron candidates that did not meet the requirements
   * @param candidates list of Michel electron track candidates
   */
  void RemoveFailedMichelElectronCandidates(const std::vector<B2TrackSummary *> &candidates);

  /**
   * From all the Michel electron candidates, pick the one that really comes from
   * a muon decay (if any). The invariant mass conservation of the decay is checked.
   * @param candidates list of Michel electron track candidates
   * @return true in case a Michel electron was found
   */
  bool CheckMichelElectronCandidates(const std::vector<B2TrackSummary *> &candidates);

  /**
   * Calculate the vertex properties of a muon decay into a Michel electron
   * @param muon muon track
   * @param muon_neutrino muon (anti)neutrino track
   * @param electron_neutrino electron (anti)neutrino track
   * @param michel_electron Michel electron track
   */
  void AddMichelVertex(B2TrackSummary *muon, B2TrackSummary *muon_neutrino, B2TrackSummary *electron_neutrino,
                       B2TrackSummary *michel_electron);

  /**
   * @param track_summary a track
   * @return true if the track is a Michel electron candidate
   */
  static bool IsMichelElectronCandidate(const B2TrackSummary &track_summary);

  /**
   * @param track_summary a track
   * @return true if the track is a neutrino or antineutrino from muon decay candidate
   */
  static bool IsMuonDecayNeutrinoCandidate(const B2TrackSummary &track_summary);

  /**
   * @param muon muon
   * @param electron Michel electron
   * @param muon_neutrino muon neutrino from muon decay
   * @param electron_neutrino electron neutrino from muon decay
   * @return true if the invariant mass is conserved with invariant_mass_cut_ tolerance.
   */
  static bool IsInvariantMassConserved(const B2TrackSummary &muon, const B2TrackSummary &electron,
                                       const B2TrackSummary &muon_neutrino, const B2TrackSummary &electron_neutrino);

public:

  explicit B2MichelElectron(B2SpillSummary &spill_summary, bool remove_invalid = true) :
      spill_summary_(spill_summary),
      remove_michel_electrons_candidates_(remove_invalid) {}

  /**
   * Search for Michel electron candidates
   * @return true if a Michel electron was found
   */
  bool SearchMichelElectronCandidates();

};


#endif //WAGASCIBABYMINDMONTECARLO_B2MICHELELECTRON_HH
