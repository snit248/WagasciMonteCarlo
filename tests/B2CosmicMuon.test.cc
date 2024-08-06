//
// Created by Giorgio Pintaudi on 8/21/20.
//

#include <vector>

#include <TCanvas.h>
#include <TH1D.h>
#include <TH3D.h>

#include "gtest/gtest.h"

#include "G4SystemOfUnits.hh"


#include "B2CosmicMuon.hh"

TEST(B2CosmicMuon, Histograms) {

  TH1D histo1("energy_histo", "Energy (GeV)", 200, 0, 25);
  histo1.GetXaxis()->SetTitle("Energy (GeV)");
  histo1.GetYaxis()->SetTitle("Events");

  TH1D histo2("momentum_histo", "Momentum (GeV/c)", 200, 0, 25);
  histo2.GetXaxis()->SetTitle("Momentum (GeV/c)");
  histo2.GetYaxis()->SetTitle("Events");

  TH3D histo3("position_histo", "Vertex position (m)", 50, -15, 15, 50, -15, 15, 10, 3, 4);
  histo3.GetXaxis()->SetTitle("Position Z (m)");
  histo3.GetYaxis()->SetTitle("Position X (m)");
  histo3.GetZaxis()->SetTitle("Position Y (m)");
  histo3.GetXaxis()->SetTitleOffset(2);
  histo3.GetYaxis()->SetTitleOffset(2);

  TH3D histo4("direction_histo", "Direction", 50, -1, 1, 50, -1, 1, 50, -1, 1);
  histo4.GetXaxis()->SetTitle("Z direction");
  histo4.GetYaxis()->SetTitle("X direction");
  histo4.GetZaxis()->SetTitle("Y direction");
  histo4.GetXaxis()->SetLabelSize(0);
  histo4.GetYaxis()->SetLabelSize(0);
  histo4.GetZaxis()->SetLabelSize(0);


  for (int i = 0; i < 200000; ++i) {
    B2CosmicMuon test;
    histo1.Fill(test.GetEnergy() / GeV);
    histo2.Fill(test.GetAbsMomentum() / GeV);
    G4ThreeVector position(test.GetPosition() * mm / m);
    histo3.Fill(position.getZ(), position.getX(), position.getY());
    histo4.Fill(test.GetDirection().getZ(), test.GetDirection().getX(), test.GetDirection().getY());
  }

  histo1.SetMinimum(0);
  histo2.SetMinimum(0);

  TCanvas canvas1("energy_canvas", "energy_canvas", 1280, 720);
  histo1.Draw();
  canvas1.Print("CosmicMuonEnergy.png");

  TCanvas canvas2("momentum_canvas", "momentum_canvas", 1280, 720);
  histo2.Draw();
  canvas2.Print("CosmicMuonMomentum.png");

  TCanvas canvas3("position_canvas", "position_canvas", 720, 720);
  histo3.Draw("BOX2");
  canvas3.Print("CosmicMuonPosition.png");

  TCanvas canvas4("direction_canvas", "direction_canvas", 720, 720);
  histo4.Draw("BOX2");
  canvas4.SetTheta(10);
  canvas4.SetPhi(30);
  canvas4.Print("CosmicMuonDirection.png");
}