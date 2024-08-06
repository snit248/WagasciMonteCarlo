//
// Created by Giorgio Pintaudi on 8/15/20.
//

#include "B2ClusterSummary.hh"

#include <iostream>

#include "B2EventSummary.hh"
#include "B2HitSummary.hh"
#include "B2TrackSummary.hh"
#include "B2HitsSet.hh"

B2ClusterSummary::B2ClusterSummary() :
    B2HitsSet()
{
  B2ClusterSummary::Clear("C");
}

void B2ClusterSummary::Clear(Option_t *option) {
  cluster_id_ = 0;
  is_ghost_ = kFALSE;
  B2HitsSet::Clear(option);
}

std::ostream &operator<<(std::ostream &os, const B2ClusterSummary &obj) {
  os << "Geant4 Cluster ID = " << obj.cluster_id_ << "\n"
     << "Is ghost = " << std::boolalpha << (bool) obj.is_ghost_ << "\n";
  os << static_cast<const B2HitsSet&>(obj);
  return os;
}

void B2ClusterSummary::AddHit(B2HitSummary &hit) {
  B2HitsSet::AddHit(hit);
  hit.SetParentCluster(this);
  hit.SetParentClusterId(cluster_id_);
}

void B2ClusterSummary::AddHit(const B2HitSummary &hit) {
  B2HitsSet::AddHit(hit);
}

void B2ClusterSummary::AddHit(B2HitSummary *hit) {
  B2ClusterSummary::AddHit(*hit);
}

void B2ClusterSummary::AddHit(const B2HitSummary *hit) {
  B2HitsSet::AddHit(*hit);
}

UInt_t B2ClusterSummary::GetClusterId() const {
  return cluster_id_;
}

void B2ClusterSummary::SetClusterId(UInt_t cluster_id) {
  cluster_id_ = cluster_id;
}

Bool_t B2ClusterSummary::IsGhost() {
  if (parent_track_.IsValid() || parent_track_id_ != 0)
    is_ghost_ = kFALSE;
  return is_ghost_;
}

void B2ClusterSummary::Ghostify() {
  is_ghost_ = kTRUE;
  SetParentTrack(nullptr);
  SetParentTrackId(0);
}

ClassImp(B2ClusterSummary)