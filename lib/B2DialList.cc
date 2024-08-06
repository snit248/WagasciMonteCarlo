//
// Created by Giorgio Pintaudi on 2021/11/15.
//

#include <B2DialList.hh>

const char *DIAL_TDIRECTORY_NAME = "dials";

B2DialList::B2DialConstIterator B2DialList::begin() const {
  return dials_.begin();
}

B2DialList::B2DialConstIterator B2DialList::end() const {
  return dials_.end();
}

void B2DialList::InsertDial(const B2Dial &dial) {
  dials_.emplace_back(dial);
}

const B2Dial &B2DialList::At(const std::string &dial_name) const {
  auto it = std::find_if(dials_.begin(), dials_.end(), [dial_name](const B2Dial &key){
    return key.GetDialName() == dial_name;
  });
  if (it == dials_.end())
    throw std::out_of_range("B2Dial with name " + dial_name + " not found");
  return *it;
}

bool B2DialList::empty() const {
  return dials_.empty();
}

const char *B2DialList::GetDialListLabel() {
  return "B2DialList";
}

ClassImp(B2DialList)