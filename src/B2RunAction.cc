#include "B2RunAction.hh"

// system includes
#include <ctime>

// BOOST includes
#include <boost/log/trivial.hpp>

// Geant4 includes
#include "G4Run.hh"
#include "CLHEP/Random/Random.h"

B2RunAction::B2RunAction(const std::string &output_filepath) : writer_(output_filepath) {}

void B2RunAction::EndOfRunAction(const G4Run *) {
  BOOST_LOG_TRIVIAL(info) << " ============= END OF RUN =============";
}

void B2RunAction::BeginOfRunAction(const G4Run *) {
  BOOST_LOG_TRIVIAL(info) << " ============= BEGIN OF RUN =============";
  const auto timer = std::time(nullptr);
  const auto seed = long(timer);
  BOOST_LOG_TRIVIAL(info) << "Seeding the random number generator with seed  "
                          << seed << " (" << timer << ")";
  CLHEP::HepRandom::setTheSeed(seed);
}

void B2RunAction::FillOutputTrees() {
  writer_.Fill();
}

B2SpillSummary &B2RunAction::GetSpillSummary() {
  return writer_.GetSpillSummary();
}

void B2RunAction::ClearSpillSummary() {
  writer_.ClearSpillSummary();
}

void B2RunAction::CloneNEUTTree(TTree *h10) {
  writer_.SetNEUTTree(h10->CloneTree(0));
}
