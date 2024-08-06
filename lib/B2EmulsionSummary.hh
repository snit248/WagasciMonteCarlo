//
//Created by Takahiro Odagawa os 11/04/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2EMULSIONSUMMARY_HH
#define WAGASCIBABYMINDMONTECARLO_B2EMULSIONSUMMARY_HH

// ROOT includes
#include <TObject.h>
#include <TRef.h>

// project includes
#include "B2Measurement.hh"
#include "B2Enum.hh"

class B2TrackSummary;

class B2EventSummary;


/**
 * Each instance of this class describes a collection of tracks inside the emulsion films.\n
 * You can use this class almost same as base track objects.
 * Note that this class is only used in Monte Carlo simulation study since track connection
 * between films and so on will become quite complicated accounting weght factors into analysis.\n
 * (Remember, emulsions don't have timing information and we need to handle all track information
 * at the same time.)\n
 * Moreover, emulsion data format is already established in Nagoya emulsion group
 * and implementation of the format into this MC is almost impossible.
 */
class B2EmulsionSummary : public TObject {

public:

  B2EmulsionSummary();

  /**
   * Set the all members to B2_NON_INITIALIZED_VALUE
   * except energy_depoit_diff_ = 0 since this value can be physically negative.
   * no memory is released.
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;

  /**
   * Print all the emulsion track members value to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream   
   */
  friend std::ostream &operator<<(std::ostream &os, const B2EmulsionSummary &obj);

  /**
   * Set the parent track of the emulsion track
   * @param track parent track
   */
  void SetParentTrack(const B2TrackSummary *track);

  /**
   * Set the parent track of the emulsion track
   * @param track parent track
   */
  void SetParentTrack(const B2TrackSummary &track);

  /**
   * Get the parent track of the emulsion track
   * @return parent track
   */
  B2TrackSummary &GetParentTrack();

  /**
   * Get the parent track of the emulsion track
   * @return parent track
   */
  const B2TrackSummary &GetParentTrack() const;

  /**
   * Set the parent track ID
   * @param parent_track_id parent track ID
   */
  void SetParentTrackId(UInt_t parent_track_id);

  /**
   * Get te parent track ID
   * @return parent track ID
   */
  UInt_t GetParentTrackId() const;

  /**
   * Set the parent event of the emulsion track
   * @param evet parent event
   */
  void SetParentEvent(const B2EventSummary &event);

  /**
   * Set the parent event of the emulsion track
   * @param event parent event
   */
  void SetParentEvent(const B2EventSummary *event);

  /**
   * Get the parent event of the emulsion track
   * @return parent event
   */
  B2EventSummary &GetParentEvent();

  /**
   * Get the parent event of the emulsion track
   * @return parent event
   */
  const B2EventSummary &GetParentEvent() const;

  /**
   * @param momentum momentum vector
   */
  void SetMomentum(const B2Momentum &momentum);

  /**
   * @param momentum momentum vector
   */
  void SetMomentum(const TVector3 &momentum);

  /**
   * @return momentum vector
   */
  const B2Momentum &GetMomentum() const;

  /**
   * Set the emulsion track position in the global coordinate
   * @param absolute_position position in the global coordinate
   */
  void SetAbsolutePosition(const B2Position &absolute_position);

  /**
   * Setth emulsion track position in the global coordinate
   * @param absolute_position position in the global coordinate
   */
  void SetAbsolutePosition(const TVector3 &absolute_position);

  /**
   * @return position vector in the global coordinate
   */
  const B2Position &GetAbsolutePosition() const;

  /**
   * Set the emulsion track position in the film
   * @param film_position position vector in the film coordinate
   */
  void SetFilmPosition(const B2Position &film_position);

  /**
   * Set the emulsion track position in the film
   * @param film_position position vector in the film coordinate
   */
  void SetFilmPosition(const TVector3 &film_position);

  /**
   * Get the emulsion track position in the film
   * @return position vector in the film coordinate
   */
  const B2Position &GetFilmPosition() const;

  /**
   * Set the emulsion track angle (tangent) in the film
   * @param tangent tangent of track angle (in the film coordinate)
   */
  void SetTangent(const B2Measurement3D &tangent);

  /**
   * Set the emulsion track angle (tangent) in the film
   * @param tangent tangent of track angle (in the film coordinate)
   */
  void SetTangent(const TVector3 &tangent);

  /**
   * Get the emulsion track angle (tangent) in the film
   * @return tangent vector in the film coordinate (base direction is always 1)
   */
  const B2Measurement3D &GetTangent() const;

  /**
   * Set the emulsion track position in the downstream film coordinate
   * @param film_position_in_dpwm_coordinate\n
   * position vector in the downstream film coordinate
   */
  void SetFilmPositionInDownCoordinate(const B2Position &film_position_in_down_coordinate);

  /**
   * Set the emulsion track position in the downstream film coordinate
   * @param film_position_in_down_coordinate\n
   *  position vector in the downstream film coordinate
   */
  void SetFilmPositionInDownCoordinate(const TVector3 &film_position_in_down_coordinate);

  /**
   * Get the emulsion track position in the downsteram film coordinate
   * @return position vector in the downstream film coordinate
   */
  const B2Position &GetFilmPositionInDownCoordinate() const;

  /**
   * Set the emulsion track angle (tangent) in the downstream film coordinate
   * @param tangent_in_down_coordinate tangent vector in the downstream film coordinate
   */
  void SetTangentInDownCoordinate(const B2Measurement3D &tangent_in_down_coordinate);

  /**
   * Set the emulsion track angle (tangent) in the downstream film coordinate
   * @param tangent_in_down_coordinate tangent vector in the downstream film coordinate
   */
  void SetTangentInDownCoordinate(const TVector3 &tangent_in_down_coordinate);

  /**
   * Get the emulsion track angle (tangent) in the downstream film coordinate
   * @return tangent vector in the downstream film coordinate
   */
  const B2Measurement3D &GetTangentInDownCoordinate() const;

  /**
   * Set the emulsion track's sum of energy deposit in the film
   * @param energy_deposit_sum energy deposit sum of both gels
   */
  void SetEdepSum(Double_t energy_deposit_sum);

  /**
   * Get the emulsion track's sum of energy deposit in the film
   * @return energy deposit sum of both gels
   */
  Double_t GetEdepSum() const;

  /**
   * Set the emulsion track's difference of energy deposit in the film
   * @param energy_deposit_diff energy deposit difference between both gels
   */
  void SetEdepDiff(Double_t energy_deposit_diff);

  /**
   * Get the emulsion track's difference of energy deposit in the film
   * @return energy deposit difference between both gels
   */
  Double_t GetEdepDiff() const;

  /**
   * Set the PH of the upstream microtrack
   * @param ph_up PH of the upstream microtrack
   */
  void SetPhUp(Double_t ph_up);

  /**
   * Get the PH of the upstream microtrack
   * @return PH of the upstream microtrack
   */
  Double_t GetPhUp() const;

  /**
   * Set the PH of the downstream microtrack
   * @param ph_down PH of the downstream microtrack
   */
  void SetPhDown(Double_t ph_down);

  /**
   * Get the PH of the downstream microtrack
   * @return PH of the downstream microtrack
   */
  Double_t GetPhDown() const;

  /**
   * Set the VPH of the upstream microtrack
   * @param vph_up VPH of the upstream microtrack
   */
  void SetVphUp(Double_t vph_up);

  /**
   * Get the VPH of the upstream microtrack
   * @return VPH of the upstream microtrack
   */
  Double_t GetVphUp() const;

  /**
   * Set the VPH of the downstream microtrack
   * @param vph_down VPH of the downstream microtrack
   */
  void SetVphDown(Double_t vph_down);

  /**
   * Get the VPH of the downstream microtrack
   * @return VPH of the downstream microtrack
   */
  Double_t GetVphDown() const;

  /**
   * Set the pixel count of the upstream microtrack
   * @param pixel_count_up pixel count of the upstream microtrack
   */
  void SetPixelCountUp(Double_t pixel_count_up);

  /**
   * Get the pixel count of the upstream microtrack
   * @return pixel count of the upstream microtrack
   */
  Double_t GetPixelCountUp() const;

  /**
   * Set the pixel count of the downstream microtrack
   * @param pixel_count_down pixel count of the downstream microtrack
   */
  void SetPixelCountDown(Double_t pixel_count_down);

  /**
   * Get the pixel count of the downstream microtrack
   * @return pixel count of the downstream microtrack
   */
  Double_t GetPixelCountDown() const;

  /**
   * Set the total pixel of the upstream microtrack
   * @param total_pixel_up total pixel of the upstream microtrack
   */
  void SetTotalPixelUp(Double_t total_pixel_up);

  /**
   * Get the total pixel of the upstream microtrack
   * @return total pixel of the upstream microtrack
   */
  Double_t GetTotalPixelUp() const;

  /**
   * Set the total pixel of the downstream microtrack
   * @param total_pixel_down total pixel of the downstream microtrack
   */
  void SetTotalPixelDown(Double_t total_pixel_down);

  /**
   * Get the total pixel of the downstream microtrack
   * @return total pixel of the downstream microtrack
   */
  Double_t GetTotalPixelDown() const;

  /**
   * Set the emulsion film type
   * @param film_type emulsion film type (ECC, Shifter, and SSS)
   */
  void SetFilmType(Int_t film_type);

  /**
   * Get the emulsion film type
   * @return emulsion film type (ECC, Shifter, and SSS)
   */
  Int_t GetFilmType() const;

  /**
   * Set the ecc ID
   * @param ecc ecc ID (0-8) or packing ID (0-3 or 0-6)
   */
  void SetEcc(Int_t ecc);

  /**
   * Get the ecc ID
   * @return ecc ID (0-8) or packing ID (0-3 or 0-6)
   */
  Int_t GetEcc() const;

  /**
   * Set the plate ID
   * @param plate plate ID in ecc
   */
  void SetPlate(Int_t plate);

  /**
   * Get the plate ID
   * @return plate ID in ecc
   */
  Int_t GetPlate() const;

  /**
   * Set Muon track ID
   * @param muon_track_id muon track ID
   */
  void SetMuonTrackId(Int_t muon_track_id);

  /**
   * Get Muon track ID
   * @return muon track ID
   */
  Int_t GetMuonTrackId() const;

  /**
   * @param emulsion_track_id Emulsion track unique ID
   */
  void SetEmulsionTrackId(UInt_t emulsion_track_id);

  /**
   * @return Emulsion track unique ID
   */
  UInt_t GetEmulsionTrackId() const;

  /**
   * Check if two emulsion tracks are the same
   * @param lhs left hand side
   * @param rhs right hand side
   * @return true if the emulsion tracks are the same
   */
  friend inline bool operator==(const B2EmulsionSummary &lhs, const B2EmulsionSummary &rhs) {
    return lhs.Hash() == rhs.Hash();
  }

private:
  
  ///> Unique emulsion track ID
  UInt_t emulsion_track_id_;
  ///> TRef of the parent track the track belongs
  TRef parent_track_;
  ///> ID of the parent track the track belongs
  UInt_t parent_track_id_{};
  ///> TRef of the parent event the track belongs
  TRef parent_event_;
  ///> Momentum of the particle
  B2Momentum momentum_;
  ///> Position of the track in global coordinate
  ///> Defined as upstream edge of the corresponding base track
  B2Position absolute_position_;
  ///> Position of the track in film coordinate\n
  ///> The origin is film x/y minimum point (z = 0)
  ///> or rotate it to the proper coordinate in the SSS case
  B2Position film_position_;
  ///> Tangent of the track\n
  ///> Each element is calculated by position difference in the edges
  ///> of the corresponding base track divided by the base thickness.
  B2Measurement3D tangent_;
  ///> Position of the track in downstream film coordinate\n
  ///> The origin is upstream film x/y minimum point\n
  ///> It is only used in ECC data
  B2Position film_position_in_down_coordinate_;
  ///> Tangent of the track in downstream film coordinate\n
  ///> It is only used in ECC data
  B2Measurement3D tangent_in_down_coordinate_;
  ///> Sum of energy deposit in two gels of the track\n
  ///> Basically we convert this value into VPH  
  Double_t energy_deposit_sum_{};
  ///> Difference of energy deposit in two gels of the track\n
  ///> Downstream energy deposit is subtracted from upstream one\n
  ///> Use this value to calculate microtrack VPH if you want
  Double_t energy_deposit_diff_{};
  ///> Upstream PH
  Double_t ph_up_{};
  ///> Downstream PH
  Double_t ph_down_{};
  ///> Upstream VPH
  Double_t vph_up_{};
  ///> Downstream VPH
  Double_t vph_down_{};
  ///> Upstream pixel count
  Double_t pixel_count_up_{};
  ///> Downstream pixel count
  Double_t pixel_count_down_{};
  ///> Upstream total number of pixel
  Double_t total_pixel_up_{};
  ///> Downstream total number of pixel
  Double_t total_pixel_down_{};
  ///> Type of the emulsion film. Refer B2EmulsionType enum documentation
  Int_t film_type_{};
  ///> Number of the ECC (or shifter/SSS packings) starting from zero
  Int_t ecc_{};
  ///> Number of the emulsion plate (film) starting from zero
  Int_t plate_{};
  ///> Corresponding muon track id
  Int_t muon_track_id_{};

ClassDefOverride(B2EmulsionSummary, 6) // B2 Emulsion Summary
};

#endif // WAGASCIBABYMINDMONTECARLO_B2EMULSIONSUMMARY_HH
////////////////////////////////////////////////////////////////////////
