//
// Created by Giorgio Pintaudi on 2020/10/21.
//


#include <string>

#include "gtest/gtest.h"
#include "B2Volume.hh"

struct B2VolumeTest : public testing::Test {

public:
  TVector3 position;
  TVector3 dimensions;
  B2Detector detector;
  B2DetectorVolume test_origin;
  B2DetectorVolume test_generic;

  B2VolumeTest() : position(10 * m, 10 * m, 10 * m),
                   dimensions(1 * m, 1 * m, 1 * m),
                   detector(B2Detector::kWagasciUpstream),
                   test_origin(TVector3(0, 0, 0), dimensions, detector, "WagasciUpstream"),
                   test_generic(position, dimensions, detector, "WagasciUpstream") {}
};

TEST_F(B2VolumeTest, IsRelativePointContained) {
  ASSERT_TRUE(test_origin.IsRelativePointContained(TVector3(0, 0, 0)));
  ASSERT_TRUE(test_origin.IsRelativePointContained(TVector3(100, 0, 0)));
  ASSERT_TRUE(test_origin.IsRelativePointContained(TVector3(0, 100, 0)));
  ASSERT_TRUE(test_origin.IsRelativePointContained(TVector3(0, 0, 100)));
  ASSERT_TRUE(test_origin.IsRelativePointContained(TVector3(100, 100, 100)));
  ASSERT_FALSE(test_origin.IsRelativePointContained(TVector3(1100, 0, 0)));
  ASSERT_FALSE(test_origin.IsRelativePointContained(TVector3(0, 1100, 0)));
  ASSERT_FALSE(test_origin.IsRelativePointContained(TVector3(0, 0, 1100)));
  ASSERT_FALSE(test_origin.IsRelativePointContained(TVector3(1100, 0, 0)));
  ASSERT_FALSE(test_origin.IsRelativePointContained(TVector3(1100, 1100, 1100)));

  ASSERT_TRUE(test_generic.IsRelativePointContained(TVector3(0, 0, 0)));
  ASSERT_TRUE(test_generic.IsRelativePointContained(TVector3(100, 0, 0)));
  ASSERT_TRUE(test_generic.IsRelativePointContained(TVector3(0, 100, 0)));
  ASSERT_TRUE(test_generic.IsRelativePointContained(TVector3(0, 0, 100)));
  ASSERT_TRUE(test_generic.IsRelativePointContained(TVector3(100, 100, 100)));
  ASSERT_FALSE(test_generic.IsRelativePointContained(TVector3(1100, 0, 0)));
  ASSERT_FALSE(test_generic.IsRelativePointContained(TVector3(0, 1100, 0)));
  ASSERT_FALSE(test_generic.IsRelativePointContained(TVector3(0, 0, 1100)));
  ASSERT_FALSE(test_generic.IsRelativePointContained(TVector3(1100, 0, 0)));
  ASSERT_FALSE(test_generic.IsRelativePointContained(TVector3(1100, 1100, 1100)));
}

TEST_F(B2VolumeTest, IsAbsolutePointContained) {
  ASSERT_TRUE(test_origin.IsAbsolutePointContained(TVector3(0, 0, 0)));
  ASSERT_TRUE(test_origin.IsAbsolutePointContained(TVector3(100, 0, 0)));
  ASSERT_TRUE(test_origin.IsAbsolutePointContained(TVector3(0, 100, 0)));
  ASSERT_TRUE(test_origin.IsAbsolutePointContained(TVector3(0, 0, 100)));
  ASSERT_TRUE(test_origin.IsAbsolutePointContained(TVector3(100, 100, 100)));
  ASSERT_FALSE(test_origin.IsAbsolutePointContained(TVector3(1100, 0, 0)));
  ASSERT_FALSE(test_origin.IsAbsolutePointContained(TVector3(0, 1100, 0)));
  ASSERT_FALSE(test_origin.IsAbsolutePointContained(TVector3(0, 0, 1100)));
  ASSERT_FALSE(test_origin.IsAbsolutePointContained(TVector3(1100, 0, 0)));
  ASSERT_FALSE(test_origin.IsAbsolutePointContained(TVector3(1100, 1100, 1100)));

  ASSERT_TRUE(test_generic.IsAbsolutePointContained(TVector3(10 * m, 10 * m, 10 * m)));
  ASSERT_TRUE(test_generic.IsAbsolutePointContained(TVector3(10 * m + 100, 10 * m, 10 * m)));
  ASSERT_TRUE(test_generic.IsAbsolutePointContained(TVector3(10 * m, 10 * m + 100, 10 * m)));
  ASSERT_TRUE(test_generic.IsAbsolutePointContained(TVector3(10 * m, 10 * m, 10 * m + 100)));
  ASSERT_TRUE(test_generic.IsAbsolutePointContained(TVector3(10 * m + 100, 10 * m + 100, 10 * m + 100)));
  ASSERT_FALSE(test_generic.IsAbsolutePointContained(TVector3(0, 0, 0)));
  ASSERT_FALSE(test_generic.IsAbsolutePointContained(TVector3(100, 0, 0)));
  ASSERT_FALSE(test_generic.IsAbsolutePointContained(TVector3(0, 100, 0)));
  ASSERT_FALSE(test_generic.IsAbsolutePointContained(TVector3(0, 0, 100)));
  ASSERT_FALSE(test_generic.IsAbsolutePointContained(TVector3(100, 100, 100)));
}

TEST_F(B2VolumeTest, IntersectionPointRelative1) {
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(1, 0, 0);
    TVector2 intersection;
    ASSERT_TRUE(test_origin.IntersectionPointRelative(B2View::kTopView, start, direction, intersection));
    TVector2 expected(0, 500);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(1, 0, 0);
    TVector2 intersection;
    ASSERT_TRUE(test_generic.IntersectionPointRelative(B2View::kTopView, start, direction, intersection));
    TVector2 expected(0, 500);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
}

TEST_F(B2VolumeTest, IntersectionPointRelative2) {
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(0, 1, 0);
    TVector2 intersection;
    ASSERT_FALSE(test_origin.IntersectionPointRelative(B2View::kTopView, start, direction, intersection));
  }
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(0, 1, 0);
    TVector2 intersection;
    ASSERT_FALSE(test_generic.IntersectionPointRelative(B2View::kTopView, start, direction, intersection));
  }
}

TEST_F(B2VolumeTest, IntersectionPointRelative3) {
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(0, 0, 1);
    TVector2 intersection;
    ASSERT_TRUE(test_origin.IntersectionPointRelative(B2View::kTopView, start, direction, intersection));
    TVector2 expected(500, 0);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(0, 0, 1);
    TVector2 intersection;
    ASSERT_TRUE(test_generic.IntersectionPointRelative(B2View::kTopView, start, direction, intersection));
    TVector2 expected(500, 0);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
}

TEST_F(B2VolumeTest, IntersectionPointAbsolute1) {
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(1, 0, 0);
    TVector2 intersection;
    ASSERT_TRUE(test_origin.IntersectionPointAbsolute(B2View::kTopView, start, direction, intersection));
    TVector2 expected(0, 500);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
  {
    TVector3 start(10 * m, 10 * m, 10 * m);
    TVector3 direction(1, 0, 0);
    TVector2 intersection;
    ASSERT_TRUE(test_generic.IntersectionPointAbsolute(B2View::kTopView, start, direction, intersection));
    TVector2 expected(10 * m, 10 * m + 500);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
}

TEST_F(B2VolumeTest, IntersectionPointAbsolute2) {
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(0, 1, 0);
    TVector2 intersection;
    ASSERT_FALSE(test_origin.IntersectionPointAbsolute(B2View::kTopView, start, direction, intersection));
  }
  {
    TVector3 start(10 * m, 10 * m, 10 * m);
    TVector3 direction(0, 1, 0);
    TVector2 intersection;
    ASSERT_FALSE(test_generic.IntersectionPointAbsolute(B2View::kTopView, start, direction, intersection));
  }
}

TEST_F(B2VolumeTest, IntersectionPointAbsolute3) {
  {
    TVector3 start(0, 0, 0);
    TVector3 direction(0, 0, 1);
    TVector2 intersection;
    ASSERT_TRUE(test_origin.IntersectionPointAbsolute(B2View::kTopView, start, direction, intersection));
    TVector2 expected(500, 0);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
  {
    TVector3 start(10 * m, 10 * m, 10 * m);
    TVector3 direction(0, 0, 1);
    TVector2 intersection;
    ASSERT_TRUE(test_generic.IntersectionPointAbsolute(B2View::kTopView, start, direction, intersection));
    TVector2 expected(10 * m + 500, 10 * m);
    ASSERT_DOUBLE_EQ(intersection.X(), expected.X());
    ASSERT_DOUBLE_EQ(intersection.Y(), expected.Y());
  }
}