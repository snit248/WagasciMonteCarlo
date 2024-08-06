//
// Created by Giorgio Pintaudi on 2021/01/19.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2REFARRAY_HH
#define WAGASCIBABYMINDMONTECARLO_B2REFARRAY_HH

#include <TRef.h>


using B2Ref = TRef;
using B2RefArrayContainer = std::vector<B2Ref>;
using B2RefArrayIterator = B2RefArrayContainer::iterator;
using B2RefArrayConstIterator = B2RefArrayContainer::const_iterator;

class B2RefArray : public TObject {

private:

  B2RefArrayContainer references_;

public:

  B2RefArrayIterator begin();

  B2RefArrayIterator end();

  B2RefArrayConstIterator begin() const;

  B2RefArrayConstIterator end() const;

  B2RefArrayConstIterator cbegin() const;

  B2RefArrayConstIterator cend() const;

  Long64_t GetEntries();

  void Add(TObject *object);

  void Add(TObject &object);

  TObject *At(Int_t idx) const;

  void Clear(Option_t *option) override;

  void Remove(TObject *object);

  void Remove(TObject &object);

ClassDefOverride(B2RefArray, 1)
};


#endif //WAGASCIBABYMINDMONTECARLO_B2REFARRAY_HH
