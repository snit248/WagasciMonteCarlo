//
// Created by Giorgio Pintaudi on 8/23/20.
//

#include <string>
#include "gtest/gtest.h"
#include "B2Dimension.hh"
#include <fstream>
#include <boost/make_unique.hpp>

std::string GEOMETRY_DIRECTORY;

struct TestB2Dimension : public testing::Test {
  std::unique_ptr<B2Dimension> test;

  void SetUp() override {
    test = boost::make_unique<B2Dimension>(GEOMETRY_DIRECTORY);
  }
};

TEST_F(TestB2Dimension, ProtonModule) {
  std::ofstream of("proton_module_channel_position.txt", std::ios::trunc);
  of << "# index X Y Z view color\n";
  int index = 0;

  // Front VETO
  for (int channel = 0; channel < PM_NUM_CHANNELS_FRONT_VETO; ++channel) {
    TVector3 pos_top, pos_side;
    ASSERT_TRUE(B2Dimension::GetPosPm(B2View::kTopView, 0, channel, pos_top));
    of << index++ << " " << pos_top.x() << " " << pos_top.y() << " "
       << pos_top.z() << " " << B2View::kTopView << " " << 2 <<"\n";
    ASSERT_TRUE(B2Dimension::GetPosPm(B2View::kSideView, 0, channel, pos_side));
    of << index++ << " " << pos_side.x() << " " << pos_side.y() << " "
       << pos_side.z() << " " << B2View::kSideView << " " << 2 << "\n";
  }

  // Tracking planes
  for (int plane = PM_NUM_FRONT_VETO_PLANES; plane < PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES; ++plane) {
    for (int channel = 0; channel < PM_NUM_CHANNELS_ONE_TRACK_PLANE; ++channel) {
      TVector3 pos_top, pos_side;
      ASSERT_TRUE(B2Dimension::GetPosPm(B2View::kTopView, plane, channel, pos_top));
      of << index++ << " " << pos_top.x() << " " << pos_top.y() << " "
         << pos_top.z() << " " << B2View::kTopView << " " << 1 << "\n";
      ASSERT_TRUE(B2Dimension::GetPosPm(B2View::kSideView, plane, channel, pos_side));
      of << index++ << " " << pos_side.x() << " " << pos_side.y() << " "
         << pos_side.z() << " " << B2View::kSideView << " " << 1 << "\n";
    }
  }

  // Other VETO planes
  for (int plane = PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES; plane < PM_NUM_PLANES; ++plane) {
    for (int channel = 0; channel < PM_NUM_TRACKING_PLANES; ++channel) {
      TVector3 pos_top, pos_side;
      ASSERT_TRUE(B2Dimension::GetPosPm(B2View::kTopView, plane, channel, pos_top));
      of << index++ << " " << pos_top.x() << " " << pos_top.y() << " "
         << pos_top.z() << " " << B2View::kTopView << " " << 3 << "\n";
      ASSERT_TRUE(B2Dimension::GetPosPm(B2View::kSideView, plane, channel, pos_side));
      of << index++ << " " << pos_side.x() << " " << pos_side.y() << " "
         << pos_side.z() << " " << B2View::kSideView << " " << 3 << "\n";
    }
  }
}

TEST_F(TestB2Dimension, ProtonModuleFailure) {
  TVector3 ignore;
  ASSERT_FALSE(B2Dimension::GetPosPm(B2View::kTopView, -1, 0 , ignore));
  ASSERT_FALSE(B2Dimension::GetPosPm(B2View::kTopView, PM_NUM_PLANES, 0 , ignore));
  ASSERT_FALSE(B2Dimension::GetPosPm(B2View::kTopView, 0, -1 , ignore));
  ASSERT_FALSE(B2Dimension::GetPosPm(B2View::kTopView, 0,  PM_NUM_CHANNELS_FRONT_VETO, ignore));
  ASSERT_FALSE(B2Dimension::GetPosPm(B2View::kTopView, 1, -1 , ignore));
  ASSERT_FALSE(B2Dimension::GetPosPm(B2View::kTopView, 1, PM_NUM_CHANNELS_ONE_TRACK_PLANE , ignore));
}

TEST_F(TestB2Dimension, ProtonModuleErrorFailure) {
  TVector3 ignore;
  ASSERT_FALSE(B2Dimension::GetErrorPm(B2View::kTopView, -1, 0 , ignore));
  ASSERT_FALSE(B2Dimension::GetErrorPm(B2View::kTopView, PM_NUM_PLANES, 0 , ignore));
  ASSERT_FALSE(B2Dimension::GetErrorPm(B2View::kTopView, 0, -1 , ignore));
  ASSERT_FALSE(B2Dimension::GetErrorPm(B2View::kTopView, 0,  PM_NUM_CHANNELS_FRONT_VETO, ignore));
  ASSERT_FALSE(B2Dimension::GetErrorPm(B2View::kTopView, 1, -1 , ignore));
  ASSERT_FALSE(B2Dimension::GetErrorPm(B2View::kTopView, 1, PM_NUM_CHANNELS_ONE_TRACK_PLANE , ignore));
}

TEST_F(TestB2Dimension, Wagasci) {

  std::ofstream of("wagasci_channel_position.txt", std::ios::trunc);
  of << "# index X Y Z view color\n";
  int index = 1;

  for (unsigned plane = 0; plane < WGS_NUM_PLANES; ++plane) {
    for (unsigned slot = 0; slot < WGS_NUM_SLOTS; ++slot) {
      TVector3 pos_top, pos_side;
      ASSERT_TRUE(test->GetPosWgs(B2View::kTopView, plane, slot, pos_top));
      of << index++ << " " << pos_top.x() << " " << pos_top.y() << " "
         << pos_top.z() << " " << B2View::kTopView << " " << plane % 2 + 1 << "\n";
      ASSERT_TRUE(test->GetPosWgs(B2View::kSideView, plane, slot, pos_side));
      of << index++ << " " << pos_side.x() << " " << pos_side.y() << " "
         << pos_side.z() << " " << B2View::kSideView << " " << plane % 2 + 1 << "\n";
    }
  }
}

TEST_F(TestB2Dimension, WagasciFailure) {
  TVector3 ignore;
  ASSERT_FALSE(test->GetPosWgs(B2View::kTopView, -1, 0, ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kSideView, -1, 0, ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kTopView, WGS_NUM_PLANES, 0, ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kSideView, WGS_NUM_PLANES, 0, ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kTopView, 0, -1 , ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kSideView, 0, -1 , ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kTopView, 0, WGS_NUM_SLOTS, ignore));
  ASSERT_FALSE(test->GetPosWgs(B2View::kSideView, 0, WGS_NUM_SLOTS, ignore));
}

TEST_F(TestB2Dimension, WallMrdNorth) {

  std::ofstream of("wallmrd_north_channel_position.txt", std::ios::trunc);
  of << "# index X Y Z view color\n";
  int index = 1;

  for (unsigned plane = 0; plane < WM_NUM_SCINTI_PLANES; ++plane) {
    for (unsigned slot = 0; slot < WM_NUM_SCINTI_IN_ONE_PLANE; ++slot) {
      TVector3 pos;
      ASSERT_TRUE(test->GetPosWallMrd(B2Detector::kWallMrdNorth, plane, slot, pos));
      of << index++ << " " << pos.x() << " " << pos.y() << " "
         << pos.z() << " " << B2View::kTopView << " " << plane % 2 + 1 << "\n";
    }
  }
}

TEST_F(TestB2Dimension, WallMrdSouth) {

  std::ofstream of("wallmrd_south_channel_position.txt", std::ios::trunc);
  of << "# index X Y Z view color\n";
  int index = 1;

  for (unsigned plane = 0; plane < WM_NUM_SCINTI_PLANES; ++plane) {
    for (unsigned slot = 0; slot < WM_NUM_SCINTI_IN_ONE_PLANE; ++slot) {
      TVector3 pos;
      ASSERT_TRUE(test->GetPosWallMrd(B2Detector::kWallMrdSouth, plane, slot, pos));
      of << index++ << " " << pos.x() << " " << pos.y() << " "
         << pos.z() << " " << B2View::kTopView << " " << plane % 2 + 1 << "\n";
    }
  }
}

TEST_F(TestB2Dimension, WallMrdFailure) {
  TVector3 ignore;
  ASSERT_FALSE(B2Dimension::GetPosWallMrd(B2Detector::kWallMrdNorth, -1, 0, ignore));
  ASSERT_FALSE(B2Dimension::GetPosWallMrd(B2Detector::kWallMrdSouth, -1, 0, ignore));
  ASSERT_FALSE(B2Dimension::GetPosWallMrd(B2Detector::kWallMrdNorth, WM_NUM_SCINTI_PLANES, 0, ignore));
  ASSERT_FALSE(B2Dimension::GetPosWallMrd(B2Detector::kWallMrdSouth, WM_NUM_SCINTI_PLANES, 0, ignore));
  ASSERT_FALSE(B2Dimension::GetPosWallMrd(B2Detector::kWallMrdNorth, 0, WM_NUM_SCINTI_IN_ONE_PLANE, ignore));
  ASSERT_FALSE(B2Dimension::GetPosWallMrd(B2Detector::kWallMrdSouth, 0, WM_NUM_SCINTI_IN_ONE_PLANE, ignore));
}

TEST_F(TestB2Dimension, BabyMind) {

  std::ofstream of("baby_mind_channel_position.txt", std::ios::trunc);
  of << "# index X Y Z view color\n";
  int index = 1;

  for (unsigned plane = 0; plane < BM_NUM_TRACKING_PLANES; ++plane) {
    for (unsigned channel = 0; channel < BM_NUM_HORIZ_SCINTI_ONE_PLANE; ++channel) {
      TVector3 pos;
      ASSERT_TRUE(test->GetPosBm(B2View::kSideView, plane, channel, pos));
      of << index++ << " " << pos.x() << " " << pos.y() << " "
         << pos.z() << " " << B2View::kSideView << " " << plane % 2 + 1 << "\n";
    }
    for (unsigned slot = 0; slot < BM_NUM_VERTICAL_SCINTI_ONE_PLANE; ++slot) {
      TVector3 pos;
      ASSERT_TRUE(test->GetPosBm(B2View::kTopView, plane, slot, pos));
      of << index++ << " " << pos.x() << " " << pos.y() << " "
         << pos.z() << " " << B2View::kTopView << " " << plane % 2 + 1 << "\n";
    }
  }
  for (unsigned plane = 0; plane < YASU_NUM_PLANES; ++plane) {
    for (unsigned channel = 0; channel < YASU_NUM_SLOTS_ONE_PLANE; ++channel) {
      TVector3 pos;
      ASSERT_TRUE(test->GetPosYasu(plane, channel, pos));
      of << index++ << " " << pos.x() << " " << pos.y() << " "
         << pos.z() << " " << B2View::kSideView << " " << 3 << "\n";
      ASSERT_TRUE(test->GetPosYasu(plane, channel, pos));
      of << index++ << " " << pos.x() << " " << pos.y() << " "
         << pos.z() << " " << B2Readout::kRightReadout << " " << 4 << "\n";
    }
  }
}

TEST_F(TestB2Dimension, BabyMindFailure) {
  TVector3 ignore;
  ASSERT_FALSE(test->GetPosBm(B2View::kTopView, -1, 0, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kSideView, -1, 0, ignore));
  ASSERT_FALSE(test->GetPosYasu(-1, 0, ignore));
  ASSERT_FALSE(test->GetPosYasu(-1, 0, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kTopView, BM_NUM_TRACKING_PLANES, 0, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kSideView, BM_NUM_TRACKING_PLANES, 0, ignore));
  ASSERT_FALSE(test->GetPosYasu(YASU_NUM_PLANES, 0, ignore));
  ASSERT_FALSE(test->GetPosYasu(YASU_NUM_PLANES, 0, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kTopView, 0, -1, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kSideView, 0, -1, ignore));
  ASSERT_FALSE(test->GetPosYasu(0, -1, ignore));
  ASSERT_FALSE(test->GetPosYasu(0, -1, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kTopView, 0, BM_NUM_VERTICAL_SCINTI_ONE_PLANE, ignore));
  ASSERT_FALSE(test->GetPosBm(B2View::kSideView, 0, BM_NUM_HORIZ_SCINTI_ONE_PLANE, ignore));
  ASSERT_FALSE(test->GetPosYasu(0, YASU_NUM_SLOTS_ONE_PLANE, ignore));
  ASSERT_FALSE(test->GetPosYasu(0, YASU_NUM_SLOTS_ONE_PLANE, ignore));
}

int main(int argc, char **argv) {
  std::cout << "Running main() from gtest_main.cc\n";
  ::testing::InitGoogleTest(&argc, argv);
  for (int i = 0; i < argc; i++) {
    std::cout << "Argument " << i << " : " << argv[i] << std::endl;
  }
  assert(argc == 2);
  GEOMETRY_DIRECTORY = argv[1];
  return RUN_ALL_TESTS();
}