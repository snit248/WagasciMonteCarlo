//
// Created by Giorgio Pintaudi on 2020/09/02.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2WRITER_HH
#define WAGASCIBABYMINDMONTECARLO_B2WRITER_HH

// boost include
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

// ROOT includes
#include <TTree.h>
#include <TFile.h>
#include <Compression.h>

// project includes
#include "B2SpillSummary.hh"

namespace fs = boost::filesystem;

class B2Reader;

class B2Writer {

private:

  TFile tfile_; ///> output TFile
  TTree *ttree_; ///> output TTree
  TTree *h10_; ///> NEUT TTree
  TTree *reweight_; ///> Weights TTree
  B2SpillSummary *spill_summary_; ///> Spill summary object
  static const auto compression_algorithm_ = ROOT::RCompressionSetting::EAlgorithm::kLZMA;
  static const auto compression_level_ = ROOT::RCompressionSetting::ELevel::kDefaultLZMA + 1;

  /**
   * Copy a ROOT directory from source to destination
   * @param source source TDirectory
   * @param destination destination TDirectory
   */
  static void CopyDir(TDirectory *source, TDirectory *destination);

public:

  /**
   * Open TFile, create TTree and TBranch
   * @param output_filepath path to the file to write
   */
  B2Writer(const fs::path &output_filepath); // NOLINT(google-explicit-constructor)

  /**
   * Open TFile, clone TTree and TBranch
   * @param output_filepath path to the file to write
   * @param reader TTree to clone
   */
  B2Writer(const fs::path &output_filepath, B2Reader &reader);

  /**
   * Write TTree and close TBranch
   */
  ~B2Writer();

  /**
   * Non copyable
   */
  B2Writer(const B2Writer &) = delete;

  /**
   * Non movable
   */
  B2Writer &operator=(const B2Writer &) = delete;

  /**
   * @return output TTree object
   */
  TTree &GetOutputTree();

  /**
   * @return output TFile object
   */
  TFile &GetOutputFile();


  /**
   * @return B2SpillSummary object
   */
  B2SpillSummary &GetSpillSummary();

  /**
   * Wrapper around the ClearEventSummary method of the B2EventSummary class
   */
  void ClearSpillSummary();

  /**
   * Wrapper around the Fill method of the output TTree
   */
  void Fill();

  /**
   * Set the pointer to NEUT Tree. This method can be called only once. If called more than once an exception is
   * going to be thrown.
   * @param h10
   */
  void SetNEUTTree(TTree *h10);
};


#endif //WAGASCIBABYMINDMONTECARLO_B2WRITER_HH
