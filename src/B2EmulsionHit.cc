#include "B2EmulsionHit.hh"

// BOOST includes
#include <boost/log/trivial.hpp>

// Geant4 includes
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4UnitsTable.hh>

// Project includes
#include "B2Const.hh"
#include "B2Enum.hh"
#include "B2Converters.hh"

G4ThreadLocal G4Allocator<B2EmulsionHit> *B2EmulsionHitAllocator;

B2EmulsionHit::B2EmulsionHit(G4int emulsion_id, G4int track_id) :
    emulsion_id_(emulsion_id), track_id_(track_id) {

  emulsion_type_ = emulsion_id_to_emulsion_type(emulsion_id);

  plate_ = (emulsion_id_ - emulsion_type_ * DUMAX * ECCMAX * GELMAX) / (DUMAX * ECCMAX);

  ecc_ = (emulsion_id_ - emulsion_type_ * DUMAX * ECCMAX * GELMAX
          - plate_ * DUMAX * ECCMAX) / DUMAX;
  emulsion_layer_ = emulsion_id_to_emulsion_layer(emulsion_id);

  if (plate_ > GELMAX)
    throw std::invalid_argument("Error : plate id is not valid : " + std::to_string(plate_));
  if (ecc_ > ECCMAX)
    throw std::invalid_argument("Error : ecc id is not valid : " + std::to_string(ecc_));

}

G4ThreeVector B2EmulsionHit::AbsoluteToFilmPosition(G4ThreeVector pos, B2EmulsionType emulsion_type,
                                                    std::size_t plate, std::size_t ecc) {
  G4ThreeVector filmpos;
  switch (emulsion_type) {
    case kECC :
      filmpos[0] = pos[0] + 0.5 * NINJA_ECC_FILM_XY
	- NINJA_POS_X
	- NINJA_ECC_POS_X - NINJA_ECC_GAP_X * (std::floor(ecc % 3) - 1);
      filmpos[1] = pos[1] + 0.5 * NINJA_RACK_HEIGHT
	- NINJA_POS_Y
	- (103. * cm + NINJA_DESIC_THICK + NINJA_ENV_THICK)
	- NINJA_ECC_GAP_Y * (1 - std::floor(ecc / 3.));
      filmpos[2] = 0.;
      break;
    case kShifter :
      if (plate < 4) { // OSS
        filmpos[0] = pos[0] + 0.5 * NINJA_OSS_FILM_WIDTH
	  - NINJA_POS_X
	  - NINJA_ECC_POS_X - NINJA_ECC_GAP_X * (std::floor(ecc % 3) - 1);
        filmpos[1] = pos[1] + 0.5 * NINJA_RACK_HEIGHT
	  - NINJA_POS_Y
	  - (100. * cm + NINJA_OSS_ACRYL_OFFSET + NINJA_ENV_THICK)
	  - NINJA_ECC_GAP_Y * (1 - std::floor(ecc / 3.));
      } else if (plate < 14) { // Shifter
        filmpos[0] = pos[0] + 0.5 * NINJA_SHIFTER_FILM_WIDTH
	  - NINJA_POS_X
	  - NINJA_SHIFTER_POS_X;
        filmpos[1] = pos[1] + 0.5 * NINJA_SHIFTER_FILM_HEIGHT
	  - NINJA_POS_Y
	  - NINJA_SHIFTER_POS_Y
	  - NINJA_SHIFTER_FILM_GAP_Y * (1 - std::floor(ecc / 3.));
      } else { // TSS
        filmpos[0] = pos[0] + 0.5 * NINJA_SHIFTER_FILM_WIDTH
	  - NINJA_POS_X
	  - NINJA_TSS_POS_X;
        filmpos[1] = pos[1] + 0.5 * NINJA_SHIFTER_FILM_HEIGHT
	  - NINJA_POS_Y
	  - NINJA_TSS_POS_Y
	  - NINJA_SHIFTER_FILM_GAP_Y * (1 - std::floor(ecc / 3.));
      }
      filmpos[2] = 0.;
      break;
    case kSSS :
      filmpos[0] = 0.;
      filmpos[1] = pos[1] + 0.5 * NINJA_ECC_FILM_XY
	- NINJA_POS_Y
	- NINJA_ECC_POS_Y - NINJA_ECC_GAP_Y * (1. - ecc);
      filmpos[2] = pos[2] + 0.5 * NINJA_ECC_FILM_XY
                   - NINJA_POS_Z
                   - NINJA_ECC_POS_Z;
      break;

    default :
      throw std::invalid_argument("Error : emulsion id is not valid : " + std::to_string(emulsion_type));
  }

  return filmpos;
}

G4bool B2EmulsionHit::operator==(const B2EmulsionHit &rhs) const {
  return this == &rhs;
}

G4bool B2EmulsionHit::HasSameEmulsionIdAs(const B2EmulsionHit &rhs) const {
  return emulsion_id_ == rhs.emulsion_id_;
}

G4bool B2EmulsionHit::HasSameTrackIdAs(const B2EmulsionHit &rhs) const {
  return track_id_ == rhs.track_id_;
}

G4bool B2EmulsionHit::IsAfter(const B2EmulsionHit &rhs) const {
  return time_ > rhs.time_;
}

void B2EmulsionHit::Draw() const {
  G4double size;
  G4Colour colour(G4Colour::Blue());
  G4double colour_change_energy = 60 * keV; // 2 MeV/g/cm2 * 4 g/cm3 * 70 um = 56 keV
  if (energy_deposit_ < colour_change_energy) {
    size = 10. * mm + 10. * (energy_deposit_ / colour_change_energy) * mm;
    colour.SetRed(10. * (energy_deposit_ / colour_change_energy));
    colour.SetBlue(10. * (1 - energy_deposit_ / colour_change_energy));
  } else {
    size = 20. * mm;
    colour = G4Colour::Red();
  }
  G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager) {
    G4Circle circle(absolute_pre_position_);
    circle.SetScreenSize(size);
    circle.SetFillStyle(G4Circle::filled);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  } else {
    throw std::runtime_error("Error when getting the emulsion visualization manager");
  }

}

void B2EmulsionHit::Draw() {
  static_cast<const B2EmulsionHit &>(*this).Draw();
}

void B2EmulsionHit::Print() const {
  BOOST_LOG_TRIVIAL(debug) << "  Event ID  = " << event_id_ << "\n"
                           << "  Emulsion ID = " << emulsion_id_ << "\n"
                           << "  Track ID = " << track_id_ << "\n"
                           << "  Particle ID = " << particle_pdg_id_ << "\n"
                           << "  Emulsion type = " << emulsion_type_ << "\n"
                           << "  Emulsion layer = " << emulsion_layer_ << "\n"
                           << "  Plate ID = " << plate_ << "\n"
                           << "  ECC ID = " << ecc_ << "\n"
                           << "  Energy deposit = " << G4BestUnit(energy_deposit_, "Energy") << "\n"
                           << "  Quenched energy deposit = " << G4BestUnit(quenched_energy_deposit_, "Energy") << "\n"
                           << "  Absolute preposition = { X = " << absolute_pre_position_.getX()
                           << ", Y = " << absolute_pre_position_.getY()
                           << ", Z = " << absolute_pre_position_.getZ() << " }\n"
                           << "  Absolute postposition = { X = " << absolute_post_position_.getX()
                           << ", Y = " << absolute_post_position_.getY()
                           << ", Z = " << absolute_post_position_.getZ() << " }\n"
                           << "  Film preposition = { X = " << film_pre_position_.getX()
                           << ", Y = " << film_pre_position_.getY()
                           << ", Z = " << film_pre_position_.getZ() << " }\n"
                           << "  Film postposition = { X = " << film_post_position_.getX()
                           << ", Y = " << film_post_position_.getY()
                           << ", Z = " << film_post_position_.getZ() << " }\n"
                           << "  Momentum = { X = " << momentum_.getX()
                           << ", Y = " << momentum_.getY()
                           << ", Z = " << momentum_.getZ() << " }\n"
                           << "  Time = " << time_ << G4endl;
}

void B2EmulsionHit::Print() {
  static_cast<const B2EmulsionHit &>(*this).Print();
}

void B2EmulsionHit::AddEnergyDeposit(G4double energy_deposit) {
  energy_deposit_ += energy_deposit;
}

void B2EmulsionHit::AddQuenchedEnergyDeposit(G4double quenched_energy_deposit) {
  quenched_energy_deposit_ += quenched_energy_deposit;
}

void B2EmulsionHit::SetEmulsionId(G4int emulsion_id) {
  emulsion_id_ = emulsion_id;
}

void B2EmulsionHit::SetEventId(G4int event_id) {
  event_id_ = event_id;
}

void B2EmulsionHit::SetTrackId(G4int track_id) {
  track_id_ = track_id;
}

void B2EmulsionHit::SetParticlePdgId(G4int particle_pdg_id) {
  particle_pdg_id_ = particle_pdg_id;
}

void B2EmulsionHit::SetEnergyDeposit(G4double energy_deposit) {
  energy_deposit_ = energy_deposit;
}

void B2EmulsionHit::SetQuenchedEnergyDeposit(G4double quenched_energy_deposit) {
  quenched_energy_deposit_ = quenched_energy_deposit;
}

void B2EmulsionHit::SetPrePosition(const G4ThreeVector &absolute_pre_position) {
  absolute_pre_position_ = absolute_pre_position;
  film_pre_position_ = AbsoluteToFilmPosition(absolute_pre_position_, emulsion_type_, plate_, ecc_);
}

void B2EmulsionHit::SetPostPosition(const G4ThreeVector &absolute_post_position) {
  absolute_post_position_ = absolute_post_position;
  film_post_position_ = AbsoluteToFilmPosition(absolute_post_position_, emulsion_type_, plate_, ecc_);
}

void B2EmulsionHit::SetMomentum(const G4ThreeVector &momentum) {
  momentum_ = momentum;
}

void B2EmulsionHit::SetTime(G4double time) {
  time_ = time;
}

B2EmulsionType B2EmulsionHit::GetEmulsionType() const {
  return emulsion_type_;
}

std::size_t B2EmulsionHit::GetPlateId() const {
  return plate_;
}

std::size_t B2EmulsionHit::GetEccId() const {
  return ecc_;
}

B2EmulsionLayer B2EmulsionHit::GetEmulsionLayer() const {
  return emulsion_layer_;
}

G4int B2EmulsionHit::GetEventId() const {
  return event_id_;
}

G4int B2EmulsionHit::GetEmulsionId() const {
  return emulsion_id_;
}

G4int B2EmulsionHit::GetTrackId() const {
  return track_id_;
}

G4int B2EmulsionHit::GetParticlePdgId() const {
  return particle_pdg_id_;
}

G4double B2EmulsionHit::GetEnergyDeposit() const {
  return energy_deposit_;
}

G4double B2EmulsionHit::GetQuenchedEnergyDeposit() const {
  return quenched_energy_deposit_;
}

const G4ThreeVector &B2EmulsionHit::GetAbsolutePrePosition() const {
  return absolute_pre_position_;
}

const G4ThreeVector &B2EmulsionHit::GetAbsolutePostPosition() const {
  return absolute_post_position_;
}

const G4ThreeVector &B2EmulsionHit::GetFilmPrePosition() const {
  return film_pre_position_;
}

const G4ThreeVector &B2EmulsionHit::GetFilmPostPosition() const {
  return film_post_position_;
}

const G4ThreeVector &B2EmulsionHit::GetMomentum() const {
  return momentum_;
}

G4double B2EmulsionHit::GetTime() const {
  return time_;
}
