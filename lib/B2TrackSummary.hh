//
// Created by Giorgio Pintaudi on 8/16/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2TRACKSUMMARY_HH
#define WAGASCIBABYMINDMONTECARLO_B2TRACKSUMMARY_HH

// Standard includes
#include <map>
#include <iostream>

// ROOT includes
#include <TObject.h>
#include <TRef.h>
#include "B2RefArray.hh"
#include <TVectorT.h>
#include <TIterator.h>
#include <TPDGCode.h>

// Project includes
#include "B2Measurement.hh"
#include "B2HitsSet.hh"


class B2HitSummary;

class B2ClusterSummary;

class B2EventSummary;

class B2VertexSummary;

/*
 * Class describing a track due to a traveling particle.
 * Only the track initial state is described.
 */
class B2TrackSummary : public B2HitsSet {

public:

  /**
   * Wrapper around TIter for the B2TrackSummary member clusters_ that is a B2RefArray of all
   * the clusters of the track.
   */
  class B2ClusterIterator : public TObject {

  private:
    B2RefArrayIterator iterator_;
    B2RefArrayIterator end_;

  public:
    explicit B2ClusterIterator(B2TrackSummary &obj);

    explicit B2ClusterIterator(B2TrackSummary *obj);

    /*
     * Return the next cluster of the track
     */
    B2ClusterSummary *Next();
  };

  /**
   * Const version of B2TrueClusterIterator
   */
  class B2ClusterConstIterator : public TObject {

  private:
    B2RefArrayConstIterator iterator_;
    B2RefArrayConstIterator end_;

  public:
    explicit B2ClusterConstIterator(const B2TrackSummary &obj);

    explicit B2ClusterConstIterator(const B2TrackSummary *obj);

    /*
     * Return the next cluster of the track
     */
    const B2ClusterSummary *Next();
  };

  /**
   * Default constructor just clears the state of all the members
   */
  B2TrackSummary();

  /**
   * Clear the track object (set all the members to B2_NON_INITIALIZED_VALUE)
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;

  /**
   * Print all the members value to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2TrackSummary &obj);

  /**
   * Add hit to the track
   * @param hit hit
   */
  void AddHit(B2HitSummary &hit);
  void AddHit(const B2HitSummary &hit) override;

  /**
   * Add hit to the track
   * @param hit hit
   */
  void AddHit(B2HitSummary *hit);
  void AddHit(const B2HitSummary *hit) override;

  /**
   * Add a cluster to the list of clusters
   * @param cluster to add
   */
  void AddCluster(B2ClusterSummary &cluster, Bool_t add_hits);

  /**
   * Add a cluster to the list of clusters
   * @param cluster to add
   */
  void AddCluster(B2ClusterSummary *cluster, Bool_t add_hits);

  /**
   * Clear the cluster list
   */
  void ClearClusters();

  /**
   * @param id hash of the cluster
   * @return cluster with matching hash
   */
  B2ClusterSummary &GetCluster(UInt_t id);

  /**
   * @param id hash of the cluster
   * @return cluster with matching hash
   */
  const B2ClusterSummary &GetCluster(UInt_t id) const;

  /**
   * @param id Geant4 cluster ID
   * @return true if the track contains a cluster with cluster ID
   */
  bool HasCluster(UInt_t id) const;

  /**
   * Remove cluster from the list of clusters
   * @param cluster cluster to remove
   */
  void RemoveCluster(B2ClusterSummary *cluster);

  /**
   * @return list of clusters in the track
   */
  B2RefArray &GetClusters();

  /**
   * @return list of clusters in the track
   */
  const B2RefArray &GetClusters() const;

  /**
   * Return an TIter iterator pointing to the first cluster of the track
   * @return wrapper around TIter
   */
  B2ClusterIterator BeginCluster();

  /**
   * Return an TIter iterator pointing to the first cluster of the track
   * @return wrapper around TIter
   */
  B2ClusterConstIterator BeginCluster() const;


  /**
   * @return track Geant4 ID
   */
  UInt_t GetTrackId() const;

  /**
   * @param track_id track Geant4 ID
   */
  void SetTrackId(UInt_t track_id);

  /**
   * @param vertex parent vertex
   */
  void SetParentVertex(const B2VertexSummary &vertex);

  /**
   * @param vertex parent vertex
   */
  void SetParentVertex(const B2VertexSummary *vertex);

  /**
   * @return parent vertex
   */
  B2VertexSummary &GetParentVertex();

  /**
   * @return parent vertex
   */
  const B2VertexSummary &GetParentVertex() const;

  /**
   * @return particle mass in MeV/c^2
   */
  const B2Energy &GetMass() const;

  /**
   * @param mass particle mass in MeV/c^2
   */
  void SetMass(const B2Energy &mass);

  /**
   * @return initial total energy in MeV
   */
  const B2Energy &GetTotalEnergy() const;

  /**
   * @param total_energy initial total energy in MeV
   */
  void SetTotalEnergy(const B2Energy &total_energy);

  /**
   * @return initial kinetic energy in MeV
   */
  const B2Energy &GetKineticEnergy() const;

  /**
   * @param kinetic_energy initial kinetic energy in Mev
   */
  void SetKineticEnergy(const B2Energy &kinetic_energy);

  /**
   * @return initial 3-momentum in MeV/c
   */
  const B2Momentum &GetInitialMomentum() const;

  /**
   * @param initial_momentum initial 3-momentum in MeV/c
   */
  void SetInitialMomentum(const B2Momentum &initial_momentum);

  /**
   * @return initial absolute momentum in MeV/c
   */
  const B2Measurement1D &GetInitialAbsoluteMomentum() const;

  /**
   * @param initial_absolute_momentum initial absolute momentum in MeV/c
   */
  void SetInitialAbsoluteMomentum(const B2Measurement1D &initial_absolute_momentum);

  /**
   * @return initial position in mm
   */
  const B2Position &GetInitialPosition() const;

  /**
   * @param initial_position initial position in mm
   */
  void SetInitialPosition(const B2Position &initial_position);

  /**
   * @return initial direction versor
   */
  const B2Direction &GetInitialDirection() const;

  /**
   * @param initial_direction initial direction versor
   */
  void SetInitialDirection(const B2Direction &initial_direction);

  /**
   * @return final 3-momentum in MeV/c
   */
  const B2Momentum &GetFinalMomentum() const;

  /**
   * @param final_momentum final 3-momentum in MeV/c
   */
  void SetFinalMomentum(const B2Momentum &final_momentum);

  /**
   * @return final absolute momentum in MeV/c
   */
  const B2Measurement1D &GetFinalAbsoluteMomentum() const;

  /**
   * @param final_absolute_momentum final absolute momentum in MeV/c
   */
  void SetFinalAbsoluteMomentum(const B2Measurement1D &final_absolute_momentum);

  /**
   * @return final position (world coordinates) in mm
   */
  const B2Position &GetFinalPosition() const;

  /**
   * @param final_position final position (world coordinates) in mm
   */
  void SetFinalPosition(const B2Position &final_position);

  /**
   * @return final direction versor
   */
  const B2Direction &GetFinalDirection() const;

  /**
   * @param final_direction final direction versor
   */
  void SetFinalDirection(const B2Direction &final_direction);

  /**
   * @return particle PDG ID
   */
  PDG_t GetParticlePdg() const;

  /**
   * @param particle_pdg particle PDG ID
   */
  void SetParticlePdg(PDG_t particle_pdg);

  /**
   * @return type of track (primary track, secondary track, etc...)
   */
  B2TrackType GetTrackType() const;

  /**
   * @param type type of track (primary track, secondary track, etc...)
   */
  void SetTrackType(B2TrackType type);

  /**
   * @return type of primary track (matching track, sigular track, etc...)
   */
  B2PrimaryTrackType GetPrimaryTrackType() const;

  /**
   * @param primarytype type of track (matching track, sigular track, etc...)
   */
  void SetPrimaryTrackType(B2PrimaryTrackType primarytype);

  /**
   * @return type of secondary track (Michel electron, etc...)
   */
  B2SecondaryTrackType GetSecondaryTrackType() const;

  /**
   * @param secondarytype type of track (Michel electron, etc...)
   */
  void SetSecondaryTrackType(B2SecondaryTrackType secondarytype);

  /**
   * @return number of clusters in the track
   */
  Int_t GetNumClusters() const;

  /**
   * @param mass rest mass of the particle in MeV/c^2
   */
  void SetMass(Double_t mass);

  /**
   * @param total_energy initial total energy of the particle in MeV
   */
  void SetTotalEnergy(Double_t total_energy);

  /**
   * @param kinetic_energy initial kinetic energy of the particle in MeV
   */
  void SetKineticEnergy(Double_t kinetic_energy);

  /**
   * @param initial_momentum initial 3-momentum in MeV/c
   */
  void SetInitialMomentum(const TVector3 &initial_momentum);

  /**
   * @param initial_absolute_momentum initial absolute momentum in MeV/c
   */
  void SetInitialAbsoluteMomentum(Double_t initial_absolute_momentum);

  /**
   * @param initial_position initial position (in world coordinates) in mm
   */
  void SetInitialPosition(const TVector3 &initial_position);

  /**
   * @param final_momentum final 3-momentum in MeV/c
   */
  void SetFinalMomentum(const TVector3 &final_momentum);

  /**
   * @param final_absolute_momentum final absolute momentum in MeV
   */
  void SetFinalAbsoluteMomentum(Double_t final_absolute_momentum);

  /**
   * @param final_position final position (in world coordinates) in mm
   */
  void SetFinalPosition(const TVector3 &final_position);

  /**
   * @param final_direction final direction versor
   */
  void SetFinalDirection(const TVector3 &final_direction);

  /**
   * @param initial_direction initial direction versor
   */
  void SetInitialDirection(const TVector3 &initial_direction);

  /**
   * @param stop_mrd MRD the particle stops
   */
  void SetStopMrd(B2Detector stop_mrd);

  /**
   * @return the MRD the particle stops 
   */
  B2Detector GetStopMrd() const;

  /**
   * @param match_mrd MRD the particle is matched with
   */
  void SetMatchMrd(B2Detector match_mrd);

  /**
   * @return the MRD the particle is matched with
   */
  B2Detector GetMatchMrd() const;

  /**
   * @return true if the particle is stopping inside the detector
   */
  Bool_t GetIsStopping() const;

  /**
   * @param is_stopping true if the particle is stopping inside the detector
   */
  void SetIsStopping(Bool_t is_stopping);

  /**
   * @return true if the particle starts inside fiducial volume
   */
  Bool_t GetIsFiducialVolume() const;

  /**
   * @param is_stopping true if the particle starts inside fiducial volume
   */
  void SetIsFiducialVolume(Bool_t is_fiducial_volume);

  /** @param return chisquare value in sequential fitting assuming charge -
   */
  Double_t GetNegativeLogLikelihoodMinus() const;

  /** @param set chisquare value in sequential fitting assuming charge -
   */
  void SetNegativeLogLikelihoodMinus(Double_t negative_log_likelihood_minus);

  /** @param return chisquare value in sequential fitting assuming charge +
   */
  Double_t GetNegativeLogLikelihoodPlus() const;

  /** @param return chisquare value in sequential fitting assuming charge +
   */
  void SetNegativeLogLikelihoodPlus(Double_t negative_log_likelihood_plus);

  /** @param return the Muon Confidence Level in Proton Module
   */

  Double_t GetMuclPM() const;

  /** @param Muon Confidence Level in Proton Module
   */
  void SetMuclPM(Double_t mucl);

  /** @param return the Muon Confidence Level in Wagasci Upstream
   */

  Double_t GetMuclUWG() const;

  /** @param Muon Confidence Level in Wagasci Upstream
   */
  void SetMuclUWG(Double_t mucl);

  /** @param return the Muon Confidence Level in Wagasci Downstream
   */

  Double_t GetMuclDWG() const;

  /** @param Muon Confidence Level in Wagasci Downstream
   */
  void SetMuclDWG(Double_t mucl);

  /** @param Total Track Length 
   */
  void SetTrackLengthTotal(Double_t total_length_total);

  /** @param return Total Track Length
   */
  Double_t GetTrackLengthTotal() const;

  /**
   * @return detector where the track originates
   */
  B2Detector GetInitialDetector() const;

  /**
   * @return detector where the track stops or escapes
   */
  B2Detector GetFinalDetector() const;

  /** @param Reconstructed momentum by range
   */
  void SetReconMomByRange(Double_t recon_mom_by_range);

  /** @param Reconstructed momentum by range 
   */
  Double_t GetReconMomByRange() const;

  /** @param Reconstructed momentum by curvature
   */
  void SetReconMomByCurve(Double_t recon_mom_by_curve);

  /** @param return Reconstructed momentum by curvature
   */
  Double_t GetReconMomByCurve() const;


  /**
   * Return true if the tracks are the same
   * @param lhs left hand side
   * @param rhs right hand side
   * @return true if the tracks are the same
   */
  friend inline bool operator==(const B2TrackSummary &lhs, const B2TrackSummary &rhs) {
    return lhs.GetTrackId() == rhs.GetTrackId();
  }

private:

  ///> clusters of the track
  B2RefArray clusters_;
  ///> TRef of the parent vertex
  TRef parent_vertex_;
  ///> Geant4 ID of the parent vertex
  UInt_t track_id_{};
  ///> number of clusters of the track
  Int_t num_clusters_{};
  ///> Particle mass (MeV/c2)
  B2Energy mass_;
  ///> initial total energy of the particle (MeV)
  B2Energy total_energy_;
  ///> initial total kinetic energy of the particle (MeV)
  B2Energy kinetic_energy_;
  ///> initial momentum of the particle (MeV/v)
  B2Momentum initial_momentum_;
  ///> initial absolute momentum of the particle (MeV/c)
  B2Measurement1D initial_absolute_momentum_;
  ///> initial position in mm
  B2Position initial_position_;
  ///> initial direction of the particle
  B2Direction initial_direction_;
  ///> final momentum of the particle (MeV/c)
  B2Momentum final_momentum_;
  ///> final absolute momentum of the particle (MeV/c)
  B2Measurement1D final_absolute_momentum_;
  ///> final position in mm
  B2Position final_position_;
  ///> final direction of the particle
  B2Direction final_direction_;
  ///> particle PDG ID
  Int_t particle_pdg_{};
  ///> Type of tracked particle (B2TrackedParticle enum)
  Int_t type_{};
  ///> Type of primary track (B2PrimaryTrack enum)
  Int_t primary_type_{};
  ///> Type of secondary track (B2SecondaryTrack enum)
  Int_t secondary_type_{};
  ///> if the particle stops inside one of the detectors or escape
  Bool_t is_stopping_{};
  ///> if the particle start inside fiducial volume
  Bool_t is_fiducial_volume_{};
  ///> MRD the particle stops
  Int_t stop_mrd_{};
  ///> MRD the particle is matched with
  Int_t match_mrd_{};
  ///> Muon Confidence Level in PM
  Double_t mucl_pm_;
  ///> Muon Confidence Level in UWG
  Double_t mucl_uwg_;
  ///> Muon Confidence Level in DWG
  Double_t mucl_dwg_;
  ///> the chisqure value in sequential fitting assuming charge -
  Double_t negative_log_likelihood_minus_{};
  ///> the chisqure value in sequential fitting assuming charge +
  Double_t negative_log_likelihood_plus_{};
  ///> reconstructed momentum by range
  Double_t recon_mom_by_range_{};
  ///> reconstructed momentum by curvature
  Double_t recon_mom_by_curve_{};
  ///> TrackLength
  Double_t track_length_total_{};

ClassDefOverride(B2TrackSummary, 12)
};

#endif //WAGASCIBABYMINDMONTECARLO_B2TRACKSUMMARY_HH
