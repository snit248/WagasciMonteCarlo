//
// Created by Giorgio Pintaudi on 8/21/20.
//

#include "B2CosmicMuon.hh"

#include <Randomize.hh>
#include <G4SystemOfUnits.hh>

#include "B2Converters.hh"

G4double B2CosmicMuon::GetEnergy() const {
  return energy_;
}

G4double B2CosmicMuon::GetAbsMomentum() const {
  return abs_momentum_;
}

const G4ThreeVector &B2CosmicMuon::GetPosition() const {
  return position_;
}

const G4ThreeVector &B2CosmicMuon::GetDirection() const {
  return direction_;
}

void B2CosmicMuon::GenerateEnergyAndMomentum() {
  //set momentum
  G4double mass = 105.658 * MeV;
  G4double fitparam[5] = {0.01371, -2.407, 149.7, -247.0, 131.9};
  G4double muon_momentum;
  G4double muon_momentum_calc;
  G4double random_momentum_calc;
  G4double func_calc;
  while (true) {
    muon_momentum_calc = G4UniformRand() * 99 + 1; //1-100GeV
    func_calc = (G4double) (fitparam[0] +
                            fitparam[1] * pow(muon_momentum_calc, -1) +
                            fitparam[2] * pow(muon_momentum_calc, -2) +
                            fitparam[3] * pow(muon_momentum_calc, -3) +
                            fitparam[4] * pow(muon_momentum_calc, -4));
    random_momentum_calc = G4UniformRand() * 40;
    if (func_calc > random_momentum_calc) {
      muon_momentum = muon_momentum_calc * GeV;
      break;
    }
  }
  energy_ = momentum_mass_to_kinetic_energy(muon_momentum, mass);
  abs_momentum_ = muon_momentum;
}

void B2CosmicMuon::GenerateDirectionAndPosition() {
  G4double pi_calc = 4.0 * std::atan(1.0);
  G4double rand_theta_calc;
  G4double theta_calc, cos2theta_calc;
  G4double costheta_calc;
  G4double phi_calc;

  while (true) {
    while (true) {
      costheta_calc = G4UniformRand();
      phi_calc = 2. * pi_calc * G4UniformRand();
      cos2theta_calc = costheta_calc * costheta_calc;
      rand_theta_calc = G4UniformRand();
      if (cos2theta_calc > rand_theta_calc) {
        theta_calc = std::acos(costheta_calc);
        break;
      }
    }
    direction_.setX(std::sin(phi_calc) * std::sin(theta_calc));
    direction_.setY(-std::cos(theta_calc));
    direction_.setZ(std::cos(phi_calc) * std::sin(theta_calc));

    //set position
    position_.setX((G4UniformRand() - 0.5) * 3000.);
    position_.setY(350.);
    position_.setZ((G4UniformRand() - 0.5) * 3000. - 120.);

    //reject far event
    G4ThreeVector point_0(0, 0, -125);
    G4double t = direction_.getX() * (point_0.getX() - position_.getX()) +
                 direction_.getY() * (point_0.getY() - position_.getY()) +
                 direction_.getZ() * (point_0.getZ() - position_.getZ());
    G4ThreeVector point_1(direction_.getX() * t + position_.getX(),
                          direction_.getY() * t + position_.getY(),
                          direction_.getZ() * t + position_.getZ());
    auto dist = (G4double) std::sqrt(
        std::pow(point_0.getX() - point_1.getX(), 2) +
        std::pow(point_0.getY() - point_1.getY(), 2) +
        std::pow(point_0.getZ() - point_1.getZ(), 2));
    if (dist < std::sqrt(50 * 50 + 50 * 50 + 30 * 30)) {
      break;
    }
  }
  position_.setX(position_.getX() * cm);
  position_.setY(position_.getY() * cm);
  position_.setZ(position_.getZ() * cm);
}

const G4ThreeVector &B2CosmicMuon::GetMomentum() const {
  return momentum_;
}

B2CosmicMuon::B2CosmicMuon()  {
  GenerateEnergyAndMomentum();
  GenerateDirectionAndPosition();
  momentum_ = direction_ * abs_momentum_;
}
