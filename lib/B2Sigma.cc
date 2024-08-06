//
// Created by Giorgio Pintaudi on 2022/01/16.
//

#include <B2Sigma.hh>


const int MAX_SIGMA_VARIATION = B2Sigma::kPlusFiveSigmas;

const int MIN_SIGMA_VARIATION = B2Sigma::kMinusFiveSigmas;

int SigmaToInt(B2Sigma sigma) {
  if (sigma >= 0) return sigma;
  else return -sigma + MAX_SIGMA_VARIATION;
}

std::string SigmaToString(B2Sigma sigma) {
  switch (sigma) {
    case kNominal:
      return "Nominal";
    case kPlusOneSigma:
      return "PlusOneSigma";
    case kPlusTwoSigmas:
      return "PlusTwoSigmas";
    case kPlusThreeSigmas:
      return "PlusThreeSigmas";
    case kPlusFourSigmas:
      return "PlusFourSigmas";
    case kPlusFiveSigmas:
      return "PlusFiveSigmas";
    case kMinusOneSigma:
      return "MinusOneSigma";
    case kMinusTwoSigmas:
      return "MinusTwoSigmas";
    case kMinusThreeSigmas:
      return "MinusThreeSigmas";
    case kMinusFourSigmas:
      return "MinusFourSigmas";
    case kMinusFiveSigmas:
      return "MinusFiveSigmas";
    default:
      throw std::out_of_range("Sigma not recognized");
  }
}