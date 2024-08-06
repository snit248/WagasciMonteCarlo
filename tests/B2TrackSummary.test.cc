//
// Created by Giorgio Pintaudi on 8/16/20.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"

using ::testing::AtLeast;
using ::testing::Return;

class MockHit : public B2HitSummary {
public:
  MOCK_METHOD0(Print, void());
};

class MockCluster : public B2ClusterSummary {
public:
  MOCK_METHOD0(Print, void());
};

struct B2TrackSummaryTestMock : public testing::Test {
  B2TrackSummary test;
  MockCluster mock_cluster1;
  MockCluster mock_cluster2;
  MockHit mock_hit1;
  MockHit mock_hit2;

  void SetUp() override {
    mock_cluster1.SetClusterId(1);
    mock_cluster2.SetClusterId(2);
    mock_cluster1.AddHit(mock_hit1);
    mock_cluster2.AddHit(mock_hit2);
    test.AddCluster(mock_cluster1, kTRUE);
    test.AddCluster(mock_cluster2, kTRUE);
  }
};

TEST_F(B2TrackSummaryTestMock, BeginCluster) {

  EXPECT_CALL(mock_cluster1, Print).Times(1);
  EXPECT_CALL(mock_cluster2, Print).Times(1);

  auto it = test.BeginCluster();
  while (auto * cluster = (MockCluster *) it.Next()) {
    cluster->Print();
  }
}

TEST_F(B2TrackSummaryTestMock, BeginHit) {

  EXPECT_CALL(mock_hit1, Print).Times(1);
  EXPECT_CALL(mock_hit2, Print).Times(1);

  auto it = test.BeginHit();
  while (auto * hit = (MockHit *) it.Next()) {
    hit->Print();
  }
}

TEST_F(B2TrackSummaryTestMock, GetCluster) {
  auto id = mock_cluster1.GetClusterId();
  auto cluster = test.GetCluster(id);
  ASSERT_EQ(cluster, mock_cluster1);
}

TEST_F(B2TrackSummaryTestMock, GetWrongCluster) {
  ASSERT_THROW(test.GetCluster(-1), std::out_of_range);
}

TEST_F(B2TrackSummaryTestMock, Clear) {
  EXPECT_EQ(test.GetNumClusters(), 2);
  test.Clear("C");
  EXPECT_EQ(test.GetNumClusters(), 0);
}
