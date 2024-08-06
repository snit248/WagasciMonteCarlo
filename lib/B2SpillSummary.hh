//
// Created by Giorgio Pintaudi on 8/17/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2SPILLSUMMARY_HH
#define WAGASCIBABYMINDMONTECARLO_B2SPILLSUMMARY_HH

#include <TObject.h>
#include <TClonesArray.h>
#include <TVector3.h>
#include <TRef.h>
#include <TTree.h>

#include "B2Measurement.hh"
#include "B2BeamSummary.hh"


///> name of the spill tree
extern const std::string WAGASCI_TREE_NAME;

///> name of the SL tree
extern const std::string NEUT_TREE_NAME;

///> name of the SL tree
extern const std::string REWEIGHT_TREE_NAME;

extern std::atomic<UInt_t> RECON_CLUSTER_ID;
extern std::atomic<UInt_t> RECON_TRACK_ID;

class B2EmulsionSummary;

class B2HitSummary;

class B2ClusterSummary;

class B2TrackSummary;

class B2VertexSummary;

class B2EventSummary;

class B2SpillSummary : public TObject {

public:

  /**
   * Wrapper around TIter for the B2SpillSummary member hits_ that is a B2RefArray of all
   * the hits of the event.
   */
  class B2HitIterator : public TIter {
  public:
    explicit B2HitIterator(const B2SpillSummary &obj);

    explicit B2HitIterator(const B2SpillSummary *obj);

    /*
     * Return the next hit of the event
     */
    B2HitSummary *Next();
  };

  /**
   * Const version of B2HitIterator
   */
  class B2HitConstIterator : public TIter {
  public:
    explicit B2HitConstIterator(const B2SpillSummary &obj);

    explicit B2HitConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next hit of the event
     */
    const B2HitSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member clusters_ that is a B2RefArray of all
   * the clusters of the event.
   */
  class B2TrueClusterIterator : public TIter {
  public:
    explicit B2TrueClusterIterator(const B2SpillSummary &obj);

    explicit B2TrueClusterIterator(const B2SpillSummary *obj);

    /*
     * Return the next cluster of the event
     */
    B2ClusterSummary *Next();
  };

  /**
   * Const version of B2TrueClusterIterator
   */
  class B2TrueClusterConstIterator : public TIter {
  public:
    explicit B2TrueClusterConstIterator(const B2SpillSummary &obj);

    explicit B2TrueClusterConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next cluster of the event
     */
    const B2ClusterSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member tracks_ that is a B2RefArray of all
   * the tracks of the event.
   */
  class B2TrueTrackIterator : public TIter {
  public:
    explicit B2TrueTrackIterator(const B2SpillSummary &obj);

    explicit B2TrueTrackIterator(const B2SpillSummary *obj);

    /*
     * Return the next track of the event
     */
    B2TrackSummary *Next();
  };

  /**
   * Const version of B2TrueTrackIterator
   */
  class B2TrueTrackConstIterator : public TIter {
  public:
    explicit B2TrueTrackConstIterator(const B2SpillSummary &obj);

    explicit B2TrueTrackConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next track of the event
     */
    const B2TrackSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member vertices_ that is a B2RefArray of all
   * the vertices of the event.
   */
  class B2TrueVertexIterator : public TIter {
  public:
    explicit B2TrueVertexIterator(const B2SpillSummary &obj);

    explicit B2TrueVertexIterator(const B2SpillSummary *obj);

    /*
     * Return the next vertex of the event
     */
    B2VertexSummary *Next();
  };

  /**
   * Const version of B2TrueVertexIterator
   */
  class B2TrueVertexConstIterator : public TIter {
  public:
    explicit B2TrueVertexConstIterator(const B2SpillSummary &obj);

    explicit B2TrueVertexConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next vertex of the event
     */
    const B2VertexSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member vertices_ that is a B2RefArray of all
   * the vertices of the event.
   */
  class B2TrueEventIterator : public TIter {
  public:
    explicit B2TrueEventIterator(const B2SpillSummary &obj);

    explicit B2TrueEventIterator(const B2SpillSummary *obj);

    /*
     * Return the next event of the event
     */
    B2EventSummary *Next();
  };

  /**
   * Const version of B2TrueEventIterator
   */
  class B2TrueEventConstIterator : public TIter {
  public:
    explicit B2TrueEventConstIterator(const B2SpillSummary &obj);

    explicit B2TrueEventConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next event of the event
     */
    const B2EventSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member clusters_ that is a B2RefArray of all
   * the clusters of the event.
   */
  class B2ReconClusterIterator : public TIter {
  public:
    explicit B2ReconClusterIterator(const B2SpillSummary &obj);

    explicit B2ReconClusterIterator(const B2SpillSummary *obj);

    /*
     * Return the next cluster of the event
     */
    B2ClusterSummary *Next();
  };

  /**
   * Const version of B2ReconClusterIterator
   */
  class B2ReconClusterConstIterator : public TIter {
  public:
    explicit B2ReconClusterConstIterator(const B2SpillSummary &obj);

    explicit B2ReconClusterConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next cluster of the event
     */
    const B2ClusterSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member tracks_ that is a B2RefArray of all
   * the tracks of the event.
   */
  class B2ReconTrackIterator : public TIter {
  public:
    explicit B2ReconTrackIterator(const B2SpillSummary &obj);

    explicit B2ReconTrackIterator(const B2SpillSummary *obj);

    /*
     * Return the next track of the event
     */
    B2TrackSummary *Next();
  };

  /**
   * Const version of B2ReconTrackIterator
   */
  class B2ReconTrackConstIterator : public TIter {
  public:
    explicit B2ReconTrackConstIterator(const B2SpillSummary &obj);

    explicit B2ReconTrackConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next track of the event
     */
    const B2TrackSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member vertices_ that is a B2RefArray of all
   * the vertices of the event.
   */
  class B2ReconVertexIterator : public TIter {
  public:
    explicit B2ReconVertexIterator(const B2SpillSummary &obj);

    explicit B2ReconVertexIterator(const B2SpillSummary *obj);

    /*
     * Return the next vertex of the event
     */
    B2VertexSummary *Next();
  };

  /**
   * Const version of B2ReconVertexIterator
   */
  class B2ReconVertexConstIterator : public TIter {
  public:
    explicit B2ReconVertexConstIterator(const B2SpillSummary &obj);

    explicit B2ReconVertexConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next vertex of the event
     */
    const B2VertexSummary *Next();
  };

  /**
   * Wrapper around TIter for the B2SpillSummary member vertices_ that is a B2RefArray of all
   * the vertices of the event.
   */
  class B2ReconEventIterator : public TIter {
  public:
    explicit B2ReconEventIterator(const B2SpillSummary &obj);

    explicit B2ReconEventIterator(const B2SpillSummary *obj);

    /*
     * Return the next event of the event
     */
    B2EventSummary *Next();
  };

  /**
   * Const version of B2ReconEventIterator
   */
  class B2ReconEventConstIterator : public TIter {
  public:
    explicit B2ReconEventConstIterator(const B2SpillSummary &obj);

    explicit B2ReconEventConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next event of the event
     */
    const B2EventSummary *Next();
  };

  /**
   * Return an TIter iterator pointing to the first hit of the event
   * @return wrapper around TIter
   */
  B2HitIterator BeginHit();

  /**
   * Return an TIter iterator pointing to the first hit of the event
   * @return wrapper around TIter
   */
  B2HitConstIterator BeginHit() const;

  /**
   * Return an TIter iterator pointing to the first cluster of the event
   * @return wrapper around TIter
   */
  B2TrueClusterIterator BeginTrueCluster();

  /**
   * Return an TIter iterator pointing to the first cluster of the event
   * @return wrapper around TIter
   */
  B2TrueClusterConstIterator BeginTrueCluster() const;

  /**
   * Return an TIter iterator pointing to the first track of the event
   * @return wrapper around TIter
   */
  B2TrueTrackIterator BeginTrueTrack();

  /**
   * Return an TIter iterator pointing to the first track of the event
   * @return wrapper around TIter
   */
  B2TrueTrackConstIterator BeginTrueTrack() const;

  /**
   * Return an TIter iterator pointing to the first vertex of the event
   * @return wrapper around TIter
   */
  B2TrueVertexIterator BeginTrueVertex();

  /**
   * Return an TIter iterator pointing to the first vertex of the event
   * @return wrapper around TIter
   */
  B2TrueVertexConstIterator BeginTrueVertex() const;

  /**
   * @return first true vertex
   */
  B2VertexSummary &FirstTrueVertex();

  /**
   * @return first true vertex
   */
  const B2VertexSummary &FirstTrueVertex() const;


  /**
   * Return an TIter iterator pointing to the first event of the event
   * @return wrapper around TIter
   */
  B2TrueEventIterator BeginTrueEvent();

  /**
   * Return an TIter iterator pointing to the first event of the event
   * @return wrapper around TIter
   */
  B2TrueEventConstIterator BeginTrueEvent() const;

  /**
   * @return first true event
   */
  B2EventSummary &FirstTrueEvent();

  /**
   * @return first true event
   */
  const B2EventSummary &FirstTrueEvent() const;

  /**
   * Return an TIter iterator pointing to the first cluster of the event
   * @return wrapper around TIter
   */
  B2ReconClusterIterator BeginReconCluster();

  /**
   * Return an TIter iterator pointing to the first cluster of the event
   * @return wrapper around TIter
   */
  B2ReconClusterConstIterator BeginReconCluster() const;

  /**
   * Return an TIter iterator pointing to the first track of the event
   * @return wrapper around TIter
   */
  B2ReconTrackIterator BeginReconTrack();

  /**
   * Return an TIter iterator pointing to the first track of the event
   * @return wrapper around TIter
   */
  B2ReconTrackConstIterator BeginReconTrack() const;

  /**
   * Return an TIter iterator pointing to the first vertex of the event
   * @return wrapper around TIter
   */
  B2ReconVertexIterator BeginReconVertex();

  /**
   * Return an TIter iterator pointing to the first vertex of the event
   * @return wrapper around TIter
   */
  B2ReconVertexConstIterator BeginReconVertex() const;

  /**
   * Return an TIter iterator pointing to the first event of the event
   * @return wrapper around TIter
   */
  B2ReconEventIterator BeginReconEvent();

  /**
   * Return an TIter iterator pointing to the first event of the event
   * @return wrapper around TIter
   */
  B2ReconEventConstIterator BeginReconEvent() const;

  /**
   * Allocate memory for all the hits, clusters, vertices, tracks, etc..
   */
  B2SpillSummary();

  /**
   * Swap function for the copy-swap idiom
   * @param lhs left hand side object
   * @param rhs right hand side object
   */
  friend void Swap(B2SpillSummary &lhs, B2SpillSummary &rhs);

  /**
   * Copy constructor
   */
  B2SpillSummary(const B2SpillSummary &spill);

  /**
   * Copy assignment operator
   */
  B2SpillSummary &operator=(B2SpillSummary other);

  /**
   * Move constructor
   * @param other other object
   */
  B2SpillSummary(B2SpillSummary &&other) noexcept: B2SpillSummary() {
    Swap(*this, other);
  }

  /**
   * Free the memory of the TClonesArray
   */
  ~B2SpillSummary() override;

  /**
   * Clear the TClonesArray without releasing the memory
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;


  /**
   * Append a hit to the list of hits. Warning: the passed hit is not directly added
   * but a new hit is copy constructed.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2HitSummary &AddHit(const B2HitSummary *hit);

  /**
   * Append a hit to the list of hits. Warning: the passed hit is not directly added
   * but a new hit is copy constructed.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2HitSummary &AddHit(const B2HitSummary &hit);

  /**
   * Append a hit to the list of hits. The newly added hit is in uninitialized state.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2HitSummary &AddHit();

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
   * @param id hit ID
   * @return true if has hit with hit ID
   */
  bool HasHit(UInt_t id) const;

  /**
   * @return TClonesArray containing all of the hits
   */
  const TClonesArray &GetHits() const;

  /**
   * Append a cluster to the list of clusters. Warning: the passed cluster is not directly added
   * but a new cluster is copy constructed.
   *
   * @param cluster cluster to copy
   * @return reference to newly constructed cluster
   */
  B2ClusterSummary &AddTrueCluster(const B2ClusterSummary *cluster);

  /**
   * Append a cluster to the list of clusters. Warning: the passed cluster is not directly added
   * but a new cluster is copy constructed.
   *
   * @param cluster cluster to copy
   * @return reference to newly constructed cluster
   */
  B2ClusterSummary &AddTrueCluster(const B2ClusterSummary &cluster);

  /**
   * Append a cluster to the list of clusters. The newly added cluster is in uninitialized state.
   *
   * @param cluster cluster to copy
   * @return reference to newly constructed cluster
   */
  B2ClusterSummary &AddTrueCluster();

  /**
   * @param id hash of the cluster
   * @return cluster with ID equal to id
   */
  B2ClusterSummary &GetTrueCluster(UInt_t id);

  /**
   * @param id hash of the cluster
   * @return cluster with ID equal to id
   */
  const B2ClusterSummary &GetTrueCluster(UInt_t id) const;

  /**
   * @return TClonesArray containing all of the clusters
   */
  const TClonesArray &GetTrueClusters() const;

  /**
   * @return TClonesArray containing all of the clusters
   */
  TClonesArray &GetTrueClusters();

  /**
   * @param id cluster ID
   * @return true if has cluster with cluster ID
   */
  bool HasTrueCluster(UInt_t id) const;

  /**
   * Append a track to the list of tracks. Warning: the passed track is not directly added
   * but a new track is copy constructed.
   *
   * @param track track to copy
   * @return reference to newly constructed track
   */
  B2TrackSummary &AddTrueTrack(const B2TrackSummary *track);

  /**
   * Append a track to the list of tracks. Warning: the passed track is not directly added
   * but a new track is copy constructed.
   *
   * @param track track to copy
   * @return reference to newly constructed track
   */
  B2TrackSummary &AddTrueTrack(const B2TrackSummary &track);

  /**
   * Append a track to the list of tracks. The newly added track is in uninitialized state.
   *
   * @param track track to copy
   * @return reference to newly constructed track
   */
  B2TrackSummary &AddTrueTrack();

  /**
   * @param id hash of the track
   * @return track with ID equal to id
   */
  B2TrackSummary &GetTrueTrack(UInt_t id);

  /**
   * @param id hash of the track
   * @return track with ID equal to id
   */
  const B2TrackSummary &GetTrueTrack(UInt_t id) const;

  /**
   * @param id track ID
   * @return true if has track with track ID
   */
  bool HasTrueTrack(UInt_t id) const;

  /**
   * @return TClonesArray containing all of the tracks
   */
  const TClonesArray &GetTrueTracks() const;

  /**
   * @return TClonesArray containing all of the tracks
   */
  TClonesArray &GetTrueTracks();

  /**
   * @param id hash of the vertex
   * @return vertex with ID equal to id
   */
  B2VertexSummary &GetTrueVertex(UInt_t id);

  /**
   * @param id hash of the vertex
   * @return vertex with ID equal to id
   */
  const B2VertexSummary &GetTrueVertex(UInt_t id) const;

  /**
   * @param id vertex ID
   * @return true if has vertex with vertex ID
   */
  bool HasTrueVertex(UInt_t id) const;

  /**
   * Append a vertex to the list of vertices. Warning: the passed vertex is not directly added
   * but a new vertex is copy constructed.
   *
   * @param vertex vertex to copy
   * @return reference to newly constructed vertex
   */
  B2VertexSummary &AddTrueVertex(const B2VertexSummary *vertex);

  /**
   * Append a vertex to the list of vertices. Warning: the passed vertex is not directly added
   * but a new vertex is copy constructed.
   *
   * @param vertex vertex to copy
   * @return reference to newly constructed vertex
   */
  B2VertexSummary &AddTrueVertex(const B2VertexSummary &vertex);

  /**
   * Append a vertex to the list of vertices. The newly added vertex is in uninitialized state.
   *
   * @param vertex vertex to copy
   * @return reference to newly constructed vertex
   */
  B2VertexSummary &AddTrueVertex();

  /**
   * @param position position of the vertex in mm (approximate)
   * @param cut how near the vertex can be to the position in mm
   * @return closest vertex to the position
   */
  B2VertexSummary &GetTrueVertex(const TVector3 &position, Double_t cut = 10);

  /**
   * @param position position of the vertex in mm (approximate)
   * @param cut how near the vertex can be to the position in mm
   * @return closest vertex to the position
   */
  const B2VertexSummary &GetTrueVertex(const TVector3 &position, Double_t cut = 10) const;

  /**
   * @return TClonesArray containing all of the vertices
   */
  const TClonesArray &GetTrueVertices() const;

  /**
   * Append a hit to the list of hits. Warning: the passed hit is not directly added
   * but a new hit is copy constructed.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2EventSummary &AddTrueEvent(const B2EventSummary *event);

  /**
   * Append a hit to the list of hits. Warning: the passed hit is not directly added
   * but a new hit is copy constructed.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2EventSummary &AddTrueEvent(const B2EventSummary &event);

  /**
   * Append a hit to the list of hits. The newly added hit is in uninitialized state.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2EventSummary &AddTrueEvent();

  /**
   * @return TClonesArray containing all of the events
   */
  const TClonesArray &GetTrueEvents() const;

  /**
   * Append a cluster to the list of clusters. Warning: the passed cluster is not directly added
   * but a new cluster is copy constructed.
   *
   * @param cluster cluster to copy
   * @return reference to newly constructed cluster
   */
  B2ClusterSummary &AddReconCluster(const B2ClusterSummary *cluster);

  /**
   * Append a cluster to the list of clusters. Warning: the passed cluster is not directly added
   * but a new cluster is copy constructed.
   *
   * @param cluster cluster to copy
   * @return reference to newly constructed cluster
   */
  B2ClusterSummary &AddReconCluster(const B2ClusterSummary &cluster);

  /**
   * Append a cluster to the list of clusters. The newly added cluster is in uninitialized state.
   *
   * @param cluster cluster to copy
   * @return reference to newly constructed cluster
   */
  B2ClusterSummary &AddReconCluster();

  /**
   * @return TClonesArray containing all of the clusters
   */
  const TClonesArray &GetReconClusters() const;

  /**
   * @return TClonesArray containing all of the clusters
   */
  TClonesArray &GetReconClusters();

  /**
   * @param id hash of the cluster
   * @return cluster with ID equal to id
   */
  B2ClusterSummary &GetReconCluster(UInt_t id);

  /**
   * @param id hash of the cluster
   * @return cluster with ID equal to id
   */
  const B2ClusterSummary &GetReconCluster(UInt_t id) const;

  /**
   * @param id cluster ID
   * @return true if has cluster with cluster ID
   */
  bool HasReconCluster(UInt_t id) const;

  /**
   * Append a track to the list of tracks. Warning: the passed track is not directly added
   * but a new track is copy constructed.
   *
   * @param track track to copy
   * @return reference to newly constructed track
   */
  B2TrackSummary &AddReconTrack(const B2TrackSummary *track);

  /**
   * Append a track to the list of tracks. Warning: the passed track is not directly added
   * but a new track is copy constructed.
   *
   * @param track track to copy
   * @return reference to newly constructed track
   */
  B2TrackSummary &AddReconTrack(const B2TrackSummary &track);

  /**
   * Append a track to the list of tracks. The newly added track is in uninitialized state.
   *
   * @param track track to copy
   * @return reference to newly constructed track
   */
  B2TrackSummary &AddReconTrack();

  /**
   * @return TClonesArray containing all of the tracks
   */
  const TClonesArray &GetReconTracks() const;

  /**
   * @return TClonesArray containing all of the tracks
   */
  TClonesArray &GetReconTracks();

  /**
   * @param id hash of the track
   * @return track with ID equal to id
   */
  B2TrackSummary &GetReconTrack(UInt_t id);

  /**
   * @param id hash of the track
   * @return track with ID equal to id
   */
  const B2TrackSummary &GetReconTrack(UInt_t id) const;

  /**
   * @param id track ID
   * @return true if has track with track ID
   */
  bool HasReconTrack(UInt_t id) const;

  /**
   * Append a vertex to the list of vertices. Warning: the passed vertex is not directly added
   * but a new vertex is copy constructed.
   *
   * @param vertex vertex to copy
   * @return reference to newly constructed vertex
   */
  B2VertexSummary &AddReconVertex(const B2VertexSummary *vertex);

  /**
   * Append a vertex to the list of vertices. Warning: the passed vertex is not directly added
   * but a new vertex is copy constructed.
   *
   * @param vertex vertex to copy
   * @return reference to newly constructed vertex
   */
  B2VertexSummary &AddReconVertex(const B2VertexSummary &vertex);

  /**
   * Append a vertex to the list of vertices. The newly added vertex is in uninitialized state.
   *
   * @param vertex vertex to copy
   * @return reference to newly constructed vertex
   */
  B2VertexSummary &AddReconVertex();

  /**
   * @param position position of the vertex in mm (approximate)
   * @param cut how near the vertex can be to the position in mm
   * @return closest vertex to the position
   */
  B2VertexSummary &GetReconVertex(const TVector3 &position, Double_t cut = 10);

  /**
   * @param position position of the vertex in mm (approximate)
   * @param cut how near the vertex can be to the position in mm
   * @return closest vertex to the position
   */
  const B2VertexSummary &GetReconVertex(const TVector3 &position, Double_t cut = 10) const;

  /**
   * @param id hash of the vertex
   * @return vertex with ID equal to id
   */
  B2VertexSummary &GetReconVertex(UInt_t id);

  /**
   * @param id hash of the vertex
   * @return vertex with ID equal to id
   */
  const B2VertexSummary &GetReconVertex(UInt_t id) const;

  /**
   * @return TClonesArray containing all of the vertices
   */
  const TClonesArray &GetReconVertices() const;

  /**
   * @param id vertex ID
   * @return true if has vertex with vertex ID
   */
  bool HasReconVertex(UInt_t id) const;

  /**
   * Append a hit to the list of hits. Warning: the passed hit is not directly added
   * but a new hit is copy constructed.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2EventSummary &AddReconEvent(const B2EventSummary *event);

  /**
   * Append a hit to the list of hits. Warning: the passed hit is not directly added
   * but a new hit is copy constructed.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2EventSummary &AddReconEvent(const B2EventSummary &event);

  /**
   * Append a hit to the list of hits. The newly added hit is in uninitialized state.
   *
   * @param hit hit to copy
   * @return reference to newly constructed hit
   */
  B2EventSummary &AddReconEvent();

  /**
   * @return TClonesArray containing all of the events
   */
  const TClonesArray &GetReconEvents() const;

  /**
   * @return beam summary object
   */
  B2BeamSummary &GetBeamSummary();

  /**
   * @return beam summary object
   */
  const B2BeamSummary &GetBeamSummary() const;

  /**
   * Remove a track from the list of tracks
   * @param track track to remove
   * @param clusters_too if true all the clusters belonging to the track are removed too
   */
  void RemoveTrueTrack(B2TrackSummary *track, Bool_t clusters_too = kFALSE);

  /**
   * Remove a cluster from the list of clusters
   * @param cluster cluster to remove
   */
  void RemoveTrueCluster(B2ClusterSummary *cluster);

  /**
   * Print spill summary information to output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2SpillSummary &obj);

  /**
   * @return number of hits in the spill
   */
  Int_t GetNumHits(B2Detector detector = B2Detector::kUnknownDetector) const;

  /**
   * @return number of true clusters in the spill
   */
  Int_t GetNumTrueClusters() const;

  /**
   * @return number of true tracks in the spill
   */
  Int_t GetNumTrueTracks() const;

  /**
   * @return number of true vertices in the spill
   */
  Int_t GetNumTrueVertices() const;

  /**
   * @return number of true neutrino events in the spill
   */
  Int_t GetNumTrueEvents() const;

  /**
   * @return number of reconstructed clusters in the spill
   */
  Int_t GetNumReconClusters() const;

  /**
   * @return number of reconstructed tracks in the spill
   */
  Int_t GetNumReconTracks() const;

  /**
   * @return number of reconstructed vertices in the spill
   */
  Int_t GetNumReconVertices() const;

  /**
   * @return number of reconstructed neutrino events in the spill
   */
  Int_t GetNumReconEvents() const;

  /**
   * Create a branch called "spill" containing the current B2SPillSummary object
   * @param ttree
   */
  void CreateBranch(TTree &ttree);

  /**
   * Search for the closest hit to the vertex position
   * @param pos vertex absolute position
   * @param distance_cut maximum distance allowed between the hit and pos
   * @return closest hit (nullptr in case of failure)
   */
  B2HitSummary *SearchClosestHit(const TVector3 &pos, Double_t distance_cut);

  /**
   * Wrapper around TIter for the B2EmulsionSummary member emulsions_ that is a B2RefArray of all
   * the hits of the event.
   */
  class B2EmulsionIterator : public TIter {
  public:
    explicit B2EmulsionIterator(const B2SpillSummary &obj);

    explicit B2EmulsionIterator(const B2SpillSummary *obj);

    /*
     * Return the next hit of the event
     */
    B2EmulsionSummary *Next();
  };

  /**
   * Const version of B2EmulsionIterator
   */
  class B2EmulsionConstIterator : public TIter {
  public:
    explicit B2EmulsionConstIterator(const B2SpillSummary &obj);

    explicit B2EmulsionConstIterator(const B2SpillSummary *obj);

    /*
     * Return the next hit of the event
     */
    const B2EmulsionSummary *Next();
  };

  /**
   * Return an TIter iterator pointing to the first emulsion track of the event
   * @return wrapper around TIter
   */
  B2EmulsionIterator BeginEmulsion();

  /**
   * Return an TIter iterator pointing to the first emulsion track of the event
   * @return wrapper around TIter
   */
  B2EmulsionConstIterator BeginEmulsion() const;


  /**
   * Append an emulsion track to the list of emulsion tracks.
   * Warning: the passed track is not directly added
   * but a new emulsion track is copy constructed.
   *
   * @param emulsion emulsion track to copy
   * @return reference to newly constructed emulsion track
   */
  B2EmulsionSummary &AddEmulsion(const B2EmulsionSummary *emulsion);

  /**
   * Append an emulsion track to the list of emulsion tracks. 
   * Warning: the passed track is not directly added
   * but a new emulsion track is copy constructed.
   *
   * @param emulsion emulsion track to copy
   * @return reference to newly constructed emulsion track
   */
  B2EmulsionSummary &AddEmulsion(const B2EmulsionSummary &emulsion);

  /**
   * Append an emulsion track to the list of emulsion tracks.
   * The newly added emulsion track is in uninitialized state.
   *
   * @return reference to newly constructed emulsion track
   */
  B2EmulsionSummary &AddEmulsion();

  /**
   * @param id hash of the emulsion track
   * @return emulsion track with ID equal to id
   */
  B2EmulsionSummary &GetEmulsion(UInt_t id);

  /**
   * @param id hash of the emulsion track
   * @return hit with ID equal to id
   */
  const B2EmulsionSummary &GetEmulsion(UInt_t id) const;

  /**
   * @param id emulsion track ID
   * @return true if has emulsion track with emulsion track ID
   */
  bool HasEmulsion(UInt_t id) const;

  /**
   * @return TClonesArray containing all of the emulsion track
   */
  const TClonesArray &GetEmulsions() const;

  /**
   * @return TClonesArray containing all of the emulsion track
   */
  TClonesArray &GetEmulsions();

  /**
   * @return number of emulsion tracks in the spill
   */
  Int_t GetNumEmulsions() const;

private:

  ///> Maximum number of hits in a spill
  static const Int_t max_num_hits_ = 10000;
  ///> Maximum number of clusters in a spill
  static const Int_t max_num_clusters_ = max_num_hits_ / 10;
  ///> Maximum number of tracks in a spill
  static const Int_t max_num_tracks_ = max_num_hits_ / 10;
  ///> Maximum number of vertices in a spill
  static const Int_t max_num_vertices_ = max_num_hits_ / 10;
  ///> Maximum number of events (detected primary particles) in a spill
  static const Int_t max_num_events_ = max_num_vertices_ / 10;
  ///> Maximum number of emulsion tracks
  static const Int_t max_num_emulsions_ = 10000;

  ///> Number of hits
  Int_t num_hits_{};
  ///> Number of true clusters
  Int_t num_true_clusters_{};
  ///> Number of true tracks
  Int_t num_true_tracks_{};
  ///> Number of true vertices
  Int_t num_true_vertices_{};
  ///> Number of true events
  Int_t num_true_events_{};
  ///> Number of reconstructed clusters
  Int_t num_recon_clusters_{};
  ///> Number of reconstructed tracks
  Int_t num_recon_tracks_{};
  ///> Number of reconstructed vertices
  Int_t num_recon_vertices_{};
  ///> Number of reconstructed events
  Int_t num_recon_events_{};
  ///> Number of emulsion tracks
  Int_t num_emulsions_{};

  ///> List of hits
  TClonesArray *hits_;
  ///> List of true clusters
  TClonesArray *true_clusters_;
  ///> List of true tracks
  TClonesArray *true_tracks_;
  ///> List of true vertices
  TClonesArray *true_vertices_;
  ///> List of true events
  TClonesArray *true_events_;
  ///> List of reconstructed clusters
  TClonesArray *recon_clusters_;
  ///> List of reconstructed tracks
  TClonesArray *recon_tracks_;
  ///> List of reconstructed vertices
  TClonesArray *recon_vertices_;
  ///> List of reconstructed events
  TClonesArray *recon_events_;
  ///> List of emulsion tracks
  TClonesArray *emulsions_;

  ///> spill summary
  B2BeamSummary beam_summary_;

ClassDefOverride(B2SpillSummary, 5)

};

#endif //WAGASCIBABYMINDMONTECARLO_B2SPILLSUMMARY_HH
