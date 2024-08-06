//
// Created by Giorgio Pintaudi on 8/21/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2COSMICMUON_HH
#define WAGASCIBABYMINDMONTECARLO_B2COSMICMUON_HH

#include <G4ParticleDefinition.hh>
#include <G4ParticleTable.hh>
#include <G4ThreeVector.hh>

#include "B2Pdg.hh"

/**
 * Class to generate a random cosmic muon. Each object generates a single cosmic
 * muon upon construction. The muon properties can be accessed through getter methods.
 */
class B2CosmicMuon {

private:
  G4double energy_; // eV
  G4double abs_momentum_; // eV/c
  G4ThreeVector position_;
  G4ThreeVector direction_;
  G4ThreeVector momentum_; // eV/c

public:

  B2CosmicMuon();

  /**
   * @return muon momentum
   */
  const G4ThreeVector &GetMomentum() const;

  /**
   * @return muon energy in eV
   */
  G4double GetEnergy() const;

  /**
   * @return muon absolute momentum in eV/c
   */
  G4double GetAbsMomentum() const;

  /**
   * @return muon position in millimeters
   */
  const G4ThreeVector &GetPosition() const;

  /**
   * @return muon direction versor
   */
  const G4ThreeVector &GetDirection() const;

  /**
   * Set a random energy and momentum for a cosmic muon generated following
   * the appropriate distribution for cosmic rays. The distribution is averaged
   * over the zenit angle.
   * @param cosmic_muon cosmic muon object
   * @param energy energy of the cosmic muon
   * @param momentum of the cosmic muon
   */
  void GenerateEnergyAndMomentum();

  /**
   * Set a random direction and positionfor the cosmic muon
   * @param direction to be set (versor)
   * @param position to be set (in cm)
   */
  void GenerateDirectionAndPosition();
};


#endif //WAGASCIBABYMINDMONTECARLO_B2COSMICMUON_HH
