//
// Created by neo on 8/21/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2CONVERTERS_HH
#define WAGASCIBABYMINDMONTECARLO_B2CONVERTERS_HH

#include <array>
#include <TVector3.h>
#include <G4ThreeVector.hh>

#include "B2Const.hh"
#include "B2Measurement.hh"

/**
 * Convert from Geant4 3D vector to Root 3D vector
 * @param v Geant4 3D vector
 * @return Root 3D vector
 */
TVector3 geant_v_to_root_v(const G4ThreeVector& v);

/**
 * Convert from ROOT 3D vector to B2Vector3 3D vector
 * @param v ROOT 3D vector
 * @return B2Vector3 3D vector
 */
B2Vector3 root_v_to_my_v(const TVector3 &v);

/**
 * Convert from 3D std::array to Root 3D vector
 * @param v 3D std::array
 * @return Root 3D vector
 */
TVector3 std_array_to_root_v(const std::array<Float_t, 3>& v);

/**
 * Convert from 3D std::array to Geant4 3D vector
 * @param v 3D std::array
 * @return Geant4 3D vector
 */
G4ThreeVector std_array_to_geant_v(const std::array<Float_t, 3>& v);

/**
 * Convert from 3D C-array to Geant4 3D vector
 * @param v 3D C-array
 * @return Geant4 3D vector
 */
G4ThreeVector c_array_to_geant_v(const Float_t v[3]);

/**
 * Convert from 3D C-array to Geant4 3D vector
 * @param v 3D C-array
 * @return ROOT 3D vector
 */
TVector3 c_array_to_root_v(const Float_t v[3]);

/**
 * Convert from ROOT 3D vector to Geant4 3D vector
 * @param v ROOT 3D vector
 * @return Geant4 3D vector
 */
G4ThreeVector root_v_to_geant_v(const TVector3& v);

/**
 * Convert from momentum and mass to relativistic kinetic energy
 * @param momentum momentum
 * @param mass mass
 * @return relativistic kinetic energy
 */
G4double momentum_mass_to_kinetic_energy(G4double momentum, G4double mass);

/**
 * Convert from momentum and mass to relativistic total energy
 * @param momentum momentum
 * @param mass mass
 * @return relativistic total energy
 */
G4double momentum_mass_to_total_energy(G4double momentum, G4double mass);

/**
 * Convert from scintillator ID to B2Detector ID
 * @param scintillator_id scintillator ID
 * @return B2Detector ID
 */
B2Detector scinti_id_to_detector_id(G4int scintillator_id);

/**
 * Convert from emulsion ID to B2EmulsionType ID
 * @param emulsion_id emulsion ID
 * @return B2EmulsionType ID
 */
B2EmulsionType emulsion_id_to_emulsion_type(G4int emulsion_id);

/**
 * Convert from emulsion ID to B2EmulsoinLayer ID
 * @param emulsion_id emulsion ID
 * @return B2EmulsionLayer ID
 */
B2EmulsionLayer emulsion_id_to_emulsion_layer(G4int emulsion_id);

/**
 * @param direction direction of particle
 * @return angle with zeta direction for top view and side view
 */
B2ViewAngle direction_to_view_angle(const G4ThreeVector& direction);

/**
 * @param direction direction of particle
 * @return angle with zeta direction
 */
B2Angle direction_to_angle(const G4ThreeVector &direction);

#endif //WAGASCIBABYMINDMONTECARLO_B2CONVERTERS_HH
