#include <iostream>
#include "B2BeamSummary.hh"
#include "B2Measurement.hh"

//......................................................................
B2BeamSummary::B2BeamSummary() {
  B2BeamSummary::Clear("C");
}

//......................................................................
void B2BeamSummary::Clear(Option_t *option) {
  t2k_run_ = B2_NON_INITIALIZED_VALUE;
  main_ring_run_ = B2_NON_INITIALIZED_VALUE;
  neutrino_daq_run_ = B2_NON_INITIALIZED_VALUE;
  wagasci_run_ = B2_NON_INITIALIZED_VALUE;
  spill_pot_ = B2_NON_INITIALIZED_VALUE;
  for (double &i : bunch_pot_)
    i = B2_NON_INITIALIZED_VALUE;
  neutrino_mode_ = B2_NON_INITIALIZED_VALUE;
  bsd_spill_number_ = B2_NON_INITIALIZED_VALUE;
  wagasci_spill_number_ = B2_NON_INITIALIZED_VALUE;
  horn_current_ = B2_NON_INITIALIZED_VALUE;
  timestamp_ = B2_NON_INITIALIZED_VALUE;
  bsd_good_spill_flag_ = B2_NON_INITIALIZED_VALUE;
  wagasci_good_spill_flag_ = B2_NON_INITIALIZED_VALUE;
  EnableAllDetectors();
  TObject::Clear(option);
}

//......................................................................
std::ostream &operator<<(std::ostream &os, const B2BeamSummary &obj) {

  os << "T2K run number = " << obj.t2k_run_ << "\n"
     << "Main ring run number = " << obj.main_ring_run_ << "\n"
     << "Neutrino daq run = " << obj.neutrino_daq_run_ << "\n"
     << "WAGASCI run number = " << obj.wagasci_run_ << "\n"
     << "Total POT of this spill = " << obj.spill_pot_ << "\n"
     << "POT for each bunch = ";
  for (std::size_t i = 0; i < B2BeamSummary::num_bunches_; ++i) {
    os << i + 1 << " : " << obj.bunch_pot_[i];
    if (i != B2BeamSummary::num_bunches_ - 1)
      os << " ,";
  }
  os << "\n"
     << "Neutrino mode (" << B2NeutrinoBeamLineMode::kNeutrinos << " : neutrinos, "
     << B2NeutrinoBeamLineMode::kAntiNeutrinos << " : anti neutrinos) = " << obj.neutrino_mode_ << "\n"
     << "BSD spill number = " << obj.bsd_spill_number_ << "\n"
     << "WAGASCI spill number = " << obj.wagasci_spill_number_ << "\n"
     << "Horn current = " << obj.horn_current_ << "\n"
     << "Timestamp = " << obj.timestamp_ << "\n"
     << "BSD good spill flag (good : 1, bad : 0) = " << obj.bsd_good_spill_flag_ << "\n"
     << "WAGASCI good spill flag (good : 1, bad : 0) = " << obj.wagasci_good_spill_flag_ << "\n";

  return os;
}

Int_t B2BeamSummary::GetT2KRun() const {
  return t2k_run_;
}

void B2BeamSummary::SetT2KRun(Int_t t2k_run) {
  t2k_run_ = t2k_run;
}

Int_t B2BeamSummary::GetMainRingRun() const {
  return main_ring_run_;
}

void B2BeamSummary::SetMainRingRun(Int_t main_ring_run) {
  main_ring_run_ = main_ring_run;
}

Int_t B2BeamSummary::GetNeutrinoDaqRun() const {
  return neutrino_daq_run_;
}

void B2BeamSummary::SetNeutrinoDaqRun(Int_t neutrino_daq_run) {
  neutrino_daq_run_ = neutrino_daq_run;
}

Int_t B2BeamSummary::GetWagasciRun() const {
  return wagasci_run_;
}

void B2BeamSummary::SetWagasciRun(Int_t wagasci_run) {
  wagasci_run_ = wagasci_run;
}

Double_t B2BeamSummary::GetSpillPot() const {
  return spill_pot_;
}

void B2BeamSummary::SetSpillPot(Double_t spill_pot) {
  spill_pot_ = spill_pot;
}

Double_t B2BeamSummary::GetBunchPot(std::size_t bunch) const {
  if (bunch >= num_bunches_)
    throw std::out_of_range("Bunch number out of range");
  return bunch_pot_[bunch];
}

void B2BeamSummary::SetBunchPot(std::size_t bunch, Double_t pot) {
  if (bunch >= num_bunches_)
    throw std::out_of_range("Bunch number out of range");
  bunch_pot_[bunch] = pot;
}

Int_t B2BeamSummary::GetNeutrinoMode() const {
  return neutrino_mode_;
}

void B2BeamSummary::SetNeutrinoMode(Int_t neutrino_mode) {
  neutrino_mode_ = neutrino_mode;
}

Int_t B2BeamSummary::GetBsdSpillNumber() const {
  return bsd_spill_number_;
}

void B2BeamSummary::SetBsdSpillNumber(Int_t bsd_spill_number) {
  bsd_spill_number_ = bsd_spill_number;
}

Int_t B2BeamSummary::GetWagasciSpillNumber() const {
  return wagasci_spill_number_;
}

void B2BeamSummary::SetWagasciSpillNumber(Int_t wagasci_spill_number) {
  wagasci_spill_number_ = wagasci_spill_number;
}

Double_t B2BeamSummary::GetHornCurrent() const {
  return horn_current_;
}

void B2BeamSummary::SetHornCurrent(Double_t horn_current) {
  horn_current_ = horn_current;
}

Double_t B2BeamSummary::GetTimestamp() const {
  return timestamp_;
}

void B2BeamSummary::SetTimestamp(Double_t timestamp) {
  timestamp_ = timestamp;
}

Int_t B2BeamSummary::GetBsdGoodSpillFlag() const {
  return bsd_good_spill_flag_;
}

void B2BeamSummary::SetBsdGoodSpillFlag(Int_t bsd_good_spill_flag) {
  bsd_good_spill_flag_ = bsd_good_spill_flag;
}

Int_t B2BeamSummary::GetWagasciGoodSpillFlag() const {
  return wagasci_good_spill_flag_;
}

void B2BeamSummary::SetWagasciGoodSpillFlag(Int_t wagasci_good_spill_flag) {
  wagasci_good_spill_flag_ = wagasci_good_spill_flag;
}

void B2BeamSummary::EnableDetector(B2Detector detector) {
  detector_flags_.at(detector) = kTRUE;
}

void B2BeamSummary::DisableDetector(B2Detector detector) {
  detector_flags_.at(detector) = kFALSE;
}

bool B2BeamSummary::IsDetectorEnabled(B2Detector detector) {
  return detector_flags_.at(detector);
}

bool B2BeamSummary::IsDetectorDisabled(B2Detector detector) {
  return !detector_flags_.at(detector);
}

void B2BeamSummary::DisableAllDetectors() {
  for (Bool_t &flag : detector_flags_)
    flag = kFALSE;
}

void B2BeamSummary::EnableAllDetectors() {
  for (Bool_t &flag : detector_flags_)
    flag = kTRUE;
}

std::array<Bool_t, B2Detector::kNumDetectors> B2BeamSummary::GetDetectorFlags() {
  return detector_flags_;
}

void B2BeamSummary::SetDetectorFlags(std::array<Bool_t, B2Detector::kNumDetectors> detector_flags) {
  detector_flags_ = detector_flags;
}

std::array<Bool_t, B2Detector::kNumDetectors>
B2BeamSummary::MergeDetectorFlags(std::array<Bool_t, B2Detector::kNumDetectors> flag1,
                                  std::array<Bool_t, B2Detector::kNumDetectors> flag2) {
  for (int i = 0; i < B2Detector::kNumDetectors; ++i) {
    flag1.at(i) = flag1.at(i) || flag2.at(i);
  }
  return flag1;
}


ClassImp(B2BeamSummary)