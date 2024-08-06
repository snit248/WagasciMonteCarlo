//
// Created by Giorgio Pintaudi on 8/28/20.
//

#include "gtest/gtest.h"

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"
#include "B2EventAction.hh"
#include "B2MichelElectron.hh"
#include "B2SpillSummary.hh"

struct B2EventActionTest : public testing::Test {
  B2HitSummary *hit;
  B2TrackSummary *muon = nullptr;
  B2TrackSummary *muon_neutrino = nullptr;
  B2TrackSummary *electron_anti_neutrino = nullptr;
  B2TrackSummary *michel_electron1 = nullptr;
  B2TrackSummary *michel_electron2 = nullptr;
  B2SpillSummary spill_summary;

  void SetUp() override {
    // The interaction is not correct (only invariant mass and
    // momentum are conserved but not total energy). However only
    // the invariant mass is tested so this should be OK.

    muon = &spill_summary.AddTrueTrack();
    muon_neutrino = &spill_summary.AddTrueTrack();
    electron_anti_neutrino = &spill_summary.AddTrueTrack();
    michel_electron1 = &spill_summary.AddTrueTrack();
    michel_electron2 = &spill_summary.AddTrueTrack();
    hit = &spill_summary.AddHit();

    hit->SetTrueAbsolutePosition(TVector3(1, 1, 1));
    hit->SetDetector(B2Detector::kBabyMind);

    muon->SetParticlePdg(PDG_t::kMuonMinus);
    muon->SetType(B2TrackedParticle::kPrimaryTrack);
    muon->SetTotalEnergy(268);
    muon->SetMass(105.6);
    muon->SetFinalAbsoluteMomentum(std::sqrt(268 * 268 - 105.6 * 105.6));
    muon->SetFinalMomentum(TVector3(0, 0, muon->GetFinalAbsoluteMomentum().GetValue()));
    muon->SetFinalPosition(hit->GetTrueAbsolutePosition());
    muon->SetTrackId(1);
    muon->SetParentTrackId(0);
    muon->AddHit(hit);
  }

  void OneMichel() const {
    muon_neutrino->SetParticlePdg(PDG_t::kNuMu);
    muon_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    muon_neutrino->SetTotalEnergy(10);
    muon_neutrino->SetMass(0);
    muon_neutrino->SetInitialAbsoluteMomentum(10);
    muon_neutrino->SetInitialMomentum(TVector3(0, 10, 0));
    muon_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    muon_neutrino->SetParentTrackId(muon->GetTrackId());
    muon_neutrino->SetParentTrack(muon);
    muon_neutrino->SetTrackId(2);

    electron_anti_neutrino->SetParticlePdg(PDG_t::kNuE);
    electron_anti_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    electron_anti_neutrino->SetTotalEnergy(10);
    electron_anti_neutrino->SetMass(0);
    electron_anti_neutrino->SetInitialAbsoluteMomentum(10);
    electron_anti_neutrino->SetInitialMomentum(TVector3(0, -10, 0));
    electron_anti_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    electron_anti_neutrino->SetParentTrackId(muon->GetTrackId());
    electron_anti_neutrino->SetParentTrack(muon);
    electron_anti_neutrino->SetTrackId(3);

    michel_electron1->SetParticlePdg(PDG_t::kElectron);
    michel_electron1->SetType(B2TrackedParticle::kMichelElectron);
    michel_electron1->SetTotalEnergy(268);
    michel_electron1->SetMass(0);
    michel_electron1->SetInitialAbsoluteMomentum(268);
    michel_electron1->SetInitialMomentum(TVector3(0, 0, 268));
    michel_electron1->SetInitialPosition(hit->GetTrueAbsolutePosition());
    michel_electron1->SetParentTrackId(muon->GetTrackId());
    michel_electron1->SetParentTrack(muon);
    michel_electron1->SetTrackId(4);
  }

  void TwoMichel() const {
    muon_neutrino->SetParticlePdg(PDG_t::kNuMu);
    muon_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    muon_neutrino->SetTotalEnergy(10);
    muon_neutrino->SetMass(0);
    muon_neutrino->SetInitialAbsoluteMomentum(10);
    muon_neutrino->SetInitialMomentum(TVector3(0, 10, 0));
    muon_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    muon_neutrino->SetParentTrackId(muon->GetTrackId());
    muon_neutrino->SetParentTrack(muon);
    muon_neutrino->SetTrackId(2);

    electron_anti_neutrino->SetParticlePdg(PDG_t::kNuE);
    electron_anti_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    electron_anti_neutrino->SetTotalEnergy(10);
    electron_anti_neutrino->SetMass(0);
    electron_anti_neutrino->SetInitialAbsoluteMomentum(10);
    electron_anti_neutrino->SetInitialMomentum(TVector3(0, -10, 0));
    electron_anti_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    electron_anti_neutrino->SetParentTrackId(muon->GetTrackId());
    electron_anti_neutrino->SetParentTrack(muon);
    electron_anti_neutrino->SetTrackId(3);

    michel_electron1->SetParticlePdg(PDG_t::kElectron);
    michel_electron1->SetType(B2TrackedParticle::kMichelElectron);
    michel_electron1->SetTotalEnergy(268);
    michel_electron1->SetMass(0);
    michel_electron1->SetInitialAbsoluteMomentum(268);
    michel_electron1->SetInitialMomentum(TVector3(0, 0, 268));
    michel_electron1->SetInitialPosition(hit->GetTrueAbsolutePosition());
    michel_electron1->SetParentTrackId(muon->GetTrackId());
    michel_electron1->SetParentTrack(muon);
    michel_electron1->SetTrackId(4);

    michel_electron2->SetParticlePdg(PDG_t::kElectron);
    michel_electron2->SetType(B2TrackedParticle::kMichelElectron);
    michel_electron2->SetTotalEnergy(5);
    michel_electron2->SetMass(0);
    michel_electron2->SetInitialAbsoluteMomentum(5);
    michel_electron2->SetInitialMomentum(TVector3(0, 0, 5));
    michel_electron2->SetInitialPosition(hit->GetTrueAbsolutePosition());
    michel_electron2->SetParentTrackId(muon->GetTrackId());
    michel_electron2->SetParentTrack(muon);
    michel_electron2->SetTrackId(5);
  }

  void NoMuonNeutrino() const {
    B2SpillSummary::RemoveTrueTrack(muon_neutrino);

    electron_anti_neutrino->SetParticlePdg(PDG_t::kNuE);
    electron_anti_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    electron_anti_neutrino->SetTotalEnergy(10);
    electron_anti_neutrino->SetMass(0);
    electron_anti_neutrino->SetInitialAbsoluteMomentum(10);
    electron_anti_neutrino->SetInitialMomentum(TVector3(0, -10, 0));
    electron_anti_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    electron_anti_neutrino->SetParentTrackId(muon->GetTrackId());
    electron_anti_neutrino->SetParentTrack(muon);
    electron_anti_neutrino->SetTrackId(3);

    michel_electron1->SetParticlePdg(PDG_t::kElectron);
    michel_electron1->SetType(B2TrackedParticle::kMichelElectron);
    michel_electron1->SetTotalEnergy(268);
    michel_electron1->SetMass(0);
    michel_electron1->SetInitialAbsoluteMomentum(268);
    michel_electron1->SetInitialMomentum(TVector3(0, 0, 268));
    michel_electron1->SetInitialPosition(hit->GetTrueAbsolutePosition());
    michel_electron1->SetParentTrackId(muon->GetTrackId());
    michel_electron1->SetParentTrack(muon);
    michel_electron1->SetTrackId(4);
  }

  void NoElectronNeutrino() const {
    B2SpillSummary::RemoveTrueTrack(electron_anti_neutrino);

    muon_neutrino->SetParticlePdg(PDG_t::kNuMu);
    muon_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    muon_neutrino->SetTotalEnergy(10);
    muon_neutrino->SetMass(0);
    muon_neutrino->SetInitialAbsoluteMomentum(10);
    muon_neutrino->SetInitialMomentum(TVector3(0, 10, 0));
    muon_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    muon_neutrino->SetParentTrackId(muon->GetTrackId());
    muon_neutrino->SetParentTrack(muon);
    muon_neutrino->SetTrackId(2);

    michel_electron1->SetParticlePdg(PDG_t::kElectron);
    michel_electron1->SetType(B2TrackedParticle::kMichelElectron);
    michel_electron1->SetTotalEnergy(268);
    michel_electron1->SetMass(0);
    michel_electron1->SetInitialAbsoluteMomentum(268);
    michel_electron1->SetInitialMomentum(TVector3(0, 0, 268));
    michel_electron1->SetInitialPosition(hit->GetTrueAbsolutePosition());
    michel_electron1->SetParentTrackId(muon->GetTrackId());
    michel_electron1->SetParentTrack(muon);
    michel_electron1->SetTrackId(4);
  }

  void WrongMichel() const {
    muon_neutrino->SetParticlePdg(PDG_t::kNuMu);
    muon_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    muon_neutrino->SetTotalEnergy(10);
    muon_neutrino->SetMass(0);
    muon_neutrino->SetInitialAbsoluteMomentum(10);
    muon_neutrino->SetInitialMomentum(TVector3(0, 10, 0));
    muon_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    muon_neutrino->SetParentTrackId(muon->GetTrackId());
    muon_neutrino->SetParentTrack(muon);
    muon_neutrino->SetTrackId(2);

    electron_anti_neutrino->SetParticlePdg(PDG_t::kNuE);
    electron_anti_neutrino->SetType(B2TrackedParticle::kMuonDecayNeutrino);
    electron_anti_neutrino->SetTotalEnergy(10);
    electron_anti_neutrino->SetMass(0);
    electron_anti_neutrino->SetInitialAbsoluteMomentum(10);
    electron_anti_neutrino->SetInitialMomentum(TVector3(0, -10, 0));
    electron_anti_neutrino->SetInitialPosition(hit->GetTrueAbsolutePosition());
    electron_anti_neutrino->SetParentTrackId(muon->GetTrackId());
    electron_anti_neutrino->SetParentTrack(muon);
    electron_anti_neutrino->SetTrackId(3);

    michel_electron1->SetParticlePdg(PDG_t::kElectron);
    michel_electron1->SetType(B2TrackedParticle::kMichelElectron);
    michel_electron1->SetTotalEnergy(5);
    michel_electron1->SetMass(0);
    michel_electron1->SetInitialAbsoluteMomentum(5);
    michel_electron1->SetInitialMomentum(TVector3(0, 0, 5));
    michel_electron1->SetInitialPosition(hit->GetTrueAbsolutePosition());
    michel_electron1->SetParentTrackId(muon->GetTrackId());
    michel_electron1->SetParentTrack(muon);
    michel_electron1->SetTrackId(4);
  }

  B2TrackSummary *SearchTrack(B2PrimaryTrackType type, PDG_t pdg_id) {
    auto it = spill_summary.BeginTrueTrack();
    while (auto *track_summary = it.Next()) {
      if (track_summary->GetPrimaryTrackType() == type &&
          track_summary->GetParticlePdg() == pdg_id &&
          track_summary->IsValid()) {
        return track_summary;
      }
    }
    return nullptr;
  }

  int HowMany(B2TrackedParticle type, PDG_t pdg_id) {
    int counter = 0;
    auto it = spill_summary.BeginTrueTrack();
    while (auto *track_summary = it.Next()) {
      if (track_summary->GetType() == type &&
          track_summary->GetParticlePdg() == pdg_id &&
          track_summary->IsValid()) {
        ++counter;
      }
    }
    return counter;
  }
};

TEST_F(B2EventActionTest, OneMichelTest) {
  OneMichel();
  B2MichelElectron test(spill_summary);
  test.SearchMichelElectronCandidates();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kPrimaryTrack, PDG_t::kMuonMinus), muon);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), muon_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), electron_anti_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), michel_electron1);
}

TEST_F(B2EventActionTest, TwoMichelTest) {
  TwoMichel();
  EXPECT_EQ(HowMany(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), 2);
  B2MichelElectron test(spill_summary);
  test.SearchMichelElectronCandidates();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kPrimaryTrack, PDG_t::kMuonMinus), muon);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), muon_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), electron_anti_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), michel_electron1);
  EXPECT_NE(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), michel_electron2);
  EXPECT_EQ(HowMany(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), 1);
}

TEST_F(B2EventActionTest, NoMuonNeutrinoTest) {
  NoMuonNeutrino();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), electron_anti_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), michel_electron1);
  B2MichelElectron test(spill_summary);
  test.SearchMichelElectronCandidates();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kPrimaryTrack, PDG_t::kMuonMinus), muon);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), nullptr);
}

TEST_F(B2EventActionTest, NoElectronNeutrinoTest) {
  NoElectronNeutrino();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), muon_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), michel_electron1);
  B2MichelElectron test(spill_summary);
  test.SearchMichelElectronCandidates();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kPrimaryTrack, PDG_t::kMuonMinus), muon);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), nullptr);
}

TEST_F(B2EventActionTest, WrongMichelTest) {
  WrongMichel();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), muon_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), electron_anti_neutrino);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), michel_electron1);
  B2MichelElectron test(spill_summary);
  test.SearchMichelElectronCandidates();
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kPrimaryTrack, PDG_t::kMuonMinus), muon);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuMu), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMuonDecayNeutrino, PDG_t::kNuE), nullptr);
  EXPECT_EQ(SearchTrack(B2TrackedParticle::kMichelElectron, PDG_t::kElectron), nullptr);
}
