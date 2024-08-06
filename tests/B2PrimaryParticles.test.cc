//
// Created by Giorgio Pintaudi on 8/21/20.
//

#include "gtest/gtest.h"
#include "B2Neut.hh"

struct PrimaryParticlesTest : public testing::Test {

public:
  PrimaryParticles test;
  const std::size_t incoming_neutrino_index = 0;
  const std::size_t target_index = 1;
  const std::size_t outgoing_neutrino_index = 2;
  const std::size_t outgoing_lepton_index = 3;
  const std::size_t outgoing_target_index = 4;
  const std::size_t other_particle_index = 5;

  void SetUp() override {
    test.num_particles = 6;
    test.particle_id[incoming_neutrino_index] = PDG_t::kNuMu;
    test.particle_id[target_index] = PDG_t::kNeutron;
    test.particle_id[outgoing_neutrino_index] = PDG_t::kNuMu;
    test.particle_id[outgoing_lepton_index] = PDG_t::kMuonMinus;
    test.particle_id[outgoing_target_index] = PDG_t::kProton;
    test.particle_id[other_particle_index] = PDG_t::kPiPlus;
  }
};

TEST_F(PrimaryParticlesTest, GetIncomingNeutrinoIndex) {
  EXPECT_EQ(incoming_neutrino_index, test.GetIncomingNeutrinoIndex());
}

TEST_F(PrimaryParticlesTest, GetTargetIndex) {
  EXPECT_EQ(target_index, test.GetTargetIndex());
}

TEST_F(PrimaryParticlesTest, GetOutgoingNeutrinoIndex) {
  EXPECT_EQ(outgoing_neutrino_index, test.GetOutgoingNeutrinoIndex());
}

TEST_F(PrimaryParticlesTest, GetOutgoingLeptonIndex) {
  EXPECT_EQ(outgoing_lepton_index, test.GetOutgoingLeptonIndex());
}

TEST_F(PrimaryParticlesTest, GetOutgoingParticleIndex1) {
  EXPECT_EQ(outgoing_target_index, test.GetOutgoingParticleIndex(PDG_t::kProton));
}

TEST_F(PrimaryParticlesTest, GetOutgoingParticleIndex2) {
  EXPECT_EQ(other_particle_index, test.GetOutgoingParticleIndex(PDG_t::kPiPlus));
}

struct PrimaryParticlesTestFail1 : public testing::Test {

public:
  PrimaryParticles test;
  const std::size_t incoming_neutrino_index = 0;

  void SetUp() override {
    test.num_particles = 1;
    test.particle_id[incoming_neutrino_index] = PDG_t::kNuMu;
  }
};

TEST_F(PrimaryParticlesTestFail1, GetIncomingNeutrinoIndex) {
  EXPECT_EQ(incoming_neutrino_index, test.GetIncomingNeutrinoIndex());
}

TEST_F(PrimaryParticlesTestFail1, GetTargetIndex) {
  EXPECT_EQ(-1, test.GetTargetIndex());
}

TEST_F(PrimaryParticlesTestFail1, GetOutgoingNeutrinoIndex) {
  EXPECT_EQ(-1, test.GetOutgoingNeutrinoIndex());
}

TEST_F(PrimaryParticlesTestFail1, GetOutgoingLeptonIndex) {
  EXPECT_EQ(-1, test.GetOutgoingLeptonIndex());
}

TEST_F(PrimaryParticlesTestFail1, GetOutgoingParticleIndex1) {
  EXPECT_EQ(-1, test.GetOutgoingParticleIndex(PDG_t::kProton));
}

TEST_F(PrimaryParticlesTestFail1, GetOutgoingParticleIndex2) {
  EXPECT_EQ(-1, test.GetOutgoingParticleIndex(PDG_t::kPiPlus));
}

struct PrimaryParticlesTestFail2 : public testing::Test {

public:
  PrimaryParticles test;
  const std::size_t incoming_neutrino_index = 0;
  const std::size_t target_index = 1;
  const std::size_t outgoing_neutrino_index = 2;
  const std::size_t outgoing_target_index = 4;

  void SetUp() override {
    test.num_particles = 4;
    test.particle_id[incoming_neutrino_index] = PDG_t::kNuMu;
    test.particle_id[target_index] = PDG_t::kNeutron;
    test.particle_id[outgoing_neutrino_index] = PDG_t::kNuMu;
    test.particle_id[outgoing_target_index] = PDG_t::kProton;
  }
};

TEST_F(PrimaryParticlesTestFail2, GetIncomingNeutrinoIndex) {
  EXPECT_EQ(incoming_neutrino_index, test.GetIncomingNeutrinoIndex());
}

TEST_F(PrimaryParticlesTestFail2, GetTargetIndex) {
  EXPECT_EQ(target_index, test.GetTargetIndex());
}

TEST_F(PrimaryParticlesTestFail2, GetOutgoingNeutrinoIndex) {
  EXPECT_EQ(outgoing_neutrino_index, test.GetOutgoingNeutrinoIndex());
}

TEST_F(PrimaryParticlesTestFail2, GetOutgoingLeptonIndex) {
  EXPECT_EQ(-1, test.GetOutgoingLeptonIndex());
}

TEST_F(PrimaryParticlesTestFail2, GetOutgoingParticleIndex1) {
  EXPECT_EQ(outgoing_target_index, test.GetOutgoingParticleIndex(PDG_t::kProton));
}

TEST_F(PrimaryParticlesTestFail2, GetOutgoingParticleIndex2) {
  EXPECT_EQ(-1, test.GetOutgoingParticleIndex(PDG_t::kPiPlus));
}