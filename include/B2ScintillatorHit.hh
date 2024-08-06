#ifndef B2Hit_h
#define B2Hit_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "B2Enum.hh"
#include "B2Const.hh"
#include "B2Measurement.hh"
#include "B2HitSummary.hh"

/**
 * Class describing the horizontal hits for the WAGASCI, Proton Module,
 * BabyMIND detectors or the bottom hits for the WallMRD detectors.
 */
class B2ScintillatorHit : public G4VHit {
private:
  B2ScintillatorType scintillator_type_; ///> Type of scintillator
  B2HitSummary *hit_summary_{}; ///> Pointer to the B2HitSummary object representing this hit
  B2View view_; ///> Detector view
  G4int plane_{}; ///> Plane number
  G4int slot_{}; ///> Slot number
  G4int event_id_{}; ///> Event ID
  B2Detector detector_id_; ///> Detector ID
  G4int scintillator_id_; ///> Scintillator ID
  G4int track_id_{}; ///> Track ID
  G4int particle_pdg_id_{}; ///> Particle PDG ID
  G4double energy_deposit_{}; ///> Energy deposition before quenching
  G4double quenced_energy_deposit_{}; ///> Energy deposition after quenching
  B2DoubleReadoutD high_gain_peu_; ///> High gain preamp ADC
  B2DoubleReadoutD low_gain_peu_; ///> Low gain preamp ADC
  G4double time_{}; ///> absolute time of the hit inside the scintillator
  B2DoubleReadoutD delay_time_; ///> time of the hit on the MPPC
  G4ThreeVector absolute_position_; ///> Absolute position in the global coordinate system
  G4ThreeVector relative_position_; ///> Position relative to the subdetector

  void ProcessVetoHits();

  void ProcessNonVetoHits();

public:
  /**
   * @param scintillator_type type of the scintillator bar
   * @param scintillator_id Geant4 unique ID number of the scintillator bar
   * @param pos absolute position of the subdetector in the global coordinate system
   */
  B2ScintillatorHit(B2ScintillatorType scintillator_type, G4int scintillator_id, G4ThreeVector pos);

  /**
   * @param right other hit
   * @return true if is the same hit
   */
  G4bool operator==(const B2ScintillatorHit &right) const;

  /**
   * @param right other hit
   * @return true if is the same hit
   */
  G4bool HasSameScintillatorIdAs(const B2ScintillatorHit &right) const;

  /**
   * @param right other hit
   * @return true if the passed hit happened before this hit (time this hit > time right hit)
   */
  G4bool IsAfter(const B2ScintillatorHit &right) const;

  /**
   * If the "right" particle is a delta ray (an electron) the function returns always false,
   * because other wise the hits of the primary tracks would be partially hidden by the ones of the
   * delta rays
   *
   * @param right other hit
   * @return true if the passed hit has a greater energy deposit of this hit
   */
  G4bool DepositsLessEnergyThan(const B2ScintillatorHit &right) const;

  // new/delete operators
  void *operator new(std::size_t);

  void operator delete(void *a_hit);

  void Draw() const;

  void Print() const;

  void Draw() override;

  void Print() override;

  /////////////////// Adders

  void AddEnergyDeposit(G4double energy_deposit);

  void AddQuenchedEnergyDeposit(G4double quenced_energy_deposit);

  /////////////////// Setters

  void SetQuenchedEnergyDeposit(G4double quenced_energy_deposit);

  void SetEventId(G4int event_id);

  void SetHighGainPeu(G4double high_gain_peu, B2Readout readout);

  void SetLowGainPeu(G4double low_gain_peu, B2Readout readout);

  void SetTime(G4double time);

  void SetParticlePdgId(G4int particle_id);

  void SetDelayTime(G4double delay_time, B2Readout readout);

  void SetScintillatorId(G4int scintillator_id);

  void SetTrackId(G4int track_id);

  void SetB2HitSummary(B2HitSummary *hit_summary);

  /////////////////// Getters

  G4int GetScintiId() const;

  G4int GetTrackId() const;

  G4int GetParticlePdgId() const;

  G4double GetEnergyDeposit() const;

  G4double GetQuencedEnergyDeposit() const;

  G4ThreeVector GetAbsolutePosition() const;

  G4ThreeVector GetRelativePosition() const;

  G4double GetTime() const;

  G4double GetDelayTime(B2Readout readout) const;

  G4int GetEventID() const;

  B2Detector GetDetectorId() const;

  B2View GetView() const;

  G4int GetPlane() const;

  G4int GetSlot() const;

  G4double GetHighGainPeu(B2Readout readout) const;

  G4double GetLowGainPeu(B2Readout readout) const;

  B2ScintillatorType GetScintillatorType() const;

  B2HitSummary *GetB2HitSummary() const;
};

// The following methods were added following the Geant4 suggestions.
// Refer to the Geant4 documentation for the G4VHit class

typedef G4THitsCollection<B2ScintillatorHit> B2HitsCollection;

extern G4ThreadLocal G4Allocator<B2ScintillatorHit> *B2HitAllocator;

inline void *B2ScintillatorHit::operator new(std::size_t) {
  if (!B2HitAllocator) B2HitAllocator = new G4Allocator<B2ScintillatorHit>;
  return (void *) B2HitAllocator->MallocSingle();
}

inline void B2ScintillatorHit::operator delete(void *a_hit) {
  B2HitAllocator->FreeSingle((B2ScintillatorHit *) a_hit);
}

#endif
