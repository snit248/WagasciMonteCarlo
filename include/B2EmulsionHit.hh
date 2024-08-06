#ifndef B2EmulsionHit_h
#define B2EmulsionHit_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "B2Enum.hh"
#include "B2Const.hh"
#include "B2Measurement.hh"

/**
 * Class desicribing the emulsion hits for NINJA
 * This class controls real tracks in emulsion gel layers (with energy deposit).\n
 * We don't use this class directly in analysis (i.e. considered as "pseudo" micro tracks).\n
 * On the other hand, B2EmulsionSummary objects are used in the analysis
 * (i.e. considered as "pseudo" base tracks).
 */

class B2EmulsionHit : public G4VHit {

private:
  ///> Type of emulsion film
  B2EmulsionType emulsion_type_;
  ///> Plate ID
  std::size_t plate_;
  ///> ECC id
  std::size_t ecc_;
  ///> Emulsion gel side
  B2EmulsionLayer emulsion_layer_;
  ///> Event ID
  G4int event_id_{};
  ///> Eumlsion film overall ID
  G4int emulsion_id_;
  ///> Track ID
  G4int track_id_;
  ///> Particle PDG ID
  G4int particle_pdg_id_{};
  ///> Energy deposit
  G4double energy_deposit_{};
  ///> Quenched energy deposit
  G4double quenched_energy_deposit_{};
  ///> Absolute preposition
  G4ThreeVector absolute_pre_position_;
  ///> Absolute postposition
  G4ThreeVector absolute_post_position_;
  ///> Film preposition
  G4ThreeVector film_pre_position_;
  ///> Film postposition
  G4ThreeVector film_post_position_;
  ///> Momentum
  G4ThreeVector momentum_;
  ///> Time
  G4double time_{};
public:
  /**
   * @param emulsion_id Geant4 unique ID number of the emulsion film
   * @param track_id Geant4 track ID
   */
  B2EmulsionHit(G4int emulsion_id, G4int track_id);

  /**
   * @param rhs other hit
   * @return true if it is the same hit
   */
  G4bool operator==(const B2EmulsionHit &rhs) const;

  /**
   * @param rhs other hit
   * @return true if it is the same emulsion id
   */
  G4bool HasSameEmulsionIdAs(const B2EmulsionHit &rhs) const;

  /**
   * @param rhs other hit
   * @return true if it is the same track id
   */
  G4bool HasSameTrackIdAs(const B2EmulsionHit &rhs) const;

  /**
   * @param rhs other hit
   * @return true if it happens after the other hit
   */
  G4bool IsAfter(const B2EmulsionHit &rhs) const;

  /**
   * Convert positions in global coordinate into film coordinate
   * @param pos position in global coordinate
   * @param emulsion_type emulsion type refer B2EmulsionType enum
   * @param plate plate id
   * @param ecc ecc id
   * @return converted position in film coordinate (x/y minimum edge = 0, z = always 0)
   */
  static G4ThreeVector AbsoluteToFilmPosition(G4ThreeVector pos, B2EmulsionType emulsion_type, std::size_t plate, std::size_t ecc) ;

  // new/delete operators
  inline void *operator new(size_t);

  inline void operator delete(void *a_hit);

  void Draw() const;

  void Print() const;

  void Draw() override;

  void Print() override;

  /////////////////// Adders

  void AddEnergyDeposit(G4double energy_deposit);

  void AddQuenchedEnergyDeposit(G4double quenched_energy_deposit);

  /////////////////// Setters 

  void SetEmulsionId(G4int emulsion_id);

  void SetEventId(G4int event_id);

  void SetTrackId(G4int track_id);

  void SetParticlePdgId(G4int particle_pdg_id);

  void SetEnergyDeposit(G4double energy_deposit);

  void SetQuenchedEnergyDeposit(G4double quenched_energy_deposit);

  void SetPrePosition(const G4ThreeVector &absolute_pre_position);

  void SetPostPosition(const G4ThreeVector &absolute_post_position);

  void SetMomentum(const G4ThreeVector &momentum);

  void SetTime(G4double time);

  /////////////////// Getters

  B2EmulsionType GetEmulsionType() const;

  std::size_t GetPlateId() const;

  std::size_t GetEccId() const;

  B2EmulsionLayer GetEmulsionLayer() const;

  G4int GetEventId() const;

  G4int GetEmulsionId() const;

  G4int GetTrackId() const;

  G4int GetParticlePdgId() const;

  G4double GetEnergyDeposit() const;

  G4double GetQuenchedEnergyDeposit() const;

  const G4ThreeVector &GetAbsolutePrePosition() const;

  const G4ThreeVector &GetAbsolutePostPosition() const;

  const G4ThreeVector &GetFilmPrePosition() const;

  const G4ThreeVector &GetFilmPostPosition() const;

  const G4ThreeVector &GetMomentum() const;

  G4double GetTime() const;
};

// The following methods were added following the Geant4 suggestions.
// Refer to the Geant4 documentation for the G4VHit class    

typedef G4THitsCollection<B2EmulsionHit> B2EmulsionHitsCollection;

extern G4ThreadLocal G4Allocator<B2EmulsionHit> *B2EmulsionHitAllocator;

inline void *B2EmulsionHit::operator new(size_t) {
  if(!B2EmulsionHitAllocator) B2EmulsionHitAllocator = new G4Allocator<B2EmulsionHit>;
  return (void *) B2EmulsionHitAllocator->MallocSingle();
}

inline void B2EmulsionHit::operator delete(void *a_hit) {
  B2EmulsionHitAllocator->FreeSingle((B2EmulsionHit *) a_hit);
}

#endif
