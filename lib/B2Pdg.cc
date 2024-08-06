//
// Created by Giorgio Pintaudi on 30/07/2020.
//

#include "B2Pdg.hh"

#include <string>
#include <unordered_map>

const std::unordered_map<int, std::string> B2Pdg::pdgid_ = { // NOLINT(cert-err58-cpp)
    {PDG_t::kElectron,  "electron"},
    {PDG_t::kPositron,  "positron"},
    {PDG_t::kNuE,       "electron neutrino"},
    {PDG_t::kNuEBar,    "electron anti-neutrino"},
    {PDG_t::kMuonMinus, "muon"},
    {PDG_t::kMuonPlus,  "anti-muon"},
    {PDG_t::kNuMu,      "muon neutrino"},
    {PDG_t::kNuMuBar,   "muon anti-neutrino"},
    {PDG_t::kTauMinus,  "tau"},
    {PDG_t::kTauPlus,   "anti-tau"},
    {PDG_t::kNuTau,     "tau neutrino"},
    {PDG_t::kNuTauBar,  "tau anti-neutrino"},
    {PDG_t::kGamma,     "photon"},
    {PDG_t::kProton,    "proton"},
    {PDG_t::kNeutron,   "neutron"},
    {PDG_t::kPi0,       "neutral pion"},
    {PDG_t::kPiPlus,    "pion +"},
    {PDG_t::kPiMinus,   "pion -"},
    {PDG_t::kK0,        "neutral kaon"},
    {PDG_t::kKPlus,     "kaon +"},
    {PDG_t::kKMinus,    "kaon -"}
};

std::string B2Pdg::Stringify(int pdg_particle_id) {
  if (pdgid_.count(pdg_particle_id) == 0)
    return std::to_string(pdg_particle_id);
  else
    return pdgid_.at(pdg_particle_id);
}

PDG_t B2Pdg::NeutrinoFlavor2PdgId(B2NeutrinoFlavor flavor) {
  switch (flavor) {
    case B2NeutrinoFlavor::kPrimaryMuonNeutrino:
      return kNuMu;
    case B2NeutrinoFlavor::kPrimaryAntiMuonNeutrino:
      return kNuMuBar;
    case B2NeutrinoFlavor::kPrimaryElectronNeutrino:
      return kNuE;
    case B2NeutrinoFlavor::kPrimaryAntiElectronNeutrino:
      return kNuEBar;
    default:
      throw std::invalid_argument("Invalid B2NeutrinoFlavor value : " + std::to_string(flavor));
  }
}

bool B2Pdg::IsNeutrinoOrAntiNeutrino(int pdg_id) {
  return pdg_id == PDG_t::kNuE ||
         pdg_id == PDG_t::kNuEBar ||
         pdg_id == PDG_t::kNuMu ||
         pdg_id == PDG_t::kNuMuBar ||
         pdg_id == PDG_t::kNuTau ||
         pdg_id == PDG_t::kNuTauBar;
}

bool B2Pdg::IsMuonPlusOrMinus(int pdg_id) {
  return pdg_id == PDG_t::kMuonMinus ||
         pdg_id == PDG_t::kMuonPlus;
}

bool B2Pdg::IsElectronOrPositron(int pdg_id) {
  return pdg_id == PDG_t::kElectron ||
         pdg_id == PDG_t::kPositron;
}

bool B2Pdg::IsLepton(int pdg_id) {
  return pdg_id == PDG_t::kElectron ||
         pdg_id == PDG_t::kPositron ||
         pdg_id == PDG_t::kMuonMinus ||
         pdg_id == PDG_t::kMuonPlus ||
         pdg_id == PDG_t::kTauMinus ||
         pdg_id == PDG_t::kTauPlus;
}

bool B2Pdg::IsChargedPion(int pdg_id) {
  return pdg_id == PDG_t::kPiPlus ||
         pdg_id == PDG_t::kPiMinus;
}
