#ifndef B2DetectorConstruction_H
#define B2DetectorConstruction_H 1

// system includes
#include <unordered_map>

// Geant4 includes
#include <G4SDManager.hh>
#include <G4VUserDetectorConstruction.hh>

// project includes
#include "B2HorizontalSensitiveDetector.hh"
#include "B2VetoSensitiveDetector.hh"
#include "B2VerticalSensitiveDetector.hh"
#include "B2EmulsionSensitiveDetector.hh"
#include "B2Dimension.hh"
#include "B2Const.hh"
#include "B2Enum.hh"

/**
 * class to define and construct the detectors volumes and materials.
 * This is the first step to start a simulation run of the detectos.
 * All the
 */
class B2DetectorConstruction : public G4VUserDetectorConstruction {

public:
  explicit B2DetectorConstruction(const B2Settings &settings, const B2Dimension &dimension);

  /**
   * Main method where all the detectors are constructed. It just calls
   * all the Construct* private methods
   * @return PhysicalVolume object of the world
   */
  G4VPhysicalVolume *Construct() override;

private:

  ///> Water settings : if the WAGASCI modules are filled with water or not
  B2WaterSettings water_settings_;

  ///> True if the Baby MIND magnet is switched on.
  bool magnetic_field_flag_;

  ///> Field map of the magnetic field inside Baby MIND
  const std::string magfield_table_file_path_;

  ///> Path to the output GDML file
  const std::string output_gdml_file_path_;

  ///> object used to get the position coordinates from channel number
  std::reference_wrapper<const B2Dimension> dimension_;

  // Sensitive detectors
  B2VetoSensitiveDetector *veto_scintillators_;
  B2HorizontalSensitiveDetector *horizontal_scintillators_;
  B2VerticalSensitiveDetector *vertical_scintillators_;
  B2EmulsionSensitiveDetector *emulsion_sensitive_detector_;

  // Visibility attributes

  // Pillars (concrete)
  G4VisAttributes *pillar_vis_att_;
  // Hall (concrete)
  G4VisAttributes *hall_vis_att_;
  // Floor (concrete)
  G4VisAttributes *floor_vis_att_;
  // Boxes
  G4VisAttributes *box_vis_att_;
  // Scintillator (plastic)
  G4VisAttributes *sci_vis_att_;
  // Iron
  G4VisAttributes *iron_vis_att_;
  // VETO scintillators (plastic)
  G4VisAttributes *veto_vis_att_;
  // Water
  G4VisAttributes *water_vis_att_;
  // Air
  G4VisAttributes *air_vis_att_;
  // Stainless steel
  G4VisAttributes *sus_vis_att_;
  // Aluminum
  G4VisAttributes *aluminum_vis_att_;
  // PVC
  G4VisAttributes *pvc_vis_att_;
  // Emulsion gel
  G4VisAttributes *emulsion_vis_att_;

  // Scintillator vertices
  static const std::size_t num_scintillator_vertices_ = 8;

  // name length
  static const std::size_t name_length_ = 64;

  // Materials
  G4Material *air_, *iron_, *plastic_, *water_, *concrete_, *sus_304_;

  // Materials for NINJA experiment
  G4Material *PVC, *Al, *Alhoney, *Acryl, *Nylon,  *Polyethylene, *Emulsion, *SUS316L, *Polystyrene;

  // World
  G4VPhysicalVolume *world_pv_;
  G4ThreeVector world_box_;
  G4ThreeVector origin_;

  // B2 hall
  G4ThreeVector b2_hall_box_;
  G4ThreeVector b2_hall_pos_;
  G4double dirt_radius_min_, dirt_radius_max_, dirt_height_, dirt_s_phi_, dirt_d_phi_;
  G4ThreeVector dirt_pos_;
  G4double floorup_;

  // B2 pillar
  G4ThreeVector pillar_box_;
  G4ThreeVector pillar_south_pos_;
  G4ThreeVector pillar_north_pos_;

  // Size of detector boxes
  G4ThreeVector pm_box_;
  G4ThreeVector wagasci_box_;
  G4ThreeVector wallmrd_box_;
  G4ThreeVector bm_box_;
  G4ThreeVector ninja_box_;

  // Position of detector boxes
  G4ThreeVector pm_pos_;
  G4ThreeVector wg_upstream_pos_;
  G4ThreeVector wg_downstream_pos_;
  G4ThreeVector wallmrd_south_pos_;
  G4ThreeVector wallmrd_north_pos_;
  G4ThreeVector babymind_pos_;
  G4ThreeVector ninja_pos_;

  // Proton Module
  G4double pm_sci_length_;
  G4double pm_ingrid_y_, pm_scibar_y_, pm_ingrid_z_;
  G4double pm_sci_start_xy_, pm_front_veto_start_z_;
  G4double scibar_vertex_x_[num_scintillator_vertices_];
  G4double scibar_vertex_y_[num_scintillator_vertices_];
  G4double ingrid_vertex_x_[num_scintillator_vertices_];
  G4double ingrid_vertex_y_[num_scintillator_vertices_];
  G4double pm_non_front_veto_start_z_;
  G4double pm_long_veto_x_, pm_long_veto_y_, pm_long_veto_z_;
  G4double pm_short_veto_x_, pm_short_veto_y_, pm_short_veto_z_;
  G4double pm_0y_1x_plane_dist_, pm_next_plane_dist_;

  // WAGASCI
  G4double wagasci_vertex_x_[num_scintillator_vertices_];
  G4double wagasci_vertex_y_[num_scintillator_vertices_];
  G4ThreeVector sus_box_;
  G4ThreeVector water_box_;
  G4double wg_sci_length_, wg_sci_thick_, wg_sci_width_;
  G4double wg_sci_grid_space_, wg_sci_cut_thick_, wg_sci_cut_depth_;
  G4double wg_offset_xy_grid_;

  // WallMRD
  G4double wallmrd_vertex_x_[num_scintillator_vertices_];
  G4double wallmrd_vertex_y_[num_scintillator_vertices_];

  G4double c_iron_wallmrd_x_, c_iron_wallmrd_y_, c_iron_wallmrd_z_;
  G4double f_iron_wallmrd_x_, f_iron_wallmrd_y_, f_iron_wallmrd_z_;
  G4double s_iron_wallmrd_x_, s_iron_wallmrd_y_, s_iron_wallmrd_z_;
  G4double wallmrd_sci_x_, wallmrd_sci_y_, wallmrd_sci_z_;

  //BabyMIND
  G4double bm_horizontal_vertex_x_[num_scintillator_vertices_];
  G4double bm_horizontal_vertex_y_[num_scintillator_vertices_];
  G4double bm_vertical_vertex_x_[num_scintillator_vertices_];
  G4double bm_vertical_vertex_y_[num_scintillator_vertices_];

  G4double iron_bm_x_, iron_bm_y_, iron_bm_z_;
  G4double h_sci_bm_x_, h_sci_bm_y_, h_sci_bm_z_;
  G4double v_sci_bm_x_, v_sci_bm_y_, v_sci_bm_z_;
  G4double yasu_sci_x_, yasu_sci_y_, yasu_sci_z_;

  // NINJA positions in NINJA box
  G4ThreeVector nj_rack_pos_;
  G4ThreeVector nj_tracker_pos_;
  G4ThreeVector nj_tss_pos_;
  G4ThreeVector nj_shifter_pos_;
  G4ThreeVector nj_ecc_pos_;
  G4double nj_ecc_gap_x_ , nj_ecc_gap_y_;

  // NINJA rack
  G4double nj_rack_x_, nj_rack_y_, nj_rack_z_;
  G4double nj_rack_pillar_x_, nj_rack_pillar_y_, nj_rack_pillar_z_;
  G4double nj_rack_plate_x_, nj_rack_plate_y_, nj_rack_plate_z_;
  G4double nj_rack_plate_height_[6];// Bottom->Top

  // NINJA tracker
  G4double nj_tracker_box_xy_, nj_tracker_box_z_;
  G4double nj_tracker_frame_xy_, nj_tracker_frame_z_;
  G4double nj_tracker_frame_thick_;

  G4double nj_horiz_sci_length_, nj_verti_sci_length_;

  G4double nj_tracker_pvc_pillar_thin_x_, nj_tracker_pvc_pillar_thick_x_, 
    nj_tracker_pvc_pillar_y_, nj_tracker_pvc_pillar_z_;
  G4double nj_tracker_pvc_plate_x_, nj_tracker_pvc_plate_large_y_, 
    nj_tracker_pvc_plate_small_y_, nj_tracker_pvc_plate_z_;
  G4double nj_tracker_pvc_plate_gap_;
  G4double nj_tracker_pvc_pillar_offset_;

  G4double nj_tracker_pvc_remain_x_, nj_tracker_pvc_remain_y_;
  G4double nj_tracker_sci_offset_x_, nj_tracker_sci_offset_y_;

  // Emulsion
  G4double nj_emulsion_z_, nj_base_z_, nj_film_z_, nj_film_thick_;

  // Envelope
  G4double nj_env_ny_thick_, nj_env_al_thick_, nj_env_polye_thick_,
    nj_env_thick_;

  // Tracker SS acryl
  G4double nj_tss_acryl_out_x_, nj_tss_acryl_in_x_,
    nj_tss_acryl_out_y_, nj_tss_acryl_in_y_, nj_tss_acryl_z_;

  // Tracker SS and Shifter common
  G4double nj_tss_film_x_, nj_tss_film_y_, nj_tss_env_x_, nj_tss_env_y_;

  // Tracker SS
  G4double nj_tss_ssacryl_z_, nj_tss_env_z_;

  // Shifter
  G4double nj_shifter_box_x_, nj_shifter_box_y_, nj_shifter_box_z_;
  G4double nj_shifter_move_al_x_, nj_shifter_move_al_y_, nj_shifter_move_al_z_;
  G4double nj_shifter_move_acryl_z_, nj_shifter_move_env_z_;
  G4double nj_shifter_fix_acryl_z_, nj_shifter_fix_env_z_;

  // Outside SS
  G4double nj_oss_acryl_xy_, nj_oss_acryl_z_, nj_oss_acryl_offset_;
  G4double nj_oss_film_x_, nj_oss_film_y_;
  G4double nj_oss_ssacryl_z_;
  G4double nj_oss_env_x_, nj_oss_env_y_, nj_oss_env_z_;

  //ECC
  G4double nj_desic_x_, nj_desic_y_, nj_desic_z_, nj_desic_thick_;
  G4double nj_water_x_, nj_water_y_, nj_water_z_;
  G4double nj_upacryl_z_;
  G4double nj_ecc_film_xy_;
  G4double nj_ecc_fe_z_, nj_ecc_water_layer_z_, nj_ecc_ssacryl_z_;
  G4double nj_ecc_spacer_thick_, nj_ecc_spacer_x_, nj_ecc_spacer_y_;
  G4double nj_ecc_fe_spacer_z_, nj_ecc_unit_spacer_z_;
  G4double nj_ecc_water_spacer_thick_, nj_ecc_water_spacer_bottom_thick_;
  G4double nj_ecc_water_spacer_x_, nj_ecc_water_spacer_y_, nj_ecc_water_spacer_z_;
  G4double nj_ecc_env_x_, nj_ecc_env_y_, nj_ecc_fe_env_z_, nj_ecc_unit_env_z_;

  //SSS
  G4double nj_sss_film_y_, nj_sss_film_z_;
  G4double nj_sss_ssacryl_x_;
  G4double nj_sss_env_x_, nj_sds_env_x_, nj_sss_env_y_, nj_sss_env_z_;

private:

  // YASU tracker uses the same box as BabyMIND
  typedef std::unordered_map<B2Detector, G4LogicalVolume *, EnumClassHash> B2LogicalVolumeMap;

  /**
   * Set the visibility attributes for all the materials
   */
  void SetVisibilityAttributes();

  /**
   * Define the properties of all the materials
   */
  void DefineMaterial();

  /**
   * Define the position of the detectors in the world coordinate system
   */
  void DefinePosition();

  /**
   * Define the private members for all the structural elements of the detectors
   */
  void DefineStructures();

  /**
   * Define the vertices of the scintillators of WAGASCI and Proton Module
   */
  void DefineVertices();

  /**
   * Define the private members for some of the the G4Box and G4Tub
   */
  void DefineBoxes();

  /**
   * Construct the world, floor, pillars and B2 Hall box
   * @return logical volume of the B2 Hall box
   */
  G4LogicalVolume *ConstructHall();

  /**
   * Construct all the detector boxes
   * @param b2_lv B2 Hall logical volume
   * @return array of logical volumes of the detector boxes
   */
  B2LogicalVolumeMap ConstructModules(G4LogicalVolume *b2_lv);

  /**
   * Construct all the internal structures of the detectors
   * @param module_lv array of logical volumes of the detector boxes
   */
  void ConstructMaterials(B2LogicalVolumeMap module_lv);

  /**
   * Construct proton module internal structures
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volumne of the proton module box
   * @param det proton module index
   */
  void ConstructProtonModule(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct WAGASCI internal structures
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volumne of the WAGASCI box
   * @param det WAGASCI index
   */
  void ConstructWagasci(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct WallMRD internal structures
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volumne of the WallMRD box
   * @param det WallMRD index
   */
  void ConstructWallMrd(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct Baby MIND internal structures
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volumne of the Baby MIND box
   * @param det Baby MIND index
   */
  void ConstructBabyMind(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct the magnetic field inside BabyMIND if the magnetic_field_flag is set
   */
  void ConstructMagneticField();

  /**
   * Construct YASU tracker internal structures
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the Baby MIND box
   * @param det YASU tracker index
   */
  void ConstructYasuTracker(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Define the NINJA sub-detectors position in NINJA coordinate system
   */
  void DefineNinjaPosition();

  /**
   * Define the private members for all the structural
   * elements of the NINJA sub-detectors
   */
  void DefineNinjaStructures();

  /**
   * Construct NINJA detector structures
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinja(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA rack
   * @param module_lv logica lvolume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaRack(G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA tracker
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaTracker(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA Tracker SS
   * @param p_sd_manager sensitive detectors manager 
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaTSSs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA Tracker SS unit
   * @param p_sd_manager sensitive detectors manager 
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   * @param packing Tracker SS packing index
   */
  void ConstructNinjaOneTSS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det, int packing);

  /**
   * Construct NINJA shifter
   * @param p_sd_manager sensitive detectors manager 
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaShifter(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA shifter upstream moving wall unit
   * @param p_sd_manager sensitive detectors manager 
   * @param shifter_lv logical volume of the NINJA shifter box
   * @param det NINJA detector index
   * @param packing Shifter packing index
   */
  void ConstructNinjaShifterOneUpMove(G4SDManager *p_sd_manager, G4LogicalVolume *shifter_lv, int det, int packing);

  /**
   * Construct NINJA shifter fixed wall unit
   * @param p_sd_manager sensitive detectors manager 
   * @param shifter_lv logical volume of the NINJA shifter box
   * @param det NINJA detector index
   * @param packing Shifter packing index
   */
  void ConstructNinjaShifterOneFixed(G4SDManager *p_sd_manager, G4LogicalVolume *shifter_lv, int det, int packing);

  /**
   * Construct NINJA shifter downstream moving wall unit
   * @param p_sd_manager sensitive detectors manager 
   * @param shifter_lv logical volume of the NINJA shifter box
   * @param det NINJA detector index
   * @param packing Shifter packing index
   */
  void ConstructNinjaShifterOneDownMove(G4SDManager *p_sd_manager, G4LogicalVolume *shifter_lv, int det, int packing);

  /**
   * Construct NINJA Outside SS
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaOSSs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA Outside SS unit
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   * @param packing Shifter packing index
   */
  void ConstructNinjaOneOSS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det, int packing);

  /**
   * Construct NINJA ECC
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaECCs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /** 
   * Construct NINJA One ECC chamber
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   * @param chamber ECC desiccator index
   */
  void ConstructNinjaOneECC(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det, int chamber);

  /**
   * Construct NINJA Iron ECC
   * @param p_sd_manager sensitive detectors manager
   * @param water_lv NINJA water logical volume
   * @param det NINJA detector index
   * @param chamber ECC desiccator index
   */
  void ConstructNinjaIronECC(G4SDManager *p_sd_manager, G4LogicalVolume *water_lv, int det, int chamber);

  /**
   * Construct NINJA Tracking Unit
   * @param p_sd_manager sensitive detectors manager
   * @param water_lv NINJA water logical volume
   * @param det NINJA detector index
   * @param chamber ECC desiccator index
   * @param unit tracking unit index
   */
  void ConstructNinjaTrackingUnit(G4SDManager *p_sd_manager, G4LogicalVolume *water_lv, int det, int chamber, int unit);

  /**
   * Construct NINJA Tracking Unit
   * @param water_lv NINJA water logical volume
   * @param det NINJA detector index
   * @param chamber ECC desiccator index
   * @param unit tracking unit index
   */
  void ConstructNinjaWaterSpacer(G4LogicalVolume *water_lv, int det, int chamber, int unit);

  /**
   * Construct NINJA Side SS
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   */
  void ConstructNinjaSSSs(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det);

  /**
   * Construct NINJA Side SS Unit
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   * @param packing packing index
   */
  void ConstructNinjaOneSSS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det, int packing);

  /**
   * Construct NINJA Side Doublet Unit
   * @param p_sd_manager sensitive detectors manager
   * @param module_lv logical volume of the NINJA overall box
   * @param det NINJA detector index
   * @param packing packing index
   */
  void ConstructNinjaOneSDS(G4SDManager *p_sd_manager, G4LogicalVolume *module_lv, int det, int packing);

  /**
   * Construct a NINJA emulsion film
   * @param p_sd_manager sensitive detectors manager
   * @param env_polye_lv logical volume of the NINJA envelope the film is contained
   * @param det NINJA detector index
   * @param film_type film type (refer B2Enum)
   * @param ecc ecc id
   * @param plate plate id
   * @param pos film position in env_polye_lv
   * @param width film width
   * @param height film height
   */
  void ConstructNinjaFilm(G4SDManager *p_sd_mangaer, G4LogicalVolume *env_polye_lv, int det,
			  int film_type, int ecc, int plate,
			  const G4ThreeVector &pos, double width, double height);

};

#endif
