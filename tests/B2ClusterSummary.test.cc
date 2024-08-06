//
// Created by Giorgio Pintaudi on 8/15/20.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"

using ::testing::AtLeast;
using ::testing::Return;

class MockHit : public B2HitSummary {
public:
  MOCK_METHOD0(Print, void());
};

struct B2ClusterSummaryTestMockHit : public testing::Test {
  B2ClusterSummary test;
  MockHit mock_hit1;
  MockHit mock_hit2;

  void SetUp() override {
    test.AddHit(mock_hit1);
    test.AddHit(mock_hit2);
  }
};

TEST_F(B2ClusterSummaryTestMockHit, Begin) {

  EXPECT_CALL(mock_hit1, Print).Times(1);
  EXPECT_CALL(mock_hit2, Print).Times(1);

  auto it = test.BeginHit();
  while (auto * hit = (MockHit *) it.Next()) {
    hit->Print();
  }
}

struct B2ClusterSummaryTestRealHit : public testing::Test {
  B2ClusterSummary test;
  B2HitSummary real_hit1;
  B2HitSummary real_hit2;
  B2HitSummary real_hit3;

  void SetUp() override {
    real_hit1.SetTimeNs(B2Readout::kTopReadout, 1);
    real_hit2.SetTimeNs(B2Readout::kTopReadout, 2);
    real_hit3.SetTimeNs(B2Readout::kTopReadout, 3);
    real_hit1.SetTrueAbsolutePosition(B2Position(0, 0, 3, 0, 0, 0));
    real_hit2.SetTrueAbsolutePosition(B2Position(0, 0, 2, 0, 0, 0));
    real_hit3.SetTrueAbsolutePosition(B2Position(0, 0, 1, 0, 0, 0));
    test.AddHit(real_hit1);
    test.AddHit(real_hit2);
    test.AddHit(real_hit3);
  }
};

TEST_F(B2ClusterSummaryTestRealHit, SearchFirst) {
  ASSERT_EQ(real_hit1, test.GetFirstHit());
}

TEST_F(B2ClusterSummaryTestRealHit, SearchLast) {
  ASSERT_EQ(real_hit3, test.GetLastHit());
}

TEST_F(B2ClusterSummaryTestRealHit, SearchUpstream) {
  ASSERT_EQ(real_hit3, test.GetUpstreamHit());
}

TEST_F(B2ClusterSummaryTestRealHit, SearchDownstream) {
  ASSERT_EQ(real_hit1, test.GetDownstreamHit());
}