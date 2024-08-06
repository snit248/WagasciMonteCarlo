//
// Created by neo on 8/15/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2CLUSTERSUMMARY_HH
#define WAGASCIBABYMINDMONTECARLO_B2CLUSTERSUMMARY_HH

// ROOT includes
#include <TObject.h>
#include <TRef.h>
#include "B2RefArray.hh"
#include <TVectorT.h>
#include <TIterator.h>

// Project includes
#include "B2Measurement.hh"
#include "B2HitsSet.hh"


class B2HitSummary;

class B2TrackSummary;

class B2EventSummary;

/*
 * Class describing a cluster of hits. A cluster is a set of hits that might or might not
 * be a candidate to form a track. It can span over multiple detectors. This class contains
 * just the general information about the cluster and is not meant to act on it. It is just
 * a storage class to be stored in a TTree.
 */
class B2ClusterSummary : public B2HitsSet {

public:

  /**
   * Clear the cluster object after construction
   */
  B2ClusterSummary();

  /**
   * Clear the cluster object (set all the members to B2_NON_INITIALIZED_VALUE)
   */
  void Clear(Option_t *option) override;

  /**
   * Print all the members value to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2ClusterSummary &obj);

  /**
   * @return Geant4 cluster ID
   */
  UInt_t GetClusterId() const;

  /**
   * @param cluster_id Geant4 cluster ID
   */
  void SetClusterId(UInt_t cluster_id);

  /**
   * Add a hit to the cluster
   * @param hit hit to add
   */
  void AddHit(B2HitSummary &hit);
  void AddHit(const B2HitSummary &hit) override;

  /**
   * Add a hit to the cluster
   * @param hit hit to add
   */
  void AddHit(B2HitSummary *hit);
  void AddHit(const B2HitSummary *hit) override;

  /**
   * @return if true the cluster is not associated to any track
   */
  Bool_t IsGhost();

  /**
   * make the cluster a ghost (the cluster is not associated with any track)
   */
  void Ghostify();

  /**
   * Return true if the two clusters are the same
   * @param lhs left hand side
   * @param rhs right hand side
   * @return true if the two clusters are the same
   */
  friend inline bool operator==(const B2ClusterSummary& lhs, const B2ClusterSummary& rhs) {
    return lhs.GetClusterId() == rhs.GetClusterId();
  }

private:

  ///> Geant4 ID of the cluster
  UInt_t cluster_id_{};
  ///> true if the cluster does not belong to any track
  Bool_t is_ghost_{};

ClassDefOverride(B2ClusterSummary, 4)
};

#endif //WAGASCIBABYMINDMONTECARLO_B2CLUSTERSUMMARY_HH