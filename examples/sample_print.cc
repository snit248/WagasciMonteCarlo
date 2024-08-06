//
// Created by Giorgio Pintaudi on 2020/10/22.
//

#include <iostream>

#include "B2Reader.hh"
#include "B2EventSummary.hh"
#include "B2VertexSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2EmulsionSummary.hh"
#include "B2HitSummary.hh"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
    std::exit(1);
  }

  try {
    B2Reader reader(argv[1]);

    reader.ReadSpill(0);

    std::cout << " ==================== SPILL ====================\n\n";
    std::cout << reader.GetSpillSummary() << "\n";

    std::cout << " ==================== BSD ====================\n\n";
    std::cout << reader.GetSpillSummary().GetBeamSummary() << "\n";

    std::cout << " ==================== HITS ====================\n\n";
    {
      auto i = reader.GetSpillSummary().BeginHit();
      while (auto *hit = i.Next()) {
        std::cout << *hit << "\n\n";
      }
    }
    std::cout << " ==================== CLUSTERS ====================\n\n";
    {
      auto i = reader.GetSpillSummary().BeginTrueCluster();
      while (auto *cluster = i.Next()) {
        if (cluster->IsValid() && !cluster->IsGhost()) {
          std::cout << *cluster << "\n\n";
//          auto j = cluster->BeginHit();
//          while (auto *hit = j.Next()) {
//            std::cout << *hit << "\n\n";
//          }
        }
      }
    }
    std::cout << " ==================== SCINTILLATOR TRACKS ====================\n\n";
    {
      auto i = reader.GetSpillSummary().BeginTrueTrack();
      while (auto *track = i.Next()) {
        if (track->IsValid()) {
          std::cout << *track << "\n\n";
//          auto j = track->BeginHit();
//          while (auto *hit = j.Next()) {
//            std::cout << *hit << "\n\n";
//          }
//          auto k = track->BeginCluster();
//          while (auto *cluster = k.Next()) {
//            std::cout << *cluster << "\n\n";
//          }
        }
      }
    }
#ifdef NINJA
    std::cout << " ==================== EMULSION TRACKS ====================\n\n";
    {
      auto i = reader.GetSpillSummary().BeginEmulsion();
      while (auto *track = i.Next()) {
        std::cout << *track << "\n\n";
      }
    }
#endif

    std::cout << " ==================== VERTICES ====================\n\n";
    {
      auto i = reader.GetSpillSummary().BeginTrueVertex();
      while (auto *vertex = i.Next()) {
        std::cout << *vertex << "\n\n";
        auto j = vertex->BeginTrack();
        while (auto *track = j.Next()) {
          std::cout << *track << "\n\n";
        }
      }
    }
    std::cout << " ==================== EVENTS ====================\n\n";
    {
      auto i = reader.GetSpillSummary().BeginTrueEvent();
      while (auto *event = i.Next()) {
        std::cout << *event << "\n\n";
      }
    }

  } catch (const std::runtime_error &error) {
    std::cout << "Runtime error : " << error.what() << "\n";
    std::exit(1);
  } catch (const std::invalid_argument &error) {
    std::cout << "Invalid argument error : " << error.what() << "\n";
    std::exit(1);
  }

  std::cout << "SUCCESS!\n";
  std::exit(0);
}
