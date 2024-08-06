//
// Created by Giorgio Pintaudi on 2021/02/25.
//

#include <TCanvas.h>
#include <TH1D.h>
#include <TPDGCode.h>
#include <TF1.h>
#include <boost/make_unique.hpp>

#include "gtest/gtest.h"

#include "B2Response.hh"
#include "B2Dimension.hh"

fs::path GEOMETRY_DIR;
std::unique_ptr<B2Dimension> B2_DIMENSION;
std::unique_ptr<B2Response> B2_RESPONSE;

struct B2ResponseTest : public testing::Test {

  void SetUp() override {
    B2_DIMENSION = boost::make_unique<B2Dimension>(GEOMETRY_DIR);
    B2_RESPONSE = boost::make_unique<B2Response>(*B2_DIMENSION);
  }

};


Double_t ApplyLightCollectionProtonModule(Double_t *edep, Double_t *) {
  B2_RESPONSE->SwitchDetector(B2Detector::kProtonModule);
//  B2_RESPONSE->ApplyLightCollection(edep, B2View::kTopView, 0, 0, B2Readout::kTopReadout, 0);
}

TEST_F(B2ResponseTest, ApplyLightCollectionProtonModule) {



  TCanvas canvas("scinti_response", "Scintillator response", 1280, 720);
  TF1 tf1("ScintiResponse", ApplyLightCollectionProtonModule, 0, 100 * CLHEP::MeV);
  tf1.Draw();
  canvas.Print("/home/neo/Desktop/scinti_response.png");
}


int main(int argc, char **argv) {
  std::cout << "Running main() from gtest_main.cc\n";
  ::testing::InitGoogleTest(&argc, argv);
  for (int i = 0; i < argc; i++) {
    std::cout << "Argument " << i << " : " << argv[i] << std::endl;
  }
  assert(argc == 2);
  GEOMETRY_DIR = argv[1];
  return RUN_ALL_TESTS();
}