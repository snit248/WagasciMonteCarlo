//
// Created by neo on 2020/12/20.
//

#include <iostream>
#include <TFile.h>
#include "TTree.h"

#include <vector>
#include <boost/log/trivial.hpp>
#include "B2Reader.hh"
#include "B2EventSummary.hh"
#include "B2VertexSummary.hh"
//#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2HitSummary.hh"

int convert_slot(double dposz) {
  double mc_dposz[8];
  for (int slot = 0; slot < 8; slot++) {
    mc_dposz[slot] = -700 + 200 * slot;
    if (mc_dposz[slot] == dposz) return slot;
  }
  std::cerr << "No matching dposz!!\n";
  return -2;
}

int main(int argc, char *argv[]) {

  //if (argc != 2) {
  //    std::cout << "usage " << argv[0] << " </path/to/output.root>\n";
  //    std::exit(1);
  //}

  int c = -1, start_number = 0, end_number = 0;
  TString input_file_path, output_file_name;
  while ((c = getopt(argc, argv, "i:o:s:e:")) != -1) {
    switch (c) {
    case 'i':
      input_file_path = optarg;
      break;
    case 'o':
      output_file_name = optarg;
      break;
    case 's':
      start_number = atoi(optarg);
      break;
    case 'e':
      end_number = atoi(optarg);
      break;
    }
  }

  //make file, tree
  //const TString output_file = "/home/t2k/kobata/Output/analysis/true/mc_ana_0001.root";
  //const TString input_file = "/home/t2k/kobata/Output/monte-carlo/output_0001.root";
  auto *ofile = new TFile(output_file_name, "recreate");
  auto *tree = new TTree("tree", "tree");

  //make branch
  double norm;
  double xsec;
  int file_id;
  int event_id;
  //std::vector<int> clusterId;
  std::vector<int> track_type;
  std::vector<int> view;
  std::vector<int> detector;
  std::vector<int> plane;
  std::vector<int> chip_top;
  std::vector<int> chip_bottom;
  std::vector<int> slot;
  //std::vector<int> slot_top;
  //std::vector<int> slot_bottom;
  std::vector<double> pe_top;
  std::vector<double> pe_bottom;
  std::vector<double> dposz;
  std::vector<double> dposx;

  tree->Branch("normalization", &norm);
  tree->Branch("cross_section", &xsec);
  tree->Branch("file_id", &file_id);
  tree->Branch("event_id", &event_id);
  tree->Branch("track_type", &track_type);
  tree->Branch("view", &view);
  tree->Branch("detector", &detector);
  tree->Branch("plane", &plane);
  tree->Branch("chip_top", &chip_top);
  tree->Branch("chip_bottom", &chip_bottom);
  tree->Branch("slot", &slot);
  //tree->Branch("slot_top", &slot_top);
  //tree->Branch("slot_bottom", &slot_bottom);
  tree->Branch("pe_top", &pe_top);
  tree->Branch("pe_bottom", &pe_bottom);
  tree->Branch("dposz", &dposz);
  tree->Branch("dposx", &dposx);

  bool coincidence = false;
  int event_number = 0;

  for (int run_number = start_number; run_number <= end_number; run_number++) {
    TString input_file_name;
    input_file_name.Form("%s_%04d.root", input_file_path.Data(), run_number);
    file_id = run_number;
  try {
    B2Reader reader(input_file_name);
    while (reader.ReadNextSpill() > 0) {
      auto &spill_summary = reader.GetSpillSummary();
      auto it_event = spill_summary.BeginReconEvent();
      while (const auto *event = it_event.Next()) {
	const auto &vertex = event->GetPrimaryVertex();
	norm = event->GetNormalization();
	xsec = vertex.GetTotalCrossSection();
      }

        auto it_track = spill_summary.BeginReconTrack();
        while (const auto *track = it_track.Next()) {
          event_id = event_number++;
          if (track->GetTrackType() != kSandMuonMatching) continue;
          auto it_hit = track->BeginHit();
          //auto it_cluster = spill_summary.BeginReconCluster();
          //while (const auto *cluster = it_cluster.Next()) {
        //	if (cluster->GetClusterId() != 9999) continue; // sand muon cluster ID
        //	auto it_hit = cluster->BeginHit();
	coincidence = false;
	while (const auto *hit = it_hit.Next()) {
	  if (hit->GetDetectorId() != kWallMrdSouth && hit->GetDetectorId() != kWallMrdNorth) continue;
	  if (hit->GetView() == kTopView) {
	    if (hit->GetHighGainPeu().GetValue(kTopReadout) >= 6 && hit->GetHighGainPeu().GetValue(kBottomReadout) >= 6) { // Take Coincidence
	      //if (hit->GetHighGainPeu().GetValue(kTopReadout) >= 2.5 && hit->GetHighGainPeu().GetValue(kBottomReadout) >= 2.5) { // Take Coincidence
	    //if (hit->GetHighGainPeu().GetValue(kTopReadout) >= 2.5 || hit->GetHighGainPeu().GetValue(kBottomReadout) >= 2.5) { // Not Take Coincidence
	      //std::cout << "wallmrd\n";
	      coincidence = true;
	      //clusterId.push_back(cluster->GetClusterId());
	      track_type.push_back(track->GetTrackType());
	      detector.push_back(hit->GetDetectorId());
	      view.push_back(hit->GetView());
	      plane.push_back(hit->GetPlane());
	      chip_top.push_back(hit->GetChip().GetValue(kTopReadout));
	      chip_bottom.push_back(hit->GetChip().GetValue(kBottomReadout));
	      slot.push_back(hit->GetSlot().GetValue(kTopReadout));
	      //slot.push_back(convert_slot(hit->GetScintillatorPosition().GetValue().z()));
	      pe_top.push_back(hit->GetHighGainPeu().GetValue(kTopReadout));
	      pe_bottom.push_back(hit->GetHighGainPeu().GetValue(kBottomReadout));
	      dposz.push_back(hit->GetScintillatorPosition().GetValue().z());
	      dposx.push_back(hit->GetScintillatorPosition().GetValue().x());
	    }
	  }
	}
	if (coincidence) tree->Fill();
	//clusterId.clear();
	track_type.clear();
	view.clear();
	detector.clear();
	plane.clear();
	chip_top.clear();
	chip_bottom.clear();
	slot.clear();
	//slot_top.clear();
	//slot_bottom.clear();
	pe_top.clear();
	pe_bottom.clear();
	dposz.clear();
	dposx.clear();
      }
    }

  } catch (const std::runtime_error &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Runtime error : " << error.what();
    std::exit(1);
  } catch (const std::invalid_argument &error) {
    BOOST_LOG_TRIVIAL(fatal) << "Invalid argument error : " << error.what();
    std::exit(1);
  }
  }

  ofile->cd();
  tree->Write();
  ofile->Close();
  BOOST_LOG_TRIVIAL(info) << "CREATING FILE : " << output_file_name;
  BOOST_LOG_TRIVIAL(info) << "SUCCESS!";
  std::exit(0);
}
