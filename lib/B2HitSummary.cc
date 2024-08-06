#include "B2HitSummary.hh"

#include <boost/log/trivial.hpp>
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2EventSummary.hh"
#include "B2Const.hh"
#include "B2Enum.hh"

B2HitSummary::B2HitSummary() :
    parent_cluster_(nullptr), parent_track_(nullptr), parent_event_(nullptr) {
  static UInt_t hit_id = 0;
  B2HitSummary::Clear("C");
  hit_id_ = ++hit_id; // NOLINT(cppcoreguidelines-prefer-member-initializer)
}

void B2HitSummary::Clear(Option_t *option) {
  hit_id_ = 0;
  bunch_ = B2_NON_INITIALIZED_VALUE;
  detector_ = B2Detector::kUnknownDetector;
  cycle_ = B2_NON_INITIALIZED_VALUE;
  view_ = B2View::kUnknownView;
  relative_position_true_.Clear(option);
  relative_position_recon_.Clear(option);
  absolute_position_true_.Clear(option);
  absolute_position_recon_.Clear(option);
  scintillator_position_.Clear(option);
  scintillator_type_ = B2ScintillatorType::kUnknownScintillatorType;
  plane_grid_ = B2GridPlane::kUnknownScintillator;
  channel_.Clear(option);
  chip_.Clear(option);
  plane_ = B2_NON_INITIALIZED_VALUE;
  slot_.Clear(option);
  time_ns_.Clear(option);
  high_gain_peu_.Clear(option);
  energy_deposit_ = B2_NON_INITIALIZED_VALUE;
  is_in_fiducial_volume_ = kFALSE;
  is_noise_hit_true_ = kFALSE;
  is_noise_hit_recon_ = kFALSE;
  veto_ = B2VetoPlane::kNotVeto;
  parent_cluster_id_ = 0;
  parent_track_id_ = 0;
  parent_cluster_.Clear(option);
  parent_track_.Clear(option);
  parent_event_.Clear(option);
  TObject::Clear(option);
}

std::ostream &operator<<(std::ostream &os, const B2HitSummary &obj) {
  os << "Hit ID = " << obj.hit_id_ << "\n";
  if (obj.bunch_ < 0)
    os << "Bunch number = non initialized\n";
  else
    os << "Bunch number = " << obj.bunch_ << "\n";
  os << "Parent Geant4 cluster ID = " << obj.parent_cluster_id_ << "\n"
     << "Parent Geant4 track ID = " << obj.parent_track_id_ << "\n"
     << "Detector = " << DETECTOR_NAMES.at((B2Detector) obj.detector_) << "\n";
  if (obj.cycle_ < 0)
    os << "Cycle (BCID) = not initialized\n";
  else
    os << "Cycle (BCID) = " << obj.cycle_ << "\n";
  os << "True relative position = " << obj.relative_position_true_ << "\n"
     << "True absolute position = " << obj.absolute_position_true_ << "\n"
     << "Reconstructed relative position = " << obj.relative_position_recon_ << "\n"
     << "Reconstructed absolute position = " << obj.absolute_position_recon_ << "\n"
     << "Scintillator type = " << SCINTILLATOR_TYPE_NAMES.at((B2ScintillatorType) obj.scintillator_type_) << "\n"
     << "Grid/Plane type = " << GRID_PLANE_NAMES.at((B2GridPlane) obj.plane_grid_) << "\n"
     << "Plane = " << obj.plane_ << "\n";
  if (obj.energy_deposit_ < 0)
    os << "Energy deposit (MeV) = non initialized\n";
  else
    os << "Energy deposit (MeV) = " << obj.energy_deposit_ << "\n";
  os << "Is in fiducial volume = " << std::boolalpha << (bool) obj.is_in_fiducial_volume_ << "\n"
     << "Is noise hit (true) = " << std::boolalpha << (bool) obj.is_noise_hit_true_ << "\n"
     << "Is noise hit (recon) = " << std::boolalpha << (bool) obj.is_noise_hit_recon_ << "\n"
     << "Veto plane = " << obj.veto_ << "\n";
  if (obj.GetDetectorId() != B2_NON_INITIALIZED_VALUE && obj.GetNumberReadouts() == 1) {
    os << "View = " << VIEW_NAMES.at((B2View) obj.view_) << "\n"
       << "Scintillator position = " << obj.scintillator_position_ << "\n"
       << "Channel = " << obj.channel_.GetValue(obj.GetSingleReadout()) << "\n";
    if (obj.chip_.GetValue(obj.GetSingleReadout()) < 0)
      os << "Chip = not initialized\n";
    else
      os << "Chip = " << obj.chip_.GetValue(obj.GetSingleReadout()) << "\n";
    os << "Slot = " << obj.slot_.GetValue(obj.GetSingleReadout()) << "\n";
    if (obj.time_ns_.GetValue(obj.GetSingleReadout()) < 0) {
      os << "Time (ns) = not initialized\n";
    } else {
      os << "Time (ns) = " << obj.time_ns_.GetValue(obj.GetSingleReadout()) << "\n";
      if (obj.time_ns_.GetError(obj.GetSingleReadout()) > 0)
        os << "Time error (ns) = " << obj.time_ns_.GetError(obj.GetSingleReadout()) << "\n";
    }
    if (obj.high_gain_peu_.GetValue(obj.GetSingleReadout()) < 0) {
      os << "High gain PEU = not initialized\n";
    } else {
      os << "High gain PEU = " << obj.high_gain_peu_.GetValue(obj.GetSingleReadout()) << "\n";
      if (obj.high_gain_peu_.GetError(obj.GetSingleReadout()) > 0)
        os << "High gain PEU error = " << obj.high_gain_peu_.GetError(obj.GetSingleReadout()) << "\n";
    }
    if (obj.low_gain_peu_.GetValue(obj.GetSingleReadout()) < 0) {
      os << "Low gain PEU = not initialized";
    } else {
      os << "Low gain PEU = " << obj.low_gain_peu_.GetValue(obj.GetSingleReadout());
      if (obj.low_gain_peu_.GetError(obj.GetSingleReadout()) > 0)
        os << "\nLow gain PEU error = " << obj.low_gain_peu_.GetError(obj.GetSingleReadout());
    }
  } else {
    os << "View = " << VIEW_NAMES.at((B2View) obj.view_) << "\n"
       << "Scintillator position (mm) = " << obj.scintillator_position_ << "\n"
       << "Channel = " << obj.channel_ << "\n"
       << "Chip = " << obj.chip_ << "\n"
       << "Slot = " << obj.slot_ << "\n"
       << "Time (ns) = " << obj.time_ns_ << "\n"
       << "High gain PEU = " << obj.high_gain_peu_ << "\n"
       << "Low gain PEU = " << obj.low_gain_peu_;
  }
  return os;
}

void B2HitSummary::SetParentCluster(const B2ClusterSummary &cluster) {
  parent_cluster_ = (TObject *) &cluster;
}


void B2HitSummary::SetParentCluster(const B2ClusterSummary *cluster) {
  parent_cluster_ = (TObject *) cluster;
}

B2ClusterSummary &B2HitSummary::GetParentCluster() {
  return const_cast<B2ClusterSummary &>(static_cast<const B2HitSummary &>(*this).GetParentCluster());
}

const B2ClusterSummary &B2HitSummary::GetParentCluster() const {
  if (parent_cluster_.IsValid() && parent_cluster_.GetObject() != nullptr)
    return *((B2ClusterSummary *) parent_cluster_.GetObject());
  else
    throw std::out_of_range("Parent cluster not set");
}

bool B2HitSummary::HasParentCluster() const {
  return parent_cluster_.IsValid() && parent_cluster_.GetObject() != nullptr;
}

void B2HitSummary::SetParentTrack(const B2TrackSummary &track) {
  parent_track_ = (TObject *) &track;
  SetParentTrackId(track.GetTrackId());
}

void B2HitSummary::SetParentTrack(const B2TrackSummary *track) {
  if (track == nullptr) {
    parent_track_.Clear("C");
    parent_track_ = nullptr;
  } else {
    parent_track_ = (TObject *) track;
    SetParentTrackId(track->GetTrackId());
  }
}

void B2HitSummary::SetParentTrackId(UInt_t track_id) {
  parent_track_id_ = track_id;
}

B2TrackSummary &B2HitSummary::GetParentTrack() {
  return const_cast<B2TrackSummary &>(static_cast<const B2HitSummary &>(*this).GetParentTrack());
}

const B2TrackSummary &B2HitSummary::GetParentTrack() const {
  if (parent_track_.IsValid() && parent_track_.GetObject() != nullptr)
    return *((B2TrackSummary *) parent_track_.GetObject());
  else
    throw std::out_of_range("Parent track not set");
}

bool B2HitSummary::HasParentTrack() const {
  return parent_track_.IsValid() && parent_track_.GetObject() != nullptr;
}

void B2HitSummary::SetParentEvent(const B2EventSummary &event) {
  parent_event_ = (TObject *) &event;
}

void B2HitSummary::SetParentEvent(const B2EventSummary *event) {
  parent_event_ = (TObject *) event;
}

B2EventSummary &B2HitSummary::GetParentEvent() {
  return const_cast<B2EventSummary &>(static_cast<const B2HitSummary &>(*this).GetParentEvent());
}

const B2EventSummary &B2HitSummary::GetParentEvent() const {
  if (parent_event_.IsValid() && parent_event_.GetObject() != nullptr)
    return *((B2EventSummary *) parent_event_.GetObject());
  else
    throw std::out_of_range("Parent event not set");
}

UInt_t B2HitSummary::GetParentClusterId() const {
  return parent_cluster_id_;
}

void B2HitSummary::SetParentClusterId(UInt_t parent_cluster_id) {
  parent_cluster_id_ = parent_cluster_id;
}

UInt_t B2HitSummary::GetNumberReadouts() const {
  return detector_to_number_readouts(static_cast<B2Detector>(detector_));
}

std::vector<B2Readout> B2HitSummary::GetReadouts() const {
  return detector_to_readouts(GetDetectorId(), GetScintillatorType(), GetPlane());
}

B2Readout B2HitSummary::GetReadout1() const {
  if (GetNumberReadouts() == 1) {
    return GetSingleReadout();
  } else {
    return detector_to_readout1(static_cast<B2Detector>(detector_),
                                static_cast<B2ScintillatorType>(scintillator_type_));
  }
}

B2Readout B2HitSummary::GetReadout2() const {
  if (GetNumberReadouts() == 1) {
    std::stringstream ss;
    ss << "Hit " << GetHitId() << " of " << DETECTOR_NAMES.at(GetDetectorId()) << " " << VIEW_NAMES.at(GetView())
       << " has only a single readout and the GetReadout2() method should not be used";
    throw std::out_of_range(ss.str());
  } else {
    return detector_to_readout2(static_cast<B2Detector>(detector_),
                                static_cast<B2ScintillatorType>(scintillator_type_));
  }
}

B2Readout B2HitSummary::GetSingleReadout() const {
  if (GetNumberReadouts() == 1) {
    return detector_to_single_readout(static_cast<B2Detector>(detector_),
                                      static_cast<B2ScintillatorType>(scintillator_type_),
                                      plane_);
  } else {
    std::stringstream ss;
    ss << "Hit " << GetHitId() << " of " << DETECTOR_NAMES.at(GetDetectorId()) << " " << VIEW_NAMES.at(GetView())
       << " has more than one readout and GetSingleReadout() method should not be used";
    throw std::out_of_range(ss.str());
  }
}

bool B2HitSummary::ReadoutHasHit(B2Readout readout) const {
  if (GetNumberReadouts() == 1) {
    return readout == GetSingleReadout();
  } else {
    const auto readout1 = GetReadout1();
    const auto readout2 = GetReadout2();
    if (readout == readout1)
      return (GetHighGainPeu().GetValue(readout1) > 0 || GetLowGainPeu().GetValue(readout1) > 0) &&
             GetSlot().GetValue(readout1) >= 0;
    else if (readout == readout2)
      return (GetHighGainPeu().GetValue(readout2) > 0 || GetLowGainPeu().GetValue(readout2) > 0) &&
             GetSlot().GetValue(readout2) >= 0;
  }
  return false;
}

B2Measurement1D B2HitSummary::GetAveragePeu() const {
  B2Measurement1D average_peu;
  if (GetNumberReadouts() == 1) {
    average_peu.SetValue(high_gain_peu_.GetValue(GetSingleReadout()));
    average_peu.SetError(high_gain_peu_.GetError(GetSingleReadout()));
  } else {
    average_peu.SetValue(0.5 * (high_gain_peu_.GetValue(GetReadout1()) +
                                high_gain_peu_.GetValue(GetReadout2())));
    average_peu.SetError(0.5 * std::sqrt(std::pow(high_gain_peu_.GetError(GetReadout1()), 2) +
                                         std::pow(high_gain_peu_.GetError(GetReadout2()), 2)));
  }
  return average_peu;
}

Int_t B2HitSummary::GetBunch() const {
  return bunch_;
}

void B2HitSummary::SetBunch(Int_t bunch) {
  B2HitSummary::bunch_ = bunch;
}

B2Detector B2HitSummary::GetDetectorId() const {
  return (B2Detector) detector_;
}

void B2HitSummary::SetDetector(B2Detector detector) {
  B2HitSummary::detector_ = detector;
}

Int_t B2HitSummary::GetCycle() const {
  return cycle_;
}

void B2HitSummary::SetCycle(Int_t cycle) {
  B2HitSummary::cycle_ = cycle;
}

const B2Position &B2HitSummary::GetTrueRelativePosition() const {
  return relative_position_true_;
}

const B2Position &B2HitSummary::GetReconRelativePosition() const {
  return relative_position_recon_;
}

void B2HitSummary::SetTrueRelativePosition(const B2Position &relative_position) {
  B2HitSummary::relative_position_true_ = relative_position;
}

void B2HitSummary::SetReconRelativePosition(const B2Position &relative_position) {
  B2HitSummary::relative_position_recon_ = relative_position;
}

void B2HitSummary::SetTrueRelativePosition(const TVector3 &relative_position) {
  B2HitSummary::relative_position_true_.SetValue(relative_position);
}

void B2HitSummary::SetReconRelativePosition(const TVector3 &relative_position) {
  B2HitSummary::relative_position_recon_.SetValue(relative_position);
}

const B2Position &B2HitSummary::GetTrueAbsolutePosition() const {
  return absolute_position_true_;
}

const B2Position &B2HitSummary::GetReconAbsolutePosition() const {
  return absolute_position_recon_;
}

void B2HitSummary::SetTrueAbsolutePosition(const B2Position &absolute_position) {
  B2HitSummary::absolute_position_true_ = absolute_position;
}

void B2HitSummary::SetReconAbsolutePosition(const B2Position &absolute_position) {
  B2HitSummary::absolute_position_recon_ = absolute_position;
}

void B2HitSummary::SetTrueAbsolutePosition(const TVector3 &absolute_position) {
  B2HitSummary::absolute_position_true_.SetValue(absolute_position);
}

void B2HitSummary::SetReconAbsolutePosition(const TVector3 &absolute_position) {
  B2HitSummary::absolute_position_recon_.SetValue(absolute_position);
}

const B2Position &B2HitSummary::GetScintillatorPosition() const {
  return scintillator_position_;
}

void B2HitSummary::SetScintillatorPosition(const B2Position &scintillator_position) {
  B2HitSummary::scintillator_position_ = scintillator_position;
}

void B2HitSummary::SetScintillatorPosition(const B2Vector3 &position) {
  B2HitSummary::scintillator_position_.SetValue(position);
}

void B2HitSummary::SetScintillatorPosition(const B2Vector3 &position, const B2Vector3 &error) {
  B2HitSummary::scintillator_position_.Set(position, error);
}

B2View B2HitSummary::GetView() const {
  return static_cast<B2View>(view_);
}

void B2HitSummary::SetView(B2View view) {
  B2HitSummary::view_ = view;
}

B2ScintillatorType B2HitSummary::GetScintillatorType() const {
  return static_cast<B2ScintillatorType>(scintillator_type_);
}

void B2HitSummary::SetScintillatorType(B2ScintillatorType scintillator_type) {
  B2HitSummary::scintillator_type_ = scintillator_type;
}

const B2DoubleReadoutI &B2HitSummary::GetChannel() const {
  return channel_;
}

Int_t B2HitSummary::GetChannel(B2Readout readout) const {
  if (ReadoutHasHit(readout))
    return channel_.GetValue(readout);
  else
    throw std::runtime_error("(GetChannel) No hit found in readout " + READOUT_NAMES.at(readout));
}

void B2HitSummary::SetChannel(const B2DoubleReadoutI &channel) {
  B2HitSummary::channel_ = channel;
}

void B2HitSummary::SetChannel(B2Readout readout, Int_t channel) {
  B2HitSummary::channel_.Set(readout, channel);
}

const B2DoubleReadoutI &B2HitSummary::GetChip() const {
  return chip_;
}

Int_t B2HitSummary::GetChip(B2Readout readout) const {
  if (ReadoutHasHit(readout))
    return chip_.GetValue(readout);
  else
    throw std::runtime_error("(GetChip) No hit found in readout " + READOUT_NAMES.at(readout));
}

void B2HitSummary::SetChip(const B2DoubleReadoutI &chip) {
  B2HitSummary::chip_ = chip;
}

void B2HitSummary::SetChip(B2Readout readout, Int_t chip) {
  B2HitSummary::chip_.Set(readout, chip);
}

const B2DoubleReadoutI &B2HitSummary::GetSlot() const {
  return slot_;
}

Int_t B2HitSummary::GetSlot(B2Readout readout) const {
  if (ReadoutHasHit(readout))
    return slot_.GetValue(readout);
  else
    throw std::runtime_error("(GetSlot) No hit found in readout " + READOUT_NAMES.at(readout));
}

void B2HitSummary::SetSlot(const B2DoubleReadoutI &slot) {
  B2HitSummary::slot_ = slot;
}

void B2HitSummary::SetSlot(B2Readout readout, Int_t slot) {
  B2HitSummary::slot_.Set(readout, slot);
}

Int_t B2HitSummary::GetPlane() const {
  return plane_;
}

void B2HitSummary::SetPlane(Int_t plane) {
  B2HitSummary::plane_ = plane;
}

const B2DoubleReadoutD &B2HitSummary::GetTimeNs() const {
  return time_ns_;
}

Double_t B2HitSummary::GetTimeNs(B2Readout readout) const {
  if (ReadoutHasHit(readout))
    return time_ns_.GetValue(readout);
  else
    throw std::runtime_error("(GetTimeNs) No hit found in readout " + READOUT_NAMES.at(readout));
}

void B2HitSummary::SetTimeNs(const B2DoubleReadoutD &time_ns) {
  B2HitSummary::time_ns_ = time_ns;
}

void B2HitSummary::SetTimeNs(B2Readout readout, Double_t time_ns) {
  B2HitSummary::time_ns_.Set(readout, time_ns);
}

void B2HitSummary::SetTimeNs(B2Readout readout, Double_t time_ns, Double_t time_ns_error) {
  B2HitSummary::time_ns_.Set(readout, time_ns, time_ns_error);
}

const B2DoubleReadoutD &B2HitSummary::GetHighGainPeu() const {
  return high_gain_peu_;
}

Double_t B2HitSummary::GetHighGainPeu(B2Readout readout) const {
  if (ReadoutHasHit(readout))
    return high_gain_peu_.GetValue(readout);
  else
    throw std::runtime_error("(GetHighGainPeu) No hit found in readout " + READOUT_NAMES.at(readout));
}

void B2HitSummary::SetHighGainPeu(const B2DoubleReadoutD &high_gain_peu) {
  B2HitSummary::high_gain_peu_ = high_gain_peu;
}

void B2HitSummary::SetHighGainPeu(B2Readout readout, Double_t high_gain_peu) {
  B2HitSummary::high_gain_peu_.Set(readout, high_gain_peu);
}

void B2HitSummary::SetHighGainPeu(B2Readout readout, Double_t high_gain_peu, Double_t error) {
  B2HitSummary::high_gain_peu_.Set(readout, high_gain_peu, error);
}

const B2DoubleReadoutD &B2HitSummary::GetLowGainPeu() const {
  return low_gain_peu_;
}

Double_t B2HitSummary::GetLowGainPeu(B2Readout readout) const {
  if (ReadoutHasHit(readout))
    return low_gain_peu_.GetValue(readout);
  else
    throw std::runtime_error("(GetLowGainPeu) No hit found in readout " + READOUT_NAMES.at(readout));
}

void B2HitSummary::SetLowGainPeu(const B2DoubleReadoutD &low_gain_peu) {
  B2HitSummary::low_gain_peu_ = low_gain_peu;
}

void B2HitSummary::SetLowGainPeu(B2Readout readout, Double_t low_gain_peu) {
  B2HitSummary::low_gain_peu_.Set(readout, low_gain_peu);
}

void B2HitSummary::SetLowGainPeu(B2Readout readout, Double_t low_gain_peu, Double_t error) {
  B2HitSummary::low_gain_peu_.Set(readout, low_gain_peu, error);
}

Double_t B2HitSummary::GetEnergyDeposit() const {
  return energy_deposit_;
}

void B2HitSummary::SetEnergyDeposit(Double_t energy_deposit) {
  B2HitSummary::energy_deposit_ = energy_deposit;
}

Bool_t B2HitSummary::GetIsInFiducialVolume() const {
  return is_in_fiducial_volume_;
}

void B2HitSummary::SetIsInFiducialVolume(Bool_t is_in_fiducial_volume) {
  B2HitSummary::is_in_fiducial_volume_ = is_in_fiducial_volume;
}

Bool_t B2HitSummary::GetIsNoiseHitTrue() const {
  return is_noise_hit_true_;
}

void B2HitSummary::SetIsNoiseHitTrue(Bool_t is_noise_hit_true) {
  B2HitSummary::is_noise_hit_true_ = is_noise_hit_true;
}

Bool_t B2HitSummary::GetIsNoiseHitRecon() const {
  return is_noise_hit_recon_;
}

void B2HitSummary::SetIsNoiseHitRecon(Bool_t is_noise_hit_recon) {
  B2HitSummary::is_noise_hit_recon_ = is_noise_hit_recon;
}

B2VetoPlane B2HitSummary::GetVeto() const {
  return static_cast<B2VetoPlane>(veto_);
}

void B2HitSummary::SetVeto(B2VetoPlane veto) {
  B2HitSummary::veto_ = veto;
}

void B2HitSummary::MergeHits(const B2HitSummary &hit, B2Readout readout) {
  if (this->GetBunch() != hit.GetBunch() ||
      this->GetCycle() != hit.GetCycle() ||
      this->GetPlane() != hit.GetPlane() ||
      this->GetNumberReadouts() == 1 ||
      hit.GetNumberReadouts() == 1) {
    BOOST_LOG_TRIVIAL(warning) << "Trying to merge non compatible hits";
  }
  this->SetScintillatorPosition(hit.GetScintillatorPosition());
  this->SetView(hit.GetView());
  auto &channel = hit.GetChannel();
  this->SetChannel(readout, channel.GetValue(readout));
  auto &slot = hit.GetSlot();
  this->SetSlot(readout, slot.GetValue(readout));
  auto &chip = hit.GetChip();
  this->SetChip(readout, chip.GetValue(readout));
  auto &time_ns = hit.GetTimeNs();
  this->SetTimeNs(readout, time_ns.GetValue(readout));
  auto &high_gain_peu = hit.GetHighGainPeu();
  this->SetHighGainPeu(readout, high_gain_peu.GetValue(readout));
  auto &low_gain_peu = hit.GetLowGainPeu();
  this->SetLowGainPeu(readout, low_gain_peu.GetValue(readout));
}

Int_t B2HitSummary::GetPlaneGrid() const {
  return plane_grid_;
}

void B2HitSummary::SetPlaneGrid(Int_t plane_grid) {
  plane_grid_ = plane_grid;
}

UInt_t B2HitSummary::GetParentTrackId() const {
  return parent_track_id_;
}

UInt_t B2HitSummary::GetHitId() const {
  return hit_id_;
}

void B2HitSummary::SetTrueTimeNs(Double_t true_time_ns) {
  true_time_ns_ = true_time_ns;
}

Double_t B2HitSummary::GetTrueTimeNs() const {
  return true_time_ns_;
}

B2Distance B2HitSummary::GetHitMppcDistance(B2DataType data_type, B2Readout readout) const {
  if (GetDetectorId() == B2Detector::kWagasciDownstream || GetDetectorId() == B2Detector::kWagasciUpstream) {
    return WgsHitMppcDistance(data_type);
  } else {
    throw std::runtime_error("Hit to MPPC distance implemented only for WAGASCI and WallMRD detectors");
  }
}

B2Time B2HitSummary::GetHitMppcTransitionTime(B2DataType data_type, B2Readout readout) const {
  if (GetDetectorId() == B2Detector::kWagasciDownstream || GetDetectorId() == B2Detector::kWagasciUpstream) {
    return WgsHitMppcTransitionTime(data_type);
  } else {
    throw std::runtime_error("Hit to MPPC distance implemented only for WAGASCI and WallMRD detectors");
  }
}

B2Distance B2HitSummary::GetHitToHitDistance(const B2HitSummary &hit, B2DataType data_type) const {
  if (hit.GetHitId() == GetHitId())
    return {0, 0};
  switch (data_type) {
    case kMonteCarlo:
      return B2Distance((hit.GetTrueAbsolutePosition() - GetTrueAbsolutePosition()).Mag());
    case kRealData:
      return B2Distance((hit.GetReconAbsolutePosition() - GetReconAbsolutePosition()).Mag());
    default:
      throw std::invalid_argument("Invalid data type: " + std::to_string(data_type));
  }
}

B2Distance B2HitSummary::WgsHitMppcDistance(B2DataType data_type) const {
  B2Measurement2D mppc;
  mppc.SetValue(GetScintillatorPosition().GetValue().XYvector());
  mppc.SetError(GetScintillatorPosition().GetError().XYvector());
  const auto type = static_cast<B2ScintillatorType>(scintillator_type_);
  switch (type) {
    case B2ScintillatorType::kVertical:
      mppc.GetValue().SetY(mppc.GetValue().Y() + 0.5 * WGS_SCINTI_BAR_LENGTH + WGS_FIBER_BUNDLE_LENGTH);
      mppc.GetError().SetY(WGS_SCINTI_LARGE);
      break;
    case B2ScintillatorType::kHorizontal:
      mppc.GetValue().SetX(mppc.GetValue().X() - (0.5 * WGS_SCINTI_BAR_LENGTH + WGS_FIBER_BUNDLE_LENGTH));
      mppc.GetError().SetX(WGS_SCINTI_LARGE);
      break;
    default :
      throw std::invalid_argument("Error : scintillator type is not valid : " + SCINTILLATOR_TYPE_NAMES.at(type));
  }

  B2Measurement2D hit;
  switch (data_type) {
    case kMonteCarlo:
      hit.SetValue(GetTrueRelativePosition().GetValue().XYvector());
      hit.SetError(GetTrueRelativePosition().GetError().XYvector());
      break;
    case kRealData:
      hit.SetValue(GetReconRelativePosition().GetValue().XYvector());
      hit.SetError(GetReconRelativePosition().GetError().XYvector());
      break;
  }

  return B2Distance((hit - mppc).Mag());
}

B2Time B2HitSummary::WgsHitMppcTransitionTime(B2DataType data_type) const {
  auto time = WgsHitMppcDistance(data_type).GetValue() / TRANS_SPEED_IN_FIBER;
  double error = B2_NON_INITIALIZED_VALUE;
  if (WgsHitMppcDistance(data_type).GetError() > 0)
    error = WgsHitMppcDistance(data_type).GetError() / TRANS_SPEED_IN_FIBER;
  return {time, error};
}

B2Distance B2HitSummary::WallMrdCalculateYPositionFromLightYield() const {
  B2Distance y_distance;
  if (ReadoutHasHit(B2Readout::kTopReadout) && ReadoutHasHit(B2Readout::kBottomReadout)) {
    const auto top_peu = GetHighGainPeu(B2Readout::kTopReadout);
    const auto bottom_peu = GetHighGainPeu(B2Readout::kBottomReadout);
    // y_distance.SetValue();
    // y_distance.SetError();
  } else {
    throw std::runtime_error("There must be a hit in both readouts to calculate the Y position");
  }
  return y_distance;
}

TVector3 B2HitSummary::GetLocalPositioninWallMrd(double posz, double posy, int slot) {

  Double_t localposz, localposy, id_section;
  //-805 <= posz <= 795 // -950 <= posy <= 850
  BOOST_LOG_TRIVIAL(debug) << "local : " << posz + 805 - slot * 200 << " " << (int) (posy + 950) / 120 << " "
                           << posy + 949 - 120 * (int) ((posy + 950) / 120);

  localposz = posz + 805 - slot * 200;
  localposy = posy + 950 - 120 * (int) ((posy + 950) / 120);

  if (localposz >= 200)
    localposz = 200;
  else if (localposz <= 0)
    localposz = 0;
  if (localposy >= 120)
    localposy = 119;
  else if (localposy <= 0)
    localposy = 0;

  id_section = (int) (posy + 950) / 120;
  return TVector3{localposy, localposz, id_section};
}

TVector3 B2HitSummary::GetLocalPositioninYASUTracker(double posy, double posx, int slot) {

  Double_t localposy = 0.;
  Double_t localposx = 0.;
  Double_t id_section = 0.;
  //-700 <= posy <= 700 // -1800 <= posx <= 0 (slot/7 == 0), 0 <= posx <= 1800 (slot/7 == 1)

  localposy = posy - 500 + (slot % 7) * 200;
  if (slot / 7 == 0) {
    if ((int) ((posx + 1800) / 120) >= 1)
      localposx = posx + 1800 - 120 * ((int) (posx + 1800) / 120);
    else
      localposx = posx + 1800;

    id_section = (int) ((posx + 1800) / 120);
  } else if (slot / 7 == 1) {
    if ((int) (posx / 120) >= 1)
      localposx = posx - 120 * ((int) (posx / 120));
    else
      localposx = posx;
    id_section = 14 - (int) (posx / 120);
  }

  if (localposy >= 200)
    localposy = 200;
  else if (localposy <= 0)
    localposy = 0;
  if (localposx >= 120)
    localposx = 119;
  else if (localposx <= 0)
    localposx = 0;

  return TVector3{localposx, localposy, id_section};
}


ClassImp(B2HitSummary)
