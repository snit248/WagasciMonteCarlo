#ifndef B2HITSUMMARY_H
#define B2HITSUMMARY_H

// ROOT includes
#include <TObject.h>
#include <TRef.h>

// project includes
#include "B2Measurement.hh"
#include "B2Enum.hh"
#include "B2Dimension.hh"

class B2ClusterSummary;

class B2TrackSummary;

class B2EventSummary;


/**
 * Each instance of this class describes a single hit inside the scintillator. If the scintillator has single
 * readout, only one channel is contained. If the scintillator has double readout, one hit contains info about both
 * the channels. B2DoubleReadoutI and B2DoubleReadoutD are two helper classes that store information about both
 * channels.
 */
class B2HitSummary : public TObject {

public:

  B2HitSummary();

  /**
   * Merge double readout hits. Each hit must have only one readout filled (different from the readout of the other hit)
   * @param hit hit to merge
   * @param readout readout to merge
   */
  void MergeHits(const B2HitSummary &hit, B2Readout readout);

  /**
   * Set all the members to B2_NON_INITIALIZED_VALUE. No memory is released.
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;

  /**
   * Set the parent cluster of the hit
   * @param cluster parent cluster
   */
  void SetParentCluster(const B2ClusterSummary &cluster);

  /**
   * Set the parent cluster of the hit
   * @param cluster parent cluster
   */
  void SetParentCluster(const B2ClusterSummary *cluster);

  /**
   * Get the parent cluster ID of the hit
   * @return parent cluster ID
   */
  UInt_t GetParentClusterId() const;

  /**
   * Set the parent cluster ID of the hit
   * @param parent_cluster_id parent cluster ID
   */
  void SetParentClusterId(UInt_t parent_cluster_id);

  /**
   * Get the parent cluster of the hit
   * @return parent cluster
   */
  B2ClusterSummary &GetParentCluster();

  /**
   * Get the parent cluster of the hit
   * @return parent cluster
   */
  const B2ClusterSummary &GetParentCluster() const;

  /**
   * Check if the hit has a parent cluster or not
   * @return true if a parent cluster was found
   */
  bool HasParentCluster() const;

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
   * Set the parent track ID
   * @param track_id parent track ID
   */
  void SetParentTrackId(UInt_t track_id);

  /**
   * Get the parent track
   * @return parent track
   */
  B2TrackSummary &GetParentTrack();

  /**
   * Get the parent track
   * @return parent track
   */
  const B2TrackSummary &GetParentTrack() const;

  /**
   * @return parent track ID
   */
  UInt_t GetParentTrackId() const;

  /**
   * Check if the hit has a parent track or not
   * @return true if a parent track was found
   */
  bool HasParentTrack() const;

  /**
   * Set the parent event
   * @param event parent event
   */
  void SetParentEvent(const B2EventSummary &event);

  /**
   * Set the parent event
   * @param event parent event
   */
  void SetParentEvent(const B2EventSummary *event);

  /**
   * Get the parent event
   * @return parent event
   */
  B2EventSummary &GetParentEvent();

  /**
   * Get the parent event
   * @return parent event
   */
  const B2EventSummary &GetParentEvent() const;

  /**
   * Get the first readout (no matter which one) of a double readout scintillator.
   * Useful only when used in sequence with GetReadout2. In case of single readout
   * scintillators, it returns GetSingleReadout
   * @return first readout
   */
  B2Readout GetReadout1() const;

  /**
   * Get the second readout (no matter which one) of a double readout scintillator.
   * Useful only when used in sequence with GetReadout1. In case of single readout
   * scintillators, it returns GetSingleReadout
   * @return second readout
   */
  B2Readout GetReadout2() const;

  /**
   * Get the number of readouts of the scintillator the hit belongs to
   * @return number of readouts
   */
  UInt_t GetNumberReadouts() const;

  /**
   * @return readouts of the hit scintillator as a vector
   */
  std::vector<B2Readout> GetReadouts() const;

  /**
   * Get the readout type of the scintillator the hit belongs to
   * @return single readout
   */
  B2Readout GetSingleReadout() const;

  /**
   * Get the average PEU of the hit in case of double readout. In case of single
   * readout the only PEU is returned.
   * @return average PEU
   */
  B2Measurement1D GetAveragePeu() const;

  /**
   * Check if the MPPC of the selected readout has been hit
   * @param readout
   * @return true in case the MPPC on that readout has been hit
   */
  bool ReadoutHasHit(B2Readout readout) const;

  /**
   * Print all the hit members value to the output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2HitSummary &obj);

  /**
   * @return bunch number
   */
  Int_t GetBunch() const;

  /**
   * @param bunch bunch number
   */
  void SetBunch(Int_t bunch);

  /**
   * @return detector ID
   */
  B2Detector GetDetectorId() const;

  /**
   * @param detector detector ID
   */
  void SetDetector(B2Detector detector);

  /**
   * @return cycle number (same as BCID)
   */
  Int_t GetCycle() const;

  /**
   * @param cycle cycle number (same as BCID)
   */
  void SetCycle(Int_t cycle);

  /**
   * @return position in mm relative to the center of the detector (true position)
   */
  const B2Position &GetTrueRelativePosition() const;

  /**
   * @return position in mm relative to the center of the detector (reconstructed position)
   */
  const B2Position &GetReconRelativePosition() const;

  /**
   * @param relative_position position in mm relative to the center of the detector (true position)
   */
  void SetTrueRelativePosition(const B2Position &relative_position);

  /**
   * @param relative_position position in mm relative to the center of the detector (reconstructed position)
   */
  void SetReconRelativePosition(const B2Position &relative_position);

  /**
   * @param relative_position position in mm relative to the center of the detector (true position)
   */
  void SetTrueRelativePosition(const TVector3 &relative_position);

  /**
   * @param relative_position position in mm relative to the center of the detector (reconstructed position)
   */
  void SetReconRelativePosition(const TVector3 &relative_position);

  /**
   * @return absolute position in mm in world coordinates (true position)
   */
  const B2Position &GetTrueAbsolutePosition() const;

  /**
   * @return absolute position in mm in world coordinates (reconstructed position)
   */
  const B2Position &GetReconAbsolutePosition() const;

  /**
   * @param absolute_position  position in mm in world coordinates (true position)
   */
  void SetTrueAbsolutePosition(const B2Position &absolute_position);

  /**
   * @param absolute_position  position in mm in world coordinates (reconstructed position)
   */
  void SetReconAbsolutePosition(const B2Position &absolute_position);

  /**
   * @param absolute_position position in mm in world coordinates (true position)
   */
  void SetTrueAbsolutePosition(const TVector3 &absolute_position);

  /**
   * @param absolute_position position in mm in world coordinates (reconstructed position)
   */
  void SetReconAbsolutePosition(const TVector3 &absolute_position);

  /**
   * @return position in mm of the hit scintillator in world coordinates
   */
  const B2Position &GetScintillatorPosition() const;

  /**
   * @param scintillator_position position in mm of the hit scintillator in world coordinates
   */
  void SetScintillatorPosition(const B2Position &scintillator_position);

  /**
   * @return distance between the hit position (relative position) and the MPPC position
   */
  B2Distance GetHitMppcDistance(B2DataType data_type, B2Readout readout) const;

  /**
   * @return transition time in ns from the hit to the MPPC
   */
  B2Time GetHitMppcTransitionTime(B2DataType data_type, B2Readout readout) const;

  /**
   * @return distance between one hit position (relative position) and another hit position
   */
  B2Distance GetHitToHitDistance(const B2HitSummary &hit, B2DataType data_type) const;

  /**
   * @return view (top view or side view or unset) for each readout
   */
  B2View GetView() const;

  /**
   * @param view view (top view or side view) for each readout
   */
  void SetView(B2View view);

  /**
   * @return scintillator type (horizontal, vertical, veto, etc..)
   */
  B2ScintillatorType GetScintillatorType() const;

  /**
   * @param scintillator_type scintillator type (horizontal, vertical, veto, etc..)
   */
  void SetScintillatorType(B2ScintillatorType scintillator_type);

  /**
   * Deprecated (please use GetChannel(B2Readout) instead
   * @return channel number
   */
  const B2DoubleReadoutI &GetChannel() const;

  /**
   * If a hit is not found in the readout an exception is thrown
   * @return channel number
   */
  Int_t GetChannel(B2Readout readout) const;

  /**
   * @param channel channel number
   */
  void SetChannel(const B2DoubleReadoutI &channel);

  /**
   * Deprecated, please use GetChip(B2Readout) instead.
   * @return chip number
   */
  const B2DoubleReadoutI &GetChip() const;

  /**
   * If a hit is not found in the readout an exception is thrown
   * @return chip number
   */
  Int_t GetChip(B2Readout readout) const;

  /**
   * @param chip chip number
   */
  void SetChip(const B2DoubleReadoutI &chip);

  /**
   * Deprecated, please use GetSlot(B2Readout) instead.
   * @return slot number
   */
  const B2DoubleReadoutI &GetSlot() const;

  /**
   * If a hit is not found in the readout an exception is thrown
   * @return slot number
   */
  Int_t GetSlot(B2Readout readout) const;

  /**
   * @param slot slot number
   */
  void SetSlot(const B2DoubleReadoutI &slot);

  /**
   * @return plane number
   */
  Int_t GetPlane() const;

  /**
   * @param plane plane number
   */
  void SetPlane(Int_t plane);

  /**
   * @return true hit time in ns
   */
  Double_t GetTrueTimeNs() const;

  /**
   * @return time in ns from the start of the event
   */
  const B2DoubleReadoutD &GetTimeNs() const;

  /**
   * If a hit is not found in the readout an exception is thrown
   * @return time in ns from the start of the event
   */
  Double_t GetTimeNs(B2Readout readout) const;

  /**
   * @param time_ns time in ns from the start of the event
   */
  void SetTimeNs(const B2DoubleReadoutD &time_ns);

  /**
   * @return PEU reading from the high gain preamp
   */
  const B2DoubleReadoutD &GetHighGainPeu() const;

  /**
   * If a hit is not found in the readout an exception is thrown
   * @return PEU reading from the high gain preamp
   */
  Double_t GetHighGainPeu(B2Readout readout) const;

  /**
   * @param high_gain_peu PEU reading from the high gain preamp
   */
  void SetHighGainPeu(const B2DoubleReadoutD &high_gain_peu);

  /**
   * @return PEU reading from the low gain preamp
   */
  const B2DoubleReadoutD &GetLowGainPeu() const;

  /**
   * If a hit is not found in the readout an exception is thrown
   * @return PEU reading from the low gain preamp
   */
  Double_t GetLowGainPeu(B2Readout readout) const;

  /**
   * @param low_gain_peu PEU reading from the low gain preamp
   */
  void SetLowGainPeu(const B2DoubleReadoutD &low_gain_peu);

  /**
   * @return energy deposited by the particle in the hit point in MeV
   */
  Double_t GetEnergyDeposit() const;

  /**
   * @param energy_deposit energy deposited by the particle in the hit point in MeV
   */
  void SetEnergyDeposit(Double_t energy_deposit);

  /**
   * @return true if the hit is inside the fiducial volume
   */
  Bool_t GetIsInFiducialVolume() const;

  /**
   * @param is_in_fiducial_volume true if the hit is inside the fiducial volume
   */
  void SetIsInFiducialVolume(Bool_t is_in_fiducial_volume);

  /**
   * @return true if the hit is due to dark noise
   */
  Bool_t GetIsNoiseHitTrue() const;

  /**
   * @param is_noise_hit_true true if the hit is due to dark noise
   */
  void SetIsNoiseHitTrue(Bool_t is_noise_hit_true);

  /**
   * @return true if the hit is due to dark noise
   */
  Bool_t GetIsNoiseHitRecon() const;

  /**
   * @param is_noise_hit_recon true if the hit is due to dark noise
   */
  void SetIsNoiseHitRecon(Bool_t is_noise_hit_recon);

  /**
   * @return veto plane
   */
  B2VetoPlane GetVeto() const;

  /**
   * @param veto veto plane
   */
  void SetVeto(B2VetoPlane veto);

  /**
   * @param position position in mm of the hit scintillator in world coordinates
   */
  void SetScintillatorPosition(const B2Vector3 &position);

  /**
   * @param scintillator_position position in mm of the hit scintillator in world coordinates
   * @param error in mm
   */
  void SetScintillatorPosition(const B2Vector3 &position, const B2Vector3 &error);

  /**
   * @param readout readout type
   * @param channel channel number of the readout
   */
  void SetChannel(B2Readout readout, Int_t channel);

  /**
   * @param readout readout type
   * @param
   */
  void SetChip(B2Readout readout, Int_t chip);

  /**
   * @param readout readout type
   * @param slot slot number of the readout
   */
  void SetSlot(B2Readout readout, Int_t slot);

  /**
   * @param readout readout type
   * @param time_ns time in ns from the start of the event
   */
  void SetTimeNs(B2Readout readout, Double_t time_ns);

  /**
   * @param readout readout type
   * @param time_ns time in ns from the start of the event
   * @param time_ns_error error of the time measurement in ns
   */
  void SetTimeNs(B2Readout readout, Double_t time_ns, Double_t time_ns_error);

  /**
   * @param true_time_ns true hit time in ns
   */
  void SetTrueTimeNs(Double_t true_time_ns);

  /**
   * @param readout readout type
   * @param high_gain_peu PEU reading from the high gain preamp
   */
  void SetHighGainPeu(B2Readout readout, Double_t high_gain_peu);

  /**
   * @param readout readout type
   * @param low_gain_peu PEU reading from the low gain preamp
   */
  void SetLowGainPeu(B2Readout readout, Double_t low_gain_peu);

  /**
   * @param readout readout type
   * @param high_gain_peu PEU reading from the high gain preamp
   * @param error error on PEU
   */
  void SetHighGainPeu(B2Readout readout, Double_t high_gain_peu, Double_t error);

  /**
   * @param readout readout type
   * @param low_gain_peu PEU reading from the low gain preamp
   * @param error error on PEU
   */
  void SetLowGainPeu(B2Readout readout, Double_t low_gain_peu, Double_t error);

  /**
   * @return Plane or grid scintillator (B2PlaneGrid enum)
   */
  Int_t GetPlaneGrid() const;

  /**
   * @param plane_grid Plane or grid scintillator (B2PlaneGrid enum)
   */
  void SetPlaneGrid(Int_t plane_grid);

  /**
   * @return Hit unique ID
   */
  UInt_t GetHitId() const;

  /**
   * Check if two hits are the same
   * @param lhs left hand side
   * @param rhs right hand side
   * @return true if the hits are the same
   */
  friend inline bool operator==(const B2HitSummary &lhs, const B2HitSummary &rhs) {
    return lhs.Hash() == rhs.Hash();
  }

  /**
   * @return Transition time of light signal (for WAGASCI)
   */
  B2Time WgsHitMppcTransitionTime(B2DataType data_type) const;

  /**
   * @return distance in mm travelled by the light signal inside the WLS fiber (for WAGASCI)
   */
  B2Distance WgsHitMppcDistance(B2DataType data_type) const;

  /**
   * Calculate the Y position inside the scintillator bar by using the light yield in both readouts
   * @return Y position in mm (relative to the center of the detector)
   */
  B2Distance WallMrdCalculateYPositionFromLightYield() const;

/**
 * calculate the shortest distance from hit position to fiber position (for WallMRD)
 * @param slot : slot (channel) number
 * @param posy : hit of position in y-axis in mm (relative to the center of the detector)
 * @param posz : hit of position in z-axis in mm (relative to the center of the detector)
 * @return the shortest distance from hit position to fiber position in mm
 */
  static double WallMrdHitToFiber(int slot, double posy, double posz, B2Detector detector);

  /**
   * calculate the local position (in WallMRD)
   * @param pos : hit position in x,y,z-axis in mm (relative to the center of the detector)
   * @return the local position (x, y) in each section [120 mm, 200 mm] + section no. (z) 0 ~ 14
   */
  static TVector3 GetLocalPositioninWallMrd(double posz, double posy, int slot);

  /**
   * calculate the local position (in YASU Tracker)
   * @param pos : hit position in x,y,z-axis in mm (relative to the center of the detector)
   * @return the local position (x, y) in each section [120 mm, 200 mm] + section no. (z) 0 ~ 14
   */
  static TVector3 GetLocalPositioninYASUTracker(double posz, double posy, int slot);

private:

  ///> Unique hit ID
  UInt_t hit_id_;
  ///> TRef of the parent cluster the hit belongs
  TRef parent_cluster_;
  ///> Geant4 ID of the parent cluster the hit belongs
  UInt_t parent_cluster_id_{};
  ///> TRef of the parent track the hit belongs
  TRef parent_track_;
  ///> ID of the parent track the hit belongs
  UInt_t parent_track_id_{};
  ///> TRef of the parent event the hit belongs
  TRef parent_event_;
  ///> bunch number
  Int_t bunch_{};
  ///> detector number. Refer to the B2Detector enum documentation.
  Int_t detector_{};
  ///> coarse timing. For PM is called cycle (0~22).
  /// For WAGASCI is called BCID. For BabyMIND is called GTrigger.
  Int_t cycle_{};
  ///> position relative to the sub-detector center in mm (true position)
  B2Position relative_position_true_;
  ///> position relative to the sub-detector center in mm (reconstructed position_
  B2Position relative_position_recon_;
  ///> position relative to the center of the world in mm (true position)
  B2Position absolute_position_true_;
  ///> position relative to the center of the world in mm (reconstructed position)
  B2Position absolute_position_recon_;
  ///> position of the hit scintillator (center of scintillator for all detectors but PM,
  ///  MPPC position for PM)
  B2Position scintillator_position_;
  ///> Detector view. Refer to the B2View enum documentation.
  Int_t view_{};
  ///> type of the scintillator. Refer to the B2ScintillatorType enum documentation.
  Int_t scintillator_type_{};
  ///> plane/grid scintillator. Refer to the B2PlaneGrid enum documentation.
  Int_t plane_grid_{};
  ///> channel number starting from zero (one channel for each view)
  B2DoubleReadoutI channel_;
  ///> chip number starting from zero (one chip for each view)
  B2DoubleReadoutI chip_;
  ///> slot number starting from zero (only WG)
  B2DoubleReadoutI slot_;
  ///> plane number starting from zero
  Int_t plane_{};
  ///> true hit time in ns
  Double_t true_time_ns_{};
  ///> time in ns relative to beam trigger (one time for each view)
  B2DoubleReadoutD time_ns_;
  ///> Photoelectron equivalent units for high gain preamp (one PEU for each view)
  B2DoubleReadoutD high_gain_peu_;
  ///> Photoelectron equivalent units for low gain preamp (one PEU for each view)
  B2DoubleReadoutD low_gain_peu_;
  ///> Energy deposit in MeV (only MC)
  Double_t energy_deposit_{};
  ///> True if the hit lies inside the fiducial volume
  Bool_t is_in_fiducial_volume_{};
  ///> True if the hit comes from dark noise (set by Monte Carlo)
  Bool_t is_noise_hit_true_{};
  ///> True if the hit comes from dark noise (set by track seeding software)
  Bool_t is_noise_hit_recon_{};
  ///> Veto plane enum. Refer to the B2VetoPlane enum documentation.
  Int_t veto_{};

ClassDefOverride(B2HitSummary, 7) // B2 Hit Summary
};

#endif // B2HITSUMMARY_H
////////////////////////////////////////////////////////////////////////
