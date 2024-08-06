//
// Created by Giorgio Pintaudi on 8/12/20.
//
#include "B2SensitiveDetector.hh"

// Geant4 includes
#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4VTouchable.hh>
#include <G4TouchableHistory.hh>
#include <G4SDManager.hh>

// project includes
#include "B2Measurement.hh"

/**
 * Coincidence of two readouts of a scintillator bar. Each readout can store a CoincidenceHit that represents a hit
 * in the relative MPPC.
 */
class Coincidence {

public:

  struct CoincidenceHit {
    CoincidenceHit() : hit(false), highgain(-10), lowgain(-10), delaytime(-10), energydeposit(0) {}

    bool hit;
    Double_t highgain;
    Double_t lowgain;
    Double_t delaytime;
    Double_t energydeposit;
  } __attribute__((aligned(64))) __attribute__((packed));

  using CoincidenceHits = std::unordered_map<B2Readout, CoincidenceHit, EnumClassHash>;

private:

  CoincidenceHits coincidence_;

public:

  explicit Coincidence(B2Detector detector, B2View view) {

    switch (view) {

      // SIDE VIEW
      case B2View::kSideView:
        switch (detector) {
          case B2Detector::kBabyMind:
            coincidence_[B2Readout::kLeftReadout];
            coincidence_[B2Readout::kRightReadout];
            break;
          case B2Detector::kWagasciUpstream:
          case B2Detector::kWagasciDownstream:
          case B2Detector::kProtonModule:
          case B2Detector::kNinja:
          case B2Detector::kYasuTracker:
            coincidence_[B2Readout::kSideReadout];
            break;
          default:
            throw std::logic_error("Coincidence for detector " + DETECTOR_NAMES.at(detector)
                                   + " is not implemented.");
        }
        break;

        // TOP VIEW
      case B2View::kTopView:
        switch (detector) {
          case B2Detector::kWallMrdSouth:
          case B2Detector::kWallMrdNorth:
          case B2Detector::kBabyMind:
            coincidence_[B2Readout::kTopReadout];
            coincidence_[B2Readout::kBottomReadout];
            break;
          case B2Detector::kWagasciUpstream:
          case B2Detector::kWagasciDownstream:
          case B2Detector::kProtonModule:
          case B2Detector::kNinja:
            coincidence_[B2Readout::kTopReadout];
            break;
          default:
            throw std::logic_error("Coincidence for detector " + DETECTOR_NAMES.at(detector)
                                   + " is not implemented.");
        }
        break;

        // UNKNOWN VIEW
      case B2View::kUnknownView:
        throw std::logic_error("[Coincidence] Unknown view");
    }
  }

  CoincidenceHit &GetCoincidenceHit(B2Readout readout) {
    return coincidence_.at(readout);
  }

  const CoincidenceHit &GetCoincidenceHit(B2Readout readout) const {
    return coincidence_.at(readout);
  }

  CoincidenceHits &GetCoincidenceHits() {
    return coincidence_;
  }

  const CoincidenceHits &GetCoincidenceHits() const {
    return coincidence_;
  }

  bool HasCoincidence() const {
    return std::all_of(coincidence_.begin(), coincidence_.end(),
                       [](std::pair<B2Readout, const CoincidenceHit &> pair) {
                         return pair.second.hit;
                       });
  }

};

B2SensitiveDetector::B2SensitiveDetector(const G4String &name, const B2Dimension &dimension)
    : G4VSensitiveDetector(name),
      dimension_(dimension),
      hit_collection_(nullptr),
      response_(dimension),
      total_energy_deposit_(0) {}

void B2SensitiveDetector::Initialize(G4HCofThisEvent *hit_collections_this_event) {
  hit_collection_ = new B2HitsCollection(SensitiveDetectorName, collectionName.front());
  total_energy_deposit_ = 0;
  hit_collections_this_event->AddHitsCollection(GetCollectionID(0), hit_collection_);
}

G4bool B2SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *) {
  // create a new hit only when there is energy deposit in a sensitive detector
  const auto energy_deposit = step->GetTotalEnergyDeposit();
  if (energy_deposit == 0.)
    return false;
  else
    total_energy_deposit_ += energy_deposit;

  // volume information must be extracted from p_touchable of "PreStepPoint"
  const G4VTouchable *p_touchable = step->GetPreStepPoint()->GetTouchable();
  const G4int scintillator_id = p_touchable->GetVolume(0)->GetCopyNo();
  const G4ThreeVector hit_absolute_position = GetHitAbsolutePosition(step);

  // apply quenching effect
  const auto *track = step->GetTrack();
  auto quenced_energy_deposit = energy_deposit;
  response_.ApplyScintiResponse(quenced_energy_deposit, *track);

  // Create a new hit
  auto *new_hit = HitFactory(scintillator_id, hit_absolute_position);
  new_hit->AddEnergyDeposit(energy_deposit);
  new_hit->AddQuenchedEnergyDeposit(quenced_energy_deposit);
  new_hit->SetTrackId(track->GetTrackID());
  new_hit->SetParticlePdgId(track->GetDefinition()->GetPDGEncoding());
  new_hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());

  // Look for a hit in the same scintillator
  G4bool found = false;
  for (auto &hit: *hit_collection_->GetVector()) {
    // If the new hit is inside an already hit scintillator
    if (hit->HasSameScintillatorIdAs(*new_hit)) {
      // adds its energy
      hit->AddEnergyDeposit(energy_deposit);
      hit->AddQuenchedEnergyDeposit(quenced_energy_deposit);
      // if the new hit happened before this one, change the time
      if (hit->IsAfter(*new_hit)) {
        hit->SetTime(new_hit->GetTime());
      }
      // if the new hit deposits more energy, change the particle ID
      if (hit->DepositsLessEnergyThan(*new_hit)) {
        hit->SetParticlePdgId(new_hit->GetParticlePdgId());
      }
      found = true;
      break;
    }
  }
  // If the hit was not found, add it to the hits collection
  if (!found)
    hit_collection_->insert(new_hit);
  return found;
}

void B2SensitiveDetector::EndOfEvent(G4HCofThisEvent *) {

  // apply detector response
  for (const auto &hit: *hit_collection_->GetVector()) {

    auto quenched_energy_deposit = hit->GetQuencedEnergyDeposit();
    auto delay_time = hit->GetTime();
    const auto relative_position = hit->GetRelativePosition();
    const auto detector_id = hit->GetDetectorId();
    const auto scintillator_type = hit->GetScintillatorType();
    const auto view = hit->GetView();
    const auto plane = hit->GetPlane();
    const auto slot = hit->GetSlot();

    // Count the number of readouts. Some detectors have scintillators with single readout and some with double
    // readout. In the former case, the readouts vector will contain only one element, in the latter case it will
    // contain two elements. The ordering of the elements is arbitrary.
    const auto readouts = detector_to_readouts(detector_id, scintillator_type, plane);

    response_.SwitchDetector(detector_id);

    // The coincidence object is currently used only for BabyMIND detector
    Coincidence coincidence(detector_id, view);

    for (const auto &readout: readouts) {
      //apply light collection
      if(detector_id == kWallMrdNorth || detector_id == kWallMrdSouth || detector_id == kYasuTracker){
	G4double high_gain_peu = 0;
        G4double low_gain_peu = 0;
        delay_time = hit->GetTime();
	
        response_.ApplyOpticalSimulation(quenched_energy_deposit, relative_position, high_gain_peu, delay_time,
                                         slot, readout);

        hit->SetHighGainPeu(high_gain_peu, readout);
        hit->SetLowGainPeu(low_gain_peu, readout);
        hit->SetDelayTime(delay_time, readout);
        hit->SetQuenchedEnergyDeposit(quenched_energy_deposit);
	
      }else{	
	delay_time = hit->GetTime();
	quenched_energy_deposit = hit->GetQuencedEnergyDeposit();
	
	response_.ApplyLightCollection(quenched_energy_deposit, view, plane, slot, relative_position);
	
	//apply fiber attenuation
	response_.ApplyFiberResponse(quenched_energy_deposit, delay_time, view, plane, slot,
				     readout, relative_position);
	
	G4int high_gain_adc; // ignored for the time being
	G4int low_gain_adc; // ignored for the time being
	G4double high_gain_peu = 0;
	G4double low_gain_peu = 0;
	//convert edep -> p.e. &  p.e. statistic & cross-talk & after-pulse
	response_.ApplyMPPCResponse(high_gain_peu, quenched_energy_deposit, view, plane, slot,
				    readout, relative_position);
	
	//apply ADC responce
	response_.ApplyADCResponse(high_gain_peu, low_gain_peu, high_gain_adc, low_gain_adc);
	
	// In case of BabyMIND store the hits inside the coincidence object if a certain condition is
	// satisfied. The Coincidence object is useful to check if there is a coincidence in the double readout
	// scintillator bars or not.
	if (detector_id == B2Detector::kBabyMind) {
	  //if (!B2Dimension::CheckDeadChannel(B2Detector::kBabyMind, view, readout, plane, slot) &&
	  if (((view == B2View::kSideView && high_gain_peu > 1.5) ||
	       (view == B2View::kTopView && high_gain_peu > -0.0))) {
	    //if (((view == B2View::kSideView && high_gain_peu > -0.0) ||
	    //   (view == B2View::kTopView && high_gain_peu > -0.0))) {
	    coincidence.GetCoincidenceHit(readout).hit = true;
	    coincidence.GetCoincidenceHit(readout).highgain = high_gain_peu;
	    coincidence.GetCoincidenceHit(readout).lowgain = low_gain_peu;
	    coincidence.GetCoincidenceHit(readout).delaytime = delay_time;
	    coincidence.GetCoincidenceHit(readout).energydeposit = quenched_energy_deposit;
	  }
	} else {
	  // In case of detectors other than BabyMIND all the hits are saved
	  hit->SetHighGainPeu(high_gain_peu, readout);
	  hit->SetLowGainPeu(low_gain_peu, readout);
	  hit->SetDelayTime(delay_time, readout);
	  hit->SetQuenchedEnergyDeposit(quenched_energy_deposit);
	}
      }
    }

    // Save only the hits in BabyMIND that satisfy the coincidence condition
    if (detector_id == B2Detector::kBabyMind) {
      if (coincidence.HasCoincidence()) {
        for (const auto &coincidence_hit: coincidence.GetCoincidenceHits()) {
          const auto readout = coincidence_hit.first;
          const auto &hit_info = coincidence_hit.second;
          hit->SetHighGainPeu(hit_info.highgain, readout);
          hit->SetLowGainPeu(hit_info.lowgain, readout);
          hit->SetDelayTime(hit_info.delaytime, readout);
          hit->SetQuenchedEnergyDeposit(hit_info.energydeposit);
        }
      } else {
        for (const auto &coincidence_hit: coincidence.GetCoincidenceHits()) {
          const auto readout = coincidence_hit.first;
          hit->SetHighGainPeu(-10, readout);
          hit->SetLowGainPeu(-10, readout);
          hit->SetDelayTime(-10, readout);
          hit->SetQuenchedEnergyDeposit(0);
        }
      }
    }
    
    hit->Print();
  }
  
}

void B2SensitiveDetector::DrawAll() {
  for (const auto &hit: *hit_collection_->GetVector())
    hit->Draw();
}

void B2SensitiveDetector::PrintAll() {
  for (const auto &hit: *hit_collection_->GetVector())
    hit->Print();
}

