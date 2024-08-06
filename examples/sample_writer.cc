//
// Created by Giorgio Pintaudi on 2021/05/06.
//

#include <iostream>

#include <boost/log/trivial.hpp>

#include "B2Reader.hh"
#include "B2Writer.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2HitSummary.hh"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "usage " << argv[0] << "</path/to/file1.root> </path/to/file2.root>\n";
    return EXIT_SUCCESS;
  }

  try {
    B2Writer writer(argv[1]);

    auto &spill_summary = writer.GetSpillSummary();
    auto &track = spill_summary.AddReconTrack();
    auto &cluster = spill_summary.AddReconCluster();
    auto &hit = spill_summary.AddHit();

    hit.SetTrueAbsolutePosition(TVector3(1, 1, 1));
    cluster.AddHit(hit);
    track.AddCluster(cluster, true);

    writer.Fill();
  } catch (const std::exception &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    return EXIT_FAILURE;
  }

  try {
    B2Reader reader(argv[1]);
    B2Writer writer(argv[2], reader);

    while (reader.ReadNextSpill() > 0) {
      auto &spill_summary = writer.GetSpillSummary();

      auto it = spill_summary.BeginReconTrack();
      while (auto *track = it.Next()) {
        track->SetInitialAbsoluteMomentum(9999);
        track->SetInitialDirection(TVector3(1, 0, 0));
        track->SetInitialPosition(TVector3(1, 1, 1));
      }

      writer.Fill();
    }
  } catch (const std::runtime_error &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    return EXIT_FAILURE;
  }

  try {
    B2Reader reader(argv[2]);

    while (reader.ReadNextSpill() > 0) {

      auto it = reader.GetSpillSummary().BeginReconTrack();
      while (auto *track = it.Next()) {
        if (track->GetInitialAbsoluteMomentum().GetValue() != 9999)
          BOOST_LOG_TRIVIAL(fatal) << "Failed to write initial absolute momentum";

        if (track->GetInitialDirection().GetValue().X() != 1)
          BOOST_LOG_TRIVIAL(fatal) << "Failed to write initial direction";

        if (track->GetInitialPosition().GetValue().X() != 1)
          BOOST_LOG_TRIVIAL(fatal) << "Failed to write initial position";
      }
    }
  } catch (const std::runtime_error &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    return EXIT_FAILURE;
  }

  BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
  return EXIT_SUCCESS;
}


