//#define WITH_G4VIS // G4Subtraction is not used for OpenGL visualization

#include "B2DetectorConstruction.hh"

// system includes
#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>

// BOOST includes
#include <boost/any.hpp>
#include <boost/log/trivial.hpp>
#include <G4UnionSolid.hh>
#include <B2EmulsionSensitiveDetector.hh>

// Geant4 includes
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4FieldManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"
#include "G4EllipticalTube.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#ifdef WITH_GDML
#include "G4GDMLParser.hh"
#endif

// project includes
#include "B2Const.hh"
#include "B2Configuration.hh"
#include "B2Settings.hh"
#include "B2Dimension.hh"
#include "B2MagneticFieldWrapper.hh"
#include "B2Enum.hh"
#include "B2Converters.hh"

B2DetectorConstruction::B2DetectorConstruction(const B2Settings &settings, const B2Dimension &dimension) :
    water_settings_(boost::any_cast<B2WaterSettings>(settings.At(B2Settings::WaterSettings))),
    magnetic_field_flag_(boost::any_cast<bool>(settings.At(B2Settings::MagneticField))),
    magfield_table_file_path_(boost::any_cast<std::string>(settings.At(B2Settings::GeometryDirPath))
                              + MAGFIELD_TABLE_FILE.string()),
#ifdef WITH_GDML
    output_gdml_file_path_(boost::any_cast<std::string>(settings.At(B2Settings::OutputGdmlFilePath))),
#endif
    dimension_(dimension) {

  // Initialise sensitive detectors
  veto_scintillators_ = new B2VetoSensitiveDetector("B2/vetoSD", dimension_);
  horizontal_scintillators_ = new B2HorizontalSensitiveDetector("B2/hlayerSD", dimension_);
  vertical_scintillators_ = new B2VerticalSensitiveDetector("B2/vlayerSD", dimension_);
  emulsion_sensitive_detector_ = new B2EmulsionSensitiveDetector("B2/emulsionSD");

  // Initialise materials
  DefineMaterial();

  // Initialise boxes
  DefineBoxes();

  // Initialise volumes
  DefinePosition();

  // Initialise NINJA volumes
  DefineNinjaPosition();

  // Initialise structural elements
  DefineStructures();

  // Initialise NINJA structural elements
  DefineNinjaStructures();

  // Initialize scintillator vertices
  DefineVertices();
}

G4VPhysicalVolume *B2DetectorConstruction::Construct() {

  SetVisibilityAttributes();

  auto b2_lv = ConstructHall();

  auto module_lv = ConstructModules(b2_lv);

  ConstructMaterials(module_lv);

  ConstructMagneticField();

#ifdef WITH_GDML
  if (!fs::exists(output_gdml_file_path_)) {
    G4GDMLParser parser;
    parser.Write(output_gdml_file_path_, world_pv_);
  }
#endif

  return world_pv_;
}

void B2DetectorConstruction::SetVisibilityAttributes() {

  // B2 hall
  hall_vis_att_ = new G4VisAttributes(G4Color::Brown());
  hall_vis_att_->SetForceWireframe(true); // only draw edges

  // B2 floor
  floor_vis_att_ = new G4VisAttributes(G4Color::Brown());
  floor_vis_att_->SetForceWireframe(true); // only draw edges

  // B2 pillar
  pillar_vis_att_ = new G4VisAttributes(G4Color::Brown());
  pillar_vis_att_->SetForceWireframe(true); // only draw edges

  // box
  box_vis_att_ = new G4VisAttributes(G4Color::White());
  box_vis_att_->SetVisibility(false); // do not draw

  // scintillators
  sci_vis_att_ = new G4VisAttributes(G4Color::Green());
  sci_vis_att_->SetForceWireframe(true); // only draw edges
  //sci_vis_att_->SetForceSolid(true); // only draw edges

  // iron
  iron_vis_att_ = new G4VisAttributes(G4Color::Magenta());
  iron_vis_att_->SetForceSolid(true); // opaque

  // veto
  veto_vis_att_ = new G4VisAttributes(G4Color(0., 0.6, 0.5)); // Azure
  veto_vis_att_->SetForceWireframe(true); // only draw edges

  // water
  water_vis_att_ = new G4VisAttributes(G4Colour::Blue());
  water_vis_att_->SetForceWireframe(true); // only draw edges

  // air
  air_vis_att_ = new G4VisAttributes(G4Colour::Red());
  air_vis_att_->SetForceWireframe(true); // only draw edges

  // SUS 304 (stainless steel)
  sus_vis_att_ = new G4VisAttributes(G4Colour::Grey());

  // Aluminum
  aluminum_vis_att_ = new G4VisAttributes(G4Colour::Brown());
  aluminum_vis_att_->SetForceWireframe(true); // only draw edges

  // PVC
  pvc_vis_att_ = new G4VisAttributes(G4Colour::Grey());
  pvc_vis_att_->SetForceWireframe(true);

  // Emulsion gel
  emulsion_vis_att_ = new G4VisAttributes(G4Color::Yellow());
  emulsion_vis_att_->SetForceSolid(true); // opaque

}

G4LogicalVolume *B2DetectorConstruction::ConstructHall() {

  // Rotation matrix definition
  auto *xrot = new G4RotationMatrix(G4ThreeVector(1, 0, 0), 90. * degree);

  // World volume
  auto *experimental_hall_box = new G4Box("Hall", world_box_.x(), world_box_.y(), world_box_.z());
  auto *world_lv = new G4LogicalVolume(experimental_hall_box, air_, "hall_log", nullptr, nullptr, nullptr);
  world_pv_ = new G4PVPlacement(nullptr, origin_, world_lv, "hall", nullptr, false, 0);

  // Hall dirt volume
  auto *hall_dirt_sld = new G4Tubs("halldirt", dirt_radius_min_, dirt_radius_max_, dirt_height_,
                                   dirt_s_phi_, dirt_d_phi_);
  auto *hall_dirt_lv = new G4LogicalVolume(hall_dirt_sld, concrete_, "HallDirt", nullptr, nullptr, nullptr);
  new G4PVPlacement(xrot, dirt_pos_, hall_dirt_lv, "HallDirt", world_lv, false, 0);
  hall_dirt_lv->SetVisAttributes(hall_vis_att_);

  // B2 floor
  auto *hall_dirt_floor = new G4Tubs("hallfloor", 0 * cm, dirt_radius_min_ - 1 * mm,
                                     0.5 * (dirt_height_ + floorup_), dirt_s_phi_, dirt_d_phi_);
  auto *hall_dirt_floor_lv = new G4LogicalVolume(hall_dirt_floor, concrete_, "HallDirtfloor", nullptr, nullptr,
                                                 nullptr);
  dirt_pos_.setY(dirt_pos_.y() - dirt_height_ + 0.5 * (dirt_height_ + floorup_));
  new G4PVPlacement(xrot, dirt_pos_, hall_dirt_floor_lv, "HallDirtfloor", world_lv, false, 0);
  hall_dirt_floor_lv->SetVisAttributes(floor_vis_att_);

  // B2 pillar
  auto *pillar_box = new G4Box("Pillar", pillar_box_.x(), pillar_box_.y(), pillar_box_.z());
  auto *pillar_lv = new G4LogicalVolume(pillar_box, concrete_, "Pillar", nullptr, nullptr, nullptr);
  new G4PVPlacement(nullptr, pillar_south_pos_, pillar_lv, "Pillar", world_lv, false, 0);
  new G4PVPlacement(nullptr, pillar_north_pos_, pillar_lv, "Pillar", world_lv, false, 0);
  pillar_lv->SetVisAttributes(pillar_vis_att_);

  //B2 hall box
  auto *b2_hall_box = new G4Box("B2Hall", b2_hall_box_.x(), b2_hall_box_.y(), b2_hall_box_.z());
  auto *b2_lv = new G4LogicalVolume(b2_hall_box, air_, "B2_log", nullptr, nullptr, nullptr);
  new G4PVPlacement(nullptr, b2_hall_pos_, b2_lv, "B2", world_lv, false, 0);
  b2_lv->SetVisAttributes(box_vis_att_);

  return b2_lv;
}

B2DetectorConstruction::B2LogicalVolumeMap B2DetectorConstruction::ConstructModules(G4LogicalVolume *b2_lv) {

  auto *pm_box = new G4Box("Proton_Module", pm_box_.x(), pm_box_.y(), pm_box_.z());
  auto *wagasci_box = new G4Box("WAGASCI_Module", wagasci_box_.x(), wagasci_box_.y(), wagasci_box_.z());
  auto *wallmrd_box = new G4Box("WallMRD_Module", wallmrd_box_.x(), wallmrd_box_.y(), wallmrd_box_.z());
  auto *babymind_box = new G4Box("BabyMIND_Module", bm_box_.x(), bm_box_.y(), bm_box_.z());
  auto *ninja_box = new G4Box("NINJA_Module", ninja_box_.x(), ninja_box_.y(), ninja_box_.z());

  // YASU tracker uses the same box as BabyMIND
  B2LogicalVolumeMap module_lv;

  module_lv[B2Detector::kProtonModule] = new G4LogicalVolume(pm_box, air_, "module_lv_pm");
  new G4PVPlacement(nullptr, pm_pos_, module_lv[B2Detector::kProtonModule], "module0", b2_lv, false,
                    B2Detector::kProtonModule);
  module_lv[B2Detector::kProtonModule]->SetVisAttributes(box_vis_att_);

  module_lv[B2Detector::kWagasciUpstream] = new G4LogicalVolume(wagasci_box, air_, "module_lv_wagasci1");
  new G4PVPlacement(nullptr, wg_upstream_pos_, module_lv[B2Detector::kWagasciUpstream], "module1", b2_lv, false,
                    B2Detector::kWagasciUpstream);
  module_lv[B2Detector::kWagasciUpstream]->SetVisAttributes(box_vis_att_);

  module_lv[B2Detector::kWagasciDownstream] = new G4LogicalVolume(wagasci_box, air_, "module_lv_wagasci2");
  new G4PVPlacement(nullptr, wg_downstream_pos_, module_lv[B2Detector::kWagasciDownstream], "module2", b2_lv, false,
                    B2Detector::kWagasciDownstream);
  module_lv[B2Detector::kWagasciDownstream]->SetVisAttributes(box_vis_att_);

  module_lv[B2Detector::kWallMrdSouth] = new G4LogicalVolume(wallmrd_box, air_, "module_lv_wallmrd_left");
  new G4PVPlacement(nullptr, wallmrd_south_pos_, module_lv[B2Detector::kWallMrdSouth], "module3", b2_lv, false,
                    B2Detector::kWallMrdSouth);
  module_lv[B2Detector::kWallMrdSouth]->SetVisAttributes(box_vis_att_);

  module_lv[B2Detector::kWallMrdNorth] = new G4LogicalVolume(wallmrd_box, air_, "module_lv_wallmrd_right");
  new G4PVPlacement(nullptr, wallmrd_north_pos_, module_lv[B2Detector::kWallMrdNorth], "module4", b2_lv, false,
                    B2Detector::kWallMrdNorth);
  module_lv[B2Detector::kWallMrdNorth]->SetVisAttributes(box_vis_att_);

  module_lv[B2Detector::kBabyMind] = new G4LogicalVolume(babymind_box, air_, "module_lv_babymind");
  new G4PVPlacement(nullptr, babymind_pos_, module_lv[B2Detector::kBabyMind], "module5", b2_lv, false,
                    B2Detector::kBabyMind);
  module_lv[B2Detector::kBabyMind]->SetVisAttributes(box_vis_att_);

  module_lv[B2Detector::kNinja] = new G4LogicalVolume(ninja_box, air_, "module_lv_ninja");
  new G4PVPlacement(nullptr, ninja_pos_, module_lv[B2Detector::kNinja], "module7", b2_lv, false, B2Detector::kNinja);
  module_lv[B2Detector::kNinja]->SetVisAttributes(box_vis_att_);

  return module_lv;
}

void B2DetectorConstruction::ConstructProtonModule(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  // SciBar type for Proton module
  std::vector<G4TwoVector> svdim;  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> shdim;  // horizontal-layer scintillator (internal)

  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    svdim.emplace_back(scibar_vertex_x_[iver], scibar_vertex_y_[iver]);
    shdim.emplace_back(scibar_vertex_y_[num_scintillator_vertices_ - 1 - iver],
                       scibar_vertex_x_[num_scintillator_vertices_ - 1 - iver]);
  }

  // INGRID type for Proton module
  std::vector<G4TwoVector> ivdim;  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> ihdim;  // horizontal-layer scintillator (internal)

  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    ivdim.emplace_back(ingrid_vertex_x_[iver], ingrid_vertex_y_[iver]);
    ihdim.emplace_back(ingrid_vertex_y_[num_scintillator_vertices_ - 1 - iver],
                       ingrid_vertex_x_[num_scintillator_vertices_ - 1 - iver]);
  }

  std::vector<G4ExtrudedSolid::ZSection> zsec;
  zsec.emplace_back(-pm_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1);
  zsec.emplace_back(pm_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1);

  // SciBar vertical scintillator
#ifdef WITH_G4VIS
  auto *vscint2_int = new G4ExtrudedSolid("vscint2_tmp", svdim, zsec);
#else
  auto *vscint2_tmp = new G4ExtrudedSolid("vscint2_tmp", svdim, zsec);
  auto *vsci_hole2 = new G4EllipticalTube("vsci_hole2", 0.9 * mm, 0.9 * mm, pm_sci_length_ + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *vscint2_int = new G4SubtractionSolid("vscint2_int", vscint2_tmp, vsci_hole2);
#endif
  auto *vscint2_intLV = new G4LogicalVolume(vscint2_int, plastic_, "vscint2_intLV");
  vscint2_intLV->SetVisAttributes(sci_vis_att_);

  // SciBar horizontal scintillator
#ifdef WITH_G4VIS
  auto *hscint2_int = new G4ExtrudedSolid("hscint2_tmp", shdim, zsec);
#else
  auto *hscint2_tmp = new G4ExtrudedSolid("hscint2_tmp", shdim, zsec);
  auto *hsci_hole2 = new G4EllipticalTube("hsci_hole2", 0.9 * mm, 0.9 * mm, pm_sci_length_ + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *hscint2_int = new G4SubtractionSolid("hscint2_int", hscint2_tmp, hsci_hole2);
#endif
  auto *hscint2_intLV = new G4LogicalVolume(hscint2_int, plastic_, "hscint2_intLV");
  hscint2_intLV->SetVisAttributes(sci_vis_att_);

  // INGRID vertical scintillator for PM
#ifdef WITH_G4VIS
  auto *vscint3_int = new G4ExtrudedSolid("vscint3_tmp", ivdim, zsec);
#else
  auto *vscint3_tmp = new G4ExtrudedSolid("vscint3_tmp", ivdim, zsec);
  auto *vsci_hole3 = new G4EllipticalTube("vsci_hole3", 1.3 * mm, 1.95 * mm, pm_sci_length_ + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *vscint3_int = new G4SubtractionSolid("vscint3_int", vscint3_tmp, vsci_hole3);
#endif
  auto *vscint3_intLV = new G4LogicalVolume(vscint3_int, plastic_, "vscint3_intLV");
  vscint3_intLV->SetVisAttributes(sci_vis_att_);

  // INGRID horizontal scintillator for PM
#ifdef WITH_G4VIS
  auto *hscint3_int = new G4ExtrudedSolid("hscint3_tmp", ihdim, zsec);
#else
  auto *hscint3_tmp = new G4ExtrudedSolid("hscint3_tmp", ihdim, zsec);
  auto *hsci_hole3 = new G4EllipticalTube("hsci_hole3", 1.95 * mm, 1.3 * mm, pm_sci_length_ + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *hscint3_int = new G4SubtractionSolid("hscint3_int", hscint3_tmp, hsci_hole3);
#endif
  auto *hscint3_intLV = new G4LogicalVolume(hscint3_int, plastic_, "hscint3_intLV");
  hscint3_intLV->SetVisAttributes(sci_vis_att_);

  //********** Scintillator for veto planes **********//

  // Proton module Long Veto plane
  auto *long_veto_box = new G4Box("PLveto_box", pm_long_veto_x_, pm_long_veto_y_, pm_long_veto_z_);
  auto *long_veto_lv = new G4LogicalVolume(long_veto_box, plastic_, "PLvetoLV");
  long_veto_lv->SetVisAttributes(veto_vis_att_);

  // Proton module Short Veto plane
  auto *short_veto_box = new G4Box("PSveto_box", pm_short_veto_x_, pm_short_veto_y_, pm_short_veto_z_);
  auto *short_veto_lv = new G4LogicalVolume(short_veto_box, plastic_, "PSvetoLV");
  short_veto_lv->SetVisAttributes(veto_vis_att_);

  // Rotation matrices for veto planes
  auto *tb_2_lr = new G4RotationMatrix(G4ThreeVector(0, 0, 1.), 90. * degree);

  for (int plane = 0; plane < PM_NUM_PLANES; plane++) {
    TVector3 pos;
    char scint_name[name_length_];

    // Rotation matrices definition
    auto xrot = new G4RotationMatrix(G4ThreeVector(1, 0, 0), 90. * degree);
    auto yrot = new G4RotationMatrix(G4ThreeVector(0, 1, 0), 90. * degree);

    if (plane == 0) { // The front veto plane
      for (int channel = 0; channel < PM_NUM_CHANNELS_FRONT_VETO; channel++) {
	// Horizontal plane (0X)
	dimension_.get().GetPosPm(B2View::kSideView, plane, channel, pos);
        std::snprintf(scint_name, name_length_, "hlayer[%d][%d][%d]", det, plane, channel);
        new G4PVPlacement(yrot, root_v_to_geant_v(pos), hscint3_intLV, scint_name, module_lv, false,
                          channel + 0 * MAX_NUM_CHANNELS +
			  det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	// Vertical plane (0Y)
	dimension_.get().GetPosPm(B2View::kTopView, plane, channel, pos);
        std::snprintf(scint_name, name_length_, "vlayer[%d][%d][%d]", det, plane, channel);
        new G4PVPlacement(xrot, root_v_to_geant_v(pos), vscint3_intLV, scint_name, module_lv, false,
                          channel + 0 * MAX_NUM_CHANNELS + 
			  det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      }
    } else if (plane < PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES) { // 17 Tracking planes
      for (int channel = 0; channel < PM_NUM_CHANNELS_ONE_TRACK_PLANE; channel++) {
	// Horizontal tracking planes
	dimension_.get().GetPosPm(B2View::kSideView, plane, channel, pos);
        std::snprintf(scint_name, name_length_, "hlayer[%d][%d][%d]", det, plane, channel);
	if (channel < 8) // 8 INGRID type
	  new G4PVPlacement(yrot, root_v_to_geant_v(pos), hscint3_intLV, scint_name, module_lv, false,
			    channel + plane * MAX_NUM_CHANNELS +
			    det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
        else if (channel < 24) // 16 SciBar type
	  new G4PVPlacement(yrot, root_v_to_geant_v(pos), hscint2_intLV, scint_name, module_lv, false,
			    channel + plane * MAX_NUM_CHANNELS +
			    det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	else // 8 INGRID type
	  new G4PVPlacement(yrot, root_v_to_geant_v(pos), hscint3_intLV, scint_name, module_lv, false,
			    channel + plane * MAX_NUM_CHANNELS +
			    det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);

	// Vertical tracking planes
	dimension_.get().GetPosPm(B2View::kTopView, plane, channel, pos);
        std::snprintf(scint_name, name_length_, "vlayer[%d][%d][%d]", det, plane, channel);
	if (channel < 8) // 8 INGRID type
	  new G4PVPlacement(xrot, root_v_to_geant_v(pos), vscint3_intLV, scint_name, module_lv, false,
			    channel + plane * MAX_NUM_CHANNELS +
			    det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	else if (channel < 24) // 16 SciBar type
	  new G4PVPlacement(xrot, root_v_to_geant_v(pos), vscint2_intLV, scint_name, module_lv, false,
			    channel + plane * MAX_NUM_CHANNELS +
			    det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	else // 8 INGRID type
	  new G4PVPlacement(xrot, root_v_to_geant_v(pos), vscint3_intLV, scint_name, module_lv, false,
			    channel + plane * MAX_NUM_CHANNELS +
			    det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      }
    } else { // Veto other than front
      char veto_name[name_length_];

      for (int channel = 0; channel < PM_NUM_CHANNELS_OTHER_VETO; channel++) {

	switch (dimension_.get().GetVetoPlanePm(plane)) {
	case B2VetoPlane::kUpVeto :
	case B2VetoPlane::kBottomVeto :
	  dimension_.get().GetPosPm(B2View::kSideView, plane, channel, pos);
	  break;
	case B2VetoPlane::kLeftVeto :
	case B2VetoPlane::kRightVeto :
	  dimension_.get().GetPosPm(B2View::kTopView, plane, channel, pos);
	  break;
	case B2VetoPlane::kUpstreamVeto :
	  BOOST_LOG_TRIVIAL(error) << "Upstream VETO";
	  std::exit(1);
	case B2VetoPlane::kNotVeto :
	  BOOST_LOG_TRIVIAL(error) << "Non VETO plane : " << plane;
	  std::exit(1);
	}

	std::snprintf(veto_name, name_length_, "veto[%d][%d][%d]", det, plane - 18, channel);
	switch (dimension_.get().GetVetoPlanePm(plane)) {
	case B2VetoPlane::kUpVeto :
	  new G4PVPlacement(nullptr, root_v_to_geant_v(pos), long_veto_lv, veto_name, module_lv, false,
			    channel + 2 * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	  break;
	case B2VetoPlane::kLeftVeto :
	case B2VetoPlane::kRightVeto :
	  new G4PVPlacement(tb_2_lr, root_v_to_geant_v(pos), long_veto_lv, veto_name, module_lv, false,
			    channel + (plane-18) * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	  break;
	case B2VetoPlane::kBottomVeto :
	  new G4PVPlacement(nullptr, root_v_to_geant_v(pos), short_veto_lv, veto_name, module_lv, false,
			    channel + 0 * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
	  break;
	case B2VetoPlane::kUpstreamVeto :
	  BOOST_LOG_TRIVIAL(error) << "Upstream VETO";
	  std::exit(1);
	case B2VetoPlane::kNotVeto :
	  BOOST_LOG_TRIVIAL(error) << "Non VETO plane : " << plane;
	  std::exit(1);
	}
      } // channel
    }

  } // plane

  //******* Assignment of sensitive detectors *******/

  p_sd_manager->AddNewDetector(horizontal_scintillators_);
  // SciBar type for Proton Module
  hscint2_intLV->SetSensitiveDetector(horizontal_scintillators_);
  // INGRID type for Proton Module
  hscint3_intLV->SetSensitiveDetector(horizontal_scintillators_);

  p_sd_manager->AddNewDetector(vertical_scintillators_);
  // SciBar type for Proton Module
  vscint2_intLV->SetSensitiveDetector(vertical_scintillators_);
  // INGRID type for Proton Module
  vscint3_intLV->SetSensitiveDetector(vertical_scintillators_);

  p_sd_manager->AddNewDetector(veto_scintillators_);
  // Short veto for Proton Module
  short_veto_lv->SetSensitiveDetector(veto_scintillators_);
  // Long veto for Proton Module
  long_veto_lv->SetSensitiveDetector(veto_scintillators_);
}

void B2DetectorConstruction::ConstructWagasci(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  // Rotation matrices for plane layer
  auto *x_rot = new G4RotationMatrix(G4ThreeVector(1, 0, 0), -90. * degree);
  auto *y_rot = new G4RotationMatrix(G4ThreeVector(0, 1, 0), -90. * degree);
  // Rotation matrices for Y grid layer
  auto *y_rot_grid_v = new G4RotationMatrix(G4ThreeVector(0, 0, 1), 180. * degree);
  y_rot_grid_v->rotateY(-90 * degree);
  y_rot_grid_v->rotateX(-90 * degree);
  auto *y_rot_grid_h = new G4RotationMatrix(G4ThreeVector(1, 0, 0), -90. * degree);
  y_rot_grid_h->rotateY(-90 * degree);
  // Rotation matrices for X grid layer
  auto *x_rot_grid_v = new G4RotationMatrix(G4ThreeVector(0, 1, 0), -90. * degree);
  x_rot_grid_v->rotateX(-90 * degree);
  auto *x_rot_grid_h = new G4RotationMatrix(G4ThreeVector(0, 0, 1), 180. * degree);
  x_rot_grid_h->rotateX(-90 * degree);
  x_rot_grid_h->rotateY(-90 * degree);

  // Water tank (SUS304) for WAGASCI
  // We do not need two logical volumes since the volume called
  // only once in one ConstructWagasci function TODO
  G4Box *sus_box[2];
  sus_box[0] = new G4Box("SUS_box0", sus_box_.x(), sus_box_.y(), sus_box_.z());
  sus_box[1] = new G4Box("SUS_box1", sus_box_.x(), sus_box_.y(), sus_box_.z());
  G4LogicalVolume *sus_lv[2];
  sus_lv[0] = new G4LogicalVolume(sus_box[0], sus_304_, "SUSLV0");
  sus_lv[1] = new G4LogicalVolume(sus_box[1], sus_304_, "SUSLV1");
  sus_lv[0]->SetVisAttributes(sus_vis_att_);
  sus_lv[1]->SetVisAttributes(sus_vis_att_);

  // Water for WAGASCI
  G4Box *water_box[2];
  water_box[0] = new G4Box("Water_box0", water_box_.x(), water_box_.y(), water_box_.z());
  water_box[1] = new G4Box("Water_box1", water_box_.x(), water_box_.y(), water_box_.z());
  G4LogicalVolume *water_lv[2];

  switch (water_settings_) {
    case B2WaterSettings::kWgupOutWgdownOut:
      water_lv[0] = new G4LogicalVolume(water_box[0], air_, "WaterLV0");
      water_lv[0]->SetVisAttributes(air_vis_att_);
      water_lv[1] = new G4LogicalVolume(water_box[1], air_, "WaterLV1");
      water_lv[1]->SetVisAttributes(air_vis_att_);
      break;
    case B2WaterSettings::kWgupInWgdownOut:
      water_lv[0] = new G4LogicalVolume(water_box[0], water_, "WaterLV0");
      water_lv[0]->SetVisAttributes(water_vis_att_);
      water_lv[1] = new G4LogicalVolume(water_box[1], air_, "WaterLV1");
      water_lv[1]->SetVisAttributes(air_vis_att_);
      break;
    case B2WaterSettings::kWgupOutWgdownIn:
      water_lv[0] = new G4LogicalVolume(water_box[0], air_, "WaterLV0");
      water_lv[0]->SetVisAttributes(air_vis_att_);
      water_lv[1] = new G4LogicalVolume(water_box[1], water_, "WaterLV1");
      water_lv[1]->SetVisAttributes(water_vis_att_);
      break;
    case B2WaterSettings::kWgupInWgdownIn:
      water_lv[0] = new G4LogicalVolume(water_box[0], water_, "WaterLV0");
      water_lv[0]->SetVisAttributes(water_vis_att_);
      water_lv[1] = new G4LogicalVolume(water_box[1], water_, "WaterLV1");
      water_lv[1]->SetVisAttributes(water_vis_att_);
      break;
    default:
      throw std::invalid_argument("Invalid water settings : " + std::to_string(water_settings_));
  }

  //********** Scintillator for tracking plane**********//

  // Scintillator dimension for WAGASCI
  std::vector<G4TwoVector> wg_vertical_dim;  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> wg_horizontal_dim;  // horizontal-layer scintillator (internal)
  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    wg_vertical_dim.emplace_back(wagasci_vertex_x_[iver], wagasci_vertex_y_[iver]);
    wg_horizontal_dim.emplace_back(wagasci_vertex_y_[num_scintillator_vertices_ - 1 - iver],
                                   wagasci_vertex_x_[num_scintillator_vertices_ - 1 - iver]);
  }

  std::vector<G4ExtrudedSolid::ZSection> wg_z_section;
  wg_z_section.emplace_back(-wg_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1.);
  wg_z_section.emplace_back(wg_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1.);

  // WAGASCI vertical scintillator
#ifdef WITH_G4VIS
  auto *v_wg_scint_int = new G4ExtrudedSolid("v_wg_scint_tmp", wg_vertical_dim, wg_z_section);
#else
  auto *v_wg_scint_tmp = new G4ExtrudedSolid("v_wg_scint_tmp", wg_vertical_dim, wg_z_section);
  auto *v_glue = new G4Box("v_glue", 0.61 * mm, 0.61 * mm, wg_sci_length_ + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *v_wg_scint_int = new G4SubtractionSolid("v_wg_scint_int", v_wg_scint_tmp, v_glue, nullptr,
                                                G4ThreeVector(-3.9 * mm, -0.9 * mm, 0 * mm));
#endif
  auto *v_wg_scint_int_lv = new G4LogicalVolume(v_wg_scint_int, plastic_, "v_wg_scint_int_lv");
  v_wg_scint_int_lv->SetVisAttributes(sci_vis_att_);

  // WAGASCI horizontal scintillator
#ifdef WITH_G4VIS
  auto *h_wg_scint_int = new G4ExtrudedSolid("h_wg_scint_tmp", wg_horizontal_dim, wg_z_section);
#else
  auto *h_wg_scint_tmp = new G4ExtrudedSolid("h_wg_scint_tmp", wg_horizontal_dim, wg_z_section);
  auto *h_glue = new G4Box("h_glue", 0.61 * mm, 0.61 * mm, wg_sci_length_ + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *h_wg_scint_int = new G4SubtractionSolid("h_wg_scint_int", h_wg_scint_tmp, h_glue, nullptr,
                                                G4ThreeVector(0.9 * mm, -3.9 * mm, 0 * mm));
#endif
  auto *h_wg_scint_int_lv = new G4LogicalVolume(h_wg_scint_int, plastic_, "h_wg_scint_int_lv");
  h_wg_scint_int_lv->SetVisAttributes(sci_vis_att_);

  // WAGASCI vertical grid scintillator
#ifdef WITH_G4VIS
  G4VSolid *v_wg_grid_scint_int = new G4ExtrudedSolid("v_wg_grid_scint_tmp", wg_vertical_dim, wg_z_section);
#else
  G4VSolid *v_wg_grid_scint_tmp = new G4ExtrudedSolid("v_wg_grid_scint_tmp", wg_vertical_dim, wg_z_section);
  G4VSolid *v_wg_grid_scint_int = new G4SubtractionSolid("v_wg_grid_scint_int", v_wg_grid_scint_tmp, v_glue, nullptr,
                                                         G4ThreeVector(-3.9 * mm, -0.9 * mm, 0 * mm));
  G4VSolid *v_cut = new G4Box("v_cut", wg_sci_cut_depth_ + 0.1 * mm, wg_sci_cut_thick_ + 0.1 * mm, wg_sci_cut_thick_ + 0.1 * mm); // add 0.1 mm to avoid bug
  for (int i = 0; i < 20; i++) {
    G4ThreeVector tmp_vec(5.3 * mm, 0 * mm, wg_offset_xy_grid_ + i * wg_sci_grid_space_);
    G4VSolid *v_wg_grid_scint_tmp2 = new G4SubtractionSolid("", v_wg_grid_scint_int, v_cut, nullptr, tmp_vec);
    v_wg_grid_scint_int = v_wg_grid_scint_tmp2;
  }

#endif
  auto *v_wg_grid_scint_int_lv = new G4LogicalVolume(v_wg_grid_scint_int, plastic_, "v_wg_grid_scint_int_lv");
  v_wg_grid_scint_int_lv->SetVisAttributes(sci_vis_att_);

  // WAGASCI horizontal grid scintillator
#ifdef WITH_G4VIS
  G4VSolid *h_wg_grid_scint_int = new G4ExtrudedSolid("h_wg_grid_scint_tmp", wg_horizontal_dim, wg_z_section);
#else
  G4VSolid *h_wg_grid_scint_tmp = new G4ExtrudedSolid("h_wg_grid_scint_tmp", wg_horizontal_dim, wg_z_section);
  G4VSolid *h_wg_grid_scint_int = new G4SubtractionSolid("h_wg_grid_scint_int", h_wg_grid_scint_tmp, h_glue, nullptr,
                                                         G4ThreeVector(0.9 * mm, -3.9 * mm, 0 * mm));
  G4VSolid *h_cut = new G4Box("h_cut", wg_sci_cut_thick_ + 0.1 * mm, wg_sci_cut_depth_ + 0.1 * mm, wg_sci_cut_thick_ + 0.1 * mm); // add 0.1 mm to avoid bug
  for (int i = 0; i < 20; i++) {
    G4ThreeVector tmp_vec(0 * mm, 5.3 * mm,  wg_offset_xy_grid_ + i * wg_sci_grid_space_);
    G4VSolid *h_wg_grid_scint_tmp2 = new G4SubtractionSolid("", h_wg_grid_scint_int, h_cut, nullptr, tmp_vec);
    h_wg_grid_scint_int = h_wg_grid_scint_tmp2;
  }
#endif
  auto *h_wg_grid_scint_int_lv = new G4LogicalVolume(h_wg_grid_scint_int, plastic_, "h_wg_grid_scint_int_lv");
  h_wg_grid_scint_int_lv->SetVisAttributes(sci_vis_att_);

  char scint_name[name_length_];
  std::snprintf(scint_name, name_length_, "sustarget[%d]", det);
  // water tank
  new G4PVPlacement(nullptr, origin_, sus_lv[det - 1], scint_name, module_lv, false, det);
  std::snprintf(scint_name, name_length_, "watertarget[%d]", det);
  // water target
  new G4PVPlacement(nullptr, origin_, water_lv[det - 1], scint_name, sus_lv[det - 1], false, det);
  for (int plane = 0; plane < WGS_NUM_PLANES; plane++) {
    for (int slot = 0; slot < WGS_NUM_SLOTS_PLANE; slot++) {
      TVector3 pos;
      // vertical layer
      dimension_.get().GetPosWgs(B2View::kTopView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "vlayer[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(x_rot, root_v_to_geant_v(pos), v_wg_scint_int_lv, scint_name, water_lv[det - 1], false,
                        slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      // horizontal layer
      dimension_.get().GetPosWgs(B2View::kSideView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "hlayer[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(y_rot, root_v_to_geant_v(pos), h_wg_scint_int_lv, scint_name, water_lv[det - 1], false,
                        slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }
    for (int slot = WGS_NUM_SLOTS_PLANE; slot < WGS_NUM_SLOTS_PLANE + WGS_NUM_SLOTS_GRID_LEFT; slot++) {
      TVector3 pos;
      // vertical grid left layer
      dimension_.get().GetPosWgs(B2View::kTopView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "vlayer1[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(x_rot_grid_v, root_v_to_geant_v(pos), v_wg_grid_scint_int_lv, scint_name, water_lv[det - 1],
                        false, slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      // horizontal grid left layer
      dimension_.get().GetPosWgs(B2View::kSideView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "hlayer1[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(x_rot_grid_h, root_v_to_geant_v(pos), h_wg_grid_scint_int_lv, scint_name, water_lv[det - 1],
                        false, slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }
    for (int slot = WGS_NUM_SLOTS_PLANE + WGS_NUM_SLOTS_GRID_LEFT; slot < WGS_NUM_SLOTS; slot++) {
      TVector3 pos;
      // vertical grid right layer
      dimension_.get().GetPosWgs(B2View::kTopView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "vlayer2[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(y_rot_grid_v, root_v_to_geant_v(pos), v_wg_grid_scint_int_lv, scint_name, water_lv[det - 1],
                        false, slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      // horizontal grid right layer
      dimension_.get().GetPosWgs(B2View::kSideView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "hlayer2[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(y_rot_grid_h, root_v_to_geant_v(pos), h_wg_grid_scint_int_lv, scint_name, water_lv[det - 1],
                        false, slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }
  }

  //*******Assignment of sensitive detectors*******/

  p_sd_manager->AddNewDetector(horizontal_scintillators_);
  // Plane scintillator for WAGASCI
  h_wg_scint_int_lv->SetSensitiveDetector(horizontal_scintillators_);
  // Grid scintillator for WAGASCI
  h_wg_grid_scint_int_lv->SetSensitiveDetector(horizontal_scintillators_);

  p_sd_manager->AddNewDetector(vertical_scintillators_);
  // Plane scintillator for WAGASCI
  v_wg_scint_int_lv->SetSensitiveDetector(vertical_scintillators_);
  // Grid scintillator for WAGASCI
  v_wg_grid_scint_int_lv->SetSensitiveDetector(vertical_scintillators_);
}

void B2DetectorConstruction::ConstructWallMrd(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  //********** IRON  **********//

  // Inner iron plate for WallMRD
  auto *iron_wallmrd_box = new G4Box("IronWallMRD", c_iron_wallmrd_x_, c_iron_wallmrd_y_, c_iron_wallmrd_z_);
  auto *iron_wallmrd_lv = new G4LogicalVolume(iron_wallmrd_box, iron_, "iron_wallmrd_lv");
  iron_wallmrd_lv->SetVisAttributes(iron_vis_att_);

  // Front and rear iron plate for WallMRD
  auto *front_iron_wallmrd = new G4Box("FIronWallMRD", f_iron_wallmrd_x_, f_iron_wallmrd_y_, f_iron_wallmrd_z_);
  auto *front_iron_wallmrd_lv = new G4LogicalVolume(front_iron_wallmrd, iron_, "front_iron_wallmrd_lv");
  front_iron_wallmrd_lv->SetVisAttributes(iron_vis_att_);

  // Side iron plate for WallMRD
  auto *side_iron_wallmrd = new G4Box("SIronWallMRD", s_iron_wallmrd_x_, s_iron_wallmrd_y_, s_iron_wallmrd_z_);
  auto *side_iron_wallmrd_lv = new G4LogicalVolume(side_iron_wallmrd, iron_, "side_iron_wallmrd_lv");
  side_iron_wallmrd_lv->SetVisAttributes(iron_vis_att_);

  //********** Scintillator for tracking plane**********//

  // Rotation matrix definition
  auto *sci_rot = new G4RotationMatrix(G4ThreeVector(0, 1, 0), 90. * degree);
  sci_rot->rotateX(90. * degree);

  std::vector<G4TwoVector> wm_dim;

  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    wm_dim.emplace_back(wallmrd_vertex_x_[iver], wallmrd_vertex_y_[iver]);
  }

  std::vector<G4ExtrudedSolid::ZSection> wm_zsec;
  wm_zsec.emplace_back(-wallmrd_sci_y_, G4TwoVector(0 * mm, 0 * mm), 1.);
  wm_zsec.emplace_back(wallmrd_sci_y_, G4TwoVector(0 * mm, 0 * mm), 1.);
  
#ifdef WITH_G4VIS
  auto *wm_sci_int = new G4ExtrudedSolid("wm_sci_tmp", wm_dim, wm_zsec);
#else
  auto *wm_sci_int = new G4ExtrudedSolid("wm_sci_tmp", wm_dim, wm_zsec);
#endif
  auto *wm_sci_int_lv = new G4LogicalVolume(wm_sci_int, plastic_, "wm_sci_int_lv");
  /*
  auto *wm_sci_int_box = new G4Box("wm_sci_int_box", wallmrd_sci_x_, wallmrd_sci_y_, wallmrd_sci_z_);
  auto *wm_sci_int_lv = new G4LogicalVolume(wm_sci_int_box, plastic_, "wallmrd_vlayerLV");
  */
  wm_sci_int_lv->SetVisAttributes(sci_vis_att_);

  char scint_name_[name_length_], iron_name_[name_length_];

  // Iron blocks
  for (int plane = 0; plane < WM_NUM_IRON_PLANES; plane++) {
    std::snprintf(iron_name_, name_length_, "iron[%d][%d]", det, plane);
    TVector3 pos;
    dimension_.get().GetPosWallMrdIron((B2Detector) det, plane, pos);
    if (plane == 0 || plane == 10) { // front and back iron blocks
      new G4PVPlacement(nullptr, root_v_to_geant_v(pos), front_iron_wallmrd_lv, iron_name_, module_lv, false,
			plane + det * MAX_NUM_PLANES);
    } else if (plane < 10) { // inner blocks
      new G4PVPlacement(nullptr, root_v_to_geant_v(pos), iron_wallmrd_lv, iron_name_, module_lv, false,
			plane + det * MAX_NUM_PLANES);
    } else { // side blocks
      new G4PVPlacement(nullptr, root_v_to_geant_v(pos), side_iron_wallmrd_lv, iron_name_, module_lv, false,
			plane + det * MAX_NUM_PLANES);
    }
  }

  // Scintillator
  for (int plane = 0; plane < WM_NUM_SCINTI_PLANES; plane++) {
    for (int slot = 0; slot < WM_NUM_SCINTI_IN_ONE_PLANE; slot++) {
      TVector3 pos;
      dimension_.get().GetPosWallMrd((B2Detector) det, plane, slot, pos);
      std::snprintf(scint_name_, name_length_, "vlayer[%d][%d][%d]", det, plane, slot);
      new G4PVPlacement(sci_rot, root_v_to_geant_v(pos), wm_sci_int_lv, scint_name_, module_lv, false,
                        slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }
  }

  //*******Assignment of sensitive detectors*******/

  p_sd_manager->AddNewDetector(vertical_scintillators_);
  wm_sci_int_lv->SetSensitiveDetector(vertical_scintillators_);
}

void B2DetectorConstruction::ConstructBabyMind(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  // Horizontal for BabyMIND
  std::vector<G4TwoVector> hhdim;  // horizontal-layer scintillator (internal)

  // Vertical type BabyMIND
  std::vector<G4TwoVector> vvdim;  // vertical-layer scintillator (internal)

  auto xrot = new G4RotationMatrix(G4ThreeVector(1, 0, 0), 90. * degree);
  auto yrot = new G4RotationMatrix(G4ThreeVector(0, 1, 0), 90. * degree);

  // for Horizontal of BM
  // Polygon is on z direction? TODO
  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    hhdim.emplace_back(bm_horizontal_vertex_x_[iver],
                       bm_horizontal_vertex_y_[iver]);
  }

  std::vector<G4ExtrudedSolid::ZSection> hzsec;
  hzsec.emplace_back(-BM_HORIZONTAL_SCINTI_LENGTH * mm / 2., G4TwoVector(0 * mm, 0 * mm), 1);
  hzsec.emplace_back(BM_HORIZONTAL_SCINTI_LENGTH * mm / 2., G4TwoVector(0 * mm, 0 * mm), 1);

  // for Vertical of BM
  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    vvdim.emplace_back(bm_vertical_vertex_x_[iver], bm_vertical_vertex_y_[iver]);
  }

  std::vector<G4ExtrudedSolid::ZSection> vzsec;
  vzsec.emplace_back(-BM_VERTICAL_SCINTI_LENGTH * mm / 2., G4TwoVector(0 * mm, 0 * mm), 1);
  vzsec.emplace_back(BM_VERTICAL_SCINTI_LENGTH * mm / 2., G4TwoVector(0 * mm, 0 * mm), 1);

  // Magnet module (iron plate) for Baby-MIND
  auto *iron_bm = new G4Box("iron_bm", iron_bm_x_, iron_bm_y_, iron_bm_z_);
  auto *iron_bm_lv = new G4LogicalVolume(iron_bm, iron_, "iron_bm_lv");
  iron_bm_lv->SetVisAttributes(iron_vis_att_);
  // Baby-MIND horizontal scintillator

#ifdef WITH_G4VIS
  auto *h_bm_sci_int = new G4ExtrudedSolid("h_bm_sci_int", hhdim, hzsec);
#else
  auto *h_bm_sci_tmp = new G4ExtrudedSolid("h_bm_sci_tmp", hhdim, hzsec);
  auto *h_bm_hole = new G4EllipticalTube("hsci_hole", 0.9 * mm, 0.9 * mm, 1440 * mm + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *h_bm_sci_int = new G4SubtractionSolid("h_bm_sci_int", h_bm_sci_tmp, h_bm_hole);
#endif
  auto *h_bm_sci_int_box = new G4Box("h_bm_sci_int_box", h_sci_bm_x_, h_sci_bm_y_, h_sci_bm_z_);
  auto *h_bm_sci_int_lv = new G4LogicalVolume(h_bm_sci_int, plastic_, "h_bm_sci_intLV");
  //auto *h_bm_sci_int_lv = new G4LogicalVolume(h_bm_sci_int_box, plastic_, "h_bm_sci_intLV");
  h_bm_sci_int_lv->SetVisAttributes(sci_vis_att_);

  // Baby-MIND vertical scintillator

#ifdef WITH_G4VIS
  auto *v_bm_sci_int = new G4ExtrudedSolid("v_bm_sci_int", vvdim, vzsec);
#else
  auto *v_bm_sci_tmp = new G4ExtrudedSolid("v_bm_sci_tmp", vvdim, vzsec);
  // Hole in vertical scintillator is not straight TODO
  auto *v_bm_hole = new G4EllipticalTube("vsci_hole", 0.9 * mm, 0.9 * mm, 975 * mm + 0.1 * mm); // add 0.1 mm to avoid bug
  auto *v_bm_sci_int = new G4SubtractionSolid("v_bm_sci_int", v_bm_sci_tmp, v_bm_hole);
#endif
  auto *v_bm_sci_int_box = new G4Box("v_bm_sci_int_box", v_sci_bm_x_, v_sci_bm_y_, v_sci_bm_z_);
  auto *v_bm_sci_int_lv = new G4LogicalVolume(v_bm_sci_int, plastic_, "v_bm_sci_intLV");
  //auto *v_bm_sci_int_lv = new G4LogicalVolume(v_bm_sci_int_box, plastic_, "v_bm_sci_intLV");
  v_bm_sci_int_lv->SetVisAttributes(sci_vis_att_);

  char scint_name[name_length_], iron_name_[name_length_];

  // Magnetic module (iron plate)
  for (std::size_t plane = 0; plane < BM_NUM_IRON_PLANES; plane++) {
    std::snprintf(iron_name_, name_length_, "iron[%d][%lu]", det, plane);
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, BM_IRON_MODULE_Z[plane]),
                      iron_bm_lv, iron_name_, module_lv, false, plane + det * MAX_NUM_PLANES);
  }

  // Detector module (scintillator tracking planes)
  for (int plane = 0; plane < BM_NUM_TRACKING_PLANES; plane++) {
    // Horizontal scintillator
    TVector3 pos_h;
    for (int channel = 0; channel < BM_NUM_HORIZ_SCINTI_ONE_PLANE; channel++) {
      dimension_.get().GetPosBm(B2View::kSideView, plane, channel, pos_h);
      std::snprintf(scint_name, name_length_, "hlayer[%d][%d][%d]", det, plane, channel);
      //new G4PVPlacement(xrot, root_v_to_geant_v(pos_h), h_bm_sci_int_lv, scint_name, module_lv, false,
      //                channel + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      new G4PVPlacement(yrot, root_v_to_geant_v(pos_h), h_bm_sci_int_lv, scint_name, module_lv, false,
			channel + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      //new G4PVPlacement(nullptr, root_v_to_geant_v(pos_h), h_bm_sci_int_lv, scint_name, module_lv, false,
      //                channel + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }

    // Vertical scintillator
    TVector3 pos_v;
    for (int channel = 0; channel < BM_NUM_VERTICAL_SCINTI_ONE_PLANE; channel++) {
      dimension_.get().GetPosBm(B2View::kTopView, plane, channel, pos_v);
      std::snprintf(scint_name, name_length_, "vlayer[%d][%d][%d]", det, plane, channel);
      new G4PVPlacement(xrot, root_v_to_geant_v(pos_v), v_bm_sci_int_lv, scint_name, module_lv, false,
			channel + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      //new G4PVPlacement(nullptr, root_v_to_geant_v(pos_v), v_bm_sci_int_lv, scint_name, module_lv, false,
      //                channel + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }
  }

  //*******Assignment of sensitive detectors*******/
  p_sd_manager->AddNewDetector(horizontal_scintillators_);
  h_bm_sci_int_lv->SetSensitiveDetector(horizontal_scintillators_);
  v_bm_sci_int_lv->SetSensitiveDetector(vertical_scintillators_);
}

void B2DetectorConstruction::ConstructYasuTracker(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  char scint_name[name_length_];

  // Scintillator for YASU Trackers
  auto *yasu_int_box = new G4Box("yasu_int_box", yasu_sci_x_, yasu_sci_y_, yasu_sci_z_);
  auto *yasu_int_lv = new G4LogicalVolume(yasu_int_box, plastic_, "yasu_int_box");
  yasu_int_lv->SetVisAttributes(sci_vis_att_);

  // YASU Trackers
  for (int plane = 0; plane < YASU_NUM_PLANES; plane++) {
    for (int channel = 0; channel < YASU_NUM_SLOTS_ONE_PLANE; channel++) {
      TVector3 pos;
      dimension_.get().GetPosYasu(plane, channel, pos);
      std::snprintf(scint_name, name_length_, "yasulayer[%d][%d][%d]", det, plane, channel);
      new G4PVPlacement(nullptr, root_v_to_geant_v(pos), yasu_int_lv, scint_name, module_lv, false,
                        channel + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }
  }

  //*******Assignment of sensitive detectors*******//
  p_sd_manager->AddNewDetector(horizontal_scintillators_);
  yasu_int_lv->SetSensitiveDetector(horizontal_scintillators_);
}


void B2DetectorConstruction::ConstructNinja(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {
  ConstructNinjaRack(module_lv, det);
  ConstructNinjaTracker(p_sd_manager, module_lv, det);
  ConstructNinjaTSSs(p_sd_manager, module_lv, det);
  ConstructNinjaShifter(p_sd_manager, module_lv, det);
  ConstructNinjaOSSs(p_sd_manager, module_lv, det);
  ConstructNinjaECCs(p_sd_manager, module_lv, det);
  ConstructNinjaSSSs(p_sd_manager, module_lv, det);
}


void B2DetectorConstruction::ConstructNinjaRack(G4LogicalVolume *module_lv, int det) {

  auto *nj_rack_pillar_ = new G4Box("nj_rack_pillar_", nj_rack_pillar_x_, nj_rack_pillar_y_, nj_rack_pillar_z_);
  auto *nj_rack_plate_ = new G4Box("nj_rack_plate_", nj_rack_plate_x_, nj_rack_plate_y_, nj_rack_plate_z_);
  G4VSolid *nj_rack = nj_rack_pillar_;

  // Loop for pillars of the rack
  for (int pillar = 1; pillar < 4; pillar++) {
    G4VSolid *nj_rack_tmp_ = new G4UnionSolid("", nj_rack, nj_rack_pillar_, nullptr,
                                              G4ThreeVector((pillar % 2) * 2. * (nj_rack_plate_x_ + nj_rack_pillar_x_),
                                                            0,
                                                            -std::floor(pillar / 2.) * 2. *
                                                            (nj_rack_plate_z_ + nj_rack_pillar_z_)));
    nj_rack = nj_rack_tmp_;
  }

  // Loop for plates of the rack
  for (double plate : nj_rack_plate_height_) {
    G4VSolid *nj_rack_tmp_ = new G4UnionSolid("", nj_rack, nj_rack_plate_, nullptr,
                                              G4ThreeVector(nj_rack_pillar_x_ + nj_rack_plate_x_,
                                                            -nj_rack_pillar_y_ + plate,
                                                            -nj_rack_pillar_z_ - nj_rack_plate_z_));
    nj_rack = nj_rack_tmp_;
  }

  auto *nj_rack_lv = new G4LogicalVolume(nj_rack, iron_, "nj_rack_lv_");
  nj_rack_lv->SetVisAttributes(iron_vis_att_);
  new G4PVPlacement(nullptr, nj_rack_pos_, nj_rack_lv, "nj_rack", module_lv, false, det);

}

void B2DetectorConstruction::ConstructNinjaTracker(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  // Rotation matrices
  auto *y_rot = new G4RotationMatrix(G4ThreeVector(0, 1, 0), -90. * degree);
  auto *y_rot_rev = new G4RotationMatrix(G4ThreeVector(0, 1, 0), 90. * degree);
  y_rot_rev->rotateX(180. * degree);
  auto *x_rot = new G4RotationMatrix(G4ThreeVector(1, 0, 0), -90. * degree);
  auto *x_rot_rev = new G4RotationMatrix(G4ThreeVector(1, 0, 0), 90. * degree);
  x_rot_rev->rotateY(180. * degree);
  auto *pvc_rot = new G4RotationMatrix(G4ThreeVector(0, 1, 0), 180. * degree);
  pvc_rot->rotateZ(90. * degree);

  auto *nj_tracker = new G4Box("nj_tracker", nj_tracker_box_xy_, nj_tracker_box_xy_, nj_tracker_box_z_);
  auto *nj_tracker_lv = new G4LogicalVolume(nj_tracker, air_, "nj_tracker_lv");
  nj_tracker_lv->SetVisAttributes(box_vis_att_);

  // Aluminum frame for the NINJA tracker
  auto *nj_tracker_frame_out_ = new G4Box("nj_tracker_frame_out_", nj_tracker_frame_xy_, nj_tracker_frame_xy_,
                                          nj_tracker_frame_z_);
  auto *nj_tracker_frame_in_ = new G4Box("nj_tracker_frame_in_",
                                         nj_tracker_frame_xy_ - nj_tracker_frame_thick_,
                                         nj_tracker_frame_xy_ - nj_tracker_frame_thick_,
                                         nj_tracker_frame_z_);
  G4VSolid *nj_tracker_frame = new G4SubtractionSolid("nj_tracker_frame", nj_tracker_frame_out_, nj_tracker_frame_in_);
  auto *nj_tracker_frame_lv = new G4LogicalVolume(nj_tracker_frame, Al, "nj_tracker_frame_lv");
  nj_tracker_frame_lv->SetVisAttributes(aluminum_vis_att_);

  // Pillars of PVC
  auto *nj_tracker_pvc_pillar_thin_ = new G4Box("nj_tracker_pvc_pillar_thin_",
                                                nj_tracker_pvc_pillar_thin_x_, nj_tracker_pvc_pillar_y_,
                                                nj_tracker_pvc_pillar_z_);
  auto *nj_tracker_pvc_pillar_thick_ = new G4Box("nj_tracker_pvc_pillar_thick_",
                                                 nj_tracker_pvc_pillar_thick_x_, nj_tracker_pvc_pillar_y_,
                                                 nj_tracker_pvc_pillar_z_);

  // Plates of PVC
  auto *nj_tracker_pvc_plate_large_ = new G4Box("nj_tracker_pvc_plate_large_",
                                                nj_tracker_pvc_plate_x_, nj_tracker_pvc_plate_large_y_,
                                                nj_tracker_pvc_plate_z_);
  auto *nj_tracker_pvc_plate_small_ = new G4Box("nj_tracker_pvc_plate_small_",
                                                nj_tracker_pvc_plate_x_, nj_tracker_pvc_plate_small_y_,
                                                nj_tracker_pvc_plate_z_);
  G4VSolid *nj_tracker_pvc_plate_ = new G4UnionSolid("nj_tracker_pvc_plate_", nj_tracker_pvc_plate_large_,
                                                     nj_tracker_pvc_plate_small_, nullptr,
                                                     G4ThreeVector(0, -nj_tracker_pvc_plate_large_y_ -
                                                                      nj_tracker_pvc_plate_gap_
                                                                      - nj_tracker_pvc_plate_small_y_, 0));
  G4VSolid *nj_tracker_pvc_plate_tmp_ = new G4UnionSolid("nj_tracker_pvc_plate_tmp_", nj_tracker_pvc_plate_,
                                                         nj_tracker_pvc_plate_small_, nullptr,
                                                         G4ThreeVector(0, -nj_tracker_pvc_plate_large_y_ -
                                                                          2 * nj_tracker_pvc_plate_gap_
                                                                          - 3 * nj_tracker_pvc_plate_small_y_, 0));
  nj_tracker_pvc_plate_ = nj_tracker_pvc_plate_tmp_;

  // PVC structure unit
  G4VSolid *nj_tracker_pvc_unit_out_ = new G4UnionSolid("nj_tracker_pvc_unit_out_", nj_tracker_pvc_pillar_thin_,
                                                        nj_tracker_pvc_plate_, nullptr,
                                                        G4ThreeVector(
                                                            nj_tracker_pvc_pillar_thin_x_ + nj_tracker_pvc_plate_x_,
                                                            nj_tracker_pvc_pillar_y_ - nj_tracker_pvc_plate_large_y_,
                                                            -nj_tracker_pvc_pillar_z_ + nj_tracker_pvc_pillar_offset_ +
                                                            nj_tracker_pvc_plate_z_));
  G4VSolid *nj_tracker_pvc_unit_out_tmp_ = new G4UnionSolid("nj_tracker_pvc_unit_out_tmp_", nj_tracker_pvc_unit_out_,
                                                            nj_tracker_pvc_pillar_thick_, nullptr,
                                                            G4ThreeVector(nj_tracker_pvc_pillar_thin_x_ +
                                                                          2 * nj_tracker_pvc_plate_x_
                                                                          + nj_tracker_pvc_pillar_thick_x_, 0, 0));
  nj_tracker_pvc_unit_out_ = nj_tracker_pvc_unit_out_tmp_;

  G4VSolid *nj_tracker_pvc_unit_in_ = new G4UnionSolid("nj_tracker_pvc_unit_in_", nj_tracker_pvc_pillar_thin_,
                                                       nj_tracker_pvc_plate_, nullptr,
                                                       G4ThreeVector(
                                                           nj_tracker_pvc_pillar_thin_x_ + nj_tracker_pvc_plate_x_,
                                                           nj_tracker_pvc_pillar_y_ - nj_tracker_pvc_plate_large_y_,
                                                           nj_tracker_pvc_pillar_z_ - nj_tracker_pvc_pillar_offset_ -
                                                           nj_tracker_pvc_plate_z_));
  G4VSolid *nj_tracker_pvc_unit_in_tmp_ = new G4UnionSolid("nj_tracker_pvc_unit_in_tmp_", nj_tracker_pvc_unit_in_,
                                                           nj_tracker_pvc_pillar_thick_, nullptr,
                                                           G4ThreeVector(nj_tracker_pvc_pillar_thin_x_ +
                                                                         2 * nj_tracker_pvc_plate_x_
                                                                         + nj_tracker_pvc_pillar_thick_x_, 0, 0));
  nj_tracker_pvc_unit_in_ = nj_tracker_pvc_unit_in_tmp_;

  // X (or Y) PVC structure
  G4VSolid *nj_tracker_pvc = new G4UnionSolid("nj_tracker_pvc", nj_tracker_pvc_unit_out_, nj_tracker_pvc_unit_in_,
                                              nullptr,
                                              G4ThreeVector(0, 0, -2 * nj_tracker_pvc_pillar_z_));
  auto *nj_tracker_pvc_lv = new G4LogicalVolume(nj_tracker_pvc, PVC, "nj_tracker_pvc_lv");
  nj_tracker_pvc_lv->SetVisAttributes(pvc_vis_att_);

  //********** Scintillator for tracking plane**********//

  // Scintillator dimension for NINJA (same as WAGASCI )
  std::vector<G4TwoVector> nj_vertical_dim;  // vertical-layer scintillator (internal)
  std::vector<G4TwoVector> nj_horizontal_dim;  // horizontal-layer scintillator (internal)
  for (std::size_t iver = 0; iver < num_scintillator_vertices_; iver++) {
    nj_vertical_dim.emplace_back(wagasci_vertex_x_[iver], wagasci_vertex_y_[iver]);
    nj_horizontal_dim.emplace_back(wagasci_vertex_y_[num_scintillator_vertices_ - 1 - iver],
                                   wagasci_vertex_x_[num_scintillator_vertices_ - 1 - iver]);
  }

  std::vector<G4ExtrudedSolid::ZSection> nj_horiz_z_section;
  std::vector<G4ExtrudedSolid::ZSection> nj_verti_z_section;
  nj_horiz_z_section.emplace_back(-nj_horiz_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1.);
  nj_horiz_z_section.emplace_back(nj_horiz_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1.);
  nj_verti_z_section.emplace_back(-nj_verti_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1.);
  nj_verti_z_section.emplace_back(nj_verti_sci_length_, G4TwoVector(0 * mm, 0 * mm), 1.);

  // NINJA vertical scintillator

#ifdef WITH_G4VIS
  auto *v_nj_scint_int = new G4ExtrudedSolid("v_nj_scint_int", nj_vertical_dim, nj_verti_z_section);
#else
  auto *v_nj_scint_tmp = new G4ExtrudedSolid("v_nj_scint_tmp", nj_vertical_dim, nj_verti_z_section);
  auto *v_glue = new G4Box("v_glue", 0.61 * mm, 0.61 * mm, nj_verti_sci_length_ + 0.1 * mm); //add 0.1 mm to avoid bug
  auto *v_nj_scint_int = new G4SubtractionSolid("v_nj_scint_int", v_nj_scint_tmp, v_glue, nullptr,
                                                G4ThreeVector(-3.9 * mm, -0.9 * mm, 0 * mm));
#endif
  auto *v_nj_scint_int_lv = new G4LogicalVolume(v_nj_scint_int, plastic_, "v_nj_scint_int_lv");
  v_nj_scint_int_lv->SetVisAttributes(sci_vis_att_);

  // NINJA horizontal scintillator
#ifdef WITH_G4VIS
  auto *h_nj_scint_int = new G4ExtrudedSolid("h_nj_scint_int", nj_horizontal_dim, nj_horiz_z_section);
#else
  auto *h_nj_scint_tmp = new G4ExtrudedSolid("h_nj_scint_tmp", nj_horizontal_dim, nj_horiz_z_section);
  auto *h_glue = new G4Box("h_glue", 0.61 * mm, 0.61 * mm, nj_horiz_sci_length_ + 0.1 * mm); //add 0.1 mm to avoid bug
  auto *h_nj_scint_int = new G4SubtractionSolid("h_nj_scint_int", h_nj_scint_tmp, h_glue, nullptr,
                                                G4ThreeVector(0.9 * mm, -3.9 * mm, 0 * mm));
#endif
  auto *h_nj_scint_int_lv = new G4LogicalVolume(h_nj_scint_int, plastic_, "h_nj_scint_int_lv");
  h_nj_scint_int_lv->SetVisAttributes(sci_vis_att_);


  // Overall box
  new G4PVPlacement(nullptr, nj_tracker_pos_, nj_tracker_lv, "nj_tracker", module_lv, false, det);

  // Aluminum frame
  new G4PVPlacement(nullptr, origin_, nj_tracker_frame_lv, "nj_tracker_frame", nj_tracker_lv, false, det);

  // PVC plate for vertical scintillators (downstream)
  new G4PVPlacement(nullptr,
                    G4ThreeVector(-nj_tracker_frame_xy_ + nj_tracker_frame_thick_ + nj_tracker_pvc_pillar_thin_x_, 0.,
                                  nj_tracker_frame_z_ - nj_tracker_pvc_pillar_z_), nj_tracker_pvc_lv,
                    "nj_tracker_pvc_down", nj_tracker_lv, false, det);

  // PVC plate for horizontal scintillators (upstream)
  new G4PVPlacement(pvc_rot,
                    G4ThreeVector(0., nj_tracker_frame_xy_ - nj_tracker_frame_thick_ - nj_tracker_pvc_pillar_thin_x_,
                                  -nj_tracker_frame_z_ + nj_tracker_pvc_pillar_z_), nj_tracker_pvc_lv,
                    "nj_tracker_pvc_up", nj_tracker_lv, false, det);

  // Scintillator bars
  char scint_name[name_length_];
  for (int plane = 0; plane < NINJA_TRACKER_NUM_PLANES; plane++) { // 4 planes
    for (int slot = 0; slot < NINJA_TRACKER_NUM_CHANNELS_ONE_PLANE; slot++) { // 31 bars
      TVector3 pos;
      // Horizontal scintillators
      dimension_.get().GetPosNinjaTracker(B2View::kSideView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "hlayer[%d][%d][%d]", det, plane, slot);
      if (plane % 2 == 0)
        new G4PVPlacement(y_rot, root_v_to_geant_v(pos), h_nj_scint_int_lv, scint_name, nj_tracker_lv, false,
                          slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      else
        new G4PVPlacement(y_rot_rev, root_v_to_geant_v(pos), h_nj_scint_int_lv, scint_name, nj_tracker_lv, false,
                          slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      // Vertical scintillators
      dimension_.get().GetPosNinjaTracker(B2View::kTopView, plane, slot, pos);
      std::snprintf(scint_name, name_length_, "vlayer[%d][%d][%d]", det, plane, slot);
      if (plane % 2 == 0)
        new G4PVPlacement(x_rot, root_v_to_geant_v(pos), v_nj_scint_int_lv, scint_name, nj_tracker_lv, false,
                          slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
      else
        new G4PVPlacement(x_rot_rev, root_v_to_geant_v(pos), v_nj_scint_int_lv, scint_name, nj_tracker_lv, false,
                          slot + plane * MAX_NUM_CHANNELS + det * MAX_NUM_PLANES * MAX_NUM_CHANNELS);
    }//end of planes
  }//end of bars

  //*******Assignment of sensitive detectors*******/
#ifdef NINJA
  // Horizontal scintillator bars for NINJA tracker
  p_sd_manager->AddNewDetector(horizontal_scintillators_);
  h_nj_scint_int_lv->SetSensitiveDetector(horizontal_scintillators_);
  // Vertical scintillator bars for NINJA tracker
  p_sd_manager->AddNewDetector(vertical_scintillators_);
  v_nj_scint_int_lv->SetSensitiveDetector(vertical_scintillators_);
#endif
}


void B2DetectorConstruction::ConstructNinjaTSSs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  // Acryl plate attached on the NINJA tracker
  auto *nj_tss_acryl_out_ = new G4Box("nj_tss_acryl_out_", nj_tss_acryl_out_x_, nj_tss_acryl_out_y_, nj_tss_acryl_z_);
  auto *nj_tss_acryl_in_ = new G4Box("nj_tss_acryl_in_", nj_tss_acryl_in_x_, nj_tss_acryl_in_y_, nj_tss_acryl_z_);
  G4VSolid *nj_tss_acryl = new G4SubtractionSolid("nj_tss_acryl", nj_tss_acryl_out_, nj_tss_acryl_in_, nullptr,
                                                  G4ThreeVector(nj_tss_acryl_out_x_ - nj_tss_acryl_in_x_, 0, 0));
  auto *nj_tss_acryl_lv = new G4LogicalVolume(nj_tss_acryl, Acryl, "nj_tss_acryl_lv");

  new G4PVPlacement(nullptr, nj_tss_pos_, nj_tss_acryl_lv, "nj_tss_acryl", module_lv, false, det);

  for (int packing = 0; packing < 3; packing++) {
    ConstructNinjaOneTSS(p_sd_manager, module_lv, det, packing);
  }

}

void B2DetectorConstruction::ConstructNinjaOneTSS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det,
                                                  int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_tss_env = new G4Box("nj_tss_env", nj_tss_env_x_, nj_tss_env_y_, nj_tss_env_z_);
  std::snprintf(env_name, name_length_, "nj_tss_env_lv[%d]", 3 * packing);
  auto *nj_tss_env_lv = new G4LogicalVolume(nj_tss_env, Nylon, env_name);

  auto *nj_tss_env_al = new G4Box("nj_tss_env_al", nj_tss_env_x_ - nj_env_ny_thick_, nj_tss_env_y_ - nj_env_ny_thick_,
                                  nj_tss_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_tss_env_al_lv[%d]", 3 * packing);
  auto *nj_tss_env_al_lv = new G4LogicalVolume(nj_tss_env_al, Al, env_name);

  auto *nj_tss_env_polye = new G4Box("nj_tss_env_polye", nj_tss_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_tss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_tss_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_tss_env_polye_lv[%d]", 3 * packing);
  auto *nj_tss_env_polye_lv = new G4LogicalVolume(nj_tss_env_polye, Polyethylene, env_name);

  auto *nj_tss_ssacryl = new G4Box("nj_tss_ssacryl", nj_tss_film_x_, nj_tss_film_y_, nj_tss_ssacryl_z_);
  auto *nj_tss_ssacryl_lv = new G4LogicalVolume(nj_tss_ssacryl, Acryl, "nj_tss_ssacryl_lv");

  // Placement
  std::snprintf(lv_name, name_length_, "nj_tss_env_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 2 * nj_tss_env_y_ * (1 - packing),
                                           nj_tss_pos_.z() - nj_tss_acryl_z_ - nj_tss_env_z_),
                    nj_tss_env_lv, lv_name, module_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_tss_env_al_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_tss_env_al_lv, lv_name, nj_tss_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_tss_env_polye_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_tss_env_polye_lv, lv_name, nj_tss_env_al_lv, false, det);

  G4double posz = -nj_tss_env_z_ + nj_env_thick_ + nj_film_z_;
  for (int plate = 14; plate < 16; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_tss_env_polye_lv, det,
                       B2EmulsionType::kShifter, 3 * packing, plate,
                       G4ThreeVector(0, 0, posz), nj_tss_film_x_, nj_tss_film_y_);
    posz += nj_film_thick_;
  }

  posz += -nj_film_z_ + nj_tss_ssacryl_z_;
  std::snprintf(lv_name, name_length_, "nj_tss_ssacryl[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, posz), nj_tss_ssacryl_lv, lv_name, nj_tss_env_polye_lv, false, det);
  posz += nj_tss_ssacryl_z_ + nj_film_z_;

  for (int plate = 16; plate < 18; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_tss_env_polye_lv, det,
                       B2EmulsionType::kShifter, 3 * packing, plate,
                       G4ThreeVector(0, 0, posz), nj_tss_film_x_, nj_tss_film_y_);
    posz += nj_film_thick_;
  }

}

void B2DetectorConstruction::ConstructNinjaShifter(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  auto *nj_shifter = new G4Box("nj_shifter", nj_shifter_box_x_, nj_shifter_box_y_, nj_shifter_box_z_);
  auto *nj_shifter_lv = new G4LogicalVolume(nj_shifter, air_, "nj_shifter_lv");
  nj_shifter_lv->SetVisAttributes(box_vis_att_);

  new G4PVPlacement(nullptr, nj_shifter_pos_, nj_shifter_lv, "nj_shifter", module_lv, false, det);

  // Moving wall aluminum plate
  auto *nj_shifter_move_al = new G4Box("nj_shifter_move_al", nj_shifter_move_al_x_, nj_shifter_move_al_y_,
                                       nj_shifter_move_al_z_);
  auto *nj_shifter_move_al_lv = new G4LogicalVolume(nj_shifter_move_al, Alhoney, "nj_shifter_move_al_lv");
  nj_shifter_move_al_lv->SetVisAttributes(aluminum_vis_att_);

  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, -nj_shifter_box_z_ + nj_shifter_move_al_z_), nj_shifter_move_al_lv,
                    "nj_shifter_move_al_up", nj_shifter_lv, false, det);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, nj_shifter_box_z_ - nj_shifter_move_al_z_), nj_shifter_move_al_lv,
                    "nj_shifter_move_al_down", nj_shifter_lv, false, det);

  for (int packing = 0; packing < 3; packing++) {
    ConstructNinjaShifterOneUpMove(p_sd_manager, nj_shifter_lv, det, packing);
    ConstructNinjaShifterOneFixed(p_sd_manager, nj_shifter_lv, det, packing);
    ConstructNinjaShifterOneDownMove(p_sd_manager, nj_shifter_lv, det, packing);
  }
}


void
B2DetectorConstruction::ConstructNinjaShifterOneUpMove(G4SDManager *p_sd_manager, G4LogicalVolume *shifter_lv, int det,
                                                       int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_shifter_move_env = new G4Box("nj_shifter_move_env", nj_tss_env_x_, nj_tss_env_y_, nj_shifter_move_env_z_);
  std::snprintf(env_name, name_length_, "nj_shifter_move_up_env_lv[%d]", 3 * packing);
  auto *nj_shifter_move_env_lv = new G4LogicalVolume(nj_shifter_move_env, Nylon, env_name);

  auto *nj_shifter_move_env_al = new G4Box("nj_shifter_move_env_al", nj_tss_env_x_ - nj_env_ny_thick_,
                                           nj_tss_env_y_ - nj_env_ny_thick_,
                                           nj_shifter_move_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_shifter_move_up_env_al_lv[%d]", 3 * packing);
  auto *nj_shifter_move_env_al_lv = new G4LogicalVolume(nj_shifter_move_env_al, Al, env_name);

  auto *nj_shifter_move_env_polye = new G4Box("nj_shifter_move_env_polye",
                                              nj_tss_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                              nj_tss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                              nj_shifter_move_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_shifter_move_up_env_polye_lv[%d]", 3 * packing);
  auto *nj_shifter_move_env_polye_lv = new G4LogicalVolume(nj_shifter_move_env_polye, Polyethylene, env_name);

  auto *nj_shifter_move_acryl = new G4Box("nj_shifter_move_acryl", nj_tss_film_x_, nj_tss_film_y_,
                                          nj_shifter_move_acryl_z_);
  auto *nj_shifter_move_acryl_lv = new G4LogicalVolume(nj_shifter_move_acryl, Acryl, "nj_shifter_move_acryl_lv");

  // Placement
  std::snprintf(lv_name, name_length_, "nj_shfiter_move_up_env_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 2 * nj_tss_env_y_ * (1 - packing),
                                           -nj_shifter_box_z_ + 2 * nj_shifter_move_al_z_ + nj_shifter_move_env_z_),
                    nj_shifter_move_env_lv, lv_name, shifter_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_shifter_move_up_env_al_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_shifter_move_env_al_lv, lv_name, nj_shifter_move_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_shifter_move_up_env_polye_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_shifter_move_env_polye_lv, lv_name, nj_shifter_move_env_al_lv, false, det);

  G4double posz = -nj_shifter_move_env_z_ + nj_env_thick_;
  posz += nj_shifter_move_acryl_z_;
  std::snprintf(lv_name, name_length_, "nj_shifter_move_up_acryl[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, posz), nj_shifter_move_acryl_lv, lv_name, nj_shifter_move_env_polye_lv,
                    false, det);
  posz += nj_shifter_move_acryl_z_ + nj_film_z_;
  for (int plate = 4; plate < 7; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_shifter_move_env_polye_lv, det,
                       B2EmulsionType::kShifter, 3 * packing, plate,
                       G4ThreeVector(0, 0, posz), nj_tss_film_x_, nj_tss_film_y_);
    posz += nj_film_thick_;
  }

}

void
B2DetectorConstruction::ConstructNinjaShifterOneFixed(G4SDManager *p_sd_manager, G4LogicalVolume *shifter_lv, int det,
                                                      int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_shifter_fix_env = new G4Box("nj_shifter_fix_env", nj_tss_env_x_, nj_tss_env_y_, nj_shifter_fix_env_z_);
  std::snprintf(env_name, name_length_, "nj_shifter_fix_env_lv[%d]", 3 * packing);
  auto *nj_shifter_fix_env_lv = new G4LogicalVolume(nj_shifter_fix_env, Nylon, env_name);

  auto *nj_shifter_fix_env_al = new G4Box("nj_shifter_fix_env_al", nj_tss_env_x_ - nj_env_ny_thick_,
                                          nj_tss_env_y_ - nj_env_ny_thick_,
                                          nj_shifter_fix_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_shifter_fix_env_al_lv[%d]", 3 * packing);
  auto *nj_shifter_fix_env_al_lv = new G4LogicalVolume(nj_shifter_fix_env_al, Al, env_name);

  auto *nj_shifter_fix_env_polye = new G4Box("nj_shifter_fix_env_polye",
                                             nj_tss_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                             nj_tss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                             nj_shifter_fix_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_shifter_fix_env_polye_lv[%d]", 3 * packing);
  auto *nj_shifter_fix_env_polye_lv = new G4LogicalVolume(nj_shifter_fix_env_polye, Polyethylene, env_name);

  auto *nj_shifter_fix_acryl = new G4Box("nj_shifter_fix_acryl", nj_tss_film_x_, nj_tss_film_y_,
                                         nj_shifter_fix_acryl_z_);
  auto *nj_shifter_fix_acryl_lv = new G4LogicalVolume(nj_shifter_fix_acryl, Acryl, "nj_shifter_fix_acryl_lv");

  // Placement
  std::snprintf(lv_name, name_length_, "nj_shfiter_fix_env_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 2 * nj_tss_env_y_ * (1 - packing), 0),
                    nj_shifter_fix_env_lv, lv_name, shifter_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_shifter_fix_env_al_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_shifter_fix_env_al_lv, lv_name, nj_shifter_fix_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_shifter_fix_env_polye_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_shifter_fix_env_polye_lv, lv_name, nj_shifter_fix_env_al_lv, false, det);

  G4double posz = -nj_shifter_fix_env_z_ + nj_env_thick_ + nj_film_z_;
  for (int plate = 7; plate < 9; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_shifter_fix_env_polye_lv, det,
                       B2EmulsionType::kShifter, 3 * packing, plate,
                       G4ThreeVector(0, 0, posz), nj_tss_film_x_, nj_tss_film_y_);
    posz += nj_film_thick_;
  }

  posz += -nj_film_z_ + nj_shifter_fix_acryl_z_;
  std::snprintf(lv_name, name_length_, "nj_shifter_fix_acryl[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, posz), nj_shifter_fix_acryl_lv, lv_name, nj_shifter_fix_env_polye_lv,
                    false, det);
  posz += nj_shifter_fix_acryl_z_ + nj_film_z_;

  for (int plate = 9; plate < 11; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_shifter_fix_env_polye_lv, det,
                       B2EmulsionType::kShifter, 3 * packing, plate,
                       G4ThreeVector(0, 0, posz), nj_tss_film_x_, nj_tss_film_y_);
    posz += nj_film_thick_;
  }

}

void B2DetectorConstruction::ConstructNinjaShifterOneDownMove(G4SDManager *p_sd_manager, G4LogicalVolume *shifter_lv,
                                                              int det, int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_shifter_move_env = new G4Box("nj_shifter_move_env", nj_tss_env_x_, nj_tss_env_y_, nj_shifter_move_env_z_);
  std::snprintf(env_name, name_length_, "nj_shifter_move_down_env_lv[%d]", 3 * packing);
  auto *nj_shifter_move_env_lv = new G4LogicalVolume(nj_shifter_move_env, Nylon, env_name);

  auto *nj_shifter_move_env_al = new G4Box("nj_shifter_move_env_al", nj_tss_env_x_ - nj_env_ny_thick_,
                                           nj_tss_env_y_ - nj_env_ny_thick_,
                                           nj_shifter_move_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_shifter_move_down_env_al_lv[%d]", 3 * packing);
  auto *nj_shifter_move_env_al_lv = new G4LogicalVolume(nj_shifter_move_env_al, Al, env_name);

  auto *nj_shifter_move_env_polye = new G4Box("nj_shifter_move_env_polye",
                                              nj_tss_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                              nj_tss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                              nj_shifter_move_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_shifter_move_down_env_polye_lv[%d]", 3 * packing);
  auto *nj_shifter_move_env_polye_lv = new G4LogicalVolume(nj_shifter_move_env_polye, Polyethylene, env_name);

  auto *nj_shifter_move_acryl = new G4Box("nj_shifter_move_acryl", nj_tss_film_x_, nj_tss_film_y_,
                                          nj_shifter_move_acryl_z_);
  auto *nj_shifter_move_acryl_lv = new G4LogicalVolume(nj_shifter_move_acryl, Acryl, "nj_shifter_move_acryl_lv");

  // Placement
  std::snprintf(lv_name, name_length_, "nj_shfiter_move_down_env_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 2 * nj_tss_env_y_ * (1 - packing),
                                           nj_shifter_box_z_ - 2 * nj_shifter_move_al_z_ - nj_shifter_move_env_z_),
                    nj_shifter_move_env_lv, lv_name, shifter_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_shifter_move_down_env_al_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_shifter_move_env_al_lv, lv_name, nj_shifter_move_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_shifter_move_down_env_polye_lv[%d]", 3 * packing);
  new G4PVPlacement(nullptr, origin_, nj_shifter_move_env_polye_lv, lv_name, nj_shifter_move_env_al_lv, false, det);

  G4double posz = -nj_shifter_move_env_z_ + nj_env_thick_ + nj_film_z_;
  for (int plate = 11; plate < 14; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_shifter_move_env_polye_lv, det,
                       B2EmulsionType::kShifter, 3 * packing, plate,
                       G4ThreeVector(0, 0, posz), nj_tss_film_x_, nj_tss_film_y_);
    posz += nj_film_thick_;
  }

  posz += -nj_film_z_ + nj_shifter_move_acryl_z_;
  std::snprintf(lv_name, name_length_, "nj_shifter_move_down_acryl[%d]", 3 * packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, posz), nj_shifter_move_acryl_lv, lv_name, nj_shifter_move_env_polye_lv,
                    false, det);

}

void B2DetectorConstruction::ConstructNinjaOSSs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  char lv_name[name_length_];
  // Acryl for Outside SS attachment
  auto *nj_oss_acryl = new G4Box("nj_oss_acryl", nj_oss_acryl_xy_, nj_oss_acryl_xy_, nj_oss_acryl_z_);
  auto *nj_oss_acryl_lv = new G4LogicalVolume(nj_oss_acryl, Acryl, "nj_oss_acryl_lv");

  for (int packing = 0; packing < 9; packing++) {
    if (packing % 3 != 1) {
      std::snprintf(lv_name, name_length_, "nj_oss_acryl[%d]", packing);
      new G4PVPlacement(nullptr, G4ThreeVector(nj_ecc_pos_.x() + nj_ecc_gap_x_ * (packing % 3 - 1),
                                               nj_ecc_pos_.y() + nj_ecc_gap_y_ * (1 - std::floor(packing / 3.))
                                               - nj_desic_y_ + nj_oss_acryl_xy_ + nj_oss_acryl_offset_,
                                               nj_ecc_pos_.z() + nj_desic_z_ + nj_oss_acryl_z_),
                        nj_oss_acryl_lv, lv_name, module_lv, false, det);
    }
    ConstructNinjaOneOSS(p_sd_manager, module_lv, det, packing);
  }
}

void B2DetectorConstruction::ConstructNinjaOneOSS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det,
                                                  int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_oss_env = new G4Box("nj_oss_env", nj_oss_env_x_, nj_oss_env_y_, nj_oss_env_z_);
  std::snprintf(env_name, name_length_, "nj_oss_env_lv[%d]", packing);
  auto *nj_oss_env_lv = new G4LogicalVolume(nj_oss_env, Nylon, env_name);

  auto *nj_oss_env_al = new G4Box("nj_oss_env_al", nj_oss_env_x_ - nj_env_ny_thick_, nj_oss_env_y_ - nj_env_ny_thick_,
                                  nj_oss_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_oss_env_al_lv[%d]", packing);
  auto *nj_oss_env_al_lv = new G4LogicalVolume(nj_oss_env_al, Al, env_name);

  auto *nj_oss_env_polye = new G4Box("nj_oss_env_polye", nj_oss_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_oss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_oss_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_oss_env_polye_lv[%d]", packing);
  auto *nj_oss_env_polye_lv = new G4LogicalVolume(nj_oss_env_polye, Polyethylene, env_name);

  auto *nj_oss_ssacryl = new G4Box("nj_oss_ssacryl", nj_oss_film_x_, nj_oss_film_y_, nj_oss_ssacryl_z_);
  auto *nj_oss_ssacryl_lv = new G4LogicalVolume(nj_oss_ssacryl, Acryl, "nj_oss_ssacryl_lv");


  // Placement
  G4double oss_acryl_thick_;
  if (packing % 3 == 1) oss_acryl_thick_ = 0;
  else oss_acryl_thick_ = 2 * nj_oss_acryl_z_;
  std::snprintf(lv_name, name_length_, "nj_oss_env_lv[%d]", packing);
  new G4PVPlacement(nullptr, G4ThreeVector(nj_ecc_pos_.x() + nj_ecc_gap_x_ * (packing % 3 - 1),
                                           nj_ecc_pos_.y() + nj_ecc_gap_y_ * (1 - std::floor(packing / 3.))
                                           - nj_desic_y_ + nj_oss_env_y_ + nj_oss_acryl_offset_,
                                           nj_ecc_pos_.z() + nj_desic_z_ + nj_oss_env_z_ + oss_acryl_thick_),
                    nj_oss_env_lv, lv_name, module_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_oss_env_al_lv[%d]", packing);
  new G4PVPlacement(nullptr, origin_, nj_oss_env_al_lv, lv_name, nj_oss_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_oss_env_polye_lv[%d]", packing);
  new G4PVPlacement(nullptr, origin_, nj_oss_env_polye_lv, lv_name, nj_oss_env_al_lv, false, det);

  G4double posz = -nj_oss_env_z_ + nj_env_thick_ + nj_film_z_;
  for (int plate = 0; plate < 2; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_oss_env_polye_lv, det,
                       B2EmulsionType::kShifter, packing, plate,
                       G4ThreeVector(0, 0, posz), nj_oss_film_x_, nj_oss_film_y_);
    posz += nj_film_thick_;
  }

  posz += -nj_film_z_ + nj_oss_ssacryl_z_;
  std::snprintf(lv_name, name_length_, "nj_oss_ssacryl[%d]", packing);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, posz), nj_oss_ssacryl_lv, lv_name, nj_oss_env_polye_lv, false, det);
  posz += nj_oss_ssacryl_z_ + nj_film_z_;

  for (int plate = 2; plate < 4; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_oss_env_polye_lv, det,
                       B2EmulsionType::kShifter, packing, plate,
                       G4ThreeVector(0, 0, posz), nj_oss_film_x_, nj_oss_film_y_);
    posz += nj_film_thick_;
  }

}

void B2DetectorConstruction::ConstructNinjaECCs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {
  for (int chamber = 0; chamber < 9; chamber++) {
    ConstructNinjaOneECC(p_sd_manager, module_lv, det, chamber);
  }
}

void B2DetectorConstruction::ConstructNinjaOneECC(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det,
                                                  int chamber) {

  // Desiccator
  char desic_name[name_length_], lv_name[name_length_];
  auto *nj_desic = new G4Box("nj_desic", nj_desic_x_, nj_desic_y_, nj_desic_z_);
  std::snprintf(desic_name, name_length_, "nj_desic_lv[%d]", chamber);
  auto *nj_desic_lv = new G4LogicalVolume(nj_desic, Acryl, desic_name);

  // Water box
  auto *nj_water = new G4Box("nj_water", nj_water_x_, nj_water_y_, nj_water_z_);
  std::snprintf(desic_name, name_length_, "nj_water_lv[%d]", chamber);
  auto *nj_water_lv = new G4LogicalVolume(nj_water, water_, desic_name);
  nj_water_lv->SetVisAttributes(water_vis_att_);

  // Upstream acryl
  auto *nj_upacryl = new G4Box("nj_upacryl", nj_water_x_, nj_water_y_, nj_upacryl_z_);
  std::snprintf(desic_name, name_length_, "nj_upacryl_lv[%d]", chamber);
  auto *nj_upacryl_lv = new G4LogicalVolume(nj_upacryl, Acryl, desic_name);

  std::snprintf(lv_name, name_length_, "nj_desic[%d]", chamber);
  new G4PVPlacement(nullptr, G4ThreeVector(nj_ecc_pos_.x() + nj_ecc_gap_x_ * (chamber % 3 - 1),
                                           nj_ecc_pos_.y() + nj_ecc_gap_y_ * (1 - std::floor(chamber / 3.)),
                                           nj_ecc_pos_.z()), nj_desic_lv, lv_name, module_lv, false, det);

  std::snprintf(lv_name, name_length_, "nj_water[%d]", chamber);
  new G4PVPlacement(nullptr, origin_, nj_water_lv, lv_name, nj_desic_lv, false, det);

  std::snprintf(lv_name, name_length_, "nj_upacryl[%d]", chamber);
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, nj_water_z_ - 2 * nj_ecc_fe_env_z_
                                                 - 58 * 2 * (nj_ecc_unit_env_z_ + nj_ecc_water_layer_z_)
                                                 - 2 * nj_ecc_unit_env_z_ - nj_upacryl_z_),
                    nj_upacryl_lv, lv_name, nj_water_lv, false, det);

  ConstructNinjaIronECC(p_sd_manager, nj_water_lv, det, chamber);
  for (int unit = 0; unit < 59; unit++) {
    ConstructNinjaTrackingUnit(p_sd_manager, nj_water_lv, det, chamber, unit);
    if (unit != 58) ConstructNinjaWaterSpacer(nj_water_lv, det, chamber, unit);
  }
}


void B2DetectorConstruction::ConstructNinjaIronECC(G4SDManager *p_sd_manager, G4LogicalVolume *water_lv, int det,
                                                   int chamber) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_ecc_fe_env = new G4Box("nj_ecc_fe_env", nj_ecc_env_x_, nj_ecc_env_y_, nj_ecc_fe_env_z_);
  std::snprintf(env_name, name_length_, "nj_ecc_fe_env_lv[%d]", chamber);
  auto *nj_ecc_fe_env_lv = new G4LogicalVolume(nj_ecc_fe_env, Nylon, env_name);

  auto *nj_ecc_fe_env_al = new G4Box("nj_ecc_fe_env_al", nj_ecc_env_x_ - nj_env_ny_thick_,
                                     nj_ecc_env_y_ - nj_env_ny_thick_,
                                     nj_ecc_fe_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_ecc_fe_env_al_lv[%d]", chamber);
  auto *nj_ecc_fe_env_al_lv = new G4LogicalVolume(nj_ecc_fe_env_al, Al, env_name);

  auto *nj_ecc_fe_env_polye = new G4Box("nj_ecc_fe_env_polye", nj_ecc_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                        nj_ecc_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                        nj_ecc_fe_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_ecc_fe_env_polye_lv[%d]", chamber);
  auto *nj_ecc_fe_env_polye_lv = new G4LogicalVolume(nj_ecc_fe_env_polye, Polyethylene, env_name);

  // Spacer
  auto *nj_ecc_fe_spacer_out_ = new G4Box("nj_ecc_fe_spacer_out_", nj_ecc_spacer_x_, nj_ecc_spacer_y_,
                                          nj_ecc_fe_spacer_z_);
  auto *nj_ecc_fe_spacer_in_ = new G4Box("nj_ecc_fe_spacer_in_", nj_ecc_film_xy_, nj_ecc_film_xy_, nj_ecc_fe_spacer_z_);
  G4VSolid *nj_ecc_fe_spacer = new G4SubtractionSolid("nj_ecc_fe_spacer", nj_ecc_fe_spacer_out_, nj_ecc_fe_spacer_in_,
                                                      nullptr,
                                                      G4ThreeVector(0, -nj_ecc_spacer_thick_ / 2, 0));
  auto *nj_ecc_fe_spacer_lv = new G4LogicalVolume(nj_ecc_fe_spacer, Acryl, "nj_ecc_fe_spacer_lv");

  auto *nj_ecc_ssacryl = new G4Box("nj_ecc_ssacryl", nj_ecc_film_xy_, nj_ecc_film_xy_, nj_ecc_ssacryl_z_);
  auto *nj_ecc_ssacryl_lv = new G4LogicalVolume(nj_ecc_ssacryl, Acryl, "nj_ecc_ssacryl_lv");

  auto *nj_ecc_fe = new G4Box("nj_ecc_fe", nj_ecc_film_xy_, nj_ecc_film_xy_, nj_ecc_fe_z_);
  auto *nj_ecc_fe_lv = new G4LogicalVolume(nj_ecc_fe, SUS316L, "nj_ecc_fe_lv");
  nj_ecc_fe_lv->SetVisAttributes(iron_vis_att_);

  // Placement
  std::snprintf(lv_name, name_length_, "nj_ecc_fe_env_lv[%d]", chamber);
  new G4PVPlacement(nullptr, G4ThreeVector(0, -nj_water_y_ + nj_ecc_env_y_, nj_water_z_ - nj_ecc_fe_env_z_),
                    nj_ecc_fe_env_lv, lv_name, water_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_ecc_fe_env_al_lv[%d]", chamber);
  new G4PVPlacement(nullptr, origin_, nj_ecc_fe_env_al_lv, lv_name, nj_ecc_fe_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_ecc_fe_env_polye_lv[%d]", chamber);
  new G4PVPlacement(nullptr, origin_, nj_ecc_fe_env_polye_lv, lv_name, nj_ecc_fe_env_al_lv, false, det);

  std::snprintf(lv_name, name_length_, "nj_ecc_fe_spacer_lv[%d]", chamber);
  new G4PVPlacement(nullptr, origin_, nj_ecc_fe_spacer_lv, lv_name, nj_ecc_fe_env_polye_lv, false, det);

  G4double posz = nj_ecc_fe_env_z_ - nj_env_thick_ - nj_film_z_;
  for (int plate = 0; plate < 2; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_ecc_fe_env_polye_lv, det,
                       B2EmulsionType::kECC, chamber, plate,
                       G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz), nj_ecc_film_xy_,
                       nj_ecc_film_xy_);
    posz -= nj_film_thick_;
  }

  posz -= -nj_film_z_ + nj_ecc_ssacryl_z_;
  std::snprintf(lv_name, name_length_, "nj_ecc_ssacryl[%d]", chamber);
  new G4PVPlacement(nullptr, G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz),
                    nj_ecc_ssacryl_lv, lv_name, nj_ecc_fe_env_polye_lv, false, det);
  posz -= nj_ecc_ssacryl_z_ + nj_film_z_;

  for (int plate = 2; plate < 4; plate++) {
    ConstructNinjaFilm(p_sd_manager, nj_ecc_fe_env_polye_lv, det,
                       B2EmulsionType::kECC, chamber, plate,
                       G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz), nj_ecc_film_xy_,
                       nj_ecc_film_xy_);
    posz -= nj_film_thick_;
  }

  posz -= -nj_film_z_ + nj_ecc_fe_z_;
  for (int plate = 4; plate < 15; plate++) {
    std::snprintf(lv_name, name_length_, "nj_ecc_fe[%d][%d]", chamber, plate);
    new G4PVPlacement(nullptr, G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz),
                      nj_ecc_fe_lv, lv_name, nj_ecc_fe_env_polye_lv, false, det);
    posz -= nj_ecc_fe_z_ + nj_film_z_;
    ConstructNinjaFilm(p_sd_manager, nj_ecc_fe_env_polye_lv, det,
                       B2EmulsionType::kECC, chamber, plate,
                       G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz), nj_ecc_film_xy_,
                       nj_ecc_film_xy_);
    posz -= nj_film_z_ + nj_ecc_fe_z_;
  }

}

void B2DetectorConstruction::ConstructNinjaTrackingUnit(G4SDManager *p_sd_manager, G4LogicalVolume *water_lv, int det,
                                                        int chamber, int unit) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_];
  auto *nj_ecc_unit_env = new G4Box("nj_ecc_unit_env", nj_ecc_env_x_, nj_ecc_env_y_, nj_ecc_unit_env_z_);
  std::snprintf(env_name, name_length_, "nj_ecc_unit_env_lv[%d][%d]", chamber, unit);
  auto *nj_ecc_unit_env_lv = new G4LogicalVolume(nj_ecc_unit_env, Nylon, env_name);

  auto *nj_ecc_unit_env_al = new G4Box("nj_ecc_unit_env_al", nj_ecc_env_x_ - nj_env_ny_thick_,
                                       nj_ecc_env_y_ - nj_env_ny_thick_, nj_ecc_unit_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_ecc_unit_env_al_lv[%d][%d]", chamber, unit);
  auto *nj_ecc_unit_env_al_lv = new G4LogicalVolume(nj_ecc_unit_env_al, Al, env_name);

  auto *nj_ecc_unit_env_polye = new G4Box("nj_ecc_unit_env_polye", nj_ecc_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                          nj_ecc_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                          nj_ecc_unit_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_ecc_unit_env_polye_lv[%d][%d]", chamber, unit);
  auto *nj_ecc_unit_env_polye_lv = new G4LogicalVolume(nj_ecc_unit_env_polye, Polyethylene, env_name);

  // Spacer
  auto *nj_ecc_unit_spacer_out_ = new G4Box("nj_ecc_unit_spacer_out_", nj_ecc_spacer_x_, nj_ecc_spacer_y_,
                                            nj_ecc_unit_spacer_z_);
  auto *nj_ecc_unit_spacer_in_ = new G4Box("nj_ecc_unit_spacer_in_", nj_ecc_film_xy_, nj_ecc_film_xy_,
                                           nj_ecc_unit_spacer_z_);
  G4VSolid *nj_ecc_unit_spacer = new G4SubtractionSolid("nj_ecc_unit_spacer", nj_ecc_unit_spacer_out_,
                                                        nj_ecc_unit_spacer_in_, nullptr,
                                                        G4ThreeVector(0, -nj_ecc_spacer_y_ + nj_ecc_film_xy_, 0));
  std::snprintf(env_name, name_length_, "nj_ecc_unit_spacer_lv[%d][%d]", chamber, unit);
  auto *nj_ecc_unit_spacer_lv = new G4LogicalVolume(nj_ecc_unit_spacer, Acryl, env_name);

  auto *nj_ecc_fe = new G4Box("nj_ecc_fe", nj_ecc_film_xy_, nj_ecc_film_xy_, nj_ecc_fe_z_);
  auto *nj_ecc_fe_lv = new G4LogicalVolume(nj_ecc_fe, SUS316L, "nj_ecc_fe_lv");
  nj_ecc_fe_lv->SetVisAttributes(iron_vis_att_);

  // Placement
  std::snprintf(lv_name, name_length_, "nj_ecc_unit_env_lv[%d][%d]", chamber, unit);
  new G4PVPlacement(nullptr, G4ThreeVector(0, -nj_water_y_ + nj_ecc_env_y_,
                                           nj_water_z_ - 2 * nj_ecc_fe_env_z_
                                           - unit * 2 * (nj_ecc_unit_env_z_ + nj_ecc_water_spacer_z_)
                                           - nj_ecc_unit_env_z_),
                    nj_ecc_unit_env_lv, lv_name, water_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_ecc_unit_env_al_lv[%d][%d]", chamber, unit);
  new G4PVPlacement(nullptr, origin_, nj_ecc_unit_env_al_lv, lv_name, nj_ecc_unit_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_ecc_unit_env_polye_lv[%d][%d]", chamber, unit);
  new G4PVPlacement(nullptr, origin_, nj_ecc_unit_env_polye_lv, lv_name,
                    nj_ecc_unit_env_al_lv, false, det);

  std::snprintf(lv_name, name_length_, "nj_ecc_unit_spacer_lv[%d][%d]", chamber, unit);
  new G4PVPlacement(nullptr, origin_, nj_ecc_unit_spacer_lv, lv_name,
                    nj_ecc_unit_env_polye_lv, false, det);

  G4double posz = nj_ecc_unit_env_z_ - nj_env_thick_ - nj_film_z_;
  int plate = 15 + 2 * unit;
  ConstructNinjaFilm(p_sd_manager, nj_ecc_unit_env_polye_lv, det,
                     B2EmulsionType::kECC, chamber, plate,
                     G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz), nj_ecc_film_xy_,
                     nj_ecc_film_xy_);

  posz -= nj_film_z_ + nj_ecc_fe_z_;
  std::snprintf(lv_name, name_length_, "nj_ecc_fe[%d][%d]", chamber, unit);
  new G4PVPlacement(nullptr, G4ThreeVector(0, -nj_ecc_env_y_ + nj_ecc_film_xy_ + nj_env_thick_, posz), nj_ecc_fe_lv,
                    lv_name,
                    nj_ecc_unit_env_polye_lv, false, det);

  posz -= nj_ecc_fe_z_ + nj_film_z_;
  plate++;
  ConstructNinjaFilm(p_sd_manager, nj_ecc_unit_env_polye_lv, det,
                     B2EmulsionType::kECC, chamber, plate,
                     G4ThreeVector(0, -nj_ecc_env_y_ + nj_env_thick_ + nj_ecc_film_xy_, posz), nj_ecc_film_xy_,
                     nj_ecc_film_xy_);

}

void B2DetectorConstruction::ConstructNinjaWaterSpacer(G4LogicalVolume *water_lv, int det, int chamber, int unit) {

  char lv_name[name_length_];
  auto *nj_ecc_water_spacer_out_ = new G4Box("nj_ecc_water_spacer_out_", nj_ecc_water_spacer_x_, nj_ecc_water_spacer_y_,
                                             nj_ecc_water_spacer_z_);
  auto *nj_ecc_water_spacer_in_ = new G4Box("nj_ecc_water_spacer_in_",
                                            nj_ecc_water_spacer_x_ - nj_ecc_water_spacer_thick_,
                                            nj_ecc_water_spacer_y_ - nj_ecc_water_spacer_thick_ / 2 -
                                            nj_ecc_water_spacer_bottom_thick_ / 2,
                                            nj_ecc_water_spacer_z_);
  G4VSolid *nj_ecc_water_spacer = new G4SubtractionSolid("nj_ecc_water_spacer", nj_ecc_water_spacer_out_,
                                                         nj_ecc_water_spacer_in_, nullptr,
                                                         G4ThreeVector(0, nj_ecc_water_spacer_bottom_thick_ / 2 -
                                                                          nj_ecc_water_spacer_thick_ / 2, 0));
  auto *nj_ecc_water_spacer_lv = new G4LogicalVolume(nj_ecc_water_spacer, Acryl, "nj_ecc_water_spacer_lv");

  // Placement
  G4double posz = nj_water_z_ - 2 * nj_ecc_fe_env_z_
                  - unit * 2 * (nj_ecc_unit_env_z_ + nj_ecc_water_spacer_z_) - 2 * nj_ecc_unit_env_z_ -
                  nj_ecc_water_spacer_z_;
  std::snprintf(lv_name, name_length_, "nj_ecc_water_spacer_lv[%d][%d]", chamber, unit);
  new G4PVPlacement(nullptr, G4ThreeVector(0, -nj_water_y_ + nj_ecc_water_spacer_y_ + nj_env_thick_, posz),
                    nj_ecc_water_spacer_lv, lv_name, water_lv, false, det);

}


void B2DetectorConstruction::ConstructNinjaSSSs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det) {

  for (int packing = 0; packing < 6; packing++) {
    ConstructNinjaOneSSS(p_sd_manager, module_lv, det, packing);
    ConstructNinjaOneSDS(p_sd_manager, module_lv, det, packing);
  }

}

void B2DetectorConstruction::ConstructNinjaOneSSS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det,
                                                  int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_], emulsion_name[name_length_];
  auto *nj_sss_env = new G4Box("nj_sss_env", nj_sss_env_x_, nj_sss_env_y_, nj_sss_env_z_);
  std::snprintf(env_name, name_length_, "nj_sss_env_lv[%d]", packing);
  auto *nj_sss_env_lv = new G4LogicalVolume(nj_sss_env, Nylon, env_name);

  auto *nj_sss_env_al = new G4Box("nj_sss_env_al", nj_sss_env_x_ - nj_env_ny_thick_, nj_sss_env_y_ - nj_env_ny_thick_,
                                  nj_sss_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_sss_env_al_lv[%d]", packing);
  auto *nj_sss_env_al_lv = new G4LogicalVolume(nj_sss_env_al, Al, env_name);

  auto *nj_sss_env_polye = new G4Box("nj_sss_env_polye", nj_sss_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_sss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_sss_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_sss_env_polye_lv[%d]", packing);
  auto *nj_sss_env_polye_lv = new G4LogicalVolume(nj_sss_env_polye, Polyethylene, env_name);

  // Emulsion
  auto *nj_sss_emulsion = new G4Box("nj_sss_emulsion", nj_emulsion_z_, nj_sss_film_y_, nj_sss_film_z_);
  auto *nj_sss_emulsion_lv = new G4LogicalVolume(nj_sss_emulsion, Emulsion, "nj_sss_emulsion_lv");
  nj_sss_emulsion_lv->SetVisAttributes(emulsion_vis_att_);

  auto *nj_sss_base = new G4Box("nj_sss_base", nj_base_z_, nj_sss_film_y_, nj_sss_film_z_);
  auto *nj_sss_base_lv = new G4LogicalVolume(nj_sss_base, Polystyrene, "nj_sss_base_lv");

  auto *nj_sss_ssacryl = new G4Box("nj_sss_ssacryl", nj_sss_ssacryl_x_, nj_sss_film_y_, nj_sss_film_z_);
  auto *nj_sss_ssacryl_lv = new G4LogicalVolume(nj_sss_ssacryl, Acryl, "nj_sss_ssacryl_lv");

  // Placement
  std::snprintf(lv_name, name_length_, "nj_sss_env_lv[%d]", packing);
  new G4PVPlacement(nullptr, G4ThreeVector(nj_ecc_pos_.x() + (nj_desic_x_ + nj_sss_env_x_) * (2 * (packing % 2) - 1),
                                           nj_ecc_pos_.y() + nj_ecc_gap_y_ * (1 - std::floor(packing / 2)),
                                           nj_ecc_pos_.z()), nj_sss_env_lv, lv_name, module_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_sss_env_al_lv[%d]", packing);
  new G4PVPlacement(nullptr, origin_, nj_sss_env_al_lv, lv_name, nj_sss_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_sss_env_polye_lv[%d]", packing);
  new G4PVPlacement(nullptr, origin_, nj_sss_env_polye_lv, lv_name, nj_sss_env_al_lv, false, det);

  int plate = 2 + 4 * (packing % 2);
  G4double posx = -nj_sss_env_x_ + nj_env_thick_;
  posx += nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_ + nj_base_z_;
  std::snprintf(lv_name, name_length_, "nj_sss_base[%d][%d]", packing / 2, plate);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_base_lv, lv_name, nj_sss_env_polye_lv, false, det);
  posx += nj_base_z_ + nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_;

  plate++;
  posx += nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_ + nj_base_z_;
  std::snprintf(lv_name, name_length_, "nj_sss_base[%d][%d]", packing / 2, plate);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_base_lv, lv_name, nj_sss_env_polye_lv, false, det);
  posx += nj_base_z_ + nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_;

  posx += nj_sss_ssacryl_x_;
  std::snprintf(lv_name, name_length_, "nj_sss_ssacryl[%d]", packing);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_ssacryl_lv, lv_name, nj_sss_env_polye_lv, false, det);
  posx += nj_sss_ssacryl_x_;

  plate++;
  posx += nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_ + nj_base_z_;
  std::snprintf(lv_name, name_length_, "nj_sss_base[%d][%d]", packing / 2, plate);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_base_lv, lv_name, nj_sss_env_polye_lv, false, det);
  posx += nj_base_z_ + nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_;

  plate++;
  posx += nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_ + nj_base_z_;
  std::snprintf(lv_name, name_length_, "nj_sss_base[%d][%d]", packing / 2, plate);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_base_lv, lv_name, nj_sss_env_polye_lv, false, det);
  posx += nj_base_z_ + nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sss_env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_;

  //*******Assignment of sensitive detectors*******//
#ifdef NINJA
  p_sd_manager->AddNewDetector(emulsion_sensitive_detector_);
  nj_sss_emulsion_lv->SetSensitiveDetector(emulsion_sensitive_detector_);
#endif

}

void B2DetectorConstruction::ConstructNinjaOneSDS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det,
                                                  int packing) {

  // Envelope
  char env_name[name_length_], lv_name[name_length_], emulsion_name[name_length_];
  auto *nj_sds_env = new G4Box("nj_sds_env", nj_sds_env_x_, nj_sss_env_y_, nj_sss_env_z_);
  std::snprintf(env_name, name_length_, "nj_sds_env_lv[%d]", packing);
  auto *nj_sds_env_lv = new G4LogicalVolume(nj_sds_env, Nylon, env_name);

  auto *nj_sds_env_al = new G4Box("nj_sds_env_al", nj_sds_env_x_ - nj_env_ny_thick_, nj_sss_env_y_ - nj_env_ny_thick_,
                                  nj_sss_env_z_ - nj_env_ny_thick_);
  std::snprintf(env_name, name_length_, "nj_sds_env_al_lv[%d]", packing);
  auto *nj_sds_env_al_lv = new G4LogicalVolume(nj_sds_env_al, Al, env_name);

  auto *nj_sds_env_polye = new G4Box("nj_sds_env_polye", nj_sds_env_x_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_sss_env_y_ - nj_env_ny_thick_ - nj_env_al_thick_,
                                     nj_sss_env_z_ - nj_env_ny_thick_ - nj_env_al_thick_);
  std::snprintf(env_name, name_length_, "nj_sds_env_polye_lv[%d]", packing);
  auto *nj_sds_env_polye_lv = new G4LogicalVolume(nj_sds_env_polye, Polyethylene, env_name);

  // Emulsion
  auto *nj_sss_emulsion = new G4Box("nj_sss_emulsion", nj_emulsion_z_, nj_sss_film_y_, nj_sss_film_z_);
  auto *nj_sss_emulsion_lv = new G4LogicalVolume(nj_sss_emulsion, Emulsion, "nj_sss_emulsion_lv");
  nj_sss_emulsion_lv->SetVisAttributes(emulsion_vis_att_);

  auto *nj_sss_base = new G4Box("nj_sss_base", nj_base_z_, nj_sss_film_y_, nj_sss_film_z_);
  auto *nj_sss_base_lv = new G4LogicalVolume(nj_sss_base, Polystyrene, "nj_sss_base_lv");

  auto *nj_sss_ssacryl = new G4Box("nj_sss_ssacryl", nj_sss_ssacryl_x_, nj_sss_film_y_, nj_sss_film_z_);
  auto *nj_sss_ssacryl_lv = new G4LogicalVolume(nj_sss_ssacryl, Acryl, "nj_sss_ssacryl_lv");

  // Placement
  std::snprintf(lv_name, name_length_, "nj_sds_env_lv[%d]", packing);
  new G4PVPlacement(nullptr, G4ThreeVector(
      nj_ecc_pos_.x() + (nj_desic_x_ + 2 * nj_sss_env_x_ + nj_sds_env_x_) * (2 * (packing % 2) - 1),
      nj_ecc_pos_.y() + nj_ecc_gap_y_ * (1 - std::floor(packing / 2)),
      nj_ecc_pos_.z()), nj_sds_env_lv, lv_name, module_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_sds_env_al_lv[%d]", packing);
  new G4PVPlacement(nullptr, origin_, nj_sds_env_al_lv, lv_name, nj_sds_env_lv, false, det);
  std::snprintf(lv_name, name_length_, "nj_sds_env_polye_lv[%d]", packing);
  new G4PVPlacement(nullptr, origin_, nj_sds_env_polye_lv, lv_name, nj_sds_env_al_lv, false, det);

  G4double posx = -nj_sds_env_x_ + nj_env_thick_;
  if (packing % 2 == 0) {
    posx += nj_sss_ssacryl_x_;
    std::snprintf(lv_name, name_length_, "nj_sds_ssacryl_lv[%d]", packing);
    new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_ssacryl_lv, lv_name, nj_sds_env_polye_lv, false, det);
    posx += nj_sss_ssacryl_x_;
  }

  int plate = 10 * (packing % 2);
  posx += nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sds_env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_ + nj_base_z_;
  std::snprintf(lv_name, name_length_, "nj_sss_base[%d][%d]", packing / 2, plate);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_base_lv, lv_name, nj_sds_env_polye_lv, false, det);
  posx += nj_base_z_ + nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sds_env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_;

  plate++;
  posx += nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sds_env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_ + nj_base_z_;
  std::snprintf(lv_name, name_length_, "nj_sss_base[%d][%d]", packing / 2, plate);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_base_lv, lv_name, nj_sds_env_polye_lv, false, det);
  posx += nj_base_z_ + nj_emulsion_z_;
  std::snprintf(emulsion_name, name_length_, "nj_sss[%d][%d][%d]", packing / 2, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_emulsion_lv, emulsion_name, nj_sds_env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + (packing / 2) * DUMAX
                    + plate * DUMAX * ECCMAX + B2EmulsionType::kSSS * DUMAX * ECCMAX * GELMAX);
  posx += nj_emulsion_z_;

  if (packing % 2 == 1) {
    posx += nj_sss_ssacryl_x_;
    std::snprintf(lv_name, name_length_, "nj_sds_ssacryl_lv[%d]", packing);
    new G4PVPlacement(nullptr, G4ThreeVector(posx, 0, 0), nj_sss_ssacryl_lv, lv_name, nj_sds_env_polye_lv, false, det);
    posx += nj_sss_ssacryl_x_;
  }

  //*******Assignment of sensitive detectors*******//
#ifdef NINJA
  p_sd_manager->AddNewDetector(emulsion_sensitive_detector_);
  nj_sss_emulsion_lv->SetSensitiveDetector(emulsion_sensitive_detector_);
#endif
}

void B2DetectorConstruction::ConstructNinjaFilm(G4SDManager *p_sd_manager, G4LogicalVolume *env_polye_lv, int det,
                                                int film_type, int ecc, int plate,
                                                const G4ThreeVector &pos, double width, double height) {
  auto *nj_emulsion = new G4Box("nj_emulsion", width, height, nj_emulsion_z_);
  auto *nj_emulsion_lv = new G4LogicalVolume(nj_emulsion, Emulsion, "nj_emulsion_lv");
  nj_emulsion_lv->SetVisAttributes(emulsion_vis_att_);

  auto *nj_base = new G4Box("nj_base", width, height, nj_base_z_);
  auto *nj_base_lv = new G4LogicalVolume(nj_base, Polystyrene, "nj_base_lv");

  // Placement
  char emulsion_name[name_length_], base_name[name_length_];

  std::snprintf(emulsion_name, name_length_, "nj_emulsion_lv[%d][%d][%d][%d]",
                film_type, ecc, plate, B2EmulsionLayer::kDownstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(pos.x(), pos.y(), pos.z() + nj_base_z_ + nj_emulsion_z_),
                    nj_emulsion_lv, emulsion_name, env_polye_lv, false,
                    B2EmulsionLayer::kDownstreamGel + ecc * DUMAX
                    + plate * DUMAX * ECCMAX + film_type * DUMAX * ECCMAX * GELMAX);
  std::snprintf(base_name, name_length_, "nj_base_lv[%d][%d][%d]", film_type, ecc, plate);
  new G4PVPlacement(nullptr, pos, nj_base_lv, base_name, env_polye_lv, false, det);
  std::snprintf(emulsion_name, name_length_, "nj_emulsion_lv[%d][%d][%d][%d]",
                film_type, ecc, plate, B2EmulsionLayer::kUpstreamGel);
  new G4PVPlacement(nullptr, G4ThreeVector(pos.x(), pos.y(), pos.z() - nj_base_z_ - nj_emulsion_z_),
                    nj_emulsion_lv, emulsion_name, env_polye_lv, false,
                    B2EmulsionLayer::kUpstreamGel + ecc * DUMAX
                    + plate * DUMAX * ECCMAX + film_type * DUMAX * ECCMAX * GELMAX);

#ifdef NINJA
  p_sd_manager->AddNewDetector(emulsion_sensitive_detector_);
  nj_emulsion_lv->SetSensitiveDetector(emulsion_sensitive_detector_);
#endif
}

void B2DetectorConstruction::ConstructMaterials(B2LogicalVolumeMap module_lv) {

  G4SDManager *p_sd_manager = G4SDManager::GetSDMpointer();

  ConstructProtonModule(p_sd_manager, module_lv.at(B2Detector::kProtonModule), B2Detector::kProtonModule);
  ConstructWagasci(p_sd_manager, module_lv.at(B2Detector::kWagasciUpstream), B2Detector::kWagasciUpstream);
  ConstructWagasci(p_sd_manager, module_lv.at(B2Detector::kWagasciDownstream), B2Detector::kWagasciDownstream);
  ConstructWallMrd(p_sd_manager, module_lv.at(B2Detector::kWallMrdSouth), B2Detector::kWallMrdSouth);
  ConstructWallMrd(p_sd_manager, module_lv.at(B2Detector::kWallMrdNorth), B2Detector::kWallMrdNorth);
  ConstructBabyMind(p_sd_manager, module_lv.at(B2Detector::kBabyMind), B2Detector::kBabyMind);
  ConstructYasuTracker(p_sd_manager, module_lv.at(B2Detector::kBabyMind), B2Detector::kYasuTracker);
  ConstructNinja(p_sd_manager, module_lv.at(B2Detector::kNinja), B2Detector::kNinja);
}

void B2DetectorConstruction::ConstructMagneticField() {
  if (magnetic_field_flag_) {
    BOOST_LOG_TRIVIAL(info) << "Magnetic field on" << G4endl;
    auto *myfield = new B2MagneticFieldWrapper(magfield_table_file_path_);
    G4FieldManager *p_field_manager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    p_field_manager->SetDetectorField(myfield);
    p_field_manager->CreateChordFinder(myfield);
  }
}

void B2DetectorConstruction::DefinePosition() {
  // Origin
  origin_.set(0, 0, 0);

  // Dimensions of the simulated volume
  world_box_.set(0.5 * B2_WORLD_WIDTH, 0.5 * B2_WORLD_HEIGHT, 0.5 * B2_WORLD_DEPTH);

  // B2 hall
  b2_hall_pos_ = origin_;

  // B2 hall dirt
  dirt_radius_min_ = HALL_RADIUS_MIN;
  dirt_radius_max_ = HALL_RADIUS_MAX;
  dirt_height_ = 10. * m;
  dirt_s_phi_ = 0;
  dirt_d_phi_ = CLHEP::pi * 2;
  dirt_pos_.set(WALL_POS_X, WALL_POS_Y, WALL_POS_Z);

  // B2 Floor
  floorup_ = -5.944 * m;

  // Pillars
  // pillar_south_pos_.set((-8.435 + 5.722 + 0.2) * m, (-4.443 + 4.444) * m, (2.631 - 4.2) * m);
  //pillar_north_pos_.set((-8.035 + 5.0 + 5.722 + 0.2) * m, (-4.443 + 4.444) * m, (2.631 - 4.2) * m);
  pillar_south_pos_.set(PILLAR_SOUTH_POS_X, PILLAR_SOUTH_POS_Y, PILLAR_SOUTH_POS_Z);
  pillar_north_pos_.set(PILLAR_NORTH_POS_X, PILLAR_NORTH_POS_Y, PILLAR_NORTH_POS_Z);

  // proton module center
  pm_pos_.set(PROTON_MODULE_POS_X, PROTON_MODULE_POS_Y, PROTON_MODULE_POS_Z);

  // WAGASCI upstream center
  wg_upstream_pos_.set(WAGASCI_UPSTREAM_POS_X, WAGASCI_UPSTREAM_POS_Y, WAGASCI_UPSTREAM_POS_Z);

  // WAGASCI downstream center
  wg_downstream_pos_.set(WAGASCI_DOWNSTREAM_POS_X, WAGASCI_DOWNSTREAM_POS_Y, WAGASCI_DOWNSTREAM_POS_Z);

  // WallMRD south center
  wallmrd_south_pos_.set(WALLMRD_SOUTH_POS_X, WALLMRD_POS_Y, WALLMRD_SOUTH_POS_Z);

  // WallMRD north center
  wallmrd_north_pos_.set(WALLMRD_NORTH_POS_X, WALLMRD_POS_Y, WALLMRD_NORTH_POS_Z);

  // BabyMIND center
  babymind_pos_.set(BABYMIND_POS_X, BABYMIND_POS_Y, BABYMIND_POS_Z);
}

void B2DetectorConstruction::DefineNinjaPosition() {

  // NINJA overall box position
  ninja_pos_.set(NINJA_POS_X, NINJA_POS_Y, NINJA_POS_Z);

  // NINJA rack position in NINJA box
  nj_rack_pos_.set(NINJA_RACK_POS_X, NINJA_RACK_POS_Y, NINJA_RACK_POS_Z);

  // NINJA tracker position in NINJA box
  nj_tracker_pos_.set(NINJA_TRACKER_POS_X, NINJA_TRACKER_POS_Y, NINJA_TRACKER_POS_Z);

  // NINJA TSS position in NINJA box
  nj_tss_pos_.set(NINJA_TSS_POS_X, NINJA_TSS_POS_Y, NINJA_TSS_POS_Z);

  // NINJA shifter position in NINJA box
  nj_shifter_pos_.set(NINJA_SHIFTER_POS_X, NINJA_SHIFTER_POS_Y, NINJA_SHIFTER_POS_Z);

  // NINJA ECC (OSS/SSS) position in NINJA box
  nj_ecc_pos_.set(NINJA_ECC_POS_X, NINJA_ECC_POS_Y, NINJA_ECC_POS_Z);

  // NINJA ECC (OSS/SSS) gap
  nj_ecc_gap_x_ = NINJA_ECC_GAP_X;
  nj_ecc_gap_y_ = NINJA_ECC_GAP_Y;

}

void B2DetectorConstruction::DefineBoxes() {

  // B2 hall box
  b2_hall_box_.set(1.95 * m, 1.45 * m, 4.0 * m);

  // Pillar box
  // pillar_box_.set(0.5 * m, 1.5 * m, 2.0 * m);
  pillar_box_.set(0.5 * PILLAR_WIDTH, 0.5 * PILLAR_HEIGHT, 0.5 * PILLAR_DEPTH);

  // Proton Module box
  pm_box_.set(0.5 * PM_BOX_WIDTH, 0.5 * PM_BOX_HEIGHT, 0.5 * PM_BOX_DEPTH);

  // WAGASCI box
  wagasci_box_.set(0.5 * WGS_BOX_WIDTH, 0.5 * WGS_BOX_HEIGHT, 0.5 * WGS_BOX_DEPTH);
  water_box_.set(0.5 * WGS_WATER_BOX_WIDTH, 0.5 * WGS_WATER_BOX_HEIGHT, 0.5 * WGS_WATER_BOX_DEPTH);
  sus_box_.set(0.5 * WGS_STEEL_BOX_WIDTH, 0.5 * WGS_STEEL_BOX_HEIGHT, 0.5 * WGS_STEEL_BOX_DEPTH);

  // WallMRD box
  wallmrd_box_.set(0.5 * WM_BOX_WIDTH, 0.5 * WM_BOX_HEIGHT, 0.5 * WM_BOX_DEPTH);

  // BabyMIND box
  bm_box_.set(0.5 * BM_BOX_WIDTH, 0.5 * BM_BOX_HEIGHT, 0.5 * BM_BOX_DEPTH);

  // NINJA box
  ninja_box_.set(0.5 * NINJA_BOX_WIDTH, 0.5 * NINJA_BOX_HEIGHT, 0.5 * NINJA_BOX_DEPTH);
}

void B2DetectorConstruction::DefineStructures() {

  // Central iron blocks for WallMRD
  c_iron_wallmrd_x_ = 0.5 * WM_INNER_IRON_PLATE_THICK;
  c_iron_wallmrd_y_ = 0.5 * WM_INNER_IRON_PLATE_HEIGHT;
  c_iron_wallmrd_z_ = 0.5 * WM_INNER_IRON_PLATE_LARGE;

  // Front and rear iron blocks for WallMRD
  f_iron_wallmrd_x_ = 0.5 * WM_FRONT_IRON_PLATE_THICK;
  f_iron_wallmrd_y_ = 0.5 * WM_FRONT_IRON_PLATE_HEIGHT;
  f_iron_wallmrd_z_ = 0.5 * WM_FRONT_IRON_PLATE_LARGE;

  // Side iron blocks for WallMRD
  s_iron_wallmrd_x_ = 0.5 * WM_SIDE_IRON_PLATE_LARGE;
  s_iron_wallmrd_y_ = 0.5 * WM_SIDE_IRON_PLATE_HEIGHT;
  s_iron_wallmrd_z_ = 0.5 * WM_SIDE_IRON_PLATE_THICK;

  // Iron blocks for Baby-MIND
  iron_bm_x_ = 0.5 * BM_IRON_PLATE_WIDTH;
  iron_bm_y_ = 0.5 * BM_IRON_PLATE_HEIGHT;
  iron_bm_z_ = 0.5 * BM_IRON_PLATE_DEPTH;

  // Proton Module
  pm_sci_length_ = 0.5 * PM_SCINTI_BAR_LENGTH;
  pm_ingrid_y_ = 0.5 * PM_INGRID_SCINTI_LARGE;
  pm_ingrid_z_ = 0.5 * PM_INGRID_SCINTI_THICK;
  pm_scibar_y_ = 0.5 * PM_SCIBAR_SCINTI_LARGE;
  pm_front_veto_start_z_ = PM_FRONT_VETO_START_Z;
  pm_non_front_veto_start_z_ = PM_NON_FRONT_VETO_START_Z;
  pm_sci_start_xy_ = PM_SCINTI_START_XY;

  // Proton Module Long veto planes
  pm_long_veto_x_ = 0.5 * PM_LONG_VETO_SCINTI_LENGTH;
  pm_long_veto_y_ = 0.5 * PM_INGRID_SCINTI_THICK;
  pm_long_veto_z_ = 0.5 * PM_INGRID_SCINTI_LARGE;

  // Proton Module Short veto planes
  pm_short_veto_x_ = 0.5 * PM_SHORT_VETO_SCINTI_LENGTH;
  pm_short_veto_y_ = 0.5 * PM_INGRID_SCINTI_THICK;
  pm_short_veto_z_ = 0.5 * PM_INGRID_SCINTI_LARGE;

  // Distance between planes of Proton Module
  pm_0y_1x_plane_dist_ = PM_0Y_1X_PLANE_DISTANCE;
  pm_next_plane_dist_ = PM_NEXT_PLANE_DISTANCE;

  // WAGASCI scitillator dimension
  wg_sci_length_ = 0.5 * WGS_SCINTI_BAR_LENGTH;
  wg_sci_thick_ = 0.5 * WGS_SCINTI_THICK;
  wg_sci_width_ = 0.5 * WGS_SCINTI_LARGE;
  wg_sci_grid_space_ = WGS_GRID_SPACING;
  wg_sci_cut_thick_ = 0.5 * WGS_CUT_THICKNESS;
  wg_sci_cut_depth_ = 0.5 * WGS_CUT_DEPTH;
  wg_offset_xy_grid_ = WGS_OFFSET_XY_GRID;

  // WallMRD scintillator dimension
  wallmrd_sci_x_ = 0.5 * WM_SCINTI_THICK;
  wallmrd_sci_y_ = 0.5 * WM_SCINTI_LENGTH;
  wallmrd_sci_z_ = 0.5 * WM_SCINTI_LARGE;

  // Baby-MIND horizontal scintillator dimension
  h_sci_bm_x_ = 0.5 * BM_HORIZONTAL_SCINTI_LENGTH;
  h_sci_bm_y_ = 0.5 * BM_HORIZONTAL_SCINTI_LARGE;
  h_sci_bm_z_ = 0.5 * BM_HORIZONTAL_SCINTI_THICK;

  // Baby-MIND vertical scintillator dimension
  v_sci_bm_x_ = 0.5 * BM_VERTICAL_SCINTI_LARGE;
  v_sci_bm_y_ = 0.5 * BM_VERTICAL_SCINTI_LENGTH;
  v_sci_bm_z_ = 0.5 * BM_VERTICAL_SCINTI_THICK;

  // Baby MIND YASU scintillator dimension
  yasu_sci_x_ = 0.5 * WM_SCINTI_LENGTH;
  yasu_sci_y_ = 0.5 * WM_SCINTI_LARGE;
  yasu_sci_z_ = 0.5 * WM_SCINTI_THICK;
}

void B2DetectorConstruction::DefineNinjaStructures() {

  // NINJA rack structures
  // Overall 
  nj_rack_x_ = 0.5 * NINJA_RACK_WIDTH;
  nj_rack_y_ = 0.5 * NINJA_RACK_HEIGHT;
  nj_rack_z_ = 0.5 * NINJA_RACK_DEPTH;

  // Pillar
  nj_rack_pillar_x_ = 0.5 * NINJA_RACK_PILLAR_WIDTH;
  nj_rack_pillar_y_ = 0.5 * NINJA_RACK_PILLAR_HEIGHT;
  nj_rack_pillar_z_ = 0.5 * NINJA_RACK_PILLAR_DEPTH;

  // Plate
  nj_rack_plate_x_ = 0.5 * NINJA_RACK_PLATE_WIDTH;
  nj_rack_plate_y_ = 0.5 * NINJA_RACK_PLATE_HEIGHT;
  nj_rack_plate_z_ = 0.5 * NINJA_RACK_PLATE_DEPTH;

  nj_rack_plate_height_[0] = 8. * cm;
  nj_rack_plate_height_[1] = 68. * cm;
  nj_rack_plate_height_[2] = 103. * cm;
  nj_rack_plate_height_[3] = 138. * cm;
  nj_rack_plate_height_[4] = 173. * cm;
  nj_rack_plate_height_[5] = 225.8 * cm;


  // NINJA tracker structures
  // Overall
  nj_tracker_box_xy_ = 0.5 * NINJA_TRACKER_XY;
  nj_tracker_box_z_ = 0.5 * NINJA_TRACKER_DEPTH;

  // Aluminum frame
  nj_tracker_frame_xy_ = nj_tracker_box_xy_;
  nj_tracker_frame_z_ = nj_tracker_box_z_;
  nj_tracker_frame_thick_ = NINJA_TRACKER_FRAME_THICK;

  // PVC structure
  nj_tracker_pvc_pillar_thin_x_ = 0.5 * NINJA_PVC_THIN_PILLAR_WIDTH;
  nj_tracker_pvc_pillar_thick_x_ = 0.5 * NINJA_PVC_THICK_PILLAR_WIDTH;
  nj_tracker_pvc_pillar_y_ = 0.5 * NINJA_PVC_PILLAR_HEIGHT;
  nj_tracker_pvc_pillar_z_ = 0.5 * NINJA_PVC_PILLAR_DEPTH;
  nj_tracker_pvc_plate_x_ = 0.5 * NINJA_PVC_PLATE_WIDTH;
  nj_tracker_pvc_plate_large_y_ = 0.5 * NINJA_PVC_LARGE_PLATE_HEIGHT;
  nj_tracker_pvc_plate_small_y_ = 0.5 * NINJA_PVC_SMALL_PLATE_HEIGHT;
  nj_tracker_pvc_plate_z_ = 0.5 * NINJA_PVC_PLATE_DEPTH;

  // Scintillator length
  nj_horiz_sci_length_ = 0.5 * NINJA_HORIZ_SCI_LENGTH;
  nj_verti_sci_length_ = 0.5 * NINJA_VERTI_SCI_LENGTH;

  // PVC plate gap
  nj_tracker_pvc_plate_gap_ = NINJA_PVC_PLATE_GAP;
  // From PVC pillar edge to PVC plate edge (inside)
  nj_tracker_pvc_pillar_offset_ = 3. * mm;
  // From PVC thick pillar to frame inner edge
  nj_tracker_pvc_remain_x_ = NINJA_PVC_REMAIN_X;
  // From PVC small plate edge to frame inner edge
  nj_tracker_pvc_remain_y_ = NINJA_PVC_REMAIN_Y;
  // Vertical scintillator start point
  nj_tracker_sci_offset_x_ = NINJA_SCI_OFFSET_X;
  // Horizontal scintillator start point
  nj_tracker_sci_offset_y_ = NINJA_SCI_OFFSET_Y;


  // NINJA general structures
  // Emulsion thickness
  nj_emulsion_z_ = 0.5 * NINJA_EMULSION_LAYER_THICK;
  nj_base_z_ = 0.5 * NINJA_BASE_LAYER_THICK;
  nj_film_z_ = 0.5 * NINJA_FILM_THICK;
  nj_film_thick_ = NINJA_FILM_THICK;

  // Envelope thickness
  nj_env_ny_thick_ = NINJA_ENV_NYLON_THICK;
  nj_env_al_thick_ = NINJA_ENV_AL_THICK;
  nj_env_polye_thick_ = NINJA_ENV_POLYE_THICK;
  nj_env_thick_ = NINJA_ENV_THICK;


  // Tracker SS and Shifter common structures
  nj_tss_film_x_ = 0.5 * NINJA_SHIFTER_FILM_WIDTH;
  nj_tss_film_y_ = 0.5 * NINJA_SHIFTER_FILM_HEIGHT;
  nj_tss_env_x_ = nj_tss_film_x_ + nj_env_thick_;
  nj_tss_env_y_ = nj_tss_film_y_ + nj_env_thick_;

  // Tracker SS acryl structure
  nj_tss_acryl_out_x_ = 0.5 * NINJA_TSS_ATTACH_AC_WIDTH;
  nj_tss_acryl_in_x_ = 5. * cm;
  nj_tss_acryl_out_y_ = 0.5 * NINJA_TSS_ATTACH_AC_HEIGHT;
  nj_tss_acryl_in_y_ = 50. * cm;
  nj_tss_acryl_z_ = 0.5 * NINJA_TSS_ATTACH_AC_THICK;

  // Tracker SS structures
  nj_tss_ssacryl_z_ = 0.5 * NINJA_TSS_AC_THICK;
  nj_tss_env_z_ = 4 * nj_film_z_ + nj_tss_ssacryl_z_ + nj_env_thick_;

  // NINJA shifter structures
  // Overall
  nj_shifter_box_x_ = 0.5 * NINJA_SHIFTER_XY;
  nj_shifter_box_y_ = 0.5 * NINJA_SHIFTER_XY;
  nj_shifter_box_z_ = 0.5 * NINJA_SHIFTER_DEPTH;

  // Moving wall structures
  nj_shifter_move_al_x_ = nj_shifter_box_x_;
  nj_shifter_move_al_y_ = nj_shifter_box_y_;
  nj_shifter_move_al_z_ = 4. * mm;
  nj_shifter_move_acryl_z_ = 0.75 * mm;
  nj_shifter_move_env_z_ = 3 * nj_film_z_ + nj_shifter_move_acryl_z_ + nj_env_thick_;

  // Fixed wall structures
  nj_shifter_fix_acryl_z_ = 1. * mm;
  nj_shifter_fix_env_z_ = 4 * nj_film_z_ + nj_shifter_fix_acryl_z_ + nj_env_thick_;

  // Outside SS acryl structures
  nj_oss_acryl_xy_ = 12.5 * cm;
  nj_oss_acryl_z_ = 2. * mm;
  nj_oss_acryl_offset_ = NINJA_OSS_ACRYL_OFFSET;

  // Outside SS structures
  nj_oss_film_x_ = 0.5 * NINJA_OSS_FILM_WIDTH;
  nj_oss_film_y_ = 0.5 * NINJA_OSS_FILM_HEIGHT;
  nj_oss_ssacryl_z_ = 0.5 * NINJA_SS_AC_THICK;
  nj_oss_env_x_ = nj_oss_film_x_ + nj_env_thick_;
  nj_oss_env_y_ = nj_oss_film_y_ + nj_env_thick_;
  nj_oss_env_z_ = 4 * nj_film_z_ + nj_oss_ssacryl_z_ + nj_env_thick_;

  // ECC structures
  nj_desic_x_ = 0.5 * NINJA_DESIC_WIDTH;
  nj_desic_y_ = 0.5 * NINJA_DESIC_HEIGHT;
  nj_desic_z_ = 0.5 * NINJA_DESIC_DEPTH;
  nj_desic_thick_ = NINJA_DESIC_THICK;

  nj_water_x_ = nj_desic_x_ - nj_desic_thick_;
  nj_water_y_ = nj_desic_y_ - nj_desic_thick_;
  nj_water_z_ = nj_desic_z_ - nj_desic_thick_;

  nj_upacryl_z_ = 2.5 * mm;

  nj_ecc_film_xy_ = 0.5 * NINJA_ECC_FILM_XY;

  nj_ecc_fe_z_ = 0.5 * NINJA_IRON_LAYER_THICK;
  nj_ecc_water_layer_z_ = 0.5 * NINJA_WATER_LAYER_THICK;
  nj_ecc_ssacryl_z_ = 0.5 * NINJA_SS_AC_THICK;

  nj_ecc_spacer_thick_ = 1. * cm;
  nj_ecc_spacer_x_ = nj_ecc_film_xy_ + nj_ecc_spacer_thick_;
  nj_ecc_spacer_y_ = nj_ecc_film_xy_ + nj_ecc_spacer_thick_ / 2;
  nj_ecc_fe_spacer_z_ = 15 * nj_film_z_ + 11 * nj_ecc_fe_z_ + nj_ecc_ssacryl_z_;
  nj_ecc_unit_spacer_z_ = 2 * nj_film_z_ + nj_ecc_fe_z_;
  nj_ecc_water_spacer_thick_ = 2. * cm;
  nj_ecc_water_spacer_bottom_thick_ = NINJA_ECC_WATER_SPACER_BOTTOM;
  nj_ecc_water_spacer_x_ = nj_ecc_film_xy_ + nj_ecc_water_spacer_thick_;
  nj_ecc_water_spacer_y_ = 13.5 * cm;
  nj_ecc_water_spacer_z_ = nj_ecc_water_layer_z_;

  nj_ecc_env_x_ = nj_ecc_spacer_x_ + nj_env_thick_;
  nj_ecc_env_y_ = nj_ecc_spacer_y_ + nj_env_thick_;
  nj_ecc_fe_env_z_ = nj_ecc_fe_spacer_z_ + nj_env_thick_;
  nj_ecc_unit_env_z_ = nj_ecc_unit_spacer_z_ + nj_env_thick_;

  // Side SS structures
  nj_sss_film_y_ = 12.5 * cm;
  nj_sss_film_z_ = 12.5 * cm;
  nj_sss_ssacryl_x_ = 0.5 * NINJA_SS_AC_THICK;

  nj_sss_env_x_ = 0.5 * NINJA_SSS_THICK;
  nj_sds_env_x_ = 0.5 * NINJA_SDS_THICK;
  nj_sss_env_y_ = nj_sss_film_y_ + nj_env_thick_;
  nj_sss_env_z_ = nj_sss_film_z_ + nj_env_thick_;

}

void B2DetectorConstruction::DefineVertices() {
  // SciBar Scintillator dimension for PM
  scibar_vertex_x_[0] = -11.7 * mm;
  scibar_vertex_x_[1] = -12.25 * mm;
  scibar_vertex_x_[2] = -12.25 * mm;
  scibar_vertex_x_[3] = -11.7 * mm;
  scibar_vertex_x_[4] = 11.7 * mm;
  scibar_vertex_x_[5] = 12.25 * mm;
  scibar_vertex_x_[6] = 12.25 * mm;
  scibar_vertex_x_[7] = 11.7 * mm;

  scibar_vertex_y_[0] = -6.5 * mm;
  scibar_vertex_y_[1] = -3.5 * mm;
  scibar_vertex_y_[2] = 3.5 * mm;
  scibar_vertex_y_[3] = 6.5 * mm;
  scibar_vertex_y_[4] = 6.5 * mm;
  scibar_vertex_y_[5] = 3.5 * mm;
  scibar_vertex_y_[6] = -3.5 * mm;
  scibar_vertex_y_[7] = -6.5 * mm;

  // INGRID Scintillator dimension for PM
  ingrid_vertex_x_[0] = -23.65 * mm;
  ingrid_vertex_x_[1] = -24.15 * mm;
  ingrid_vertex_x_[2] = -24.15 * mm;
  ingrid_vertex_x_[3] = -23.65 * mm;
  ingrid_vertex_x_[4] = 23.65 * mm;
  ingrid_vertex_x_[5] = 24.15 * mm;
  ingrid_vertex_x_[6] = 24.15 * mm;
  ingrid_vertex_x_[7] = 23.65 * mm;

  ingrid_vertex_y_[0] = -5. * mm;
  ingrid_vertex_y_[1] = -0.5 * mm;
  ingrid_vertex_y_[2] = 0.5 * mm;
  ingrid_vertex_y_[3] = 5. * mm;
  ingrid_vertex_y_[4] = 5. * mm;
  ingrid_vertex_y_[5] = 0.5 * mm;
  ingrid_vertex_y_[6] = -0.5 * mm;
  ingrid_vertex_y_[7] = -5. * mm;

  // WAGASCI Scintillator dimension
  wagasci_vertex_x_[0] = -10.4 * mm;
  wagasci_vertex_x_[1] = -11.8 * mm;
  wagasci_vertex_x_[2] = -11.8 * mm;
  wagasci_vertex_x_[3] = -10.4 * mm;
  wagasci_vertex_x_[4] = 10.9 * mm;
  wagasci_vertex_x_[5] = 11.8 * mm;
  wagasci_vertex_x_[6] = 11.8 * mm;
  wagasci_vertex_x_[7] = 10.9 * mm;

  wagasci_vertex_y_[0] = -1.5 * mm;
  wagasci_vertex_y_[1] = -0.75 * mm;
  wagasci_vertex_y_[2] = 0.75 * mm;
  wagasci_vertex_y_[3] = 1.5 * mm;
  wagasci_vertex_y_[4] = 1.5 * mm;
  wagasci_vertex_y_[5] = 1.0 * mm;
  wagasci_vertex_y_[6] = -1.0 * mm;
  wagasci_vertex_y_[7] = -1.5 * mm;

  // WALLMRD Scintillator dimension
  wallmrd_vertex_x_[0] = -95. * mm;
  wallmrd_vertex_x_[1] = -99. * mm;
  wallmrd_vertex_x_[2] = -99. * mm;
  wallmrd_vertex_x_[3] = -95. * mm;
  wallmrd_vertex_x_[4] = 95. * mm;
  wallmrd_vertex_x_[5] = 99. * mm;
  wallmrd_vertex_x_[6] = 99. * mm;
  wallmrd_vertex_x_[7] = 95. * mm;

  wallmrd_vertex_y_[0] = -3.5 * mm;
  wallmrd_vertex_y_[1] = -1.75 * mm;
  wallmrd_vertex_y_[2] = 1.75 * mm;
  wallmrd_vertex_y_[3] = 3.5 * mm;
  wallmrd_vertex_y_[4] = 3.5 * mm;
  wallmrd_vertex_y_[5] = 1.75 * mm;
  wallmrd_vertex_y_[6] = -1.75 * mm;
  wallmrd_vertex_y_[7] = -3.5 * mm;

  // BabyMIND Vertical Scintillator dimension
  
  bm_vertical_vertex_x_[0] = -100. * mm;
  bm_vertical_vertex_x_[1] = -105.3 * mm;
  bm_vertical_vertex_x_[2] = -105.3 * mm;
  bm_vertical_vertex_x_[3] = -100. * mm;
  bm_vertical_vertex_x_[4] = 100. * mm;
  bm_vertical_vertex_x_[5] = 105.3 * mm;
  bm_vertical_vertex_x_[6] = 105.3 * mm;
  bm_vertical_vertex_x_[7] = 100. * mm;

  bm_vertical_vertex_y_[0] = -3.75 * mm;
  bm_vertical_vertex_y_[1] = -1.875 * mm;
  bm_vertical_vertex_y_[2] = 1.875 * mm;
  bm_vertical_vertex_y_[3] = 3.75 * mm;
  bm_vertical_vertex_y_[4] = 3.75 * mm;
  bm_vertical_vertex_y_[5] = 1.875 * mm;
  bm_vertical_vertex_y_[6] = -1.875 * mm;
  bm_vertical_vertex_y_[7] = -3.75 * mm;
  
  // BabyMIND Horizontal Scintillator dimension
  
  bm_horizontal_vertex_x_[0] = (-7.5/2 + 1) * mm;
  bm_horizontal_vertex_x_[1] = (-7.5/2) * mm;
  bm_horizontal_vertex_x_[2] = (-7.5/2) * mm;
  bm_horizontal_vertex_x_[3] = (-7.5/2 + 1) * mm;
  bm_horizontal_vertex_x_[4] = (7.5/2 - 1) * mm;
  bm_horizontal_vertex_x_[5] = (7.5/2) * mm;
  bm_horizontal_vertex_x_[6] = (7.5/2) * mm;
  bm_horizontal_vertex_x_[7] = (7.5/2 - 1) * mm;

  bm_horizontal_vertex_y_[0] = (31.3/2) * mm;
  bm_horizontal_vertex_y_[1] = (31.3/2 - 1) * mm;
  bm_horizontal_vertex_y_[2] = (-31.3/2 + 1) * mm;
  bm_horizontal_vertex_y_[3] = (-31.3/2) * mm;
  bm_horizontal_vertex_y_[4] = (-31.3/2) * mm;
  bm_horizontal_vertex_y_[5] = (-31.3/2 + 1) * mm;
  bm_horizontal_vertex_y_[6] = (31.3/2 - 1) * mm;
  bm_horizontal_vertex_y_[7] = (31.3/2) * mm;
}

void B2DetectorConstruction::DefineMaterial() {
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4String material, symbol;
  G4int nel;
  G4double iz;

  a = 14.01 * g / mole;
  auto *elN = new G4Element(material = "Nitrogen", symbol = "N", iz = 7., a);
  a = 16.00 * g / mole;
  auto *elO = new G4Element(material = "Oxigen", symbol = "O", iz = 8., a);
  a = 1.01 * g / mole;
  auto *elH = new G4Element(material = "Hydrogen", symbol = "H", z = 1., a);
  a = 12.01 * g / mole;
  auto *elC = new G4Element(material = "Carbon", symbol = "C", z = 6., a);
  a = 28.1 * g / mole;
  auto *elSi = new G4Element(material = "Silicon", symbol = "Si", z = 14., a);
  a = 40.1 * g / mole;
  auto *elCa = new G4Element(material = "Calusium", symbol = "Ca", z = 20., a);
  a = 23.0 * g / mole;
  auto *elNa = new G4Element(material = "Sodium", symbol = "Na", z = 11., a);
  a = 55.8 * g / mole;
  auto *elFe = new G4Element(material = "Iron", symbol = "Fe", z = 26., a);
  a = 27.0 * g / mole;
  auto *elAl = new G4Element(material = "Aluminium", symbol = "Al", z = 13., a);
  a = 58.69 * g / mole;
  auto *elNi = new G4Element(material = "Nickel", symbol = "Ni", z = 28., a);
  a = 51.99 * g / mole;
  auto *elCr = new G4Element(material = "Chromium", symbol = "Cr", z = 24., a);
  a = 35.45 * g / mole;
  auto *elCl = new G4Element(material = "Clorine", symbol = "Cl", z = 17., a);
  a = 79.9 * g / mole;
  auto *elBr = new G4Element(material = "Bromine", symbol = "Br", z = 35., a);
  a = 107.9 * g / mole;
  auto *elAg = new G4Element(material = "Silver", symbol = "Ag", z = 47., a);
  a = 126.9 * g / mole;
  auto *elI = new G4Element(material = "Iodine", symbol = "I", z = 53., a);
  a = 32.07 * g / mole;
  auto *elS = new G4Element(material = "Sulphur", symbol = "S", z = 16., a);
  a = 95.96 * g / mole;
  auto *elMo = new G4Element(material = "Molybdenum", symbol = "Mo", z = 42., a);

  // Air
  density = AIR_DENSITY * mg / cm3;
  air_ = new G4Material(material = "Air", density, nel = 2);
  air_->AddElement(elN, .7);
  air_->AddElement(elO, .3);

  // Iron
  a = 55.845 * g / mole;
  density = IRON_DENSITY * g / cm3;
  iron_ = new G4Material(material = "Iron", z = 26., a, density);

  // Water
  density = 1.000 * g / cm3;
  water_ = new G4Material(material = "Water", density, nel = 2);
  water_->AddElement(elH, 2);
  water_->AddElement(elO, 1);

  // Scintillator
  density = SCINTILLATOR_DENSITY * g / cm3;
  plastic_ = new G4Material(material = "Scintillator", density, nel = 2);
  plastic_->AddElement(elC, 9);
  plastic_->AddElement(elH, 10);

  // Concrete
  density = CONCRETE_DENSITY * g / cm3;
  concrete_ = new G4Material(material = "Concrete", density, nel = 6);
  concrete_->AddElement(elO, .53);
  concrete_->AddElement(elSi, .335);
  concrete_->AddElement(elCa, 0.06);
  concrete_->AddElement(elNa, 0.015);
  concrete_->AddElement(elFe, 0.02);
  concrete_->AddElement(elAl, 0.04);

  // SUS304
  density = 7.93 * g / cm3;
  sus_304_ = new G4Material(material = "SUS304", density, nel = 3);
  sus_304_->AddElement(elFe, 0.72);
  sus_304_->AddElement(elCr, 0.19);
  sus_304_->AddElement(elNi, 0.09);

  // PVC
  density = 1.4 * g / cm3;
  PVC = new G4Material(material = "PVC", density, nel = 3);
  PVC->AddElement(elC, 2);
  PVC->AddElement(elH, 3);
  PVC->AddElement(elCl, 1);

  // Alminum
  a = 26.98 * g / mole;
  density = 2.70 * g / cm3;
  Al = new G4Material(material = "Alminum", z = 13., a, density);

  // Alminum honeycome
  a = 26.98 * g / mole;
  density = 0.68 * g / cm3;
  Alhoney = new G4Material(material = "Alhoney", z = 13., a, density);

  // Acryl
  density = 1.18 * g / cm3;
  Acryl = new G4Material(material = "Acryl", density, nel = 3);
  Acryl->AddElement(elC, 5);
  Acryl->AddElement(elO, 2);
  Acryl->AddElement(elH, 8);

  // Envelope

  // Nylon
  density = 1.15 * g / cm3;
  Nylon = new G4Material(material = "Nylon", density, nel = 4);
  Nylon->AddElement(elC, 1);
  Nylon->AddElement(elO, 1);
  Nylon->AddElement(elN, 1);
  Nylon->AddElement(elH, 1);

  // Polyethylene
  density = 0.90 * g / cm3;
  Polyethylene = new G4Material(material = "Polyethylene", density, nel = 2);
  Polyethylene->AddElement(elC, 2);
  Polyethylene->AddElement(elH, 4);

  // Emulsion
  density = 3.816 * g / cm3;
  Emulsion = new G4Material(material = "Emulsion", density, nel = 8);
  Emulsion->AddElement(elAg, 1.809 / 3.816);
  Emulsion->AddElement(elBr, 1.332 / 3.816);
  Emulsion->AddElement(elI, 0.012 / 3.816);
  Emulsion->AddElement(elC, 0.276 / 3.816);
  Emulsion->AddElement(elH, 0.054 / 3.816);
  Emulsion->AddElement(elO, 0.252 / 3.816);
  Emulsion->AddElement(elN, 0.074 / 3.816);
  Emulsion->AddElement(elS, 0.007 / 3.816);

  // SUS316L
  density = 8.03 * g / cm3;
  SUS316L = new G4Material(material = "SUS316L", density, nel = 4);
  SUS316L->AddElement(elFe, 0.67);
  SUS316L->AddElement(elCr, 0.17);
  SUS316L->AddElement(elNi, 0.14);
  SUS316L->AddElement(elMo, 0.02);

  // Polystyrene for ECC base
  density = 1.032 * g / cm3;
  Polystyrene = new G4Material("Polystyrene", density = 1.032, nel = 2);
  Polystyrene->AddElement(elC, 8);
  Polystyrene->AddElement(elH, 8);
}
