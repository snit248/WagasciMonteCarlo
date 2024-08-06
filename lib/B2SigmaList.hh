//
// Created by Giorgio Pintaudi on 2021/11/15.
//

#ifndef WAGASCIREWEIGHT_B2SIGMALIST_HPP
#define WAGASCIREWEIGHT_B2SIGMALIST_HPP

// system includes
#include <set>
#include <vector>

// ROOT includes
#include <TObject.h>

// B2 includes
#include <B2Sigma.hh>


typedef std::set<B2Sigma> B2SigmaContainer;
typedef B2SigmaContainer::const_iterator B2SigmaConstIterator;

// A list of sigma variations to be applied to each dial. Each sigma can be specified with an integer or using the
// B2Sigma enum. The name list does not imply that the std::list container is used internally.
//
// For example if this list contains the values +1 and -1, every dial is going to be varied to (nominal +/- sigma)
// and the corresponding weight is calculated.
class B2SigmaList : public TObject {

private:

  // container of sigma variation
  B2SigmaContainer sigmas_;

public:

  B2SigmaList() = default;

  /**
   * @param sigmas list of sigma variations as integer. Only
   */
  explicit B2SigmaList(const std::vector<int> &sigmas);

  /**
   * iterator to the first dial. Dials are not guaranteed to be in any particular order.
   */
  B2SigmaConstIterator begin() const;

  /**
   * iterator beyond the last dial. Dials are not guaranteed to be in any particular order.
   */
  B2SigmaConstIterator end() const;

  /**
   * @return size of the container
   */
  std::size_t size() const;

  /**
   * @return true if container is empty
   */
  bool empty() const;

  /**
   * @param sigma sigma to insert in the container
   */
  void InsertSigma(B2Sigma sigma);

  /**
   * The value of sigma is checked for out of boundary condition before insertion
   * @param sigma sigma to insert in the container
   */
  void InsertSigma(int sigma);

  /**
   * @return most left sigma
   */
  B2Sigma GetLeftMostSigma() const;

  /**
   * @return most right sigma
   */
  B2Sigma GetRightMostSigma() const;

  /**
   * @return label by which the sigma list is labeled in the ROOT file
   */
  static const char *GetSigmaListLabel();

ClassDef(B2SigmaList, 1)
};

#endif //WAGASCIREWEIGHT_B2SIGMALIST_HPP
