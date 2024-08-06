//
// Created by Giorgio Pintaudi on 2020/10/21.
//

//
// Created by Giorgio Pintaudi on 8/31/20.
//

#include <iostream>
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
  if (argc != 3) {
    std::cout << "usage " << argv[0] << " </path/to/input.root> </path/to/input.root>\n";
    std::exit(1);
  }

  try {

    {
      B2Reader reader(argv[1]);
      B2Writer writer(argv[2], reader);

      reader.ReadSpill(0);
      writer.Fill();
    }
    {
      B2Reader reader(argv[2]);
      while (reader.ReadNextSpill() > 0) {
        std::cout << " ==================== CLUSTERS ====================\n\n";
        {
          auto i = reader.GetSpillSummary().BeginTrueCluster();
          while (auto *cluster = i.Next()) {
            std::cout << *cluster << "\n\n";
            auto j = cluster->BeginHit();
            while (auto *hit = j.Next()) {
              std::cout << *hit << "\n\n";
            }
          }
        }
        std::cout << " ==================== TRACKS ====================\n\n";
        {
          auto i = reader.GetSpillSummary().BeginTrueTrack();
          while (auto *track = i.Next()) {
            std::cout << *track << "\n\n";
            auto j = track->BeginHit();
            while (auto *hit = j.Next()) {
              std::cout << *hit << "\n\n";
            }
            auto k = track->BeginCluster();
            while (auto *cluster = k.Next()) {
              std::cout << *cluster << "\n\n";
            }
          }
        }
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
      }
      std::cout << " ==================== EVENTS ====================\n\n";
      {
        auto i = reader.GetSpillSummary().BeginTrueEvent();
        while (auto *event = i.Next()) {
          std::cout << *event << "\n\n";
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



