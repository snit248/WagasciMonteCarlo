#include "B2EmulsionSummary.hh"

#include <iostream>

#include <boost/log/trivial.hpp>

#include "B2TrackSummary.hh"
#include "B2EventSummary.hh"
#include "B2Enum.hh"

B2EmulsionSummary::B2EmulsionSummary() :
    parent_track_(nullptr),
    parent_event_(nullptr) {
  static UInt_t emulsion_track_id = 0;
  B2EmulsionSummary::Clear("C");
  emulsion_track_id_ = ++emulsion_track_id;
}

void B2EmulsionSummary::Clear(Option_t *option) {
  emulsion_track_id_ = 0;
  parent_track_.Clear(option);
  parent_track_id_ = 0;
  parent_event_.Clear(option);
  momentum_.Clear(option);
  absolute_position_.Clear(option);
  film_position_.Clear(option);
  tangent_.Clear(option);
  film_position_in_down_coordinate_.Clear(option);
  tangent_in_down_coordinate_.Clear(option);
  energy_deposit_sum_ = B2_NON_INITIALIZED_VALUE;
  energy_deposit_diff_ = 0;
  ph_up_ = B2_NON_INITIALIZED_VALUE;
  ph_down_ = B2_NON_INITIALIZED_VALUE;
  vph_up_ = B2_NON_INITIALIZED_VALUE;
  vph_down_ = B2_NON_INITIALIZED_VALUE;
  pixel_count_up_ = B2_NON_INITIALIZED_VALUE;
  pixel_count_down_ = B2_NON_INITIALIZED_VALUE;
  total_pixel_up_ = B2_NON_INITIALIZED_VALUE;
  total_pixel_down_ = B2_NON_INITIALIZED_VALUE;
  film_type_ = B2_NON_INITIALIZED_VALUE;
  ecc_ = B2_NON_INITIALIZED_VALUE;
  plate_ = B2_NON_INITIALIZED_VALUE;
  muon_track_id_ = B2_NON_INITIALIZED_VALUE;
  TObject::Clear(option);
}

std::ostream &operator<<(std::ostream &os, const B2EmulsionSummary &obj) {
  os << "Emulsion track ID = " << obj.emulsion_track_id_ << "\n"
     << "Parent Geant4 track ID = " << obj.parent_track_id_ << "\n"
     << "Momentum = " << obj.momentum_ << "\n"
     << "Absolute position (mm) = " << obj.absolute_position_ << "\n"
     << "Relative position in film (mm) = " << obj.film_position_ << "\n"
     << "Tangent = " << obj.tangent_ << "\n"
     << "Relative position in downstream film coordinate (mm)"
     << obj.film_position_in_down_coordinate_ << "\n"
     << "Tangent in downstream coordiate"
     << obj.tangent_in_down_coordinate_ << "\n";
  if (obj.energy_deposit_sum_ == B2_NON_INITIALIZED_VALUE)
    os << "Sum of energy deposit in the film (MeV) = non initialized" << "\n";
  else
    os << "Sum of energy deposit in the film (MeV) = " << obj.energy_deposit_sum_ << "\n";
  if (obj.energy_deposit_diff_ == 0)
    os << "Difference of energy deposit in the film (MeV) = non initialized (0)" << "\n";
  else
    os << "Difference of energy deposit in the film (MeV) = " << obj.energy_deposit_diff_ << "\n";
  if (obj.ph_up_ == B2_NON_INITIALIZED_VALUE)
    os << "Upstream PH = non initialized" << "\n";
  else
    os << "Upstream PH = " << obj.ph_up_ << "\n";
  if (obj.ph_down_ == B2_NON_INITIALIZED_VALUE)
    os << "Downstream PH = non initialized" << "\n";
  else
    os << "Downstream PH = " << obj.ph_down_ << "\n";
  if (obj.vph_up_ == B2_NON_INITIALIZED_VALUE)
    os << "Upstream VPH = non initialized" << "\n";
  else
    os << "Upstream VPH = " << obj.vph_up_ << "\n";
  if (obj.vph_down_ == B2_NON_INITIALIZED_VALUE)
    os << "Downstream VPH = non initialized" << "\n";
  else
    os << "Downstream VPH = " << obj.vph_down_ << "\n";
  if (obj.pixel_count_up_ == B2_NON_INITIALIZED_VALUE)
    os << "Upstream pixel count = non initialized" << "\n";
  else
    os << "Upstream pixel count = " << obj.pixel_count_up_ << "\n";
  if (obj.pixel_count_down_ == B2_NON_INITIALIZED_VALUE)
    os << "Downstream pixel count = non initialized" << "\n";
  else
    os << "Downstream pixel count = " << obj.pixel_count_down_ << "\n";
  if (obj.total_pixel_up_ == B2_NON_INITIALIZED_VALUE)
    os << "Upstream total pixel = non initialized" << "\n";
  else
    os << "Upstream total pixel = " << obj.total_pixel_up_ << "\n";
  if (obj.total_pixel_down_ == B2_NON_INITIALIZED_VALUE)
    os << "Downstream total pixel = non initialized" << "\n";
  else
    os << "Downstream total pixel = " << obj.total_pixel_down_ << "\n";

  os << "Emulsion type = " << FILMTYPE_NAMES.at((B2EmulsionType) obj.film_type_) << "\n"
     << "ECC = " << obj.ecc_ << "\n"
     << "Plate = " << obj.plate_ << "\n"
     << "Muon track ID = " << obj.muon_track_id_ << "\n";
  return os;
}

void B2EmulsionSummary::SetParentTrack(const B2TrackSummary *track) {
  if (track == nullptr) {
    parent_track_.Clear("C");
    parent_track_ = nullptr;
  } else {
    parent_track_ = (TObject *) track;
    SetParentTrackId(track->GetTrackId());
  }
}

void B2EmulsionSummary::SetParentTrack(const B2TrackSummary &track) {
  parent_track_ = (TObject *) &track;
  SetParentTrackId(track.GetTrackId());
}

B2TrackSummary &B2EmulsionSummary::GetParentTrack() {
  return const_cast<B2TrackSummary &>(static_cast<const B2EmulsionSummary &>(*this).GetParentTrack());
}

const B2TrackSummary &B2EmulsionSummary::GetParentTrack() const {
  if (parent_track_.IsValid() && parent_track_.GetObject() != nullptr)
    return *((B2TrackSummary *) parent_track_.GetObject());
  else
    throw std::out_of_range("Parent track not set");
}

void B2EmulsionSummary::SetParentTrackId(UInt_t parent_track_id) {
  parent_track_id_ = parent_track_id;
}

UInt_t B2EmulsionSummary::GetParentTrackId() const {
  return parent_track_id_;
}

void B2EmulsionSummary::SetParentEvent(const B2EventSummary *event) {
  parent_event_ = (TObject *) event;
}

void B2EmulsionSummary::SetParentEvent(const B2EventSummary &event) {
  parent_event_ = (TObject *) &event;
}

B2EventSummary &B2EmulsionSummary::GetParentEvent() {
  return const_cast<B2EventSummary &>(static_cast<const B2EmulsionSummary &>(*this).GetParentEvent());
}

const B2EventSummary &B2EmulsionSummary::GetParentEvent() const {
  if (parent_event_.IsValid() && parent_event_.GetObject() != nullptr)
    return *((B2EventSummary *) parent_event_.GetObject());
  else
    throw std::out_of_range("Parent event not set");
}

void B2EmulsionSummary::SetMomentum(const B2Momentum &momentum) {
  B2EmulsionSummary::momentum_ = momentum;
}

void B2EmulsionSummary::SetMomentum(const TVector3 &momentum) {
  B2EmulsionSummary::momentum_.SetValue(momentum);
}

const B2Momentum &B2EmulsionSummary::GetMomentum() const {
  return momentum_;
}

void B2EmulsionSummary::SetAbsolutePosition(const B2Position &absolute_position) {
  B2EmulsionSummary::absolute_position_ = absolute_position;
}

void B2EmulsionSummary::SetAbsolutePosition(const TVector3 &absolute_position) {
  B2EmulsionSummary::absolute_position_.SetValue(absolute_position);
}

const B2Position &B2EmulsionSummary::GetAbsolutePosition() const {
  return absolute_position_;
}

void B2EmulsionSummary::SetFilmPosition(const B2Position &film_position) {
  B2EmulsionSummary::film_position_ = film_position;
}

void B2EmulsionSummary::SetFilmPosition(const TVector3 &film_position) {
  B2EmulsionSummary::film_position_.SetValue(film_position);
}

const B2Position &B2EmulsionSummary::GetFilmPosition() const {
  return film_position_;
}

void B2EmulsionSummary::SetTangent(const B2Measurement3D &tangent) {
  B2EmulsionSummary::tangent_ = tangent;
}

void B2EmulsionSummary::SetTangent(const TVector3 &tangent) {
  B2EmulsionSummary::tangent_.SetValue(tangent);
}

const B2Measurement3D &B2EmulsionSummary::GetTangent() const {
  return tangent_;
}

void B2EmulsionSummary::SetFilmPositionInDownCoordinate(const B2Position &film_position_in_down_coordinate) {
  B2EmulsionSummary::film_position_in_down_coordinate_ = film_position_in_down_coordinate;
}

void B2EmulsionSummary::SetFilmPositionInDownCoordinate(const TVector3 &film_position_in_down_coordinate) {
  B2EmulsionSummary::film_position_in_down_coordinate_.SetValue(film_position_in_down_coordinate);
}

const B2Position &B2EmulsionSummary::GetFilmPositionInDownCoordinate() const {
  return film_position_in_down_coordinate_;
}

void B2EmulsionSummary::SetTangentInDownCoordinate(const B2Measurement3D &tangent_in_down_coordinate) {
  B2EmulsionSummary::tangent_in_down_coordinate_ = tangent_in_down_coordinate;
}

void B2EmulsionSummary::SetTangentInDownCoordinate(const TVector3 &tangent_in_down_coordinate) {
  B2EmulsionSummary::tangent_in_down_coordinate_.SetValue(tangent_in_down_coordinate);
}

const B2Measurement3D &B2EmulsionSummary::GetTangentInDownCoordinate() const {
  return tangent_in_down_coordinate_;
}

void B2EmulsionSummary::SetEdepSum(Double_t energy_deposit_sum) {
  B2EmulsionSummary::energy_deposit_sum_ = energy_deposit_sum;
}

Double_t B2EmulsionSummary::GetEdepSum() const {
  return energy_deposit_sum_;
}

void B2EmulsionSummary::SetEdepDiff(Double_t energy_deposit_diff) {
  B2EmulsionSummary::energy_deposit_diff_ = energy_deposit_diff;
}

Double_t B2EmulsionSummary::GetEdepDiff() const {
  return energy_deposit_diff_;
}

void B2EmulsionSummary::SetPhUp(Double_t ph_up) {
  B2EmulsionSummary::ph_up_ = ph_up;
}

Double_t B2EmulsionSummary::GetPhUp() const {
  return ph_up_;
}

void B2EmulsionSummary::SetPhDown(Double_t ph_down) {
  B2EmulsionSummary::ph_down_ = ph_down;
}

Double_t B2EmulsionSummary::GetPhDown() const {
  return ph_down_;
}

void B2EmulsionSummary::SetVphUp(Double_t vph_up) {
  B2EmulsionSummary::vph_up_ = vph_up;
}

Double_t B2EmulsionSummary::GetVphUp() const {
  return vph_up_;
}

void B2EmulsionSummary::SetVphDown(Double_t vph_down) {
  B2EmulsionSummary::vph_down_ = vph_down;
}

Double_t B2EmulsionSummary::GetVphDown() const {
  return vph_down_;
}

void B2EmulsionSummary::SetPixelCountUp(Double_t pixel_count_up) {
  B2EmulsionSummary::pixel_count_up_ = pixel_count_up;
}

Double_t B2EmulsionSummary::GetPixelCountUp() const {
  return pixel_count_up_;
}

void B2EmulsionSummary::SetPixelCountDown(Double_t pixel_count_down) {
  B2EmulsionSummary::pixel_count_down_ = pixel_count_down;
}

Double_t B2EmulsionSummary::GetPixelCountDown() const {
  return pixel_count_down_;
}

void B2EmulsionSummary::SetTotalPixelUp(Double_t total_pixel_up) {
  B2EmulsionSummary::total_pixel_up_ = total_pixel_up;
}

Double_t B2EmulsionSummary::GetTotalPixelUp() const {
  return total_pixel_up_;
}

void B2EmulsionSummary::SetTotalPixelDown(Double_t total_pixel_down) {
  B2EmulsionSummary::total_pixel_down_ = total_pixel_down;
}

Double_t B2EmulsionSummary::GetTotalPixelDown() const {
  return total_pixel_down_;
}

void B2EmulsionSummary::SetFilmType(Int_t film_type) {
  B2EmulsionSummary::film_type_ = film_type;
}

Int_t B2EmulsionSummary::GetFilmType() const {
  return film_type_;
}

void B2EmulsionSummary::SetEcc(Int_t ecc) {
  B2EmulsionSummary::ecc_ = ecc;
}

Int_t B2EmulsionSummary::GetEcc() const {
  return ecc_;
}

void B2EmulsionSummary::SetPlate(Int_t plate) {
  B2EmulsionSummary::plate_ = plate;
}

Int_t B2EmulsionSummary::GetPlate() const {
  return plate_;
}

void B2EmulsionSummary::SetMuonTrackId(Int_t muon_track_id) {
  B2EmulsionSummary::muon_track_id_ = muon_track_id;
}

Int_t B2EmulsionSummary::GetMuonTrackId() const {
  return muon_track_id_;
}

UInt_t B2EmulsionSummary::GetEmulsionTrackId() const {
  return emulsion_track_id_;
}

void B2EmulsionSummary::SetEmulsionTrackId(UInt_t emulsion_track_id) {
  emulsion_track_id_ = emulsion_track_id;
}

ClassImp(B2EmulsionSummary)
