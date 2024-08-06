//
// Created by Giorgio Pintaudi on 8/18/20.
//

#include "gtest/gtest.h"

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"
#include "B2EventSummary.hh"
#include "B2EmulsionSummary.hh"
#include "B2SpillSummary.hh"

struct B2SpillSummaryTest : public testing::Test {
  B2SpillSummary test;
  B2HitSummary mock_hit1;
  B2HitSummary mock_hit2;
  B2ClusterSummary mock_cluster1;
  B2ClusterSummary mock_cluster2;
  B2TrackSummary mock_track1;
  B2TrackSummary mock_track2;
  B2VertexSummary mock_vertex1;
  B2VertexSummary mock_vertex2;
  B2EventSummary mock_event1;
  B2EventSummary mock_event2;
#ifdef NINJA
  B2EmulsionSummary mock_emulsion1;
  B2EmulsionSummary mock_emulsion2;
#endif

  void SetUp() override {
    mock_hit1.SetDetector(B2Detector::kBabyMind);
    mock_hit2.SetDetector(B2Detector::kBabyMind);
    mock_hit1.SetScintillatorType(B2ScintillatorType::kHorizontal);
    mock_hit2.SetScintillatorType(B2ScintillatorType::kHorizontal);
    mock_hit1.SetPlaneGrid(B2GridPlane::kPlaneScintillator);
    mock_hit2.SetPlaneGrid(B2GridPlane::kPlaneScintillator);
    mock_cluster1.SetClusterId(1);
    mock_cluster2.SetClusterId(2);
    mock_track1.SetTrackId(1);
    mock_track2.SetTrackId(2);
    mock_cluster1.AddHit(mock_hit1);
    mock_cluster2.AddHit(mock_hit2);
    mock_track1.AddCluster(mock_cluster1, kTRUE);
    mock_track2.AddCluster(mock_cluster2, kTRUE);

    test.AddHit(mock_hit1);
    test.AddHit(mock_hit2);
    test.AddTrueCluster(mock_cluster1);
    test.AddTrueCluster(mock_cluster2);
    test.AddTrueTrack(mock_track1);
    test.AddTrueTrack(mock_track2);
    test.AddTrueVertex(mock_vertex1);
    test.AddTrueVertex(mock_vertex2);
    test.AddTrueEvent(mock_event1);
    test.AddTrueEvent(mock_event2);
    test.GetBeamSummary().SetWagasciRun(100);

#ifdef NINJA
    mock_emulsion1.SetEmulsionTrackId(1);
    mock_emulsion2.SetEmulsionTrackId(2);
    mock_emulsion1.SetEcc(1);
    mock_emulsion2.SetEcc(2);
    test.AddEmulsion(mock_emulsion1);
    test.AddEmulsion(mock_emulsion2);
#endif
  }
};

TEST_F(B2SpillSummaryTest, CopyConstructor) {
  B2SpillSummary test_copy(test);
  ASSERT_EQ(test.GetNumHits(), test_copy.GetNumHits());
  ASSERT_EQ(test.GetHits().GetLast(), test_copy.GetHits().GetLast());
  ASSERT_EQ(test.GetBeamSummary().GetWagasciRun(), 100);
  ASSERT_EQ(test_copy.GetBeamSummary().GetWagasciRun(), 100);
}

TEST_F(B2SpillSummaryTest, CopyAssignment) {
  B2SpillSummary test_copy;
  test_copy = test;
  ASSERT_EQ(test.GetNumHits(), test_copy.GetNumHits());
  ASSERT_EQ(test.GetHits().GetLast(), test_copy.GetHits().GetLast());
}

TEST_F(B2SpillSummaryTest, MoveConstructor) {
  ASSERT_NO_THROW(B2SpillSummary test_copy(std::move(test)));
}

TEST_F(B2SpillSummaryTest, MoveAssignment) {
  ASSERT_NO_THROW(
      B2SpillSummary test_copy;
      test_copy = std::move(test);
      test.Clear("C");
  );
}

TEST_F(B2SpillSummaryTest, BeginHit) {
  auto it = test.BeginHit();
  while (auto * hit = (B2HitSummary *) it.Next()) {
    std::cout << *hit << std::endl;
  }
}

TEST_F(B2SpillSummaryTest, BeginCluster) {
  auto it = test.BeginTrueCluster();
  while (auto * cluster = (B2ClusterSummary *) it.Next()) {
    cluster->Print();
  }
}

TEST_F(B2SpillSummaryTest, BeginTrueTrack) {
  auto it = test.BeginTrueTrack();
  while (auto * track = (B2TrackSummary *) it.Next()) {
    track->Print();
  }
}

TEST_F(B2SpillSummaryTest, BeginTrueVertex) {
  auto it = test.BeginTrueVertex();
  while (auto * vertex = (B2VertexSummary *) it.Next()) {
    vertex->Print();
  }
}

TEST_F(B2SpillSummaryTest, BeginTrueEvent) {
  auto it = test.BeginTrueEvent();
  while (auto * event = (B2EventSummary *) it.Next()) {
    event->Print();
  }
}

TEST_F(B2SpillSummaryTest, GetCluster) {
  auto cluster = test.GetTrueCluster(mock_cluster1.GetClusterId());
  ASSERT_EQ(cluster, mock_cluster1);
}

TEST_F(B2SpillSummaryTest, GetTrack) {
  auto track = test.GetTrueTrack(mock_track1.GetTrackId());
  ASSERT_EQ(track, mock_track1);
}

TEST_F(B2SpillSummaryTest, GetWrongCluster) {
  ASSERT_THROW(test.GetTrueCluster(-1), std::out_of_range);
}

TEST_F(B2SpillSummaryTest, GetWrongTrack) {
  ASSERT_THROW(test.GetTrueTrack(-1), std::out_of_range);
}

#ifdef NINJA
TEST_F(B2SpillSummaryTest, GetEmulsion) {
  ASSERT_EQ(test.GetNumEmulsions(), 2);
  ASSERT_EQ(test.GetEmulsion(1).GetEcc(), 1);
  ASSERT_EQ(test.GetEmulsion(2).GetEcc(), 2);
}
#endif

TEST_F(B2SpillSummaryTest, Clear) {
  EXPECT_EQ(test.GetNumHits(), 2);
  EXPECT_EQ(test.GetNumTrueClusters(), 2);
  EXPECT_EQ(test.GetNumTrueTracks(), 2);
  EXPECT_EQ(test.GetNumTrueVertices(), 2);
  EXPECT_EQ(test.GetNumTrueEvents(), 2);
  test.Clear("C");
  EXPECT_EQ(test.GetNumHits(), 0);
  EXPECT_EQ(test.GetNumTrueClusters(), 0);
  EXPECT_EQ(test.GetNumTrueTracks(), 0);
  EXPECT_EQ(test.GetNumTrueVertices(), 0);
  EXPECT_EQ(test.GetNumTrueEvents(), 0);
}