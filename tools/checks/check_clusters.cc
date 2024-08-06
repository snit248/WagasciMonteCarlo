//
// Created by Giorgio Pintaudi on 2020/10/06.
//

#include <iostream>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <TH1I.h>
#include <TCanvas.h>

#include "B2Reader.hh"
#include "B2EventSummary.hh"
#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"

namespace fs = boost::filesystem;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
    std::exit(1);
  }

  const fs::path input_file(argv[1]);

  try {
    B2Reader reader(input_file);

    while (reader.ReadNextSpill() > 0) {

      auto &input_spill_summary = reader.GetSpillSummary();

      auto it1 = input_spill_summary.BeginHit();
      while (const auto *hit = it1.Next()) {
        std::cout << *hit << "\n\n";
      }

      auto it2 = input_spill_summary.BeginTrueCluster();

      while (const auto *cluster = it2.Next()) {
        std::cout << *cluster << "\n\n";

        auto it3 = cluster->BeginHit();
        while (const auto *hit = it3.Next()) {
          std::cout << *hit << "\n\n";
        }
      }
    }

  } catch (const std::runtime_error &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    std::exit(1);
  } catch (const std::invalid_argument &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Invalid argument error : " << error.what();
    std::exit(1);
  }

  BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
  std::exit(0);
}



