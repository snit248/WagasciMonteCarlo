//
// Created by Giorgio Pintaudi on 2021/01/19.
//

#include "B2RefArray.hh"
#include <algorithm>

B2RefArrayIterator B2RefArray::begin() {
  return references_.begin();
}

B2RefArrayIterator B2RefArray::end() {
  return references_.end();
}

B2RefArrayConstIterator B2RefArray::begin() const {
  return references_.begin();
}

B2RefArrayConstIterator B2RefArray::end() const {
  return references_.end();
}

B2RefArrayConstIterator B2RefArray::cbegin() const {
  return references_.cbegin();
}

B2RefArrayConstIterator B2RefArray::cend() const {
  return references_.cend();
}

Long64_t B2RefArray::GetEntries() {
  return references_.size();
}

void B2RefArray::Add(TObject *object) {
  references_.emplace_back(object);
}

void B2RefArray::Add(TObject &object) {
  references_.emplace_back(&object);
}

void B2RefArray::Remove(TObject *object) {
  std::remove(references_.begin(), references_.end(), object); // NOLINT(bugprone-unused-return-value)
}

void B2RefArray::Remove(TObject &object) {
  std::remove(references_.begin(), references_.end(), &object); // NOLINT(bugprone-unused-return-value)
}

void B2RefArray::Clear(Option_t *option) {
  references_.clear();
  TObject::Clear(option);
}

TObject *B2RefArray::At(Int_t idx) const {
  return references_.at(idx).GetObject();
}

ClassImp(B2RefArray)