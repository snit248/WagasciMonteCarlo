//
// Created by Giorgio Pintaudi on 8/12/20.
//

#include "B2VetoSensitiveDetector.hh"

B2VetoSensitiveDetector::B2VetoSensitiveDetector(const G4String &name, const B2Dimension &dimension) :
    B2SensitiveDetector(name, dimension) {
  collectionName.insert("vetoHitCollection");
}

B2ScintillatorHit *B2VetoSensitiveDetector::HitFactory(G4int scintillator_id, const G4ThreeVector &hit_position) {
  auto *new_hit = new B2ScintillatorHit(B2ScintillatorType::kVeto, scintillator_id, hit_position);
  return new_hit;
}

G4ThreeVector B2VetoSensitiveDetector::GetHitAbsolutePosition(G4Step *step) {
  // We want true X and Y of veto-hit, Z of veto-hit is the Z-center of veto-bar...
  const G4VTouchable *touchable = step->GetPreStepPoint()->GetTouchable();
  const G4ThreeVector& hit_pos_true = step->GetPreStepPoint()->GetPosition();
  const G4ThreeVector& hit_pos_center = touchable->GetTranslation(0);
  G4ThreeVector hit_pos;
  hit_pos.set(hit_pos_true.getX(), hit_pos_true.getY(), hit_pos_center.getZ());
  return hit_pos;
}

