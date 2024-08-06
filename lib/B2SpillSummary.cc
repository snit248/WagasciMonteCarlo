//
// Created by Giorgio Pintaudi on 8/17/20.
//

#include "B2SpillSummary.hh"

#include <iostream>
#include <boost/log/trivial.hpp>
#include <TIterator.h>
#include <TTree.h>

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"
#include "B2EventSummary.hh"
#include "B2EmulsionSummary.hh"
#include "B2BeamSummary.hh"

///> name of the spill tree
const std::string WAGASCI_TREE_NAME = "tree";

///> name of the NEUT tree
const std::string NEUT_TREE_NAME = "h10";

///> name of the NEUT tree
const std::string REWEIGHT_TREE_NAME = "reweight";

std::atomic<UInt_t> RECON_CLUSTER_ID(1);
std::atomic<UInt_t> RECON_TRACK_ID(1);

B2SpillSummary::B2SpillSummary() :
    hits_(new TClonesArray("B2HitSummary", max_num_hits_)),
    true_clusters_(new TClonesArray("B2ClusterSummary", max_num_clusters_)),
    true_tracks_(new TClonesArray("B2TrackSummary", max_num_tracks_)),
    true_vertices_(new TClonesArray("B2VertexSummary", max_num_vertices_)),
    true_events_(new TClonesArray("B2EventSummary", max_num_events_)),
    recon_clusters_(new TClonesArray("B2ClusterSummary", max_num_clusters_)),
    recon_tracks_(new TClonesArray("B2TrackSummary", max_num_tracks_)),
    recon_vertices_(new TClonesArray("B2VertexSummary", max_num_vertices_)),
    recon_events_(new TClonesArray("B2EventSummary", max_num_events_)),
    emulsions_(new TClonesArray("B2EmulsionSummary", max_num_emulsions_)) {
  B2SpillSummary::Clear("C");
  BOOST_LOG_TRIVIAL(warning) << "Calling B2SpillSummary constructor!";
  BOOST_LOG_TRIVIAL(warning) << "This warning is OK if it happens only at the beginning of the run!";
}

B2SpillSummary::B2SpillSummary(const B2SpillSummary &spill) :
    TObject(spill),

    num_hits_(spill.num_hits_),
    num_true_clusters_(spill.num_true_clusters_),
    num_true_tracks_(spill.num_true_tracks_),
    num_true_vertices_(spill.num_true_vertices_),
    num_true_events_(spill.num_true_events_),
    num_recon_clusters_(spill.num_recon_clusters_),
    num_recon_tracks_(spill.num_recon_tracks_),
    num_recon_vertices_(spill.num_recon_vertices_),
    num_recon_events_(spill.num_recon_events_),
    num_emulsions_(spill.num_emulsions_),

    hits_(dynamic_cast<TClonesArray *>(spill.hits_->Clone())),
    true_clusters_(dynamic_cast<TClonesArray *>(spill.true_clusters_->Clone())),
    true_tracks_(dynamic_cast<TClonesArray *>(spill.true_tracks_->Clone())),
    true_vertices_(dynamic_cast<TClonesArray *>(spill.true_vertices_->Clone())),
    true_events_(dynamic_cast<TClonesArray *>(spill.true_events_->Clone())),
    recon_clusters_(dynamic_cast<TClonesArray *>(spill.recon_clusters_->Clone())),
    recon_tracks_(dynamic_cast<TClonesArray *>(spill.recon_tracks_->Clone())),
    recon_vertices_(dynamic_cast<TClonesArray *>(spill.recon_vertices_->Clone())),
    recon_events_(dynamic_cast<TClonesArray *>(spill.recon_events_->Clone())),
    emulsions_(dynamic_cast<TClonesArray *>(spill.emulsions_->Clone())),

    beam_summary_(spill.beam_summary_) {
  BOOST_LOG_TRIVIAL(warning) << "Calling B2SpillSummary copy constructor!";
}

B2SpillSummary &B2SpillSummary::operator=(B2SpillSummary other) {
  Swap(*this, other);
  return *this;
}

void Swap(B2SpillSummary &lhs, B2SpillSummary &rhs) // nothrow
{
  // enable ADL (not necessary in our case, but good practice)
  using std::swap;

  // by swapping the members of two objects,
  // the two objects are effectively swapped
  swap(lhs.num_hits_, rhs.num_hits_);
  swap(lhs.num_true_clusters_, rhs.num_true_clusters_);
  swap(lhs.num_true_tracks_, rhs.num_true_tracks_);
  swap(lhs.num_true_vertices_, rhs.num_true_vertices_);
  swap(lhs.num_true_events_, rhs.num_true_events_);
  swap(lhs.num_recon_clusters_, rhs.num_recon_clusters_);
  swap(lhs.num_recon_tracks_, rhs.num_recon_tracks_);
  swap(lhs.num_recon_vertices_, rhs.num_recon_vertices_);
  swap(lhs.num_recon_events_, rhs.num_recon_events_);

  swap(lhs.hits_, rhs.hits_);
  swap(lhs.true_clusters_, rhs.true_clusters_);
  swap(lhs.true_tracks_, rhs.true_tracks_);
  swap(lhs.true_vertices_, rhs.true_vertices_);
  swap(lhs.true_events_, rhs.true_events_);
  swap(lhs.recon_clusters_, rhs.recon_clusters_);
  swap(lhs.recon_tracks_, rhs.recon_tracks_);
  swap(lhs.recon_vertices_, rhs.recon_vertices_);
  swap(lhs.recon_events_, rhs.recon_events_);

  swap(lhs.num_emulsions_, rhs.num_emulsions_);
  swap(lhs.emulsions_, rhs.emulsions_);

  swap(lhs.beam_summary_, rhs.beam_summary_);
}

B2SpillSummary::~B2SpillSummary() {
  BOOST_LOG_TRIVIAL(warning) << "Calling B2SpillSummary destructor!";
  BOOST_LOG_TRIVIAL(warning) << "This warning is OK if it happens only at the end of the run!";
  hits_->Delete();
  emulsions_->Delete();
  true_clusters_->Delete();
  true_tracks_->Delete();
  true_vertices_->Delete();
  true_events_->Delete();
  recon_clusters_->Delete();
  recon_tracks_->Delete();
  recon_vertices_->Delete();
  recon_events_->Delete();

  delete hits_;
  delete emulsions_;
  delete true_clusters_;
  delete true_tracks_;
  delete true_vertices_;
  delete true_events_;
  delete recon_clusters_;
  delete recon_tracks_;
  delete recon_vertices_;
  delete recon_events_;
}

void B2SpillSummary::Clear(Option_t *option) {
  hits_->Clear(option);
  emulsions_->Clear(option);
  true_clusters_->Clear(option);
  true_tracks_->Clear(option);
  true_vertices_->Clear(option);
  true_events_->Clear(option);
  recon_clusters_->Clear(option);
  recon_tracks_->Clear(option);
  recon_vertices_->Clear(option);
  recon_events_->Clear(option);

  num_hits_ = hits_->GetEntries();
  num_emulsions_ = emulsions_->GetEntries();
  num_true_clusters_ = true_clusters_->GetEntries();
  num_true_tracks_ = true_tracks_->GetEntries();
  num_true_vertices_ = true_vertices_->GetEntries();
  num_true_events_ = true_events_->GetEntries();
  num_recon_clusters_ = recon_clusters_->GetEntries();
  num_recon_tracks_ = recon_tracks_->GetEntries();
  num_recon_vertices_ = recon_vertices_->GetEntries();
  num_recon_events_ = recon_events_->GetEntries();

  beam_summary_.Clear(option);
  TObject::Clear(option);
}

B2HitSummary &B2SpillSummary::AddHit(const B2HitSummary &hit) {
  // use copy constructor
  new((*hits_)[num_hits_++]) B2HitSummary(hit);
  return *(B2HitSummary *) (hits_->Last());
}

B2HitSummary &B2SpillSummary::AddHit(const B2HitSummary *hit) {
  return AddHit(*hit);
}

B2HitSummary &B2SpillSummary::AddHit() {
  new((*hits_)[num_hits_++]) B2HitSummary();
  return *(B2HitSummary *) (hits_->Last());
}

const TClonesArray &B2SpillSummary::GetHits() const { return *hits_; }

B2ClusterSummary &B2SpillSummary::AddTrueCluster(const B2ClusterSummary &cluster) {
  // use copy constructor
  new((*true_clusters_)[num_true_clusters_++]) B2ClusterSummary(cluster);
  return *(B2ClusterSummary *) (true_clusters_->Last());
}

B2ClusterSummary &B2SpillSummary::AddTrueCluster() {
  new((*true_clusters_)[num_true_clusters_++]) B2ClusterSummary();
  return *(B2ClusterSummary *) (true_clusters_->Last());
}

B2ClusterSummary &B2SpillSummary::AddTrueCluster(const B2ClusterSummary *cluster) {
  return AddTrueCluster(*cluster);
}

const B2ClusterSummary &B2SpillSummary::GetTrueCluster(UInt_t id) const {
  auto it = BeginTrueCluster();
  while (const auto *cluster = it.Next()) {
    if (cluster->GetClusterId() == id)
      return *cluster;
  }
  throw std::out_of_range("Cluster not found with ID " + std::to_string(id));
}

B2ClusterSummary &B2SpillSummary::GetTrueCluster(UInt_t id) {
  return const_cast<B2ClusterSummary &>(static_cast<const B2SpillSummary &>(*this).GetTrueCluster(id));
}

bool B2SpillSummary::HasTrueCluster(UInt_t id) const {
  auto it = BeginTrueCluster();
  while (const auto *i = it.Next()) {
    if (i->GetClusterId() == id)
      return true;
  }
  return false;
}

const TClonesArray &B2SpillSummary::GetTrueClusters() const { return *true_clusters_; }

TClonesArray &B2SpillSummary::GetTrueClusters() { return *true_clusters_; }

B2TrackSummary &B2SpillSummary::AddTrueTrack(const B2TrackSummary &track) {
  // use copy constructor
  new((*true_tracks_)[num_true_tracks_++]) B2TrackSummary(track);
  return *(B2TrackSummary *) (true_tracks_->Last());
}

B2TrackSummary &B2SpillSummary::AddTrueTrack() {
  new((*true_tracks_)[num_true_tracks_++]) B2TrackSummary();
  return *(B2TrackSummary *) (true_tracks_->Last());
}

B2TrackSummary &B2SpillSummary::AddTrueTrack(const B2TrackSummary *track) {
  return AddTrueTrack(*track);
}

const TClonesArray &B2SpillSummary::GetTrueTracks() const { return *true_tracks_; }

TClonesArray &B2SpillSummary::GetTrueTracks() { return *true_tracks_; }

B2VertexSummary &B2SpillSummary::AddTrueVertex(const B2VertexSummary &vertex) {
  // use copy constructor
  new((*true_vertices_)[num_true_vertices_++]) B2VertexSummary(vertex);
  return *(B2VertexSummary *) true_vertices_->Last();
}

B2VertexSummary &B2SpillSummary::AddTrueVertex() {
  new((*true_vertices_)[num_true_vertices_++]) B2VertexSummary();
  return *(B2VertexSummary *) true_vertices_->Last();
}

B2VertexSummary &B2SpillSummary::AddTrueVertex(const B2VertexSummary *vertex) {
  return AddTrueVertex(*vertex);
}

const B2VertexSummary &B2SpillSummary::GetTrueVertex(const TVector3 &position, Double_t cut) const {

  auto it = BeginTrueVertex();
  while (const auto *i = it.Next()) {
    if ((i->GetAbsolutePosition().GetValue() - position).Mag() < cut)
      return *i;
  }
  std::stringstream ss;
  ss << "No vertex found near point X = " << position.x()
     << " Y = " << position.y() << " Z = " << position.z();
  throw std::out_of_range(ss.str());
}

B2VertexSummary &B2SpillSummary::GetTrueVertex(const TVector3 &position, Double_t cut) {
  return const_cast<B2VertexSummary &>(static_cast<const B2SpillSummary &>(*this).GetTrueVertex(position, cut));
}

const TClonesArray &B2SpillSummary::GetTrueVertices() const { return *true_vertices_; }

B2EventSummary &B2SpillSummary::AddTrueEvent(const B2EventSummary &event) {
  // use copy constructor
  new((*true_events_)[num_true_events_++]) B2EventSummary(event);
  return *(B2EventSummary *) (true_events_->Last());
}

B2EventSummary &B2SpillSummary::AddTrueEvent() {
  new((*true_events_)[num_true_events_++]) B2EventSummary();
  return *(B2EventSummary *) (true_events_->Last());
}

B2EventSummary &B2SpillSummary::AddTrueEvent(const B2EventSummary *event) {
  return AddTrueEvent(*event);
}

const TClonesArray &B2SpillSummary::GetTrueEvents() const { return *true_events_; }

B2ClusterSummary &B2SpillSummary::AddReconCluster(const B2ClusterSummary &cluster) {
  // use copy constructor
  new((*recon_clusters_)[num_recon_clusters_++]) B2ClusterSummary(cluster);
  auto new_cluster = dynamic_cast<B2ClusterSummary *>(recon_clusters_->Last());
  new_cluster->SetClusterId(++RECON_CLUSTER_ID);
  return *new_cluster;
}

B2ClusterSummary &B2SpillSummary::AddReconCluster() {
  new((*recon_clusters_)[num_recon_clusters_++]) B2ClusterSummary();
  auto new_cluster = dynamic_cast<B2ClusterSummary *>(recon_clusters_->Last());
  new_cluster->SetClusterId(++RECON_CLUSTER_ID);
  return *new_cluster;
}

B2ClusterSummary &B2SpillSummary::AddReconCluster(const B2ClusterSummary *cluster) {
  return AddReconCluster(*cluster);
}

const TClonesArray &B2SpillSummary::GetReconClusters() const { return *recon_clusters_; }

TClonesArray &B2SpillSummary::GetReconClusters() { return *recon_clusters_; }

B2TrackSummary &B2SpillSummary::AddReconTrack(const B2TrackSummary &track) {
  // use copy constructor
  new((*recon_tracks_)[num_recon_tracks_++]) B2TrackSummary(track);
  auto new_track = dynamic_cast<B2TrackSummary *>(recon_tracks_->Last());
  new_track->SetTrackId(++RECON_TRACK_ID);
  return *new_track;
}

B2TrackSummary &B2SpillSummary::AddReconTrack() {
  new((*recon_tracks_)[num_recon_tracks_++]) B2TrackSummary();
  auto new_track = dynamic_cast<B2TrackSummary *>(recon_tracks_->Last());
  new_track->SetTrackId(++RECON_TRACK_ID);
  return *new_track;
}

B2TrackSummary &B2SpillSummary::AddReconTrack(const B2TrackSummary *track) {
  return AddReconTrack(*track);
}

const TClonesArray &B2SpillSummary::GetReconTracks() const { return *recon_tracks_; }

TClonesArray &B2SpillSummary::GetReconTracks() { return *recon_tracks_; }

B2VertexSummary &B2SpillSummary::AddReconVertex(const B2VertexSummary &vertex) {
  // use copy constructor
  new((*recon_vertices_)[num_recon_vertices_++]) B2VertexSummary(vertex);
  return *(B2VertexSummary *) recon_vertices_->Last();
}

B2VertexSummary &B2SpillSummary::AddReconVertex() {
  new((*recon_vertices_)[num_recon_vertices_++]) B2VertexSummary();
  return *(B2VertexSummary *) recon_vertices_->Last();
}

B2VertexSummary &B2SpillSummary::AddReconVertex(const B2VertexSummary *vertex) {
  return AddReconVertex(*vertex);
}

const B2VertexSummary &B2SpillSummary::GetReconVertex(const TVector3 &position, Double_t cut) const {

  auto it = BeginReconVertex();
  while (const auto *i = it.Next()) {
    if ((i->GetAbsolutePosition().GetValue() - position).Mag() < cut)
      return *i;
  }
  std::stringstream ss;
  ss << "No vertex found near point X = " << position.x()
     << " Y = " << position.y() << " Z = " << position.z();
  throw std::out_of_range(ss.str());
}

B2VertexSummary &B2SpillSummary::GetReconVertex(const TVector3 &position, Double_t cut) {
  return const_cast<B2VertexSummary &>(static_cast<const B2SpillSummary &>(*this).GetReconVertex(position, cut));
}

const TClonesArray &B2SpillSummary::GetReconVertices() const { return *recon_vertices_; }

B2EventSummary &B2SpillSummary::AddReconEvent(const B2EventSummary &event) {
  // use copy constructor
  new((*recon_events_)[num_recon_events_++]) B2EventSummary(event);
  return *(B2EventSummary *) (recon_events_->Last());
}

B2EventSummary &B2SpillSummary::AddReconEvent() {
  new((*recon_events_)[num_recon_events_++]) B2EventSummary();
  return *(B2EventSummary *) (recon_events_->Last());
}

B2EventSummary &B2SpillSummary::AddReconEvent(const B2EventSummary *event) {
  return AddReconEvent(*event);
}

const TClonesArray &B2SpillSummary::GetReconEvents() const { return *recon_events_; }


B2SpillSummary::B2HitIterator B2SpillSummary::BeginHit() {
  return B2HitIterator(this);
}

B2SpillSummary::B2HitConstIterator B2SpillSummary::BeginHit() const {
  return B2HitConstIterator(this);
}

B2SpillSummary::B2TrueClusterIterator B2SpillSummary::BeginTrueCluster() {
  return B2TrueClusterIterator(this);
}

B2SpillSummary::B2TrueClusterConstIterator B2SpillSummary::BeginTrueCluster() const {
  return B2TrueClusterConstIterator(this);
}

B2SpillSummary::B2TrueTrackIterator B2SpillSummary::BeginTrueTrack() {
  return B2TrueTrackIterator(this);
}

B2SpillSummary::B2TrueTrackConstIterator B2SpillSummary::BeginTrueTrack() const {
  return B2TrueTrackConstIterator(this);
}

B2SpillSummary::B2TrueVertexIterator B2SpillSummary::BeginTrueVertex() {
  return B2TrueVertexIterator(this);
}

B2SpillSummary::B2TrueVertexConstIterator B2SpillSummary::BeginTrueVertex() const {
  return B2TrueVertexConstIterator(this);
}

B2VertexSummary &B2SpillSummary::FirstTrueVertex() {
  return const_cast<B2VertexSummary &>(static_cast<const B2SpillSummary &>(*this).FirstTrueVertex());
}

const B2VertexSummary &B2SpillSummary::FirstTrueVertex() const {
  if (num_true_vertices_ == 0)
    throw std::runtime_error("No true vertices in spill with spill number " +
                             std::to_string(beam_summary_.GetWagasciSpillNumber()));
  return *BeginTrueVertex().Next();
}

B2SpillSummary::B2TrueEventIterator B2SpillSummary::BeginTrueEvent() {
  return B2TrueEventIterator(this);
}

B2SpillSummary::B2TrueEventConstIterator B2SpillSummary::BeginTrueEvent() const {
  return B2TrueEventConstIterator(this);
}

B2EventSummary &B2SpillSummary::FirstTrueEvent() {
  return const_cast<B2EventSummary &>(static_cast<const B2SpillSummary &>(*this).FirstTrueEvent());
}

const B2EventSummary &B2SpillSummary::FirstTrueEvent() const {
  if (num_true_events_ == 0)
    throw std::runtime_error("No true events in spill with spill number " +
                             std::to_string(beam_summary_.GetWagasciSpillNumber()));
  return *BeginTrueEvent().Next();
}

B2SpillSummary::B2ReconClusterIterator B2SpillSummary::BeginReconCluster() {
  return B2ReconClusterIterator(this);
}

B2SpillSummary::B2ReconClusterConstIterator B2SpillSummary::BeginReconCluster() const {
  return B2ReconClusterConstIterator(this);
}

B2SpillSummary::B2ReconTrackIterator B2SpillSummary::BeginReconTrack() {
  return B2ReconTrackIterator(this);
}

B2SpillSummary::B2ReconTrackConstIterator B2SpillSummary::BeginReconTrack() const {
  return B2ReconTrackConstIterator(this);
}

B2SpillSummary::B2ReconVertexIterator B2SpillSummary::BeginReconVertex() {
  return B2ReconVertexIterator(this);
}

B2SpillSummary::B2ReconVertexConstIterator B2SpillSummary::BeginReconVertex() const {
  return B2ReconVertexConstIterator(this);
}

B2SpillSummary::B2ReconEventIterator B2SpillSummary::BeginReconEvent() {
  return B2ReconEventIterator(this);
}

B2SpillSummary::B2ReconEventConstIterator B2SpillSummary::BeginReconEvent() const {
  return B2ReconEventConstIterator(this);
}

B2BeamSummary &B2SpillSummary::GetBeamSummary() { return beam_summary_; }

const B2BeamSummary &B2SpillSummary::GetBeamSummary() const { return beam_summary_; }

std::ostream &operator<<(std::ostream &os, const B2SpillSummary &obj) {
  os << "Number of hits = " << obj.num_hits_ << "\n"
     << "Number of true clusters = " << obj.num_true_clusters_ << "\n"
     << "Number of reconstructed clusters = " << obj.num_recon_clusters_ << "\n"
     << "Number of true tracks = " << obj.num_true_tracks_ << "\n"
     << "Number of reconstructed tracks = " << obj.num_recon_tracks_ << "\n"
     << "Number of true vertices = " << obj.num_true_vertices_ << "\n"
     << "Number of reconstructed vertices = " << obj.num_recon_vertices_ << "\n"
     << "Number of true events = " << obj.num_true_events_ << "\n"
     << "Number of reconstructed events = " << obj.num_recon_events_ << "\n"
     << "Number of emulsion tracks = " << obj.num_emulsions_ << "\n";
  return os;
}

void B2SpillSummary::RemoveTrueTrack(B2TrackSummary *track, Bool_t clusters_too) {

  if (track == nullptr)
    return;

  BOOST_LOG_TRIVIAL(debug) << "Removing track : \n" << *track << "\n";

  // Remove all references to the track in the hits
  {
    auto it = track->BeginHit();
    while (auto *hit_summary = it.Next()) {
      hit_summary->SetParentTrack(nullptr);
      hit_summary->SetParentTrackId(0);
    }
  }
  // Remove all references to the track in the clusters
  {
    auto it = track->BeginCluster();
    while (auto *cluster_summary = it.Next()) {
      cluster_summary->SetParentTrack(nullptr);
      cluster_summary->SetParentTrackId(0);
      cluster_summary->Ghostify();
    }
  }

  if (clusters_too) {
    {
      // Remove all references to the clusters
      auto it = track->BeginHit();
      while (auto *hit_summary = it.Next()) {
        hit_summary->SetParentCluster(nullptr);
        hit_summary->SetParentClusterId(0);
      }
    }
    // Remove clusters
    {
      auto it = track->BeginCluster();
      while (auto *cluster_summary = it.Next()) {
        true_clusters_->Remove((TObject *) cluster_summary);
      }
    }
    true_clusters_->Compress();
  }

  // Actually remove track
  track->Invalidate();
  true_tracks_->Remove((TObject *) track);
  true_tracks_->Compress();
  --num_true_tracks_;
}

void B2SpillSummary::RemoveTrueCluster(B2ClusterSummary *cluster) {
  BOOST_LOG_TRIVIAL(debug) << "Removing cluster : \n" << *cluster << "\n";

  // Remove all references to the cluster in the hits
  auto it = cluster->BeginHit();
  while (auto *hit_summary = it.Next()) {
    hit_summary->SetParentCluster(nullptr);
    hit_summary->SetParentClusterId(0);
  }
  // Remove all references to the cluster in the tracks
  if (cluster->HasParentTrack()) {
    cluster->GetParentTrack().RemoveCluster(cluster);
  }

  // Actually remove cluster
  cluster->Invalidate();
  true_clusters_->Remove((TObject *) cluster);
  true_clusters_->Compress();
  --num_true_clusters_;
}

Int_t B2SpillSummary::GetNumHits(B2Detector detector) const {
  if (detector == B2Detector::kUnknownDetector) {
    return num_hits_;
  } else {
    Int_t counter = 0;
    auto it = BeginHit();
    while (const auto *hit = it.Next()) {
      if (hit->GetDetectorId() == detector) {
        ++counter;
      }
    }
    return counter;
  }
}

Int_t B2SpillSummary::GetNumTrueClusters() const {
  return num_true_clusters_;
}

Int_t B2SpillSummary::GetNumTrueTracks() const {
  return num_true_tracks_;
}

Int_t B2SpillSummary::GetNumTrueVertices() const {
  return num_true_vertices_;
}

Int_t B2SpillSummary::GetNumTrueEvents() const {
  return num_true_events_;
}

Int_t B2SpillSummary::GetNumReconClusters() const {
  return num_recon_clusters_;
}

Int_t B2SpillSummary::GetNumReconTracks() const {
  return num_recon_tracks_;
}

Int_t B2SpillSummary::GetNumReconVertices() const {
  return num_recon_vertices_;
}

Int_t B2SpillSummary::GetNumReconEvents() const {
  return num_recon_events_;
}

void B2SpillSummary::CreateBranch(TTree &ttree) {
  ttree.Branch("spill", "B2SpillSummary", this, 64000, 99);
}

B2HitSummary *B2SpillSummary::SearchClosestHit(const TVector3 &pos, Double_t distance_cut) {
  auto it = this->BeginHit();
  B2HitSummary *closest_hit = nullptr;
  Double_t distance = B2_WORLD_DEPTH * B2_WORLD_HEIGHT * B2_WORLD_WIDTH / 3.;
  while (auto *hit_summary = it.Next()) {
    if ((hit_summary->GetTrueAbsolutePosition().GetValue() - pos).Mag() < distance)
      distance = (hit_summary->GetTrueAbsolutePosition().GetValue() - pos).Mag();
    closest_hit = hit_summary;
  }
  if (distance > distance_cut)
    return nullptr;
  else
    return closest_hit;
}

const B2TrackSummary &B2SpillSummary::GetTrueTrack(UInt_t id) const {
  auto it = BeginTrueTrack();
  while (const auto *track = it.Next()) {
    if (track->GetTrackId() == id)
      return *track;
  }
  throw std::out_of_range("Track not found with ID " + std::to_string(id));
}

B2TrackSummary &B2SpillSummary::GetTrueTrack(UInt_t id) {
  return const_cast<B2TrackSummary &>(static_cast<const B2SpillSummary &>(*this).GetTrueTrack(id));
}

bool B2SpillSummary::HasTrueTrack(UInt_t id) const {
  auto it = BeginTrueTrack();
  while (const auto *i = it.Next()) {
    if (i->GetTrackId() == id)
      return true;
  }
  return false;
}

const B2VertexSummary &B2SpillSummary::GetTrueVertex(UInt_t id) const {
  auto it = BeginTrueVertex();
  while (const auto *vertex = it.Next()) {
    if (vertex->GetVertexId() == id)
      return *vertex;
  }
  throw std::out_of_range("Vertex not found with ID " + std::to_string(id));
}

B2VertexSummary &B2SpillSummary::GetTrueVertex(UInt_t id) {
  return const_cast<B2VertexSummary &>(static_cast<const B2SpillSummary &>(*this).GetTrueVertex(id));
}

bool B2SpillSummary::HasTrueVertex(UInt_t id) const {
  auto it = BeginTrueVertex();
  while (const auto *i = it.Next()) {
    if (i->GetVertexId() == id)
      return true;
  }
  return false;
}

const B2HitSummary &B2SpillSummary::GetHit(UInt_t id) const {
  auto it = BeginHit();
  while (const auto *hit = it.Next()) {
    if (hit->GetHitId() == id)
      return *hit;
  }
  throw std::out_of_range("Hit not found with ID " + std::to_string(id));
}

B2HitSummary &B2SpillSummary::GetHit(UInt_t id) {
  return const_cast<B2HitSummary &>(static_cast<const B2SpillSummary &>(*this).GetHit(id));
}

bool B2SpillSummary::HasHit(UInt_t id) const {
  auto it = BeginHit();
  while (const auto *i = it.Next()) {
    if (i->GetHitId() == id)
      return true;
  }
  return false;
}

B2EmulsionSummary &B2SpillSummary::AddEmulsion(const B2EmulsionSummary &emulsion) {
  // use copy constructor
  new((*emulsions_)[num_emulsions_++]) B2EmulsionSummary(emulsion);
  return *(B2EmulsionSummary *) (emulsions_->Last());
}

B2EmulsionSummary &B2SpillSummary::AddEmulsion(const B2EmulsionSummary *emulsion) {
  return AddEmulsion(*emulsion);
}

B2EmulsionSummary &B2SpillSummary::AddEmulsion() {
  new((*emulsions_)[num_emulsions_++]) B2EmulsionSummary();
  return *(B2EmulsionSummary *) (emulsions_->Last());
}

const TClonesArray &B2SpillSummary::GetEmulsions() const {
  return *emulsions_;
}

TClonesArray &B2SpillSummary::GetEmulsions() {
  return *emulsions_;
}

B2SpillSummary::B2EmulsionIterator B2SpillSummary::BeginEmulsion() {
  return B2EmulsionIterator(this);
}

B2SpillSummary::B2EmulsionConstIterator B2SpillSummary::BeginEmulsion() const {
  return B2EmulsionConstIterator(this);
}

Int_t B2SpillSummary::GetNumEmulsions() const {
  return num_emulsions_;
}

const B2EmulsionSummary &B2SpillSummary::GetEmulsion(UInt_t id) const {
  auto it = BeginEmulsion();
  while (const auto *emulsion = it.Next()) {
    if (emulsion->GetEmulsionTrackId() == id)
      return *emulsion;
  }
  throw std::out_of_range("Emulsion track not found with ID " + std::to_string(id));
}

B2EmulsionSummary &B2SpillSummary::GetEmulsion(UInt_t id) {
  return const_cast<B2EmulsionSummary &>(static_cast<const B2SpillSummary &>(*this).GetEmulsion(id));
}

bool B2SpillSummary::HasEmulsion(UInt_t id) const {
  auto it = BeginEmulsion();
  while (const auto *i = it.Next()) {
    if (i->GetEmulsionTrackId() == id)
      return true;
  }
  return false;
}

bool B2SpillSummary::HasReconCluster(UInt_t id) const {
  auto it = BeginReconCluster();
  while (const auto *i = it.Next()) {
    if (i->GetClusterId() == id)
      return true;
  }
  return false;
}

bool B2SpillSummary::HasReconTrack(UInt_t id) const {
  auto it = BeginReconTrack();
  while (const auto *i = it.Next()) {
    if (i->GetTrackId() == id)
      return true;
  }
  return false;
}

bool B2SpillSummary::HasReconVertex(UInt_t id) const {
  auto it = BeginReconVertex();
  while (const auto *i = it.Next()) {
    if (i->GetVertexId() == id)
      return true;
  }
  return false;
}

const B2ClusterSummary &B2SpillSummary::GetReconCluster(UInt_t id) const {
  auto it = BeginReconCluster();
  while (const auto *cluster = it.Next()) {
    if (cluster->GetClusterId() == id)
      return *cluster;
  }
  throw std::out_of_range("Cluster not found with ID " + std::to_string(id));
}

B2ClusterSummary &B2SpillSummary::GetReconCluster(UInt_t id) {
  return const_cast<B2ClusterSummary &>(static_cast<const B2SpillSummary &>(*this).GetReconCluster(id));
}

const B2TrackSummary &B2SpillSummary::GetReconTrack(UInt_t id) const {
  auto it = BeginReconTrack();
  while (const auto *track = it.Next()) {
    if (track->GetTrackId() == id)
      return *track;
  }
  throw std::out_of_range("Track not found with ID " + std::to_string(id));
}

B2TrackSummary &B2SpillSummary::GetReconTrack(UInt_t id) {
  return const_cast<B2TrackSummary &>(static_cast<const B2SpillSummary &>(*this).GetReconTrack(id));
}

const B2VertexSummary &B2SpillSummary::GetReconVertex(UInt_t id) const {
  auto it = BeginReconVertex();
  while (const auto *vertex = it.Next()) {
    if (vertex->GetVertexId() == id)
      return *vertex;
  }
  throw std::out_of_range("Vertex not found with ID " + std::to_string(id));
}

B2VertexSummary &B2SpillSummary::GetReconVertex(UInt_t id) {
  return const_cast<B2VertexSummary &>(static_cast<const B2SpillSummary &>(*this).GetReconVertex(id));
}


/////////////////////////////////////////////////////// B2HitIterator

B2HitSummary *B2SpillSummary::B2HitIterator::Next() {
  return dynamic_cast<B2HitSummary *>(TIter::Next());
}

B2SpillSummary::B2HitIterator::B2HitIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetHits()) {}

B2SpillSummary::B2HitIterator::B2HitIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetHits()) {}

/////////////////////////////////////////////////////// B2HitConstIterator

const B2HitSummary *B2SpillSummary::B2HitConstIterator::Next() {
  return dynamic_cast<const B2HitSummary *>(TIter::Next());
}

B2SpillSummary::B2HitConstIterator::B2HitConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetHits()) {}

B2SpillSummary::B2HitConstIterator::B2HitConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetHits()) {}

/////////////////////////////////////////////////////// B2TrueClusterIterator

B2ClusterSummary *B2SpillSummary::B2TrueClusterIterator::Next() {
  return dynamic_cast<B2ClusterSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueClusterIterator::B2TrueClusterIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueClusters()) {}

B2SpillSummary::B2TrueClusterIterator::B2TrueClusterIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueClusters()) {}

/////////////////////////////////////////////////////// B2TrueClusterConstIterator

const B2ClusterSummary *B2SpillSummary::B2TrueClusterConstIterator::Next() {
  return dynamic_cast<const B2ClusterSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueClusterConstIterator::B2TrueClusterConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueClusters()) {}

B2SpillSummary::B2TrueClusterConstIterator::B2TrueClusterConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueClusters()) {}

/////////////////////////////////////////////////////// B2TrueTrackIterator

B2TrackSummary *B2SpillSummary::B2TrueTrackIterator::Next() {
  return dynamic_cast<B2TrackSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueTrackIterator::B2TrueTrackIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueTracks()) {}

B2SpillSummary::B2TrueTrackIterator::B2TrueTrackIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueTracks()) {}

/////////////////////////////////////////////////////// B2TrueTrackConstIterator

const B2TrackSummary *B2SpillSummary::B2TrueTrackConstIterator::Next() {
  return dynamic_cast<const B2TrackSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueTrackConstIterator::B2TrueTrackConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueTracks()) {}

B2SpillSummary::B2TrueTrackConstIterator::B2TrueTrackConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueTracks()) {}

/////////////////////////////////////////////////////// B2TrueVertexIterator

B2VertexSummary *B2SpillSummary::B2TrueVertexIterator::Next() {
  return dynamic_cast<B2VertexSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueVertexIterator::B2TrueVertexIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueVertices()) {}

B2SpillSummary::B2TrueVertexIterator::B2TrueVertexIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueVertices()) {}

/////////////////////////////////////////////////////// B2TrueVertexConstIterator

const B2VertexSummary *B2SpillSummary::B2TrueVertexConstIterator::Next() {
  return dynamic_cast<const B2VertexSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueVertexConstIterator::B2TrueVertexConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueVertices()) {}

B2SpillSummary::B2TrueVertexConstIterator::B2TrueVertexConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueVertices()) {}

/////////////////////////////////////////////////////// B2TrueEventIterator

B2EventSummary *B2SpillSummary::B2TrueEventIterator::Next() {
  return dynamic_cast<B2EventSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueEventIterator::B2TrueEventIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueEvents()) {}

B2SpillSummary::B2TrueEventIterator::B2TrueEventIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueEvents()) {}

/////////////////////////////////////////////////////// B2TrueEventConstIterator

const B2EventSummary *B2SpillSummary::B2TrueEventConstIterator::Next() {
  return dynamic_cast<const B2EventSummary *>(TIter::Next());
}

B2SpillSummary::B2TrueEventConstIterator::B2TrueEventConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetTrueEvents()) {}

B2SpillSummary::B2TrueEventConstIterator::B2TrueEventConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetTrueEvents()) {}

/////////////////////////////////////////////////////// B2ReconClusterIterator

B2ClusterSummary *B2SpillSummary::B2ReconClusterIterator::Next() {
  return dynamic_cast<B2ClusterSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconClusterIterator::B2ReconClusterIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconClusters()) {}

B2SpillSummary::B2ReconClusterIterator::B2ReconClusterIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconClusters()) {}

/////////////////////////////////////////////////////// B2ReconClusterConstIterator

const B2ClusterSummary *B2SpillSummary::B2ReconClusterConstIterator::Next() {
  return dynamic_cast<const B2ClusterSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconClusterConstIterator::B2ReconClusterConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconClusters()) {}

B2SpillSummary::B2ReconClusterConstIterator::B2ReconClusterConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconClusters()) {}

/////////////////////////////////////////////////////// B2ReconTrackIterator

B2TrackSummary *B2SpillSummary::B2ReconTrackIterator::Next() {
  return dynamic_cast<B2TrackSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconTrackIterator::B2ReconTrackIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconTracks()) {}

B2SpillSummary::B2ReconTrackIterator::B2ReconTrackIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconTracks()) {}

/////////////////////////////////////////////////////// B2ReconTrackConstIterator

const B2TrackSummary *B2SpillSummary::B2ReconTrackConstIterator::Next() {
  return dynamic_cast<const B2TrackSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconTrackConstIterator::B2ReconTrackConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconTracks()) {}

B2SpillSummary::B2ReconTrackConstIterator::B2ReconTrackConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconTracks()) {}

/////////////////////////////////////////////////////// B2ReconVertexIterator

B2VertexSummary *B2SpillSummary::B2ReconVertexIterator::Next() {
  return dynamic_cast<B2VertexSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconVertexIterator::B2ReconVertexIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconVertices()) {}

B2SpillSummary::B2ReconVertexIterator::B2ReconVertexIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconVertices()) {}

/////////////////////////////////////////////////////// B2ReconVertexConstIterator

const B2VertexSummary *B2SpillSummary::B2ReconVertexConstIterator::Next() {
  return dynamic_cast<const B2VertexSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconVertexConstIterator::B2ReconVertexConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconVertices()) {}

B2SpillSummary::B2ReconVertexConstIterator::B2ReconVertexConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconVertices()) {}

/////////////////////////////////////////////////////// B2ReconEventIterator

B2EventSummary *B2SpillSummary::B2ReconEventIterator::Next() {
  return dynamic_cast<B2EventSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconEventIterator::B2ReconEventIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconEvents()) {}

B2SpillSummary::B2ReconEventIterator::B2ReconEventIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconEvents()) {}

/////////////////////////////////////////////////////// B2ReconEventConstIterator

const B2EventSummary *B2SpillSummary::B2ReconEventConstIterator::Next() {
  return dynamic_cast<const B2EventSummary *>(TIter::Next());
}

B2SpillSummary::B2ReconEventConstIterator::B2ReconEventConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetReconEvents()) {}

B2SpillSummary::B2ReconEventConstIterator::B2ReconEventConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetReconEvents()) {}

/////////////////////////////////////////////////////// B2EmulsionIterator

B2EmulsionSummary *B2SpillSummary::B2EmulsionIterator::Next() {
  return dynamic_cast<B2EmulsionSummary *>(TIter::Next());
}

B2SpillSummary::B2EmulsionIterator::B2EmulsionIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetEmulsions()) {}

B2SpillSummary::B2EmulsionIterator::B2EmulsionIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetEmulsions()) {}

/////////////////////////////////////////////////////// B2EmulsionConstIterator

const B2EmulsionSummary *B2SpillSummary::B2EmulsionConstIterator::Next() {
  return dynamic_cast<const B2EmulsionSummary *>(TIter::Next());
}

B2SpillSummary::B2EmulsionConstIterator::B2EmulsionConstIterator(const B2SpillSummary &obj) :
    TIter(&obj.GetEmulsions()) {}

B2SpillSummary::B2EmulsionConstIterator::B2EmulsionConstIterator(const B2SpillSummary *obj) :
    TIter(&obj->GetEmulsions()) {}

ClassImp(B2SpillSummary)
