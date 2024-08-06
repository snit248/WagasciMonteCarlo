//
// Created by Giorgio Pintaudi on 8/31/20.
//

#include "B2Reader.hh"

// system includes
#include <iostream>

// boost includes
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

// ROOT includes
#include <TTree.h>
#include <TClassTable.h>

// project includes
#include "B2SpillSummary.hh"
#include "B2EventSummary.hh"


B2Reader::B2Reader(TFile &root_file) :
    spill_index_(-1),
    number_spills_(0),
    has_tfile_ownership(false),
    tfile_(&root_file),
    ttree_((TTree *) tfile_->Get(WAGASCI_TREE_NAME.c_str())),
    h10_((TTree *) tfile_->Get(NEUT_TREE_NAME.c_str())),
    reweight_((TTree *) tfile_->Get(REWEIGHT_TREE_NAME.c_str())),
    spill_summary_(nullptr) {
  Initialize(tfile_->GetPath());
}

B2Reader::B2Reader(const std::string &root_file) :
    spill_index_(-1),
    number_spills_(0),
    has_tfile_ownership(true),
    tfile_(new TFile(root_file.c_str(), "READ")),
    ttree_((TTree *) tfile_->Get(WAGASCI_TREE_NAME.c_str())),
    h10_((TTree *) tfile_->Get(NEUT_TREE_NAME.c_str())),
    reweight_((TTree *) tfile_->Get(REWEIGHT_TREE_NAME.c_str())),
    spill_summary_(nullptr) {
  if (!boost::filesystem::exists(root_file)) {
    throw std::runtime_error("Input ROOT file does not exist : " + root_file);
  }
  if (Initialize(root_file) <= 0) {
    throw std::runtime_error("No events found in ROOT file : " + root_file);
  }
}

B2Reader::B2Reader(const boost::filesystem::path &root_file) :
    B2Reader(root_file.string()) {}

B2Reader::B2Reader(const char *root_file) :
    B2Reader(std::string(root_file)) {}

Long64_t B2Reader::Initialize(const std::string &root_file) {

  BOOST_LOG_TRIVIAL(info) << "Reading ROOT file " << root_file;

  if (!TClassTable::GetDict("B2SpillSummary")) {
    throw std::runtime_error("WAGASCI library was not load correctly");
  }

  if (ttree_ == nullptr) {
    std::stringstream ss;
    ss << "Failed to read TTree named " << WAGASCI_TREE_NAME << " from ROOT file " << root_file;
    throw std::runtime_error(ss.str());
  }

  if (!HasNEUTTree()) {
    BOOST_LOG_TRIVIAL(info) << "NEUT TTree named " << NEUT_TREE_NAME
                            << " not found in ROOT file " << root_file;
  }

  if (!HasWeightTree()) {
    BOOST_LOG_TRIVIAL(info) << "Weight named " << REWEIGHT_TREE_NAME
                            << " not found in ROOT file " << root_file;
  }

  // Set spill branch address
  ttree_->SetBranchAddress("spill", &spill_summary_);

  number_spills_ = ttree_->GetEntries();
  return number_spills_;
}

Long64_t B2Reader::ReadNextSpill(UInt_t stop_event_id) {
  int read_bytes;
  ++spill_index_;
  if (spill_index_ >= number_spills_) {
    read_bytes = -1;
    BOOST_LOG_TRIVIAL(info) << "Read all spills : " << spill_index_ << "/" << number_spills_;
  } else {
    ttree_->GetEntry(spill_index_);
    read_bytes = sizeof(*spill_summary_);
    if (spill_index_ % 1000 == 0) {
      BOOST_LOG_TRIVIAL(info) << "Reading spill with index " << spill_index_;
    }
  }
  if (stop_event_id > 0 && HasEventIdField() && GetEventId() > stop_event_id)
    read_bytes = -1;
  return read_bytes;
}

Long64_t B2Reader::ReadNextSpill() {
  return ReadNextSpill(-1);
}

Long64_t B2Reader::ReadSpill(Long64_t index) {
  int read_bytes;
  if (index >= number_spills_) {
    read_bytes = -1;
  } else {
    ttree_->GetEntry(index);
    read_bytes = sizeof(*spill_summary_);
    spill_index_ = index;
  }
  return read_bytes;
}


const B2SpillSummary &B2Reader::GetSpillSummary() const {
  return *spill_summary_;
}

B2SpillSummary &B2Reader::GetSpillSummary() {
  return *spill_summary_;
}

void B2Reader::DumpSpillSummary() {
  std::cout << "Spill " << spill_index_ - 1 << " summary :\n" << *spill_summary_;
  int counter = 0;
  auto it = spill_summary_->BeginTrueEvent();
  while (const auto *event = it.Next()) {
    std::cout << "Event " << ++counter << " summary :\n" << *event << "\n";
  }
}

B2Reader::~B2Reader() {
  delete spill_summary_;
  if (has_tfile_ownership)
    delete tfile_;
}

const TTree &B2Reader::GetTree() const {
  return *ttree_;
}

TTree &B2Reader::GetTree() {
  return *ttree_;
}

Long64_t B2Reader::GetEntryNumber() const {
  return spill_index_;
}

Long64_t B2Reader::ReadSpillWithEventId(Long64_t event_id) {
  Long64_t result;
  bool found = false;
  while (!found) {
    result = ReadNextSpill();
    if (result <= 0) {
      found = true;
    } else {
      auto it = spill_summary_->BeginTrueEvent();
      while (const auto *event = it.Next()) {
        if (HasEventIdField() && event->GetEventId() >= event_id) {
          found = true;
          break;
        }
      }
    }
  }
  return result;
}

UInt_t B2Reader::GetEventId() const {
  return GetSpillSummary().FirstTrueEvent().GetEventId();
}

bool B2Reader::HasNEUTTree() const {
  return h10_ != nullptr;
}

TTree &B2Reader::GetNEUTTree() {
  if (!HasNEUTTree())
    throw std::runtime_error("NEUT tree not found");
  return *h10_;
}

const TTree &B2Reader::GetNEUTTree() const {
  if (!HasNEUTTree())
    throw std::runtime_error("NEUT tree not found");
  return *h10_;
}

bool B2Reader::HasWeightTree() const {
  return reweight_ != nullptr;
}

TTree &B2Reader::GetWeightTree() {
  if (!HasWeightTree())
    throw std::runtime_error("Weight tree not found");
  return *reweight_;
}

const TTree &B2Reader::GetWeightTree() const {
  if (!HasWeightTree())
    throw std::runtime_error("Weight tree not found");
  return *reweight_;
}

bool B2Reader::HasEventIdField() {
  return spill_summary_->GetNumTrueEvents() > 0;
}

TFile *B2Reader::GetTfile() const {
  return tfile_;
}
