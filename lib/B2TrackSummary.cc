//
// Created by Giorgio Pintaudi on 8/16/20.
//

#include "B2TrackSummary.hh"

#include <boost/log/trivial.hpp>

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2Pdg.hh"
#include "B2VertexSummary.hh"

B2TrackSummary::B2TrackSummary() : B2HitsSet() {
  B2TrackSummary::Clear("C");
}

void B2TrackSummary::Clear(Option_t *option) {
  clusters_.Clear(option);
  num_clusters_ = (Int_t) clusters_.GetEntries();
  track_id_ = 0;
  parent_vertex_.Clear(option);
  total_energy_.Clear(option);
  initial_momentum_.Clear(option);
  initial_absolute_momentum_.Clear(option);
  initial_position_.Clear(option);
  initial_direction_.Clear(option);
  final_momentum_.Clear(option);
  final_absolute_momentum_.Clear(option);
  final_position_.Clear(option);
  final_direction_.Clear(option);
  particle_pdg_ = 0;
  match_mrd_ = 0;
  stop_mrd_ = 0;
  negative_log_likelihood_minus_ = 0;
  negative_log_likelihood_plus_ = 0;
  track_length_total_ = 0;
  type_ = B2TrackType::kUnknownTrackType;
  primary_type_ = B2PrimaryTrackType::kUnknownPrimaryTrackType;
  secondary_type_ = B2SecondaryTrackType::kUnknownSecondaryTrackType;
  mucl_pm_ = 0.;
  mucl_uwg_ = 0.;
  mucl_dwg_ = 0.;
  B2HitsSet::Clear(option);
}

std::ostream &operator<<(std::ostream &os, const B2TrackSummary &obj) {
  os << "Geant4 Track ID = " << obj.track_id_ << "\n"
     << "Number of clusters = " << obj.num_clusters_ << "\n"
     << "Initial total energy = " << obj.total_energy_ << " MeV\n"
     << "Initial kinetic energy = " << obj.kinetic_energy_ << " MeV\n"
     << "Particle mass = " << obj.mass_ << " MeV/c^2\n"
     << "Initial momentum (MeV/c) = " << obj.initial_momentum_ << "\n"
     << "Initial absolute momentum = " << obj.initial_absolute_momentum_ << " MeV\n"
     << "Initial position (mm) = " << obj.initial_position_ << "\n"
     << "Initial direction = " << obj.initial_direction_ << "\n"
     << "Final momentum (MeV/c) = " << obj.final_momentum_ << "\n"
     << "Final absolute momentum = " << obj.final_absolute_momentum_ << " MeV\n"
     << "Final position (mm) = " << obj.final_position_ << "\n"
     << "Final direction = " << obj.final_direction_ << "\n";
  if (TRACKED_PARTICLE_TYPE_NAMES.count(static_cast<B2TrackType>(obj.type_)) > 0)
    os << "Type of tracked particle = "
       << TRACKED_PARTICLE_TYPE_NAMES.at(static_cast<B2TrackType>(obj.type_)) << "\n";
  else
    os << "Type of tracked particle = " << obj.type_ << "\n";
  if (PRIMARY_TRACK_TYPE_NAMES.count(static_cast<B2PrimaryTrackType>(obj.primary_type_)) > 0)
    os << "Type of primary track = "
       << PRIMARY_TRACK_TYPE_NAMES.at(static_cast<B2PrimaryTrackType>(obj.primary_type_)) << "\n";
  else
    os << "Type of primary track = " << obj.primary_type_ << "\n";
  if (SECONDARY_TRACK_TYPE_NAMES.count(static_cast<B2SecondaryTrackType>(obj.secondary_type_)) > 0)
    os << "Type of secondary track = "
       << SECONDARY_TRACK_TYPE_NAMES.at(static_cast<B2SecondaryTrackType>(obj.secondary_type_)) << "\n";
  else
    os << "Type of secondary track = " << obj.secondary_type_ << "\n";
  os << "Particle = " << B2Pdg::Stringify(obj.particle_pdg_) << "\n";
  os << static_cast<const B2HitsSet &>(obj);
  return os;
}

void B2TrackSummary::AddHit(B2HitSummary &hit) {
  B2HitsSet::AddHit(hit);
  hit.SetParentTrack(this);
  hit.SetParentTrackId(track_id_);
}

void B2TrackSummary::AddHit(const B2HitSummary &hit) {
  B2HitsSet::AddHit(hit);
}

void B2TrackSummary::AddHit(B2HitSummary *hit) {
  B2TrackSummary::AddHit(*hit);
}

void B2TrackSummary::AddHit(const B2HitSummary *hit) {
  B2HitsSet::AddHit(*hit);
}

void B2TrackSummary::AddCluster(B2ClusterSummary &cluster, Bool_t add_hits) {
  clusters_.Add((TObject *) &cluster);
  ++num_clusters_;
  auto it = cluster.BeginHit();
  if (add_hits) {
    while (auto *i = it.Next()) {
      if (!B2TrackSummary::HasHit(i))
        B2TrackSummary::AddHit(i);
    }
  }
  cluster.SetParentTrack(this);
  cluster.SetParentTrackId(track_id_);
}

void B2TrackSummary::AddCluster(B2ClusterSummary *cluster, Bool_t add_hits) {
  B2TrackSummary::AddCluster(*cluster, add_hits);
}

void B2TrackSummary::ClearClusters() {
  clusters_.Clear("C");
  num_clusters_ = (Int_t) clusters_.GetEntries();
}

const B2ClusterSummary &B2TrackSummary::GetCluster(UInt_t id) const {
  auto it = BeginCluster();
  while (const auto *i = it.Next()) {
    if (i->GetClusterId() == id)
      return *i;
  }
  throw std::out_of_range("Cluster not found with ID " + std::to_string(id));
}

B2ClusterSummary &B2TrackSummary::GetCluster(UInt_t id) {
  return const_cast<B2ClusterSummary &>(static_cast<const B2TrackSummary &>(*this).GetCluster(id));
}

B2TrackSummary::B2ClusterIterator B2TrackSummary::BeginCluster() {
  return B2ClusterIterator(this);
}

B2TrackSummary::B2ClusterConstIterator B2TrackSummary::BeginCluster() const {
  return B2ClusterConstIterator(this);
}

void B2TrackSummary::SetParentVertex(const B2VertexSummary &vertex) {
  parent_vertex_ = (TObject *) &vertex;
}

void B2TrackSummary::SetParentVertex(const B2VertexSummary *vertex) {
  parent_vertex_ = (TObject *) vertex;
}

B2VertexSummary &B2TrackSummary::GetParentVertex() {
  return const_cast<B2VertexSummary &>(static_cast<const B2TrackSummary &>(*this).GetParentVertex());
}

const B2VertexSummary &B2TrackSummary::GetParentVertex() const {
  if (parent_vertex_.IsValid() && parent_vertex_.GetObject() != nullptr)
    return *((B2VertexSummary *) parent_vertex_.GetObject());
  else
    throw std::out_of_range("Parent vertex not set");
}

UInt_t B2TrackSummary::GetTrackId() const {
  return track_id_;
}

void B2TrackSummary::SetTrackId(UInt_t track_id) {
  track_id_ = track_id;
}

bool B2TrackSummary::HasCluster(UInt_t id) const {
  auto it = BeginCluster();
  while (const auto *i = it.Next()) {
    if (i->GetClusterId() == id)
      return true;
  }
  return false;
}

const B2Energy &B2TrackSummary::GetMass() const {
  return mass_;
}

void B2TrackSummary::SetMass(const B2Energy &mass) {
  mass_ = mass;
}

void B2TrackSummary::SetMass(Double_t mass) {
  mass_ = mass;
}

const B2Energy &B2TrackSummary::GetTotalEnergy() const {
  return total_energy_;
}

void B2TrackSummary::SetTotalEnergy(const B2Energy &total_energy) {
  total_energy_ = total_energy;
}

void B2TrackSummary::SetTotalEnergy(Double_t total_energy) {
  total_energy_ = total_energy;
}

const B2Energy &B2TrackSummary::GetKineticEnergy() const {
  return kinetic_energy_;
}

void B2TrackSummary::SetKineticEnergy(const B2Energy &kinetic_energy) {
  kinetic_energy_ = kinetic_energy;
}

void B2TrackSummary::SetKineticEnergy(Double_t kinetic_energy) {
  kinetic_energy_ = kinetic_energy;
}

B2Detector B2TrackSummary::GetInitialDetector() const {
  return GetParentVertex().GetDetector();
}

const B2Momentum &B2TrackSummary::GetInitialMomentum() const {
  return initial_momentum_;
}

void B2TrackSummary::SetInitialMomentum(const B2Momentum &initial_momentum) {
  initial_momentum_ = initial_momentum;
}

void B2TrackSummary::SetInitialMomentum(const TVector3 &initial_momentum) {
  initial_momentum_ = initial_momentum;
}

const B2Measurement1D &B2TrackSummary::GetInitialAbsoluteMomentum() const {
  return initial_absolute_momentum_;
}

void B2TrackSummary::SetInitialAbsoluteMomentum(const B2Measurement1D &initial_absolute_momentum) {
  initial_absolute_momentum_ = initial_absolute_momentum;
}


void B2TrackSummary::SetInitialAbsoluteMomentum(Double_t initial_absolute_momentum) {
  initial_absolute_momentum_ = initial_absolute_momentum;
}

const B2Position &B2TrackSummary::GetInitialPosition() const {
  return initial_position_;
}

void B2TrackSummary::SetInitialPosition(const B2Position &initial_position) {
  initial_position_ = initial_position;
}

void B2TrackSummary::SetInitialPosition(const TVector3 &initial_position) {
  initial_position_ = initial_position;
}

const B2Direction &B2TrackSummary::GetInitialDirection() const {
  return initial_direction_;
}

void B2TrackSummary::SetInitialDirection(const B2Direction &initial_direction) {
  initial_direction_ = initial_direction;
}

void B2TrackSummary::SetInitialDirection(const TVector3 &initial_direction) {
  initial_direction_ = initial_direction;
}

B2Detector B2TrackSummary::GetFinalDetector() const {
  if (GetStopMrd() >= 0)
    return GetStopMrd();
  else
    return GetMatchMrd();
}

const B2Momentum &B2TrackSummary::GetFinalMomentum() const {
  return final_momentum_;
}

void B2TrackSummary::SetFinalMomentum(const B2Momentum &final_momentum) {
  final_momentum_ = final_momentum;
}

void B2TrackSummary::SetFinalMomentum(const TVector3 &final_momentum) {
  final_momentum_ = final_momentum;
}

const B2Measurement1D &B2TrackSummary::GetFinalAbsoluteMomentum() const {
  return final_absolute_momentum_;
}

void B2TrackSummary::SetFinalAbsoluteMomentum(const B2Measurement1D &final_absolute_momentum) {
  final_absolute_momentum_ = final_absolute_momentum;
}

void B2TrackSummary::SetFinalAbsoluteMomentum(Double_t final_absolute_momentum) {
  final_absolute_momentum_ = final_absolute_momentum;
}

const B2Position &B2TrackSummary::GetFinalPosition() const {
  return final_position_;
}

void B2TrackSummary::SetFinalPosition(const B2Position &final_position) {
  final_position_ = final_position;
}

void B2TrackSummary::SetFinalPosition(const TVector3 &final_position) {
  final_position_ = final_position;
}

const B2Direction &B2TrackSummary::GetFinalDirection() const {
  return final_direction_;
}

void B2TrackSummary::SetFinalDirection(const B2Direction &final_direction) {
  final_direction_ = final_direction;
}

void B2TrackSummary::SetFinalDirection(const TVector3 &final_direction) {
  final_direction_ = final_direction;
}

PDG_t B2TrackSummary::GetParticlePdg() const {
  return static_cast<PDG_t>(particle_pdg_);
}

void B2TrackSummary::SetParticlePdg(PDG_t particle_pdg) {
  particle_pdg_ = particle_pdg;
}

B2TrackType B2TrackSummary::GetTrackType() const {
  return static_cast<B2TrackType>(type_);
}

void B2TrackSummary::SetTrackType(B2TrackType type) {
  type_ = type;
}

B2PrimaryTrackType B2TrackSummary::GetPrimaryTrackType() const {
  return static_cast<B2PrimaryTrackType>(primary_type_);
}

void B2TrackSummary::SetPrimaryTrackType(B2PrimaryTrackType primarytype) {
  primary_type_ = primarytype;
}

B2SecondaryTrackType B2TrackSummary::GetSecondaryTrackType() const {
  return static_cast<B2SecondaryTrackType>(secondary_type_);
}

void B2TrackSummary::SetSecondaryTrackType(B2SecondaryTrackType secondarytype) {
  secondary_type_ = secondarytype;
}

Int_t B2TrackSummary::GetNumClusters() const {
  return num_clusters_;
}

B2Detector B2TrackSummary::GetStopMrd() const {
  return static_cast<B2Detector>(stop_mrd_);
}

void B2TrackSummary::SetStopMrd(B2Detector stop_mrd) {
  stop_mrd_ = stop_mrd;
}

B2Detector B2TrackSummary::GetMatchMrd() const {
  return static_cast<B2Detector>(match_mrd_);
}

void B2TrackSummary::SetMatchMrd(B2Detector match_mrd) {
  match_mrd_ = match_mrd;
}

Bool_t B2TrackSummary::GetIsStopping() const {
  return is_stopping_;
}

void B2TrackSummary::SetIsStopping(Bool_t is_stopping) {
  is_stopping_ = is_stopping;
}

Bool_t B2TrackSummary::GetIsFiducialVolume() const {
  return is_fiducial_volume_;
}

void B2TrackSummary::SetIsFiducialVolume(Bool_t is_fiducial_volume) {
  is_fiducial_volume_ = is_fiducial_volume;
}

Double_t B2TrackSummary::GetNegativeLogLikelihoodMinus() const {
  return negative_log_likelihood_minus_;
}

void B2TrackSummary::SetNegativeLogLikelihoodMinus(Double_t negative_log_likelihood_minus) {
  negative_log_likelihood_minus_ = negative_log_likelihood_minus;
}

Double_t B2TrackSummary::GetNegativeLogLikelihoodPlus() const {
  return negative_log_likelihood_plus_;
}

void B2TrackSummary::SetNegativeLogLikelihoodPlus(Double_t negative_log_likelihood_plus) {
  negative_log_likelihood_plus_ = negative_log_likelihood_plus;
}

Double_t B2TrackSummary::GetMuclPM() const {
  return mucl_pm_;
}

void B2TrackSummary::SetMuclPM(Double_t mucl) {
  mucl_pm_ = mucl;
}

Double_t B2TrackSummary::GetMuclUWG() const {
  return mucl_uwg_;
}

void B2TrackSummary::SetMuclUWG(Double_t mucl) {
  mucl_uwg_ = mucl;
}

Double_t B2TrackSummary::GetMuclDWG() const {
  return mucl_dwg_;
}

void B2TrackSummary::SetMuclDWG(Double_t mucl) {
  mucl_dwg_ = mucl;
}

Double_t B2TrackSummary::GetTrackLengthTotal() const {
  return track_length_total_;
}

void B2TrackSummary::SetTrackLengthTotal(Double_t track_length_total) {
  track_length_total_ = track_length_total;
}

Double_t B2TrackSummary::GetReconMomByCurve() const {
  return recon_mom_by_curve_;
}

void B2TrackSummary::SetReconMomByCurve(Double_t recon_mom_by_curve) {
  recon_mom_by_curve_ = recon_mom_by_curve;
}

Double_t B2TrackSummary::GetReconMomByRange() const {
  return recon_mom_by_range_;
}

void B2TrackSummary::SetReconMomByRange(Double_t recon_mom_by_range) {
  recon_mom_by_range_ = recon_mom_by_range;
}

B2RefArray &B2TrackSummary::GetClusters() {
  return clusters_;
}

const B2RefArray &B2TrackSummary::GetClusters() const {
  return clusters_;
}

void B2TrackSummary::RemoveCluster(B2ClusterSummary *cluster) {
  clusters_.Remove((TObject *) cluster);
}

/////////////////////////////////////////////////////// B2TrueClusterIterator

B2ClusterSummary *B2TrackSummary::B2ClusterIterator::Next() {
  if (iterator_ == end_)
    return nullptr;
  auto *ref = (*iterator_++).GetObject();
  return dynamic_cast<B2ClusterSummary *>(ref);
}

B2TrackSummary::B2ClusterIterator::B2ClusterIterator(B2TrackSummary &obj) :
    iterator_(obj.GetClusters().begin()), end_(obj.GetClusters().end()) {}

B2TrackSummary::B2ClusterIterator::B2ClusterIterator(B2TrackSummary *obj) :
    iterator_(obj->GetClusters().begin()), end_(obj->GetClusters().end()) {}

/////////////////////////////////////////////////////// B2TrueClusterConstIterator

const B2ClusterSummary *B2TrackSummary::B2ClusterConstIterator::Next() {
  if (iterator_ == end_)
    return nullptr;
  auto *ref = (*iterator_++).GetObject();
  return dynamic_cast<const B2ClusterSummary *>(ref);
}

B2TrackSummary::B2ClusterConstIterator::B2ClusterConstIterator(const B2TrackSummary &obj) :
    iterator_(obj.GetClusters().begin()), end_(obj.GetClusters().end()) {}

B2TrackSummary::B2ClusterConstIterator::B2ClusterConstIterator(const B2TrackSummary *obj) :
    iterator_(obj->GetClusters().begin()), end_(obj->GetClusters().end()) {}

ClassImp(B2TrackSummary)
