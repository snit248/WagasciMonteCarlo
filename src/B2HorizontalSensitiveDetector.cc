#include "B2HorizontalSensitiveDetector.hh"

B2HorizontalSensitiveDetector::B2HorizontalSensitiveDetector(const G4String &name, const B2Dimension &dimension) :
    B2SensitiveDetector(name, dimension) {
  collectionName.insert("hlayerHitCollection");
}

B2ScintillatorHit *B2HorizontalSensitiveDetector::HitFactory(G4int scintillator_id, const G4ThreeVector &hit_position) {
  auto *new_hit = new B2ScintillatorHit(B2ScintillatorType::kHorizontal, scintillator_id, hit_position);
  return new_hit;
}

G4ThreeVector B2HorizontalSensitiveDetector::GetHitAbsolutePosition(G4Step *step) {
  return step->GetPreStepPoint()->GetPosition();
}