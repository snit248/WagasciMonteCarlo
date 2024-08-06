//
// Created by Giorgio Pintaudi on 2021/11/25.
//

#ifndef WAGASCIBABYMINDMONTECARLO_IB2READER_HH
#define WAGASCIBABYMINDMONTECARLO_IB2READER_HH

#include <TTree.h>
#include "B2SpillSummary.hh"

/**
 * Interface for B2Reader. Used in other libraries to add decorators to the B2Reader class. The documentation for
 * the interface methods can be found in the B2Reader.hh implementation.
 */
class IB2Reader {

public:

  /**
   * Define a virtual destructor because this is an interface
   */
  virtual ~IB2Reader() = default;

  /**
   * This class should not be copiable
   */
  IB2Reader &operator()(const IB2Reader &) = delete;

  virtual Long64_t GetEntryNumber() const = 0;

  virtual UInt_t GetEventId() const = 0;

  virtual Long64_t ReadSpillWithEventId(Long64_t event_id) = 0;

  virtual Long64_t ReadNextSpill() = 0;

  virtual Long64_t ReadNextSpill(UInt_t stop_event_id) = 0;

  virtual Long64_t ReadSpill(Long64_t index) = 0;

  virtual const B2SpillSummary &GetSpillSummary() const = 0;

  virtual B2SpillSummary &GetSpillSummary() = 0;

  virtual void DumpSpillSummary() = 0;

  virtual const TTree &GetTree() const = 0;

  virtual TTree &GetTree() = 0;

  virtual bool HasNEUTTree() const = 0;

  virtual const TTree &GetNEUTTree() const = 0;

  virtual TTree &GetNEUTTree() = 0;
};


#endif //WAGASCIBABYMINDMONTECARLO_IB2READER_HH
