//
// Created by Giorgio Pintaudi on 8/21/20.
//

#include <TVector3.h>
#include <TCanvas.h>
#include <TH1D.h>

#include "gtest/gtest.h"

#include "B2RandomVertexZ.hh"

::testing::AssertionResult IsBetweenInclusive(double val, double a, double b) {
  if ((val >= a) && (val <= b))
    return ::testing::AssertionSuccess();
  else
    return ::testing::AssertionFailure()
        << val << " is outside the range " << a << " to " << b;
}

struct B2RandomVertexZTest : public testing::Test {

public:
  // Center of detector (Proton module SciBar only region)
  double vertex_x1 = 0;
  double vertex_y1 = 0;
  TVector3 vertex1;
  // Proton module SciBar-INGRID mixed region
  double vertex_x2 = 30 * cm;
  double vertex_y2 = 0;
  TVector3 vertex2;
  // Proton module INGRID only region
  double vertex_x3 = 30 * cm;
  double vertex_y3 = 30 * cm;
  TVector3 vertex3;
  // vertex too far away
  double vertex_x4 = 10 * m;
  double vertex_y4 = 10 * m;
  TVector3 vertex4;

  const int num_iterations = 10000000;

  void SetUp() override {
    vertex1.SetXYZ(vertex_x1, vertex_y1, 0);
    vertex2.SetXYZ(vertex_x2, vertex_y2, 0);
    vertex3.SetXYZ(vertex_x3, vertex_y3, 0);
    vertex4.SetXYZ(vertex_x4, vertex_y4, 0);
  }
};

TEST_F(B2RandomVertexZTest, ProtonModuleSciBarOnly) {

  TH1D histo1("ProtonModuleSciBarOnlyHisto",
              "Proton Module - SciBar only region - vertex distribution along Z",
              1000, PM_FRONT_VETO_START_Z, PM_FRONT_VETO_START_Z + PM_TOTAL_FRAME_DEPTH);
  histo1.GetXaxis()->SetTitle("Depth (mm)");
  histo1.GetYaxis()->SetTitle("Interaction probability weighted by thickness (arbitrary units)");

  TH1I histo2("ProtonModuleSciBarOnlyProbHisto", "Interaction frequency", 2, 0, 2);
  histo2.GetXaxis()->SetBinLabel(1, "Has NOT interacted");
  histo2.GetXaxis()->SetBinLabel(2, "Has interacted");
  histo2.GetYaxis()->SetTitle("Interaction frequency (arbitrary units)");

  for (int i = 0; i < num_iterations; ++i) {
    bool have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kProtonModule, vertex1);
    if (have_interaction) {
      histo1.Fill(vertex1.Z());
      ASSERT_TRUE(IsBetweenInclusive(vertex3.Z(), PM_FRONT_VETO_START_Z, PM_FRONT_VETO_START_Z + PM_TOTAL_FRAME_DEPTH));
    }
    histo2.Fill(static_cast<int>(have_interaction));
  }
  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("ProtonModuleSciBarOnlyCanvas", "Vertex distribution along Z", 1280, 720);
  histo1.Draw();
  canvas1.Print("ProtonModuleSciBarOnly.png");

  TCanvas canvas2("ProtonModuleSciBarOnlyProbCanvas", "Interaction frequency", 1280, 720);
  histo2.Draw();
  canvas2.Print("ProtonModuleSciBarOnlyProb.png");
}

TEST_F(B2RandomVertexZTest, ProtonModuleMixed) {

  TH1D histo1("ProtonModuleMixedHisto",
              "Proton Module - INGRID/SciBar mixed region - vertex distribution along Z",
              1000, PM_FRONT_VETO_START_Z, PM_FRONT_VETO_START_Z + PM_TOTAL_FRAME_DEPTH);
  histo1.GetXaxis()->SetTitle("Depth (mm)");
  histo1.GetYaxis()->SetTitle("Interaction probability weighted by thickness (arbitrary units)");

  TH1I histo2("ProtonModuleMixedProbHisto", "Interaction frequency", 2, 0, 2);
  histo2.GetXaxis()->SetBinLabel(1, "Has NOT interacted");
  histo2.GetXaxis()->SetBinLabel(2, "Has interacted");
  histo2.GetYaxis()->SetTitle("Interaction frequency (arbitrary units)");

  for (int i = 0; i < num_iterations; ++i) {
    bool have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kProtonModule, vertex2);
    if (have_interaction) {
      histo1.Fill(vertex2.Z());
      ASSERT_TRUE(IsBetweenInclusive(vertex3.Z(), PM_FRONT_VETO_START_Z, PM_FRONT_VETO_START_Z + PM_TOTAL_FRAME_DEPTH));
    }
    histo2.Fill(static_cast<int>(have_interaction));
  }
  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("ProtonModuleMixedCanvas", "Vertex distribution along Z", 1280, 720);
  histo1.Draw();
  canvas1.Print("ProtonModuleMixed.png");

  TCanvas canvas2("ProtonModuleMixedProbCanvas", "Interaction frequency", 1280, 720);
  histo2.Draw();
  canvas2.Print("ProtonModuleMixedProb.png");
}

TEST_F(B2RandomVertexZTest, ProtonModuleIngridOnly) {

  TH1D histo1("ProtonModuleIngridOnlyHisto",
              "Proton Module - INGRID only region - Vertex distribution along Z",
              1000, PM_FRONT_VETO_START_Z, PM_FRONT_VETO_START_Z + PM_TOTAL_FRAME_DEPTH);
  histo1.GetXaxis()->SetTitle("Depth (mm)");
  histo1.GetYaxis()->SetTitle("Interaction probability weighted by thickness (arbitrary units)");

  TH1I histo2("ProtonModuleIngridOnlyProbHisto", "Interaction frequency", 2, 0, 2);
  histo2.GetXaxis()->SetBinLabel(1, "Has NOT interacted");
  histo2.GetXaxis()->SetBinLabel(2, "Has interacted");
  histo2.GetYaxis()->SetTitle("Interaction frequency (arbitrary units)");

  for (int i = 0; i < num_iterations; ++i) {
    bool have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kProtonModule, vertex3);
    if (have_interaction) {
      histo1.Fill(vertex3.Z());
      ASSERT_TRUE(IsBetweenInclusive(vertex3.Z(), PM_FRONT_VETO_START_Z, PM_FRONT_VETO_START_Z + PM_TOTAL_FRAME_DEPTH));
    }
    histo2.Fill(static_cast<int>(have_interaction));
  }
  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("ProtonModuleIngridOnlyCanvas", "Vertex distribution along Z", 1280, 720);
  histo1.Draw();
  canvas1.Print("ProtonModuleIngridOnly.png");

  TCanvas canvas2("ProtonModuleIngridOnlyProbCanvas", "Interaction frequency", 1280, 720);
  histo2.Draw();
  canvas2.Print("ProtonModuleIngridOnlyProb.png");
}

TEST_F(B2RandomVertexZTest, ProtonModuleFailure) {
  for (int i = 0; i < num_iterations; ++i) {
    ASSERT_FALSE(B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kProtonModule, vertex4));
  }
}

TEST_F(B2RandomVertexZTest, Wagasci) {

  TH1D histo1("WagasciHisto", "WAGASCI - Vertex distribution along Z",
              100, WGS_FRAME_START_Z, WGS_FRAME_START_Z + WGS_WATER_BOX_DEPTH);
  histo1.GetXaxis()->SetTitle("Depth (mm)");
  histo1.GetYaxis()->SetTitle("Interaction probability (arbitrary units)");

  TH1I histo2("WagasciProbHisto", "Interaction frequency", 2, 0, 2);
  histo2.GetXaxis()->SetBinLabel(1, "Has NOT interacted");
  histo2.GetXaxis()->SetBinLabel(2, "Has interacted");
  histo2.GetYaxis()->SetTitle("Interaction frequency (arbitrary units)");

  for (int i = 0; i < num_iterations; ++i) {
    bool have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kWagasciUpstream, vertex1);
    if (have_interaction) {
      histo1.Fill(vertex1.Z());
      ASSERT_TRUE(IsBetweenInclusive(vertex1.Z(), WGS_FRAME_START_Z, WGS_FRAME_START_Z + WGS_WATER_BOX_DEPTH));
    }
    histo2.Fill(static_cast<int>(have_interaction));
  }
  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("WagasciCanvas", "WagasciCanvas", 1280, 720);
  histo1.Draw();
  canvas1.Print("Wagasci.png");

  TCanvas canvas2("WagasciProbCanvas", "WagasciProbCanvas", 1280, 720);
  histo2.Draw();
  canvas2.Print("WagasciProb.png");
}

TEST_F(B2RandomVertexZTest, WagasciFailure) {
  for (int i = 0; i < num_iterations; ++i) {
    ASSERT_FALSE(B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kWagasciUpstream, vertex4));
  }
}

TEST_F(B2RandomVertexZTest, WallMrd) {

  TH1D histo1("WallMrdHisto", "WallMrd - Vertex distribution along Z",
              100, WM_INNER_FRAME_START_Z, WM_INNER_FRAME_START_Z + WM_INNER_FRAME_DEPTH);
  histo1.GetXaxis()->SetTitle("Depth (mm)");
  histo1.GetYaxis()->SetTitle("Interaction probability (arbitrary units)");

  TH1I histo2("WallMrdProbHisto", "Interaction frequency", 2, 0, 2);
  histo2.GetXaxis()->SetBinLabel(1, "Has NOT interacted");
  histo2.GetXaxis()->SetBinLabel(2, "Has interacted");
  histo2.GetYaxis()->SetTitle("Interaction frequency (arbitrary units)");

  for (int i = 0; i < num_iterations; ++i) {
    bool have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kWallMrdNorth, vertex1);
    if (have_interaction) {
      histo1.Fill(vertex1.Z());
      ASSERT_TRUE(IsBetweenInclusive(vertex1.Z(), WM_INNER_FRAME_START_Z,
                                     WM_INNER_FRAME_START_Z + WM_INNER_FRAME_DEPTH));
    }
    histo2.Fill(static_cast<int>(have_interaction));
  }
  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("WallMrdCanvas", "WallMrdCanvas", 1280, 720);
  histo1.Draw();
  canvas1.Print("WallMrd.png");

  TCanvas canvas2("WallMrdProbCanvas", "WallMrdProbCanvas", 1280, 720);
  histo2.Draw();
  canvas2.Print("WallMrdProb.png");
}

TEST_F(B2RandomVertexZTest, WallMrdFailure) {
  for (int i = 0; i < num_iterations; ++i) {
    ASSERT_FALSE(B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kWallMrdNorth, vertex4));
  }
}

TEST_F(B2RandomVertexZTest, BabyMind) {

  TH1D histo1("BabyMindHisto", "BabyMind - Vertex distribution along Z",
              1000, BM_FRAME_START_Z, BM_FRAME_START_Z + BM_FRAME_DEPTH);
  histo1.GetXaxis()->SetTitle("Depth (mm)");
  histo1.GetYaxis()->SetTitle("Interaction probability (arbitrary units)");

  TH1I histo2("BabyMindProbHisto", "Interaction frequency", 2, 0, 2);
  histo2.GetXaxis()->SetBinLabel(1, "Has NOT interacted");
  histo2.GetXaxis()->SetBinLabel(2, "Has interacted");
  histo2.GetYaxis()->SetTitle("Interaction frequency (arbitrary units)");

  for (int i = 0; i < num_iterations; ++i) {
    bool have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kBabyMind, vertex1);
    if (have_interaction) {
      histo1.Fill(vertex1.Z());
      ASSERT_TRUE(IsBetweenInclusive(vertex1.Z(), BM_FRAME_START_Z, BM_FRAME_START_Z + BM_FRAME_DEPTH));
    }
    histo2.Fill(static_cast<int>(have_interaction));
  }
  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("BabyMindCanvas", "BabyMindCanvas", 1280, 720);
  histo1.Draw();
  canvas1.Print("BabyMind.png");

  TCanvas canvas2("BabyMindProbCanvas", "BabyMindProbCanvas", 1280, 720);
  histo2.Draw();
  canvas2.Print("BabyMindProb.png");
}

TEST_F(B2RandomVertexZTest, BabyMindFailure) {
  for (int i = 0; i < num_iterations; ++i) {
    ASSERT_FALSE(B2RandomVertexZ::GenerateRandomVertexZ(B2Detector::kBabyMind, vertex4));
  }
}