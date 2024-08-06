#include "B2EmulsionSensitiveDetector.hh"

#include <G4HCofThisEvent.hh>
#include <G4Step.hh>
#include <G4Track.hh>
#include <G4VTouchable.hh>
#include <G4TouchableHistory.hh>

#include "B2Pdg.hh"

B2EmulsionSensitiveDetector::B2EmulsionSensitiveDetector(const G4String &name)
    : G4VSensitiveDetector(name) {
  collectionName.insert("emulsionHitCollection");
}

void B2EmulsionSensitiveDetector::Initialize(G4HCofThisEvent *emulsion_hit_collections_this_event) {
  emulsion_hit_collection_ =
    new B2EmulsionHitsCollection(SensitiveDetectorName, collectionName.front());
  total_emulsion_dep_ = 0;
  emulsion_hit_collections_this_event->AddHitsCollection(GetCollectionID(0), emulsion_hit_collection_);
}

G4bool B2EmulsionSensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *) {
  // Create a new hit only when there is energy deposit 
  const G4double energy_deposit = step->GetTotalEnergyDeposit();
  if (energy_deposit == 0.) return false;
  else total_emulsion_dep_ += energy_deposit;
  const G4double quenched_energy_deposit = energy_deposit;

  G4Track *track = step->GetTrack();
  G4int track_id = track->GetTrackID();

  // Only Muon, Proton, Charged pion information is stored 
  const G4int particle_pdg_id = track->GetDefinition()->GetPDGEncoding();
  if(!B2Pdg::IsMuonPlusOrMinus(particle_pdg_id) &&
     !(particle_pdg_id == kProton) &&
     !B2Pdg::IsChargedPion(particle_pdg_id))
    return false;

  // Volume information must be extracted from Touchable of "PreStepPoint"
  const G4VTouchable *p_touchable = step->GetPreStepPoint()->GetTouchable();
  const G4int emulsion_id = p_touchable->GetVolume(0)->GetCopyNo();

  const G4ThreeVector hit_absolute_pre_position = step->GetPreStepPoint()->GetPosition();
  const G4ThreeVector hit_absolute_post_position = step->GetPostStepPoint()->GetPosition();
  const G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();

  // Create a new hit
  B2EmulsionHit *new_emulsion_hit = new B2EmulsionHit(emulsion_id, track_id);
  new_emulsion_hit->SetParticlePdgId(particle_pdg_id);
  new_emulsion_hit->SetEnergyDeposit(energy_deposit);
  new_emulsion_hit->SetQuenchedEnergyDeposit(quenched_energy_deposit);
  new_emulsion_hit->SetPrePosition(hit_absolute_pre_position);
  new_emulsion_hit->SetPostPosition(hit_absolute_post_position);
  new_emulsion_hit->SetMomentum(momentum);
  new_emulsion_hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());

  // Look for a hit in the same film and of the same track
  G4bool found = false;
  for(auto &emulsion_hit : *emulsion_hit_collection_->GetVector()) {
    if(emulsion_hit->HasSameEmulsionIdAs(*new_emulsion_hit) &&
       emulsion_hit->HasSameTrackIdAs(*new_emulsion_hit)) {
      // add its energy
      emulsion_hit->AddEnergyDeposit(energy_deposit);
      emulsion_hit->AddQuenchedEnergyDeposit(quenched_energy_deposit);
      // if the new hit happend before, update preposition, momentum, and time
      if (emulsion_hit->IsAfter(*new_emulsion_hit)) {
	emulsion_hit->SetPrePosition(new_emulsion_hit->GetAbsolutePrePosition());
	emulsion_hit->SetMomentum(new_emulsion_hit->GetMomentum());
	emulsion_hit->SetTime(new_emulsion_hit->GetTime());
      }
      // else the new hit happend after, update postposition
      else {
	emulsion_hit->SetPostPosition(new_emulsion_hit->GetAbsolutePostPosition());
      }
      found = true;
      break;
    }
  }
  if(!found)
    emulsion_hit_collection_->insert(new_emulsion_hit);
  return found;
}

void B2EmulsionSensitiveDetector::EndOfEvent(G4HCofThisEvent *) {
  for (const auto &emulsion_hit : *emulsion_hit_collection_->GetVector())
    // Apply hit response if necessary TODO
    emulsion_hit->Print();
}

void B2EmulsionSensitiveDetector::DrawAll() {
  for (const auto &emulsion_hit : *emulsion_hit_collection_->GetVector())
    emulsion_hit->Draw();
}

void B2EmulsionSensitiveDetector::PrintAll() {
  for (const auto &emulsion_hit : *emulsion_hit_collection_->GetVector())
    emulsion_hit->Print();
}

