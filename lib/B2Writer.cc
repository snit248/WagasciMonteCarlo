//
// Created by Giorgio Pintaudi on 2020/09/02.
//

#include "B2Writer.hh"

// system includes
#include <iostream>

// ROOT includes
#include <TDirectory.h>

// project includes
#include "B2Reader.hh"
#include "B2SigmaList.hh"
#include "B2DialList.hh"

void B2Writer::CopyDir(TDirectory *source, TDirectory *destination) {
  source->cd();
  B2DialList *p_dial_list;
  source->GetObject(B2DialList::GetDialListLabel(), p_dial_list);
  if (p_dial_list) {
    BOOST_LOG_TRIVIAL(info) << "Writing dial list";
    destination->cd();
    p_dial_list->Write();
  } else {
    BOOST_LOG_TRIVIAL(info) << "Dial list \"" << B2DialList::GetDialListLabel() << "\" not found";
  }
  source->cd();
  B2SigmaList *p_sigma_list;
  source->GetObject(B2SigmaList::GetSigmaListLabel(), p_sigma_list);
  if (p_sigma_list) {
    BOOST_LOG_TRIVIAL(info) << "Writing sigma list";
    destination->cd();
    p_sigma_list->Write();
  } else {
    BOOST_LOG_TRIVIAL(info) << "Sigma list \"" << B2SigmaList::GetSigmaListLabel() << "\" not found";
  }
}

B2Writer::B2Writer(const fs::path &output_filepath) :
    tfile_(output_filepath.c_str(), "RECREATE"),
    ttree_(new TTree(WAGASCI_TREE_NAME.c_str(), "WAGASCI-BabyMIND common data format")),
    h10_(nullptr),
    reweight_(nullptr),
    spill_summary_(new B2SpillSummary()) {
  tfile_.SetCompressionAlgorithm(compression_algorithm_);
  tfile_.SetCompressionLevel(compression_level_);
  BOOST_LOG_TRIVIAL(info) << "Creating output file TBranches";
  ttree_->SetDirectory(&tfile_);
  ttree_->SetBit(EObjBits::kCanDelete);
  ttree_->SetAutoFlush(100);
  ttree_->SetAutoSave(100);
  spill_summary_->CreateBranch(*ttree_);
  spill_summary_->SetBit(EObjBits::kCanDelete);
}

B2Writer::B2Writer(const fs::path &output_filepath, B2Reader &reader) :
    tfile_(output_filepath.c_str(), "RECREATE"),
    ttree_(reader.GetTree().CloneTree(0)),
    h10_(reader.HasNEUTTree() ? reader.GetNEUTTree().CloneTree(0) : nullptr),
    reweight_(reader.HasWeightTree() ? reader.GetWeightTree().CloneTree(-1, "fast") : nullptr),
    spill_summary_(&reader.GetSpillSummary()) {
  if (h10_)
    ttree_->AddFriend(h10_);
  if (reweight_)
    ttree_->AddFriend(reweight_);
  auto *source_dir = reader.GetTfile()->GetDirectory(DIAL_TDIRECTORY_NAME);
  if (source_dir) {
    auto *dest_dir = tfile_.mkdir(DIAL_TDIRECTORY_NAME);
    CopyDir(source_dir, dest_dir);
  }
}

B2Writer::~B2Writer() {
  BOOST_LOG_TRIVIAL(info) << "Writing WAGASCI TTree \"" << ttree_->GetName() << "\" to TFile";
  ttree_->AutoSave();
  if (h10_ != nullptr) {
    BOOST_LOG_TRIVIAL(info) << "Writing NEUT TTree \"" << h10_->GetName() << "\" to TFile";
    h10_->AutoSave();
  }
  if (reweight_ != nullptr) {
    BOOST_LOG_TRIVIAL(info) << "Writing Weight TTree \"" << reweight_->GetName() << "\" to TFile";
    reweight_->AutoSave();
  }
  BOOST_LOG_TRIVIAL(info) << "Closing output TFile : \"" << tfile_.GetName() << "\"";
  tfile_.Close();
}

TTree &B2Writer::GetOutputTree() {
  return *ttree_;
}

TFile &B2Writer::GetOutputFile() {
  return tfile_;
}

B2SpillSummary &B2Writer::GetSpillSummary() {
  return *spill_summary_;
}

void B2Writer::ClearSpillSummary() {
  BOOST_LOG_TRIVIAL(trace) << "Clearing B2SpillSummary singleton object";
  spill_summary_->Clear("C");
}

void B2Writer::SetNEUTTree(TTree *h10) {
  if (h10_)
    throw std::runtime_error("The NEUT TTree can be initialized only once!");
  h10_ = h10;
  ttree_->AddFriend(h10_);
}

void B2Writer::Fill() {
  //static int counter = 0;
  //std::cout << "event number " << counter++ << std::endl;
  BOOST_LOG_TRIVIAL(trace) << "Filling output TTree of TFile \"" << tfile_.GetName() << "\"";
  ttree_->Fill();
  if (h10_ != nullptr)
    h10_->Fill();
  ClearSpillSummary();
}
