//
// Created by Giorgio Pintaudi on 2022/02/12.
//

#include "B2McWeightCalculator.hh"

B2McWeightCalculator::B2McWeightCalculator() {
  density_g_over_cm3_[B2Detector::kUnknownDetector] = 0;
  density_g_over_cm3_[B2Detector::kWagasciDownstream] = WAGASCI_WATER_DENSITY;
  density_g_over_cm3_[B2Detector::kWagasciUpstream] = WAGASCI_WATER_DENSITY;
  density_g_over_cm3_[B2Detector::kProtonModule] = SCINTILLATOR_DENSITY;
  density_g_over_cm3_[B2Detector::kWallMrdNorth] = IRON_DENSITY;
  density_g_over_cm3_[B2Detector::kWallMrdSouth] = IRON_DENSITY;
  density_g_over_cm3_[B2Detector::kBabyMind] = IRON_DENSITY;
  density_g_over_cm3_[B2Detector::kWall] = CONCRETE_DENSITY;
  density_g_over_cm3_[B2Detector::kYasuTracker] = SCINTILLATOR_DENSITY;
  density_g_over_cm3_[B2Detector::kNinja] = NINJA_WATER_DENSITY;

  thickness_[B2Detector::kUnknownDetector] = 0;
  thickness_[B2Detector::kWagasciDownstream] = WGS_WATER_BOX_DEPTH;
  thickness_[B2Detector::kWagasciUpstream] = WGS_WATER_BOX_DEPTH;
  thickness_[B2Detector::kProtonModule] = PM_SCIBAR_REGION_THICKNESS + PM_VETO_REGION_THICKNESS;
  thickness_[B2Detector::kWallMrdNorth] =
      WM_INNER_IRON_PLATE_THICK * (WM_NUM_INNER_IRON_PLANES + WM_NUM_OUTER_IRON_PLANES);
  thickness_[B2Detector::kWallMrdSouth] =
      WM_INNER_IRON_PLATE_THICK * (WM_NUM_INNER_IRON_PLANES + WM_NUM_OUTER_IRON_PLANES);
  thickness_[B2Detector::kBabyMind] = BM_IRON_PLATE_DEPTH * BM_NUM_IRON_PLANES;
  thickness_[B2Detector::kWall] = WALL_DEPTH;
  thickness_[B2Detector::kYasuTracker] = YASU_NUM_PLANES * WM_SCINTI_THICK;
  thickness_[B2Detector::kNinja] = NINJA_ECC_WATER_LAYERS * NINJA_WATER_LAYER_THICK;

  std::for_each(thickness_.begin(), thickness_.end(), [](std::pair<const B2Detector, Double_t> &thickness) {
    thickness.second *= CLHEP::millimeter / CLHEP::centimeter;
  });
}

Double_t B2McWeightCalculator::CalculateWeight(B2Detector detector, double total_xsec, double normalization) const {
  return avogadro_constant_ * xsec_factor_ * total_xsec * normalization *
         thickness_.at(detector) * density_g_over_cm3_.at(detector);
}
