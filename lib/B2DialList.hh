//
// Created by Giorgio Pintaudi on 2021/11/15.
//

#ifndef WAGASCIREWEIGHT_B2DIALLIST_HPP
#define WAGASCIREWEIGHT_B2DIALLIST_HPP

// system includes
#include <unordered_map>
#include <utility>
#include <vector>
#include <ostream>

// ROOT includes
#include <TObject.h>
#include <TROOT.h>

// B2 includes
#include <B2Dial.hh>
#include <B2DialSigmaKey.hh>


namespace wgrw {

  class FileDialReader;

  class RootDialReader;

}

// Name of TDirectory containing dial info
extern const char *DIAL_TDIRECTORY_NAME;

// A list of dial objects. It can contain any list of dials, but it only contains the dials that should be varied
// from the nominal value and not all the possible dials. The name list does not imply that the std::list container
// is used internally.

class B2DialList : public TObject {

  friend wgrw::FileDialReader;
  friend wgrw::RootDialReader;

private:

  typedef std::vector<B2Dial> B2DialContainer;

  typedef B2DialContainer::const_iterator B2DialConstIterator;

  // dial container
  B2DialContainer dials_;

private:

  /**
   * @param dial dial to insert in the list
   */
  void InsertDial(const B2Dial &dial);

public:

  /**
   * iterator to the first dial. Dials are not guaranteed to be in any particular order.
   */
  B2DialConstIterator begin() const;

  /**
   * iterator beyond the last dial. Dials are not guaranteed to be in any particular order.
   */
  B2DialConstIterator end() const;

  /**
   * @return true if container is empty
   */
  bool empty() const;

  /**
   * return a specific dial by name. throw an exception if a dial is not found
   */
  const B2Dial &At(const std::string &dial_name) const;

  /**
   * @return label by which the dial list is labeled in the ROOT file
   */
  static const char *GetDialListLabel();

ClassDef(B2DialList, 1)
};


#endif //WAGASCIREWEIGHT_B2DIALLIST_HPP
