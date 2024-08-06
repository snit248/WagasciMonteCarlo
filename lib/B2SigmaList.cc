//
// Created by Giorgio Pintaudi on 2021/11/15.
//

#include <sstream>
#include <vector>
#include <B2Sigma.hh>
#include <B2SigmaList.hh>


#define any boost::any_cast

B2SigmaConstIterator B2SigmaList::begin() const {
  return sigmas_.begin();
}

B2SigmaConstIterator B2SigmaList::end() const {
  return sigmas_.end();
}

B2SigmaList::B2SigmaList(const std::vector<int> &sigmas) {
  for (const auto &sigma: sigmas) {
    if (sigma > MAX_SIGMA_VARIATION || sigma < MIN_SIGMA_VARIATION) {
      std::stringstream ss;
      ss << "B2Sigma " << sigma << " is out of range [" << MIN_SIGMA_VARIATION << ", "
         << MAX_SIGMA_VARIATION << "]";
      throw std::out_of_range(ss.str());
    }
    sigmas_.insert(static_cast<B2Sigma>(sigma));
  }
}

std::size_t B2SigmaList::size() const {
  return sigmas_.size();
}

B2Sigma B2SigmaList::GetLeftMostSigma() const {
  return *std::min_element(sigmas_.begin(), sigmas_.end());
}


B2Sigma B2SigmaList::GetRightMostSigma() const {
  return *std::max_element(sigmas_.begin(), sigmas_.end());
}

const char *B2SigmaList::GetSigmaListLabel() {
  return "B2SigmaList";
}

void B2SigmaList::InsertSigma(B2Sigma sigma) {
  sigmas_.insert(sigma);
}

void B2SigmaList::InsertSigma(int sigma) {
  if (sigma > MAX_SIGMA_VARIATION || sigma < MIN_SIGMA_VARIATION) {
    std::stringstream ss;
    ss << "B2Sigma " << sigma << " is out of range [" << MIN_SIGMA_VARIATION << ", "
       << MAX_SIGMA_VARIATION << "]";
    throw std::out_of_range(ss.str());
  }
  InsertSigma(static_cast<B2Sigma>(sigma));
}

bool B2SigmaList::empty() const {
  return sigmas_.empty();
}

ClassImp(B2SigmaList)