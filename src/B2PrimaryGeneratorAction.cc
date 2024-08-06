#include "B2PrimaryGeneratorAction.hh"

// BOOST includes
#include <boost/log/trivial.hpp>
#include <boost/any.hpp>

// Geant4 includes
#include <G4RunManager.hh>
#include <G4Event.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>

// project includes
#include "B2DetectorConstruction.hh"
#include "B2RunAction.hh"
#include "B2Neut.hh"
#include "B2EventSummary.hh"
#include "B2VertexSummary.hh"
#include "B2Converters.hh"
#include "B2RandomVertexZ.hh"
#include "B2CosmicMuon.hh"
#include "B2Enum.hh"

#define any boost::any_cast

B2PrimaryGeneratorAction::B2PrimaryGeneratorAction(B2Neut &neut,
                                                   B2RunAction *rac,
                                                   B2EventAction *evt,
                                                   const B2Settings &settings)
    : particle_gun_(1), // num_particles = 1
      particle_table_(G4ParticleTable::GetParticleTable()),
      p_run_action_(rac),
      p_event_action_(evt),
      neut_(neut),
      neutrino_interaction_module_(any<B2Detector>(settings.At(B2Settings::NeutrinoInteractionSettings))),
      neutrino_interaction_material_(any<B2Material>(settings.At(B2Settings::NeutrinoInteractionMaterial))),
      neutrino_flavor_settings_(any<B2NeutrinoFlavor>(settings.At(B2Settings::NeutrinoFlavorSettings))),
      cosmic_muons_(any<bool>(settings.At(B2Settings::CosmicMuons))),
      pencil_beam_(any<bool>(settings.At(B2Settings::PencilBeam))),
      pencil_beam_random_direction_(any<bool>(settings.At(B2Settings::PencilBeamRandomDirection))),
      pencil_beam_particle_pdg_(any<PDG_t>(settings.At(B2Settings::PencilBeamParticlePdg))),
      pencil_beam_position_(any<double>(settings.At(B2Settings::PencilBeamX)),
                            any<double>(settings.At(B2Settings::PencilBeamY)),
                            any<double>(settings.At(B2Settings::PencilBeamZ))),
      pencil_beam_direction_(0, 0, 1),
      pencil_beam_momentum_(any<double>(settings.At(B2Settings::PencilBeamMomentum))),
      offset_x_(POSITION_OFFSET_X.at(neutrino_interaction_module_)),
      offset_y_(POSITION_OFFSET_Y.at(neutrino_interaction_module_)),
      offset_z_(POSITION_OFFSET_Z.at(neutrino_interaction_module_)),
      ninja_kink_study_(any<bool>(settings.At(B2Settings::NinjaKinkStudy))){
  const auto angle_top_radiants = CLHEP::pi * any<double>(settings.At(B2Settings::PencilBeamAngleTop)) / 180;
  const auto angle_side_radiants = CLHEP::pi * any<double>(settings.At(B2Settings::PencilBeamAngleSide)) / 180;
  pencil_beam_direction_.RotateX(angle_top_radiants);
  pencil_beam_direction_.RotateY(angle_side_radiants);
  p_run_action_->CloneNEUTTree(neut_.get().GetNEUTTree());
  if (ninja_kink_study_) {
    kink_hist_file_ = new TFile(any<std::string>(settings.At(B2Settings::KinkFilePath)).c_str(), "read");
    kink_momentum_hist_ = (TH1D*)kink_hist_file_->Get("kink_momentum_hist_");
    kink_ax_hist_ = (TH1D*)kink_hist_file_->Get("kink_ax_hist_");
    kink_ay_hist_ = (TH1D*)kink_hist_file_->Get("kink_ay_hist_");
  }
}

void B2PrimaryGeneratorAction::GeneratePrimaries(G4Event *g4_event) {

  BOOST_LOG_TRIVIAL(debug) << "----- GeneratePrimaries -----";

  if (cosmic_muons_) {

    // ===================== Cosmic muon mode =====================

    GenerateCosmicMuon(g4_event);

  } else if (pencil_beam_) {

    // ===================== Pencil beam mode =======================

    GeneratePencilBeam(g4_event);

  } else if (ninja_kink_study_) {

    // ===================== NINJA kink study mode =======================

    GenerateNinjaKinkBeam(g4_event);

  } else {

    // ===================== Neutrino mode =======================

    GenerateNeutrino(g4_event);
  }
}

void B2PrimaryGeneratorAction::GenerateNeutrino(G4Event *g4_event) {

  BOOST_LOG_TRIVIAL(debug) << "Generating primary vertex for beam neutrino";

  interaction_vertex_.Clear("C");

  // Read an event from NEUT and set the relative position of the vertex
  const NeutEvent *p_neut_event = ReadNeutEvent();
  if (p_neut_event == nullptr)
    return;

  auto &spill_summary = p_run_action_->GetSpillSummary();
  spill_summary.GetBeamSummary().SetWagasciSpillNumber(p_neut_event->primary.event_number);
  spill_summary.GetBeamSummary().SetBsdSpillNumber(p_neut_event->primary.event_number);

  // Add the vertex information to the output TTree
  auto &primary_vertex = spill_summary.AddTrueVertex();
  primary_vertex.SetRelativePosition(interaction_vertex_);

  // Set detector offset (change the vertex reference frame from the
  // center-of-detector one to the absolute one, aka the world coordinate system)
  interaction_vertex_.SetX(interaction_vertex_.X() + offset_x_);
  interaction_vertex_.SetY(interaction_vertex_.Y() + offset_y_);
  interaction_vertex_.SetZ(interaction_vertex_.Z() + offset_z_);
  primary_vertex.SetAbsolutePosition(interaction_vertex_);

  if ( neutrino_interaction_module_ == B2Detector::kNinja ) {
    primary_vertex.SetPlane(1000 * GetEcc(interaction_vertex_) + GetEccPlate(interaction_vertex_.Z()));
  }

  if (p_neut_event->neutrino.primary_particle.particle_id !=
      B2Neut::ProductionMode2PdgId(p_neut_event->neutrino.production_mode)) {
    BOOST_LOG_TRIVIAL(debug) << "Neutrino flavor mismatch! "
                             << B2Pdg::Stringify(p_neut_event->neutrino.primary_particle.particle_id) << " "
                             << p_neut_event->neutrino.primary_particle.particle_id << " != "
                             << B2Pdg::Stringify(B2Neut::ProductionMode2PdgId(p_neut_event->neutrino.production_mode));
  }

  primary_vertex.SetIncomingParticlePdg(p_neut_event->neutrino.primary_particle.particle_id);
  primary_vertex.SetTotalEnergy(p_neut_event->neutrino.energy * GeV);
  primary_vertex.SetDetector(neutrino_interaction_module_);
  primary_vertex.SetTotalCrossSection(p_neut_event->neut_crs.total_cross_section);
  primary_vertex.SetNormalization(p_neut_event->neutrino.normalization);
  primary_vertex.SetInteractionType(static_cast<B2InteractionMode>(p_neut_event->primary.mode));
  primary_vertex.SetInteractionMaterial(p_neut_event->target_info.GetMaterial());
  auto neutrino_index = p_neut_event->primary.GetIncomingNeutrinoIndex();
  primary_vertex.SetMomentum(c_array_to_root_v(p_neut_event->primary.momentum[neutrino_index]) * GeV);

  // Add the event information to the output TTree
  auto &event = spill_summary.AddTrueEvent();
  event.SetEventType(B2EventType::kBeamNeutrinoEvent);
  event.SetPrimaryVertex(primary_vertex);

  // particle gun settings
  particle_gun_.SetParticlePosition(root_v_to_geant_v(interaction_vertex_));

  for (int ipart = 0; ipart < p_neut_event->secondary.num_particles; ipart++) {

    if (p_neut_event->secondary.tracking_flag.at(ipart) == SecondaryParticles::TrackingFlag::kExitNucleus) {

      auto *particle = particle_table_->FindParticle(p_neut_event->secondary.particle_id[ipart]);
      particle_gun_.SetParticleDefinition(particle);
      particle_gun_.SetParticleMomentumDirection(c_array_to_geant_v(p_neut_event->secondary.momentum[ipart]) /
                                                 p_neut_event->secondary.abs_momentum.at(ipart));
      G4double mass = particle->GetPDGMass();
      G4double momentum = p_neut_event->secondary.abs_momentum[ipart] * MeV;
      G4double energy = momentum_mass_to_kinetic_energy(momentum, mass);
      particle_gun_.SetParticleEnergy(energy);
      particle_gun_.SetParticleTime(0.0 * ns);
      particle_gun_.GeneratePrimaryVertex(g4_event);

    } // end of if
  } // end of for loop

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex information";
  BOOST_LOG_TRIVIAL(debug) << primary_vertex;
  BOOST_LOG_TRIVIAL(debug) << "Event information";
  BOOST_LOG_TRIVIAL(debug) << event;

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex for beam neutrino successfully generated";
}

const NeutEvent *B2PrimaryGeneratorAction::ReadNeutEvent() {
  const NeutEvent *p_neut_event;
  bool have_interaction = false;

  // Read NEUT events until we find one that satisfies the user
  // settings and selection criteria
  while (!have_interaction) {
    if (neut_.get().ReadNextEvent() == B2InteractionMode::MODE_ERROR) {
      BOOST_LOG_TRIVIAL(warning) << "Aborting run : NEUT reader returned code "
                                 << B2InteractionMode::MODE_ERROR;
      BOOST_LOG_TRIVIAL(warning) << "This warning is harmless only if it happens when";
      BOOST_LOG_TRIVIAL(warning) << "there are no more events in the NEUT file to be processed";
      G4RunManager *runManager = G4RunManager::GetRunManager();
      p_event_action_->UnsetWriteFlag();
      runManager->AbortRun(true);
      return nullptr;
    }

    // Get NEUT event handle
    p_neut_event = &neut_.get().GetEvent();
    BOOST_LOG_TRIVIAL(debug) << "Read event " << p_neut_event->primary.event_number << " from NEUT file";

    // Extract the neutrino flavor and PDG ID from NEUT input
    auto neutrino_flavor = B2Neut::ProductionMode2NeutrinoFlavor(p_neut_event->neutrino.production_mode);
    auto neutrino_pdg = p_neut_event->neutrino.primary_particle.particle_id;

    // Check that the neutrino flavor generated by NEUT is the same as the one requested by the user,
    // otherwise read the next event
    if (neutrino_flavor != neutrino_flavor_settings_) {
      BOOST_LOG_TRIVIAL(debug) << "NEUT neutrino flavor (" << B2Pdg::Stringify(neutrino_pdg)
                               << ") is different from requested one ("
                               << B2Pdg::Stringify(B2Pdg::NeutrinoFlavor2PdgId(neutrino_flavor))
                               << "). Skipping event.";
    } else {
      // Extract vertex X and Y coordinates from NEUT input
      if (neutrino_interaction_module_ == B2Detector::kWallMrdNorth ||
          neutrino_interaction_module_ == B2Detector::kWallMrdSouth) {
        interaction_vertex_.SetXYZ(0, p_neut_event->neutrino.y * cm, p_neut_event->neutrino.x * cm); // cm
      } else {
        interaction_vertex_.SetXYZ(p_neut_event->neutrino.x * cm, p_neut_event->neutrino.y * cm, 0); // cm
      }

      // To enlarge the statistics, after a naive study of the flux,
      // the vertex X and Y coordinates can be also randomly generated
      // inside ECC5 detector cross section if necessary
      // Comment out this section for 9 ECC analysis
      // 2022.06.17 T. Odagawa

      if (neutrino_interaction_module_ == B2Detector::kNinja) {
	double x = -12.5 + 25. * G4UniformRand();
	double y = -12.5 + 25. * G4UniformRand();
	x += NINJA_FV_IRON_POS_X / 10.; // center of emulsion films in ECC5 (mm->cm)
	y += NINJA_FV_IRON_POS_Y / 10.;
	interaction_vertex_.SetXYZ(x * cm, y * cm, 0.);
      }

      // Randomly generate the vertex Z coordinate
      // Decide Vertex X for only WallMRD
      have_interaction = B2RandomVertexZ::GenerateRandomVertexZ(neutrino_interaction_module_,
                                                                interaction_vertex_,
                                                                neutrino_interaction_material_);
    }

    // Count the number of total NEUT events, effectively selected events and discarded events
    if (!have_interaction) {
      BOOST_LOG_TRIVIAL(debug) << "Interaction vertex is outside the detector active area "
                                  "or in an region of lesser relative mass (only proton module)";
      BOOST_LOG_TRIVIAL(debug) << "Skipping this event";
      p_run_action_->number_discarded_events++;
    } else {
      p_run_action_->number_used_events++;
    }
    p_run_action_->number_simulated_events++;
  } // end while loop
  return p_neut_event;
}

void B2PrimaryGeneratorAction::GenerateCosmicMuon(G4Event *g4_event) {

  BOOST_LOG_TRIVIAL(debug) << "Generating primary vertex for cosmic muon";

  interaction_vertex_.Clear("C");

  auto &spill_summary = p_run_action_->GetSpillSummary();
  spill_summary.GetBeamSummary().SetWagasciSpillNumber(g4_event->GetEventID());
  spill_summary.GetBeamSummary().SetBsdSpillNumber(g4_event->GetEventID());

  // Generate a cosmic muon (inside the B2CosmicMuon constructor)
  B2CosmicMuon muon;

  // Add the vertex information to the output TTree
  auto &primary_vertex = p_run_action_->GetSpillSummary().AddTrueVertex();
  primary_vertex.SetIncomingParticlePdg(PDG_t::kMuonMinus);
  primary_vertex.SetDetector(B2Detector::kUnknownDetector);
  primary_vertex.SetTotalEnergy(B2Energy(muon.GetEnergy()));
  primary_vertex.SetMomentum(geant_v_to_root_v(muon.GetMomentum()));
  primary_vertex.SetRelativePosition(geant_v_to_root_v(muon.GetPosition())); // TODO absolute position?
  primary_vertex.SetInteractionType(B2InteractionMode::MODE_COSMIC_MUON);
  primary_vertex.SetIsInsideFiducialVolume(kFALSE);

  // Add the event information to the output TTree
  auto &event = p_run_action_->GetSpillSummary().AddTrueEvent();
  event.SetEventType(B2EventType::kCosmicSandMuonEvent);
  event.SetPrimaryVertex(primary_vertex);

  // particle gun settings
  particle_gun_.SetParticleDefinition(particle_table_->FindParticle(PDG_t::kMuonMinus));
  particle_gun_.SetParticleEnergy(muon.GetEnergy());
  particle_gun_.SetParticleMomentumDirection(muon.GetDirection());
  particle_gun_.SetParticlePosition(muon.GetPosition());
  particle_gun_.SetParticleTime(0.0 * ns);
  particle_gun_.GeneratePrimaryVertex(g4_event);

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex information";
  BOOST_LOG_TRIVIAL(debug) << primary_vertex;
  BOOST_LOG_TRIVIAL(debug) << "Event information";
  BOOST_LOG_TRIVIAL(debug) << event;

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex for cosmic muon successfully generated";
}

void B2PrimaryGeneratorAction::GeneratePencilBeam(G4Event *g4_event) {

  BOOST_LOG_TRIVIAL(debug) << "Generating pencil beam";

  interaction_vertex_.Clear("C");

  auto &spill_summary = p_run_action_->GetSpillSummary();
  spill_summary.GetBeamSummary().SetWagasciSpillNumber(g4_event->GetEventID());
  spill_summary.GetBeamSummary().SetBsdSpillNumber(g4_event->GetEventID());

  auto *particle = particle_table_->FindParticle(pencil_beam_particle_pdg_);
  G4double mass = particle->GetPDGMass();
  G4double total_energy = momentum_mass_to_total_energy(pencil_beam_momentum_, mass);
  G4double kinetic_energy = momentum_mass_to_kinetic_energy(pencil_beam_momentum_, mass);

  // Add the vertex information to the output TTree
  auto &primary_vertex = p_run_action_->GetSpillSummary().AddTrueVertex();
  primary_vertex.SetIncomingParticlePdg(pencil_beam_particle_pdg_);
  primary_vertex.SetTotalEnergy(total_energy);
  primary_vertex.SetDetector(B2Detector::kUnknownDetector);
  primary_vertex.SetMomentum(pencil_beam_direction_ * pencil_beam_momentum_);
  primary_vertex.SetAbsolutePosition(pencil_beam_position_);
  primary_vertex.SetInteractionType(B2InteractionMode::MODE_PENCIL_BEAM);
  primary_vertex.SetIsInsideFiducialVolume(kFALSE);

  // Add the event information to the output TTree
  auto &event = p_run_action_->GetSpillSummary().AddTrueEvent();
  event.SetEventType(B2EventType::kPencilBeamEvent);
  event.SetPrimaryVertex(primary_vertex);

  // particle gun settings
  particle_gun_.SetParticleDefinition(particle);
  if (!pencil_beam_random_direction_)
    particle_gun_.SetParticleMomentumDirection(root_v_to_geant_v(pencil_beam_direction_));
  else {
    random_direction_.SetXYZ(0, 0, 1);
    double random_top_angle = -20. + G4UniformRand() * 40;
    double random_side_angle = -20 + G4UniformRand() * 40;
    double random_angle_top_radiants = CLHEP::pi * (random_top_angle) / 180;
    double random_angle_side_radiants = CLHEP::pi * (random_side_angle) / 180;
    random_direction_.RotateY(random_angle_top_radiants);
    random_direction_.RotateX(random_angle_side_radiants);
    particle_gun_.SetParticleMomentumDirection(root_v_to_geant_v(random_direction_));
  }
  particle_gun_.SetParticleEnergy(kinetic_energy);
  particle_gun_.SetParticlePosition(root_v_to_geant_v(pencil_beam_position_));
  particle_gun_.SetParticleTime(0.0 * ns);
  particle_gun_.GeneratePrimaryVertex(g4_event);

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex information";
  BOOST_LOG_TRIVIAL(debug) << primary_vertex;
  BOOST_LOG_TRIVIAL(debug) << "Event information";
  BOOST_LOG_TRIVIAL(debug) << event;

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex for pencil beam successfully generated";
}

void B2PrimaryGeneratorAction::GenerateNinjaKinkBeam(G4Event *g4_event) {

  BOOST_LOG_TRIVIAL(debug) << "Generate muon beam for NINJA kink study";

  interaction_vertex_.Clear("C");

  auto &spill_summary = p_run_action_->GetSpillSummary();
  spill_summary.GetBeamSummary().SetWagasciSpillNumber(g4_event->GetEventID());
  spill_summary.GetBeamSummary().SetBsdSpillNumber(g4_event->GetEventID());

  // Generate muon beam
  auto *particle = particle_table_->FindParticle(pencil_beam_particle_pdg_);
  G4double mass = particle->GetPDGMass();
  G4double beam_momentum_ = kink_momentum_hist_->GetRandom();
  G4double total_energy = momentum_mass_to_total_energy(beam_momentum_, mass);
  G4double kinetic_energy = momentum_mass_to_kinetic_energy(beam_momentum_, mass);

  // Add the vertex information to the output TTree
  auto &primary_vertex = p_run_action_->GetSpillSummary().AddTrueVertex();
  primary_vertex.SetIncomingParticlePdg(pencil_beam_particle_pdg_);
  primary_vertex.SetTotalEnergy(total_energy);
  primary_vertex.SetDetector(B2Detector::kUnknownDetector);
  random_direction_.SetXYZ(0, 0, 1);
  random_direction_.SetX(kink_ax_hist_->GetRandom());
  random_direction_.SetY(kink_ay_hist_->GetRandom());
  random_direction_ = (1./random_direction_.Mag()) * random_direction_;
  primary_vertex.SetMomentum(random_direction_ * beam_momentum_);
  pencil_beam_position_.SetX(-1500. + G4UniformRand() * 3000.);
  pencil_beam_position_.SetY(-1500. + G4UniformRand() * 3000.);
  primary_vertex.SetAbsolutePosition(pencil_beam_position_);
  primary_vertex.SetInteractionType(B2InteractionMode::MODE_NINJA_KINK_BEAM);
  primary_vertex.SetIsInsideFiducialVolume(kFALSE);

  // Add the event information to the output TTree
  auto &event = p_run_action_->GetSpillSummary().AddTrueEvent();
  event.SetEventType(B2EventType::kPencilBeamEvent);
  event.SetPrimaryVertex(primary_vertex);

  // particle gun settings
  particle_gun_.SetParticleDefinition(particle);
  particle_gun_.SetParticleMomentumDirection(root_v_to_geant_v(random_direction_));
  particle_gun_.SetParticleEnergy(kinetic_energy);
  particle_gun_.SetParticlePosition(root_v_to_geant_v(pencil_beam_position_));
  particle_gun_.SetParticleTime(0.0 * ns);
  particle_gun_.GeneratePrimaryVertex(g4_event);

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex information";
  BOOST_LOG_TRIVIAL(debug) << primary_vertex;
  BOOST_LOG_TRIVIAL(debug) << "Evnet information";
  BOOST_LOG_TRIVIAL(debug) << event;

  BOOST_LOG_TRIVIAL(debug) << "Primary vertex for NINJA kink study successfully generated";

}

int B2PrimaryGeneratorAction::GetEccPlate(G4double z_pos) {

  z_pos = z_pos - NINJA_POS_Z - NINJA_ECC_POS_Z;
  z_pos = z_pos - 0.5 * NINJA_DESIC_DEPTH
    + NINJA_DESIC_THICK
    + NINJA_ENV_THICK
    + NINJA_EMULSION_LAYER_THICK
    + NINJA_BASE_LAYER_THICK;

  if ( z_pos > -NINJA_EMULSION_LAYER_THICK
       - 14 * NINJA_FILM_THICK
       - 11 * NINJA_IRON_LAYER_THICK
       - NINJA_SS_AC_THICK
       - NINJA_ENV_THICK ) { // Iron ECC
    z_pos = z_pos + NINJA_EMULSION_LAYER_THICK
      + 3 * NINJA_FILM_THICK
      + NINJA_SS_AC_THICK; // iron most downstream position -> origin
    int film_id = (int)(-z_pos / (NINJA_FILM_THICK + NINJA_IRON_LAYER_THICK));
    z_pos = z_pos + film_id * (NINJA_FILM_THICK + NINJA_IRON_LAYER_THICK);
    if ( -NINJA_IRON_LAYER_THICK < z_pos &&
	 z_pos <= 0. ) {
      return film_id + 3;
    }
    else {
      throw std::runtime_error("Vertex is not correctly assigned");
    }
  } 
  else if ( z_pos > -NINJA_EMULSION_LAYER_THICK
	    - 132 * NINJA_FILM_THICK
	    - 58 * NINJA_WATER_LAYER_THICK
	    - (59 * 2 + 1) * NINJA_ENV_THICK
	    - 70 * NINJA_IRON_LAYER_THICK
	    - NINJA_SS_AC_THICK ) { // Water ECC
    z_pos = z_pos + NINJA_EMULSION_LAYER_THICK
      + 15 * NINJA_FILM_THICK
      + 11 * NINJA_IRON_LAYER_THICK
      + NINJA_SS_AC_THICK
      + 2 * NINJA_ENV_THICK; // iron most downstream in water ECC -> origin
    int unit_id = (int)(-z_pos / (2 * NINJA_FILM_THICK + NINJA_IRON_LAYER_THICK
				  + NINJA_WATER_LAYER_THICK + 2 * NINJA_ENV_THICK));
    z_pos = z_pos + unit_id * (2 * NINJA_FILM_THICK + NINJA_IRON_LAYER_THICK
			       + NINJA_WATER_LAYER_THICK + 2 * NINJA_ENV_THICK); // iron most downstream in one unit -> origin
    if ( -NINJA_IRON_LAYER_THICK < z_pos &&
	 z_pos <= 0. ) { // iron interaction
      return 2 * (unit_id + 8) - 1;
    }
    else if ( -NINJA_IRON_LAYER_THICK - NINJA_FILM_THICK - NINJA_WATER_LAYER_THICK - NINJA_ENV_THICK < z_pos &&
	      z_pos <= -NINJA_IRON_LAYER_THICK - NINJA_FILM_THICK - NINJA_ENV_THICK ) { // water interaction
      return 2 * (unit_id + 8);
    }
    else {
      throw std::runtime_error("Vertex is not correctly assigned");
    }      
  }
  else {
    throw std::runtime_error("Vertex is not correctly assigned");
  }    
}

int B2PrimaryGeneratorAction::GetEcc(TVector3 vertex_position) {
  vertex_position.SetX(vertex_position.X() - NINJA_POS_X - NINJA_ECC_POS_X);
  vertex_position.SetY(vertex_position.Y() - NINJA_POS_Y - NINJA_ECC_POS_Y);

  Int_t topid, sideid;

  if ( std::fabs(vertex_position.X() + NINJA_ECC_GAP_X) < 0.5 * NINJA_DESIC_WIDTH )
    topid = 0;
  else if ( std::fabs(vertex_position.X()) < 0.5 * NINJA_DESIC_WIDTH ) 
    topid = 1;
  else if ( std::fabs(vertex_position.X() - NINJA_ECC_GAP_X) < 0.5 * NINJA_DESIC_WIDTH )
    topid = 2;
  else
    throw std::runtime_error("Vertex position is not correctly assigned");

  if ( std::fabs(vertex_position.Y() - NINJA_ECC_GAP_Y) < 0.5 * NINJA_DESIC_HEIGHT )
    sideid = 0;
  else if ( std::fabs(vertex_position.Y()) < 0.5 * NINJA_DESIC_HEIGHT )
    sideid = 1;
  else if ( std::fabs(vertex_position.Y() + NINJA_ECC_GAP_Y) < 0.5 * NINJA_DESIC_HEIGHT )
    sideid = 2;
  else
    throw std::runtime_error("Vertex position is not correctly assigned");

  return 3 * sideid + topid;

}
