//
// Created by Giorgio Pintaudi on 8/16/20.
//

#include "B2VertexSummary.hh"

#include <iostream>

#include "B2HitSummary.hh"
#include "B2TrackSummary.hh"
#include "B2EventSummary.hh"
#include "B2Const.hh"
#include "B2Pdg.hh"
#include "B2Enum.hh"
#include "B2McWeightCalculator.hh"

B2VertexSummary::B2VertexSummary() :
    vertex_id_(0),
    incoming_track_(nullptr),
    parent_event_(nullptr),
    closest_hit_(nullptr) {
  static std::atomic<UInt_t> vertex_id(0);
  B2VertexSummary::Clear("C");
  vertex_id_ = ++vertex_id; // NOLINT(cppcoreguidelines-prefer-member-initializer)
}

void B2VertexSummary::Clear(Option_t *option) {

  incoming_track_.Clear(option);
  outgoing_tracks_.Clear(option);
  parent_event_.Clear(option);
  closest_hit_.Clear(option);

  vertex_id_ = 0;
  bunch_ = B2_NON_INITIALIZED_VALUE;
  num_outgoing_tracks_ = outgoing_tracks_.GetEntries();
  relative_position_.Clear("C");
  absolute_position_.Clear("C");
  detector_ = B2Detector::kUnknownDetector;
  mrd_detector_ = B2Detector::kUnknownDetector;
  dimensionality_ = B2Dimensionality::kUnknownDimension;
  view_ = B2View::kUnknownView;
  is_inside_fiducial_volume_ = kFALSE;
  incoming_particle_pdg_ = 0;
  interaction_material_ = B2Material::kUnknownMaterial;
  total_energy_.Clear(option);
  momentum_.Clear(option);
  interaction_type_ = B2InteractionMode::MODE_ERROR;
  total_cross_section_ = B2_NON_INITIALIZED_VALUE;
  plane_ = 0;
  TObject::Clear(option);
}

void B2VertexSummary::SetIncomingTrack(const B2TrackSummary &track) {
  incoming_track_ = (TObject *) &track;
}

void B2VertexSummary::SetIncomingTrack(const B2TrackSummary *track) {
  incoming_track_ = (TObject *) track;
}

B2TrackSummary &B2VertexSummary::GetIncomingTrack() {
  return const_cast<B2TrackSummary &>(static_cast<const B2VertexSummary &>(*this).GetIncomingTrack());
}

const B2TrackSummary &B2VertexSummary::GetIncomingTrack() const {
  if (incoming_track_.IsValid() && incoming_track_.GetObject() != nullptr)
    return *((B2TrackSummary *) incoming_track_.GetObject());
  else
    throw std::out_of_range("Incoming track not set");
}

bool B2VertexSummary::HasIncomingTrack() const {
  if (incoming_track_.IsValid() && incoming_track_.GetObject() != nullptr)
    return true;
  return false;
}

std::ostream &operator<<(std::ostream &os, const B2VertexSummary &obj) {
  os << "Vertex ID = " << obj.vertex_id_ << "\n"
     << "Bunch number = " << obj.bunch_ << "\n"
     << "Number outgoing tracks = " << obj.num_outgoing_tracks_ << " (ID = ";
  auto it = obj.BeginTrack();
  while (const auto *track = it.Next())
    os << track->GetTrackId() << ", ";
  os << ")\n"
     << "Relative position (mm) = " << obj.relative_position_ << "\n"
     << "Absolute position (mm) = " << obj.absolute_position_ << "\n"
     << "Plane = " << obj.plane_ << "\n"
     << "View = " << VIEW_NAMES.at((B2View) obj.view_) << "\n"
     << "Dimension = " << DIMENSIONALITY_NAMES.at((B2Dimensionality) obj.dimensionality_) << "\n";
  if (DETECTOR_NAMES.count((B2Detector) obj.detector_) > 0)
    os << "Detector = " << DETECTOR_NAMES.at((B2Detector) obj.detector_) << "\n";
  if (DETECTOR_NAMES.count((B2Detector) obj.mrd_detector_) > 0)
    os << "MRD detector = " << DETECTOR_NAMES.at((B2Detector) obj.mrd_detector_) << "\n";
  os << "Is inside fiducial volume = " << obj.is_inside_fiducial_volume_ << "\n"
     << "Incoming particle = " << B2Pdg::Stringify(obj.incoming_particle_pdg_) << "\n"
     << "Interaction material = " << MATERIAL_NAMES.at((B2Material) obj.interaction_material_) << "\n"
     << "Energy (MeV) = " << obj.total_energy_ << "\n"
     << "Momentum (MeV/c) = " << obj.momentum_ << "\n"
     << "NEUT interaction code = " << obj.interaction_type_ << "\n";
  if (obj.total_cross_section_ > 0)
    os << "Total cross section = " << obj.total_cross_section_ << "x10^-38 cm^2\n";
  return os;
}

void B2VertexSummary::AddOutgoingTrack(B2TrackSummary &track) {
  outgoing_tracks_.Add((TObject *) &track);
  num_outgoing_tracks_ = outgoing_tracks_.GetEntries();
  bunch_ = track.GetBunch();
  track.SetParentVertex(this);
}

void B2VertexSummary::AddOutgoingTrack(B2TrackSummary *track) {
  B2VertexSummary::AddOutgoingTrack(*track);
}

B2TrackSummary &B2VertexSummary::GetOutgoingTrack(UInt_t id) {
  auto it = BeginTrack();
  while (auto *i = it.Next()) {
    if (i->GetTrackId() == id)
      return *i;
  }
  throw std::out_of_range("Track not found with ID " + std::to_string(id));
}

B2VertexSummary::B2VertexSummaryIterator B2VertexSummary::BeginTrack() {
  return B2VertexSummary::B2VertexSummaryIterator(this);
}

B2VertexSummary::B2VertexSummaryConstIterator B2VertexSummary::BeginTrack() const {
  return B2VertexSummary::B2VertexSummaryConstIterator(this);
}

void B2VertexSummary::SetClosestHit(const B2HitSummary &hit) {
  SetClosestHit(&hit);
}

void B2VertexSummary::SetClosestHit(const B2HitSummary *hit) {
  closest_hit_ = (TObject *) hit;
}

const B2HitSummary &B2VertexSummary::GetClosestHit() const {
  return *(B2HitSummary *) closest_hit_.GetObject();
}

const B2EventSummary & B2VertexSummary::GetParentEvent() const {
  if (parent_event_.IsValid() && parent_event_.GetObject() != nullptr)
    return *((B2EventSummary *) parent_event_.GetObject());
  else
    throw std::out_of_range("Parent event not set");
}

Int_t B2VertexSummary::GetBunch() const {
  return bunch_;
}

Long64_t B2VertexSummary::GetNumOutgoingTracks(B2View view, B2Detector detector) const {
  if (view == B2View::kUnknownView && detector == B2Detector::kUnknownDetector) {
    return num_outgoing_tracks_;
  } else {
    int num_outgoing_tracks = 0;
    auto it = BeginTrack();
    while (auto *track = it.Next()) {
      if (track->GetNumHits(view, detector) > 0)
        ++num_outgoing_tracks;
    }
    return num_outgoing_tracks;
  }
}

const B2Position &B2VertexSummary::GetRelativePosition() const {
  return relative_position_;
}

const B2Position &B2VertexSummary::GetAbsolutePosition() const {
  return absolute_position_;
}

B2Detector B2VertexSummary::GetDetector() const {
  return (B2Detector) detector_;
}

Bool_t B2VertexSummary::GetInsideFiducialVolume() const {
  return is_inside_fiducial_volume_;
}

Int_t B2VertexSummary::GetIncomingParticlePdg() const {
  return incoming_particle_pdg_;
}

Int_t B2VertexSummary::GetInteractionMaterial() const {
  return interaction_material_;
}

const B2Energy &B2VertexSummary::GetTotalEnergy() const {
  return total_energy_;
}

const B2Momentum &B2VertexSummary::GetMomentum() const {
  return momentum_;
}

B2InteractionMode B2VertexSummary::GetInteractionType() const {
  return static_cast<B2InteractionMode>(interaction_type_);
}

Double_t B2VertexSummary::GetTotalCrossSection() const {
  return total_cross_section_;
}

void B2VertexSummary::SetRelativePosition(const B2Position &relative_position) {
  B2VertexSummary::relative_position_ = relative_position;
}

void B2VertexSummary::SetAbsolutePosition(const B2Position &absolute_position) {
  B2VertexSummary::absolute_position_ = absolute_position;
}

void B2VertexSummary::SetRelativePosition(const TVector3 &relative_position) {
  B2VertexSummary::relative_position_ = relative_position;
}

void B2VertexSummary::SetAbsolutePosition(const TVector3 &absolute_position) {
  B2VertexSummary::absolute_position_ = absolute_position;
}

void B2VertexSummary::SetDetector(B2Detector detector) {
  B2VertexSummary::detector_ = detector;
}

void B2VertexSummary::SetMRDDetector(B2Detector mrddetector) {
  B2VertexSummary::mrd_detector_ = mrddetector;
}

void B2VertexSummary::SetIsInsideFiducialVolume(Bool_t is_inside_fiducial_volume) {
  B2VertexSummary::is_inside_fiducial_volume_ = is_inside_fiducial_volume;
}

void B2VertexSummary::SetIncomingParticlePdg(Int_t incoming_particle_pdg) {
  B2VertexSummary::incoming_particle_pdg_ = incoming_particle_pdg;
}

void B2VertexSummary::SetInteractionMaterial(Int_t interaction_material) {
  B2VertexSummary::interaction_material_ = interaction_material;
}

void B2VertexSummary::SetTotalEnergy(const B2Energy &total_energy) {
  B2VertexSummary::total_energy_ = total_energy;
}

void B2VertexSummary::SetTotalEnergy(Double_t total_energy) {
  B2VertexSummary::total_energy_ = total_energy;
}

void B2VertexSummary::SetMomentum(const B2Momentum &momentum) {
  B2VertexSummary::momentum_ = momentum;
}

void B2VertexSummary::SetMomentum(const TVector3 &momentum) {
  B2VertexSummary::momentum_ = momentum;
}

void B2VertexSummary::SetInteractionType(B2InteractionMode interaction_type) {
  B2VertexSummary::interaction_type_ = interaction_type;
}

void B2VertexSummary::SetTotalCrossSection(Double_t total_cross_section) {
  B2VertexSummary::total_cross_section_ = total_cross_section;
}

UInt_t B2VertexSummary::GetVertexId() const {
  return vertex_id_;
}

void B2VertexSummary::ClearTracks() {
  outgoing_tracks_.Clear("C");
  num_outgoing_tracks_ = outgoing_tracks_.GetEntries();
}

B2RefArray &B2VertexSummary::GetOutgoingTracks() {
  return outgoing_tracks_;
}

const B2RefArray &B2VertexSummary::GetOutgoingTracks() const {
  return outgoing_tracks_;
}

B2Dimensionality B2VertexSummary::GetDimensionality() const {
  return (B2Dimensionality) dimensionality_;
}

void B2VertexSummary::SetDimensionality(B2Dimensionality dimensionality) {
  dimensionality_ = dimensionality;
}

B2View B2VertexSummary::GetView() const {
  return (B2View) view_;
}

void B2VertexSummary::SetView(B2View view) {
  view_ = view;
}

B2Detector B2VertexSummary::GetMRDDetector() const {
  return (B2Detector) mrd_detector_;
}

Int_t B2VertexSummary::GetPlane() const {
  return plane_;
}

void B2VertexSummary::SetPlane(Int_t plane) {
  plane_ = plane;
}

void B2VertexSummary::SetParentEvent(const B2EventSummary &event) {
  parent_event_ = (TObject *) &event;
}

Double_t B2VertexSummary::GetMcWeight() const {
  static const B2McWeightCalculator calculator;
  return calculator.CalculateWeight(GetDetector(), GetTotalCrossSection(), GetNormalization());
}

Double_t B2VertexSummary::GetNormalization() const {
  return normalization_;
}

void B2VertexSummary::SetNormalization(Double_t normalization) {
  normalization_ = normalization;
}

B2TrackSummary *B2VertexSummary::B2VertexSummaryIterator::Next() {
  if (iterator_ == end_)
    return nullptr;
  auto *ref = (*iterator_++).GetObject();
  return dynamic_cast<B2TrackSummary *>(ref);
}

B2VertexSummary::B2VertexSummaryIterator::B2VertexSummaryIterator(B2VertexSummary &obj) :
    iterator_(obj.GetOutgoingTracks().begin()), end_(obj.GetOutgoingTracks().end()) {}

B2VertexSummary::B2VertexSummaryIterator::B2VertexSummaryIterator(B2VertexSummary *obj) :
    iterator_(obj->GetOutgoingTracks().begin()), end_(obj->GetOutgoingTracks().end()) {}

const B2TrackSummary *B2VertexSummary::B2VertexSummaryConstIterator::Next() {
  if (iterator_ == end_)
    return nullptr;
  auto *ref = (*iterator_++).GetObject();
  return dynamic_cast<const B2TrackSummary *>(ref);
}

B2VertexSummary::B2VertexSummaryConstIterator::B2VertexSummaryConstIterator(const B2VertexSummary &obj) :
    iterator_(obj.GetOutgoingTracks().begin()), end_(obj.GetOutgoingTracks().end()) {}

B2VertexSummary::B2VertexSummaryConstIterator::B2VertexSummaryConstIterator(const B2VertexSummary *obj) :
    iterator_(obj->GetOutgoingTracks().begin()), end_(obj->GetOutgoingTracks().end()) {}

ClassImp(B2VertexSummary)
