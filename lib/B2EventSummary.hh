#ifndef B2EventSummary_H
#define B2EventSummary_H

#include <TObject.h>
#include <TRef.h>

#include "B2Measurement.hh"


class B2VertexSummary;

class B2HitSummary;

/**
 * This class contains the information about the primary particle
 * (be it a neutrino or another particle).
 */
class B2EventSummary : public TObject {

public:

  /*
   * Default constructor where the members are initialized
   */
  B2EventSummary();

  /*
   * Clear the state of the object
   */
  void Clear(Option_t *option) override;

  /*
   * Print the public members to console
   */
  void Print() const;

  /**
   * @param vertex primary interaction vertex
   */
  void SetPrimaryVertex(B2VertexSummary &vertex);

  /**
   * @param vertex primary interaction vertex
   */
  void SetPrimaryVertex(B2VertexSummary *vertex);

  /**
   * @return primary interaction vertex
   */
  const B2VertexSummary &GetPrimaryVertex() const;

  /**
   * @return primary interaction vertex
   */
  B2VertexSummary &GetPrimaryVertex();

  /**
   * @return true if the primary vertex is set
   */
  bool HasPrimaryVertex() const;

  /**
   * Print all the hit members value to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2EventSummary &obj);

  /**
   * @return bunch number
   */
  Int_t GetBunch() const;

  /**
   * @return initial 3-momentum of the primary particle in MeV/c
   */
  const B2Momentum &GetPrimaryParticleMomentum() const;

  /**
   * @return initial total energy of the primary particle in MeV
   */
  const B2Energy &GetPrimaryParticleEnergy() const;

  /**
   * @return PDG ID of the primary particle
   */
  Int_t GetPrimaryParticlePdg() const;

  /**
   * @return event type (neutrino event, cosmic muon, etc...)
   */
  B2EventType GetEventType() const;

  /**
   * @return normalization of the NEUT event generator
   */
  Double_t GetNormalization() const;

  /**
   * @return NEUT interaction mode (CCQE, NC elastic scattering,
   *         coherent pion production, etc...)
   */
  B2InteractionMode GetInteractionType() const;

  /**
   * @return cross section of the interaction in 10^-38 cm^2
   */
  Double_t GetTotalCrossSection() const;

  /**
   * @param event_type event type (neutrino event, cosmic muon, etc...)
   */
  void SetEventType(B2EventType event_type);

  /**
   * @param normalization JNUBEAM normalization of the event
   */
  void SetNormalization(Double_t normalization);

  /**
   * @return unique event ID
   */
  UInt_t GetEventId() const;

  /**
   * Search for the closest hit to the vertex position
   * @param pos vertex absolute position
   * @param distance_cut maximum distance allowed between the hit and pos
   * @return closest hit (nullptr in case of failure)
   */
  B2HitSummary *SearchClosestHit(const TVector3 &pos, Double_t distance_cut);

private:

  ///> Event ID
  UInt_t event_id_;
  ///> Bunch number
  Int_t bunch_{}; // TODO to remove
  ///> Momentum of the primary particle
  B2Momentum primary_particle_momentum_; // TODO to remove
  ///> Energy of the primary particle
  B2Energy primary_particle_energy_; // TODO to remove
  ///> Primary particle PDG ID
  Int_t primary_particle_pdg_{}; // TODO to remove
  ///> Type of event: neutrino event, sand muon, cosmic particle, etc...
  Int_t event_type_{};
  ///> normalization constant (used only in the Monte Carlo to reweight the interaction probability)
  Double_t normalization_{}; // TODO to remove
  ///> interaction type (used only in the Monte Carlo). Same as the NEUT interaction mode. Refer to the
  // B2InteractionMode enum.
  Int_t interaction_type_{}; // TODO to remove
  ///> Total cross section of the interaction type (used only in the Monte Carlo).
  Double_t total_cross_section_{}; // TODO to remove
  ///> true if the event is fully contained inside the detectors
  Bool_t is_fully_contained_{}; // TODO to remove
  ///> TRef to the primary vertex
  TRef primary_vertex_;

ClassDefOverride(B2EventSummary, 4) // DST Summary of event
};

#endif // B2EventSummary_H

