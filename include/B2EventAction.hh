#ifndef B2EventAction_h
#define B2EventAction_h 1

// system includes
#include <vector>

// Geant4 includes
#include <G4UserEventAction.hh>
#include <G4Event.hh>

// Project includes
#include "B2Settings.hh"
#include "B2RunAction.hh"
#include "B2HitSummary.hh"
#include "B2EmulsionSummary.hh"
#include "B2Dimension.hh"
#include "B2ScintillatorHit.hh"
#include "B2EmulsionHit.hh"
#include "B2Pdg.hh"

/**
 * User routines to be called at the beginning and at the end of an event
 */
class B2EventAction : public G4UserEventAction {

public:

  explicit B2EventAction(B2RunAction *rac, const B2Dimension &dimension,
			 const B2Settings &settings);

  /**
   * Routine to be called at the beginning of an event
   * @param p_event Geant4 event
   */
  void BeginOfEventAction(const G4Event *p_event) override;

  /**
   * Routine to be called at the end of an event
   * @param p_event Geant4 event
   */
  void EndOfEventAction(const G4Event *p_event) override;

  /**
   * Do not process and record to file the current event
   */
  inline void UnsetWriteFlag() { write_flag_ = false; }

private:

  ///> maximum closest distance between an hit and the associated vertex
  constexpr static const double closest_distance_cut_ = 10 * cm;

  ///> Geant4 run action
  B2RunAction *run_action_;

  ///> Reference to the B2Dimension singleton
  std::reference_wrapper<const B2Dimension> dimension_;

  ///> If true the event is processed and recorded
  bool write_flag_;

  ///> Neutrino interaction detector name (refer B2Enum)
  const B2Detector neutrino_interaction_module_;

  ///> Process Michel electrons or not
  const bool process_michel_electrons_;

  ///> Remove invalid Michel electrons or not
  const bool remove_invalid_michel_electrons_;

  /**
   * Draw an event if the Geant4 visualization is enabled
   * @param p_event Geant4 event
   * @param hits list of hits to draw
   * @param emulsion_hits list of emulsion hits to draw
   */
  void DrawEvent(const G4Event *p_event, const std::vector<B2ScintillatorHit *> &hits,
                 const std::vector<B2EmulsionHit *> &emulsion_hits = std::vector<B2EmulsionHit *>());

  /**
   * Fill a vector with all the hits of an event
   * @param p_event Geant4 event
   * @param hits vector to be filled
   * @return number of hits found
   */
  static std::size_t CollectScintillatorHits(const G4Event *p_event, std::vector<B2ScintillatorHit *> &hits);


  /**
   * Fill the B2HitSummary object with the info contained in the B2Hit object
   * @param hit B2hit object
   * @return B2HitSummary object
   */
  void CreateHitSummary(B2ScintillatorHit *hit);

  /**
   * Fill the B2TrackSummary and B2ClusterSummary objects with the hit info
   * contained in the B2Hit and B2HitSummary. Then add the track reference
   * to the B2HitSummary object.
   * @param hit B2Hit object
   * @param hit_summary B2HitSummary object
   */
  void AddHitsToTrackSummary(const B2ScintillatorHit *hit);

  /**
   * Calculate some global information about the track from all its hits
   */
  void ProcessTracks();

  /**
   * Remove all tracks without any hit
   */
  void RemoveEmptyTracks();

  /**
   * Calculate some global information about the cluster from all its hits
   */
  void ProcessClusters();

  /**
   * Set the closest hit to the primary vertex
   */
  void SetPrimaryVertexClosestHit();

  /**
   * Process the hits
   * @param hits hits
   */
  void ProcessScintillatorHits(std::vector<B2ScintillatorHit *> &hits);

  /**
   * Process the Michel electrons
   */
  void ProcessMichelElectrons();

#ifdef NINJA

  /**
   * Fill a vector with all the emulsion hits of an event
   * @param p_event Geant4 event
   * @param emuslion_hits vector to be filled
   * @return number of emulsion hits found
   */
  static std::size_t CollectEmulsionHits(const G4Event *p_event, std::vector<B2EmulsionHit *> &emulsion_hits);

  /**
   * Fill the B2EmulsionSummary object with the info contained in the B2Hit objects
   * @param emulsion_hit_up upstream B2EmulsionHit object
   * @param emulsion_hit_down downstream B2EmulsionHit object
   * @return B2EmulsionSummary object
   */
  B2EmulsionSummary &CreateEmulsionSummary(const B2EmulsionHit *emulsion_hit_up,
                                           const B2EmulsionHit *emulsion_hit_down);

  /**
   * @param emulsion_hit B2EmulsionHit object
   * @param emulsion_summary B2EmulsionSummary object
   */
  void AddEmulsionsToTrackSummary(const B2EmulsionHit *emulsion_hit, B2EmulsionSummary &emulsion_summary);

  /**
   * Process the emulsion hits
   */
  void ProcessEmulsionHits(const std::vector<B2EmulsionHit *> &emulsion_hits);

#endif

};

#endif
