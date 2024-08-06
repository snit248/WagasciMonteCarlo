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
    std::cout << "usage " << argv[0] << " </path/to/input.root>\n";
    std::exit(1);
  }

  try {
    B2Reader reader(argv[1]);
    B2Writer writer("ouput_CC0pi_0000.root", reader);

    while (reader.ReadNextSpill() > 0) {

    auto &spill_summary = writer.GetSpillSummary();
//    std::vector<B2EventSummary *> cc0_events;
    auto it_event = spill_summary.BeginTrueEvent();
	while (const auto *event = it_event.Next()){
		if((event->GetInteractionType())==1 || (event->GetInteractionType())==2){
//		cc0_events.push_back(dynamic_cast<B2EventSummary *>(spill_summary.GetTrueEvents().First()));
    writer.Fill();
		}
	else continue;
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


