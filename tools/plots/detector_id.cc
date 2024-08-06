//
// Created by Giorgio Pintaudi on 2020/10/05.
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

namespace fs = boost::filesystem;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
    std::exit(1);
  }

  const fs::path input_file(argv[1]);

  try {
    B2Reader reader(input_file);

    const fs::path output_file_path(input_file.parent_path() / "detector_id.png");

    TH1I h_detector_id("detector_id", "Num of hits in each detector;detector;number of hits",
                       B2Detector::kNumDetectors, 0, B2Detector::kNumDetectors);

    for (int det = B2Detector::kProtonModule; det != B2Detector::kNumDetectors; ++det)
      h_detector_id.GetXaxis()->SetBinLabel(det + 1, DETECTOR_NAMES.at(static_cast<B2Detector>(det)).c_str());


    while (reader.ReadNextSpill() > 0) {

      auto &input_spill_summary = reader.GetSpillSummary();

      auto it = input_spill_summary.BeginHit();

      while (const auto *hit = it.Next()) {
        if (hit->GetDetectorId() < B2Detector::kProtonModule ||
            hit->GetDetectorId() >= B2Detector::kNumDetectors) {
          BOOST_LOG_TRIVIAL(error) << "Found a hit in an unknown detector : " << hit->GetDetectorId();
        } else {
          h_detector_id.Fill(hit->GetDetectorId());
        }
      }
    }

    TCanvas tcanvas("c1", "c1", 1280, 720);
    h_detector_id.Draw();
    tcanvas.Print(output_file_path.c_str());

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



