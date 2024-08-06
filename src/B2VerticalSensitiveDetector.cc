#include "B2VerticalSensitiveDetector.hh"

B2VerticalSensitiveDetector::B2VerticalSensitiveDetector(const G4String &name, const B2Dimension &dimension) :
    B2SensitiveDetector(name, dimension) {
  collectionName.insert("vlayerHitCollection");
}

B2ScintillatorHit *B2VerticalSensitiveDetector::HitFactory(G4int scintillator_id, const G4ThreeVector &hit_position) {
  auto *new_hit = new B2ScintillatorHit(B2ScintillatorType::kVertical, scintillator_id, hit_position);
  return new_hit;
}

G4ThreeVector B2VerticalSensitiveDetector::GetHitAbsolutePosition(G4Step *step) {
  return step->GetPreStepPoint()->GetPosition();
}