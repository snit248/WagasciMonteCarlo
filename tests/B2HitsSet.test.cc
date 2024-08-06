//
// Created by Giorgio Pintaudi on 8/27/20.
//

#include "gtest/gtest.h"
#include "B2HitsSet.hh"
#include "B2HitSummary.hh"
#include "B2Enum.hh"

struct B2HitsSetTest : public testing::Test {

public:
  B2HitSummary hit1, hit2, hit3;
  Double_t peu_top1 = 1, peu_top2 = 2, peu_top3 = 3;
  Double_t peu_bottom1 = 1.5, peu_bottom2 = 2.5, peu_bottom3 = 3.5;
  Double_t time_top1 = 1, time_top2 = 2, time_top3 = 3;
  Double_t time_bottom1 = 1.5, time_bottom2 = 2.5, time_bottom3 = 3.5;
  Double_t average_peu;
  Double_t max_peu;
  TVector3 pos1, pos2, pos3;
  B2HitsSet test;
  B2Readout readout_top = B2Readout::kTopReadout;
  B2Readout readout_bottom = B2Readout::kBottomReadout;

  void SetUp() override {
    average_peu = (peu_top1 + peu_top2 + peu_top3 + peu_bottom1 + peu_bottom2 + peu_bottom3) / 6.;
    max_peu = peu_bottom3;
    pos1.SetXYZ(1, 1, 1);
    pos2.SetXYZ(2, 2, 2);
    pos3.SetXYZ(3, 3, 3);
    hit1.SetDetector(B2Detector::kWallMrdSouth);
    hit2.SetDetector(B2Detector::kWallMrdSouth);
    hit3.SetDetector(B2Detector::kWallMrdNorth);
    hit1.SetView(B2View::kUnknownView);
    hit2.SetView(B2View::kSideView);
    hit3.SetView(B2View::kTopView);
    hit1.SetPlane(3);
    hit2.SetPlane(3);
    hit3.SetPlane(6);
    hit1.SetTrueAbsolutePosition(pos1);
    hit2.SetTrueAbsolutePosition(pos2);
    hit3.SetTrueAbsolutePosition(pos3);
    hit1.SetScintillatorPosition(B2Position(pos1));
    hit2.SetScintillatorPosition(B2Position(pos2));
    hit3.SetScintillatorPosition(B2Position(pos3));
    hit1.SetHighGainPeu(readout_top, peu_top1);
    hit2.SetHighGainPeu(readout_top, peu_top2);
    hit3.SetHighGainPeu(readout_top, peu_top3);
    hit1.SetHighGainPeu(readout_bottom, peu_bottom1);
    hit2.SetHighGainPeu(readout_bottom, peu_bottom2);
    hit3.SetHighGainPeu(readout_bottom, peu_bottom3);
    hit1.SetTimeNs(readout_top, time_top1);
    hit2.SetTimeNs(readout_top, time_top2);
    hit3.SetTimeNs(readout_top, time_top3);
    hit1.SetTimeNs(readout_bottom, time_bottom1);
    hit2.SetTimeNs(readout_bottom, time_bottom2);
    hit3.SetTimeNs(readout_bottom, time_bottom3);

    test.AddHit(hit1);
    test.AddHit(hit2);
    test.AddHit(hit3);
  }
} __attribute__((packed));

TEST_F(B2HitsSetTest, SearchUpstreamHit) {
  auto &hit = test.GetUpstreamHit();
  ASSERT_DOUBLE_EQ(hit.GetTrueAbsolutePosition().GetValue().X(), pos3.X());
  ASSERT_DOUBLE_EQ(hit.GetTrueAbsolutePosition().GetValue().Y(), pos3.Y());
  ASSERT_DOUBLE_EQ(hit.GetTrueAbsolutePosition().GetValue().Z(), pos3.Z());
}

TEST_F(B2HitsSetTest, SearchDownstreamHit) {
  auto &hit = test.GetDownstreamHit();
  ASSERT_DOUBLE_EQ(hit.GetTrueAbsolutePosition().GetValue().X(), pos2.X());
  ASSERT_DOUBLE_EQ(hit.GetTrueAbsolutePosition().GetValue().Y(), pos2.Y());
  ASSERT_DOUBLE_EQ(hit.GetTrueAbsolutePosition().GetValue().Z(), pos2.Z());
}

TEST_F(B2HitsSetTest, SearchFirstHit) {
  auto &hit = test.GetFirstHit();
  ASSERT_DOUBLE_EQ(hit.GetTimeNs().GetValue(readout_top), time_top1);
}

TEST_F(B2HitsSetTest, SearchLastHit) {
  auto &hit = test.GetLastHit();
  ASSERT_DOUBLE_EQ(hit.GetTimeNs().GetValue(readout_bottom), time_bottom3);
}

TEST_F(B2HitsSetTest, SearchAveragePeu) {
  ASSERT_DOUBLE_EQ(test.GetAveragePeu().GetValue(), average_peu);
}

TEST_F(B2HitsSetTest, SearchMaxPeu) {
  ASSERT_DOUBLE_EQ(test.GetMaxPeu().GetValue(), max_peu);
}

TEST_F(B2HitsSetTest, SearchNumActivePlanes) {
  ASSERT_DOUBLE_EQ(test.GetNumActivePlanes(), 2);
}

TEST_F(B2HitsSetTest, AddDetector) {
  ASSERT_EQ(test.GetDetectors().At(0), B2Detector::kWallMrdSouth);
  ASSERT_EQ(test.GetDetectors().At(1), B2Detector::kWallMrdNorth);
  ASSERT_EQ(test.GetDetectors().At(2), B2Detector::kUnknownDetector);
  std::cout << test << std::endl;
}

TEST_F(B2HitsSetTest, GetNumHits) {
  ASSERT_EQ(test.GetNumHits(), 3);
  ASSERT_EQ(test.GetNumHits(B2View::kUnknownView), 3);
  ASSERT_EQ(test.GetNumHits(B2View::kSideView), 1);
  ASSERT_EQ(test.GetNumHits(B2View::kTopView), 1);
  ASSERT_EQ(test.GetNumHits(B2View::kUnknownView, B2Detector::kWallMrdSouth), 2);
  ASSERT_EQ(test.GetNumHits(B2View::kUnknownView, B2Detector::kWallMrdNorth), 1);
  ASSERT_EQ(test.GetNumHits(B2View::kSideView, B2Detector::kWallMrdNorth), 0);
  ASSERT_EQ(test.GetNumHits(B2View::kTopView, B2Detector::kWallMrdNorth), 1);
  ASSERT_EQ(test.GetNumHits(B2View::kSideView, B2Detector::kWallMrdSouth), 1);
  ASSERT_EQ(test.GetNumHits(B2View::kTopView, B2Detector::kWallMrdSouth), 0);
}

TEST_F(B2HitsSetTest, CardinalDirections) {
  ASSERT_EQ(test.GetHitAlongDirection(B2CardinalDirection::kNorthDirection).GetHitId(), hit1.GetHitId());
  ASSERT_EQ(test.GetHitAlongDirection(B2CardinalDirection::kDownstreamDirection).GetHitId(), hit1.GetHitId());
  ASSERT_EQ(test.GetHitAlongDirection(B2CardinalDirection::kDownDirection).GetHitId(), hit1.GetHitId());
  ASSERT_EQ(test.GetHitAlongDirection(B2CardinalDirection::kSouthDirection).GetHitId(), hit3.GetHitId());
  ASSERT_EQ(test.GetHitAlongDirection(B2CardinalDirection::kUpstreamDirection).GetHitId(), hit3.GetHitId());
  ASSERT_EQ(test.GetHitAlongDirection(B2CardinalDirection::kUpDirection).GetHitId(), hit3.GetHitId());
}