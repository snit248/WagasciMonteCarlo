//
// Created by Giorgio Pintaudi on 8/23/20.
//

#include "B2Enum.hh"
#include <stdexcept>
#include <unordered_map>
#include <string>


B2View readout_to_view(B2Readout readout) {
  switch (readout) {
    case B2Readout::kSideReadout:
    case B2Readout::kLeftReadout:
    case B2Readout::kRightReadout:
      return B2View::kSideView;
    case B2Readout::kTopReadout:
    case B2Readout::kBottomReadout:
      return B2View::kTopView;
    default:
      throw std::invalid_argument("Invalid readout : " + std::to_string(readout));
  }
}

const std::unordered_map<B2Detector, std::string, EnumClassHash> DETECTOR_NAMES = {
    {B2Detector::kProtonModule,      "Proton module"},
    {B2Detector::kWagasciUpstream,   "WAGASCI upstream"},
    {B2Detector::kWagasciDownstream, "WAGASCI downstream"},
    {B2Detector::kWallMrdSouth,      "WallMRD south"},
    {B2Detector::kWallMrdNorth,      "WallMRD north"},
    {B2Detector::kBabyMind,          "BabyMIND"},
    {B2Detector::kYasuTracker,       "YASU tracker"},
    {B2Detector::kNinja,             "NINJA"},
    {B2Detector::kWall,              "B2 floor concrete wall"},
    {B2Detector::kPillarSouth,       "B2 floor south pillar"},
    {B2Detector::kPillarNorth,       "B2 floor north pillar"},
    {B2Detector::kUnknownDetector,   "Unknown detector"}
};

const std::unordered_map<B2Material, std::string, EnumClassHash> MATERIAL_NAMES = {
    {B2Material::kWater,           "Water"},
    {B2Material::kIron,            "Iron"},
    {B2Material::kCarbon,          "Carbon"},
    {B2Material::kConcrete,        "Concrete"},
    {B2Material::kSus304,          "Stainless steel"},
    {B2Material::kUnknownMaterial, "Unknown material"}
};

const std::unordered_map<B2View, std::string, EnumClassHash> VIEW_NAMES = {
    {B2View::kTopView,     "Top view"},
    {B2View::kSideView,    "Side view"},
    {B2View::kUnknownView, "Unknown view"}
};

const std::unordered_map<B2Dimensionality, std::string, EnumClassHash> DIMENSIONALITY_NAMES = {
    {B2Dimensionality::kBidimensional,    "2D"},
    {B2Dimensionality::kTridimensional,   "3D"},
    {B2Dimensionality::kOnePair,          "2D (matching pair not found)"},
    {B2Dimensionality::kUnknownDimension, "Unknown dimensionality"}
};

const std::unordered_map<B2ScintillatorType, std::string, EnumClassHash> SCINTILLATOR_TYPE_NAMES = {
    {B2ScintillatorType::kVertical,                "Vertical"},
    {B2ScintillatorType::kHorizontal,              "Horizontal"},
    {B2ScintillatorType::kVeto,                    "Veto"},
    {B2ScintillatorType::kLeft,                    "Left"},
    {B2ScintillatorType::kRight,                   "Right"},
    {B2ScintillatorType::kUnknownScintillatorType, "Unknown scintillator type"}
};

const std::unordered_map<B2GridPlane, std::string, EnumClassHash> GRID_PLANE_NAMES = {
    {B2GridPlane::kPlaneScintillator,     "Plane scintillator"},
    {B2GridPlane::kGridLeftScintillator,  "Grid scintillator left"},
    {B2GridPlane::kGridRightScintillator, "Grid scintillator right"},
    {B2GridPlane::kUnknownScintillator,   "Unknown scintillator type"}
};


const std::unordered_map<B2Readout, std::size_t, EnumClassHash> READOUT_MAP = {
    {B2Readout::kTopReadout,    1},
    {B2Readout::kSideReadout,   0},
    {B2Readout::kBottomReadout, 0},
    {B2Readout::kLeftReadout,   0},
    {B2Readout::kRightReadout,  1}
};

extern const std::unordered_map<B2Readout, std::string, EnumClassHash> READOUT_NAMES{
    {B2Readout::kTopReadout,    "Top readout"},
    {B2Readout::kSideReadout,   "Side readout"},
    {B2Readout::kBottomReadout, "Bottom readout"},
    {B2Readout::kLeftReadout,   "Left readout"},
    {B2Readout::kRightReadout,  "Right readout"}
};

const std::unordered_map<B2TrackType, std::string, EnumClassHash> TRACKED_PARTICLE_TYPE_NAMES = {
    {B2TrackType::kPrimaryTrack,     "Primary track"},
    {B2TrackType::kSecondaryTrack,   "Secondary track"},
    {B2TrackType::kUnknownTrackType, "Unknown track type"}
};

const std::unordered_map<B2PrimaryTrackType, std::string, EnumClassHash> PRIMARY_TRACK_TYPE_NAMES = {
    {B2PrimaryTrackType::kMatchingTrack,           "Matching Track"},
    {B2PrimaryTrackType::kSingularTrack,           "Singular Track"},
    {B2PrimaryTrackType::kSandMuonNonMatching,     "Sand muon (one detector)"},
    {B2PrimaryTrackType::kSandMuonMatching,        "Sand muon (multiple detectors)"},
    {B2PrimaryTrackType::kBabyMind3DTrack,         "BabyMIND 3D track"},
    {B2PrimaryTrackType::kSingleYASU,              "YASU samples (a TM to YASU)"},
    {B2PrimaryTrackType::kPMtoDWGtoYASU,           "YASU samples (PM to DWG to YASU)"},
    {B2PrimaryTrackType::kUWGtoPMtoDWGtoYASU,      "YASU samples (UWG to PM to DWG to YASU)"},
    {B2PrimaryTrackType::kPMtoYASU,                "YASU samples (PM to YASU)"},
    {B2PrimaryTrackType::kUnknownPrimaryTrackType, "Unknown track type"}
};

const std::unordered_map<B2SecondaryTrackType, std::string, EnumClassHash> SECONDARY_TRACK_TYPE_NAMES = {
    {B2SecondaryTrackType::kMuonDecayNeutrino,                  "Neutrino from muon decay"},
    {B2SecondaryTrackType::kMichelElectron,                     "Michel electron"},
    {B2SecondaryTrackType::kGenericSecondaryTrack,              "Generic secondary track"},
    {B2SecondaryTrackType::kMichelElectronCandidateThatFailed,  "Michel electron removed from preprocess"},
    {B2SecondaryTrackType::kUnknownSecondaryTrackType,          "Unknown track type"}
};

const std::unordered_map<B2EmulsionType, std::string, EnumClassHash> FILMTYPE_NAMES = {
    {B2EmulsionType::kECC,                 "Water/Iron ECC, ISS"},
    {B2EmulsionType::kShifter,             "OSS, Shifter, TSS"},
    {B2EmulsionType::kSSS,                 "SSS, SDS"},
    {B2EmulsionType::kUnknownEmulsionType, "Unknown film type"}

};

const std::unordered_map<B2Detector, double, EnumClassHash> POSITION_OFFSET_X =
    {{B2Detector::kProtonModule,      PROTON_MODULE_POS_X},
     {B2Detector::kWagasciUpstream,   WAGASCI_UPSTREAM_POS_X},
     {B2Detector::kWagasciDownstream, WAGASCI_DOWNSTREAM_POS_X},
     {B2Detector::kWallMrdSouth,      WALLMRD_SOUTH_POS_X},
     {B2Detector::kWallMrdNorth,      WALLMRD_NORTH_POS_X},
     {B2Detector::kBabyMind,          BABYMIND_POS_X},
     {B2Detector::kYasuTracker,       BABYMIND_POS_X},
     {B2Detector::kNinja,             NINJA_POS_X},
     {B2Detector::kWall,              4. * m},
     {B2Detector::kPillarSouth,       PILLAR_SOUTH_POS_X},
     {B2Detector::kPillarNorth,       PILLAR_NORTH_POS_X}};

const std::unordered_map<B2Detector, double, EnumClassHash> POSITION_OFFSET_Y =
    {{B2Detector::kProtonModule,      PROTON_MODULE_POS_Y},
     {B2Detector::kWagasciUpstream,   WAGASCI_UPSTREAM_POS_Y},
     {B2Detector::kWagasciDownstream, WAGASCI_DOWNSTREAM_POS_Y},
     {B2Detector::kWallMrdSouth,      WALLMRD_POS_Y},
     {B2Detector::kWallMrdNorth,      WALLMRD_POS_Y},
     {B2Detector::kBabyMind,          BABYMIND_POS_Y},
     {B2Detector::kYasuTracker,       BABYMIND_POS_Y},
     {B2Detector::kNinja,             NINJA_POS_Y},
     {B2Detector::kWall,              5. * m}, // depends on flux file center
     {B2Detector::kPillarSouth,       PILLAR_SOUTH_POS_Y},
     {B2Detector::kPillarNorth,       PILLAR_NORTH_POS_Y}};

const std::unordered_map<B2Detector, double, EnumClassHash> POSITION_OFFSET_Z =
    {{B2Detector::kProtonModule,      PROTON_MODULE_POS_Z},
     {B2Detector::kWagasciUpstream,   WAGASCI_UPSTREAM_POS_Z},
     {B2Detector::kWagasciDownstream, WAGASCI_DOWNSTREAM_POS_Z},
     {B2Detector::kWallMrdSouth,      WALLMRD_SOUTH_POS_Z},
     {B2Detector::kWallMrdNorth,      WALLMRD_NORTH_POS_Z},
     {B2Detector::kBabyMind,          BABYMIND_POS_Z},
     {B2Detector::kYasuTracker,       BABYMIND_POS_Z},
     {B2Detector::kNinja,             NINJA_POS_Z},
     {B2Detector::kWall,              WALL_POS_Z},
     {B2Detector::kPillarSouth,       PILLAR_SOUTH_POS_Z},
     {B2Detector::kPillarNorth,       PILLAR_NORTH_POS_Z}};

unsigned detector_to_number_readouts(B2Detector detector) {
  switch (detector) {
    case B2Detector::kProtonModule:
    case B2Detector::kWagasciUpstream:
    case B2Detector::kWagasciDownstream:
    case B2Detector::kYasuTracker:
    case B2Detector::kNinja:
      return 1;
    case B2Detector::kWallMrdNorth:
    case B2Detector::kWallMrdSouth:
    case B2Detector::kBabyMind:
      return 2;
    default:
      throw std::invalid_argument("GetNumberReadouts : detector not recognized " + std::to_string(detector));
  }
}

B2Readout detector_to_readout1(B2Detector detector, B2ScintillatorType scintillator_type) {
  switch (detector) {
    case B2Detector::kWallMrdNorth:
    case B2Detector::kWallMrdSouth:
      return B2Readout::kBottomReadout;
    case B2Detector::kBabyMind:
      switch (scintillator_type) {
        case B2ScintillatorType::kVertical:
          return B2Readout::kBottomReadout;
        case B2ScintillatorType::kHorizontal:
          return B2Readout::kLeftReadout;
        default:
          throw std::invalid_argument("GetReadout1 : scintillator type not recognized " +
                                      std::to_string(scintillator_type));
      }
    default:
      throw std::invalid_argument("GetReadout1 : detector not recognized " +
                                  std::to_string(detector));
  }
}

B2Readout detector_to_readout2(B2Detector detector, B2ScintillatorType scintillator_type) {
  switch (detector) {
    case B2Detector::kWallMrdNorth:
    case B2Detector::kWallMrdSouth:
      return B2Readout::kTopReadout;
    case B2Detector::kBabyMind:
      switch (scintillator_type) {
        case B2ScintillatorType::kVertical:
          return B2Readout::kTopReadout;
        case B2ScintillatorType::kHorizontal:
          return B2Readout::kRightReadout;
        default:
          throw std::invalid_argument("GetReadout2 : scintillator type not recognized " +
                                      std::to_string(scintillator_type));
      }
    default:
      throw std::invalid_argument("GetReadout1 : detector not recognized " +
                                  std::to_string(detector));
  }
}

B2Readout detector_to_single_readout(B2Detector detector, B2ScintillatorType scintillator_type, int plane) {
  switch (scintillator_type) {
    case B2ScintillatorType::kVertical:
      switch (detector) {
        case B2Detector::kProtonModule:
        case B2Detector::kWagasciUpstream:
        case B2Detector::kWagasciDownstream:
        case B2Detector::kNinja:
          return B2Readout::kTopReadout;
        default:
          throw std::invalid_argument("GetSingleReadout : detector not recognized " +
                                      std::to_string(detector));
      }
    case B2ScintillatorType::kHorizontal:
      switch (detector) {
        case B2Detector::kProtonModule:
        case B2Detector::kWagasciUpstream:
        case B2Detector::kWagasciDownstream:
        case B2Detector::kNinja:
          return B2Readout::kSideReadout;
        default:
          throw std::invalid_argument("GetSingleReadout : detector not recognized " +
                                      std::to_string(detector));
      }
    case B2ScintillatorType::kLeft:
      return B2Readout::kLeftReadout;
    case B2ScintillatorType::kRight:
      return B2Readout::kRightReadout;
    case B2ScintillatorType::kVeto:
      if (plane == 18 || plane == 20)
        return B2Readout::kSideReadout;
      else
        return B2Readout::kTopReadout;
    default:
      throw std::invalid_argument("GetSingleReadout : scintillator type not recognized " +
                                  std::to_string(scintillator_type));
  }
}

std::vector<B2Readout> detector_to_readouts(B2Detector detector, B2ScintillatorType scintillator_type, int plane) {
  std::vector<B2Readout> readouts;
  if (detector_to_number_readouts(detector) == 1) {
    readouts.push_back(detector_to_single_readout(detector, scintillator_type, plane));
  } else {
    readouts.push_back(detector_to_readout1(detector, scintillator_type));
    readouts.push_back(detector_to_readout2(detector, scintillator_type));
  }
  return readouts;
}

const std::unordered_map<B2InteractionMode, std::string, EnumClassHash> INTERACTION_MODE = {
    {B2InteractionMode::MODE_UNKNOWN,              "Unknown interaction mode"},
    {B2InteractionMode::MODE_CCQE,                 "CCQE (NEU,N -> LEPTON-,P)"},
    {B2InteractionMode::MODE_2P2H,                 "2P2H (NEU,N,P -> LEPTON-,P,P)"},
    {B2InteractionMode::MODE_CC_1PROTON_1PI_PLUS,  "CC 1 pion (NEU,P -> LEPTON-,P,PI+)"},
    {B2InteractionMode::MODE_CC_1PROTON_1PI_ZERO,  "CC 1 pion (NEU,N -> LEPTON-,P,PI0)"},
    {B2InteractionMode::MODE_CC_1NEUTRON_1PI_PLUS, "CC 1 pion (NEU,N -> LEPTON-,N,PI+)"},
    {B2InteractionMode::MODE_CC_COHERENT_PI_PLUS,  "CC coherent pion production (NEU,O(16) -> LEPTON-,O(16),PI+)"},
    {B2InteractionMode::MODE_CC_1PROTON_1GAMMA,    "CC 1 gamma (NEU,N -> LEPTON-,P,GAMMA)"},
    {B2InteractionMode::MODE_CC_MULTI_PI,          "CC multi pion (NEU,(N OR P) -> LEPTON-,(N OR P),MULTI PI)"},
    {B2InteractionMode::MODE_CC_ETA,               "CC eta (NEU,N -> LEPTON-,P,ETA0)"},
    {B2InteractionMode::MODE_CC_LAMBDA,            "CC lambda (NEU,N -> LEPTON-,LAMBDA,K+)"},
    {B2InteractionMode::MODE_CC_DIS,               "CC deep inelastic scattering (NEU,(N OR P) -> LEPTON-,(N OR P),MESONS)"},
    {B2InteractionMode::MODE_CC_DIFFRACTIVE_PI,    "CC diffractive pion production (NEU,(N or P) -> LEPTON-,(P or N),(PI+ or PI-))"},
    {B2InteractionMode::MODE_NC_1NEUTRON_1PI_ZERO, "NC 1 pion (NEU,N -> NEU,N,PI0)"},
    {B2InteractionMode::MODE_NC_1PROTON_1PI_ZERO,  "NC 1 pion (NEU,P -> NEU,P,PI0)"},
    {B2InteractionMode::MODE_NC_1PROTON_1PI_MINUS, "NC 1 pion (NEU,N -> NEU,P,PI-)"},
    {B2InteractionMode::MODE_NC_1NEUTRON_1PI_PLUS, "NC 1 pion (NEU,P -> NEU,N,PI+)"},
    {B2InteractionMode::MODE_NC_COHERENT_PI_ZERO,  "NC coherent pion production (NEU,O(16) -> NEU,O(16),PI0)"},
    {B2InteractionMode::MODE_NC_1NEUTRON_1GAMMA,   "NC 1 gamma (NEU,N -> NEU,N,GAMMA)"},
    {B2InteractionMode::MODE_NC_1PROTON_1GAMMA,    "NC 1 gamma (NEU,P -> NEU,P,GAMMA)"},
    {B2InteractionMode::MODE_NC_MULTI_PI,          "NC multi pion production (NEU,(N OR P) -> NEU,(N OR P),MULTI PI)"},
    {B2InteractionMode::MODE_NC_1NEUTRON_ETA,      "NC eta (NEU,N -> NEU,N,ETA0)"},
    {B2InteractionMode::MODE_NC_1PROTON_ETA,       "NC eta (NEU,P -> NEU,P,ETA0)"},
    {B2InteractionMode::MODE_NC_LAMBDA_KAON_ZERO,  "NC lambda (NEU,N -> NEU,LAMBDA,K0)"},
    {B2InteractionMode::MODE_NC_LAMBDA_KAON_PLUS,  "NC lambda (NEU,P -> NEU,LAMBDA,K+)"},
    {B2InteractionMode::MODE_NC_MESONS,            "NC mesons (NEU,(N OR P) -> NEU,(N OR P),MESONS)"},
    {B2InteractionMode::MODE_NC_DIFFRACTIVE_PI,    "NC diffractive pion production"},
    {B2InteractionMode::MODE_NC_ELASTIC_1PROTON,   "NC elastic (NEU,P -> NEU,P)"},
    {B2InteractionMode::MODE_NC_ELASTIC_1NEUTRON,  "NC elastic (NEU,N -> NEU,N)"}
};
