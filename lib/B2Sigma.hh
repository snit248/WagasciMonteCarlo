//
// Created by Giorgio Pintaudi on 2022/01/16.
//

#ifndef WAGASCIREWEIGHT_B2SIGMA_HPP
#define WAGASCIREWEIGHT_B2SIGMA_HPP

#include <string>
#include <TROOT.h>


// Supported sigma variations
enum B2Sigma {
  kNominal = 0,
  kPlusOneSigma = 1,
  kPlusTwoSigmas = 2,
  kPlusThreeSigmas = 3,
  kPlusFourSigmas = 4,
  kPlusFiveSigmas = 5,
  kMinusOneSigma = -1,
  kMinusTwoSigmas = -2,
  kMinusThreeSigmas = -3,
  kMinusFourSigmas = -4,
  kMinusFiveSigmas = -5,
};

// maximum sigma variation (on the right)
extern const int MAX_SIGMA_VARIATION;

// maximum sigma variation (on the left)
extern const int MIN_SIGMA_VARIATION;

// Convert a sigma variation to an arbitrary positive index. Used for arrays where one index represents a sigma.
int SigmaToInt(B2Sigma sigma);

// Convert a sigma to a human-readable string
std::string SigmaToString(B2Sigma sigma);


#endif //WAGASCIREWEIGHT_B2SIGMA_HPP
