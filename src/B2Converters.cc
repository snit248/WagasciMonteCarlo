//
// Created by Giorgio Pintaudi on 8/21/20.
//

#include "B2Converters.hh"
#include "B2Enum.hh"
#include "B2Measurement.hh"

TVector3 geant_v_to_root_v(const G4ThreeVector &v) {
  return TVector3(v.getX(), v.getY(), v.getZ());
}

B2Vector3 root_v_to_my_v(const TVector3 &v) {
  return B2Vector3(v.X(), v.Y(), v.Z());
}

TVector3 std_array_to_root_v(const std::array<Float_t, 3> &v) {
  return TVector3(v.at(B2Coordinate::kX), v.at(B2Coordinate::kY), v.at(B2Coordinate::kZ));
}

G4ThreeVector root_v_to_geant_v(const TVector3 &v) {
  return G4ThreeVector(v.X(), v.Y(), v.Z());
}

G4ThreeVector std_array_to_geant_v(const std::array<Float_t, 3> &v) {
  return G4ThreeVector(v.at(B2Coordinate::kX), v.at(B2Coordinate::kY), v.at(B2Coordinate::kZ));
}

G4double momentum_mass_to_kinetic_energy(G4double momentum, G4double mass) {
  return std::sqrt(mass * mass + momentum * momentum) - mass;
}

G4double momentum_mass_to_total_energy(G4double momentum, G4double mass) {
  return std::sqrt(mass * mass + momentum * momentum);
}

B2Detector scinti_id_to_detector_id(G4int scintillator_id) {
  const G4int delimiter = MAX_NUM_CHANNELS * MAX_NUM_PLANES;
  if (scintillator_id >= delimiter * B2Detector::kProtonModule &&
      scintillator_id < delimiter * (B2Detector::kProtonModule + 1))
    return B2Detector::kProtonModule;
  else if (scintillator_id >= delimiter * B2Detector::kWagasciUpstream &&
           scintillator_id < delimiter * (B2Detector::kWagasciUpstream + 1))
    return B2Detector::kWagasciUpstream;
  else if (scintillator_id >= delimiter * B2Detector::kWagasciDownstream &&
           scintillator_id < delimiter * (B2Detector::kWagasciDownstream + 1))
    return B2Detector::kWagasciDownstream;
  else if (scintillator_id >= delimiter * B2Detector::kWallMrdSouth &&
           scintillator_id < delimiter * (B2Detector::kWallMrdSouth + 1))
    return B2Detector::kWallMrdSouth;
  else if (scintillator_id >= delimiter * B2Detector::kWallMrdNorth &&
           scintillator_id < delimiter * (B2Detector::kWallMrdNorth + 1))
    return B2Detector::kWallMrdNorth;
  else if (scintillator_id >= delimiter * B2Detector::kBabyMind &&
           scintillator_id < delimiter * (B2Detector::kBabyMind + 1))
    return B2Detector::kBabyMind;
  else if (scintillator_id >= delimiter * B2Detector::kYasuTracker &&
           scintillator_id < delimiter * (B2Detector::kYasuTracker + 1))
    return B2Detector::kYasuTracker;
  else if (scintillator_id >= delimiter * B2Detector::kNinja &&
           scintillator_id < delimiter * (B2Detector::kNinja + 1))
    return B2Detector::kNinja;
  else
    throw std::invalid_argument("Something wrong with the scintillator ID");
}

B2EmulsionType emulsion_id_to_emulsion_type(G4int emulsion_id) {
  const G4int delimiter = DUMAX * ECCMAX * GELMAX;
  if (emulsion_id >= delimiter * B2EmulsionType::kECC &&
     emulsion_id < delimiter * (B2EmulsionType::kECC + 1))
    return kECC;
  else if (emulsion_id >= delimiter * B2EmulsionType::kShifter &&
	  emulsion_id < delimiter * (B2EmulsionType::kShifter + 1))
    return kShifter;
  else if (emulsion_id >= delimiter * B2EmulsionType::kSSS &&
	   emulsion_id < delimiter * (B2EmulsionType::kSSS + 1))
    return kSSS;
  else 
    throw std::invalid_argument("Something wrong with the emulsion type");
}

B2EmulsionLayer emulsion_id_to_emulsion_layer(G4int emulsion_id) {
  if(emulsion_id%DUMAX == B2EmulsionLayer::kUpstreamGel)
    return B2EmulsionLayer::kUpstreamGel;
  else if(emulsion_id%DUMAX == B2EmulsionLayer::kDownstreamGel)
    return B2EmulsionLayer::kDownstreamGel;
  else
    throw std::invalid_argument("Something wrong with the emulsion layer");
}

B2ViewAngle direction_to_view_angle(const G4ThreeVector &direction) {
  G4double theta = std::asin(direction.y());
  G4double phi = (180 / CLHEP::pi) * (std::acos(direction.z() / std::cos(theta)));
  theta *= 180 / CLHEP::pi;
  B2ViewAngle angle;
  angle.SetPolarAngle(theta);
  angle.SetAzimuthalAngle(phi);
  return angle;
}

B2Angle direction_to_angle(const G4ThreeVector &direction) {
  G4ThreeVector zeta(0, 0, 1);
  return B2Angle(180 / CLHEP::pi * direction.angle(zeta));
}

G4ThreeVector c_array_to_geant_v(const Float_t v[3]) {
  return G4ThreeVector(v[B2Coordinate::kX], v[B2Coordinate::kY], v[B2Coordinate::kZ]);
}

TVector3 c_array_to_root_v(const Float_t v[3]) {
  return TVector3(v[B2Coordinate::kX], v[B2Coordinate::kY], v[B2Coordinate::kZ]);
}
