#include "B2EventAction.hh"

// system includes
#include <cassert>

// ROOT includes
#include <TClonesArray.h>

// Geant4 includes
#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4TrajectoryContainer.hh>
#include <G4Trajectory.hh>
#include <G4VVisManager.hh>
#include <G4VisManager.hh>
#include <G4ios.hh>
#include <G4SDManager.hh>
#include <G4Square.hh>

// BOOST includes
#include <boost/log/trivial.hpp>

// project includes
#include "B2RunAction.hh"
#include "B2HorizontalSensitiveDetector.hh"
#include "B2Dimension.hh"
#include "B2Converters.hh"
#include "B2EventSummary.hh"
#include "B2TrackSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2VertexSummary.hh"
#include "B2Pdg.hh"
#include "B2Enum.hh"
#include "B2Volume.hh"
#include "B2MichelElectron.hh"

#ifdef NINJA
#include "B2EmulsionSummary.hh"
#endif


B2EventAction::B2EventAction(B2RunAction *rac, const B2Dimension &dimension, const B2Settings &settings)
    : run_action_(rac),
      dimension_(dimension),
      write_flag_(true),
      neutrino_interaction_module_(boost::any_cast<B2Detector>(settings.At(B2Settings::NeutrinoInteractionSettings))),
      process_michel_electrons_(boost::any_cast<bool>(settings.At(B2Settings::MichelElectrons))),
      remove_invalid_michel_electrons_(!boost::any_cast<bool>(settings.At(B2Settings::SecondaryTracks))) {}

void B2EventAction::BeginOfEventAction(const G4Event *) {}

void B2EventAction::EndOfEventAction(const G4Event *p_event) {

  BOOST_LOG_TRIVIAL(debug) << "----- EndOfEventAction -----";

  if (write_flag_) {

    auto &beam_summary = run_action_->GetSpillSummary().GetBeamSummary();
    auto event_number = beam_summary.GetWagasciSpillNumber();

    std::vector<B2ScintillatorHit *> scintillator_hits;

    CollectScintillatorHits(p_event, scintillator_hits);

    ProcessScintillatorHits(scintillator_hits);

    std::vector<B2EmulsionHit *> emulsion_hits;

#ifdef NINJA
    CollectEmulsionHits(p_event, emulsion_hits);

    ProcessEmulsionHits(emulsion_hits);

    beam_summary.EnableDetector(B2Detector::kNinja);
#else
    beam_summary.DisableDetector(B2Detector::kNinja);
#endif

    ProcessClusters();

    ProcessTracks();

    if (process_michel_electrons_)
      ProcessMichelElectrons();

    SetPrimaryVertexClosestHit();

    RemoveEmptyTracks();

    if (neutrino_interaction_module_ == B2Detector::kWall) {
      if (CollectScintillatorHits(p_event, scintillator_hits) > 3) {
        run_action_->FillOutputTrees();
      }
    } else {
      run_action_->FillOutputTrees();
    }

    run_action_->ClearSpillSummary();

#ifdef WITH_G4VIS
    DrawEvent(p_event, scintillator_hits, emulsion_hits);
#endif

    if (event_number % 10000 == 0)
      BOOST_LOG_TRIVIAL(info) << "  ============= Event " << event_number << " =============";

  } else {
    BOOST_LOG_TRIVIAL(info) << "------- Write flag set to false -------";
  }
}

void B2EventAction::DrawEvent(const G4Event *p_event,
                              const std::vector<B2ScintillatorHit *> &hits,
                              const std::vector<B2EmulsionHit *> &emulsion_hits) {

  auto *vis = G4VVisManager::GetConcreteInstance();
  if (vis) {

    for (auto const &hit: hits) {
      hit->Draw();
    }
    for (auto const &emulsion_hit: emulsion_hits) {
      emulsion_hit->Draw();
    }
    G4int event_id = p_event->GetEventID();

    // get number of stored trajectories
    G4TrajectoryContainer *p_trajectory_container = p_event->GetTrajectoryContainer();
    std::size_t num_trajectories = 0;
    if (p_trajectory_container) {
      num_trajectories = p_trajectory_container->entries();
      BOOST_LOG_TRIVIAL(debug) << num_trajectories << " trajectories stored in event " << event_id;
    } else {
      BOOST_LOG_TRIVIAL(debug) << "No trajectories found in event " << event_id;
    }

    for (std::size_t i = 0; i < num_trajectories; i++) {
      auto *trj = (G4Trajectory *) (*(p_event->GetTrajectoryContainer()))[i];
      if (trj->GetParentID() == 0) {
        // primary particles created at neutrino interaction point have parent ID zero
        trj->G4Trajectory::DrawTrajectory();
      }
    }

    // Draw vertex of neutrino interactions
    auto it = run_action_->GetSpillSummary().BeginTrueEvent();
    while (auto *event = it.Next()) {
      G4ThreeVector position(root_v_to_geant_v(event->GetPrimaryVertex().GetAbsolutePosition().GetValue()));
      G4Square square(position);
      square.SetScreenSize(100);
      square.SetFillStyle(G4Square::filled);
      G4Colour colour(G4Colour::White());
      G4VisAttributes attribs(colour);
      square.SetVisAttributes(attribs);
      vis->Draw(square);
    }
  }
}

std::size_t B2EventAction::CollectScintillatorHits(const G4Event *p_event, std::vector<B2ScintillatorHit *> &hits) {

  G4int event_id = p_event->GetEventID();

  // Get hit collections
  G4SDManager *p_sd_manager = G4SDManager::GetSDMpointer();
  G4HCofThisEvent *p_hit_container = p_event->GetHCofThisEvent();
  if (p_hit_container && p_sd_manager) {
    BOOST_LOG_TRIVIAL(debug) << p_hit_container->GetNumberOfCollections()
                             << " hit collections in event " << event_id;
  } else {
    BOOST_LOG_TRIVIAL(debug) << "no hits in this events. nothing to do!";
    hits.clear();
    return 0;
  }
  G4int hlayer_id = p_sd_manager->GetCollectionID("hlayerHitCollection");
  G4int vlayer_id = p_sd_manager->GetCollectionID("vlayerHitCollection");
  G4int veto_id = p_sd_manager->GetCollectionID("vetoHitCollection");
  auto *hlayer_hits_collection = (B2HitsCollection *) p_hit_container->GetHC(hlayer_id);
  auto *vlayer_hits_collection = (B2HitsCollection *) p_hit_container->GetHC(vlayer_id);
  auto *veto_hits_collection = (B2HitsCollection *) p_hit_container->GetHC(veto_id);
  std::size_t num_hits_vlayer = 0;
  std::size_t num_hits_hlayer = 0;
  std::size_t num_hits_veto = 0;
  if (hlayer_hits_collection) num_hits_hlayer = hlayer_hits_collection->entries();
  if (vlayer_hits_collection) num_hits_vlayer = vlayer_hits_collection->entries();
  if (veto_hits_collection) num_hits_veto = veto_hits_collection->entries();
  BOOST_LOG_TRIVIAL(debug) << num_hits_vlayer << " hits in the vlayer";
  BOOST_LOG_TRIVIAL(debug) << num_hits_hlayer << " hits in the hlayer";
  BOOST_LOG_TRIVIAL(debug) << num_hits_veto << " hits in the veto";

  //////// Concatenate all hits //////////
  hits.reserve(num_hits_hlayer + num_hits_vlayer + num_hits_veto);
  if (hlayer_hits_collection) {
    auto *vec = hlayer_hits_collection->GetVector();
    hits.insert(hits.begin(), vec->begin(), vec->end());
  }
  if (vlayer_hits_collection) {
    auto *vec = vlayer_hits_collection->GetVector();
    hits.insert(hits.end(), vec->begin(), vec->end());
  }
  if (veto_hits_collection) {
    auto *vec = veto_hits_collection->GetVector();
    hits.insert(hits.end(), vec->begin(), vec->end());
  }

  return hits.size();
}


void B2EventAction::CreateHitSummary(B2ScintillatorHit *hit) {

  // WAGASCI plane/grid scintillator
  B2GridPlane grid = B2GridPlane::kPlaneScintillator;
  if (hit->GetDetectorId() == B2Detector::kWagasciUpstream ||
      hit->GetDetectorId() == B2Detector::kWagasciDownstream) {
    unsigned ignore;
    if (!B2Dimension::GetGridWgs(hit->GetSlot(), ignore, grid))
      BOOST_LOG_TRIVIAL(warning) << "Could not get grid/plane information for hit : " << hit;
  }

  // Get scintillator position
  TVector3 pos{B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE};
  if (!dimension_.get().GetPosition(hit->GetDetectorId(), hit->GetView(), hit->GetPlane(), hit->GetSlot(), pos))
    BOOST_LOG_TRIVIAL(warning) << "Failed to get position of hit";

  TVector3 err{B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE};
  if (!B2Dimension::GetError(hit->GetDetectorId(), hit->GetView(), hit->GetPlane(), hit->GetSlot(), err))
    BOOST_LOG_TRIVIAL(warning) << "Failed to get error on position of hit";

  // Create and fill hit summary
  auto &spill_summary = run_action_->GetSpillSummary();
  auto &hit_summary = spill_summary.AddHit();

  hit_summary.SetDetector(hit->GetDetectorId());
  hit_summary.SetScintillatorType(hit->GetScintillatorType());
  hit_summary.SetPlane(hit->GetPlane());
  hit_summary.SetTrueRelativePosition(geant_v_to_root_v(hit->GetRelativePosition()));
  hit_summary.SetTrueAbsolutePosition(geant_v_to_root_v(hit->GetAbsolutePosition()));
  if (hit->GetDetectorId() == B2Detector::kNinja) { // NINJA always has recon same as true in MC
    hit_summary.SetReconRelativePosition(geant_v_to_root_v(hit->GetRelativePosition()));
    hit_summary.SetReconAbsolutePosition(geant_v_to_root_v(hit->GetAbsolutePosition()));
  }
  hit_summary.SetEnergyDeposit(hit->GetEnergyDeposit());
  hit_summary.SetView(hit->GetView());
  hit_summary.SetPlaneGrid(grid);
  hit_summary.SetScintillatorPosition(B2Position(pos, err));
  hit_summary.SetTrueTimeNs(hit->GetTime());
  hit_summary.SetBunch(DEFAULT_MC_BUNCH_ID);

  // Proton module veto planes
  if (hit->GetDetectorId() == B2Detector::kProtonModule) {
    hit_summary.SetVeto(B2Dimension::GetVetoPlanePm(hit->GetPlane()));
  }

  // list readouts
  for (const auto &readout: detector_to_readouts(hit->GetDetectorId(), hit->GetScintillatorType(), hit->GetPlane())) {
    hit_summary.SetSlot(readout, hit->GetSlot());
    hit_summary.SetTimeNs(readout, hit->GetDelayTime(readout));
    hit_summary.SetHighGainPeu(readout, hit->GetHighGainPeu(readout));
    hit_summary.SetLowGainPeu(readout, hit->GetLowGainPeu(readout));
  }

  // In case there is a single event in the spill, assign all the spills to it
  if (spill_summary.GetNumTrueEvents() == 1) {
    auto *event_summary = spill_summary.BeginTrueEvent().Next();
    hit_summary.SetParentEvent(event_summary);
  } else {
    BOOST_LOG_TRIVIAL(warning) << "No events or more than one event found";
  }

  hit->SetB2HitSummary(&hit_summary);
}


void B2EventAction::AddHitsToTrackSummary(const B2ScintillatorHit *hit) {
  auto &spill_summary = run_action_->GetSpillSummary();
  auto *hit_summary = hit->GetB2HitSummary();

  // look for a track with the matching track ID.
  if (spill_summary.HasTrueTrack(hit->GetTrackId())) {

    auto &track_summary = spill_summary.GetTrueTrack(hit->GetTrackId());

    if (track_summary.GetParticlePdg() != hit->GetParticlePdgId())
      BOOST_LOG_TRIVIAL(debug) << "Particle of the track ("
                               << B2Pdg::Stringify(track_summary.GetParticlePdg())
                               << ") different from the one of the hit ("
                               << B2Pdg::Stringify(hit->GetParticlePdgId()) << ")";

    // add hit to the track
    track_summary.AddHit(hit_summary);

    // if the track has one and only one cluster, add the hit to the cluster too
    if (track_summary.GetNumClusters() == 1) {
      auto *cluster_summary = track_summary.BeginCluster().Next();
      cluster_summary->AddHit(hit_summary);
    } else {
      BOOST_LOG_TRIVIAL(warning) << "No single child clusters found for track with ID " << hit->GetTrackId();
    }
  } else {
    BOOST_LOG_TRIVIAL(debug) << "Track with ID " << hit->GetTrackId() << " not found";
  }
}

void B2EventAction::SetPrimaryVertexClosestHit() {
  auto &spill_summary = run_action_->GetSpillSummary();
  auto *event_summary = dynamic_cast<B2EventSummary *>(spill_summary.GetTrueEvents().First());
  auto &primary_vertex = event_summary->GetPrimaryVertex();
  // In case of multiple events per spill, the B2EventSummary::SearchClosestHit needs to be called
  auto *closest_hit = spill_summary.SearchClosestHit(primary_vertex.GetAbsolutePosition().GetValue(),
                                                     closest_distance_cut_);
  if (closest_hit)
    primary_vertex.SetClosestHit(closest_hit);
}

void B2EventAction::ProcessScintillatorHits(std::vector<B2ScintillatorHit *> &hits) {
  for (auto *hit: hits) {
    CreateHitSummary(hit);
    AddHitsToTrackSummary(hit);
    BOOST_LOG_TRIVIAL(debug) << "Hit summary : \n" << *hit->GetB2HitSummary();
  }
}

void B2EventAction::ProcessMichelElectrons() {
  B2MichelElectron michel_electron_searcher(run_action_->GetSpillSummary(), remove_invalid_michel_electrons_);
  if (michel_electron_searcher.SearchMichelElectronCandidates())
    BOOST_LOG_TRIVIAL(debug) << "Found Michel electron!";
}

void B2EventAction::RemoveEmptyTracks() {
  auto &spill_summary = run_action_->GetSpillSummary();
  std::vector<B2TrackSummary *> tracks_to_remove;
  tracks_to_remove.reserve(spill_summary.GetNumTrueTracks());
  auto i = spill_summary.BeginTrueTrack();
  while (auto *track_summary = i.Next()) {
    if (track_summary->GetTrackType() != B2TrackType::kPrimaryTrack && track_summary->GetNumHits() <= 0) {
      tracks_to_remove.push_back(track_summary);
    }
  }
  for (auto *track: tracks_to_remove) {
    spill_summary.RemoveTrueTrack(track, kTRUE);
  }
}

void B2EventAction::ProcessTracks() {
  auto &spill_summary = run_action_->GetSpillSummary();

  // look for a reference to the parent track inside the spill summary
  {
    auto i = spill_summary.BeginTrueTrack();
    while (auto *track_summary = i.Next()) {
      if (spill_summary.HasTrueTrack(track_summary->GetParentTrackId()))
        track_summary->SetParentTrack(spill_summary.GetTrueTrack(track_summary->GetParentTrackId()));
    }
  }

  // Check if the track is stopping inside one of the detectors or not
  {
    auto i = spill_summary.BeginTrueTrack();
    while (auto *track_summary = i.Next()) {
      Bool_t is_stopping = kFALSE;
      for (const auto &volume: DETECTOR_VOLUMES) {
        if (volume.second.IsAbsolutePointContained(track_summary->GetFinalPosition().GetValue())) {
          is_stopping = kTRUE;
          break;
        }
      }
      track_summary->SetIsStopping(is_stopping);
      BOOST_LOG_TRIVIAL(debug) << "Track summary : \n" << *track_summary << "\n";
    }
  }
}

void B2EventAction::ProcessClusters() {
  auto &spill_summary = run_action_->GetSpillSummary();

  // remove empty clusters
  {
    std::vector<B2ClusterSummary *> clusters_to_remove;
    clusters_to_remove.reserve(spill_summary.GetNumTrueClusters());
    auto i = spill_summary.BeginTrueCluster();
    while (auto *cluster_summary = i.Next()) {
      if (cluster_summary->GetNumHits() <= 0) {
        clusters_to_remove.push_back(cluster_summary);
      }
    }
    for (auto *cluster: clusters_to_remove) {
      spill_summary.RemoveTrueCluster(cluster);
    }
  }

  // loop over all the clusters
  auto i = spill_summary.BeginTrueCluster();
  while (auto *cluster_summary = i.Next()) {
    // look for a reference to the parent track
    if (spill_summary.HasTrueTrack(cluster_summary->GetParentTrackId()))
      cluster_summary->SetParentTrack(spill_summary.GetTrueTrack(cluster_summary->GetParentTrackId()));
    BOOST_LOG_TRIVIAL(debug) << "Cluster summary : \n" << *cluster_summary << "\n";
  }
}

#ifdef NINJA

void B2EventAction::AddEmulsionsToTrackSummary(const B2EmulsionHit *emulsion_hit,
                                               B2EmulsionSummary &emulsion_summary) {
  auto &spill_summary = run_action_->GetSpillSummary();

  // look for a track with the matching track ID
  if (spill_summary.HasTrueTrack(emulsion_hit->GetTrackId())) {
    auto &track_summary = spill_summary.GetTrueTrack(emulsion_hit->GetTrackId());
    if (track_summary.GetParticlePdg() != emulsion_hit->GetParticlePdgId())
      BOOST_LOG_TRIVIAL(debug) << "Particle of the track ("
                               << B2Pdg::Stringify(track_summary.GetParticlePdg())
                               << ") different from the one of the hit ("
                               << B2Pdg::Stringify(emulsion_hit->GetParticlePdgId()) << ")";
    // add emulsion to the track TODO
    emulsion_summary.SetParentTrack(track_summary);
    emulsion_summary.SetParentTrackId(emulsion_hit->GetTrackId());
    //track_summary.AddEmulsion(emulsion_summary, kFALSE);
  } else {
    BOOST_LOG_TRIVIAL(debug) << "Track with ID " << emulsion_hit->GetTrackId() << " not found";
  }
}

void B2EventAction::ProcessEmulsionHits(const std::vector<B2EmulsionHit *> &emulsion_hits) {

  G4int track_id_tmp_ = B2_NON_INITIALIZED_VALUE;
  G4int emulsion_id_tmp_ = B2_NON_INITIALIZED_VALUE;
  const B2EmulsionHit *emulsion_hit_up_, *emulsion_hit_down_;
  G4bool found_up = false, found_down = false;
  // Track id and emulsion id is assigned sequentially!!
  for (auto const *emulsion_hit : emulsion_hits) { 
    G4int track_id_ = emulsion_hit->GetTrackId();
    G4int emulsion_id_ = emulsion_hit->GetEmulsionId();
    B2EmulsionLayer emulsion_layer = emulsion_hit->GetEmulsionLayer();
    emulsion_id_ -= (int)emulsion_layer;
    if ((track_id_tmp_ != track_id_) ||
  (emulsion_id_tmp_ != emulsion_id_)) {
      found_up = false;
      found_down = false;
    }
    track_id_tmp_ = track_id_;
    emulsion_id_tmp_ = emulsion_id_;

    switch (emulsion_layer) {
      case kUpstreamGel :
        emulsion_hit_up_ = emulsion_hit;
        found_up = true;
        break;
      case kDownstreamGel :
        emulsion_hit_down_ = emulsion_hit;
        found_down = true;
        break;
    }

    if (found_up && found_down) {
      if (emulsion_hit_up_->GetEmulsionType() != B2EmulsionType::kSSS) { // ECC and Shifter films are applied z difference cut
  if (emulsion_hit_up_->GetAbsolutePrePosition().getZ() < emulsion_hit_up_->GetAbsolutePostPosition().getZ() &&
      std::fabs(std::fabs(emulsion_hit_down_->GetAbsolutePrePosition().getZ() - emulsion_hit_up_->GetAbsolutePostPosition().getZ()) / NINJA_BASE_LAYER_THICK - 1.) < 1.e-9) {
    auto &emulsion_summary = CreateEmulsionSummary(emulsion_hit_up_, emulsion_hit_down_);
    AddEmulsionsToTrackSummary(emulsion_hit_up_, emulsion_summary);
    BOOST_LOG_TRIVIAL(debug) << "Emulsion summary : \n" << emulsion_summary;
  } else if (emulsion_hit_up_->GetAbsolutePrePosition().getZ() >= emulsion_hit_up_->GetAbsolutePostPosition().getZ() &&
     std::fabs(std::fabs(emulsion_hit_up_->GetAbsolutePrePosition().getZ() - emulsion_hit_down_->GetAbsolutePostPosition().getZ()) / NINJA_BASE_LAYER_THICK - 1.) < 1.e-9) {
    auto &emulsion_summary = CreateEmulsionSummary(emulsion_hit_up_, emulsion_hit_down_);
    AddEmulsionsToTrackSummary(emulsion_hit_up_, emulsion_summary);
    BOOST_LOG_TRIVIAL(debug) << "Emulsion summary : \n" << emulsion_summary;
  }
      } else { // Side SS films are not PRa interest for now
  auto &emulsion_summary = CreateEmulsionSummary(emulsion_hit_up_, emulsion_hit_down_);
  AddEmulsionsToTrackSummary(emulsion_hit_up_, emulsion_summary);
  BOOST_LOG_TRIVIAL(debug) << "Emulsion summary : \n" << emulsion_summary;
  BOOST_LOG_TRIVIAL(debug) << "Side SS tangent is not correctly applied";
      }
      found_up = false;
      found_down = false;
    }
  }
}

B2EmulsionSummary &B2EventAction::CreateEmulsionSummary(const B2EmulsionHit *emulsion_hit_up,
                                                        const B2EmulsionHit *emulsion_hit_down) {

  auto &spill_summary = run_action_->GetSpillSummary();
  auto &emulsion_summary = spill_summary.AddEmulsion();

  // Position, angle
  G4ThreeVector absolute_pos, film_pos, tangent;
  if (emulsion_hit_up->GetAbsolutePrePosition().getZ() <
      emulsion_hit_up->GetAbsolutePostPosition().getZ()) { // forward
    absolute_pos = emulsion_hit_up->GetAbsolutePostPosition();
    film_pos = emulsion_hit_up->GetFilmPostPosition();
    tangent = (emulsion_hit_down->GetAbsolutePrePosition()
               - emulsion_hit_up->GetAbsolutePostPosition())
              / NINJA_BASE_LAYER_THICK;
  } else { // backward
    absolute_pos = emulsion_hit_up->GetAbsolutePrePosition();
    film_pos = emulsion_hit_up->GetFilmPrePosition();
    tangent = (emulsion_hit_up->GetAbsolutePrePosition()
               - emulsion_hit_down->GetAbsolutePostPosition())
              / NINJA_BASE_LAYER_THICK;
  }

  emulsion_summary.SetAbsolutePosition(geant_v_to_root_v(absolute_pos));
  emulsion_summary.SetFilmPosition(geant_v_to_root_v(film_pos));
  emulsion_summary.SetTangent(geant_v_to_root_v(tangent));
  if (emulsion_hit_up->GetEmulsionType() == B2EmulsionType::kECC) {
    if (emulsion_hit_up->GetPlateId() == 1 ||
  emulsion_hit_up->GetPlateId() == 3) // upstream of film
      film_pos.setZ(-(NINJA_FILM_THICK));
    else if (emulsion_hit_up->GetPlateId() == 2) // upstream of acryl
      film_pos.setZ(-(NINJA_FILM_THICK + NINJA_SS_AC_THICK));
    else if (emulsion_hit_up->GetPlateId() < 15) // iron ECC
      film_pos.setZ(-(NINJA_FILM_THICK + NINJA_IRON_LAYER_THICK));
    else if (emulsion_hit_up->GetPlateId() == 15) // b/w iron & water ECCs
      film_pos.setZ(-(NINJA_FILM_THICK + 2 * NINJA_ENV_THICK));
    else if (emulsion_hit_up->GetPlateId() % 2 == 0) // upstream of iron
      film_pos.setZ(-(NINJA_FILM_THICK + NINJA_IRON_LAYER_THICK));
    else if (emulsion_hit_up->GetPlateId() % 2 == 1) // upstream of water
      film_pos.setZ(-(NINJA_FILM_THICK + 2 * NINJA_ENV_THICK + NINJA_WATER_LAYER_THICK));
  }
  emulsion_summary.SetFilmPositionInDownCoordinate(geant_v_to_root_v(film_pos));
  emulsion_summary.SetTangentInDownCoordinate(geant_v_to_root_v(tangent));

  // Momentum
  G4ThreeVector momentum;
  momentum = (emulsion_hit_up->GetMomentum() + emulsion_hit_down->GetMomentum()) / 2.;
  emulsion_summary.SetMomentum(geant_v_to_root_v(momentum));

  // Energy deposit
  emulsion_summary.SetEdepSum(emulsion_hit_up->GetEnergyDeposit() +
                              emulsion_hit_down->GetEnergyDeposit());
  emulsion_summary.SetEdepDiff(emulsion_hit_up->GetEnergyDeposit() -
                               emulsion_hit_down->GetEnergyDeposit());

  // Film ID
  emulsion_summary.SetFilmType(emulsion_hit_up->GetEmulsionType());
  emulsion_summary.SetEcc(emulsion_hit_up->GetEccId());
  emulsion_summary.SetPlate(emulsion_hit_up->GetPlateId());

  return emulsion_summary;
}

std::size_t B2EventAction::CollectEmulsionHits(const G4Event *p_event, std::vector<B2EmulsionHit *> &emulsion_hits) {

  G4int event_id = p_event->GetEventID();

  //Get hit collections
  G4SDManager *p_sd_manager = G4SDManager::GetSDMpointer();
  G4HCofThisEvent *p_hit_container = p_event->GetHCofThisEvent();
  BOOST_LOG_TRIVIAL(debug) << "Message from B2EventAction::CollectEmulsionHits()";
  if (p_hit_container && p_sd_manager) {
    BOOST_LOG_TRIVIAL(debug) << p_hit_container->GetNumberOfCollections()
                             << " hit collections in event " << event_id;
  } else {
    BOOST_LOG_TRIVIAL(debug) << "no hits in this event. nothing to do!";
    emulsion_hits.clear();
    return 0;
  }
  G4int emulsion_id = p_sd_manager->GetCollectionID("emulsionHitCollection");
  auto *emulsion_hits_collection = (B2EmulsionHitsCollection *) p_hit_container->GetHC(emulsion_id);
  G4int num_hits_emulsion = 0;
  if (emulsion_hits_collection) num_hits_emulsion = emulsion_hits_collection->entries();
  BOOST_LOG_TRIVIAL(debug) << num_hits_emulsion << " hits in the emulsion films";

  //////// Concatenate all emulsion hits //////////
  emulsion_hits.reserve(num_hits_emulsion);
  if (emulsion_hits_collection) {
    auto *vec = emulsion_hits_collection->GetVector();
    emulsion_hits.insert(emulsion_hits.begin(), vec->begin(), vec->end());
  }

  return emulsion_hits.size();

}

#endif
