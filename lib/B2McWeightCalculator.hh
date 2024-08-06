//
// Created by Giorgio Pintaudi on 2022/02/12.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2MCWEIGHTCALCULATOR_HH
#define WAGASCIBABYMINDMONTECARLO_B2MCWEIGHTCALCULATOR_HH

#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <RtypesCore.h>
#include "B2Enum.hh"

class B2McWeightCalculator {

private:

  const Double_t avogadro_constant_ = 6.022 * std::pow(10, 23);
  const Double_t xsec_factor_ = std::pow(10, -38);
  std::unordered_map<B2Detector, Double_t, EnumClassHash> density_g_over_cm3_;
  std::unordered_map<B2Detector, Double_t, EnumClassHash> thickness_;

public:

  B2McWeightCalculator();

  Double_t CalculateWeight(B2Detector detector, double total_xsec, double normalization) const;

};


#endif //WAGASCIBABYMINDMONTECARLO_B2MCWEIGHTCALCULATOR_HH
