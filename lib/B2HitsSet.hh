//
// Created by Giorgio Pintaudi on 8/27/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2HITSSET_HH
#define WAGASCIBABYMINDMONTECARLO_B2HITSSET_HH

#include <functional>

#include <TRef.h>
#include <TArrayI.h>

#include "B2Measurement.hh"
#include "B2RefArray.hh"


class B2HitSummary;

class B2TrackSummary;

class B2EventSummary;

namespace hit {
  using HitRef = std::reference_wrapper<const B2HitSummary>;
  using ComparatorAlongDirection = std::function<bool(const HitRef &left, const HitRef &right)>;
  using CardinalDirectionComparators = std::unordered_map<B2CardinalDirection, ComparatorAlongDirection, EnumClassHash>;
  extern const CardinalDirectionComparators CARDINAL_DIRECTION_COMPARATORS;
}

/**
 * Virtual class to manage a set of hits
 */
class B2HitsSet : public TObject {

public:

  /**
   * Initialize the protected members
   */
  B2HitsSet();

  /**
   * Wrapper around TIter
   */
  class B2HitIterator : public TObject {

  private:
    B2RefArrayIterator iterator_;
    B2RefArrayIterator end_;

  public:
    explicit B2HitIterator(B2HitsSet &obj);

    explicit B2HitIterator(B2HitsSet *obj);

    /*
     * Return the next hit
     */
    B2HitSummary *Next();
  };

  /**
   * Const version of B2HitIterator
   */
  class B2HitConstIterator : public TObject {

  private:
    B2RefArrayConstIterator iterator_;
    B2RefArrayConstIterator end_;

  public:
    explicit B2HitConstIterator(const B2HitsSet &obj);

    explicit B2HitConstIterator(const B2HitsSet *obj);

    /*
     * Return the next hit
     */
    const B2HitSummary *Next();
  };

  /**
   * Add a hit to the list of hits
   * @param hit hit to add
   */
  virtual void AddHit(const B2HitSummary &hit);

  /**
   * Add a hit to the list of hits
   * @param hit hit to add
   */
  virtual void AddHit(const B2HitSummary *hit);

  /**
   * Clear the hit list
   */
  void ClearHits();

  /**
   * @return list of hits
   */
  const B2RefArray &GetHits() const;

  /**
   * @return list of hits
   */
  B2RefArray &GetHits();

  /**
   * @param id hash of the hit
   * @return hit with ID equal to id
   */
  B2HitSummary &GetHit(UInt_t id);

  /**
   * @param id hash of the hit
   * @return hit with ID equal to id
   */
  const B2HitSummary &GetHit(UInt_t id) const;

  /**
   * @param other hit to look for
   * @return true if the hit was found
   */
  bool HasHit(const B2HitSummary *other) const;

  /**
   * Return an TIter iterator pointing to the first hit of the track
   * @return wrapper around TIter
   */
  B2HitIterator BeginHit();

  /**
   * Return an TIter iterator pointing to the first hit of the track
   * @return wrapper around TIter
   */
  B2HitConstIterator BeginHit() const;

  /**
   * @return most upstream hit
   */
  B2HitSummary &GetUpstreamHit();

  /**
   * @return most upstream hit
   */
  const B2HitSummary &GetUpstreamHit() const;

  /**
   * @return most downstream hit
   */
  B2HitSummary &GetDownstreamHit();

  /**
   * @return most downstream hit
   */
  const B2HitSummary &GetDownstreamHit() const;

  /**
   * @return first hit in time
   */
  B2HitSummary &GetFirstHit();

  /**
   * @return first hit in time
   */
  const B2HitSummary &GetFirstHit() const;

  /**
   * @return last hit in time
   */
  B2HitSummary &GetLastHit();

  /**
   * @return last hit in time
   */
  const B2HitSummary &GetLastHit() const;

  /**
   * @return extremal hit along direction
   */
  const B2HitSummary &GetHitAlongDirection(B2CardinalDirection direction, B2View view = B2View::kUnknownView,
                                           B2Detector detector = B2Detector::kUnknownDetector) const;

  /**
   * @return extremal hit along direction
   */
  B2HitSummary &GetHitAlongDirection(B2CardinalDirection direction, B2View view = B2View::kUnknownView,
                                     B2Detector detector = B2Detector::kUnknownDetector);

  /**
   * Clear internal state of the object
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;

  /**
   * Print object state to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2HitsSet &obj);

  /**
   * Set the parent track
   * @param track parent track
   */
  void SetParentTrack(const B2TrackSummary &track);

  /**
   * Set the parent track
   * @param track parent track
   */
  void SetParentTrack(const B2TrackSummary *track);

  /**
   * @return parent track
   */
  B2TrackSummary &GetParentTrack();

  /**
   * @return parent track
   */
  const B2TrackSummary &GetParentTrack() const;

  /**
   * @return parent track ID
   */
  UInt_t GetParentTrackId() const;

  /**
   * @param track_id parent track ID
   */
  void SetParentTrackId(UInt_t track_id);

  /**
   * @return true if there is a parent track
   */
  bool HasParentTrack() const;

  /**
   * @param event parent event
   */
  void SetParentEvent(const B2EventSummary &event);

  /**
   * @param event parent event
   */
  void SetParentEvent(const B2EventSummary *event);

  /**
   * @return parent event
   */
  B2EventSummary &GetParentEvent();

  /**
   * @return parent event
   */
  const B2EventSummary &GetParentEvent() const;

  /**
   * @return number of hits (the view and detector conditions are ANDed together)
   * @param view : count only hits in a certain view. If view == kUnknownView, hits from all view are counted
   * @param detector : count only in a certain detector. If detector == kUnknownDetector, hits from all detectors are
   * counted
   */
  Int_t GetNumHits(B2View view = B2View::kUnknownView, B2Detector detector = B2Detector::kUnknownDetector) const;

  /**
   * @return list of detectors crossed by the track
   */
  const TArrayI &GetDetectors() const;

  /**
   * Check if at least one hit is inside detector
   * @param detector detector ID
   */
  Bool_t HasDetector(B2Detector detector) const;

  /**
   * @return number of crossed detectors
   */
  Int_t GetNumDetectors() const;

  /**
   * @return PEU of the hit with the highest PEU
   */
  B2Measurement1D GetMaxPeu() const;

  /**
   * @return average PEU across all the hits
   */
  B2Measurement1D GetAveragePeu() const;

  /**
   * @return number of planes crossed by the track
   */
  Int_t GetNumActivePlanes() const;

  /**
   * @return angles of the track with respect to the zeta direction in top view and side view
   */
  const B2ViewAngle &GetViewAngle() const;

  /**
   * @param angle angles of the track with respect to the zeta direction in top view and side view
   */
  void SetViewAngle(const B2ViewAngle &angle);

  /**
   * @return angle of the track with respect to the zeta direction
   */
  const B2Angle &GetAngle() const;

  /**
   * @param angle angle of the track with respect to the zeta direction
   */
  void SetAngle(const B2Angle &angle);

  /**
   * @return track length
   */
  const B2Measurement1D &GetLength() const;

  /**
   * @param length track length
   */
  void SetLength(const B2Measurement1D &length);

  /**
   * @param length track length
   */
  void SetLength(Double_t length);

  /**
   * @return track view (may be top view, or side view, or unset)
   */
  Int_t GetView() const;

  /**
   * @param view track view (may be top view or side view)
   */
  void SetView(Int_t view);

  /**
   * @return Dimension of the cluster (2D or 3D)
   */
  B2Dimensionality GetDimensionality() const;

  /**
   * @param dimensionality Dimension of the cluster (2D or 3D)
   */
  void SetDimensionality(B2Dimensionality dimensionality);

  /**
   * @return bunch number
   */
  Int_t GetBunch() const;

  /**
   * @return true if it is a valid track
   */
  Bool_t IsValid() const;

  /**
   * Set the track as a valid one
   */
  void Validate();

  /**
   * Set the track as invalid
   */
  void Invalidate();

  /**
   * Reset parent track
   */
  void ResetParentTrack();

protected:

  ///> bunch number
  Int_t bunch_{};
  ///> TRef of the parent track the cluster belongs
  TRef parent_track_;
  ///> Geant4 ID of the parent track the cluster belongs
  UInt_t parent_track_id_{};
  ///> TRef of the parent event the cluster belongs
  TRef parent_event_;
  ///> view of the cluster if it is 2D
  Int_t view_{};
  ///> dimensionality of the cluster
  Int_t dimensionality_{};
  ///> List of references to the hits
  B2RefArray hits_;
  ///> ID of the most upstream hit
  Int_t num_hits_{};
  ///> list of detectors crossed by this cluster
  TArrayI detectors_;
  ///> angle with respect to the zeta direction. Refer to the B2Angle documentation.
  B2Angle angle_;
  ///> angles with respect to the zeta direction in top view and side view. Refer to the B2ViewAngle documentation.
  B2ViewAngle view_angle_;
  ///> sum of all the seqments of the track
  B2Measurement1D length_;
  ///> Flag to check if a track is valid or not
  Bool_t is_valid_{};

private:

  /**
   * check if detector is already present in the track and if not add it
   * @param detector detector ID to add
   */
  void AddDetector(B2Detector detector);

ClassDefOverride(B2HitsSet, 4)
};

#endif //WAGASCIBABYMINDMONTECARLO_B2HITSSET_HH
