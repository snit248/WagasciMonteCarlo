//
// Created by Giorgio Pintaudi on 2021/11/25.
//

#include <B2ReaderDecorator.hh>


B2ReaderDecorator::B2ReaderDecorator(IB2Reader &wrappee) : wrappee_(wrappee) {}

Long64_t B2ReaderDecorator::GetEntryNumber() const {
  return wrappee_.GetEntryNumber();
}

UInt_t B2ReaderDecorator::GetEventId() const {
  return wrappee_.GetEventId();
}

Long64_t B2ReaderDecorator::ReadSpillWithEventId(Long64_t event_id) {
  return wrappee_.ReadSpillWithEventId(event_id);
}

Long64_t B2ReaderDecorator::ReadNextSpill() {
  return wrappee_.ReadNextSpill();
}

Long64_t B2ReaderDecorator::ReadNextSpill(UInt_t stop_event_id) {
  return wrappee_.ReadNextSpill(stop_event_id);
}

Long64_t B2ReaderDecorator::ReadSpill(Long64_t index) {
  return wrappee_.ReadSpill(index);
}

const B2SpillSummary &B2ReaderDecorator::GetSpillSummary() const {
  return wrappee_.GetSpillSummary();
}

B2SpillSummary &B2ReaderDecorator::GetSpillSummary() {
  return wrappee_.GetSpillSummary();
}

void B2ReaderDecorator::DumpSpillSummary() {
  return wrappee_.DumpSpillSummary();
}

const TTree &B2ReaderDecorator::GetTree() const {
  return wrappee_.GetTree();
}

TTree &B2ReaderDecorator::GetTree() {
  return wrappee_.GetTree();
}

bool B2ReaderDecorator::HasNEUTTree() const {
  return wrappee_.HasNEUTTree();
}

TTree &B2ReaderDecorator::GetNEUTTree() {
  return wrappee_.GetNEUTTree();
}

const TTree &B2ReaderDecorator::GetNEUTTree() const {
  return wrappee_.GetNEUTTree();
}