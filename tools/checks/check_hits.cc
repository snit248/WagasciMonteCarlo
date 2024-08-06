//
// Created by Giorgio Pintaudi on 22/07/02.
//


#include <iostream>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <TCanvas.h>

#include "B2Reader.hh"
#include "B2EventSummary.hh"
#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"

namespace fs = boost::filesystem;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
    return 1;
  }

  const fs::path input_file(argv[1]);

  try {
    B2Reader reader(input_file);

    while (reader.ReadNextSpill() > 0) {

      auto &spill_summary = reader.GetSpillSummary();

      std::cout << " ############ Event " << reader.GetEventId() << " | Num hits " <<
                spill_summary.GetNumHits(B2Detector::kProtonModule) << " #############\n\n";

      auto it1 = spill_summary.BeginHit();
      while (const auto *hit = it1.Next()) {
        std::cout << *hit << "\n\n";
      }
    }

  } catch (const std::exception &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    return EXIT_FAILURE;
  }

  BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
  return EXIT_SUCCESS;
}