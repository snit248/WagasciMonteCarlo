//
// Created by Giorgio Pintaudi on 8/16/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2VERTEXSUMMARY_HH
#define WAGASCIBABYMINDMONTECARLO_B2VERTEXSUMMARY_HH

#include <TObject.h>
#include <TRef.h>
#include <TArrayI.h>

#include "B2RefArray.hh"
#include "B2Measurement.hh"


class B2HitSummary;

class B2TrackSummary;

class B2EventSummary;

/**
 * Class containing summary information about each vertex. The vertex can be a primary vertex or
 * a secondary vertex as well. It is assumed that only one track is coming into the vertex, i.e.
 * that the other interacting particle, if any, is stationary in the laboratory frame of reference.
 */
class B2VertexSummary : public TObject {

public:

  /**
   * Wrapper around TIter for the B2VertexSummary member outgoing_tracks_ that is a B2RefArray of all
   * the tracks going out of the vertex.
   */
  class B2VertexSummaryIterator : public TObject {

  private:
    B2RefArrayIterator iterator_;
    B2RefArrayIterator end_;

  public:
    explicit B2VertexSummaryIterator(B2VertexSummary &obj);

    explicit B2VertexSummaryIterator(B2VertexSummary *obj);

    /*
     * Return the next outgoing track of the vertex
     */
    B2TrackSummary *Next();
  };

  /**
   * Const version of B2VertexSummaryIterator
   */
  class B2VertexSummaryConstIterator : public TObject {

  private:
    B2RefArrayConstIterator iterator_;
    B2RefArrayConstIterator end_;

  public:
    explicit B2VertexSummaryConstIterator(const B2VertexSummary &obj);

    explicit B2VertexSummaryConstIterator(const B2VertexSummary *obj);

    /*
     * Return the next outgoing track of the vertex
     */
    const B2TrackSummary *Next();
  };

  /**
   * Return an TIter iterator pointing to the first outgoing track
   * @return wrapper around TIter
   */
  B2VertexSummaryIterator BeginTrack();

  /**
   * Return an constant TIter iterator pointing to the first outgoing track
   * @return wrapper around TIter
   */
  B2VertexSummaryConstIterator BeginTrack() const;

  /**
   * Default constructor just clears the state of all the members
   */
  B2VertexSummary();

  /**
   * Set all the members to B2_NON_INITIALIZED_VALUE. No memory is released.
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;

  /**
   * Add an outgoing track to the list of tracks
   * @param track track to add
   */
  void AddOutgoingTrack(B2TrackSummary &track);

  /**
   * Add an outgoing track to the list of tracks
   * @param track track to add
   */
  void AddOutgoingTrack(B2TrackSummary *track);

  /**
   * @param id hash of the track
   * @return track with matching hash
   */
  B2TrackSummary &GetOutgoingTrack(UInt_t id);

  /**
   * @return list of outgoing tracks
   */
  B2RefArray &GetOutgoingTracks();

  /**
   * @return list of outgoing tracks
   */
  const B2RefArray &GetOutgoingTracks() const;

  /**
   * @param track incoming track
   */
  void SetIncomingTrack(const B2TrackSummary &track);

  /**
   * @param track incoming track
   */
  void SetIncomingTrack(const B2TrackSummary *track);

  /**
   * Get the incoming track
   */
  B2TrackSummary &GetIncomingTrack();

  /**
   * Get the incoming track
   */
  const B2TrackSummary &GetIncomingTrack() const;

  /**
   * @return true if there is an incoming track object
   */
  bool HasIncomingTrack() const;

  /**
   * Print all the vertex members value to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2VertexSummary &obj);

  /**
   * Set the parent event
   * @param event parent event
   */
  void SetParentEvent(const B2EventSummary &event);

  /**
   * @param hit closest hit to the vertex
   */
  void SetClosestHit(const B2HitSummary &hit);

  /**
   * @param hit closest hit to the vertex
   */
  void SetClosestHit(const B2HitSummary *hit);

  /**
   * @return closest hit to the vertex
   */
  const B2HitSummary &GetClosestHit() const;

  /**
   * @return parent event
   */
  const B2EventSummary & GetParentEvent() const;

  /**
   * @return bunch number
   */
  Int_t GetBunch() const;

  /**
   * @return number of tracks going out of the vertex (the view and detector conditions are ANDed together)
   * @param view : only count tracks that have at least one hit in a certain view
   * @param detector : only count tracks that have at least one hit in a certain detector
   */
  Long64_t GetNumOutgoingTracks(B2View view = B2View::kUnknownView,
                                B2Detector detector = B2Detector::kUnknownDetector) const;

  /**
   * @return position relative to the center of the detector in mm
   */
  const B2Position &GetRelativePosition() const;

  /**
   * @return vertex position in world coordinates in mm
   */
  const B2Position &GetAbsolutePosition() const;

  /**
   * @return detector ID
   */
  B2Detector GetDetector() const;

  /**
   * @return matching MRD detector ID
   */
  B2Detector GetMRDDetector() const;

  /**
   * @return true if the vertex is inside the fiducial volume of the detector
   */
  Bool_t GetInsideFiducialVolume() const;

  /**
   * @return PDG ID of the particle going inside the vertex
   */
  Int_t GetIncomingParticlePdg() const;

  /**
   * @return material of the target particle
   */
  Int_t GetInteractionMaterial() const;

  /**
   * @return total energy of the particle going into the vertex in MeV
   */
  const B2Energy &GetTotalEnergy() const;

  /**
   * @return 3-momentum of the particle going into the vertex in MeV/c
   */
  const B2Momentum &GetMomentum() const;

  /**
   * @return NEUT interaction mode
   */
  B2InteractionMode GetInteractionType() const;

  /**
   * @return cross section of the interaction in 10^-38 cm^2
   */
  Double_t GetTotalCrossSection() const;

  /**
 * @return JNUBEAM normalization factor
 */
  Double_t GetNormalization() const;

  /**
   * @param relative_position position in mm relative to the center of the detector
   */
  void SetRelativePosition(const B2Position &relative_position);

  /**
   * @param absolute_position position in mm in world coordinates
   */
  void SetAbsolutePosition(const B2Position &absolute_position);

  /**
   * @param detector detector ID
   */
  void SetDetector(B2Detector detector);

  /**
   * @param mrddetector detector ID of the MRD where at least one the the outgoing tracks stops in
   */
  void SetMRDDetector(B2Detector mrddetector);

  /**
   * @param is_inside_fiducial_volume true if the vertex is inside the fiducial volume of the detector
   */
  void SetIsInsideFiducialVolume(Bool_t is_inside_fiducial_volume);

  /**
   * @param incoming_particle_pdg PDG ID of the particle going inside the vertex
   */
  void SetIncomingParticlePdg(Int_t incoming_particle_pdg);

  /**
   * @param interaction_material material of the target particle
   */
  void SetInteractionMaterial(Int_t interaction_material);

  /**
   * @param total_energy total energy of the particle going into the vertex in MeV
   */
  void SetTotalEnergy(const B2Energy &total_energy);

  /**
   * @param momentum 3-momentum of the particle going into the vertex in MeV/c
   */
  void SetMomentum(const B2Momentum &momentum);

  /**
   * @param interaction_type NEUT interaction mode
   */
  void SetInteractionType(B2InteractionMode interaction_type);

  /**
   * @param total_cross_section cross section of the interaction in 10^-38 cm^2
   */
  void SetTotalCrossSection(Double_t total_cross_section);

  /**
 * @param normalization JNUBEAM normalization
 */
  void SetNormalization(Double_t normalization);

  /**
   * @param momentum
   */
  void SetMomentum(const TVector3 &momentum);

  /**
   * @param relative_position position in mm relative to the center of the detector
   */
  void SetRelativePosition(const TVector3 &relative_position);

  /**
   * @param absolute_position position in mm in world coordinates
   */
  void SetAbsolutePosition(const TVector3 &absolute_position);

  /**
   * @param total_energy total energy of the particle
   */
  void SetTotalEnergy(Double_t total_energy);

  /**
   * @return vertex unique ID
   */
  UInt_t GetVertexId() const;

  /**
   * @return dimensionality
   */
  B2Dimensionality GetDimensionality() const;

  /**
   * @param dimensionality dimensionality
   */
  void SetDimensionality(B2Dimensionality dimensionality);

  /**
   * @return view view
   */
  B2View GetView() const;

  /**
   * @param view view
   */
  void SetView(B2View view);

  /**
   * @return detector plane where the vertex is
   */
  Int_t GetPlane() const;

  /**
   * @param plane detector plane where the vertex is
   */
  void SetPlane(Int_t plane);

  /**
   * @return MC weight of the event (also called MC factor). It is the normalization factor described at the end of
   * the README file.
   */
  Double_t GetMcWeight() const;

  /**
   * Clear the list of outgoing tracks
   */
  void ClearTracks();

private:

  ///>
  UInt_t vertex_id_;
  ///> track ending in the vertex
  TRef incoming_track_;
  ///> tracks originating from the vertex
  B2RefArray outgoing_tracks_;
  ///> TRef of the parent event the hit belongs
  TRef parent_event_;
  ///> ID of the closest hit
  TRef closest_hit_;
  ///> bunch number
  Int_t bunch_{};
  ///> number of outgoing tracks
  Long64_t num_outgoing_tracks_{};
  ///> position relative to the sub-detector center in mm
  B2Position relative_position_;
  ///> position relative to center of WAGASCI upstream in mm
  B2Position absolute_position_;
  ///> detector of the vertex
  Int_t detector_{};
  ///> detector of the matching MRD
  Int_t mrd_detector_{};
  ///> true if the vertex is inside the fiducial volume
  Bool_t is_inside_fiducial_volume_{};
  ///>　PDG ID of the interacting particle
  Int_t incoming_particle_pdg_{};
  ///> Interaction material
  Int_t interaction_material_{};
  ///> Energy of incoming particle
  B2Energy total_energy_;
  ///> Momentum of incoming particle
  B2Momentum momentum_;
  ///> interaction type (used only in the Monte Carlo). Same as the NEUT interaction mode. Refer to the
  // B2InteractionMode enum.
  Int_t interaction_type_{};
  ///> Total cross section of the process (x10^-38 cm^2)  (used only in the Monte Carlo).
  Double_t total_cross_section_{};
  ///> normalization constant (used only in the Monte Carlo to reweight the interaction probability)
  Double_t normalization_{};
  ///> Vertex dimensionality
  Int_t dimensionality_{};
  ///> view
  Int_t view_{};
  ///> plane
  Int_t plane_{};

ClassDefOverride(B2VertexSummary, 6)
};


#endif //WAGASCIBABYMINDMONTECARLO_B2VERTEXSUMMARY_HH
