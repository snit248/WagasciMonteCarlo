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
#include "B2ClusterSummary.hh"
#include "B2HitSummary.hh"

double convert_dposz(double dposz) {
  const int number_of_scintillator = 8;
  double mc_dposz[number_of_scintillator];
  double convert_dposz[number_of_scintillator];
  for (int i = 0; i < number_of_scintillator; i++) {
    mc_dposz[i] = -700 + 200 * i;
    convert_dposz[i] = 100 + 200 * i;
    if (dposz == mc_dposz[i] || dposz == convert_dposz[i]) return convert_dposz[i];
  }
  return -2;
}

double convert_dposx(double dposx) {
  const int number_of_plane = 10;
  double mc_dposx[number_of_plane];
  double convert_dposx[number_of_plane];
  for (int i = 0; i < number_of_plane; i++) {
    mc_dposx[i] = -193.5 + 43 * i;
    convert_dposx[i] = 36.5 + 43 * i;
    if (dposx == mc_dposx[i] || dposx == convert_dposx[i]) return convert_dposx[i];
  }
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
  int event_id;
  //std::vector<int> clusterId;
  std::vector<int> track_type;
  std::vector<int> view;
  std::vector<int> detector;
  std::vector<int> plane;
  std::vector<int> chip_top;
  std::vector<int> chip_bottom;
  std::vector<int> slot_top;
  std::vector<int> slot_bottom;
  std::vector<double> pe_top;
  std::vector<double> pe_bottom;
  std::vector<double> dposz;
  std::vector<double> dposx;

  tree->Branch("normalization", &norm);
  tree->Branch("cross_section", &xsec);
  tree->Branch("event_id", &event_id);
  //tree->Branch("clusterId", &clusterId);
  tree->Branch("track_type", &track_type);
  tree->Branch("view", &view);
  tree->Branch("detector", &detector);
  tree->Branch("plane", &plane);
  tree->Branch("chip_top", &chip_top);
  tree->Branch("chip_bottom", &chip_bottom);
  tree->Branch("slot_top", &slot_top);
  tree->Branch("slot_bottom", &slot_bottom);
  tree->Branch("pe_top", &pe_top);
  tree->Branch("pe_bottom", &pe_bottom);
  tree->Branch("dposz", &dposz);
  tree->Branch("dposx", &dposx);

  bool coincidence = false;

  for (int run_number = start_number; run_number <= end_number; run_number++) {
    TString input_file_name;
    input_file_name.Form("%s_%04d.root", input_file_path.Data(), run_number);
  try {
    B2Reader reader(input_file_name);
    while (reader.ReadNextSpill() > 0) {
      auto &spill_summary = reader.GetSpillSummary();
      auto it_event = spill_summary.BeginTrueEvent();
      while (const auto *event = it_event.Next()) {
	const auto &vertex = event->GetPrimaryVertex();
	norm = event->GetNormalization();
	xsec = vertex.GetTotalCrossSection();
      }

      auto it_cluster = spill_summary.BeginTrueCluster();
      while (const auto *cluster = it_cluster.Next()) {
	//if (cluster->GetClusterId() != 9999) continue; // sand muon cluster ID
	auto it_hit = cluster->BeginHit();
	coincidence = false;
	while (const auto *hit = it_hit.Next()) {
	  if (hit->GetDetectorId() != kWallMrdSouth && hit->GetDetectorId() != kWallMrdNorth) continue;
	  if (hit->GetView() == kTopView) {
	    if (hit->GetHighGainPeu().GetValue(kTopReadout) > 0 &&
		hit->GetHighGainPeu().GetValue(kBottomReadout) > 0) {
	      coincidence = true;
	      //clusterId.push_back(cluster->GetClusterId());
	      detector.push_back(hit->GetDetectorId());
	      view.push_back(hit->GetView());
	      plane.push_back(hit->GetPlane());
	      chip_top.push_back(hit->GetChip().GetValue(kTopReadout));
	      chip_bottom.push_back(hit->GetChip().GetValue(kBottomReadout));
	      slot_top.push_back(hit->GetSlot().GetValue(kTopReadout));
	      slot_bottom.push_back(hit->GetSlot().GetValue(kBottomReadout));
	      pe_top.push_back(hit->GetHighGainPeu().GetValue(kTopReadout));
	      pe_bottom.push_back(hit->GetHighGainPeu().GetValue(kBottomReadout));
	      dposz.push_back(convert_dposz(hit->GetScintillatorPosition().GetValue().z()));
	      dposx.push_back(convert_dposx(hit->GetScintillatorPosition().GetValue().x()));
	    }
	  }
	}
	if (coincidence) tree->Fill();
	//clusterId.clear();
	view.clear();
	detector.clear();
	plane.clear();
	chip_top.clear();
	chip_bottom.clear();
	slot_top.clear();
	slot_bottom.clear();
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
