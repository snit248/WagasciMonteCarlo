//
// Created by Giorgio Pintaudi on 8/31/20.
//

#include <iostream>
#include <vector>
#include <boost/log/trivial.hpp>

#include "B2Reader.hh"
#include "B2Writer.hh"
#include "B2EventSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2HitSummary.hh"
#include "B2Pdg.hh"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/output.root>\n";
    std::exit(1);
  }

  try {
    B2Reader reader(argv[1]);
    B2Writer writer("test_ouput.root", reader);

    reader.ReadSpill(1);

    auto &spill_summary = writer.GetSpillSummary();

    auto it = spill_summary.BeginTrueTrack();

    std::vector<B2HitSummary *> muon_hits;
    while (auto *track = it.Next()) {
      if (B2Pdg::IsMuonPlusOrMinus(track->GetParticlePdg())) {
        auto &hits = track->GetHits();
        muon_hits.reserve(hits.GetEntries());
        for (int i = 0; i < hits.GetEntries(); ++i) {
          muon_hits.push_back(dynamic_cast<B2HitSummary *>(hits.At(i)));
        }
      }
    }

    auto position = muon_hits.at(0)->GetTrueAbsolutePosition().GetValue();
    // use position.x() ... as you see fit
    // Cluster reconstruction (Cellular Automaton)

    auto &cluster = spill_summary.AddTrueCluster();

    for (const auto &hit : muon_hits) {
      cluster.AddHit(*hit);
    }

    auto &track = spill_summary.AddTrueTrack();
    track.AddCluster(cluster, kTRUE);
    track.SetInitialAbsoluteMomentum(1000); // 1 GeV = 1000 MeV

    writer.Fill();

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


