#ifndef B2_RUN_ACTION_H
#define B2_RUN_ACTION_H

// ROOT includes
#include <TTree.h>
#include <TFile.h>

// Geant4 includes
#include <G4UserRunAction.hh>
#include <G4ThreeVector.hh>

// project includes
#include "B2SpillSummary.hh"
#include "B2Writer.hh"

/**
 * The B2RunAction class takes care of handling the output TTree and the B2EventSummary class.
 */
class B2RunAction : public G4UserRunAction {

private:

  B2Writer writer_; ///> Object to handle writing to output TTree

public:

  /*
   * Total number of simulated events (including events that do not produce any output)
   */
  int number_simulated_events = 0;
  int number_used_events = 0;
  int number_discarded_events = 0;

  /**
   * @param output_filepath path to the output ROOT file
   */
  explicit B2RunAction(const std::string &output_filepath);

  /**
   * This method is invoked before entering the event loop but after the calculation of the physics tables.
   * It opens the output TFile and creates the output TTree. It also initialize the random number generator.
   */
  void BeginOfRunAction(const G4Run *) override;

  /**
   * This method is invoked at the very end of the run processing. It writes the TTree to the output TFile.
   */
  void EndOfRunAction(const G4Run *) override;

  /**
   * @return output TTree object
   */
  void FillOutputTrees();

  /**
   * @return B2SpillSummary object
   */
  B2SpillSummary &GetSpillSummary();

  /**
   * Wrapper arout the ClearEventSummary method of the B2EventSummary class
   */
  void ClearSpillSummary();

  /**
   * Clone the given NEUT tree and put it inside the B2Writer object, that in turn is going to write
   * it to the output file. The ownership of h10 is not taken.
   * @param h10 input TTree
   */
  void CloneNEUTTree(TTree *h10);
};

#endif
