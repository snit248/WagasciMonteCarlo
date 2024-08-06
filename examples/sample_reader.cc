//
// Created by Giorgio Pintaudi on 8/31/20.
//

#include <iostream>

#include <boost/log/trivial.hpp>

#include "B2Reader.hh"
#include "B2Writer.hh"
#include "B2EventSummary.hh"
#include "B2VertexSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2HitSummary.hh"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
    return EXIT_SUCCESS;
  }

  try {
    B2Reader reader(argv[1]);
    B2Writer writer("test_output.root", reader);

    while (reader.ReadNextSpill() > 0) {
      auto &spill_summary = writer.GetSpillSummary();

      auto it = spill_summary.BeginHit();
      std::vector<const B2HitSummary *> my_hits;
      while (const auto *hit = it.Next()) {
        if (hit->GetDetectorId() == B2Detector::kBabyMind)
          my_hits.push_back(hit);
      }

      // Cluster reconstruction (Cellular Automaton)
      auto &cluster = spill_summary.AddReconCluster();

      for (const auto &hit : my_hits) {
        cluster.AddHit(*hit);
      }

      writer.Fill();
    }

  } catch (const std::exception &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    return EXIT_FAILURE;
  }

  BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
  return EXIT_SUCCESS;
}


