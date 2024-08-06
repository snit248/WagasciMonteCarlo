//
// Created by Giorgio Pintaudi on 30/07/2020.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2PDG_HH
#define WAGASCIBABYMINDMONTECARLO_B2PDG_HH

#include <string>
#include <unordered_map>
#include <TPDGCode.h>
#include "B2Enum.hh"

/*
 * Class to deal with PDG ID for various elementary particles
 */
class B2Pdg {

private:
  ///> map from PDG ID to the name of the particle
  const static std::unordered_map<int, std::string> pdgid_;

public:

  /**
   * Convert the PDG ID into the particle name
   * @param pdg_particle_id PDG ID of the particle
   * @return human readable particle name
   */
  static std::string Stringify(int pdg_particle_id);

  /**
   * Convert the B2NeutrinoFlavor enum into the corresponding PDG ID
   *
   * @param flavor B2NeutrinoFlavor settings
   * @return neutrino PDG ID
   */
  static PDG_t NeutrinoFlavor2PdgId(B2NeutrinoFlavor flavor);

  /**
   * @param pdg_id PDG ID of the particle
   * @return true if the particle is a neutrino
   */
  static bool IsNeutrinoOrAntiNeutrino(int pdg_id);

  /**
   * @param pdg_id PDG ID of the particle
   * @return true if the particle is a muon or anti-muon
   */
  static bool IsMuonPlusOrMinus(int pdg_id);

  /**
   * @param pdg_id PDG ID of the particle
   * @return true if the particle is a electron or positron
   */
  static bool IsElectronOrPositron(int pdg_id);

  /**
   * @param pdg_id PDG ID of the particle
   * @return true if the particle is a lepton (but not neutrino)
   */
  static bool IsLepton(int pdg_id);

  /**
   * @param pdg_id PDG ID of the particle
   * @return true if the particle is a charged pion
   */
  static bool IsChargedPion(int pdg_id);
};

#endif //WAGASCIBABYMINDMONTECARLO_B2PDG_HH
