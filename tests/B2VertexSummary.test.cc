//
// Created by Giorgio Pintaudi on 8/17/20.
//

#include "gtest/gtest.h"

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"

struct B2VertexSummaryTest : public testing::Test {
  B2VertexSummary test;
  B2TrackSummary mock_track1;
  B2TrackSummary mock_track2;
  B2TrackSummary mock_track3;
  B2HitSummary mock_hit1;

  void SetUp() override {
    test.SetClosestHit(mock_hit1);
    test.SetIncomingTrack(mock_track3);
    test.AddOutgoingTrack(mock_track1);
    test.AddOutgoingTrack(mock_track2);
  }
};

TEST_F(B2VertexSummaryTest, Begin) {
  auto it = test.BeginTrack();
  while (auto * hit = (B2TrackSummary *) it.Next()) {
    hit->Print();
  }
}

TEST_F(B2VertexSummaryTest, GetIncomingTrack) {
  auto track = test.GetIncomingTrack();
  ASSERT_EQ(track, mock_track3);
}

TEST_F(B2VertexSummaryTest, GetWrongTrack) {
  ASSERT_THROW(test.GetOutgoingTrack(-1), std::out_of_range);
}

TEST_F(B2VertexSummaryTest, Clear) {
  EXPECT_EQ(test.GetNumOutgoingTracks(), 2);
  test.Clear("C");
  EXPECT_EQ(test.GetNumOutgoingTracks(), 0);
}
