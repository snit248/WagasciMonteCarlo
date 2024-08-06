#ifndef B2_TRACKING_ACTION_H
#define B2_TRACKING_ACTION_H 1

#include "G4UserTrackingAction.hh"
#include "B2RunAction.hh"
#include "B2EventAction.hh"

/**
 * Class to access the track information during the propagation process.
 * The track information is taken from the G4Track object and stored
 * into the output format B2TrackSummary.
 */
class B2TrackingAction : public G4UserTrackingAction {

public:
  B2TrackingAction(B2RunAction *rac, const B2Settings &settings);

  /**
   * Routine called at the beginning of the track propagation process
   *
   * @param track Geant4 track
   */
  void PreUserTrackingAction(const G4Track *track) override;

  /**
   * Routine called at the end of the track propagation process
   *
   * @param track Geant4 track
   */
  void PostUserTrackingAction(const G4Track *track) override;

private:
  ///> run action
  B2RunAction *run_action_;

  const double michel_electron_decay_point_tolerance_ = 1 * cm;

  const double michel_electron_momentum_cut_ = 10 * MeV;

  bool process_michel_electrons_ = false;

  bool process_secondary_tracks_ = false;

  bool IsMichelElectronCandidate(const G4Track *track, const B2SpillSummary &spill_summary) const;

  bool IsMuonDecayNeutrino(const G4Track *track, const B2SpillSummary &spill_summary) const;
};

#endif
