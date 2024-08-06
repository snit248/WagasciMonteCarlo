#include <iostream>
#include "B2EventSummary.hh"

#include "B2VertexSummary.hh"
#include "B2HitSummary.hh"
#include "B2TrackSummary.hh"
#include "B2Pdg.hh"

B2EventSummary::B2EventSummary() :
    event_id_(0), primary_vertex_(nullptr) {
  static std::atomic<UInt_t> event_id(0);
  B2EventSummary::Clear("C");
  event_id_ = ++event_id;
}

void B2EventSummary::Clear(Option_t *option) {
  primary_vertex_.Clear(option);
  event_id_ = 0;
  event_type_ = B2EventType::kUnknownEventType;
  TObject::Clear(option);
}

std::ostream &operator<<(std::ostream &os, const B2EventSummary &obj) {
  os << "Event ID = " << obj.event_id_ << "\n"
     << "Event type = " << obj.event_type_ << "\n";
  if (obj.HasPrimaryVertex()) {
    os << "Bunch number = " << obj.GetBunch() << "\n"
       << "Primary particle = " << B2Pdg::Stringify(obj.GetPrimaryParticlePdg()) << "\n"
       << "Primary particle momentum (MeV/c) = " << obj.GetPrimaryParticleMomentum() << "\n"
       << "Primary Particle energy (MeV) = " << obj.GetPrimaryParticleEnergy() << "\n"
       << "Normalization factor = " << obj.GetNormalization() << "\n"
       << "Interaction type = " << obj.GetInteractionType() << "\n"
       << "Total cross-section = " << obj.GetTotalCrossSection() << "\n";
  }
  return os;
}

void B2EventSummary::Print() const {
  std::cout << *this << std::endl;
}

void B2EventSummary::SetPrimaryVertex(B2VertexSummary &vertex) {
  primary_vertex_ = dynamic_cast<TObject *>(&vertex);
  vertex.SetParentEvent(*this);
}

void B2EventSummary::SetPrimaryVertex(B2VertexSummary *vertex) {
  SetPrimaryVertex(*vertex);
  vertex->SetParentEvent(*this);
}

const B2VertexSummary &B2EventSummary::GetPrimaryVertex() const {
  return *(B2VertexSummary *) primary_vertex_.GetObject();
}

B2VertexSummary &B2EventSummary::GetPrimaryVertex() {
  return const_cast<B2VertexSummary &>(static_cast<const B2EventSummary &>(*this).GetPrimaryVertex());
}

bool B2EventSummary::HasPrimaryVertex() const {
  return primary_vertex_.IsValid() && primary_vertex_.GetObject() != nullptr;
}

Int_t B2EventSummary::GetBunch() const {
  if (HasPrimaryVertex())
    return GetPrimaryVertex().GetBunch();
  else
    throw std::runtime_error("Primary vertex not set!");
}

const B2Momentum &B2EventSummary::GetPrimaryParticleMomentum() const {
  if (HasPrimaryVertex())
    return GetPrimaryVertex().GetMomentum();
  else
    throw std::runtime_error("Primary vertex not set!");
}

const B2Energy &B2EventSummary::GetPrimaryParticleEnergy() const {
  if (HasPrimaryVertex())
    return GetPrimaryVertex().GetTotalEnergy();
  else
    throw std::runtime_error("Primary vertex not set!");
}

Int_t B2EventSummary::GetPrimaryParticlePdg() const {
  if (HasPrimaryVertex())
    return GetPrimaryVertex().GetIncomingParticlePdg();
  else
    throw std::runtime_error("Primary vertex not set!");
}

B2EventType B2EventSummary::GetEventType() const {
  return static_cast<B2EventType>(event_type_);
}

Double_t B2EventSummary::GetNormalization() const {
  if (HasPrimaryVertex() && GetPrimaryVertex().GetNormalization() > 0)
    return GetPrimaryVertex().GetNormalization();
  else
    return normalization_;
}

void B2EventSummary::SetNormalization(Double_t normalization) {
  if (HasPrimaryVertex() && GetPrimaryVertex().GetNormalization() > 0)
    GetPrimaryVertex().SetNormalization(normalization);
  normalization_ = normalization;
}

B2InteractionMode B2EventSummary::GetInteractionType() const {
  return GetPrimaryVertex().GetInteractionType();
}

Double_t B2EventSummary::GetTotalCrossSection() const {
  if (HasPrimaryVertex())
    return GetPrimaryVertex().GetTotalCrossSection();
  else
    throw std::runtime_error("Primary vertex not set!");
}

void B2EventSummary::SetEventType(B2EventType event_type) {
  B2EventSummary::event_type_ = event_type;
}

B2HitSummary *B2EventSummary::SearchClosestHit(const TVector3 &pos, Double_t distance_cut) {
  Double_t distance = B2_WORLD_DEPTH * B2_WORLD_HEIGHT * B2_WORLD_WIDTH / 3.;
  B2HitSummary *closest_hit = nullptr;
  auto itrack = dynamic_cast<B2VertexSummary *>(primary_vertex_.GetObject())->BeginTrack();
  while (auto *track_summary = itrack.Next()) {
    auto ihit = track_summary->BeginHit();
    while (auto *hit_summary = ihit.Next()) {
      if ((hit_summary->GetTrueAbsolutePosition().GetValue() - pos).Mag() < distance)
        distance = (hit_summary->GetTrueAbsolutePosition().GetValue() - pos).Mag();
      closest_hit = hit_summary;
    }
  }
  if (distance > distance_cut)
    return nullptr;
  else
    return closest_hit;
}

UInt_t B2EventSummary::GetEventId() const {
  return event_id_;
}

ClassImp(B2EventSummary)


