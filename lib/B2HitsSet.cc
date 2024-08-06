//
// Created by Giorgio Pintaudi on 8/27/20.
//

#include "B2HitsSet.hh"

#include <unordered_set>
#include <TObject.h>
#include "B2Const.hh"
#include "B2HitSummary.hh"
#include "B2EventSummary.hh"
#include "B2TrackSummary.hh"
#include "B2Measurement.hh"

const hit::CardinalDirectionComparators hit::CARDINAL_DIRECTION_COMPARATORS = {
    {B2CardinalDirection::kNorthDirection, [](const hit::HitRef &left, const hit::HitRef &right) {
      return left.get().GetScintillatorPosition().GetValue().X() >
             right.get().GetScintillatorPosition().GetValue().X();
    }},
    {B2CardinalDirection::kSouthDirection, [](const hit::HitRef &left, const hit::HitRef &right) {
      return left.get().GetScintillatorPosition().GetValue().X() <
             right.get().GetScintillatorPosition().GetValue().X();
    }},
    {B2CardinalDirection::kUpstreamDirection, [](const hit::HitRef &left, const hit::HitRef &right) {
      return left.get().GetScintillatorPosition().GetValue().Z() <
             right.get().GetScintillatorPosition().GetValue().Z();
    }},
    {B2CardinalDirection::kDownstreamDirection, [](const hit::HitRef &left, const hit::HitRef &right) {
      return left.get().GetScintillatorPosition().GetValue().Z() >
             right.get().GetScintillatorPosition().GetValue().Z();
    }},
    {B2CardinalDirection::kUpDirection, [](const hit::HitRef &left, const hit::HitRef &right) {
      return left.get().GetScintillatorPosition().GetValue().Y() <
             right.get().GetScintillatorPosition().GetValue().Y();
    }},
    {B2CardinalDirection::kDownDirection, [](const hit::HitRef &left, const hit::HitRef &right) {
      return left.get().GetScintillatorPosition().GetValue().Y() >
             right.get().GetScintillatorPosition().GetValue().Y();
    }}
};

/////////////////////////////////////////////////////// B2HitIterator

B2HitSummary *B2HitsSet::B2HitIterator::Next() {
  if (iterator_ == end_)
    return nullptr;
  auto *ref = (*iterator_++).GetObject();
  return dynamic_cast<B2HitSummary *>(ref);
}

B2HitsSet::B2HitIterator::B2HitIterator(B2HitsSet &obj) :
    iterator_(obj.GetHits().begin()), end_(obj.GetHits().end()) {}

B2HitsSet::B2HitIterator::B2HitIterator(B2HitsSet *obj) :
    iterator_(obj->GetHits().begin()), end_(obj->GetHits().end()) {}

/////////////////////////////////////////////////////// B2HitConstIterator

const B2HitSummary *B2HitsSet::B2HitConstIterator::Next() {
  if (iterator_ == end_)
    return nullptr;
  auto *ref = (*iterator_++).GetObject();
  return dynamic_cast<const B2HitSummary *>(ref);
}

B2HitsSet::B2HitConstIterator::B2HitConstIterator(const B2HitsSet &obj) :
    iterator_(obj.GetHits().cbegin()), end_(obj.GetHits().cend()) {}

B2HitsSet::B2HitConstIterator::B2HitConstIterator(const B2HitsSet *obj) :
    iterator_(obj->GetHits().cbegin()), end_(obj->GetHits().cend()) {}

/////////////////////////////////////////////////////// B2HitsSet

void B2HitsSet::Clear(Option_t *option) {
  is_valid_ = kTRUE;
  parent_event_.Clear(option);
  parent_track_.Clear(option);
  parent_track_id_ = 0;
  bunch_ = B2_NON_INITIALIZED_VALUE;
  view_ = B2View::kUnknownView;
  view_ = B2Dimensionality::kUnknownDimension;
  hits_.Clear(option);
  num_hits_ = 0;
  detectors_.Reset(B2Detector::kUnknownDetector);
  angle_.Clear(option);
  view_angle_.Clear(option);
  length_.Clear(option);
  TObject::Clear(option);
}

B2HitsSet::B2HitIterator B2HitsSet::BeginHit() {
  return B2HitIterator(this);
}

B2HitsSet::B2HitConstIterator B2HitsSet::BeginHit() const {
  return B2HitConstIterator(this);
}

B2HitsSet::B2HitsSet() :
    parent_track_(nullptr),
    parent_event_(nullptr),
    detectors_(B2Detector::kNumDetectors) {
  B2HitsSet::Clear("C");
}

void B2HitsSet::SetParentTrack(const B2TrackSummary &track) {
  parent_track_ = (TObject *) &track;
  SetParentTrackId(track.GetTrackId());
}

void B2HitsSet::SetParentTrack(const B2TrackSummary *track) {
  if (track == nullptr) {
    parent_track_.Clear("C");
    parent_track_ = nullptr;
  } else {
    parent_track_ = (TObject *) track;
    SetParentTrackId(track->GetTrackId());
  }
}

void B2HitsSet::ResetParentTrack() {
  parent_track_.Clear();
  parent_track_id_ = 0;
}

void B2HitsSet::SetParentTrackId(UInt_t track_id) {
  parent_track_id_ = track_id;
}

B2TrackSummary &B2HitsSet::GetParentTrack() {
  return const_cast<B2TrackSummary &>(static_cast<const B2HitsSet &>(*this).GetParentTrack());
}

const B2TrackSummary &B2HitsSet::GetParentTrack() const {
  if (parent_track_.IsValid() && parent_track_.GetObject() != nullptr)
    return *((B2TrackSummary *) parent_track_.GetObject());
  else
    throw std::out_of_range("Parent track not set");
}

void B2HitsSet::SetParentEvent(const B2EventSummary &event) {
  parent_event_ = (TObject *) &event;
}

void B2HitsSet::SetParentEvent(const B2EventSummary *event) {
  parent_event_ = (TObject *) event;
}

B2EventSummary &B2HitsSet::GetParentEvent() {
  return const_cast<B2EventSummary &>(static_cast<const B2HitsSet &>(*this).GetParentEvent());
}

const B2EventSummary &B2HitsSet::GetParentEvent() const {
  if (parent_event_.IsValid() && parent_event_.GetObject() != nullptr)
    return *((B2EventSummary *) parent_event_.GetObject());
  else
    throw std::out_of_range("Parent event not set");
}

UInt_t B2HitsSet::GetParentTrackId() const {
  return parent_track_id_;
}


Int_t B2HitsSet::GetView() const {
  return view_;
}

void B2HitsSet::SetView(Int_t view) {
  view_ = view;
}

Int_t B2HitsSet::GetBunch() const {
  return bunch_;
}

void B2HitsSet::AddHit(const B2HitSummary &hit) {
  hits_.Add((TObject *) &hit);
  ++num_hits_;
  if (hit.GetDetectorId() >= 0 && hit.GetDetectorId() < B2Detector::kNumDetectors)
    AddDetector((B2Detector) hit.GetDetectorId());
  if (bunch_ < 0 || (hit.GetBunch() < bunch_ && hit.GetBunch() >= 0))
    bunch_ = hit.GetBunch();
}

void B2HitsSet::AddHit(const B2HitSummary *hit) {
  B2HitsSet::AddHit(*hit);
}

void B2HitsSet::AddDetector(B2Detector detector) {
  int i = 0;
  bool found = false;
  while (i < detectors_.GetSize() && !found) {
    if (detectors_.At(i) == detector)
      found = true;
    else if (detectors_.At(i) == B2_NON_INITIALIZED_VALUE)
      i = detectors_.GetSize();
    else
      ++i;
  }
  if (!found) {
    i = 0;
    while (i < detectors_.GetSize()) {
      if (detectors_.At(i) == B2_NON_INITIALIZED_VALUE) {
        detectors_[i] = detector;
        i = detectors_.GetSize();
      } else {
        ++i;
      }
    }
  }
}

B2HitSummary &B2HitsSet::GetUpstreamHit() {
  return const_cast<B2HitSummary &>(static_cast<const B2HitsSet &>(*this).GetUpstreamHit());
}

B2HitSummary &B2HitsSet::GetDownstreamHit() {
  return const_cast<B2HitSummary &>(static_cast<const B2HitsSet &>(*this).GetDownstreamHit());
}

const B2HitSummary &B2HitsSet::GetUpstreamHit() const {
  if (num_hits_ == 0) {
    throw std::out_of_range("Upstream hit not set because there are no hits!");
  }
  auto it = BeginHit();
  const B2HitSummary *upstream_hit = nullptr;
  while (auto *i = it.Next()) {
    if (!upstream_hit)
      upstream_hit = i;
    const auto i_detector = (B2Detector) i->GetDetectorId();
    const auto up_detector = (B2Detector) upstream_hit->GetDetectorId();
    if (i_detector != B2Detector::kUnknownDetector && i_detector < B2Detector::kNumDetectors &&
        up_detector != B2Detector::kUnknownDetector && up_detector < B2Detector::kNumDetectors) {
      if (i->GetScintillatorPosition().GetValue().Z() + POSITION_OFFSET_Z.at(i_detector) <
          upstream_hit->GetScintillatorPosition().GetValue().Z() + POSITION_OFFSET_Z.at(up_detector)) {
        upstream_hit = i;
      }
    }
  }
  return *upstream_hit;
}

const B2HitSummary &B2HitsSet::GetDownstreamHit() const {
  if (num_hits_ == 0) {
    throw std::out_of_range("Downstream hit not set because there are no hits!");
  }
  auto it = BeginHit();
  const B2HitSummary *downstream_hit = nullptr;
  while (auto *i = it.Next()) {
    if (!downstream_hit)
      downstream_hit = i;
    const auto i_detector = (B2Detector) i->GetDetectorId();
    const auto down_detector = (B2Detector) downstream_hit->GetDetectorId();
    if (i_detector != B2Detector::kUnknownDetector && i_detector < B2Detector::kNumDetectors &&
        down_detector != B2Detector::kUnknownDetector && down_detector < B2Detector::kNumDetectors) {
      if (i->GetScintillatorPosition().GetValue().Z() + POSITION_OFFSET_Z.at(i_detector) >
          downstream_hit->GetScintillatorPosition().GetValue().Z() + POSITION_OFFSET_Z.at(down_detector)) {
        downstream_hit = i;
      }
    }
  }
  return *downstream_hit;
}

B2HitSummary &B2HitsSet::GetFirstHit() {
  return const_cast<B2HitSummary &>(static_cast<const B2HitsSet &>(*this).GetFirstHit());
}

B2HitSummary &B2HitsSet::GetLastHit() {
  return const_cast<B2HitSummary &>(static_cast<const B2HitsSet &>(*this).GetLastHit());
}

const B2HitSummary &B2HitsSet::GetFirstHit() const {
  if (num_hits_ == 0) {
    throw std::out_of_range("First hit not set because there are no hits!");
  }
  auto it = BeginHit();
  const B2HitSummary *first_hit = nullptr;
  while (auto *i = it.Next()) {
    if (!first_hit ||
        i->GetTimeNs().GetMinimumValue() < first_hit->GetTimeNs().GetMinimumValue()) {
      first_hit = i;
    }
  }
  return *first_hit;
}

const B2HitSummary &B2HitsSet::GetLastHit() const {
  if (num_hits_ == 0) {
    throw std::out_of_range("Last hit not set because there are no hits!");
  }
  auto it = BeginHit();
  const B2HitSummary *last_hit = nullptr;
  while (auto *i = it.Next()) {
    if (!last_hit ||
        i->GetTimeNs().GetMinimumValue() > last_hit->GetTimeNs().GetMinimumValue()) {
      last_hit = i;
    }
  }
  return *last_hit;
}

std::ostream &operator<<(std::ostream &os, const B2HitsSet &obj) {
  os << "Is valid = " << std::boolalpha << (bool) obj.is_valid_ << "\n"
     << "Num hits = " << obj.num_hits_ << "\n"
     << "Parent track Geant4 ID = " << obj.parent_track_id_ << "\n"
     << "Bunch number = " << obj.bunch_ << "\n"
     << "View = " << VIEW_NAMES.at((B2View) obj.view_) << "\n"
     << "Dimension = " << DIMENSIONALITY_NAMES.at((B2Dimensionality) obj.dimensionality_) << "\n"
     << "Crossed detectors = ";
  Int_t i = 0;
  while (obj.detectors_.At(i) != B2_NON_INITIALIZED_VALUE && i < obj.detectors_.GetSize()) {
    os << DETECTOR_NAMES.at((B2Detector) obj.detectors_.At(i)) << ", ";
    ++i;
  }
  os << "\nNumber of active planes = " << obj.GetNumActivePlanes() << "\n"
     << "View angle (degrees) = " << obj.view_angle_ << "\n"
     << "Angle (degrees) = " << obj.angle_ << "\n"
     << "Length = " << obj.length_ << " mm\n"
     << "Max PEU = " << obj.GetMaxPeu() << "\n"
     << "Average PEU = " << obj.GetAveragePeu() << "\n";
  return os;
}

Int_t B2HitsSet::GetNumHits(B2View view, B2Detector detector) const {
  if (view == B2View::kUnknownView && detector == B2Detector::kUnknownDetector) {
    return num_hits_;
  } else {
    int counter = 0;
    auto it = BeginHit();
    while (const auto *hit = it.Next()) {
      auto this_view = hit->GetView();
      auto this_detector = hit->GetDetectorId();
      if ((view == B2View::kUnknownView || this_view == view) &&
          (detector == B2Detector::kUnknownDetector || this_detector == detector)) {
        ++counter;
      }
    }
    return counter;
  }
}

const TArrayI &B2HitsSet::GetDetectors() const {
  return detectors_;
}

Bool_t B2HitsSet::HasDetector(B2Detector detector) const {
  for (int i = 0; i < detectors_.GetSize(); ++i) {
    if (detector == detectors_.At(i))
      return kTRUE;
    else if (detector == B2Detector::kUnknownDetector)
      return kFALSE;
  }
  return kFALSE;
}

Int_t B2HitsSet::GetNumDetectors() const {
  Int_t counter = 0;
  for (int i = 0; i < detectors_.GetSize(); ++i) {
    if (detectors_.At(i) >= 0)
      ++counter;
    else
      return counter;
  }
  return counter;
}

B2Measurement1D B2HitsSet::GetMaxPeu() const {
  B2Measurement1D max_peu;
  auto it = BeginHit();
  max_peu.Set(0, B2_NON_INITIALIZED_VALUE);
  while (const auto *hit = it.Next()) {
    if (hit->GetHighGainPeu().GetMaximumValue() > max_peu.GetValue())
      max_peu.SetValue(hit->GetHighGainPeu().GetMaximumValue());
  }
  return max_peu;
}

B2Measurement1D B2HitsSet::GetAveragePeu() const {
  B2Measurement1D average_peu;
  auto it = BeginHit();
  average_peu.Set(0, B2_NON_INITIALIZED_VALUE);
  while (const auto *hit = it.Next()) {
    average_peu.SetValue(average_peu.GetValue() + hit->GetAveragePeu().GetValue());
  }
  if (num_hits_ > 0)
    average_peu.SetValue(average_peu.GetValue() / (Double_t) num_hits_);
  return average_peu;
}

const B2ViewAngle &B2HitsSet::GetViewAngle() const {
  return view_angle_;
}

void B2HitsSet::SetViewAngle(const B2ViewAngle &angle) {
  view_angle_ = angle;
}

const B2Angle &B2HitsSet::GetAngle() const {
  return angle_;
}

void B2HitsSet::SetAngle(const B2Angle &angle) {
  angle_ = angle;
}

const B2Measurement1D &B2HitsSet::GetLength() const {
  return length_;
}

void B2HitsSet::SetLength(const B2Measurement1D &length) {
  length_ = length;
}

void B2HitsSet::SetLength(Double_t length) {
  length_ = length;
}

Int_t B2HitsSet::GetNumActivePlanes() const {
  auto it = BeginHit();
  std::unordered_map<B2Detector, std::unordered_set<Int_t>, EnumClassHash> planes =
      {{B2Detector::kProtonModule,      std::unordered_set<Int_t>()},
       {B2Detector::kWagasciUpstream,   std::unordered_set<Int_t>()},
       {B2Detector::kWagasciDownstream, std::unordered_set<Int_t>()},
       {B2Detector::kWallMrdSouth,      std::unordered_set<Int_t>()},
       {B2Detector::kWallMrdNorth,      std::unordered_set<Int_t>()},
       {B2Detector::kBabyMind,          std::unordered_set<Int_t>()},
       {B2Detector::kYasuTracker,       std::unordered_set<Int_t>()},
       {B2Detector::kNinja,             std::unordered_set<Int_t>()},
       {B2Detector::kUnknownDetector,   std::unordered_set<Int_t>()}};
  while (const auto *hit = it.Next()) {
    planes.at((B2Detector) hit->GetDetectorId()).insert(hit->GetPlane());
  }
  Int_t num_active_planes = 0;
  for (const auto &set_of_planes : planes) {
    num_active_planes += set_of_planes.second.size();
  }
  return num_active_planes;
}

Bool_t B2HitsSet::IsValid() const {
  return is_valid_;
}

void B2HitsSet::Validate() {
  is_valid_ = kTRUE;
}

void B2HitsSet::Invalidate() {
  is_valid_ = kFALSE;
}

bool B2HitsSet::HasHit(const B2HitSummary *other) const {
  auto it = BeginHit();
  while (const auto *hit = it.Next()) {
    if (other == hit)
      return true;
  }
  return false;
}

void B2HitsSet::ClearHits() {
  hits_.Clear("C");
  num_hits_ = 0;
}

B2Dimensionality B2HitsSet::GetDimensionality() const {
  return static_cast<B2Dimensionality>(dimensionality_);
}

void B2HitsSet::SetDimensionality(B2Dimensionality dimensionality) {
  dimensionality_ = dimensionality;
}

const B2HitSummary &B2HitsSet::GetHit(UInt_t id) const {
  auto it = BeginHit();
  while (const auto *hit = it.Next()) {
    if (hit->GetHitId() == id)
      return *hit;
  }
  throw std::out_of_range("Hit not found with ID " + std::to_string(id));
}

B2HitSummary &B2HitsSet::GetHit(UInt_t id) {
  return const_cast<B2HitSummary &>(static_cast<const B2HitsSet &>(*this).GetHit(id));
}

const B2RefArray &B2HitsSet::GetHits() const {
  return hits_;
}

B2RefArray &B2HitsSet::GetHits() {
  return hits_;
}

const B2HitSummary &B2HitsSet::GetHitAlongDirection(B2CardinalDirection direction,
                                                    B2View view, B2Detector detector) const {
  auto it = BeginHit();
  std::vector<hit::HitRef> hits;
  while (const auto *hit = it.Next()) {
    const auto hit_view = hit->GetView();
    const auto hit_detector = hit->GetDetectorId();
    if ((view == B2View::kUnknownView || hit_view == view) &&
        (detector == B2Detector::kUnknownDetector || hit_detector == detector)) {
      hits.emplace_back(*hit);
    }
  }
  return *std::max_element(hits.begin(), hits.end(), hit::CARDINAL_DIRECTION_COMPARATORS.at(direction));
}

B2HitSummary &B2HitsSet::GetHitAlongDirection(B2CardinalDirection direction, B2View view, B2Detector detector) {
  return const_cast<B2HitSummary &>(static_cast<const B2HitsSet &>(*this).GetHitAlongDirection(direction, view,
                                                                                               detector));
}

bool B2HitsSet::HasParentTrack() const {
  return parent_track_id_ > 0 || parent_track_ != nullptr;
}

ClassImp(B2HitsSet)
