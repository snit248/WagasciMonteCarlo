//
// Created by Giorgio Pintaudi on 8/12/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2SENSITIVEDETECTOR_HH
#define WAGASCIBABYMINDMONTECARLO_B2SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "B2ScintillatorHit.hh"
#include "B2Response.hh"

/**
 * G4VSensitiveDetector is an abstract base class which represents a
 * detector. The principal mandate of a sensitive detector is the construction
 * of hit objects using information from steps along a particle track.  If user needs to define an
 * artificial second geometry, use Parallel Geometrie */
class B2SensitiveDetector : public G4VSensitiveDetector {

private:
  ///> Collection of hits
  std::reference_wrapper<const B2Dimension> dimension_;
  G4THitsCollection<B2ScintillatorHit>* hit_collection_;
  ///> Response of the detector to the passage of particles through it
  B2Response response_;
  ///> Total energy deposit in this view
  G4double total_energy_deposit_;

  /*
   * Produce a hit of a certain type
   */
  virtual B2ScintillatorHit * HitFactory(G4int scintillator_id, const G4ThreeVector & hit_position) = 0;

  /**
   * Get the hit position
   * @param step Geant4 step
   * @return hit position
   */
  virtual G4ThreeVector GetHitAbsolutePosition(G4Step *step) = 0;

public:
  /**
   * @param name name of the sensitive detector
   */
  explicit B2SensitiveDetector(const G4String &name, const B2Dimension &dimension);

  /**
   * Initialize the private members and add the hits collection to the list of collections
   * of this event
   * @param hit_collections_this_event list of collections of hits of this event
   */
  void Initialize(G4HCofThisEvent* hit_collections_this_event) override;

  /*
   * The ProcessHits() method of G4VSensitiveDetector performs this task using G4Step
   * objects as input. The second argument of ProcessHits() method, i.e. G4TouchableHistory,
   * is obsolete and not used.
   *
   * @param step simulation step
   * @return This return value is not used by Geant4 kernel. It may be used by the user’s
   * use-case where one sensitive detector dispatches ProcessHits() to some subsequent
   * (i.e. child) sensitive detectors, and to avoid double-counting, one of these child
   * detector may return true or else.
   */
  G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;

  /**
   * Process again all the hits in this event and apply many physical corrections.
   *  - Light collection corrections
   *  - Fiber response corrections
   *  - MPPC response corrections
   *  - Electronics ADC corrections
   */
  void EndOfEvent(G4HCofThisEvent*) override;

  /**
   * Draw all hits
   */
  void DrawAll() override;

  /**
   * Print all hits
   */
  void PrintAll() override;
};


#endif //WAGASCIBABYMINDMONTECARLO_B2SENSITIVEDETECTOR_HH

