//
// Created by Giorgio Pintaudi on 2021/11/25.
//

#ifndef WAGASCIREWEIGHT_B2READERDECORATOR_HPP
#define WAGASCIREWEIGHT_B2READERDECORATOR_HPP

// B2MC includes
#include <IB2Reader.hh>

// BOOST includes
#include <boost/core/noncopyable.hpp>


class B2ReaderDecorator : public IB2Reader, private boost::noncopyable {

private:

  IB2Reader &wrappee_;

public:

  B2ReaderDecorator(IB2Reader &wrappee); // NOLINT(google-explicit-constructor)

  Long64_t GetEntryNumber() const override;

  UInt_t GetEventId() const override;

  Long64_t ReadSpillWithEventId(Long64_t event_id) override;

  Long64_t ReadNextSpill() override;

  Long64_t ReadNextSpill(UInt_t stop_event_id) override;

  Long64_t ReadSpill(Long64_t index) override;

  const B2SpillSummary &GetSpillSummary() const override;

  B2SpillSummary &GetSpillSummary() override;

  void DumpSpillSummary() override;

  const TTree &GetTree() const override;

  TTree &GetTree() override;

  bool HasNEUTTree() const override;

  const TTree &GetNEUTTree() const override;

  TTree &GetNEUTTree() override;

};


#endif //WAGASCIREWEIGHT_B2READERDECORATOR_HPP
