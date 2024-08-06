#ifndef BEAMINFOSUMMARY_H
#define BEAMINFOSUMMARY_H

#include <array>
#include <TObject.h>
#include "B2Enum.hh"


/**
 * Class containing info about the neutrino beam. One instance describe a whole spill (8 bunches).
 */
class B2BeamSummary : public TObject {

public:
  B2BeamSummary();

  /**
   * Clear the object state
   * @param option same as TObject option
   */
  void Clear(Option_t *option) override;

  /**
   * Print object state to output stream
   * @param os output stream
   * @param obj object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &os, const B2BeamSummary &obj);

  Int_t GetT2KRun() const;

  void SetT2KRun(Int_t t2k_run);

  Int_t GetMainRingRun() const;

  void SetMainRingRun(Int_t main_ring_run);

  Int_t GetNeutrinoDaqRun() const;

  void SetNeutrinoDaqRun(Int_t neutrino_daq_run);

  Int_t GetWagasciRun() const;

  void SetWagasciRun(Int_t wagasci_run);

  Double_t GetSpillPot() const;

  void SetSpillPot(Double_t spill_pot);

  Double_t GetBunchPot(std::size_t bunch) const;

  void SetBunchPot(size_t bunch, Double_t pot);

  Int_t GetNeutrinoMode() const;

  void SetNeutrinoMode(Int_t neutrino_mode);

  Int_t GetBsdSpillNumber() const;

  void SetBsdSpillNumber(Int_t bsd_spill_number);

  Int_t GetWagasciSpillNumber() const;

  void SetWagasciSpillNumber(Int_t wagasci_spill_number);

  Double_t GetHornCurrent() const;

  void SetHornCurrent(Double_t horn_current);

  Double_t GetTimestamp() const;

  void SetTimestamp(Double_t timestamp);

  Int_t GetBsdGoodSpillFlag() const;

  void SetBsdGoodSpillFlag(Int_t bsd_good_spill_flag);

  Int_t GetWagasciGoodSpillFlag() const;

  void SetWagasciGoodSpillFlag(Int_t wagasci_good_spill_flag);

  void EnableDetector(B2Detector detector);

  void DisableDetector(B2Detector detector);

  bool IsDetectorEnabled(B2Detector detector);

  bool IsDetectorDisabled(B2Detector detector);

  void DisableAllDetectors();

  void EnableAllDetectors();

  std::array<Bool_t, B2Detector::kNumDetectors> GetDetectorFlags();

  void SetDetectorFlags(std::array<Bool_t, B2Detector::kNumDetectors> detector_flags);

  static std::array<Bool_t, B2Detector::kNumDetectors>
  MergeDetectorFlags(std::array<Bool_t, B2Detector::kNumDetectors> flag1,
                     std::array<Bool_t, B2Detector::kNumDetectors> flag2);

private:

  ///> Number of bunches in one spill
  static const std::size_t num_bunches_ = 8;

  ///> T2K run number
  Int_t t2k_run_{};
  ///> Main ring run number
  Int_t main_ring_run_{};
  ///> Neutrino DAQ run number
  Int_t neutrino_daq_run_{};
  ///> WAGASCI run number
  Int_t wagasci_run_{};
  ///> Number of POT for this spill
  Double_t spill_pot_{};
  ///> Number of POT for each bunch
  std::array<Double_t, num_bunches_> bunch_pot_{};
  ///> Neutrino beam line mode (neutrinos or anti-neutrinos)
  Int_t neutrino_mode_{};
  ///> BSD spill number (32 bit)
  Int_t bsd_spill_number_{};
  ///> WAGASCI spill number (16 bit)
  Int_t wagasci_spill_number_{};
  ///> horn current in Amperes
  Double_t horn_current_{};
  ///> Timestamp in seconds (taken from beam line rubidium atomic clock)
  Double_t timestamp_{};
  ///> BSD good spill flag
  Int_t bsd_good_spill_flag_{};
  ///> WAGASCI good spill flag
  Int_t wagasci_good_spill_flag_{};
  ///> Flag to notify if a detector is enabled or disabled
  std::array<Bool_t, B2Detector::kNumDetectors> detector_flags_{};

ClassDefOverride(B2BeamSummary, 2) // Beam Info Summary
};

#endif // BEAMINFOSUMMARY_H
////////////////////////////////////////////////////////////////////////
