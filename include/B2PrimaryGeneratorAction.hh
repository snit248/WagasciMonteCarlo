#ifndef B2PrimaryGeneratorAction_h
#define B2PrimaryGeneratorAction_h 1

// system includes
#include <unordered_map>

// Geant4 includes
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>

// project includes
#include "B2RunAction.hh"
#include "B2EventAction.hh"
#include "B2Neut.hh"
#include "B2Settings.hh"

class B2PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:

  B2PrimaryGeneratorAction(B2Neut &neut,
                           B2RunAction *rac,
                           B2EventAction *evt,
                           const B2Settings &settings);

  void GeneratePrimaries(G4Event *g4_event) override;

private:

  /**
   * Generate the primary vertex for a cosmic muon using the particle gun
   *
   * @param g4_event Geant4 event as passed to GeneratePrimaries
   */
  void GenerateCosmicMuon(G4Event *g4_event);

  /**
   * Generate a pencil beam
   *
   * @param g4_event Geant4 event as passed to GeneratePrimaries
   */
  void GeneratePencilBeam(G4Event *g4_event);

  /**
   * Generate a muon beam for NINJA kink study
   * 
   * @param g4_event Geant4 event as passed to GeneratePriamries
   */
  void GenerateNinjaKinkBeam(G4Event *g4_event);

  /**
   * Generate the primary vertex for a neutrino using the NEUT output
   *
   * @param g4_event Geant4 event as passed to GeneratePrimaries
   */
  void GenerateNeutrino(G4Event *g4_event);

  /**
   * Read an event from the input NEUT file. If an error is encountered
   * a nullptr is returned
   * @return pointer to NeutEvent object
   */
  const NeutEvent * ReadNeutEvent();

  /**
   * Get ECC plate id corresponding to the neutrino interaction point
   * @param z_pos vertex position in absolute coordinate
   * @return ecc plate id starting from zero
   */
  int GetEccPlate(G4double z_pos);

  /**
   * Get ECC id corresponding to the neutrino interaction point
   * @param vertex_position vertex position in absolute coordinate
   * @return ecc id starting from zero
   */
  int GetEcc(TVector3 vertex_position);

private:

  G4ParticleGun particle_gun_;
  G4ParticleTable *particle_table_;

  B2RunAction *const p_run_action_;
  B2EventAction *const p_event_action_;
  std::reference_wrapper<B2Neut> neut_;

  B2Detector neutrino_interaction_module_;
  B2Material neutrino_interaction_material_;
  B2NeutrinoFlavor neutrino_flavor_settings_;
  bool cosmic_muons_;
  bool pencil_beam_;
  bool pencil_beam_random_direction_;
  PDG_t pencil_beam_particle_pdg_;
  TVector3 pencil_beam_position_;
  TVector3 pencil_beam_direction_;
  TVector3 random_direction_;
  double pencil_beam_momentum_;

  G4double offset_x_;
  G4double offset_y_;
  G4double offset_z_;

  TVector3 interaction_vertex_;

  bool ninja_kink_study_;
  TFile *kink_hist_file_;
  TH1D *kink_momentum_hist_;
  TH1D *kink_ax_hist_;
  TH1D *kink_ay_hist_;

};

#endif
