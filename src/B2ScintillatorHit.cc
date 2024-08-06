#include "B2ScintillatorHit.hh"

// System includes
#include <fstream>

// BOOST includes
#include <boost/log/trivial.hpp>

// Geant4 includes
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4UnitsTable.hh>
#include <utility>

// Project includes
#include "B2Const.hh"
#include "B2Pdg.hh"
#include "B2Enum.hh"
#include "B2Converters.hh"
#include "B2Dimension.hh"

G4ThreadLocal G4Allocator<B2ScintillatorHit> *B2HitAllocator;

void B2ScintillatorHit::ProcessNonVetoHits() {

  view_ = (scintillator_type_ == B2ScintillatorType::kVertical) ?
          B2View::kTopView : B2View::kSideView;
  plane_ = (scintillator_id_ - detector_id_ * MAX_NUM_PLANES * MAX_NUM_CHANNELS) / MAX_NUM_CHANNELS;
  slot_ = scintillator_id_ - detector_id_ * MAX_NUM_PLANES * MAX_NUM_CHANNELS - plane_ * MAX_NUM_CHANNELS;

  if (slot_ > (G4int) MAX_NUM_CHANNELS)
    throw std::invalid_argument("Error : slot number is not valid : " + std::to_string(slot_));
  if (plane_ > (G4int) MAX_NUM_PLANES)
    throw std::invalid_argument("Error : plane number is not valid " + std::to_string(plane_));

  switch (detector_id_) {
    case B2Detector::kProtonModule: {
      relative_position_.setX(absolute_position_.getX() - PROTON_MODULE_POS_X);
      relative_position_.setY(absolute_position_.getY() - PROTON_MODULE_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - PROTON_MODULE_POS_Z);
      break;
    }
    case B2Detector::kWagasciUpstream: {
      relative_position_.setX(absolute_position_.getX() - WAGASCI_UPSTREAM_POS_X);
      relative_position_.setY(absolute_position_.getY() - WAGASCI_UPSTREAM_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - WAGASCI_UPSTREAM_POS_Z);
      break;
    }
    case B2Detector::kWagasciDownstream: {
      relative_position_.setX(absolute_position_.getX() - WAGASCI_DOWNSTREAM_POS_X);
      relative_position_.setY(absolute_position_.getY() - WAGASCI_DOWNSTREAM_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - WAGASCI_DOWNSTREAM_POS_Z);
      break;
    }
    case B2Detector::kWallMrdSouth: {
      relative_position_.setX(absolute_position_.getX() - WALLMRD_SOUTH_POS_X);
      relative_position_.setY(absolute_position_.getY() - WALLMRD_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - WALLMRD_SOUTH_POS_Z);
      break;
    }
    case B2Detector::kWallMrdNorth: {
      relative_position_.setX(absolute_position_.getX() - WALLMRD_NORTH_POS_X);
      relative_position_.setY(absolute_position_.getY() - WALLMRD_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - WALLMRD_NORTH_POS_Z);
      break;
    }
    case B2Detector::kBabyMind: {
      relative_position_.setX(absolute_position_.getX() - BABYMIND_POS_X);
      relative_position_.setY(absolute_position_.getY() - BABYMIND_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - BABYMIND_POS_Z);
      break;
    }
    case B2Detector::kYasuTracker: {
      relative_position_.setX(absolute_position_.getX() - BABYMIND_POS_X);
      relative_position_.setY(absolute_position_.getY() - BABYMIND_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - BABYMIND_POS_Z);
      scintillator_type_ = B2Dimension::GetScintillatorTypeYasu(slot_);
      break;
    }
    case B2Detector::kNinja: {
      relative_position_.setX(absolute_position_.getX() - NINJA_POS_X - NINJA_TRACKER_POS_X);
      relative_position_.setY(absolute_position_.getY() - NINJA_POS_Y - NINJA_TRACKER_POS_Y);
      relative_position_.setZ(absolute_position_.getZ() - NINJA_POS_Z - NINJA_TRACKER_POS_Z);
      break;
    }
    default:
      throw std::invalid_argument("Error : detector ID is not valid : " +
                                  std::to_string(detector_id_));
  }
}

void B2ScintillatorHit::ProcessVetoHits() {
  if (detector_id_ != B2Detector::kProtonModule) {
    throw std::invalid_argument("Detector " + std::to_string(detector_id_) +
                                " does not have veto planes!");
  }
  plane_ = (scintillator_id_ - detector_id_ * MAX_NUM_PLANES * MAX_NUM_CHANNELS) /
           MAX_NUM_CHANNELS + PM_NUM_TRACKING_PLANES + PM_NUM_FRONT_VETO_PLANES;
  slot_ = scintillator_id_ - detector_id_ * MAX_NUM_PLANES * MAX_NUM_CHANNELS -
          (plane_ - PM_NUM_TRACKING_PLANES - PM_NUM_FRONT_VETO_PLANES) * MAX_NUM_CHANNELS;
  if (plane_ == 19 || plane_ == 21) {
    view_ = B2View::kTopView;
  } else if (plane_ == 18 || plane_ == 20) {
    view_ = B2View::kSideView;
  } else {
    throw std::invalid_argument("Error : VETO plane is not valid : " +
                                std::to_string(plane_));
  }
  relative_position_.setX(absolute_position_.getX() - PROTON_MODULE_POS_X);
  relative_position_.setY(absolute_position_.getY() - PROTON_MODULE_POS_Y);
  relative_position_.setZ(absolute_position_.getZ() - PROTON_MODULE_POS_Z);
}

B2ScintillatorHit::B2ScintillatorHit(B2ScintillatorType scintillator_type, G4int scintillator_id, G4ThreeVector pos) :
    scintillator_type_(scintillator_type),
    view_(B2View::kUnknownView),
    scintillator_id_(scintillator_id),
    absolute_position_(std::move(pos)) {
  detector_id_ = scinti_id_to_detector_id(scintillator_id_);
  if (scintillator_type_ == B2ScintillatorType::kVeto) {
    ProcessVetoHits();
  } else {
    ProcessNonVetoHits();
  }
}

G4bool B2ScintillatorHit::operator==(const B2ScintillatorHit &rhs) const {
  return this == &rhs;
}

G4bool B2ScintillatorHit::HasSameScintillatorIdAs(const B2ScintillatorHit &right) const {
  return scintillator_id_ == right.scintillator_id_;
}

G4bool B2ScintillatorHit::IsAfter(const B2ScintillatorHit &right) const {
  return time_ > right.time_;
}

G4bool B2ScintillatorHit::DepositsLessEnergyThan(const B2ScintillatorHit &right) const {
  if (particle_pdg_id_ == PDG_t::kElectron)
    return true;
  else if (right.particle_pdg_id_ == PDG_t::kElectron)
    return false;
  return energy_deposit_ < right.energy_deposit_;
}

void B2ScintillatorHit::Draw() const {
  G4double size;
  G4Colour colour(G4Colour::Blue());
  if (energy_deposit_ < 10 * MeV) {
    size = 5 * cm + 0.5 * (energy_deposit_) * cm / MeV;
    colour.SetRed(0.1 * energy_deposit_ / MeV);
    colour.SetBlue(1 - 0.1 * energy_deposit_ / MeV);
  } else {
    size = 10 * cm;
    colour = G4Colour::Red();
  }
  G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager) {
    G4Circle circle(absolute_position_);
    circle.SetScreenSize(size);
    circle.SetFillStyle(G4Circle::filled);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  } else {
    throw std::runtime_error("Error when getting the visualization manager");
  }
}

void B2ScintillatorHit::Draw() {
  static_cast<const B2ScintillatorHit &>(*this).Draw();
}

void B2ScintillatorHit::Print() const {
  BOOST_LOG_TRIVIAL(debug) << "  Event ID = " << event_id_ << "\n"
                           << "  Detector ID = " << detector_id_ << "\n"
                           << "  Scintillator ID = " << scintillator_id_ << "\n"
                           << "  Track ID = " << track_id_ << "\n"
                           << "  Particle ID = " << particle_pdg_id_ << "\n"
                           << "  Scintillator type = " << scintillator_type_ << "\n"
                           << "  View = " << view_ << "\n"
                           << "  Plane = " << plane_ << "\n"
                           << "  Slot = " << slot_ << "\n"
                           << "  Energy deposit = " << G4BestUnit(energy_deposit_, "Energy") << "\n"
                           << "  Quenched energy deposit = " << G4BestUnit(quenced_energy_deposit_, "Energy") << "\n"
                           << "  High gain PEU = " << high_gain_peu_ << "\n"
                           << "  Low gain PEU = " << low_gain_peu_ << "\n"
                           << "  Time = " << time_ << "\n"
                           << "  Delay time = " << delay_time_ << "\n"
                           << "  Absolute position { X = " << absolute_position_.getX()
                           << ", Y = " << absolute_position_.getY()
                           << ", Z = " << absolute_position_.getZ() << "}" << "\n"
                           << "  Relative position { X = " << relative_position_.getX()
                           << ", Y = " << relative_position_.getY()
                           << ", Z = " << relative_position_.getZ() << "}" << G4endl;
}

void B2ScintillatorHit::Print() {
  static_cast<const B2ScintillatorHit &>(*this).Print();
}

void B2ScintillatorHit::AddEnergyDeposit(G4double energy_deposit) {
  energy_deposit_ += energy_deposit;
}

void B2ScintillatorHit::AddQuenchedEnergyDeposit(G4double quenced_energy_deposit) {
  quenced_energy_deposit_ += quenced_energy_deposit;
}

void B2ScintillatorHit::SetQuenchedEnergyDeposit(G4double quenced_energy_deposit) {
  quenced_energy_deposit_ = quenced_energy_deposit;
}

void B2ScintillatorHit::SetEventId(G4int event_id) {
  event_id_ = event_id;
}

void B2ScintillatorHit::SetHighGainPeu(G4double high_gain_peu, B2Readout readout) {
  high_gain_peu_.Set(readout, high_gain_peu);
}

void B2ScintillatorHit::SetLowGainPeu(G4double low_gain_peu, B2Readout readout) {
  low_gain_peu_.Set(readout, low_gain_peu);
}

void B2ScintillatorHit::SetTime(G4double time) {
  time_ = time;
}

void B2ScintillatorHit::SetParticlePdgId(G4int particle_id) {
  particle_pdg_id_ = particle_id;
}

void B2ScintillatorHit::SetDelayTime(G4double delay_time, B2Readout readout) {
  delay_time_.Set(readout, delay_time);
}

void B2ScintillatorHit::SetScintillatorId(G4int scintillator_id) {
  scintillator_id_ = scintillator_id;
}

void B2ScintillatorHit::SetTrackId(G4int track_id) {
  track_id_ = track_id;
}

G4int B2ScintillatorHit::GetScintiId() const {
  return scintillator_id_;
}

G4int B2ScintillatorHit::GetTrackId() const {
  return track_id_;
}

G4int B2ScintillatorHit::GetParticlePdgId() const {
  return particle_pdg_id_;
}

G4double B2ScintillatorHit::GetEnergyDeposit() const {
  return energy_deposit_;
}

G4double B2ScintillatorHit::GetQuencedEnergyDeposit() const {
  return quenced_energy_deposit_;
}

G4ThreeVector B2ScintillatorHit::GetAbsolutePosition() const {
  return absolute_position_;
}

G4ThreeVector B2ScintillatorHit::GetRelativePosition() const {
  return relative_position_;
}

G4double B2ScintillatorHit::GetTime() const {
  return time_;
}

G4double B2ScintillatorHit::GetDelayTime(B2Readout readout) const {
  return delay_time_.GetValue(readout);
}

G4int B2ScintillatorHit::GetEventID() const {
  return event_id_;
}

B2Detector B2ScintillatorHit::GetDetectorId() const {
  return detector_id_;
}

B2View B2ScintillatorHit::GetView() const {
  return view_;
}

G4int B2ScintillatorHit::GetPlane() const {
  return plane_;
}

G4int B2ScintillatorHit::GetSlot() const {
  return slot_;
}

G4double B2ScintillatorHit::GetHighGainPeu(B2Readout readout) const {
  return high_gain_peu_.GetValue(readout);
}

G4double B2ScintillatorHit::GetLowGainPeu(B2Readout readout) const {
  return low_gain_peu_.GetValue(readout);
}

B2ScintillatorType B2ScintillatorHit::GetScintillatorType() const {
  return scintillator_type_;
}

void B2ScintillatorHit::SetB2HitSummary(B2HitSummary *hit_summary) {
  hit_summary_ = hit_summary;
}

B2HitSummary *B2ScintillatorHit::GetB2HitSummary() const {
  return hit_summary_;
}
