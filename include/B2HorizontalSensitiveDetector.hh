#ifndef B2HLayerSD_H
#define B2HLayerSD_H

#include "G4VSensitiveDetector.hh"

#include "B2ScintillatorHit.hh"
#include "B2Response.hh"
#include "B2SensitiveDetector.hh"

/**
 * Class describing horizontal scintillator bars and their hits
 */
class B2HorizontalSensitiveDetector : public B2SensitiveDetector {

private:
  /**
   * Generate a hit object on the heap.
   *
   * @param scintillator_id scintillator ID
   * @param hit_position hit position
   * @return B2Hit object
   */
  B2ScintillatorHit *HitFactory(G4int scintillator_id, const G4ThreeVector &hit_position) override;

  /**
   * Get the hit position
   * @param step Geant4 step
   * @return hit position
   */
  G4ThreeVector GetHitAbsolutePosition(G4Step *step) override;

public:
  /**
   * @param name name of the sensitive detector
   */
  explicit B2HorizontalSensitiveDetector(const G4String &name, const B2Dimension &dimension);
};

#endif
