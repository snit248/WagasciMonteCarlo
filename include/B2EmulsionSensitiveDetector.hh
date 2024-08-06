#ifndef WAGASCIBABYMINDMONTECARLO_B2EMULSIONSENSITIVEDETECTOR_HH
#define WAGASCIBABYMINDMONTECARLO_B2EMULSIONSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

#include "B2EmulsionHit.hh"

class B2EmulsionSensitiveDetector : public G4VSensitiveDetector {

private:
  ///> Collection of emulsion hits
  G4THitsCollection<B2EmulsionHit> *emulsion_hit_collection_;
  ///> Total energy deposit
  G4double total_emulsion_dep_;

public:
  /**
   * @param name name of sensitive detector
   */
  explicit B2EmulsionSensitiveDetector(const G4String &name);

  /**
   * Initialize the private members and add the hit collection to the list of collections
   * of this event
   * @param emulsion_hit_collections_this_event list of collections of hits of this event
   */
  void Initialize(G4HCofThisEvent *emulsion_hit_collections_this_event) override;

  /**
   * The ProcessHits() method of G4VSensitiveDetector performs this task using G4Step
   * objects as input. The second argument of ProcessHits() method, i.e. G4TouchableHistory,
   * is obsolete and not used.
   * 
   * @param step simulation step
   * @return may not be used
   */
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *) override;

  /**
   * Process again all the hits if you apply hit resopnse
   */
  void EndOfEvent(G4HCofThisEvent *) override;

  /**
   * Draw all hits
   */
  void DrawAll() override;


  /**
   * Print all hits
   */
  void PrintAll() override;

};

#endif // WAGASCIBABYMINDMONTECARLO_B2EMULSIONSENSITIVEDETECTOR_HH
