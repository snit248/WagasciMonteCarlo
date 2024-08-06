//
// Created by Giorgio Pintaudi on 8/31/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2READER_HH
#define WAGASCIBABYMINDMONTECARLO_B2READER_HH

// system includes
#include <string>

// boost includes
#include <boost/filesystem.hpp>

// ROOT includes
#include <TFile.h>

// project includes
#include "IB2Reader.hh"

class B2Writer;

class B2Reader : public IB2Reader {

  friend B2Writer;

private:
  ///> index of the current spill
  Long64_t spill_index_;

  ///> total number of spills
  Long64_t number_spills_;

  ///> If true the B2Reader object has ownership on the TFile
  bool has_tfile_ownership;

  ///> TFile object
  TFile *tfile_;


  ///> Pointer to TTree
  TTree *ttree_;

  ///> Pointer to NEUT TTree
  TTree *h10_;

  ///> Pointer to T2KReWeight TTree
  TTree *reweight_;

  ///> spill object
  B2SpillSummary *spill_summary_;

  /**
   * Open the ROOT file and set branches addresses
   * @param root_file ROOT file to open
   * @return number of events in the ROOT file
   */
  Long64_t Initialize(const std::string &root_file);

  /**
   * @return true if the spill has a true event with the event ID filed
   */
  bool HasEventIdField();

protected:

  TFile *GetTfile() const;

public:

  /**
   * Initialize ROOT file reader. Just calls the Initialize method.
   * @param root_file path to ROOT file
   */
  explicit B2Reader(const char *root_file);

  /**
   * Initialize ROOT file reader. Just calls the Initialize method.
   * @param root_file path to ROOT file
   */
  explicit B2Reader(const std::string &root_file);

  /**
   * Initialize ROOT file reader. Just calls the Initialize method.
   * @param root_file path to ROOT file
   */
  explicit B2Reader(const boost::filesystem::path &root_file);

  /**
   * Initialize ROOT file reader. Just calls the Initialize method.
   * @param root_file ROOT TFile object
   */
  explicit B2Reader(TFile &root_file);

  /**
   * Release B2SpillSummary memory
   */
  ~B2Reader() override;

  /**
   * This class should not be copiable. move constructor and move assignment
   * are not implicitly declared (Cf. C++11 12.8/9)
   */
  B2Reader(const B2Reader &) = delete;

  /**
 * Read the next spill into the B2SpillSummary container.
 *
 * @return positive value in case of success, negative value in case of failure
 */
  Long64_t ReadNextSpill() override;

  /**
   * Read the next spill into the B2SpillSummary container.
   *
   * @param stop_event_id stop at event with this ID
   * @return positive value in case of success, negative value in case of failure
   */
  Long64_t ReadNextSpill(UInt_t stop_event_id) override;

  /**
   * Read the spill with index into the B2SpillSummary container.
   *
   * @return positive value in case of success, negative value in case of failure
   */
  Long64_t ReadSpill(Long64_t index) override;

  /**
   * @return B2SpillSummary object getter
   */
  const B2SpillSummary &GetSpillSummary() const override;

  /**
   * @return B2SpillSummary object getter
   */
  B2SpillSummary &GetSpillSummary() override;

  /**
   * Print current event info to the console
   */
  void DumpSpillSummary() override;

  /**
   * @return TTree
   */
  const TTree &GetTree() const override;

  /**
   * @return TTree
   */
  TTree &GetTree() override;

  /**
   * @return true if the NEUT TTree is present
   */
  bool HasNEUTTree() const override;

  /**
   * @return NEUT TTree if present otherwise an exception is thrown
   */
  const TTree &GetNEUTTree() const override;

  /**
   * @return NEUT TTree if present otherwise an exception is thrown
   */
  TTree &GetNEUTTree() override;

  /**
   * @return true if the Weight TTree is present
   */
  bool HasWeightTree() const;

  /**
   * @return Weight TTree if present otherwise an exception is thrown
   */
  const TTree &GetWeightTree() const;

  /**
   * @return Weight TTree if present otherwise an exception is thrown
   */
  TTree &GetWeightTree();

  /**
   * @return current spill count
   */
  Long64_t GetEntryNumber() const override;

  /**
   * @return current event ID
   */
  UInt_t GetEventId() const override;

  /**
   * Read until the event with event ID
   * @param event_id
   * @return number of read bytes (-1 in case of error or EOF)
   */
  Long64_t ReadSpillWithEventId(Long64_t event_id) override;
};


#endif //WAGASCIBABYMINDMONTECARLO_B2READER_HH
