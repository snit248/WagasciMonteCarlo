//
// Created by Giorgio Pintaudi on 8/28/20.
//

#include "gtest/gtest.h"
#include <array>
#include <TH2D.h>
#include <TCanvas.h>
#include <TGraph2D.h>
#include "B2HitSummary.hh"
#include "B2Enum.hh"

struct B2HitsSummaryDoubleReadoutTest : public testing::Test {

public:
  B2HitSummary hit;
  Double_t peu_top = 1;
  Double_t peu_side = 2;
  B2Readout readout_top = B2Readout::kTopReadout;
  B2Readout readout_side = B2Readout::kBottomReadout;

  void SetUp() override {
    hit.SetDetector(B2Detector::kWallMrdSouth);
    hit.SetScintillatorType(B2ScintillatorType::kVertical);
    hit.SetScintillatorPosition(B2Vector3(1, 2, 3), B2Vector3(0.1, 0.2, 0.3));
    hit.SetHighGainPeu(readout_top, peu_top);
    hit.SetHighGainPeu(readout_side, peu_side);
  }
};

TEST_F(B2HitsSummaryDoubleReadoutTest, GetNumberReadouts) {
  ASSERT_EQ(hit.GetNumberReadouts(), 2);
}

TEST_F(B2HitsSummaryDoubleReadoutTest, GetReadout1) {
  ASSERT_EQ(hit.GetReadout1(), readout_side);
}

TEST_F(B2HitsSummaryDoubleReadoutTest, GetReadout2) {
  ASSERT_EQ(hit.GetReadout2(), readout_top);
}

TEST_F(B2HitsSummaryDoubleReadoutTest, GetAveragePeu) {
  ASSERT_EQ(hit.GetAveragePeu().GetValue(), 0.5 * (peu_top + peu_side));
}

TEST_F(B2HitsSummaryDoubleReadoutTest, Dump) {
  std::cout << hit << "\n";
}

TEST_F(B2HitsSummaryDoubleReadoutTest, MergeHits) {
  B2HitSummary hit1;
  B2HitSummary hit2;

  hit1.SetDetector(B2Detector::kWallMrdNorth);
  hit1.SetChannel(hit1.GetReadout1(), 1);
  hit1.SetSlot(hit1.GetReadout1(), 1);
  hit1.SetChip(hit1.GetReadout1(), 1);
  hit1.SetTimeNs(hit1.GetReadout1(), 1);
  hit1.SetHighGainPeu(hit1.GetReadout1(), 1);
  hit1.SetView(B2View::kTopView);
  hit1.SetScintillatorPosition(B2Position(1, 1, 1, 1, 1, 1));

  hit2.SetDetector(B2Detector::kWallMrdNorth);
  hit2.SetChannel(hit2.GetReadout2(), 2);
  hit2.SetSlot(hit2.GetReadout2(), 2);
  hit2.SetChip(hit2.GetReadout2(), 2);
  hit2.SetTimeNs(hit2.GetReadout2(), 2);
  hit2.SetHighGainPeu(hit2.GetReadout2(), 2);
  hit2.SetView(B2View::kTopView);
  hit2.SetScintillatorPosition(B2Position(1, 1, 1, 1, 1, 1));

  hit1.MergeHits(hit2, hit2.GetReadout2());

  ASSERT_EQ(hit1.GetChannel().GetValue(hit1.GetReadout1()), 1);
  ASSERT_EQ(hit1.GetSlot().GetValue(hit1.GetReadout1()), 1);
  ASSERT_EQ(hit1.GetChip().GetValue(hit1.GetReadout1()), 1);
  ASSERT_EQ(hit1.GetTimeNs().GetValue(hit1.GetReadout1()), 1);
  ASSERT_EQ(hit1.GetHighGainPeu().GetValue(hit1.GetReadout1()), 1);
  ASSERT_EQ(hit1.GetView(), B2View::kTopView);

  ASSERT_EQ(hit1.GetChannel().GetValue(hit1.GetReadout2()), 2);
  ASSERT_EQ(hit1.GetSlot().GetValue(hit1.GetReadout2()), 2);
  ASSERT_EQ(hit1.GetChip().GetValue(hit1.GetReadout2()), 2);
  ASSERT_EQ(hit1.GetTimeNs().GetValue(hit1.GetReadout2()), 2);
  ASSERT_EQ(hit1.GetHighGainPeu().GetValue(hit1.GetReadout2()), 2);
  ASSERT_EQ(hit1.GetView(), B2View::kTopView);

  TVector3 value(hit1.GetScintillatorPosition().GetValue());
  ASSERT_EQ(B2Vector3(value.x(), value.y(), value.z()), B2Vector3(1, 1, 1));
  TVector3 error(hit1.GetScintillatorPosition().GetError());
  ASSERT_EQ(B2Vector3(error.x(), error.y(), error.z()), B2Vector3(1, 1, 1));
}


struct B2HitsSummarySingleReadoutTest : public testing::Test {

public:
  B2HitSummary hit_top, hit_side;
  Double_t peu_top = 1;
  Double_t peu_side = 2;
  B2Readout readout_top = B2Readout::kTopReadout;
  B2Readout readout_side = B2Readout::kSideReadout;

  void SetUp() override {
    hit_top.SetDetector(B2Detector::kWagasciUpstream);
    hit_top.SetScintillatorType(B2ScintillatorType::kVertical);
    hit_side.SetDetector(B2Detector::kWagasciUpstream);
    hit_side.SetScintillatorType(B2ScintillatorType::kHorizontal);
    hit_top.SetHighGainPeu(readout_top, peu_top);
    hit_side.SetHighGainPeu(readout_side, peu_side);
  }
};

TEST_F(B2HitsSummarySingleReadoutTest, GetNumberReadouts) {
  ASSERT_EQ(hit_top.GetNumberReadouts(), 1);
  ASSERT_EQ(hit_side.GetNumberReadouts(), 1);
}

TEST_F(B2HitsSummarySingleReadoutTest, GetSingleReadout) {
  ASSERT_EQ(hit_top.GetSingleReadout(), readout_top);
  ASSERT_EQ(hit_side.GetSingleReadout(), readout_side);
}

TEST_F(B2HitsSummarySingleReadoutTest, GetReadout1) {
  ASSERT_EQ(hit_top.GetReadout1(), readout_top);
  ASSERT_EQ(hit_side.GetReadout1(), readout_side);
}

TEST_F(B2HitsSummarySingleReadoutTest, GetReadout2) {
  ASSERT_EQ(hit_top.GetReadout2(), readout_top);
  ASSERT_EQ(hit_side.GetReadout2(), readout_side);
}

TEST_F(B2HitsSummarySingleReadoutTest, GetAveragePeu) {
  ASSERT_EQ(hit_top.GetAveragePeu().GetValue(), peu_top);
  ASSERT_EQ(hit_side.GetAveragePeu().GetValue(), peu_side);
}


/*

TEST(B2HitsSummaryTransmissionWallMrd, WallMrdHitToFiber) {
  std::array<B2Detector, 2> detectors = {B2Detector::kWallMrdNorth, B2Detector::kWallMrdSouth};
  for (const auto &detector: detectors) {
    TGraph2D hit_map;
    for (int slot = 0; slot < WM_NUM_SCINTI_IN_ONE_PLANE; ++slot) {
      TVector3 rel_pos;
      B2Dimension::GetPosWallMrd(detector, 0, slot, rel_pos);
      for (double posz = rel_pos.Z() - 0.5 * WM_SCINTI_LARGE; posz <= rel_pos.Z() + 0.5 * WM_SCINTI_LARGE;
           posz = posz + 2) {
        for (double posy = rel_pos.Y() - 0.5 * WM_SCINTI_LENGTH; posy <= rel_pos.Y() + 0.5 * WM_SCINTI_LENGTH;
             posy = posy + 2) {
          const double hit_fiber_distance = B2HitSummary::WallMrdHitToFiber(slot, posy, posz, detector);
          hit_map.SetPoint(hit_map.GetN(), posy, posz, hit_fiber_distance);
        }
      }
    }
    hit_map.GetXaxis()->SetTitle("Y axis [mm]");
    hit_map.GetXaxis()->SetTitleOffset(-2);
    hit_map.GetXaxis()->SetLabelOffset(0.035);
    hit_map.GetXaxis()->SetTickLength(-0.02);
    hit_map.GetYaxis()->SetTitle("Z axis [mm]");
    hit_map.GetYaxis()->SetTitleOffset(0);
    hit_map.GetYaxis()->SetLabelOffset(-0.1);
    hit_map.SetMarkerStyle(6);
    hit_map.SetMarkerSize(2);
    std::stringstream title;
    title << DETECTOR_NAMES.at(detector) << " - Hit fiber distance";
    TCanvas canvas("c1", "c1", 1000, 1200);
    canvas.SetTheta(270);
    canvas.SetPhi(-90);
    canvas.SetMargin(0.15, 0.15, 0.15, 0.1);
    hit_map.SetTitle(title.str().c_str());
    hit_map.Draw("PCOLZ");
    fs::path path("/home/neo/Desktop");
    path /= (title.str() + ".png");
    canvas.Print(path.c_str());
  }
}

TEST(B2HitsSummaryTransmissionWallMrd, WallMFiberTransLength) {
  std::array<B2Detector, 2> detectors = {B2Detector::kWallMrdNorth, B2Detector::kWallMrdSouth};
  std::array<B2Readout, 2> readouts = {B2Readout::kBottomReadout, B2Readout::kTopReadout};
  for (const auto &detector: detectors) {
    for (const auto &readout: readouts) {
      TGraph2D hit_map;
      for (int slot = 0; slot < WM_NUM_SCINTI_IN_ONE_PLANE; ++slot) {
        TVector3 rel_pos;
        B2Dimension::GetPosWallMrd(detector, 0, slot, rel_pos);
        for (double posz = rel_pos.Z() - 0.5 * WM_SCINTI_LARGE; posz <= rel_pos.Z() + 0.5 * WM_SCINTI_LARGE;
             posz = posz + 2) {
          for (double posy = rel_pos.Y() - 0.5 * WM_SCINTI_LENGTH; posy <= rel_pos.Y() + 0.5 * WM_SCINTI_LENGTH;
               posy = posy + 2) {
            const double distance = B2HitSummary::WallMrdFiberTransmissionDistance(slot, posy, posz, readout,
                                                                                   detector);
            hit_map.SetPoint(hit_map.GetN(), posy, posz, distance);
          }
        }
      }
      hit_map.GetXaxis()->SetTitle("Y axis [mm]");
      hit_map.GetXaxis()->SetTitleOffset(-2);
      hit_map.GetXaxis()->SetLabelOffset(0.035);
      hit_map.GetXaxis()->SetTickLength(-0.02);
      hit_map.GetYaxis()->SetTitle("Z axis [mm]");
      hit_map.GetYaxis()->SetTitleOffset(0);
      hit_map.GetYaxis()->SetLabelOffset(-0.1);
      hit_map.SetMarkerStyle(6);
      hit_map.SetMarkerSize(2);
      std::stringstream title;
      title << DETECTOR_NAMES.at(detector) << " - " << READOUT_NAMES.at(readout) << " - Fiber MPPC distance";
      TCanvas canvas("c1", "c1", 1000, 1200);
      canvas.SetTheta(270);
      canvas.SetPhi(-90);
      canvas.SetMargin(0.15, 0.15, 0.15, 0.1);
      hit_map.SetTitle(title.str().c_str());
      hit_map.Draw("PCOLZ");
      fs::path path("/home/neo/Desktop");
      path /= (title.str() + ".png");
      canvas.Print(path.c_str());
    }
  }
}

TEST(B2HitsSummaryTransmissionWallMrd, WallMFiberTransTime) {
  std::array<B2Detector, 2> detectors = {B2Detector::kWallMrdNorth, B2Detector::kWallMrdSouth};
  std::array<B2Readout, 2> readouts = {B2Readout::kBottomReadout, B2Readout::kTopReadout};
  for (const auto &detector: detectors) {
    for (const auto &readout: readouts) {
      TGraph2D hit_map;
      for (int slot = 0; slot < WM_NUM_SCINTI_IN_ONE_PLANE; ++slot) {
        TVector3 rel_pos;
        B2Dimension::GetPosWallMrd(detector, 0, slot, rel_pos);
        for (double posz = rel_pos.Z() - 0.5 * WM_SCINTI_LARGE; posz <= rel_pos.Z() + 0.5 * WM_SCINTI_LARGE;
             posz = posz + 2) {
          for (double posy = rel_pos.Y() - 0.5 * WM_SCINTI_LENGTH; posy <= rel_pos.Y() + 0.5 * WM_SCINTI_LENGTH;
               posy = posy + 2) {
            const double distance = B2HitSummary::WallMrdFiberTransmissionDistance(slot, posy, posz, readout,
                                                                                   detector);
            hit_map.SetPoint(hit_map.GetN(), posy, posz, distance / TRANS_SPEED_IN_FIBER_WMRD);
          }
        }
      }
      hit_map.GetXaxis()->SetTitle("Y axis [mm]");
      hit_map.GetXaxis()->SetTitleOffset(-2);
      hit_map.GetXaxis()->SetLabelOffset(0.035);
      hit_map.GetXaxis()->SetTickLength(-0.02);
      hit_map.GetYaxis()->SetTitle("Z axis [mm]");
      hit_map.GetYaxis()->SetTitleOffset(0);
      hit_map.GetYaxis()->SetLabelOffset(-0.1);
      hit_map.SetMarkerStyle(6);
      hit_map.SetMarkerSize(2);
      std::stringstream title;
      title << DETECTOR_NAMES.at(detector) << " - " << READOUT_NAMES.at(readout) << " - transition time";
      TCanvas canvas("c1", "c1", 1000, 1200);
      canvas.SetTheta(270);
      canvas.SetPhi(-90);
      canvas.SetMargin(0.15, 0.15, 0.15, 0.1);
      hit_map.SetTitle(title.str().c_str());
      hit_map.Draw("PCOLZ");
      fs::path path("/home/neo/Desktop");
      path /= (title.str() + ".png");
      canvas.Print(path.c_str());
    }
  }
}

*/